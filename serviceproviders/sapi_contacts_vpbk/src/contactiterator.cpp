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
* Description:  Iterator in the output of GetList
*
*/


#include "contactiterator.h"
#include "contactinterface.hrh"

/*
-----------------------------------------------------------------------------
    CContactIterator::~CContactIterator()
    Description    : Destructor
    Return values  : N/A
-----------------------------------------------------------------------------
*/
CContactIterator::~CContactIterator()
	{
	delete iContactIter; 
	}


/*
-----------------------------------------------------------------------------
    CContactIterator::NewL()
    Description    : Allocates memory
    Return values  : Returns class instance
-----------------------------------------------------------------------------
*/

CContactIterator* CContactIterator::NewL(CContactIter* aIter)
	{
	return (new (ELeave) CContactIterator(aIter));
	}


/*
-----------------------------------------------------------------------------
    CContactIterator::CContactIterator()
    Description    : Constructor- Initializes data
    Return values  : N/A
-----------------------------------------------------------------------------
*/
CContactIterator::CContactIterator(CContactIter* aIter)
	{
	iContactIter = aIter;
	iIndex = -1;
	}

/*
-----------------------------------------------------------------------------
    CContactIterator::Reset()
    Description    : Resets the cursor of the iterator to -1
    Return values  : N/A
-----------------------------------------------------------------------------
*/
void CContactIterator:: Reset()
	{
	iIndex=-1;
	}

/*
-----------------------------------------------------------------------------
    CContactIterator::GetContactIDUTF()
    Description    : Converts to UTF format
    Return values  : N/A
-----------------------------------------------------------------------------
*/
void CContactIterator :: ContactIDToUTF(HBufC* aContactID)
    {
    TInt len = aContactID->Length();
    TUint16* ptr16 = const_cast<TUint16*> (aContactID->Des().Ptr());
    for(TInt i=0; i<len; i++)
        {
        ptr16[i] = ptr16[i] | 0xE000;    
        }
    }

/*
-----------------------------------------------------------------------------
    CContactIterator::NextL()
    Description    : returns in outparam, the next item in the list that iterator
    				 is iterating on
    Return values  : ETrue/EFalse based on success or failure
-----------------------------------------------------------------------------
*/  
TBool CContactIterator::NextL(TLiwVariant& aEntry)
	{

	CLiwMap* pContactMap = NULL;
	TBool retVal = EFalse;
	RPointerArray<HBufC> xspidArray;
	CLiwList* IdList = NULL;
	TLiwVariant outputVal;
	//If iterator is iterating over contacts
	if(iContactIter->iIndicator == EContacts)
		{
	    CSingleContact* contact = NULL;
	    HBufC8* cntId = NULL ;
	    CSingleContactField* field =  NULL;
		HBufC* cntIdUnicode = NULL;
		
		//Get the next contact on the list
		iContactIter->NextL(contact, cntId);
			
		if(contact)
			{
			TPtrC8 fieldName;
        	TPtrC  fieldLabel;
        	TPtrC  fieldValue;
        	TTime  fieldTime;
        	TBool date = EFalse;
        	TBool xspid = EFalse;
        	
        	CleanupStack :: PushL(contact);        	        	
        							    		    		    			    	        	
			pContactMap = CLiwDefaultMap::NewL();
			CleanupStack :: PushL(pContactMap);	
			
			cntIdUnicode = HBufC::NewL(cntId->Length());
	    	CleanupStack :: PushL(cntIdUnicode);
	    	cntIdUnicode->Des().Copy(*cntId);
	    	delete cntId;
	    	cntId = NULL;
	    	ContactIDToUTF(cntIdUnicode);			
			pContactMap->InsertL(KContactId,TLiwVariant(*cntIdUnicode));
			CleanupStack :: Pop(cntIdUnicode);						
			
			TLiwVariant val;
 		    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &val) );

			TInt fieldCount = contact->FieldCount();
			for(TInt i=0 ; i< fieldCount ; i++)
				{
			    CLiwMap* pFieldLinkedMap = CLiwDefaultMap::NewL();
				CleanupClosePushL(*pFieldLinkedMap);
				//Get the next field
				field = contact->FieldAt(i);
				
				//Get field data and populate the map structure
				field->GetFieldDataL(fieldName, fieldLabel, fieldValue);
				if(fieldName.Compare(KXspid) == 0)
				    {
				    xspid = ETrue;
				    fieldLabel.Set(KXspidLabel);
				    field->GetUriFieldParamL(xspidArray);
				    if(xspidArray.Count() > 0)
				           {
				           
				           TInt count = xspidArray.Count();
				           TInt i;
				           IdList = CLiwDefaultList::NewL();
				           for(i=0; i<count; i++)
				               {
				               TDesC* idVal = xspidArray[i];
				               outputVal.Set(*idVal);
				               IdList->AppendL(outputVal);
				               }
				           
				           }
				    xspidArray.ResetAndDestroy();
				    
				    }
				if((fieldName.Compare(KDate) == 0) || (fieldName.Compare(KAnniversary) == 0)) // || fieldName.Compare(KBirthDay) == 0)
					{
					date = ETrue;
					fieldTime = field->GetDateTime();
					}
				
				if(EFalse != pContactMap->FindL(fieldName,val))
					{
					//In case there are multiple values for a given Fieldkey, add "Next" key to the map.
					// and create a linked list of label-value pairs for a given key
					pFieldLinkedMap->InsertL(KFieldLabel,TLiwVariant(fieldLabel));
					if(date)
						{
						pFieldLinkedMap->InsertL(KFieldValue,TLiwVariant(fieldTime));				
						}
					else if(xspid)
					    {
					  //  CLiwMap* pFieldLinkedMap = CLiwDefaultMap::NewL();
                       // CleanupClosePushL(*pFieldLinkedMap);
                        pFieldLinkedMap->InsertL(KFieldValue,TLiwVariant(IdList));
						}
					else
						{
						pFieldLinkedMap->InsertL(KFieldValue,TLiwVariant(fieldValue));				
						}
					pFieldLinkedMap->InsertL(KFieldNext,TLiwVariant(val));
					}
				else
					{
					//In case its the first time the FieldKey is being read, just have label-value pair inserted
					pFieldLinkedMap->InsertL(KFieldLabel,TLiwVariant(fieldLabel));
					if(date)
						{
						date = EFalse;
						pFieldLinkedMap->InsertL(KFieldValue,TLiwVariant(fieldTime));				
						}
					else if(xspid)
                        {
                        xspid = EFalse;
                        pFieldLinkedMap->InsertL(KFieldValue,TLiwVariant(IdList));
						}
					else
						{
						pFieldLinkedMap->InsertL(KFieldValue,TLiwVariant(fieldValue));				
						}
					}
				//For the given Fieldkey insert the label-value pair
				pContactMap->InsertL(fieldName, TLiwVariant(pFieldLinkedMap));
		        CleanupStack::PopAndDestroy(pFieldLinkedMap);
				}
			CleanupStack::Pop(&val);
			val.Reset();
			CleanupStack::Pop(pContactMap);												               
			CleanupStack::PopAndDestroy(contact);			
			retVal = ETrue;
			}
		else
    		{
    		delete cntId;    
    		}
		}
	//In case the iterator is iterating over a list of groups
	else if(iContactIter->iIndicator == EGroups)
		{
		CSingleContact* contact;
	    HBufC8* grpID;
	    CSingleContactField* field;
	    HBufC* grpUnicode = NULL;	
		//Get the next group
		iContactIter->NextL(contact, grpID);
		
		if(contact)
			{
			CleanupStack::PushL(contact);			
			
	    	TPtrC groupLabel;
			RPointerArray<TDesC8> array;			
			CleanupClosePushL(array);
			pContactMap = CLiwDefaultMap::NewL();			
			CleanupStack::PushL(pContactMap);
				
		    grpUnicode = HBufC::NewL(grpID->Length());
	    	grpUnicode->Des().Copy(*grpID);
	    	delete grpID;
	    	grpID = NULL;
	    	ContactIDToUTF(grpUnicode);
	    	CleanupStack::PushL(grpUnicode);	
			//Insert the contact id
			pContactMap->InsertL(KGroupId,TLiwVariant(*grpUnicode));
			CleanupStack::Pop(grpUnicode);            
            
			field = contact->FieldAt(0);
			
			//Get the field data of the group
			field->GetFieldDataL(groupLabel, array);
			
			//Insert group label
			pContactMap->InsertL(KGroupLabel,TLiwVariant(groupLabel));
			
			CLiwList* pContentsList = CLiwDefaultList::NewL();
			CleanupClosePushL(*pContentsList); 
			TInt count = array.Count();
			if(count)
			{
			for(TInt i=0; i<count ; i++)
				{
				HBufC* cntidUni = HBufC:: NewL(array[i]->Length());
			    cntidUni->Des().Copy(*array[i]);
			    CleanupStack::PushL(cntidUni);
			    ContactIDToUTF(cntidUni);	
				pContentsList->AppendL(*cntidUni);
				CleanupStack::Pop(cntidUni);								
				}
			//Insert the list of contacts for the given group
			pContactMap->InsertL(KContents,TLiwVariant(pContentsList));
			}
			CleanupStack::PopAndDestroy(pContentsList);
			CleanupStack :: Pop(pContactMap);
			CleanupStack :: PopAndDestroy();				
			CleanupStack :: PopAndDestroy(contact);
		
			retVal = ETrue;
			}
		else
    		{
    		delete grpID;    
    		}
		}
	//In case iterator is iterating over list of databases
	else if(iContactIter->iIndicator == EDatabase)
		{
		TPtrC DbName;
		//Get the next database name
		iContactIter->NextL(DbName);
		if(DbName.Compare(KNullDesC) != 0)
			{
			pContactMap = CLiwDefaultMap::NewL();	
			CleanupStack::PushL(pContactMap);
			//Insert DbName into the map
			pContactMap->InsertL(KDBUri,TLiwVariant(DbName));
			CleanupStack::Pop(pContactMap);
			retVal = ETrue;
			}
		}
	if(pContactMap)
    	{
		CleanupClosePushL(*pContactMap);
    	aEntry.SetL(pContactMap);
    	CleanupStack::PopAndDestroy(pContactMap);
    	}	
	return retVal;
	}
