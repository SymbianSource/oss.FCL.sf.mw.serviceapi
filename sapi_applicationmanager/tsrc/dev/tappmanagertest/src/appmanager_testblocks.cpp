/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/



// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "appmanagertest.h"
#include "appmanagerservice.h"
#include "appmanagercommon.h"
#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>

#include "testappobserver.h"
const TInt KDocMaxDigitsInHexString = 8; // 32 bits.
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
// Csapi_getheader:Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CAppManagerTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Csapi_getheader:RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CAppManagerTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
         ENTRY( "getlisttest", CAppManagerTest::getlisttestL ),
         ENTRY( "launchApp", CAppManagerTest::launchAppL ),
         ENTRY( "launchDoc", CAppManagerTest::launchDocL ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CAppManagerTest:getlistapplication1_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAppManagerTest::getlisttestL( CStifItemParser& aItem  )
    {
    
    __UHEAP_MARK;
 	TPtrC16 content;
 	TPtrC16 docname;
 	TPtrC16 mimetype16;
 	TInt expected;
 	TInt noOfmaps;
 	TPtrC16 filename;
 	TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
 	
 	aItem.GetNextString(content);
 	aItem.GetNextString(docname);
 	aItem.GetNextString(mimetype16);
 	aItem.GetNextInt(expected);
 	aItem.GetNextString(filename);
 	aItem.GetNextInt(noOfmaps);
 	
 	
 	       
        
    // Convert 16 Bit values into 8 bit as SAPI accept 8 bit Des
    TBuf8<30> mimetype ;
    mimetype.Copy(mimetype16);    
        
  
	CAppManagerService* test = CAppManagerService::NewL();
	CleanupStack::PushL(test);


	CFilterParam* param = NULL;
	
	if(docname.CompareF(_L("NULL")) != 0 )
		{
		param = CFilterParam::NewL();
		CleanupStack::PushL(param);
		param->SetDocName(docname);	
		}
	
	
	if(mimetype.CompareF(_L8("NULL")) != 0)
		{
		if(!param)
			{
			param = CFilterParam::NewL();
			CleanupStack::PushL(param);
			}
		
		param->SetmimeType(mimetype);	
		}
	
	TInt err= 0;
	MIterator* iter;
	if(param)
		{
		TRAP(err,test->GetListL(iter,content,param));	
		}
	else
		{
		TRAP(err,test->GetListL(iter,content));		
		}
    
	




	 CleanupStack::PushL(iter);
     
     
     if(noOfmaps > 0)
	    {
		     RArray<TInt> uidArray;
		     TInt matchedOutput =0; 
		     TInt32 appuid;
		     TInt index;
		     TPtrC16 appuidstring;
             for(TInt i =0 ;i < noOfmaps; i++  )
                {
                aItem.GetNextString( appuidstring );
                ConvertHexStringToInt32(appuidstring,appuid );
                uidArray.Append(appuid);
 	            }
 	    
 	         MInfoMap* infomap = NULL;  
 	         _LIT8(UidKey,"Uid");// Key In The Map
        	 TPtrC KeyValue;// value of that key	
 	         
 	         
 	         while( (uidArray.Count()>0) && iter->NextL(infomap) )
        	 	{
        	 	//KeyValue.Zero();
        	 	infomap->FindL(UidKey, KeyValue);
        	 	ConvertHexStringToInt32(KeyValue,appuid );
    
           	 	if( ( index = uidArray.Find( appuid ) )!= KErrNotFound)
           	 	    {
           	 	    matchedOutput++;
           	 	    uidArray.Remove(index);
           	 	    uidArray.Compress();
           	 	    }
           	 	    		
        		delete infomap;
        		infomap = NULL;
        	 	}
        	 	
        	 //iter->Reset(); has to implement by lokesh
           	 if( matchedOutput != noOfmaps )
        	    {
        	    //Test case failed    
        	    err = KErrGeneral;  
        	    }
            uidArray.Reset();
            uidArray.Close();   	 	
       	 }

		
          /*------------------------------------Output For Manual Testing ---------------------------------*/		
		    if(filename.CompareF(_L("NULL"))!= 0)
		        {
		        
		            // Convert 16 Bit values into 8 bit as SAPI accept 8 bit Des
                    TBuf8<30> content8 ;
                    content8.Copy(content);  
		        	
		        
			        // Show the output 
			        RFs fs;
    	            RFile file;  
            		User::LeaveIfError(fs.Connect());
            		CleanupClosePushL(fs);
        			TInt errfile=0;
        			TEntry entry;
        			if( fs.Entry(_L("c:\\Data\\AppManager\\"),entry) != KErrNone)
        			    {
        			     TInt ret = fs.MkDir(_L("c:\\Data\\AppManager\\")); 
        			    }
        			TBuf<100> flname(_L("c:\\data\\AppManager\\"));

        			flname.Append(filename);
        			flname.Append(_L(".txt"));
        	
        			errfile =file.Replace(fs,flname, EFileWrite | EFileStreamText); 
            	    CleanupClosePushL(file);
        	
        			MInfoMap* infomap = NULL;
         			TBuf8<100> filebuf;
        			TInt index =0 ;
        			TBuf8<50> Key;// Key In The Map
        			TPtrC KeyValue;// value of that key
        			
        			filebuf.Append(_L8("TestCase     \n"));
        			filebuf.Append(_L8("Content = "));
        			filebuf.Append(content8);
        			filebuf.Append(_L8(","));
        			
        			filebuf.Append(_L8("docname = "));
        			filebuf.Append(docname);	
        			filebuf.Append(_L8(","));
        			
        			filebuf.Append(_L8("mimetype16 = "));
        			filebuf.Append(mimetype16);	
        			filebuf.Append(_L8("\n"));
        			
        			file.Write(filebuf);
        			filebuf.Zero();
			
        			TInt count =1;
        			
        			while(iter->NextL(infomap))
        	 			{
        	 			filebuf.Append(_L8(" :- "));
        	 			filebuf.AppendNum(count);
        	 			file.Write(content8);
        	 			file.Write(filebuf);
        	 			file.Write(_L8("\n"));
        	 			filebuf.Zero();
        				file.Write(_L8("----------------------------------------------------\n"));
        			 	
        			 	for(index =0 ;index <infomap->Count(); index++ )
        					{
        		 	 		infomap->AtL(index,Key);
        					infomap->FindL(Key, KeyValue);
        					file.Write(Key);
        			 		file.Write(_L8("\t"));
        			 		filebuf.Copy(KeyValue);
        					file.Write(filebuf);
        					file.Write(_L8("\n"));	
        			 		filebuf.Zero();
        			 		Key.Zero();
        			 		//KeyValue.Zero();
        					}// Map
        			 		
        			 	delete infomap;
        			 	infomap = NULL;	
        			 	file.Write(_L8("----------------------------------------------------\n\n"));
        				
        				count++;
        			 	}//Iterator 
        			
        			CleanupStack::PopAndDestroy();//File
        			CleanupStack::PopAndDestroy();//File Session
        		
        	    }
        		
		/*------------------------------------Output For Manual Testing ---------------------------------*/		
		
		   	CleanupStack::Pop(iter);//Iterator release
        	delete iter;
        	iter = NULL;
		  
		
	
	
    
    
    if(!expected)
		{
			//Postive Test Case
			if(err != KErrNone)
			{
				result = KErrGeneral;
			}
		
		}
	else
		{
			if (err == KErrNone)
			{
				result = KErrGeneral;	
			}
				//Neagative Test Case
		}
		

	if(param)
	CleanupStack::PopAndDestroy();//Filter Parameter
	
	CleanupStack::PopAndDestroy();//core class
	__UHEAP_MARKEND;		
	return result;

	
    }
	

// -----------------------------------------------------------------------------
// CAppManagerTest:launchAppL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt CAppManagerTest::launchAppL( CStifItemParser& aItem  )
    {
    __UHEAP_MARK;
    TOptions options;
    TDocument criteria;
    TInt expected;
   	CAppManagerService* coreClass = CAppManagerService::NewL();
 	CleanupStack::PushL(coreClass);
    /*--------Test Logic Starts-----------*/
    TPtrC16 temp;
    TBuf<30> appId;
 	TPtrC16 cmdLine16;
 	TPtrC16 document;
  	TPtrC16 mode;
  	TPtrC16 postion;
  	TPtrC16 callback;
  	TInt err;
 	TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
  	
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
 	
 	TBuf8<30> cmdLine ;
 	if( cmdLine16.CompareF(_L("NULL")) != 0 )
    	{
 	    // Convert 16 Bit values into 8 bit as SAPI accept 8 bit Des
        cmdLine.Copy(cmdLine16);
 	    }
    else
        {
        cmdLine.Copy(KNullDesC8);   
        }
 	
 	if( document.CompareF(_L("NULL")) != 0 )
    	{
 	    options.iDocument.Set(document);
       	}
   
   	if( mode.CompareF(_L("NULL")) != 0 )
    	{
 	    options.iMode.Set(mode);
       	}

    if( postion.CompareF(_L("NULL")) != 0 )
    	{
 	    options.iPostion.Set(postion);
       	}
  
    if( callback.CompareF(_L("NULL")) != 0 )
   	    {
            //Aysnch Call;
            CActiveSchedulerWait *wait = new CActiveSchedulerWait();
            CleanupStack::PushL( wait);
            CAppObserver* callback = CAppObserver::NewL(wait); 
            CleanupStack::PushL( callback);
            TRAP( err,coreClass->LaunchApplicationL( appId,cmdLine,options,callback,1) );
            
           
            //Reason of failure can be either 0 or some negative value which incates 
	        //error but it cant be greater than 0 
	        
	        if(err == 0)
	            {
	             wait->Start();
	            // application launch 
	            if ( callback->iReason > 0 )
	                {
	                //but we didn't get notifaction
	                
	                 //Reason of failure can be either 0 or some negative value which incates 
	                //error but it cant be greater than 0 
	                err =  KErrGeneral;
	                }
	            }

            CleanupStack::PopAndDestroy();
            CleanupStack::PopAndDestroy();	        
        }
    else
        {
            //Synch call
            TRAP( err,coreClass->LaunchApplicationL( appId,cmdLine,options) );
        }
  
    if(!expected)
		{
			//Postive Test Case
			if(err != KErrNone)
			{
			result = KErrGeneral;
			}
		
		}
	else
		{
			if (err == KErrNone)
			{
			result = KErrGeneral;	
			}
				//Neagative Test Case
		}
		
          
    /*--------Test Logic Ends -----------*/
    CleanupStack::PopAndDestroy(coreClass);
    __UHEAP_MARK;
	return result;
    
    }
    
    
// -----------------------------------------------------------------------------
// CAppManagerTest:launchDocL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt CAppManagerTest::launchDocL( CStifItemParser& aItem )
    {
 	
    
	__UHEAP_MARK;
    TOptions options;
    TDocument criteria;
    TInt expected;
   	CAppManagerService* coreClass = CAppManagerService::NewL();
 	CleanupStack::PushL(coreClass);
    /*--------Test Logic Starts-----------*/
   
    TBuf<30> filename;
 	TPtrC16 path;
 	TPtrC16 handle;
  	TPtrC16 mimetype16;
  	TPtrC16 mode;
  	TPtrC16 callback;
  	TInt err;
 	TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
  	
 
 	aItem.GetNextString(path);
 	aItem.GetNextString(handle);
 	aItem.GetNextString(mimetype16);
 	aItem.GetNextString(mode);
 	aItem.GetNextString(callback);
 	aItem.GetNextInt(expected);
 	
 
 	if( path.CompareF(_L("NULL")) != 0 )
    	{
 	    criteria.iPath.Set(path);
 	    }
   
   
   
    
 	if( handle.CompareF(_L("NULL")) != 0 )
    	{
 	     RFs fileSession;
         User::LeaveIfError(fileSession.Connect());
         RFile file;
         User::LeaveIfError(fileSession.ShareProtected());
         file.Open(fileSession,handle,EFileShareReadersOnly);
         criteria.iHandle.Duplicate(file);
       	}
   
   
   
   	if( mode.CompareF(_L("NULL")) != 0 )
    	{
 	    options.iMode.Set(mode);
       	}

    
    
    TBuf8<30> mimetype ;
 	if( mimetype16.CompareF(_L("NULL")) != 0 )
    	{
 	    // Convert 16 Bit values into 8 bit as SAPI accept 8 bit Des
        mimetype.Copy(mimetype16);
 	    }
    else
        {
        mimetype.Copy(KNullDesC8);   
        }
  
  
  
    if( callback.CompareF(_L("NULL")) != 0 )
   	    {
            //Aysnch Call;
            CActiveSchedulerWait *wait = new CActiveSchedulerWait();
            CleanupStack::PushL( wait);
            CAppObserver* callback = CAppObserver::NewL(wait); 
            CleanupStack::PushL( callback);
            TRAP( err,coreClass->LaunchDocumentL(criteria,mimetype,options,filename,callback,1) );
            
            //Reason of failure can be either 0 or some negative value which incates 
	        //error but it cant be greater than 0 
	        
	        if(err == 0)
	            {
	            wait->Start();
	            // application launch 
	            if ( callback->iReason > 0 )
	                {
	                //but we didn't get notifaction
	                
	                 //Reason of failure can be either 0 or some negative value which incates 
	                //error but it cant be greater than 0 
	                err =  KErrGeneral;
	                }
	            }

            CleanupStack::PopAndDestroy();
            CleanupStack::PopAndDestroy();	        
        }
    else
        {
            //Synch call
           TRAP( err,coreClass->LaunchDocumentL(criteria,mimetype,options,filename) );
        }
  
    if(!expected)
		{
			//Postive Test Case
			if(err != KErrNone)
			{
			result = err;
			}
		
		}
	else
		{
			if (err == KErrNone)
			{
			result = KErrGeneral;	
			}
				//Neagative Test Case
		}
		
          
    /*--------Test Logic Ends -----------*/
    CleanupStack::PopAndDestroy(coreClass);
    __UHEAP_MARK;
	return result;

    }
    
    
    
//Helper Function     
     
TInt CAppManagerTest::ConvertHexStringToInt32(const TDesC& aHexString,TInt32& aInt32 )
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

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
