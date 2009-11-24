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
* Description:   Implements CLiwIterable type
*
*/



#include <MCLFItem.h>
#include <MCLFItemListModel.h>

#include "mgitemslist.h"
#include "mgmediaitemfactory.h"
#include "mgmediaitem.h"


_LIT8( KMgFileNameAndPath, "FileNameAndPath" );

const TInt KStartItemIndex = -1;

// ---------------------------------------------------------------------------
// CMgItemsList::CMgItemsList
// Parameterised constructor
// ---------------------------------------------------------------------------
//
 
CMgItemsList::CMgItemsList( MCLFItemListModel* aItemListModel, TMgCmdId aCmdId )
    {
    iItemListModel = aItemListModel; 
    iCount = iItemListModel->ItemCount(); 
    iCurrent = KStartItemIndex; 
    iCmdId = aCmdId; 
    iMediaItem = NULL; 
    
    }
// ---------------------------------------------------------------------------
// CMgItemsList::NewL
// Two-phased constructor
// ---------------------------------------------------------------------------
//
 
CMgItemsList* CMgItemsList::NewL( MCLFItemListModel* aItemListModel, TMgCmdId aCmdId )
    {
    CMgItemsList* self = new( ELeave ) CMgItemsList( aItemListModel, aCmdId);
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CMgItemsList::ConstructL
// Two-phased constructor
// ---------------------------------------------------------------------------
//
 
void CMgItemsList::ConstructL()
    {
    iMGMediaItemFactory = CMgMediaItemFactory::NewL();
    }
// ---------------------------------------------------------------------------
// CMgItemsList::~CMgItemsList
// Class destructor
// ---------------------------------------------------------------------------
//
CMgItemsList::~CMgItemsList()
    {
  	if( iItemListModel )
	  	{
	  	delete iItemListModel;
	  	iItemListModel = NULL;
	  	}
  	
  	if( iMGMediaItemFactory )
	  	{
	  	delete iMGMediaItemFactory;
		iMGMediaItemFactory = NULL;	
	  	}
	  	
  	if( iMediaItem )
	  	{
	  	delete iMediaItem;
		iMediaItem = NULL;	
	  	}
	
	}
// ---------------------------------------------------------------------------
// CMgItemsList::Reset
// Resets the iterator to point to the beginning of list
// ---------------------------------------------------------------------------
//

void CMgItemsList::Reset() 
    {
    iCurrent = KStartItemIndex;// if user resets the list
    }
    

// ---------------------------------------------------------------------------
// CMgItemsList::NextL
// Constructs the next media item in the form of a map
// ---------------------------------------------------------------------------
//
TBool CMgItemsList::NextL( TLiwVariant& aItem )
    {
    iCurrent++;
    if( iCurrent<iCount )
        {
        const MCLFItem& item = iItemListModel->Item( iCurrent );
        TPtrC fullPath;
        item.GetField(ECLFFieldIdFileNameAndPath, fullPath );
        CLiwDefaultMap *outputMap = CLiwDefaultMap::NewL();
        outputMap->InsertL(KMgFileNameAndPath,TLiwVariant(fullPath));
        if( iCmdId==EMgGetFilesInfo )// if user requests for file metadata
            {
            if( NULL == iMediaItem ) 
                {
            	iMediaItem = iMGMediaItemFactory->GetMediaItemL( item );
                }
           	if( NULL == iMediaItem )
           	    {
           		return KErrNotSupported;
           	    }
           	iMediaItem->FillInfo( outputMap, item ); 
            }
	    aItem.SetL(TLiwVariant(outputMap)); 
        return ETrue;	
        }
    else
        {
        return EFalse;	
        }
    }
    




