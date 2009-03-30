/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   getlocation performance test
*
*/



#include <e32svr.h>
#include <f32file.h>
#include <LbsPosition.h>
#include <LbsPositionInfo.h> 
#include <LbsCommon.h>
#include <glib-object.h>
#include <pthread.h>
#include <semaphore.h>
#include "cliwbinding.h"
#include "cliwbindinghandler.h"

TInt media_cb();
TInt SymPerformanceTestL();
void OpenFile();
int media_file_cb (GValue* value);
void CloseFile(); 