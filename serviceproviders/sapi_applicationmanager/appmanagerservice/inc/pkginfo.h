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
* Description:  This Class provides information of particular package installed on phone.
*				 				 
*
*/


#ifndef _PKGINFO_H__
#define _PKGINFO_H__

//Loesh : Moves these .h files from here
//why some .h files coming in cpas

#include <swi/sisregistrysession.h>
#include <swi/sisregistryentry.h>
#include<javaregistry.h> 
#include<javaregistryentry.h>
#include<javaregistrypackageentry.h>

#include <AppVersion.h> 
#include <BADESCA.H> // CDesC16Array

#include "appManagercommon.h"



_LIT8(KPkgName,"PackageName");
_LIT8(KUid,"Uid");
_LIT8(KVersion,"Version");
_LIT8(KVendor,"Vendor");
_LIT8(KDrive,"Drive");
_LIT( KDriveC, "C");
_LIT( KDrivec, "c");
_LIT( KDriveZ, "Z");
_LIT( KDrivez, "z");


/**
* This Class provides the information of the User installed package
*
* @since  Series60 v3.2

*/
class CPkgInfo : public CBase , public MInfoMap
{

	public:

    	 /**
        * Returns the instance of CPkgInfo.
        * @since  Series60 v3.2
        * @param  aSisRegSession Pointer to the instance of Swi::RSisRegistrySession session
        * @return CPkgInfo* return the instance of CPkgInfo class
        */
        
        
		static CPkgInfo* NewL( Swi::RSisRegistrySession* aSisRegSession);

    	 /**
        * Returns the instance of CPkgInfo.
        * @since  Series60 v3.2
        * @param  aJavaReg Pointer to the instance of Java::CJavaRegistry session
        * @return CPkgInfo* return the instance of CPkgInfo class
        */
        

		static CPkgInfo* NewL(Java::CJavaRegistry* aJavaReg);

        /**
    	* Destructor.
    	*/
		~CPkgInfo();

     	/**
        * This function finds the value as per key given in argument.
        * @param aKey  Key given to find corresponding value.
        * @param aVal  value as per key.
        * @return TBool ETrue in case of key - value is found else EFalse.
        * @since  Series60 v3.2
        */
        
         
		virtual TBool  FindL(const TDesC8& aKey, TPtrC& aVal );

     	/**
        * This function gives the key value at a given index
        * @param aIndex TInt index value
        * @param aKeyVal Pointer to descriptor containing key .
        * @return TBool ETrue in case of key is found else EFalse.
        * @since  Series60 v3.2
        */
		virtual TBool AtL( TInt aIndex, TDes8& aKeyVal );

     	/**
        * This function gives the number of keys
        * @param void 
        * @return TInt Number of keys
        * @since  Series60 v3.2
        */
		virtual TInt Count()const;

     	/**
        * This function sets the appropriate entry as per uid 
        * @param aUid   TUid  
        * @param aErrflg TBool ETrue if appropriate entry is found else false
        * @return void
        * @since  Series60 v3.2
        */
		void SetEntryL( TUid aUid, TBool& aErrflg );


		
	private: 

     	/**
        * Constructor
        * @param aSisRegSession   Instance  of  Swi::RSisRegistrySession class
        * @since  Series60 v3.2
        */
		CPkgInfo( Swi::RSisRegistrySession* aSisRegSession);

     	/**
        * Constructor
        * @param aJavaReg   Instance  of  Java::CJavaRegistry class
        * @since  Series60 v3.2
        */
		CPkgInfo(Java::CJavaRegistry* aJavaReg);

     	/**
        * Two-phased constructor
        * @return void
        * @since  Series60 v3.2
        */
		void ConstructL();
		
     	/**
        * Gives the value as per key input for java installed packages
		* @param  aKey Key 
		* @param  aVal Value as per key input
        * @return TBool
        * @since  Series60 v3.2
        */
		TBool GetJavaInfoL(const TDesC8& aKey, TPtrC& aVal);

     	/**
        * Gives the value as per key input for Series60(Sisx) installed packages
		* @param  aKey Key 
		* @param  aVal Value as per key input
        * @return TBool
        * @since  Series60 v3.2
        */
		TBool GetSisxInfoL(const TDesC8& aKey, TPtrC& aVal);
	
	private:		

     	/**
        * Uid of the package
        */
		TUid iUid;
     	/**
        * Instance of Swi::RSisRegistrySession class
        */
		Swi::RSisRegistrySession* iSisRegSession;
     	/**
        * Instance of Swi::RSisRegistryEntry class
        */
		Swi::RSisRegistryEntry iSisRegEntry;

     	/**
        * Instance of Java::CJavaRegistry class
        */
		Java::CJavaRegistry* iJavaReg;
		
     	/**
        * Instance of Java::CJavaRegistryEntry class
        */
		Java::CJavaRegistryEntry* iJavaRegEntry;

     	/**
        * Pointer to the array containing keys
        */
		CDesC8Array* iKeyArray;
		
		RPointerArray<HBufC> iKeyValArray;

};


#endif