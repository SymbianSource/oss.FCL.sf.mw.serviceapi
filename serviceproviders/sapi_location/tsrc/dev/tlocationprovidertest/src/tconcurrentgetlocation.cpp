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
 
class ConcurrentGetLoc : public MLiwNotifyCallback
{

	MLiwInterface *iLocationInterface ;
	CLiwGenericParamList *iInputList ;
	
	public :
	TInt iRetStatus ;

	TInt HandleNotifyL(
	    TInt aCmdId,
	    TInt aEventId,
	    CLiwGenericParamList& aEventParamList,
	    const CLiwGenericParamList& aInParamList) ;

	ConcurrentGetLoc() : iRetStatus(KErrGeneral) //Default constructor 
		{
			;
		}
	ConcurrentGetLoc(TInt aCmd , MLiwInterface *aInterface , CLiwGenericParamList *aInputList)	 ;
};


ConcurrentGetLoc :: ConcurrentGetLoc(TInt aCmd ,MLiwInterface *aInterface , CLiwGenericParamList *aInputList)
{ 
  
  iLocationInterface = aInterface ;
  iInputList = aInputList ;
  	
}

TInt ConcurrentGetLoc ::  HandleNotifyL(
	    TInt aCmdId,
	    TInt aEventId,
	    CLiwGenericParamList& aEventParamList,
	    const CLiwGenericParamList& aInParamList)
{

//DeRefrence Allocated Map first 
	 return 0 ;
}
  
  
TInt ConcurrentGetLocCallsL()
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
  

	
    TBuf8<20>CmdBuf(KGetLocation) ;
	
	CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;
	CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;
	
	
	ConcurrentGetLoc Updates(GETLOCATION , locinterface , InputList)  ;
	ConcurrentGetLoc GetLoc(GETLOCATION , locinterface , InputList) ;
	
	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &Updates);
	pos = 0 ;
	
	const TLiwGenericParam *errparam1 = OutParmList->FindFirst(pos , KErrorCode) ;

	
	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &GetLoc);
	pos = 0 ;
	
	const TLiwGenericParam *errparam = OutParmList->FindFirst(pos , KErrorCode) ;
	
	if(!errparam)
	{
		return KErrNotFound ;
	}
	
    TLiwVariant ErrVariant = errparam->Value() ;
    TInt ret = ErrVariant.AsTInt32() ;
    a.ResetAndDestroy() ;
	locinterface->Close() ;
	delete ServiceHandler ;
	delete InputList ;
	delete OutParmList ;
	delete Scheduler ;
    __UHEAP_MARKEND ;
	return ret ; // Controll never reaches here
}


TInt ConcurrentGetLocationCalls(TAny */*Arg*/)
{
  
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TInt  Val ;
	//Install a new active scheduler to this thread 
	TRAPD(err ,( Val = ConcurrentGetLocCallsL()) );
	delete cleanup ;
 	
 	if(err)
 	    {
 	        return err ;
 	    }
	return Val ;
}

  