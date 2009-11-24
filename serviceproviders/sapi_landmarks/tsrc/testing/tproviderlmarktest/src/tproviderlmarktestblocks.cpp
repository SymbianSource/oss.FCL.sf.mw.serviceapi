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
#include <StifParser.h>
#include <StifTestInterface.h>
#include <liwservicehandler.h>
#include <liwbufferextension.h>

#include "txmlconvertor.h"

#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>

#include "tprovidertestobserver.h"
#include "txmlconvertor.h"
#include "landmarkliwparams.hrh"
#include "tproviderlmarktest.h"

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

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctproviderlmarktest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctproviderlmarktest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctproviderlmarktest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctproviderlmarktest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "CheckInputArgumentType", Ctproviderlmarktest::CheckInputArgumentType ),
         ENTRY( "RemoveFile", Ctproviderlmarktest::RemoveFile ),
        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt Ctproviderlmarktest::RemoveFile( CStifItemParser& aItem )
    {
				TPtrC16 file;
    aItem.GetNextString(file);
  	RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,file , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(file);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();
	return KErrNone;
    
    }

TInt Ctproviderlmarktest::CheckInputArgumentType( CStifItemParser& aItem  )
    {
    
    __UHEAP_MARK;
 	TPtrC16 serice16;
 	TPtrC16 title;
 	TPtrC16 Interface16;
 	TPtrC16 command16;
 	TInt servicecmdpptions;
 	TPtrC16 callback;	
 	
 	TInt expected;
 	TInt32 err = 0;
    CProviderObserver* callbackobj = NULL;
 		
 	TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
 	
 	aItem.GetNextString(serice16);
 	aItem.GetNextString(Interface16);
 	aItem.GetNextString(command16);
 	aItem.GetNextInt(servicecmdpptions);
 	aItem.GetNextString(callback); 
 	
    iLog->Log(_L("read varibale "));  
            
  /*-------------------------------------------------------------------------------------------*/
  
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1
    
    if ( iServiceHandler ) 
        iLog->Log(_L("Got Service Handler "));  
    else
        iLog->Log(_L("Didn't get service handler"));  
    
    
    //Take the Interface name and provider from cfg file
    TBuf8<30> interface8;
    TBuf8<30> service8;
    interface8.Copy(Interface16);
    service8.Copy(serice16);
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,interface8,service8);
    iLog->Log(_L("Create criterai Item"));
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);//2

        
    RCriteriaArray critArray;
    iLog->Log(_L("Append in Crit"));
    critArray.AppendL(crit);
    CleanupClosePushL(critArray);//3

    iServiceHandler->AttachL(critArray);
    
    
    iLog->Log(_L("Creating Output"));
    CLiwGenericParamList* output = CLiwGenericParamList::NewL();
	CleanupStack::PushL(output);//4
	CLiwGenericParamList* input = CLiwGenericParamList::NewL();
	CleanupStack::PushL(input);//5

    iLog->Log(_L("call Service cmd L"));
    iServiceHandler->ExecuteServiceCmdL(*crit, *input, *output);

    iLog->Log(_L("Service cmdl is over"));
    
    // Create the Instance of SAPI class and the Input Param and output Param
    TInt pos = 0;
    MLiwInterface* Interface = NULL;
    output->FindFirst(pos,interface8 );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();

    CleanupClosePushL(*Interface);//6
    iLog->Log(_L("got Interface"));
    input->Reset();
  

  if (FillInputParmaeterList( aItem, input) == KErrNone )
    {
    //Call Service 
 //   PrintInputParameterList(input);
    TBuf8<30> command8;
    if(command16.Compare(_L("Update")))
   	 command8.Copy(command16);  
    else
     command8.Copy(_L("Add"));
    
     if(callback.CompareF(_L("NULL"))==0)
        {
        //without call back 
           	Interface->ExecuteCmdL(command8,*input,*output,servicecmdpptions, NULL);        
        }
     else
        
        {
         //need to change the observer  
         callbackobj = CProviderObserver::NewL(); 
         //CleanupStack::PushL( callbackobj); 
         Interface->ExecuteCmdL(command8,*input,*output,servicecmdpptions, callbackobj); 
         //CleanupStack::PopAndDestroy( );
        }
        
    aItem.GetNextInt(expected);
    aItem.GetNextString(title);
    TInt index =0;
    const TLiwGenericParam* error = output->FindFirst(index,KErrorCode);
    if(error)
    	err = error->Value().AsTInt32();
    if(err == 0 )
    {
     	 	if(!command16.Compare(_L("GetList")))
     	 	{
     	 		
     	     // Requested Accepted by the provider
     	     if( (callback != NULL) && (KLiwOptASyncronous == servicecmdpptions) )
     	        {
     	         // need to wait for callback 
     	        CActiveSchedulerWait* wait = new CActiveSchedulerWait();
                CleanupStack::PushL( wait);
                callbackobj->SetWait( wait );
                wait->Start();
     	        CleanupStack::PopAndDestroy();//Active Wait Scheduler	
     	        }
     	 	/*	// Iterate through the items and fetch the count
     	 		TInt count =0;
     	 		TInt search_pos=0;
				const TLiwGenericParam* output_data = output->FindFirst( search_pos,_L8("ReturnValue"));
					
				if(output_data)     
				{
					CLiwIterable* iterlist = output_data->Value().AsIterable();	
		    		TLiwVariant data;
		    		while( iterlist->NextL(data))
		    		{
		    			count++;
		    			const CLiwMap* res = data.AsMap();
						if ( res )
						{
							TLiwVariant new_data;
							TLiwVariant desc_data;
							if(res->FindL(KLandmarkName, new_data))
							{
								TPtrC name = new_data.AsDes();
								TBuf<40> name_data;
								name_data.Copy(name);
								TInt name_comparison_res = name.Compare(_L("200e-2.5"));
							
							}
							if(res->FindL(KLandmarkDesc, desc_data))
							{
								TPtrC desc = desc_data.AsDes();
								TBuf<4000> description_data;
								description_data.Copy(desc);
								iLog->Log(_L("Description Data:"));
								iLog->Log(description_data);							
							}
							new_data.Reset();
							desc_data.Reset();
							//const_cast<CLiwMap*>(res)->DecRef();
						}
		    		}
			 		data.Reset();
     	 		}*/
     	 	}
     }   	
     	
    iLog->Log(_L("Got Error Code "));
    iLog->Log(_L("Expected value for test case [%S] is [%d]"), &title,expected );
    iLog->Log(_L("Actual value for test case [%S] is [%d]"), &title,err );
            
    	if(expected != err)
		{
	  	 result = KErrGeneral;	
		}      
    }  
  else
    {
        //Input Parameter List is not properly entered in Cfg file
     //   PrintInputParameterList(input);
     iLog->Log(_L("Input not properly passed "));
        result = KErrGeneral;
    }
    
   output->Reset();
   input->Reset();
   delete callbackobj;
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );

	__UHEAP_MARKEND;		
	return result;

    }

TInt Ctproviderlmarktest::FillInputParmaeterList( CStifItemParser& aItem , CLiwGenericParamList* input  )     
    
{
 
    TInt intValue;
   
    TPtrC16 value16;
    TBuf8<40> value8;
    TLiwVariant value;
    TLiwGenericParam valueParam;
	TBuf8<40> next8 ;
	TPtrC next16;
 	TPtrC16 dataType;
     
    aItem.GetNextString(next16);               
    while( next16.CompareF(_L("Finish"))!= 0)
        {
        aItem.GetNextString(dataType);
        //Convert variable name into 8 bit key
        next8.Copy(next16);
  
      	if(dataType.CompareF(_L("Int") )== 0)
       		{
       	    //Value should be Integer 
       	    aItem.GetNextInt(intValue);
       	    value.SetL((TInt32)intValue);
            valueParam.SetNameAndValueL(next8, value);
	        input->AppendL(valueParam);
      		}
 		
        else if ( dataType.CompareF(_L("String") ) == 0)
        	{
             //Value should be 8 bit
             aItem.GetNextString(value16);
             value8.Copy(value16);
       		 value.SetL(value8);
             valueParam.SetNameAndValueL(next8, value);
	         input->AppendL(valueParam); 
        	}
        
        else if ( dataType.CompareF(_L("UnicodeString") ) == 0)
        	{
        	 //Value should be 16 bit string
        	 aItem.GetNextString(value16);
             value.SetL(value16);
             valueParam.SetNameAndValueL(next8, value);
	         input->AppendL(valueParam); 
        	}
        else if ( dataType.CompareF(_L("Map")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultMap *map = CLiwDefaultMap::NewL();
        	value.SetL(map);
        	valueParam.SetNameAndValueL(next8, value);
            input->AppendL(valueParam);
            map->DecRef();
            
            if( FillMap(aItem,map) !=KErrNone)
                return KErrGeneral; 
    	
        	}
        else if ( dataType.CompareF(_L("List")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultList *list = CLiwDefaultList::NewL();
        	value.SetL(list);
        	valueParam.SetNameAndValueL(next8, value);
            input->AppendL(valueParam);
            list->DecRef();
            
            if( FillList(aItem,list) !=KErrNone)
                return KErrGeneral; 
        	}
        else
        	{
            return KErrGeneral;
        	}
        valueParam.Reset();
        value.Reset();	
       aItem.GetNextString(next16);
       }//While loop 
    
      
    return KErrNone;
}

TInt Ctproviderlmarktest::FillMap( CStifItemParser& aItem , CLiwDefaultMap* aMap  )     
    
{
 
    TInt intValue;
     TReal32 incorrect_realValue = -5433465343434343434343434343.3456;
     TReal32 correct_realValue = 5401234.32e25;
    TPtrC16 value16;
    TPtrC16 null_value;
    null_value.Set(KNullDesC);
    TBuf8<40> value8;
    TLiwVariant value;
   	TBuf8<40> next8 ;
	TPtrC next16;
 	TPtrC16 dataType;
     
    aItem.GetNextString(next16);               
    while( next16.CompareF(_L("End"))!= 0)
        {
        aItem.GetNextString(dataType);
        //Convert variable name into 8 bit key
        next8.Copy(next16);
  
      	if(dataType.CompareF(_L("Int") )== 0)
       		{
       	    //Value should be Integer 
       	    aItem.GetNextInt(intValue);
       	    value.SetL((TInt32)intValue);
       	    aMap->InsertL(next8,value);
      		}
 		else if (dataType.CompareF(_L("Real") ) == 0)
 		{
 			//Value should be Real 
       	    aItem.GetNextInt(intValue);
       	    if(intValue == 1)
       	    	value.SetL((TReal32)incorrect_realValue);
       	    else
       	    	value.SetL((TReal32)correct_realValue);
            aMap->InsertL(next8,value);
 		}
 		else if ( dataType.CompareF(_L("Bool") ) == 0)
        	{
             //Value should be 8 bit
             aItem.GetNextInt(intValue);
             if(intValue)
             	value.SetL((TBool)1);
             else
             	value.SetL((TBool)0);
             aMap->InsertL(next8,value);
        	}
        else if ( dataType.CompareF(_L("String") ) == 0)
        	{
            //Value should be 8 bit
            aItem.GetNextString(value16);
            value8.Copy(value16);
       		value.SetL(value8);
            aMap->InsertL(next8,value);
        	}
        else if ( dataType.CompareF(_L("UnicodeString") ) == 0)
        	{
        	//Value should be 16 bit string
        	aItem.GetNextString(value16);
        	if(value16.Compare(_L("Null")))
        		value.SetL(value16);
        	else
        		value.SetL(null_value);
            aMap->InsertL(next8,value);
        	}
        else if ( dataType.CompareF(_L("Map")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultMap *map = CLiwDefaultMap::NewL();
        	value.SetL(map);
        	aMap->InsertL(next8,value);
            map->DecRef();
            
            if( FillMap(aItem,map) !=KErrNone)
                return KErrGeneral; 
    	
        	}
        else if ( dataType.CompareF(_L("List")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultList *list = CLiwDefaultList::NewL();
        	value.SetL(list);
        	aMap->InsertL(next8,value);
            list->DecRef();
            
            if( FillList(aItem,list) !=KErrNone)
                return KErrGeneral; 
        	}
        else
        	{
            return KErrGeneral; 
        	}
       value.Reset();
       aItem.GetNextString(next16);
       }//While loop 
    
       
    return KErrNone;

}
   
   
   
TInt Ctproviderlmarktest::FillList( CStifItemParser& aItem , CLiwDefaultList* aList  )     
    
{
 
    TInt intValue;
    TPtrC16 value16;
    TBuf8<40> value8;
    TLiwVariant value;
   	TBuf8<40> next8 ;
	TPtrC next16;
 	TPtrC16 dataType;
     
    aItem.GetNextString(dataType);               
    while( dataType.CompareF(_L("End"))!= 0)
        {
        //aItem.GetNextString(dataType);
       
      	if(dataType.CompareF(_L("Int") )== 0)
       		{
       	    //Value should be Integer 
       	    aItem.GetNextInt(intValue);
       	    value.SetL((TInt32)intValue);
       	    aList->AppendL(value);
      		}
 
        else if ( dataType.CompareF(_L("String") ) == 0)
        	{
            //Value should be 8 bit
            aItem.GetNextString(value16);
            value8.Copy(value16);
       		value.SetL(value8);
            aList->AppendL(value);
        	}
        else if ( dataType.CompareF(_L("UnicodeString") ) == 0)
        	{
        	//Value should be 16 bit string
        	aItem.GetNextString(value16);
            value.SetL(value16);
            aList->AppendL(value);
        	}
        else if ( dataType.CompareF(_L("Map")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultMap *map = CLiwDefaultMap::NewL();
        	value.SetL(map);
        	aList->AppendL(value);
            map->DecRef();
            
            if( FillMap(aItem,map) !=KErrNone)
                return KErrGeneral; 
    	
        	}
        else if ( dataType.CompareF(_L("List")) == 0)
        	{
        	//Value should be List
          	CLiwDefaultList *list = CLiwDefaultList::NewL();
        	value.SetL(list);
        	aList->AppendL(value);
            list->DecRef();
            
            if( FillList(aItem,list) !=KErrNone)
                return KErrGeneral; 
        	
        	}
        else
        	{
            return KErrGeneral;
        	}
        value.Reset();
       aItem.GetNextString(dataType);
       }//While loop 
    
       
    return KErrNone;

}
    
    
void Ctproviderlmarktest::PrintInputParameterList( CLiwGenericParamList* input  ) 
{
    
 // Show the Input List
 RFs fs;
 RFile file;  
 User::LeaveIfError(fs.Connect());
 
 CleanupClosePushL(fs);//1
 TInt errfile=0;
 TEntry entry;
        			
        			
        			
 if( fs.Entry(_L("c:\\Data\\Provider\\"),entry) != KErrNone)
    {
    TInt ret = fs.MkDir(_L("c:\\Data\\Provider\\")); 
    }
        			
 TBuf<100> flname(_L("c:\\Data\\Provider\\InputList.xml"));

 errfile =file.Replace(fs,flname, EFileWrite | EFileStreamText); 
 CleanupClosePushL(file);//2
 
 
/*------------------------------------------------------------------------------*/
 //Generate Xml file 
 TPtrC filebuf;

 
 CXmlConvertor* convertor = CXmlConvertor::NewL();
 CleanupStack::PushL(convertor);
 convertor->BuildOutputTreeL(*input,filebuf);
 
 HBufC8* heapBuffer = HBufC8::NewL(filebuf.Length());
 TPtr8  filebuf8(heapBuffer->Des());
 filebuf8.Copy(filebuf);
 
 file.Write(filebuf8);
 
 delete heapBuffer;
 CleanupStack::PopAndDestroy(); 
 
/*------------------------------------------------------------------------------*/ 
 

 CleanupStack::PopAndDestroy();//File   1
 CleanupStack::PopAndDestroy();//File Session  2       		   
}

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
