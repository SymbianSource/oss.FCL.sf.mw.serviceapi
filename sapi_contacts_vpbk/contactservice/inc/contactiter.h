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
* Description:  Provides the Iterator
*
*/


#ifndef C_CCONTACTITER_H
#define C_CCONTACTITER_H

//System include files
#include <MVPbkStoreContact.h>
#include <MVPbkContactLinkArray.h>
#include <CVPbkContactManager.h>
#include <badesca.h>

#include "contactservice.h"
#include "contactservice.hrh"
#include "syncbehaviour.h"
#include "singlecontact.h"

//Class Declarations

class CContactService;
class CContactRetrieveObserver;
class CSingleContact;
class CGetListStoreListObserver;

/**
 * CContactIter - Iterator Class
 * @since S60 5.0
 */
class CContactIter:public CBase
{
    public:// Construction and Destruction
			
		/**
         * Two-phased constructor.
         * @return CContactIter*
         */
        IMPORT_C static CContactIter* NewL();
		
		/**
         * Destructor - virtual and class not intended
         * for derivation, so not exported
         */
	    virtual ~CContactIter();
    
    public:// General Functions - Exported	    
        /**
		 * NextL
		 * 
		 * Gets the Next Contact/Group
		 *
		 * Returns pointer to contact/group and also the ContactId in the form 
		 * of a buffer
		 * @return MVPbkStoreContact* and  HBufC8* respectively
		 */
        IMPORT_C void NextL(CSingleContact*& aSingleContact, HBufC8*& aContactID);
        /**
		 * NextL
		 * 
		 * Gets the Next Database Name
		 *
		 * Returns pointer to the DbName
		 * @return TPtrC16*
		 */
        IMPORT_C void NextL(TPtrC& iDbs);
        /**
		 * Reset
		 * 
		 * Resets the cursor position 
	  	 * @return void
		 */
        IMPORT_C void Reset();
        /**
         * Sets the iContacts which is array of contact ids
         *
         * @param aContactIdArray - Array of Contact Ids
         * @return void
         */	
        TInt SetParams(MVPbkContactLinkArray * aContactIdArray,
        			   const TDesC& aStoreUri,
        			   TOrder aSortOrder,
        			   TInt aTransId,
        			   Ttype aIndicator,
        			   CContactService* aContactService);
        /**
         * Sets the iDbNamePtr which is array of Database names
         * and the number of them
         * @return void
         */	
        void SetDbNamePtr(RPointerArray<HBufC>& aArray, TInt aCnt);

        /**
         * Sets the iContact member variable
         * @return void
         */	
        void SetContactFetchResult(MVPbkStoreContact* aContact);  
        
        
        //Sets up Environment before NextL() is called
        void SetupEnvironL();
                
        // Sets up the Database
        void SetupDBL();
        
        //Reads the contact from the database
        void ReadContactL(const MVPbkContactLink& aLink, 
                          CContactRetrieveObserver& aObserver);
    private:
        
        /** 
		 * C++ constructor - not exported;
		 * implicitly called from NewLC()
		 */
	    CContactIter();
                 
        
   private: 
        // POINTER MEMBERS
        /**
         * Pointer to the array of contact Links
         */  
		MVPbkContactLinkArray* iContactLinkArray;
        
        // Index or Cursor 
		TInt iCursor; 
		
		// Number of search results
		TInt iCount;
		
		// Pointer to list of Database names
		RPointerArray<HBufC> iDbArray;
		
		// Contact info
		MVPbkStoreContact* iContact;
		
		//File Session
	    RFs iFs;
	    
	    // Store Uri
		const TDesC* iStoreUri;
		
		//Order in which to sort
		TOrder iSortOrder;
		
		//Contact Manager
		CVPbkContactManager* iContactManager;
		
		//Contact Store
		MVPbkContactStore* iContactStore;
		
		//Pointer to Service Class
		CContactService* iContactService;
		
		//Handle to GetlistStoreList Observer
		CGetListStoreListObserver* iGetListStoreListObserver ;
		
		//Transaction Id
		TInt iTransId;
public:
		//Synchronous Iterator
		CContactSyncIter* iSyncIter;
				
		//Indicator for the kind of data iterator is iterating on.
		Ttype iIndicator;
};
#endif // C_CCONTACTITER_H