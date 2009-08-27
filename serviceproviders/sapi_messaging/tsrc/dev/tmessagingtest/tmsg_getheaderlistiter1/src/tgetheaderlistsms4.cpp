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

 

#include <e32base.h>
////#include <senduiconsts.h>
#include "messagingservice.h"
#include <BADESCA.H>
#include "getheader.h"
#include <f32file.h>
//#include "messageheader.h"
#ifdef MAIN
#define getheadersmsasync_test4 main
#endif

class CTestAsync1;
/**
 * Callback class for asynchronous SAPI message header
*/  
class CMsgCallbackHeader1 : public CMsgCallbackBase
    {
    public:
        
        static CMsgCallbackHeader1* NewL(CActiveSchedulerWait* aWaitSchedular, CMessagingService*s);
        
        virtual ~CMsgCallbackHeader1(){}
        
        virtual void HandleGetlistL (TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter);
        
        virtual void NotifyResultL(TInt aErrCode, TAny* aResult);
        
       
        
    private:
    
        CMsgCallbackHeader1(CActiveSchedulerWait* aWaitSchedular, CMessagingService*s):iWaitSchedular(aWaitSchedular), iservice(s){ }
        CTestAsync1 *testasync;
        CActiveSchedulerWait*   iWaitSchedular;
        CMessagingService*  iservice;
        
    };

class CTestAsync1 : public CActive
{
public:
    static CTestAsync1* NewL();
    ~CTestAsync1();
    void Start();
    TInt Result();
    void setCallbackresult(TInt res);

    
private:
    void ConstructL();
    CTestAsync1();
    
    virtual void DoCancel();
    virtual void RunL();
    
    
    void TestFunc();

    
    
private:    
    CActiveSchedulerWait*   iWaitSchedular;
    CMessagingService*      iMessagingService;
    CMsgCallbackHeader1*     iCallBack;
    TInt                    iResult; 
    TInt                iCallbackresult;
   
};


void CMsgCallbackHeader1::NotifyResultL( TInt aErrCode, TAny* aResult )
    {
    
    }

void CMsgCallbackHeader1::HandleGetlistL( TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter )
    {
    
    testasync = CTestAsync1::NewL();
    CFilterParamInfo* filterParams = aFilter;
    CMsvEntrySelection* en=aEntrySelection;
    TInt iter=0;
    TInt val=0;
    TInt index = 0;
    TTime startdate=filterParams->StartDate();
    TTime enddate = filterParams->EndDate();
    for(;;)
        {
            CMessageHeader* header = NULL;
            iservice->GetNextHeaderL(filterParams, en, index, NULL, header);
            if(header)
                {
                 iter++;
                 TTime temp =header->Time();
                 
                  if((header->Mtm().FindF(_L("SMS")) != KErrNotFound ) && (startdate <= temp && temp <= enddate ) )   
                     val++;
                 
                  
                delete header;
                }
            else
                break;  
            
        }
   delete filterParams;
   
   delete en;
   
   if(iter==val)
       testasync->setCallbackresult(KErrNone);
   else
       testasync->setCallbackresult(KErrGeneral);
   delete testasync;

   iWaitSchedular->AsyncStop();
   }

CMsgCallbackHeader1* CMsgCallbackHeader1::NewL(CActiveSchedulerWait* aWaitSchedular, CMessagingService* s)
    {
    CMsgCallbackHeader1* self = new (ELeave) CMsgCallbackHeader1(aWaitSchedular, s);
    return self;
    }

CTestAsync1* CTestAsync1::NewL()
    {
    CTestAsync1* self = new(ELeave) CTestAsync1();
    self->ConstructL();
    return self;
    }

CTestAsync1::~CTestAsync1()
    {
    Cancel();
    
    if(iWaitSchedular->IsStarted() )
        iWaitSchedular->AsyncStop();
    
    if(iMessagingService )
        delete iMessagingService;
    
    if(iWaitSchedular )
        delete iWaitSchedular;
    }

void CTestAsync1::ConstructL()
    {
    CActiveScheduler::Add(this);
    iMessagingService = CMessagingService::NewL();
    iWaitSchedular = new(ELeave) CActiveSchedulerWait();
    }

CTestAsync1::CTestAsync1() :
CActive(EPriorityStandard)
    {
    }

void CTestAsync1::DoCancel()
    {
        
    }

void CTestAsync1::RunL()
    {
    TestFunc();
    }

void CTestAsync1::Start()
    {
    iCallBack = CMsgCallbackHeader1::NewL(iWaitSchedular, iMessagingService);
    SetActive();
    TRequestStatus* temp = &iStatus;
    User::RequestComplete(temp, KErrNone);
    iWaitSchedular->Start();    
    }

void CTestAsync1::setCallbackresult(TInt res)
    {
    if(res==KErrNone)
        iCallbackresult=KErrNone;
    else
        iCallbackresult=KErrGeneral;
    }
TInt CTestAsync1::Result()
    {
   
    if(iCallbackresult==KErrNone && iResult==KErrNone)
       return KErrNone;
    else
       return KErrGeneral; 
    }


void CTestAsync1::TestFunc()
    {
    CFilterParamInfo* filterParams = CFilterParamInfo::NewL();
        CleanupStack::PushL(filterParams);

        filterParams->SetSortType(EMsvSortByDate);
          
            filterParams->AddMtmL(_L("SMS"));
             
           TDateTime start(2008,EMarch,22,0,0,0,0);
           TInt startyear = start.Year();
           TInt startmonth = start.Month();
           TInt startday = start.Day();
           
           TTime startdate(start);
           
           filterParams->SetStartDateFilter(startdate);

           TDateTime end(2010,EJune,23,0,0,0,0);
           TInt endyear = end.Year();
           TInt endmonth = end.Month();
           TInt endday = end.Day();


           TTime enddate(end) ;       

           filterParams->SetEndDate(enddate);

        
        CMsvEntrySelection* entryselection = NULL ;  
    TRAPD(err, iMessagingService->GetIdListL(filterParams,0,iCallBack,entryselection));
    if(err==KErrNone )
        iResult=KErrNone;
    else
        iResult=KErrGeneral;
    CleanupStack::PopAndDestroy(filterParams);
    
    }


int getheadersmsasync_test4(int, char**)
    {
    TInt result;
    __UHEAP_MARK;
    CTestAsync1* test = CTestAsync1::NewL();
    test->Start();
    result=test->Result();
    delete test;
    __UHEAP_MARKEND;
    if(result==KErrNone)
       return KErrNone;
    else
       return KErrGeneral;

    
    }
