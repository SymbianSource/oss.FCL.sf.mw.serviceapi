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

#ifndef _CLIWBINDING_HANDLER_H_
#define _CLIWBINDING_HANDLER_H_

#include <e32uid.h>
#include <e32def.h>
#include <e32base.h>
#include <e32des16.h>
#include <LiwCommon.h>
#include <LiwServiceHandler.h>
#include <LiwGenericParam.hrh>
#include <LiwVariant.h>

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>

#include "cliwbindingCommon.h"
#include "cliwbindingprivate.h"

struct TCallbackInfo
{
	//(output structure, callback, flags)
	int iTransId;
	BINDING_CALL_BACK iCallback;
	GValue *iOutputParam;
};

struct TActiveScheduleInfo
{
	CActiveScheduler* aScheduler;
	TInt aRefCount;
	TInt aStarted;
	
};

NONSHARABLE_CLASS(CBindingHandler) : public MLiwNotifyCallback
{
	public:
		
		static CBindingHandler* GetInstance();
		static void DeleteInstance();
		void *LoadServiceL (const char *aServiceName, const char *aInterfaceName);
		TInt RequestServiceL (void *aInterfaceHandle, const char *aService, va_list *arglist);
		TInt UnloadServiceL (const char *aServiceName, const char *aInterfaceName);
		void CloseInterfaceL (void *aInterfaceHandle);
		
		int MapConstructL(GValue *mapPtr, va_list *arg);
		int MapInsertNodeL(GValue map, va_list *arg );
		int MapFindKeyAtIndexL(GValue map, int index, char *keyfound);	
		int MapFindValueWithKeyL(GValue map, const char *key, GValue *foundvalue);
		
		int ListConstructL(GValue *lstPtr, va_list *arg);		
		int ListAppendNodeL(GValue list, va_list *arg);
		int ListEntryAtIndexL(GValue list, int index, GValue *entry);

		int IteratorNextL(GValue iterator, GValue *nextEntry);

	private:
		// C++ constructor
		CBindingHandler();
		
		// Reference to the singleton object
		static CBindingHandler* NewL();
		
		// C++ copy constructor
		CBindingHandler(const CBindingHandler&);
		
		// C++ equality operator
		CBindingHandler& operator=(const CBindingHandler &);
		
		// Symbian phase 2 constructor
		TInt ConstructL();
			
		void StoreInterestAndInterfaceL (const char* aInterest,
										 const char *aInterfaceName,
										 void *aInteraceHandle);
		TInt RetrieveInterestAndInterface (char **aInterest, 
										   char **aInterfaceName,
										   void *aInterfaceHandle);
		
		TInt HandleNotifyL (TInt  aCmdId,TInt  aEventId,
							 CLiwGenericParamList& aEventParamList,
							 const CLiwGenericParamList&  aInParamList);
							 
		TInt HandleAsyncServiceReturn (TInt  aCmdId, TInt  aEventId,
									   CLiwGenericParamList& aEventParamList);
									   
		TInt retrieveResultToOutParam(GValue *outParam, TLiwVariant inParam, 
									  TInt transId, TInt eventId, TInt error);
									  
		TInt ProcessOutputParam(CLiwGenericParamList &inParam, GValue *outParam, 
								TInt transId, TInt eventId, TInt error);
								
		TInt HandleError(GValue *outParam, TInt transId, TInt eventId, TInt error);
		
		TInt retrieveResult(GValue *outParam, TLiwVariant inParam);


	private:
		// Structure to hold the service name, interface name and the
		// interface pointer
		struct TInterfaceInfo
		{
			char *iServiceName;
			char *iInterfaceName;
			void *iInterfaceHandle;
		};
		// An array of RPointerArray to store the Interface
		static RPointerArray <TInterfaceInfo> iInterfaceArray;
		
		// An array of RPointerArray type to store the callback Info
		static RPointerArray <TCallbackInfo> iCallbackInfoArray;
		
		// An RPointerArray to store the BindingOutParam that are created
		// internal to the binding
		static RPointerArray <BindingOutParam> iBindingOutParamArray;

		// An RPointerArray to store the BindingParam that are created
		// internal to the binding
		static RPointerArray <BindingParam> iBindingParamArray;
		
		// Instance pointer of the singleton class
		static CBindingHandler* iBindingHandlerInstance;
		// Reference count to the singleton class
		static TInt				iRefCount;
		// Pointer to the Service Handler class
		static CLiwServiceHandler*		iServiceHandler;
		// Pointer to the active schedulers
		static RPointerArray<TActiveScheduleInfo> iActiveSchedulerInfo;
};

#endif //_CLIWBINDING_HANDLER_H_