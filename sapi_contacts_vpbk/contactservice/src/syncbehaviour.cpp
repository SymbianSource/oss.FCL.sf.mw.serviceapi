/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Sync behaviour implemetation for getlist iterator.
*
*/




#include "syncbehaviour.h"

//------------------------------------
// Adds itself to the active scheduler
//------------------------------------
CContactSyncIter::CContactSyncIter():CActive(0)
    {
    CActiveScheduler::Add(this);
    }

//---------------------
// RunL() calls Signal()
//----------------------
void CContactSyncIter::RunL()
    {
    Signal();
    }

void CContactSyncIter::DoCancel()
    {
    	
    }

//------------------------------------
// Stops the scheduler and does cleanup
//------------------------------------
void CContactSyncIter::Signal()
    {
    iWaitScheduler->AsyncStop();    	
    }

//------------------------------------
// Sets the status of the Scheduler 
// and starts it
//------------------------------------
void CContactSyncIter::Wait()
    {
    if(!IsActive()) 
    	{
    	iStatus = KRequestPending;
    	SetActive();
    	}
    iWaitScheduler->Start();
    }

//----------------------------------
// NewL() Method
//----------------------------------
CContactSyncIter* CContactSyncIter::NewL()
    {
    CContactSyncIter* self = new( ELeave ) CContactSyncIter( );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;

    }

//----------------------------------------------------
// ConstructL method - 
// Installs the active scheduler if not already installed
//----------------------------------------------------
void CContactSyncIter::ConstructL()
{
/*
   iInstalled = 0;
   if(!CActiveScheduler::Current())
   {
   		iNewscheduler = new (ELeave) CActiveScheduler(); 
   		CActiveScheduler::Install(iNewscheduler);
		iInstalled = 1;
   }
*/   
   iWaitScheduler = new (ELeave) CActiveSchedulerWait;
}

CContactSyncIter::~CContactSyncIter()
{
	delete iNewscheduler;
	delete iWaitScheduler;
}
