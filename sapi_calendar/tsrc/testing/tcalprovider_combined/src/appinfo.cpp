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
* Description:   This Class provides information of Application installed on phone.
*
*/



#include "appinfo.h"

// Length of heap descriptor holding keyvalue.

 //(8*8) + (2 * 8) = 64 + 16 = 80 , 10 bytes + 1 = 11 bytes
const TInt KUidLength = 20;

_LIT(KHEXAdd,"0x");
// -----------------------------------------------------------------------------
// CAppInfo::NewL
// Returns the instance of CAppInfo class.
// -----------------------------------------------------------------------------
CAppInfo*  CAppInfo::NewL(TApaAppInfo& aAppInfo)
	{
	CAppInfo* self = new(ELeave) CAppInfo(aAppInfo);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CAppInfo::ConstructL
// Two-phased constructor
// -----------------------------------------------------------------------------
void CAppInfo::ConstructL()
	{
	iKeyArray = new(ELeave)	CDesC8ArraySeg( KArrayGranularity );

	iKeyArray->AppendL(KName);
	iKeyArray->AppendL(KUid);
	iKeyArray->AppendL(KCaption);
	iKeyArray->AppendL(KShortCaption);
    TInt count = iKeyArray->Count();
	for(TInt index = 0 ; index < count ;index++)
		{
		//Intializing the Array
		iKeyValArray.AppendL(NULL);
		}


	}


// -----------------------------------------------------------------------------
// CAppInfo::CAppInfo
// C++ constructor
// -----------------------------------------------------------------------------
CAppInfo::CAppInfo(TApaAppInfo& aAppInfo):iAppInfo(aAppInfo)
	{

	}

// -----------------------------------------------------------------------------
// CAppInfo::~CAppInfo
// destructor
// -----------------------------------------------------------------------------
CAppInfo::~CAppInfo()
	{


	iKeyValArray.ResetAndDestroy();

	if(iKeyArray)
		{

		iKeyArray->Reset();
		delete iKeyArray;

		}

	}

// -----------------------------------------------------------------------------
// CAppInfo::FindL
// This function finds the value as per key given in argument
// -----------------------------------------------------------------------------
 TBool  CAppInfo::FindL(const TDesC8& aKey, TPtrC& aVal)
	{
	TBool flgret = ETrue;
	TInt index = -1;

    //For each key fetching the Value from underlying S60 classes
	if(aKey.CompareF(KName) == KErrNone)
		{

		iKeyArray->Find(KName,index);

		if(index >= 0)
			{
			if( NULL == iKeyValArray[index])
			{
			HBufC* keyval = HBufC::NewL(iAppInfo.iFullName.Length());

			TPtr val(keyval->Des());

			val.Append(iAppInfo.iFullName);



			iKeyValArray.Insert(keyval,index);
			}

		aVal.Set(*iKeyValArray[index]);

			}

		}
	else if(aKey.CompareF(KUid) == KErrNone)
		{

		iKeyArray->Find(KUid,index);

		if(index >= 0)
			{
		if(NULL == iKeyValArray[index])
			{

			HBufC* keyval = HBufC::NewL(KUidLength);

			TPtr val(keyval->Des());
				val.Append(KHEXAdd);
			val.AppendNum(iAppInfo.iUid.iUid,EHex);


			iKeyValArray.Insert(keyval,index);
			}

		aVal.Set(*iKeyValArray[index]);

			}

		}
	else if(aKey.CompareF(KShortCaption) == KErrNone)
		{

		iKeyArray->Find(KShortCaption,index);

		if(index >= 0)
			{
		if(NULL == iKeyValArray[index])
			{

			HBufC* keyval = HBufC::NewL(iAppInfo.iShortCaption.Length());

			TPtr val(keyval->Des());

			val.Append(iAppInfo.iShortCaption);


			iKeyValArray.Insert(keyval,index);
			}

		aVal.Set(*iKeyValArray[index]);

			}

		}
	else if(aKey.CompareF(KCaption) == KErrNone)
		{

		iKeyArray->Find(KCaption,index);

		if(index >= 0)
			{
		if(NULL == iKeyValArray[index])
			{

			HBufC* keyval = HBufC::NewL(iAppInfo.iCaption.Length());

			TPtr val(keyval->Des());

			val.Append(iAppInfo.iCaption);


			iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do
			}

		aVal.Set(*iKeyValArray[index]);

			}
		}
	else
		{
		flgret = EFalse;
		}

	return flgret;
	}


// -----------------------------------------------------------------------------
// CAppInfo::AtL
// This function gives the key value at a given index
// -----------------------------------------------------------------------------
 TBool CAppInfo::AtL(TInt aIndex, TDes8& aKeyVal)
	{
	TBool flgret= EFalse;

	 if(aIndex< iKeyArray->Count())
	    {
	    aKeyVal.Copy((*iKeyArray)[aIndex]);
	    flgret = ETrue;
	    }
	 else
	    {
	    flgret = ETrue;
	    }

	return flgret;
	 
	}

// -----------------------------------------------------------------------------
// CAppInfo::Count
// This function gives the number of keys
// -----------------------------------------------------------------------------
 TInt CAppInfo::Count() const
	{

	return iKeyArray->Length();
	}
