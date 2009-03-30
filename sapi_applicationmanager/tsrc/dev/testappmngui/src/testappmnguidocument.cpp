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


#include "testappmnguiAppUi.h"
#include "testappmnguiDocument.h"

// Standard Symbian OS construction sequence
CtestappmnguiDocument* CtestappmnguiDocument::NewL(CEikApplication& aApp)
    {
    CtestappmnguiDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CtestappmnguiDocument* CtestappmnguiDocument::NewLC(CEikApplication& aApp)
    {
    CtestappmnguiDocument* self = new (ELeave) CtestappmnguiDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CtestappmnguiDocument::ConstructL()
    {
	// no implementation required
    }    

CtestappmnguiDocument::CtestappmnguiDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
	// no implementation required
    }

CtestappmnguiDocument::~CtestappmnguiDocument()
    {
	// no implementation required
    }

CEikAppUi* CtestappmnguiDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CtestappmnguiAppUi;
    return appUi;
    }

