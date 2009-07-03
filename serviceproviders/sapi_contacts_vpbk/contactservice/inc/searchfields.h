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




#ifndef C_SEARCHFIELDS_H
#define C_SEARCHFIELDS_H

//searchfields.h - defines mapping for contacts UIDs.
#include <VPbkEng.rsg>
#include <CVPbkFieldTypeRefsList.h>		//Used to specify search fields
#include <CVPbkContactManager.h>
#include <cntdef.h>

#include "contactservice.h"

class CContactService;

#define SIZEOFTABLE 79

const TInt KInvalidFieldID = -1;

//Structure to define the fields in the mapping table
typedef struct UIDMapping
	{
	TInt iFieldId;
	TPtrC8 iFieldValue;
	}MAPPING_TABLE;

//Mapping Table for different contact fields in contact model.
extern MAPPING_TABLE mappingTable[SIZEOFTABLE];

class CSearchFields:public CBase
{
    public:// Construction and Destruction
		
		/**
         * Two-phased constructor.
         * @return CSearchFields*
         */
        IMPORT_C static CSearchFields* NewL(CContactService* aContactService);
		static CSearchFields* NewL();
		/**
         * Destructor - virtual and class not intended
         * for derivation, so not exported
         */
    
    public:// General Functions - Exported	    
        IMPORT_C void AppendL(TDesC8& aFieldName);
		
		//Functions for internal use
		
		//Gets the RefField List
		CVPbkFieldTypeRefsList* GetFieldListL();
		
		//Gets the FieldKeyValue for the FieldId specified
	   	IMPORT_C static TPtrC8 GetFieldKeyFromId( TInt aFieldId );
	   	
	   	//Gets the FieldId for the FieldKeyValue specified
		IMPORT_C static TInt GetIdFromFieldKey(TDesC8& aFieldValue);
		
		//Gets the FieldId from Index
		static TInt GetIdfromIndex(TInt index);
		
		//Gets the size of the table
		static TInt GetSizeofTable();

		//Destructor
		~CSearchFields();

    private:		
		void ConstructL(CContactService* aContactService);	
    private: 
		//Pointer to contact service class		
        CContactService* iContactService;
        
        //FieldType Ref List
        CVPbkFieldTypeRefsList* iFieldList;
};

#endif //CONTACTMAPPINGTABLE_H
