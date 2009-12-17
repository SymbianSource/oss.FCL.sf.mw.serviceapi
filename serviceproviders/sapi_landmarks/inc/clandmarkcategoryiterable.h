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
* Description:  CLandmarkCategoryIterable class
*
*/


#ifndef __CLANDMARKCATEGORYITERABLE_H__
#define __CLANDMARKCATEGORYITERABLE_H__

//INCLUDES
#include <liwvariant.h>

//FORWARD DECLARATIONS
class CPosLandmarkCategory;
class CPosLandmarkDatabase;
class CPosLmCategoryManager;
class CPosLmItemIterator;
class CLandmarkHandler;
/**
* CLandmarkCategoryIterable
* This class inherits from CLiwIterable and implements the Reset() and 
* NextL(TLiwVariant& aEntry) functions. This class is used to iterate through 
* a list of landmark categories.
*/
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkCategoryIterable): public CLiwIterable
    {
    public: //New methods

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CLandmarkCategoryIterable object.
        * @param aIterator The iterator to be used for iterating landmark categories. This owns the iterator.
        * @param aDatabaseUri The URI of the database on which the iteration is to be done.
        * @return A pointer to the created instance of CLandmarkCategoryIterable.
        */
        static CLandmarkCategoryIterable* NewL( CPosLmItemIterator* aIterator,
            const TDesC& aDatabaseUri );

        /**
        * ~CLandmarkCategoryIterable
        * Destructor.
        */
        ~CLandmarkCategoryIterable();
        
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
        * CLandmarkCategoryIterable object.
        * @param aDatabaseUri The URI of the database on which the iteration is to be done.
        */
        void ConstructL( const TDesC& aDatabaseUri );

        /**
        * CLandmarkCategoryIterable.
        * C++ default constructor.
        * @param aIterator The iterator to be used for iterating landmark categories. This owns the iterator.
        */
        CLandmarkCategoryIterable( CPosLmItemIterator* aIterator );

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
        * iCategoryManager
        * The handle to the CPosLmCategoryManager.
        */
        CPosLmCategoryManager* iCategoryManager;

        /**
        * iLandmarkCategory
        * The CPosLandmark instance retrieved by iterator.
        */
        CPosLandmarkCategory* iLandmarkCategory;
        
        /**
        * iCategoryId
        * The Id of the category stored as string.
        */
        HBufC* iCategoryId;
        
        /**
        * iGlobalCategoryId
        * The Global Id of the category stored as string.
        */
        HBufC* iGlobalCategoryId;
    };

#endif // __CLANDMARKCATEGORYITERABLE_H__

// End of File