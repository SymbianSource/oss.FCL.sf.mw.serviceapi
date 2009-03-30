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

#include "singlecontact.h"
#include "singlecontactfield.h"

/*
-----------------------------------------------------------------------------
    CSingleContactField  ::NewL()
    Description          : static method which creates the object and constructs it.
    Return values        : CSingleContactField*
-----------------------------------------------------------------------------
*/
EXPORT_C CSingleContactField* CSingleContactField::NewL()
	{
	return new (ELeave) CSingleContactField();
	}

/*
-----------------------------------------------------------------------------
    CSingleContactField  ::CSingleContactField().
    Description          : Default Constructor.
    Return values        : None.
-----------------------------------------------------------------------------
*/
CSingleContactField::CSingleContactField()
	{
	}

/*
-----------------------------------------------------------------------------
    CSingleContactField  ::GetFieldDataL(TPtrC8& aFieldKey,
                                         TPtrC& aLabel,
                                         TPtrC& aValue).
    Description          : Gets the Field Data and returns them as output parameters.
                         : If one of the params is not there then leaves.
    Return values        : None.
-----------------------------------------------------------------------------
*/
EXPORT_C void CSingleContactField::GetFieldDataL(TPtrC8& aFieldKey,
                                                 TPtrC& aLabel,
                                                 TPtrC& aValue)
	{
	if(iFieldKey && iLabel && iValue)
    	{
    	aFieldKey.Set(*iFieldKey);
    	aLabel.Set(*iLabel);
    	aValue.Set(*iValue);    
    	}
    else
        {
        User::Leave(KErrNotFound);    
        }		
	}

/*
-----------------------------------------------------------------------------
    CSingleContactField  ::GetFieldDataL(TPtrC8& aFieldKey,
                                         TPtrC& aLabel,
                                         TPtrC& aValue).
    Description          : Gets the Field Data and returns them as output parameters.
                         : Can leave.
    Return values        : None.
-----------------------------------------------------------------------------
*/
EXPORT_C void CSingleContactField::
              SetFieldParamsL(const TDesC8& aFieldKey,
                              const TDesC& aLabel,
                              const TDesC& aValue)
	{
	if(iFieldKey)
	    {
	    delete iFieldKey;
	    iFieldKey = NULL;
	    }
    if( iLabel )
        {
        delete iLabel;
        iLabel = NULL;
        }
    if( iValue )
        {
        delete iValue;
        iValue = NULL;
        }
	iFieldKey= aFieldKey.AllocL();
	iLabel = aLabel.AllocL();
	iValue = aValue.AllocL();
	}

//Gets the Group Data and returns them as output parameters
/*
-----------------------------------------------------------------------------
    CSingleContactField  ::CSingleContactField::
                           GetFieldDataL(TPtrC& aGroupLabel,
                                         RPointerArray<HBufC8>& aArray)
    Description          : Gets the Field Data and returns them as output parameters.
                         : Can leave.
    Return values        : None.
-----------------------------------------------------------------------------
*/
EXPORT_C void CSingleContactField::
              GetFieldDataL(TPtrC& aGroupLabel,
                            RPointerArray<TDesC8>& aArray)
	{
	aGroupLabel.Set(*iGroupLabel);
	
	TInt count = iContactIdArray.Count();
	
	for(TInt i=0;i<count;i++)
    	{
    	 aArray.AppendL(iContactIdArray[i]);    	 
    	}    		
	}

//Sets the Group Data.
void CSingleContactField::
     SetFieldParamsL(const TPtrC& aGroupLabel,
     RPointerArray<HBufC8>& aArray)
	{
	if( iGroupLabel )
	    {
	    delete iGroupLabel;
	    iGroupLabel = NULL;
	    }
	iGroupLabel = aGroupLabel.AllocL();
	iContactIdArray.ResetAndDestroy();
	iContactIdArray = aArray;
	}

//Private method used to set TTime variable
EXPORT_C void CSingleContactField::SetDateTime(TTime aDateTime)
	{
	iDateAndTime = aDateTime;
	}

//Method to get the TTime variable
EXPORT_C TTime CSingleContactField::GetDateTime()
	{
	return iDateAndTime;
	}

CSingleContactField::~CSingleContactField()
    {
    delete iFieldKey;
    delete iLabel;
    delete iValue;
    delete iGroupLabel;
    iContactIdArray.ResetAndDestroy();
    }
