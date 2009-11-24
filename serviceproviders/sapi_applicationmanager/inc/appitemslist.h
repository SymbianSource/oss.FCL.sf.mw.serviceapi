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
* Description:  Implements CLiwIterable type
*
*/


#ifndef __CAPPITEMSLIST_H
#define __CAPPITEMSLIST_H

#include <liwgenericparam.h> 

class MIterator;

/**
 *  This class implements the abstract methods of CLiwIterable   
 *  class so that the user may iterate over the result 
 *  
 *  @since Series60 v3.2
 */
NONSHARABLE_CLASS( CAppItemsList ) : public CLiwIterable
    {

public:
       
    /**
     * Two-phased constructor.
     * @param aIter holds a reference to the item list 
     * @return A pointer of type CAppItemsList
     */
     static CAppItemsList* NewL( MIterator* aIter );
    
    /**
    * Destructor.
    */
    ~CAppItemsList();


    /**
     * Resets the iterator to point to the beginning of list
     * @param void
     * @return void
     */
    void Reset();	
    
    /**
     * Constructs the next media item in the form of a map
     * @param TLiwVariant an output parameter that contains the result
     * @return TBool On success this returns ETrue else returns EFalse
     */	
    TBool NextL( TLiwVariant& aItem );


private:
    
     /**
     * Parameterised constructor
     * @since  Series60 v3.2
     * @param  aIter holds a reference to the item list model
     */
    
    CAppItemsList( MIterator* aIter );
    
private: // data

    /**
    * A pointer to Iterator of core class
    */
    MIterator* iIter;
   
    };

#endif // __CAPPITEMSLIST_H
