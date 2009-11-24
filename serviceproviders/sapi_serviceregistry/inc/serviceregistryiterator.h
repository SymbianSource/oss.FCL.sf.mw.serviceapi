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


#ifndef __CSVCREGITERATOR_H
#define __CSVCREGITERATOR_H

#include <liwgenericparam.h> 
#include <liwcommon.h>
#include <liwvariant.h>

/**
 *  This class implements the abstract methods of CLiwIterable   
 *  class so that the user may iterate over the result 
 *  
 *  @since Series60 v3.2
 */
NONSHARABLE_CLASS( CSvcRegIterator ) : public CLiwIterable
    {

public:
       
    /**
     * Two-phased constructor.     
     * @return A pointer of type CSvcRegIterator
     */
     static CSvcRegIterator* NewL();
    
    /**
    * Destructor.
    */
    ~CSvcRegIterator();
    /**
     * Resets the iterator to point to the beginning of list
     * @param void
     * @return void
     */
    void Reset();	
    
    /**
     * Constructs the next meta data item in the form of a map
     * @param TLiwVariant an output parameter that contains the result
     * @return TBool On success this returns ETrue else returns EFalse
     */	
    TBool NextL( TLiwVariant& aItem );

    void SetProviderDataList(RCriteriaArray* aList);        
private:
    
    //Default constructor.
    CSvcRegIterator();
    
private: // data    
    TInt iCount;
    /**
    * Gives the current item being processed
    */
    TInt iIndex; 
    
    //The list of providers
    RCriteriaArray* iProviderDataList;    
    };

#endif // __CSVCREGITERATOR_H
