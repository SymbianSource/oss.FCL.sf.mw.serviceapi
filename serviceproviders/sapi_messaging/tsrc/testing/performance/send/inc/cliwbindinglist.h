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


#ifndef _CLIWBINDINGLIST_H_
#define _CLIWBINDINGLIST_H_

#include <_ansi.h>
#include <glib-object.h>

#ifdef __cplusplus
extern "C"
{
#endif

IMPORT_C int list_construct(GValue *lstPtr, ...);
IMPORT_C int list_delete(GValue list);

IMPORT_C int list_count(GValue list);
IMPORT_C int list_appendnode(GValue list, ...);
IMPORT_C int list_entryatindex(GValue list, int index, GValue *entry);

#ifdef __cplusplus
}
#endif

#endif //_CLIWBINDINGLIST_H_