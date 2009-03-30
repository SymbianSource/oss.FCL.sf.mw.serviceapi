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

#ifndef _CLIWBINDINGCOMMON_H_
#define _CLIWBINDINGCOMMON_H_

#include <_ansi.h>
#include <glib-object.h>

#define G_BINDING_DERIVED_TYPE_MAP      (binding_map_get_type ())
#define G_BINDING_DERIVED_TYPE_LIST		(binding_list_get_type())
#define G_BINDING_DERIVED_TYPE_ITERATOR (binding_iterator_get_type())
#define G_BINDING_DERIVED_TYPE_BUFFER   (binding_buffer_get_type())
#define G_BINDING_DERIVED_TYPE_UNICODE  (binding_unicode_get_type())
#define G_BINDING_DERIVED_TYPE_DATE     (binding_date_get_type())

typedef int (*BINDING_CALL_BACK)(GValue *);

#define CLIWBINDING_ASYNC_CANCEL        0x0001

#ifdef __cplusplus
extern "C"
{
#endif

IMPORT_C GType binding_map_get_type();
IMPORT_C GType binding_list_get_type();
IMPORT_C GType binding_iterator_get_type();
IMPORT_C GType binding_buffer_get_type();
IMPORT_C GType binding_unicode_get_type();
IMPORT_C GType binding_date_get_type();

IMPORT_C int getoutputcount(GValue outparam);
IMPORT_C GType getoutputatindex(GValue outputlist, GValue *result, int index);
IMPORT_C int getresult(GValue output, GType type, ...);
IMPORT_C int geterrorvalue(GValue outparam);
IMPORT_C int getreturnstatus(GValue outparam);
IMPORT_C int gettransactionid(GValue outparam);
IMPORT_C int resetoutput(GValue outparam);

#ifdef __cplusplus
}
#endif

#endif //_CLIWBINDINGCOMMON_H_
