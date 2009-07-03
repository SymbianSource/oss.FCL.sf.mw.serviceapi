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


#ifndef __APPITERATOR_H__
#define __APPITERATOR_H__


#include <e32base.h>
class RApaLsSession ;

#include "appmanagercommon.h"

/**
* This is iterator class which iterates on the applications
* installed on phone
*
* @since  Series60 v3.2

*/
class CAppIterator: public CBase, public MIterator
	{
	public:
		 /**
		* Returns the instance of CAppIterator.
		* @since  Series60 v3.2
		* @param  aApaLsSession Instance of RApaLsSession(App arch server) class
		* @param  aFilterParam  Instance of CFilterParam which is the filter param
		* @return CAppIterator* return the instance of CAppIterator class
		*/

		static CAppIterator* NewL(RApaLsSession& aApaLsSession,const CFilterParam* aFilterParam);
        
        /**
    	* Destructor.
    	*/
		~CAppIterator();
		
		 /**
		* It gives the instance of MInfoMap which contains the information about next application on 
		* iterator list.
		* @since  Series60 v3.2
		* @param  aInfo Instance of MInfoMap
		* @return TBool returns ETrue when get next application or else False when no more applications
		* 				are present on the iterator list
		*/
		virtual TBool  NextL(MInfoMap*& aInfo);

       
		
        /**
    	* It resets the iterator;
    	*/
		virtual void Reset();


		private:


     	/**
        * Constructor
        * @param aApaLsSession Instance of RApaLsSession class
        * @since  Series60 v3.2
        */
		CAppIterator(RApaLsSession& aApaLsSession);

     	/**
        * Two-phased constructor
        * @param aFilterParam  Instance of CFilterParam which is the filter param
        * @return void
        * @since  Series60 v3.2
        */
		void ConstructL(const CFilterParam* aFilterParam);

		private:

        /**
        * Reference to the RApaLsSession instance
        */  
		RApaLsSession&  iApaLsSession;


        /**
        * Uid of the application 
        */  
		TUid iUid;

        /**
        * TBool boolean instance
        */  
		TBool iHandler;	
	

	};



#endif