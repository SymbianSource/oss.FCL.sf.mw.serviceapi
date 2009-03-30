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
* Description:  Provides utility functions
*
*/


#ifndef SINGLECONTACT_H
#define SINGLECONTACT_H

#include <e32base.h>
#include <MVPbkStoreContact.h>
#include "contactservice.h"

//User includes
#include "searchfields.h"
#include "singlecontactfield.h"

//Class declarations
class CContactService;
class CSearchFields;
class CSingleContactField;

//Wrapper class around a single contact item of type MVPbkStoreContact
class CSingleContact:public CBase
{
    public:
		
		/**
         * NewL() Method for CSingleContact class
         * @return CSingleContact*
         */
        static CSingleContact* NewL(MVPbkStoreContact* aSingleContact, 
                                    Ttype aIndicator);
        
        IMPORT_C
        static CSingleContact* NewL();
   		/*
		 * Constructor
		 */
		CSingleContact();
		void ConstructL(MVPbkStoreContact* aSingleContact, 
		                Ttype aIndicator);
		void ConvertContactToFieldListL(MVPbkStoreContact* aSingleContact);
		
	public:
		/*
		 * Remove a field from the Contact.
		 */
		IMPORT_C TInt RemoveField( TInt aIndex );
		
		/*
		 * Remove all fields from a Contact.
		 */
		IMPORT_C void RemoveAllFields();
		
		/* 
		 * Sets the contact id for a contact
		 */
		IMPORT_C void SetContactIdL(const TDesC8& aContactId);
		
		/* 
		 * Gets the contact id of a contact
		 */
		IMPORT_C TDesC8& GetContactId();
		
		
		/*
		 * Creates a field with the specified fields and adds it to the contact.
		 */
		IMPORT_C void AddFieldToContactL(const CSingleContactField* aField );
 

		/* 
		 *General Functions - Exported		 
		 */
		CSingleContactField* NextFieldL(MVPbkStoreContact* aSingleContact, 
		                                TInt aIndex);
				
		/*
		 *Get the  number of fields in the contact
		 */
		IMPORT_C TInt FieldCount();
		/*
		 *Get the field at the index;
		 */
		IMPORT_C CSingleContactField* FieldAt(TInt aIndex);
		
   		/**
         * Destructor 
         */
		~CSingleContact();
    	
    private: //Data members
    	//No.of Fields
	    TInt iFieldCount;
	    //Index
	    TInt iFieldIndex;
	    
	    Ttype iIndicator;	        		        	
    	/* 
		 * Pointer to a contact id
		 */
    	HBufC8* iContactId;
    	
    	RPointerArray<CSingleContactField> iFields;
};

#endif //SINGLECONTACT_H