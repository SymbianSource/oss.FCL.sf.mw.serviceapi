/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/


#include <MVPbkFieldType.h>
#include <MVPbkContactFieldTextData.h>
#include <MVPbkContactLink.h>
#include <MVPbkContactLinkArray.h>
#include <MVPbkContactGroup.h>
#include <barsread.h>
#include <eikenv.h>
#include <TVPbkFieldTypeMapping.h>
#include <MVPbkContactFieldTextData.h>					     
#include <MVPbkContactFieldData.h>
#include <MVPbkContactFieldBinaryData.h>
#include <MVPbkContactFieldDateTimeData.h>			      
#include <MVPbkStoreContactField.h>

#include "singlecontact.h"

//NewL method for CSingleContact class. It holds MVPbkStoreContact variable as its member
CSingleContact* CSingleContact::NewL(MVPbkStoreContact* aSingleContact, Ttype aIndicator)
    {
	CSingleContact* self = new( ELeave ) CSingleContact();
	CleanupStack::PushL( self );
	self->ConstructL(aSingleContact, aIndicator);
	CleanupStack::Pop( self );
	return self;
    }

EXPORT_C
CSingleContact* CSingleContact::NewL()
    {
    CSingleContact* self = new( ELeave ) CSingleContact();
    CleanupStack::PushL( self );
    self->iContactId = KNullDesC8().AllocL();
    CleanupStack::Pop( self );
	return self;		
    }


// ---------------------------------------------------------------------------
//Constructor
// ---------------------------------------------------------------------------
CSingleContact::CSingleContact()
	{	
	}

void CSingleContact::ConstructL(MVPbkStoreContact* aSingleContact, Ttype aIndicator)
    {
	iIndicator = aIndicator;
	iContactId = KNullDesC8().AllocL();
	ConvertContactToFieldListL(aSingleContact);
    }

void CSingleContact::ConvertContactToFieldListL(MVPbkStoreContact* aSingleContact)
    {

	if(aSingleContact)
	{
	TInt fieldCount = aSingleContact->Fields().FieldCount();	
	CSingleContactField* field = NULL;
	for(TInt fieldIndex = 0; fieldIndex < fieldCount ; fieldIndex++)
		{
		field = NextFieldL(aSingleContact, fieldIndex);
		if(field !=NULL)
			{
			iFields.AppendL(field);	
			}
		}
	}
		delete aSingleContact;

    }
//Returns the Next field in the contact if any, otherwise returns NULL
CSingleContactField* CSingleContact::NextFieldL(MVPbkStoreContact* aSingleContact, TInt aIndex)
	{
    TPtrC text(KNullDesC);
    TTime time;
    TPtrC8 val;
    
	CSingleContactField* contactField = CSingleContactField::NewL();
    CleanupStack::PushL(contactField);
	if(iIndicator == EContacts)
		{
		//Get the field at iFieldIndex in the contact
		MVPbkStoreContactField& field = aSingleContact->Fields().FieldAt(aIndex);
		
		//Get the fieldKey of the field 
	    TPtrC8 fieldKey = CSearchFields::GetFieldKeyFromId(field.BestMatchingFieldType()->FieldTypeResId());
		if(fieldKey.Compare(KNullDesC8) == 0)
			{
			CleanupStack::PopAndDestroy(contactField);		
			return NULL;
			}
		//Get the label of the field
	    TPtrC label(field.FieldLabel());
       		
		//Get the value of the field

		TVPbkFieldStorageType storageType = field.FieldData().DataType();
		//TBuf<KMinHeapGrowBy> value;
		
	    if( EVPbkFieldStorageTypeBinary == storageType )
	    	{
	        val.Set((MVPbkContactFieldBinaryData::Cast(field.FieldData())).BinaryData());
	        //value.Copy(val);
	    	}
	    else if( EVPbkFieldStorageTypeDateTime == storageType )
	    	{
	    	time = (MVPbkContactFieldDateTimeData::Cast(field.FieldData())).DateTime();
	    	contactField->SetDateTime(time);
	    	}
	    else
	    	{
	    	text.Set((MVPbkContactFieldTextData::Cast(field.FieldData())).Text());
	    	}
			
		//Set the parameters in CSingleContactField object
		contactField->SetFieldParamsL(fieldKey, label, text);
		
		}
	else if(iIndicator == EGroups)
		{
		TPtrC groupLabel = (aSingleContact->Group())->GroupLabel();
		
		MVPbkContactLinkArray* linkArray = (aSingleContact->Group())->ItemsContainedLC();
		TInt noOfEntries = linkArray->Count();		    	
		if(noOfEntries > 0)
			{
			RPointerArray<HBufC8> array(noOfEntries);
			CleanupClosePushL(array);
			const HBufC8* packedLink;
			
			for(int i=0; i<noOfEntries; i++)
				{
				packedLink = const_cast <MVPbkContactLink&>(linkArray->At(i)).PackLC();
				array.AppendL(packedLink);
				}
			
			//Set the parameters in CSingleContactField object
			contactField->SetFieldParamsL(groupLabel, array);

			CleanupStack::Pop(noOfEntries);
            CleanupStack::Pop(&array);		    		
			}
		else
			{
			RPointerArray<HBufC8> array;
			//Set the parameters in CSingleContactField object
			contactField->SetFieldParamsL(groupLabel, array);
			}
		CleanupStack::PopAndDestroy();
		}
	CleanupStack::Pop(contactField);		
	return contactField;
	}
// ---------------------------------------------------------------------------
//Sets the contact id of a contact
// ---------------------------------------------------------------------------
EXPORT_C void CSingleContact::SetContactIdL(const TDesC8& aContactId)
	{
	if(iContactId)
    	{
    	delete iContactId;
    	iContactId = NULL;
    	}
    iContactId = aContactId.AllocL();
	}

// ---------------------------------------------------------------------------
//Gets the contact id of a contact
// ---------------------------------------------------------------------------
 EXPORT_C TDesC8& CSingleContact::GetContactId()
	{	    
    return *iContactId;
	}
// ---------------------------------------------------------------------------
// CSingleContact::RemoveFieldL
// Removes the specified field from the contact
// ---------------------------------------------------------------------------

EXPORT_C TInt CSingleContact::RemoveField(TInt aIndex)
    {
	TInt retVal = KErrArgument;
	
	if((aIndex >= 0) && (aIndex < iFields.Count()))
		{
		delete iFields[aIndex];
		iFields[aIndex] = NULL;
		iFields.Remove(aIndex);
		retVal = KErrNone;
		}
	
	return retVal;
    }


// ---------------------------------------------------------------------------
// CSingleContact::RemoveAllFields
// Removes all fields from the contact
// ---------------------------------------------------------------------------

EXPORT_C void CSingleContact::RemoveAllFields()
    {
	iFields.ResetAndDestroy();
    }


// ---------------------------------------------------------------------------
// CSingleContact::AddFieldToContactL
// Add a Field to Contact
// ---------------------------------------------------------------------------

EXPORT_C void CSingleContact::AddFieldToContactL( const CSingleContactField* aField )
    {
    iFields.AppendL(aField);	
    } 
    

//Destructor
CSingleContact::~CSingleContact()
	{
	iFields.ResetAndDestroy();
	delete iContactId;
	}
	

//Get the  number of fields in the contact
EXPORT_C 
TInt CSingleContact::FieldCount()
    {
	return iFields.Count();
    }
//Get the field at the index;
EXPORT_C 
CSingleContactField* CSingleContact::FieldAt(TInt aIndex)
    {
    if((aIndex >= 0) && (aIndex < iFields.Count()))
    	{
    	return iFields[aIndex];	
    	}
    else
    	{
    	return NULL;	
    	}
    }

