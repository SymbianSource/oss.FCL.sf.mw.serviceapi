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
* Description:  Implements CLiwMap type
*
*/


#ifndef __CAPPINFOMAP_H
#define __CAPPINFOMAP_H

#include <Liwgenericparam.h> 

class MInfoMap;

/**
 *  This class implements the abstract methods of CLiwIterable   
 *  class so that the user may iterate over the result 
 *  
 *  @since Series60 v3.2
 */
NONSHARABLE_CLASS( CAppInfoMap ) : public CLiwMap
    {

public:
       
    /**
     * Two-phased constructor.
     * @param aIter holds a reference to the item list 
     * @return A pointer of type CAppItemsList
     */
     static CAppInfoMap* NewL( MInfoMap* aIter );
    
    /**
    * Destructor.
    */
    ~CAppInfoMap();

    /**
    * Inserts a key-value pair element to the map collection. A default
    * implementation is provided in \c CLiwDefaultMap.
    *  
    * @param aKey the key to be stored
    * @param aValue the value associated with the key to be stored
    *
    * @see CLiwDefaultMap::InsertL
   */
    virtual void InsertL(const TDesC8& aKey, const TLiwVariant& aValue);
 
    /**
    * Finds a value stored in the map collection based on the key. 
    *  
    * @param aKey the key to be searched
    * @param aFndValue the value associated with the found key
    *
    * @return false if there is no key stored; true otherwise
    *
    */
    virtual TBool FindL(const TDesC8& aKey, TLiwVariant& aFndValue) const;
  
    /**
    * Returns the number of key-value pair stored in the map collection. 
    *  
    * @return the number of key-value pair stored in the map collection
    *
    */
    virtual TInt Count() const ;
  
    /**
    * Returns the key stored at the passed index. 
    *  
    * @param aIndex the index of the key to be found
    * @param aFndKey the key found at the passed index
    *
    * @return true if a key-value entry is found at the passed index;
    * false otherwise
    *
    * 
    */
    virtual TBool AtL(TInt aIndex, TDes8& aFndKey) const;
  
    /**
    * Removes a key from the map collection. A default
    * implementation is provided in \c CLiwDefaultMap.
    *  
    * @param aKey the key to be removed from the map
    *
    */
    
    
    /**
    * Removes a key from the map collection. A default
    * implementation is provided in \c CLiwDefaultMap.
    *  
    * @param aKey the key to be removed from the map
    *
    * @see CLiwDefaultMap::Remove
   */
    virtual void Remove(const TDesC8& aKey);
  
    /**
    * Default implementation of equality operator.
    *  
    * @param aMap the map to be compared
    *
    * @see CLiwDefaultMap::operator==
    * 
    */
    virtual TBool operator==(const CLiwMap& aMap) const;

private:
    
     /**
     * Parameterised constructor
     * @since  Series60 v3.2
     * @param  aIter holds a reference to the item list model
     */
    
     CAppInfoMap( MInfoMap* aIter );
    
private: // data

     /**
     * A pointer to Iterator of core class
     */
     MInfoMap* iMap;
   
    };

#endif // __CAPPINFOMAP_H
