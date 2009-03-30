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
* Description:  It contains the defination filter param class
*
*
*/


#include "appmanagercommon.h"

// -----------------------------------------------------------------------------
// MInfoMap::~MInfoMap
// Destructor
// -----------------------------------------------------------------------------
MInfoMap::~MInfoMap(){}

// -----------------------------------------------------------------------------
// MInfoMap::~MInfoMap
// Destructor
// -----------------------------------------------------------------------------
MIterator::~MIterator(){}


// -----------------------------------------------------------------------------
// CFilterParam::NewL
// Returns the instance of CFilterParam.
// -----------------------------------------------------------------------------
EXPORT_C  CFilterParam* CFilterParam::NewL()
	{
	CFilterParam* self = new(ELeave)CFilterParam();
	return self;
	}


// -----------------------------------------------------------------------------
// CFilterParam::CFilterParam
// C++ Constructor
// -----------------------------------------------------------------------------
CFilterParam::CFilterParam():iDocumentName(NULL),iMimeType(NULL)
	{
	}

// -----------------------------------------------------------------------------
// CFilterParam::~CFilterParam
// Destructor
// -----------------------------------------------------------------------------
CFilterParam::~CFilterParam()
	{
		delete iMimeType;
		delete iDocumentName;
	}

// -----------------------------------------------------------------------------
// CFilterParam::SetDocName
// Sets the document name.
// -----------------------------------------------------------------------------
EXPORT_C void  CFilterParam::SetDocName(const TDesC& aDocName)
	{
	 iDocumentName = aDocName.Alloc(); 

	}


// -----------------------------------------------------------------------------
// CFilterParam::DocName
// Gives the document name.
// -----------------------------------------------------------------------------
EXPORT_C TPtrC  CFilterParam::DocName() const
	{
	 if(iDocumentName)
	 	return TPtrC(*iDocumentName);
	 else
	 	return TPtrC();

	}


// -----------------------------------------------------------------------------
// CFilterParam::SetmimeType
// Sets the mimetype.
// -----------------------------------------------------------------------------
EXPORT_C void  CFilterParam::SetmimeType(const TDesC8& aMimeType)
	{
	 iMimeType = aMimeType.Alloc(); 

	}

// -----------------------------------------------------------------------------
// CFilterParam::MimeType
// Gives the mimetype.
// -----------------------------------------------------------------------------
EXPORT_C TPtrC8  CFilterParam::MimeType() const
	{
	 if(iMimeType)
	 	return TPtrC8(*iMimeType);
	 else
	 	return TPtrC8();

	}
