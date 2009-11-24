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

#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
//#include <senduiconsts.h>
#include <cmsvattachment.h>
#include "messagingservice.h"
#include "messageheader.h"


#ifndef __ASYNC_H__
#define __ASYNC_H__

class Cheader_test;

class CMsgCallbackHeader : public CMsgCallbackBase
    {
    public:
        enum TestCaseCallbackId
                {
                ESMS,
                EMMS,
                };
        
        static CMsgCallbackHeader* NewL(CActiveSchedulerWait* aWaitSchedular, CMessagingService*s);
        
        virtual ~CMsgCallbackHeader(){}
        
        virtual void HandleGetlistL (TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter);
        
        virtual void NotifyResultL(TInt aErrCode, TAny* aResult);
        
       void setcallbackid(TestCaseCallbackId id);
        
    private:
    
        CMsgCallbackHeader(CActiveSchedulerWait* aWaitSchedular, CMessagingService*s):iWaitSchedular(aWaitSchedular), iservice(s){ }
       // Cheader_test *testasync;
        CActiveSchedulerWait*   iWaitSchedular;
        CMessagingService*  iservice;
        TestCaseCallbackId iCid;
    };


class Cheader_test : public CActive
{
public:
    
    TInt pick2,attcnt,canflag,exflag,posnegflag;
    TPtrC b,s,r[20];
    TMsvId  iD;
    CFilterParamInfo* v;
    static Cheader_test* NewL();
    ~Cheader_test();
    void Start();
    CFilterParamInfo* get(void);
    TInt getposneg(void);
    void set(CFilterParamInfo* p);
    void setposneg(TInt aFlag);

private:
    void ConstructL();
    Cheader_test();
    
    virtual void DoCancel();
    virtual void RunL();
    
    
    
    void TestFunc();
    //void HandleGetlistL(TInt aErrCode,CMsvEntrySelection* aEntryselection, CFilterParamInfo* aFilterParams);
    //void NotifyResultL(TInt aErrCode,TAny* aResult);

private:
    CMsgCallbackHeader*     iCallBack;
    
    
private:    
    CActiveSchedulerWait*   iWaitSchedular;
    CMessagingService*      iMessagingService;
        
};


#endif
