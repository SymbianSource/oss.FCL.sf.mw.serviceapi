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
* Description:   Factory method for media types
*
*/



#ifndef __CMGMEDIAITEMFACTORY_H
#define __CMGMEDIAITEMFACTORY_H




// FORWARD DECLARATIONS
class MCLFItem;
class CMgMediaItem;

//CLASS DECLARATION
/**
 *  Media Item Factory implementation.
 *  Returns an appropriate instance depending on
 *  the type of a media item 
 *  
 *  @since S60 v3.2
 */
 
  
NONSHARABLE_CLASS( CMgMediaItemFactory ) : public CBase
    {

public:
    /**
     * Two-phased constructor.
     * 
     */
    static CMgMediaItemFactory* NewL();
    
    /**
    * Destructor.
    */
    ~CMgMediaItemFactory(){};

    /**
     * Returns a reference to a media type depending on the type
     * of the media item
     * @param aClfItem A reference to an MCLFItem object
     * @return An instance of CMgMediaItem
     */
    CMgMediaItem* GetMediaItemL( const MCLFItem& aClfItem );
    
    
private: 
        
    /**
     * Returns a reference to a media type depending on the type
     * of the media item
     * @param aClfItem A reference to an MCLFItem object
     * @return An instance of CMgMediaItem
     */
    CMgMediaItem* NewMediaItemL( const MCLFItem& aClfItem );


    };

#endif // __CMGMEDIAITEMFACTORY_H
