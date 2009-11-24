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
#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>

#include "ttestmediathumbobserver.h"
#include "tmediathumbnailtest.h"
// GETthumb
_LIT8(KService, "Service.MediaManagement");
_LIT8(KIDataSource,"IDataSource");

_LIT8(KGetThumbnail,"GetThumbnail"); 
_LIT8(KCmdCancel,"Cancel");
//Input Keys/arguments
_LIT8(KTransactionID,"TransactionID");
// for Url
_LIT8(KUrl,"Url");

// thumbnailsize
_LIT8(KThumbnailSize,"ThumbnailSize");

// Width
_LIT8(KWidth,"width");
//height
_LIT8(KHeight,"height");

//_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");
//_LIT8(KThumbNailUrl,"ThumbnailUrl");

//_LIT(KImageUrl,"C:\\Data\\images\\ant.jpg");
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
void CMediaThumbTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Csapi_getheader:RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CMediaThumbTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
         ENTRY( "getthumbnailtest", CMediaThumbTest::getthumbnailL ),
        ENTRY( "cancelthumbnail", CMediaThumbTest::CancelThumbnailL ),
       ENTRY( "gethumbanilwrongtype", CMediaThumbTest::GetThumbnailWrrongURLType ),
         ENTRY( "getThumbnailwrongthumbnailsize", CMediaThumbTest::GetThumbnailWrongThumnailSizeType ),
        ENTRY( "getThumbnailwrongwidthtype", CMediaThumbTest::getThumbnail_WrongWidthType ),
         ENTRY( "getThumbnailwrongheighttype", CMediaThumbTest::getThumbnail_WrongHeightType ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CMediaThumbTest:getlistapplication1_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CMediaThumbTest::getthumbnailL( CStifItemParser& aItem  )
    {
    RFs fs;
    User::LeaveIfError(fs.Connect());
    RFile file;
    User::LeaveIfError(file.Replace(fs,_L("C:\\Data\\TestCase.txt"),EFileRead | EFileStreamText ));
    
    file.Write(_L8("Testcase staretd\n"));
    // Type Url val Type ThumbnailSize Type width val type height val
    __UHEAP_MARK;
    TPtrC16 url;
    TPtrC16 heightstr;
    TPtrC16 widthstr;
    TInt widthVal=-1;
    TInt heightVal=-1;
    TInt ExpectedResult = 0;
 	TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
    iLog->Log(_L("read varibale "));  
            
  /*-------------------------------------------------------------------------------------------*/
  
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1
    
    if ( iServiceHandler ) 
        iLog->Log(_L("Got Service Handler "));  
    else
        iLog->Log(_L("Didn't get service handler"));  

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIDataSource,KService);
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
    output->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    CleanupClosePushL(*Interface);//6

    
    iLog->Log(_L("got Interface"));
 
    
//======= Now creating input============================================================================ 
    
   
    // Getting Url value
  
 
        aItem.GetNextString(url); // Taking value as string for url
        
        TLiwGenericParam urlVal(KUrl,TLiwVariant(url));
        input->AppendL(urlVal);
  
      // ThumbnailSize as Ma
        CLiwDefaultMap *ThumbnailSizeMap = CLiwDefaultMap::NewL();
        CleanupStack::PushL(ThumbnailSizeMap); 
        // Getting width value
        aItem.GetNextString(widthstr);
        if(widthstr.Compare(_L("NULL")) != 0 )
            {
            aItem.GetNextInt(widthVal);
            ThumbnailSizeMap->InsertL(KWidth,TLiwVariant((TInt32)widthVal));          
            }
        aItem.GetNextString(heightstr);
        if(heightstr.Compare(_L("NULL")) != 0 )
             {
             aItem.GetNextInt(heightVal);
             ThumbnailSizeMap->InsertL(KHeight,TLiwVariant((TInt32)heightVal));       
             }
        TLiwGenericParam thumbsizemap(KThumbnailSize, TLiwVariant(ThumbnailSizeMap));
        input->AppendL(thumbsizemap);
        CleanupStack::Pop(ThumbnailSizeMap);
        ThumbnailSizeMap->DecRef();
       
        aItem.GetNextInt(ExpectedResult);
        
     // Creating callback 
    
       
        
        CActiveSchedulerWait *wait = new CActiveSchedulerWait();
           CleanupStack::PushL( wait);
           CThumbnailObserver* callback = CThumbnailObserver::NewL(wait,widthVal,heightVal); 
           CleanupStack::PushL( callback);
           file.Write(_L8("Instance of callback and Activewait schedual is created\n"));
           file.Write(_L8("Calling execute commandL\n"));
           
           Interface->ExecuteCmdL(KGetThumbnail,*input,*output,KLiwOptASyncronous,callback);
           file.Write(_L8("Returning to test case\n"));  
           const TLiwGenericParam* p= NULL;
           pos = 0;
           p = output->FindFirst(pos, KErrorCode); // Finding Error Code
           if(p)
               {
               result = p->Value().AsTInt32();
               }
           else
               {
               result = KErrGeneral; 
               }
           TBuf8<50> bufer;
           bufer.AppendNum(result);
           
           file.Write(_L8("Got errcode from provider : "));
           file.Write(bufer);
           if ( result == KErrNone)
               {
               // Asynch request properly accepted 
               file.Write(_L8("Starting schdular\n"));
               wait->Start();
               result = callback->iErrorReturn;
               file.Write(_L8("Schedual is returned\n"));
               }

                
           CleanupStack::PopAndDestroy(callback);//Callback
           CleanupStack::PopAndDestroy(wait);//Active Wait Scheduler   
    
          
    
  
    output->Reset();
    input->Reset();
	
    CleanupStack::PopAndDestroy();// interface
    CleanupStack::PopAndDestroy(input);
    CleanupStack::PopAndDestroy(output);
    CleanupStack::PopAndDestroy(&critArray);
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(iServiceHandler);
    file.Write(_L8("Cleanup done\n"));
    
	__UHEAP_MARKEND;		

	file.Write(_L8("No memory Leak\n"));
	file.Close();
fs.Close();
	
	if(ExpectedResult == result)
	    return KErrNone;
 	else
	    return KErrGeneral;
	

    }
	
 
TInt CMediaThumbTest::CancelThumbnailL( CStifItemParser& aItem )
    {
    RFs fs;
    User::LeaveIfError(fs.Connect());
    RFile file;
    User::LeaveIfError(file.Replace(fs,_L("C:\\Data\\CancelTestCase.txt"),EFileRead | EFileStreamText ));
    
    file.Write(_L8("Testcase staretd\n"));
    // Type Url val Type ThumbnailSize Type width val type height val
    __UHEAP_MARK;
    TPtrC16 url;
    TPtrC16 heightstr;
    TPtrC16 widthstr;
    TInt widthVal=-1;
    TInt heightVal=-1;
    TInt ExpectedResult = 0;
    TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
    iLog->Log(_L("read varibale "));  
            
  /*-------------------------------------------------------------------------------------------*/
  
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1
    
    if ( iServiceHandler ) 
        iLog->Log(_L("Got Service Handler "));  
    else
        iLog->Log(_L("Didn't get service handler"));  

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIDataSource,KService);
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
    output->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    CleanupClosePushL(*Interface);//6

    
    iLog->Log(_L("got Interface"));
 
    
//======= Now creating input============================================================================ 
    
   
    // Getting Url value
  
 
        aItem.GetNextString(url); // Taking value as string for url
        
        TLiwGenericParam urlVal(KUrl,TLiwVariant(url));
        input->AppendL(urlVal);
  
      // ThumbnailSize as Ma
        CLiwDefaultMap *ThumbnailSizeMap = CLiwDefaultMap::NewL();
        CleanupStack::PushL(ThumbnailSizeMap); 
        // Getting width value
        aItem.GetNextString(widthstr);
        if(widthstr.Compare(_L("NULL")) != 0 )
            {
            aItem.GetNextInt(widthVal);
            ThumbnailSizeMap->InsertL(KWidth,TLiwVariant((TInt32)widthVal));          
            }
        aItem.GetNextString(heightstr);
        if(heightstr.Compare(_L("NULL")) != 0 )
             {
             aItem.GetNextInt(heightVal);
             ThumbnailSizeMap->InsertL(KHeight,TLiwVariant((TInt32)heightVal));       
             }
        TLiwGenericParam thumbsizemap(KThumbnailSize, TLiwVariant(ThumbnailSizeMap));
        input->AppendL(thumbsizemap);
        CleanupStack::Pop(ThumbnailSizeMap);
        ThumbnailSizeMap->DecRef();
       
        aItem.GetNextInt(ExpectedResult);
        
     // Creating callback 
    
       
        
        CActiveSchedulerWait *wait = new CActiveSchedulerWait();
           CleanupStack::PushL( wait);
           CThumbnailObserver* callback = CThumbnailObserver::NewL(wait,widthVal,heightVal); 
           CleanupStack::PushL( callback);
           file.Write(_L8("Instance of callback and Activewait schedual is created\n"));
           file.Write(_L8("Calling execute commandL\n"));
           
           Interface->ExecuteCmdL(KGetThumbnail,*input,*output,KLiwOptASyncronous,callback);
           file.Write(_L8("Returning to test case\n"));  
           const TLiwGenericParam* p= NULL;
           pos = 0;
           p = output->FindFirst(pos, KErrorCode); // Finding Error Code
           if(p)
               {
               result = p->Value().AsTInt32();
               }
           else
               {
               result = KErrGeneral; 
               }
           TBuf8<50> bufer;
           bufer.AppendNum(result);
           
           file.Write(_L8("Got errcode from provider : "));
           file.Write(bufer);
           if ( result == KErrNone)
               {
               pos = 0;
                p = output->FindFirst(pos, KTransactionID);
                TInt TransId =  p->Value().AsTInt32();
                output->Reset();
                  
                input->AppendL( TLiwGenericParam (KTransactionID, TLiwVariant ((TInt32) TransId ) ) );
                file.Write(_L8("Calling cancel \n"));
                Interface->ExecuteCmdL(KCmdCancel,*input,*output,KLiwOptCancel);
               
                pos = 0;
            
                p = output->FindFirst(pos, KErrorCode); // Finding Error Code
                if(p)
                    {
                    result = p->Value().AsTInt32();
                    }
                else
                    {
                    result = KErrGeneral; 
                    }
                 TBuf8<20>    buf;
                 buf.AppendNum(result);
                file.Write(_L8("Result is "));   
                file.Write(buf);
           
 
               }
               if(callback->iCancel)
                   result = KErrNone;
               else
                   result = KErrGeneral;
                
           CleanupStack::PopAndDestroy(callback);//Callback
           CleanupStack::PopAndDestroy(wait);//Active Wait Scheduler   
    
          
    
  
    output->Reset();
    input->Reset();
    
    CleanupStack::PopAndDestroy();// interface
    CleanupStack::PopAndDestroy(input);
    CleanupStack::PopAndDestroy(output);
    CleanupStack::PopAndDestroy(&critArray);
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(iServiceHandler);
    file.Write(_L8("Cleanup done\n"));
    
    __UHEAP_MARKEND;        

    file.Write(_L8("No memory Leak\n"));
    file.Close();
fs.Close();
    
    if(ExpectedResult == result)
        return KErrNone;
    else
        return KErrGeneral;
    

    }

    
TInt CMediaThumbTest::GetThumbnailWrrongURLType( CStifItemParser& aItem )
    {

    // Type Url val Type ThumbnailSize Type width val type height val
    __UHEAP_MARK;
       TPtrC16 url;
    TInt widthVal=-1;
    TInt heightVal=-1;
   // TInt ExpectedResult = 0;
    TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
    iLog->Log(_L("read varibale "));  
            
  /*-------------------------------------------------------------------------------------------*/

    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1
    
    if ( iServiceHandler ) 
        iLog->Log(_L("Got Service Handler "));  
    else
        iLog->Log(_L("Didn't get service handler"));  

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIDataSource,KService);
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
    output->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    CleanupClosePushL(*Interface);//6

    
    iLog->Log(_L("got Interface"));
 
    
//======= Now creating input============================================================================ 
    
   
    // Getting Url value
  
 aItem.GetNextString(url);
              
        // Giving an integer as url
        TInt uRL = 50;
        TLiwGenericParam urlVal(KUrl,TLiwVariant(uRL));
        input->AppendL(urlVal);
  
       
        CActiveSchedulerWait *wait = new CActiveSchedulerWait();
           CleanupStack::PushL( wait);
           CThumbnailObserver* callback = CThumbnailObserver::NewL(wait,widthVal,heightVal); 
           CleanupStack::PushL( callback);
          Interface->ExecuteCmdL(KGetThumbnail,*input,*output,KLiwOptASyncronous,callback);
 
           const TLiwGenericParam* p= NULL;
           pos = 0;
           p = output->FindFirst(pos, KErrorCode); // Finding Error Code
           if(p)
               {
               result = p->Value().AsTInt32();
               }
           else
               {
               result = KErrGeneral; 
               }
               
           if(1002 == result)
               result = KErrNone;
           else
               result = KErrGeneral;
           
                 
           CleanupStack::PopAndDestroy(callback);//Callback
           CleanupStack::PopAndDestroy(wait);//Active Wait Scheduler   
    
    
    
  
    output->Reset();
    input->Reset();
    
    CleanupStack::PopAndDestroy();// interface
    CleanupStack::PopAndDestroy(input);
    CleanupStack::PopAndDestroy(output);
    CleanupStack::PopAndDestroy(&critArray);
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(iServiceHandler);
    __UHEAP_MARKEND;        

  return result;

    
    
    }


TInt CMediaThumbTest::GetThumbnailWrongThumnailSizeType( CStifItemParser& aItem )
    {
    // Type Url val Type ThumbnailSize Type width val type height val
    __UHEAP_MARK;
    TPtrC16 url;
    TPtrC16 heightstr;
    TPtrC16 widthstr;
    TInt widthVal=-1;
    TInt heightVal=-1;
    TInt ExpectedResult = 0;
    TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
    iLog->Log(_L("read varibale "));  
            
  /*-------------------------------------------------------------------------------------------*/
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1
    
    if ( iServiceHandler ) 
        iLog->Log(_L("Got Service Handler "));  
    else
        iLog->Log(_L("Didn't get service handler"));  

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIDataSource,KService);
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
    output->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    CleanupClosePushL(*Interface);//6

    
    iLog->Log(_L("got Interface"));
 
    
//======= Now creating input============================================================================ 
    
   
    // Getting Url value
  
 
        aItem.GetNextString(url); // Taking value as string for url
        
        TLiwGenericParam urlVal(KUrl,TLiwVariant(url));
        input->AppendL(urlVal);
  
      // ThumbnailSize as List
        CLiwDefaultList* ThumbnailSizeList = CLiwDefaultList::NewL();
        CleanupStack::PushL(ThumbnailSizeList);
        
        
    
        TLiwGenericParam thumbsizelist(KThumbnailSize, TLiwVariant(ThumbnailSizeList));
        input->AppendL(thumbsizelist);
        CleanupStack::Pop(ThumbnailSizeList);
        ThumbnailSizeList->DecRef();
       
        aItem.GetNextInt(ExpectedResult);
        
     // Creating callback 
    
       
        
        CActiveSchedulerWait *wait = new CActiveSchedulerWait();
           CleanupStack::PushL( wait);
           CThumbnailObserver* callback = CThumbnailObserver::NewL(wait,widthVal,heightVal); 
           CleanupStack::PushL( callback);
          Interface->ExecuteCmdL(KGetThumbnail,*input,*output,KLiwOptASyncronous,callback);
 
           const TLiwGenericParam* p= NULL;
           pos = 0;
           p = output->FindFirst(pos, KErrorCode); // Finding Error Code
           if(p)
               {
               result = p->Value().AsTInt32();
               }
           else
               {
               result = KErrGeneral; 
               }
               
           if ( ExpectedResult == result )
               {
               result =KErrNone;
               }
           else
               result =KErrGeneral;

                
           CleanupStack::PopAndDestroy(callback);//Callback
           CleanupStack::PopAndDestroy(wait);//Active Wait Scheduler   
    
    
    
  
    output->Reset();
    input->Reset();
    
    CleanupStack::PopAndDestroy();// interface
    CleanupStack::PopAndDestroy(input);
    CleanupStack::PopAndDestroy(output);
    CleanupStack::PopAndDestroy(&critArray);
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(iServiceHandler);
    __UHEAP_MARKEND;        

  return result;

    }
    

TInt CMediaThumbTest::getThumbnail_WrongWidthType( CStifItemParser& aItem  )
    {
    // Type Url val Type ThumbnailSize Type width val type height val
    __UHEAP_MARK;
    TPtrC16 url;
    TPtrC16 heightstr;
    TPtrC16 widthstr;
    TInt widthVal=-1;
    TInt heightVal=-1;
    TInt ExpectedResult = 0;
    TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
    iLog->Log(_L("read varibale "));  
            
  /*-------------------------------------------------------------------------------------------*/
  
 
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1
    
    if ( iServiceHandler ) 
        iLog->Log(_L("Got Service Handler "));  
    else
        iLog->Log(_L("Didn't get service handler"));  

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIDataSource,KService);
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
    output->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    CleanupClosePushL(*Interface);//6

    
    iLog->Log(_L("got Interface"));
 
    
//======= Now creating input============================================================================ 
    
   
    // Getting Url value
  
 
        aItem.GetNextString(url); // Taking value as string for url
        
        TLiwGenericParam urlVal(KUrl,TLiwVariant(url));
        input->AppendL(urlVal);
  
      // ThumbnailSize as Map
        CLiwDefaultMap *ThumbnailSizeMap = CLiwDefaultMap::NewL();
        CleanupStack::PushL(ThumbnailSizeMap); 
        // Getting width value
        aItem.GetNextString(widthstr);
        if(widthstr.Compare(_L("NULL")) != 0 )
            {
            aItem.GetNextInt(widthVal);
            TBuf<50> widthbuf;
            widthbuf.Append(_L("String"));
            ThumbnailSizeMap->InsertL(KWidth,TLiwVariant(widthbuf));          
            }
        aItem.GetNextString(heightstr);
        if(heightstr.Compare(_L("NULL")) != 0 )
             {
             aItem.GetNextInt(heightVal);
             ThumbnailSizeMap->InsertL(KHeight,TLiwVariant((TInt32)heightVal));       
             }
        TLiwGenericParam thumbsizemap(KThumbnailSize, TLiwVariant(ThumbnailSizeMap));
        input->AppendL(thumbsizemap);
        CleanupStack::Pop(ThumbnailSizeMap);
        ThumbnailSizeMap->DecRef();
       
        aItem.GetNextInt(ExpectedResult);
        
     // Creating callback 
    
       
        
        CActiveSchedulerWait *wait = new CActiveSchedulerWait();
           CleanupStack::PushL( wait);
           CThumbnailObserver* callback = CThumbnailObserver::NewL(wait,widthVal,heightVal); 
           CleanupStack::PushL( callback);
          Interface->ExecuteCmdL(KGetThumbnail,*input,*output,KLiwOptASyncronous,callback);
 
           const TLiwGenericParam* p= NULL;
           pos = 0;
           p = output->FindFirst(pos, KErrorCode); // Finding Error Code
           if(p)
               {
               result = p->Value().AsTInt32();
               }
           else
               {
               result = KErrGeneral; 
               }
               
           if ( ExpectedResult == result)
               {
               result= KErrNone;    
               
               }
           else
               result = KErrGeneral;

                
           CleanupStack::PopAndDestroy(callback);//Callback
           CleanupStack::PopAndDestroy(wait);//Active Wait Scheduler   
    
    
    
  
    output->Reset();
    input->Reset();
    
    CleanupStack::PopAndDestroy();// interface
    CleanupStack::PopAndDestroy(input);
    CleanupStack::PopAndDestroy(output);
    CleanupStack::PopAndDestroy(&critArray);
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(iServiceHandler);
    __UHEAP_MARKEND;        

  return result;
    

    }


TInt CMediaThumbTest::getThumbnail_WrongHeightType( CStifItemParser& aItem  )
    {
    // Type Url val Type ThumbnailSize Type width val type height val
    __UHEAP_MARK;
    TPtrC16 url;
    TPtrC16 heightstr;
    TPtrC16 widthstr;
    TInt widthVal=-1;
    TInt heightVal=-1;
    TInt ExpectedResult = 0;
    TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
    iLog->Log(_L("read varibale "));  
            
  /*-------------------------------------------------------------------------------------------*/
  
 
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1
    
    if ( iServiceHandler ) 
        iLog->Log(_L("Got Service Handler "));  
    else
        iLog->Log(_L("Didn't get service handler"));  

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIDataSource,KService);
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
    output->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();



    CleanupClosePushL(*Interface);//6

    
    iLog->Log(_L("got Interface"));
 
    
//======= Now creating input============================================================================ 
    
   
    // Getting Url value
  
 
        aItem.GetNextString(url); // Taking value as string for url
        
        TLiwGenericParam urlVal(KUrl,TLiwVariant(url));
        input->AppendL(urlVal);
  
      // ThumbnailSize as Map
        CLiwDefaultMap *ThumbnailSizeMap = CLiwDefaultMap::NewL();
        CleanupStack::PushL(ThumbnailSizeMap); 
        // Getting width value
        aItem.GetNextString(widthstr);
        if(widthstr.Compare(_L("NULL")) != 0 )
            {
            aItem.GetNextInt(widthVal);

            ThumbnailSizeMap->InsertL(KWidth,TLiwVariant(widthVal));          
            }
        aItem.GetNextString(heightstr);
        if(heightstr.Compare(_L("NULL")) != 0 )
             {
             aItem.GetNextInt(heightVal);
             TBuf<50> heightbuf;
             heightbuf.Append(_L("String"));             
             ThumbnailSizeMap->InsertL(KHeight,TLiwVariant(heightbuf));       
             }
        TLiwGenericParam thumbsizemap(KThumbnailSize, TLiwVariant(ThumbnailSizeMap));
        input->AppendL(thumbsizemap);
        CleanupStack::Pop(ThumbnailSizeMap);
        ThumbnailSizeMap->DecRef();
       
        aItem.GetNextInt(ExpectedResult);
        
     // Creating callback 
    
       
        
        CActiveSchedulerWait *wait = new CActiveSchedulerWait();
           CleanupStack::PushL( wait);
           CThumbnailObserver* callback = CThumbnailObserver::NewL(wait,widthVal,heightVal); 
           CleanupStack::PushL( callback);
          Interface->ExecuteCmdL(KGetThumbnail,*input,*output,KLiwOptASyncronous,callback);
 
           const TLiwGenericParam* p= NULL;
           pos = 0;
           p = output->FindFirst(pos, KErrorCode); // Finding Error Code
           if(p)
               {
               result = p->Value().AsTInt32();
               }
           else
               {
               result = KErrGeneral; 
               }
               
           if ( ExpectedResult == result)
               {
               result= KErrNone;    
               
               }
           else
               result = KErrGeneral;

                
           CleanupStack::PopAndDestroy(callback);//Callback
           CleanupStack::PopAndDestroy(wait);//Active Wait Scheduler   
    
    
    
  
    output->Reset();
    input->Reset();
    
    CleanupStack::PopAndDestroy();// interface
    CleanupStack::PopAndDestroy(input);
    CleanupStack::PopAndDestroy(output);
    CleanupStack::PopAndDestroy(&critArray);
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(iServiceHandler);
    __UHEAP_MARKEND;        

  return result;
    

    }


// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
