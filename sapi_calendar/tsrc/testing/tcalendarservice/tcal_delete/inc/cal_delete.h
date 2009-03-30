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
#include "entryattributes.h"

class CCalendarService;

class CCalDelTestCases: public CActive, public MCalCallbackBase
		{
		
		enum TTestCaseType
				{
				KDeleteSync = 0,
				KDeleteAllAsync,
				KDeleteUsingGuidsAsync,
				KDeleteUsingLuidsAsync,
				KDeleteUsingInvalidGuidAsync,
				KDeleteUsingInvalidLuidAsync,
				KDeleteUsingGuidLuidsAndTmRgAsync,
				KDeleteUsingTmRgAsync
				};
		public:
		
			static CCalDelTestCases* NewL( TInt& aResult); //1 means vCal
		
			~CCalDelTestCases();
		    
			TInt TestDeleteUsingGUidL();
		
			TInt TestDeleteUsingLocalUidL();
			
			TInt TestDeleteGuidTmRgLocalUidL();
			
			TInt TestDeleteInvalidGUidLuidL();
			
			TInt TestDeleteTmRgL();
			
			TInt TestDeleteByDefCalL();
		
			void TestDeleteUsingGUidAsyncL();
			
			void TestDeleteUsingLocalUidAsyncL();
				
			void TestDeleteGuidTmRgLocalUidAsyncL();
				
			void TestDeleteInvalidGUidAsyncL();
			
			void TestDeleteInvalidLUidAsyncL();
				
			void TestDeleteTmRgAsyncL();
			
			TInt Result();
			
			void addSomeEntries(  const TDesC& aName );
			
			void ExportAllToFileL( const TDesC16 &aCalFileName,  const TDesC16 &aFileName);
		private:
		
			void ConstructL();
		
			CCalDelTestCases(TInt& aResult); //1 means vCal
			
		
			//for the sake of ActiveObject
			virtual void DoCancel();
		
			virtual void RunL();
			
			virtual TInt RunError(TInt aError);
			
		
			void Start();
			
			void NotifyResultL(TInt aErrCode, TAny* aResult);
			
		private:	
		
			CActiveSchedulerWait* 	iWaitSchedular;
		
			CCalendarService*		iCalendarService;
		
			TInt& 					iResult;
			
			TTestCaseType			iTestCaseType;	
			
			RPointerArray<TUIDSet> 	iArruids;
		};



#endif      // CALEXPTESTCASES_H

