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
* Description:  This Class provides the interface for
*				 calling the functionality to Media Management SAPI.
*  Interafce
*
*/



#include <liwcommon.h>
#include <utf.h>

#include "mginterface.h"
#include "mgservice.h"
#include "mgserviceobserver.h"
#include "serviceerrno.h"

//using namespace LIW;

//Supported Operation
_LIT8(KGetList,"GetList");
_LIT8(KCmdCancel,"Cancel");

//Input Keys/arguments

// Data source name
_LIT8(KDsName,"Type");

// Filter Map
_LIT8(KFilter,"Filter");

// Sorting Map
_LIT8(KSort,"Sort");

//Required file type
_LIT8(KFileType,"FileType");

//Filter criteria
_LIT8(KKey,"Key");

//Start range of filter
_LIT8(KStartRange,"StartRange");

//End range of filter
_LIT8(KEndRange,"EndRange");


//Sorting order
_LIT8(KOrder,"Order");


//Possible DataSource or supported operation
_LIT(KFile,"FileInfo");
_LIT(KFileInfo,"FileInfo");


//Output Keys/arguments
_LIT8(KErrorCode,"ErrorCode");
_LIT8(KErrorMessage,"ErrorMessage");
_LIT8(KTransactionID,"TransactionID");
_LIT(KCmdInvalid, 	 "Command Not Supported");
_LIT(KMissing,		 " is missing");
_LIT(KMissingOrInvalid,		 " is missing/invalid");
_LIT(KInvalid,		 " is invalid");
_LIT(KNotSupported,	 " not supported");
_LIT(KInvalidAsyncParam,"Insufficient arguments for async request");
_LIT(KInvalidCancelParam,"Cancel bit not set in aCmdOptions");
_LIT(KServerBusy,	"Server busy");
//_LIT(KTypeMismatch, " Type mismatch");


// Constants for Error Message
_LIT(KErrorMsgSeparator, 	" : ");
_LIT(KDomainName, 			"MediaMgmt");


// -----------------------------------------------------------------------------
// CMgInterface::NewLC
// Returns the instance of CMgInterface.
// -----------------------------------------------------------------------------
CMgInterface* CMgInterface::NewL()
	{

	CMgInterface* self = new ( ELeave )CMgInterface();
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}


// -----------------------------------------------------------------------------
// CMgInterface::~CMgInterface
// Destructor of class
// -----------------------------------------------------------------------------
CMgInterface::~CMgInterface()
	{

    //Release the instance of service observer class
    delete iServiceObserver;
    iServiceObserver = NULL;

	//Release the instance of core class
    delete iCoreClass;
	iCoreClass = NULL;

	}


// -----------------------------------------------------------------------------
// CMgService::ExecuteCmdL
// Request handler method of interface class
// -----------------------------------------------------------------------------

void CMgInterface::ExecuteCmdL(const TDesC8& aCmdName,
                           const CLiwGenericParamList& aInParamList,
                           CLiwGenericParamList& aOutParamList,
                           TUint aCmdOptions ,
                           MLiwNotifyCallback* aCallBack)
	{

    TInt32 transactionID = 0;
	TInt errCode = 0;
	TInt pos = 0;
	TPtrC dsName(KNullDesC);
    const TLiwGenericParam* param = NULL;
    TLiwGenericParam posbasedparam;
    TBool postionbasedsearching = EFalse;
    
    if( 0 == aCmdName.CompareF( KCmdCancel ) )
	    {
	    if( aCmdOptions & KLiwOptCancel ) // for cancel asynchronous request
			{

			param = aInParamList.FindFirst( pos, KTransactionID );
			if( ( !param ) && ( aInParamList.Count() > 0) )
			    {
			    pos = 0;
			    aInParamList.AtL( pos, posbasedparam );
			    if ( posbasedparam.Name().Compare(KNullDesC8) != 0 || posbasedparam.Value().IsEmpty() )
			        {
			        param = NULL;
			        }
			    else
			        {
			        param = &posbasedparam;
			        }
			    }
			if( param )
			    {
			    
			    if ((*param).Value().Get( transactionID ))
			    
			        {
				    errCode = iCoreClass->CancelL( transactionID );   
				   
					if ( KErrNone != errCode )
				        {
				        TInt sapiErr = SapiError(errCode);
				        AppendErrorMessageL( aCmdName, KTransactionID, KInvalid );
				        aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant( iErrorMessage ) ) );
				        aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)sapiErr)));
			        	}
				    }
				else
				    {
				    AppendErrorMessageL( aCmdName, KTransactionID, KInvalid );
				    aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant( iErrorMessage ) ) );
				    aOutParamList.AppendL( TLiwGenericParam ( KErrorCode,TLiwVariant( TInt32( SErrBadArgumentType ) ) ) );
				    }   

			    }
			else
			    {
			    AppendErrorMessageL( aCmdName, KTransactionID, KMissing );
			    aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant( iErrorMessage ) ) );
			    aOutParamList.AppendL( TLiwGenericParam ( KErrorCode,TLiwVariant( TInt32( SErrMissingArgument ) ) ) );
			    }

			}
		else
			{
			AppendErrorMessageL( aCmdName, KNullDesC8, KInvalidCancelParam );			        
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant( iErrorMessage ) ) );
			aOutParamList.AppendL( TLiwGenericParam ( KErrorCode,TLiwVariant( TInt32( SErrBadArgumentType ) ) ) );	
			}
	    return;	
	    }

	// Check the command name;Cmd name should be GetList
	else if( 0 == aCmdName.CompareF( KGetList ) )
		{
		pos = 0 ;
		param = aInParamList.FindFirst( pos, KDsName );
	    if( ( !param ) && ( aInParamList.Count() > 0 ) )
            {
            pos = 0;
            aInParamList.AtL( pos,posbasedparam );
            if ( (posbasedparam.Name().CompareF(KNullDesC8) != 0 ) || posbasedparam.Value().IsEmpty() ) 
                {
                param = NULL;
                }
            else
                {
                param = &posbasedparam;
                postionbasedsearching = ETrue;
                }
            }
		if(param)
			{
	    	if ((*param).Value().Get( dsName ))
	    	
	    	    {
	    	    //dsName.Set((*param).Value().AsDes());

			    if( ( 0 == dsName.CompareF( KFileInfo )  )
				    || ( 0 == dsName.CompareF( KFile ) )  )
				    {
				// check if core class ready to accept request
			    	if( EMgFree == iCoreClass->State() )
					    {
					    if( aCmdOptions & KLiwOptASyncronous ) //Asynchronous request
						    {
						    if( NULL != aCallBack ) // Asynchronous call
								{
								transactionID = aCallBack->GetTransactionID();
								if( 0 == dsName.CompareF( KFileInfo ) )
									{
								    iServiceObserver->SetMemberVar( EMgGetFilesInfo,
									NULL,aCallBack );
									}
								else
									{
								    iServiceObserver->SetMemberVar( EMgGetFiles,
									NULL,aCallBack );
									}

							   	 //Sending request to core class
							     TRAP (errCode,SendRequestL( aInParamList , transactionID ,postionbasedsearching ));

						        }
							else		//Callback  missing
								{
								AppendErrorMessageL( aCmdName, KNullDesC8, KInvalidAsyncParam );
								errCode = KErrNotFound;
								}

							}
						else //synchronous request
							{
						    //synch request currently not supported
						    AppendErrorMessageL( aCmdName, KNullDesC8, KInvalidAsyncParam );
						    errCode = KErrNotFound;
							}//synchronous request

						}//Sapi status
				    else
				        {
				        AppendErrorMessageL( aCmdName, KNullDesC8, KServerBusy );
				        errCode = KErrServerBusy;
				        }

					}//Data Source support
				else
				    {
				    //Incorrect Data source
				    AppendErrorMessageL( aCmdName, KDsName, KNotSupported );
				    errCode = KErrNotSupported;
				    }

	    	    
		    	}//DataType Mismatch
	    	else
	    	    {
	    	    AppendErrorMessageL( aCmdName, KDsName, KInvalid );
			    errCode = KErrArgument;   
	    	    }
		

		    }//datasource missing
		else
		    {
		    AppendErrorMessageL( aCmdName, KDsName, KMissing );
		    errCode = KErrNotFound;
		    }


		}//GetList
	else
	    {
	    AppendErrorMessageL( aCmdName, KNullDesC8, KCmdInvalid );
	    errCode = KErrNotSupported; //command not supported
	    }

	// check error code if any error occurs then insert into output list
    posbasedparam.Reset();
    TInt sapiErr = SErrNone;
    if (errCode)
    	{
    	sapiErr = SapiError(errCode);
    	}
    		
    aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)sapiErr)));
	if ( iErrorMessage )
		{
		aOutParamList.AppendL(TLiwGenericParam( KErrorMessage, 
									TLiwVariant(iErrorMessage->Des())));
		delete iErrorMessage;
		iErrorMessage = NULL;		
		}

	aOutParamList.AppendL( TLiwGenericParam( KTransactionID, TLiwVariant( (TInt32)transactionID ) ) );

	}


// -----------------------------------------------------------------------------
// CMgInterface::CMgInterface
// Constructor  of class
// -----------------------------------------------------------------------------

CMgInterface::CMgInterface()
             :iCoreClass( NULL ),
			  iServiceObserver( NULL )
	{
	;
	}


// -----------------------------------------------------------------------------
// CMgInterface::ConstructL
// Two-phased constructor of class
// -----------------------------------------------------------------------------

void CMgInterface::ConstructL()
	{
	// Create the instance of core class
	iCoreClass = CMgService::NewL();

	//Create the instance of service observer class
	iServiceObserver = CMgServiceObserver::NewL();

	}



// -----------------------------------------------------------------------------
// CMgInterface::SendRequestL
// This function will send the request to Core class
// -----------------------------------------------------------------------------

void CMgInterface::SendRequestL(const CLiwGenericParamList& aInParamList , TUint aTransactionID , TBool aPostionBasedSearching )

	{
	TInt   pos=0;
	const CLiwMap* filter;
    const CLiwMap* sorting;
 	TMgServiceRequest requestParam;
	const TLiwGenericParam* param;
	TLiwVariant fileType;
	TLiwVariant filterField;
	TLiwVariant startVal;
	TLiwVariant endVal;
	TLiwVariant sortingField;
	TLiwVariant order;
	TLiwGenericParam posbasedparam;

	//setting the TransactionID
    requestParam.iTransactionID = aTransactionID;
   
    //Get the Filter Map
    if ( aPostionBasedSearching && ( aInParamList.Count() > 1) )
        {
         pos = 1;
         aInParamList.AtL( pos,posbasedparam );
         if ( (posbasedparam.Name().CompareF(KNullDesC8) != 0 ) || posbasedparam.Value().IsEmpty() ) 
             {
             param = NULL;
             }
         else
             {
             param = &posbasedparam;
             }
        }
    else
        {
        pos=0;//Search from starting point
        //filter map
        param =  aInParamList.FindFirst( pos, KFilter );
        }
    
       
	HBufC8* heapBuffer3 = NULL;
	HBufC8* heapBuffer4 = NULL;
    
    
    if(param)
        {
        filter = (*param).Value().AsMap();
        if(!filter)
            {
            //Filter Map missing : 
            posbasedparam.Reset();
            AppendErrorMessageL( KGetList, KFilter, KInvalid );
  	        User ::Leave(KErrArgument);
            }
          
        }
        
    
    if( (param) &&  (filter) )
        {//filter map
     
	    TPtrC type16;
	    
	    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &fileType) );	    
	    if( (filter->FindL( KFileType, fileType )) )
	        {
	        if ( (fileType.Get( type16 ))  && (type16.Length() > 0 ) )
		        {
		        heapBuffer3 = HBufC8::NewL( type16.Length() );
	            CleanupStack::PushL( heapBuffer3 );
	            TPtr8 type8( heapBuffer3->Des() );
	            type8.Copy( type16 );
	            requestParam.iFileType.Set(type8);
		        }
	    	else
		        {
		        //fileType.Reset();
		        posbasedparam.Reset();
		        AppendErrorMessageL( KGetList, KFileType, KMissingOrInvalid );
		        User ::Leave(KErrArgument);
	            }
	        }
	    else
	        {
	        //fileType.Reset();
		    posbasedparam.Reset();
		    AppendErrorMessageL( KGetList, KFileType, KMissing );
		    User ::Leave(KErrNotFound);  
	        } 
	        
	        
		CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &filterField) );	       
	    if( filter->FindL( KKey, filterField ) )
	        {
	        TPtrC filter16;
	    
	        if ( filterField.Get( filter16 ))
	            {
		        heapBuffer4 = HBufC8::NewL( filter16.Length() );
	            CleanupStack::PushL( heapBuffer4 );
	            TPtr8 filter8( heapBuffer4->Des() );
	            filter8.Copy( filter16 );
	            requestParam.iFilterField.Set(filter8);
		        }
		    else
		        {
		        //fileType.Reset();
		        //filterField.Reset();
		        posbasedparam.Reset();
		        AppendErrorMessageL( KGetList, KKey, KInvalid );
		        User ::Leave(KErrArgument);
		        }
	        }

 	    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &startVal) );
 	    if(filter->FindL( KStartRange, startVal ))
 	        {
 	        if ( !startVal.Get( requestParam.iStartVal ))
 	            {
 	            //fileType.Reset();
		        //filterField.Reset();
		        //startVal.Reset();
		        posbasedparam.Reset();
		        AppendErrorMessageL( KGetList, KStartRange, KInvalid );
		        User ::Leave(KErrArgument);
 	            }
 	        }
	    
	    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &endVal) );
	    if (filter->FindL( KEndRange, endVal  ))
	        {
	        if ( !endVal.Get( requestParam.iEndVal ))
 	            {
 	            //fileType.Reset();
		        //filterField.Reset();
		        //startVal.Reset();
		        //endVal.Reset();
		        posbasedparam.Reset();
		        AppendErrorMessageL( KGetList, KEndRange, KInvalid );
		        User ::Leave(KErrArgument);
		        }
	        }
	 
	    }//filter map

    else
        {
         //Filter Map missing : 
         posbasedparam.Reset();
         AppendErrorMessageL( KGetList, KFilter, KMissing );
  	     User ::Leave(KErrNotFound); 
        }

   if ( aPostionBasedSearching && ( aInParamList.Count() > 2) )
        {
         pos = 2;
         aInParamList.AtL( pos,posbasedparam );
         if ( (posbasedparam.Name().CompareF(KNullDesC8) != 0 ) || posbasedparam.Value().IsEmpty() ) 
             {
              param = NULL;
             }
         else
             {
             param = &posbasedparam;
             }
        }
    else
        {
        pos=0;//Search from starting point
	    //Sorting map
	    param =  aInParamList.FindFirst( pos, KSort );
        }
        
	HBufC8* heapBuffer1 = NULL;
	HBufC8* heapBuffer2 = NULL;
	    
    if(param)
        {
        sorting = (*param).Value().AsMap();
        if(!sorting)
            {
            //Filter Map missing : 
            posbasedparam.Reset();
            AppendErrorMessageL( KGetList, KSort, KInvalid );
  	        User ::Leave(KErrArgument);
            }
        }
        
	if( (param) &&  sorting )
	    {//sort map
	        CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &sortingField) );
	        if (sorting->FindL( KKey, sortingField ))
	            {
	            TPtrC sort16;
	            if ( sortingField.Get( sort16))
 	                {
 	                heapBuffer1 = HBufC8::NewL( sort16.Length() );
         	        CleanupStack::PushL( heapBuffer1 );
                    TPtr8 sort8( heapBuffer1->Des() );
                    sort8.Copy( sort16 );
                    requestParam.iSortField.Set(sort8);
		            }
		        else
		            {
		            //fileType.Reset();
		            //filterField.Reset();
		            //startVal.Reset();
		            //endVal.Reset();
		            //sortingField.Reset();
		            posbasedparam.Reset();
		            AppendErrorMessageL( KGetList, KKey, KInvalid );
		            User ::Leave(KErrArgument);
		            }
	            }

            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &order) );
            if (sorting->FindL( KOrder, order ))
	            {
	            TPtrC sortOrder16;
	            if ( order.Get( sortOrder16))
 	                {
 	                heapBuffer2 = HBufC8::NewL( sortOrder16.Length() );
	                CleanupStack::PushL( heapBuffer2 );
	                TPtr8 sortOrder8( heapBuffer2->Des() );
	                sortOrder8.Copy( sortOrder16 );
		            order.Get( requestParam.iOrder );
		            requestParam.iOrder.Set(sortOrder8);
		            }
		        else
		            {
		            //fileType.Reset();
		            //filterField.Reset();
		            //startVal.Reset();
		            //endVal.Reset();
		            //sortingField.Reset();
		            //order.Reset();
		            posbasedparam.Reset();
		            AppendErrorMessageL( KGetList, KOrder, KInvalid );
		            User ::Leave(KErrArgument);
		            }
	            }

	    }//sort map


	 iCoreClass->GetListL( requestParam,iServiceObserver ) ;
	 
	 
	 
	  //Sorting is an optional parameter, if it is present only then sorting fields and order present in stack
    if( (param) &&  sorting )
        {
       
        if( heapBuffer2 )
    		CleanupStack::PopAndDestroy( heapBuffer2 );
    
    	CleanupStack::Pop(&order);
	
		if( heapBuffer1 )
	    	CleanupStack::PopAndDestroy( heapBuffer1 );
	
    	CleanupStack::Pop(&sortingField); 
	
        }
     
	CleanupStack::Pop(&endVal); 
   	CleanupStack::Pop(&startVal);
   	 
   	if( heapBuffer4 )
	    CleanupStack::PopAndDestroy( heapBuffer4 );
   	 
   	CleanupStack::Pop(&filterField); 
   	 
    if( heapBuffer3 )
	    CleanupStack::PopAndDestroy( heapBuffer3 );
   	 
   	CleanupStack::Pop(&fileType); 
	
    fileType.Reset();
    filterField.Reset();
    startVal.Reset();
    endVal.Reset();
    sortingField.Reset();
    order.Reset();
    posbasedparam.Reset();

	}

// -----------------------------------------------------------------------------
// CMgInterface::SendRequestL
// This function is called by the user to get mapped SAPI generic error code
// from symbian error codes .
// -----------------------------------------------------------------------------

TInt CMgInterface::SapiError( TInt aSymbianErr )
    {
    TInt sapiErr(SErrGeneralError);

   	switch (aSymbianErr)
    	{
      	case KErrArgument:
   		    {
   		    sapiErr = SErrBadArgumentType;
   		    break;
   		    }
   	    case KErrNotFound:
   		    {
   		    sapiErr = SErrMissingArgument;
   		    break;
   		    }
   		    
   		case KErrNotSupported:
   		    {
   		    sapiErr = SErrServiceNotSupported;
   		    break;
   		    }
   		case KErrServerBusy:
   		    {
   		    sapiErr = SErrServerBusy;
   		    break;
   		    }
    	case KErrGeneral:
    		{
   		    sapiErr = SErrGeneralError;
   		    break;
   		    }
   		case KErrCancel:
	   		{
	   		sapiErr = SErrCancelSuccess;
			break;
	   		}
		case KErrNone:
			{
			sapiErr= SErrNone;
			break;
			}
	
		case KErrNoMemory:
			{
			sapiErr = SErrNoMemory;
			break;
			}
		case KErrInUse:
			{
			sapiErr = SErrServiceInUse;
			break;
			}
		case KErrNotReady:
        	{
        	sapiErr = SErrServiceNotReady;
        	break;
        	}
   		}
    return sapiErr;
    }

// ---------------------------------------------------------------------------
// Append Error Message
// ---------------------------------------------------------------------------
//
void CMgInterface::AppendErrorMessageL( const TDesC8& aCmdName, const TDesC8& aParameter, const TDesC& aMessage )
	{
	iErrorMessage = HBufC::NewL( KMaxErrorMessageLength );
	TPtr tmpMsgPtr = iErrorMessage->Des();
	tmpMsgPtr.Copy(KDomainName);
	
	HBufC* temp = HBufC::New( KMaxErrorMessageLength );

	if ( aCmdName.Length() )
		{
		tmpMsgPtr.Append( KErrorMsgSeparator );
		temp->Des().Copy( aCmdName ); 
		tmpMsgPtr.Append( temp->Des() );
		}

	tmpMsgPtr.Append(KErrorMsgSeparator);
	
	if ( aParameter.Length() )
		{
		temp->Des().Copy(aParameter); 
		tmpMsgPtr.Append(temp->Des());
		}
	
	if ( aMessage.Length() )
		{
		tmpMsgPtr.Append( aMessage );
		}

	delete temp;	
	}
