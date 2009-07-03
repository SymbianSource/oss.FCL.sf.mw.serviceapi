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
#include <Stiftestinterface.h>
#include <LbsRequestor.h>
#include <liwServiceHandler.h>
#include <LiwCommon.h>

#include "tcomplugin.h"
 
 #define TRACE 0 
 #define GETLOCATION 1
 
class ASyncCB : public MLiwNotifyCallback
{
	TInt iCount ; 
	TInt iCmd ;
	MLiwInterface *iLocationInterface ;
	CLiwGenericParamList *iInputList ;
	
	public :
	TInt iRetStatus ;

	TInt HandleNotifyL(
	    TInt aCmdId,
	    TInt aEventId,
	    CLiwGenericParamList& aEventParamList,
	    const CLiwGenericParamList& aInParamList) ;

	ASyncCB() : iRetStatus(KErrGeneral) , iCount(0) ,iCmd(0)//Default constructor 
		{
			;
		}
	ASyncCB(TInt aCmd , MLiwInterface *aInterface , CLiwGenericParamList *aInputList)	 ;
};


ASyncCB :: ASyncCB(TInt aCmd ,MLiwInterface *aInterface , CLiwGenericParamList *aInputList):iCount(0) 
{ 
  iCmd = aCmd ;
  iLocationInterface = aInterface ;
  iInputList = aInputList ;
  	
}


TInt ASyncCB ::  HandleNotifyL(
	    TInt aCmdId,
	    TInt aEventId,
	    CLiwGenericParamList& aEventParamList,
	    const CLiwGenericParamList& aInParamList)
{

//DeRefrence Allocated Map first 
	TInt index = 0 ;
	
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
	
	TInt pos =  0 ;
	TraceFile.Seek(ESeekEnd , pos) ;

//	const TLiwGenericParam *Notifyparm = aEventParamList.FindFirst(index ,KLocationMap) ;
/*
	if(Notifyparm)
	{
		TLiwVariant mapVar = Notifyparm->Value() ;
		const CLiwMap *map = mapVar.AsMap() ;
		//map->DecRef() ;
	}
	
*/		iCount++ ;
	
	
		
	if(iCount > 2)
		{
		 CActiveScheduler *current = CActiveScheduler :: Current() ;
		 TraceFile.Write(_L8("Active Scheduler stopped\n")) ;
		 current->Stop() ;
		 return KErrNone ;
		}
		
	if(iCmd == TRACE)
		{
		TBuf8<20>CmdBuf(KCmdCancelRequest) ;
		TLiwVariant CancelType(KCmdTraceLocation) ;
		
		TLiwGenericParam CancelParm(KCancelType ,  TLiwVariant (KRequestTrace)) ;
		iInputList->AppendL(CancelParm) ;
		CLiwGenericParamList *outlist1 = CLiwGenericParamList :: NewL() ;	
		 
		TraceFile.Write(_L8("Trace Command Cancelled Submitted \n")) ;
		
	    iLocationInterface->ExecuteCmdL(CmdBuf , *iInputList , *outlist1 ) ;
	    TraceFile.Write(_L8("Trace Command Cancelled Executed \n")) ;
		iInputList->Reset() ;
		TraceFile.Write(_L8("Input list reset  \n")) ;
		delete outlist1 ;
		TraceFile.Write(_L8("outlist deleted \n")) ;
		return 0;
		}
		
	else if(iCmd == GETLOCATION)
		{
		
		TraceFile.Write(_L8("GetLoc Notification \n")) ;
		TraceFile.Flush() ;
		
		TBuf8<20>CmdBuf(KCmdGetLocation) ;
		CLiwGenericParamList *outlist2 = CLiwGenericParamList :: NewL() ;
		
		
		iInputList->Reset() ;
		
		TraceFile.Write(_L8("input for GetLoc   List reset \n")) ;
		TraceFile.Flush() ;
		TraceFile.Write(_L8("GetLocation Cmd submitted \n")) ;
		TraceFile.Flush() ;
		
		iLocationInterface->ExecuteCmdL(CmdBuf , *iInputList , *outlist2 , 0 , this );
		TraceFile.Write(_L8("GetLocation Command Executed \n")) ;
		outlist2->Reset() ;
		TraceFile.Write(_L8("Out List GetLocation reset \n")) ;
		delete outlist2 ;

		 
		}
		

	iRetStatus = KErrNone ;
	return iRetStatus ;	
}
  
  
TInt StrayTestL()
{

	
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

	CActiveScheduler *Scheduler = new CActiveScheduler ;

	CActiveScheduler :: Install(Scheduler) ;

	 
    
	
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
	
    pos = 0 ;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos, KLsInterfaceName );
	
	if(!genericparm)
	{
	
		return KErrGeneral ;
	}
	
   MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
	
  

    TBuf8<20>CmdBuf(KCmdTraceLocation) ;
	
	CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;
	CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;
	
	
	ASyncCB Updates(TRACE , locinterface , InputList)  ;
	ASyncCB GetLoc(GETLOCATION , locinterface , InputList) ;
	
	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &Updates);
	
	CmdBuf = KCmdGetLocation ;
	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &GetLoc);

	CActiveScheduler :: Start() ;
	
	TInt skpos = 0 ;
	
	TraceFile.Seek(ESeekEnd , skpos) ;
	
	TraceFile.Write(_L8("Trace stray signal executed \n")) ;
	
	
	a.ResetAndDestroy() ;
	locinterface->Close() ;
	
	TraceFile.Write(_L8("Interface closed \n")) ;

	delete ServiceHandler ;
	
	TraceFile.Write(_L8("ServiceHandler deleted\n")) ;
	delete InputList ;
	delete OutParmList ;
	delete Scheduler ;
	
	TraceFile.Write(_L8("Scheduler  deleted\n")) ;
	return 0 ; // Controll never reaches here
}


TInt StrayTest(TAny */*Arg*/)
{
 // __UHEAP_MARK ;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TInt val = 0 ;
	//Install a new active scheduler to this thread 
	TRAPD(err , (val =StrayTestL())) ;
	delete cleanup ;
	
	if(err)
	    {
	     return err ;
	    }
	 
	return val ;   	
	return 0 ;
}

  