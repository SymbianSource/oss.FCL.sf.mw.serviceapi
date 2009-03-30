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


#include <coemain.h>
#include <testappmngui.rsg>

#include "testappmnguiAppView.h"

// Standard construction sequence
CtestappmnguiAppView* CtestappmnguiAppView::NewL(const TRect& aRect)
    {
    CtestappmnguiAppView* self = CtestappmnguiAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CtestappmnguiAppView* CtestappmnguiAppView::NewLC(const TRect& aRect)
    {
    CtestappmnguiAppView* self = new (ELeave) CtestappmnguiAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

CtestappmnguiAppView::CtestappmnguiAppView()
    {
	// no implementation required
    }

CtestappmnguiAppView::~CtestappmnguiAppView()
    {
	// no implementation required
    }

void CtestappmnguiAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// Draw this application's view to the screen
void CtestappmnguiAppView::Draw(const TRect& /*aRect*/) const
    {
    // Get the standard graphics context 
    CWindowGc& gc = SystemGc();
    
    // Gets the control's extent
    TRect rect = Rect();
    
    // Clears the screen
    gc.Clear(rect);
    }


