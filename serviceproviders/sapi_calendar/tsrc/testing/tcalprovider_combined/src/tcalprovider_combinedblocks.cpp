/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include<stdio.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "tcalprovider_combined.h"
#include <LiwCommon.h>
#include <LiwVariant.h>
#include <LiwServiceHandler.h>
#include "calendarheader.h"
#include "calendarconstants.h"
#include <BADESCA.H>
#include <SendUiConsts.h>
#include <messaginginterface.h>
#include "sendmessage.h"
#include <LbsRequestor.h>
#include <f32file.h>
#include <messageheader.h>
#include <serviceerrno.h>
#include <liwgenericparam.h>
#include <epos_cposlandmarkdatabase.h>
#include <epos_cposlandmark.h>
#include <epos_cposlandmarkencoder.h>
#include <epos_cposlmcategorymanager.h>
#include <EPos_HPosLmDatabaseInfo.h>
#include <EPos_CPosLmDatabaseManager.h>
#include <lbsposition.h> 
#include "TLandmarkProvider.h"
#include "landmarkliwparams.hrh"
//#include <VPbkEng.rsg>
//#include <MVPbkContactFieldTextData.h>
//#include <MVPbkContactStoreList.h>
//#include <MVPbkContactOperationBase.h>
//#include <MVPbkContactLink.h>
//#include <CVPbkContactLinkArray.h>
//#include <MVPbkContactGroup.h>
//#include <CVPbkContactManager.h>
//#include <MVPbkContactStoreList.h>
//#include <MVPbkContactStore.h>
//#include <TVPbkContactStoreUriPtr.h>
//#include <CVPbkFieldTypeRefsList.h>
//#include <MVPbkContactFieldTextData.h>
#include "tconstants.h"
//#include "sensrprovidertest.h"
//#include "sensorinterface_const.hrh"
#include <utf.h>
//#include <sensrtestthread.h>
//#include "appmanagertest.h"
//#include <appmanagerservice.h>
//#include <appmanagercommon.h>
#include <e32des16.h>
#include <e32base.h>

using namespace LIW;

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddAppointmentProvLocal(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);

void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid );
void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid );


_LIT8(KIDataSource, "IDataSource");
_LIT8(KCalService, "Service.Calendar");
_LIT8(KContactIDataSource, "IDataSource");
_LIT8(KContactService, "Service.Contact");
_LIT8(KAppService, "Service.AppManager");
_LIT8(KAppIDataSource,"IAppManager");

_LIT8(KMsgService, 		"Service.Messaging");
_LIT8(KMsgIDataSource,		"IMessaging");
_LIT8(KMsgSendCmd,				"Send");
//_LIT8(KErrCode,"ErrorCode");
_LIT8(KMsgGetListCmd,"GetList");
_LIT(KName,"Test landmark");
_LIT8(KFieldLabel, "Label");
_LIT8(KFieldValue, "Value");
_LIT8(KFieldNext, "Next");
//_LIT8(KContents, "Contents");
_LIT8(KContactId, "CntId");
_LIT8(KDBUri, "DBUri");
_LIT8(KFirstName, "FirstName");
_LIT8(KSourceFileNameParam, "SourceFile");
_LIT8(KDestFileNameParam, "DestinationFile");
_LIT8(KList, "CntIdList"); 
_LIT8(KCmdLine,"CmdLine");
_LIT(KSearchTexttest                 ,"Meeting");

_LIT(KDefaultCalendar                ,"C:Calendar");

_LIT(KTestCal1File, "C:getlistcal1");
_LIT(KTestCalFile, "C:ccc");
_LIT(KTestCal2File, "C:getlistcal2");
_LIT8(KSensorInterfaceNotFound , "Sensor Interface not found");
_LIT8(KLogUnknownErr, "Success/Failure state not known-no error returned");
_LIT8(KOutParamError, "Out Param not found");
_LIT8(KPropertyTestLog, "GetChannelProperty for %s channel for %s property has %d count");
_LIT8(KSetPropertyTestLog, "SetChannelProperty is supported for %s channel for %s property");
_LIT8(KDocumentPath,"DocumentPath");
//_LIT8(KMimeType,"MimeType");
_LIT8(KMode,"Mode");
_LIT8(KPostion,"Position");
_LIT8(KHandle,"Handle");
_LIT8(KDocument,"Document");
//_LIT(KNull,"NULL");

_LIT8(KApplicationID,"ApplicationID");
_LIT8(KDocumentName,"DocumentName");

//Supported Operation
//_LIT8(KGetList,  "GetList");
_LIT8(KLaunchApp,"LaunchApp");
_LIT8(KLaunchDoc,"LaunchDoc");

//_LIT8(KResponse,"ReturnValue");
//_LIT8(KErrorCode,"ErrorCode");
_LIT8(KOptions,"Options");


const TInt KDocMaxDigitsInHexString = 8; // 32 bits.



CEventDet :: CEventDet(): iStatus(-1) , iDirection(-1) ,iEventType(-1)
	{
	  ;
	}
 
/**
 * Default Destructor
 */
  
 CEventDet :: ~CEventDet()
	{
	;
	}
	
/**
 *Two phased constructor implementation
 */

 EXPORT_C CEventDet* CEventDet :: NewL()
	{
	CEventDet* self = CEventDet::NewLC();
	CleanupStack::Pop(self);
	return self;
	}
	  
/**
 * Two phased constructor implementation
 */
  
 CEventDet* CEventDet :: NewLC() 
	{
	CEventDet* self = new (ELeave) CEventDet();
    CleanupStack::PushL(self);
	return self;
	}
	
	
	/**
 * Default Constructor Method
 */
 
 CFilterDetails :: CFilterDetails(): iDirection(-1) , iStatus(-1)
	{
	  ;
	}
 
/**
 * Default Destructor
 */
  
 CFilterDetails :: ~CFilterDetails()
	{
	;
	}
	
/**
 *Two phased constructor implementation
 */

 EXPORT_C CFilterDetails* CFilterDetails :: NewL()
	{
	CFilterDetails* self = CFilterDetails::NewLC();
	CleanupStack::Pop(self);
	return self;
	}
	  
/**
 * Two phased constructor implementation
 */
  
 CFilterDetails* CFilterDetails :: NewLC() 
	{
	CFilterDetails* self = new (ELeave) CFilterDetails();
    CleanupStack::PushL(self);
	return self;
	}
	
	
// Sensor call back class

/*class SensorAsyncCallback : public MLiwNotifyCallback
	{
	private:
	TUint iChannelId;
	MLiwInterface* iSensorInterface;
	TInt iListenType;
	
	public :
	TInt iRetStatus;
	TInt HandleNotifyL( TInt aCmdId,
            			TInt aEventId,
            			CLiwGenericParamList& aEventParamList,
            			const CLiwGenericParamList& aInParamList);

	SensorAsyncCallback(MLiwInterface* aSensorInterface,
						TUint aChannelId,
						TInt aListenType)
		{
		iSensorInterface = aSensorInterface;
		iChannelId = aChannelId;
		iRetStatus = KErrGeneral;
		iListenType = aListenType;
		}
	
	};


TInt SensorAsyncCallback:: HandleNotifyL(TInt aCmdId,
							             TInt aEventId,
							             CLiwGenericParamList& aEventParamList,
							             const CLiwGenericParamList& aInParamList)
	{
	TInt index = 0;
	const TLiwGenericParam *GenericParam = aEventParamList.FindFirst(index ,KErrorCode);

	if(!GenericParam)
		{
		return KErrGeneral;
		}
	if((GenericParam->Value()).AsTInt32() != KErrNone)
		{
		return (GenericParam->Value()).AsTInt32() ;
		}
	index = 0;
	
	const TLiwGenericParam *outGenericParam =  aEventParamList.FindFirst(index , KReturnValue) ;
	
	if( iListenType == 0)
		{
			
			
		const CLiwMap* chnlDataMap = (outGenericParam->Value()).AsMap();
	    TLiwVariant infoVariant;
	    chnlDataMap->FindL( KDataType , infoVariant );
	    TPtrC8 dataType;
	    infoVariant.Get( dataType );
	    
	    
	    //log data
	    RFile LogResult;
	    RFs LogResultSession;
	    User::LeaveIfError(LogResultSession.Connect());
	    if(LogResult.Open(LogResultSession ,_L("c:\\sensrdatalog.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
	        {
	        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\sensrdatalog.txt") , EFileWrite | EFileShareAny ) ;
	        }
	    TInt End = 0 ;
	    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
	    
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
		    
		    //Write data to the log file
		    
		    
			LogResult.Write(_L8("****Data received from AcclMtrXYZ****\n"));
			data.Num(xAxisData,format);
			LogResult.Write(_L8("XAxisData= "));
			LogResult.Write(data);
			LogResult.Write(_L8("\n"));
			
			data.Num(yAxisData,format);
			LogResult.Write(_L8("YAxisData= "));
			LogResult.Write(data);
			LogResult.Write(_L8("\n"));
			
			data.Num(zAxisData,format);
			LogResult.Write(_L8("ZAxisData= "));
			LogResult.Write(data);
			LogResult.Write(_L8("\n"));
			
			
			
		    }
		else if ( dataType == KAcclmtrWakeupData  )
			{
			TBuf8<50> data;
	    	TRealFormat format;
		    chnlDataMap->FindL( KDirection , infoVariant ) ;
		    TInt32 direction = infoVariant.AsTInt32();
			
			LogResult.Write(_L8("\n"));
			data.Num(direction,format);
			LogResult.Write(_L8("****Data Obtained from AcclmtrWakeupData channel****"));
			LogResult.Write(_L8("\nDirection= "));
			LogResult.Write(data);
			LogResult.Write(_L8("\n"));
			
			}
		else if ( dataType == KAcclmtrDoubleTappingData  )
			{
			
			TBuf8<50> data;
	    	TRealFormat format;
	    	
		    chnlDataMap->FindL( KDirection , infoVariant ) ;
		    TInt32 direction = infoVariant.AsTInt32();
		    
		    LogResult.Write(_L8("\n****Data obtained from Dbl Tapping Channel****\n"));
		    data.Num(direction,format);
		    LogResult.Write(_L8("\nDirection= "));
		    LogResult.Write(data);
		    LogResult.Write(_L8("\n"));
			
			}
		else if ( dataType == KOrientationData )
			{
			
			LogResult.Write(_L8("\n****Data Received from Orientation Chnl****"));
			chnlDataMap->FindL( KDeviceOrientation,infoVariant );
			TPtrC8 data;
			infoVariant.Get( data );
			LogResult.Write(_L8("\nOrientation Of the Device is = "));
			LogResult.Write(data);
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
			LogResult.Write(_L8("\n****Data Obtained From Rotation Channel****\n"));
			LogResult.Write(_L8("\nRotaion Abt XAxis= "));
			data.Num(xAxis,format);
			LogResult.Write(data);
			
			LogResult.Write(_L8("\nRotaion Abt YAxis= "));
			data.Num(yAxis,format);
			LogResult.Write(data);
			
			
			LogResult.Write(_L8("\nRotaion Abt ZAxis= "));
			data.Num(zAxis,format);
			LogResult.Write(data);
			
			
			}
			LogResult.Close();
    		LogResultSession.Close();
		}
	else if( iListenType == 1)
		{
		//log data
	    RFile LogResult;
	    RFs LogResultSession;
	    User::LeaveIfError(LogResultSession.Connect());
	    if(LogResult.Open(LogResultSession ,_L("c:\\sensrlog.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
	        {
	        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\sensrdatalog.txt") , EFileWrite | EFileShareAny ) ;
	        }
	    TInt End = 0 ;
	    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
	    
		LogResult.Write(_L8("\nChannel Changed\n"));
		LogResult.Close();
    	LogResultSession.Close();
		}		
	else if( iListenType == 2)
		{
		RFile LogResult;
	    RFs LogResultSession;
	    User::LeaveIfError(LogResultSession.Connect());
	    if(LogResult.Open(LogResultSession ,_L("c:\\sensrlog.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
	        {
	        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\sensrdatalog.txt") , EFileWrite | EFileShareAny ) ;
	        }
	    TInt End = 0 ;
	    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
	    
		
		LogResult.Write(_L8("\nChannel Property Changed\n"));
		LogResult.Close();
    	LogResultSession.Close();
		}
	else if( iListenType == 3)
		{
		RFile LogResult;
	    RFs LogResultSession;
	    User::LeaveIfError(LogResultSession.Connect());
	    if(LogResult.Open(LogResultSession ,_L("c:\\sensrlog.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
	        {
	        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\sensrdatalog.txt") , EFileWrite | EFileShareAny ) ;
	        }
	    TInt End = 0 ;
	    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
	    
		
		LogResult.Write(_L8("\nChannel Condition Set Changed\n"));
		LogResult.Close();
    	LogResultSession.Close();
		}
	
	TBuf8<50>CmdBuf(KStopNotification) ;
	CLiwGenericParamList* inputList = CLiwGenericParamList::NewL();
	CLiwGenericParamList* outList = CLiwGenericParamList::NewL();
	
	if( iListenType == 0)
		{
		inputList->AppendL(TLiwGenericParam(KStopNotificationType,TLiwVariant(KChnlData)));
		}
	else if( iListenType == 1)
		{
		inputList->AppendL(TLiwGenericParam(KStopNotificationType,TLiwVariant(KChannelChange)));
		}		
	else if( iListenType == 2)
		{
		inputList->AppendL(TLiwGenericParam(KStopNotificationType,TLiwVariant(KPropertyChange)));
		}
	else if( iListenType == 3)
		{
		inputList->AppendL(TLiwGenericParam(KStopNotificationType,TLiwVariant(KChnlCondnChange)));
		} 
	
	inputList->AppendL(TLiwGenericParam(KChnlId,TLiwVariant(iChannelId)));
	iSensorInterface->ExecuteCmdL(CmdBuf , *inputList , *outList);

	CActiveScheduler *current = CActiveScheduler :: Current() ;
	current->Stop();
	}*/


	

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctcalprovider_combined::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcalprovider_combined::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctcalprovider_combined::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "operations1", Ctcalprovider_combined::operations1 ),
        ENTRY( "Cal_ops2", Ctcalprovider_combined::Cal_ops2 ),
       // ENTRY( "Cal_ops3", Ctcalprovider_combined::Cal_ops3 ),
        ENTRY( "Cal_ops4", Ctcalprovider_combined::Cal_ops4 ),
        ENTRY( "Cal_ops5", Ctcalprovider_combined::Cal_ops5 ),
        ENTRY( "Cal_ops6", Ctcalprovider_combined::Cal_ops6 ),
        ENTRY( "Cal_ops7", Ctcalprovider_combined::Cal_ops7 ),
       // ENTRY( "Cal_ops8", Ctcalprovider_combined::Cal_ops8 ),
        //ENTRY( "Cal_ops9", Ctcalprovider_combined::Cal_ops9 ),
        ENTRY( "Cal_ops10", Ctcalprovider_combined::Cal_ops10 ),
        ENTRY( "Cal_ops11", Ctcalprovider_combined::Cal_ops11 ),
     //   ENTRY( "Cal_ops12", Ctcalprovider_combined::Cal_ops12 ),
      //  ENTRY( "Cal_ops13", Ctcalprovider_combined::Cal_ops13 ),
      //  ENTRY( "Cal_ops12", Ctcalprovider_combined::Cal_ops12 ),
       // ENTRY( "Cal_ops13", Ctcalprovider_combined::Cal_ops13 ),
        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


TBuf<50> data ;
TBuf<50> file_attach ;
TBuf<50> att;
TInt flagg = 0;
CLiwGenericParamList* inParamList;


// -----------------------------------------------------------------------------
// Ctcalprovider_combined::operations1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::operations1( CStifItemParser& aItem )
    {

    struct ParamPass* arg1 = new ParamPass();
    arg1->it = &aItem;
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;

    //creating the thread , this thread is reponsible for sending the request to SAPI
    TInt ret = FunctionThread.Create( _L("FunctionThread1"), ThreadFunction ,KDefaultStackSize ,
    						NULL ,( TAny * ) arg1);

    User::LeaveIfError(ret);
    FunctionThread.Logon(Status);
    FunctionThread.Resume() ;

    // Waiting for thread to die in other words we are making asynch call to synch call :-))
    User :: WaitForRequest (Status)	;

    FunctionThread.Close();

    delete arg1;
	return Status.Int() ;


    }
    
// -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops2
// create cal entry with msg sender information
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops2( CStifItemParser& aItem )
    {

		TInt result=KErrNone;  

		TInt err;
				
    
	__UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParam = &(iServiceHandler->InParamListL());
   	CLiwGenericParamList* outParam = &(iServiceHandler->OutParamListL());
	CLiwCriteriaItem* crit_msg = CLiwCriteriaItem::NewL(1, KMsgIDataSource,KMsgService);
    
    crit_msg->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a_msg;
   	a_msg.AppendL(crit_msg);    

   	iServiceHandler->AttachL(a_msg);
    iServiceHandler->ExecuteServiceCmdL(*crit_msg, *inParam, *outParam); 
	TInt pos_msg = 0;
   	MLiwInterface* interface_msg = NULL;
    
   	outParam->FindFirst(pos_msg,KMsgIDataSource);
   	if(pos_msg != KErrNotFound)
     {
    	 interface_msg = (*outParam)[pos_msg].Value().AsInterface();	
      }

	inParam->Reset();
	outParam->Reset();
	
	delete crit_msg;
	crit_msg = NULL;
	a_msg.Reset();
	
	inParam->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParam->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9740067396") )));
	inParam->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("Roshan") )));
	
	TRAPD(err1,interface_msg->ExecuteCmdL( KMsgSendCmd ,*inParam ,*outParam,0,NULL ));
 	if(err1 == KErrNone)
 	{
 		TInt index = 0;
		const TLiwGenericParam* err2 = outParam->FindFirst(index,KErrCode);
		err1 = err2->Value().AsTInt32();
 	}
	
	if(err1 != KErrNone)
		result = err1;
	
	// send same message again
	
	TRAPD(err3,interface_msg->ExecuteCmdL( KMsgSendCmd ,*inParam ,*outParam,0,NULL ));
 	if(err3 == KErrNone)
 	{
 		TInt index1 = 0;
		const TLiwGenericParam* err4 = outParam->FindFirst(index1,KErrCode);
		err3 = err4->Value().AsTInt32();
 	}
	
	if(err3 != KErrNone && result == KErrNone)
		result = err1;
			
			
	inParam->Reset();
	outParam->Reset();
	
	// retreive the list of messages 
	
	TLiwVariant content(_L8("Inbox"));
	TLiwGenericParam element1 ;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inParam->AppendL(element1);
	content.Reset();
	element1.Reset();
   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

    CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
    CleanupStack::PushL(mtmtypelist);
    
    
    TLiwVariant mmsmtm(KMessageTypeSMS);// how the user wud gv this param
    mtmtypelist->AppendL(mmsmtm);
    mmsmtm.Reset();
    
    TLiwVariant add1(mtmtypelist);
    
    map1->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
    mtmtypelist->DecRef();
    CleanupStack::Pop(mtmtypelist);
    add1.Reset();	
    
    TLiwVariant filterparam1(map1);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam1);
	filterparam1.Reset();
	
    inParam->AppendL(element2);
	element2.Reset();
		
    map1->DecRef();
    CleanupStack::Pop(map1);
    
    TRAP(err,interface_msg->ExecuteCmdL( KMsgGetListCmd ,*inParam ,*outParam));
    TInt pos = 0 ;
    TBuf<40> buf ;
    
    const TLiwGenericParam* output1 = outParam->FindFirst( pos,_L8("ReturnValue"));
    TPtrC sender_text;
    TInt count=0;
    if(output1)     
			{
				TInt err = output1->Value().AsTInt32();
				CLiwIterable* iterlist2 = output1->Value().AsIterable();

			    TLiwVariant data;
			    
	    	    while( iterlist2->NextL(data))
				{
					const CLiwMap* res = data.AsMap();
					if ( res )
					{
						count++;
						TLiwVariant text;
						if(res->FindL(_L8("Sender"), text))
						{
							TPtrC sender_text = text.AsDes();
							
							buf.Copy(sender_text) ;
							iLog->Log(buf) ;
																											
						}
						text.Reset();
					}
					else
						result = KErrGeneral;
			  	}
			  		
			  	data.Reset();	
			  	
			  
			} 
			
	inParam->Reset();
	outParam->Reset();
	
	interface_msg->Close();	
	
	// create a cal entry
	
	CLiwGenericParamList* inParamListe= &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamListe,*outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamListe->Reset();
	outParamList->Reset();
	
	RemoveProvCalendar(inParamListe, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamListe, outParamList, interface, KTestCal1File);
	
	
	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamListe->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
	map->InsertL(_L8("Type"), TLiwVariant( _L("ToDo")  ));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Private")));
	map->InsertL(_L8("Description"), TLiwVariant(buf));
	map->InsertL(_L8("Status"), TLiwVariant(_L("TodoNeedsAction")));
	
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamListe->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdAdd ,*inParamListe,*outParamList));
	
	if(err_list == KErrNone)
 	{
 		TInt index = 0;
		const TLiwGenericParam* err5 = outParamList->FindFirst(index,KErrCode);
		err_list = err5->Value().AsTInt32();
 	}
	
	if(err_list != KErrNone && result == KErrNone)
		result = err1;
		 
		 
	inParamListe->Reset();
	outParamList->Reset();
//	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	iServiceHandler->Reset();	
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;	


    }
    
// -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops4
// create cal entry with loc information
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops4( CStifItemParser& aItem )
    {

		TInt result=KErrNone;  

		TInt err;
				
    
	__UHEAP_MARK;

	TBuf8<50> locdata  ;
	TBuf8<150> locdata1 ;
	TBuf8<50> locdata2 ;
	TBuf8<50> locdata3 ;
	
	TRealFormat format ;
   
    // LOAD LOCATION SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSourceloc , KLocationContents);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray al;
	al.AppendL(crit);	
	ServiceHandler->AttachL(al) ;

	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
	// EXTRACT LOCATION INTERFACE	

	TInt pos = 0;	
	const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCodeloc) ;
	 
	pos = 0 ;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);
	
    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
  
    outputlist->Reset() ;
    inputlist->Reset() ;
    
    
    // EXTRACT CALENDAR INTERFACE	
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	//SET LOCATION IDENTITY INFO
	
    TBuf8<20>CmdBufSet(KCmdSetIdentity) ;
    
    CLiwList* requestorList = CLiwDefaultList::NewL();
    CLiwDefaultMap *RequestorMap  = CLiwDefaultMap::NewL() ;
    RequestorMap->InsertL(KRequestMapType ,  TLiwVariant((TInt32 )CRequestor::ERequestorService));
    RequestorMap->InsertL(KRequestMapFormat , TLiwVariant( (TInt32)CRequestor::EFormatApplication) ) ;
    _LIT(KRequestinfo , "Location Test Application") ;
	
    RequestorMap->InsertL(KRequestMapData , TLiwVariant(KRequestinfo));
    requestorList->AppendL(TLiwVariant(RequestorMap));
    RequestorMap->DecRef();
  
    inputlist->AppendL(TLiwGenericParam(KRequestorList,TLiwVariant(requestorList)));
    requestorList->DecRef();
    locinterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist);
  
    RequestorMap->DecRef() ; //Extra DecRef()  

    
    // EXECUTE GET LOCATION
    
    TBuf8<20>CmdBuf(KCmdGetLocation) ;    
    outputlist->Reset() ;
    inputlist->Reset() ;
    
	locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);
	
	pos = 0 ;	
	const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCodeloc ) ;
	
	if(!ErrorParm)
	{
		return KErrGeneral ;
	}
	
	if((ErrorParm->Value()).AsTInt32() )
	{
		return (ErrorParm->Value()).AsTInt32() ;	
	}

	TInt index = 0 ;
	const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KLocationMap);	

	TLiwVariant Variant,PosVariant ;
	Variant = GenericParam->Value() ;
	const	CLiwMap *LocMap = Variant.AsMap() ;

	LocMap->FindL(KLongitudeKey , PosVariant) ;
	TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
	locdata1.Append(_L8("  longitude = "));
	locdata.Num(LongData , format) ;
	locdata1.Append(locdata);

	LocMap->FindL(KLatitudeKey ,PosVariant) ;           
	TReal64 LatData = (TReal64)PosVariant.AsTReal() ;  //Latitude
	locdata2.Num(LatData , format) ;
	locdata1.Append(_L8("  latitude = "));
	locdata1.Append(locdata2);
	
	LocMap->FindL(KAltitudeKey , PosVariant) ;         
	TReal32 AltData = PosVariant.AsTReal() ;           //Altitude
	locdata3.Num(AltData , format) ;
	locdata1.Append(_L8("  altitude = "));
	locdata1.Append(locdata3);

	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Priority"),TLiwVariant(AltData));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAP(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
 		}
	
	result = err;
	
	locinterface->Close() ;
	ServiceHandler->Reset();
   	delete ServiceHandler ;
   	al.ResetAndDestroy() ;
	al.Close() ;
	a.ResetAndDestroy() ;
	a.Close() ;
	
	
	inParamList->Reset();
	outParamList->Reset();

    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	iServiceHandler->Reset();
	delete iServiceHandler;
    
    __UHEAP_MARKEND;
    
    return result;

    }
    
 // -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops5
// create cal entry with loc information
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops5( CStifItemParser& aItem )
    {

		TInt result=KErrNone;  

		TInt err;
				
    
	__UHEAP_MARK;

	TBuf8<50> locdata  ;
	TBuf8<150> locdata1 ;
	TBuf8<50> locdata2 ;
	TBuf8<50> locdata3 ;
	
	TRealFormat format ;
   
    // LOAD LOCATION SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSourceloc , KLocationContents);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray al;
	al.AppendL(crit);	
	ServiceHandler->AttachL(al) ;

	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
	// EXTRACT LOCATION INTERFACE	

	TInt pos = 0;	
	const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCodeloc) ;
	 
	pos = 0 ;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);
	
    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
  
    outputlist->Reset() ;
    inputlist->Reset() ;
    
    
    // EXTRACT CALENDAR INTERFACE	
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal2File);
	
	//SET LOCATION IDENTITY INFO
	
    TBuf8<20>CmdBufSet(KCmdSetIdentity) ;
    
    CLiwList* requestorList = CLiwDefaultList::NewL();
    CLiwDefaultMap *RequestorMap  = CLiwDefaultMap::NewL() ;
    RequestorMap->InsertL(KRequestMapType ,  TLiwVariant((TInt32 )CRequestor::ERequestorService));
    RequestorMap->InsertL(KRequestMapFormat , TLiwVariant( (TInt32)CRequestor::EFormatApplication) ) ;
    _LIT(KRequestinfo , "Location Test Application") ;
	
    RequestorMap->InsertL(KRequestMapData , TLiwVariant(KRequestinfo));
    requestorList->AppendL(TLiwVariant(RequestorMap));
    RequestorMap->DecRef();
  
    inputlist->AppendL(TLiwGenericParam(KRequestorList,TLiwVariant(requestorList)));
    requestorList->DecRef();
    locinterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist);
  
    RequestorMap->DecRef() ; //Extra DecRef()  

    
    // EXECUTE GET LOCATION
    
    TBuf8<20>CmdBuf(KCmdGetLocation) ;    
    outputlist->Reset() ;
    inputlist->Reset() ;
    
	locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);
	
	pos = 0 ;	
	const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCodeloc ) ;
	
	if(!ErrorParm)
	{
		return KErrGeneral ;
	}
	
	if((ErrorParm->Value()).AsTInt32() )
	{
		return (ErrorParm->Value()).AsTInt32() ;	
	}

	TInt index = 0 ;
	const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KLocationMap);	

	TLiwVariant Variant,PosVariant ;
	Variant = GenericParam->Value() ;
	const	CLiwMap *LocMap = Variant.AsMap() ;

	LocMap->FindL(KLongitudeKey , PosVariant) ;
	TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
	locdata1.Append(_L8("  longitude = "));
	locdata.Num(LongData , format) ;
	locdata1.Append(locdata);

	LocMap->FindL(KLatitudeKey ,PosVariant) ;           
	TReal64 LatData = (TReal64)PosVariant.AsTReal() ;  //Latitude
	locdata2.Num(LatData , format) ;
	locdata1.Append(_L8("  latitude = "));
	locdata1.Append(locdata2);
	
	LocMap->FindL(KAltitudeKey , PosVariant) ;         
	TReal32 AltData = PosVariant.AsTReal() ;           //Altitude
	locdata3.Num(AltData , format) ;
	locdata1.Append(_L8("  altitude = "));
	locdata1.Append(locdata3);

	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Priority"),TLiwVariant(AltData));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAP(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
 		}
	
	// EXECUTE GET LOCATION AGAIN
	
	outputlist->Reset() ;
    inputlist->Reset() ;
    
    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);
	
	pos = 0 ;	
	const TLiwGenericParam *ErrorParm1 =  outputlist->FindFirst(pos ,KErrorCodeloc ) ;
	
	if(!ErrorParm1)
	{
		return KErrGeneral ;
	}
	
	if((ErrorParm1->Value()).AsTInt32() )
	{
		return (ErrorParm1->Value()).AsTInt32() ;	
	}

	index = 0 ;
	TReal32 CalAltData;
	TReal32 CalAltData1;
	const TLiwGenericParam *GenericParam1  = outputlist->FindFirst(index , KLocationMap);	

	Variant = GenericParam1->Value() ;
	LocMap = Variant.AsMap() ;

	LocMap->FindL(KLongitudeKey , PosVariant) ;
	TReal64 LongData1 = (TReal64)PosVariant.AsTReal() ; //Longitude
	
	LocMap->FindL(KLatitudeKey ,PosVariant) ;           
	TReal64 LatData1 = (TReal64)PosVariant.AsTReal() ;  //Latitude
		
	LocMap->FindL(KAltitudeKey , PosVariant) ;         
	TReal32 AltData1 = PosVariant.AsTReal() ;           //Altitude
	
	// Create another cal entry with new loc information
	
	inParamList->Reset();
	outParamList->Reset();
	
	
	TLiwGenericParam dsNameParam1(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam1);
			
	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

	map1->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map1->InsertL(_L8("Type"),TLiwVariant(_L("DayEvent")));
	map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EAugust,25,0,0,0,0))));
	map1->InsertL(_L8("Priority"),TLiwVariant(AltData1));		
			
	TLiwVariant filterparam1(map1);
	TLiwGenericParam element1 ;	
	element1.SetNameAndValueL(_L8("Item"),filterparam1);
	filterparam1.Reset();
			
	inParamList->AppendL(element1);
	element1.Reset();
						
	map1->DecRef();
	CleanupStack::Pop(map1);
		    
	TRAPD(err2,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err2 == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err2 = err1->Value().AsTInt32();
 		}
 		
 	// Retreive the values from cal entries
 	
 	inParamList->Reset();
	outParamList->Reset();
 	
 	TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam2);
			
	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map2);

	map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map2->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
			
			
	TLiwVariant filterparam2(map2);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam2);
	filterparam2.Reset();
			
	inParamList->AppendL(element2);
	element2.Reset();
						
	map2->DecRef();
	CleanupStack::Pop(map2);
		    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			const CLiwMap* res = data.AsMap();
			TLiwVariant alt_data;
			if(res->FindL(_L8("Priority"), alt_data))
			{
			
				CalAltData = alt_data.AsTReal() ;		
		
			}
			else
				result = KErrGeneral;
			
			alt_data.Reset();
		}
		data.Reset();	
	} 
	
	inParamList->Reset();
	outParamList->Reset();
 	
 	TLiwGenericParam dsNameParam3(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam3);
			
	CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map3);

	map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map3->InsertL(_L8("Type"),TLiwVariant(_L("DayEvent")));
			
			
	TLiwVariant filterparam3(map3);
	TLiwGenericParam element3 ;	
	element3.SetNameAndValueL(_L8("Filter"),filterparam3);
	filterparam3.Reset();
			
	inParamList->AppendL(element3);
	element3.Reset();
						
	map3->DecRef();
	CleanupStack::Pop(map3);
		    
		    		
	TRAPD(err_list1,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output1 = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output1->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			const CLiwMap* res = data.AsMap();
			TLiwVariant alt_data;
			if(res->FindL(_L8("Priority"), alt_data))
			{
			
				CalAltData1 = alt_data.AsTReal() ;		
		
			}
			else
				result = KErrGeneral;
			
			alt_data.Reset();
		}
		data.Reset();	
	} 
				
    // Do math on location informations
    
    outputlist->Reset() ;
    inputlist->Reset() ;
    
	
	CLiwDefaultMap* src_map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(src_map);
	
	CLiwDefaultMap* dest_map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(dest_map);
	
	src_map->InsertL(_L8("Longitude"), TLiwVariant(LongData) );
	src_map->InsertL(_L8("Latitude"), TLiwVariant(LatData) );
	src_map->InsertL(_L8("Altitude"), TLiwVariant(CalAltData) );
	
	dest_map->InsertL(_L8("Longitude"), TLiwVariant(LongData1) );
	dest_map->InsertL(_L8("Latitude"), TLiwVariant(LatData1) );
	dest_map->InsertL(_L8("Altitude"), TLiwVariant(CalAltData1) );
	


	inputlist->AppendL(TLiwGenericParam( _L8("MathRequest"), TLiwVariant( _L("FindDistance") )));
	inputlist->AppendL(TLiwGenericParam( _L8("DistanceParamSource"), TLiwVariant( src_map )));
	inputlist->AppendL(TLiwGenericParam( _L8("DistanceParamDestination"), TLiwVariant( dest_map )));		
			
	locinterface->ExecuteCmdL(KCmdCalc , *inputlist , *outputlist);
	
	pos = 0 ;	
	const TLiwGenericParam *ErrorParm2 =  outputlist->FindFirst(pos ,KErrorCodeloc ) ;
	
	if(!ErrorParm2)
	{
		return KErrGeneral ;
	}
	
	if((ErrorParm2->Value()).AsTInt32() )
	{
		return (ErrorParm2->Value()).AsTInt32() ;	
	}
						
	src_map->DecRef();
	CleanupStack::Pop(dest_map);
    dest_map->DecRef();
	CleanupStack::Pop(src_map);
    
	locinterface->Close() ;
	ServiceHandler->Reset();
   	delete ServiceHandler ;
   	al.ResetAndDestroy() ;
	al.Close() ;
	a.ResetAndDestroy() ;
	a.Close() ;
	
	
	inParamList->Reset();
	outParamList->Reset();

    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	iServiceHandler->Reset();
	delete iServiceHandler;
    
    __UHEAP_MARKEND;
    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops6
// create cal entry with loc information, retreive loc information from cal and create a landmark
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops6( CStifItemParser& aItem )
    {

		TInt result=KErrNone;  

		TInt err;
				
    
	__UHEAP_MARK;

	TBuf8<50> locdata  ;
	TBuf8<150> locdata1 ;
	TBuf8<50> locdata2 ;
	TBuf8<50> locdata3 ;
	
	TRealFormat format ;
   
    // LOAD LOCATION SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSourceloc , KLocationContents);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray al;
	al.AppendL(crit);	
	ServiceHandler->AttachL(al) ;

	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	// LOAD LANDMARK SERVICE-HANDLER
    
    CLiwServiceHandler* lServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inps = &(lServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(lServiceHandler->OutParamListL());

	CLiwCriteriaItem* critl = CLiwCriteriaItem::NewL(1, KLandIDataSource , KLandService);
	critl->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray land_mark;
	land_mark.AppendL(critl);	
	lServiceHandler->AttachL(land_mark);

	lServiceHandler->ExecuteServiceCmdL(*critl, *inps, *outps);
	
	
	// EXTRACT LOCATION INTERFACE	

	TInt pos = 0;	
	const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCodeloc) ;
	 
	pos = 0 ;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);
	
    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
  
    outputlist->Reset() ;
    inputlist->Reset() ;
    delete crit;
	crit = NULL;
	al.Reset();
    
    
    // EXTRACT CALENDAR INTERFACE	
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	
	// EXTRACT LANDMARK INTERFACE	

	pos = 0;	
	const TLiwGenericParam *errorprm_landmmark = outps->FindFirst(pos,KErrorCodeloc) ;
	 
	pos=0;
 	const TLiwGenericParam *genericparm_landmark = outps->FindFirst(pos,KLandIDataSource);
	
    MLiwInterface* landinterface = (genericparm_landmark->Value()).AsInterface();
  
    outps->Reset();
    inps->Reset();
    delete critl;
	critl = NULL;
	land_mark.Reset();
	
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	//SET LOCATION IDENTITY INFO
	
    TBuf8<20>CmdBufSet(KCmdSetIdentity) ;
    
    CLiwList* requestorList = CLiwDefaultList::NewL();
    CLiwDefaultMap *RequestorMap  = CLiwDefaultMap::NewL() ;
    RequestorMap->InsertL(KRequestMapType ,  TLiwVariant((TInt32 )CRequestor::ERequestorService));
    RequestorMap->InsertL(KRequestMapFormat , TLiwVariant( (TInt32)CRequestor::EFormatApplication) ) ;
    _LIT(KRequestinfo , "Location Test Application") ;
	
    RequestorMap->InsertL(KRequestMapData , TLiwVariant(KRequestinfo));
    requestorList->AppendL(TLiwVariant(RequestorMap));
    RequestorMap->DecRef();
  
    inputlist->AppendL(TLiwGenericParam(KRequestorList,TLiwVariant(requestorList)));
    requestorList->DecRef();
    locinterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist);
  
    RequestorMap->DecRef() ; //Extra DecRef()  

    
    // EXECUTE GET LOCATION
    
    TBuf8<20>CmdBuf(KCmdGetLocation) ;    
    outputlist->Reset() ;
    inputlist->Reset() ;
    
	locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);
	
	pos = 0 ;	
	const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCodeloc ) ;
	
	if(!ErrorParm)
	{
		return KErrGeneral ;
	}
	
	if((ErrorParm->Value()).AsTInt32() )
	{
		return (ErrorParm->Value()).AsTInt32() ;	
	}

	TInt index = 0 ;
	const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KLocationMap);	

	TLiwVariant Variant,PosVariant ;
	Variant = GenericParam->Value() ;
	const	CLiwMap *LocMap = Variant.AsMap() ;

	LocMap->FindL(KLongitudeKey , PosVariant) ;
	TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
	locdata1.Append(_L8("  longitude = "));
	locdata.Num(LongData , format) ;
	locdata1.Append(locdata);

	LocMap->FindL(KLatitudeKey ,PosVariant) ;           
	TReal64 LatData = (TReal64)PosVariant.AsTReal() ;  //Latitude
	locdata2.Num(LatData , format) ;
	locdata1.Append(_L8("  latitude = "));
	locdata1.Append(locdata2);
	
	LocMap->FindL(KAltitudeKey , PosVariant) ;         
	TReal32 AltData = PosVariant.AsTReal() ;           //Altitude
	locdata3.Num(AltData , format) ;
	locdata1.Append(_L8("  altitude = "));
	locdata1.Append(locdata3);

	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Priority"),TLiwVariant(AltData));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAP(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
 		}
	
	if(err != KErrNone)
 		result = err;
 	
 	// Retreive the values from cal entries
 	
 	inParamList->Reset();
	outParamList->Reset();
 	
 	TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam2);
			
	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map2);

	map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map2->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
			
			
	TLiwVariant filterparam2(map2);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam2);
	filterparam2.Reset();
			
	inParamList->AppendL(element2);
	element2.Reset();
						
	map2->DecRef();
	CleanupStack::Pop(map2);
	TReal32 CalAltData;	    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			const CLiwMap* res = data.AsMap();
			TLiwVariant alt_data;
			if(res->FindL(_L8("Priority"), alt_data))
			{
			
				CalAltData = alt_data.AsTReal() ;		
			
			}
			else
				result = KErrGeneral;
			
			alt_data.Reset();
		}
		data.Reset();	
	} 
	
	inParamList->Reset();
	outParamList->Reset();   	
	
	// Create a landmark entry using the altitude information
 	
 	
 	TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
   
    _LIT(KDescription,"Extremely good ");
    _LIT(KPhone1,"123456");
    _LIT(KOffice1,"eat");
    _LIT(KOffice2,"sleep");
    _LIT(KOffice3,"drink");
    TReal64 latitude = 45.1122;
    TReal64 longitude = 34.0099;
   
    TReal32 hacc = 0.1234;
    TReal32 vacc = 0.3456;
    TPosition locale;
    locale.SetCurrentTime();
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
   // inps->AppendL(TLiwGenericParam(KDataFields,TLiwVariant(landmarkMap)));
   // iIflandmarks->ExecuteCmdL(KCmdAdd,*inps,*outps,0,0);
   // landmarkMap->DecRef();
   // TInt index1 = 0;
   // TInt32 err1 = -1;
   // const TLiwGenericParam* outParam1 = outps->FindFirst(index1,KErrorCode);
   // if( outParam1 )
     // {
     // outParam1->Value().Get(err1);
     // }
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
    //position
    CLiwMap* position = CLiwDefaultMap::NewL();
    position->InsertL(KLatitude,TLiwVariant(latitude));
    position->InsertL(KLongitude,TLiwVariant(longitude));
    position->InsertL(KAltitude,TLiwVariant(CalAltData));
    position->InsertL(KHAccuracy,TLiwVariant(hacc));
    position->InsertL(KVAccuracy,TLiwVariant(vacc));
    position->InsertL(KTStamp,TLiwVariant(locale.Time()));    
    landmarkMap->InsertL(KLandmarkPosition,TLiwVariant(position));
    position->DecRef();
    //coverage radius
    TReal32 covRad = 12.3456; 
    landmarkMap->InsertL(KCoverageRadius,TLiwVariant(covRad));
    //categoryInfo
    CLiwList* catList = CLiwDefaultList::NewL();
    CPosLandmarkDatabase* db = CPosLandmarkDatabase ::OpenL(KTestDbUri);
    CleanupStack::PushL(db);
    ExecuteAndDeleteLD(db->InitializeL());
    CPosLmCategoryManager* catMan = CPosLmCategoryManager::NewL(*db);
    CleanupStack::PushL(catMan);
    RemoveAllCategories(catMan);
    CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
    TPosLmItemId catId;
    category->SetCategoryNameL(KOffice1);
  	catId = catMan->AddCategoryL(*category);
  	TBuf<5> catIdString;
    catIdString.NumFixedWidth(catId,EDecimal,5);
    
    catList->AppendL(TLiwVariant(catIdString));
    category->SetCategoryNameL(KOffice2);
  	catId = catMan->AddCategoryL(*category);
  	TBuf<5> catIdString1;
    catIdString1.NumFixedWidth(catId,EDecimal,5);
  	catList->AppendL(TLiwVariant(catIdString1));
  	category->SetCategoryNameL(KOffice3);
  	catId = catMan->AddCategoryL(*category);
  	TBuf<5> catIdString2;
    catIdString2.NumFixedWidth(catId,EDecimal,5);
  	catList->AppendL(TLiwVariant(catIdString2));
    CleanupStack::PopAndDestroy(3,db);
    landmarkMap->InsertL(KCategoryInfo,TLiwVariant(catList));
    
      catList->DecRef();
    //icon
    _LIT(KFileName,"//s60//icons//qgn_graf_s60_logo.svg");
    landmarkMap->InsertL(KIconFile,TLiwVariant(KFileName));
    landmarkMap->InsertL(KIconIndex,TLiwVariant(17));
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    //lm fields
    CLiwMap* landmarkFields = CLiwDefaultMap::NewL();
    landmarkFields->InsertL(KLandmarkTelephone,TLiwVariant(KPhone1));
    landmarkMap->InsertL(KLandmarkFields,TLiwVariant(landmarkFields));
    landmarkFields->DecRef();
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();   
    

    landinterface->ExecuteCmdL(KCmdAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    index = 0;
    err = 0;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      err = outParam->Value().AsTInt32();
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("AddLandmarkL Error="));
      LogResult.Write(error);
      if(result == KErrNone)
      	result = err;
      LogResult.Write(_L8("\n"));
      }
    LogResult.Close();
    LogResultSession.Close();
    position->DecRef();
    landmarkMap->DecRef(); 
	
	locinterface->Close() ;
	ServiceHandler->Reset();
   	delete ServiceHandler ;
   	
    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();	
   	
	iServiceHandler->Reset();
	delete iServiceHandler;
	
	landinterface->Close();
	lServiceHandler->Reset();
   	delete lServiceHandler ;
    
    __UHEAP_MARKEND;
    
    return result;

    }

    
// -----------------------------------------------------------------------------
// Ctcalprovider_combined::AddLandmarkL
// function to add a landmark
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::AddLandmarkL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In AddLandmarkL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }


    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

    TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    
    _LIT(KDescription,"Extremely good chinese food");
    _LIT(KPhone1,"123456");
    _LIT(KOffice1,"eat");
    _LIT(KOffice2,"sleep");
    _LIT(KOffice3,"drink");
    TReal64 latitude = 45.1122;
    TReal64 longitude = 34.0099;
    TReal32 altitude = 41.0022;
    TReal32 hacc = 0.1234;
    TReal32 vacc = 0.3456;
    TPosition locale;
    locale.SetCurrentTime();
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    inps->AppendL(TLiwGenericParam(KDataFields,TLiwVariant(landmarkMap)));
    iIflandmarks->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    TInt index1 = 0;
    TInt32 err1 = -1;
    const TLiwGenericParam* outParam1 = outps->FindFirst(index1,KErrorCode);
    if( outParam1 )
      {
      outParam1->Value().Get(err1);
      }
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
    //position
    CLiwMap* position = CLiwDefaultMap::NewL();
    position->InsertL(KLatitude,TLiwVariant(latitude));
    position->InsertL(KLongitude,TLiwVariant(longitude));
    position->InsertL(KAltitude,TLiwVariant(altitude));
    position->InsertL(KHAccuracy,TLiwVariant(hacc));
    position->InsertL(KVAccuracy,TLiwVariant(vacc));
    position->InsertL(KTStamp,TLiwVariant(locale.Time()));    
    landmarkMap->InsertL(KLandmarkPosition,TLiwVariant(position));
    position->DecRef();
    //coverage radius
    TReal32 covRad = 12.3456; 
    landmarkMap->InsertL(KCoverageRadius,TLiwVariant(covRad));
    //categoryInfo
    CLiwList* catList = CLiwDefaultList::NewL();
    CPosLandmarkDatabase* db = CPosLandmarkDatabase ::OpenL(KTestDbUri1);
    CleanupStack::PushL(db);
    ExecuteAndDeleteLD(db->InitializeL());
    CPosLmCategoryManager* catMan = CPosLmCategoryManager::NewL(*db);
    CleanupStack::PushL(catMan);
    RemoveAllCategories(catMan);
    CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
    TPosLmItemId catId;
    category->SetCategoryNameL(KOffice1);
  	catId = catMan->AddCategoryL(*category);
  	TBuf<5> catIdString;
    catIdString.NumFixedWidth(catId,EDecimal,5);
    
    catList->AppendL(TLiwVariant(catIdString));
    category->SetCategoryNameL(KOffice2);
  	catId = catMan->AddCategoryL(*category);
  	TBuf<5> catIdString1;
    catIdString1.NumFixedWidth(catId,EDecimal,5);
  	catList->AppendL(TLiwVariant(catIdString1));
  	category->SetCategoryNameL(KOffice3);
  	catId = catMan->AddCategoryL(*category);
  	TBuf<5> catIdString2;
    catIdString2.NumFixedWidth(catId,EDecimal,5);
  	catList->AppendL(TLiwVariant(catIdString2));
    CleanupStack::PopAndDestroy(3,db);
    landmarkMap->InsertL(KCategoryInfo,TLiwVariant(catList));
    catList->DecRef();
    //icon
    _LIT(KFileName,"//s60//icons//qgn_graf_s60_logo.svg");
    landmarkMap->InsertL(KIconFile,TLiwVariant(KFileName));
    landmarkMap->InsertL(KIconIndex,TLiwVariant(17));
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    //lm fields
    CLiwMap* landmarkFields = CLiwDefaultMap::NewL();
    landmarkFields->InsertL(KLandmarkTelephone,TLiwVariant(KPhone1));
    landmarkMap->InsertL(KLandmarkFields,TLiwVariant(landmarkFields));
    landmarkFields->DecRef();
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();   
    

    iIflandmarks->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    TInt index = 0;
    TInt32 err = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("AddLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }
    LogResult.Close();
    LogResultSession.Close();
    position->DecRef();
    landmarkMap->DecRef();

    return err;

    }

// -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops7
// create cal entry, use info from cal to update and delete landmark entry
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops7( CStifItemParser& /*aItem*/ )
    {

	TInt result=KErrNone;  

		TInt err;
		TInt flag=0;		
    
	__UHEAP_MARK;

	TBuf8<50> locdata  ;
	TBuf8<150> locdata1 ;
	TBuf8<50> locdata2 ;
	TBuf8<50> locdata3 ;
	
	TRealFormat format ;
   
    // LOAD LANDMARK SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KLandIDataSource , KLandService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray al;
	al.AppendL(crit);	
	ServiceHandler->AttachL(al) ;

	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
	// EXTRACT LANDMARK INTERFACE	

	TInt pos = 0;	
	const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCodeloc) ;
	 
	pos = 0 ;
 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLandIDataSource);
	
    MLiwInterface* landinterface = (genericparm->Value()).AsInterface();
  
    outputlist->Reset() ;
    inputlist->Reset() ;
    
    
    // EXTRACT CALENDAR INTERFACE	
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TPtrC desc_data;
	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Description"),TLiwVariant(_L("Test Landmark")));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAP(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
 		}
 		
 	
	
	// Retreive cal desc info
	
	inParamList->Reset();
	outParamList->Reset();
 	
 	TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam2);
			
	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map2);

	map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map2->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
			
			
	TLiwVariant filterparam2(map2);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam2);
	filterparam2.Reset();
			
	inParamList->AppendL(element2);
	element2.Reset();
						
	map2->DecRef();
	CleanupStack::Pop(map2);
	TReal32 CalAltData;	    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			const CLiwMap* res = data.AsMap();
			TLiwVariant desc;
			if(res->FindL(_L8("Description"), desc))
			{
			
				TPtrC desc_data = desc.AsDes() ;		
				TBuf<40> buf ;
				buf.Copy(desc_data) ;
				iLog->Log(buf) ;
				
				if(desc_data.Compare(_L("Test Landmark")) != 0)
					result = KErrGeneral;
				else
					flag=1;			
			}
			else
				result = KErrGeneral;
			
			desc.Reset();
		}
		data.Reset();	
	} 
	
	inParamList->Reset();
	outParamList->Reset();  
	 	
	
	// Update landmark if cal desc matches the landmark added
  
  
  	_LIT(KName1,"Mainland China");

  	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  	CleanupStack::PushL(db);
  	ExecuteAndDeleteLD(db->InitializeL());
	//  RemoveAllLandmarks(db);

 	 TPosLmItemId lmId;
 	 CPosLandmark* lm = CPosLandmark::NewLC();
 	 lm->SetLandmarkNameL(KName1);
 	 lmId = db->AddLandmarkL(*lm);

 	 lm = db->ReadLandmarkLC(lmId);

	if(result == KErrNone)
	{
		
		 /*Set the params*/
  	CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
  	CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

  	TLiwGenericParam param;
  	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  	inps->AppendL(param);
  	param.Reset();

 	 CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
 	 TBuf<5> lmIdString;
 	 lmIdString.NumFixedWidth(lm->LandmarkId(),EDecimal,5);
 	 landmarkMap->InsertL(KLandmarkId,TLiwVariant(lmIdString));
  	 landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
  	param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
 	 inps->AppendL(param);
  	landmarkMap->DecRef();
  	param.Reset();

 	 landinterface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
  	TInt index = 0;
  	TInt32 err_upd = -1;
  	const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  
  	if( outParam )
    {
    err_upd = outParam->Value().AsTInt32();
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    
    if(result == KErrNone)
    result = err_upd;
    }
    
    inps->Reset();
	outps->Reset();
	
    // Delete the Landmark
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  	inps->AppendL(param);
  	
    landmarkMap = CLiwDefaultMap::NewL();
    landmarkMap->InsertL(KLandmarkId,TLiwVariant(-8));
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    landmarkMap->DecRef();
    param.Reset();

    TRAPD(err_rem,landinterface->ExecuteCmdL(KRemove,*inps,*outps,0,0));
    
    index = 0;
    TInt32 err_del = -1;
    const TLiwGenericParam* outParam_del = outps->FindFirst(index,KErrorCode);
    if( outParam_del )
      {
      err_del = outParam_del->Value().AsTInt32();
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      
      if(result == KErrNone)
      	result = err_del;
      }
    
    inps->Reset();
	outps->Reset();
  }
 	 CleanupStack::PopAndDestroy(lm);

  	CleanupStack::PopAndDestroy(2,db);
  	ReleaseLandmarkResources();
  
  
	landinterface->Close() ;
	ServiceHandler->Reset();
   	delete ServiceHandler ;
   	al.ResetAndDestroy() ;
	al.Close() ;
	a.ResetAndDestroy() ;
	a.Close() ;
	
	
	
	inParamList->Reset();
	outParamList->Reset();

    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	iServiceHandler->Reset();
	delete iServiceHandler;
    
    __UHEAP_MARKEND;
    return result;  
   
    

    }
 
/* -----------------------------------------------------------------------------
 Ctcalprovider_combined::Cal_ops8
// create cal entry, use info from cal to create a contact
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops8( CStifItemParser& aItem )
    {

	TInt result=KErrNone;  
	TInt err_contact = -1;


	TRealFormat format ;
   
    // LOAD CONTACT SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContactIDataSource , KContactService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray ac;
	ac.AppendL(crit);	
	ServiceHandler->AttachL(ac) ;

	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
	// EXTRACT CONTACT INTERFACE	

	TInt pos = 0;
    MLiwInterface* cinterface = NULL;
    outputlist->FindFirst(pos,KContactIDataSource );
    if(pos != KErrNotFound)
        {
        cinterface = (*outputlist)[pos].Value().AsInterface();	
        }

	inputlist->Reset();
	outputlist->Reset();
	delete crit;
	crit = NULL;
	ac.Reset();
    
    // EXTRACT CALENDAR INTERFACE	
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TPtrC desc_data;
	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Description"),TLiwVariant(_L("Create Contact")));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAPD(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
 		}
 		
 	
	
	// Retreive cal desc info
	
	inParamList->Reset();
	outParamList->Reset();
 	
 	TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam2);
			
	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map2);

	map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map2->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
			
			
	TLiwVariant filterparam2(map2);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam2);
	filterparam2.Reset();
			
	inParamList->AppendL(element2);
	element2.Reset();
						
	map2->DecRef();
	CleanupStack::Pop(map2);
	TReal32 CalAltData;	    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			const CLiwMap* res = data.AsMap();
			TLiwVariant desc;
			if(res->FindL(_L8("Description"), desc))
			{
			
				TPtrC desc_data = desc.AsDes() ;		
				TBuf<40> buf ;
				buf.Copy(desc_data) ;
				iLog->Log(buf) ;
				
				if(desc_data.Compare(_L("Create Contact")) != 0)
					result = KErrGeneral;
						
			}
			else
				result = KErrGeneral;
			
			desc.Reset();
		}
		data.Reset();	
	} 
	
	inParamList->Reset();
	outParamList->Reset();  
	 	
	
	// Add contact
	
	if(result == KErrNone)
	{
		
		CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    
    	CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();     
    	pos = 0;  	          
    	fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));
    	
    	fieldMap->InsertL(KFieldValue,TLiwVariant(_L("ADDTest")));
   		pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    
    
    	pMap->InsertL(KContactId, TLiwVariant( _L("")));
    	pMap->InsertL(KFirstName, TLiwVariant(fieldMap));
    	
    	TLiwGenericParam param;
  		param.SetNameAndValueL(KContentType,TLiwVariant( _L("Contact")));
  		inputlist->AppendL(param);
  		param.Reset();
  		
  		
		TLiwGenericParam param_data;
  		param_data.SetNameAndValueL(KData,TLiwVariant(pMap));
  		inputlist->AppendL(param_data);
  		param_data.Reset();
        	
 		cinterface->ExecuteCmdL(KCmdAdd, *inputlist, *outputlist,0, NULL);
        
        const TLiwGenericParam* err_c = outputlist->FindFirst(pos,KErCode);
	    err_contact = err_c->Value().AsTInt32();
	   	
               
   		 if(err_contact != SErrNone)
        {
           result = KErrGeneral;
        }
                  
    	pMap->DecRef();
   		 fieldMap->DecRef();
    	
    
    	inputlist->Reset();
		outputlist->Reset();
                   
   
  }
 	cinterface->Close();
	ServiceHandler->Reset();
   	delete ServiceHandler ;
   	ac.ResetAndDestroy() ;
	ac.Close() ;
	a.ResetAndDestroy() ;
	a.Close() ;
	
	
	
	inParamList->Reset();
	outParamList->Reset();

    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	iServiceHandler->Reset();
	delete iServiceHandler;
    
    return result;   
   
    

    }
 
// -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops9
// test case to create contact, cal entry, Export contact
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops9( CStifItemParser& aItem )
    {

	TInt result=KErrNone;  
	TInt err_contact = -1;
	TInt err_get_contact = -1;
	TInt err_exp_contact = -1;
	TInt count=0;


	TRealFormat format ;
   
    // LOAD CONTACT SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContactIDataSource , KContactService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray ac;
	ac.AppendL(crit);	
	ServiceHandler->AttachL(ac) ;

	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
	// EXTRACT CONTACT INTERFACE	

	TInt pos = 0;
    MLiwInterface* cinterface = NULL;
    outputlist->FindFirst(pos,KContactIDataSource );
    if(pos != KErrNotFound)
        {
        cinterface = (*outputlist)[pos].Value().AsInterface();	
        }

	inputlist->Reset();
	outputlist->Reset();
	delete crit;
	crit = NULL;
	ac.Reset();
    
    // EXTRACT CALENDAR INTERFACE	
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TPtrC desc_data;
	
	// Add contact
	
		CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    
    	CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();     
    	pos = 0;  	          
    	fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));
    	
    	fieldMap->InsertL(KFieldValue,TLiwVariant(_L("ADDTest")));
   		pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    
    
    	pMap->InsertL(KContactId, TLiwVariant( _L("")));
    	pMap->InsertL(KFirstName, TLiwVariant(fieldMap));
    	
    	TLiwGenericParam param;
  		param.SetNameAndValueL(KContentType,TLiwVariant( _L("Contact")));
  		inputlist->AppendL(param);
  		param.Reset();
  		
  		
		TLiwGenericParam param_data;
  		param_data.SetNameAndValueL(KData,TLiwVariant(pMap));
  		inputlist->AppendL(param_data);
  		param_data.Reset();
        	
 		cinterface->ExecuteCmdL(KCmdAdd, *inputlist, *outputlist,0, NULL);
        
        const TLiwGenericParam* err_c = outputlist->FindFirst(pos,KErCode);
	    err_contact = err_c->Value().AsTInt32();
	   	
               
   		 if(err_contact != SErrNone)
        {
           result = KErrGeneral;
        }
                  
    	pMap->DecRef();
   		 fieldMap->DecRef();
    	
    
    	inputlist->Reset();
		outputlist->Reset();
                   
                   
                   
	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Description"),TLiwVariant(_L("Create Contact")));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAPD(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
 		}
 		
 	
	
	// Retreive cal desc info
	
	inParamList->Reset();
	outParamList->Reset();
 	
 	TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam2);
			
	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map2);

	map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map2->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
			
			
	TLiwVariant filterparam2(map2);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam2);
	filterparam2.Reset();
			
	inParamList->AppendL(element2);
	element2.Reset();
						
	map2->DecRef();
	CleanupStack::Pop(map2);
	TReal32 CalAltData;	    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			const CLiwMap* res = data.AsMap();
			TLiwVariant desc;
			if(res->FindL(_L8("Description"), desc))
			{
			
				TPtrC desc_data = desc.AsDes() ;		
				TBuf<40> buf ;
				buf.Copy(desc_data) ;
				iLog->Log(buf) ;
				
				if(desc_data.Compare(_L("Create Contact")) != 0)
					result = KErrGeneral;
						
			}
			else
				result = KErrGeneral;
			
			desc.Reset();
		}
		data.Reset();	
	} 
	
	inParamList->Reset();
	outParamList->Reset();  
	 	
	
	// Export contact
	
	if(result == KErrNone)
	{
		iIdArrayList.ResetAndDestroy();
	pos = 0;      	    
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));    
    inputlist ->AppendL( paramContentType );
    cinterface->ExecuteCmdL(KCmdGetList, *inputlist, *outputlist,0, NULL);
        
    const TLiwGenericParam* err_c2 = outputlist->FindFirst(pos,KErCode);
	err_get_contact = err_c2->Value().AsTInt32();
	   	
    pos = 0;
        TLiwVariant cntId;
        TLiwVariant entry;
        const CLiwMap* map = NULL;
       
        
        const TLiwGenericParam* outparam = outputlist->FindFirst( pos,_L8("ReturnValue"));
	
		CLiwIterable* iter = outparam->Value().AsIterable();
               
        
        while(1)
            {
            if(iter->NextL(entry))
                {
                map = entry.AsMap();
                //count = map->Count();       
                map->FindL(KContactId, cntId); 
                             
                TPtrC16 ptr = cntId.AsDes();   
                HBufC* cnt = HBufC::NewL(ptr.Length());
        		*cnt = ptr;
        		iIdArrayList.AppendL(cnt);              
              //  delete cnt;
                }
            else
                {
                break;                    
                }
            }
        entry.Reset();
        cntId.Reset();
        iter->Reset();
        map=NULL;
        
    inputlist->Reset();
	outputlist->Reset();  
    
    pMap = CLiwDefaultMap::NewL();
	
	RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\vcardExport.vcf") , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(_L("c:\\vcardExport.vcf"));
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();
    
    pos = 0;  	          
    TBuf<255> cntIdunicode;
    count = iIdArrayList.Count();
    cntIdunicode.Copy(*iIdArrayList[0]);
    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KContactId, TLiwVariant(cntIdunicode));
    
    pMap->InsertL(KDestFileNameParam, TLiwVariant( _L("c:\\vcardExport.vcf")));    
    
    TLiwGenericParam param;
  	param.SetNameAndValueL(KContentType,TLiwVariant( _L("Contact")));
  	inputlist->AppendL(param);
  	param.Reset();
  		
  	TLiwGenericParam param_data;
  	param_data.SetNameAndValueL(KData,TLiwVariant(pMap));
  	inputlist->AppendL(param_data);
  	param_data.Reset();
  	
  
	cinterface->ExecuteCmdL(KCmdExport, *inputlist, *outputlist,0, NULL);
        
    const TLiwGenericParam* err_c1 = outputlist->FindFirst(pos,KErCode);
	err_exp_contact = err_c1->Value().AsTInt32();
	   	
    if(err_exp_contact != SErrNone)
    {
       result = KErrGeneral;
    }
                  
    pMap->DecRef();
   	iIdArrayList.ResetAndDestroy();
	iIdArrayList.Close();        
    inputlist->Reset();
	outputlist->Reset();     
	
   
    }
 	cinterface->Close();
	ServiceHandler->Reset();
   	delete ServiceHandler ;
   	ac.ResetAndDestroy() ;
	ac.Close() ;
	a.ResetAndDestroy() ;
	a.Close() ;
	
	
	
	inParamList->Reset();
	outParamList->Reset();

    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	iServiceHandler->Reset();
	delete iServiceHandler;
    
    return result;   

    } */
    
    
// -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops10
// create cal entry, read cal info and log an event
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops10( CStifItemParser& aItem )
    {

	TInt result=KErrNone;  
	TInt err_logging = -1;
	TInt flag=0;
	__UHEAP_MARK;

	TRealFormat format ;
   
    // LOAD LOGGING SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KLoggingIDataSource , KLoggingService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray ac;
	ac.AppendL(crit);	
	ServiceHandler->AttachL(ac) ;

	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
	// EXTRACT LOGGING INTERFACE	

	TInt pos = 0;
    MLiwInterface* linterface = NULL;
    outputlist->FindFirst(pos,KLoggingIDataSource);
    if(pos != KErrNotFound)
        {
        linterface = (*outputlist)[pos].Value().AsInterface();	
        }

	inputlist->Reset();
	outputlist->Reset();
	delete crit;
	crit = NULL;
	ac.Reset();
    
    // EXTRACT CALENDAR INTERFACE	
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TPtrC desc_data;
	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Description"),TLiwVariant(_L("Log an event")));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAPD(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
 		}
 		
 	
	
	// Retreive cal desc info
	
	inParamList->Reset();
	outParamList->Reset();
 	
 	TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam2);
			
	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map2);

	map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map2->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
			
			
	TLiwVariant filterparam2(map2);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam2);
	filterparam2.Reset();
			
	inParamList->AppendL(element2);
	element2.Reset();
						
	map2->DecRef();
	CleanupStack::Pop(map2);
	TReal32 CalAltData;	    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			const CLiwMap* res = data.AsMap();
			TLiwVariant desc;
			if(res->FindL(_L8("Description"), desc))
			{
			
				TPtrC desc_data = desc.AsDes() ;		
				TBuf<40> buf ;
				buf.Copy(desc_data) ;
				iLog->Log(buf) ;
				
				if(desc_data.Compare(_L("Log an event")) != 0)
					result = KErrGeneral;
				else
					flag = 1;
						
			}
			else
				result = KErrGeneral;
			
			desc.Reset();
		}
		data.Reset();	
	} 
	
	inParamList->Reset();
	outParamList->Reset();  
	 	
	
	// Log an event
	
	if(result == KErrNone && flag==1)
	{
		
		CEventDet *eventDetails = CEventDet::NewL() ;
		CFilterDetails *filterDetails = CFilterDetails::NewL() ;

        TInt ParsedValue ;
      
    	 TBufC<100> String; 
      	 TPtrC sptr;
     	  sptr.Set(String);
     	  TInt ParsedValue1 ;      
       
     	 if(aItem.GetNextInt( ParsedValue) != KErrNone )
         {
          _LIT(KLog , "Eventid  not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;
         }
     
		if((ParsedValue >= KCallEvent ) && (ParsedValue <=KLogLbsAssistanceDataEvent))
		{
		eventDetails->SetEventType(ParsedValue) ;
			switch(ParsedValue)
        	{
        
        
        		case  KCallEvent :
            	 {
             		filterDetails->SetEventType(KLogCallEventType) ;
             		break ;
                
             	 }
                 
       			 case  KLogDataEvent :           
                
             	 filterDetails->SetEventType(KLogDataEventType) ;
              	break;
             
                 
        		case  KLogFaxEvent :
              	filterDetails->SetEventType(KLogFaxEventType) ;
                 break ;
                 
       			 case  KLogShortMessageEvent :
              	filterDetails->SetEventType(KLogShortMessageEventType) ;
                 break ;
                 
        		case  KLogMailEvent :
             	 filterDetails->SetEventType(KLogMailEventType) ;
                 break ;
                 
       			 case  KLogTaskSchedulerEvent :
             	 filterDetails->SetEventType(KLogTaskSchedulerEventType) ;
                 break ;
                 
       			 case  KLogPacketDataEvent :
              	filterDetails->SetEventType(KLogPacketDataEventType) ;
                 break ;
                 
        		case  KLogLbsSelfLocateEvent :
              	filterDetails->SetEventType(KLogLbsSelfLocateEventType) ;
                 break ;
                 
        		case  KLogLbsExternalLocateEvent :
              	filterDetails->SetEventType(KLogLbsExternalLocateEventType) ;
                 break ;
                 
        		case  KLogLbsTransmitLocationEvent :
              	filterDetails->SetEventType(KLogLbsTransmitLocationEventType) ;
                 break ;
                 
        		case  KLogLbsNetworkLocateEvent :
             	 filterDetails->SetEventType(KLogLbsNetworkLocateEventType) ;
                 break ;
                 
        		case  KLogLbsAssistanceDataEvent :
              	filterDetails->SetEventType(KLogLbsAssistanceDataEventType) ;
                 break ; 
                 
           		 default:
            
            		break;
                                                                       
        	}
        
			
		}

		else 
		{
		_LIT(KLog , "Wrong input EventID") ;
		iLog->Log(KLog) ;		
		}     

     
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         _LIT(KLog , "duration not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument) ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetDurationType(ParsedValue) ;
        }
        
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
        _LIT(KLog , "contact id not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetContactType(ParsedValue) ;
         filterDetails->SetContactType(ParsedValue) ;
        }
        
        
        
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         _LIT(KLog , "link value not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetLinkType(ParsedValue) ;
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         _LIT(KLog , "time value not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue> 0 )
        {
        
         TTime time(ParsedValue);
         eventDetails->SetTimer(time) ;
         filterDetails->SetTimer(time) ;
        }
        
        _LIT(KNull,"NULL");
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "subject not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetSubjectType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "phone number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetNumberType(sptr) ;
          filterDetails->SetNumberType(sptr) ;    
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "remote party number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetRemotePartyType(sptr) ;
          filterDetails->SetRemotePartyType(sptr) ;    
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
          _LIT(KLog , "direction not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0)
    	{
		eventDetails->SetDirectionType(ParsedValue) ;   
		filterDetails->SetDirectionType(ParsedValue) ;  	
    	}   	
        
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "description not found") ;
	 	 iLog->Log(KLog) ;
          
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetDescriptionType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) !=KErrNone)
        {
          _LIT(KLog , "status value not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0)
        {
          eventDetails->SetStatusType(ParsedValue) ; 
          filterDetails->SetStatusType(ParsedValue) ;   
        }     
        
        
        if(aItem.GetNextInt(ParsedValue1) != KErrNone)
        {
         _LIT(KLog , "Sync/Async version  not found") ;
	 	  iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }      
        
     
        if(aItem.GetNextInt(ParsedValue) != KErrNone )
        {
         _LIT(KLog , "Expected value not found") ;
	 	  iLog->Log(KLog) ;
        
        }
        else
        {
            result = ParsedValue ;
        }
        
        filterDetails->SetAllEvent(TRUE);
        
        CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  		EventDetails->InsertL(KEventTypeKey , TLiwVariant(eventDetails->GetEventType()) );
  
  
 		if(((unsigned int)eventDetails->GetDurationType()!=0))
 		{
 			EventDetails->InsertL(KEventDurationKey ,TLiwVariant((unsigned int)eventDetails->GetDurationType()) );
 		}
    
 		if(eventDetails->GetContactType() !=0 )
 		{
 			EventDetails->InsertL(KContactidKey , TLiwVariant(eventDetails->GetContactType()) );
 		}
    
 		if((unsigned int)eventDetails->GetLinkType()!=0)
 		{
 			EventDetails->InsertL(KLinkKey , TLiwVariant((unsigned int)eventDetails->GetLinkType()) );
 		}
    
		 if(eventDetails->GetTimer() !=0 )
 		{
 			EventDetails->InsertL(KEventTimeKey , TLiwVariant(eventDetails->GetTimer())) ;
 		}   
   
  		TBuf<10> EmptyDes ;
   
   
   		//if(ptr.Compare(KNull) )
   		if(eventDetails->GetSubjectType() != EmptyDes)
   		{
   	 		EventDetails->InsertL(KSubjectKey , TLiwVariant(eventDetails->GetSubjectType())) ;
   		}  
   
		if(eventDetails->GetNumberType()!= EmptyDes)
 		{
 			EventDetails->InsertL(KPhoneNumberKey , TLiwVariant(eventDetails->GetNumberType())) ;
 		}
    
 		if(eventDetails->GetRemotePartyType() != EmptyDes)
 		{
 			EventDetails->InsertL(KRemotePartyKey , TLiwVariant(eventDetails->GetRemotePartyType())) ;
 		}
    
 		if(eventDetails->GetDirectionType() >= 0 )
		{
 			EventDetails->InsertL(KDirectionKey , TLiwVariant(eventDetails->GetDirectionType())) ;
 		}
    
		 if(eventDetails->GetDescriptionType() != EmptyDes)
 		{
 			EventDetails->InsertL(KDescriptionKey , TLiwVariant(eventDetails->GetDescriptionType())) ;
 		}
    
 		if(eventDetails->GetStatusType() >= 0  )
 		{
 			EventDetails->InsertL(KDeliveryStatusKey , TLiwVariant(eventDetails->GetStatusType())) ;
 		} 

  		TBuf16 <10> Contents(KLogType) ;
  
  		inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(Contents))) ;
  
  		inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(EventDetails))) ;
  		EventDetails->DecRef();
    
  		linterface->ExecuteCmdL(KCmdAdd , *inputlist , *outputlist ); 
 
  
  
  /** 
   * Extract the error param, and check the status of the call
   */
  		 TInt index = 0 ;
   
  		 const TLiwGenericParam *ErrCode  = outputlist->FindFirst(index , KErrCode) ;
   
  		 if(!ErrCode )
   		 {
    		 _LIT(KLog , "Generic error param missing form the outputlist of add" ) ;
  			 iLog->Log(KLog) ;
  			 User :: Leave(KErrArgument) ;
   		 }
    
  		  TInt retval  = ErrCode->Value().AsTInt32() ;
  
  		 if(retval != SErrNone )
  		{
  	
  	   		 linterface->Close() ;
  	   	 	delete ServiceHandler;
  	   		a.ResetAndDestroy();
   	  		 a.Close();    
    
  			 _LIT(KLog , "Functionality test of add call failed ") ;
  			 iLog->Log(KLog) ;
  	 		User :: Leave(KErrArgument) ;
  	 		result = retval;
  		}
   
 		 index = 0 ;
 		 const TLiwGenericParam *genparm = outputlist->FindFirst(index , KLogId) ;
  
  		if(!genparm)
   		 {
    		 _LIT8(KLog , "Log id of the added item not found") ;
   			 iLog->Log(KLog) ;
   			 User :: Leave(KErrArgument) ;
    	}
    
    	inputlist->Reset();
		outputlist->Reset();
		
		 
		
		// Do a getList on the event Logged
		
		CLiwDefaultMap *EventFilter = CLiwDefaultMap :: NewL() ;
    
  		//if(aDetails->GetEventId()!=0)  
    	EventFilter->InsertL(KEventIdKey , TLiwVariant(filterDetails->GetEventId()) );
 
    	EventFilter->InsertL(KEventTypeKey , TLiwVariant(filterDetails->GetEventType()) );
  
  		if(filterDetails->GetContactType()!=0)
  		{
  			EventFilter->InsertL(KContactidKey , TLiwVariant(filterDetails->GetContactType()) );
  		}  
       
  		if((long)filterDetails->GetTimer()!=0)
  		{
  			EventFilter->InsertL(KEndTimeKey , TLiwVariant((long)filterDetails->GetTimer())) ;
  		}
    
    	TBuf<6> EmptyDes1 ;
    
  		if(filterDetails->GetNumberType() != EmptyDes1)
  		{
  			EventFilter->InsertL(KPhoneNumberKey , TLiwVariant(filterDetails->GetNumberType())) ;
  		}
    
  		if(filterDetails->GetRemotePartyType() != EmptyDes1)
  		{
  			EventFilter->InsertL(KRemotePartyKey , TLiwVariant(filterDetails->GetRemotePartyType())) ;
  		}    
    
  		if(filterDetails->GetDirectionType() >= 0)
  		{
  			EventFilter->InsertL(KDirectionKey , TLiwVariant(filterDetails->GetDirectionType())) ;
  		}
    
  		if(filterDetails->GetStatusType() >= 0)
  		{
  			EventFilter->InsertL(KDeliveryStatusKey , TLiwVariant(filterDetails->GetStatusType())) ;
  		}
    
    
 		 EventFilter->InsertL(KRecentListKey , TLiwVariant(filterDetails->GetRecentList())) ;
 		 EventFilter->InsertL(KAllEvents , TLiwVariant(filterDetails->GetAllEvent())) ;
  
  
		TBufC16<10> contentType(KLogType) ;

	//Insert the contenttype to inputlist
		inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;  
  		inputlist->AppendL(TLiwGenericParam(KFilter , TLiwVariant(EventFilter))) ;
 		 EventFilter->DecRef() ; 
  
  		linterface->ExecuteCmdL(KCmdGetList , *inputlist , *outputlist );  
  
  
     	index = 0 ;
   
   		const TLiwGenericParam *ErrCode_getlist  = outputlist->FindFirst(index , KErrCode) ;
   
   		TInt retval_getlist  = ErrCode_getlist->Value().AsTInt32() ;
  
 		 if(retval_getlist != SErrNone )
  		{
  	 		_LIT(KLog , "Functionality test of getlist failed ") ;
  			 iLog->Log(KLog) ;
  			 User :: Leave(KErrArgument) ;
  			 result = retval_getlist;
  		}
  		else
  		{
  			pos = 0 ;
  		
			const TLiwGenericParam* output_getlist = outputlist->FindFirst( pos,KLogIter);
			CLiwIterable *LogIter = (output_getlist->Value()).AsIterable() ;
      		TLiwVariant mapvar ;
      
      		TLiwVariant eventVars ;
     
          
      
     		 while(LogIter->NextL(mapvar)) 
        	{
         		 const CLiwMap *eventDet = mapvar.AsMap() ;
         		if(eventDet->FindL(KEventTypeKey , eventVars)) 
            	{
              		TUid eventtype =  eventVars.AsTUid() ;
              		TInt32 val = eventtype.iUid ;
              
              		char Buff[20] ;
              
              
              		sprintf(Buff , "Event id %d" , (int)val) ;
              		TBuf8<20> buf((TUint8 *) Buff) ;
              		iLog->Log(buf) ;
              
              
            	}
          (const_cast<CLiwMap *>(eventDet))->DecRef() ;
  			}
  			eventVars.Reset();
       		 mapvar.Reset();
        	LogIter->Reset();
  		}
  		
  		
  		inputlist->Reset();
		outputlist->Reset();
        delete eventDetails;          
   		delete filterDetails;
  }
  	
 	linterface->Close();
	ServiceHandler->Reset();
   	delete ServiceHandler ;
   	ac.ResetAndDestroy() ;
	ac.Close() ;
	a.ResetAndDestroy() ;
	a.Close() ;
	
	
	
	inParamList->Reset();
	outParamList->Reset();

    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	iServiceHandler->Reset();
	delete iServiceHandler;
    
    __UHEAP_MARKEND;
    return result;   
   
    

    }
 
 // -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops11
// create cal entry, log an event and delete event
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops11( CStifItemParser& aItem )
    {

	TInt result=KErrNone;  
	TInt err_logging = -1;
	TInt flag=0;
	__UHEAP_MARK;

	TRealFormat format ;
   
    // LOAD LOGGING SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KLoggingIDataSource , KLoggingService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray ac;
	ac.AppendL(crit);	
	ServiceHandler->AttachL(ac) ;

	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
	// EXTRACT LOGGING INTERFACE	

	TInt pos = 0;
    MLiwInterface* linterface = NULL;
    outputlist->FindFirst(pos,KLoggingIDataSource);
    if(pos != KErrNotFound)
        {
        linterface = (*outputlist)[pos].Value().AsInterface();	
        }

	inputlist->Reset();
	outputlist->Reset();
	delete crit;
	crit = NULL;
	ac.Reset();
    
    // EXTRACT CALENDAR INTERFACE	
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TPtrC desc_data;
	
	//Log an event
			
	CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;	
   
   EventDetails->InsertL(KEventTypeKey ,TLiwVariant(KLogShortMessageEventType)) ;
   
   
   TBufC16<10> contentType(KLogType) ;
   
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
   
   inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(EventDetails))) ;
   
   TBufC8<20>CmdBuf(KCmdAdd) ;
   
   linterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist) ;
   EventDetails->DecRef();
   //Now get the id to deleted
   
   pos = 0 ;
   
   const TLiwGenericParam *outparm1 = outputlist->FindFirst(pos , KLogId) ; 
   
   if(!outparm1)
   	{
   	 _LIT8(KLog , "Log id of the delete item not found") ;
   	 iLog->Log(KLog) ;
   	 User :: Leave(KErrArgument) ;
   	}
  	
  //Get the item ID
  
 TInt itemid = (outparm1->Value()).AsTInt32() ;
  
  if(itemid  < 0 )
   {
   _LIT(KLog , "Invalid item id ") ;
   iLog->Log(KLog) ;
   User :: Leave(KErrArgument) ;	
   }
   
  inputlist->Reset() ; 
  outputlist->Reset() ;
   
   
	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Description"),TLiwVariant(_L("Delete events")));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAPD(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
 		}
 		
 	
	
	// Retreive cal desc info
	
	inParamList->Reset();
	outParamList->Reset();
 	
 	TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam2);
			
	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map2);

	map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map2->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
			
			
	TLiwVariant filterparam2(map2);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam2);
	filterparam2.Reset();
			
	inParamList->AppendL(element2);
	element2.Reset();
						
	map2->DecRef();
	CleanupStack::Pop(map2);
	TReal32 CalAltData;	    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			const CLiwMap* res = data.AsMap();
			TLiwVariant desc;
			if(res->FindL(_L8("Description"), desc))
			{
			
				TPtrC desc_data = desc.AsDes() ;		
				TBuf<40> buf ;
				buf.Copy(desc_data) ;
				iLog->Log(buf) ;
				
				if(desc_data.Compare(_L("Delete events")) != 0 && result != KErrNone)
					result = KErrGeneral;
				else
					flag = 1;
						
			}
			else
				result = KErrGeneral;
			
			desc.Reset();
		}
		data.Reset();	
	} 
	
	inParamList->Reset();
	outParamList->Reset();  
	 	
	
	// Delete event
	
	if(result == KErrNone && flag == 1)
	{
		//Insert the contenttype to inputlist
  		 inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
   
  		inputlist->AppendL(TLiwGenericParam(KLogId , TLiwVariant((TInt32)itemid))) ;
  
 		 CmdBuf = KCmdDelete ;
  		linterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist) ;
  
  		pos = 0 ;
  		const TLiwGenericParam *Errprm = outputlist->FindFirst(pos , KErrCode ) ;
  
  		if(!Errprm)
  		{
  	 		_LIT(KLog , "Generic error param missing form the outputlist of delete" ) ;
  	 		iLog->Log(KLog) ;
  	 		User :: Leave(KErrArgument) ;
  		}
  	
  		TInt retval  = Errprm->Value().AsTInt32() ;
  
  		if(retval != SErrNone )
  		{
  	 		_LIT(KLog , "Functionality test of delete call failed ") ;
  	 		iLog->Log(KLog) ;
  			 User :: Leave(KErrArgument) ;
  			  result = retval;
  		}
  
	}
	
	inputlist->Reset() ; 
 	outputlist->Reset() ;
  	
 	linterface->Close();
	ServiceHandler->Reset();
   	delete ServiceHandler ;
   	ac.ResetAndDestroy() ;
	ac.Close() ;
	a.ResetAndDestroy() ;
	a.Close() ;
	
	
	
	inParamList->Reset();
	outParamList->Reset();

    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	iServiceHandler->Reset();
	delete iServiceHandler;
    
    __UHEAP_MARKEND;
    return result;   
   
    

    }
 
/*//  -----------------------------------------------------------------------------
 //Ctcalprovider_combined::Cal_ops12
 //Example test method function to combine cal and sensors.
 //(other items were commented in a header).
 //-----------------------------------------------------------------------------

TInt Ctcalprovider_combined::Cal_ops12( CStifItemParser& aItem )
    {

	TInt32 data_val=0;
	TInt result = KErrNone;
	__UHEAP_MARK;
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
	CLiwCriteriaItem* scrit = CLiwCriteriaItem::NewL(1, KSensorIDataSource , KSensorService);
	scrit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray as;
	as.AppendL(scrit);
	ServiceHandler->AttachL(as) ;
	ServiceHandler->ExecuteServiceCmdL(*scrit, *inputlist, *outputlist);
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
	delete scrit;
	scrit = NULL;
	as.Reset();

	TPtrC commandSet( _L("UnknownCmd") );
   	aItem.GetNextString(commandSet);
   	TBuf8<KMaxFileName> commandSet8;
   	CnvUtfConverter::ConvertFromUnicodeToUtf8(commandSet8, commandSet );

	TPtrC inChannel( _L("Invalid") );
    aItem.GetNextString(inChannel);
    TBuf8<KMaxFileName> inChannel8;
    CnvUtfConverter::ConvertFromUnicodeToUtf8(inChannel8, inChannel );

	TPtrC propertyId( _L("InvalidId") );
   	aItem.GetNextString(propertyId);
   	TBuf8<KMaxFileName> propertyId8;
   	CnvUtfConverter::ConvertFromUnicodeToUtf8(propertyId8, propertyId );


	TBuf8<20> CmdBufSet(_L8("FindSensorChannel"));
	inputlist->AppendL(TLiwGenericParam(KSearchCriterion,TLiwVariant(inChannel8)));
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
			iLog->Log(_L8("Service not supported"));
			sensrinterface->Close();
    		delete ServiceHandler ;   
    		return KErrNone;
			}
		else
			{
			iLog->Log(_L8("FindSensorChannel Failed for %s criterion"),
						inChannel8.PtrZ());
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
		TLiwVariant variant,chnlVariant;
		variant = GenericParam->Value();
		const CLiwList *chnlInfoList = variant.AsList();
		TInt count = chnlInfoList->Count();
		
		for(TInt i = 0; i < count; i++)
			{
			chnlInfoList->AtL(i,chnlVariant);
	    	const CLiwMap *chnlInfo = chnlVariant.AsMap();
			outputlist->Reset();
			inputlist->Reset();
   
			inputlist->AppendL(TLiwGenericParam(KChnlInfoMap,TLiwVariant(chnlInfo)));   
			if(propertyId8.CompareF( _L8("AllProps") ) )
				{
				inputlist->AppendL(TLiwGenericParam(KPropId,
								   TLiwVariant(propertyId8)));
				
				}
			sensrinterface->ExecuteCmdL(commandSet8 , *inputlist , *outputlist);
			pos = 0 ;
			const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;
	
			if(!ErrorParm)
				{
				iLog->Log(KLogUnknownErr);
				retError = KErrGeneral ;
				}
			else if((ErrorParm->Value()).AsTInt32() )
				{
				TInt32 error = ErrorParm->Value().AsTInt32();
				sensrinterface->Close();
    			delete ServiceHandler;
    			if( error == SErrServiceNotSupported )
    				{
				    iLog->Log(_L8("GetChannelProperty not supported for %s channel for %s property"),
    						  inChannel8.PtrZ(),propertyId8.PtrZ());
    				return KErrNone;
    				}
    			else
    				{
    				iLog->Log(_L8("GetChannelProperty Failed for %s channel for %s property"),
    				    	  inChannel8.PtrZ(),propertyId8.PtrZ());
    				return error;
    				}
				}
			
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
				TLiwVariant variant,variant1;
				variant = GenericParam->Value();
				const CLiwList* propertyList = variant.AsList();
				TInt propcount = propertyList->Count();
				propertyList->AtL(0,variant1);
	    		const CLiwMap *res = variant1.AsMap();
				TLiwVariant desc;
				if(res->FindL(_L8("MaxValue"), desc))
				{
			
					data_val = desc.AsTInt32() ;						
						
				}
				else
					result = KErrGeneral;
				desc.Reset();
				iLog->Log(KPropertyTestLog,
						  inChannel8.PtrZ(),propertyId8.PtrZ(),propcount);
				(const_cast<CLiwMap *>(res))->DecRef() ;
				(const_cast<CLiwMap *>(chnlInfo))->DecRef() ;
				delete propertyList;
				variant.Reset();
				variant1.Reset();
				chnlVariant.Reset();
				
				}
			}

		}
	inputlist->Reset() ; 
  	outputlist->Reset() ;
  
		
	// Create a cal entry using the Max value of the channel as priority.
	
		// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
   
    // EXTRACT CALENDAR INTERFACE	
	
	pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	

   
   
	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Priority"),TLiwVariant(data_val));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAPD(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
	   	if(result == KErrNone)
	   		result = err;
 		}	
 		
	
	inParamList->Reset();
	outParamList->Reset();
	
	
	sensrinterface->Close();
	ServiceHandler->Reset();
    delete ServiceHandler ;   
    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	iServiceHandler->Reset();
	delete iServiceHandler;
    
    __UHEAP_MARKEND;
    return result;   
	


    }
    
// -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops13
// Example test method function to combine cal and sensors.start receiving sensor channel notification after reading a cal entry
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops13( CStifItemParser& aItem )
    {

	TInt result=KErrNone;  
	TInt flag=0;
	
	TRealFormat format ;
   
    
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
	   
    // EXTRACT CALENDAR INTERFACE	
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TPtrC desc_data;
	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Description"),TLiwVariant(_L("Start Receiving Notification")));		
			
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAPD(err,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err = err1->Value().AsTInt32();
 		}
 		
 	
	
	// Retreive cal desc info
	
	inParamList->Reset();
	outParamList->Reset();
 	
 	TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam2);
			
	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map2);

	map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map2->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
			
			
	TLiwVariant filterparam2(map2);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam2);
	filterparam2.Reset();
			
	inParamList->AppendL(element2);
	element2.Reset();
						
	map2->DecRef();
	CleanupStack::Pop(map2);
	TReal32 CalAltData;	    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			const CLiwMap* res = data.AsMap();
			TLiwVariant desc;
			if(res->FindL(_L8("Description"), desc))
			{
			
				TPtrC desc_data = desc.AsDes() ;		
				TBuf<40> buf ;
				buf.Copy(desc_data) ;
				iLog->Log(buf) ;
				
				if(desc_data.Compare(_L("Start Receiving Notification")) != 0)
					result = KErrGeneral;
				else
					flag = 1;
						
			}
			else
				result = KErrGeneral;
			
			desc.Reset();
		}
		data.Reset();	
	} 
	
	inParamList->Reset();
	outParamList->Reset();  
	 	
	
	// Start receiving notification
	
	if(result == KErrNone && flag==1)
	{
		CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
   		 CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    	CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
		CLiwCriteriaItem* scrit = CLiwCriteriaItem::NewL(1, KDataSource , KService);
		scrit->SetServiceClass(TUid::Uid(KLiwClassBase));
		RCriteriaArray as;
		as.AppendL(scrit);
		ServiceHandler->AttachL(as) ;
		ServiceHandler->ExecuteServiceCmdL(*scrit, *inputlist, *outputlist);
		pos = 0;
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
		delete scrit;
		scrit = NULL;
		as.Reset();
	

		TPtrC commandSet( _L("UnknownCmd") );
   		aItem.GetNextString(commandSet);
   		TBuf8<KMaxFileName> commandSet8;
   		CnvUtfConverter::ConvertFromUnicodeToUtf8(commandSet8, commandSet );

		TPtrC inChannel( _L("Invalid") );
    	aItem.GetNextString(inChannel);
    	TBuf8<KMaxFileName> inChannel8;
    	CnvUtfConverter::ConvertFromUnicodeToUtf8(inChannel8, inChannel );

		TPtrC listenStr( _L("InvalidId") );
   		aItem.GetNextString(listenStr);
   		TBuf8<KMaxFileName> listenStr8;
   		CnvUtfConverter::ConvertFromUnicodeToUtf8(listenStr8, listenStr );


		TBuf8<20> CmdBufSet(_L8("FindSensorChannel"));
		inputlist->AppendL(TLiwGenericParam(KSearchCriterion,TLiwVariant(inChannel8)));
		sensrinterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist);
		pos = 0 ;
		const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;
	
		if(!ErrorParm)
		{
		iLog->Log(KLogUnknownErr);
		result = KErrGeneral ;
		}
		else if((ErrorParm->Value()).AsTInt32() )
		{
		TInt32 error = ErrorParm->Value().AsTInt32() ;
		if ( error == SErrServiceNotSupported ) //Invalid channel
			{
			iLog->Log(_L8("Service not supported"));
			sensrinterface->Close();
    		delete ServiceHandler ;   
    		return KErrNone;
			}
		else
			{
			iLog->Log(_L8("FindSensorChannel Failed for %s criterion"),
						inChannel8.PtrZ());
			result = error;
			}
		}

		TInt index = 0 ;
		const TLiwGenericParam *GenericParam  = outputlist->FindFirst(index , KReturnValue);
		if(!GenericParam)
		{
    	iLog->Log(KOutParamError);
		result = KErrGeneral;
		}
		else //actual test starts here
		{
		TLiwVariant variant,chnlVariant;
		variant = GenericParam->Value();
		const CLiwList *chnlInfoList = variant.AsList();
		TInt count = chnlInfoList->Count();
		
		chnlInfoList->AtL(0,chnlVariant);
    	const CLiwMap *chnlInfo = chnlVariant.AsMap();
    	TLiwVariant idVariant,typeVariant;
		chnlInfo->FindL(KChnlId,idVariant);
		TUint chnlid = idVariant.AsTUint();

		chnlInfo->FindL(KChnlDataTypeId,typeVariant);
		TUint chnltypeid = typeVariant.AsTUint();
    	
		outputlist->Reset();
		inputlist->Reset();
 
		inputlist->AppendL(TLiwGenericParam(KChnlInfoMap,TLiwVariant(chnlInfo)));
		inputlist->AppendL(TLiwGenericParam(KListeningType,TLiwVariant(listenStr8)));
		
		TInt listen = 5;
		if(listenStr8 == KChnlData)
			listen = 0;
		else if(listenStr8 == KChannelChange)
			listen = 1;
		else if(listenStr8 == KPropertyChange)
			listen = 2;
		else if(listenStr8 == KChnlCondnChange)
			listen = 3;
		
		SensorAsyncCallback callback(sensrinterface,chnlid,listen);
		sensrinterface->ExecuteCmdL(commandSet8,*inputlist,*outputlist,0,&callback);
		pos = 0 ;
		const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;
	
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
		    iLog->Log(_L8("StartGettingNotification failed for %s channel for %s listentype"),
    						  inChannel8.PtrZ(),listenStr8.PtrZ());
    		return error;
    		}

		if( listenStr8 == KChnlData )
			{
			CActiveScheduler::Start();
			
			}
		else
			{
			TRequestStatus status = KRequestPending;
    		RThread setThread;
    		setThread.Create(_L("Execute a Property Change"), DoPropertyChange,KDefaultStackSize, KMinHeapSize, KDefaultStackSize,(TAny*)chnltypeid);
    		setThread.Logon(status);
    		setThread.Resume();		      
    		User::WaitForRequest(status);				
			setThread.Close();
			
			TInt setStatus = status.Int();
			if( setStatus != -5 )
				{
				CActiveScheduler::Start();
				}
			else
				{
				iLog->Log(_L("SetChannelProperty failed for %s channel"),
					      inChannel8.PtrZ());
			
				TBuf8<50>CmdBuf(KStopNotification);
				outputlist->Reset();
				inputlist->Reset();
				inputlist->AppendL(TLiwGenericParam(KStopNotificationType,TLiwVariant(KPropertyChange)));
				inputlist->AppendL(TLiwGenericParam(KChnlId,TLiwVariant(chnlid)));
				sensrinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist);
			
				}

			}

		}
		inputlist->Reset();
		outputlist->Reset();  
		sensrinterface->Close();
		ServiceHandler->Reset();
    	delete ServiceHandler ; 
	}
	  
    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	iServiceHandler->Reset();
	delete iServiceHandler;
    
    return result;   


    }*/
    
    
/* -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops12
// Example test method function to combine cal and app manager
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops12( CStifItemParser& aItem )
    {

	TInt result=KErrNone; 
	TInt err= 0; 
	__UHEAP_MARK;
	
	TRealFormat format ;
   
    
	TPtrC16 content;
 	TPtrC16 docname;
 	TPtrC16 mimetype16;
 	TInt expected;
 	TInt noOfmaps;
 	TPtrC16 filename;
 	 	
 	aItem.GetNextString(content);
 	aItem.GetNextString(docname);
 	aItem.GetNextString(mimetype16);
 	aItem.GetNextInt(expected);
 	aItem.GetNextString(filename);
 	aItem.GetNextInt(noOfmaps);
 	
    iLog->Log(_L("read varibale "));  
            
  	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(ServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    ServiceHandler->AttachL(a);
    
	ServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 	
	
	   
    // EXTRACT CALENDAR INTERFACE	
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TPtrC desc_data;	
  	
  	// ADD CAL ENTRY
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
			
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map->InsertL(_L8("Type"),TLiwVariant(_L("Reminder")));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));		
			
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList* input = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* output = &(iServiceHandler->OutParamListL());

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KAppIDataSource,KAppService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
           
    RCriteriaArray critArray;
    critArray.AppendL(crit);
    iServiceHandler->AttachL(critArray);  
	    
    iServiceHandler->ExecuteServiceCmdL(*crit, *input, *output);

    
    
    // Create the Instance of SAPI class and the Input Param and output Param
    pos = 0;
    MLiwInterface* Interface = NULL;
    output->FindFirst(pos,KAppIDataSource );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    input->Reset();
    output->Reset();
    delete crit;
	crit = NULL;
	critArray.Reset();
  
  	//Inserting content
	if( 0 != content.CompareF(KNull) )
	    {
	    TLiwVariant dsName;
	    dsName.Set(content);
        TLiwGenericParam dsNameParam(KContentType, content);
	    input->AppendL(dsNameParam);
	    } 
   
  
  	CLiwDefaultMap *filterMap = NULL;
	
	if(docname.CompareF(_L("NULL")) != 0 )
		{
		filterMap = CLiwDefaultMap::NewL();
    	//CleanupStack::PushL( filterMap );//7
       	filterMap->InsertL(KDocumentPath,TLiwVariant(docname));
		TLiwGenericParam iFilterParam(KFilter, TLiwVariant(filterMap));
	    input->AppendL(iFilterParam);
	    
	    filterMap->DecRef();
	 	}	
	
	if(mimetype16.CompareF(_L("NULL")) != 0)
		{
		if( !filterMap )
			{
			filterMap = CLiwDefaultMap::NewL();
        	//CleanupStack::PushL( filterMap );//7
        	TLiwGenericParam iFilterParam(KFilter, TLiwVariant(filterMap));
	        input->AppendL(iFilterParam);
	        filterMap->DecRef();
			}
		
		filterMap->InsertL(KMimeType,TLiwVariant(mimetype16));	
		}
  
    if( Interface != NULL)
        {
         iLog->Log(_L("got Interface"));
        Interface->ExecuteCmdL(KGetList,*input,*output);
         iLog->Log(_L("SAPI called"));
        }
  	else
  	    {
  	        iLog->Log(_L("Didn't get interface"));
  	        return KErrGeneral;
  	    }
    
    
    const TLiwGenericParam* p= NULL;
    CLiwIterable* iter;
	TLiwVariant Map;
	const CLiwMap* infomap;    
    pos = 0;
    
    p = output->FindFirst(pos, KErrorCode); // Finding Error Code
    if(p)
        {
       
    	err = p->Value().AsTInt32();
    	iLog->Log(_L("Got Error Code "));
        }
     p = output->FindFirst(pos, KResponse);// Finding out the response of Media Management
	if(!p)
	    { 
		    if( err == KErrNone )
		    err =  KErrGeneral;
	    }
	else
	    {
		iter = p->Value().AsIterable();// returning Iterator as Response
	    } 
  
  
    _LIT8(UidKey,"UID");// Key In The Map
    TPtrC KeyValue;// value of that key	
 	TLiwVariant val;//just for extracting the value
 	         
 	while( iter->NextL(Map) )
    {
      	infomap = Map.AsMap();
    	infomap->FindL(UidKey, val);
    	val.Get(KeyValue);
    //	 	ConvertHexStringToInt32(KeyValue,appuid );
    	map->InsertL(_L8("Description"),TLiwVariant(KeyValue));   			       	 	      	 	    		
      		    	
       Map.Reset();
    }
    val.Reset();
    infomap=NULL;
    iter->Reset();   	 	
    
	TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
			
	inParamList->AppendL(element);
	element.Reset();
						
	map->DecRef();
	CleanupStack::Pop(map);
		    
	TRAPD(err_add,interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList,0,NULL));
	if(err_add == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err_add = err1->Value().AsTInt32();
	   	if(err_add != KErrNone && result == KErrNone)
	   		result = err_add;
 		}
 	
 	Interface->Close();
 	iServiceHandler->Reset();
	delete iServiceHandler;
		
    RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	
	ServiceHandler->Reset();
	delete ServiceHandler;
    
   __UHEAP_MARKEND;
    return result;   


    }

// -----------------------------------------------------------------------------
// Ctcalprovider_combined::Cal_ops13
// Example test method function to launch an App if there are no calendar entries
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcalprovider_combined::Cal_ops13( CStifItemParser& aItem )
    {

	TInt result=KErrNone;  
	TInt flag=0;
	TInt count=0;
	__UHEAP_MARK;
	TRealFormat format ;
   
    
	// LOAD CALENDAR SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(ServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(critm);    
    ServiceHandler->AttachL(a);
    
	ServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	
	   
    // EXTRACT CALENDAR INTERFACE	
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	a.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	
 	TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam2);
			
	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map2);

	map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
	map2->InsertL(_L8("Type"),TLiwVariant(_L("IncludeAll")));
			
			
	TLiwVariant filterparam2(map2);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam2);
	filterparam2.Reset();
			
	inParamList->AppendL(element2);
	element2.Reset();
						
	map2->DecRef();
	CleanupStack::Pop(map2);
	TReal32 CalAltData;	    
		    		
	TRAPD(err_list,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    
	pos = 0 ;
  		
	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	if(output)     
	{
		
		CLiwIterable* iterlist1 = output->Value().AsIterable();

	    TLiwVariant data;
			    
	   	while( iterlist1->NextL(data))
	   	{
			count++;
		}
		data.Reset();	
	} 
	
	inParamList->Reset();
	outParamList->Reset();  
	 	
	
	// Launch App
	
	if(result == KErrNone && count==0)
	{
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList* input = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* output = &(iServiceHandler->OutParamListL());

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KAppIDataSource,KAppService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
           
    RCriteriaArray critArray;
    critArray.AppendL(crit);
    iServiceHandler->AttachL(critArray);  
	    
    iServiceHandler->ExecuteServiceCmdL(*crit, *input, *output);

    
    
    // Create the Instance of SAPI class and the Input Param and output Param
    pos = 0;
    MLiwInterface* Interface = NULL;
    output->FindFirst(pos,KAppIDataSource );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    input->Reset();
    output->Reset();
    delete crit;
	crit = NULL;
	critArray.Reset();
	
	
    TOptions options;
    TInt expected;
    TPtrC16 temp;
    TBuf<30> appId;
 	TPtrC16 cmdLine16;
 	TPtrC16 document;
  	TPtrC16 mode;
  	TPtrC16 postion;
  	TPtrC16 callback;
  	TInt err;
 	  	
 	aItem.GetNextString( temp );
 	appId.Append( temp );
 	appId.Append(_L("//"));
 	aItem.GetNextString( temp );
 	appId.Append( temp );
 	
 	
 	aItem.GetNextString(cmdLine16);
 	aItem.GetNextString(document);
 	aItem.GetNextString(mode);
 	aItem.GetNextString(postion);
 	aItem.GetNextString(callback);
 	aItem.GetNextInt(expected);
 	
 	
 	//Inserting ApplicationID
	if( 0 != appId.CompareF(KNull) )
	    {
	    TLiwVariant id;
	    id.Set(appId);
        TLiwGenericParam idParam(KApplicationID, id);
	    input->AppendL(idParam);
	    }	
 	
 	
 	//Inserting cmdLine
	if( 0 != cmdLine16.CompareF(KNull) )
	    {
	    TLiwVariant cmdline;
	    cmdline.Set(cmdLine16);
        TLiwGenericParam cmdlineParam(KCmdLine, cmdline);
	    input->AppendL(cmdlineParam);
	    }	
 	
 	
 	CLiwDefaultMap *filterMap = NULL;
	
	if( document.CompareF(_L("NULL")) != 0 )
		{
		filterMap = CLiwDefaultMap::NewL();
    	//CleanupStack::PushL( filterMap );//7
       	filterMap->InsertL(KDocumentPath,TLiwVariant(document));
		TLiwGenericParam iFilterParam(KOptions, TLiwVariant(filterMap));
	    input->AppendL(iFilterParam);
	    filterMap->DecRef();
	 	}
	
	
	if( mode.CompareF(_L("NULL") ) != 0)
		{
		if( !filterMap )
			{
			filterMap = CLiwDefaultMap::NewL();
        	CleanupStack::PushL( filterMap );//7
        	TLiwGenericParam iFilterParam(KOptions, TLiwVariant(filterMap));
	        input->AppendL(iFilterParam);
	        filterMap->DecRef();
			}
		
		filterMap->InsertL(KMode,TLiwVariant(mode));	
		}
 	
 	if( postion.CompareF(_L("NULL") ) != 0)
		{
		if( !filterMap )
			{
			filterMap = CLiwDefaultMap::NewL();
        	//CleanupStack::PushL( filterMap );//7
        	TLiwGenericParam iFilterParam(KOptions, TLiwVariant(filterMap));
	        input->AppendL(iFilterParam);
	        filterMap->DecRef();
			}
		
		filterMap->InsertL(KPostion,TLiwVariant( postion ));	
		}  
    
            
        _LIT8(KLaunchApp,"LaunchApp");
        Interface->ExecuteCmdL(KLaunchApp,*input,*output);
                
  	        
        
            const TLiwGenericParam* p= NULL;
            pos = 0;
            p = output->FindFirst(pos, KErrorCode); // Finding Error Code
            if(p)
                {
                err = p->Value().AsTInt32();
                }
            else
                {
                 err = KErrGeneral; 
                }
    input->Reset();
    output->Reset(); 
    Interface->Close();
 	iServiceHandler->Reset();
	delete iServiceHandler;    
	  
	} 
    
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	ServiceHandler->Reset();
	delete ServiceHandler;
    
    __UHEAP_MARKEND;
    return result;   


    }*/
//Helper Function     
     
TInt Ctcalprovider_combined::ConvertHexStringToInt32(const TDesC& aHexString,TInt32& aInt32 )
    {
    aInt32 = 0;

    TInt pos = aHexString.LocateF( 'x' );
    if ( pos == KErrNotFound )
        {
        pos = 0;
        }
    else
        {
        pos++;
        }

    if( ( aHexString.Length() - pos ) > KDocMaxDigitsInHexString )
        {
        return KErrArgument; // Error: value too big.
        }
    TPtrC aHexStringPtr( aHexString.Mid( pos ) );

    TInt64 value64;
    if ( TLex( aHexStringPtr ).Val( value64, EHex ) != KErrNone )
        {
        return KErrArgument; // Error: conversion failed.
        }
    aInt32 = value64;

    return KErrNone;
    }
    
// -----------------------------------------------------------------------------
// CTLmAsyncTest::RemoveAllCategories
// Helper method to remove all categories for preconditional tests.
// -----------------------------------------------------------------------------
//
void Ctcalprovider_combined::RemoveAllCategories  (CPosLmCategoryManager* aHandle)
  {
  TPosLmItemId catID;
  CPosLmItemIterator*iterator = aHandle->CategoryIteratorL();
  CleanupStack::PushL(iterator);

  while ((catID = iterator->NextL()) != KPosLmNullItemId)
    {
      TRAPD(err,ExecuteAndDeleteLD(aHandle->RemoveCategoryL( catID )));
       TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      iLog->Log( error );
    }
  CleanupStack::PopAndDestroy(iterator);
}

           
/* -----------------------------------------------------------------------------
 Ctcalprovider_combined::Cal_ops3
 Example test method function.
 (other items were commented in a header).
 -----------------------------------------------------------------------------

TInt Ctcalprovider_combined::Cal_ops3( CStifItemParser& aItem )
    {

    struct ParamPass* arg1 = new ParamPass();
    arg1->it = &aItem;
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;

    //creating the thread , this thread is reponsible for sending the request to SAPI
    TInt ret = FunctionThread.Create( _L("FunctionThread1"), ThreadFunction ,KDefaultStackSize ,
    						NULL ,( TAny * ) arg1);

    User::LeaveIfError(ret);
    FunctionThread.Logon(Status);
    FunctionThread.Resume() ;

    // Waiting for thread to die in other words we are making asynch call to synch call :-))
    User :: WaitForRequest (Status)	;

    FunctionThread.Close();

    delete arg1;
	return Status.Int() ;


    }*/
    

TInt Callback:: HandleNotifyL(TInt /*aCmdId*/,TInt aEventId,CLiwGenericParamList& aOutParamList,const CLiwGenericParamList& /*aInParamList*/)
{

	if ( KLiwEventStarted == aEventId )
	{
	    arg->log->Log(_L(" Started Event Capture "));
		// Asynchronous request started
	}
	else if ( KLiwEventCanceled == aEventId )
	{
		// Asynchronous event canceled
		arg->log->Log(_L("Cancel Event Capture "));
		User::Exit( KErrNone );
	}
	else if( KLiwEventError == aEventId)
	{
	    // Error occurs in Asynchronous operation
	    arg->log->Log(_L(" Error Event Capture "));
	    User::Exit( KErrGeneral );
	}
	else
	{


	TInt32 ErrCode;
	CLiwIterable* iIterable;
	TLiwVariant Map;
	const CLiwMap* MetaData;
	TInt pos = 0;

	// Traiverse the List and Fill in the Log Files
	const TLiwGenericParam* p = aOutParamList.FindFirst(pos, KErrorCodem); // Finding Error Code
	if( p )
	{
		ErrCode = p->Value().AsTInt32();

	}
	else
	{
		arg->log->Log(_L(" Not able to Find the Error Code "));
		CActiveScheduler :: Stop() ;
		User::Exit( KErrGeneral );
	}

	if(ErrCode < 0 ) // If any error comes in MG SAPI
	{
		arg->log->Log(_L(" Error Occured in SAPI = %d"),ErrCode);
		CActiveScheduler :: Stop() ;
		User::Exit( KErrGeneral );
	}

	p = aOutParamList.FindFirst(pos, KResponse);// Finding out the response of Media Management
	if(!p)
	{
		arg->log->Log(_L(" Not able to Find the Response "));
		CActiveScheduler :: Stop() ;
		User::Exit( KErrGeneral );
	}
	else
	{
		iIterable = p->Value().AsIterable();// returning Iterator as Response
		TBuf8<30> Key;// Key In The Map		
		_LIT(Kkey,"FileNameAndPath");
		TPtrC KeyValue;// value of that key
		TPtrC KeyValue1;
		TPtrC KeyValue2;
		TLiwVariant val;//just for extracting the value
		TLiwVariant val1;
		TInt flagz = 0; 
		TInt ip = 0;
		CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
		CLiwDefaultList* attachmentlist = CLiwDefaultList::NewL();
		CLiwDefaultMap* attachmentmap1 = CLiwDefaultMap::NewL();
		CLiwDefaultMap* attachmentmap2 = CLiwDefaultMap::NewL();
		CLiwDefaultMap* attachmentmap3 = CLiwDefaultMap::NewL();
		CLiwDefaultMap* attachmentmap4 = CLiwDefaultMap::NewL();	

		//-----------Loop for Iterator -------------------------------//
		TBuf<200> Output;
		int count =0;
		while(iIterable->NextL(Map))// Find the next value from Iterator
		{
			count++;
			Output.Copy(_L("\n\nFile\n"));
			arg->log->Log(Output);

			MetaData = Map.AsMap();// Iterator return the map which contains meta data
			Output.Copy(_L("key"));
			Output.Append(_L("							"));
			Output.Append(_L("KeyValue"));
			arg->log->Log(Output);
			flagz = 0;			

			for(TInt i = 0 ; i <MetaData->Count(); i++ )
			{

				MetaData->AtL(i,Key);
				MetaData->FindL(Key, val);
				Key.Trim();				  				 				
				Output.Copy(Key);
				Output.Append(_L("            "));
				if(EVariantTypeTInt32==val.TypeId())
				{
					TInt value = val.AsTInt32();
					TBuf<30> string;
					string.AppendNum(value);
					string.Trim();
					Output.Append(string);
				}
				else if(EVariantTypeTTime==val.TypeId())
				{
					TTime time = val.AsTTime();
					_LIT(KTimeFormat,"%F%M/%D/%Y %H:%T");
					TBuf <20> StringTime;
					time.FormatL(StringTime, KTimeFormat);
					StringTime.Trim();
					Output.Append(StringTime);
                    // date format : 5/25/2005 12:40"
				}
				else
				{
					val.Get(KeyValue);	
					if((KeyValue.FindF(file_attach) != -1) && (flagz == 0))
					{
					 if(flagg == 0)
					 {
					  att.Copy(KeyValue);
					  arg->log->Log(_L("Attachment:")) ;
					  arg->log->Log(att);
					  flagz = 1;
					  flagg = 1;	
					 }
					 else
					 {
					    HBufC* filename1 = HBufC::NewL(80)	;
					    CleanupStack::PushL(filename1);
					    filename1->Des().Copy(KeyValue);
					    TLiwVariant file1(filename1);
					    
					    
					    if(ip == 0)
					    {
					       attachmentmap1->InsertL(_L8("FileName"),file1);
					       TLiwVariant attachment1(attachmentmap1);
					       attachmentlist->AppendL(attachment1);
						   attachment1.Reset();
					    }
					    else if(ip == 1)
					    {
					       attachmentmap2->InsertL(_L8("FileName"),file1);
					       TLiwVariant attachment1(attachmentmap2);
					       attachmentlist->AppendL(attachment1);
						   attachment1.Reset();
					    }   
					    else if(ip == 2)
					    {
					       attachmentmap3->InsertL(_L8("FileName"),file1);
					       TLiwVariant attachment1(attachmentmap3);
					       attachmentlist->AppendL(attachment1);
						   attachment1.Reset();
					    }
					    else if(ip == 3)
					    {
					       attachmentmap4->InsertL(_L8("FileName"),file1);
					       TLiwVariant attachment1(attachmentmap4);
					       attachmentlist->AppendL(attachment1);
						   attachment1.Reset();
					    }  
					      
					    file1.Reset();
					    CleanupStack::PopAndDestroy(filename1);	
						
						flagz = 1;
						ip++;																 
					 } 
					}												
				 
				 Output.Append(KeyValue);
			    }
									
			arg->log->Log(Output); // printing Key Values in log files

			}		
		 
		Map.Reset();
		}
				
		TLiwVariant attachments(attachmentlist);
		 //attachment list added to message info ,map  
		map1->InsertL(_L8("AttachmentList"),attachments);
		attachments.Reset();   							     
		inParamList->AppendL(TLiwGenericParam( KMessageParam, TLiwVariant( map1 )));
		attachmentlist->DecRef();	
		attachmentmap1->DecRef();
		attachmentmap2->DecRef();
		attachmentmap3->DecRef();
		attachmentmap4->DecRef();
		map1->DecRef();
		
	}
	//------Loop for Iterator-----------------------------------------//
	CActiveScheduler :: Stop() ;	

	}
	return 0;
}

// -----------------------------------------------------------------------------
// Thread Function For Sending the Asynch request to Media Management SAPI
// -----------------------------------------------------------------------------
//

TInt ThreadFunction (TAny *a)
{
	// Creating the Cleanup stack for this new thread
	 CTrapCleanup* cleanup = CTrapCleanup::New();
	 struct ParamPass* arg1 = (ParamPass*) a;
	 TInt errorCode;
	 TInt error = KErrNone;
	 TInt expectedResult;

	 TRAP(error, errorCode = GetFilesAsynchL(a));
	 delete cleanup;
/*	 if( arg1->it->GetNextInt(expectedResult) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the Sorting Order ")) ;
        return KErrGeneral;
        }*/
	 if(error == KErrNone)
	 {
	 	if(errorCode>0)
	 	{
	 	  arg1->log->Log(_L(" Error in input "));
	 	  TBuf<30> string;
		  string.AppendNum(errorCode);
		  arg1->log->Log(string);
		  delete arg1->log;
		  if( expectedResult != 0)//negative test case
    	  {
    	    return KErrNone;
          }
		  return KErrGeneral;

	 	}
	 	else
	 	{
	 	   return  KErrNone;
	 	}

	 }

	 return KErrGeneral;
}




TInt GetFilesAsynchL( TAny *a)
{
    TPtrC attach;
    TPtrC attach1;
    TPtrC cfgCommand16;
    TPtrC cfgDataSourceName;
	TPtrC FileType16;
	TPtrC FilterField16;
	TPtrC StartVal;
	TPtrC EndVal;
	TPtrC SortField16;
	TPtrC order;
	TInt expectedResult = 0;
	TInt operation = 0;
	TInt test_case;

	struct ParamPass *arg1 = (ParamPass *)a;

	arg1->log = CStifLogger::NewL( KMediaMgmtLogPath,KResultFile,CStifLogger::ETxt,CStifLogger::EFile,ETrue,EFalse);



    // Get All the Values From CFG file
    
    if( arg1->it->GetNextString ( attach1 ) != KErrNone )
        {
        arg1->log->Log(_L(" Failed to Get the File filter ") );
        return KErrGeneral;
        }
    file_attach.Copy(attach1);
        
    if( arg1->it->GetNextString ( cfgCommand16 ) != KErrNone )
        {
        arg1->log->Log(_L(" Failed to Get the File Type ") );
        return KErrGeneral;
        }

    if( arg1->it->GetNextString ( cfgDataSourceName ) != KErrNone )
        {
        arg1->log->Log(_L(" Failed to Get the File Type ") );
        return KErrGeneral;
        }

    if( arg1->it->GetNextString ( FileType16 ) != KErrNone )
        {
        arg1->log->Log(_L(" Failed to Get the File Type ") );
        return KErrGeneral;
        }
	if( arg1->it->GetNextString ( FilterField16 ) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the Filter Field of File ")) ;
        return KErrGeneral;
        }
    if( arg1->it->GetNextString ( StartVal ) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the start value of Filter ")) ;
        return KErrGeneral;
        }
	if( arg1->it->GetNextString ( EndVal ) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the End Value of Filter ")) ;
        return KErrGeneral;
        }
    if( arg1->it->GetNextString ( SortField16 ) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the Sort Filed  ")) ;
        return KErrGeneral;
        }

	if( arg1->it->GetNextString(order) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the Sorting Order ")) ;
        return KErrGeneral;
        }

    if( arg1->it->GetNextInt(operation) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the Sorting Order ")) ;
        return KErrGeneral;
        }
        
     if( arg1->it->GetNextInt(test_case) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the Test Case Number ")) ;
        return KErrGeneral;
        }

        // the below section for giving header to log files

     	TBuf<200> TestCase;

     	TestCase.Copy(_L("FileType "));
     	TestCase.Append(_L("   "));

       	TestCase.Append(_L("FilterField"));
     	TestCase.Append(_L("   "));


     	TestCase.Append(_L("StartVal"));
     	TestCase.Append(_L("   "));


     	TestCase.Append(_L("EndVal"));
     	TestCase.Append(_L("   "));


     	TestCase.Append(_L("SortField"));
     	TestCase.Append(_L("   "));


       	TestCase.Append(_L("order"));
     	TestCase.Append(_L("   "));



     	arg1->log->Log(TestCase);

     	TestCase.Copy(FileType16);
     	TestCase.Append(_L("   "));

       	TestCase.Append(FilterField16);
     	TestCase.Append(_L("   "));


     	TestCase.Append(StartVal);
     	TestCase.Append(_L("   "));


     	TestCase.Append(EndVal);
     	TestCase.Append(_L("   "));


     	TestCase.Append(SortField16);
     	TestCase.Append(_L("   "));


       	TestCase.Append(order);
     	TestCase.Append(_L("   "));

     	arg1->log->Log(TestCase);


         // Convert 16 Bit values into 8 bit as SAPI accept 8 bit key
        TBuf8<30> Command1 ;
        Command1.Copy(cfgCommand16);

        TBuf8<30> FileType ;
        //FileType.Copy(FileType16);

        TBuf8<30> FilterField ;
        //FilterField.Copy(FilterField16);

        TBuf8<30> SortField ;
        //SortField.Copy(SortField16);

        TBuf8<30> Order ;
        //Order.Copy(order);

    	// Start Scheduler
	CActiveScheduler *Scheduler = new (ELeave) CActiveScheduler ;
	CActiveScheduler :: Install(Scheduler) ;
	CleanupStack::PushL(Scheduler);

    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KMediaIDataSource,KMediaService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);


    RCriteriaArray critArray;
    critArray.AppendL(crit);
    CleanupClosePushL(critArray);

    iServiceHandler->AttachL(critArray);

    //Create the object of callback
	MLiwNotifyCallback*  aCallBack = new (ELeave) Callback(arg1);
	CleanupStack::PushL(aCallBack);



    CLiwGenericParamList* output = CLiwGenericParamList::NewL();
	CleanupStack::PushL(output);
	CLiwGenericParamList* input = CLiwGenericParamList::NewL();
	CleanupStack::PushL(input);

    iServiceHandler->ExecuteServiceCmdL(*crit, *input, *output);


    // Create the Instance of SAPI class and the Input Param and output Param
    TInt pos = 0;
    MLiwInterface* Interface = NULL;
    output->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();

    input->Reset();

    //MLiwInterface* Interface = CMgDataSourceInterface::NewL();
    CleanupClosePushL(*Interface);

	if( 0 != cfgDataSourceName.CompareF(KNull) )
	{
	TLiwVariant dsName;
	dsName.Set(cfgDataSourceName);
    TLiwGenericParam dsNameParam(KDsName, dsName);
	input->AppendL(dsNameParam);
	}
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam iFilterParam(KFilter, TLiwVariant(filterMap));
	input->AppendL(iFilterParam);
	filterMap->DecRef();

    CLiwDefaultMap *sortingMap = CLiwDefaultMap::NewL();
    TLiwGenericParam iSortingParam(KSort, TLiwVariant(sortingMap));
	input->AppendL(iSortingParam);
	sortingMap->DecRef();


	// LOAD APP SERVICE-HANDLER
    
    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();  
    inParamList = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(ServiceHandler->OutParamListL());
    
          
    CLiwCriteriaItem* critm = CLiwCriteriaItem::NewL(1, KIDataSource,KCalService);   
    critm->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray ap;
    ap.AppendL(critm);    
    ServiceHandler->AttachL(ap);
    
	ServiceHandler->ExecuteServiceCmdL(*critm, *inParamList, *outParamList); 
	
	

	// EXTRACT INTERFACE	
	
	pos = 0;
    MLiwInterface* minterface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
         minterface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete critm;
	critm = NULL;
	ap.Reset();
	
	RemoveProvCalendar(inParamList, outParamList, minterface, KTestCal1File);
	
	TRAPD(err_addcal,AddProvCalendar(inParamList, outParamList, minterface, KTestCal1File));
	
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inParamList->AppendL(dsNameParam);
	
	inParamList->AppendL(TLiwGenericParam( _L8("CalendarName"), TLiwVariant( KTestCal1File )));
	inParamList->AppendL(TLiwGenericParam( _L8("Type"), TLiwVariant( _L("DayEvent") )));
    inParamList->AppendL(TLiwGenericParam( _L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0)))));
	
	

	//Inserting data source name

//------Send all this thing in Filter Map -------------------------------//



	if( 0 != FileType16.CompareF( KNull ) )
	{
	    TLiwVariant ifileType;
	    //ifileType.Set(FileType);
	    ifileType.Set(FileType16);
	    filterMap->InsertL(KFileType,ifileType);
	}

	if( 0 != FilterField16.CompareF( KNull ) )
	{
	    TLiwVariant iFilterField;
	    //iFilterField.Set(FilterField);
	    iFilterField.Set(FilterField16);
	    filterMap->InsertL(KKey,iFilterField);
	}

	if( 0 != StartVal.CompareF( KNull ) )
	{
	   	TLiwVariant iStartVal;
	    iStartVal.Set(StartVal);
	    filterMap->InsertL(KStartRange,iStartVal);
	}

	if( 0 != EndVal.CompareF( KNull ) )
	{
	   	TLiwVariant iEndVal;
	    iEndVal.Set(EndVal);
	    filterMap->InsertL(KEndRange,iEndVal);
	}







//------------------Send all the below in sorting map----------------------------------------------------------//

	if( 0 != SortField16.CompareF( KNull ) )
	{
	    TLiwVariant iSortField;
	    //iSortField.Set(SortField);
	    iSortField.Set(SortField16);
	    sortingMap->InsertL(KKey,iSortField);
	}

	if( 0 != order.CompareF( KNull ) )
	{
	    TLiwVariant iOrder;
	    //iOrder.Set(Order);
	    iOrder.Set(order);
	    sortingMap->InsertL(KOrder,iOrder);
	}



const TLiwGenericParam* p= NULL;

//---------------------------------------------------------------------------------//

	if( operation == 0)
	{
	        // normal asynch operation
	        if( Interface != NULL)
	    	Interface->ExecuteCmdL(Command1,*input,*output,KLiwOptASyncronous,aCallBack);

	}
	else if(operation == 1)
	{
	        //cancel
	        Interface->ExecuteCmdL(Command1,*input,*output,KLiwOptASyncronous,aCallBack);
	        pos = 0;
            p = output->FindFirst(pos, KTransactionID); // Finding Error Code
            input->Reset();
            TUint transactionID = 0;
	        if( p )
	        {
		    p->Value().Get(transactionID);
		    input->AppendL( TLiwGenericParam( KTransactionID, TLiwVariant( transactionID ) ) );
            }
	    	Interface->ExecuteCmdL(Command1,*input,*output,KLiwOptCancel,aCallBack);

    }
	else if( operation == 3)
	{
	        // check back to back request
	    	Interface->ExecuteCmdL(Command1,*input,*output,KLiwOptASyncronous,aCallBack);
            Interface->ExecuteCmdL(Command1,*input,*output,KLiwOptASyncronous,aCallBack);
            Interface->ExecuteCmdL(Command1,*input,*output,KLiwOptCancel,aCallBack);
	}
		else if(operation == 4)
	{
	        Interface->Close();
	        CleanupStack::Pop();
	        CleanupStack::PopAndDestroy(7);
            return KErrNone;
	}
	else
	{
	        // synchronous
	    	Interface->ExecuteCmdL(Command1,*input,*output,0,aCallBack);
	}

    _LIT8(KErrorCodem,"ErrorCode");
    pos = 0;
    TInt retcode;
    p = output->FindFirst(pos, KErrorCodem); // Finding Error Code


    if(p)
    {
    	retcode = p->Value().AsTInt32();

    	if(retcode != KErrNone)
    	{

    	CleanupStack::PopAndDestroy(); //.sorting Map,filterMap,Interface,input, output, Scheduler,aCallBack
    	CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy();
    	return retcode;
    	}
    }

    CActiveScheduler :: Start() ;  
    
      
    
	
    // Add calendar entry with attachment value at Description
      
	inParamList->AppendL(TLiwGenericParam( _L8("Description"), TLiwVariant( att )));		
	
	TRAPD(err_add,minterface->ExecuteCmdL( KCmdAdd ,*inParamList,*outParamList));
	
 	if(err_add == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErCode);
	   	err_add = err1->Value().AsTInt32();
 		}
	
	
	if(err_add != KErrNone && retcode == KErrNone)
		retcode = err_add;
	
	inParamList->Reset();
	outParamList->Reset();
	minterface->Close();
	ServiceHandler->Reset();
	delete ServiceHandler;

    
    CleanupStack::PopAndDestroy(8); //Interface ,input, output, coreobj, Scheduler,aCallBack
    return retcode ;
}


	
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------




// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File

// -----------------------------------------------------------------------------
// Ctcalprovider_combined::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctcalprovider_combined::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File

TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar)
	{
	inparam->Reset();
	outparam->Reset();
	__UHEAP_MARK;
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    CLiwDefaultList* callist = CLiwDefaultList::NewL();
    CleanupStack::PushL(callist);
    
    TLiwVariant content(_L("Calendar"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();
    
    TLiwVariant smsmtm(aCalendar); 
    callist->AppendL(smsmtm);
    smsmtm.Reset();
    
    TLiwVariant add1(callist);
   // map->InsertL(_L8("CalendarList"), add1); 
   map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
    callist->DecRef();
    CleanupStack::Pop(callist);
    add1.Reset();	
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Data"),filterparam);
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TRAPD(err, interface->ExecuteCmdL( KCmdDelete ,*inparam,*outparam ));
    TInt pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	if(output)
		{
		err = output->Value().AsTInt32();
		}
	
	inparam->Reset();
	outparam->Reset();
	__UHEAP_MARKEND;

	return err;
	}
	
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar)
	{
	inparam->Reset();
	outparam->Reset();

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("Calendar"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();
    
    
    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
    
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map));
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	if(output)
		{
		err = output->Value().AsTInt32();
		}
	
	inparam->Reset();
	outparam->Reset();

	return err;
	};
	

TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();
	TInt cells = User::CountAllocCells();


   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( _L("Meeting") ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,30,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Meeting")));
	map->InsertL(_L8("Status"), TLiwVariant(_L("Confirmed")));
	map->InsertL(_L8("Method"), TLiwVariant(_L("None")));
	
   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(repeatmap);
	repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(1)));
	repeatmap->InsertL(_L8("StartDate"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2007,ENovember,0,10,0,0,0))));
	map->InsertL(_L8("RepeatRule"), TLiwVariant(repeatmap));
	CleanupStack::Pop(repeatmap);
	repeatmap->DecRef();
	
    
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map));
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);
    
    cells = User::CountAllocCells();


	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    cells = User::CountAllocCells();
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	cells = User::CountAllocCells();
	
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				uidset = new (ELeave) TUIDSet;
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				GetLocalUid( uidval, uidset->iLocalUID );
				
				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
				GetGlobalUid( uidval, tmp );
				
				}
			else
				err = -1;
			}
		}
	cells = User::CountAllocCells();	
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();


	return err;
	};

void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid )
	{
	aOutLocalUid = 0;
	if( aLocalUid.Length() )
		{
		TInt sepPos = aLocalUid.Locate( KUidSeparator );
		TPtrC temp;
		if( sepPos == KErrNotFound )
			{
			temp.Set(aLocalUid.Mid(0));
			}
		else
			{
			temp.Set(aLocalUid.Mid(0, sepPos));
			}

		TLex lex(temp);
		TInt32 num;

		if(lex.Val(num) == KErrNone)
			aOutLocalUid = TCalLocalUid(num);
		}
	}

void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid )
	{
	if( aGlobalUid.Length() )
		{
		TInt sepPos = aGlobalUid.Locate( KUidSeparator );

		if( sepPos == KErrNotFound )
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid(0) );
			}
		else
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid( sepPos + 1 ) );
			}	
		}
	}


TInt AddAppointmentProvLocal(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{

	inparam->Reset();
	outparam->Reset();
	TInt cells = User::CountAllocCells();


   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( _L("Meeting")  ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,30,0,0))));
	map->InsertL(_L8("SeqNum"), TLiwVariant(1));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Location"), TLiwVariant(_L("Hara Room")));
	map->InsertL(_L8("Summary"), TLiwVariant(_L("Meeting happen at 10")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Meeting")));
	map->InsertL(_L8("Status"), TLiwVariant(_L("Confirmed")));
	map->InsertL(_L8("Method"), TLiwVariant(_L("None")));
	
   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(repeatmap);
	repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(1)));
	repeatmap->InsertL(_L8("StartDate"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2007,EOctober,30,10,0,0,0))));
	map->InsertL(_L8("RepeatRule"), TLiwVariant(repeatmap));
	CleanupStack::Pop(repeatmap);
	repeatmap->DecRef();
	
    
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map));
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);
    
    cells = User::CountAllocCells();

	//TInt err;
	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    cells = User::CountAllocCells();
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	cells = User::CountAllocCells();
	
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				uidset = new (ELeave) TUIDSet;
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				GetLocalUid( uidval, uidset->iLocalUID );
				
				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
				GetGlobalUid( uidval, tmp );
			
				}
			else
				err = -1;
			}
		}
	cells = User::CountAllocCells();	
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();


	return err;
    }

TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();

	TInt cells = User::CountAllocCells();


   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( _L("ToDo")  ));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Private")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("To do")));
	map->InsertL(_L8("Status"), TLiwVariant(_L("TodoNeedsAction")));
	
	
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map));
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);
    
    cells = User::CountAllocCells();

	//TInt err;
	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    cells = User::CountAllocCells();
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	cells = User::CountAllocCells();
	
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				uidset = new (ELeave) TUIDSet;
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				GetLocalUid( uidval, uidset->iLocalUID );
				
				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
				GetGlobalUid( uidval, tmp );
			
				}
			else
				err = -1;
			}
		}
	cells = User::CountAllocCells();	
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();


	return err;
	}
			

TInt AddProvEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();

	TInt cells = User::CountAllocCells();


   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( _L("DayEvent")  ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,24,0,0,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Event")));
	map->InsertL(_L8("Method"), TLiwVariant(_L("None")));
	
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map));
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);
    
    cells = User::CountAllocCells();

	//TInt err;
	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    cells = User::CountAllocCells();
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	cells = User::CountAllocCells();
	
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				uidset = new (ELeave) TUIDSet;
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				GetLocalUid( uidval, uidset->iLocalUID );
				
				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
				GetGlobalUid( uidval, tmp );
			
				}
			else
				err = -1;
			}
		}
	cells = User::CountAllocCells();	
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();


	return err;
	}; 
				
				
