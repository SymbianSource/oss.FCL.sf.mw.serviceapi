/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   Tests battery notifications
*
*/



#include "tsysmanualtest.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysbatterynot.h"

using namespace SysInfo;

_LIT(KBatteryLevel,"BatteryLevel");

CBatteryNot* CBatteryNot::NewL(CStifLogger* aLog)
	{
	CBatteryNot* self = new(ELeave) CBatteryNot(aLog);
	self->ConstructL();
	return self;
	}

CBatteryNot::~CBatteryNot()
	{
	Cancel();
	
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitScheduler;
	delete iTimer;
	}

void CBatteryNot::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	iCallBackCounter = 0 ;
	iCount = 3 ;
	CActiveScheduler::Add(this);
	}

CBatteryNot::CBatteryNot(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CBatteryNot::DoCancel()
	{
	}

void CBatteryNot::RunL()
	{
	TestFuncL();
//	iWaitScheduler->AsyncStop();
	}

void CBatteryNot::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CBatteryNot::Result()
	{
	if(iError || iChargingResult || iLevelResult || iStrengthResult)
	return KErrGeneral ;
	else
	return KErrNone ;
	}

void CBatteryNot::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 threeMin(180000000);
	CStatus* batStrength = CStatus::NewL(50) ;
	iSysInfoService->GetInfoL(KBattery,KBatteryStrength,1,this,batStrength);
	iSysInfoService->GetNotificationL(KBattery,KBatteryLevel,2,this);
	iSysInfoService->GetNotificationL(KBattery,KChargingStatus,3,this);
   	iTimer->After(threeMin);
	delete batStrength ;
	}

void CBatteryNot::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID,TSysRequest::TRequestType aType, TInt aError)
	{
	if(iCount == iCallBackCounter)
		{
		delete iTimer;
		iTimer = NULL;
		iSysInfoService->Cancel(1) ;
		iSysInfoService->Cancel(2) ;
		iSysInfoService->Cancel(3) ;
		iWaitScheduler->AsyncStop();
		}
		
	else
		{
		iCallBackCounter++ ;
		iLog->Log(_L("Entity: %s, Key: %s "),aEntity.Ptr(),aKey.Ptr());
		
		if(!aEntity.Compare(KBattery) )
			{
			 if(!aKey.Compare(KBatteryStrength))
				 {
	             iLog->Log(_L("Battery Strength read.."));
		         if(!aError)
					{
					TInt32 tid = aTransID;
					if(tid != 1)
						{
						iStrengthResult = KErrGeneral;
						iLog->Log(_L("Incorrect TID Retured.. %d"),tid);
						}
					
					TInt BatteryStrength = ((CStatus*)aOutput)->Status();
					
					iLog->Log(_L("Battery Strength: %d "),BatteryStrength);
					
					if( BatteryStrength > 0	&& BatteryStrength <= 100 )
						{
						iStrengthResult = KErrNone;
						iLog->Log(_L("Battery strength is with in expected range"));
						}
					else
						{
						iStrengthResult = KErrGeneral;
						iLog->Log(_L("Battery strength is out of range"));
						}
					delete aOutput;
					}
				else
					{
					iLog->Log(_L("ERROR SET"));
					iStrengthResult = KErrGeneral;
					}
		 
				 }

 			 else if(!aKey.Compare(KBatteryLevel))
 			 	{
 			     iLog->Log(_L("Battery Level read.."));
		         
		         if(!aError)
					{
					TInt32 tid = aTransID;
					if(tid != 2)
						{
						iLevelResult = KErrGeneral;
						iLog->Log(_L("Incorrect TID Retured.. %d"),tid);
						}
					
					TInt batteryLevel = ((CStatus*)aOutput)->Status();
					
					iLog->Log(_L("Battery Level: %d "),batteryLevel);
					
					if( batteryLevel >= 0	&& batteryLevel <= 7 )
						{
						iLevelResult = KErrNone;
						iLog->Log(_L("Battery Level is with in expected range"));
						}
					else
						{
						iLevelResult = KErrGeneral;
						iLog->Log(_L("Battery Level is out of range"));
						}
					delete aOutput;
					}
				else
					{
					iLog->Log(_L("ERROR SET"));
					iLevelResult = KErrGeneral;
					}
		 
				 
 			 	}
				
			 else if(!aKey.Compare(KChargingStatus))
 			 	{
 			     iLog->Log(_L("Battery Charging Status read.."));
		         
		         if(!aError)
					{
					TInt32 tid = aTransID;
					if(tid != 3)
						{
						iChargingResult = KErrGeneral;
						iLog->Log(_L("Incorrect TID Retured.. %d"),tid);
						}
					
					TInt chargingStatus = ((CStatus*)aOutput)->Status();
					
					iLog->Log(_L("ChargingStatus: %d "),chargingStatus);
					
					if( chargingStatus == 1 )
						{
						iChargingResult = KErrNone;
						iLog->Log(_L("Charging status is as expected"));
						}
					else
						{
						iChargingResult = KErrGeneral;
						iLog->Log(_L("Charging status is wrong"));
						}
					delete aOutput;
					}
				else
					{
					iLog->Log(_L("ERROR SET"));
					iChargingResult = KErrGeneral;
					}
		 			 
 			 	}
				 	
			}
			
		else
			{
			iLog->Log(_L("Incorrect Entity,Key.."));
			iError = KErrGeneral ;
			}
		}
	
	}

void CBatteryNot::HandleTimeOut()
{
	iLog->Log(_L("CBatteryNot TimeOut reached..."));
	iSysInfoService->Cancel(1) ;
	iSysInfoService->Cancel(2) ;
	iSysInfoService->Cancel(3) ;
	iError = KErrGeneral;
	iWaitScheduler->AsyncStop();
}


