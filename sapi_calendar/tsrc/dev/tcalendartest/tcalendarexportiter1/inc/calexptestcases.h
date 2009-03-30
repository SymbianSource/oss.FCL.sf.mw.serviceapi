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




#ifndef CALEXPTESTCASES_H
#define CALEXPTESTCASES_H

#include <e32base.h>

#include "calendarheader.h"

class CCalendarService;

class CCalExpTestCases: public CActive, public MCalCallbackBase
		{
		
		enum TTestCaseType
				{
				KExportSync = 0,
				KExportAllAsync,
				KExportForGuidsAsync,
				KExportForLuidsAsync,
				KExportAllAsyncICAL,
				KExportForGuidsAsyncICAL,
				KExportForLuidsAsyncICAL,
				};
		public:
		
			static CCalExpTestCases* NewL(TInt& aResult, TInt aVCalOrICal = 1); //1 means vCal
		
			~CCalExpTestCases();
		
			TInt TestExportAllL();
		
			TInt TestExportForGuidsL();
		
			TInt TestExportForLuidsL();
		
			void TestExportAllAsyncL();
			
			void TestExportForGuidsAsyncL();
			
			void TestExportForLuidsAsyncL();
			
			TInt Result();
		
		private:
		
			void ConstructL();
		
			CCalExpTestCases(TInt& aResult, TInt aVCalOrICal = 1); //1 means vCal
			
		
			//for the sake of ActiveObject
			virtual void DoCancel();
		
			virtual void RunL();
			
		
			void Start();
			
			void NotifyResultL(TInt aErrCode, TAny* aResult);
			
		private:	
		
			CActiveSchedulerWait* 	iWaitSchedular;
		
			CCalendarService*		iCalendarService;
		
			TInt& 					iResult;
			
			TTestCaseType			iTestCaseType;	
			
			TInt					iVCalOrICal;
			
			RPointerArray<TUIDSet> 	iArruids;
		};



#endif      // CALEXPTESTCASES_H

