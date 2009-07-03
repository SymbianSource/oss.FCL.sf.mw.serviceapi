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
 #include "locationservice.h"
 
 #define TRACE 0 
 #define GETLOCATION 1
 
 _LIT(KRequestor,"testapp");
 
class ASyncLocCB : public MLocationCallBack
{
	TInt iCmd ;
	TInt iRetStatus ;
	TInt iCount ;
	
	CLocationService *iService ;


	public :
		
		
		TInt HandleNotifyL(HPositionGenericInfo* aInfo , TInt aError) ;

		ASyncLocCB() :iCmd(0) , iRetStatus(KErrGeneral) , iCount(0) //Default constructor 
			{
				;
			}
		ASyncLocCB(TInt aCmd , CLocationService *aService)	 ;
};


ASyncLocCB :: ASyncLocCB(TInt aCmd ,CLocationService *aService):iCount(0) 
{ 
  iCmd = aCmd ;
  iService = aService ;
  	
}

TInt ASyncLocCB :: HandleNotifyL(HPositionGenericInfo* aInfo , TInt Error )
{
	if(iCmd == GETLOCATION)
		{
		iService->CancelOnGoingService(ECancelGetLocation) ;
		}

	if(iCount > 5)
		{
		 CActiveScheduler *current = CActiveScheduler :: Current() ;
		 current->Stop() ;
		}
	iCount++ ;	
	iRetStatus = KErrNone ;
	return iRetStatus ;	
}
  
  
TInt StrayTestGetLocL()
{
	
	CActiveScheduler *Scheduler = new CActiveScheduler ;

	CActiveScheduler :: Install(Scheduler) ;
	CLocationService *CoreObj = CLocationService ::NewL() ;
	ASyncLocCB Updates(TRACE , CoreObj)  ;
	ASyncLocCB GetLoc(GETLOCATION , CoreObj)  ;

	// GelocUpdateCallBack  MyUpdates(&CmdId  , (CLocationService *)NULL) ;
	CoreObj->TraceL(&Updates,EBasicInfo) ;
	CoreObj->GetLocationL(&GetLoc,EBasicInfo) ;

	CActiveScheduler :: Start() ;
	return 0 ; // Controll never reaches here
}


TInt StrayTestGetLoc(TAny */*Arg*/)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
	//Install a new active scheduler to this thread 
	TRAPD(err , StrayTestGetLocL()) ;
	delete cleanup ;
	return 0 ;
}

  