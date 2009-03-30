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


#ifndef __TESTAPPMNGUI_APPUI_H__
#define __TESTAPPMNGUI_APPUI_H__

#include <aknappui.h>

// Forward reference
class CtestappmnguiAppView;

/*! 
  @class CtestappmnguiAppUi
  
  @discussion An instance of class CtestappmnguiAppUi is the UserInterface part of the AVKON
  application framework for the testappmngui example application
  */
class CtestappmnguiAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CtestappmnguiAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CtestappmnguiAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CtestappmnguiAppUi();


/*!
  @function ~CtestappmnguiAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CtestappmnguiAppUi();


public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
/*! @var iAppView The application view */
    TInt GetBufferFromFile(HBufC8*& aBuffer, const TDesC& aFileName);
    CtestappmnguiAppView* iAppView;
    };


#endif // __TESTAPPMNGUI_APPUI_H__

