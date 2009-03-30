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


#include "testappmnguiApplication.h"
#include <eikstart.h>

#pragma message("Please ensure that you read the ReadMe file.")

#ifdef __UI_FRAMEWORKS_V2__

// Create an application, and return a pointer to it
CApaApplication* NewApplication()
	{
	return new CtestappmnguiApplication;
	}


TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	
	}

///////////////////////////////////////////////////////////////////////////////
//
// The following is required for wins on EKA1 (using the exedll target)
//
#if defined(__WINS__) && !defined(EKA2)
EXPORT_C TInt WinsMain(TDesC* aCmdLine)
	{
	return EikStart::RunApplication(NewApplication, aCmdLine);
	}

TInt E32Dll(TDllReason)
	{
	return KErrNone;
	}
#endif

#else // __UI_FRAMEWORKS_V2__

// Create an application, and return a pointer to it
EXPORT_C CApaApplication* NewApplication()
  {
  return new CtestappmnguiApplication;
  }

// DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason)
  {
  return KErrNone;
  }

#endif // __UI_FRAMEWORKS_V2__

