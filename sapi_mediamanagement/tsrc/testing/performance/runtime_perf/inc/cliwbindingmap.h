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


#ifndef _CLIWBINDINGMAP_H_
#define _CLIWBINDINGMAP_H_

#include <_ansi.h>
#include <stdarg.h>
#include <glib-object.h>

#ifdef __cplusplus
extern "C"
{
#endif

IMPORT_C int map_construct(GValue *mapPtr, ...);
IMPORT_C int map_delete(GValue map);

IMPORT_C int map_insertnode(GValue map, ...);
IMPORT_C int map_count(GValue map);
IMPORT_C int map_findkeyatindex(GValue map, int index, char *keyfound);
IMPORT_C int map_findvaluewithkey(GValue map, const char *key, GValue *foundvalue);

#ifdef __cplusplus
}
#endif

#endif //_CLIWBINDINGMAP_H_