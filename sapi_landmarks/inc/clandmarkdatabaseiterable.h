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


#ifndef __CLANDMARKDATABASEITERABLE_H__
#define __CLANDMARKDATABASEITERABLE_H__

//INCLUDES
#include <liwvariant.h>

/**
* CDatabaseIterable
* This class inherits from CLiwIterable and implements the Reset() and 
* NextL(TLiwVariant& aEntry) functions. This class is used to iterate through 
* a list of databases.
*/
// CLASS DECLARATION
NONSHARABLE_CLASS(CDatabaseIterable): public CLiwIterable
    {
    public://New Methods

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CDatabaseIterable object.
        * @param aDbList The list of databases to be iterated.
        * @return A pointer to the created instance of CDatabaseIterable.
        */
        static CDatabaseIterable* NewL( CDesCArray* aDbList );

        /**
        * ~CDatabaseIterator
        * Destructor.
        */
        ~CDatabaseIterable();

    private:

        /**
        * ConstructL
        * 2nd phase constructor.
        * Perform the second phase construction of a
        * CDatabaseIterable object.
        */
        void ConstructL();

        /**
        * CDatabaseIterable.
        * C++ default constructor.
        * @param aDbList The list of databases to be iterated.
        */
        CDatabaseIterable( CDesCArray* aDbList );

    protected:
    
        // Resets the iterator.
        void Reset();

        // Iterates over the collection entries to fetch the next data element.
        TBool NextL(TLiwVariant& aEntry);

    private:
    
        /**
        * iDbManager
        * The handle to the CPosLmDatabaseManager.
        */
        CPosLmDatabaseManager*  iDbManager;
        
        /**
        * iDatabaseList
        * The handle to the CDesCArray database array.
        */
        CDesCArray* iDatabaseList;
        
        /**
        * iIndex
        * This holds the index of the current database to which the iterable is pointing.
        */
        TInt iIndex;
        
        /**
        * iCount
        * This holds the count of the total databases in the list.
        */
        TInt iCount;
    };

#endif //__CLANDMARKDATABASEITERABLE_H__