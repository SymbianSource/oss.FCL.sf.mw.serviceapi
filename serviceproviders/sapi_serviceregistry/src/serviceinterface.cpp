/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  
*
*/


#include "serviceinterface.h"

// Including a copy of common constants for this compilation unit
#include "serviceregistryservice.hrh"

// Including utilities
#include "serviceregistryutilities.h"

#include "serviceregistryiterator.h"

#include<hal.h>



//constants for default and invalid versions
const TReal KUnSpMaxVersion = 0.0;  
const TReal KDefaultMinVersion = 1.0;
//thread name
_LIT(KThreadName,"ListThread");


// -----------------------------------------------------------------------------
// CServiceInterface::NewLC
// Returns the instance of CServiceInterface.
// -----------------------------------------------------------------------------
//
CServiceInterface* CServiceInterface::NewL()
    {
    CServiceInterface* self = new(ELeave) CServiceInterface();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CServiceInterface::~CServiceInterface
// Destructor of class
// -----------------------------------------------------------------------------
//
CServiceInterface::~CServiceInterface()
    {
    Cancel();
    iThread.Close();            
    delete iServiceHandler;  
    iServiceHandler  =  NULL;

    delete iServiceName;
    iServiceName  =  NULL;

    delete iInterfaceName;    
    iInterfaceName =  NULL;
    }


void CServiceInterface :: RCriteriaArrayCleanup(TAny* aParam)
    {
    RCriteriaArray* ptr = reinterpret_cast<RCriteriaArray*>(aParam);
    ptr->ResetAndDestroy();  
    delete ptr;  
    }
// -----------------------------------------------------------------------------
// CServiceInterface::ExecuteCmdL
// Request handler method of interface class
// -----------------------------------------------------------------------------
//
void CServiceInterface::ExecuteCmdL(const TDesC8& aCmdName,
                                    const CLiwGenericParamList& aInParamList,
                                    CLiwGenericParamList& aOutParamList,
                                    TUint aCmdOptions ,
                                    MLiwNotifyCallback* aCallBack)
    {
    TInt errCode(KErrNone);

    // Process the command.
    TRAP( errCode, ProcessCommandL(aCmdName, 
                                   aInParamList, 
                                   aOutParamList, 
                                   aCmdOptions, 
                                   aCallBack));
    // Checking error code in here.
    // If any error has been occurred then it is inserted into output list.
    
    
    if(errCode != KErrNone)    
        {
        TServiceRegistryUtilities utils;
        TLiwVariant retErrCode;
        retErrCode.Set(TInt32(utils.GetSapiErrorCode(errCode)));
        TLiwGenericParam errTypeParam(KErrorCode, retErrCode);
        aOutParamList.AppendL(errTypeParam);        
        }
    }
// -----------------------------------------------------------------------------
// CServiceInterface::ExecuteServiceCommandL
// Request handler method of interface class
// -----------------------------------------------------------------------------
//
void CServiceInterface::ExecuteServiceCommandL(const TDesC8& aCmdName,
                                               const CLiwGenericParamList& aInParamList,
                                               CLiwGenericParamList& aOutParamList,
                                               TUint aCmdOptions ,
                                               MLiwNotifyCallback* aCallBack)
    {
    ExecuteCmdL(aCmdName, 
                aInParamList, 
                aOutParamList, 
                aCmdOptions, 
                aCallBack);
    }


// -----------------------------------------------------------------------------
// CServiceInterface::ProcessCommandL
// Method that processes calls of interface class
// -----------------------------------------------------------------------------
//
void CServiceInterface::ProcessCommandL(const TDesC8& aCmdName,
                                        const CLiwGenericParamList& aInParamList,
                                        CLiwGenericParamList& aOutParamList,
                                        TUint aCmdOptions ,
                                        MLiwNotifyCallback* aCallBack)
    {
    TInt32 transactionID(aCallBack->GetTransactionID());

    if(aCmdName.CompareF(KGetList) == 0)
        {
        // If requesting asynchronous service
        if (aCmdOptions & KLiwOptASyncronous) // Asynchronous request
            {
            // Asynchronous request is supported
            if (aCallBack) // Callback object must be passed
                {
                GetListL(aInParamList, aOutParamList, transactionID, aCallBack);
                }
            else
                {
                // Asynchronous request did not have callback object available                                
                User::Leave(KErrArgument);
                }
            }
            else 
            {
            // Synchronous request not supported for this method.            
            User::Leave(KErrNotSupported);
            }
        }//GetList
    else if(aCmdName.CompareF(KCmdCancel) == 0)
        {
        // TServiceRegistryUtilities utility class instance
        TServiceRegistryUtilities utils;
        TInt32 transID(utils.ConvertInputInt32L(aInParamList, 
                                                KTransactionId));
        if(KLiwOptCancel & aCmdOptions)
            {                        
            if(transID != iTransactionId)
                {               
                User::Leave(KErrNotFound);
                }            
            Cancel();
            aOutParamList.AppendL(TLiwGenericParam(KErrorCode, 
                                  TLiwVariant((TInt32)SErrNone)));    
            }
        else
            {           
            User::Leave(KErrNotSupported);
            }
        }//Cancel
    else
        {        
        User::Leave(KErrNotSupported);//Command is not supported
        }
    // Sending transaction ID back to the client in case of an successful asynchronous call
    if (aCallBack && aCmdOptions == KLiwOptASyncronous)
        {
        aOutParamList.AppendL(TLiwGenericParam(KTransactionId, 
                              TLiwVariant((TInt32)transactionID)));
        }
    }

// -----------------------------------------------------------------------------
// CServiceInterface::CServiceInterface
// Constructor of class
// -----------------------------------------------------------------------------
//
CServiceInterface::CServiceInterface()
                       :CActive(EPriorityStandard),
                        iTransactionId(0),
                        iServiceName(NULL),
                        iInterfaceName(NULL),
                        iMinVersion(KUnSpMaxVersion),
                        iMaxVersion(KUnSpMaxVersion),
                        iInParamList(NULL),
                        iServiceHandler(NULL)                        
    {
    CActiveScheduler::Add(this);
    }

// -----------------------------------------------------------------------------
// CServiceInterface::ConstructL
// Two-phased constructor of class
// -----------------------------------------------------------------------------
//
void CServiceInterface::ConstructL()
    {
    iServiceHandler = CLiwServiceHandler :: NewL();
    iServiceName =  KNullDesC8().Alloc();
    iInterfaceName = KNullDesC8().Alloc();
    }
    
// -----------------------------------------------------------------------------
// CServiceInterface::ListServiceProvidersL
// This class is called once the async request is complete 
// It puts the iterator into the ouputlist and calls the HnadleNotifyL.
// -----------------------------------------------------------------------------
//    
void CServiceInterface :: ListServiceProvidersL(TInt32 aError)
    {
    CLiwGenericParamList* eventParamList = CLiwGenericParamList::NewL();
    CleanupStack::PushL(eventParamList);
          
    TInt event = KLiwEventError;    
                                                       
    eventParamList->AppendL(TLiwGenericParam(KErrorCode, 
                            TLiwVariant(aError)));
    if(aError == KErrNone)
        {    
        event =  KLiwEventCompleted;       
        eventParamList->AppendL(TLiwGenericParam(KReturnValue, 
                                TLiwVariant(iIterator)));                             
        iIterator->DecRef(); 
        }                            
                                     
    TRAPD(err, iCallback->HandleNotifyL((TInt32)iTransactionId, 
                                         event, 
                                         *eventParamList, 
                                         *iInParamList));
                                                
    //eventParamList->Reset();                                                                                                                                                                        
    CleanupStack::PopAndDestroy(eventParamList);          
    }
   
   

// -----------------------------------------------------------------------------
// This funtion runs as a part of the thread and fetches the list of providers 
// creates the iterator to the list.
// -----------------------------------------------------------------------------
//

void GetListProviderL(CServiceInterface* aInterface)
    {             
    CLiwMap* pMetaDataMap = NULL;    // map with key as "range" and value as a List
    CLiwList* pRangeList = NULL;                                              
    RCriteriaArray* interest = new(ELeave) RCriteriaArray;
    RCriteriaArray* providerList = new(ELeave) RCriteriaArray;

    CleanupStack::PushL(TCleanupItem(CServiceInterface::RCriteriaArrayCleanup, interest));
    CleanupStack::PushL(TCleanupItem(CServiceInterface::RCriteriaArrayCleanup, providerList));
        
    if(aInterface->iServiceName->CompareF(KNullDesC8) == 0)
        {
        delete aInterface->iServiceName; 
        aInterface->iServiceName = KWild().Alloc();                           
        }
    if(aInterface->iInterfaceName->CompareF(KNullDesC8) == 0)
        {
        delete aInterface->iInterfaceName;
        aInterface->iInterfaceName = KWild().Alloc();            
        }
                
    //To Query for a list of all the LIW providers present.        
    CLiwCriteriaItem* criteria = CLiwCriteriaItem::NewL(1, 
                                                        *aInterface->iInterfaceName, 
                                                        *aInterface->iServiceName);
    //delete the member variables so that they cab be used again
    // for the next call.
    
    delete aInterface->iServiceName;
    aInterface->iServiceName = KNullDesC8().Alloc();
    delete aInterface->iInterfaceName;
    aInterface->iInterfaceName = KNullDesC8().Alloc();
                                                        
    CleanupStack::PushL(criteria);
        
    if(aInterface->iMinVersion != KUnSpMaxVersion || aInterface->iMaxVersion != KUnSpMaxVersion)
        {        
        pMetaDataMap = CLiwDefaultMap::NewL();    // map with key as "range" and value as a List
        CleanupStack::PushL(pMetaDataMap);
        
        pRangeList = CLiwDefaultList::NewL();    // List where the values such as "ver" , minimum and maximum will be stored
        CleanupStack::PushL(pRangeList);
                                                   
        pRangeList->AppendL(TLiwVariant(KVersion)); // "ver" is the string representing VERSION information in metadata                
        
        pRangeList->AppendL(TLiwVariant(aInterface->iMinVersion)); // minimum range - The service should contain version only above this    
        
        pRangeList->AppendL(TLiwVariant(aInterface->iMaxVersion)); // maximum range - The service should contain version only below this    
                           
        pMetaDataMap->InsertL(KRange, pRangeList);         // "range" is set as key and the value is the List created above
    	criteria->SetMetaDataOptions(pMetaDataMap);		
    	
        pRangeList->DecRef();                              // Decrementing the reference of the List
        pMetaDataMap->DecRef();                            // Decrementing the reference of the Map 
                  
        CleanupStack::Pop(pRangeList);
        CleanupStack::Pop(pMetaDataMap);
        }
    //reset the version members to unspecified.
    aInterface->iMinVersion = KUnSpMaxVersion;
    aInterface->iMaxVersion = KUnSpMaxVersion;
    
    //Presently this value is changed to differentiate LIW Providers from other Ecom plug-ins.    
    criteria->SetServiceClass(TUid::Uid(KLiwClassBase));        
                  
    interest->AppendL(criteria);
    CleanupStack::Pop(criteria); 
                     
    aInterface->iServiceHandler->QueryImplementationL(*interest, *providerList); 
               
    aInterface->iIterator = CSvcRegIterator :: NewL();       
    
    aInterface->iIterator->SetProviderDataList(providerList);
            
    CleanupStack::Pop(providerList);    
    CleanupStack::PopAndDestroy(interest); 
    
}


// -----------------------------------------------------------------------------
// Thread Function which calls the  GetListProviderL
// -----------------------------------------------------------------------------
// 
TInt ThreadListProvider(TAny* aData)
    {
    CTrapCleanup* cleanup=CTrapCleanup::New(); // get clean-up stack    
    CServiceInterface* svcifc = reinterpret_cast<CServiceInterface*> (aData);
    TRAPD(err, GetListProviderL(svcifc));    
    delete cleanup;        
    User::Exit(err);
    return 0;
    } 
      
// -----------------------------------------------------------------------------
// CServiceInterface::GetListL
// Gets the list of ServiceProviders.
// -----------------------------------------------------------------------------
//

void  CServiceInterface::GetListL(const CLiwGenericParamList& aInParamList, 
                                  CLiwGenericParamList&  aOutParamList, 
                                  TInt32 aTransactionId, 
                                  MLiwNotifyCallback* aCallBack)                                   
    {
    TInt pos =  0;    
    TLiwVariant minver;
    TLiwVariant maxver;
    TLiwVariant serviceName;    
    TLiwVariant interfaceName;    
    
    const CLiwMap* pMap = NULL;
    const TLiwGenericParam* paramFilterMap = NULL;
    
    iCallback =  aCallBack;
    iTransactionId =  aTransactionId;    
                                                                                      
    paramFilterMap  = aInParamList.FindFirst(pos, KParamFilter);
    
    if(paramFilterMap)
        {
        pMap = paramFilterMap->Value().AsMap(); 
        if(pMap)
            {                           
            if( pMap->FindL(KServiceName, serviceName))
                {
                if ( serviceName.TypeId() != LIW::EVariantTypeDesC )
                    {
                    serviceName.Reset();
                    User::Leave( KErrArgument );
                    }
                delete iServiceName;
                iServiceName = NULL;
                iServiceName = HBufC8::NewL(serviceName.AsDes().Length());
                iServiceName->Des().Copy(serviceName.AsDes());    
                }            
            if( pMap->FindL(KInterfaceName, interfaceName))
                {
                if ( interfaceName.TypeId() != LIW::EVariantTypeDesC )
                    {
                    serviceName.Reset();
                    interfaceName.Reset();     
                    User::Leave( KErrArgument );
                    }
                delete iInterfaceName;
                iInterfaceName = NULL;
                iInterfaceName = HBufC8::NewL(interfaceName.AsDes().Length());
                iInterfaceName->Des().Copy(interfaceName.AsDes());    
                }                              
            if( pMap->FindL(KMinVersion, minver))
                {
                if ( minver.TypeId() != LIW::EVariantTypeTReal && minver.TypeId() != LIW::EVariantTypeTInt32)
                    {
                    minver.Reset();
                    serviceName.Reset();
                    interfaceName.Reset();     
                    User::Leave( KErrArgument );
                    }
                iMinVersion = minver.AsTReal();
                }
            if( pMap->FindL(KMaxVersion, maxver))
               { 
               if ( maxver.TypeId() != LIW::EVariantTypeTReal  && maxver.TypeId() != LIW::EVariantTypeTInt32 )
                   {
                   minver.Reset();
                   maxver.Reset();
                   serviceName.Reset();
                   interfaceName.Reset();     
                   User::Leave( KErrArgument );
                   }
               iMaxVersion = maxver.AsTReal();
               //set the min version to default only if max version is specified.                
               if(iMinVersion == KUnSpMaxVersion)
                   iMinVersion = KDefaultMinVersion;  
               }                               
        if(iMaxVersion != KUnSpMaxVersion)
            {
             if(iMaxVersion < iMinVersion)
                {
                minver.Reset();
                maxver.Reset();
                serviceName.Reset();
                interfaceName.Reset();               
                User::Leave(KErrArgument);    
                }                 
            }                      
        } 
    else
        {
        minver.Reset();
        maxver.Reset();
        serviceName.Reset();
        interfaceName.Reset();               
        User::Leave(KErrArgument);  
        }
        }        
    minver.Reset();
    maxver.Reset();  
    serviceName.Reset();
    interfaceName.Reset();     
           
    if(!IsActive())
        {
        User::LeaveIfError(iThread.Create(KThreadName, 
                           ThreadListProvider, 
                           KDefaultStackSize,
                           &User::Allocator(),
                           this));
        }
    else
        {
        User::Leave(KErrInUse);
        }            
    iStatus = KRequestPending;        
    SetActive();    
    iThread.Resume();          
    iThread.Logon(iStatus);      
    // append the error code to the outputlist.
    aOutParamList.AppendL(TLiwGenericParam(KErrorCode, 
                          TLiwVariant(TInt32(SErrNone))));
    }

void CServiceInterface :: DoCancel()
    {
    iThread.Kill(KErrNone); 
    iThread.Close();
    }
    
    
void CServiceInterface :: RunL()
    {
    iThread.Close();           
    ListServiceProvidersL(iStatus.Int());        
    }    
    
