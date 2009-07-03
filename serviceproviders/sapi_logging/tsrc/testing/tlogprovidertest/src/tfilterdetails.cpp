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

#include <e32base.h>
#include "tfilterdetails.h"




/**
 * Default Constructor Method
 */
 
 CFilterDetails :: CFilterDetails(): iDirection(-1) , iStatus(-1),iEventType(-1)
	{
	  ;
	}
 
/**
 * Default Destructor
 */
  
 CFilterDetails :: ~CFilterDetails()
	{
	;
	}
	
/**
 *Two phased constructor implementation
 */

 EXPORT_C CFilterDetails* CFilterDetails :: NewL()
	{
	CFilterDetails* self = CFilterDetails::NewLC();
	CleanupStack::Pop(self);
	return self;
	}
	  
/**
 * Two phased constructor implementation
 */
  
 CFilterDetails* CFilterDetails :: NewLC() 
	{
	CFilterDetails* self = new (ELeave) CFilterDetails();
    CleanupStack::PushL(self);
	return self;
	}
	