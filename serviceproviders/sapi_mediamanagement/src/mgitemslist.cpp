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


#include <MCLFItem.h>
#include <MCLFItemListModel.h>

#include "mgitemslist.h"
#include "mgmediaitemfactory.h"
#include "mgmediaitem.h"
#include "mgclfoperationobserver.h"


_LIT8( KMgFileNameAndPath, "FileNameAndPath" );

const TInt KStartItemIndex = -1;

// ---------------------------------------------------------------------------
// CMgItemsList::CMgItemsList
// Parameterised constructor
// ---------------------------------------------------------------------------
//

CMgItemsList::CMgItemsList( MCLFItemListModel* aItemListModel, CClfOperationObserver* aOperationObserver, TMgCmdId aCmdId )
            : iItemListModel(aItemListModel),
              iOperationObserver(aOperationObserver),
            	iCmdId(aCmdId),
              iCount(iItemListModel->ItemCount()),
              iCurrent(KStartItemIndex),
  						iMediaItem(NULL)
    {

    }
// ---------------------------------------------------------------------------
// CMgItemsList::NewL
// Two-phased constructor
// ---------------------------------------------------------------------------
//

CMgItemsList* CMgItemsList::NewL( MCLFItemListModel* aItemListModel, CClfOperationObserver* aOperationObserver, TMgCmdId aCmdId )
    {
    return new( ELeave ) CMgItemsList( aItemListModel, aOperationObserver, aCmdId );
    }


// ---------------------------------------------------------------------------
// CMgItemsList::~CMgItemsList
// Class destructor
// ---------------------------------------------------------------------------
//
CMgItemsList::~CMgItemsList()
    {

    if(iItemListModel)
        {
            iItemListModel->CancelRefresh();
            delete iItemListModel;
            iItemListModel = NULL;
        }
    if(iOperationObserver)
        {
            delete iOperationObserver;
            iOperationObserver = NULL;
        }
    if(iMediaItem)
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
    
    if( iCurrent< iCount )
        {

        const MCLFItem& item = iItemListModel->Item( iCurrent );

        TPtrC fullPath;
        item.GetField( ECLFFieldIdFileNameAndPath, fullPath );

        CLiwDefaultMap *outputMap = CLiwDefaultMap::NewL();
        CleanupStack::PushL( outputMap );
        outputMap->InsertL( KMgFileNameAndPath,TLiwVariant( fullPath ) );

       // if( EMgGetFilesInfo == iCmdId )// if user requests for file metadata
            //{
            if( NULL == iMediaItem )
                {
            	iMediaItem = MgMediaItemFactory::GetMediaItemL( item );

       	        if( NULL == iMediaItem )
       	            {
       	    		return KErrNotSupported;
       	        	}
                }
           	iMediaItem->FillInfoL( outputMap, item );
            //}

	    aItem.SetL( TLiwVariant( outputMap ) );
	    if( outputMap )
		    {
		    outputMap->DecRef();
		    }
	    CleanupStack::Pop( outputMap );
        return ETrue;

        }
    else
        {

        return EFalse;

        }
    }





