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
#include <Stiftestinterface.h>
#include <LbsRequestor.h>
#include <LiwServiceHandler.h>
#include <liwCommon.h>
#include <lbs.h>

#include "tcomplugin.h"

_LIT(LogFileName , "C:\\Notifications.txt") ;

class CallBack : public MLiwNotifyCallback
{
	
	public :
	TInt iRetStatus ;
		
		TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList) ;

		CallBack() : iRetStatus(KErrGeneral)  //Default constructor 
			{
				;
			}
	
};

TInt CallBack :: HandleNotifyL(
            TInt /*aCmdId*/,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList) 
{
  
  	TInt Index = 0 ;
  	const TLiwGenericParam *GenericParam = aEventParamList.FindFirst(Index , KErrorCode );
  	
  	TInt error ;
  	
  	if(GenericParam)
			{
				TLiwVariant Variant ;
	
				Variant = GenericParam->Value() ;
				error  = Variant.AsTInt32() ;
				iRetStatus = error ;
				CActiveScheduler *Current  = CActiveScheduler :: Current() ;
				Current->Stop() ;

			}
	return error ;			
}


/** 
  *@ This call back interface is for testing  Service Not available  
 */
 //---------------------------------------------------------------------------------------------------------


TInt ServiceFailedFunctionL()
{
    __UHEAP_MARK ;
	CallBack MyUpdates ;
	
	_LIT8(KService, "Service.Location");
    _LIT8(KIDataSource,"ILocation");

	
	
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
    
    


	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KService, KIDataSource);
	

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);
	
	ServiceHandler->AttachL(a) ;
   
	
	 
 	 

	TInt pos = 0;
	
	const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;
	
	if(!errorprm)
	{
		return KErrGeneral ;
	}
	

	_LIT8(KDataSource, "ILocation");

 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );
	
	if(!genericparm)
	{
	
		return KErrGeneral ;
	}
	
   MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
  // CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;

    

	CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;
	CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;
	TBuf8<20>CmdBuf(KCmdTraceLocation) ;


	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,0 ,  &MyUpdates);
	const TInt KSecond = 1000000;
	const TInt KUpdateTimeOut = 15*KSecond ; // Default timeout value for synchrnous call waits..
	
	User :: After((TTimeIntervalMicroSeconds32 )KUpdateTimeOut) ;


	CActiveScheduler :: Start() ;
	delete Scheduler ;
	
	locinterface->Close();
	delete InputList ;
	delete  OutParmList ;
    __UHEAP_MARKEND ;	
	return  MyUpdates.iRetStatus ;
    	
    	

}

TInt ServiceFailedTest(TAny */*Arg*/)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TRAPD(err , ServiceFailedFunctionL()) ;
	delete cleanup ;
	return err ;
	
}
