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
* Description:   ?Description
*
*/




// INCLUDE FILES
#include "sensrprovidertest.h"
#include "sensorinterface.hrh"
#include "serviceerrno.h"

_LIT(KSensorInterfaceNotFound , "Sensor Interface not found");
_LIT(KLogUnknownErr, "Success/Failure state not known-no error returned");
_LIT(KOutParamError, "Out Param not found");

class DataCallback : public MLiwNotifyCallback
	{
	private:
	TUint iChannelId;

	public :
	TInt iRetStatus;
	TInt HandleNotifyL( TInt aCmdId,
            			TInt aEventId,
            			CLiwGenericParamList& aEventParamList,
            			const CLiwGenericParamList& aInParamList);

	DataCallback( TUint aChannelId )
		{
		iChannelId = aChannelId;
		iRetStatus = KErrGeneral;
		}
	};


TInt DataCallback:: HandleNotifyL(TInt /*aCmdId*/,
					              TInt /*aEventId*/,
							      CLiwGenericParamList& aEventParamList,
							      const CLiwGenericParamList& /*aInParamList*/ )
	{
	
	TInt amemcnt = User::CountAllocCells();
	
	TInt index = 0;
	const TLiwGenericParam *GenericParam = aEventParamList.FindFirst
	                                      ( index, KErrorCode);

	if(!GenericParam)
		{
		return KErrGeneral;
		}
	if((GenericParam->Value()).AsTInt32() != KErrNone)
		{
		return (GenericParam->Value()).AsTInt32() ;
		}
	index = 0;
	
	const TLiwGenericParam *outGenericParam =  aEventParamList.FindFirst
	                                           (index, KReturnValue);
	
	const CLiwMap* chnlDataMap = (outGenericParam->Value()).AsMap();
    TLiwVariant infoVariant;
    chnlDataMap->FindL( KDataType , infoVariant );
    TPtrC dataType;
    infoVariant.Get( dataType );
	    
    if ( dataType == KAcclmtrAxisData )
		{
		TBuf8<50> data;
    	TRealFormat format;
	    chnlDataMap->FindL( KXAxisData , infoVariant ) ;
	    TInt32 xAxisData = infoVariant.AsTInt32();
	    chnlDataMap->FindL( KYAxisData , infoVariant ) ;
	    TInt32 yAxisData = infoVariant.AsTInt32();
	    chnlDataMap->FindL( KZAxisData , infoVariant ) ;
	    TInt32 zAxisData = infoVariant.AsTInt32();
	    
	    }
	else if ( dataType == KAcclmtrWakeupData  )
		{
		TBuf8<50> data;
    	TRealFormat format;
	    chnlDataMap->FindL( KDirection , infoVariant ) ;
	    TInt32 direction = infoVariant.AsTInt32();
			
		}
	else if ( dataType == KAcclmtrDoubleTappingData  )
		{
		TBuf8<50> data;
    	TRealFormat format;
	    	
	    chnlDataMap->FindL( KDirection , infoVariant ) ;
	    TInt32 direction = infoVariant.AsTInt32();
		
		}
	else if ( dataType == KOrientationData )
		{
		chnlDataMap->FindL( KDeviceOrientation,infoVariant );
		TPtrC data;
		infoVariant.Get( data );
		infoVariant.Reset();
		}
		else if ( dataType == KRotationData )
		{
		TBuf8<50> data;
    	TRealFormat format;
		TInt xAxis,yAxis,zAxis;
		chnlDataMap->FindL( KAbtXAxis , infoVariant );	
		infoVariant.Get( xAxis );
		chnlDataMap->FindL( KAbtYAxis , infoVariant );	
		infoVariant.Get( yAxis );
		chnlDataMap->FindL( KAbtZAxis , infoVariant );	
		infoVariant.Get( zAxis );
		}
		
	amemcnt = User::CountAllocCells();	
	CActiveScheduler::Stop();
	return KErrNone;
	}



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSensrProviderTest::Delete
// Delete here all resources allocated and opened from test methods.
// Called from destructor.
// -----------------------------------------------------------------------------
//
void CSensrProviderTest::Delete()
    {

    }

// -----------------------------------------------------------------------------
// CSensrProviderTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CSensrProviderTest::RunMethodL(
    CStifItemParser& aItem )
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.
        ENTRY( "TestEcomDiscovery", CSensrProviderTest::TestEcomDiscovery ),
        ENTRY( "TestFindSensorChannel", CSensrProviderTest::TestFindSensorChannel ),
        ENTRY( "GeneralNeg1", CSensrProviderTest::GeneralNeg1 ),
        ENTRY( "GeneralNeg2", CSensrProviderTest::GeneralNeg2 ),
        ENTRY( "RegisterForNotificationData", CSensrProviderTest::TestRegisterForNotificationData ),
        ENTRY( "TestGetChannelProperty", CSensrProviderTest::TestGetChannelProperty),
        };

    const TInt count = sizeof( KFunctions ) /
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt CSensrProviderTest::GeneralNeg1( CStifItemParser & /*aItem*/ )
	{
	__UHEAP_MARK;
	TInt memcnt = User::CountAllocCells();
	
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray a;
	a.AppendL(crit);
	ServiceHandler->AttachL(a) ;
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	TInt pos = 0;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource);
	if(!genericparm)
		{
		iLog->Log(KSensorInterfaceNotFound) ;
		return KErrGeneral;
		}
	TInt retError = KErrGeneral;
	MLiwInterface* sensrinterface = (genericparm->Value()).AsInterface();
	outputlist->Reset();
	inputlist->Reset();

	TPtrC8 commandSet8( _L8("Unknown") );

	inputlist->AppendL(TLiwGenericParam(_L8("Dummy"),TLiwVariant(0)));

	sensrinterface->ExecuteCmdL( commandSet8 , *inputlist , *outputlist);
	
	pos = 0;
	const TLiwGenericParam *ErrorCode =  outputlist->FindFirst(pos ,_L8("ErrorCode") );
	pos = 0;
	const TLiwGenericParam *ErrorStr =  outputlist->FindFirst(pos ,_L8("ErrorMessage") );
	
	if(!ErrorCode)
		{
		iLog->Log(KLogUnknownErr);
		retError = KErrGeneral ;
		}
	else if((ErrorCode->Value()).AsTInt32() )
		{
		TInt32 error = ErrorCode->Value().AsTInt32() ;
	    TPtrC errorStr = ErrorStr->Value().AsDes();
	
		if ( error == SErrServiceNotSupported )
			{
			iLog->Log( errorStr );
    		retError = KErrNone;
			}
		else
			{
			iLog->Log(_L("Invalid cmd name test failed"));
			retError = error;
			}
		}

	sensrinterface->Close();
	inputlist->Reset();
	outputlist->Reset();
	delete ServiceHandler;
	a.ResetAndDestroy();
    a.Close();
    
    memcnt = User::CountAllocCells();
    __UHEAP_MARKEND;   
    return retError;
	}


TInt CSensrProviderTest::GeneralNeg2( CStifItemParser & /*aItem*/ )
	{
	__UHEAP_MARK;
	TInt memcnt = User::CountAllocCells();
	
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray a;
	a.AppendL(crit);
	ServiceHandler->AttachL(a) ;
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	TInt pos = 0;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource);
	if(!genericparm)
		{
		iLog->Log(KSensorInterfaceNotFound) ;
		return KErrGeneral;
		}
	TInt retError = KErrGeneral;
	MLiwInterface* sensrinterface = (genericparm->Value()).AsInterface();
	outputlist->Reset();
	inputlist->Reset();

	TPtrC8 commandSet8( _L8("FindSensorChannel") );

	sensrinterface->ExecuteCmdL(commandSet8 , *inputlist , *outputlist);
	
	pos = 0;
	const TLiwGenericParam *ErrorCode =  outputlist->FindFirst(pos ,_L8("ErrorCode") );
	pos = 0;
	const TLiwGenericParam *ErrorStr =  outputlist->FindFirst(pos ,_L8("ErrorMessage") );
	
	if(!ErrorCode)
		{
		iLog->Log(KLogUnknownErr);
		retError = KErrGeneral ;
		}
	else if((ErrorCode->Value()).AsTInt32() )
		{
		TInt32 error = ErrorCode->Value().AsTInt32() ;
	    TPtrC errorStr = ErrorStr->Value().AsDes();
	
		if ( error == SErrMissingArgument )
			{
			iLog->Log( errorStr );
    		retError = KErrNone;
			}
		else
			{
			iLog->Log(_L("Empty input param list test failed"));
			retError = error;
			}
		}

	sensrinterface->Close();
	inputlist->Reset();
	outputlist->Reset();
	delete ServiceHandler;
	a.ResetAndDestroy();
    a.Close();
    
    memcnt = User::CountAllocCells();
    __UHEAP_MARKEND;   
    return retError;
	}


TInt CSensrProviderTest::TestGetChannelProperty( CStifItemParser &aItem )
	{
	__UHEAP_MARK;
	TInt memcnt = User::CountAllocCells();
	
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray a;
	a.AppendL(crit);
	ServiceHandler->AttachL(a) ;
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	TInt pos = 0;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource);

	TInt retError = KErrGeneral;
	MLiwInterface* sensrinterface = (genericparm->Value()).AsInterface();
	outputlist->Reset();
	inputlist->Reset();

	TPtrC commandSet( _L("UnknownCmd") );
   	aItem.GetNextString(commandSet);
   	TBuf8<KMaxFileName> commandSet8;
   	CnvUtfConverter::ConvertFromUnicodeToUtf8(commandSet8, commandSet );

	TPtrC inChannel( _L("Invalid") );
    aItem.GetNextString(inChannel);

    iLog->Log(_L("channel="));
    iLog->Log(inChannel);

	TPtrC propertyId( _L("InvalidId") );
   	aItem.GetNextString(propertyId);

	TBuf8<20> CmdBufSet(_L8("FindSensorChannel"));
	inputlist->AppendL(TLiwGenericParam(KSearchCriterion,TLiwVariant(inChannel)));
	sensrinterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist);
	pos = 0 ;
	const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;
	
	if(!ErrorParm)
		{
		iLog->Log(KLogUnknownErr);
		retError = KErrGeneral ;
		}
	else if((ErrorParm->Value()).AsTInt32() )
		{
		TInt32 error = ErrorParm->Value().AsTInt32() ;
		if ( error == SErrServiceNotSupported ) //Invalid channel
			{
			iLog->Log(_L("Service not supported"));
			sensrinterface->Close();
			inputlist->Reset();
			outputlist->Reset();
			delete ServiceHandler;
			a.ResetAndDestroy();
    		a.Close();
   			return KErrNone;
			}
		else
			{
			iLog->Log(_L("FindSensorChannel Failed"));
			retError = error;
			}
		}

	TInt index = 0 ;
	const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KReturnValue);
	if(!GenericParam)
		{
    	iLog->Log(KOutParamError);
		retError = KErrGeneral;
		}
	else //actual test starts here
		{
		memcnt = User::CountAllocCells();
		TLiwVariant variant,chnlVariant;
		variant = GenericParam->Value();
		const CLiwList *chnlInfoList = variant.AsList();
		TInt count = chnlInfoList->Count();
		
		chnlInfoList->AtL( 0, chnlVariant );
    	const CLiwMap *chnlInfo = chnlVariant.AsMap();
		outputlist->Reset();
		inputlist->Reset();
   
		inputlist->AppendL(TLiwGenericParam(KChnlInfoMap,TLiwVariant(chnlInfo)));   
		inputlist->AppendL(TLiwGenericParam(KPropId,
						   TLiwVariant(propertyId)));
		
		sensrinterface->ExecuteCmdL(commandSet8 , *inputlist , *outputlist);
		pos = 0 ;
		const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;
		pos = 0;
		const TLiwGenericParam *ErrorStr =  outputlist->FindFirst(pos ,_L8("ErrorMessage") );

	
		if(!ErrorParm)
			{
			iLog->Log(KLogUnknownErr);
			retError = KErrGeneral ;
			}
		else if((ErrorParm->Value()).AsTInt32() )
			{
			TInt32 error = ErrorParm->Value().AsTInt32();
			TPtrC errorStr = ErrorStr->Value().AsDes();
			
    		if( error == SErrNotFound )
    			{
    			iLog->Log(_L("propid="));
    			iLog->Log(propertyId);
			    iLog->Log(errorStr);
    			retError = KErrNone;
    			}
    		else
    			{
    			iLog->Log(_L("GetChannelProperty Failed"));
    			retError = error;
    			}
			}
		else
			{
			//output processing
			index = 0 ;
			const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KReturnValue);
			if(!GenericParam)
				{
    			iLog->Log(KOutParamError);
				retError = KErrGeneral;
				}
			else
				{
				retError = KErrNone;
				TLiwVariant variant;
				variant = GenericParam->Value();
				const CLiwMap* propertyMap = variant.AsMap();
				
				TInt mapcount = propertyMap->Count();
				TLiwVariant mapVariant;
				TInt propvalint;
				TReal propvalreal;
				
    			propertyMap->FindL( _L8("PropertyId") , mapVariant ) ;
				TPtrC propid = mapVariant.AsDes();
    			
    			iLog->Log(_L("propid="));
    			iLog->Log(propid);

    			propertyMap->FindL( _L8("PropertyDataType") , mapVariant ) ;
				TInt proptype = mapVariant.AsTInt32();
    			iLog->Log(_L("propdatatype=%d"),proptype);

    			propertyMap->FindL( _L8("PropertyValue") , mapVariant ) ;
    			if( proptype == 0 )
    				{
    				propvalint = mapVariant.AsTInt32();
    				iLog->Log(_L("proptype=%d"),proptype);
    				iLog->Log(_L("value=%d"),propvalint);	
    				}
    			else if( proptype == 1 )
    				{
    				propvalreal = mapVariant.AsTReal();
    				iLog->Log(_L("proptype=%d"),proptype);
    				iLog->Log(_L("value=%f"),propvalreal);
    				}
    			else if( proptype == 2 )
    				{
    				TPtrC propvaldes = mapVariant.AsDes();
    				iLog->Log(_L("proptype=%d"),proptype);
    				iLog->Log(_L("value="));
    				iLog->Log(propvaldes);
    				}
				
				}
			}
		chnlVariant.Reset();
		}
	
	memcnt = User::CountAllocCells();
	
	sensrinterface->Close();
	inputlist->Reset();
	outputlist->Reset();
	delete ServiceHandler;
	a.ResetAndDestroy();
    a.Close();
	
	memcnt = User::CountAllocCells();
	__UHEAP_MARKEND;
    return retError;
	}

    
TInt CSensrProviderTest::TestFindSensorChannel(CStifItemParser &aItem )
	{
	__UHEAP_MARK;
	TInt memcnt = User::CountAllocCells();
	
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray a;
	a.AppendL(crit);
	ServiceHandler->AttachL(a) ;
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	TInt pos = 0;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource);
	if(!genericparm)
		{
		iLog->Log(KSensorInterfaceNotFound) ;
		return KErrGeneral;
		}
	TInt retError = KErrGeneral;
	MLiwInterface* sensrinterface = (genericparm->Value()).AsInterface();
	outputlist->Reset();
	inputlist->Reset();

	TPtrC commandSet( _L("UnknownCmd") );
    aItem.GetNextString(commandSet);
    TBuf8<KMaxFileName> commandSet8;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(commandSet8, commandSet );

	TPtrC searchCrit( _L("Invalid") );
    aItem.GetNextString(searchCrit);
    
	inputlist->AppendL(TLiwGenericParam(KSearchCriterion,TLiwVariant(searchCrit)));
	
	sensrinterface->ExecuteCmdL(commandSet8 , *inputlist , *outputlist);
	
	pos = 0;
	const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,_L8("ErrorCode"));
	pos = 0;
	const TLiwGenericParam *ErrorStr =  outputlist->FindFirst(pos ,_L8("ErrorMessage"));
	
	if(!ErrorParm)
		{
		iLog->Log(KLogUnknownErr);
		retError = KErrGeneral ;
		}
	else if((ErrorParm->Value()).AsTInt32() )
		{
		TInt32 error = ErrorParm->Value().AsTInt32();
		TPtrC errStr = ErrorStr->Value().AsDes();
		
		if ( error == SErrInvalidServiceArgument ) //Invalid channel
			{
			iLog->Log(errStr);
    		retError = KErrNone;
			}
		else
			{
			iLog->Log(_L("FindSensorChannel Failed"));
			retError = error;
			}
		}
	else
		{
		//Output processing
		TInt index = 0 ;
		const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KReturnValue);
		if(!GenericParam)
			{
	    	iLog->Log(KOutParamError);
			retError = KErrGeneral;
			}
		else //test passed
			{
			retError = KErrNone; 
			TLiwVariant variant,chnlVariant;
			variant = GenericParam->Value();
			const CLiwList *chnlInfoList = variant.AsList();
			TInt count = chnlInfoList->Count();
			iLog->Log(_L("FindSensorChannel returned %d channels"),
					  count);
			
			for( int i = 0; i < count; i++ )
				{
				chnlInfoList->AtL( i, chnlVariant );
		    	const CLiwMap *aChnlInfoMap = chnlVariant.AsMap();
		    	
		    	TLiwVariant infoVariant;
		    	
		    	aChnlInfoMap->FindL( KChnlId , infoVariant );
		    	iLog->Log(_L("\n Channel id = %d"),infoVariant.AsTInt32());
		    			
			    aChnlInfoMap->FindL( KContextType , infoVariant );
		    	iLog->Log(_L("\n Context type = %d"),infoVariant.AsTInt32());

				aChnlInfoMap->FindL( KQuantity , infoVariant );
    			iLog->Log(_L("\n Quantity = %d"),infoVariant.AsTInt32());

		    	aChnlInfoMap->FindL( KChannelType , infoVariant );
		    	iLog->Log(_L("\n Channel type = %d"),infoVariant.AsTInt32());

				aChnlInfoMap->FindL( KLocation , infoVariant );
				iLog->Log(_L("\n Location = "));
				iLog->Log(infoVariant.AsDes());

				aChnlInfoMap->FindL( KVendorId , infoVariant );
				iLog->Log(_L("\n Vendor id = "));
				iLog->Log(infoVariant.AsDes());

				aChnlInfoMap->FindL( KDataItemSize , infoVariant );
		    	iLog->Log(_L("\n Dataitem size = %d"),infoVariant.AsTInt32());	

				aChnlInfoMap->FindL( KChnlDataTypeId , infoVariant );
		    	iLog->Log(_L("\n Datatype id = %d"),infoVariant.AsTInt32());

				iLog->Log(_L("\n ********"));
		    	infoVariant.Reset();
		    	chnlVariant.Reset();
				}
			outputlist->Reset();
			inputlist->Reset();
			}
		}
	
	sensrinterface->Close();
	inputlist->Reset();
	outputlist->Reset();
	delete ServiceHandler;
	a.ResetAndDestroy();
    a.Close();
    
    memcnt = User::CountAllocCells();
    __UHEAP_MARKEND;   
    return retError;
	}
    
    
TInt CSensrProviderTest::TestEcomDiscovery( CStifItemParser&/* aItem*/ )
	{
	__UHEAP_MARK;
	
	TInt memcnt = User::CountAllocCells();
	
	TInt error = KErrNone;
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray a;
	a.AppendL(crit);
	TRAP(error,ServiceHandler->AttachL(a));
	TRAP(error,ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist));
	TInt pos = 0;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource);
	if(!genericparm)
		{
		iLog->Log(KSensorInterfaceNotFound);
		return KErrGeneral;
		}
	memcnt = User::CountAllocCells();
	
	MLiwInterface* sensrinterface = (genericparm->Value()).AsInterface();
	memcnt = User::CountAllocCells();
	
	sensrinterface->Close();
	inputlist->Reset();
	outputlist->Reset();
	delete ServiceHandler;
	a.ResetAndDestroy();
    a.Close();
    
    memcnt = User::CountAllocCells();
	__UHEAP_MARKEND;  
    return KErrNone;
	}


TInt CSensrProviderTest::TestRegisterForNotificationData( CStifItemParser& aItem )
	{
	__UHEAP_MARK;
	TInt memcnt = User::CountAllocCells();
	
	TInt callCancel = 0;
	aItem.GetNextInt( callCancel );
	
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray a;
	a.AppendL(crit);
	ServiceHandler->AttachL(a) ;
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	TInt pos = 0;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource);
	if(!genericparm)
		{
		iLog->Log(KSensorInterfaceNotFound) ;
		return KErrGeneral;
		}
	TInt retError = KErrGeneral;
	MLiwInterface* sensrinterface = (genericparm->Value()).AsInterface();
	outputlist->Reset();
	inputlist->Reset();

	TPtrC commandSet( _L("UnknownCmd") );
    aItem.GetNextString(commandSet);
    TBuf8<KMaxFileName> commandSet8;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(commandSet8, commandSet );

	TPtrC searchCrit( _L("Invalid") );
    aItem.GetNextString(searchCrit);
    
	inputlist->AppendL(TLiwGenericParam(KSearchCriterion,TLiwVariant(searchCrit)));
	
	sensrinterface->ExecuteCmdL(_L8("FindSensorChannel") ,*inputlist , *outputlist);
	
	pos = 0;
	const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,_L8("ErrorCode"));
	pos = 0;
	const TLiwGenericParam *ErrorStr =  outputlist->FindFirst(pos ,_L8("ErrorMessage"));
	
	if(!ErrorParm)
		{
		iLog->Log(KLogUnknownErr);
		retError = KErrGeneral ;
		}
	else if((ErrorParm->Value()).AsTInt32() )
		{
		TInt32 error = ErrorParm->Value().AsTInt32();
		TPtrC errStr = ErrorStr->Value().AsDes();
		
		if ( error == SErrServiceNotSupported ) //Invalid channel
			{
			iLog->Log(errStr);
    		retError = KErrNone;
			}
		else
			{
			iLog->Log(_L("FindSensorChannel Failed"));
			retError = error;
			}
		}
	else
		{
		//Output processing
		TInt index = 0 ;
		const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KReturnValue);
		if(!GenericParam)
			{
	    	iLog->Log(KOutParamError);
			retError = KErrGeneral;
			}
		else //test starts here
			{
			retError = KErrNone; 
			TLiwVariant variant,chnlVariant;
			variant = GenericParam->Value();
			const CLiwList *chnlInfoList = variant.AsList();
			TInt count = chnlInfoList->Count();
			iLog->Log(_L("FindSensorChannel returned %d channels"),
					  count);
			
			chnlInfoList->AtL( 0, chnlVariant );
	    	const CLiwMap *chnlInfo = chnlVariant.AsMap();

			outputlist->Reset();
			inputlist->Reset();
				
	    	TLiwVariant idVariant;
			chnlInfo->FindL(KChnlId,idVariant);
			TUint chnlid = idVariant.AsTUint();
			
			TPtrC listenStr( _L("ChannelData") );
			
			inputlist->AppendL(TLiwGenericParam(KChnlInfoMap,
			                                    TLiwVariant(chnlInfo)));
			inputlist->AppendL(TLiwGenericParam(KListeningType,
			                                    TLiwVariant(listenStr)));
		
			DataCallback callback( chnlid );
			memcnt = User::CountAllocCells();
		
			sensrinterface->ExecuteCmdL(commandSet8,
										*inputlist,
										*outputlist,
										1,
										&callback);
			pos = 0;
			const TLiwGenericParam *ErrorParm = outputlist->FindFirst
											    ( pos ,KErrorCode );
			pos = 0;
			const TLiwGenericParam *transIdParm = outputlist->FindFirst
			                                      ( pos ,KTransactionId );
		
			memcnt = User::CountAllocCells();
		
			TInt32 transid = (transIdParm->Value()).AsTInt32();
		
	
			if(!ErrorParm)
				{
				iLog->Log(KLogUnknownErr);
				sensrinterface->Close();
	   			delete ServiceHandler;
				return KErrGeneral ;
				}
			else if((ErrorParm->Value()).AsTInt32() )
				{
				TInt32 error = ErrorParm->Value().AsTInt32();
				sensrinterface->Close();
	   			delete ServiceHandler;
			    iLog->Log(_L("StartGettingNotification failed"));
	    		return error;
	    		}

			memcnt = User::CountAllocCells();
			CActiveScheduler::Start();
			
			if( callCancel )
				{
				TBuf8<50>CmdBuf(KStopNotification);
				outputlist->Reset();
				inputlist->Reset();
				inputlist->AppendL(TLiwGenericParam(KTransactionId,transid));
				sensrinterface->ExecuteCmdL( CmdBuf,
				                             *inputlist,
				                             *outputlist,
				                             KLiwOptCancel);
				
				}
			retError = KErrNone;
			chnlVariant.Reset();
			}
		
		}
	
	sensrinterface->Close();
	inputlist->Reset();
	outputlist->Reset();
	delete ServiceHandler;
	a.ResetAndDestroy();
    a.Close();
    
    memcnt = User::CountAllocCells();
    __UHEAP_MARKEND;   
    return retError;
	
	}


