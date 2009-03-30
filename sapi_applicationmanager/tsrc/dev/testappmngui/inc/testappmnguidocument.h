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


#ifndef __TESTAPPMNGUI_DOCUMENT_H__
#define __TESTAPPMNGUI_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CtestappmnguiAppUi;
class CEikApplication;


/*! 
  @class CtestappmnguiDocument
  
  @discussion An instance of class CtestappmnguiDocument is the Document part of the AVKON
  application framework for the testappmngui example application
  */
class CtestappmnguiDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CtestappmnguiDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CtestappmnguiDocument
  */
    static CtestappmnguiDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CtestappmnguiDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CtestappmnguiDocument
  */
    static CtestappmnguiDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CtestappmnguiDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CtestappmnguiDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CtestappmnguiAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CtestappmnguiDocument object
  */
    void ConstructL();

/*!
  @function CtestappmnguiDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CtestappmnguiDocument(CEikApplication& aApp);

    };


#endif // __TESTAPPMNGUI_DOCUMENT_H__
