/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  List implementation
*
*/


#include"sysinfolists.h"
#include"sysinfointerface.h"
#include"sysinfo.h"

using namespace LIW ;
const TInt KStartItemIndex = -1;

// ---------------------------------------------------------------------------
// CSysInfoAccList::CSysInfoAccList
// Parameterised constructor
// ---------------------------------------------------------------------------
//

CSysInfoAccList::CSysInfoAccList(const CAccList* aAccList )
                                :iAccList(aAccList),
                                iCount(iAccList->Count()),
                                iCurrent(KStartItemIndex)
    {
    }

// ---------------------------------------------------------------------------
// CSysInfoAccList::NewL
// Two-phased constructor
// ---------------------------------------------------------------------------
//
CSysInfoAccList* CSysInfoAccList::NewL(const CAccList* aAccList )
    {
    return new( ELeave ) CSysInfoAccList(aAccList);
    }

// ---------------------------------------------------------------------------
// CSysInfoAccList::~CSysInfoAccList
// Class destructor
// ---------------------------------------------------------------------------
//
CSysInfoAccList::~CSysInfoAccList()
    {
    delete iAccList;
    }

// ---------------------------------------------------------------------------
// CSysInfoAccList::Reset
// Resets the iterator to point to the beginning of list
// ---------------------------------------------------------------------------
//

void CSysInfoAccList::Reset()
    {
    iCurrent = KStartItemIndex;
    }

// ---------------------------------------------------------------------------
// CSysInfoAccList::NextL
// Constructs the next media item in the form of a map
// ---------------------------------------------------------------------------
//
TBool CSysInfoAccList::NextL(TLiwVariant& aItem)
    {
    iCurrent++;
    if( iCurrent<iCount )
        {
        const CAccessoryInfo* temp;
        iAccList->AtL( iCurrent,temp );

        CAccessoryInfo* accItem = (CAccessoryInfo*) temp;
        CleanupStack::PushL( accItem );
        CLiwDefaultMap *outputMap = NULL;
        CSysInfoInterface::ConvertSysData2AiwParamL(accItem,(CLiwMap*&)outputMap);
        CleanupStack::PopAndDestroy(accItem);

        //Place output map on cleanup stack.
        CleanupClosePushL(*outputMap);
        aItem.SetL( TLiwVariant( outputMap ) );
        CleanupStack::PopAndDestroy(outputMap);
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

// ---------------------------------------------------------------------------
// CSysInfoConnList::CSysInfoConnList
// Parameterised constructor
// ---------------------------------------------------------------------------
//
CSysInfoConnList::CSysInfoConnList(const CConnectionList* aConnList )
                                            :iConnList(aConnList),
                                            iCount(iConnList->Count()),
                                            iCurrent(KStartItemIndex)
    {
    }
// ---------------------------------------------------------------------------
// CSysInfoAccList::NewL
// Two-phased constructor
// ---------------------------------------------------------------------------
//
CSysInfoConnList* CSysInfoConnList::NewL(const CConnectionList* aConnList )
    {
    return new( ELeave ) CSysInfoConnList(aConnList);
    }

// ---------------------------------------------------------------------------
// CSysInfoAccList::~CSysInfoAccList
// Class destructor
// ---------------------------------------------------------------------------
//
CSysInfoConnList::~CSysInfoConnList()
    {
    delete iConnList;
    iConnList = NULL ;
    }
    
// ---------------------------------------------------------------------------
// CSysInfoAccList::Reset
// Resets the iterator to point to the beginning of list
// ---------------------------------------------------------------------------
//
void CSysInfoConnList::Reset()
    {
    iCurrent = KStartItemIndex;
    }

// ---------------------------------------------------------------------------
// CSysInfoAccList::NextL
// Constructs the next media item in the form of a map
// ---------------------------------------------------------------------------
//
TBool CSysInfoConnList::NextL( TLiwVariant& aItem )
    {
    iCurrent++;

    if( iCurrent<iCount )
        {
        const CConnectionInfo* temp;
        iConnList->At( iCurrent,temp );

        CConnectionInfo* connItem = (CConnectionInfo*) temp;
        CLiwDefaultMap *outputMap = NULL;

        CSysInfoInterface::CSysInfoInterface::ConvertSysData2AiwParamL(
                                            connItem,(CLiwMap*&)outputMap );
        CleanupClosePushL(*outputMap);
        aItem.SetL(TLiwVariant(outputMap));
        CleanupStack::PopAndDestroy(outputMap);
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }
//End of file
