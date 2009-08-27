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
#include <LiwServiceHandler.h>
#include <LiwCommon.h>

#include "tcomplugin.h" 
 
 #define TRACE 0 
 #define GETLOCATION 1
 
class TraceCB : public MLiwNotifyCallback
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

	TraceCB() : iRetStatus(KErrGeneral) , iCount(0) ,iCmd(0)//Default constructor 
		{
			;
		}
	TraceCB(TInt aCmd , MLiwInterface *aInterface , CLiwGenericParamList *aInputList)	 ;
};


TraceCB :: TraceCB(TInt aCmd ,MLiwInterface *aInterface , CLiwGenericParamList *aInputList):iCount(0) 
{ 
  iCmd = aCmd ;
  iLocationInterface = aInterface ;
  iInputList = aInputList ;
  	
}

TInt TraceCB ::  HandleNotifyL(
	    TInt aCmdId,
	    TInt aEventId,
	    CLiwGenericParamList& aEventParamList,
	    const CLiwGenericParamList& aInParamList)
{

//DeRefrence Allocated Map first 
	TInt index = 0 ;


	const TLiwGenericParam *Notifyparm = aEventParamList.FindFirst(index ,KLocationMap) ;

	if(Notifyparm)
	{
		TLiwVariant mapVar = Notifyparm->Value() ;
		const CLiwMap *map = mapVar.AsMap() ;
		// map->DecRef() ;
	}
	iCount++ ;
	if(iCount > 3)
	{
		 CActiveScheduler *current = CActiveScheduler :: Current() ;
		 current->Stop() ;
	}
	if(iCmd == GETLOCATION)
		{
		TBuf8<20>CmdBuf(KCmdCancelRequest) ;
		TLiwVariant CancelType(KCmdGetLocation) ;
		
		TLiwGenericParam CancelParm(KCancelType ,  TLiwVariant (KRequestGetLoc)) ;
		iInputList->AppendL(CancelParm) ;	
		CLiwGenericParamList *outlist1 = CLiwGenericParamList :: NewL() ;
		iLocationInterface->ExecuteCmdL(CmdBuf , *iInputList , *outlist1 ) ;
		iInputList->Reset() ;
		
		delete outlist1 ;
		return 0;
		}
		

	
		

	iRetStatus = KErrNone ;
	return iRetStatus ;	
}
  
  
TInt StrayTestGetLocL()
{
    __UHEAP_MARK ;
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
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );
	
	if(!genericparm)
	{
	
		return KErrGeneral ;
	}
	
   MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
  
  
    TBuf8<20>CmdBuf(KCmdTraceLocation) ;
	
	CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;
	CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;
	
	
	TraceCB Updates(TRACE , locinterface , InputList)  ;
	TraceCB GetLoc(GETLOCATION , locinterface , InputList) ;
	
	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &Updates);
	
	CmdBuf = KCmdGetLocation ;
	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &GetLoc);

	CActiveScheduler :: Start() ;
	
	a.ResetAndDestroy() ;
	locinterface->Close() ;
	delete ServiceHandler ;
	delete InputList ;
	delete OutParmList ;
	delete Scheduler ;
	__UHEAP_MARKEND ;
	return 0 ; // Controll never reaches here
}


TInt StrayTestGetLoc(TAny */*Arg*/)
{
  
	CTrapCleanup* cleanup = CTrapCleanup::New();
	//Install a new active scheduler to this thread 
	TRAPD(err , StrayTestGetLocL()) ;
	delete cleanup ;
 	
	return err ;
}

  