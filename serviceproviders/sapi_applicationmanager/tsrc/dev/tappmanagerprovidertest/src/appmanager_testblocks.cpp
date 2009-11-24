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
#include <StifTestInterface.h>
#include <liwservicehandler.h>
#include <liwbufferextension.h>
#include "appmanagertest.h"
#include "appmanagerservice.h"
#include "appmanagercommon.h"
#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>

#include "testappobserver.h"

_LIT8(KContent,"Type");
_LIT8(KDocumentPath,"DocumentPath");
_LIT8(KMimeType,"MimeType");
_LIT8(KMode,"Mode");
_LIT8(KPostion,"Position");
_LIT8(KHandle,"Handle");
_LIT8(KDocument,"Document");
_LIT(KNull,"NULL");

_LIT8(KService, "Service.AppManager");
_LIT8(KIAppManager,"IAppManager");
_LIT8(KTransactionID,"TransactionID");
_LIT8(KCmdLine,"CmdLine");

_LIT8(KApplicationID,"ApplicationID");
_LIT8(KDocumentName,"DocumentName");

//Supported Operation
_LIT8(KGetList,  "GetList");
_LIT8(KLaunchApp,"LaunchApp");
_LIT8(KLaunchDoc,"LaunchDoc");

_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");
_LIT8(KOptions,"Options");

// Filter Map
_LIT8(KFilter,"Filter");

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
         ENTRY( "cancellaunchDoc", CAppManagerTest::CancellaunchDocL ),
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
 	
    iLog->Log(_L("read varibale "));  
            
  /*-------------------------------------------------------------------------------------------*/
  
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1
    
    if ( iServiceHandler ) 
        iLog->Log(_L("Got Service Handler "));  
    else
        iLog->Log(_L("Didn't get service handler"));  

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIAppManager,KService);
    iLog->Log(_L("Create criterai Item"));
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);//2

        
    RCriteriaArray critArray;
    iLog->Log(_L("Append in Crit"));
    critArray.AppendL(crit);
    CleanupClosePushL(critArray);//3

    iServiceHandler->AttachL(critArray);
    //critArray.Reset();
    //critArray.Close();
    
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
    output->FindFirst(pos,KIAppManager );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    CleanupClosePushL(*Interface);//6

    
    iLog->Log(_L("got Interface"));
  
  
  	//Inserting content
	if( 0 != content.CompareF(KNull) )
	    {
	    TLiwVariant dsName;
	    dsName.Set(content);
        TLiwGenericParam dsNameParam(KContent, content);
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
    CLiwIterable* iter = NULL;
	TLiwVariant Map;
	const CLiwMap* infomap;
    TInt err= 0;
    pos = 0;
    TInt retcode;
    p = output->FindFirst(pos, KErrorCode); // Finding Error Code
    if(p)
        {
       
    	err = p->Value().AsTInt32();
    	iLog->Log(_L("Got Error Code "));
        }
  
    pos = 0;
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
  
  
  
  
  /*---------------------------------------------------------------------------------------------*/

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
 	    
 	         _LIT8(UidKey,"Uid");// Key In The Map
        	 TPtrC KeyValue;// value of that key	
 	         TLiwVariant val;//just for extracting the value
 	         
 	         while( (uidArray.Count()>0) && iter->NextL(Map) )
        	 	{
        	  	infomap = Map.AsMap();
        	 	infomap->FindL(UidKey, val);
        	 	val.Get(KeyValue);
        	 	ConvertHexStringToInt32(KeyValue,appuid );
    
           	 	if( ( index = uidArray.Find( appuid ) )!= KErrNotFound)
           	 	    {
           	 	    matchedOutput++;
           	 	    uidArray.Remove(index);
           	 	    uidArray.Compress();
           	 	    }
           	 	    		
      		    infomap = NULL;	
        		Map.Reset();
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
            		CleanupClosePushL(fs);//8
        			TInt errfile=0;
        			TEntry entry;
        			if( fs.Entry(_L("c:\\Data\\AppManager\\"),entry) != KErrNone)
        			    {
        			     TInt ret = fs.MkDir(_L("c:\\Data\\AppManager\\")); 
        			    }
        			
        			TBuf<100> flname(_L("c:\\Data\\AppManager\\"));

        			flname.Append(filename);
        			flname.Append(_L(".txt"));
        	
        			errfile =file.Replace(fs,flname, EFileWrite | EFileStreamText); 
            	    CleanupClosePushL(file);//9
        	
        	        TBuf8<100> filebuf;
        			TInt index =0 ;
        			TBuf8<15> Key;// Key In The Map
        			TPtrC16 KeyValue;// value of that key
        			
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
        			 TLiwVariant val;//just for extracting the value
        			while(iter && iter->NextL(Map))
        	 			{
        	 			infomap = Map.AsMap();
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
        					infomap->FindL(Key, val);
        					val.Get(KeyValue);
        					file.Write(Key);
        			 		file.Write(_L8("\t"));
        			 		filebuf.Copy(KeyValue);
        					file.Write(filebuf);
        					file.Write(_L8("\n"));	
        			 		filebuf.Zero();
        			 	    }// Map
        			 		
        			 	//delete infomap;
        			 	infomap = NULL;	
        			 	Map.Reset();
        			 	file.Write(_L8("----------------------------------------------------\n\n"));
        				
        				count++;
        			 	}//Iterator 
        			
        			CleanupStack::PopAndDestroy();//File   9
        			CleanupStack::PopAndDestroy();//File Session  8
        		
        	    }
        		
		/*------------------------------------Output For Manual Testing ---------------------------------*/		
		
		   	iter->DecRef();
            

    
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
		
    output->Reset();
    input->Reset();
	
	//if(filterMap)
	//CleanupStack::PopAndDestroy();//Filter Parameter 7
	
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
    CleanupStack::PopAndDestroy( );
   //Interface->Close();
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
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIAppManager,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);//2


    RCriteriaArray critArray;
    critArray.AppendL(crit);
    CleanupClosePushL(critArray);//3

    iServiceHandler->AttachL(critArray);

   

    CLiwGenericParamList* output = CLiwGenericParamList::NewL();
	CleanupStack::PushL(output);//4
	CLiwGenericParamList* input = CLiwGenericParamList::NewL();
	CleanupStack::PushL(input);//5

    iServiceHandler->ExecuteServiceCmdL(*crit, *input, *output);


    // Create the Instance of SAPI class and the Input Param and output Param
    TInt pos = 0;
    MLiwInterface* Interface = NULL;
    output->FindFirst(pos,KIAppManager );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    //MLiwInterface* Interface = CMgDataSourceInterface::NewL();
    CleanupClosePushL(*Interface);//6

    /*--------Test Logic Starts-----------*/
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
 	
 	

  
    if( callback.CompareF(_L("NULL")) != 0 )
   	    {
            //Aysnch Call;
            CActiveSchedulerWait *wait = new CActiveSchedulerWait();
            CleanupStack::PushL( wait);
            CAppObserver* callback = CAppObserver::NewL(wait); 
            CleanupStack::PushL( callback);
            Interface->ExecuteCmdL(KLaunchApp,*input,*output,KLiwOptASyncronous,callback);
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
                
            if ( err == KErrNone)
                {
                // Asynch request properly accepted 
                wait->Start();
                err = callback->iErrorReturn;
                if ( callback->iReason > 0 )
	                {
	                //but we didn't get notifaction
                    //Reason of failure can be either 0 or some negative value which incates 
	                //error but it cant be greater than 0 
	                err =  KErrGeneral;
	                }
	               
                }
           
            CleanupStack::PopAndDestroy();//Callback
            CleanupStack::PopAndDestroy();//Active Wait Scheduler	        
        }
    else
        {
            //Synch call
            if( Interface != NULL)
                {
                _LIT8(KLaunchApp,"LaunchApp");
                Interface->ExecuteCmdL(KLaunchApp,*input,*output);
                }
  	        else
  	            {
  	            //Didn't get the interface
  	            return KErrGeneral;
  	            }
            
        
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
   	//if(filterMap)
	//CleanupStack::PopAndDestroy();//Filter Parameter 7
	
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
    CleanupStack::PopAndDestroy( );
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
	

    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIAppManager,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);//2


    RCriteriaArray critArray;
    critArray.AppendL(crit);
    CleanupClosePushL(critArray);//3

    iServiceHandler->AttachL(critArray);

   

    CLiwGenericParamList* output = CLiwGenericParamList::NewL();
	CleanupStack::PushL(output);//4
	CLiwGenericParamList* input = CLiwGenericParamList::NewL();
	CleanupStack::PushL(input);//5

    iServiceHandler->ExecuteServiceCmdL(*crit, *input, *output);


    // Create the Instance of SAPI class and the Input Param and output Param
    TInt pos = 0;
    MLiwInterface* Interface = NULL;
    output->FindFirst(pos,KIAppManager );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    //MLiwInterface* Interface = CMgDataSourceInterface::NewL();
    CleanupClosePushL(*Interface);//6
    
    /*--------Test Logic Starts-----------*/
    TOptions options;
    TDocument criteria;
    TInt expected;
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
 	
 /*------------------------------------------------------------------*/
 
   	
   	//Inserting Document
   	
   	
 	CLiwDefaultMap *documentMap = NULL;
	input->Reset();
	
	if(  path.CompareF(_L("NULL")) != 0 )
		{
		documentMap = CLiwDefaultMap::NewL();
       	documentMap->InsertL(KDocumentPath,TLiwVariant(path));
		TLiwGenericParam iFilterParam( KDocument, TLiwVariant(documentMap));
	    input->AppendL(iFilterParam);
	    documentMap->DecRef();
	 	}
	
	
	if( handle.CompareF(_L("NULL") ) != 0)
		{
		if( !documentMap )
			{
			documentMap = CLiwDefaultMap::NewL();
           	TLiwGenericParam iFilterParam(KDocument, TLiwVariant(documentMap));
	        input->AppendL(iFilterParam);
	        documentMap->DecRef();
			}
		
	     RFs fileSession;
         User::LeaveIfError(fileSession.Connect());
         RFile file;
         User::LeaveIfError(fileSession.ShareProtected());
         file.Open(fileSession,handle,EFileShareReadersOnly);
         //CLiwDefaultFileBuffer* filebuffer = CLiwFileBuffer::NewL();
         documentMap->InsertL(KHandle,TLiwVariant(file));	
		}
 
 
 
 
    //Inserting MimeType
	if( 0 != mimetype16.CompareF(KNull) )
	    {
	    TLiwVariant mimetype;
	    mimetype.Set(mimetype16);
        TLiwGenericParam mimetypeParam(KMimeType, mimetype);
	    input->AppendL(mimetypeParam);
	    }
 
 
 	 
	
	if( mode.CompareF(_L("NULL")) != 0 )
		{
		CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
       	filterMap->InsertL(KMode,TLiwVariant(mode));
		TLiwGenericParam iFilterParam(KOptions, TLiwVariant(filterMap));
	    input->AppendL(iFilterParam);
	    filterMap->DecRef();
	 	}
	
 
  
    if( callback.CompareF(_L("NULL")) != 0 )
   	    {
            //Aysnch Call;
            CActiveSchedulerWait *wait = new CActiveSchedulerWait();
            CleanupStack::PushL( wait);
            CAppObserver* callback = CAppObserver::NewL(wait); 
            CleanupStack::PushL( callback);
            Interface->ExecuteCmdL(KLaunchDoc,*input,*output,KLiwOptASyncronous,callback);
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
                
            if ( err == KErrNone)
                {
                // Asynch request properly accepted 
                
                wait->Start();
                err = callback->iErrorReturn;
                if ( callback->iReason > 0 )
	                {
	                //but we didn't get notifaction
                    //Reason of failure can be either 0 or some negative value which incates 
	                //error but it cant be greater than 0 
	                err =  KErrGeneral;
	                }
	               
                }
           
            CleanupStack::PopAndDestroy();//Callback
            CleanupStack::PopAndDestroy();//Active Wait Scheduler	        
        }
    else
        {
            //Synch call
            if( Interface != NULL)
                {
                _LIT8(KLaunchApp,"LaunchApp");
                Interface->ExecuteCmdL(KLaunchDoc,*input,*output);
                }
  	        else
  	            {
  	            //Didn't get the interface
  	            return KErrGeneral;
  	            }
            
        
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
                
            p= NULL;
            pos = 0;
            p = output->FindFirst(pos, KDocumentName); // Finding Error Code
            if(p)
                {
                TPtrC filname ;
                p->Value().Get(filname);
                }
            
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
   	
	
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
    CleanupStack::PopAndDestroy( );
    __UHEAP_MARK;
	return result;
    }
    
    
    
    // -----------------------------------------------------------------------------
// CAppManagerTest:launchDocL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt CAppManagerTest::CancellaunchDocL( CStifItemParser& aItem )
    {
 	
    
	__UHEAP_MARK;
	

    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIAppManager,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);//2


    RCriteriaArray critArray;
    critArray.AppendL(crit);
    CleanupClosePushL(critArray);//3

    iServiceHandler->AttachL(critArray);

   

    CLiwGenericParamList* output = CLiwGenericParamList::NewL();
	CleanupStack::PushL(output);//4
	CLiwGenericParamList* input = CLiwGenericParamList::NewL();
	CleanupStack::PushL(input);//5

    iServiceHandler->ExecuteServiceCmdL(*crit, *input, *output);


    // Create the Instance of SAPI class and the Input Param and output Param
    TInt pos = 0;
    MLiwInterface* Interface = NULL;
    output->FindFirst(pos,KIAppManager );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    //MLiwInterface* Interface = CMgDataSourceInterface::NewL();
    CleanupClosePushL(*Interface);//6
    
    /*--------Test Logic Starts-----------*/
    TOptions options;
    TDocument criteria;
    TInt expected;
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
 	
 /*------------------------------------------------------------------*/
 
   	
   	//Inserting Document
   	
   	
 	CLiwDefaultMap *documentMap = NULL;
	
	if(  path.CompareF(_L("NULL")) != 0 )
		{
		documentMap = CLiwDefaultMap::NewL();
       	documentMap->InsertL(KDocumentPath,TLiwVariant(path));
		TLiwGenericParam iFilterParam( KDocument, TLiwVariant(documentMap));
	    input->AppendL(iFilterParam);
	    documentMap->DecRef();
	 	}
	
	
	if( handle.CompareF(_L("NULL") ) != 0)
		{
		if( !documentMap )
			{
			documentMap = CLiwDefaultMap::NewL();
           	TLiwGenericParam iFilterParam(KDocument, TLiwVariant(documentMap));
	        input->AppendL(iFilterParam);
	        documentMap->DecRef();
			}
		
	     RFs fileSession;
         User::LeaveIfError(fileSession.Connect());
         RFile file;
         User::LeaveIfError(fileSession.ShareProtected());
         file.Open(fileSession,handle,EFileShareReadersOnly);
         //criteria.iHandle.Duplicate(file);
	     documentMap->InsertL(KHandle,TLiwVariant(file));	
		}
 
 
 
 
    //Inserting MimeType
	if( 0 != mimetype16.CompareF(KNull) )
	    {
	    TLiwVariant mimetype;
	    mimetype.Set(mimetype16);
        TLiwGenericParam mimetypeParam(KMimeType, mimetype);
	    input->AppendL(mimetypeParam);
	    }
 
 
 	 
	
	if( mode.CompareF(_L("NULL")) != 0 )
		{
		CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
       	filterMap->InsertL(KMode,TLiwVariant(mode));
		TLiwGenericParam iFilterParam(KOptions, TLiwVariant(filterMap));
	    input->AppendL(iFilterParam);
	    filterMap->DecRef();
	 	}
	
 
  
    if( callback.CompareF(_L("NULL")) != 0 )
   	    {
            //Aysnch Call;
            CActiveSchedulerWait *wait = new CActiveSchedulerWait();
            CleanupStack::PushL( wait);
            CAppObserver* callback = CAppObserver::NewL(wait); 
            CleanupStack::PushL( callback);
            Interface->ExecuteCmdL(KLaunchDoc,*input,*output,KLiwOptASyncronous,callback);
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
                
            if ( err == KErrNone)
                {
                pos = 0;
                p = output->FindFirst(pos, KTransactionID);
                input->Reset();
                
	            input->AppendL( TLiwGenericParam (KTransactionID, TLiwVariant ( p->Value().AsTInt32() ) ) );
                //Interface->ExecuteCmdL(KLaunchDoc,*input,*output,KLiwOptCancel,callback);
                //wait->Start();
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
	               
                }
           
            CleanupStack::PopAndDestroy();//Callback
            CleanupStack::PopAndDestroy();//Active Wait Scheduler	        
        }
    else
        {
            //Synch call
            if( Interface != NULL)
                {
                _LIT8(KLaunchApp,"LaunchApp");
                Interface->ExecuteCmdL(KLaunchDoc,*input,*output);
                }
  	        else
  	            {
  	            //Didn't get the interface
  	            return KErrGeneral;
  	            }
            
        
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
                
            p= NULL;
            pos = 0;
            p = output->FindFirst(pos, KDocumentName); // Finding Error Code
            if(p)
                {
                TPtrC filname ;
                p->Value().Get(filname);
                }
            
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
   	
	
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
	CleanupStack::PopAndDestroy( );
    CleanupStack::PopAndDestroy( );
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
