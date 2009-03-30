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
#include <Stiftestinterface.h>
//#include <senduiconsts.h>
#include <CMsvAttachment.h>
#include "messagingservice.h"
#include "messageheader.h"


#ifndef __ASYNC_H__
#define __ASYNC_H__

class Cheader_test : public CActive, public CMsgCallbackBase
{
public:
	
	TInt pick2,attcnt,canflag,exflag;
	TPtrC b,s,r[20];
	TMsvId  iD;
	CSendMessageParams* v;
	static Cheader_test* NewL();
	~Cheader_test();
	void Start();
	CSendMessageParams* get(void);
	void set(CSendMessageParams* p);


private:
	void ConstructL();
	Cheader_test();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	
	void TestFunc();
	void NotifyResultL(TInt aErrCode, TAny* aResult);

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CMessagingService*		iMessagingService;
		
};


#endif