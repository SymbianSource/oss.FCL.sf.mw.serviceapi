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


#include "getlocasyncperf.h"


CMyActiveObj :: CMyActiveObj():CActive( CActive::EPriorityStandard ){} 

CMyActiveObj :: ~CMyActiveObj()

	{
	iPositioner.Close() ;
	iPosServer.Close() ;
	}

void CMyActiveObj :: ConstructL()
	{
	if(!(this->IsAdded()))
		{
		CActiveScheduler :: Add(this) ;
		}
	}


TInt CMyActiveObj :: MyAsyncInvoc(RRequestorStack& aRequestorInfoStack, TPositionUpdateOptions& aOptions)

	{
	TInt aRet ;
	
	aRet = iPositioner.SetRequestor(aRequestorInfoStack) ;
	
	if (KErrNone == aRet)
		{
		aRet = iPositioner.SetUpdateOptions(aOptions) ;
		
		if(KErrNone == aRet)
			{
			iPositioner.NotifyPositionUpdate(iPositionInfo,iStatus) ;
			SetActive() ;
			return KErrNone ;
			}
		}
	
	return aRet ;
	}

void CMyActiveObj :: RunL()
	
	{
	if( KErrNone ==iStatus.Int() )
		{
		TPosition aPos ;
		
		iPositionInfo.GetPosition(aPos) ;
		
		iLatitude = aPos.Latitude() ;
		iLongitude = aPos.Longitude() ;
		iAltitude = aPos.Altitude() ;
		
		}
	if(this->IsAdded())
       {
       this->Deque() ;
       CActiveScheduler::Stop() ;
       }

	}
	

void CMyActiveObj :: DoCancel()
    {
       	iPositioner.CancelRequest(EPositionerNotifyPositionUpdate);
    }
	

CMyActiveObj* CMyActiveObj :: NewL( )
	{
	TInt aError = KErrNone ;
	CActiveScheduler *current = CActiveScheduler :: Current() ;

    if(!current)
        {
        User::Leave(KErrNotFound); 
        }
	
	CMyActiveObj* tempObj = new(ELeave) CMyActiveObj() ;
	
	CleanupStack::PushL(tempObj);
	
	aError = tempObj->iPosServer.Connect() ;
	User::LeaveIfError(aError) ;
	
	aError = tempObj->iPositioner.Open(tempObj->iPosServer) ;
	User::LeaveIfError(aError) ;
	
	
	
	tempObj->ConstructL() ;
	
	CleanupStack::Pop(tempObj) ;
	
	return tempObj ;
	
	}