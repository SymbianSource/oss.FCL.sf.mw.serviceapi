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

#ifndef _CLIWBINDINGPRIVATE_H_
#define _CLIWBINDINGPRIVATE_H_
#include <LiwCommon.h>
#include <LiwServiceHandler.h>

#include <glib-object.h>

#define G_CBINDING_DERIVED_TYPE  	G_TYPE_FUNDAMENTAL_MAX +1
#define BINDING_NEW_DERIVED_TYPE(x) (G_CBINDING_DERIVED_TYPE +x)

#define	DERIVED_MAP_TYPE 		(BINDING_NEW_DERIVED_TYPE(0))
#define DERIVED_LIST_TYPE 		(BINDING_NEW_DERIVED_TYPE(1))
#define DERIVED_ITERATOR_TYPE 	(BINDING_NEW_DERIVED_TYPE(2))
#define DERIVED_BUFFER_TYPE     (BINDING_NEW_DERIVED_TYPE(3))
#define DERIVED_UNICODE_TYPE	(BINDING_NEW_DERIVED_TYPE(4))

#define G_BINDING_DERIVED_TYPE_OUTPARAM   (binding_outparam_get_type())

#define RESULT_OFFSET 1

typedef struct _BindingOutParam   BindingOutParam;
typedef struct _BindingParam      BindingParam;
typedef struct _BindingParamClass BindingParamClass;

struct _BindingOutParam
{
  	GObject parent;
  
	GValue result;
	int TransactionId;
	int RequestReturnEvent;
	int error;
};

struct _BindingParam
{
  	GObject parent;
  
 	void *data_pointer;
};

struct _BindingParamClass
{
  GObjectClass parent_class;
};

//_LIT8(KErrorCode, "ErrorCode");
_LIT8(KErrorCode, "Error");
_LIT8(KTransactionId, "TransactionId");

GType FindType(GType type);

GType binding_outparam_get_type();
void *getFbsPointer(GValue *fbsContainer);

#endif //_CLIWBINDINGPRIVATE_H_