/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Provides the interface to contacgtservice Iterator
*
*/


#ifndef C_CCONTACTITERATOR_H
#define C_CCONTACTITERATOR_H

//System includes
#include <LiwServiceIfBase.h>
#include <LiwCommon.h>

//User include
#include "contactiter.h"

/**
 * CContactIterator - Iterator Class
 * @since S60 5.0
 */
class CContactIterator: public CLiwIterable
{

 public:
 	/*
 	 * @NewL Method
 	 * @Returns the instance of the class
 	 */
 	static CContactIterator* NewL(CContactIter* aIter);
 	/*
 	 * @~CContactIterator Method
 	 * @N/A
 	 */
 	virtual ~CContactIterator();
 	/*
 	 * @Reset Method
 	 * @Returns void
 	 */
 	virtual void Reset();
    /*
 	 * @NextL Method
 	 * @ETrue/EFalse
 	 */
    virtual TBool NextL(TLiwVariant& aEntry);

private:
    //Constructor taking contactservice iterator
    CContactIterator(CContactIter* aIter);
    
    void ContactIDToUTF(HBufC* aContactID);
	
	//Index/Cursor    
    TInt iIndex;
    //ContactService iterator pointer
    CContactIter* iContactIter;
};

#endif C_CCONTACTITERATOR_H
