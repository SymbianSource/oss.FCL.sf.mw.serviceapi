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
#include "mediamgmt.h"
_LIT8(KGetList,"GetList");

//Just for comparison with cfg file
_LIT8(KNull8,"NULL");
_LIT(KNull,"NULL");


//Input Keys/arguments
_LIT8(KDsName,"Ds_Name");// used by interface class
_LIT8(KFileType,"FileType");
_LIT8(KMetadata,"Metadata");
_LIT8(KStartRange,"StartRange");
_LIT8(KEndRange,"EndRange");
_LIT8(KOrder,"Order");


// Filter Map
_LIT8(KFilter,"Filter");

// Sorting Map
_LIT8(KSort,"Sort");

//Output Keys/arguments
_LIT8(KErrorCode,"Error");
_LIT8(KResponse,"Response");





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
        ENTRY( "InterfaceClass", CMediaMgmt::InterfaceClassL ),

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
TInt CMediaMgmt::InterfaceClassL( CStifItemParser& aItem )
    {
    _LIT( KExample, "In InterfaceClass" );
    iLog->Log( KExample );

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
// Callback:: HandleNotifyL
// Call Back Function Called by the Media Management SAPI.
// -----------------------------------------------------------------------------
//



TInt Callback:: HandleNotifyL(TInt /*aCmdId*/,TInt aEventId,CAiwGenericParamList& aOutParamList,const CAiwGenericParamList& /*aInParamList*/)
{

	if ( KAiwEventStarted == aEventId )
	{
	    arg->log->Log(_L(" Started Event Capture "));
		// Asynchronous request started
	}
	else if ( KAiwEventCanceled == aEventId )
	{
		// Asynchronous event canceled
		arg->log->Log(_L("Cancel Event Capture "));
		User::Exit( KErrNone );
	}
	else if( KAiwEventError == aEventId)
	{
	    // Error occurs in Asynchronous operation 
	    arg->log->Log(_L(" Error Event Capture "));
	    User::Exit( KErrGeneral );
	}
	else
	{

	_LIT8(KErrorCode,"Error");
	_LIT8(KResponse,"Response");

	TInt32 ErrCode;
	CAiwIterable* iIterable;
	TAiwVariant Map;
	const CAiwMap* MetaData;
	TInt pos = 0;

	// Traiverse the List and Fill in the Log Files
	const TAiwGenericParam* p = aOutParamList.FindFirst(pos, KErrorCode); // Finding Error Code
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
		TPtrC KeyValue;// value of that key
		TAiwVariant val;//just for extracting the value

		//-----------Loop for Iterator -------------------------------//
		TBuf<200> Output;
		int count =0;
		while(iIterable->NextL(Map))// Find the next value from Iterator
		{
			count++;
			Output.Copy(_L("File"));
			arg->log->Log(Output);

			MetaData = Map.AsMap();// Iterator return the map which contains meta data
			Output.Copy(_L("key"));
			Output.Append(_L("							"));
			Output.Append(_L("KeyValue"));
			arg->log->Log(Output);

			for(TInt i = 0 ; i <MetaData->Count(); i++ )
			{

				MetaData->AtL(i,Key);
				MetaData->FindL(Key, val);
				Output.Copy(Key);
				Output.Append(_L("            "));
				if(EVariantTypeTInt32==val.TypeId())
				{
					TInt value = val.AsTInt32();
					TBuf<30> string;
					string.AppendNum(value);
					Output.Append(string);
				}
				else if(EVariantTypeTTime==val.TypeId())
				{
					TTime time = val.AsTTime();
					_LIT(KTimeFormat,"%F%M/%D/%Y %H:%T");
					TBuf <20> StringTime;
					time.FormatL(StringTime, KTimeFormat);
					Output.Append(StringTime);
                    // date format : 5/25/2005 12:40"
				}
				else
				{
					val.Get(KeyValue);
				Output.Append(KeyValue);
				}
				arg->log->Log(Output); // printing Key Values in log files

			}
		}
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
	 if( arg1->it->GetNextInt(expectedResult) != KErrNone )
        {
        arg1->log->Log(_L("Failed to Get the Sorting Order ")) ;
        return KErrGeneral;
        }
	 if(error == KErrNone)
	 {
	 	if(errorCode<0)
	 	{
	 	  arg1->log->Log(_L(" Error in input "));
	 	  TBuf<30> string;
		  string.AppendNum(errorCode);
		  arg1->log->Log(string);
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

	struct ParamPass *arg1 = (ParamPass *)a;

	arg1->log = CStifLogger::NewL( KMediaMgmtLogPath,
                          KResultFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          ETrue );



    // Get All the Values From CFG file
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
        TBuf8<30> Command ;
        Command.Copy(cfgCommand16);

        TBuf8<30> FileType ;
        FileType.Copy(FileType16);

        TBuf8<30> FilterField ;
        FilterField.Copy(FilterField16);

        TBuf8<30> SortField ;
        SortField.Copy(SortField16);

        TBuf8<30> Order ;
        Order.Copy(order);





	//Create the object of callback
	MAiwNotifyCallback*  aCallBack = new (ELeave) Callback(arg1);
	CleanupStack::PushL(aCallBack);
	// Start Scheduler
	CActiveScheduler *Scheduler = new (ELeave) CActiveScheduler ;
	CActiveScheduler :: Install(Scheduler) ;
	CleanupStack::PushL(Scheduler);

    // Create the Instance of SAPI class and the Input Param and output Param
    MAiwInterface* Interface = CMgDataSourceInterface::NewL();
    CleanupClosePushL(*Interface);
    CAiwGenericParamList* output = CAiwGenericParamList::NewL();
	CleanupStack::PushL(output);
	CAiwGenericParamList* input = CAiwGenericParamList::NewL();
	CleanupStack::PushL(input);
	CAiwDefaultMap *filterMap = CAiwDefaultMap::NewL();
	TAiwGenericParam iFilterParam(KFilter, TAiwVariant(filterMap));
	input->AppendL(iFilterParam);
    CAiwDefaultMap *sortingMap = CAiwDefaultMap::NewL();
    TAiwGenericParam iSortingParam(KSort, TAiwVariant(sortingMap));
	input->AppendL(iSortingParam);





	//Inserting data source name
	if( 0 != cfgDataSourceName.CompareF(KNull) )
	{
	TAiwVariant dsName;
	dsName.Set(cfgDataSourceName);
    TAiwGenericParam dsNameParam(KDsName, dsName);
	input->AppendL(dsNameParam);
	}

//------Send all this thing in Filter Map -------------------------------//



	if( 0 != FileType.CompareF( KNull8 ) )
	{
	    TAiwVariant ifileType;
	    ifileType.Set(FileType);
	    filterMap->InsertL(KFileType,ifileType);
	}

	if( 0 != FilterField.CompareF( KNull8 ) )
	{
	    TAiwVariant iFilterField;
	    iFilterField.Set(FilterField);
	    filterMap->InsertL(KMetadata,iFilterField);
	}

	if( 0 != StartVal.CompareF( KNull ) )
	{
	   	TAiwVariant iStartVal;
	    iStartVal.Set(StartVal);
	    filterMap->InsertL(KStartRange,iStartVal);
	}

	if( 0 != EndVal.CompareF( KNull ) )
	{
	   	TAiwVariant iEndVal;
	    iEndVal.Set(EndVal);
	    filterMap->InsertL(KEndRange,iEndVal);
	}







//------------------Send all the below in sorting map----------------------------------------------------------//

	if( 0 != SortField.CompareF( KNull8 ) )
	{
	    TAiwVariant iSortField;
	    iSortField.Set(SortField);
	    sortingMap->InsertL(KMetadata,iSortField);
	}

	if( 0 != Order.CompareF( KNull8 ) )
	{
	    TAiwVariant iOrder;
	    iOrder.Set(Order);
	    sortingMap->InsertL(KOrder,iOrder);
	}





//---------------------------------------------------------------------------------//

	if( operation == 0)
	{
	        // normal asynch operation
	    	Interface->ExecuteCmdL(Command,*input,*output,KAiwOptASyncronous,aCallBack);

	}
	else if(operation == 1)
	{
	        //cancel
	        Interface->ExecuteCmdL(Command,*input,*output,KAiwOptASyncronous,aCallBack);
	    	Interface->ExecuteCmdL(Command,*input,*output,KAiwOptCancel,aCallBack);
            Interface->ExecuteCmdL(Command,*input,*output,KAiwOptCancel,aCallBack);
    }
	else if( operation == 3)
	{
	        // check back to back request
	    	Interface->ExecuteCmdL(Command,*input,*output,KAiwOptASyncronous,aCallBack);
            Interface->ExecuteCmdL(Command,*input,*output,KAiwOptASyncronous,aCallBack);
	}
		else if(operation == 4)
	{
	        //close without request
	        MAiwInterface* I = CMgDataSourceInterface::NewL();
	        I->Close();
	        // check close of interface
	       	I = CMgDataSourceInterface::NewL();
	    	I->ExecuteCmdL(Command,*input,*output,KAiwOptASyncronous,aCallBack);
            I->Close();
            CleanupStack::PopAndDestroy(5);
            return KErrNone;
	}
	else
	{
	        // synchronous
	    	Interface->ExecuteCmdL(Command,*input,*output,0,aCallBack);
	}

    _LIT8(KErrorCode,"Error");
    TInt pos = 0;
    TInt retcode;
    const TAiwGenericParam* p = output->FindFirst(pos, KErrorCode); // Finding Error Code


    if(p)
    {
    	retcode = p->Value().AsTInt32();
    	CleanupStack::PopAndDestroy(); //.sorting Map,filterMap,Interface,input, output, Scheduler,aCallBack
    	CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy();
   	   	return retcode;
    }

    CActiveScheduler :: Start() ;
    pos = 0;
    p = output->FindFirst(pos, KErrorCode); // Finding Error Code
	if( p )
	{
		retcode =  p->Value().AsTInt32();

	}
	else
	{
		arg1->log->Log(_L(" Not able to Find the Error Code "));
		retcode = KErrGeneral;
	}

    CleanupStack::PopAndDestroy(5); //Interface ,input, output, coreobj, Scheduler,aCallBack
    return retcode;
}

