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
* Description:   ?Description
*
*/



#ifndef GETLIST_H
#define GETLIST_H

#include <liwcommon.h>
#include <e32base.h>
#include <f32file.h>
#include <BADESCA.H>

class CLiwServiceHandler;
class CLiwGenericParamList;
class MLiwInterface;
class CStifLogger;
class CPosLandmarkDatabase;
class CPosLmCategoryManager;
class CPosLmDatabaseManager;

//CPosLmDatabaseManager* iDatabaseManager;

void CreateLandmarksL (CPosLandmarkDatabase* aLandmarkHandle);
void RemoveAllCategories ( CPosLmCategoryManager* aHandle );
void RemoveAllLandmarks ( CPosLandmarkDatabase* aLandmarkHandle );
TInt CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32& aError );
//void DeleteAllLocalDatabasesL();


class CCalCallback : public MLiwNotifyCallback
	{
	public:
		
		static CCalCallback* NewL(CActiveSchedulerWait* aWaitSchedular, TInt32& aResult );
		
	/*	CCalCallback() 
		{
			iResult = KErrGeneral;
		}		*/
		virtual ~CCalCallback(){}
		
		TInt HandleNotifyL(TInt aCmdId,
	            TInt aEventId,
	            CLiwGenericParamList& aEventParamList,
	            const CLiwGenericParamList& aInParamList);		
		
	private:
	
 		CCalCallback(CActiveSchedulerWait* aWaitSchedular, TInt32& aResult ):iWaitSchedular(aWaitSchedular), iResult(aResult){ }

		CActiveSchedulerWait* 	iWaitSchedular;
		TInt32& 			iResult;
		
			
	};


class CTestAsync : public CActive
{
public:
	static CTestAsync* NewL(TInt type);
	~CTestAsync();
	void Start();
	void CancelNotification(TBool include_tid,TInt32 tid);
	void CancelNotification_KeyBased();
	void CancelNotification_PosBased();
	void CancelNotification_InvalidTidType();
	void CancelNotification_InvalidCmd();
	TInt32 Result();
	
private:
	void ConstructL(TInt case_type);
	CTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	void TestFunc();
	void GetListInvalidCase();
	
	void AddGetListCancel();
	void CancelWithInvalidTid();
	void CallGetListMultipleTimes();
	void CancelKeyBasedTid();
	void CancelPosBasedTid();
	void CancelLargeTid();
	void CancelInvalidTidType();
	void CancelInvalidCmd();
	MLiwInterface* CreateInterface();

public:	
	TInt32 					iTransactionId;	
	TInt					iTestCaseType;
	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	CLiwGenericParamList* inparam;
	CLiwGenericParamList* outparam;
	CActiveSchedulerWait* 	iWaitSchedular;
	TInt32 					iResult;
	CCalCallback*			iCallback;
	MLiwInterface* 			interface;
	CStifLogger *gLog;
};

#endif