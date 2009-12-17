/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CLandmarkIterable class
*
*/


#ifndef __CLANDMARKITERABLE_H__
#define __CLANDMARKITERABLE_H__

//INCLUDES
#include <liwvariant.h>

//FORWARD DECLARATIONS
class CPosLandmark;
class CPosLandmarkDatabase;
class CPosLmItemIterator;
class CLandmarkHandler;

/**
* CLandmarkIterable
* This class inherits from CLiwIterable and implements the Reset() and 
* NextL(TLiwVariant& aEntry) functions. This class acts as wrapper for the 
* CPosLmItemIterator to iterate through a list of landmarks in a database.
*/
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkIterable): public CLiwIterable
    {
    public: //New methods

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CLandmarkIterable object.
        * @param aIterator The iterator to be used for iterating landmarks. This owns the iterator.
        * @param aDatabaseUri The URI of the database on which the iteration is to be done.
        * @return A pointer to the created instance of CLandmarkIterable.
        */
        static CLandmarkIterable* NewL( CPosLmItemIterator* aIterator,
            const TDesC& aDatabaseUri );

        /**
        * ~CLandmarkIterable
        * Destructor.
        */
        ~CLandmarkIterable();
        
        void SetHandler(CLandmarkHandler* aHandler);
        void Close(); 

    protected: //from CLiwIterable

        // Resets the iterator. 
        void Reset();

        // Iterates over the collection entries to fetch the next data element.
        TBool NextL(TLiwVariant& aEntry);

    private: //constructor

        /**
        * ConstructL
        * 2nd phase constructor.
        * Perform the second phase construction of a
        * CLandmarkIterable object.
        * @param aDatabaseUri The URI of the database on which the iteration is to be done.
        */
        void ConstructL( const TDesC& aDatabaseUri );

        /**
        * CLandmarkIterable.
        * C++ default constructor.
        * @param aIterator The iterator to be used for iterating landmarks. This owns the iterator.
        */
        CLandmarkIterable( CPosLmItemIterator* aIterator );

    private: //data

        CLandmarkHandler* iHandler;
        /**
        * iIterator
        * The handle to the CPosLmItemIterator landmark iterator. 
        */
        CPosLmItemIterator* iIterator;

        /**
        * iDatabase
        * The handle to the CPosLandmarkDatabase.
        */
        CPosLandmarkDatabase* iDatabase;

        /**
        * iLandmark
        * The CPosLandmark instance retrieved by iterator.
        */
        CPosLandmark* iLandmark;
        
        /**
        * iLandmarkId
        * The Id of the landmark stored as string.
        */
        HBufC* iLandmarkId;
        
        /**
        * iCategoryIds
        * The Id of the landmark categories stored as string.
        */
        RPointerArray<HBufC> iCategoryIds;
    };

#endif // __CLANDMARKITERABLE_H__

// End of File