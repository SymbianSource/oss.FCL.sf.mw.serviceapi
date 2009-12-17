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

/**
 * Forward declartaions
 */
 
 class MLoggingCallback ;
 class CSapiEvent ;
 class CActiveSchedulerWait ;

/**
 * Generic call back function
 */
NONSHARABLE_CLASS (MLogCallback) :public MLoggingCallback
{
	public:
	 void HandleNotifyL(TUint aTransid ,TUint aStatus , CLogIter *iter )  ;
	 
	 void CancelNotifyL(TUint aTransid);
								   
	 MLogCallback() ;
	 
	 void HandleRequestL(TUint aTransid ,TUint aStatus , CLogsEvent *aEvent )  ;
	 
	 //---------------------------------------------------------
	 // Starts the wait loop
	 //---------------------------------------------------------
	 void Start() ;
	 ~MLogCallback() ;
	 
	 
								   
	private :							   
	   CActiveSchedulerWait *iScheduler ;
};
