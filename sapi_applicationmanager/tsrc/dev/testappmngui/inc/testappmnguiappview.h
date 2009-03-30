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


#ifndef __TESTAPPMNGUI_APPVIEW_H__
#define __TESTAPPMNGUI_APPVIEW_H__


#include <coecntrl.h>

/*! 
  @class CtestappmnguiAppView
  
  @discussion An instance of the Application View object for the testappmngui 
  example application
  */
class CtestappmnguiAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CtestappmnguiAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CtestappmnguiAppView
  */
    static CtestappmnguiAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CtestappmnguiAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CtestappmnguiAppView
  */
    static CtestappmnguiAppView* NewLC(const TRect& aRect);


/*!
  @function ~CtestappmnguiAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CtestappmnguiAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CtestappmnguiAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CtestappmnguiAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CtestappmnguiAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CtestappmnguiAppView();
    };


#endif // __TESTAPPMNGUI_APPVIEW_H__
