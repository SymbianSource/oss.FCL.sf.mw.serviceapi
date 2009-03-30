/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   tsysinfoaccessorystatus
*
*/


/*#include "tsysmanualtest.h"
#include "tmemnot.h"
#include "entitykeys.h"

using namespace SysInfo;


CCriticalMemNot* CCriticalMemNot::NewL(CStifLogger* aLog, TInt aDrive, TInt aTestId)
	{
	CCriticalMemNot* self = new(ELeave) CCriticalMemNot(aLog,aDrive, aTestId);
	self->ConstructL();
	return self;
	}

CCriticalMemNot::~CCriticalMemNot()
	{
	Cancel();
	
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitScheduler)
		delete iWaitScheduler;
	
	if(iTimer)
		delete iTimer;
	}

void CCriticalMemNot::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CCriticalMemNot::CCriticalMemNot(CStifLogger* aLog,TInt aDrive, TInt aTestId) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog),iDrive(aDrive), iTestId(aTestId), iCount(0)
	{
	}

void CCriticalMemNot::DoCancel()
	{

	}

void CCriticalMemNot::RunL()
	{
	if(iTestId == ETestCriticalMem)
		{
		TestFunc() ;	
		}
	else
		{
		TestFunc1() ;
		}	
	}

void CCriticalMemNot::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CCriticalMemNot::Result()
	{
	return iResult;
	}


void CCriticalMemNot::TestFunc()
	{

	const TTimeIntervalMicroSeconds32 threeMin(180000000);
	CDriveInfo* driveInfo = CDriveInfo::NewL(iDrive) ;
    CSysData* sysData ;
   	   	
    iLog->Log(_L8("expDrive : %d"),iDrive) ;	
    
    TRAPD(leaveCode, iSysInfoService->GetInfoL(KMemory,KDriveInfo,sysData,driveInfo)) ;
    
    if(KErrNone == leaveCode)
	    {
	    CDriveInfo *status = (CDriveInfo*)sysData ;
	    TRAPD(err1,iSysInfoService->GetNotificationL(KMemory,KCriticalMemory,1000,this,status));
		iTimer->After(threeMin);
	    delete sysData ;
	    } 
	else
		{
		iResult = KErrGeneral ;	
		iWaitScheduler->AsyncStop();
		}
	
	delete driveInfo ;
	return ;
	}


void CCriticalMemNot::TestFunc1()
	{

	const TTimeIntervalMicroSeconds32 threeMin(180000000);
   	   	
    iLog->Log(_L8("expDrive : %d"),iDrive) ;	
        
    TRAPD(err1,iSysInfoService->GetNotificationL(KMemory,KMemoryCard,1001,this));
	
	iTimer->After(threeMin);

	return ;
	}
void CCriticalMemNot::HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TInt aError)
	{

	if(aError == KErrNone) 
		{
		if(aTransID == 1000)
			{
		/*	TInt expIpLanguage = 58 ;
			
			const CStatus* data = (CStatus*)aResponse ;
			TInt IpLang = data->Status() ;
			
			if(IpLang == expIpLanguage)
				{
				iResult = KErrNone ;
				}
			iLog->Log(_L8("IpLanguage : %d"),IpLang) ;
		
			delete aResponse ;
			iWaitScheduler->AsyncStop() ;
			}
			
		else if(aTransID == 1001)
			{
			iCount++ ;
			TInt expRemStatus = 0 ;
			TInt expInsStatus = 1 ;
			const CStatus* data = (CStatus*)aResponse ;
			TInt retStatus = data->Status() ;
			if((iCount==1) && (retStatus!=expRemStatus))
				{
				iResult = KErrGeneral ;
				iWaitScheduler->AsyncStop() ;		
				}
			else if((iCount==2) && (retStatus!=expInsStatus))
				{
				
				iResult = KErrGeneral ;
				iWaitScheduler->AsyncStop() ;
				}
			else if(iCount==2)
				{
				iResult = KErrNone ;
				iWaitScheduler->AsyncStop() ;
				}
			delete aResponse ;
			
			}
			
			}
	
	else
		{
		iResult = KErrGeneral ;
		iWaitScheduler->AsyncStop() ;
		}
		
	}
	


void CCriticalMemNot::HandleTimeOut()
{
	iLog->Log(_L("CCriticalMemNot TimeOut reached...")) ;
	iSysInfoService->Cancel(1000) ;
	iSysInfoService->Cancel(1001) ;
	iResult = KErrGeneral ;
	iWaitScheduler->AsyncStop() ;
}


*/
