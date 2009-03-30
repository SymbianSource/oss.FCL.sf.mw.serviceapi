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
* Description:  This Class provides information of all packages installed on 
*                the phone by user.
*				 				 
*
*/


#ifndef __INSTALLPKGITR_H__
#define __INSTALLPKGITR_H__



#include <e32base.h>
#include <swi/sisregistrysession.h>
#include <javaregistry.h> 
#include "appmanagercommon.h"

/**
* This Class is an iterator to the list of installed packages
*
* @since  Series60 v3.2
*/
class CInstallPkgIterator: public CBase , public MIterator
	{

	public:

    	 /**
        * Returns the instance of CInstallPkgIterator.
        * @since  Series60 v3.2
        * @param  void
        * @return CInstallPkgIterator* return the instance of CInstallPkgIterator class
        */
		 static CInstallPkgIterator* NewL();
		 
		/**
    	* Destructor.
    	*/
		~CInstallPkgIterator();

		 /**
		* It gives the instance of MInfoMap which contains the information about the next package 
		* on iterator list.
		* @since  Series60 v3.2
		* @param  aInfo Instance of MInfoMap
		* @return TBool returns ETrue when get next application or else False when no more applications
		* 				are present on the iterator list
		*/
		virtual TBool NextL(MInfoMap*& aInfo);

       
        /**
    	* It resets the iterator;
    	*/
		virtual void Reset();


	private:		

     	/**
        * Constructor
        * @since  Series60 v3.2
        */
		CInstallPkgIterator();

     	/**
        * Two-phased constructor
        * @return void
        * @since  Series60 v3.2
        */
		void ConstructL();

	private:

        /**
        * Instance of Swi::RSisRegistrySession
        */  
		Swi::RSisRegistrySession  iSisRegSession;			

        /**
        * Pointer to Java::CJavaRegistry instance
        */  
		Java::CJavaRegistry* iJavaReg;

        /**
        * Array of uids of installed native packages(sisx)
        */  
		RArray<TUid>  iSisxUids;

        /**
        * Array of uids of installed non-native packages(.jar)
        */  
		RArray<TUid>  iJavaUids;

        /**
        * Gives the current value of index in arrays
        */  
		TInt iCurrent;
	};


#endif __INSTALLPKGITR_H__