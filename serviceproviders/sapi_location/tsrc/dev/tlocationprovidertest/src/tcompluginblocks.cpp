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
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <LbsRequestor.h>
#include <LiwServiceHandler.h>
#include <LiwCommon.h>
#include <lbs.h>

#include "Tcomplugin.h"

using namespace LIW;

_LIT(LogFileName , "C:\\Notifications.txt") ;

//----------------------------------------------------------------------------
// CTestProvider :: Delete()
//----------------------------------------------------------------------------
void CTestProvider::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTestProvider::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestProvider::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY("GetLocation" , CTestProvider :: GetLocation),
        ENTRY("LocationUpdates" , CTestProvider :: LocationUpdates),
        ENTRY("GetLocationAsynch" , CTestProvider :: GetLocationAsynch),
        ENTRY("ServiceFailed" , CTestProvider :: ServiceFailed),
        ENTRY("ServiceNotAvailable" , CTestProvider :: ServiceNotAvailable),
        ENTRY("StraySignalTrace" , CTestProvider :: StraySignal),
       	ENTRY("StraySignalGetLoc" , CTestProvider :: StraySignalGetLoc),
       	ENTRY("ConcurrentCallsGetLoc" , CTestProvider:: ConcurrentCallsGetLoc),
       	ENTRY("ConcurrentCallsTrace" , CTestProvider:: ConcurrentCallsTrace),
       	ENTRY("EmptyCancelTraceTest" , CTestProvider:: EmptyCancelTraceTest),
       	ENTRY("EmptyCancelGetLocTest" , CTestProvider:: EmptyCancelGetLocTest),
       	ENTRY("CancelWrongNotification1" , CTestProvider:: CancelWrongNotification1),
       	ENTRY("CancelWrongNotification2" , CTestProvider:: CancelWrongNotification2),
       	ENTRY("GetLocationCancel" , CTestProvider:: GetLocationCancel),
       	ENTRY("TraceLocationCancel" , CTestProvider:: TraceLocationCancel),
       	ENTRY("GetLocationTimedOut" , CTestProvider :: GetLocationTimedOut ),
       	ENTRY("BearingToTest" , CTestProvider :: BearingToTest),
       	ENTRY("FindDistance" , CTestProvider :: FindDistance),
       	ENTRY("FindDistanceAgain" , CTestProvider :: FindDistanceAgain),
       	ENTRY("GetLocationUpdateOpts" , CTestProvider :: GetLocationUpdateOpts),
       	ENTRY("MoveCoordinates" , CTestProvider :: MoveCoordinates),
       	ENTRY("GetLocationSynchWrongUpdateMapType" , CTestProvider :: GetLocationSynchWrongUpdateMapType),
       	ENTRY("CancelWithInvalidTransId" , CTestProvider ::CancelWithInvalidTransId),
       	ENTRY("getlocationPostionbased" , CTestProvider :: getlocationPostionbased),
       	ENTRY("getlocationPostionbasedwithupdateoption" , CTestProvider ::getlocationPostionbasedwithupdateoption),
       	ENTRY("getlocationPostionbasedpdateoption" , CTestProvider :: getlocationPostionbasedpdateoption),
       	
       	ENTRY("GetLocationWrongInfoClass" , CTestProvider :: GetLocationWrongInfoClass),
       	ENTRY("TraceWrongInfoClass" , CTestProvider :: TraceWrongInfoClass),
       	ENTRY("GetLocNegativeUpdateoption" , CTestProvider :: GetLocNegativeUpdateoption),
       	ENTRY("TraceNegativeUpdateoption" , CTestProvider :: TraceNegativeUpdateoption),
       	ENTRY("TestWrongInterfaceName" , CTestProvider :: TestWrongInterfaceName),
       	ENTRY("TestAllApi" , CTestProvider :: TestAllApi),
       	ENTRY("CancelTwice" , CTestProvider :: CancelTwice),
            ENTRY("GetLastLocation" , CTestProvider :: GetLastLocation),
            ENTRY("GetLocationMultiple" , CTestProvider :: GetLocationMultiple),
            ENTRY("TraceMultiple" , CTestProvider :: TraceMultiple),
            ENTRY("TraceTimeOut" , CTestProvider :: TraceTimeOut),
            ENTRY("TraceMultipleWrongCancel", CTestProvider::TraceMultipleWrongCancel),
            ENTRY("EnableAccTrueGetLoc", CTestProvider::EnableAccTrueGetLoc),
            ENTRY("EnableAccFalseGetLoc", CTestProvider::EnableAccFalseGetLoc),
            ENTRY("EnableAccTrueTrace", CTestProvider::EnableAccTrueTrace),
            ENTRY("EnableAccFalseTrace", CTestProvider::EnableAccFalseTrace),
            ENTRY("EnableAccPosBasedGetloc", CTestProvider::EnableAccPosBasedGetloc),
            ENTRY("EnableAccPosBasedWrongTypeGetloc", CTestProvider::EnableAccPosBasedWrongTypeGetloc),
            ENTRY("EnableAccPosBasedTrace", CTestProvider::EnableAccPosBasedTrace),
            ENTRY("EnableAccPosBasedWrongTypeTrace", CTestProvider::EnableAccPosBasedWrongTypeTrace),

            ENTRY("CancelWithoutTransId" , CTestProvider ::CancelWithoutTransId),     
            ENTRY("CancelTransIdPosBased", CTestProvider::CancelTransIdPosBased),    
            ENTRY("GetLocationAsyncPosBasedUpdate" , CTestProvider ::GetLocationAsyncPosBasedUpdate),  
            ENTRY("GetLocationPosBasedWrongVal", CTestProvider::GetLocationPosBasedWrongVal),        
            ENTRY("GetLocationAsyncWrongUpdate" ,CTestProvider::GetLocationAsyncWrongUpdate),           
            ENTRY("GetLocPosBasedWrongVal" , CTestProvider ::GetLocPosBasedWrongVal),       
            ENTRY("TracePosBasedWrongVal" , CTestProvider ::TracePosBasedWrongVal),    
            ENTRY("TracePosBasedUpdateOpts" , CTestProvider ::TracePosBasedUpdateOpts),   
            ENTRY("TracePosBasedUpdateWrongVal" , CTestProvider ::TracePosBasedUpdateWrongVal),  
            ENTRY("FindDistancePositionBased" ,CTestProvider ::FindDistancePositionBased),  
            ENTRY("MoveCoordinatePosBased",CTestProvider::MoveCoordinatePosBased)    
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
    
    
 class ASyncLocCBF : public MLiwNotifyCallback
{
    TInt cnt;
	public :
	TInt iRetStatus ;
		
		TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList) ;

		ASyncLocCBF() : iRetStatus(KErrGeneral)  //Default constructor 
			{
			        cnt = 0;
			}
	
};
TInt ASyncLocCBF::HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList) 
{
    cnt++;
	return 0;
}


TInt CTestProvider :: CancelTwice( CStifItemParser& /*aItem*/ )
{
__UHEAP_MARK ;
	CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

	// Input and output parameter list
	CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
	CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);

	ServiceHandler->AttachL(a) ;
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);

	 
	 

	TInt pos = 0;

	const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

	if(!errorprm)
	{
		
		return KErrGeneral ;
	}


	_LIT8(KDataSource, "ILocation");
	 
	 pos = 0 ;

	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

	if(!genericparm)
	{
		
		return KErrGeneral ;
	}

	MLiwInterface* locinterface = (genericparm->Value()).AsInterface();

	
	    
	TBuf8<20>CmdBuf(KCmdGetLocation) ;

	outputlist->Reset() ;
	inputlist->Reset() ;
	ASyncLocCBF* callBack = new(ELeave) ASyncLocCBF;

	locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);

	pos = 0 ;

	const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

	if(!ErrorParm)
	{
		return KErrGeneral ;
	}
	
	TInt reqerror = (ErrorParm->Value()).AsTInt32();
	
	pos = 0;
	
	_LIT8(KTransactionId, "TransactionID");
	const TLiwGenericParam *transid =  outputlist->FindFirst(pos ,KTransactionId ) ;
	if(!transid)
	{
		return KErrGeneral;
	}
	TInt32 trid = (transid->Value()).AsTInt32();
	outputlist->Reset() ;
	inputlist->Reset() ;
	
	
	inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid)));
	
	locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);
	
	ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

	if(!ErrorParm)
	{
		return KErrGeneral ;
	}
	
	reqerror = (ErrorParm->Value()).AsTInt32();
	
	/*if( SErrNotFound == reqerror )
		{
		reqerror = 0;	
		}*/
	
	//Call cancel again with same transaction id
	outputlist->Reset() ;
	inputlist->Reset() ;
	
	
	inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid-2)));
	
	locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);
	
	ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

	if(!ErrorParm)
	{
		return KErrGeneral ;
	}
	
	reqerror = (ErrorParm->Value()).AsTInt32();
	
	if( SErrNotFound == reqerror )
		{
		reqerror = 0;	
		}
	

	



	locinterface->Close() ;
	inputlist->Reset();
	outputlist->Reset();
	delete callBack;
	delete ServiceHandler ;
	a.ResetAndDestroy() ;
	a.Close() ;

	__UHEAP_MARKEND ;
	return reqerror ;



		
}
TInt CTestProvider :: TestAllApi( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK ;
    TInt start = User::CountAllocCells();
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }




    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create notifications log file") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CTGetLocation") ;
    iLog->Log(KLog) ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {
        _LIT(KLog , "Interface not found");
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT(KClass,"GenericLocationInfo");
    inputlist->AppendL( TLiwGenericParam( KNullDesC8,TLiwVariant(KClass  )  ) );
    //inputlist->AppendL(TLiwGenericParam(NULL));
    CLiwDefaultMap* updatemap = CLiwDefaultMap::NewL();

    _LIT8(KInterval,"UpdateInterval");
    _LIT8(KTimeout,"UpdateTimeOut");
    _LIT8(KAge,"UpdateMaxAge");
    _LIT8(KPartial,"PartialUpdates");
    const TInt KTime = 1000000;

    updatemap->InsertL(KInterval , TLiwVariant(TInt32(2*KTime)));
    updatemap->InsertL(KTimeout , TLiwVariant(TInt32(30*KTime)));
    updatemap->InsertL(KAge , TLiwVariant(TInt32(0)));
    updatemap->InsertL(KPartial , TLiwVariant(TBool(FALSE)));

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(updatemap)));
    updatemap->DecRef();



    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog, "Success/Failure state not known") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }

    if((ErrorParm->Value()).AsTInt32() )
        {
        _LIT(KLog , "ExecutecmdL failed ");
        iLog->Log(KLog) ;
        return (ErrorParm->Value()).AsTInt32() ;	
        }



    TInt index = 0 ;

    const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KLocationMap);


    if(!GenericParam)
        {
        _LIT(Klog, "Out Param not found") ;
        iLog->Log(Klog) ;
        return KErrGeneral ; //Param Error
        }	

    TLiwVariant Variant ;

    Variant = GenericParam->Value() ;
    const	CLiwMap *LocMap = Variant.AsMap() ;

    TLiwVariant PosVariant ;

    LocMap->FindL(KLongitudeKey , PosVariant) ;
    TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
    data.Num(LongData , format) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Write(_L8("Logitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KLatitudeKey ,PosVariant) ; //Latitude 

    TReal64 LatData = (TReal64)PosVariant.AsTReal() ;
    data.Num(LatData , format) ;
    LogFile.Write(_L8("   Latitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KAltitudeKey , PosVariant) ; //Altitude
    TReal32 AltData = PosVariant.AsTReal() ;
    data.Num(AltData , format) ;

    LogFile.Write(_L8("   Altitude = "))	 ;
    LogFile.Write(data) ;



    //Test Calculate
    //TBuf8<20>CmdBufSet(KRequestCalculate) ;
    outputlist->Reset() ;
    inputlist->Reset() ;

    //CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    TLiwGenericParam requesttype(KMathRequest , TLiwVariant(KRequestDistance)) ;
    inputlist->AppendL(requesttype) ;



    //Inserting first input param
    CLiwMap* SourceCoordinate = CLiwDefaultMap::NewL();
    TReal64 slongitude = 71.03;
    SourceCoordinate->InsertL(KLongitudeKey,TLiwVariant(slongitude));
    TReal64 slatitude = 42.37;
    SourceCoordinate->InsertL(KLatitudeKey,TLiwVariant(slatitude));

    TReal64 saltitude = 1;
    SourceCoordinate->InsertL(KAltitudeKey,TLiwVariant(saltitude));


    TLiwGenericParam scoordinate(KDistanceParmSource,TLiwVariant(SourceCoordinate));
    inputlist->AppendL(scoordinate) ;
    SourceCoordinate->DecRef() ;



    //Inserting 2nd input param
    CLiwMap* DestCoordinate = CLiwDefaultMap::NewL();
    TReal64 dlongitude = 83.02;
    DestCoordinate->InsertL(KLongitudeKey,TLiwVariant(dlongitude));
    TReal64 dlatitude = 42.42;
    DestCoordinate->InsertL(KLatitudeKey,TLiwVariant(dlatitude));

    TReal64 daltitude = 1;
    DestCoordinate->InsertL(KAltitudeKey,TLiwVariant(daltitude));


    TLiwGenericParam dcoordinate(KDistanceParmDestination,TLiwVariant(DestCoordinate));
    inputlist->AppendL(dcoordinate) ;
    DestCoordinate->DecRef() ;  

    //CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;


    TBuf8<20>CmdBufSet(KRequestCalculate) ;

    locinterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist);


    pos = 0;
    const TLiwGenericParam* param = outputlist->FindFirst(pos, KErrorCode);

    if((param->Value()).AsTInt32() )
        {
        _LIT(KLog , "Calculate failed ");
        iLog->Log(KLog) ;
        return (ErrorParm->Value()).AsTInt32() ;	
        }

    pos = 0;
    const TLiwGenericParam* paramb = outputlist->FindFirst(pos, KErrorCode);

    if((paramb->Value()).AsTInt32() )
        {
        _LIT(KLog , "Calculate failed ");
        iLog->Log(KLog) ;
        return (paramb->Value()).AsTInt32() ;	
        }
    pos = 0;
    const TLiwGenericParam* resultparam = outputlist->FindFirst(pos, KMathOpResult);		
    TLiwVariant resultvariant = resultparam->Value();
    TReal64 distance = resultvariant.AsTReal();

    //Test Calculate done	

    LogFile.Close() ;
    LogSession.Close() ;


    locinterface->Close() ;
    outputlist->Reset() ;
    inputlist->Reset() ;

    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    TInt end = User::CountAllocCells();

    __UHEAP_MARKEND ;
    return KErrNone ;




    }
TInt CTestProvider :: TestWrongInterfaceName( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK;

    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());



    _LIT8(KServicename,"abc");
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KServicename);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        //return KErrGeneral ;
        }
    TInt error = (errorprm->Value()).AsTInt32();
    delete ServiceHandler;
    a.ResetAndDestroy() ;
    a.Close() ;
    __UHEAP_MARKEND;	

    return KErrNone;
    }

TInt CTestProvider :: TraceNegativeUpdateoption( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK;
    ASyncLocCBF callback;
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();

    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    //Append LocationInformation Category
    TLiwGenericParam informationCategory(KLocationInfoCategory , TLiwVariant(KLocationBasicinfo)) ;
    InputList->AppendL(informationCategory) ;

    //Appending update options
    CLiwMap* updateoptionMap = CLiwDefaultMap::NewL();

    TInt32 updateInterval = 30000;

    updateoptionMap->InsertL(KUpdateOptionInterval,TLiwVariant(updateInterval));

    TInt32 updateTimeOut = -10000;
    updateoptionMap->InsertL(KUpdateOptionTimeOut,TLiwVariant(updateTimeOut));

    TInt32 updateMaxAge = 2000;
    updateoptionMap->InsertL(KUpdateOptionMaxAge,TLiwVariant(updateMaxAge));

    TLiwGenericParam updateOption(KUpdateOptionMap,TLiwVariant(updateoptionMap));
    InputList->AppendL(updateOption) ;
    updateoptionMap->DecRef();

    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;


    locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList,KLiwOptASyncronous,&callback);




    pos = 0;
    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {

        return KErrGeneral ;
        }
    TInt error = (ErrorParm->Value()).AsTInt32();
    if( SErrBadArgumentType == error )
        {
        error = KErrNone;	


        }
    locinterface->Close() ;
    outputlist->Reset() ;
    inputlist->Reset() ;
    delete ServiceHandler ;
    delete OutParmList;
    delete InputList;
    a.ResetAndDestroy() ;
    a.Close() ;
    __UHEAP_MARKEND ;	
    return error;




    }

TInt CTestProvider :: GetLocNegativeUpdateoption( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK;
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    //Append LocationInformation Category
    TLiwGenericParam informationCategory(KLocationInfoCategory , TLiwVariant(KLocationBasicinfo)) ;
    InputList->AppendL(informationCategory) ;

    //Appending update options
    CLiwMap* updateoptionMap = CLiwDefaultMap::NewL();

    TInt32 updateInterval = 30000;

    updateoptionMap->InsertL(KUpdateOptionInterval,TLiwVariant(updateInterval));

    TInt32 updateTimeOut = -10000;
    updateoptionMap->InsertL(KUpdateOptionTimeOut,TLiwVariant(updateTimeOut));

    TInt32 updateMaxAge = 2000;
    updateoptionMap->InsertL(KUpdateOptionMaxAge,TLiwVariant(updateMaxAge));

    TLiwGenericParam updateOption(KUpdateOptionMap,TLiwVariant(updateoptionMap));
    InputList->AppendL(updateOption) ;
    updateoptionMap->DecRef();

    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;




    locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList);


    pos = 0;
    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {

        return KErrGeneral ;
        }
    TInt error = (ErrorParm->Value()).AsTInt32();
    if( SErrBadArgumentType == error )
        {
        error = KErrNone;	


        }
    locinterface->Close() ;
    delete ServiceHandler ;
    delete OutParmList;
    delete InputList;
    a.ResetAndDestroy() ;
    a.Close() ;
    __UHEAP_MARKEND ;	
    return error;




    }
TInt CTestProvider :: GetLocationWrongInfoClass( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT8(KClass,"LocationInformationClass");
    _LIT(KClassArg,"Invalid");
    inputlist->AppendL(TLiwGenericParam(KClass,TLiwVariant(KClassArg)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {

        return KErrGeneral ;
        }
    TInt error = (ErrorParm->Value()).AsTInt32();
    if( SErrBadArgumentType == error )
        {
        error = KErrNone;	


        }
    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    __UHEAP_MARKEND ;	
    return error;

    }

TInt CTestProvider :: TraceWrongInfoClass( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK ;
    TInt start = User::CountAllocCells();
    ASyncLocCBF callback;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());



    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);

    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);
    ServiceHandler->AttachL(a) ;


    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);


    TInt pos = 0;
    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");
    pos = 0 ;
    
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);
    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();


    TBuf8<20>CmdBuf(KCmdTraceLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT8(KClass,"LocationInformationClass");
    _LIT(KClassArg,"Invalid");
    inputlist->AppendL(TLiwGenericParam(KClass,TLiwVariant(KClassArg)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous,&callback);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;
    if(!ErrorParm)
        {

        return KErrGeneral ;
        }
    TInt error = (ErrorParm->Value()).AsTInt32();
    if( SErrBadArgumentType == error )
        {
        error = KErrNone;	
        }
    locinterface->Close() ;
    outputlist->Reset() ;
    inputlist->Reset() ;
    
    //delete inputlist;
    //delete outputlist;
    
   	delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    TInt end = User::CountAllocCells();
    __UHEAP_MARKEND ;	
    return error;

    }

TInt CTestProvider :: getlocationPostionbasedpdateoption( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }




    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create notifications log file") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CTGetLocation") ;
    iLog->Log(KLog) ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {
        _LIT(KLog , "Interface not found");
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT(KClass,"GenericLocationInfo");
    inputlist->AppendL( TLiwGenericParam( KNullDesC8,TLiwVariant(  )  ) );
    //inputlist->AppendL(TLiwGenericParam(NULL));
    CLiwDefaultMap* updatemap = CLiwDefaultMap::NewL();

    _LIT8(KInterval,"UpdateInterval");
    _LIT8(KTimeout,"UpdateTimeOut");
    _LIT8(KAge,"UpdateMaxAge");
    _LIT8(KPartial,"PartialUpdates");
    const TInt KTime = 1000000;

    updatemap->InsertL(KInterval , TLiwVariant(TInt32(2*KTime)));
    updatemap->InsertL(KTimeout , TLiwVariant(TInt32(30*KTime)));
    updatemap->InsertL(KAge , TLiwVariant(TInt32(0)));
    updatemap->InsertL(KPartial , TLiwVariant(TBool(FALSE)));

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(updatemap)));
    updatemap->DecRef();



    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog, "Success/Failure state not known") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }

    if((ErrorParm->Value()).AsTInt32() )
        {
        _LIT(KLog , "ExecutecmdL failed ");
        iLog->Log(KLog) ;
        //return (ErrorParm->Value()).AsTInt32() ;	
        }



    TInt index = 0 ;

    const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KLocationMap);


    if(!GenericParam)
        {
        _LIT(Klog, "Out Param not found") ;
        iLog->Log(Klog) ;
        return KErrGeneral ; //Param Error
        }	

    TLiwVariant Variant ;

    Variant = GenericParam->Value() ;
    const	CLiwMap *LocMap = Variant.AsMap() ;

    TLiwVariant PosVariant ;

    LocMap->FindL(KLongitudeKey , PosVariant) ;
    TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
    data.Num(LongData , format) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Write(_L8("Logitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KLatitudeKey ,PosVariant) ; //Latitude 

    TReal64 LatData = (TReal64)PosVariant.AsTReal() ;
    data.Num(LatData , format) ;
    LogFile.Write(_L8("   Latitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KAltitudeKey , PosVariant) ; //Altitude
    TReal32 AltData = PosVariant.AsTReal() ;
    data.Num(AltData , format) ;

    LogFile.Write(_L8("   Altitude = "))	 ;
    LogFile.Write(data) ;

    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return KErrNone ;



    }

TInt CTestProvider :: getlocationPostionbasedwithupdateoption( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }




    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create notifications log file") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CTGetLocation") ;
    iLog->Log(KLog) ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {
        _LIT(KLog , "Interface not found");
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT(KClass,"GenericLocationInfo");
    inputlist->AppendL( TLiwGenericParam( KNullDesC8,TLiwVariant( KClass )  ) );
    CLiwDefaultMap* updatemap = CLiwDefaultMap::NewL();

    _LIT8(KInterval,"UpdateInterval");
    _LIT8(KTimeout,"UpdateTimeOut");
    _LIT8(KAge,"UpdateMaxAge");
    _LIT8(KPartial,"PartialUpdates");
    const TInt KTime = 1000000;

    updatemap->InsertL(KInterval , TLiwVariant(TInt32(2*KTime)));
    updatemap->InsertL(KTimeout , TLiwVariant(TInt32(30*KTime)));
    updatemap->InsertL(KAge , TLiwVariant(TInt32(0)));
    updatemap->InsertL(KPartial , TLiwVariant(TBool(FALSE)));

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(updatemap)));
    updatemap->DecRef();



    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog, "Success/Failure state not known") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }

    if((ErrorParm->Value()).AsTInt32() )
        {
        _LIT(KLog , "ExecutecmdL failed ");
        iLog->Log(KLog) ;
        return (ErrorParm->Value()).AsTInt32() ;	
        }



    TInt index = 0 ;

    const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KLocationMap);


    if(!GenericParam)
        {
        _LIT(Klog, "Out Param not found") ;
        iLog->Log(Klog) ;
        return KErrGeneral ; //Param Error
        }	

    TLiwVariant Variant ;

    Variant = GenericParam->Value() ;
    const	CLiwMap *LocMap = Variant.AsMap() ;

    TLiwVariant PosVariant ;

    LocMap->FindL(KLongitudeKey , PosVariant) ;
    TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
    data.Num(LongData , format) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Write(_L8("Logitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KLatitudeKey ,PosVariant) ; //Latitude 

    TReal64 LatData = (TReal64)PosVariant.AsTReal() ;
    data.Num(LatData , format) ;
    LogFile.Write(_L8("   Latitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KAltitudeKey , PosVariant) ; //Altitude
    TReal32 AltData = PosVariant.AsTReal() ;
    data.Num(AltData , format) ;

    LogFile.Write(_L8("   Altitude = "))	 ;
    LogFile.Write(data) ;


    TLiwVariant Speed ;

    index = LocMap->FindL(_L8("HorizontalSpeed") , Speed ) ;

    if(index )
        {

        TReal speed =  Speed.AsTReal() ;

        data.Num(speed , format) ;

        LogFile.Write(_L8("Speed = ")) ;
        LogFile.Write(data) ;

        }


    TLiwVariant SpeedError ;
    index = LocMap->FindL( _L8("HorizontalSpeedError") , SpeedError) ;


    if(index )
        {

        TReal speed =  SpeedError.AsTReal() ;

        data.Num(speed , format) ;

        LogFile.Write(_L8("Speed = ")) ;
        LogFile.Write(data) ;

        }

    index = 0 ;

    TLiwVariant SatInfo ;

    index = LocMap->FindL(_L8("SatelliteNumView") , SatInfo) ;

    if(index )
        {

        TInt satnumView = SatInfo.AsTInt32() ;
        data.Num(satnumView , format);

        LogFile.Write(_L8("Satellite information")) ;

        LogFile.Write(_L8("Number of visible satellites ")) ;
        LogFile.Write(data) ;
        }

    index = 0 ;

    TLiwVariant SatInfoview ;

    index = LocMap->FindL( _L8("SatelliteNumViewUsed") , SatInfoview) ;
    if(index )
        {


        TInt satnumViewUsed = SatInfoview.AsTInt32() ;
        data.Num(satnumViewUsed , format);

        LogFile.Write(_L8("\nSatellite information")) ;

        LogFile.Write(_L8("\nSatelliteNumViewUsed")) ;
        LogFile.Write(data) ;
        }

    index = 0 ;

    TInt Headinginfo = 0 ;

    TLiwVariant  Heading ;
    Headinginfo = LocMap->FindL(_L8("Heading") ,Heading) ;

    if(Headinginfo)
        {


        TReal heading = Heading.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\ncompass information")) ;

        LogFile.Write(_L8("\nHeading")) ;
        LogFile.Write(data) ;
        }


    if(Headinginfo)
        {
        TLiwVariant HeadingError ;
        index  = LocMap->FindL( _L8("HeadingError") , HeadingError ) ;

        if(index)
            {


            TReal heading = HeadingError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nHeading Error")) ;
            LogFile.Write(data) ;

            }

        TLiwVariant MagneticHeading ;
        index = LocMap->FindL( _L8("MagneticHeading") ,  MagneticHeading) ;

        if(index)
            {


            TReal heading = MagneticHeading.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\n MagneticHeading ")) ;
            LogFile.Write(data) ;

            }


        TLiwVariant MagneticHeadingError ;
        index = LocMap->FindL(_L8("MagneticHeadingError")  ,MagneticHeadingError) ;

        if(index)
            {


            TReal heading = MagneticHeadingError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nMagneticHeading Error")) ;
            LogFile.Write(data) ;

            }


        } //End of Heading



    TLiwVariant TrueCourse ;
    index = LocMap->FindL( _L8("TrueCourse") , TrueCourse ) ;

    if( index)
        {


        TReal heading = TrueCourse.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\nDirection ")) ;

        LogFile.Write(_L8("\n TrueCourse Error")) ;
        LogFile.Write(data) ;



        TLiwVariant TrueCourseError ;
        index  = LocMap->FindL( _L8("TrueCourseError") , TrueCourseError ) ;

        if( index)
            {


            TReal heading = TrueCourseError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nMagneticHeading Error")) ;
            LogFile.Write(data) ;

            }


        }


    TLiwVariant MagneticCourse ;
    index =  LocMap->FindL(_L8("MagneticCourse") , MagneticCourse ) ;


    if(index)
        {

        TReal heading = MagneticCourse.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\ncompass information")) ;

        LogFile.Write(_L8("\nMagneticCourse ")) ;
        LogFile.Write(data) ;



        TLiwVariant MagneticCourseError  ;
        index = LocMap->FindL(_L8("MagneticCourseError") ,MagneticCourseError ) ;

        if( index)
            {


            TReal heading = MagneticCourseError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\n MagneticCourseError Error")) ;
            LogFile.Write(data) ;

            }


        }



    TLiwVariant NmeaNum ;
    index = LocMap->FindL(_L8("NMEASentence") , NmeaNum ) ;  	 


    if(index)
        {

        TInt32 NMEASentence = NmeaNum.AsTInt32() ;
        data.Num(NMEASentence , format);

        LogFile.Write(_L8("\nNMEA Information")) ;

        LogFile.Write(_L8("\n number of NMEA Sentences ")) ;
        LogFile.Write(data) ;

        index = 0 ;

        const TLiwGenericParam *MagneticCourseError  = outputlist->FindFirst(index , _L8("NMEASentenceStart") ) ;

        if(-1 != index)
            {
            Variant = MagneticCourseError->Value() ;


            }


        }


    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return KErrNone ;



    }


TInt CTestProvider :: getlocationPostionbased( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }




    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create notifications log file") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CTGetLocation") ;
    iLog->Log(KLog) ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {
        _LIT(KLog , "Interface not found");
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT(KClass,"GenericLocationInfo");
    inputlist->AppendL( TLiwGenericParam( KNullDesC8,TLiwVariant( KClass )  ) );

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog, "Success/Failure state not known") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }

    if((ErrorParm->Value()).AsTInt32() )
        {
        _LIT(KLog , "ExecutecmdL failed ");
        iLog->Log(KLog) ;
        return (ErrorParm->Value()).AsTInt32() ;	
        }



    TInt index = 0 ;

    const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KLocationMap);


    if(!GenericParam)
        {
        _LIT(Klog, "Out Param not found") ;
        iLog->Log(Klog) ;
        return KErrGeneral ; //Param Error
        }	

    TLiwVariant Variant ;

    Variant = GenericParam->Value() ;
    const	CLiwMap *LocMap = Variant.AsMap() ;

    TLiwVariant PosVariant ;

    LocMap->FindL(KLongitudeKey , PosVariant) ;
    TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
    data.Num(LongData , format) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Write(_L8("Logitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KLatitudeKey ,PosVariant) ; //Latitude 

    TReal64 LatData = (TReal64)PosVariant.AsTReal() ;
    data.Num(LatData , format) ;
    LogFile.Write(_L8("   Latitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KAltitudeKey , PosVariant) ; //Altitude
    TReal32 AltData = PosVariant.AsTReal() ;
    data.Num(AltData , format) ;

    LogFile.Write(_L8("   Altitude = "))	 ;
    LogFile.Write(data) ;


    TLiwVariant Speed ;

    index = LocMap->FindL(_L8("HorizontalSpeed") , Speed ) ;

    if(index )
        {

        TReal speed =  Speed.AsTReal() ;

        data.Num(speed , format) ;

        LogFile.Write(_L8("Speed = ")) ;
        LogFile.Write(data) ;

        }


    TLiwVariant SpeedError ;
    index = LocMap->FindL( _L8("HorizontalSpeedError") , SpeedError) ;


    if(index )
        {

        TReal speed =  SpeedError.AsTReal() ;

        data.Num(speed , format) ;

        LogFile.Write(_L8("Speed = ")) ;
        LogFile.Write(data) ;

        }

    index = 0 ;

    TLiwVariant SatInfo ;

    index = LocMap->FindL(_L8("SatelliteNumView") , SatInfo) ;

    if(index )
        {

        TInt satnumView = SatInfo.AsTInt32() ;
        data.Num(satnumView , format);

        LogFile.Write(_L8("Satellite information")) ;

        LogFile.Write(_L8("Number of visible satellites ")) ;
        LogFile.Write(data) ;
        }

    index = 0 ;

    TLiwVariant SatInfoview ;

    index = LocMap->FindL( _L8("SatelliteNumViewUsed") , SatInfoview) ;
    if(index )
        {


        TInt satnumViewUsed = SatInfoview.AsTInt32() ;
        data.Num(satnumViewUsed , format);

        LogFile.Write(_L8("\nSatellite information")) ;

        LogFile.Write(_L8("\nSatelliteNumViewUsed")) ;
        LogFile.Write(data) ;
        }

    index = 0 ;

    TInt Headinginfo = 0 ;

    TLiwVariant  Heading ;
    Headinginfo = LocMap->FindL(_L8("Heading") ,Heading) ;

    if(Headinginfo)
        {


        TReal heading = Heading.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\ncompass information")) ;

        LogFile.Write(_L8("\nHeading")) ;
        LogFile.Write(data) ;
        }


    if(Headinginfo)
        {
        TLiwVariant HeadingError ;
        index  = LocMap->FindL( _L8("HeadingError") , HeadingError ) ;

        if(index)
            {


            TReal heading = HeadingError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nHeading Error")) ;
            LogFile.Write(data) ;

            }

        TLiwVariant MagneticHeading ;
        index = LocMap->FindL( _L8("MagneticHeading") ,  MagneticHeading) ;

        if(index)
            {


            TReal heading = MagneticHeading.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\n MagneticHeading ")) ;
            LogFile.Write(data) ;

            }


        TLiwVariant MagneticHeadingError ;
        index = LocMap->FindL(_L8("MagneticHeadingError")  ,MagneticHeadingError) ;

        if(index)
            {


            TReal heading = MagneticHeadingError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nMagneticHeading Error")) ;
            LogFile.Write(data) ;

            }


        } //End of Heading



    TLiwVariant TrueCourse ;
    index = LocMap->FindL( _L8("TrueCourse") , TrueCourse ) ;

    if( index)
        {


        TReal heading = TrueCourse.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\nDirection ")) ;

        LogFile.Write(_L8("\n TrueCourse Error")) ;
        LogFile.Write(data) ;



        TLiwVariant TrueCourseError ;
        index  = LocMap->FindL( _L8("TrueCourseError") , TrueCourseError ) ;

        if( index)
            {


            TReal heading = TrueCourseError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nMagneticHeading Error")) ;
            LogFile.Write(data) ;

            }


        }


    TLiwVariant MagneticCourse ;
    index =  LocMap->FindL(_L8("MagneticCourse") , MagneticCourse ) ;


    if(index)
        {

        TReal heading = MagneticCourse.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\ncompass information")) ;

        LogFile.Write(_L8("\nMagneticCourse ")) ;
        LogFile.Write(data) ;



        TLiwVariant MagneticCourseError  ;
        index = LocMap->FindL(_L8("MagneticCourseError") ,MagneticCourseError ) ;

        if( index)
            {


            TReal heading = MagneticCourseError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\n MagneticCourseError Error")) ;
            LogFile.Write(data) ;

            }


        }



    TLiwVariant NmeaNum ;
    index = LocMap->FindL(_L8("NMEASentence") , NmeaNum ) ;  	 


    if(index)
        {

        TInt32 NMEASentence = NmeaNum.AsTInt32() ;
        data.Num(NMEASentence , format);

        LogFile.Write(_L8("\nNMEA Information")) ;

        LogFile.Write(_L8("\n number of NMEA Sentences ")) ;
        LogFile.Write(data) ;

        index = 0 ;

        const TLiwGenericParam *MagneticCourseError  = outputlist->FindFirst(index , _L8("NMEASentenceStart") ) ;

        if(-1 != index)
            {
            Variant = MagneticCourseError->Value() ;


            }


        }


    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return KErrNone ;



    }


TInt CTestProvider :: CancelWithInvalidTransId(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }


    _LIT(LogFileNameCancel , "C:\\cancelinvalid.txt") ;

    if(LogFile.Open(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create  log file\n") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CancelWithInvalidTransactionID\n") ;
    data.Copy(KLog);
    LogFile.Write(data) ;

    User::After(5000000);



    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    ASyncLocCBF* callBack ;

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist\n") ;
        data.Copy(Klog);
        LogFile.Write(data) ;

        //LogFile.Write(Klog) ;
        return KErrGeneral ;
        }

    TInt reqerror = (ErrorParm->Value()).AsTInt32();
    _LIT(Klog , "ERRor code from getlocationasynch  ") ;
    data.Copy(Klog);
    LogFile.Write(data) ;

    //LogFile.Write(Klog) ;

    TReal64 errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;


    pos = 0;

    _LIT8(KTransactionId, "TransactionID");
    const TLiwGenericParam *transid =  outputlist->FindFirst(pos ,KTransactionId ) ;
    if(!transid)
        {
        _LIT(KTran,"Missing Transaction ID\n");
        data.Copy(KTran);
        LogFile.Write(data) ;
        //LogFile.Write(KTran);
        return KErrGeneral;
        }
    TInt trid = (transid->Value()).AsTInt32();
    outputlist->Reset() ;
    inputlist->Reset() ;


    inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid-2)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);

    ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist in cancel\n ") ;
        data.Copy(Klog);
        LogFile.Write(data) ;
        //LogFile.Write(Klog);
        return KErrGeneral ;
        }

    reqerror = (ErrorParm->Value()).AsTInt32();

    _LIT(Klog1 , "\nERRor code from cancel  ") ;

    data.Copy(Klog1);
    LogFile.Write(data) ;	
    //LogFile.Write(Klog1) ;

    errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;
    if( SErrNotFound == reqerror )
        {
        reqerror = 0;	
        }






    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return reqerror ;



    }


TInt CTestProvider :: GetLocationSynchWrongUpdateMapType(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();


    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT8(KLocCategory,"LocationInformationClass");
    _LIT16(KBasic,"BasicLocationInformation");
    inputlist->AppendL(TLiwGenericParam(KLocCategory,TLiwVariant(KBasic)));



    _LIT8(KUpdate,"Updateoptions");
    inputlist->AppendL(TLiwGenericParam(KUpdate,TLiwVariant(30)));


    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;


    if(!ErrorParm)
        {
        locinterface->Close() ;
        delete ServiceHandler ;
        a.ResetAndDestroy() ;
        a.Close() ;
        return KErrGeneral ;
        }

    TInt err = (ErrorParm->Value()).AsTInt32();

    if( SErrBadArgumentType == err )
        {
        _LIT8(KErrorMessage,"ErrorMessage");
        _LIT(KNone,"Error");

        TPtrC errorstring(KNone);
        pos = 0;
        const TLiwGenericParam *ErrorParmstring =  outputlist->FindFirst(pos ,KErrorMessage ) ;
        TLiwVariant variant =  ErrorParmstring->Value();
        errorstring.Set( variant.AsDes() );

        locinterface->Close() ;
        delete ServiceHandler ;
        a.ResetAndDestroy() ;
        a.Close() ;
        __UHEAP_MARKEND ;
        return KErrNone;	
        }







    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return err ;



    }


TInt CTestProvider :: CTestGetLocation()
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }




    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create notifications log file") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CTGetLocation") ;
    iLog->Log(KLog) ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {
        _LIT(KLog , "Interface not found");
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog, "Success/Failure state not known") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }

    if((ErrorParm->Value()).AsTInt32() )
        {
        _LIT(KLog , "ExecutecmdL failed ");
        iLog->Log(KLog) ;
        return (ErrorParm->Value()).AsTInt32() ;	
        }



    TInt index = 0 ;

    const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KLocationMap);


    if(!GenericParam)
        {
        _LIT(Klog, "Out Param not found") ;
        iLog->Log(Klog) ;
        return KErrGeneral ; //Param Error
        }	

    TLiwVariant Variant ;

    Variant = GenericParam->Value() ;
    const	CLiwMap *LocMap = Variant.AsMap() ;

    TLiwVariant PosVariant ;

    LocMap->FindL(KLongitudeKey , PosVariant) ;
    TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
    data.Num(LongData , format) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Write(_L8("Logitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KLatitudeKey ,PosVariant) ; //Latitude 

    TReal64 LatData = (TReal64)PosVariant.AsTReal() ;
    data.Num(LatData , format) ;
    LogFile.Write(_L8("   Latitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KAltitudeKey , PosVariant) ; //Altitude
    TReal32 AltData = PosVariant.AsTReal() ;
    data.Num(AltData , format) ;

    LogFile.Write(_L8("   Altitude = "))	 ;
    LogFile.Write(data) ;

    TLiwVariant Accuracy;
    index = LocMap->FindL(_L8("HorizontalAccuracy"),Accuracy);

    if(index)
        {
        TReal32 AccuracyVal = Accuracy.AsTReal();
        data.Num(AccuracyVal , format) ;

        LogFile.Write(_L8("Horizontal Acc = ")) ;
        LogFile.Write(data) ;
        }

    Accuracy.Reset();
    index = LocMap->FindL(_L8("VerticalAccuracy"),Accuracy);

    if(index)
        {
        TReal32 AccuracyVal = Accuracy.AsTReal();
        data.Num(AccuracyVal , format) ;

        LogFile.Write(_L8("Vertical Acc = ")) ;
        LogFile.Write(data) ;
        }
    TLiwVariant Speed ;

    index = LocMap->FindL(_L8("HorizontalSpeed") , Speed ) ;

    if(index )
        {

        TReal speed =  Speed.AsTReal() ;

        data.Num(speed , format) ;

        LogFile.Write(_L8("Speed = ")) ;
        LogFile.Write(data) ;

        }


    TLiwVariant SpeedError ;
    index = LocMap->FindL( _L8("HorizontalSpeedError") , SpeedError) ;


    if(index )
        {

        TReal speed =  SpeedError.AsTReal() ;

        data.Num(speed , format) ;

        LogFile.Write(_L8("Speed = ")) ;
        LogFile.Write(data) ;

        }

    index = 0 ;

    TLiwVariant SatInfo ;

    index = LocMap->FindL(_L8("SatelliteNumView") , SatInfo) ;

    if(index )
        {

        TInt satnumView = SatInfo.AsTInt32() ;
        data.Num(satnumView , format);

        LogFile.Write(_L8("Satellite information")) ;

        LogFile.Write(_L8("Number of visible satellites ")) ;
        LogFile.Write(data) ;
        }

    index = 0 ;

    TLiwVariant SatInfoview ;

    index = LocMap->FindL( _L8("SatelliteNumViewUsed") , SatInfoview) ;
    if(index )
        {


        TInt satnumViewUsed = SatInfoview.AsTInt32() ;
        data.Num(satnumViewUsed , format);

        LogFile.Write(_L8("\nSatellite information")) ;

        LogFile.Write(_L8("\nSatelliteNumViewUsed")) ;
        LogFile.Write(data) ;
        }

    index = 0 ;

    TInt Headinginfo = 0 ;

    TLiwVariant  Heading ;
    Headinginfo = LocMap->FindL(_L8("Heading") ,Heading) ;

    if(Headinginfo)
        {


        TReal heading = Heading.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\ncompass information")) ;

        LogFile.Write(_L8("\nHeading")) ;
        LogFile.Write(data) ;
        }


    if(Headinginfo)
        {
        TLiwVariant HeadingError ;
        index  = LocMap->FindL( _L8("HeadingError") , HeadingError ) ;

        if(index)
            {


            TReal heading = HeadingError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nHeading Error")) ;
            LogFile.Write(data) ;

            }

        TLiwVariant MagneticHeading ;
        index = LocMap->FindL( _L8("MagneticHeading") ,  MagneticHeading) ;

        if(index)
            {


            TReal heading = MagneticHeading.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\n MagneticHeading ")) ;
            LogFile.Write(data) ;

            }


        TLiwVariant MagneticHeadingError ;
        index = LocMap->FindL(_L8("MagneticHeadingError")  ,MagneticHeadingError) ;

        if(index)
            {


            TReal heading = MagneticHeadingError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nMagneticHeading Error")) ;
            LogFile.Write(data) ;

            }


        } //End of Heading



    TLiwVariant TrueCourse ;
    index = LocMap->FindL( _L8("TrueCourse") , TrueCourse ) ;

    if( index)
        {


        TReal heading = TrueCourse.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\nDirection ")) ;

        LogFile.Write(_L8("\n TrueCourse Error")) ;
        LogFile.Write(data) ;



        TLiwVariant TrueCourseError ;
        index  = LocMap->FindL( _L8("TrueCourseError") , TrueCourseError ) ;

        if( index)
            {


            TReal heading = TrueCourseError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nMagneticHeading Error")) ;
            LogFile.Write(data) ;

            }


        }


    TLiwVariant MagneticCourse ;
    index =  LocMap->FindL(_L8("MagneticCourse") , MagneticCourse ) ;


    if(index)
        {

        TReal heading = MagneticCourse.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\ncompass information")) ;

        LogFile.Write(_L8("\nMagneticCourse ")) ;
        LogFile.Write(data) ;



        TLiwVariant MagneticCourseError  ;
        index = LocMap->FindL(_L8("MagneticCourseError") ,MagneticCourseError ) ;

        if( index)
            {


            TReal heading = MagneticCourseError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\n MagneticCourseError Error")) ;
            LogFile.Write(data) ;

            }


        }



    TLiwVariant NmeaNum ;
    index = LocMap->FindL(_L8("NMEASentence") , NmeaNum ) ;  	 


    if(index)
        {

        TInt32 NMEASentence = NmeaNum.AsTInt32() ;
        data.Num(NMEASentence , format);

        LogFile.Write(_L8("\nNMEA Information")) ;

        LogFile.Write(_L8("\n number of NMEA Sentences ")) ;
        LogFile.Write(data) ;

        index = 0 ;

        const TLiwGenericParam *MagneticCourseError  = outputlist->FindFirst(index , _L8("NMEASentenceStart") ) ;

        if(-1 != index)
            {
            Variant = MagneticCourseError->Value() ;


            }


        }


    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return KErrNone ;



    }


TInt CTestProvider :: GetLocation(CStifItemParser & /*aItem */)
    {
    __UHEAP_MARK ; 
    TInt ret = CTestGetLocation() ;
    __UHEAP_MARKEND ;
    return ret ;

    }


TInt CTestProvider :: LocationUpdates(CStifItemParser& /*aItem*/)
    {
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" LocationUpdates Thread") , GetLocUpdates ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);

    if(!ret)
        {
        FunctionThread.Logon(Status)	;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status)	;				
        FunctionThread.Close();

        ret = Status.Int() ;
        }
    return ret; 
    }    
#if 0 
TInt CTestProvider :: LastKnownLoc(CStifItemParser& /*aItem*/)
    {
    return KErrNone ;
    }
#endif	

TInt  CTestProvider ::GetLocationAsynch(CStifItemParser& /*aItem*/)
    {


    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    FunctionThread.Create(_L("GetLocationAsynch Thread") , FindLocationAsynch ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);

    FunctionThread.Logon(Status)	;
    FunctionThread.Resume() ;

    User :: WaitForRequest (Status)	;				
    FunctionThread.Close();

    return Status.Int() ;


    }


TInt  CTestProvider ::ServiceNotAvailable(CStifItemParser& /*aItem*/)
    {

    __UHEAP_MARK ;

    _LIT8(KService, "Service.Location");
    _LIT8(KIDataSource,"ILocation");

    return KErrNone ; //Manual test case 
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KService, KIDataSource);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;





    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {
        _LIT(KLog , "Interface not found");
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();


    TInt result = KErrGeneral ;
    TInt error ;
    TInt index = 0;


    //	CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;
    TBuf8<20>CmdBuf(KCmdGetLocation) ;
    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    locinterface->ExecuteCmdL(CmdBuf , *InputList , *InputList );
    const TLiwGenericParam *GenericParam = InputList->FindFirst(index , KErrorCode ) ;

    if(GenericParam)
        {
        TLiwVariant ErrorVariant = GenericParam->Value() ;

        error = ErrorVariant.AsTInt32();
        }

    if((error == KErrNotFound  ) || (error == KPositionQualityLoss))
        {
        _LIT(KLog , "positioning  technology not available") ;
        iLog->Log(KLog) ;
        result = KErrNone  ;
        } 


    locinterface->Close() ;
    delete 	InputList ;
    delete ServiceHandler ;

    a.ResetAndDestroy() ;
    //	delete  OutParmList ;
    __UHEAP_MARKEND ;
    return result  ;

    }



/*
 * This is a manual test case were the service was available when the 
 * request was made and then   Lost the service (Contact to location servier lost
 */


TInt CTestProvider :: ServiceFailed(CStifItemParser& /*aItem*/)
    {
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;
    _LIT(KLog , "In service failed test ") ;
    iLog->Log(KTLocTest) ;

    return KErrNone ; //Manual test case 
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret =  FunctionThread.Create(_L("ServiceFailed Thread") , ServiceFailedTest ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);;

            if(!ret)
                {

                _LIT(Klog , "Created the thread ") ;
                iLog->Log(Klog) ;
                FunctionThread.Logon(Status)	;
                FunctionThread.Resume() ;

                User :: WaitForRequest (Status)	;				
                FunctionThread.Close();

                ret = Status.Int() ;
                }


            if((ret == KErrNotFound  ) || (ret == KPositionQualityLoss))
                {
                _LIT(KLog , "Service provider crashed or went dowm") ;
                iLog->Log(KLog) ;
                }


            return ret;	
    }



/**
 *Stray signal test, tests for any unhandled events from location server
 */

TInt CTestProvider :: StraySignal(CStifItemParser& /*aItem*/)
    {
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;
    _LIT(KLog , "StraySignalTest ") ;
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret =  FunctionThread.Create(_L("stray signal") , StrayTest ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);;

            if(!ret)
                {

                _LIT(Klog , "Created the thread ") ;
                iLog->Log(Klog) ;
                FunctionThread.Logon(Status)	;
                FunctionThread.Resume() ;

                User :: WaitForRequest (Status)	;				
                FunctionThread.Close();

                ret = Status.Int() ;
                }

            return ret;	
    }



TInt CTestProvider :: StraySignalGetLoc(CStifItemParser& /*aItem*/)
    {
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;
    _LIT(KLog , "StraySignalTestGetLoc ") ;
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret =  FunctionThread.Create(_L("stray signal GetLocation") , StrayTestGetLoc ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);;

            if(!ret)
                {

                _LIT(Klog , "Created the thread ") ;
                iLog->Log(Klog) ;
                FunctionThread.Logon(Status)	;
                FunctionThread.Resume() ;

                User :: WaitForRequest (Status)	;				
                FunctionThread.Close();

                ret = Status.Int() ;
                }


            return ret;	
    }

TInt CTestProvider :: ConcurrentCallsGetLoc (CStifItemParser& /*aItem*/)
    {
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" ConcurrentCallsGetLoc Thread") , ConcurrentGetLocationCalls ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)	;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status)	;				


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        return KErrGeneral ;

    return KErrNone; 
    }


TInt CTestProvider :: ConcurrentCallsTrace (CStifItemParser& /*aItem*/)
    {
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" ConcurrentCallsGetLoc Thread") , TraceConcurrent ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)	;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status)	;				


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        {
        _LIT(KLog , "Return Type is valid");
        iLog->Log(KLog);
        }

    else
        {
        _LIT(KLog , "Return type is not valid\n") ;
        iLog->Log(KLog) ;	
        }	
    return KErrNone ;

    return KErrGeneral; 
    }


/**
 *Cancel test, to test cancel functionality
 */
TInt CTestProvider :: EmptyCancelTraceTest(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    _LIT(KLog , "CancellTest") ;


    iLog->Log(KLog) ;





    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();

    _LIT8(KCancell , "CancelNotification") ;
    _LIT8( KType ,"CancelRequestType") ;
    _LIT8( KTraceCancel ,"TraceCancel") ;
    inputlist->AppendL(TLiwGenericParam (KType , TLiwVariant (KTraceCancel))) ;

    locinterface->ExecuteCmdL(KCancell , *inputlist , *outputlist) ;

    pos = 0 ;
    const TLiwGenericParam  *errprm = outputlist->FindFirst(pos , KErrCode) ;

    if(!errprm)
        {
        _LIT(Kerr, "Success/Failure code missing from outputlist") ;
        iLog->Log(Kerr) ;
        }


    TInt ret = KErrGeneral ; //Return Code
    TLiwVariant var = errprm->Value() ;

    if(var.AsTInt32() == SErrBadArgumentType )
        {
        ret= KErrNone ;
        }
    else
        {
        _LIT(KDebugMsg , "Return and expected values are different") ;
        iLog->Log(KDebugMsg) ; 
        }

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;	




    return ret ;

    }

/**
 *Cancel test, to test cancel functionality
 */
TInt CTestProvider :: EmptyCancelGetLocTest(CStifItemParser& /*aItem*/)
    {
    _LIT(KLog , "CancellTest") ;
    iLog->Log(KLog) ;

    __UHEAP_MARK ;

    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();




    _LIT8(KCancell , "CancelNotification") ;
    _LIT8( KType ,"CancelRequestType") ;
    _LIT8( KGetLocCancel ,"GetLocCancel") ;
    inputlist->AppendL(TLiwGenericParam (KType , TLiwVariant (KGetLocCancel))) ;

    locinterface->ExecuteCmdL(KCancell , *inputlist , *outputlist) ;

    pos = 0 ;
    const TLiwGenericParam  *errprm = outputlist->FindFirst(pos , KErrCode) ;

    if(!errprm)
        {
        _LIT(Kerr, "Success/Failure code missing from outputlist") ;
        iLog->Log(Kerr) ;
        }


    TInt ret = KErrGeneral ; 

    if((errprm->Value()).AsTInt32() == SErrBadArgumentType)
        {
        ret = KErrNone  ;
        }

    locinterface->Close() ;

    //delete inlist ;
    //Sdelete outlist ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    __UHEAP_MARKEND ; 

    return ret ;

    }

/**
 *Cancel test, with wrong notification
 */
TInt CTestProvider :: CancelWrongNotification1(CStifItemParser& /*aItem*/)
    {


    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;
    _LIT(KLog , "StraySignalTest ") ;
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret =  FunctionThread.Create(_L("Wrong Notification GetLoc cancel") , GetLocWrongCancel ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);;

            if(!ret)
                {

                _LIT(Klog , "Created the thread ") ;
                iLog->Log(Klog) ;
                FunctionThread.Logon(Status)	;
                FunctionThread.Resume() ;

                User :: WaitForRequest (Status)	;				
                FunctionThread.Close();

                ret = Status.Int() ;
                }
            else
                {
                return ret ;
                }

            if(ret == SErrBadArgumentType)  
                {
                ret = KErrNone ;
                }
            /*else
	    {
	        ret = KErrGeneral ;
	    } */
            return ret;	
    }



/**
 *Cancel test, with wrong notification issues a Trace request and then calls for getlocation 
 * cancellation
 */
TInt CTestProvider :: CancelWrongNotification2(CStifItemParser& /*aItem*/)
    {


    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;
    _LIT(KLog , "CancelWrongNotification2 ") ;
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret =  FunctionThread.Create(_L("Wrong Notification Trace cancel") , TraceLocWrongCancel ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);;

            if(!ret)
                {

                _LIT(Klog , "Created the thread ") ;
                iLog->Log(Klog) ;
                FunctionThread.Logon(Status)	;
                FunctionThread.Resume() ;

                User :: WaitForRequest (Status)	;				
                FunctionThread.Close();

                ret = Status.Int() ;
                }
            else
                {
                return ret ;
                }

            if(ret == SErrBadArgumentType)  
                {
                ret = KErrNone ;
                }

            return ret;	
    }


/**
 *Cancel test, Normal cancel test for getlocation 
 */
TInt CTestProvider :: GetLocationCancel(CStifItemParser& /*aItem*/)
    {


    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;
    _LIT(KLog , "Getlocationcancel ") ;
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret =  FunctionThread.Create(_L("Getlocationcancel ") , GetLocCancel  ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);;

            if(!ret)
                {

                _LIT(Klog , "Created the thread ") ;
                iLog->Log(Klog) ;
                FunctionThread.Logon(Status)	;
                FunctionThread.Resume() ;

                User :: WaitForRequest (Status)	;				
                FunctionThread.Close();

                ret = Status.Int() ;
                }
            else
                {
                return ret ;
                }


            return ret;	
    }

/**
 * GetLocation Timeout
 */
TInt CTestProvider :: GetLocationTimedOut(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;
    _LIT(KLog , "GetLocationTimedOut ") ;
    iLog->Log(KTLocTest) ;

    return KErrNone ; //This is a manul test case
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
    inputlist->Reset();
    outputlist->Reset();
    const  TInt Ksecond = 1000000;
    const TInt KUpdatetimeOut = 100 ; //*Ksecond ;

    //SetUpdate time out less then 2 second(response time) ;
    CLiwMap *UpdateOptsMap = CLiwDefaultMap :: NewL() ;

    UpdateOptsMap->InsertL(KUpdateOptionTimeOut , (TInt32)KUpdatetimeOut) ;

    inputlist->AppendL(TLiwGenericParam (KUpdateOptionMap , TLiwVariant(UpdateOptsMap)) ) ;

    TBuf8<20>CmdBufSet(KCmdGetLocation)  ;

    locinterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist);
    UpdateOptsMap->DecRef() ;

    pos = 0 ;

    const TLiwGenericParam *errcode = outputlist->FindFirst(pos , KErrCode) ;

    if(pos == KErrNotFound)
        {
        _LIT(KLog , "Success/Error Code is missing ") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    pos = (errcode->Value()).AsTInt32() ;

    delete ServiceHandler ;
    delete crit ;
    locinterface->Close() ;
    __UHEAP_MARKEND ;
    if(pos == KErrTimedOut)
        {
        return KErrNone ;
        }

    _LIT(Kerr , "Time out value not set correctly") ;    
    return KErrNone ;

    }

/**
 *Normal Trace cancell test.
 */
TInt CTestProvider :: TraceLocationCancel(CStifItemParser& /*aItem*/)
    {


    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;
    _LIT(KLog , "Getlocationcancel ") ;
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret =  FunctionThread.Create(_L("Getlocationcancel ") , TraceLocCancel  ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);;

            if(!ret)
                {

                _LIT(Klog , "Created the thread ") ;
                iLog->Log(Klog) ;
                FunctionThread.Logon(Status)	;
                FunctionThread.Resume() ;

                User :: WaitForRequest (Status)	;				
                FunctionThread.Close();

                ret = Status.Int() ;
                }
            else
                {
                return ret ;
                }


            return ret;	
    }

/**
 *Math Operation Find distance : Position based parameter
 */
TInt CTestProvider :: FindDistanceAgain(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK;
    TInt start = User::CountAllocCells();
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KRequestCalculate) ;

    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    TLiwGenericParam requesttype(KNullDesC8 , TLiwVariant(KRequestBearingTo)) ;
    InputList->AppendL(requesttype) ;

    //Inserting first input param
    CLiwMap* SourceCoordinate = CLiwDefaultMap::NewL();
    TReal64 slongitude = 22;
    SourceCoordinate->InsertL(KLongitudeKey,TLiwVariant(slongitude));
    TReal64 slatitude = 88;
    SourceCoordinate->InsertL(KLatitudeKey,TLiwVariant(slatitude));
    TReal64 saltitude = 1;
    SourceCoordinate->InsertL(KAltitudeKey,TLiwVariant(slatitude));

    TLiwGenericParam scoordinate(KNullDesC8,TLiwVariant(SourceCoordinate));
    InputList->AppendL(scoordinate) ;
    SourceCoordinate->DecRef() ;



    //Inserting 2nd input param
    CLiwDefaultMap* DestCoordinate = CLiwDefaultMap::NewL();
    TReal64 dlongitude = 13;
    DestCoordinate->InsertL(KLongitudeKey,TLiwVariant(dlongitude));
    TReal64 dlatitude = 77;


    DestCoordinate->InsertL(KLatitudeKey,TLiwVariant(dlatitude));
    TReal64 daltitude = 1;
    DestCoordinate->InsertL(KAltitudeKey,TLiwVariant(dlatitude));

    TLiwGenericParam dcoordinate(KNullDesC8,TLiwVariant(DestCoordinate));
    InputList->AppendL(dcoordinate) ;
    DestCoordinate->DecRef() ;


    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;


    CmdBuf = KRequestCalculate ;

    locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList);


    pos = 0;
    const TLiwGenericParam* param = OutParmList->FindFirst(pos, KErrorCode);

    pos = 0;
    const TLiwGenericParam* resultparam = OutParmList->FindFirst(pos, KMathOpResult);		
    TLiwVariant resultvariant = resultparam->Value();
    TReal32 bearingTo = resultvariant.AsTReal();




    //Logging result into a file
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> Buffer(_L8("BearingTo = ")) ;
    LogSession.Connect() ;

    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
        }

    TInt End = 0 ;

    LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 

    TBuf8<50> num ;
    TRealFormat format ;

    num.Num(bearingTo , format) ;


    LogFile.Write(_L8("BearingTo= "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    OutParmList->Reset();
    InputList->Reset();
    delete OutParmList ;
    delete InputList ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;

    TInt end = User::CountAllocCells();
    __UHEAP_MARKEND ;   



    return KErrNone ;




    }
/**
 * Math operation BearingTo Test
 */

TInt CTestProvider ::BearingToTest(CStifItemParser& /*aItem*/) 
    {
    __UHEAP_MARK ;

    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
    TBuf8<20>CmdBuf(KRequestCalculate) ;

    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    TLiwGenericParam requesttype(KMathRequest , TLiwVariant(KRequestBearingTo)) ;
    InputList->AppendL(requesttype) ;

    //Inserting first input param
    CLiwMap* SourceCoordinate = CLiwDefaultMap::NewL();
    TReal64 slongitude = 22;
    SourceCoordinate->InsertL(KLongitudeKey,TLiwVariant(slongitude));
    TReal64 slatitude = 88;
    SourceCoordinate->InsertL(KLatitudeKey,TLiwVariant(slatitude));
    TReal64 saltitude = 1;
    SourceCoordinate->InsertL(KAltitudeKey,TLiwVariant(slatitude));

    TLiwGenericParam scoordinate(KDistanceParmSource,TLiwVariant(SourceCoordinate));
    InputList->AppendL(scoordinate) ;
    SourceCoordinate->DecRef() ;



    //Inserting 2nd input param
    CLiwMap* DestCoordinate = CLiwDefaultMap::NewL();
    TReal64 dlongitude = 13;
    DestCoordinate->InsertL(KLongitudeKey,TLiwVariant(dlongitude));
    TReal64 dlatitude = 77;
    DestCoordinate->InsertL(KLatitudeKey,TLiwVariant(dlatitude));
    TReal64 daltitude = 1;
    DestCoordinate->InsertL(KAltitudeKey,TLiwVariant(dlatitude));

    TLiwGenericParam dcoordinate(KDistanceParmDestination,TLiwVariant(DestCoordinate));
    InputList->AppendL(dcoordinate) ;
    DestCoordinate->DecRef() ;


    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;


    CmdBuf = KRequestCalculate ;

    locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList);


    pos = 0;
    const TLiwGenericParam* param = OutParmList->FindFirst(pos, KErrorCode);

    pos = 0;
    const TLiwGenericParam* resultparam = OutParmList->FindFirst(pos, KMathOpResult);		
    TLiwVariant resultvariant = resultparam->Value();
    TReal32 bearingTo = resultvariant.AsTReal();




    //Logging result into a file
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> Buffer(_L8("BearingTo = ")) ;
    LogSession.Connect() ;

    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
        }

    TInt End = 0 ;

    LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 

    TBuf8<50> num ;
    TRealFormat format ;

    num.Num(bearingTo , format) ;


    LogFile.Write(_L8("BearingTo= "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Close() ;
    LogSession.Close() ;

    delete OutParmList ; 
    dcoordinate.Reset() ;
    scoordinate.Reset() ;
    delete InputList ;   
    locinterface->Close() ;
    inputlist->Reset() ;
    outputlist->Reset() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    __UHEAP_MARKEND ;  
    return KErrNone ;


    }

TInt CTestProvider ::FindDistance(CStifItemParser& /*aItem*/) 
    {
    __UHEAP_MARK ;
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
    //First set the identity information

    ;
    TBuf8<20>CmdBufSet(KRequestCalculate) ;
    outputlist->Reset() ;
    inputlist->Reset() ;

    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    TLiwGenericParam requesttype(KMathRequest , TLiwVariant(KRequestDistance)) ;
    InputList->AppendL(requesttype) ;



    //Inserting first input param
    CLiwMap* SourceCoordinate = CLiwDefaultMap::NewL();
    TReal64 slongitude = 71.03;
    SourceCoordinate->InsertL(KLongitudeKey,TLiwVariant(slongitude));
    TReal64 slatitude = 42.37;
    SourceCoordinate->InsertL(KLatitudeKey,TLiwVariant(slatitude));
    TReal64 saltitude = 1;
    SourceCoordinate->InsertL(KAltitudeKey,TLiwVariant(slatitude));

    TLiwGenericParam scoordinate(KDistanceParmSource,TLiwVariant(SourceCoordinate));
    InputList->AppendL(scoordinate) ;
    SourceCoordinate->DecRef() ;



    //Inserting 2nd input param
    CLiwMap* DestCoordinate = CLiwDefaultMap::NewL();
    TReal64 dlongitude = 83.02;
    DestCoordinate->InsertL(KLongitudeKey,TLiwVariant(dlongitude));
    TReal64 dlatitude = 42.42;
    DestCoordinate->InsertL(KLatitudeKey,TLiwVariant(dlatitude));
    TReal64 daltitude = 1;
    DestCoordinate->InsertL(KAltitudeKey,TLiwVariant(dlatitude));

    TLiwGenericParam dcoordinate(KDistanceParmDestination,TLiwVariant(DestCoordinate));
    InputList->AppendL(dcoordinate) ;
    DestCoordinate->DecRef() ;  

    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;


    CmdBufSet = KRequestCalculate ;

    locinterface->ExecuteCmdL(CmdBufSet , *InputList , *OutParmList);


    pos = 0;
    const TLiwGenericParam* param = OutParmList->FindFirst(pos, KErrorCode);


    pos = 0;
    const TLiwGenericParam* resultparam = OutParmList->FindFirst(pos, KMathOpResult);		
    TLiwVariant resultvariant = resultparam->Value();
    TReal64 distance = resultvariant.AsTReal();




    //Logging result into a file
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> Buffer(_L8("Distance = ")) ;
    LogSession.Connect() ;

    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

        }

    TInt End = 0 ;

    LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 

    TBuf8<50> num ;
    TRealFormat format ;
    //TReal64 Val = aPosition.Latitude() ;
    num.Num(distance , format) ;

    //Logging Latitude 
    LogFile.Write(_L8("distance = "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Close() ;
    LogSession.Close() ;

    delete InputList ;
    delete OutParmList ;
    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;

    __UHEAP_MARKEND ;  
    return KErrNone ;




    }

TInt CTestProvider ::GetLocationUpdateOpts(CStifItemParser& /*aItem*/) 
    {

    __UHEAP_MARK;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;
    LogSession.Connect()  ;
    _LIT8(KLog , "GetLocationUpdateOPts") ;
    iLog->Log(KLog) ;



    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
        }

    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();

    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    //Append LocationInformation Category
    TLiwGenericParam informationCategory(KLocationInfoCategory , TLiwVariant(KLocationBasicinfo)) ;
    InputList->AppendL(informationCategory) ;

    //Appending update options
    CLiwMap* updateoptionMap = CLiwDefaultMap::NewL();

    TInt32 updateInterval = 30000;

    updateoptionMap->InsertL(KUpdateOptionInterval,TLiwVariant(updateInterval));

    TInt32 updateTimeOut = 10000;
    updateoptionMap->InsertL(KUpdateOptionTimeOut,TLiwVariant(updateTimeOut));

    TInt32 updateMaxAge = 2000;
    updateoptionMap->InsertL(KUpdateOptionMaxAge,TLiwVariant(updateMaxAge));

    TLiwGenericParam updateOption(KUpdateOptionMap,TLiwVariant(updateoptionMap));
    InputList->AppendL(updateOption) ;

    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;




    locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList);


    pos = 0;
    const TLiwGenericParam* param = OutParmList->FindFirst(pos, KErrorCode);


    pos = 0;
    const TLiwGenericParam* resultparam = OutParmList->FindFirst(pos, KLocationMap);		
    TLiwVariant resultvariant = resultparam->Value();

    const CLiwMap *LocMap = resultvariant.AsMap() ;

    TLiwVariant PosVariant ;

    LocMap->FindL(KLongitudeKey , PosVariant) ;


    TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
    data.Num(LongData , format) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Write(_L8("Logitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KLatitudeKey ,PosVariant) ; //Latitude 

    TReal64 LatData = (TReal64)PosVariant.AsTReal() ;
    data.Num(LatData , format) ;
    LogFile.Write(_L8("   Latitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KAltitudeKey , PosVariant) ; //Altitude
    TReal32 AltData = PosVariant.AsTReal() ;
    data.Num(AltData , format) ;

    LogFile.Write(_L8("   Altitude = "))	 ;
    LogFile.Write(data) ;
    LogFile.Close() ;
    locinterface->Close() ;
    LogSession.Close() ;

    delete ServiceHandler ;
    InputList->Reset();
    OutParmList->Reset();
    delete InputList ;
    delete OutParmList ;
    __UHEAP_MARKEND;
    return KErrNone ;

    }



void  FillCoordinatesL ( TCoordinate &aCoordinate , const CLiwMap *aMap )
    {
    __UHEAP_MARK ;
    TLiwVariant longitudevar ;
    TLiwVariant latitudevar ;
    TLiwVariant altitudevar ;

    aMap->FindL(KLongitudeKey , longitudevar) ;
    aMap->FindL(KLatitudeKey ,  latitudevar) ;
    aMap->FindL(KAltitudeKey , altitudevar ) ;

    TReal64 latitude = (TReal64)latitudevar.AsTReal() ; 
    TReal64 longitude = (TReal64)longitudevar.AsTReal() ;
    TReal32 altitude = (TReal32)altitudevar.AsTReal() ;

    aCoordinate.SetCoordinate( latitude , longitude , altitude) ;

    __UHEAP_MARKEND ;
    }

/**
 * Math Function test Move coordinates
 */

TInt CTestProvider :: MoveCoordinates(CStifItemParser& /*aItem*/)
    {

    __UHEAP_MARK ;
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();

    TBuf8<20>CmdBuf(KRequestCalculate) ;
    outputlist->Reset() ;
    inputlist->Reset() ;   


    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    TLiwGenericParam requesttype(KMathRequest , TLiwVariant(KRequestMove)) ;
    InputList->AppendL(requesttype) ;


    //Inserting first input param
    CLiwMap* SourceCoordinate = CLiwDefaultMap::NewL();
    TReal64 slongitude = 22;
    SourceCoordinate->InsertL(KLongitudeKey,TLiwVariant(slongitude));
    TReal64 slatitude = 88;
    SourceCoordinate->InsertL(KLatitudeKey,TLiwVariant(slatitude));

    TReal64 saltitude = 1;
    SourceCoordinate->InsertL(KAltitudeKey,TLiwVariant(saltitude));



    TLiwGenericParam scoordinate(KDistanceParmSource,TLiwVariant(SourceCoordinate));
    InputList->AppendL(scoordinate) ;
    SourceCoordinate->DecRef() ;



    TReal32 distanceToMove = 345;
    TReal32 bearingToMove = 45;


    //Inserting distance by which coordinate should be moved
    TLiwVariant distanceVal((TReal)distanceToMove);
    TLiwGenericParam distanceParam(KDistanceMove,distanceVal);
    InputList->AppendL(distanceParam);

    //Inserting bearing by which coordinate should be moved
    TLiwVariant bearingVal((TReal)bearingToMove);
    TLiwGenericParam bearingParam(KBearingMove,bearingVal);
    InputList->AppendL(bearingParam);





    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;




    locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList);





    TInt mathindex = 0;

    // calculation							  						
    const TLiwGenericParam *smapparam = OutParmList->FindFirst(mathindex , KLocationMap) ;
    TLiwVariant mapVariant= smapparam->Value() ; 
    const CLiwMap  *map = mapVariant.AsMap() ;
    TCoordinate source  ;

    FillCoordinatesL(source , map) ;

    TReal64 longitudeInputVal = source.Longitude(); 		
    TReal64 latitudeInputVal = source.Latitude(); 
    TReal64 altitudeInputVal = source.Altitude(); 


    //Logging result into a file
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> Buffer(_L8("Longitude = ")) ;
    LogSession.Connect() ;

    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

        }

    TInt End = 0 ;

    LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 

    TBuf8<50> num ;
    TRealFormat format ;

    num.Num(longitudeInputVal, format) ;

    //Logging 
    LogFile.Write(_L8("Longitude = "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    //LogFile.Seek(ESeekEnd , End) ;
    num.Num(latitudeInputVal, format) ;
    LogFile.Write(_L8("Latitude = "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    num.Num(altitudeInputVal, format) ;
    LogFile.Write(_L8("altitude = "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Close() ;
    LogSession.Close() ;

    delete OutParmList ;
    delete InputList ;
    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    __UHEAP_MARKEND ;
    return KErrNone ;
    }






TInt CTestProvider :: GetLastLocation(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }




    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create notifications log file") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CTGetLocation") ;
    iLog->Log(KLog) ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {
        _LIT(KLog , "Interface not found");
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    //TBuf8<20>CmdBuf(KCmdGetLocation) ;
    TBuf8<20>CmdBuf(_L8("GetLastPosition"));
    outputlist->Reset() ;
    inputlist->Reset() ;

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog, "Success/Failure state not known") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }

    if((ErrorParm->Value()).AsTInt32() )
        {
        _LIT(KLog , "ExecutecmdL failed ");
        iLog->Log(KLog) ;
        return (ErrorParm->Value()).AsTInt32() ;    
        }



    TInt index = 0 ;

    const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KLocationMap);


    if(!GenericParam)
        {
        _LIT(Klog, "Out Param not found") ;
        iLog->Log(Klog) ;
        return KErrGeneral ; //Param Error
        }   

    TLiwVariant Variant ;

    Variant = GenericParam->Value() ;
    const   CLiwMap *LocMap = Variant.AsMap() ;

    TLiwVariant PosVariant ;

    LocMap->FindL(KLongitudeKey , PosVariant) ;
    TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
    data.Num(LongData , format) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Write(_L8("Logitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KLatitudeKey ,PosVariant) ; //Latitude 

    TReal64 LatData = (TReal64)PosVariant.AsTReal() ;
    data.Num(LatData , format) ;
    LogFile.Write(_L8("   Latitude = ")) ;
    LogFile.Write(data) ;

    LocMap->FindL(KAltitudeKey , PosVariant) ; //Altitude
    TReal32 AltData = PosVariant.AsTReal() ;
    data.Num(AltData , format) ;

    LogFile.Write(_L8("   Altitude = "))     ;
    LogFile.Write(data) ;


    TLiwVariant Speed ;

    index = LocMap->FindL(_L8("HorizontalSpeed") , Speed ) ;

    if(index )
        {

        TReal speed =  Speed.AsTReal() ;

        data.Num(speed , format) ;

        LogFile.Write(_L8("Speed = ")) ;
        LogFile.Write(data) ;

        }
    TLiwVariant Accuracy;
    index = LocMap->FindL(_L8("HorizontalAccuracy"),Accuracy);

    if(index)
        {
        TReal32 AccuracyVal = Accuracy.AsTReal();
        data.Num(AccuracyVal , format) ;

        LogFile.Write(_L8("Horizontal Acc = ")) ;
        LogFile.Write(data) ;
        }

    Accuracy.Reset();
    index = LocMap->FindL(_L8("VerticalAccuracy"),Accuracy);

    if(index)
        {
        TReal32 AccuracyVal = Accuracy.AsTReal();
        data.Num(AccuracyVal , format) ;

        LogFile.Write(_L8("Vertical Acc = ")) ;
        LogFile.Write(data) ;
        }

    TLiwVariant SpeedError ;
    index = LocMap->FindL( _L8("HorizontalSpeedError") , SpeedError) ;


    if(index )
        {

        TReal speed =  SpeedError.AsTReal() ;

        data.Num(speed , format) ;

        LogFile.Write(_L8("Speed = ")) ;
        LogFile.Write(data) ;

        }

    index = 0 ;

    TLiwVariant SatInfo ;

    index = LocMap->FindL(_L8("SatelliteNumView") , SatInfo) ;

    if(index )
        {

        TInt satnumView = SatInfo.AsTInt32() ;
        data.Num(satnumView , format);

        LogFile.Write(_L8("Satellite information")) ;

        LogFile.Write(_L8("Number of visible satellites ")) ;
        LogFile.Write(data) ;
        }

    index = 0 ;

    TLiwVariant SatInfoview ;

    index = LocMap->FindL( _L8("SatelliteNumViewUsed") , SatInfoview) ;
    if(index )
        {


        TInt satnumViewUsed = SatInfoview.AsTInt32() ;
        data.Num(satnumViewUsed , format);

        LogFile.Write(_L8("\nSatellite information")) ;

        LogFile.Write(_L8("\nSatelliteNumViewUsed")) ;
        LogFile.Write(data) ;
        }

    index = 0 ;

    TInt Headinginfo = 0 ;

    TLiwVariant  Heading ;
    Headinginfo = LocMap->FindL(_L8("Heading") ,Heading) ;

    if(Headinginfo)
        {


        TReal heading = Heading.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\ncompass information")) ;

        LogFile.Write(_L8("\nHeading")) ;
        LogFile.Write(data) ;
        }


    if(Headinginfo)
        {
        TLiwVariant HeadingError ;
        index  = LocMap->FindL( _L8("HeadingError") , HeadingError ) ;

        if(index)
            {


            TReal heading = HeadingError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nHeading Error")) ;
            LogFile.Write(data) ;

            }

        TLiwVariant MagneticHeading ;
        index = LocMap->FindL( _L8("MagneticHeading") ,  MagneticHeading) ;

        if(index)
            {


            TReal heading = MagneticHeading.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\n MagneticHeading ")) ;
            LogFile.Write(data) ;

            }


        TLiwVariant MagneticHeadingError ;
        index = LocMap->FindL(_L8("MagneticHeadingError")  ,MagneticHeadingError) ;

        if(index)
            {


            TReal heading = MagneticHeadingError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nMagneticHeading Error")) ;
            LogFile.Write(data) ;

            }


        } //End of Heading



    TLiwVariant TrueCourse ;
    index = LocMap->FindL( _L8("TrueCourse") , TrueCourse ) ;

    if( index)
        {


        TReal heading = TrueCourse.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\nDirection ")) ;

        LogFile.Write(_L8("\n TrueCourse Error")) ;
        LogFile.Write(data) ;



        TLiwVariant TrueCourseError ;
        index  = LocMap->FindL( _L8("TrueCourseError") , TrueCourseError ) ;

        if( index)
            {


            TReal heading = TrueCourseError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\nMagneticHeading Error")) ;
            LogFile.Write(data) ;

            }


        }


    TLiwVariant MagneticCourse ;
    index =  LocMap->FindL(_L8("MagneticCourse") , MagneticCourse ) ;


    if(index)
        {

        TReal heading = MagneticCourse.AsTReal() ;
        data.Num(heading , format);

        LogFile.Write(_L8("\ncompass information")) ;

        LogFile.Write(_L8("\nMagneticCourse ")) ;
        LogFile.Write(data) ;



        TLiwVariant MagneticCourseError  ;
        index = LocMap->FindL(_L8("MagneticCourseError") ,MagneticCourseError ) ;

        if( index)
            {


            TReal heading = MagneticCourseError.AsTReal() ;
            data.Num(heading , format);

            LogFile.Write(_L8("\ncompass information")) ;

            LogFile.Write(_L8("\n MagneticCourseError Error")) ;
            LogFile.Write(data) ;

            }


        }



    TLiwVariant NmeaNum ;
    index = LocMap->FindL(_L8("NMEASentence") , NmeaNum ) ;      


    if(index)
        {

        TInt32 NMEASentence = NmeaNum.AsTInt32() ;
        data.Num(NMEASentence , format);

        LogFile.Write(_L8("\nNMEA Information")) ;

        LogFile.Write(_L8("\n number of NMEA Sentences ")) ;
        LogFile.Write(data) ;

        index = 0 ;

        const TLiwGenericParam *MagneticCourseError  = outputlist->FindFirst(index , _L8("NMEASentenceStart") ) ;

        if(-1 != index)
            {
            Variant = MagneticCourseError->Value() ;


            }


        }


    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return KErrNone ;



    }


TInt  CTestProvider ::GetLocationMultiple(CStifItemParser& /*aItem*/)
    {


    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }


    _LIT(LogFileNameCancel , "C:\\cancelinvalid.txt") ;

    if(LogFile.Open(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create  log file\n") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CancelWithInvalidTransactionID\n") ;
    data.Copy(KLog);
    LogFile.Write(data) ;



    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    ASyncLocCBF* callBack = new(ELeave) ASyncLocCBF;
    //Make the first call
    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist\n") ;
        data.Copy(Klog);
        LogFile.Write(data) ;

        //LogFile.Write(Klog) ;
        return KErrGeneral ;
        }

    TInt reqerror = (ErrorParm->Value()).AsTInt32();
    _LIT(Klog , "ERRor code from getlocationasynch  ") ;
    data.Copy(Klog);
    LogFile.Write(data) ;

    //LogFile.Write(Klog) ;

    TReal64 errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;


    pos = 0;

    _LIT8(KTransactionId, "TransactionID");
    const TLiwGenericParam *transid =  outputlist->FindFirst(pos ,KTransactionId ) ;


    if(!transid)
        {
        _LIT(KTran,"Missing Transaction ID\n");
        data.Copy(KTran);
        LogFile.Write(data) ;
        //LogFile.Write(KTran);
        return KErrGeneral;
        }
    TInt32 trid = (transid->Value()).AsTInt32();
    outputlist->Reset() ;
    inputlist->Reset() ;
    //Make second call   
    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);
    pos = 0 ;

    const TLiwGenericParam *ErrorParm1 =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm1)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist\n") ;
        data.Copy(Klog);
        LogFile.Write(data) ;

        //LogFile.Write(Klog) ;
        return KErrGeneral ;
        }

    TInt reqerror1 = (ErrorParm1->Value()).AsTInt32();
    _LIT(Klog1 , "ERRor code from getlocationasynch  ") ;
    data.Copy(Klog1);
    LogFile.Write(data) ;

    //LogFile.Write(Klog) ;

    TReal64 errordata1 = reqerror1 ; 
    data.Num(errordata1 , format) ;


    LogFile.Write(data) ;


    pos = 0;


    const TLiwGenericParam *transid1 =  outputlist->FindFirst(pos ,KTransactionId ) ;


    if(!transid1)
        {
        _LIT(KTran,"Missing Transaction ID\n");
        data.Copy(KTran);
        LogFile.Write(data) ;
        //LogFile.Write(KTran);
        return KErrGeneral;
        }
    TInt32 trid1 = (transid1->Value()).AsTInt32();
    outputlist->Reset() ;
    inputlist->Reset() ;

    ///////////////Cancel  first call

    inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);

    ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist in cancel\n ") ;
        data.Copy(Klog);
        LogFile.Write(data) ;
        //LogFile.Write(Klog);
        return KErrGeneral ;
        }

    reqerror = (ErrorParm->Value()).AsTInt32();

    _LIT(Klog2 , "\nERRor code from cancel  ") ;

    data.Copy(Klog2);
    LogFile.Write(data) ;   
    //LogFile.Write(Klog1) ;

    errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;
    if( KErrNone != reqerror )
        {
        User::Leave(reqerror);   
        }
    //Cancel the second call
    inputlist->Reset();
    inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid1)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);

    ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist in cancel\n ") ;
        data.Copy(Klog);
        LogFile.Write(data) ;
        //LogFile.Write(Klog);
        return KErrGeneral ;
        }

    reqerror = (ErrorParm->Value()).AsTInt32();

    _LIT(Klog3 , "\nERRor code from cancel  ") ;

    data.Copy(Klog3);
    LogFile.Write(data) ;   
    //LogFile.Write(Klog1) ;

    errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;

    if( KErrNone != reqerror )
        {
        LogFile.Close() ;
        LogSession.Close() ;

        locinterface->Close() ;
        delete callBack;
        delete crit;
        //a.ResetAndDestroy() ;
        a.Close() ;
        delete ServiceHandler ;

        __UHEAP_MARKEND ;
        return reqerror ;
        }


    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete callBack;
    delete crit;
    //a.ResetAndDestroy() ;
    a.Close() ;
    delete ServiceHandler ;

    __UHEAP_MARKEND ;
    return reqerror ;





    }



TInt  CTestProvider ::TraceMultiple(CStifItemParser& /*aItem*/)
    {


    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }


    _LIT(LogFileNameCancel , "C:\\cancelinvalid.txt") ;

    if(LogFile.Open(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create  log file\n") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CancelWithInvalidTransactionID\n") ;
    data.Copy(KLog);
    LogFile.Write(data) ;



    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KTraceLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    ASyncLocCBF* callBack = new(ELeave) ASyncLocCBF;
    //Make the first call
    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist\n") ;
        data.Copy(Klog);
        LogFile.Write(data) ;

        //LogFile.Write(Klog) ;
        return KErrGeneral ;
        }

    TInt reqerror = (ErrorParm->Value()).AsTInt32();
    _LIT(Klog , "ERRor code from getlocationasynch  ") ;
    data.Copy(Klog);
    LogFile.Write(data) ;

    //LogFile.Write(Klog) ;

    TReal64 errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;


    pos = 0;

    _LIT8(KTransactionId, "TransactionID");
    const TLiwGenericParam *transid =  outputlist->FindFirst(pos ,KTransactionId ) ;


    if(!transid)
        {
        _LIT(KTran,"Missing Transaction ID\n");
        data.Copy(KTran);
        LogFile.Write(data) ;
        //LogFile.Write(KTran);
        return KErrGeneral;
        }
    TInt32 trid = (transid->Value()).AsTInt32();
    outputlist->Reset() ;
    inputlist->Reset() ;
    //Make second call   
    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);
    pos = 0 ;

    const TLiwGenericParam *ErrorParm1 =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm1)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist\n") ;
        data.Copy(Klog);
        LogFile.Write(data) ;

        //LogFile.Write(Klog) ;
        return KErrGeneral ;
        }

    TInt reqerror1 = (ErrorParm1->Value()).AsTInt32();
    _LIT(Klog1 , "ERRor code from getlocationasynch  ") ;
    data.Copy(Klog1);
    LogFile.Write(data) ;

    //LogFile.Write(Klog) ;

    TReal64 errordata1 = reqerror1 ; 
    data.Num(errordata1 , format) ;


    LogFile.Write(data) ;


    pos = 0;


    const TLiwGenericParam *transid1 =  outputlist->FindFirst(pos ,KTransactionId ) ;


    if(!transid1)
        {
        _LIT(KTran,"Missing Transaction ID\n");
        data.Copy(KTran);
        LogFile.Write(data) ;
        //LogFile.Write(KTran);
        return KErrGeneral;
        }
    TInt32 trid1 = (transid1->Value()).AsTInt32();
    outputlist->Reset() ;
    inputlist->Reset() ;

    ///////////////Cancel  first call

    inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);

    ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist in cancel\n ") ;
        data.Copy(Klog);
        LogFile.Write(data) ;
        //LogFile.Write(Klog);
        return KErrGeneral ;
        }

    reqerror = (ErrorParm->Value()).AsTInt32();

    _LIT(Klog2 , "\nERRor code from cancel  ") ;

    data.Copy(Klog2);
    LogFile.Write(data) ;   
    //LogFile.Write(Klog1) ;

    errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;
    if( KErrNone != reqerror )
        {
        User::Leave(reqerror);   
        }
    //Cancel the second call
    inputlist->Reset();
    inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid1)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);

    ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist in cancel\n ") ;
        data.Copy(Klog);
        LogFile.Write(data) ;
        //LogFile.Write(Klog);
        return KErrGeneral ;
        }

    reqerror = (ErrorParm->Value()).AsTInt32();

    _LIT(Klog3 , "\nERRor code from cancel  ") ;

    data.Copy(Klog3);
    LogFile.Write(data) ;   
    //LogFile.Write(Klog1) ;

    errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;

    if( KErrNone != reqerror )
        {
        LogFile.Close() ;
        LogSession.Close() ;

        locinterface->Close() ;
        delete callBack;
        delete crit;
        //a.ResetAndDestroy() ;
        a.Close() ;
        delete ServiceHandler ;

        __UHEAP_MARKEND ;
        return reqerror ;
        }


    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete callBack;
    delete crit;
    //a.ResetAndDestroy() ;
    a.Close() ;
    delete ServiceHandler ;

    __UHEAP_MARKEND ;
    return reqerror ;





    }




TInt  CTestProvider ::TraceTimeOut(CStifItemParser& /*aItem*/)
    {
    //return KErrGeneral;
    _LIT(KTLocTest ,"TraceTimeOut");
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" Timeouttrace Thread") , TraceTO ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        {
        _LIT(KLog , "Return Type is valid");
        iLog->Log(KLog);
        }

    else
        {
        _LIT(KLog , "Return type is not valid\n") ;
        iLog->Log(KLog) ;  
        }   
    return KErrNone ;

    }

TInt  CTestProvider ::TraceMultipleWrongCancel(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }


    _LIT(LogFileNameCancel , "C:\\cancelinvalid.txt") ;

    if(LogFile.Open(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create  log file\n") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CancelWithInvalidTransactionID\n") ;
    data.Copy(KLog);
    LogFile.Write(data) ;



    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KTraceLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    ASyncLocCBF* callBack = new(ELeave) ASyncLocCBF;
    //Make the first call
    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist\n") ;
        data.Copy(Klog);
        LogFile.Write(data) ;

        //LogFile.Write(Klog) ;
        return KErrGeneral ;
        }

    TInt reqerror = (ErrorParm->Value()).AsTInt32();
    _LIT(Klog , "ERRor code from getlocationasynch  ") ;
    data.Copy(Klog);
    LogFile.Write(data) ;

    //LogFile.Write(Klog) ;

    TReal64 errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;


    pos = 0;

    _LIT8(KTransactionId, "TransactionID");
    const TLiwGenericParam *transid =  outputlist->FindFirst(pos ,KTransactionId ) ;


    if(!transid)
        {
        _LIT(KTran,"Missing Transaction ID\n");
        data.Copy(KTran);
        LogFile.Write(data) ;
        //LogFile.Write(KTran);
        return KErrGeneral;
        }
    TInt32 trid = (transid->Value()).AsTInt32();
    outputlist->Reset() ;
    inputlist->Reset() ;
    //Make second call   
    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);
    pos = 0 ;

    const TLiwGenericParam *ErrorParm1 =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm1)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist\n") ;
        data.Copy(Klog);
        LogFile.Write(data) ;

        //LogFile.Write(Klog) ;
        return KErrGeneral ;
        }

    TInt reqerror1 = (ErrorParm1->Value()).AsTInt32();
    _LIT(Klog1 , "ERRor code from getlocationasynch  ") ;
    data.Copy(Klog1);
    LogFile.Write(data) ;

    //LogFile.Write(Klog) ;

    TReal64 errordata1 = reqerror1 ; 
    data.Num(errordata1 , format) ;


    LogFile.Write(data) ;


    pos = 0;


    const TLiwGenericParam *transid1 =  outputlist->FindFirst(pos ,KTransactionId ) ;


    if(!transid1)
        {
        _LIT(KTran,"Missing Transaction ID\n");
        data.Copy(KTran);
        LogFile.Write(data) ;
        //LogFile.Write(KTran);
        return KErrGeneral;
        }
    TInt32 trid1 = (transid1->Value()).AsTInt32();
    outputlist->Reset() ;
    inputlist->Reset() ;

    ///////////////Cancel  first call by using CancelNotification
    _LIT8(KCancel , "CancelNotification") ;
    _LIT8( KType ,"CancelRequestType") ;
    _LIT( KTraceCancel ,"TraceCancel") ;
    inputlist->AppendL(TLiwGenericParam (KType , TLiwVariant (KTraceCancel))) ;

    locinterface->ExecuteCmdL(KCancel , *inputlist , *outputlist) ;

    pos = 0 ;
    const TLiwGenericParam  *errprm = outputlist->FindFirst(pos , KErrCode) ;

    if(!errprm)
        {
        _LIT(Kerr, "Success/Failure code missing from outputlist") ;
        iLog->Log(Kerr) ;
        }



    TLiwVariant var = errprm->Value() ;




    //Cancel the second call the usual way
    inputlist->Reset();
    inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid1)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);

    ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist in cancel\n ") ;
        data.Copy(Klog);
        LogFile.Write(data) ;
        //LogFile.Write(Klog);
        return KErrGeneral ;
        }

    reqerror = (ErrorParm->Value()).AsTInt32();

    _LIT(Klog3 , "\nERRor code from cancel  ") ;

    data.Copy(Klog3);
    LogFile.Write(data) ;   
    //LogFile.Write(Klog1) ;

    errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;

    if( KErrNone != reqerror || var.AsTInt32() != KErrNone)
        {
        LogFile.Close() ;
        LogSession.Close() ;

        locinterface->Close() ;
        delete callBack;
        delete crit;
        //a.ResetAndDestroy() ;
        a.Close() ;
        delete ServiceHandler ;

        __UHEAP_MARKEND ;
        return KErrGeneral ;
        }


    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete callBack;
    delete crit;
    //a.ResetAndDestroy() ;
    a.Close() ;
    delete ServiceHandler ;

    __UHEAP_MARKEND ;
    return reqerror ;



    }


TInt  CTestProvider ::EnableAccTrueGetLoc(CStifItemParser& /*aItem*/)
    {
    //return KErrGeneral;
    _LIT(KTLocTest ,"EnableAccTrueGetLoc");
    iLog->Log(KTLocTest) ;
    TInt flag = 1;
    TInt *flagAddr = &flag;
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" EnableAccTrueGetLoc Thread") , EnableHighAcc ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) flagAddr);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  


    return ret ;

    }

TInt  CTestProvider ::EnableAccFalseGetLoc(CStifItemParser& /*aItem*/)
    {
    //return KErrGeneral;
    _LIT(KTLocTest ,"EnableAccTrueGetLoc");
    iLog->Log(KTLocTest) ;
    TInt flag = 2;
    TInt *flagAddr = &flag;
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" EnableAccTrueGetLoc Thread") , EnableHighAcc ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) flagAddr);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        {
        _LIT(KLog , "Return Type is valid");
        iLog->Log(KLog);
        }

    else
        {
        _LIT(KLog , "Return type is not valid\n") ;
        iLog->Log(KLog) ;  
        }   
    return KErrNone ;

    }



TInt  CTestProvider ::EnableAccTrueTrace(CStifItemParser& /*aItem*/)
    {
    //return KErrGeneral;
    _LIT(KTLocTest ,"EnableAccTrueGetLoc");
    iLog->Log(KTLocTest) ;
    TInt flag = 3;
    TInt *flagAddr = &flag;
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" EnableAccTrueGetLoc Thread") , EnableHighAcc ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) flagAddr);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        {
        _LIT(KLog , "Return Type is valid");
        iLog->Log(KLog);
        }

    else
        {
        _LIT(KLog , "Return type is not valid\n") ;
        iLog->Log(KLog) ;  
        }   
    return KErrNone ;

    }

TInt  CTestProvider ::EnableAccFalseTrace(CStifItemParser& /*aItem*/)
    {
    //return KErrGeneral;
    _LIT(KTLocTest ,"EnableAccTrueGetLoc");
    iLog->Log(KTLocTest) ;
    TInt flag = 4;
    TInt *flagAddr = &flag;
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" EnableAccTrueGetLoc Thread") , EnableHighAcc ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) flagAddr);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        {
        _LIT(KLog , "Return Type is valid");
        iLog->Log(KLog);
        }

    else
        {
        _LIT(KLog , "Return type is not valid\n") ;
        iLog->Log(KLog) ;  
        }   
    return KErrNone ;

    }


TInt  CTestProvider ::EnableAccPosBasedGetloc(CStifItemParser& /*aItem*/)
    {
    //return KErrGeneral;
    _LIT(KTLocTest ,"EnableAccTrueGetLoc");
    iLog->Log(KTLocTest) ;
    TInt flag = 1;
    TInt *flagAddr = &flag;
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" EnableAccTrueGetLoc Thread") , EnableHighAcc_PosBased ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) flagAddr);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        {
        _LIT(KLog , "Return Type is valid");
        iLog->Log(KLog);
        }

    else
        {
        _LIT(KLog , "Return type is not valid\n") ;
        iLog->Log(KLog) ;  
        }   
    return KErrNone ;

    }


TInt  CTestProvider ::EnableAccPosBasedWrongTypeGetloc(CStifItemParser& /*aItem*/)
    {
    //return KErrGeneral;
    _LIT(KTLocTest ,"EnableAccTrueGetLoc");
    iLog->Log(KTLocTest) ;
    TInt flag = 2;
    TInt *flagAddr = &flag;
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" EnableAccTrueGetLoc Thread") , EnableHighAcc_PosBased ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) flagAddr);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        {
        _LIT(KLog , "Return Type is valid");
        iLog->Log(KLog);
        }

    else
        {
        _LIT(KLog , "Return type is not valid\n") ;
        iLog->Log(KLog) ;  
        }   
    return KErrNone ;

    }


TInt  CTestProvider ::EnableAccPosBasedTrace(CStifItemParser& /*aItem*/)
    {
    //return KErrGeneral;
    _LIT(KTLocTest ,"EnableAccTrueGetLoc");
    iLog->Log(KTLocTest) ;
    TInt flag = 3;
    TInt *flagAddr = &flag;
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" EnableAccTrueGetLoc Thread") , EnableHighAcc_PosBased ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) flagAddr);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        {
        _LIT(KLog , "Return Type is valid");
        iLog->Log(KLog);
        }

    else
        {
        _LIT(KLog , "Return type is not valid\n") ;
        iLog->Log(KLog) ;  
        }   
    return KErrNone ;

    }



TInt  CTestProvider ::EnableAccPosBasedWrongTypeTrace(CStifItemParser& /*aItem*/)
    {
    //return KErrGeneral;
    _LIT(KTLocTest ,"EnableAccTrueGetLoc");
    iLog->Log(KTLocTest) ;
    TInt flag = 4;
    TInt *flagAddr = &flag;
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" EnableAccTrueGetLoc Thread") , EnableHighAcc_PosBased ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) flagAddr);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  

    if(ret == SErrServiceInUse)
        {
        _LIT(KLog , "Return Type is valid");
        iLog->Log(KLog);
        }

    else
        {
        _LIT(KLog , "Return type is not valid\n") ;
        iLog->Log(KLog) ;  
        }   
    return KErrNone ;

    }
TInt CTestProvider::GetLocationPosBasedWrongVal(CStifItemParser& /*aItem*/)
    {

    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }




    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create notifications log file") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CTGetLocation") ;
    iLog->Log(KLog) ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {
        _LIT(KLog , "Interface not found");
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    //_LIT(KClass,"GenericLocationInfo");//Invalid KClass value
    TInt KClass = 12;
    inputlist->AppendL( TLiwGenericParam( KNullDesC8,TLiwVariant( KClass )  ) );

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog, "Success/Failure state not known") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }

    if((ErrorParm->Value()).AsTInt32() != SErrBadArgumentType )
        {
        _LIT(KLog , "ExecutecmdL failed ");
        iLog->Log(KLog) ;
        return (ErrorParm->Value()).AsTInt32() ;    
        }




    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return KErrNone ;




    }


TInt CTestProvider :: CancelTransIdPosBased(CStifItemParser& /*aItem*/)
    {

    __UHEAP_MARK ;
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    ASyncLocCBF* callBack = new(ELeave) ASyncLocCBF;

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        return KErrGeneral ;
        }

    TInt reqerror = (ErrorParm->Value()).AsTInt32();

    pos = 0;

    _LIT8(KTransactionId, "TransactionID");
    const TLiwGenericParam *transid =  outputlist->FindFirst(pos ,KTransactionId ) ;
    if(!transid)
        {
        return KErrGeneral;
        }
    TInt32 trid = (transid->Value()).AsTInt32();
    outputlist->Reset() ;
    inputlist->Reset() ;


    //inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid)));
    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(trid)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);

    ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        return KErrGeneral ;
        }

    reqerror = (ErrorParm->Value()).AsTInt32();
    TInt retr = KErrGeneral;
    if( 0 == reqerror )
        {
        retr = 0;   
        }

    locinterface->Close() ;
    inputlist->Reset();
    outputlist->Reset();
    delete callBack;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return reqerror ;


    }

TInt CTestProvider ::CancelWithoutTransId(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }


    _LIT(LogFileNameCancel , "C:\\cancelinvalid.txt") ;

    if(LogFile.Open(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileNameCancel , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create  log file\n") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CancelWithInvalidTransactionID\n") ;
    data.Copy(KLog);
    LogFile.Write(data) ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    ASyncLocCBF* callBack ;

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous, callBack);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist\n") ;
        data.Copy(Klog);
        LogFile.Write(data) ;

        //LogFile.Write(Klog) ;
        return KErrGeneral ;
        }

    TInt reqerror = (ErrorParm->Value()).AsTInt32();
    _LIT(Klog , "ERRor code from getlocationasynch  ") ;
    data.Copy(Klog);
    LogFile.Write(data) ;

    //LogFile.Write(Klog) ;

    TReal64 errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;


    pos = 0;

    _LIT8(KTransactionId, "TransactionID");
    const TLiwGenericParam *transid =  outputlist->FindFirst(pos ,KTransactionId ) ;
    if(!transid)
        {
        _LIT(KTran,"Missing Transaction ID\n");
        data.Copy(KTran);
        LogFile.Write(data) ;
        //LogFile.Write(KTran);
        return KErrGeneral;
        }
    TInt trid = (transid->Value()).AsTInt32();
    outputlist->Reset() ;
    inputlist->Reset() ;


    //No trans Id is passed
    //inputlist->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(trid-2)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptCancel);

    ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist in cancel\n ") ;
        data.Copy(Klog);
        LogFile.Write(data) ;
        //LogFile.Write(Klog);
        return KErrGeneral ;
        }

    reqerror = (ErrorParm->Value()).AsTInt32();

    _LIT(Klog1 , "\nERRor code from cancel  ") ;

    data.Copy(Klog1);
    LogFile.Write(data) ;   
    //LogFile.Write(Klog1) ;

    errordata = reqerror ; 
    data.Num(errordata , format) ;


    LogFile.Write(data) ;


    TInt retr = KErrGeneral;
    if( 1002 == reqerror )
        {
        retr = 0;   
        }






    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return retr ;

    }

TInt CTestProvider :: GetLocationAsyncPosBasedUpdate(CStifItemParser& /*aItem*/)
    {
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    FunctionThread.Create(_L("GetLocationAsynchThread2") , GetLocAsynchPosBased ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);

    FunctionThread.Logon(Status)    ;
    FunctionThread.Resume() ;

    User :: WaitForRequest (Status) ;               
    FunctionThread.Close();

    return Status.Int() ;

    }

TInt CTestProvider :: GetLocationAsyncWrongUpdate(CStifItemParser& /*aItem*/)
    {
    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    FunctionThread.Create(_L("GetLocationAsynchThread2") , GetLocAsynchWrongVal ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);
    // FunctionThread.Create(_L("GetLocationAsynchThread1") , GetLocAsynchWrongVal ,KDefaultStackSize , 
    //                       NULL , NULL,(TAny *) NULL);

    FunctionThread.Logon(Status)    ;
    FunctionThread.Resume() ;

    User :: WaitForRequest (Status) ;               
    FunctionThread.Close();

    return Status.Int() ;

    }

TInt CTestProvider::GetLocPosBasedWrongVal(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> data ;
    TRealFormat format ;


    if(LogSession.Connect() != KErrNone)
        {
        _LIT(KLog , "Failed to connect to file server") ;
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }




    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        if(LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) != KErrNone)
            {
            _LIT(KLog , "Failed to create notifications log file") ;
            iLog->Log(KLog) ;
            return KErrGeneral ;
            }

        }

    _LIT(KLog , "In CTGetLocation") ;
    iLog->Log(KLog) ;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;







    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        _LIT(Klog , "Success/Failure error code missing from outputlist") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {
        _LIT(KLog , "Interface not found");
        iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT(KClass,"GenericLocationInfo");
    inputlist->AppendL( TLiwGenericParam( KNullDesC8,TLiwVariant( KClass )  ) );

    TInt updatemap =12 ;

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(updatemap)));          

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog, "Success/Failure state not known") ;
        iLog->Log(Klog) ;
        return KErrGeneral ;
        }

    if((ErrorParm->Value()).AsTInt32() != 1002)
        {
        _LIT(KLog , "ExecutecmdL failed ");
        iLog->Log(KLog) ;
        return KErrGeneral;    
        }

    LogFile.Close() ;
    LogSession.Close() ;

    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;

    __UHEAP_MARKEND ;
    return KErrNone ;


    }


TInt CTestProvider::GetLocPosBasedWrongVal1(CStifItemParser& /*aItem*/)
    {
    //currently not needed

    }


TInt CTestProvider :: TracePosBasedWrongVal( CStifItemParser& /*aItem*/ )
    {
    __UHEAP_MARK ;
    TInt start = User::CountAllocCells();
    ASyncLocCBF callback;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);

    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;

    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);

    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdTraceLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT8(KClass,"LocationInformationClass");
    //_LIT(KClassArg,"Invalid");
    TInt KClassArg = 12;
    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(KClassArg)));

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous,&callback);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {

        return KErrGeneral ;
        }
    TInt error = (ErrorParm->Value()).AsTInt32();
    TInt retr = KErrGeneral;
    if( SErrBadArgumentType == error )
        {
        retr = KErrNone;   


        }
    locinterface->Close() ;
    outputlist->Reset() ;
    inputlist->Reset() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    TInt end = User::CountAllocCells();
    __UHEAP_MARKEND ;  
    return retr;

    }

TInt CTestProvider::TracePosBasedUpdateOpts(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    TInt start = User::CountAllocCells();
    ASyncLocCBF callback;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);

    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;

    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);

    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdTraceLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT8(KClass,"LocationInformationClass");
    _LIT(KClassArg,"Invalid");

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(KClassArg)));

    CLiwDefaultMap* updatemap = CLiwDefaultMap::NewL();

    _LIT8(KInterval,"UpdateInterval");
    _LIT8(KTimeout,"UpdateTimeOut");
    _LIT8(KAge,"UpdateMaxAge");
    _LIT8(KPartial,"PartialUpdates");
    const TInt KTime = -1000000;  // bad time 

    updatemap->InsertL(KInterval , TLiwVariant(TInt32(2*KTime)));
    updatemap->InsertL(KTimeout , TLiwVariant(TInt32(30*KTime)));
    updatemap->InsertL(KAge , TLiwVariant(TInt32(0)));
    updatemap->InsertL(KPartial , TLiwVariant(TBool(FALSE)));

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(updatemap)));
    updatemap->DecRef();

    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous,&callback);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {

        return KErrGeneral ;
        }
    TInt error = (ErrorParm->Value()).AsTInt32();
    TInt retr = KErrGeneral;
    if( SErrBadArgumentType == error )
        {
        retr = KErrNone;   


        }
    locinterface->Close() ;
    outputlist->Reset() ;
    inputlist->Reset() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    TInt end = User::CountAllocCells();
    __UHEAP_MARKEND ;  
    return retr;

    }

TInt CTestProvider::TracePosBasedUpdateWrongVal(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    TInt start = User::CountAllocCells();
    ASyncLocCBF callback;


    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);

    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;

    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);

    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {

        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();



    TBuf8<20>CmdBuf(KCmdTraceLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT8(KClass,"LocationInformationClass");
    _LIT(KClassArg,"Invalid");

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(KClassArg)));

    TInt updatemap = 12;

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(updatemap)));


    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist,KLiwOptASyncronous,&callback);

    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {

        return KErrGeneral ;
        }
    TInt error = (ErrorParm->Value()).AsTInt32();
    TInt retr = KErrGeneral;
    if( SErrBadArgumentType == error )
        {
        retr = KErrNone;   


        }
    locinterface->Close() ;
    outputlist->Reset() ;
    inputlist->Reset() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    TInt end = User::CountAllocCells();
    __UHEAP_MARKEND ;  
    return retr;

    }


TInt CTestProvider ::FindDistancePositionBased(CStifItemParser& /*aItem*/) 
    {
    __UHEAP_MARK ;
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
    //First set the identity information

    TBuf8<20>CmdBufSet(KRequestCalculate) ;
    outputlist->Reset() ;
    inputlist->Reset() ;

    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    TLiwGenericParam requesttype(KNullDesC8 , TLiwVariant(KRequestDistance)) ;
    InputList->AppendL(requesttype) ;



    //Inserting first input param
    CLiwMap* SourceCoordinate = CLiwDefaultMap::NewL();
    TReal64 slongitude = 71.03;
    SourceCoordinate->InsertL(KLongitudeKey,TLiwVariant(slongitude));
    TReal64 slatitude = 42.37;
    SourceCoordinate->InsertL(KLatitudeKey,TLiwVariant(slatitude));
    TReal64 saltitude = 1;
    SourceCoordinate->InsertL(KAltitudeKey,TLiwVariant(slatitude));

    TLiwGenericParam scoordinate(KNullDesC8,TLiwVariant(SourceCoordinate));
    InputList->AppendL(scoordinate) ;
    SourceCoordinate->DecRef() ;



    //Inserting 2nd input param
    CLiwMap* DestCoordinate = CLiwDefaultMap::NewL();
    TReal64 dlongitude = 83.02;
    DestCoordinate->InsertL(KLongitudeKey,TLiwVariant(dlongitude));
    TReal64 dlatitude = 42.42;
    DestCoordinate->InsertL(KLatitudeKey,TLiwVariant(dlatitude));
    TReal64 daltitude = 1;
    DestCoordinate->InsertL(KAltitudeKey,TLiwVariant(dlatitude));

    TLiwGenericParam dcoordinate(KNullDesC8,TLiwVariant(DestCoordinate));
    InputList->AppendL(dcoordinate) ;
    DestCoordinate->DecRef() ;  

    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;


    CmdBufSet = KRequestCalculate ;

    locinterface->ExecuteCmdL(CmdBufSet , *InputList , *OutParmList);


    pos = 0;
    const TLiwGenericParam* param = OutParmList->FindFirst(pos, KErrorCode);


    pos = 0;
    const TLiwGenericParam* resultparam = OutParmList->FindFirst(pos, KMathOpResult);       
    TLiwVariant resultvariant = resultparam->Value();
    TReal64 distance = resultvariant.AsTReal();




    //Logging result into a file
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> Buffer(_L8("Distance = ")) ;
    LogSession.Connect() ;

    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

        }

    TInt End = 0 ;

    LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 

    TBuf8<50> num ;
    TRealFormat format ;
    //TReal64 Val = aPosition.Latitude() ;
    num.Num(distance , format) ;

    //Logging Latitude 
    LogFile.Write(_L8("distance = "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Close() ;
    LogSession.Close() ;

    delete InputList ;
    delete OutParmList ;
    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;

    __UHEAP_MARKEND ;  
    return KErrNone ;

    }


TInt CTestProvider::MoveCoordinatePosBased(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();

    TBuf8<20>CmdBuf(KRequestCalculate) ;
    outputlist->Reset() ;
    inputlist->Reset() ;   


    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    TLiwGenericParam requesttype(KNullDesC8 , TLiwVariant(KRequestMove)) ;
    InputList->AppendL(requesttype) ;


    //Inserting first input param
    CLiwMap* SourceCoordinate = CLiwDefaultMap::NewL();
    TReal64 slongitude = 22;
    SourceCoordinate->InsertL(KLongitudeKey,TLiwVariant(slongitude));
    TReal64 slatitude = 88;
    SourceCoordinate->InsertL(KLatitudeKey,TLiwVariant(slatitude));

    TReal64 saltitude = 1;
    SourceCoordinate->InsertL(KAltitudeKey,TLiwVariant(saltitude));



    TLiwGenericParam scoordinate(KNullDesC8,TLiwVariant(SourceCoordinate));
    InputList->AppendL(scoordinate) ;
    SourceCoordinate->DecRef() ;



    TReal32 distanceToMove = 345;
    TReal32 bearingToMove = 45;


    //Inserting distance by which coordinate should be moved
    TLiwVariant distanceVal((TReal)distanceToMove);
    TLiwGenericParam distanceParam(KNullDesC8,distanceVal);
    InputList->AppendL(distanceParam);

    //Inserting bearing by which coordinate should be moved
    TLiwVariant bearingVal((TReal)bearingToMove);
    TLiwGenericParam bearingParam(KNullDesC8,bearingVal);
    InputList->AppendL(bearingParam);





    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;




    locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList);





    TInt mathindex = 0;

    // calculation                                                  
    const TLiwGenericParam *smapparam = OutParmList->FindFirst(mathindex , KLocationMap) ;
    TLiwVariant mapVariant= smapparam->Value() ; 
    const CLiwMap  *map = mapVariant.AsMap() ;
    TCoordinate source  ;

    FillCoordinatesL(source , map) ;

    TReal64 longitudeInputVal = source.Longitude();         
    TReal64 latitudeInputVal = source.Latitude(); 
    TReal64 altitudeInputVal = source.Altitude(); 


    //Logging result into a file
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> Buffer(_L8("Longitude = ")) ;
    LogSession.Connect() ;

    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

        }

    TInt End = 0 ;

    LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 

    TBuf8<50> num ;
    TRealFormat format ;

    num.Num(longitudeInputVal, format) ;

    //Logging 
    LogFile.Write(_L8("Longitude = "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    //LogFile.Seek(ESeekEnd , End) ;
    num.Num(latitudeInputVal, format) ;
    LogFile.Write(_L8("Latitude = "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    num.Num(altitudeInputVal, format) ;
    LogFile.Write(_L8("altitude = "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Close() ;
    LogSession.Close() ;

    delete OutParmList ;
    delete InputList ;
    locinterface->Close() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    __UHEAP_MARKEND ;
    return KErrNone ;
    }

TInt CTestProvider::FindBearingPosBased(CStifItemParser& /*aItem*/)
    {
    __UHEAP_MARK ;

    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;
    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);




    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        return KErrGeneral ;
        }

    pos = 0 ;
    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KDataSource );

    if(!genericparm)
        {

        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
    TBuf8<20>CmdBuf(KRequestCalculate) ;

    CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;

    TLiwGenericParam requesttype(KNullDesC8 , TLiwVariant(KRequestBearingTo)) ;
    InputList->AppendL(requesttype) ;

    //Inserting first input param
    CLiwMap* SourceCoordinate = CLiwDefaultMap::NewL();
    TReal64 slongitude = 22;
    SourceCoordinate->InsertL(KLongitudeKey,TLiwVariant(slongitude));
    TReal64 slatitude = 88;
    SourceCoordinate->InsertL(KLatitudeKey,TLiwVariant(slatitude));
    TReal64 saltitude = 1;
    SourceCoordinate->InsertL(KAltitudeKey,TLiwVariant(slatitude));

    TLiwGenericParam scoordinate(KNullDesC8,TLiwVariant(SourceCoordinate));
    InputList->AppendL(scoordinate) ;
    SourceCoordinate->DecRef() ;



    //Inserting 2nd input param
    CLiwMap* DestCoordinate = CLiwDefaultMap::NewL();
    TReal64 dlongitude = 13;
    DestCoordinate->InsertL(KLongitudeKey,TLiwVariant(dlongitude));
    TReal64 dlatitude = 77;
    DestCoordinate->InsertL(KLatitudeKey,TLiwVariant(dlatitude));
    TReal64 daltitude = 1;
    DestCoordinate->InsertL(KAltitudeKey,TLiwVariant(dlatitude));

    TLiwGenericParam dcoordinate(KNullDesC8,TLiwVariant(DestCoordinate));
    InputList->AppendL(dcoordinate) ;
    DestCoordinate->DecRef() ;


    CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;


    CmdBuf = KRequestCalculate ;

    locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList);


    pos = 0;
    const TLiwGenericParam* param = OutParmList->FindFirst(pos, KErrorCode);

    pos = 0;
    const TLiwGenericParam* resultparam = OutParmList->FindFirst(pos, KMathOpResult);       
    TLiwVariant resultvariant = resultparam->Value();
    TReal32 bearingTo = resultvariant.AsTReal();




    //Logging result into a file
    RFile LogFile ;
    RFs LogSession ;
    TBuf8<50> Buffer(_L8("BearingTo = ")) ;
    LogSession.Connect() ;

    if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
        }

    TInt End = 0 ;

    LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 

    TBuf8<50> num ;
    TRealFormat format ;

    num.Num(bearingTo , format) ;


    LogFile.Write(_L8("BearingTo= "));
    LogFile.Write(num) ;
    LogFile.Write(_L8("\n")) ;
    LogFile.Close() ;
    LogSession.Close() ;

    delete OutParmList ; 
    dcoordinate.Reset() ;
    scoordinate.Reset() ;
    delete InputList ;   
    locinterface->Close() ;
    inputlist->Reset() ;
    outputlist->Reset() ;
    delete ServiceHandler ;
    a.ResetAndDestroy() ;
    a.Close() ;
    __UHEAP_MARKEND ;  
    return KErrNone ;


    }
