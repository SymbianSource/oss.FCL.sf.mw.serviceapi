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

/*
 * Stray signal test function
 */

 #include "locationservice.h"
 
#define TRACE 1 
#define GETLOCATION 0

TInt reqErr1;//To share the error value from callback
 _LIT(KRequestor,"testapp");
 
class ASyncCB : public MLocationCallBack
{
	TInt iCmd ;
	TInt iRetStatus ;
	TInt iCount ;
    TInt iRequestType;
    TInt iTransactionId;

    CLocationService *iService ;


public :


    TInt HandleNotifyL(HPositionGenericInfo* aPosInfo , TInt aError) ;

    ASyncCB() :iCmd(0) , iRetStatus(KErrGeneral) , iCount(0) //Default constructor 
			    {
			    }
    ASyncCB(TInt transId,TInt aCmd , CLocationService *aService)	 ;

    inline TUint GetRequestType(void) 
        {
        return iRequestType ;
        }
    /**
     * GetTransactionId function returns transcation id associated with current async object
     *
     */
    inline TInt32 GetTransactionId(void)
        {
        return iTransactionId ;
        }
    };


ASyncCB :: ASyncCB(TInt transId,TInt aCmd ,CLocationService *aService):iCount(0) 
    { 
    iCmd = aCmd ;
    iService = aService ;

    iTransactionId = transId;
    iRequestType = aCmd;
    }

TInt ASyncCB :: HandleNotifyL (HPositionGenericInfo* aPosInfo , TInt Error )
    {
    if(iCmd == TRACE)
        {
        if(iService->CancelService(this->GetTransactionId()))
            reqErr1 = KErrGeneral;
        }
    else if(iCmd == GETLOCATION)
        {
        iCount++;
        TRAPD(err,iService->GetLocationL(this,EBasicInfo));
        if(err) 
            reqErr1 = KErrGeneral;		
        }

    if(iCount > 2)
        {
        CActiveScheduler *current = CActiveScheduler :: Current() ;
        current->Stop() ;
        }
    iRetStatus = KErrNone ;
    return iRetStatus ;	
    }
  
  
TInt StrayTestL()
    {
    __UHEAP_MARK ;
    reqErr1 = KErrNone;
    CActiveScheduler *Scheduler = new CActiveScheduler ;

    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;
    ASyncCB Updates(12,TRACE , CoreObj)  ;
    ASyncCB GetLoc(13,GETLOCATION , CoreObj)  ;

    // GelocUpdateCallBack  MyUpdates(&CmdId  , (CLocationService *)NULL) ;
    CoreObj->TraceL(&Updates,EBasicInfo) ;
    CoreObj->GetLocationL(&GetLoc,EBasicInfo) ;

    CActiveScheduler :: Start() ;
    delete Scheduler;
    delete CoreObj;
    __UHEAP_MARKEND ;
    return reqErr1 ; 
    }


TInt StrayTest(TAny */*Arg*/)
    {
    TInt errval = 0;
    CTrapCleanup* cleanup = CTrapCleanup::New();
    //Install a new active scheduler to this thread 
    TRAPD(err , errval = StrayTestL()) ;
    delete cleanup ;
    return errval | err ;
    }

