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
* Description:   This Class provides the core functionality to Media Management
*				 SAPI Interafce
*
*/


//#include <liwserviceifbase.h>
#include <liwcommon.h>
#include <mclfitemlistmodel.h>
#include <mclfcontentlistingengine.h>
#include <contentlistingfactory.h>
#include <mclfsortingstyle.h>


#include "mgservice.h"
#include "mgpostfilter.h"
#include "mgoperationobserver.h"
#include "mgclfoperationobserver.h"
#include "mgconsts.h"


_LIT8( KMgMusic        ,"Music" );
_LIT8( KMgSound        ,"Sound" );
_LIT8( KMgImage        ,"Image" );
_LIT8( KMgVideo        ,"Video" );
_LIT8( KMgStreamingURL ,"StreamingURL" );
//SortingOrder
_LIT8( KMgDescending,   "Descending" );

_LIT(LogFileName , "C:\\Performance_Image.txt") ;
RFile LogFile ;
RFs LogSession ;


// -----------------------------------------------------------------------------
// CMgService::NewLC
// Returns the instance of CMgService class.
// -----------------------------------------------------------------------------
CMgService* CMgService::NewL()
	{
	CMgService* self = new ( ELeave )CMgService();
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}
// -----------------------------------------------------------------------------
// CMgService::~CMgService
// Destructor
// -----------------------------------------------------------------------------

CMgService::~CMgService()
	{
    //release iEngine;
    delete iEngine;

    //release filter class
    //delete iFilter;

    // release sorting style
   // delete iSortingStyle;

	// release clf observer class

   // delete iClfObserver;
    

	}




// -----------------------------------------------------------------------------
// CMgService::GetFiles
// This function extracts all media item that match the given arguments
// -----------------------------------------------------------------------------

void CMgService::GetListL(const TMgServiceRequest& aInParameters,
						  MMgOperationObserver* aServiceObserver)
	{

	//Check if the class is busy or waiting for asynchronous request
	//This has already been verified by SAPI interface class ,still this condition
	//is checked keeping in mind that this class may be called directly by a
	//Series60 application in future
	if( EMgFree == iState )
		{



		if( NULL != aServiceObserver )//Asynchronous request
			{
			// create the instance of CLF list Model for the current request
   	 	    MCLFItemListModel* listModel = iEngine->
   	 	                                   CreateListModelLC( *iClfObserver );


			

		    SendRequestToClfL( aInParameters.iFileType,
		    				   aInParameters.iFilterField,
		    				   aInParameters.iStartVal,
		    				   aInParameters.iEndVal,
		    				   aInParameters.iSortField,
		    				   aInParameters.iOrder,
		    				   listModel );
		    				   
		    CleanupStack::Pop();
		    
		    iTransactionID = aInParameters.iTransactionID;
		    iClfObserver->SetMemberVar( aInParameters.iTransactionID,
		                                aServiceObserver,
										listModel,
										this );
		    

	 
			}
		else
			{
			//Synchronous request handling is currently not supported
			User::Leave( KErrNotSupported );
			}

		}//SAPI State
	else
	    {
        User::Leave( KErrServerBusy ); // busy in previous request
	    }

	}


// -----------------------------------------------------------------------------
// CMgService::Cancel
// Cancel the pending asynchronous request
// -----------------------------------------------------------------------------
TInt CMgService::Cancel( TUint aTransactionID)
	{
		// call cancel of CLF
		// Right now we are not supporting aTransactionID
		// but in future we have to find the iClfObserver
		// coresponding to this Transaction ID and Call cancel
		// on that observer
	if( EMgBusy == iState )
		{
		if( aTransactionID == iTransactionID )
		    {
		    iClfObserver->Cancel( );
		    Clear();
	    	}
	    else
	        {
	            return KErrArgument;
            }	
		   
		}
    
        return KErrNone;
	}

// -----------------------------------------------------------------------------
// CMgService::Clear
//	It will clear the set filter metadata field ,registered callback
//	function and sorting fields
// -----------------------------------------------------------------------------

void CMgService::Clear()
	{
       	iFilter->Clear();
		iState = EMgFree;
		iTransactionID = 0;
	}




// -----------------------------------------------------------------------------
// CMgService::State
// It will return the state of service class.
// return EMgFree if it is free and ready to accept
// the another request else EMgBusy
// -----------------------------------------------------------------------------
const TMgState& CMgService::State() const
	{
    return iState;
	}




// -----------------------------------------------------------------------------
// CMgService::SetSortingField
// It will set the metadata field on which the result
// should be sorted.
// Leave with KErrArgument if aSortField is not valid.
// -----------------------------------------------------------------------------

void CMgService::SetSortingFieldL(const TDesC8& aSortField ,
								  const TDesC8&  aOrder ,
								  const RArray<TInt>& aMediaTypes,
								  MCLFItemListModel* alistModel ,
								  MCLFSortingStyle* aSortingStyle )
	{

	// Default sorting as per file name
	TCLFDefaultFieldId metaDataId = ECLFFieldIdFileName;
    TCLFItemDataType  metaDataType = ECLFItemDataTypeDesC;

    //Check If the aSortField is not NULL Descriptor i.e.
    // sorting metadata is specified

   	if( 0 != aSortField.CompareF( KNullDesC8 ) )
   		{

    	GetMetaDataIdAndType( aSortField,
    						  metaDataId,
    						  metaDataType,
    						  aMediaTypes );

	 	if( ECLFFieldIdNull == metaDataId ) // check the return type
	 	    {
	 	    // The given Sort Field  is not supported by Media Management SAPI
	 		User::Leave( KErrArgument );
	 		}
    	}
   	aSortingStyle->ResetL();
	//iSortingStyle->ResetL();


 	//Set the field on which sorting has to perform
   	aSortingStyle->AddFieldL( metaDataId );
   	//iSortingStyle->AddFieldL( metaDataId );

	// Set the sorting field data type
   	aSortingStyle->SetSortingDataType( metaDataType );
	//iSortingStyle->SetSortingDataType( metaDataType );

	if( 0 == aOrder.CompareF( KMgDescending ) )
		{
		
		aSortingStyle->SetOrdering( ECLFOrderingDescending  );
		//iSortingStyle->SetOrdering( ECLFOrderingDescending  );
		}
	else
		{
		aSortingStyle->SetOrdering( ECLFOrderingAscending   );
		//iSortingStyle->SetOrdering( ECLFOrderingAscending );
		}

	//Items with undefined fields are placed after items with defined fields
	aSortingStyle->SetUndefinedItemPosition( ECLFSortingStyleUndefinedEnd );
	//iSortingStyle->SetUndefinedItemPosition( ECLFSortingStyleUndefinedEnd );

	// set sorting style in CLF.
	alistModel->SetSortingStyle( aSortingStyle );


	}


// -----------------------------------------------------------------------------
// CPostFilter::SetFilterMetaData
// Method to set the filter metadata
// -----------------------------------------------------------------------------
void CMgService::SetFilterMetaDataL( const TDesC8& aFilterField,
									 const TDesC& aStartVal,
									 const TDesC& aEndVal,
									 const RArray<TInt>& aMediaTypes, 
									 MCLFItemListModel* alistModel,
									 CPostFilter* aFilter)
	{
	TCLFDefaultFieldId metaDataId;
    TCLFItemDataType  metaDataType;
    


    //Check If the Filter Meta Data is NULL Descriptor, if so
    // no filtration will be performed
    if( 0 == aFilterField.CompareF( KNullDesC8 ) )
    	{
       	metaDataId = ECLFFieldIdNull;
       	metaDataType = ECLFItemDataTypeDesC;	// Blank Descriptor
       	aFilter->SetFilterMetaData( metaDataId, metaDataType );
        //iFilter->SetFilterMetaData( metaDataId, metaDataType );
   		}
    else
    	{
    	GetMetaDataIdAndType( aFilterField,
    						  metaDataId,
    						  metaDataType,
    						  aMediaTypes);

	 	if( ECLFFieldIdNull == metaDataId )
	 		{
	 		// The given metaData is not supported by Media Management SAPI
	 		User::Leave( KErrNotSupported );
	 		}

	 	aFilter->SetFilterMetaData( metaDataId, metaDataType );
	 	//iFilter->SetFilterMetaData( metaDataId, metaDataType );

       	// set filter value of CLF
	 	aFilter->SetFilterValueL( aStartVal,aEndVal );
	    //iFilter->SetFilterValueL( aStartVal,aEndVal );

		// Set Post Filter in CLF
	    alistModel->SetPostFilter( aFilter );

	 	}

  	}


// -----------------------------------------------------------------------------
// CMgService::ConstuctL
// It will intialize the underlying CLF(Content Listing Framework)
// framework classes and CPostFilter class.
// -----------------------------------------------------------------------------
void CMgService::ConstructL()
	{
	// create the instance of CLF engine and store it in member data.
	iEngine = ContentListingFactory::NewContentListingEngineLC();
    CleanupStack::Pop();


    // create the instance of CPostFilter and store it in member data
//    iFilter = CPostFilter::NewL();

    // Get the sorting style from CLF
//	iSortingStyle = ContentListingFactory::NewSortingStyleLC();
 //	CleanupStack::Pop();

 	//create the instance of clf observer
 //	iClfObserver = CClfOperationObserver::NewL();

	}




// -----------------------------------------------------------------------------
// CMgService::CMgService
// Constructor
// -----------------------------------------------------------------------------
CMgService::CMgService()
          : iState( EMgFree ),
            iEngine( NULL ),
			iTransactionID( 0 )
	{

	}



// -----------------------------------------------------------------------------
// CMgService::SetMediaTypeL
// It will convert the aFiletype string into
// equivalent Mediatype ID and Fill the Media Type Array
// if it is not valid then return KErrNotSupported
// -----------------------------------------------------------------------------
void CMgService::SetMediaTypeL (const TDesC8& aFileType,
								RArray<TInt>& aMediaType)
	{

	if( 0 == aFileType.CompareF( KMgMusic ) )
 		{
 	 	aMediaType.AppendL( ECLFMediaTypeMusic );
 	 	}
	else if( 0 == aFileType.CompareF( KMgSound ) )
 	 	{
 	 	aMediaType.AppendL( ECLFMediaTypeSound );
 	 	}

 	else if( 0 == aFileType.CompareF( KMgImage ) )
 	 	{
 	 	aMediaType.AppendL( ECLFMediaTypeImage );
 	 	}

 	else if( 0 == aFileType.CompareF( KMgVideo ) )
 	 	{
 	 	aMediaType.AppendL( ECLFMediaTypeVideo );
 	 	}

 	else if( 0 == aFileType.CompareF( KMgStreamingURL ) )
 	 	{
 	 	aMediaType.AppendL( ECLFMediaTypeStreamingURL );
 	 	}
 	else
 	 	{
 	 	User::Leave ( KErrNotSupported ); // Media Type Not suuported
 	 	}

   	}





// -----------------------------------------------------------------------------
// CMgService::SendRequestToCLF
// This Function will pass the request to CLF frame work for required media type.
// return KErrArgument if the FilterMetaData is not Supported
// return KErrArgument if the Start Value is not Supported
// return KErrArgument  if the End Value is mot supported
// return KErrNone if sucessful
// -----------------------------------------------------------------------------

void CMgService::SendRequestToClfL( const TDesC8& aFileType,
								    const TDesC8& aFilterField,
                				    const TDesC&  aStartVal,
                				    const TDesC&  aEndVal,
                				    const TDesC8& aSortField,
                				    const TDesC8&  aOrder,
                				    MCLFItemListModel* alistModel ,
                				    CPostFilter* aFilter,
                				    MCLFSortingStyle* aSortingStyle)
    {



	RArray<TInt> mediaTypes;
	CleanupClosePushL( mediaTypes );

	//check if it is a valid file type or not
	SetMediaTypeL( aFileType,mediaTypes );


	//set wanted media type in CLF
	alistModel->SetWantedMediaTypesL( mediaTypes.Array() );


	// Set Filter Meta Data  and Value
    SetFilterMetaDataL( aFilterField,aStartVal,aEndVal,mediaTypes,alistModel,aFilter);
    


    // call set sorting field of CLF
    SetSortingFieldL( aSortField,aOrder,mediaTypes,alistModel, aSortingStyle);
   
 	// set the state = Busy
 	// till this request is complete
 	//which indicates no further request will be taken
 	iState = EMgBusy;

	//asynchronous call to CLF ECLFRefreshAll
 	alistModel->RefreshL();


 	CleanupStack::PopAndDestroy( &mediaTypes );


	}



// -----------------------------------------------------------------------------
// CMgService::GetMetaDataIdAndType
// It will convert the aFilterData string into equivalent Metadata ID and Type
// which is recognized by underlying framework.(i.e CLF)
// -----------------------------------------------------------------------------
void CMgService::GetMetaDataIdAndType(const TDesC8& aMetaData,
									  TCLFDefaultFieldId&  aMetaDataId,
          							  TCLFItemDataType& aMetaDataType,
          							  const RArray<TInt> &aMediaTypes)
	{
    //File name field
    if( 0 == aMetaData.CompareF( KMgFileName ))
    	{
    	aMetaDataType = ECLFItemDataTypeDesC;
    	aMetaDataId = ECLFFieldIdFileName;
    	}



    // File Extension
    else if( 0 == aMetaData.CompareF( KMgFileExtension ))
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
		aMetaDataId = ECLFFieldIdFileExtension;
    	}


    // File path field
    else if( 0 == aMetaData.CompareF( KMgPath ))
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
		aMetaDataId = ECLFFieldIdPath;
    	}


    // File drive field
    else if( 0 == aMetaData.CompareF( KMgDrive ))
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
		aMetaDataId = ECLFFieldIdDrive;
	    }


    // File size field
    else if( 0 == aMetaData.CompareF( KMgFileSize ))
       	{
   		aMetaDataType = ECLFItemDataTypeTInt32;
   		aMetaDataId = ECLFFieldIdFileSize;
       	}



    // File date field
    else if( 0 == aMetaData.CompareF( KMgFileDate ))
    	{
		aMetaDataType = ECLFItemDataTypeTTime;
		aMetaDataId = ECLFFieldIdFileDate;
    	}



    // Mime type field
    else if( 0 == aMetaData.CompareF( KMgMimeType ))
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
		aMetaDataId = ECLFFieldIdMimeType;
    	}


    // Full name and path of the file
    else if( 0 == aMetaData.CompareF( KMgFileNameAndPath ))
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
	   	aMetaDataId = ECLFFieldIdFileNameAndPath;
    	}

    // Music file song name: and also check If the File type is Music File
    else if( ( 0 == aMetaData.CompareF( KMgSongName ) ) &&
    		( ( KErrNotFound != aMediaTypes.Find( ECLFMediaTypeMusic ) )
    		|| ( KErrNotFound != aMediaTypes.Find( ECLFMediaTypeVideo ) ) ) )
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
	    aMetaDataId = ECLFFieldIdSongName;

    	}
   	// Music file artist
    else if( (0 == aMetaData.CompareF( KMgArtist )) &&
    		( ( KErrNotFound != aMediaTypes.Find( ECLFMediaTypeMusic ))
    		||( KErrNotFound != aMediaTypes.Find( ECLFMediaTypeVideo ) ) ) )
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
		aMetaDataId =  ECLFFieldIdArtist;
    	}


    // Music file album
    else if((0 == aMetaData.CompareF( KMgAlbum )) &&
    		( KErrNotFound != aMediaTypes.Find( ECLFMediaTypeMusic ) ) )
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
		aMetaDataId = ECLFFieldIdAlbum;
    	}



    // Music file genre
    else if((0==aMetaData.CompareF( KMgGenre))&&
    	( KErrNotFound != aMediaTypes.Find(ECLFMediaTypeMusic) ) )
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
		aMetaDataId =  ECLFFieldIdGenre;
    	}



    // Music file track number
    else if((0 == aMetaData.CompareF( KMgTrackNumber ))&&
    	( KErrNotFound != aMediaTypes.Find( ECLFMediaTypeMusic ) ) )
    	{
		aMetaDataType = ECLFItemDataTypeTInt32;
		aMetaDataId =  ECLFFieldIdTrackNumber;
    	}



    // Music file composer
   	else if( (0 == aMetaData.CompareF( KMgComposer )) &&
   		( KErrNotFound != aMediaTypes.Find( ECLFMediaTypeMusic ) ) )
    	{
		aMetaDataType = ECLFItemDataTypeDesC;
	    aMetaDataId =  ECLFFieldIdComposer;
    	}

    // Ram link first URL
    else if( (0 == aMetaData.CompareF( KMgLinkFirstURL )) &&
    	 ( KErrNotFound != aMediaTypes.Find( ECLFMediaTypeStreamingURL ) ) )
    	{
	    aMetaDataType = ECLFItemDataTypeDesC;
	    aMetaDataId =  ECLFFieldIdRamLinkFirstURL;
    	}

    else
    	{
		aMetaDataType = ECLFItemDataTypeTInt32;
		aMetaDataId = ECLFFieldIdNull;
     	}


	}

void Callback::MgNotifyL(TUint /*aTransactionID*/, 
                               MCLFItemListModel*  aListModel,
        					   TMgOperationEvent& aOperationEvent,
                               const TInt& aError )
{
    	CActiveScheduler :: Stop() ;
		return ;
}
                               
    TInt E32Main()
	{
	
	//	__UHEAP_MARK;

  	CTrapCleanup* cleanup = CTrapCleanup::New();
  	
  	TRAPD(error, Performance_mgmt());
    __ASSERT_ALWAYS(!error, User::Panic(_L("SAPIcode PANIC"), error));
   	
   	delete cleanup;
	//	__UHEAP_MARKEND;
	return 0;
	
	} //E32main() function ends here
	
	TInt Performance_mgmt()
	{
	
		
		//Create the object of callback
		TTime start ; // TTime class objects for storing time
	    TTime end ;	
	    TTimeIntervalMicroSeconds aTimeTaken ; 
	    TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;
	    TInt retcode = 0;
	    TBool aFlag  = EFalse ;
	    
	    
		TBuf8<50> buf ;
		TRealFormat format ;
		
	    OpenFile() ;
		LogFile.Write(_L8("<SAPI GetFile MediaMgmt Async PERFORMANCE DATA>\n ")) ;
		

	    //for (TInt i=0; i<20 ; i++)	    	
	    //{
	    aFlag = ETrue ;
	    start.HomeTime() ;
	    	     	
		MMgOperationObserver*  aCallBack = new (ELeave) Callback();
		CleanupStack::PushL(aCallBack);
		
		// Start Scheduler
		CActiveScheduler *Scheduler = new CActiveScheduler() ;
  		CActiveScheduler :: Install(Scheduler) ;
		CleanupStack::PushL(Scheduler);
		
		
		CMgService* CoreObj = CMgService ::NewL() ;
       	CleanupStack::PushL(CoreObj);
		
		TMgServiceRequest reqArgument;
		reqArgument.iFileType.Set(_L8("Music") ); 
		reqArgument.iStartVal.Set(_L("0") ); 
		reqArgument.iEndVal.Set(_L("NULL") ); 
		reqArgument.iSortField.Set( _L8("Composer")  ); 
		reqArgument.iOrder.Set( _L8("Descending") ); 

		
		TRAP( retcode , CoreObj->GetListL(reqArgument ,aCallBack) );
		  
		  if(retcode < 0)
	    {


		CleanupStack::PopAndDestroy();//Remove callback
		CleanupStack::PopAndDestroy();//Remove scheduler
		CleanupStack::PopAndDestroy();//Remove core object
	    end.HomeTime();  	    
	    }
	    
	    else
	    { 
	    CActiveScheduler :: Start();
        
	    CleanupStack::PopAndDestroy();//Remove callback
		CleanupStack::PopAndDestroy();//Remove scheduler
		CleanupStack::PopAndDestroy();//Remove core object
		
	    end.HomeTime();  	
	    } 
	    
	    aTimeTaken = end.MicroSecondsFrom(start) ;  
		aTimeDelay = aTimeTaken.Int64() ;
	    aSum = aSum + aTimeDelay ;
	    
	    
		
		if( aFlag )
			{
			buf.Num(aTimeDelay , format) ;
			LogFile.Write(_L8("Time = ")) ;
			LogFile.Write(buf) ;
			LogFile.Write(_L8("\n") ) ;
			}
		else
			{
			LogFile.Write(_L8("Failed..\n ")) ;
			}
		
		
	   // }
	    
	    /*aAvgTime = aSum/20.0 ;
		buf.Num(aAvgTime , format) ;
		LogFile.Write(_L8("\n\nAverage = ")) ;
		LogFile.Write(buf) ;
		LogFile.Write(_L8("\n\n") ) ;*/
		
		CloseFile() ;	
	    return retcode;
	    
		
	}
	
	void OpenFile()
	{
	LogSession.Connect() ;

	LogFile.Replace(LogSession ,LogFileName , EFileWrite );
	TInt End = 0 ;
	LogFile.Seek(ESeekEnd , End) ; 
	}
	
	void CloseFile()
	{
	LogFile.Close() ;
	LogSession.Close() ;
	}

//  End of File
