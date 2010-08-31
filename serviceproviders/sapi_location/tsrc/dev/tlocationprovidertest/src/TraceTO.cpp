/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

/*
 * Stray signal test function
 */

#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <lbsrequestor.h>
#include <liwservicehandler.h>
#include <liwcommon.h>
 
 
 #include "tcomplugin.h"
 

 
class TOTraceLoc : public MLiwNotifyCallback
{

    MLiwInterface *iLocationInterface ;
    CLiwGenericParamList *iInputList ;
    TInt cnt;
    public :
    TInt iRetStatus ;
     
    TInt HandleNotifyL(
        TInt aCmdId,
        TInt aEventId,
        CLiwGenericParamList& aEventParamList,
        const CLiwGenericParamList& aInParamList) ;

    TOTraceLoc() : iRetStatus(KErrGeneral),cnt(0) //Default constructor 
        {
            ;
        }
    TOTraceLoc(TInt aCmd , MLiwInterface *aInterface , CLiwGenericParamList *aInputList)     ;
};


TOTraceLoc :: TOTraceLoc(TInt aCmd ,MLiwInterface *aInterface , CLiwGenericParamList *aInputList)
{ 
  cnt = 0;
  iLocationInterface = aInterface ;
  iInputList = aInputList ;
    
}

TInt TOTraceLoc ::  HandleNotifyL(
        TInt aCmdId,
        TInt aEventId,
        CLiwGenericParamList& aEventParamList,
        const CLiwGenericParamList& aInParamList)
{

//DeRefrence Allocated Map first 
    cnt++;
    TInt trid = aCmdId;
   
    if(cnt == 4)
        {
   
        CActiveScheduler::Stop();
        }
     return 0 ;
}
  
  
TInt TraceTOL()
{
__UHEAP_MARK ;
      RFile LogFile ;
      RFs LogSession ;
      TBuf8<50> data ;
      TRealFormat format ;
      CActiveScheduler *Scheduler  = CActiveScheduler :: Current() ;
          
          if(!Scheduler)
          {
              Scheduler = new CActiveScheduler ;
          }
          
         
          CActiveScheduler :: Install(Scheduler) ;
           
      
      
       
       
      _LIT(LogFileNameCancel , "C:\\cancelinvalid.txt") ;
/*
      if(LogFile.Open(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
          if(LogFile.Create(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny ) != KErrNone)
          {
              _LIT(KLog , "Failed to create  log file\n") ;
             
              return KErrGeneral ;
          }

      }
  */    
      _LIT(KLog , "In CancelWithInvalidTransactionID\n") ;
      data.Copy(KLog);
    //  LogFile.Write(data) ;
      
     

      CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

      // Input and output parameter list
      CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
      CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




      CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


      crit->SetServiceClass(TUid::Uid(KLiwClassBase));

      RCriteriaArray a;
      a.AppendL(crit);

      ServiceHandler->AttachL(a) ;
      ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);

       
       

      TInt pos = 0;

      const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

      if(!errorprm)
      {
          
          return KErrGeneral ;
      }


      _LIT8(KDataSource, "ILocation");
       
       pos = 0 ;

      const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

      if(!genericparm)
      {
          
          return KErrGeneral ;
      }

      MLiwInterface* locinterface = (genericparm->Value()).AsInterface();

      
          
      TBuf8<20>CmdBuf(KTraceLocation) ;

      outputlist->Reset() ;
      inputlist->Reset() ;
      TOTraceLoc* callBack = new(ELeave) TOTraceLoc;
     
      //Appending update options
          CLiwMap* updateoptionMap = CLiwDefaultMap::NewL();
          
          TInt32 updateInterval = 2;
          
          updateoptionMap->InsertL(KUpdateOptionInterval,TLiwVariant(updateInterval));
          
          TInt32 updateTimeOut = 3;
          updateoptionMap->InsertL(KUpdateOptionTimeOut,TLiwVariant(updateTimeOut));
          
          TInt32 updateMaxAge = 1;
          updateoptionMap->InsertL(KUpdateOptionMaxAge,TLiwVariant(updateMaxAge));
          
          TLiwGenericParam updateOption(KUpdateOptionMap,TLiwVariant(updateoptionMap));
          inputlist->AppendL(updateOption) ;
          
      locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);
      CActiveScheduler::Start();
      pos = 0 ;

      //const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;
      delete updateoptionMap;
      delete callBack;
      locinterface->Close() ;
      delete ServiceHandler ;
      a.ResetAndDestroy() ;
      a.Close() ;

      __UHEAP_MARKEND ;
      return KErrNone ;



}


TInt TraceTO(TAny */*Arg*/)
{
  
    CTrapCleanup* cleanup = CTrapCleanup::New();
    TInt  Val ;
    //Install a new active scheduler to this thread 
    TRAPD(err ,( Val = TraceTOL()) );
    delete cleanup ;
    
    if(err)
        {
            return err ;
        }
    return Val ;
}

  
