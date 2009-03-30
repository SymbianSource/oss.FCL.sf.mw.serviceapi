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
* Description:  CSysinfoInterface class implementation
*
*/

//INCLUDES
#include <e32math.h>
#include <liwcommon.h>
#include <liwgenericparam.h> 
#include <NumberConversion.h>
#include <PtiEngine.h>

#include "errormsgs.h"
#include "sysinfointerface.h"
#include "sysinfoservice.h"
#include "sysinfoobserver.h"
#include "../../inc/serviceerrno.h"
#include "sysinfoaiwparams.hrh"
#include "sysinfocallbackmap.h"
#include "sysinfolists.h"


using namespace LIW;
using namespace sysinfoaiwparams;

const TUint KMax64BitNumLen(24);
const TInt  KMaxVersionTxt = 10;
const TInt  KMinArgumentCount = 2;
const TInt  KMaxCommandName = 32;

_LIT(KDriveSeperator,":\\");
const TInt KMaxDriveLength = 5;

// ============================ MEMBER FUNCTIONS =============================

// ---------------------------------------------------------------------------
// CSysInfoInterface::NewL()
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CSysInfoInterface* CSysInfoInterface::NewL()
    {
    CSysInfoInterface* self = new (ELeave) CSysInfoInterface();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// ---------------------------------------------------------------------------
// CSysInfoInterface::~CSysInfoInterface()
// Destructor.
// ---------------------------------------------------------------------------
//
CSysInfoInterface::~CSysInfoInterface()
    {
    delete iService;
    delete iObserver;        
    TInt count = iCallbackMap.Count();
    for ( TInt i = 0; i < count; ++i )
        {
        delete(iCallbackMap[i]);
        }
    iCallbackMap.Close();
    }

// ---------------------------------------------------------------------------
// CSysInfoInterface::CSysInfoInterface()
// C++ default constructor can NOT contain any code, that might leave.
// ---------------------------------------------------------------------------
//
CSysInfoInterface::CSysInfoInterface()
    {
    }

// ---------------------------------------------------------------------------
// CLandmarkFilter::ConstructL()
// Symbian 2nd phase constructor can leave.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::ConstructL()
    {
    //instantiate the service class
    iService = CSysInfoService::NewL();
    //instantiate observer to handle async requests.
    iObserver = CSysInfoObserver::NewL(this);
    }

// ---------------------------------------------------------------------------
// CSysInfoInterface::ExecuteCmdL( const TDesC8& aCmdName,
//                           const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This function is called by the user to handle the service commands.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::ExecuteCmdL( const TDesC8& aCmdName,
                                    const CLiwGenericParamList& aInParamList,
                                    CLiwGenericParamList& aOutParamList,
                                    TUint aCmdOptions,
                                    MLiwNotifyCallback* aCallback )
    {
    TInt err(KErrNone);
    iErrBuf.FillZ(0);
    iErrBuf.Append(KModuleName);
    TBuf<KMaxCommandName> CommandName; 
    if( aCmdName.Length() < KMaxCommandName )
        {
        CommandName.Copy( aCmdName ); 
        iErrBuf.Append(CommandName);
        iErrBuf.Append(KColon);

        //check if any of the service API's leave
        TRAP(err,SwitchCmdL(aCmdName,aInParamList,aOutParamList,
        aCmdOptions,aCallback));
        }
    else
        {
        err = SErrInvalidServiceArgument;
        iErrBuf.Append(SErrInvalidServiceArgument);
        }

    TInt SapiErr = SErrNone;
    if (err)
        {
        aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant(iErrBuf)));
        SapiErr = SapiError(err);
        }

    aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiErr)));
    }

// ---------------------------------------------------------------------------
// CSysInfoInterface::SapiError( )
// This function is called by the user to get mapped SAPI generic error code
// from symbian error codes .
// ---------------------------------------------------------------------------
//
TInt CSysInfoInterface::SapiError( TInt aSymbianErr )
    {
    TInt sapiErr(SErrGeneralError);

    switch (aSymbianErr)
        {
        case KErrBadName:			
        case KErrArgument:			
            {
            sapiErr = SErrBadArgumentType;
            break;
            }
        case KErrLanguageNotFound:
        case KErrNotSupported:
            {
            sapiErr = SErrServiceNotSupported;
            break;
            }   		
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
        case KErrPathNotFound:
            {
            sapiErr = SErrPathNotFound;
            break;
            }
        case SErrMissingArgument:
            {
            sapiErr = SErrMissingArgument;
            break;
            }
        case SErrInvalidServiceArgument:
            {
            sapiErr = SErrInvalidServiceArgument;
            break;
            }
        }
    return sapiErr;
    }

// ---------------------------------------------------------------------------
// CSysInfoInterface::Close( )
// This function is called by the user to close the interface.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::Close()
    {
    delete this;
    }

// ---------------------------------------------------------------------------
// CSysInfoInterface::GetCallbackAndRemove( TInt32 aTransactionId )
// This function returns the callback for the given transaction id and 
// removes it from the list.
// ---------------------------------------------------------------------------
//
MLiwNotifyCallback* CSysInfoInterface::GetCallbackAndRemove( TInt32 aTransactionId )
    {
    TInt count = iCallbackMap.Count();
    for ( TInt i = 0; i < count; ++i )
        {
        MLiwNotifyCallback* callback;
        if ( iCallbackMap[i]->Get(aTransactionId,callback) )
            {        		
            delete(iCallbackMap[i]);
            iCallbackMap.Remove(i);
            return callback;
            }        
        }    
    return NULL;
    }

// ---------------------------------------------------------------------------
// CSysInfoInterface::GetCallback( TInt32 aTransactionId )
// This function returns the callback for the given transaction id
// ---------------------------------------------------------------------------
//
MLiwNotifyCallback* CSysInfoInterface::GetCallback( TInt32 aTransactionId )
    {
    TInt count = iCallbackMap.Count();
    for ( TInt i = 0; i < count; ++i )
        {
        MLiwNotifyCallback* callback;
        if ( iCallbackMap[i]->Get(aTransactionId,callback) )
            {        		
            return callback;
            }        
        }
    return NULL;
    }
    
// ---------------------------------------------------------------------------
// CSysInfoInterface::SwitchCmdL( const TDesC8& aCmdName,
//                           const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This function calls the appropriate functions based on the command id.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::SwitchCmdL( const TDesC8& aCmdName,
                                    const CLiwGenericParamList& aInParamList,
                                    CLiwGenericParamList& aOutParamList,
                                    TUint aCmdOptions,
                                    MLiwNotifyCallback* aCallback )
    {
    if ( ( (KLiwOptASyncronous & aCmdOptions) && !aCallback) ||
            ( !((KLiwOptASyncronous|KLiwOptCancel) & aCmdOptions) && aCallback) )

        {
        iErrBuf.Append(KErrInCorrectSyncAsyncRequest);
        User::Leave(KErrArgument);        	
        }

    if ( aCmdName == KCancel && (KLiwOptCancel & aCmdOptions) )
        {
        CancelL (aInParamList, aOutParamList, aCmdOptions, aCallback );
        }
    else if ( !aCmdName.Compare(KGetInfo) )
        {
        GetInfoL(aInParamList,aOutParamList,aCmdOptions,aCallback);
        }
    else if ( !aCmdName.Compare(KSetInfo) )
        {
        if( aCallback )
            {
            iErrBuf.Append(KErrASyncVersionNotSupported);
            User::Leave(KErrArgument);        	
            }
        SetInfoL(aInParamList);
        }
    else if ( !aCmdName.Compare(KGetNotification) )
        {
        if( !aCallback )
            {
            iErrBuf.Append(KErrSyncVersionNotSupported);
            User::Leave(KErrArgument);        	
            }
        GetNotificationL(aInParamList,aOutParamList,aCmdOptions,aCallback);
        }
    else
        {
        // invalid command return error in outparam list
        iErrBuf.Append(KErrCmdNotSupported);
        User::Leave(KErrNotSupported);
        }
    }

// ---------------------------------------------------------------------------
// CSysInfoInterface::SetInfoL( const TDesC8& aCmdName,
//                           const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This function reads input params and calls core class SetInfoL function.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::SetInfoL(const CLiwGenericParamList& aInParamList)
    {
    TPtrC entity,key;
    CSysData* insysdata=NULL;

    ReadInputParamsL(aInParamList,entity,key,insysdata);
    //insysdata must be specified for setinfo operation.
    if(!insysdata)
        {
        iErrBuf.Append(KErrSystemDataMissing);
        User::Leave(SErrMissingArgument);
        }

    CleanupStack::PushL(insysdata);
    iService->SetInfoL(entity,key,insysdata);
    CleanupStack::PopAndDestroy(insysdata);
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::GetInfoL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This function parses input params and calls sync/async version of 
// core class GetInfoL function.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::GetInfoL( const CLiwGenericParamList& aInParamList,
                                        CLiwGenericParamList& aOutParamList, 
                                        TUint /*aCmdOptions*/,
                                        MLiwNotifyCallback* aCallback )
    {
    TPtrC entity,key;
    CSysData* insysdata=NULL;
    //Get entity,key and insysdata.
    ReadInputParamsL(aInParamList,entity,key,insysdata);
    CleanupStack::PushL(insysdata);

    //Async Call
    if ( aCallback )
        {
        //Get the transaction ID
        TInt32 transactionId(aCallback->GetTransactionID());

        CSysInfoCallbackMap* map = new (ELeave) CSysInfoCallbackMap(transactionId,aCallback);
        CleanupStack::PushL(map);
        iCallbackMap.AppendL(map);
        CleanupStack::Pop(map);
        iService->GetInfoL(entity,key,transactionId,iObserver,insysdata);
        aOutParamList.AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(TInt32(transactionId))));
        }
    else
        {
        CSysData* outsysdata = NULL;
        iService->GetInfoL(entity,key,outsysdata,insysdata);
        //after this call outsysdata shouldn't be NULL.
        if(!outsysdata)
            {
            iErrBuf.Append(KErrReadingGetInfo);
            User::Leave(SErrGeneralError);
            }

        CleanupStack::PushL(outsysdata);
        //convert outsysdata into a liwmap.
        CLiwMap* outmapparam=NULL;
        CSysInfoInterface::ConvertSysData2AiwParamL(outsysdata,outmapparam);

        if((outsysdata->DataType() == CSysData::EAccessoryList) || 
            (outsysdata->DataType() == CSysData::EConnectionList))
            CleanupStack::Pop(outsysdata);
        else
            CleanupStack::PopAndDestroy(outsysdata);
        
        CleanupClosePushL(*outmapparam);
        // append entity and key.
        outmapparam->InsertL(KEntity,entity);
        outmapparam->InsertL(KKey,key);
        aOutParamList.AppendL(TLiwGenericParam(KReturnValue,TLiwVariant(outmapparam)));
        CleanupStack::PopAndDestroy(outmapparam);
        }
    CleanupStack::PopAndDestroy(insysdata);
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::GetNotificationL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& aOutParamList,
//                           TUint aCmdOptions,
//                           MLiwNotifyCallback* aCallback )
// This function parses input params and calls core class GetNotificationL 
// function.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::GetNotificationL( const CLiwGenericParamList& aInParamList,
                                            CLiwGenericParamList& aOutParamList, 
                                            TUint /*aCmdOptions*/,
                                            MLiwNotifyCallback* aCallback )
    {
	TPtrC entity,key;
	CSysData* insysdata=NULL;
	
	ReadInputParamsL(aInParamList,entity,key,insysdata);
	CleanupStack::PushL(insysdata);

    //Get the transaction ID
    TInt32 transactionId(aCallback->GetTransactionID());

    CSysInfoCallbackMap* map = new (ELeave) CSysInfoCallbackMap(transactionId,aCallback);
    CleanupStack::PushL(map);
    iCallbackMap.AppendL(map);
    CleanupStack::Pop(map);

    iService->GetNotificationL(entity,key,transactionId,iObserver,insysdata);
    aOutParamList.AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(TInt32(transactionId))));

	CleanupStack::PopAndDestroy(insysdata);
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::ReadInputParamsL(const CLiwGenericParamList& aInParamList,
//                           TPtrC& aEntity,TPtrC& aKey,
//                           const CSysData*& aSysData)
// This function parses input params.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::ReadInputParamsL(const CLiwGenericParamList& aInParamList,
                                        TPtrC& aEntity,TPtrC& aKey,
                                        CSysData*& aSysData)
    {
    aSysData = NULL;
    //position to start search in input params.
    TInt index = 0;
    //Atleast Entity Key must be specified in input list.
    if ( aInParamList.Count() < KMinArgumentCount )
        {
        //leave since argument is improper
        iErrBuf.Append(KErrInsufficientArgs);
        User::Leave(SErrMissingArgument);
        }

    const TLiwGenericParam* param = &aInParamList[EIndex0];

    if ( param->Name() == KNullDesC8 )
        {
        //Position based parsing
        aEntity.Set(aInParamList[EIndex0].Value().AsDes());
        if(!(aEntity.Length()))
            {
            iErrBuf.Append(KErrEntityMissing);
            User::Leave(SErrMissingArgument);
            }

        aKey.Set(aInParamList[EIndex1].Value().AsDes());
        if(!(aKey.Length()))
            {
            iErrBuf.Append(KErrKeyMissing);
            User::Leave(SErrMissingArgument);
            }

        if( aInParamList.Count()>KMinArgumentCount )
            {
            const TLiwGenericParam aInputData = aInParamList[EIndex2]; 
            Convert2SysDataL(aInputData,aSysData);
            }
        }
    else
        {
        //Name based parsing
        //check for Entity.
        index = 0;
        param = aInParamList.FindFirst(index,KEntity);
        if( param )
            {
            aEntity.Set(param->Value().AsDes());
            }
        else
            {
            iErrBuf.Append(KErrEntityMissing);
            User::Leave(SErrMissingArgument);
            }

        //check for Key.
        index = 0;
        param = aInParamList.FindFirst(index,KKey);
        if(param)
            {
            aKey.Set(param->Value().AsDes());
            }
        else
            {
            iErrBuf.Append(KErrKeyMissing);
            User::Leave(SErrMissingArgument);
            }
        //check for SysData.
        index = 0;
        const TLiwGenericParam* aInputData = aInParamList.FindFirst(index,KSysData);
        if(aInputData)
            {
            Convert2SysDataL(*aInputData,aSysData);
            }
        }	
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::Convert2SysDataL(const CLiwGenericParamList& aInParamList,
//                           const CSysData*& aSysData)
// This function converts aiw param to CSysData.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::Convert2SysDataL(const TLiwGenericParam& aInputParam,
                                                            CSysData*& aSysData)
    {
    aSysData = NULL;
    const CLiwMap* inmap = aInputParam.Value().AsMap();

    if( !inmap )
        {
        iErrBuf.Append(KErrSysdataType);
        User::Leave(KErrArgument);
        }

    TLiwVariant indata;
    // check status information.
    if( inmap->FindL(KStatus,indata) )
        {
        if( indata.TypeId() == EVariantTypeTInt32 )
            {
            aSysData = CStatus::NewL(indata.AsTInt32());
            }
        else
            {
            indata.Reset();
            iErrBuf.Append(KErrSystemAttributeValue);
            User::Leave(KErrArgument);
            }
        }
    //check Drive information.
    else if( inmap->FindL(KDriveNo,indata) )
        {
        if( indata.TypeId() == EVariantTypeDesC )
            {
            TPtrC Path;
            indata.Get(Path);

            //expected syntax for drive.
            //[drivename][driveseperator]rest of the path.
            //Ex.c:\\Others
            const TInt KDriveLength(1);

            TInt32 driveno(0);
            TInt offset = Path.Find(KDriveSeperator);
            if ( KErrNotFound == offset )
                {
                iErrBuf.Append(KErrSystemAttributeValue);
                indata.Reset();
                User::Leave(KErrArgument);
                }
            else
                {
                if( offset == KDriveLength )
                    {
                    TPtrC Drive(Path.Left(offset));
                    TChar DriveLetter = Drive[0];
                    if( !DriveLetter.IsAlpha() )
                        {
                        iErrBuf.Append(KErrSystemAttributeValue);
                        indata.Reset();
                        User::Leave(KErrArgument);
                        }
                    DriveLetter.GetUpperCase();
                    driveno = DriveLetter.GetUpperCase() - 'A';
                    }
                else
                    {
                    iErrBuf.Append(KErrSystemAttributeValue);
                    indata.Reset();
                    User::Leave(KErrArgument);
                    }
                }
                // Check if critical space is specified.
                if ( inmap->FindL(KCriticalSpace,indata) )
                    {
                    if( indata.TypeId() == EVariantTypeTInt32 )
                        {
                        TInt32 criticalspace = indata.AsTInt32();
                        aSysData = CDriveInfo::NewL(driveno,criticalspace);
                        }
                    else
                        {
                        indata.Reset();
                        iErrBuf.Append(KErrSystemAttributeValue);
                        User::Leave(KErrArgument);
                        }
                    }
                else
                    {
                    aSysData = CDriveInfo::NewL(driveno);
                    }
                }
        else
            {
            indata.Reset();
            iErrBuf.Append(KErrSystemAttributeValue);
            User::Leave(KErrArgument);
            }
    }
    //check for string data.
    else if( inmap->FindL(KStringData,indata) )
        {
        if( indata.TypeId() == EVariantTypeDesC )
            {
            aSysData = CStringData::NewL(indata.AsDes());		
            }
        else
            {
            indata.Reset();
            iErrBuf.Append(KErrSystemAttributeValue);
            User::Leave(KErrArgument);
            }
        }	
    //Unsupported input data.
    else
        {
        iErrBuf.Append(KErrUnsupportedInput);
        User::Leave(SErrMissingArgument);
        }
    indata.Reset();
    }

// ---------------------------------------------------------------------------
// CLandmarkInterface::ConvertSysData2AiwParamL(const CLiwGenericParamList& 
//                                    aInParamList, CLiwMap*& aOutMapParam)
// This function converts CSysData to aiw param.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::ConvertSysData2AiwParamL(const CSysData* aInSysData,
                                                        CLiwMap*& aOutMapParam)
    {
    aOutMapParam = CLiwDefaultMap::NewL();
    CleanupClosePushL(*aOutMapParam);
    TInt count = 0;
    switch (aInSysData->DataType())
        {
        case CSysData::EStatus:
            {
            TInt32 status = ((CStatus*) aInSysData)->Status();
            aOutMapParam->InsertL(KStatus,(TInt32)status);
            }
            break;
        case CSysData::EVersion:
            {
            TBuf<KMaxVersionTxt> majortxt(KNullDesC);
            TBuf<KMaxVersionTxt> minortxt(KNullDesC);
            majortxt.FillZ(0);
            minortxt.FillZ(0);
            const CVersion* version = (CVersion*) aInSysData;
            NumberConversion::AppendFormatNumber (majortxt, 
                            version->MajorVersion(),EDigitTypeWestern);
            aOutMapParam->InsertL(KMajorVersion,majortxt);
            NumberConversion::AppendFormatNumber (minortxt, 
                            version->MinorVersion(),EDigitTypeWestern);
            aOutMapParam->InsertL(KMinorVersion,minortxt);
            }
            break;
        case CSysData::EConnectionList:
            {
            CConnectionList* dataconnections = (CConnectionList*) aInSysData;
            CSysInfoConnList* connlist = CSysInfoConnList::NewL(dataconnections);
            CleanupClosePushL(*connlist);
            aOutMapParam->InsertL(KConnectionList,connlist);
            CleanupStack::PopAndDestroy(connlist);
            }
            break;
        case CSysData::ENetworkInfo:
            {
            const CNetworkInfo* networkinfo = (CNetworkInfo*) aInSysData;
            aOutMapParam->InsertL(KNetworkName,networkinfo->NetworkName());
            aOutMapParam->InsertL(KNetworkStatus,
                                        (TInt32)networkinfo->NetworkStatus());
            aOutMapParam->InsertL(KNetworkMode,(TInt32)networkinfo->NetworkMode());
            aOutMapParam->InsertL(KCountryCode,networkinfo->CountryCode());
            aOutMapParam->InsertL(KNetworkCode,networkinfo->NetworkCode());
            aOutMapParam->InsertL(KLocationStatus,
                                        networkinfo->ValidLocationAreaCode());
            aOutMapParam->InsertL(KAreaCode,networkinfo->LocationAreaCode());
            aOutMapParam->InsertL(KCellId,networkinfo->CellId());
            }
            break;
        case CSysData::EConnectionInfo:
            {
            const CConnectionInfo* connectioninfo = 
                                            ((CConnectionInfo*) aInSysData);
            aOutMapParam->InsertL(KIAPID,(TInt32)connectioninfo->IAPId());
            aOutMapParam->InsertL(KIAPName,connectioninfo->IAPName());
            aOutMapParam->InsertL(KIAPConnectionName,
                                            connectioninfo->ConnectionName());
            aOutMapParam->InsertL(KNetworkName,connectioninfo->NetworkName());
            aOutMapParam->InsertL(KConnectionType,
                                        (TInt32)connectioninfo->BearerType());
            aOutMapParam->InsertL(KConnectionStatus,
                                    (TInt32)connectioninfo->ConnectionState());
            }
            break;
        case CSysData::EDriveInfo:	
            {
            const CDriveInfo* driveinfo = (CDriveInfo*) aInSysData;		
            
            TBuf<KMaxDriveLength> drive;
            drive.FillZ();
            drive.Append('A'+driveinfo->DriveNumber());
            drive.Append(KDriveSeperator);
            
            aOutMapParam->InsertL(KDriveNo,drive);
            aOutMapParam->InsertL(KCriticalSpace,
                                        (TInt32)driveinfo->CriticalSpace());
            aOutMapParam->InsertL(KMediaType,(TInt32)driveinfo->MediaType());
            //totalspace and freespace converted to string .
            TBuf<KMax64BitNumLen> string64bitnum(KNullDesC);
            string64bitnum.FillZ(0);
            string64bitnum.Num(driveinfo->TotalSpace());
            aOutMapParam->InsertL(KTotalSpace,string64bitnum);
            string64bitnum.FillZ(0);
            string64bitnum.Num(driveinfo->FreeSpace());
            aOutMapParam->InsertL(KFreeSpace,string64bitnum);
            TPtrC drvname;
            driveinfo->DriveName(drvname);
            aOutMapParam->InsertL(KDriveName,drvname);
            aOutMapParam->InsertL(KBatteryState,(TInt32)driveinfo->BatteryState());
            }
            break;
            
        case CSysData::EAccessoryInfo:
            {
            const CAccessoryInfo* accessoryinfo = ((CAccessoryInfo*) aInSysData);
            aOutMapParam->InsertL(KAccessoryType,
                                    (TInt32)accessoryinfo->AccessoryType());
            aOutMapParam->InsertL(KAccessoryState,
                                    (TInt32)accessoryinfo->ConnectionState());
            }
            break;
        case CSysData::EResolution:
            {
            const CResolution* resolution = ((CResolution*) aInSysData);
            aOutMapParam->InsertL(KXPixels,(TInt32)resolution->XPixels());
            aOutMapParam->InsertL(KYPixels,(TInt32)resolution->YPixels());
            }
            break;
        case CSysData::EStringData:
            {
            const CStringData* stringdata = ((CStringData*) aInSysData);
            TPtrC string;
            stringdata->StringData(string);
            aOutMapParam->InsertL(KStringData,string);
            }
            break;
        case CSysData::EAccessoryList:
            {
            CAccList* accessories = (CAccList*) aInSysData;
            CSysInfoAccList* accessorylist = CSysInfoAccList::NewL(accessories);
            CleanupClosePushL(*accessorylist);
            aOutMapParam->InsertL(KAccessoryList,accessorylist);
            CleanupStack::PopAndDestroy(accessorylist);
            }
            break;
        case  CSysData::ELanguageList:
            {
            CLiwList* langlist = CLiwDefaultList::NewL();
            CleanupClosePushL(*langlist);
            const CLanguageList* languages = ((CLanguageList*) aInSysData);
            count= languages->Count();
            for(int index=0; index<count; index++ )
                {
                TInt language = 0;
                languages->At(index,language);
                langlist->AppendL(TLiwVariant(((TInt32)language)));
                }
            aOutMapParam->InsertL(KLanguageList,langlist);
            CleanupStack::PopAndDestroy(langlist);
            }
            break;

        case  CSysData::EDriveList:
            {
            CLiwList* drivelist = CLiwDefaultList::NewL();
            CleanupClosePushL(*drivelist);
            const CDriveList* drives = ((CDriveList*) aInSysData);
            count = drives->Count();
            for(int index=0; index<count; index++ )
                {
                TInt driveVal = 0;
                drives->At(index,driveVal);
                TBuf<KMaxDriveLength> drive;
                drive.FillZ();
                drive.Append('A'+driveVal);
                drive.Append(KDriveSeperator);
                drivelist->AppendL(TLiwVariant(drive));
                }
            aOutMapParam->InsertL(KDriveList,drivelist);
            CleanupStack::PopAndDestroy(drivelist);
            }
            break;	

        case  CSysData::EStringList:
            {
            CLiwList* stringlist = CLiwDefaultList::NewL();
            CleanupClosePushL(*stringlist);
            CStringList* strings = ((CStringList*) aInSysData);
            count = strings->Count();
            for(int index=0; index<count; index++ )
                {
                TPtrC string;
                strings->At(index,string);
                stringlist->AppendL(TLiwVariant(string));
                }
            aOutMapParam->InsertL(KStringList,stringlist);
            CleanupStack::PopAndDestroy(stringlist);
            }
            break;	

        default:
            User::Leave(KErrArgument);
        }
    CleanupStack::Pop(aOutMapParam);
    }

// ---------------------------------------------------------------------------
// CSysInfoInterface::CancelL(const CLiwGenericParamList& aInParamList,
//                           CLiwGenericParamList& /*aOutParamList*/,
//                           TUint /*aCmdOptions*/,
//                           MLiwNotifyCallback* aCallback )
// This cancels the ongoing async call.
// ---------------------------------------------------------------------------
//
void CSysInfoInterface::CancelL( const CLiwGenericParamList& aInParamList,
    CLiwGenericParamList& aOutParamList, TUint /*aCmdOptions*/,
    MLiwNotifyCallback* /*aCallback*/)
    {
    //Input param List must have transactionID specified
    if ( !aInParamList.Count() )
        {
        iErrBuf.Append(KErrTransactionIdMissing);
        User::Leave(SErrMissingArgument);
        }

    //position to start search in input params
    TInt index = 0;
    //get the transactionid is specified
    const TLiwGenericParam* param = aInParamList.FindFirst(index,KTransactionId);
    if ( !param  )
        {
        //Position based parsing
        param = &aInParamList[EIndex0];
        }

    TInt32 transactionId = param->Value().AsTInt32();

    MLiwNotifyCallback* CallbackObj = GetCallbackAndRemove(transactionId);

    if( !CallbackObj )
        {
        iErrBuf.Append(KErrCallbackNotPresent);
        User::Leave(KErrNotFound);
        }

    iService->Cancel(transactionId);
    TRAP_IGNORE(CallbackObj->HandleNotifyL(transactionId,
                            KLiwEventCanceled,aOutParamList,aInParamList));
    }

//end of file
