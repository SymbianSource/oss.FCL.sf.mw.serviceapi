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
* Description:  It contains the declarations of interface classes and filter param class
*				 				 
*
*/



#ifndef __APPMANAGERCOMMON_H__
#define __APPMANAGERCOMMON_H__

#include <e32cmn.h> // TDesC
#include <e32base.h> // CBase
#include <f32file.h> // Rfile
#include <e32des16.h>
#include <e32des8.h>

class CLauncherObserver;
const TInt KArrayGranularity = 5;

_LIT(KForeground ,"Foreground");
_LIT(KStandalone,"Standalone");
/**
* This is an interface class which provides the information about the installed application or package as per 
* content type.
*
* @since  Series60 v3.2
*/

class MInfoMap
	{

	public :

		 /**
		* Finds the value as per key.
		* @since  Series60 v3.2
		* @param  akey  Descriptor defining key to findout.
		* @param  aVal  On return it contains the value as per key 
		* @return TBool If key argument is correct then returns ETrue or else EFalse
		*/
		
		
		virtual TBool FindL(const TDesC8& akey ,TPtrC& aVal)=0;

		 /**
		* Gives the total number of keys.
		* @since  Series60 v3.2
		* @param  void
		* @return TInt Number of keys
		*/
		virtual TInt Count()const =0 ;

		 /**
		* Gives the key present at a given index.
		* @since  Series60 v3.2
		* @param  aIndex   Index value 
		* @param  aKeyVal  Value present at the given index.	
		* @return TBool    Returns ETrue if valid index is given otherwise returns EFalse
		*/
		virtual TBool AtL(TInt aIndex, TDes8& aFndKey)=0;

		 /**
		* Destructor.
		* @since  Series60 v3.2
		*/
		virtual ~MInfoMap();

	};

/**
* This is an interface class which provides the iterator 
*
* @since  Series60 v3.2

*/
class MIterator 
	{
	public: 
	
		/**
		* Destructor.
		* @since  Series60 v3.2
		*/
		virtual ~MIterator();
		
		 /**
		* Gives the next apllication info map, on the iterator list
		* @since  Series60 v3.2
		* @param  aMap     Instance of MInfoMap 
		* @return TBool    Returns ETrue if next application is present in the on the iterator list else 
		*				   returns EFalse.
		*/
		virtual TBool NextL(MInfoMap*& aMap)=0;

	
		
		/**
        * Resets the iterator. 
        *
        */
        virtual void Reset() = 0 ;

	};


/**
* This class is filter parameter for GetList operation  
*
* @since  Series60 v3.2
*/

class CFilterParam : public CBase
	{

	public :

		 /**
		* Returns the instance of CFilterParam.
		* @since  Series60 v3.2
		* @return CFilterParam* return the instance of CFilterParam class
		*/
		IMPORT_C static  CFilterParam* NewL(); 

		 /**
		* Sets the document name.
		* @since  Series60 v3.2
		* @param  aDocName   document name
		* @return void
		*/
		IMPORT_C void SetDocName(const TDesC& aDocName) ;

		 /**
		* Gives the document name
		* @since  Series60 v3.2
		* @param  void
		* @return TPtrC points to the document name.
		*/
		IMPORT_C TPtrC DocName() const ;
		
		 /**
		* Sets the mimetype.
		* @since  Series60 v3.2
		* @param  aMimeType   mimetype
		* @return void
		*/
		IMPORT_C void SetmimeType(const TDesC8& aMimeType) ;


		 /**
		* Gives the mimetype
		* @since  Series60 v3.2
		* @param  void
		* @return TPtrC8 points to the document name.
		*/
		IMPORT_C TPtrC8 MimeType() const;

	private :
		
        /**
    	* Constructor.
    	*/
		CFilterParam();
        /**
    	* Destructor.
    	*/
		~CFilterParam();

	private :

        /**
        * Document name
        */  
		HBufC* iDocumentName;

        /**
        * MimeType
        */  
		HBufC8* iMimeType;

	};

/**
* This Class is used to contain the Document to launch in any form
* 
* @since  Series60 v3.2
*/

class TDocument
{
    public:
        /**
        * Constructor
        * @since  Series60 v3.2
        */
        TDocument():iPath( KNullDesC )
        {

    	}

    public:	

        RFile iHandle;
	   	TPtrC iPath;

};


/**
* This Class is used to contain the options for launching application
* e.g its postion,launching mode, document to send to launcing 
* application 
* 
* @since  Series60 v3.2
*/

class TOptions
{

    public:
        /**
        * Constructor
        * @since  Series60 v3.2
        */
        TOptions():iDocument( KNullDesC),
        		   iMode( KStandalone ),
        		   iPostion( KForeground )
        {

    	}

    public:	

        TPtrC iDocument;
		TPtrC iMode;
		TPtrC iPostion;
};


/**
 * Structure for storing transaction id and associated active object.
*/
class TAsyncRequestInfo
	{
	
	
	 public:
        /**
        * Constructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
        TAsyncRequestInfo():iTransactionId( 0 ),
        		            iAsyncObj( NULL )
        {

    	}

    /**
     * TransactionId
    */
	TInt32 iTransactionId;

    /**
     * Active object pointer
    */
	CLauncherObserver* iAsyncObj;
	};	
	
	
	
enum TAppOperationEvent
    {
    // Operation is completed
    EAppComplete = 0x0,
    
    // Operation is canceled
    EAppCancel = 0x1
    };

#endif