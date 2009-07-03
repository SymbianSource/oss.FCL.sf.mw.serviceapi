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


#ifndef __CSYSINFOLISTS_H
#define __CSYSINFOLISTS_H

#include <liwgenericparam.h> 

class CAccList;
class CAccessoryInfo;
class CConnectionList;

/**
 *  This class implements the abstract methods of CLiwIterable   
 *  class so that the user may iterate over the result 
 *  
 *  @since Series60 v3.2
 */
NONSHARABLE_CLASS( CSysInfoAccList ) : public CLiwIterable
    {
    public:

    /**
    * Two-phased constructor.
    * @param aAccList holds a reference to the item list model
    * @return A pointer of type CSysInfoAccList
    */
    static CSysInfoAccList* NewL(const CAccList* aAccList );

    /**
    * Destructor.
    */
    ~CSysInfoAccList();

    /**
    * Resets the iterator to point to the beginning of list
    * @param void
    * @return void
    */
    void Reset();	

    /**
    * Constructs the next accessory item in the form of a map
    * @param TLiwVariant an output parameter that contains the result
    * @return TBool On success this returns ETrue else returns EFalse
    */	
    TBool NextL( TLiwVariant& aItem );

    private:
    /**
    * Parameterised constructor
    * @since  Series60 v3.2
    * @param  aItemListModel holds a reference to the item list model
    * @param  aCmdId specifies whether the SAPI is GetFiles or GetFilesInfo
    */

    CSysInfoAccList(const CAccList* aAccList );

    private: // data

    /**
    * A pointer to MCLFItemListModel class
    */
    const CAccList* iAccList;

    /**
    * Gives the total number of items in list model 
    */
    TInt iCount;
    /**
    * Gives the current item being processed
    */
    TInt iCurrent;
    };

/**
 *  This class implements the abstract methods of CLiwIterable   
 *  class so that the user may iterate over the result 
 *  
 *  @since Series60 v3.2
 */
NONSHARABLE_CLASS( CSysInfoConnList ) : public CLiwIterable
    {
    public:

    /**
    * Two-phased constructor.
    * @param aItemListModel holds a reference to the item list model
    * @param aCmdId specifies whether the SAPI is GetFiles or GetFilesInfo
    * @return A pointer of type CSysInfoAccList
    */
    static CSysInfoConnList* NewL(const CConnectionList* aConnList );

    /**
    * Destructor.
    */
    ~CSysInfoConnList();

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
    * @param  aConnList holds a reference to the item list model
    */

    CSysInfoConnList(const CConnectionList* aConnList );

    private: // data

    /**
    * A pointer to MCLFItemListModel class
    */
    const CConnectionList* iConnList;

    /**
    * Gives the total number of items in list model 
    */
    TInt iCount;
    /**
    * Gives the current item being processed
    */
    TInt iCurrent;
    };

#endif // __CSYSINFOLISTS_H
