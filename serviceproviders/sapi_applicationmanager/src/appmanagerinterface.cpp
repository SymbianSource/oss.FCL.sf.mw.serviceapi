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
*				 calling the functionality to Application Manager SAPI.
*  Interafce
*
*/



#include <liwcommon.h>
#include <liwbufferextension.h>
#include <utf.h>

#include "appmanagerinterface.h"
#include "appmanagerservice.h"
#include "appitemslist.h"
#include "appserviceobserver.h"
#include "serviceerrno.h"
#include "appserviceerrmsg.hrh"


#define KMAXCONTENTLENGTH 32
#define KMAXPATHLENGTH 255

//Supported Operation
_LIT8(KGetList,  "GetList");
_LIT8(KCancel,  "Cancel");
_LIT8(KLaunchApp,"LaunchApp");
_LIT8(KLaunchDoc,"LaunchDoc");

//Input Keys/arguments

// Data source name
_LIT8(KType,"Type");
_LIT8(KApplicationID,"ApplicationID");
_LIT8(KCmdLine,"CmdLine");
_LIT8(KOptions,"Options");
_LIT8(KDocument,"Document");
_LIT8(KMimeType,"MimeType");

// Filter Map
_LIT8(KFilter,"Filter");


//Filter criteria
_LIT8(KDocumentPath,"DocumentPath");
_LIT8(KMode,"Mode");
_LIT8(KPosition,"Position");
//_LIT8(KPath ,"Path");
_LIT8(KHandle,"Handle");
_LIT8(KDocumentName,"DocumentName");


//Possible Content
//_LIT(KUserInstalledPackage,"UserInstalledPackage");
//_LIT(KApplication,"Application");


//Output Keys/arguments
_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");
_LIT8(KTransactionID,"TransactionID");



// -----------------------------------------------------------------------------
// CAppManagerInterface::NewLC
// Returns the instance of CAppManagerInterface.
// -----------------------------------------------------------------------------
CAppManagerInterface* CAppManagerInterface::NewL()
	{

	CAppManagerInterface* self = new ( ELeave )CAppManagerInterface();
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}


// -----------------------------------------------------------------------------
// CAppManagerInterface::~CAppManagerInterface
// Destructor of class
// -----------------------------------------------------------------------------
CAppManagerInterface::~CAppManagerInterface()
	{
     //Release the instance of core class
	 delete iCoreClass;
     iCoreClass = NULL;
	}


// -----------------------------------------------------------------------------
// CAppManagerService::ExecuteCmdL
// Request handler method of interface class
// -----------------------------------------------------------------------------

void CAppManagerInterface::ExecuteCmdL(const TDesC8& aCmdName,
                           const CLiwGenericParamList& aInParamList,
                           CLiwGenericParamList& aOutParamList,
                           TUint aCmdOptions ,
                           MLiwNotifyCallback* aCallBack)
	{

    TInt32 transactionID = 0;
	TInt errCode = 0;
	TInt pos = 0;
    const TLiwGenericParam* param = NULL;
    TLiwGenericParam posbasedparam;

    if( (aCmdOptions & KLiwOptCancel ) && (0== aCmdName.CompareF( KCancel ))) // for cancel asynchronous request
	    {

            param = aInParamList.FindFirst( pos, KTransactionID );
            if( !param )
                {
                
                if( aInParamList.Count() > 0 )
                    {
                     pos = 0;
                     aInParamList.AtL( pos, posbasedparam );
                     if (posbasedparam.Value().IsEmpty() )
                        {
                        param = NULL;
                        }
                     else
                        {
                        param = &posbasedparam;
                        }
                     }
               
                 }


            if( param )
			    {
			    param->Value().Get( transactionID );
                errCode = iCoreClass->Cancel( transactionID );
		    	if ( KErrNone != errCode )
			        {
			        TInt sapiErr = SapiError(errCode);
                    aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)sapiErr)));
                    aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KIncorrectTransactionId ) ) );
			        }
			    }
			else
			    {
			    aOutParamList.AppendL( TLiwGenericParam ( KErrorCode,TLiwVariant( TInt32( SErrMissingArgument ) ) ) );
			    aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KTransactionIdMissing ) ) );
	            }

	    return;

    	}



    // Check the command name;Cmd name should be GetList,LaunchApp or LaunchDoc
	if( 0 == aCmdName.CompareF( KGetList ) )
		{
	    //Call GetListAPI
	    if( (aCmdOptions & KLiwOptASyncronous ) && ( NULL != aCallBack ) ) //Asynchronous request
		    {
		    //No Asynch version of getlist is supported
             aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiError(KErrNotSupported))));
             aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant(KAsynchVersionNotSupported ) ) );
		    }
		else if( (!aCmdOptions) && ( NULL == aCallBack ) ) //Synchronous request
		    {
		    GetListL( aInParamList, aOutParamList );
		    }
		else
		    {
		    aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiError(KErrArgument))));
		    aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KAsynchRequestNotProper ) )  );    
		    }
	    }
	else if( 0 == aCmdName.CompareF( KLaunchApp ) )
	    {
	    //Call LaunchApp API
	    if( (aCmdOptions & KLiwOptASyncronous ) && ( NULL != aCallBack ) ) //Asynchronous request
	        {
	            
	        //Asynch Call
	        transactionID = aCallBack->GetTransactionID();
	        LaunchAppL( aInParamList, aOutParamList, aCallBack , transactionID );
	            	            
	        }
	    else if( (!aCmdOptions) && ( NULL == aCallBack ) ) //Synchronous request
	        {
	        //Synchronous Call
	        LaunchAppL( aInParamList, aOutParamList);
	        }
	    else
	        {
	        aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiError(KErrArgument))));
		    aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KAsynchRequestNotProper ) )  );       
	        }

	    }

	else if( 0 == aCmdName.CompareF( KLaunchDoc )  )
	    {
	    //Call LaunchDoc API
	    if( (aCmdOptions & KLiwOptASyncronous ) && ( NULL != aCallBack ) ) //Asynchronous request
	        {
	         //Asynch Call
	         transactionID = aCallBack->GetTransactionID();
	         LaunchDocL( aInParamList, aOutParamList, aCallBack , transactionID );
	        
	        }
	    else if( (!aCmdOptions) && ( NULL == aCallBack ) ) //Synchronous request
	        {
	        //Synchronous Call
	        LaunchDocL( aInParamList, aOutParamList);
	        }
	    else
	        {
	        aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiError(KErrArgument))));
		    aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KAsynchRequestNotProper ) )  );       
	        }    
	    }
	else
	    {
	    //error code = command not supported
	    aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiError(KErrNotSupported))));
	    aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KCommandNotSupported ) ) );
	    }


    if( (aCmdOptions & KLiwOptASyncronous ) && ( NULL != aCallBack ) ) //Asynchronous request
        {
		aOutParamList.AppendL( TLiwGenericParam( KTransactionID, TLiwVariant( transactionID ) ) );
        }
	}


// -----------------------------------------------------------------------------
// CAppManagerInterface::CAppManagerInterface
// Constructor  of class
// -----------------------------------------------------------------------------

CAppManagerInterface::CAppManagerInterface()
                       :iCoreClass( NULL )

	{

	}


// -----------------------------------------------------------------------------
// CAppManagerInterface::ConstructL
// Two-phased constructor of class
// -----------------------------------------------------------------------------

void CAppManagerInterface::ConstructL()
	{
	// Create the instance of core class
	iCoreClass = CAppManagerService::NewL();

    }



// -----------------------------------------------------------------------------
// CAppManagerInterface::GetListL
// This function will send the request to Core class
// -----------------------------------------------------------------------------

void CAppManagerInterface::GetListL(const CLiwGenericParamList& aInParamList , CLiwGenericParamList& aOutParamList  )

	{



	 TLiwGenericParam posbasedparam;
     TBool postionbasedsearching = EFalse;
	 const TLiwGenericParam* param = NULL;
	 TInt pos = 0;
	 param = aInParamList.FindFirst( pos, KType );

	 if(!param)
        {

         if( aInParamList.Count() > 0 )
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
        }
    TBuf<KMAXCONTENTLENGTH>  content;
    if( param )
        {
        
	 // content present : Mandatory Argument
		if (param->Value().TypeId() != LIW::EVariantTypeDesC || param->Value().AsDes().Length() > KMAXCONTENTLENGTH || !param->Value().Get( content )   ) 
	    	{
	    	//content type is different: append error and return
	    	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ((TInt32)SErrBadArgumentType) ));
	    	aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KContentTypeMismatch ) ) ); 
	    	
	    	posbasedparam.Reset();
	    	
	    	return;
	    	}
	  
        HBufC8* heapBuffer = NULL;
     	param = NULL;
       	if ( postionbasedsearching && ( aInParamList.Count() > 1) )
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
        CFilterParam* filter = NULL;
        TLiwVariant documentname;
	    TLiwVariant mimetype;
	    
	    
        //Filter is prsent
        if ( param && (param->Value().TypeId() != LIW::EVariantTypeNull ) )
            {

            filter = CFilterParam::NewL();
            CleanupStack::PushL( filter );
            const CLiwMap* filtermap;

	        TPtrC val;
	        filtermap = param->Value().AsMap();

			if (filtermap )
                {
                CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &documentname) );
	    
                if (filtermap->FindL( KDocumentPath, documentname ) && (documentname.TypeId() != LIW::EVariantTypeNull )  )
                	{
                	if ((documentname.AsDes().Length() < KMAXPATHLENGTH ) && documentname.Get(val))
                		{
                		filter->SetDocName(val);
                		val.Set(NULL,0);	
                		}
                	 else
                	 	{
                	 	//content type is different: do cleanup, append error and return			        
				        CleanupStack::Pop(&documentname);    
				        documentname.Reset();
				        
                	 	if( filter )
				            {
				            CleanupStack::PopAndDestroy( filter );
				            }

                	 	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrBadArgumentType) ) );
                		aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KFilterTypeMismatch ) ) ); 	
                		
                		posbasedparam.Reset();
                		
                		return;
                	 	}	
                	}
                	
				CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &mimetype) );
	            if (filtermap->FindL( KMimeType, mimetype ) && (mimetype.TypeId() != LIW::EVariantTypeNull ) )
	            	{
	            	
	                if ((mimetype.AsDes().Length() < KMAXPATHLENGTH ) && mimetype.Get(val))
                		{
	               		//Before sending convert 16 bit to 8 Bit
			            heapBuffer = HBufC8::NewL(val.Length());
		                TPtr8  val8(heapBuffer->Des());
		                val8.Copy(val);
		                filter->SetmimeType(val8);			
	            		}
	            	else
                	 	{
                	 	//content type is different: do cleanup, append error and return
                	 	
                	 	CleanupStack::Pop(&mimetype); 
				        mimetype.Reset();
				        
				        CleanupStack::Pop(&documentname);    
				        documentname.Reset();
				        
                	 	if( filter )
				            {
				            CleanupStack::PopAndDestroy( filter );
				            }
   
				        delete heapBuffer;    
				         
                	 	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrBadArgumentType) ) );
                		aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KFilterTypeMismatch ) ) ); 	
                		
                		posbasedparam.Reset();
                		
                		return;
                	 	}			            	
	            	}
	            CleanupStack::Pop(2);
                }
	        else
	            {
	            aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrBadArgumentType  ) ));
                aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KFilterTypeMismatch ) ) ); 
                CleanupStack::PopAndDestroy( filter );
                posbasedparam.Reset();
                return;   
	            }

	        }

         //Call GetList of Core class
         MIterator* iter = NULL;
         TRAPD ( errCode, iCoreClass->GetListL( iter, content, filter ) );

         TInt sapiErr = SErrNone;
         if (errCode)
    	    {
    	    sapiErr = SapiError(errCode);
    	    }

         aOutParamList.AppendL( TLiwGenericParam ( KErrorCode,TLiwVariant( ( TInt32 )sapiErr ) ) );


         if( errCode == KErrNone )

            {
             // Fill the Iterator in Generic Paaram List
             TLiwVariant response;

	         // Iterator will accept the MIterator * and will become the owner
             CAppItemsList *iterator = CAppItemsList::NewL( iter );
 	         CleanupClosePushL( *iterator );
	         response.Set( iterator );
	         aOutParamList.AppendL( TLiwGenericParam ( KResponse, response ) );
 		     CleanupStack::Pop( iterator );
             iterator->DecRef();

            }

          if( filter )
            {		        
            CleanupStack::PopAndDestroy( filter );
            }
            
          mimetype.Reset();
		  documentname.Reset();
       	  
       	  delete heapBuffer;
       	 
        }
     else
        {
        //content type missig : Mandatory Argument
        aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrMissingArgument)));
        aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KContentMissing ) ) );
        }

       posbasedparam.Reset();

	}

// -----------------------------------------------------------------------------
// CAppManagerInterface::LaunchAppL
// This function will send the request to Core class
// -----------------------------------------------------------------------------

void CAppManagerInterface::LaunchAppL(const CLiwGenericParamList& aInParamList ,
                                            CLiwGenericParamList& aOutParamList,
                                            MLiwNotifyCallback* aCallBack,
                                            TInt32 aTransactionID )

	{
	 TLiwGenericParam posbasedparam;
     TBool postionbasedsearching = EFalse;
     TOptions options;
	 const TLiwGenericParam* param = NULL;
	 TInt pos = 0;



	 param = aInParamList.FindFirst( pos, KApplicationID );

	 if( !param )
        {

         if( aInParamList.Count() > 0 )
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
        }
    TBuf<KMAXCONTENTLENGTH> appId;
    if( param )
        {

        // content present : Mandatory Argument
		if (param->Value().TypeId() != LIW::EVariantTypeDesC || param->Value().AsDes().Length() > KMAXCONTENTLENGTH || !param->Value().Get( appId ))
	    	{
	    	//content type is different: append error and return
	    	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ((TInt32)SErrBadArgumentType) ));
	    	aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KApplicationIDMismatch ) ) ); 
	    	
	    	posbasedparam.Reset();
	    	
	    	return;
	    	}
	    	
        TPtrC  cmdline;
       // TBuf<KMAXCONTENTLENGTH> cmdline;
        TLiwVariant mode;
	    TLiwVariant postion;
	    TLiwVariant document;

       	param = NULL;
        if ( postionbasedsearching && ( aInParamList.Count() > 1) )
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
            param =  aInParamList.FindFirst( pos, KCmdLine );
            }

        //CommandLine  is prsent
        if ( param && (param->Value().TypeId() != LIW::EVariantTypeNull ) )
            {
            if( !param->Value().Get( cmdline ) )
                {
                aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant( (TInt32)SErrBadArgumentType ) ) );
                aOutParamList.AppendL( TLiwGenericParam( KErrorMsg, TLiwVariant( KCommandLineMismatch ) ) );
                posbasedparam.Reset();
                return;
                }
            }







        param = NULL;
       	if ( postionbasedsearching && ( aInParamList.Count() > 2) )
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
            //filter map
            param =  aInParamList.FindFirst( pos, KOptions );
            }



		
        //Options is prsent
        if ( param && (param->Value().TypeId() != LIW::EVariantTypeNull ) )
            {
            if( (param->Value().TypeId() != LIW::EVariantTypeMap ) && 
            	(param->Value().TypeId() != LIW::EVariantTypeNull ))
            		{
            		aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant( (TInt32)SErrBadArgumentType ) ) );
                	aOutParamList.AppendL( TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchAppOptionsTypeMismatch ) ) );
	                posbasedparam.Reset();
	                return;    	
            		}

            const CLiwMap* optionsmap = param->Value().AsMap();

            if ( optionsmap )
                {
				CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &mode) );
				
                if (optionsmap->FindL( KMode, mode ) && (mode.TypeId() != LIW::EVariantTypeNull ))
                	{
                	if (( mode.AsDes().Length() > KMAXCONTENTLENGTH ) || !mode.Get( options.iMode ))
                		{
	               	 	//content type is different: do cleanup, append error and return 
				         
				        CleanupStack::Pop(&mode);
				        mode.Reset() ;
				         
                	 	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrBadArgumentType) ) );
                		aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchAppOptionsTypeMismatch ) ) ); 	
                		
                		posbasedparam.Reset();
                		return;		            	
	            		}	
                		
                	}
	            
	            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &postion) );
				
                if (optionsmap->FindL( KPosition, postion ) && (postion.TypeId() != LIW::EVariantTypeNull ))
                	{
                	if (( postion.AsDes().Length() > KMAXCONTENTLENGTH ) || !postion.Get( options.iPostion ))
                		{
	               	 	//content type is different: do cleanup, append error and return 
	               	 	CleanupStack::Pop(&postion);
	               	 	CleanupStack::Pop(&mode);
	               	 	
				        mode.Reset() ;
				        postion.Reset() ;
				         
                	 	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrBadArgumentType) ) );
                		aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchAppOptionsTypeMismatch ) ) ); 	
                		
                		posbasedparam.Reset();
                		return;		            	
	            		}
                	}
	            
	            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &document) );
	            
				if (optionsmap->FindL( KDocumentPath, document ) || (document.TypeId() != LIW::EVariantTypeNull ) )
					{
					if ( ( document.AsDes().Length() > KMAXPATHLENGTH ) || !document.Get( options.iDocument ) )
						{
	               	 	//content type is different: do cleanup, append error and return 
	               	 	CleanupStack::Pop(3); //document, position, mode
	               	 	
				        mode.Reset() ;
				        postion.Reset() ;
				        document.Reset();
				         
                	 	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrBadArgumentType) ) );
                		aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchAppOptionsTypeMismatch ) ) ); 	
                		
                		posbasedparam.Reset();
                		return;		            	
	            		}
					} 
				
				CleanupStack::Pop(3);	 //document, position, mode

                }

	        }



       TInt errCode;

       //Converting command line form 16 to 8-bit

       HBufC8* heapBuffer = HBufC8::NewL( cmdline.Length() );
       CleanupStack::PushL( heapBuffer );
       TPtr8 cmdline8( heapBuffer->Des() );
       cmdline8.Copy( cmdline );

        if( aCallBack )
            {
             //Asynch Call
             CAppServiceObserver* observer = CAppServiceObserver::NewL( aCallBack );
             CleanupStack::PushL( observer );
             TRAP ( errCode, iCoreClass->LaunchApplicationL( appId, cmdline8, options, observer,  aTransactionID  )  );
             CleanupStack::Pop( observer );
            }
        else
            {
             TRAP ( errCode, iCoreClass->LaunchApplicationL( appId, cmdline8, options )  );
            }

        CleanupStack::PopAndDestroy( heapBuffer );
                
        mode.Reset();
	    postion.Reset();
	    document.Reset();

        TInt sapiErr = SErrNone;
        if (errCode)
           {
           sapiErr = SapiError( errCode );
           }

        aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant( ( TInt32 ) sapiErr ) ));

        }
     else
        {
        //content type missig : Mandatory Argument
        aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant( (TInt32)SErrMissingArgument) ) );
        aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KApplicationIDMissing ) ) );
        }

       posbasedparam.Reset();

	}



// -----------------------------------------------------------------------------
// CAppManagerInterface::GetListL
// This function will send the request to Core class
// -----------------------------------------------------------------------------

void CAppManagerInterface::LaunchDocL(const CLiwGenericParamList& aInParamList,
                                            CLiwGenericParamList& aOutParamList,
                                            MLiwNotifyCallback* aCallBack,
                                            TInt32 aTransactionID )

	{

	 TLiwGenericParam posbasedparam;
     TBool postionbasedsearching = EFalse;
     TDocument document;
     TOptions options;
	 const TLiwGenericParam* param = NULL;
	 TInt pos = 0;
	 const CLiwMap* documentmap = NULL;
     TLiwVariant mode;
     TLiwVariant path;
	 TLiwVariant handle;   

	 param = aInParamList.FindFirst( pos, KDocument );

	 if( !param )
        {

         if( aInParamList.Count() > 0 )
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
        }

    if ( param )
        {
          documentmap = param->Value().AsMap();
	      if ((param->Value().TypeId() != LIW::EVariantTypeNull) && 
	      		(!documentmap && !postionbasedsearching))
	        {
	        aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant( (TInt32)SErrBadArgumentType ) ) );
	        aOutParamList.AppendL( TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchDocMapTypeMismatch ) ) );
	        posbasedparam.Reset();
	        return;    
	        }
            
        }


    param = aInParamList.FindFirst( pos, KMimeType );

    if( !param )
        {

         if( aInParamList.Count() > 1 )
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
                postionbasedsearching = ETrue;
                }
            }
        }


	if ((param) && (param->Value().TypeId() != LIW::EVariantTypeNull)  && (param->Value().TypeId() != LIW::EVariantTypeDesC)  )
		{
		aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant( (TInt32)SErrBadArgumentType ) ) );
        aOutParamList.AppendL( TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchDocMimeTypeMismatch ) ) );
        posbasedparam.Reset();
        return;    	
		}
		
		
    // present : Mandatory Argument
    TBuf<KMAXCONTENTLENGTH>  mimetype;
    if( ( (param)  && ( param->Value().AsDes().Length() < KMAXCONTENTLENGTH ) && (param->Value().Get( mimetype ))  ) || ( documentmap ) )
        {

        
        
        param = NULL;
       	if ( postionbasedsearching && ( aInParamList.Count() > 2) )
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
            //filter map
            param =  aInParamList.FindFirst( pos, KOptions );
            }


        //Options is prsent
        if ( param )
            {
            if( (param->Value().TypeId() != LIW::EVariantTypeMap ) && 
            	(param->Value().TypeId() != LIW::EVariantTypeNull ) )
        		{
        		 //Option Type MisMatch 
            
                mode.Reset();
                
                aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant( (TInt32)SErrBadArgumentType  ) ) );
                aOutParamList.AppendL( TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchOptionsTypeMismatch ) ) );
                posbasedparam.Reset();
                return;       	
        		}
            		
            const CLiwMap* optionsmap = param->Value().AsMap();

            if(optionsmap)
            	 
                {
                CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &mode) );
                optionsmap->FindL( KMode, mode );
                if (( mode.AsDes().Length() > KMAXCONTENTLENGTH ) || !mode.Get( options.iMode ))
                		{
	               	      
				        CleanupStack::Pop(&mode);
				        mode.Reset() ;
				         
                	 	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrBadArgumentType) ) );
                		aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchAppOptionsTypeMismatch ) ) ); 	
                		
                		posbasedparam.Reset();
                		return;		            	
	            		}	
                CleanupStack::Pop(&mode);
                }
            }
        

       	//Document is prsent
        if ( documentmap )
            {
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &path) );
            if (documentmap->FindL( KDocumentPath, path ))
            	{
            	
            		if ( ( path.AsDes().Length() > KMAXPATHLENGTH ) || !path.Get( document.iPath ) )
						{
	               	 	//content type is different: do cleanup, append error and return 
	               	 	CleanupStack::Pop(&path);//path
	                    path.Reset();
				         
                	 	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrBadArgumentType) ) );
                		aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchAppOptionsTypeMismatch ) ) ); 	
                		
                		posbasedparam.Reset();
                		return;		            	
	            		}
            	
            	}
            CleanupStack::Pop();
            	
			CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &handle) );
	    	if (documentmap->FindL( KHandle, handle ) && (handle.TypeId() != LIW::EVariantTypeNull ))
                {
            	if (!handle.Get( document.iHandle ))
                		{
	               	 	//do cleanup, append error and return 
				        CleanupStack::Pop(&handle);
				        handle.Reset() ;

                	 	aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant ( (TInt32)SErrBadArgumentType) ) );
                		aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KLaunchAppOptionsTypeMismatch ) ) ); 	
                		
                		posbasedparam.Reset();
                		return;		            	
	            		}	
            	
               	}
            
            CleanupStack::Pop();
            /*
            // The follwing code will be introduced once default file buffer is created
            CLiwBuffer* buffer = NULL;
            buffer = handle.AsBuffer();
            if ( KLiwBufferFile == buffer->TypeID() )
                {
                CLiwFileBuffer* filebuffer = ( CLiwFileBuffer* ) buffer;
                document.iHandle = filebuffer->AsFile();
                }
            */
            }


       TInt errCode;
       //Converting command line form 16 to 8-bit

       HBufC8* heapBuffer = HBufC8::NewL( mimetype.Length() );
       CleanupStack::PushL( heapBuffer );
       TPtr8 mimetype8( heapBuffer->Des() );
       mimetype8.Copy( mimetype );
       TPtrC filename;

       if( aCallBack )
            {
             //Asynch Call
             CAppServiceObserver* observer = CAppServiceObserver::NewL( aCallBack );
             CleanupStack::PushL( observer );
             TRAP ( errCode, iCoreClass->LaunchDocumentL( document, mimetype8, options , filename, observer,  aTransactionID  )  );
             CleanupStack::Pop( observer );
            }
        else
            {
             TRAP ( errCode, iCoreClass->LaunchDocumentL(document, mimetype8, options , filename )  );
            }

        CleanupStack::PopAndDestroy( heapBuffer );
        path.Reset();
	    handle.Reset();
	    mode.Reset();

        TInt sapiErr = SErrNone;
        if (errCode)
           {
           sapiErr = SapiError( errCode );
           }

        aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant( ( TInt32 ) sapiErr ) ));

        if( filename.Length() != 0)
            {
            aOutParamList.AppendL( TLiwGenericParam( KDocumentName, TLiwVariant( filename ) ));
            }

        }
     else
        {
        //missig : Mandatory Argument
        aOutParamList.AppendL( TLiwGenericParam( KErrorCode, TLiwVariant( ( TInt32 ) SErrMissingArgument  ) ) );
        aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KDocumentMissing ) ) );
        }

       posbasedparam.Reset();

	}



// -----------------------------------------------------------------------------
// CAppManagerInterface::SapiError
// This function is called by the user to get mapped SAPI generic error code
// from symbian error codes .
// -----------------------------------------------------------------------------

TInt CAppManagerInterface::SapiError( TInt aSymbianErr )
    {
    TInt sapiErr(SErrGeneralError);

   	switch (aSymbianErr)
    	{
      	case KErrArgument:
   		    {
   		    sapiErr = SErrBadArgumentType;
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
    	case KErrBadName: 
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
		case KErrNotFound:
			{
			sapiErr= SErrMissingArgument;
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
		case KErrPathNotFound:
			{
			sapiErr = SErrPathNotFound ;
        	break;	
			}
   		}
    return sapiErr;
    }
