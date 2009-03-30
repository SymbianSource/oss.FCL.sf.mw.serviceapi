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


#ifndef SINGLECONTACTFIELD_H
#define SINGLECONTACTFIELD_H

/**
 * CSingleContactField : Class that represents a field in a given contact Item.
 * This class is used to create a contact item and add it to the database and also
 * it is used to return a contact from the database.
 */ 
class CSingleContactField:public CBase
{
    public:		
		/**
         * NewL() Method for CSingleContactField class
         * @return CSingleContactField*
         */
    IMPORT_C static CSingleContactField* NewL();
		
		/**
         * Destructor - virtual and class not intended
         * for derivation, so not exported
         */
    
    public:// General Functions - Meant for use within the dll
    	    
	    /**
         * Gets the Field Key, The Label and the Value of the field.
         * @param aFieldkey A reference to hold the resultant field key.
         * @param aLabel A reference to hold the resultant Label.
         * @param aValue A reference to hold the resultant Value.
         * @return None.
         */
		IMPORT_C void GetFieldDataL(TPtrC8& aFieldkey,
		                            TPtrC& aLabel,
		                            TPtrC& aValue);
				
		/**
         * Gets the Group Label and the array containing 
         * the contact id's of the group         
         * @param aGroupLabel A reference to hold the resultant Label.
         * @param aArray A reference to array that contains the contact id's.
         * @return None.
         */
		IMPORT_C void GetFieldDataL(TPtrC& aGroupLabel,
		                            RPointerArray<TDesC8>& aArray);
	 		
	   /**
	     * Sets the Field Key, The Label and the Value of the field.         
         * @param aFieldkey A reference that holds the fieldkey.
         * @param aLabel A reference that holds the Label.
         * @param aValue A reference that holds the Value.
         * @return None.
         */
		IMPORT_C void SetFieldParamsL(const TDesC8& Fieldkey,
		                              const TDesC& aLabel,
		                              const TDesC& aValue);
	    
	    /**
         * Sets the Label and the id arrray  of the group.                  
         * @param aGroupLabel A reference that holds the Label.
         * @param aArray A reference to array that contains the contact id's.
         * @return None.
         */
	    void SetFieldParamsL(const TPtrC& aGroupLabel,
	                         RPointerArray<HBufC8>& aArray);
	    
	    /**
	     * Get Method for time.
	     * @param none.
	     * @return TTime.
	     */
		IMPORT_C TTime GetDateTime();	    

	    /**
	     * Set Method for time.
	     * @param TTime.
	     * @return None.
	     */
	    IMPORT_C void SetDateTime(TTime aDateTime);
	    		
		/**
	     * CSingleContactField Destructor.
	     * @param None.
	     * @return None.
	     */
	    ~CSingleContactField();
	
    private:

        /**
	     * Second phase Constructor.
	     * @param None.
	     * @return None.
	     */
		void ConstructL();
		/**
	     * Default Constructor.
	     * @param None.
	     * @return None.
	     */
		CSingleContactField();
		
    private: //Data Members
    
    //FieldKey, Label, and Value in a given field
    HBufC8* iFieldKey;
    HBufC* iLabel;
    HBufC* iValue;
    
    //In case the value is of type TTime
    TTime iDateAndTime;
   
    //In case we are iterating a group
    HBufC* iGroupLabel;
    RPointerArray<HBufC8> iContactIdArray;

};

#endif //SINGLECONTACTFIELD_H