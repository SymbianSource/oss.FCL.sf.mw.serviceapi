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

#ifndef _CLIWBINDING_H_
#define _CLIWBINDING_H_

#include <_ansi.h>
#include <pthreadtypes.h>

#include "cliwbindingcommon.h"
#include "cliwbindingmap.h"
#include "cliwbindinglist.h"
#include "cliwbindingiterator.h"

#ifdef __cplusplus
extern "C"
{
#endif

IMPORT_C int cbindingattach();
IMPORT_C void cbindingdetach();
IMPORT_C void* loadservice(const char *aServiceName, const char *aInterfaceName, ...);
IMPORT_C void requestservice(void *aInterfaceHandle, const char *aService, ...);
IMPORT_C void unloadservice(const char *aServiceName, const char *aInterfaceName);
IMPORT_C void closeinterface (void *aInterfaceHandle);
IMPORT_C void createnewscheduler(pthread_t aThreadId);
IMPORT_C int startscheduler(pthread_t aThreadId);
IMPORT_C int stopscheduler (pthread_t aThreadId);

#ifdef __cplusplus
}
#endif

#endif //_CLIWBINDING_H_
