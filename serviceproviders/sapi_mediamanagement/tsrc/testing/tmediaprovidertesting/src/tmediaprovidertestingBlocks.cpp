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
#include <StifTestInterface.h>
#include <liwservicehandler.h>
#include<f32file.h>
#include "tmediaprovidertesting.h"
#include "tmediaprovidertesting.hrh"
#include "tmediaobserver.h"



using namespace LIW;

TInt count = 0; 

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctmediaprovidertesting::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctmediaprovidertesting::Delete() 
    {  
    TInt count = iExpectedOutPutArray.Count();
    for(TInt index =0 ;index<count;index++)
        {
        iExpectedOutPutArray[index]->DecRef();	    	
        }    
    iExpectedOutPutArray.Close();    
    iIface->Close();   
    delete iServicehandler;   
    delete iInList;
    delete iOutList;   
    }

// -----------------------------------------------------------------------------
// Ctmediaprovidertesting::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctmediaprovidertesting::RunMethodL(CStifItemParser& aItem) 
    {
    static TStifFunctionInfo const KFunctions[] =
        {          
        ENTRY("GetFilesListL", Ctmediaprovidertesting::GetFilesListL)  , 
        ENTRY("GetListBackToBackCall",Ctmediaprovidertesting::GetListBackToBackCallL)
        };
    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );
    return RunInternalL( KFunctions, count, aItem );
    }
    
// -----------------------------------------------------------------------------
// Callback:: HandleNotifyL
// Call Back Function Called by the Media Management SAPI.
// -----------------------------------------------------------------------------
//        
 TInt Ctmediaprovidertesting:: HandleNotifyL(TInt /*aCmdId*/,
                               TInt aEventId,
                               CLiwGenericParamList& aEventParamList,
                               const CLiwGenericParamList& /*aInParamList*/)
  { 
  TInt pos = 0;
  TInt error = KErrGeneral;
  iResult = KErrGeneral;
  
  TBuf<25> errorcodedes(KNullDesC);
  const TLiwGenericParam* errorCode = NULL;
  const TLiwGenericParam* resultList = NULL;
  CLiwIterable* iterator = NULL;
  
  CActiveScheduler::Stop();
  
  errorCode = aEventParamList.FindFirst(pos, KErrorCode); // Finding Error Code
  resultList = aEventParamList.FindFirst(pos, KResponse); // Finding Iterator for the result list
    
  if(errorCode)
      {
      error = errorCode->Value().AsTInt32();
      errorcodedes.Num(error);
      iLog->Log(_L("Error code:"));
      iLog->Log(errorcodedes);      
      }
  if(iExpErrorCode != error)
      {
      iLog->Log(_L("Expected Error code does not match"));
      User::Leave(KErrGeneral);
      }
  if(resultList)
      {
      iterator = resultList->Value().AsIterable();
      if(IsExpectedResult(iterator))
          {
          iResult = KErrNone;
          }
      }
  else
      {
      if(iExpectedOutPutArray.Count() != 0)
          {
          iLog->Log(_L("Result Iterator Not Found"));
          User::Leave(KErrNotFound);
          }
      }
   return KErrNone;
  }

/* --------------------------------------------------------------------------
 Ctmediaprovidertesting :: GetImageFilesL
 Calls the Getlist of Media management SAPI.
-----------------------------------------------------------------------------
*/
TInt Ctmediaprovidertesting::GetFilesListL( CStifItemParser& aItem )
    {  
    TInt error = KErrGeneral;
    
    LoadServiceL();	
    
    ParseStiffInput(aItem);
	
	iIface->ExecuteCmdL(command8,
                        *iInList,
                        *iOutList,
                        KLiwOptASyncronous,
                        this);    
	TInt pos = 0;
    const TLiwGenericParam* p = iOutList->FindFirst(pos,
                                                    KErrorCode); // Finding Error Code
    if(p)
        {
        TInt retcode = p->Value().AsTInt32();
        if(KErrNone == retcode)
            {
            CActiveScheduler::Start();     
            }
        else
            {
            if(iExpErrorCode == retcode)
                {
                iResult = KErrNone;
                }
            else
                {
                User::Leave(KErrGeneral);
                }             
            }
        }	
   	iInList->Reset();
	iOutList->Reset();
	iLog->Log(_L(""));
    return iResult;
    }
    


/* --------------------------------------------------------------------------
 Ctmediaprovidertesting :: LoadServiceL
 Loads the mediamanagement service.
-----------------------------------------------------------------------------
*/
void Ctmediaprovidertesting :: LoadServiceL()
    {
    TInt pos = 0;  		  	
    iInList = CLiwGenericParamList::NewL();    
    
    iOutList = CLiwGenericParamList::NewL();    
    
    iServicehandler = CLiwServiceHandler::NewL();  
    
    CLiwCriteriaItem* criteria = CLiwCriteriaItem::NewL(1, 
                                                        KIDataSource, 
                                                        KService);    
    CleanupStack :: PushL(criteria);    
    
    criteria->SetServiceClass(TUid::Uid(KLiwClassBase));    
	RCriteriaArray critArray;
	CleanupClosePushL(critArray);
    critArray.AppendL(criteria);
    
    iServicehandler->AttachL(critArray);
    iServicehandler->ExecuteServiceCmdL(*criteria, 
                                       *iInList, 
                                       *iOutList);   
    
    iOutList->FindFirst( pos, KIDataSource );
    if(pos != KErrNotFound)
        {        
        iIface = (*iOutList)[pos].Value().AsInterface();
        }
    else
        {
        User::Leave(KErrNotFound);
        }                                             
    iInList->Reset();
    iOutList->Reset();    
    CleanupStack :: PopAndDestroy(); 
    CleanupStack :: PopAndDestroy(criteria); 
    }           

/*--------------------------------------------------------------------------
 Ctmediaprovidertesting :: LoadServiceL
 Loads the mediamanagement service.
-----------------------------------------------------------------------------
*/
TInt Ctmediaprovidertesting::GetListBackToBackCallL( CStifItemParser& aItem )
    {
    TInt error = KErrGeneral;
     
     LoadServiceL(); 
  //__UHEAP_MARK;
     // Creating callback instance
  TInt a  =User::CountAllocCells();
     CMediaObserver* observer = CMediaObserver::NewL();
     CleanupStack::PushL(observer);
     //Parsing stiff input 
     observer->ParseStiffInput(aItem);
     
     //Creating another callback
     CMediaObserver* observer2 = CMediaObserver::NewL();
     CleanupStack::PushL(observer2);
     //Parsing stiff input 
     observer2->ParseStiffInput(aItem);
   
   // Giving first call  
     iIface->ExecuteCmdL(command8,
                         *(observer->iInList),
                         *(observer->iOutList),
                         KLiwOptASyncronous,
                         observer);    
     TInt pos = 0;
     const TLiwGenericParam* p = observer->iOutList->FindFirst(pos,
                                                     KErrorCode); // Finding Error Code
     //count++;
     if(p)
         {
         TInt retcode = p->Value().AsTInt32();
         if(KErrNone == retcode)
             {
   //          CActiveScheduler::Start();
             //give second call 
             
            iIface->ExecuteCmdL(command8,
                                  *(observer2->iInList),
                                  *(observer2->iOutList),
                                  KLiwOptASyncronous,
                                  observer2);    
             //count++;
             pos =0 ;
             
             const TLiwGenericParam* p = observer2->iOutList->FindFirst(pos,
                                                             KErrorCode); // Finding Error Code
            
             
             if(p)
                 {
                 TInt retcode = p->Value().AsTInt32();
                 if(KErrNone == retcode)
                     {
                     CActiveScheduler::Start();                     
                     }
                 else
                     {
                     if(observer2->iExpErrorCode == retcode)
                         {
                         observer2->iResult = KErrNone;
                         }
                     else
                         {
                         User::Leave(KErrGeneral);
                         }             
                     }

                     }
             
             
                 }
         else
             {  if(observer->iExpErrorCode == retcode)
                 {
                 observer->iResult = KErrNone;
                 }
             else
                 {
                 User::Leave(KErrGeneral);
                 }          
             }
           }   

     if( (KErrNone == observer->iResult) && (KErrNone == observer2->iResult) )
         {
         error = KErrNone ;
         }
     else
         {
         error = KErrGeneral;
         }
     
observer->iInList->Reset();
observer->iOutList->Reset();
     
observer2->iInList->Reset();
observer2->iOutList->Reset();

CleanupStack::PopAndDestroy(observer2);
CleanupStack::PopAndDestroy(observer);
a  =User::CountAllocCells();
a = error;
//__UHEAP_MARKEND;    
    return a;
    }
