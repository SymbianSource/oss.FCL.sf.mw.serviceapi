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
#define sendmessage_test11 main
#endif



int sendmessage_test11(int, char**)
    {
    __UHEAP_MARK;
    TInt result = KErrNone;
    TMsvId messageid = 0;
    CFilterParamInfo* filterParams = CFilterParamInfo::NewL();
    CleanupStack::PushL(filterParams);
    filterParams->AddMtmL(_L("MMS"));
    CMsvEntrySelection* entryselection = NULL ;  
    CMessagingService* test = (CMessagingService*) CMessagingService::NewL() ; 
    CleanupStack::PushL( test );
    TRAPD(err, test->GetIdListL(filterParams,0,NULL,entryselection));
    if(err==KErrNone)
        {
        CMessageHeader* header = NULL;
        TInt index=0;
        test->GetNextHeaderL(filterParams, entryselection, index, NULL, header);
        if(header)
            {
            messageid = header->MessageId();
            }
        delete header;
        }
    delete entryselection;
    
    CSendMessageParams* messageParam = CSendMessageParams::NewL();
    CleanupStack::PushL(messageParam);
    messageParam->AddRecipientL(_L("9008032761"));
    messageParam->AddRecipientL(_L("9008032762"));
    messageParam->SetMessageTypeL(_L("SMS"));
    messageParam->SetBodyTextL(_L("Hi How are you!!! Its the first sms from imessaging"));
    if(messageid > 0)
    messageParam->SetTemplateId(messageid);
    
    TRAP(result, test->SendMessageL(messageParam, NULL));
    
    CleanupStack::PopAndDestroy(2, test) ;
    CleanupStack::PopAndDestroy(filterParams) ;

    __UHEAP_MARKEND;
    if(messageid)
        {
        if(result==KErrNotSupported)
            return KErrNone;
        else
            return KErrGeneral;
        }
    else
    return result;
    }
