/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __TESTAPPMNGUI_PAN__
#define __TESTAPPMNGUI_PAN__

/** testappmngui application panic codes */
enum TtestappmnguiPanics 
    {
    EtestappmnguiBasicUi = 1
    // add further panics here
    };

inline void Panic(TtestappmnguiPanics aReason)
    {
	_LIT(applicationName,"testappmngui");
    User::Panic(applicationName, aReason);
    }

#endif // __TESTAPPMNGUI_PAN__
