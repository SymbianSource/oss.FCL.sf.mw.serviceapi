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
* Description:  This Class provides the core functionality to
*				 Media Management SAPI Interafce
*
*/



#ifndef __CMGSERVICE_H
#define __CMGSERVICE_H
#include <e32base.h>
#include <CLFContentListing.hrh>

#include "mgservice.hrh"

class CAsynchRequestManager;
class CPostFilter;
class MCLFSortingStyle;
class MMgOperationObserver;
class CLiwGenericParamList;
class MCLFContentListingEngine;
class MCLFItemListModel;
class CClfOperationObserver;
class MThumbnailObserver;
class CThumbnailGeneration;

_LIT8( KMgAscending,   "Ascending" );
const TInt KNegDefaultVal = -1;
/**
* This Class is used to contain all the request
* parameters of the client
* 
* @since  Series60 v3.2
*/
class TMgServiceRequest
{

    public:
        /**
        * Constructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
        TMgServiceRequest():iFileType( KNullDesC8 ),
                            iFilterField( KNullDesC8 ),
        					iStartVal( KNullDesC ),
        					iEndVal( KNullDesC ),
        					iSortField( KNullDesC8 ),
        					iOrder( KMgAscending ),
        					iTransactionID( 0 )
    	{

    	}

    public:	

        TPtrC8 iFileType;
	    TPtrC8 iFilterField;
		TPtrC  iStartVal;
		TPtrC  iEndVal;
		TPtrC8 iSortField;
    	TPtrC8 iOrder;
    	TUint  iTransactionID;


};

// CLASS DECLARATION

/**
* This Class provides the core functionality of
* Media Management SAPI
* 
* @since  Series60 v3.2
*/
class CMgService : public CBase
    {

    public:

    	 /**
        * Returns the instance of CMgService.
        * @since  Series60 v3.2
        * @param  void
        * @return CMgService* return the instance of CMgService class
        */
         IMPORT_C static CMgService* NewL();

        /**
    	* Destructor.
    	*/
        virtual ~CMgService();


         /**
        * This function extract all media item matches with the given arguments
        * Leave with System wide error code if the operation did not
        * succeed.
        * @since  Series60 v3.2
        * @param aFileType 	It specifies the required media type
        * @param aFilterField It specifies the Filter criteria
        * @param aStartVal 	It specifies the start value for filter criteria
        * @param aEndVal   	It specifies the end value for filter criteria
        * @param aSortField	It specifies the field for sorting the result
        * @param aOrder		It specifies the sorting order Ascending/Descending
        * @param aServiceObserver It specifies Callback for Asynchronous request
        */
       	IMPORT_C void GetListL( const TMgServiceRequest& aInParameters,
							    MMgOperationObserver* aServiceObserver );


       	
         /**
        * Cancel the pending asynchronous request
        * @since  Series60 v3.2
        * @param aTransactionID  Transaction Id
        * @return TInt
        */
        IMPORT_C TInt CancelL( TUint aTransactionID );

         /**
        * It will clear the  filter metadata field ,registered callback
        * and sorting fields
        * @since  Series60 v3.2
        * @param  void
        * @return void
        */
        void Clear();


   		/**
        * It will return the state of service class
        * @since  Series60 v3.2
        * @param  void
        * @return State(EMgFree/EMgBusy) which indicates the availability of class
        *		  for another request
        */
   		 IMPORT_C const TMgState& State() const;
   		 
    	/**
        * This function generates thumbnail for image/video files 
        * Leave with System wide error code if the operation did not
        * succeed.
        * @since 
        * @param aObs       It specifies callback for Asynchronous request
        * @param aUrl       It specifies the URI of media file
        * @param aTransactionID  It is transactionId for Asynchronous request 
        * @param aHeight    It specifies the required height for thumbnail 
        * @param aWidth     It specifies the required width  for thumbnail
        */
       	IMPORT_C void GetThumbnailL(MThumbnailObserver* aThumbnailObserver, TDesC& aUrl, TInt32 aTransactionID,
       	        TInt aHeight = KNegDefaultVal, TInt aWidth = KNegDefaultVal);

   	private:

   		/**
        * It will set the metadata field on which the result
        * should be sorted
        * Leave with KErrNotSupported if aSortField is not valid.
        * @since Series60 v3.2
        * @param aSortField metadata field for sort the result
       	* @param aOrder specify the order of sorting Ascending(0)/Descending(1)
       	* @param aMediaTypes specify the media type for which this sorting
       	*					 should performed
        */
 	    void SetSortingFieldL(  const TDesC8& aSortField ,
 	    					    const TDesC8&  aOrder ,
        					    const RArray<TInt>& aMediaTypes,
        					    MCLFItemListModel* alistModel,
        					    MCLFSortingStyle* aSortingStyle );

        /**
        * It will set the metadata field and values on which the result
        * should be filtered.
        * Leave with KErrNotSupported/KErrArgument
        * if aSortField or aStartVal/aEndVal is not valid  .
        * @since  Series60 v3.2
        * @param aFilterField filter criteria
        * @param aStartVal Start value of the filter criteria
        * @param aEndVal	End Value of the filter criteria
        * @param aMediaTypes specify the media type for which this
       	*		 filtering should be performed
       	* @param aFilter It is instance of filter	 
        */
        void SetFilterMetaDataL( const TDesC8& aFilterField,
        					     const TDesC& aStartVal,
        					     const TDesC& aEndVal,
        					     const RArray<TInt>& aMediaTypes,
        					     MCLFItemListModel* alistModel,
        					     CPostFilter* aFilter);

        /**
        * Two-phased constructor
        * @since  Series60 v3.2
        * @param  void
        * @return void
        */
        void ConstructL();

   		/**
        * Constructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
        CMgService();

         /**
        * It will convert the aFiletype string into equivalent mediatype ID
        * which is recognized by underlying framework.(i.e CLF)
        * Leave with KErrNotSupported If that media type is not supported.
        * @since  Series60 v3.2
        * @param aFileType Required filetype(e.g image/music) in string format
        * @param aMediaType contains the ID of given file type
        *
        */
        static void SetMediaTypeL (const TDesC8& aFileType,
        					RArray<TInt>& aMediaType);

        /**
        * This function will pass the request to CLF for
        * required media type
        * @since  Series60 v3.2
        * @param aFileType 	It specifies the required media type
        * @param aFilterField It specifies the Filter criteria
        * @param aStartVal 	It specifies the start value for filter criteria
        * @param aEndVal   	It specifies the end value for filter criteria
        * @param aSortField	It specifies the field for sorting the result
        * @param aOrder		It specifies the sorting order Ascending/Descending
        * @param aListModel It stores the instance of Listmodel object
        * @param aFilter    It stores the instance of filter param 
        * @param aSortingStyle It stores the instance of MCLSortingStyle
        * @return 			System wide error code if the operation did not
        *         			succeed.
        */
        void SendRequestToClfL( const TDesC8& aFileType,
        					   const TDesC8& aFilterField,
        					   const TDesC& aStartVal,
        					   const TDesC& aEndVal,
        					   const TDesC8& aSortField,
        					   const TDesC8& aOrder,
        					   MCLFItemListModel* aListModel,
        					   CPostFilter* aFilter,
        					   MCLFSortingStyle* aSortingStyle );

         /**
        * This function will check whether metadata is supported for
        * requested mediafiles or not,If it is supported 
        * then convert it into equivalent metadata ID
        * @since  Series60 v3.2
        * @param aFilterData Input filter data in string format
        * @param aFilterMetaData Equivalent metadata Id filled by the function
        * @param aFilterDataType Datatype of the given aFilterData
        * @return void
        */
        static void GetMetaDataIdAndType( const TDesC8& aFilterData,
        						   TCLFDefaultFieldId& aFilterMetaData,
        						   TCLFItemDataType& aFilterDataType ,
        						   const RArray<TInt> &aMediaTypes );

      /**
       * Cancel the pending asynchronous request for Thumbnail Generation
       * @since  Series60 v3.2
       * @param  aTransactionID  Transaction Id
        * @return TInt
       */
       TInt CancelThumbnailReq( TUint aTransactionID );
        


    private:

    	/**
     	* indicates whether service class is busy or free to accept another request.
     	*/
    	TMgState iState;

       	/**
     	* stores the instance of the engine of CLF Framework
     	*/
    	MCLFContentListingEngine* iEngine;


    	/**
     	* store the instance of CPostfilter which filters the result
     	* as per the set filter criteria
     	*/
    	//CPostFilter* iFilter;

    	/**
     	* store the instance of sorting style which sorts the result
     	* as per the set sort criteria
     	*/
       	//MCLFSortingStyle* iSortingStyle;

       	/**
     	* store the instance of class which observes CLF event
     	*/
       	//CClfOperationObserver* iClfObserver;
       	
       	/**
     	* stores the Cuurent TransactionID
     	*/
    	TUint  iTransactionID;

        /**
        * stores the instance of TumbnailGeneration
        */    	
    	CThumbnailGeneration* iTumbnailGeneration; 
    	
    	/**
    	 * stores the instance of AsyncRequestManager 
    	 */
    	CAsynchRequestManager* iAsyncRequestManager;
    	
    	
    	
      };

#endif __CMGSERVICE_H