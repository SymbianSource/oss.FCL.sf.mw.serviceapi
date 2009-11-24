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

#ifndef __CMGITEMSLIST_H
#define __CMGITEMSLIST_H

#include <liwgenericparam.h> 
#include "mgservice.hrh"

class MCLFItemListModel;
class MgMediaItemFactory;
class CMgMediaItem;
class CClfOperationObserver;

/**
 *  This class implements the abstract methods of CLiwIterable   
 *  class so that the user may iterate over the result 
 *  
 *  @since Series60 v3.2
 */
NONSHARABLE_CLASS( CMgItemsList ) : public CLiwIterable
    {

public:
       
    /**
     * Two-phased constructor.
     * @param aItemListModel holds a reference to the item list model
     * @param aCmdId specifies whether the SAPI is GetFiles or GetFilesInfo
     * @return A pointer of type CMgItemsList
     */
     static CMgItemsList* NewL( MCLFItemListModel* aItemListModel, CClfOperationObserver* aOperationObserver, TMgCmdId aCmdId );
    
    /**
    * Destructor.
    */
    ~CMgItemsList();


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
     * @param  aItemListModel holds a reference to the item list model
     * @param  aCmdId specifies whether the SAPI is GetFiles or GetFilesInfo
     */
    
    CMgItemsList( MCLFItemListModel* aItemListModel, CClfOperationObserver* aOperationObserver, TMgCmdId aCmdId );
    
private: // data

    /**
    * A pointer to MCLFItemListModel class
    */
    MCLFItemListModel* iItemListModel;
    
    CClfOperationObserver* iOperationObserver;
        
    /**
    * Indicates whether GetFiles or GetFilesInfo SAPI is being processed
    */
    TMgCmdId iCmdId;
    /**
    * Gives the total number of items in list model 
    */
    TInt iCount;
    /**
    * Gives the current item being processed
    */
    TInt iCurrent;
    /**
    * Store the file type of current list 
    */
    CMgMediaItem* iMediaItem;
    };

#endif // __CMGITEMSLIST_H
