/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CLandmarkInterface class implementation
 *
*/

//INCLUDES
#include <e32math.h>
#include <liwcommon.h>
#include <epos_cposlandmarkparser.h>
#include <epos_cposlandmarkencoder.h>
#include <epos_cposlandmarksearch.h>
#include <epos_cposlmcompositecriteria.h>
#include <epos_cposlmnearestcriteria.h>
#include <epos_cposlmtextcriteria.h>
#include <epos_cposlmareacriteria.h>
#include <epos_cposlmcategorycriteria.h>
#include <epos_cposlmcatnamecriteria.h>
#include <epos_cposlmdatabasemanager.h>
#include <epos_tposlmdatabasesettings.h>
#include <utf.h>
#include "landmarkliwparams.hrh"
#include "landmarkinterface.h"
#include "landmarkservice.h"
#include "clandmarkfilter.h"
#include "clandmarkiterable.h"
#include "clandmarkcategoryiterable.h"
#include "clandmarkdatabaseiterable.h"
#include "clandmarkobserver.h"
#include "clandmarkcallbackmap.h"
#include "../../inc/serviceerrno.h"

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CLandmarkInterface::NewL()
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CLandmarkInterface* CLandmarkInterface::NewL( )
    {
    CLandmarkInterface* self = new (ELeave) CLandmarkInterface();
    CleanupStack::PushL (self );
    self->ConstructL ( );
    CleanupStack::Pop (self );
    return self;
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::~CLandmarkInterface()
// Destructor.
// ---------------------------------------------------------------------------
//
CLandmarkInterface::~CLandmarkInterface( )
    {
    delete iService;
    delete iObserver;
    delete iErrMsg;
    delete iId;
    iCallbackMap.ResetAndDestroy ( );
    iCallbackMap.Close ( );
    ReleaseLandmarkResources ( );
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::CLandmarkInterface()
// C++ default constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CLandmarkInterface::CLandmarkInterface( )
    {
    }

// ---------------------------------------------------------------------------
// CLandmarkFilter::ConstructL()
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::ConstructL( )
    {
    //instantiate the service class
    iService = CLandmarkService::NewL ( );
    //register observer for async requests
    iObserver = CLandmarkObserver::NewL ( this );
    iService->RegisterObserver (iObserver );
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::ExecuteCmdL( const TDesC8& aCmdName,
//                           const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This function is called by the user to handle the service commands.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::ExecuteCmdL( const TDesC8& aCmdName,
        const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
        MLiwNotifyCallback* aCallback )
    {
    if ( iErrMsg )
        {
        delete iErrMsg;
        iErrMsg = NULL;
        }
    if( iId )
    	{
    	delete iId;
    	iId = NULL;
    	}
    //check if any of the service API's leave
    TRAPD(err,SwitchCmdL(aCmdName,aInParamList,aOutParamList,
                    aCmdOptions,aCallback))
    ;
    TInt SapiErr = SErrNone;
    if (err )
        {
        SapiErr = SapiError (err );
        }

    aOutParamList.AppendL (TLiwGenericParam (KErrorCode, TLiwVariant ((TInt32)SapiErr ) ) );
    if ( iErrMsg )
        {
        aOutParamList.AppendL (TLiwGenericParam (KErrorMsg,
                TLiwVariant (iErrMsg ) ) );
        }
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::SapiError( )
// This function is called by the user to get mapped SAPI generic error code
// from symbian error codes .
// ---------------------------------------------------------------------------
//
TInt CLandmarkInterface::SapiError( TInt aSymbianErr )
    {
    TInt sapiErr(aSymbianErr);

    switch ( sapiErr )
        {
        //case EPosLmInvalidArgument:
        case KErrBadName:
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
        case KErrLocked:
        case KErrInUse:
            {
            sapiErr = SErrServiceInUse;
            break;
            }
        case KErrAccessDenied:
            {
            sapiErr = SErrAccessDenied;
            break;
            }
        case KErrAlreadyExists:
            {
            sapiErr = SErrEntryExists;
            break;
            }
        case KErrNotReady:
            {
            sapiErr = SErrServiceNotReady;
            break;
            }
        case KErrNotFound:
            {
            sapiErr = SErrNotFound;
            break;
            }
        case KErrPosLmUnknownFormat:
            {
            sapiErr = SErrUnknownFormat;
            break;
            }
        case KErrPathNotFound:
            {
            sapiErr = SErrPathNotFound;
            break;
            }
        case KErrGeneral:
            {
            sapiErr = SErrGeneralError;
            break;
            }
        case SErrInvalidServiceArgument:
            break;
        case SErrMissingArgument:
            break;
        default:
            sapiErr = SErrGeneralError;
            break;
        }
    return sapiErr;
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::Close( )
// This function is called by the user to close the interface.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::Close( )
    {
    delete this;
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::Callback( TInt32 aTransactionId )
// This function returns the callback for the given transaction id and removes it from the list.
// ---------------------------------------------------------------------------
//
MLiwNotifyCallback* CLandmarkInterface::Callback( TInt32 aTransactionId )
    {
    MLiwNotifyCallback* callback=  NULL;
    TInt count = iCallbackMap.Count ( );
    for (TInt i = 0; i < count; ++i )
        {
        if ( iCallbackMap[i]->Get (aTransactionId, callback ) )
            {
            delete(iCallbackMap[i]);
            iCallbackMap.Remove (i );
            break;
            }
        }
    return callback;
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::SetActiveL( const CLiwGenericParamList& aInParamList )
// This calls the appropriate service function for setting active database.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::SetActiveL( const CLiwGenericParamList& aInParamList )
    {
    TInt index = 0;
    const TLiwGenericParam* database = aInParamList.FindFirst ( index, KDbUri );
    if ( !database )
        {
        // If position based parsing is implemented then
        // the name of parameter will be empty CHECK
        index = 0;
        database = aInParamList.FindFirst ( index, KNullDesC8 );
        }
    if ( database )
        {
        const TLiwVariant& variant = database->Value ( );
        if ( variant.TypeId ( )== LIW::EVariantTypeDesC )
            {
            iService->SetActiveL ( variant.AsDes ( ) );
            }
        else
            {
            User::Leave (SErrBadArgumentType );
            }
        }
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::SwitchCmdL( const TDesC8& aCmdName,
//                           const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This function calls the appropriate functions based on the command id.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::SwitchCmdL( const TDesC8& aCmdName,
        const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
        MLiwNotifyCallback* aCallback )
    {
    if ( ( (KLiwOptASyncronous & aCmdOptions) && !aCallback) ||( !(KLiwOptASyncronous & aCmdOptions) && aCallback) )
        {
        iErrMsg = KIncorrectAsyncReq().AllocL ( );
        User::Leave (SErrInvalidServiceArgument );
        }

    if ( aCmdName == KCancel && (KLiwOptCancel & aCmdOptions) )
        {
        Cancel (aInParamList, aOutParamList, aCmdOptions, aCallback );
        }
    else
        if ( aCmdName == KGetList )
            {
            GetListL (aInParamList, aOutParamList, aCmdOptions, aCallback );
            }
        else
            //since no other APIs support async return error if callback is 
            //provide
            if ( aCallback )
                {
                iErrMsg = KAsyncNotSupported().AllocL ( );
                User::Leave (SErrInvalidServiceArgument );
                }
            else
                if ( aCmdName == KAdd )
                    {
                    AddL (aInParamList, aOutParamList, aCmdOptions, aCallback );
                    }
                else
                    if ( aCmdName == KRemove )
                        {
                        RemoveL (aInParamList, aOutParamList, aCmdOptions,
                                aCallback );
                        }
                    else
                        if ( aCmdName == KOrganise )
                            {
                            OrganiseL (aInParamList, aOutParamList,
                                    aCmdOptions, aCallback );
                            }
                        else
                            if ( aCmdName == KImport )
                                {
                                ImportL (aInParamList, aOutParamList,
                                        aCmdOptions, aCallback );
                                }
                            else
                                if ( aCmdName == KExport )
                                    {
                                    ExportL (aInParamList, aOutParamList,
                                            aCmdOptions, aCallback );
                                    }
                                else
                                    if ( aCmdName == KNew )
                                        {
                                        NewTemplateL (aInParamList,
                                                aOutParamList, aCmdOptions,
                                                aCallback );
                                        }
                                    else
                                        {
                                        // invalid command return error in outparam list
                                        iErrMsg = KInvalidServiceCmd().AllocL ( );
                                        User::Leave (SErrInvalidServiceArgument );
                                        }
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::GetListL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This function calls the appropriate functions based on the content type.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::GetListL( const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
        MLiwNotifyCallback* aCallback )
    {
    //Input param List must have Type specified
    if ( !aInParamList.Count() )
        {
        ErrorMessageL (KGetList, KContentType );
        iErrMsg->Des().Append ( KMissing );
        //leave since argument is improper
        User::Leave (SErrMissingArgument );
        }
    //position to start search in input params
    TInt index = 0;
    //get content type
    const TLiwGenericParam* param = &aInParamList[EIndex0];
    //check whether pos based or value based
    if ( param->Name ( )!= KNullDesC8 )
        {
        param = aInParamList.FindFirst (index, KContentType );
        if ( !param )
            {
            ErrorMessageL (KGetList, KContentType );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }
    TLiwVariant variant(param->Value ( ));
    ValidateParamL (KGetList, KContentType, variant, LIW::EVariantTypeDesC );
    TPtrC contentType(variant.AsDes ( ));

    //Content type is Landmark.
    if ( contentType == KLandmark )
        {
        GetLandmarksL (aInParamList, aOutParamList, aCmdOptions, aCallback );
        }
    //Content type is Category.
    else
        if ( contentType == KCategory )
            {
            GetCategoriesL (aInParamList, aOutParamList, aCmdOptions, aCallback );
            }
        //Content type is Database.
        else
            if ( contentType == KDatabase )
                {
                //Async not supported for databases
                if( !aCallback )
                	GetListDatabasesL (aInParamList, aOutParamList );
              	else
              		{
              		iErrMsg = KAsyncNotSupported().AllocL ( );
                	User::Leave (SErrInvalidServiceArgument );
              		}
                }
            else
                {
                ErrorMessageL (KGetList, KContentType );
                iErrMsg->Des().Append (KInvalid );
                //leave since argument is improper
                User::Leave (SErrInvalidServiceArgument );
                }
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::AddL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint /*aCmdOptions*/,
//                           MLiwNotifyCallback* /*aCallback*/ )
// This function calls the appropriate functions based on the content type.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::AddL( const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList, TUint /*aCmdOptions*/,
        MLiwNotifyCallback* /*aCallback*/)
    {
    //Input param List must have contentType and data specified
    if ( aInParamList.Count ( )< EIndex2 )
        {
        ErrorMessageL (KAdd, KArgsMissing );
        iErrMsg->Des().Append (KMissing );
        //leave since argument is improper
        User::Leave (SErrMissingArgument );
        }

    //position to start search in input params
    TInt index = 0;
    //get content type
    const TLiwGenericParam* param = &aInParamList[EIndex0];
    //check whether pos based or value based
    if ( param->Name ( )!= KNullDesC8 )
        {
        param = aInParamList.FindFirst (index, KContentType );
        if ( !param )
            {
            ErrorMessageL (KAdd, KContentType );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }

    TLiwVariant variant(param->Value ( ));
    ValidateParamL (KAdd, KContentType, variant, LIW::EVariantTypeDesC );
    TPtrC contentType(variant.AsDes ( ));

    //Content type is Landmark
    if ( contentType == KLandmark )
        {
        AddLandmarksL (aInParamList,aOutParamList );
        }
    //Content type is Category.
    else
        if ( contentType == KCategory )
            {
            AddCategoryL (aInParamList,aOutParamList );
            }
        else
            {
            ErrorMessageL (KAdd, KContentType );
            iErrMsg->Des().Append (KInvalid );
            //leave since argument is improper
            User::Leave (SErrInvalidServiceArgument );
            }
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::RemoveL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& /*aOutParamList*/,
//                           TUint /*aCmdOptions*/,
//                           MLiwNotifyCallback* /*aCallback*/ )
// This calls the appropriate service function based on the content type.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::RemoveL( const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& /*aOutParamList*/, TUint /*aCmdOptions*/,
        MLiwNotifyCallback* /*aCallback*/)
    {
    //Input param List must have contentType and data specified
    if ( aInParamList.Count ( )< EIndex2 )
        {
        ErrorMessageL (KAdd, KArgsMissing );
        iErrMsg->Des().Append (KMissing );
        //leave since argument is improper
        User::Leave (SErrMissingArgument );
        }

    //position to start search in input params
    TInt index = 0;
    //Flag for pos based
    TBool posBased = EFalse;
    //get content type
    const TLiwGenericParam* param = &aInParamList[EIndex0];
    //check whether pos based or value based
    if ( param->Name ( )== KNullDesC8 )
        {
        posBased = ETrue;
        }
    else
        {
        param = aInParamList.FindFirst (index, KContentType );
        if ( !param )
            {
            ErrorMessageL (KRemove, KContentType );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }

    TLiwVariant variant(param->Value ( ));
    ValidateParamL (KRemove, KContentType, variant, LIW::EVariantTypeDesC );
    TPtrC contentType(variant.AsDes ( ));

    TPtrC dbUri;
    //Content type is Landmark.
    if ( contentType == KLandmark )
        {
        index = 0;
        if ( posBased )
            {
            param = &aInParamList[EIndex1];
            }
        else
            {
            param = aInParamList.FindFirst (index, KDataFields );
            if ( !param )
                {
                ErrorMessageL (KRemove, KDataFields );
                iErrMsg->Des().Append (KMissing );
                //leave since argument is improper
                User::Leave (SErrMissingArgument );
                }
            }
        variant = param->Value ( );
        ValidateParamL (KRemove, KDataFields, variant, LIW::EVariantTypeMap );
        const CLiwMap* landmarkMap = variant.AsMap ( );
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
        ValidateParamL (KRemove, KId, landmarkMap,
                LIW::EVariantTypeDesC, ETrue, variant );
        TPtrC lmPtr(variant.AsDes ( ));
        TLex lmparseString(lmPtr); //Get Id as string and convert to TUint32
        TPosLmItemId lmid;
        TInt parseErr = lmparseString.Val (lmid, EDecimal );
        TBuf<KMaxIDStringLength> lmIdString(KNullDesC ( ));
        if ( !parseErr )
            {
            lmIdString.Num (lmid );
            }
        if ( parseErr || lmIdString != lmPtr )
            {
            ErrorMessageL (KRemove, KId );
            iErrMsg->Des().Append (KInvalid );
            User::Leave (SErrInvalidServiceArgument );
            }

        if (ValidateParamL (KRemove, KDbUri, landmarkMap,
                LIW::EVariantTypeDesC, EFalse, variant ) )
            {
            dbUri.Set (variant.AsDes ( ) );
            }
        iService->RemoveItemL (lmid, CLandmarkService::ELandmark, dbUri );
        CleanupStack::PopAndDestroy(&variant);
        }
    //Content type is Category.
    else
        if ( contentType == KCategory )
            {
            index = 0;
            if ( posBased )
                {
                param = &aInParamList[EIndex1];
                }
            else
                {
                param = aInParamList.FindFirst (index, KDataFields );
                if ( !param )
                    {
                    ErrorMessageL (KRemove, KDataFields );
                    iErrMsg->Des().Append (KMissing );
                    //leave since argument is improper
                    User::Leave (SErrMissingArgument );
                    }
                }
            variant = param->Value ( );
            ValidateParamL (KRemove, KDataFields, variant, LIW::EVariantTypeMap );
            const CLiwMap* categoryMap = variant.AsMap ( );
            CleanupStack::PushL( 
                    TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
            ValidateParamL (KRemove, KId, categoryMap,
                    LIW::EVariantTypeDesC, ETrue, variant );
            TPtrC catPtr(variant.AsDes ( ));
            TLex catparseString(catPtr); //Get Id as string and convert to TUint32
            TPosLmItemId catid;
            TInt parseErr = catparseString.Val (catid, EDecimal );
            TBuf<KMaxIDStringLength> catIdString(KNullDesC ( ));
            if ( !parseErr )
                {
                catIdString.Num (catid );
                }
            if ( parseErr || catIdString != catPtr )
                {
                ErrorMessageL (KRemove, KId );
                iErrMsg->Des().Append (KInvalid );
                User::Leave (SErrInvalidServiceArgument );
                }

            if (ValidateParamL (KRemove, KDbUri, categoryMap,
                    LIW::EVariantTypeDesC, EFalse, variant ) )
                {
                dbUri.Set (variant.AsDes ( ) );
                }
            iService->RemoveItemL (catid, CLandmarkService::ECategory, dbUri );
            CleanupStack::PopAndDestroy(&variant);
            }
        else
            {
            ErrorMessageL (KRemove, KContentType );
            iErrMsg->Des().Append (KInvalid );
            //leave since argument is improper
            User::Leave (SErrInvalidServiceArgument );
            }
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::ImportL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& /*aOutParamList*/,
//                           TUint /*aCmdOptions*/,
//                           MLiwNotifyCallback* /*aCallback*/ )
// This calls the appropriate service function for importing landmarks.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::ImportL( const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList, TUint /*aCmdOptions*/,
        MLiwNotifyCallback* /*aCallback*/)
    {
    //Input param List must have contentType and importData specified
    if ( aInParamList.Count ( )< EIndex2 )
        {
        ErrorMessageL (KAdd, KArgsMissing );
        iErrMsg->Des().Append (KMissing );
        //leave since argument is improper
        User::Leave (SErrMissingArgument );
        }
    //position to start search in input params
    TInt index = 0;
    //Flag for pos based
    TBool posBased = EFalse;
    //get content type
    const TLiwGenericParam* param = &aInParamList[EIndex0];
    //check whether pos based or value based
    if ( param->Name ( )== KNullDesC8 )
        {
        posBased = ETrue;
        }
    else
        {
        param = aInParamList.FindFirst (index, KContentType );
        if ( !param )
            {
            ErrorMessageL (KImport, KContentType );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }

    TLiwVariant variant(param->Value ( ));
    ValidateParamL (KImport, KContentType, variant, LIW::EVariantTypeDesC );
    TPtrC contentType(variant.AsDes ( ));
    //Content type is Landmark.
    if ( contentType == KLandmark )
        {
        index = 0;
        if ( posBased )
            {
            param = &aInParamList[EIndex1];
            }
        else
            {
            param = aInParamList.FindFirst (index, KDataFields );
            if ( !param )
                {
                ErrorMessageL (KImport, KDataFields );
                iErrMsg->Des().Append (KMissing );
                //leave since argument is improper
                User::Leave (SErrMissingArgument );
                }
            }
        variant = param->Value ( );
        ValidateParamL (KImport, KDataFields, variant, LIW::EVariantTypeMap );
        const CLiwMap* importData = variant.AsMap ( );
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
        ValidateParamL (KImport, KMimeType, importData, LIW::EVariantTypeDesC,
                ETrue, variant );
		if( variant.AsDes() == KNullDesC )
			{
			ErrorMessageL (KImport, KMimeType );
            iErrMsg->Des().Append (KInvalid );
            //leave since argument is improper
            User::Leave (SErrInvalidServiceArgument );
			}
        //Construct the parser
        HBufC8* mimeType8 = 
            CnvUtfConverter::ConvertFromUnicodeToUtf8L ( variant.AsDes ( ) );
        CleanupStack::PushL( mimeType8 );       
        CPosLandmarkParser* parser = CPosLandmarkParser::NewL (*mimeType8 );
        CleanupStack::PushL (parser );

        ValidateParamL (KImport, KSourceFile, importData,
                LIW::EVariantTypeDesC, ETrue, variant );
		if( variant.AsDes() == KNullDesC )
			{
			ErrorMessageL (KImport, KSourceFile );
            iErrMsg->Des().Append (KInvalid );
            //leave since argument is improper
            User::Leave (SErrInvalidServiceArgument );
			}
        parser->SetInputFileL (variant.AsDes ( ) );
        //check if complete file is ok
        CPosLmOperation* op = parser->ParseContentL ( );
        CleanupStack::PushL (op );
        op->ExecuteL ( );
        CleanupStack::PopAndDestroy (op );
        //getdb
        TPtrC dbUri;
        if (ValidateParamL (KImport, KDbUri, importData, LIW::EVariantTypeDesC,
                EFalse, variant ) )
            {
            dbUri.Set (variant.AsDes ( ) );
            }
        CPosLmItemIterator* iterator=  NULL;
        //call the service function for import
        iService->ImportL (iterator, *parser, dbUri );
        CleanupStack::PopAndDestroy (parser );
        CleanupStack::PopAndDestroy (mimeType8 );
        CleanupStack::PushL(iterator);
        // if dbURI is not specified retrieve default databse URI
        if ( dbUri == KNullDesC )
            {
            iService->GetDefaultDbUriL (dbUri );
            }
        //instantiate CLandmarkIterable
        CLiwIterable* iterable = CLandmarkIterable::NewL (iterator, dbUri );
        CleanupStack::Pop(iterator);
        CleanupClosePushL(*iterable);
        aOutParamList.AppendL (TLiwGenericParam (KReturnValue,
                TLiwVariant (iterable ) ) );
        CleanupStack::PopAndDestroy(iterable);
        CleanupStack::PopAndDestroy(&variant);
        }
    else
        {
        ErrorMessageL (KImport, KContentType );
        iErrMsg->Des().Append (KInvalid );
        //leave since argument is improper
        User::Leave (SErrInvalidServiceArgument );
        }
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::ExportL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& /*aOutParamList*/,
//                           TUint /*aCmdOptions*/,
//                           MLiwNotifyCallback* /*aCallback*/ )
// This calls the appropriate service function for exporting landmarks.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::ExportL( const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& /*aOutParamList*/, TUint /*aCmdOptions*/,
        MLiwNotifyCallback* /*aCallback*/)
    {
    //Input param List must have contentType and exportData specified
    if ( aInParamList.Count ( )< EIndex2 )
        {
        ErrorMessageL (KAdd, KArgsMissing );
        iErrMsg->Des().Append (KMissing );
        //leave since argument is improper
        User::Leave (SErrMissingArgument );
        }

    //position to start search in input params
    TInt index = 0;
    //Flag for pos based
    TBool posBased = EFalse;
    //get content type
    const TLiwGenericParam* param = &aInParamList[EIndex0];
    //check whether pos based or value based
    if ( param->Name ( )== KNullDesC8 )
        {
        posBased = ETrue;
        }
    else
        {
        param = aInParamList.FindFirst (index, KContentType );
        if ( !param )
            {
            ErrorMessageL (KExport, KContentType );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }

    TLiwVariant variant(param->Value ( ));
    ValidateParamL (KExport, KContentType, variant, LIW::EVariantTypeDesC );
    TPtrC contentType(variant.AsDes ( ));
    //Content type is Landmark.
    if ( contentType == KLandmark )
        {
        index = 0;
        if ( posBased )
            {
            param = &aInParamList[EIndex1];
            }
        else
            {
            param = aInParamList.FindFirst (index, KDataFields );
            if ( !param )
                {
                ErrorMessageL (KExport, KDataFields );
                iErrMsg->Des().Append (KMissing );
                //leave since argument is improper
                User::Leave (SErrMissingArgument );
                }
            }
        variant = param->Value ( );
        ValidateParamL (KExport, KDataFields, variant, LIW::EVariantTypeMap );
        const CLiwMap* exportData = variant.AsMap ( );
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
        ValidateParamL (KExport, KDestinationFile, exportData,
                LIW::EVariantTypeDesC, ETrue, variant );
		if( variant.AsDes() == KNullDesC )
			{
			ErrorMessageL (KExport, KDestinationFile );
            iErrMsg->Des().Append (KInvalid );
            //leave since argument is improper
            User::Leave (SErrInvalidServiceArgument );
			}
        ValidateParamL (KExport, KMimeType, exportData, LIW::EVariantTypeDesC,
                ETrue, variant );
		if( variant.AsDes() == KNullDesC )
			{
			ErrorMessageL (KExport, KMimeType );
            iErrMsg->Des().Append (KInvalid );
            //leave since argument is improper
            User::Leave (SErrInvalidServiceArgument );
			}
        //instantiate CPosLandmarkEncoder based on mime type.
        HBufC8* mimeType8 = 
            CnvUtfConverter::ConvertFromUnicodeToUtf8L ( variant.AsDes ( ) );
        CleanupStack::PushL( mimeType8 );       
        CPosLandmarkEncoder* encoder = CPosLandmarkEncoder::NewL ( *mimeType8 );
        CleanupStack::PushL (encoder );
        CBufBase* exportBuffer = encoder->SetUseOutputBufferL();
        CleanupStack::PushL(exportBuffer);
        ValidateParamL (KExport, KIdList, exportData,
                LIW::EVariantTypeList, ETrue, variant );
        const CLiwList* lmList = variant.AsList ( );
        TInt lmcount = lmList->Count ( );
        if ( !lmcount )
            {
            ErrorMessageL (KExport, KIdList );
            iErrMsg->Des().Append (KEmpty );
            //leave since argument is improper
            User::Leave (KErrNotFound );
            }
        //array of landmark ids to be exported.
        RArray<TPosLmItemId> landmarkIdArray;
        CleanupClosePushL (landmarkIdArray );
        for (TInt index = 0; index < lmcount; ++index )
            {
            if ( lmList->AtL (index, variant ) )
                {
                ValidateParamL (KExport, KId, variant,
                        LIW::EVariantTypeDesC );
                TPtrC lmPtr(variant.AsDes ( ));
                TLex lmparseString(lmPtr); //Get Id as string and convert to TUint32
                TPosLmItemId lmid;
                TInt parseErr = lmparseString.Val (lmid, EDecimal );

                TBuf<KMaxIDStringLength> lmIdString(KNullDesC ( ));
                if ( !parseErr )
                    {
                    lmIdString.Num (lmid );
                    }
                if ( parseErr || lmIdString != lmPtr )
                    {
                    ErrorMessageL (KExport, KId );
                    iErrMsg->Des().Append (KInvalid );
                    User::Leave (SErrInvalidServiceArgument );
                    }
                landmarkIdArray.AppendL (lmid );
                }
            }
        TPtrC dbUri;
        if (ValidateParamL (KExport, KDbUri, exportData, LIW::EVariantTypeDesC,
                EFalse, variant ) )
            {
            dbUri.Set (variant.AsDes ( ) );
            }
        iService->ExportL (*encoder, landmarkIdArray, dbUri );
        ExecuteAndDeleteLD (encoder->FinalizeEncodingL ( ) );
        //Write to file
        ValidateParamL (KExport, KDestinationFile, exportData,
                        LIW::EVariantTypeDesC, ETrue, variant );
        RFs fs;
        User::LeaveIfError(fs.Connect());
        CleanupClosePushL(fs);
        RFile file;
        CleanupClosePushL(file);
        User::LeaveIfError(file.Create(fs, variant.AsDes(), 
                EFileShareExclusive | EFileStreamText | EFileWrite));
        TInt size = exportBuffer->Size();
        for( TInt i = 0; i < size; ++i )
            {
            file.Write(i,exportBuffer->Ptr(i));
            }
        CleanupStack::PopAndDestroy(&file);
        CleanupStack::PopAndDestroy(&fs);
        CleanupStack::PopAndDestroy (&landmarkIdArray );
        CleanupStack::PopAndDestroy (exportBuffer);
        CleanupStack::PopAndDestroy (encoder );
        CleanupStack::PopAndDestroy (mimeType8 );
        CleanupStack::PopAndDestroy(&variant);
        }
    else
        {
        ErrorMessageL (KExport, KContentType );
        iErrMsg->Des().Append (KInvalid );
        //leave since argument is improper
        User::Leave (SErrInvalidServiceArgument );
        }
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::OrganiseL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& /*aOutParamList*/,
//                           TUint /*aCmdOptions*/,
//                           MLiwNotifyCallback* /*aCallback*/ )
// This calls the appropriate service function for organising landmarks.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::OrganiseL( const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& /*aOutParamList*/, TUint /*aCmdOptions*/,
        MLiwNotifyCallback* /*aCallback*/)
    {
    //Input param List must have contentType, filter and operationType specified
    if ( aInParamList.Count ( )< EIndex3 )
        {
        ErrorMessageL (KAdd, KOrganiseArgsMissing );
        iErrMsg->Des().Append (KMissing );
        //leave since argument is improper
        User::Leave (SErrMissingArgument );
        }
    //position to start search in input params
    TInt index = 0;
    //Flag for pos based
    TBool posBased = EFalse;
    //get content type
    const TLiwGenericParam* param = &aInParamList[EIndex0];
    //check whether pos based or value based
    if ( param->Name ( )== KNullDesC8 )
        {
        posBased = ETrue;
        }
    else
        {
        param = aInParamList.FindFirst (index, KContentType );
        if ( !param )
            {
            ErrorMessageL (KOrganise, KContentType );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }

    TLiwVariant variant(param->Value ( ));
    ValidateParamL (KOrganise, KContentType, variant, LIW::EVariantTypeDesC );
    TPtrC contentType(variant.AsDes ( ));

    //Content type is Landmark
    if ( contentType == KLandmark )
        {
        index = 0;
        if ( posBased )
            {
            param = &aInParamList[EIndex1];
            }
        else
            {
            param = aInParamList.FindFirst (index, KDataFields );
            if ( !param )
                {
                ErrorMessageL (KOrganise, KDataFields );
                iErrMsg->Des().Append (KMissing );
                //leave since argument is improper
                User::Leave (SErrMissingArgument );
                }
            }
        variant = param->Value ( );
        ValidateParamL (KOrganise, KDataFields, variant, LIW::EVariantTypeMap );
        const CLiwMap* filter = variant.AsMap ( );
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
        ValidateParamL (KOrganise, KId, filter, LIW::EVariantTypeDesC,
                ETrue, variant );
        TPtrC catPtr(variant.AsDes ( ));
        TLex catparseString(catPtr); //Get Id as string and convert to TUint32
        TPosLmItemId catid;
        TInt parseErr = catparseString.Val (catid, EDecimal );

        TBuf<KMaxIDStringLength> catIdString(KNullDesC ( ));
        if ( !parseErr )
            {
            catIdString.Num (catid );
            }
        if ( parseErr || catIdString != catPtr )
            {
            ErrorMessageL (KOrganise, KId );
            iErrMsg->Des().Append (KInvalid );
            User::Leave (SErrInvalidServiceArgument );
            }
        ValidateParamL (KOrganise, KIdList, filter,
                LIW::EVariantTypeList, ETrue, variant );
        const CLiwList* lmList = variant.AsList ( );
        TInt count = lmList->Count ( );
        if ( !count )
            {
            ErrorMessageL (KOrganise, KIdList );
            iErrMsg->Des().Append (KEmpty );
            //leave since argument is improper
            User::Leave (KErrNotFound );
            }
        //array of landmark ids to be organised.
        RArray<TPosLmItemId> landmarkIdArray;
        CleanupClosePushL (landmarkIdArray );
        for (TInt pos = 0; pos < count; ++pos )
            {
            if ( lmList->AtL (pos, variant ) )
                {
                ValidateParamL (KOrganise, KId, variant,
                        LIW::EVariantTypeDesC );
                TPtrC lmPtr(variant.AsDes ( ));
                TLex lmparseString(lmPtr); //Get Id as string and convert to TUint32
                TPosLmItemId lmid;
                TInt parseErr = lmparseString.Val (lmid, EDecimal );

                TBuf<KMaxIDStringLength> lmIdString(KNullDesC ( ));
                if ( !parseErr )
                    {
                    lmIdString.Num (lmid );
                    }
                if ( parseErr || lmIdString != lmPtr )
                    {
                    ErrorMessageL (KOrganise, KId );
                    iErrMsg->Des().Append (KInvalid );
                    User::Leave (SErrInvalidServiceArgument );
                    }
                landmarkIdArray.AppendL (lmid );
                }
            }
        TPtrC dbUri;
        TLiwVariant variantDb;
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup , &variantDb ) );
        if (ValidateParamL (KOrganise, KDbUri, filter, LIW::EVariantTypeDesC,
                EFalse, variantDb ) )
            {
            variantDb.Get (dbUri );
            }
        index = 0;
        if ( posBased )
            {
            //Position based parsing
            param = &aInParamList[EIndex2];
            }
        else
            {
            param = aInParamList.FindFirst (index, KOperationType );
            if ( !param )
                {
                ErrorMessageL (KOrganise, KOperationType );
                iErrMsg->Des().Append (KMissing );
                //leave since argument is improper
                User::Leave (SErrMissingArgument );
                }
            }
        variant = param->Value ( );
        ValidateParamL (KOrganise, KOperationType, variant,
                LIW::EVariantTypeDesC );
        TPtrC operationType = variant.AsDes ( );
        if ( operationType == KAssociate )
            {
            iService->LinkCategoryToLandmarksL (catid, landmarkIdArray, dbUri );
            }
        else
            if ( operationType == KDisassociate )
                {
                iService->UnlinkCategoryToLandmarksL (catid, landmarkIdArray,
                        dbUri );
                }
            else
                {
                ErrorMessageL (KOrganise, KOperationType );
                iErrMsg->Des().Append (KInvalid );
                //leave since argument is improper
                User::Leave (SErrInvalidServiceArgument );
                }
        CleanupStack::PopAndDestroy(&variantDb);
        CleanupStack::PopAndDestroy (&landmarkIdArray );        
        CleanupStack::PopAndDestroy(&variant);
        }
    else
        {
        ErrorMessageL (KOrganise, KContentType );
        iErrMsg->Des().Append (KInvalid );
        //leave since argument is improper
        User::Leave (SErrInvalidServiceArgument );
        }
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::Cancel(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& /*aOutParamList*/,
//                           TUint /*aCmdOptions*/,
//                           MLiwNotifyCallback* aCallback )
// This cancels the ongoing async call.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::Cancel( const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList, TUint /*aCmdOptions*/,
        MLiwNotifyCallback* aCallback )
    {
    //Input param List must have transactionID specified
    if ( aInParamList.Count ( ) )
        {
        //position to start search in input params
        TInt index = 0;
        //get content type
        const TLiwGenericParam* param = &aInParamList[EIndex0];
        //check whether pos based or value based
        if ( param->Name ( )!= KNullDesC8 )
            {
            param = aInParamList.FindFirst (index, KTransactionId );
            if ( !param )
                {
                ErrorMessageL (KCancel, KTransactionId );
                iErrMsg->Des().Append (KMissing );
                //leave since argument is improper
                User::Leave (SErrMissingArgument );
                }
            }

        TLiwVariant variant(param->Value ( ));
        ValidateParamL (KCancel, KTransactionId, variant,
                LIW::EVariantTypeTInt32 );
        TInt32 transactionId = variant.AsTInt32 ( );
        iService->Cancel (transactionId );
        if (!aCallback )
            {
            //retrieve the stored callback if callback not explicitly passed
            aCallback = Callback (transactionId );
            }
        else
            {
            // remove the stored callback since the async request has been cancelled
            Callback (transactionId );
            }
        if ( aCallback )
            {
            TRAP_IGNORE(aCallback->HandleNotifyL(transactionId,KLiwEventCanceled,aOutParamList,aInParamList));
            }
        }
    else
        {
        ErrorMessageL (KCancel, KTransactionId );
        iErrMsg->Des().Append (KMissing );
        User::Leave (SErrMissingArgument );
        }

    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::NewTemplateL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This function calls the appropriate functions based on the content type.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::NewTemplateL(const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList, TUint /*aCmdOptions*/,
        MLiwNotifyCallback* /*aCallback*/)
    {
    //Input param List must have Type specified
    if ( !aInParamList.Count() )
        {
        ErrorMessageL (KNew, KContentType );
        iErrMsg->Des().Append (KMissing );
        //leave since argument is improper
        User::Leave (SErrMissingArgument );
        }
    //position to start search in input params
    TInt index = 0;
    //get content type
    const TLiwGenericParam* param = &aInParamList[EIndex0];
    //check whether pos based or value based
    if ( param->Name ( )!= KNullDesC8 )
        {
        param = aInParamList.FindFirst (index, KContentType );
        if ( !param )
            {
            ErrorMessageL (KNew, KContentType );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }

    TLiwVariant variant(param->Value ( ));
    ValidateParamL (KNew, KContentType, variant, LIW::EVariantTypeDesC );
    TPtrC contentType(variant.AsDes ( ));

    CLiwMap* contentMap = CLiwDefaultMap::NewL ( );
    CleanupClosePushL ( *contentMap );
    //Content type is Landmark.
    if ( contentType == KLandmark )
        {
        contentMap->InsertL (KLandmarkName, TLiwVariant (KNullDesC ) );
        contentMap->InsertL (KLandmarkDesc, TLiwVariant (KNullDesC ) );

        CLiwMap* location = CLiwDefaultMap::NewL ( );
        CleanupClosePushL(*location);
        location->InsertL (KDbUri, TLiwVariant (KNullDesC ) );
        location->InsertL (KLatitude, TLiwVariant (TReal64 (0.0 ) ) );
        location->InsertL (KLongitude, TLiwVariant (TReal64 (0.0 ) ) );
        location->InsertL (KAltitude, TLiwVariant (TReal32 (0.0 ) ) );
        location->InsertL (KHAccuracy, TLiwVariant (TReal32 (0.0 ) ) );
        location->InsertL (KVAccuracy, TLiwVariant (TReal32 (0.0 ) ) );
        //location->InsertL (KTStamp, TLiwVariant (TInt32 (0 ) ) );
        contentMap->InsertL (KLandmarkPosition, TLiwVariant (location ) );
        CleanupStack::PopAndDestroy (location );

        contentMap->InsertL (KCoverageRadius, TLiwVariant (TReal32 (0.0 ) ) );

        CLiwList* categoryInfo = CLiwDefaultList::NewL ( );
        CleanupClosePushL ( *categoryInfo );
        contentMap->InsertL (KCategoryInfo, TLiwVariant (categoryInfo ) );
        CleanupStack::PopAndDestroy (categoryInfo );;

        contentMap->InsertL (KIconFile, TLiwVariant (KNullDesC ) );
        contentMap->InsertL (KIconIndex, TLiwVariant (TInt32 (0 ) ) );
        contentMap->InsertL (KIconMaskIndex,
                TLiwVariant (KPosLmIconMaskNotUsed ) );

        CLiwMap* landmarkFields = CLiwDefaultMap::NewL ( );
        CleanupClosePushL ( *landmarkFields );
        landmarkFields->InsertL (KLandmarkCountry, TLiwVariant (KNullDesC ) );
        landmarkFields->InsertL (KLandmarkAreaCode, TLiwVariant (KNullDesC ) );
        landmarkFields->InsertL (KLandmarkCity, TLiwVariant (KNullDesC ) );
        landmarkFields->InsertL (KLandmarkDistrict, TLiwVariant (KNullDesC ) );
        landmarkFields->InsertL (KLandmarkBuildingName, TLiwVariant (KNullDesC ) );
        landmarkFields->InsertL (KLandmarkStreet, TLiwVariant (KNullDesC ) );
        landmarkFields->InsertL (KLandmarkTelephone, TLiwVariant (KNullDesC ) );
        contentMap->InsertL (KLandmarkFields, TLiwVariant (landmarkFields ) );
        CleanupStack::PopAndDestroy (landmarkFields );
        }
    //Content type is Category.
    else
        if ( contentType == KCategory )
            {
            contentMap->InsertL (KCategoryName, TLiwVariant (KNullDesC ) );
            contentMap->InsertL (KIconFile, TLiwVariant (KNullDesC ) );
            contentMap->InsertL (KIconIndex, TLiwVariant (TInt32 (0 ) ) );
            contentMap->InsertL (KIconMaskIndex,
                    TLiwVariant (KPosLmIconMaskNotUsed ) );
            }
        //Content type is Database.
        else
            if ( contentType == KDatabase )
                {
                contentMap->InsertL (KDbUri, TLiwVariant (KNullDesC ) );
                contentMap->InsertL (KDbName, TLiwVariant (KNullDesC ) );
                }
            else
                {

                //leave since argument is improper
                ErrorMessageL (KNew, KContentType );
                iErrMsg->Des().Append (KInvalid );
                User::Leave (SErrInvalidServiceArgument );
                }

    aOutParamList.AppendL (TLiwGenericParam (KReturnValue,
            TLiwVariant (contentMap ) ) );
	CleanupStack::PopAndDestroy (contentMap );
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::GetLandmarksL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This calls the appropriate service function for retrieving landmarks.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::GetLandmarksL(
        const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList, TUint /*aCmdOptions*/,
        MLiwNotifyCallback* aCallback )
    {
    CLandmarkFilter
            * lmFilter = CLandmarkFilter::NewLC (CLandmarkFilter::ELandmark );
    TLiwVariant variantDb;
    CleanupStack::PushL( 
            TCleanupItem( TLiwVariant::VariantCleanup, &variantDb ) );
    TPtrC dbUri;
    //position to start search in input params
    TInt index = 0;
    //Flag for pos based
    TBool posBased = EFalse;
    //get filter if specified
    const TLiwGenericParam* param=  NULL;
    if ( aInParamList.Count ( )> EIndex1 )
        {
        param = &aInParamList[EIndex1];
        //check whether pos based or value based
        if ( param->Name ( )== KNullDesC8 )
            {
            posBased = ETrue;
            }
        }
    if ( !posBased )
        {
        param = aInParamList.FindFirst (index, KFilter );
        }

    if ( param )
        {
        TLiwVariant variant(param->Value ( ));
        ValidateParamL (KGetList, KFilter, variant, LIW::EVariantTypeMap );
        const CLiwMap* filter = variant.AsMap ( );
        if ( filter->Count ( ) )
            {
            CPosLmCompositeCriteria* criteria = CPosLmCompositeCriteria::NewLC (CPosLmCompositeCriteria::ECompositionAND );
            //for different criteria create and append to composite criteria class.
            CleanupStack::PushL( 
                    TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
            if ( ValidateParamL (KGetList, KLandmarkName, filter,
                    LIW::EVariantTypeDesC, EFalse, variant ) )
                {
                TPtrC name( variant.AsDes ( ) );
                if( name != KNullDesC )
                	{
                	CPosLmTextCriteria* crit = CPosLmTextCriteria::NewLC ( );
                    crit->SetTextL(name);
                    crit->SetAttributesToSearch (CPosLandmark::ELandmarkName );
                    User::LeaveIfError (criteria->AddArgument (crit ) );
                    CleanupStack::Pop (crit );
                	}
                else
                	{
                	//Do whatever is default
                	}
                }
            if ( ValidateParamL (KGetList, KCategoryName, filter,
                    LIW::EVariantTypeDesC, EFalse, variant ) )
                {
                TPtrC name( variant.AsDes( ) );
                if( name != KNullDesC )
                	{
	                CPosLmCategoryCriteria* crit = CPosLmCategoryCriteria::NewLC ( );
	                crit->SetCategoryNameL (name);
	                User::LeaveIfError (criteria->AddArgument (crit ) );
	                CleanupStack::Pop (crit );
                	}
                else
                	{
                	//Do whatever is default
                	}
                }
            if ( ValidateParamL (KGetList, KLandmarkDesc, filter,
                    LIW::EVariantTypeDesC, EFalse, variant ) )
                {
                TPtrC description( variant.AsDes( ) );
                if( description != KNullDesC )
                	{
	                CPosLmTextCriteria* crit = CPosLmTextCriteria::NewLC ( );
	                crit->SetTextL (variant.AsDes ( ) );
	                crit->SetAttributesToSearch (CPosLandmark::EDescription );
	                User::LeaveIfError (criteria->AddArgument (crit ) );
	                CleanupStack::Pop (crit );
                	}
                else
                	{
                	//Do whatever is default
                	}
                }
            if ( ValidateParamL (KGetList, KLandmarkPosition, filter,
                    LIW::EVariantTypeMap, EFalse, variant ) )
                {
                const CLiwMap* position = variant.AsMap ( );
                TReal64 latitude(0);
                TReal64 longitude(0);
                TBool coverageRadiusOption = EFalse;
                ValidateParamL (KGetList, KLatitude, position,
                        LIW::EVariantTypeTReal, ETrue, variant );
                latitude = variant.AsTReal ( );
                ValidateParamL (KGetList, KLongitude, position,
                        LIW::EVariantTypeTReal, ETrue, variant );
                longitude = variant.AsTReal ( );
                if ( ValidateParamL (KGetList, KCoverageRadiusOption, filter,
                        LIW::EVariantTypeTBool, EFalse, variant ) )
                    {
                    coverageRadiusOption = variant.AsTBool ( );
                    }
                CPosLmNearestCriteria* crit = CPosLmNearestCriteria::NewLC (
                        TCoordinate (latitude, longitude ),
                        coverageRadiusOption );
                if ( ValidateParamL (KGetList, KMaximumDistance, filter,
                        LIW::EVariantTypeTReal, EFalse, variant ) )
                    {
                    TReal maxDist = variant.AsTReal ( );
                    if ( maxDist < 0 )
                        {
                        ErrorMessageL (KGetList, KMaximumDistance );
                        iErrMsg->Des().Append (KInvalid );
                        User::Leave (SErrInvalidServiceArgument );
                        }
                    crit->SetMaxDistance (maxDist );
                    }
                User::LeaveIfError (criteria->AddArgument (crit ) );
                CleanupStack::Pop (crit );
                }
            if ( ValidateParamL (KGetList, KBoundedArea, filter,
                    LIW::EVariantTypeMap, EFalse, variant ) )
                {
                const CLiwMap* boundedArea = variant.AsMap ( );
                TReal northLatitude;
                TReal southLatitude;
                TReal eastLongitude;
                TReal westLongitude;
                ValidateParamL (KGetList, KNorthLatitude, boundedArea,
                        LIW::EVariantTypeTReal, ETrue, variant );
                northLatitude = variant.AsTReal ( );
                ValidateParamL (KGetList, KSouthLatitude, boundedArea,
                        LIW::EVariantTypeTReal, ETrue, variant );
                southLatitude = variant.AsTReal ( );
                ValidateParamL (KGetList, KEastLongitude, boundedArea,
                        LIW::EVariantTypeTReal, ETrue, variant );
                eastLongitude = variant.AsTReal ( );
                ValidateParamL (KGetList, KWestLongitude, boundedArea,
                        LIW::EVariantTypeTReal, ETrue, variant );
                westLongitude = variant.AsTReal ( );
                CPosLmAreaCriteria* crit = CPosLmAreaCriteria::NewLC (
                        southLatitude,northLatitude,westLongitude, 
						eastLongitude );
                User::LeaveIfError (criteria->AddArgument (crit ) );
                CleanupStack::Pop (crit );
                }
            if ( ValidateParamL (KGetList, KMaximumMatches, filter,
                    LIW::EVariantTypeTInt32, EFalse, variant ) )
                {
                TInt32 count = variant.AsTInt32 ( );
                if ( count > 0 )
                    {
                    lmFilter->SetMaximumMatches (count );
                    }
                else
                    {
                    ErrorMessageL (KGetList, KMaximumMatches );
                    iErrMsg->Des().Append (KInvalid );
                    //leave since argument is improper
                    User::Leave (SErrInvalidServiceArgument );
                    }
                }
            if ( ValidateParamL (KGetList, KPrevMatchesOnly, filter,
                    LIW::EVariantTypeTBool, EFalse, variant ) )
                {
                lmFilter->SetPreviousMatches (variant.AsTBool ( ) );
                }
            
            CleanupStack::PopAndDestroy(&variant);
            //Set criteria only if it contains one or more criterion
            if ( criteria->NumOfArguments ( ) )
                {
                lmFilter->SetCriteria (criteria );
                CleanupStack::Pop (criteria );
                }
            else
	            {
	            CleanupStack::PopAndDestroy( criteria );
	            }
            
            
            if ( ValidateParamL (KGetList, KDbUri, filter,
                    LIW::EVariantTypeDesC, EFalse, variantDb ) )
                {
                variantDb.Get (dbUri );
                }
            
            }
        }
    param = NULL;
    index = 0;
    if ( posBased && aInParamList.Count ( )> EIndex2 )
        {
        param = &aInParamList[EIndex2];
        }
    if ( !posBased )
        {
        param = aInParamList.FindFirst (index, KSort );
        }
    if ( param )
        {
        TLiwVariant variant(param->Value ( ));
        ValidateParamL (KGetList, KSort, variant, LIW::EVariantTypeMap );
        const CLiwMap* sort = variant.AsMap ( );
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
        if ( ValidateParamL (KGetList, KSortOrder, sort, LIW::EVariantTypeDesC,
                ETrue, variant ) )
            {
            //by default sort is ascending
            if ( variant.AsDes() == KDescending )
                {
                lmFilter->SetLmSortPref (TPosLmSortPref (
                        CPosLandmark::ELandmarkName,
                        TPosLmSortPref::EDescending ) );
                }
            else
                if ( variant.AsDes() != KAscending  && variant.AsDes() != KNullDesC )
                    {
                    ErrorMessageL (KGetList, KSortOrder );
                    iErrMsg->Des().Append (KInvalid );
                    //leave since argument is improper
                    User::Leave (SErrInvalidServiceArgument );
                    }
            }
        CleanupStack::PopAndDestroy(&variant);
        }
    //Async Call
    if ( aCallback )
        {
        //Get the transaction ID
        TInt32 transactionId(aCallback->GetTransactionID ( ));
        CLandmarkCallbackMap* map = new (ELeave) CLandmarkCallbackMap(transactionId,aCallback);
        CleanupStack::PushL (map );
        iCallbackMap.AppendL (map );
        CleanupStack::Pop (map );
        iService->GetListL (transactionId, *lmFilter, dbUri );
        aOutParamList.AppendL (TLiwGenericParam (KTransactionId,
                TLiwVariant (TInt32 (transactionId ) ) ) );
        }
    else //sync call
        {
        CPosLmItemIterator* iterator = NULL;
        iService->GetListL (iterator, *lmFilter, dbUri );
        CleanupStack::PushL (iterator );
        // if dbURI is not specified retrieve default databse URI
        if ( dbUri == KNullDesC )
            {
            iService->GetDefaultDbUriL (dbUri );
            }
        
        //instantiate CLandmarkIterable
        CLiwIterable* iterable = CLandmarkIterable::NewL (iterator, dbUri );
        CleanupStack::Pop (iterator );
        CleanupClosePushL(*iterable);
        //pack to aOutParamList
        aOutParamList.AppendL (TLiwGenericParam (KReturnValue,
                TLiwVariant (iterable ) ) );
        CleanupStack::PopAndDestroy(iterable);
        }
    CleanupStack::PopAndDestroy(&variantDb);
    CleanupStack::PopAndDestroy (lmFilter );
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::GetCategoriesL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This calls the appropriate service function for retrieving landmarks.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::GetCategoriesL(
        const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList, TUint /*aCmdOptions*/,
        MLiwNotifyCallback* aCallback )
    {
    CLandmarkFilter
            * lmFilter = CLandmarkFilter::NewLC (CLandmarkFilter::ECategory );
    TLiwVariant variantDb;
    CleanupStack::PushL( 
            TCleanupItem( TLiwVariant::VariantCleanup, &variantDb ) );
    TPtrC dbUri;
    //position to start search in input params
    TInt index = 0;
    //Flag for pos based
    TBool posBased = EFalse;
    //get filter if specified
    const TLiwGenericParam* param=  NULL;
    if ( aInParamList.Count ( )> EIndex1 )
        {
        param = &aInParamList[EIndex1];
        //check whether pos based or value based
        if ( param->Name ( )== KNullDesC8 )
            {
            posBased = ETrue;
            }
        }
    if ( !posBased )
        {
        param = aInParamList.FindFirst (index, KFilter );
        }

    if ( param )
        {
        TLiwVariant variant(param->Value ( ));
        ValidateParamL (KGetList, KFilter, variant, LIW::EVariantTypeMap );
        const CLiwMap* filter = variant.AsMap ( );

        if ( filter->Count ( ) )
            {
            CleanupStack::PushL( 
                    TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
            if ( ValidateParamL (KGetList, KCategoryName, filter,
                    LIW::EVariantTypeDesC, EFalse, variant ) )
                {
                TPtrC name( variant.AsDes ( ) );
                if( name != KNullDesC )
                	{
	                CPosLmCatNameCriteria* criteria = CPosLmCatNameCriteria::NewLC ( );
	                criteria->SetSearchPatternL (variant.AsDes ( ) );
	                lmFilter->SetCriteria (criteria );
	                CleanupStack::Pop (criteria );
                	}
                }
            if ( ValidateParamL (KGetList, KMaximumMatches, filter,
                    LIW::EVariantTypeTInt32, EFalse, variant ) )
                {
                TInt32 count = variant.AsTInt32 ( );
                if ( count > 0 )
                    {
                    lmFilter->SetMaximumMatches (count );
                    }
                else
                    {
                    ErrorMessageL (KGetList, KMaximumMatches );
                    iErrMsg->Des().Append (KInvalid );
                    //leave since argument is improper
                    User::Leave ( SErrInvalidServiceArgument );
                    }
                }
            if ( ValidateParamL (KGetList, KPrevMatchesOnly, filter,
                    LIW::EVariantTypeTBool, EFalse, variant ) )
                {
                lmFilter->SetPreviousMatches (variant.AsTBool ( ) );
                }
            if ( ValidateParamL (KGetList, KDbUri, filter,
                    LIW::EVariantTypeDesC, EFalse, variantDb ) )
                {
                variantDb.Get (dbUri );
                }
            CleanupStack::PopAndDestroy(&variant);
            }
        }

    param = NULL;
    index = 0;
    if ( posBased && aInParamList.Count ( )> EIndex2 )
        {
        param = &aInParamList[EIndex2];
        }
    if ( !posBased )
        {
        param = aInParamList.FindFirst (index, KSort );
        }

    if ( param )
        {
        TLiwVariant variant(param->Value ( ));
        ValidateParamL (KGetList, KSort, variant, LIW::EVariantTypeMap );
        const CLiwMap* sort = param->Value().AsMap ( );
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
        if ( ValidateParamL (KGetList, KSortOrder, sort, LIW::EVariantTypeDesC,
                ETrue, variant ) )
            {
            TPtrC sortOrder = variant.AsDes ( );
            if ( sortOrder == KDescending )
                {
                lmFilter->SetCatSortPref (CPosLmCategoryManager::ECategorySortOrderNameDescending );
                }
            else
                if ( sortOrder == KAscending )
                    {
                    lmFilter->SetCatSortPref (CPosLmCategoryManager::ECategorySortOrderNameAscending );
                    }
                else
                    {
                    ErrorMessageL (KGetList, KSortOrder );
                    iErrMsg->Des().Append (KInvalid );
                    //leave since argument is improper
                    User::Leave (SErrInvalidServiceArgument );
                    }
            }
        CleanupStack::PopAndDestroy(&variant);
        }

    //Async Call
    if ( aCallback )
        {
        //Get the transaction ID
        TInt32 transactionId(aCallback->GetTransactionID ( ));
        CLandmarkCallbackMap* map = new (ELeave) CLandmarkCallbackMap(transactionId,aCallback);
        CleanupStack::PushL (map );
        iCallbackMap.AppendL (map );
        CleanupStack::Pop (map );
        iService->GetListL (transactionId, *lmFilter, dbUri );

        aOutParamList.AppendL (TLiwGenericParam (KTransactionId,
                TLiwVariant (TInt32 (transactionId ) ) ) );
        }
    else //sync call
        {
        CPosLmItemIterator* iterator = NULL;
        iService->GetListL (iterator, *lmFilter, dbUri );
        CleanupStack::PushL (iterator );
        // if dbURI is not specified retrieve default databse URI
        if ( dbUri == KNullDesC )
            {
            iService->GetDefaultDbUriL (dbUri );
            }
        
        //instantiate CLandmarkIterable
        CLiwIterable* iterable = CLandmarkCategoryIterable::NewL (iterator,
                dbUri );
        CleanupStack::Pop (iterator );
        CleanupClosePushL (*iterable );
        //pack to aOutParamList
        aOutParamList.AppendL (TLiwGenericParam (KReturnValue,
                TLiwVariant (iterable ) ) );
        CleanupStack::PopAndDestroy(iterable);
        }
    CleanupStack::PopAndDestroy(&variantDb);
    CleanupStack::PopAndDestroy (lmFilter );
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::GetListDatabasesL(const CLiwGenericParamList& aInParamList
//                CLiwGenericParamList& aOutParamList)
// This calls the appropriate service function for Getting List of
// available Databases.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::GetListDatabasesL(
        const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList )
    {
    CDesCArray* DbList=  NULL;
    //position to start search in input params
    TInt index = 0;
    //Flag for pos based
    TBool posBased = EFalse;
    //get filter if specified
    const TLiwGenericParam* param=  NULL;
    if ( aInParamList.Count ( )> EIndex1 )
        {
        param = &aInParamList[EIndex1];
        //check whether pos based or value based
        if ( param->Name ( )== KNullDesC8 )
            {
            posBased = ETrue;
            }
        }
    if ( !posBased )
        {
        param = aInParamList.FindFirst (index, KFilter );
        }
    if ( !param )
        {
        iService->GetListL (DbList );
        }
    else
        {
        TLiwVariant variant(param->Value ( ));
        ValidateParamL (KGetList, KFilter, variant, LIW::EVariantTypeMap );
        const CLiwMap* CriteriaMap = variant.AsMap ( );
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
        if ( ValidateParamL (KGetList, KDbProtocol, CriteriaMap,
                LIW::EVariantTypeDesC, ETrue, variant ) )
            {
            iService->GetListL (DbList, variant.AsDes ( ) );
            }
        else
            {
            iService->GetListL (DbList );
            }
        CleanupStack::PopAndDestroy(&variant);
        }
    CleanupStack::PushL (DbList );
 	param = NULL;
    index = 0;
    if ( posBased && aInParamList.Count ( )> EIndex2 )
        {
        param = &aInParamList[EIndex2];
        }
    if ( !posBased )
        {
        param = aInParamList.FindFirst (index, KSort );
        }

    if ( param )
        {
        TLiwVariant variant(param->Value ( ));
        ValidateParamL (KGetList, KSort, variant, LIW::EVariantTypeMap );
        const CLiwMap* sort = param->Value().AsMap ( );
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
        if ( ValidateParamL (KGetList, KSortOrder, sort, LIW::EVariantTypeDesC,
                ETrue, variant ) )
            {
            TPtrC sortOrder = variant.AsDes ( );
            TBool compare = EFalse;
            if ( sortOrder == KDescending )
                {
                index = DbList->Count();
                for(TInt i = 0 ; i<index ; i++)
	                {
	                compare = EFalse;
                	for(TInt j = 0; j<(index-1); j++ )
	                	{
	                	TPtrC temp1(DbList->MdcaPoint(j));
	                	TPtrC temp2(DbList->MdcaPoint(j+1));
                		if(temp1.Compare(temp2) < 1 )
	                		{
                			DbList->InsertL(j,temp2);
                			DbList->InsertL(j+1,temp1);
                			DbList->Delete(j+2,2);
                			DbList->Compress();
                			compare = ETrue;
	                		}
	                	}
	                if( !compare )
		                {
		                break;	
		                }
	                }
                }
            else
                if ( sortOrder != KAscending )
                    {
                    ErrorMessageL (KGetList, KSortOrder );
                    iErrMsg->Des().Append (KInvalid );
                    //leave since argument is improper
                    User::Leave (SErrInvalidServiceArgument );
                    }
                    else
	                    {
	                    index = DbList->Count();
                		for(TInt i = 0 ; i<index ; i++)
			                {
			                compare = EFalse;
		                	for(TInt j = 0; j<(index-1); j++ )
			                	{
		                		TPtrC temp1(DbList->MdcaPoint(j));
			                	TPtrC temp2(DbList->MdcaPoint(j+1));
		                		if(temp1.Compare(temp2) > 1 )
			                		{
		                			DbList->InsertL(j,temp2);
                					DbList->InsertL(j+1,temp1);
                					DbList->Delete(j+2,2);
                					DbList->Compress();
                					compare = ETrue;
			                		}
			                	}
			                if( !compare )
				                {
				                break;	
				                }	
			                }
	                	}
            }	
        CleanupStack::PopAndDestroy(&variant);
        }
    
    CLiwIterable* iterable = CDatabaseIterable::NewL (DbList );
    CleanupStack::Pop (DbList );
    CleanupClosePushL(*iterable);
    aOutParamList.AppendL (TLiwGenericParam (KReturnValue,
            TLiwVariant (iterable ) ) );
    CleanupStack::PopAndDestroy(iterable);
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::AddLandmarksL(const CLiwGenericParamList& aInParamList )
// This calls the appropriate service function for adding landmarks.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::AddLandmarksL( const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList )
    {
    //position to start search in input params
    TInt index = 0;
    //find if filter is specified
    const TLiwGenericParam* param = &aInParamList[EIndex1];
    if ( param->Name ( )!= KNullDesC8 )
        {
        param = aInParamList.FindFirst (index, KDataFields );
        if ( !param )
            {
            ErrorMessageL (KAdd, KDataFields );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }
    TLiwVariant variant = param->Value ( );
    ValidateParamL (KAdd, KDataFields, variant, LIW::EVariantTypeMap );
    const CLiwMap* dataFields = variant.AsMap ( );
    CPosLandmark* landmark =  NULL;
    TBool update = EFalse;
    TPtrC dbUri;
    TLiwVariant variantDb;
    TPosLmItemId lmid;
    CleanupStack::PushL( 
            TCleanupItem( TLiwVariant::VariantCleanup, &variantDb ) );
    if ( ValidateParamL (KAdd, KDbUri, dataFields, LIW::EVariantTypeDesC,
            EFalse, variantDb ) )
        {
        variantDb.Get (dbUri );
        }
    CleanupStack::PushL( 
            TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
    if ( ValidateParamL (KAdd, KId, dataFields, LIW::EVariantTypeDesC,
            EFalse, variant ) )
        {
        update = ETrue;
        TPtrC lmPtr(variant.AsDes ( ));
        TLex lmparseString(lmPtr); //Get Id as string and convert to TUint32
        TInt parseErr = lmparseString.Val (lmid, EDecimal );
        TBuf<KMaxIDStringLength> lmIdString(KNullDesC ( ));
        if ( !parseErr )
            {
            lmIdString.Num (lmid );
            }
        if ( parseErr || lmIdString != lmPtr )
            {
            ErrorMessageL (KAdd, KId );
            iErrMsg->Des().Append (KInvalid );
            User::Leave (SErrInvalidServiceArgument );
            }
        landmark = iService->LandmarkLC (lmid, dbUri );
        if ( !landmark )
            {
            //leave since landmark not found
            User::Leave (KErrNotFound );
            }
        }
    else
        {
        landmark = CPosLandmark::NewLC ( );
        }
    if ( ValidateParamL (KAdd, KLandmarkName, dataFields,
            LIW::EVariantTypeDesC, EFalse, variant ) )
        {
        landmark->SetLandmarkNameL (variant.AsDes ( ) );
        }
    if ( ValidateParamL (KAdd, KLandmarkPosition, dataFields,
            LIW::EVariantTypeMap, EFalse, variant ) )
        {
        const CLiwMap* location = variant.AsMap ( );
        TLocality locale;
        TReal latitude(0);
        TReal longitude(0);
        ValidateParamL (KAdd, KLatitude, location, LIW::EVariantTypeTReal,
                ETrue, variant );
        latitude = variant.AsTReal ( );
        ValidateParamL (KAdd, KLongitude, location,
                LIW::EVariantTypeTReal, ETrue, variant );
        longitude = variant.AsTReal ( );
        
        if ( ValidateParamL (KAdd, KAltitude, location, LIW::EVariantTypeTReal,
                EFalse, variant ) )
            {
            locale.SetCoordinate (latitude, longitude, variant.AsTReal ( ) );
            }
        else
            {
            locale.SetCoordinate (latitude, longitude );
            }
        if ( ValidateParamL (KAdd, KHAccuracy, location,
                LIW::EVariantTypeTReal, EFalse, variant ) )
            {
            TReal hacc(variant.AsTReal ( ));
            if ( hacc < 0 )
                {
                ErrorMessageL (KAdd, KHAccuracy );
                iErrMsg->Des().Append (KInvalid );
                User::Leave (SErrInvalidServiceArgument );
                }
            locale.SetHorizontalAccuracy (hacc );
            }
        if ( ValidateParamL (KAdd, KVAccuracy, location,
                LIW::EVariantTypeTReal, EFalse, variant ) )
            {
            TReal vacc(variant.AsTReal ( ));
            if ( vacc < 0 )
                {
                ErrorMessageL (KAdd, KVAccuracy );
                iErrMsg->Des().Append (KInvalid );
                User::Leave (SErrInvalidServiceArgument );
                }
            locale.SetVerticalAccuracy (vacc );
            }
        landmark->SetPositionL (locale );
        }
    if ( ValidateParamL (KAdd, KCoverageRadius, dataFields,
            LIW::EVariantTypeTReal, EFalse, variant ) )
        {
        TReal covRad = variant.AsTReal ( );
        if ( covRad < 0 )
            {
            ErrorMessageL (KAdd, KCoverageRadius );
            iErrMsg->Des().Append (KInvalid );
            User::Leave (SErrInvalidServiceArgument );
            }
        landmark->SetCoverageRadius (covRad );
        }
    if ( ValidateParamL (KAdd, KCategoryInfo, dataFields,
            LIW::EVariantTypeList, EFalse, variant ) )
        {
        const CLiwList* category = variant.AsList ( );
        TInt count = category->Count ( );
        for (TInt index = 0; index < count; ++index )
            {
            if ( category->AtL (index, variant ) )
                {
                ValidateParamL (KAdd, KId, variant,
                        LIW::EVariantTypeDesC );
                TPtrC catPtr(variant.AsDes ( ));
                TLex catparseString(catPtr); //Get Id as string and convert to TUint32
                TPosLmItemId catid;
                TInt parseErr = catparseString.Val (catid, EDecimal );
                TBuf<KMaxIDStringLength> catIdString(KNullDesC ( ));
                if ( !parseErr )
                    {
                    catIdString.Num (catid );
                    }
                if ( parseErr || catIdString != catPtr )
                    {
                    ErrorMessageL (KAdd, KId );
                    iErrMsg->Des().Append (KInvalid );
                    User::Leave (SErrInvalidServiceArgument );
                    }
                landmark->AddCategoryL (catid );
                }
            }
        }
    if ( ValidateParamL (KAdd, KIconFile, dataFields, LIW::EVariantTypeDesC,
            EFalse, variant ) )
        {
        TPtrC iconFile = variant.AsDes ( );
        if ( iconFile == KNullDesC )
            {
            ErrorMessageL (KAdd, KIconFile );
            iErrMsg->Des().Append (KInvalid );
            User::Leave (SErrInvalidServiceArgument );
            }
        TLiwVariant iconVariant;
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &iconVariant ) );
        ValidateParamL (KAdd, KIconIndex, dataFields, LIW::EVariantTypeTInt32,
                ETrue, iconVariant );
        TInt32 iconIndex = iconVariant.AsTInt32 ( );
        if ( iconIndex < 0 )
            {
            ErrorMessageL (KAdd, KIconIndex );
            iErrMsg->Des().Append (KInvalid );
            User::Leave (SErrInvalidServiceArgument );
            }
        TInt32 iconMaskIndex = KPosLmIconMaskNotUsed;
        if ( ValidateParamL (KAdd, KIconMaskIndex, dataFields,
                LIW::EVariantTypeTInt32, ETrue, iconVariant ) )
            {
            iconMaskIndex = iconVariant.AsTInt32 ( );
            if ( iconMaskIndex < KPosLmIconMaskNotUsed )
                {
                ErrorMessageL (KAdd, KIconMaskIndex );
                iErrMsg->Des().Append (KInvalid );
                User::Leave (SErrInvalidServiceArgument );
                }
            }
        landmark->SetIconL (iconFile, iconIndex, iconMaskIndex );
        CleanupStack::PopAndDestroy(&iconVariant);
        }
    if ( ValidateParamL (KAdd, KLandmarkDesc, dataFields,
            LIW::EVariantTypeDesC, EFalse, variant ) )
        {
        landmark->SetLandmarkDescriptionL (variant.AsDes ( ) );
        }
    if ( ValidateParamL (KAdd, KLandmarkFields, dataFields,
            LIW::EVariantTypeMap, EFalse, variant ) )
        {
        const CLiwMap* lmFields = variant.AsMap ( );
        if ( ValidateParamL (KAdd, KLandmarkCountry, lmFields,
                LIW::EVariantTypeDesC, EFalse, variant ) )
            {
            landmark->SetPositionFieldL (EPositionFieldCountry,
                    variant.AsDes ( ) );
            }
        if ( ValidateParamL (KAdd, KLandmarkAreaCode, lmFields,
                LIW::EVariantTypeDesC, EFalse, variant ) )
            {
            landmark->SetPositionFieldL (EPositionFieldPostalCode,
                    variant.AsDes ( ) );
            }
        if ( ValidateParamL (KAdd, KLandmarkCity, lmFields,
                LIW::EVariantTypeDesC, EFalse, variant ) )
            {
            landmark->SetPositionFieldL (EPositionFieldCity, variant.AsDes ( ) );
            }
        if ( ValidateParamL (KAdd, KLandmarkDistrict, lmFields,
                LIW::EVariantTypeDesC, EFalse, variant ) )
            {
            landmark->SetPositionFieldL (EPositionFieldDistrict,
                    variant.AsDes ( ) );
            }
        if ( ValidateParamL (KAdd, KLandmarkBuildingName, lmFields,
                LIW::EVariantTypeDesC, EFalse, variant ) )
            {
            landmark->SetPositionFieldL (EPositionFieldBuildingName,
                    variant.AsDes ( ) );
            }
        if ( ValidateParamL (KAdd, KLandmarkStreet, lmFields,
                LIW::EVariantTypeDesC, EFalse, variant ) )
            {
            landmark->SetPositionFieldL (EPositionFieldStreet, variant.AsDes ( ) );
            }
        if ( ValidateParamL (KAdd, KLandmarkTelephone, lmFields,
                LIW::EVariantTypeDesC, EFalse, variant ) )
            {
            landmark->SetPositionFieldL (EPositionFieldBuildingTelephone,
                    variant.AsDes ( ) );
            }
        }
    //checks if the landmark passed is to update an existing lanmark or add a
    //new landmark.
    if ( update )
        {
        iService->UpdateItemL (*landmark, dbUri );
        }
    else
        {
        lmid = iService->AddItemL (*landmark, dbUri );
        }
    CleanupStack::PopAndDestroy (landmark );
    CleanupStack::PopAndDestroy(&variant);
    CleanupStack::PopAndDestroy(&variantDb);
    
    iId = HBufC::NewL(KMaxIDStringLength);
    iId->Des().Num(lmid,EDecimal);
    aOutParamList.AppendL (TLiwGenericParam (KReturnValue,
            TLiwVariant (iId ) ) );
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::AddCategoryL(const CLiwGenericParamList& aInParamList)
// This calls the appropriate service function for adding a category.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::AddCategoryL(const CLiwGenericParamList& aInParamList,
        CLiwGenericParamList& aOutParamList )
    {
    //position to start search in input params
    TInt index = 0;
    //find if filter is specified
    const TLiwGenericParam* param = &aInParamList[EIndex1];
    if ( param->Name ( )!= KNullDesC8 )
        {
        param = aInParamList.FindFirst (index, KDataFields );
        if ( !param )
            {
            ErrorMessageL (KAdd, KDataFields );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }
    TLiwVariant variant = param->Value ( );
    ValidateParamL (KAdd, KDataFields, variant, LIW::EVariantTypeMap );
    const CLiwMap* dataFields = variant.AsMap ( );
    CPosLandmarkCategory* category=  NULL;
    TBool update = EFalse;
    TPtrC dbUri;
    TLiwVariant variantDb;
    TPosLmItemId catid;
    CleanupStack::PushL( 
            TCleanupItem( TLiwVariant::VariantCleanup, &variantDb ) );
    if ( ValidateParamL (KAdd, KDbUri, dataFields, LIW::EVariantTypeDesC,
            EFalse, variantDb ) )
        {
        variantDb.Get (dbUri );
        }
    CleanupStack::PushL( 
            TCleanupItem( TLiwVariant::VariantCleanup, &variant ) );
    /*if ( ValidateParamL (KAdd, KGlobalCategory, dataFields,
            LIW::EVariantTypeDesC, EFalse, variant ) )
        {
        ErrorMessageL (KAdd, KGlobalCategory );
        iErrMsg->Des().Append (KInvalid );
        //leave since argument is improper
        User::Leave (SErrInvalidServiceArgument );
        }*/
    if ( ValidateParamL (KAdd, KId, dataFields, LIW::EVariantTypeDesC,
            EFalse, variant ) )
        {
        update = ETrue;
        TPtrC catPtr(variant.AsDes ( ));
        TLex catparseString(catPtr); //Get Id as string and convert to TUint32
        TInt parseErr = catparseString.Val (catid, EDecimal );

        TBuf<KMaxIDStringLength> catIdString(KNullDesC ( ));
        if ( !parseErr )
            {
            catIdString.Num (catid );
            }
        if ( parseErr || catIdString != catPtr )
            {
            ErrorMessageL (KAdd, KId );
            iErrMsg->Des().Append (KInvalid );
            User::Leave (SErrInvalidServiceArgument );
            }
        category = iService->CategoryLC (catid, dbUri );
        if ( !category )
            {
            //leave since landmark not found
            User::Leave (KErrNotFound );
            }
        }
    else
        {
        category = CPosLandmarkCategory::NewLC ( );
        }
    ValidateParamL (KAdd, KCategoryName, dataFields, LIW::EVariantTypeDesC,
            ETrue, variant );
    category->SetCategoryNameL (variant.AsDes ( ) );
    if ( ValidateParamL (KAdd, KIconFile, dataFields, LIW::EVariantTypeDesC,
            EFalse, variant ) )
        {
        TPtrC iconFile = variant.AsDes ( );
        if ( iconFile == KNullDesC )
            {
            ErrorMessageL (KAdd, KIconFile );
            iErrMsg->Des().Append (KInvalid );
            User::Leave (SErrInvalidServiceArgument );
            }
        TLiwVariant iconVariant;
        CleanupStack::PushL( 
                TCleanupItem( TLiwVariant::VariantCleanup, &iconVariant ) );
        ValidateParamL (KAdd, KIconIndex, dataFields, LIW::EVariantTypeTInt32,
                ETrue, iconVariant );
        TInt32 iconIndex = iconVariant.AsTInt32 ( );
        if ( iconIndex < 0 )
            {
            ErrorMessageL (KAdd, KIconIndex );
            iErrMsg->Des().Append (KInvalid );
            User::Leave (SErrInvalidServiceArgument );
            }
        TInt32 iconMaskIndex = KPosLmIconMaskNotUsed;
        if ( ValidateParamL (KAdd, KIconMaskIndex, dataFields,
                LIW::EVariantTypeTInt32, ETrue, iconVariant ) )
            {
            iconMaskIndex = iconVariant.AsTInt32 ( );
            if ( iconMaskIndex < KPosLmIconMaskNotUsed )
                {
                ErrorMessageL (KAdd, KIconMaskIndex );
                iErrMsg->Des().Append (KInvalid );
                User::Leave (SErrInvalidServiceArgument );
                }
            }
        category->SetIconL (iconFile, iconIndex, iconMaskIndex );
        CleanupStack::PopAndDestroy(&iconVariant);
        }

    if ( update )
        {
        iService->UpdateItemL (*category, dbUri );
        }
    else
        {
        catid = iService->AddItemL (*category, dbUri );
        }

    CleanupStack::PopAndDestroy (category );
    CleanupStack::PopAndDestroy(&variant);
    CleanupStack::PopAndDestroy(&variantDb);
    
    iId = HBufC::NewL(KMaxIDStringLength);
    iId->Des().Num(catid,EDecimal);
    aOutParamList.AppendL (TLiwGenericParam (KReturnValue,
            TLiwVariant (iId ) ) );
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::AddDatabaseL(const CLiwGenericParamList& aInParamList)
// This calls the appropriate service function for adding a database.
// ---------------------------------------------------------------------------
//
void CLandmarkInterface::AddDatabaseL(const CLiwGenericParamList& aInParamList )
    {
    //position to start search in input params
    TInt index = 0;
    //find if filter is specified
    const TLiwGenericParam* param = &aInParamList[EIndex1];
    if ( param->Name ( )!= KNullDesC8 )
        {
        param = aInParamList.FindFirst (index, KDataFields );
        if ( !param )
            {
            ErrorMessageL (KAdd, KDataFields );
            iErrMsg->Des().Append (KMissing );
            //leave since argument is improper
            User::Leave (SErrMissingArgument );
            }
        }
    TLiwVariant variant = param->Value ( );
    ValidateParamL (KAdd, KDataFields, variant, LIW::EVariantTypeMap );
    const CLiwMap* dataFields = variant.AsMap ( );
    TLiwVariant dbname;
    TLiwVariant dburi;
    CleanupStack::PushL( 
            TCleanupItem( TLiwVariant::VariantCleanup, &dburi ) );
    ValidateParamL (KAdd, KDbUri, dataFields, LIW::EVariantTypeDesC, ETrue,
            dburi );
    TRAPD(err,iService->AddItemL (dburi.AsDes()));
    if ( err && (err != KErrAlreadyExists) )
        {
        User::Leave (err );
        }
    //existing database will be updated.
    CleanupStack::PushL( 
            TCleanupItem( TLiwVariant::VariantCleanup, &dbname ) );
    if ( ValidateParamL (KAdd, KDbName, dataFields, LIW::EVariantTypeDesC,
            EFalse, dbname ) )
        {
        TPosLmDatabaseSettings settings;
        TPosLmDatabaseName name(dbname.AsDes ( ));
        settings.SetDatabaseName (name );
        iService->UpdateItemL (settings, dburi.AsDes ( ) );
        }
    CleanupStack::PopAndDestroy(&dbname);
    CleanupStack::PopAndDestroy(&dburi);
    }

void CLandmarkInterface::ErrorMessageL( const TDesC8& aServiceCmd,
        const TDesC8& aKey )
    {
    iErrMsg = HBufC::NewL (KMaxMsgSize );
    *iErrMsg = KModule ( );
    TPtr ptr(iErrMsg->Des ( ));
    TBuf<KMaxKeySize> buf;
    buf.Copy (aServiceCmd );
    ptr.Append (buf );
    ptr.Append (KColon ( ) );
    buf.Copy (aKey );
    ptr.Append (buf );
    }

void CLandmarkInterface::ValidateParamL( const TDesC8& aServiceCmd,
        const TDesC8& aKey, const TLiwVariant& aVariant,
        LIW::TVariantTypeId aType )
    {
    if ( aVariant.TypeId ( )!= aType )
        {
        //Number handling relaxation 
        if( !(LIW::EVariantTypeTReal == aType && LIW::EVariantTypeTInt32 == aVariant.TypeId ()) )
		    {
	        ErrorMessageL ( aServiceCmd, aKey );
	        TPtr ptr(iErrMsg->Des ( ));
	        ptr.Append (KInvalid ( ) );
	        User::Leave (KErrArgument );
		    }
        }
    }

TBool CLandmarkInterface::ValidateParamL( const TDesC8& aServiceCmd,
        const TDesC8& aKey, const CLiwMap* aMap, LIW::TVariantTypeId aType,
        TBool isMandatory, TLiwVariant& aOutVariant )
    {
    TBool status = ETrue;
    TBool present = aMap->FindL (aKey, aOutVariant );
    if ( !present && isMandatory )
        {
        ErrorMessageL ( aServiceCmd, aKey );
        TPtr ptr(iErrMsg->Des ( ));
        ptr.Append (KMissing ( ) );
        User::Leave (SErrMissingArgument );
        }
    else
        if ( !present && !isMandatory )
            {
            status = EFalse;
            }
    if ( status )
        {
        ValidateParamL (aServiceCmd, aKey, aOutVariant, aType );
        }
    return status;
    }

//end of file
