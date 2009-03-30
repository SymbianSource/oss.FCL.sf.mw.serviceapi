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

 
// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include<e32base.h>

#include "messagingservice.h"
#include "sendmessage.h"

#ifdef MAIN
#define sendmessage_test3 main
#endif



int sendmessage_test3(int, char**)
	{
	__UHEAP_MARK;
	TInt result = KErrNone;
	CMessagingService* test = (CMessagingService* ) CMessagingService::NewL() ; 
	CleanupStack::PushL(test);
	CSendMessageParams* messageParam = CSendMessageParams::NewL();
	CleanupStack::PushL(messageParam);
	messageParam->AddRecipientL(_L("9008032761"));
	messageParam->AddRecipientL(_L("9008032762"));
	messageParam->SetMessageTypeL(_L("SMS"));
	messageParam->SetBodyTextL(_L("Hi How are you!!! Its the first sms from imessaging"));
	messageParam->SetSubjectL(_L("SMS subject"));
	
	TRAP(result, test->SendMessageL(messageParam, NULL));
	
	if(result == KErrNone)
		result = KErrGeneral;
	else
		result = KErrNone;
	
	
	CleanupStack::PopAndDestroy(2, test) ;
	
	__UHEAP_MARKEND;
	
	return result;
	}
