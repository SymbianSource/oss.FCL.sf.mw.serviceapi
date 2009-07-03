/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Includes call back slot methods.
*
*/

#ifndef LOGGINGCALLBACKSLOT_H_
#define LOGGINGCALLBACKSLOT_H_


/**
* forward declarations
*/
class CLogAsyncService ;
class CBase ;

class CCallbackSlot : public CBase
    {
    public:

        /**
        * NewL: Two phased construction
        */

        IMPORT_C static CCallbackSlot *NewL() ;

        /**
        * NewLC: Creates an instance of CLogSyncServiceClass
        * Two Phased constructor
        * returns newly allocated object.
        */

        static CCallbackSlot* NewLC() ;

        /**
        * Default Destructor
        */

        ~CCallbackSlot() ;

        /**
        * Get the transid.
        */

        inline TUint TransactionId()
            {
            return iTransId ;
            }

        /**
        * set active object
        */

        inline void SetActiveObj(CLogAsyncService * aActive)
            {
            iActive = aActive ;
            }

        /**
        * set the id
        */

        inline void SetUid(TUint aTransId)
            {
            iTransId = aTransId;
            }

        /**
        * get the id
        */

        inline TUint getUid()
            {
            return iTransId;
            }

        /**
        * get active object
        */

        inline CLogAsyncService * GetActiveObj()
            {
            return iActive  ;
            }

    private:

        TUint iTransId ;
        CLogAsyncService * iActive ;
    };

#endif
