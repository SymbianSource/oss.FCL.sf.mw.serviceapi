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
* Description:   Holds information common to all media types
*
*/



#ifndef __CMGMEDIAITEM_H
#define __CMGMEDIAITEM_H
#include <e32const.h>
#include <e32base.h>
#include <e32std.h>
#include <e32cmn.h>

#include "liwvariant.h"
#include "liwgenericparam.h" 

class MCLFItem;
class CLiwDefaultMap;
/**
 *  Base class for all media types
 *  Responsible for filling parameters common to all media types
 *  
 *  @since Series60 v3.2
 */
NONSHARABLE_CLASS( CMgMediaItem ) : public CBase
    {


public:
   
    
       
    /**
    * Destructor.
    */
    ~CMgMediaItem(){};

    /**
     * This is a pure virtual function, the appropriate version 
     * of FillInfo gets called depending on the object pointed to 
     * @param aOutputMap contains a list of key-value pairs specific 
     * to a media type
     * @param aClfItem A reference to the list model item to be processed
     * @return void
     */
    virtual void FillInfo( CLiwDefaultMap *aOutputMap, const MCLFItem& aClfItem ) = 0;
    
        
protected:
    /**
     * This function gets the information common to all media types 
     * @param aMediaItemMap a list of key-value pairs common to all 
     * media types
     * @param aClfItem A reference to the list model item to be processed
     * @return void
     */
    void FillCommonAttributes(CLiwDefaultMap* aMediaItemMap, const MCLFItem& aClfItem);
    
        
    };

#endif // __CMGMEDIAITEM_H
