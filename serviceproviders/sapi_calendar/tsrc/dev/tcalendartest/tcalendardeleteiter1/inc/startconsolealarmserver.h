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

#ifndef STARTALARMSERVERTEST_H
#define STARTALARMSERVERTEST_H

#if __WINS__
const TUid KServerUid2={0x1000008D};
const TUid KServerUid3={0x101F502A};
_LIT(KConsoleAlarmAlertServerImg,"ConsoleAlarmAlertServer");	
void StartAlarmServerL()
	{
	// Have to start the alarm alert server otherwise the alarm
	// server cannot start.
	/*const TUidType serverUid(KNullUid,KServerUid2,KServerUid3);
	TBuf<256> cmdline;
	for (TInt i = 0 ; i < 100 ; i++)
		{
        cmdline.Append('a');
		}

	RProcess server;
	TInt ret = 0;
	ret = server.Create(KConsoleAlarmAlertServerImg,cmdline,serverUid);
	TRequestStatus stat;
	server.Rendezvous(stat);
	if (stat!=KRequestPending)
		{
		server.Kill(0);		// abort startup
		}
	else
		{
		server.Resume();	// logon OK - start the server
		}*/

	}
#endif // __WINS__

#endif	
