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
*
*/

#include"mgmediacontainer.h"
// -----------------------------------------------------------------------------
// CMediaContainer::NewL
// Returns the instance of CMediaContainer.
// -----------------------------------------------------------------------------
CMediaContainer* CMediaContainer::NewL(TRect& aRect)
    {
    CMediaContainer* self = new (ELeave) CMediaContainer();
    CleanupStack::PushL(self); 
    self->ConstructL(aRect);
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CMediaContainer::CMediaContainer
// Constructor
// -----------------------------------------------------------------------------   
CMediaContainer::CMediaContainer()
    {
    // no implementation required
    }
// -----------------------------------------------------------------------------
// CMediaContainer::~CMediaContainer
// Destructor
// -----------------------------------------------------------------------------   
CMediaContainer::~CMediaContainer()
    {
    CloseWindow();
     // no implementation required
    }
// -----------------------------------------------------------------------------
// CMediaContainer::ConstructL
// 
// -----------------------------------------------------------------------------   
void CMediaContainer::ConstructL(TRect& aRect)
    {
     
    CreateWindowL();
       SetRect(aRect);

      iVideoRect = Rect();
      TPoint point = PositionRelativeToScreen();
      iVideoRect.iTl.iX += point.iX;
      iVideoRect.iTl.iY += point.iY;
      iVideoRect.iBr.iX += point.iX;
      iVideoRect.iBr.iY += point.iY;
      ActivateL();

    }
// -----------------------------------------------------------------------------
// CMediaContainer::Draw
// CCoeControl protected method implementation
// -----------------------------------------------------------------------------   
void CMediaContainer::Draw(const TRect& /*aRect*/) const
    {
     CWindowGc& gc = SystemGc();
     gc.SetBrushColor(KRgbBlack);
     gc.SetBrushStyle (CGraphicsContext::ESolidBrush);
     TRect rect = Rect();
     gc.Clear(rect);
    }
