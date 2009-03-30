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

#include "searchfields.h"
#include "singlecontact.h"

//Initialization of the mapping table
MAPPING_TABLE mappingTable[SIZEOFTABLE] =
	{
//		{R_VPBK_SYNCRONIZATION_FIELD_PROPERTY      ,		_L8("Sync")},
		{R_VPBK_FIELD_TYPE_LASTNAME                ,		_L8("LastName")},
//		{R_VPBK_FIELD_TYPE_LASTNAMEREADING         ,		_L8("LastNameReading")},
		{R_VPBK_FIELD_TYPE_FIRSTNAME               ,		_L8("FirstName")},
//		{R_VPBK_FIELD_TYPE_FIRSTNAMEREADING        ,		_L8("FirstNameReading")},
		{R_VPBK_FIELD_TYPE_PREFIX                  ,		_L8("Prefix")},
		{R_VPBK_FIELD_TYPE_SUFFIX                  ,		_L8("Suffix")},
		{R_VPBK_FIELD_TYPE_SECONDNAME              ,		_L8("SecondName")},
		{R_VPBK_FIELD_TYPE_LANDPHONEHOME           ,		_L8("LandPhoneHome")},
		{R_VPBK_FIELD_TYPE_MOBILEPHONEHOME         ,		_L8("MobilePhoneHome")},
		{R_VPBK_FIELD_TYPE_VIDEONUMBERHOME         ,		_L8("VideoNumberHome")},
		{R_VPBK_FIELD_TYPE_FAXNUMBERHOME           ,		_L8("FaxNumberHome")},
		{R_VPBK_FIELD_TYPE_VOIPHOME                ,		_L8("VoipHome")},
		{R_VPBK_FIELD_TYPE_EMAILHOME               ,		_L8("EmailHome")},
		{R_VPBK_FIELD_TYPE_URLHOME                 ,		_L8("URLHome")},
		{R_VPBK_FIELD_TYPE_ADDRLABELHOME           ,		_L8("AddrLabelHome")},
		{R_VPBK_FIELD_TYPE_ADDRPOHOME              ,		_L8("AddrPOHome")},
		{R_VPBK_FIELD_TYPE_ADDREXTHOME             ,		_L8("AddrEXTHome")},
		{R_VPBK_FIELD_TYPE_ADDRSTREETHOME          ,		_L8("AddrStreetHome")},
		{R_VPBK_FIELD_TYPE_ADDRLOCALHOME           ,		_L8("AddrLocalHome")},
		{R_VPBK_FIELD_TYPE_ADDRREGIONHOME          ,		_L8("AddrRegionHome")},
		{R_VPBK_FIELD_TYPE_ADDRPOSTCODEHOME        ,		_L8("AddrPostCodeHome")},
		{R_VPBK_FIELD_TYPE_ADDRCOUNTRYHOME         ,		_L8("AddrCountryHome")},
		{R_VPBK_FIELD_TYPE_JOBTITLE                ,		_L8("JobTitle")},
		{R_VPBK_FIELD_TYPE_COMPANYNAME             ,		_L8("CompanyName")},
		{R_VPBK_FIELD_TYPE_LANDPHONEWORK           ,		_L8("LandPhoneWork")},
		{R_VPBK_FIELD_TYPE_MOBILEPHONEWORK         ,		_L8("MobilePhoneWork")},
		{R_VPBK_FIELD_TYPE_VIDEONUMBERWORK         ,		_L8("VideoNumberWork")},
		{R_VPBK_FIELD_TYPE_FAXNUMBERWORK           ,		_L8("FaxNumberWork")},
		{R_VPBK_FIELD_TYPE_VOIPWORK                ,		_L8("VoipWork")},
		{R_VPBK_FIELD_TYPE_EMAILWORK               ,		_L8("EmailWork")},
		{R_VPBK_FIELD_TYPE_URLWORK                 ,		_L8("URLWork")},
		{R_VPBK_FIELD_TYPE_ADDRLABELWORK           ,		_L8("AddrLabelWork")},
		{R_VPBK_FIELD_TYPE_ADDRPOWORK              ,		_L8("AddrPOWork")},
		{R_VPBK_FIELD_TYPE_ADDREXTWORK             ,		_L8("AddrEXTWork")},
		{R_VPBK_FIELD_TYPE_ADDRSTREETWORK          ,		_L8("AddrStreetWork")},
		{R_VPBK_FIELD_TYPE_ADDRLOCALWORK           ,		_L8("AddrLocalWork")},
		{R_VPBK_FIELD_TYPE_ADDRREGIONWORK          ,		_L8("AddrRegionWork")},
		{R_VPBK_FIELD_TYPE_ADDRPOSTCODEWORK        ,		_L8("AddrPostCodeWork")},
		{R_VPBK_FIELD_TYPE_ADDRCOUNTRYWORK         ,		_L8("AddrCountryWork")},
		{R_VPBK_FIELD_TYPE_LANDPHONEGEN            ,		_L8("LandPhoneGen")},
		{R_VPBK_FIELD_TYPE_MOBILEPHONEGEN          ,		_L8("MobilePhoneGen")},
		{R_VPBK_FIELD_TYPE_VIDEONUMBERGEN          ,		_L8("VideoNumberGen")},
		{R_VPBK_FIELD_TYPE_FAXNUMBERGEN            ,		_L8("FaxNumberGen")},
		{R_VPBK_FIELD_TYPE_VOIPGEN                 ,		_L8("VOIPGen")},
		{R_VPBK_FIELD_TYPE_POC                     ,		_L8("POC")},
		{R_VPBK_FIELD_TYPE_SWIS                    ,		_L8("SWIS")},
		{R_VPBK_FIELD_TYPE_SIP                     ,		_L8("SIP")},
		{R_VPBK_FIELD_TYPE_EMAILGEN                ,		_L8("EmailGen")},
		{R_VPBK_FIELD_TYPE_URLGEN                  ,		_L8("URLGen")},
		{R_VPBK_FIELD_TYPE_ADDRLABELGEN            ,		_L8("AddrLabelGen")},
		{R_VPBK_FIELD_TYPE_ADDRPOGEN               ,		_L8("AddrPOGen")},
		{R_VPBK_FIELD_TYPE_ADDREXTGEN              ,		_L8("AddrExtGen")},
		{R_VPBK_FIELD_TYPE_ADDRSTREETGEN           ,		_L8("AddrStreetGen")},
		{R_VPBK_FIELD_TYPE_ADDRLOCALGEN            ,		_L8("AddrLocalGen")},
		{R_VPBK_FIELD_TYPE_ADDRREGIONGEN           ,		_L8("AddrRegionGen")},
		{R_VPBK_FIELD_TYPE_ADDRPOSTCODEGEN         ,		_L8("AddrPostCodeGen")},
		{R_VPBK_FIELD_TYPE_ADDRCOUNTRYGEN          ,		_L8("AddrCountryGen")},
		{R_VPBK_FIELD_TYPE_PAGERNUMBER             ,		_L8("PageNumber")},
		{R_VPBK_FIELD_TYPE_DTMFSTRING              ,		_L8("DTMFString")},
//		{R_VPBK_FIELD_TYPE_WVADDRESS               ,		_L8("WVAddress")},
		{R_VPBK_FIELD_TYPE_DATE                    ,		_L8("Date")},
		{R_VPBK_FIELD_TYPE_NOTE                    ,		_L8("Note")},
//		{R_VPBK_FIELD_TYPE_THUMBNAILPIC            ,		_L8("ThumbNailPic")},
		{R_VPBK_FIELD_TYPE_RINGTONE                ,		_L8("Ringtone")},
//		{R_VPBK_FIELD_TYPE_CALLEROBJIMG            ,		_L8("CallerObjImg")},
//		{R_VPBK_FIELD_TYPE_CALLEROBJTEXT           ,		_L8("CallerObjText")},
		{R_VPBK_FIELD_TYPE_MIDDLENAME              ,		_L8("MiddleName")},
		{R_VPBK_FIELD_TYPE_DEPARTMENT              ,		_L8("Department")},
		{R_VPBK_FIELD_TYPE_ASSTNAME                ,		_L8("AsstName")},
		{R_VPBK_FIELD_TYPE_SPOUSE                  ,		_L8("Spouse")},
		{R_VPBK_FIELD_TYPE_CHILDREN                ,		_L8("Children")},
		{R_VPBK_FIELD_TYPE_ASSTPHONE               ,		_L8("AsstPhone")},
		{R_VPBK_FIELD_TYPE_CARPHONE                ,		_L8("CarPhone")},
		{R_VPBK_FIELD_TYPE_ANNIVERSARY             ,		_L8("Anniversary")},
		{R_VPBK_FIELD_TYPE_SYNCCLASS               ,		_L8("SyncClass")},
		{R_VPBK_FIELD_TYPE_LOCPRIVACY              ,		_L8("LOCPrivacy")},
//		{R_VPBK_FIELD_TYPE_GENLABEL   			   ,		_L8("GenLabel")},
	};

//Gets the size of the mappingTable
TInt CSearchFields::GetSizeofTable()
	{
	return (sizeof(mappingTable)/sizeof(MAPPING_TABLE));
	}


//Gets the FieldId based on the index
TInt CSearchFields::GetIdfromIndex(TInt index)
	{
	return mappingTable[index].iFieldId;
	}


//Takes Field value as the input and returns the corresponding contact model UID.
EXPORT_C TInt CSearchFields::GetIdFromFieldKey( TDesC8& aFieldValue )
	{
		if( !aFieldValue.Size() )
		{
			return KInvalidFieldID;
		}
		//calculate the no of entries in the mapping table
		TInt noOfEntries = GetSizeofTable();

		for(TInt index = 0; index < noOfEntries; index++)
		{
			if( !aFieldValue.Compare(mappingTable[index].iFieldValue) )
			{
				return GetIdfromIndex(index);
			}
		}

		return KInvalidFieldID;
	}


//Takes contact model field id as the input and returns the corresponding
//mapped field value
EXPORT_C TPtrC8 CSearchFields::GetFieldKeyFromId( TInt aFieldId )
	{
	//calculate the no of entries in the mapping table
	TInt noOfEntries = GetSizeofTable();
	TInt index;
	for(index = 0; index < noOfEntries; index++)
	    {
		if( aFieldId == mappingTable[index].iFieldId )
		    {
			return mappingTable[index].iFieldValue;
		    }
	    }
	return TPtrC8(KNullDesC8);
	}


//NewL method for CSearchFields class
EXPORT_C CSearchFields* CSearchFields::NewL(CContactService* aContactService)
	{
	CSearchFields* self=new (ELeave) CSearchFields();
	CleanupStack::PushL(self);
	self->ConstructL(aContactService);
	CleanupStack::Pop(self);
	return self;
	}	

//NewL overloaded
CSearchFields* CSearchFields::NewL()
	{
	return new (ELeave) CSearchFields();
	}

//ConstructL()
void CSearchFields::ConstructL(CContactService* aContactService)
	{
	iContactService = aContactService;
	iFieldList = CVPbkFieldTypeRefsList::NewL();
	}


//Exported function, used to Append the fields the user is interested in.
EXPORT_C void CSearchFields::AppendL(TDesC8& aFieldName)
	{
	TInt fieldId = GetIdFromFieldKey(aFieldName);
	if(fieldId != KInvalidFieldID)
		{
		iFieldList->AppendL(*(iContactService->GetFieldTypes()).Find(fieldId));
		}
	else
		{
	    User::Leave(KErrArgument);
		}
	}

//Destructor
CSearchFields::~CSearchFields()
	{
	delete iFieldList;
	}

//Returned the RefList of Fields constructed.
CVPbkFieldTypeRefsList* CSearchFields::GetFieldListL()
	{
	if(iFieldList->FieldTypeCount() == 0)
		{
		iFieldList->AppendL(*(iContactService->GetFieldTypes()).Find(R_VPBK_FIELD_TYPE_LASTNAME));
		iFieldList->AppendL(*(iContactService->GetFieldTypes()).Find(R_VPBK_FIELD_TYPE_FIRSTNAME));
		}
	return iFieldList;
	}

