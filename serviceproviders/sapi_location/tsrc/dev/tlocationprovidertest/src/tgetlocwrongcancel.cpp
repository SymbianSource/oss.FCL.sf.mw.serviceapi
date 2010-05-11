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

#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <lbsrequestor.h>
#include <liwservicehandler.h>
#include <liwcommon.h>

#include "tcomplugin.h"

_LIT(LogFileName , "C:\\Notifications.txt") ;

class WrongNotificationGetLoc : public MLiwNotifyCallback
{
	
	public :
	TInt iRetStatus ;
		
		TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList) 
		    {
		        return 0;
		    }

		WrongNotificationGetLoc() : iRetStatus(KErrGeneral)  //Default constructor 
			{
				;
			}
	
};




TInt GetLocWrongCancelL()
{
    __UHEAP_MARK ;
	WrongNotificationGetLoc MyUpdates ;
	
    CActiveScheduler *Scheduler  = CActiveScheduler :: Current() ;
    
    if(!Scheduler)
    {
    	Scheduler = new CActiveScheduler ;
    }
    
   
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
	
	CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;
	CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;
	TBuf8<20>CmdBuf(KCmdGetLocation) ;
	

	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &MyUpdates);
	
   _LIT8(KCancell , "CancelNotification") ;
   _LIT8( KType ,"CancelRequestType") ;
   _LIT( KTraceCancel ,"TraceCancel") ;
   
   InputList->AppendL(TLiwGenericParam (KType , TLiwVariant (KTraceCancel))) ;
   CmdBuf = KCancell ;
   locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,0 ,  &MyUpdates);
   
   pos =  0;
   
   const TLiwGenericParam *errprm = OutParmList->FindFirst(pos , KErrCode) ;
   
   TInt ret = (errprm->Value()).AsTInt32() ;
    a.ResetAndDestroy() ;
    delete Scheduler ;
    
    locinterface->Close();
    delete InputList ;
    delete  OutParmList ;
    delete ServiceHandler;
    __UHEAP_MARKEND ;
    if ( SErrNotFound == ret )
	    {
	    return KErrNone;	
	    }
	else
	    
    	return ret ;  
}




TInt GetLocWrongCancel(TAny * /*Arg*/)
{
//	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
    TInt val = 0;
    TRAPD(err , (val = GetLocWrongCancelL() ) ) ;
    delete cleanup ;
 //    __UHEAP_MARKEND;   

	return val ;
	
}