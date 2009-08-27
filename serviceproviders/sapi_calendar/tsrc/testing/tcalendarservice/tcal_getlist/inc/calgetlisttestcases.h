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
* Description:  ?Description
*
*/



#ifndef CALGETLISTTESTCASES_H
#define CALGETLISTTESTCASES_H

#include <e32base.h>

#include "calendarheader.h"
//#include "teststartconsolealarmserver.h"

class CCalendarService;
class CEntryAttributes;

class CCalGetlistTestCases: public CActive, public MCalCallbackBase
		{
		
		enum TTestCaseType
				{
				KGetlistGuidFilterAsync,
				KGetlistLuidFilterAsync,
				KGetlistTmRgFilterAsync,
				KGetlistTextFilterAsync,
				KGetlistTypeFilterAsync,
				KGetlistInvalidGuidFilterAsync,
				KGetlistInvalidLuidFilterAsync,
				};
		public:
		
			static CCalGetlistTestCases* NewL( TInt& aResult, TBool aEntryArray = ETrue); 
		
			~CCalGetlistTestCases();
		    
			void TestGetlistGuidFilterAsyncL();
			
			void TestGetlistLuidFilterAsyncL();
			
			void TestGetlistTmRgFilterAsyncL();
			
			void TestGetlistTextFilterAsyncL();
			
			void TestGetlistTypeFilterAsyncL();

			void TestGetlistInvalidGuidFilterAsyncL();
            
            void TestGetlistInvalidLuidFilterAsyncL();
			
			
			TInt Result();
	        
			void addSomeEntries(  const TDesC& aName );

		private:
		
			void ConstructL();
		
			CCalGetlistTestCases(TInt& aResult, TBool aEntryArray = ETrue); 
			
		
			//for the sake of ActiveObject
			virtual void DoCancel();
		
			virtual void RunL();
			
		
			void Start();
			
			void NotifyResultL(TInt aErrCode, TAny* aResult);
			
		private:	
		
			CActiveSchedulerWait* 	iWaitSchedular;
		
			CCalendarService*		iCalendarService;
		
			TInt& 					iResult;
			
			TBool                   iEntryArray;
			
			TTestCaseType			iTestCaseType;
			
			
	//		RPointerArray<CCalEntry> 	entryList;
	//		RPointerArray<CCalInstance> instanceList;
			RPointerArray<TUIDSet>   iArruids;
		};



#endif      // CALGETLISTTESTCASES_H

