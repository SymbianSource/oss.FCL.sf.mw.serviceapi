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
#include <StifTestInterface.h>
#include  <utf.h>
#include "mediamgmt.h"
#include "mgitemslist.h"
using namespace LIW;


_LIT8(KResponse,"Response");
_LIT8(KErrorCode,"ErrorCode");

_LIT8( KMgNull8, "NULL" );
_LIT16( KMgNull, "NULL");
_LIT(KTimeFormat,"%F%M/%D/%Y/%H:%T");


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

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CMediaMgmt::Delete
// Delete here all resources allocated and opened from test methods.
// Called from destructor.
// -----------------------------------------------------------------------------
//
void CMediaMgmt::Delete()
    {

    }

// -----------------------------------------------------------------------------
// CMediaMgmt::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CMediaMgmt::RunMethodL(
    CStifItemParser& aItem )
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.
        ENTRY( "GetFiles", CMediaMgmt::GetFilesL ),
        ENTRY( "GetFilesInfo", CMediaMgmt::GetFilesInfoL ),

        };

    const TInt count = sizeof( KFunctions ) /
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CMediaMgmt::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CMediaMgmt::GetFilesL( CStifItemParser& aItem )
    {
    _LIT( KExample, "In GetFilesL" );
    iLog->Log( KExample );
	struct ParamPass* arg1 = new ParamPass();
    arg1->it = &aItem;  // Just stoing into global variables so that it can be used by thread
    arg1->log = iLog;  //  function
    arg1->CmdId = EMgGetFiles ;  // Command For Get Files

	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;

    //creating the thread , this thread is reponsible for sending the request to SAPI
    TInt ret = FunctionThread.Create( _L("FunctionThread"), ThreadFunction ,KDefaultStackSize ,
    						NULL ,( TAny * ) arg1);

    User::LeaveIfError(ret);
    FunctionThread.Logon(Status);
    FunctionThread.Resume() ;

    // Waiting for thread to die in other words we make asynch call to synch call :-))
    User :: WaitForRequest (Status)	;


    FunctionThread.Close();

    delete arg1;
	return Status.Int() ;
   }


// -----------------------------------------------------------------------------
// CMediaMgmt::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CMediaMgmt::GetFilesInfoL( CStifItemParser& aItem )
    {
    _LIT( KExample, "In GetFilesInfoL" );
    iLog->Log( KExample );

    struct ParamPass* arg1 = new ParamPass();
    arg1->it = &aItem;  // Just stoing into global variables so that it can be used by thread
    arg1->log = iLog;  //  function
    arg1->CmdId = EMgGetFilesInfo ;  // Command For Get Files Info

	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;

    //creating the thread , this thread is reponsible for sending the request to SAPI
    TInt ret = FunctionThread.Create( _L("FunctionThread"), ThreadFunction ,KDefaultStackSize ,
    						NULL ,( TAny * ) arg1);

    User::LeaveIfError(ret);
    FunctionThread.Logon(Status);
    FunctionThread.Resume() ;

    // Waiting for thread to die in other words we make asynch call to synch call :-))
    User :: WaitForRequest (Status)	;

    FunctionThread.Close();

    delete arg1;
	return Status.Int() ;

    }



// -----------------------------------------------------------------------------
// Callback:: MgNotify
// Call Back Function Called by the Media Management SAPIin Iteration 1
// -----------------------------------------------------------------------------
//


 void Callback::MgNotifyL(TUint /*aTransactionID*/,
                               MCLFItemListModel*  aListModel,
                               CClfOperationObserver* aOperationObserver,
        					   TMgOperationEvent& aOperationEvent,
                               const TInt& aError )


	{

    CLiwGenericParamList* output = CLiwGenericParamList::NewL();
    CLiwGenericParamList* input = CLiwGenericParamList::NewL();
    CleanupStack::PushL(output);
    CleanupStack::PushL(input);
	// Fill the Error code Inside Generic Param List
	TLiwVariant errCode;
    errCode.Set( aError );
	TLiwGenericParam errTypeParam( KErrorCode, errCode );
	output->AppendL( errTypeParam );

	// if not error create the iterator class and put it into output list
	if(  KErrNone == aError   )
     	{
        // Fill the Iterator in Generic Paaram List
        TLiwVariant response;

	 	// Iterator will accept the cmd Id and iListmodel and
	 	// it will become the owner of iListModel,Ownership of
	 	// Iterator is transfered to consumer

	 	CMgItemsList *iterator = CMgItemsList::NewL( aListModel, arg->CmdId  );


	 	response.Set( iterator );
	 	TLiwGenericParam responseTypeParam( KResponse, response );
 		output->AppendL( responseTypeParam );

        }


    	// call callback of consumer
    	if( KErrNone ==  aError   )
    	    {
    	    HandleNotifyL ( 0, KLiwEventCompleted, *output,*input );
    	    }
        else
            {
            HandleNotifyL ( 0, KLiwEventError, *output,*input );
            }

  	CleanupStack::PopAndDestroy();
  	CleanupStack::PopAndDestroy();



	}






// -----------------------------------------------------------------------------
// Callback:: HandleNotifyL
// Call Back Function Called by the Media Management SAPI.in Iteration 2
// -----------------------------------------------------------------------------
//



TInt Callback:: HandleNotifyL(TInt aCmdId,TInt aEventId,CLiwGenericParamList& aOutParamList,const CLiwGenericParamList& aInParamList)
{

   arg->log->Log(_L("Enter in Handle notify"));
	if ( KLiwEventStarted == aEventId )
	{
		// Asynchronous request started
	}
	else if ( KLiwEventCanceled == aEventId )
	{
		// Asynchronous event canceled
		arg->returnCode = KErrCancel;
		CActiveScheduler :: Stop() ;
		return 0;
	}
	else
	{

	TInt32 ErrCode;
	CLiwIterable* iIterable;
	TLiwVariant Map;
	const CLiwMap* MetaData;
	TInt pos = 0;
	//TBuf<200> aValue1[20][20]; // Hemae : very large value for stack
	TInt no_of_maps;

	// Traiverse the List and Fill in the Log Files
	const TLiwGenericParam* p = aOutParamList.FindFirst(pos, KErrorCode); // Finding Error Code
	if(p)
	{
		ErrCode = p->Value().AsTInt32();
		//arg->log->Log(_L("Got error Code"));
	}
	else
	{
		arg->log->Log(_L(" Not able to Find the Error Code "));
		arg->returnCode = KErrGeneral;
		CActiveScheduler :: Stop() ;
		return 0;
		//User::Exit( KErrGeneral );
	}

	if(ErrCode < 0 ) // If any error comes in MG SAPI
	{
		arg->log->Log(_L(" Error Occured in SAPI = %d"),ErrCode);
		arg->returnCode = KErrGeneral;
		CActiveScheduler :: Stop() ;
		return 0;
		//User::Exit( KErrGeneral );
	}

	p = aOutParamList.FindFirst(pos, KResponse);// Finding out the response of Media Management
	if(!p)
	{
		arg->log->Log(_L(" Not able to Find the Response "));
		arg->returnCode = KErrGeneral;
		CActiveScheduler :: Stop() ;
		return 0;
		//User::Exit( KErrGeneral );
	}
	else
	{
	    //arg->log->Log(_L(" Got the Response "));
		iIterable = p->Value().AsIterable();// returning Iterator as Response
		TBuf8<30> Key;// Key In The Map
		TPtrC KeyValue;// value of that key
		TLiwVariant val;//just for extracting the value
		//-----------Loop for Iterator -------------------------------//
		TBuf<200> Output;
		int count =0;
		TBuf<30> string;
        TBuf<20> StringTime;
        TInt i;
        TInt value;
        TTime time;
        TPtrC temp;
		while(iIterable->NextL(Map))// Find the next value from Iterator
		{

			Output.Copy(_L("File"));
			arg->log->Log(Output);
			MetaData = Map.AsMap();// Iterator return the map which contains meta data
			Output.Copy(_L("key"));
			Output.Append(_L("							"));
			Output.Append(_L("KeyValue"));
			arg->log->Log(Output);

			for(i = 0 ; i <MetaData->Count(); i++ )
			{

				MetaData->AtL(i,Key);
				MetaData->FindL(Key, val);
				Output.Copy(Key);
		    	Output.Append(_L("            "));
				if(EVariantTypeTInt32==val.TypeId())
				{
					value = val.AsTInt32();
					string.Delete(0,string.Length());
					string.AppendNum(value);
					//aValue1[count][i] = string;
					Output.Append(string);
				}
				else if(EVariantTypeTTime==val.TypeId())
				{
					time = val.AsTTime();
					//dheeraj clear
					time.FormatL(StringTime, KTimeFormat);
					//aValue1[count][i] = StringTime;
					Output.Append(StringTime);
                    // date format : 5/25/2005 12:40"
				}
				else
				{
					val.Get(KeyValue);
					temp.Set( val.AsDes() );
					//aValue1[count][i] = temp ;
					Output.Append(KeyValue);
				}

				arg->log->Log(Output); // printing Key Values in log files

			}
			count++;
		}

		/*arg->it->GetNextInt(no_of_maps);
		TPtrC expected_out[no_of_maps][20];
		switch (arg->meta)
		{
			case 1:
					TInt row,col;
					for (row=0; row <no_of_maps; row++)
        			for (col=0 ;col<8;col++)
        			arg->it->GetNextString(expected_out[row][col]);
        			for (TInt i=0; i < row ; i++)
				    for (TInt j=0; j<col ; j++)
				    if (expected_out[i][j].CompareF(aValue1[i][j])!=0)
				 	User::Exit( KErrArgument );
       				break;

			case 2: ;


		}*/


    }
	//------Loop for Iterator-----------------------------------------//
     arg->returnCode = KErrNone;
	CActiveScheduler :: Stop() ;
	return KErrNone;
 	}
   return KErrNone;
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
	 TInt errorCode = KErrNone;
	 TInt error = KErrNone;
	 TRAP(error, errorCode = GetFilesAsynchL(a));
	 delete cleanup;
	 if(error == KErrNone)
	 {
	 	if(errorCode<0)
	 	{
	 	  arg1->log->Log(_L(" Error in input "));
	 	  TBuf<30> string;
		  string.AppendNum(errorCode);
		  arg1->log->Log(string);
		  // Hema : check here if the case is neagative or postive
		  // then return proper error code
		  return KErrNone;

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
	TPtrC FileType16;
	TPtrC FilterField16;
	TPtrC StartVal;
	TPtrC EndVal;
	TPtrC SortField16;
	TInt order = 0;

	struct ParamPass *arg1 = (ParamPass *)a;

	arg1->log = CStifLogger::NewL( KMediaMgmtLogPath,
                          KResultFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          ETrue );



    // Get All the Values From CFG
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

	if( arg1->it->GetNextInt(order) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the Sorting Order ")) ;
        return KErrGeneral;
        }

     	if (!FileType16.Compare(_L("Image")) || !FileType16.Compare(_L("Sound")))

     	arg1->meta = 1;


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

        if( 0 != order)
       	TestCase.Append(_L("Descending"));
        else
        TestCase.Append(_L("Ascending"));

     	TestCase.Append(_L("   "));

     	arg1->log->Log(TestCase);


         // Convert 16 Bit values into 8 bit as SAPI accept 8 bit Des
        TBuf8<30> FileType ;
        FileType.Copy(FileType16);

        TBuf8<30> FilterField ;
        FilterField.Copy(FilterField16);

        TBuf8<30> SortField ;
        SortField.Copy(SortField16);



	//Create the object of callback
	MMgOperationObserver*  aCallBack = new (ELeave) Callback(arg1);
	CleanupStack::PushL(aCallBack);

	// Start Scheduler
	CActiveScheduler *Scheduler = new CActiveScheduler ;
	CActiveScheduler :: Install(Scheduler) ;
	CleanupStack::PushL(Scheduler);

    // Create the Instance of SAPI core class and
    //the Input Param and output Param
    CMgService* CoreObj = CMgService ::NewL() ;
	CleanupStack::PushL(CoreObj);

//------- New Code Added ---------------------------------------------------//
TMgServiceRequest reqArgument;


if( 0 != FileType.CompareF( KMgNull8 ) )
    reqArgument.iFileType.Set( FileType );


if( 0 != FilterField.CompareF( KMgNull8 ) )
    reqArgument.iFilterField.Set( FilterField );

if( 0 != StartVal.CompareF( KMgNull ) )
    reqArgument.iStartVal.Set( StartVal );

if( 0 != EndVal.CompareF( KMgNull ) )
    reqArgument.iEndVal.Set( EndVal );

if( 0 != SortField.CompareF( KMgNull8 ) )
    reqArgument.iSortField.Set( SortField );

if( 0 != order)
{
    reqArgument.iOrder.Set( _L8("Descending") );
}



//--------------------------------------------------------------------------//




	TInt retcode = 0;

	// Calling SAPI :-)))


     	 TRAP( retcode , CoreObj->GetListL(reqArgument ,aCallBack) );


    if(retcode < 0)
    {


	CleanupStack::PopAndDestroy();//Remove callback
	CleanupStack::PopAndDestroy();//Remove scheduler
	CleanupStack::PopAndDestroy();//Remove core object
    return retcode;

    }

    CActiveScheduler :: Start() ;

    CleanupStack::PopAndDestroy();//Remove callback
	CleanupStack::PopAndDestroy();//Remove scheduler
	CleanupStack::PopAndDestroy();//Remove core object

    return arg1->returnCode;
}

