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
* Description:  This Class provides information of Application installed on phone.
*				 				 
*
*/




#ifndef _APPINFO_H__
#define _APPINFO_H__
#include <e32base.h>
#include <apaid.h> // For TApaAppInfo
#include <badesca.h> // CDesC16Array
#include "appmanagercommon.h"

_LIT8(KCaption,"Caption");
_LIT8(KShortCaption,"ShortCaption");
_LIT8(KUid,"Uid");
_LIT8(KName,"Path");


/**
* This Class provides the information for Application
* on phone
*
* @since  Series60 v3.2

*/

class CAppInfo : public CBase ,public MInfoMap
	{
	public:

    	 /**
        * Returns the instance of CAppInfo.
        * @since  Series60 v3.2
        * @param  aAppInfo Instance of TApaAppInfo class
        * @return CAppInfo* return the instance of CAppInfo class
        */
	
		static CAppInfo*  NewL(TApaAppInfo& aAppInfo);

        /**
    	* Destructor.
    	*/

		~CAppInfo();

     	/**
        * This function finds the value as per key given in argument.
        * @param aKey  Key given to find corresponding value.
        * @param aVal  value as per key.
        * @return TBool ETrue in case of key - value is found else EFalse.
        * @since  Series60 v3.2
        */
         
		virtual TBool  FindL(const TDesC8& aKey, TPtrC& aVal);

     	/**
        * This function gives the key value at a given index
        * @param aIndex TInt index value
        * @return TPtrC Pointer to descriptor containing key .
        * @since  Series60 v3.2
        */
		virtual TBool AtL( TInt aIndex, TDes8& aKeyVal );

     	/**
        * This function gives the number of keys
        * @param void 
        * @return TInt Number of keys
        * @since  Series60 v3.2
        */
		virtual TInt Count() const;
		
	private:

     	/**
        * Constructor
        * @param aAppInfo Instance of  TApaAppInfo class
        * @since  Series60 v3.2
        */
		CAppInfo(TApaAppInfo& aAppInfo);

     	/**
        * Two-phased constructor
        * @param void 
        * @return void
        * @since  Series60 v3.2
        */
		void ConstructL();
	
	private:		
	
        /**
        * TApaAppinfo instance containing information of installed application
        */  
		TApaAppInfo iAppInfo;

        /**
        * Array containing keys 
        */  
		CDesC8Array* iKeyArray;		
		
		RPointerArray<HBufC> iKeyValArray;
		
	};

#endif
