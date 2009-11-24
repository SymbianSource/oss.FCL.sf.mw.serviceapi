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
#include <badesca.h>
#include "getheader.h"
#include <f32file.h>
//#include "messageheader.h"
#ifdef MAIN
#define getheadermmsasync_test3 main
#endif

class CTestAsync;
/**
 * Callback class for asynchronous SAPI message header
*/  
class CMsgCallbackHeader : public CMsgCallbackBase
    {
    public:
        
        static CMsgCallbackHeader* NewL(CActiveSchedulerWait* aWaitSchedular, CMessagingService*s);
        
        virtual ~CMsgCallbackHeader(){}
        
        virtual void HandleGetlistL (TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter);
        
        virtual void NotifyResultL(TInt aErrCode, TAny* aResult);
        
       
        
    private:
    
        CMsgCallbackHeader(CActiveSchedulerWait* aWaitSchedular, CMessagingService*s):iWaitSchedular(aWaitSchedular), iservice(s){ }
        CTestAsync *testasync;
        CActiveSchedulerWait*   iWaitSchedular;
        CMessagingService*  iservice;
       
    };

class CTestAsync : public CActive
{
public:
    static CTestAsync* NewL();
    ~CTestAsync();
    void Start();
    TInt Result();
    void setCallbackresult(TInt res);

    
private:
    void ConstructL();
    CTestAsync();
    
    virtual void DoCancel();
    virtual void RunL();
    
    
    void TestFunc();

    
    
private:    
    CActiveSchedulerWait*   iWaitSchedular;
    CMessagingService*      iMessagingService;
    CMsgCallbackHeader*     iCallBack;
    TInt                    iResult; 
    TInt                iCallbackresult;
   
};


void CMsgCallbackHeader::NotifyResultL( TInt aErrCode, TAny* aResult )
    {
    
    }

void CMsgCallbackHeader::HandleGetlistL( TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter )
    {
    
    testasync = CTestAsync::NewL();
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
                 
                  if((header->Mtm().FindF(_L("MMS")) != KErrNotFound ) && (startdate <= temp && temp <= enddate ) )   
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

CMsgCallbackHeader* CMsgCallbackHeader::NewL(CActiveSchedulerWait* aWaitSchedular, CMessagingService* s)
    {
    CMsgCallbackHeader* self = new (ELeave) CMsgCallbackHeader(aWaitSchedular, s);
    return self;
    }

CTestAsync* CTestAsync::NewL()
    {
    CTestAsync* self = new(ELeave) CTestAsync();
    self->ConstructL();
    return self;
    }

CTestAsync::~CTestAsync()
    {
    Cancel();
    
    if(iWaitSchedular->IsStarted() )
        iWaitSchedular->AsyncStop();
    
    if(iMessagingService )
        delete iMessagingService;
    
    if(iWaitSchedular )
        delete iWaitSchedular;
    }

void CTestAsync::ConstructL()
    {
    CActiveScheduler::Add(this);
    iMessagingService = CMessagingService::NewL();
    iWaitSchedular = new(ELeave) CActiveSchedulerWait();
    }

CTestAsync::CTestAsync() :
CActive(EPriorityStandard)
    {
    }

void CTestAsync::DoCancel()
    {
        
    }

void CTestAsync::RunL()
    {
    TestFunc();
    }

void CTestAsync::Start()
    {
    iCallBack = CMsgCallbackHeader::NewL(iWaitSchedular, iMessagingService);
    SetActive();
    TRequestStatus* temp = &iStatus;
    User::RequestComplete(temp, KErrNone);
    iWaitSchedular->Start();    
    }

void CTestAsync::setCallbackresult(TInt res)
    {
    if(res==KErrNone)
        iCallbackresult=KErrNone;
    else
        iCallbackresult=KErrGeneral;
    }
TInt CTestAsync::Result()
    {
   
    if(iCallbackresult==KErrNone && iResult==KErrNone)
       return KErrNone;
    else
       return KErrGeneral; 
    }


void CTestAsync::TestFunc()
    {
    CFilterParamInfo* filterParams = CFilterParamInfo::NewL();
        CleanupStack::PushL(filterParams);

        filterParams->SetSortType(EMsvSortByDate);
          
            filterParams->AddMtmL(_L("MMS"));
             
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


int getheadermmsasync_test3(int, char**)
    {
    TInt result;
    __UHEAP_MARK;
    CTestAsync* test = CTestAsync::NewL();
    test->Start();
    result=test->Result();
    delete test;
    __UHEAP_MARKEND;
    if(result==KErrNone)
       return KErrNone;
    else
       return KErrGeneral;

    
    }
