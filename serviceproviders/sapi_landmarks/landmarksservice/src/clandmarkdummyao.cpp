/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CLandmarkCmdGetLandmarks class
 *
*/

#include <EPos_CPosLandmarkDatabase.h>
#include <EPos_CPosLmCategoryManager.h>
#include "landmarkservice.h"
#include "mlandmarkobserver.h"
#include "clandmarkmanageobjects.h"
#include "clandmarkdummyao.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkDummyAO::CLandmarkDummyAO( CLandmarkManageObjects* aManageObjects )
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkDummyAO::CLandmarkDummyAO(MLandmarkObserver* aObserver,
		CLandmarkManageObjects* aManageObjects) :
	CActive(EPriorityNormal), iObserver(aObserver), iManageObjects(
			aManageObjects),iIsDelay(EFalse)
	{
	CActiveScheduler::Add(this);
	}

CLandmarkDummyAO::~CLandmarkDummyAO()
	{
	Cancel();
	}

void CLandmarkDummyAO::DoCancel()
	{
	}

void CLandmarkDummyAO::Start(TInt32 aTransactionId,
		CLandmarkDummyAO::TCommand aCmd, TPosLmItemId aId,
		TInt aError)
	{
	iTransactionId = aTransactionId;
	iCmd = aCmd;
	iId = aId;
	SetActive();
	TRequestStatus* status = &iStatus;
	User::RequestComplete(status, aError);
	iIsDelay = ETrue;
	}

void CLandmarkDummyAO::Delay(TInt aError)
    {
    SetActive();
    TRequestStatus* status = &iStatus;
    User::RequestComplete(status, aError);
    iIsDelay = EFalse;
    }
void CLandmarkDummyAO::RunL()
	{
	/*if( iIsDelay )
	    {
	    Delay(iStatus.Int());
	    }
	else*/
	    //{
        switch(iCmd)
         {
         case EAdd: TRAP_IGNORE(iObserver->HandleAddItemsL(iId,iTransactionId,iStatus.Int()));
                    break;
         case EUpdate:
         case ERemove: TRAP_IGNORE(iObserver->HandleItemsL(iTransactionId,iStatus.Int()));
                        break;
         default:
             break;
         }
        
        if (!iManageObjects->IsActive())
            {
            iManageObjects->Start();
            }
       // }
	}

