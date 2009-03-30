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
 
class ASyncCB : public MLocationCallBack
{
	TInt iCmd ;
	TInt iRetStatus ;
	TInt iCount ;
	
	CLocationService *iService ;


	public :
		
		
		TInt HandleNotifyL(HPositionGenericInfo* aPosInfo , TInt aError) ;

		ASyncCB() :iCmd(0) , iRetStatus(KErrGeneral) , iCount(0) //Default constructor 
			{
				;
			}
		ASyncCB(TInt aCmd , CLocationService *aService)	 ;
};


ASyncCB :: ASyncCB(TInt aCmd ,CLocationService *aService):iCount(0) 
{ 
  iCmd = aCmd ;
  iService = aService ;
  	
}

TInt ASyncCB :: HandleNotifyL (HPositionGenericInfo* aPosInfo , TInt Error )
{
	if(iCmd == TRACE)
		{
		iService->CancelOnGoingService(ECancelTrace) ;
		}
	else if(iCmd == GETLOCATION)
		{
		 iService->GetLocationL(this,EBasicInfo) ;
		 iCount++ ;
		}
		
	if(iCount > 3)
		{
		 CActiveScheduler *current = CActiveScheduler :: Current() ;
		 current->Stop() ;
		}
	iRetStatus = KErrNone ;
	return iRetStatus ;	
}
  
  
TInt StrayTestL()
{
	
	CActiveScheduler *Scheduler = new CActiveScheduler ;

	CActiveScheduler :: Install(Scheduler) ;
	CLocationService *CoreObj = CLocationService ::NewL() ;
	ASyncCB Updates(TRACE , CoreObj)  ;
	ASyncCB GetLoc(GETLOCATION , CoreObj)  ;

	// GelocUpdateCallBack  MyUpdates(&CmdId  , (CLocationService *)NULL) ;
	CoreObj->TraceL(&Updates,EBasicInfo) ;
	CoreObj->GetLocationL(&GetLoc,EBasicInfo) ;

	CActiveScheduler :: Start() ;
	return 0 ; // Controll never reaches here
}


TInt StrayTest(TAny */*Arg*/)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
	//Install a new active scheduler to this thread 
	TRAPD(err , StrayTestL()) ;
	delete cleanup ;
	return 0 ;
}

  