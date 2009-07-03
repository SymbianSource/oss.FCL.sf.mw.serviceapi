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
#include <LiwServiceHandler.h>

#include "tmediaprovidertesting.h"
#include "tmediaprovidertesting.hrh"



using namespace LIW;

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
        ENTRY("GetFilesListL", Ctmediaprovidertesting::GetFilesListL)            
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
    CleanupStack :: PopAndDestroy(criteria); 
    critArray.Close();
    }           
