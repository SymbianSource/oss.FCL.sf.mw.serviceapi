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


#include "testappmnguidocument.h"
#include "testappmnguiapplication.h"

// UID for the application, this should correspond to the uid defined in the mmp file
static const TUid KUidtestappmnguiApp = {0x03AB7FB5};

CApaDocument* CtestappmnguiApplication::CreateDocumentL()
    {  
    // Create an testappmngui document, and return a pointer to it
    CApaDocument* document = CtestappmnguiDocument::NewL(*this);
    return document;
    }

TUid CtestappmnguiApplication::AppDllUid() const
    {
    // Return the UID for the testappmngui application
    return KUidtestappmnguiApp;
    }

