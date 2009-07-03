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




#ifndef CALIMPTESTCASES_H
#define CALIMPTESTCASES_H

#include <e32base.h>

#include "calendarheader.h"

class CCalendarService;

class CCalImpTestCases: public CActive, public MCalCallbackBase
		{
			enum TTestCaseType
				{
				KImportSync = 0,
				KImportGuidAsync,
				KImportLuidAsync,
				KImportUsingFileAsync,
				KMultipleImportUsingFileAsync,
				KImportAsync,
				KImportAsyncICAL,
				};
		public:
		
			static CCalImpTestCases* NewL( TInt& aResult, TInt aVCalOrICal = 1); //1 means vCal
		
			~CCalImpTestCases();
		
			TInt TestImportGuidL();
			
			TInt TestImportLuidL();
			
			TInt TestImportCases1();
			
			TInt TestImportCases2();
			
			TInt TestImportCases3();
			
			TInt TestImportFromFileL();
			
			TInt TestImportMultipleEntry();

			void TestImportUsingGuidAsyncL();
			
			void TestImportUsingLuidAsyncL();
			
			void TestImportUsingFileAsyncL();
			
			void TestImportMultipleEntryAsyncL();
			
			void TestImportCaseAsyncL();

			TInt Result();
		
		private:
		
			void ConstructL();
		
			CCalImpTestCases( TInt& aResult,TInt aVCalOrICal = 1); //1 means vCal

			//for the sake of ActiveObject
			virtual void DoCancel();
		
			virtual void RunL();

			void Start();

			void NotifyResultL(TInt aErrCode, TAny* aResult);
			
		private:	
		
			CActiveSchedulerWait* 	iWaitSchedular;
		
			CCalendarService*		iCalendarService;
			
			TTestCaseType			iTestCaseType;
		
			TInt& 					iResult;
			
			TInt					iVCalOrICal;
			
			RPointerArray<TUIDSet> 	iArruids;
			
		};



#endif      // CALIMPTESTCASES_H

