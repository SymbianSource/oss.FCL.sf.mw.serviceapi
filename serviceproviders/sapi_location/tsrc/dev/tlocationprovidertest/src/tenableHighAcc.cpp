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
 * Enable High Accuracy params
 */

#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <LbsRequestor.h>
#include <LiwServiceHandler.h>
#include <LiwCommon.h>


#include "tcomplugin.h"
TInt cbErr;
TInt EnableHighAccL(TInt aCallType,TBool aEnableAcc);

class EnableHighAccClass : public MLiwNotifyCallback
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

    EnableHighAccClass() : iRetStatus(KErrGeneral),cnt(0) //Default constructor 
                    {
                    ;
                    }
    EnableHighAccClass(TInt aCmd , MLiwInterface *aInterface , CLiwGenericParamList *aInputList)     ;
    };


EnableHighAccClass :: EnableHighAccClass(TInt aCmd ,MLiwInterface *aInterface , CLiwGenericParamList *aInputList)
    { 
    cnt = 0;
    iLocationInterface = aInterface ;
    iInputList = aInputList ;

    }

TInt EnableHighAccClass ::  HandleNotifyL(
        TInt aCmdId,
        TInt aEventId,
        CLiwGenericParamList& aEventParamList,
        const CLiwGenericParamList& aInParamList)
    {

    //DeRefrence Allocated Map first 
    cnt++;
    TInt index = 0;
    const TLiwGenericParam *GenericParam =  aEventParamList.FindFirst(index , KErrorCode) ;

    if(!GenericParam)
        {
        cbErr =  KErrGeneral ;
        }

    if((GenericParam->Value()).AsTInt32() != KErrNone)
        {
        cbErr = (GenericParam->Value()).AsTInt32() ;
        }

    CActiveScheduler::Stop();

    return 0 ;
    }


TInt EnableHighAccL(TInt aCallType,TBool aEnableAcc)
    {
    __UHEAP_MARK ;
    cbErr = KErrNone;
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

    outputlist->Reset() ;
    inputlist->Reset() ;
    EnableHighAccClass* callBack = new(ELeave) EnableHighAccClass;

    TBuf8<20>CmdBuf(KTraceLocation) ;

    if(aCallType == 1)
        {
        TBuf8<20>CmdBuf1(KCmdGetLocation);
        CmdBuf = CmdBuf1;
        }




    //Appending update options
    /* CLiwMap* updateoptionMap = CLiwDefaultMap::NewL();

          TInt32 updateInterval = 2;

          updateoptionMap->InsertL(KUpdateOptionInterval,TLiwVariant(updateInterval));

          TInt32 updateTimeOut = 3;
          updateoptionMap->InsertL(KUpdateOptionTimeOut,TLiwVariant(updateTimeOut));

          TInt32 updateMaxAge = 1;
          updateoptionMap->InsertL(KUpdateOptionMaxAge,TLiwVariant(updateMaxAge));

          TLiwGenericParam updateOption(KUpdateOptionMap,TLiwVariant(updateoptionMap));
          inputlist->AppendL(updateOption) ;
     */
    _LIT8(KEnableHighAccuracy,"EnableHighAccuracy");

    TLiwGenericParam EnableHighAcc(KEnableHighAccuracy,TLiwVariant(aEnableAcc));

    inputlist->AppendL(EnableHighAcc);


    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        return KErrGeneral ;
        }

    TInt reqerror = (ErrorParm->Value()).AsTInt32();

    if(reqerror == KErrNone )     
        CActiveScheduler::Start();



    //const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;
    //delete updateoptionMap;
    delete callBack;
    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    delete Scheduler;


    __UHEAP_MARKEND ;
    return reqerror | cbErr ;



    }


TInt EnableHighAcc(TAny *aFlag)
    {

    CTrapCleanup* cleanup = CTrapCleanup::New();
    TInt  Val = KErrGeneral;
    TInt *flag = static_cast<TInt *>(aFlag);
    TInt err = 0;
    //Install a new active scheduler to this thread

    if(*flag == 1)
        {
        //GetLocation, EnablehighAcc is true
        TRAP(err ,( Val = EnableHighAccL(1,true)) );
        }

    else if(*flag == 2)
        {
        //GetLocation, EnablehighAcc is false
        TRAP(err ,( Val = EnableHighAccL(1,false)) );
        }

    else if(*flag == 3)
        {
        //Trace, EnablehighAcc is true
        TRAP(err ,( Val = EnableHighAccL(2,true)) );
        }

    else if(*flag == 4)
        {
        //Trace, EnablehighAcc is false
        TRAP(err ,( Val = EnableHighAccL(2,false)) );
        }

    delete cleanup ;


    return Val | err;
    }



TInt EnableHighAcc_PosBased(TAny *aFlag)
    {

    CTrapCleanup* cleanup = CTrapCleanup::New();
    TInt  Val ;
    TInt *flag = static_cast<TInt *>(aFlag);
    TInt err;
    //Install a new active scheduler to this thread

    if(*flag == 1)
        {
        //GetLocation, Correct value for EnableAcc PosBased
        TRAP(err ,( Val = EnableHighAcc_PosBasedL(1,true)) );
        }

    else if(*flag == 2)
        {
        //GetLocation, Wrong Type for enableAcc
        TRAP(err ,( Val = EnableHighAcc_PosBasedL(1,false)) );
        }

    else if(*flag == 3)
        {
        //Trace , Correct type
        TRAP(err ,( Val = EnableHighAcc_PosBasedL(2,true)) );
        }

    else if(*flag == 4)
        {
        //Trace, Wrong type
        TRAP(err ,( Val = EnableHighAcc_PosBasedL(2,false)) );
        }

    delete cleanup ;

    return Val | err;
    }


TInt EnableHighAcc_PosBasedL(TInt aCallType,TBool aEnableAcc)
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;
    cbErr = KErrNone;
    CActiveScheduler *Scheduler  = CActiveScheduler :: Current() ;

    if(!Scheduler)
        {
        Scheduler = new CActiveScheduler ;
        }


    CActiveScheduler :: Install(Scheduler) ;





    _LIT(LogFileNameCancel , "C:\\cancelinvalid.txt") ;

    _LIT(KLog , "In CancelWithInvalidTransactionID\n") ;
    data.Copy(KLog);
    //  LogFile.Write(data) ;



    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = CLiwGenericParamList::NewL();
    CLiwGenericParamList* outputlist = CLiwGenericParamList::NewL();




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

    outputlist->Reset() ;
    inputlist->Reset() ;
    EnableHighAccClass* callBack = new(ELeave) EnableHighAccClass;

    TBuf8<20>CmdBuf(KTraceLocation) ;

    if(aCallType == 1)
        {
        TBuf8<20>CmdBuf1(KCmdGetLocation);
        CmdBuf = CmdBuf1;
        }




    _LIT(KClass,"GenericLocationInfo");
    inputlist->AppendL( TLiwGenericParam( KNullDesC8,TLiwVariant( KClass )  ) );
    CLiwMap* updatemap = CLiwDefaultMap::NewL();
    updatemap->PushL();
    _LIT8(KInterval,"UpdateInterval");
    _LIT8(KTimeout,"UpdateTimeOut");
    _LIT8(KAge,"UpdateMaxAge");
    _LIT8(KPartial,"PartialUpdates");
    const TInt KTime = 1000000;

    updatemap->InsertL(KInterval , TLiwVariant(TInt32(2*KTime)));
    updatemap->InsertL(KTimeout , TLiwVariant(TInt32(30*KTime)));
    updatemap->InsertL(KAge , TLiwVariant(TInt32(0)));
    updatemap->InsertL(KPartial , TLiwVariant(TBool(FALSE)));

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(updatemap)));
    updatemap->DecRef();

    if(aEnableAcc){
    TLiwGenericParam EnableHighAcc(KNullDesC8,TLiwVariant(aEnableAcc));
    inputlist->AppendL(EnableHighAcc);
    }
    else
        {
        TPtrC aEnableAcc1(_L("hi"));
        TLiwGenericParam EnableHighAcc(KNullDesC8,TLiwVariant(aEnableAcc1));
        inputlist->AppendL(EnableHighAcc);
        }




    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        return KErrGeneral ;
        }

    TInt reqerror = (ErrorParm->Value()).AsTInt32();

    if(reqerror == KErrNone)
        CActiveScheduler::Start();

    if(reqerror == SErrBadArgumentType && !aEnableAcc)
        reqerror = KErrNone;

    pos = 0 ;
    CleanupStack::PopAndDestroy(updatemap);
    inputlist->Reset();
    outputlist->Reset();
    delete outputlist; 
    
    delete inputlist;
    
    delete callBack;
    locinterface->Close() ;
    
    a.ResetAndDestroy() ;
    a.Close() ;
    delete Scheduler;
    delete ServiceHandler ;
    __UHEAP_MARKEND ;

    return reqerror | cbErr;



    }


