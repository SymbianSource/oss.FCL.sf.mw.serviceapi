/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/



// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <hal.h>

#include "tserviceregistrytest.h"
#include "serviceerrno.h"


// Other generated constants
_LIT8(KService, "IService");
_LIT8(KCmdCancel, "Cancel");


_LIT8( KParamFilter, "Filter" );
_LIT8( KServiceName, "ServiceName" );
_LIT8( KInterfaceName, "InterfaceName" );
_LIT8( KVersionList, "VersionList" );




// Constants for supported Operations
_LIT8(KGetList, "GetList");

_LIT8(KBadCmd, "BadCmd");


// Constants for error messages
_LIT8(KErrorMessage, "ErrorMessage");
_LIT(KMessageSeparator, ": ");
_LIT(KInterfaceErrorMessage, "Invalid Interface"); 
_LIT(KMissingArgument, "Input argument was not found.");
_LIT(KBadArgumentType, "Input argument type was wrong.");
_LIT(KInvalidCMD, "Command not supported.");
_LIT(KInvalidCMDOptions, "Invalid command options.");
_LIT(KCallbackNotFound, "Callback was not found for asynchronous method.");
_LIT(KSyncRequestNotSupported, "Synchronous request not supported.");
_LIT(KAsyncRequestNotSupported, "Asynchronous request not supported.");
_LIT(KGeneralErrorMessage, "Error occured during runtime.");
_LIT(KTransactionCancelFailed, "Canceling transaction failed.");
_LIT(KMissingCancelOption, "Cancel option was not set.");

_LIT8(KWild, "*");
 
_LIT8(KErrorCode , "ErrorCode"); 

/*
 * Return Value Identifier in output parameter list.
 */
_LIT8(KReturnValue , "ReturnValue");

/**
 * Command identifier in input parameter list
 */
_LIT8(KCommand, "cmd");

/**
 * Transaction id in output parameter list needed for asynchronous request
 */
_LIT8(KTransactionId, "TransactionID");


_LIT(KInputStart, "InputStart");
_LIT(KInputEnd, "InputEnd");

_LIT(KExpectedStart,"ExpectedStart");
_LIT(KExpectedEnd,"ExpectedEnd");

_LIT(KMapStart,"StartMap");
_LIT(KMapEnd,"EndMap");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CIServiceTestModule::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CIServiceTestModule::Delete() 
    {
    iIface->Close();
    iCriteriaArray.Close();
    delete iServiceHandler;        
    delete iCriteria;    
    for(TInt i=0; i<iExpectedOutPutArray.Count(); i++)
        {
        iExpectedOutPutArray[i]->DecRef();    
        } 
    iExpectedOutPutArray.Reset();       
    }
        

TInt CIServiceTestModule :: HandleNotifyL(TInt /*aCmdId*/,
                            	          TInt /*aEventId*/,
                            	          CLiwGenericParamList& aEventParamList,
                            	          const CLiwGenericParamList& /*aInParamList*/)
    {
    TInt pos = 0 ;
    
    const TLiwGenericParam* param =  NULL;
    const TLiwGenericParam* paramIter =  NULL;
    const CLiwList* pList = NULL;
    CLiwIterable* iter = NULL;
    
    CActiveScheduler::Stop();
    param = aEventParamList.FindFirst(pos, KErrorCode);
    
    if(param)
        {         
        TLiwVariant err = param->Value();
        TInt code = err.AsTInt32(); 
        err.Reset();
        if(code != iExpectedError)
            {                        
            iResult =  KErrGeneral;
            return;    
            }
        } 
        
    pos = 0;         
    paramIter = aEventParamList.FindFirst(pos, KReturnValue);    
    
	iter = paramIter->Value().AsIterable();
	
	if(iter)
    	{
    	if(IsExpectedResult(iter))
            {
            iResult = KErrNone;    
            }     
    	}                      
    
    }
                    
TInt CIServiceTestModule::LoadProviderTest(CStifItemParser& aItem)
    {    
    __UHEAP_MARK;  
    if(iIface)
        {
        iResult = KErrNone;
        }
    else
        {
        iResult = KErrNotFound;
        }   
    iInparams->Reset();    
    iOutparams->Reset();        
    Delete();
    __UHEAP_MARKEND;
    return iResult;
    }

TInt CIServiceTestModule::InvalidServiceValue(CStifItemParser& aItem)
    {
    __UHEAP_MARK;
    TInt pos = 0;
    TReal serviceName = 1.0;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
    pMap->InsertL(KServiceName,TLiwVariant(serviceName));
    iInparams->AppendL(TLiwGenericParam(KParamFilter, TLiwVariant(pMap)));                        
    pMap->DecRef(); 
    
    iIface->ExecuteCmdL(KGetList, 
                        *iInparams, 
                        *iOutparams, 
                        KLiwOptASyncronous, 
                        this);
    
    const TLiwGenericParam* param = iOutparams->FindFirst(pos, KErrorCode); 
      
    TInt code = KErrGeneral;
    if(param)
      {
      TLiwVariant err = param->Value();    
      code = err.AsTInt32();
      err.Reset();     
      }
    if(SErrInvalidServiceArgument == code)
      {
      iResult = KErrNone;
      }
    else
      {
      iResult = KErrGeneral;
      }
    iInparams->Reset();    
    iOutparams->Reset();            
    Delete();
    __UHEAP_MARKEND;
    return iResult;
    }
TInt CIServiceTestModule::InvalidInterfaceValue(CStifItemParser& aItem)
    {
    __UHEAP_MARK;
    TInt pos = 0;
    TReal interfacename = 1.0;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
    pMap->InsertL(KInterfaceName,TLiwVariant(interfacename));
    iInparams->AppendL(TLiwGenericParam(KParamFilter, TLiwVariant(pMap)));                        
    pMap->DecRef(); 
    
    iIface->ExecuteCmdL(KGetList, 
                        *iInparams, 
                        *iOutparams, 
                        KLiwOptASyncronous, 
                        this);
    
    const TLiwGenericParam* param = iOutparams->FindFirst(pos, KErrorCode); 
      
    TInt code = KErrGeneral;
    if(param)
      {
      TLiwVariant err = param->Value();    
      code = err.AsTInt32();
      err.Reset();     
      }
    if(SErrInvalidServiceArgument == code)
      {
      iResult = KErrNone;
      }
    else
      {
      iResult = KErrGeneral;
      }
    iInparams->Reset();    
    iOutparams->Reset();            
    Delete();
    __UHEAP_MARKEND;
    return iResult;
    }

TInt CIServiceTestModule::InvalidMinVerValue(CStifItemParser& aItem)
    {
    __UHEAP_MARK;
    TInt pos = 0;
    TBuf<25> Minver(_L("InvalidVer"));
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
    pMap->InsertL(_L8("MinimumVersion"),TLiwVariant(Minver));
    iInparams->AppendL(TLiwGenericParam(KParamFilter, TLiwVariant(pMap)));                        
    pMap->DecRef(); 
    
    iIface->ExecuteCmdL(KGetList, 
                        *iInparams, 
                        *iOutparams, 
                        KLiwOptASyncronous, 
                        this);
    
    const TLiwGenericParam* param = iOutparams->FindFirst(pos, KErrorCode); 
      
    TInt code = KErrGeneral;
    if(param)
      {
      TLiwVariant err = param->Value();    
      code = err.AsTInt32();
      err.Reset();     
      }
    if(SErrInvalidServiceArgument == code)
      {
      iResult = KErrNone;
      }
    else
      {
      iResult = KErrGeneral;
      }
    iInparams->Reset();    
    iOutparams->Reset();            
    Delete();
    __UHEAP_MARKEND;
    return iResult;
    }
TInt CIServiceTestModule::InvalidMaxVerValue(CStifItemParser& aItem)
    {
    __UHEAP_MARK;
    TInt pos = 0;
    TBuf<25> Maxver(_L("InvalidVer"));
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
    pMap->InsertL(_L8("MaximumVersion"),TLiwVariant(Maxver));
    iInparams->AppendL(TLiwGenericParam(KParamFilter, TLiwVariant(pMap)));                        
    pMap->DecRef(); 
    
    iIface->ExecuteCmdL(KGetList, 
                        *iInparams, 
                        *iOutparams, 
                        KLiwOptASyncronous, 
                        this);
    
    const TLiwGenericParam* param = iOutparams->FindFirst(pos, KErrorCode); 
      
    TInt code = KErrGeneral;
    if(param)
      {
      TLiwVariant err = param->Value();    
      code = err.AsTInt32();
      err.Reset();     
      }
    if(SErrInvalidServiceArgument == code)
      {
      iResult = KErrNone;
      }
    else
      {
      iResult = KErrGeneral;
      }
    iInparams->Reset();    
    iOutparams->Reset();            
    Delete();
    __UHEAP_MARKEND;
    return iResult;
    }

TInt CIServiceTestModule::InvalidFilterValue(CStifItemParser& aItem)
    {
    __UHEAP_MARK;
    TInt pos = 0;    
    CLiwDefaultList* pList= CLiwDefaultList::NewL();   
    iInparams->AppendL(TLiwGenericParam(KParamFilter, TLiwVariant(pList)));                        
    pList->DecRef(); 
    
    iIface->ExecuteCmdL(KGetList, 
                       *iInparams, 
                       *iOutparams, 
                       KLiwOptASyncronous, 
                       this);
    
    const TLiwGenericParam* param = iOutparams->FindFirst(pos, KErrorCode); 
     
    TInt code = KErrGeneral;
    if(param)
     {
     TLiwVariant err = param->Value();    
     code = err.AsTInt32();
     err.Reset();     
     }
    if(SErrInvalidServiceArgument == code)
     {
     iResult = KErrNone;
     }
    else
     {
     iResult = KErrGeneral;
     }
    iInparams->Reset();    
    iOutparams->Reset();            
    Delete();
    __UHEAP_MARKEND;
    return iResult;
    }

TInt CIServiceTestModule::GetListTwice(CStifItemParser& aItem)
    {
    __UHEAP_MARK; 
    TInt pos =0;
    iIface->ExecuteCmdL(KGetList, 
                        *iInparams, 
                        *iOutparams, 
                        KLiwOptASyncronous, 
                        this);
    const TLiwGenericParam* param = iOutparams->FindFirst(pos, KErrorCode); 
        
    TInt code = KErrGeneral;
    if(param)
        {
        TLiwVariant err = param->Value();    
        code = err.AsTInt32();
        err.Reset();     
        }
    if(code == KErrNone)
        {
        iInparams->Reset();    
        iOutparams->Reset();
        iIface->ExecuteCmdL(KGetList, 
                            *iInparams, 
                            *iOutparams, 
                            KLiwOptASyncronous, 
                            this);
        }    
    pos =0;
    const TLiwGenericParam* param1 = iOutparams->FindFirst(pos, KErrorCode); 
            
    TInt code1 = KErrGeneral;
    if(param1)
        {
        TLiwVariant err1 = param1->Value();    
        code1 = err1.AsTInt32();
        err1.Reset();     
        }
        
    if(code1 == SErrServiceInUse)
        {
        iResult = KErrNone;
        }
    else
        {
        iResult = KErrGeneral;
        }
    iInparams->Reset();    
    iOutparams->Reset();
        
    Delete();
    __UHEAP_MARKEND;
    return iResult;
    }

TInt CIServiceTestModule::InvalidCommand(CStifItemParser& aItem)
    {
    __UHEAP_MARK;
    TInt pos = 0;
    iIface->ExecuteCmdL(_L8("Dummy"), 
                        *iInparams, 
                        *iOutparams, 
                        KLiwOptASyncronous, 
                        this);    
    const TLiwGenericParam* param = iOutparams->FindFirst(pos, KErrorCode); 
        
    TInt code = KErrGeneral;
    if(param)
        {
        TLiwVariant err = param->Value();    
        code = err.AsTInt32();
        err.Reset();     
        }
    if(SErrServiceNotSupported == code)
        {
        iResult = KErrNone;
        }
    else
        {
        iResult = KErrNotFound;
            }
    iInparams->Reset();    
    iOutparams->Reset();            
    Delete();
    __UHEAP_MARKEND;
    return iResult;
    }



TInt CIServiceTestModule::CancelInvalidTransID(CStifItemParser& aItem)
    {
    __UHEAP_MARK; 
    TInt pos =0 ;
    iIface->ExecuteCmdL(KGetList, 
                        *iInparams, 
                        *iOutparams, 
                        KLiwOptASyncronous, 
                        this);
                                                                            
    const TLiwGenericParam* param = iOutparams->FindFirst(pos, KErrorCode); 
    
    TInt code = KErrGeneral;
    if(param)
        {
        TLiwVariant err = param->Value();    
        code = err.AsTInt32();
        err.Reset();     
        }
            
    if(code == KErrNone)
        {            
        pos = 0;            
            
        iInparams->Reset();
        iOutparams->Reset();
                        
        iInparams->AppendL(TLiwGenericParam(KTransactionId, TLiwVariant(TInt32(12345))));
     
        iIface->ExecuteCmdL(KCmdCancel, 
                            *iInparams, 
                            *iOutparams, 
                            KLiwOptCancel, 
                            this);                
        pos =0;
        const TLiwGenericParam* paramerr = iOutparams->FindFirst(pos, KErrorCode);
            
        TLiwVariant error = paramerr->Value();    
        code = error.AsTInt32();
        error.Reset();
        
        if(code == SErrNotFound)
            {
            iResult = KErrNone;
            }
        else
            {
            iResult = KErrGeneral;
            } 
        } 
    iInparams->Reset();    
    iOutparams->Reset();
            
    Delete();
    __UHEAP_MARKEND;               
    }


// -----------------------------------------------------------------------------
// CIServiceTestModule::GetListL
// Test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CIServiceTestModule::GetMetaDataListL(CStifItemParser& aItem)
    {
    
    TInt pos = 0;
    iResult = KErrGeneral;
    TInt cancelbit = -1;
    TPtrC nextString; 
    CLiwDefaultMap* pMap = NULL;
           
    __UHEAP_MARK;  
          
    aItem.GetNextInt(iExpectedError); 
    aItem.GetNextInt(cancelbit);       
    aItem.GetNextString(nextString);
    
    if(nextString.CompareF(KInputStart) == 0)
        {       
        pMap = SetInputFilterL(aItem);
        aItem.GetNextString(nextString);
        }
    if(nextString.CompareF(KExpectedStart) == 0)
        { 
        SetExpectedOutputMap(aItem);
        }
    if(pMap)
        {
        iInparams->AppendL(TLiwGenericParam(KParamFilter, TLiwVariant(pMap)));                        
        pMap->DecRef();    
        }
            
    iIface->ExecuteCmdL(KGetList, 
                        *iInparams, 
                        *iOutparams, 
                        KLiwOptASyncronous, 
                        this);
                                                                        
    const TLiwGenericParam* param = iOutparams->FindFirst(pos, KErrorCode); 
    
    TInt code = KErrGeneral;
    if(param)
        {
        TLiwVariant err = param->Value();    
        code = err.AsTInt32();
        err.Reset();     
        }
            
    if(code == KErrNone)
        {
        if(cancelbit == 1)
            {
            pos = 0;
            const TLiwGenericParam* paramtransid = iOutparams->FindFirst(pos, KTransactionId);
            if(paramtransid)
                {
                TLiwVariant trID = paramtransid->Value();                                    
                TInt32 transID =  trID.AsTInt32();                   
                trID.Reset();                
                iInparams->Reset();
                iOutparams->Reset();
                                
                iInparams->AppendL(TLiwGenericParam(KTransactionId, TLiwVariant(transID)));
             
                iIface->ExecuteCmdL(KCmdCancel, 
                                    *iInparams, 
                                    *iOutparams, 
                                    KLiwOptCancel, 
                                    this);                
                pos =0;
                const TLiwGenericParam* paramerr = iOutparams->FindFirst(pos, KErrorCode);
                    
                TLiwVariant error = paramerr->Value();    
                code = error.AsTInt32();
                error.Reset();
                
                if(iExpectedError == code)
                    {
                    iResult = KErrNone;    
                    } 
                }                                    
            }
        else
            CActiveScheduler::Start();    
        } 
    else
        {
        if(iExpectedError == code)
            {
            iResult = KErrNone;    
            }
        }     
                         
    iInparams->Reset();    
    iOutparams->Reset();
    
    Delete();
    
    __UHEAP_MARKEND;                    
    return iResult;    
    }


CLiwDefaultMap* CIServiceTestModule::SetInputFilterL(CStifItemParser& aItem)
    {        
    TPtrC nextString(KNullDesC);            
    
    CLiwDefaultMap* pMap = CLiwDefaultMap :: NewL();
    
    aItem.GetNextString(nextString);
    
    while(nextString.CompareF(KInputEnd) != 0) 
        {            
        TPtrC value(KNullDesC);
                    
        aItem.GetNextString(value);
        
        TBuf8<255> key8bit;        
        key8bit.Copy(nextString);
        
        if(key8bit.CompareF(_L8("MinimumVersion"))==0)
            {            
            TReal version;            
            TLex lex(value);
            lex.Val(version,'.'); 
            aItem.GetNextString(nextString);
            pMap->InsertL(key8bit, version);
            continue;
            }
        if(key8bit.CompareF(_L8("MaximumVersion"))==0)
            {            
            TReal version;            
            TLex lex(value);
            lex.Val(version,'.');
            aItem.GetNextString(nextString);
            pMap->InsertL(key8bit, version);
            continue;
            }
        aItem.GetNextString(nextString);
        
        pMap->InsertL(key8bit, value);                    
        }
                
    return  pMap;  
    }
    

void CIServiceTestModule :: SetExpectedOutputMap(CStifItemParser& aItem)
    {
    TPtrC16 nextString(KNullDesC);   
        
    iLog->Log(_L("Inside SetExpectedOutputMap"));
    
    //aItem.GetNextString(nextString);
    /*
     * The expected output is in the format. 
     * [ExpectredStart StartMap Key Value[...]EndMap[...]ExpectedEnd].     
     */
               
    while(nextString.CompareF(KExpectedEnd)!=0)
        {
        if(nextString.CompareF(KMapStart) == 0)
            {
            CLiwDefaultMap* expectedOutPutMap = CLiwDefaultMap::NewL(); 
            CleanupStack::PushL(expectedOutPutMap);
            aItem.GetNextString(nextString);
            
            while(nextString.CompareF(KMapEnd)!= 0)
                {
                TPtrC key;
                TPtrC value;                
                TBuf8<255> insertKey;                
                                
                key.Set(nextString);
                insertKey.Copy(key);
                
                if(key.CompareF(_L("Version"))==0)
                    {
                    TPtrC ver(KNullDesC);
                    TReal version;
                    aItem.GetNextString(ver);
                    TLex lex(ver);
                    lex.Val(version,'.');                                                            
                    expectedOutPutMap->InsertL(insertKey, version);                    
                    }
                else
                    {
                    aItem.GetNextString(nextString); 
                    value.Set(nextString);
                    expectedOutPutMap->InsertL(insertKey, value);
                    }
                aItem.GetNextString(nextString);
                }
            
            iExpectedOutPutArray.Append(expectedOutPutMap);                        
            CleanupStack::Pop(expectedOutPutMap);
            }
        aItem.GetNextString(nextString);
        }                                                      
    }
   
   
   
TBool  CIServiceTestModule::IsExpectedResult(CLiwIterable* aResultlist)
    {
    TLiwVariant metadata;
    TBool foundMap = EFalse;    
    iLog->Log(_L("Inside IsExpectedResult"));        
    
    for(TInt i = 0; i<iExpectedOutPutArray.Count(); i++)
        
        {                 
        while(aResultlist->NextL(metadata))
            {                      
            const CLiwMap* map =  metadata.AsMap();
            if(map)
                {
                iLog->Log(_L("Map found from iterator"));
                //compare the two maps the result and the expected one.
                if(CompareMaps(iExpectedOutPutArray[i], map))
                    {
                    aResultlist->Reset();
                    metadata.Reset();
                    foundMap = ETrue;                                                            
                    break;
                    }                
                } 
            metadata.Reset();
            }    
        if(foundMap)
            {
            foundMap = EFalse;
            }
        else
            {
            iLog->Log(_L("Expected map not found in the result list"));
            return EFalse;            
            }
        }
    return ETrue;
    }
    
    
           

TBool CIServiceTestModule::CompareMaps(CLiwMap* aExpectedMap,
                                       const CLiwMap* aResultMap)
    {  
    
    iLog->Log(_L("Inside CompareMaps"));
    
    if(!CompareStringResult(KServiceName, aExpectedMap, aResultMap))
        {
        return EFalse;
        }   
    if(!CompareStringResult(KInterfaceName, aExpectedMap, aResultMap))
        {
        return EFalse;
        }
    if(!CompareTRealResult(KVersionList, aExpectedMap, aResultMap))
        {
        return EFalse;
        }  
        
    return ETrue;     
    }
    
    
    
    
/* --------------------------------------------------------------------------
 Ctmediaprovidertesting :: CompareStringResult.
 A static method which compares two string results from the maps.
-----------------------------------------------------------------------------
*/
TBool CIServiceTestModule::CompareStringResult(const TDesC8& aKey,
                                                  CLiwMap* aExpectedMap,
                                                  const CLiwMap* aResultMap)
    {
    TLiwVariant expValue;
    TLiwVariant resValue;       
    TBool equal = EFalse; 
    
    iLog->Log(_L("Inside CompareStringResult"));
    
    if(!aExpectedMap->FindL(aKey, expValue))
        {
        expValue.Reset();
        return ETrue;
        }
    aResultMap->FindL(aKey, resValue);
       
    TPtrC expPtr = expValue.AsDes();
    TPtrC resPtr = resValue.AsDes();
    
    iLog->Log(_L("Expected Value"));
    iLog->Log(expPtr);
    
    iLog->Log(_L("Result Value"));
    iLog->Log(resPtr);
    
    if(expPtr.CompareF(_L("NULL"))!=0)
        {
        if(expPtr.CompareF(resPtr) == 0)
            {
            equal = ETrue;
            }        
        }    
    expValue.Reset();
    resValue.Reset();
    
    return equal;
    }  
    
    
TBool CIServiceTestModule::CompareTRealResult(const TDesC8& aKey,
                                              CLiwMap* aExpectedMap,
                                              const CLiwMap* aResultMap)
    {
    TLiwVariant expValue;
    TLiwVariant resValue; 
        
    TBool equal = EFalse; 
    TReal expValueReal;
    TReal resValueReal;
    
    if(!aExpectedMap->FindL(aKey, expValue))
        {
        expValue.Reset();
        return ETrue;
        }
    else
        {
        expValueReal = expValue.AsTReal();    
        }
        
    if(aResultMap->FindL(KVersionList,resValue))
        {
        TLiwVariant ver;
        const CLiwList* verList =  resValue.AsList();
        if(verList->Count() == 0)
            {
            expValue.Reset();
            resValue.Reset(); 
            return ETrue;    
            }
        for(TInt i = 0; i < verList->Count(); ++i)
            {
            verList->AtL(i,ver);
            resValueReal = ver.AsTReal();   
            }
        ver.Reset();    
        }
     else
         {
         return ETrue;   
         }
                       
    //iLog->Log(_L("Expected Value"));
    //iLog->Log(expValueReal);
        
    //iLog->Log(_L("Result Value"));    
    //iLog->Log(resValueReal);
    
    if(expValueReal == resValueReal)
        {
        equal = ETrue;                    
        }
        
    expValue.Reset();
    resValue.Reset();
    return equal;
    }    
        
  

