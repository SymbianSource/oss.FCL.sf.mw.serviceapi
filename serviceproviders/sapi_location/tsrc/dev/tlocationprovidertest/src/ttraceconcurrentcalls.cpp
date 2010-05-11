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
 
 #define TRACE 0 
 #define GETLOCATION 1
 
class ConcurrentTraceLoc : public MLiwNotifyCallback
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

    ConcurrentTraceLoc() : iRetStatus(KErrGeneral),cnt(0) //Default constructor 
		{
			;
		}
	ConcurrentTraceLoc(TInt aCmd , MLiwInterface *aInterface , CLiwGenericParamList *aInputList)	 ;
};


ConcurrentTraceLoc :: ConcurrentTraceLoc(TInt aCmd ,MLiwInterface *aInterface , CLiwGenericParamList *aInputList)
{ 
    cnt = 0;
  iLocationInterface = aInterface ;
  iInputList = aInputList ;
  	
}

TInt ConcurrentTraceLoc ::  HandleNotifyL(
	    TInt aCmdId,
	    TInt aEventId,
	    CLiwGenericParamList& aEventParamList,
	    const CLiwGenericParamList& aInParamList)
{

//DeRefrence Allocated Map first 
    cnt++;
    TInt trid = aCmdId;

    if(cnt == 2)
        {

        CActiveScheduler::Stop();
        }
    return 0 ;
    }
  
  
TInt TraceConcurrentCallsL()
{
    __UHEAP_MARK ;
    CActiveScheduler *Scheduler  = CActiveScheduler :: Current() ;

    if(!Scheduler)
        {
        Scheduler = new CActiveScheduler ;
        }


    CActiveScheduler :: Install(Scheduler) ;
	_LIT(KTraceFile , "C:\\Trace.txt") ;
	
	RFile TraceFile ;
	RFs  TraceSession ;
	
	TraceSession.Connect() ;
	
	if(TraceFile.Open(TraceSession ,KTraceFile , EFileWrite | EFileShareAny )  == KErrNotFound)
	{
		if(TraceFile.Create(TraceSession ,KTraceFile , EFileWrite | EFileShareAny ) != KErrNone)
		{
		 	return KErrGeneral ;
		}

	}
	 
    
	
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
  
    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
    
    


	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);
	

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
	TraceFile.Write(_L8("Error Param searched \n")) ;
	
    pos = 0 ;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );
	
	if(!genericparm)
	{
	
		return KErrGeneral ;
	}
	
	TraceFile.Write(_L8("Interface Found")) ;
	
   MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
	
	
    TBuf8<20>CmdBuf(KTraceLocation) ;
	
	CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;
	CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;
	
	
	ConcurrentTraceLoc Updates(TRACE , locinterface , InputList)  ;
	ConcurrentTraceLoc GetLoc(TRACE , locinterface , InputList) ;
	
	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &Updates);
	pos = 0 ;
	
	const TLiwGenericParam *errparam1 = outputlist->FindFirst(pos , KErrorCode) ;

	
	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &GetLoc);
	pos = 0 ;
    CActiveScheduler :: Start() ;
	const TLiwGenericParam *errparam = OutParmList->FindFirst(pos , KErrorCode) ;
	
	if(!errparam)
	{
		return KErrNotFound ;
	}
	TraceFile.Write(_L8("Error param  Found \n")) ;
	
    TLiwVariant ErrVariant = errparam->Value() ;
    TInt ret = ErrVariant.AsTInt32() ;
    a.ResetAndDestroy() ;
	locinterface->Close() ;
	delete ServiceHandler ;
	delete InputList ;
	delete OutParmList ;
	delete Scheduler ;
	TraceFile.Write(_L8("Gracefully returned \n")) ;
    __UHEAP_MARKEND ;
	return  ret ; 
}


TInt TraceConcurrent(TAny */*Arg*/)
{
  
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TInt  Val = 0;
	//Install a new active scheduler to this thread 
	TRAPD(err ,( Val = TraceConcurrentCallsL()) );
	delete cleanup ;
 	
 	if(err)
 	    {
 	        return err ;
 	    }
	return Val ;
}

  