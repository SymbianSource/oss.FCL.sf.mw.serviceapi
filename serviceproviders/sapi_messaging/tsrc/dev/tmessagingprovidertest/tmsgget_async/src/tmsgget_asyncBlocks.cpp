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
* Description:   ?Description
*
*/


// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "tmsgget_async.h"

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

_LIT8(KService, "Service.Messaging");
_LIT8(KIDataSource,"IMessaging");
_LIT(KMessageTypeSMS,"SMS");
_LIT8(KErrCode,"ErrorCode");
_LIT(KMessageTypeMMS,"MMS");


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
// Ctmsgget_async::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctmsgget_async::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctmsgget_async::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctmsgget_async::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "Example", Ctmsgget_async::ExampleL ),
        ENTRY( "getlist_asyncsms", Ctmsgget_async::getlist_asyncsmsL ),
        ENTRY( "getlist_asyncmms", Ctmsgget_async::getlist_asyncmmsL ),
        ENTRY( "getlist_asyncstress", Ctmsgget_async::getlist_asyncstressL )
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt Ctmsgget_async::HandleNotifyL(TInt aCmdId,
                                            TInt aEventId,
                                            CLiwGenericParamList& aEventParamList,
                                            const CLiwGenericParamList& aInParamList)
    {
    TInt pos = 0;
    const TLiwGenericParam* output = aEventParamList.FindFirst( pos,_L8("ReturnValue"));
          
          TInt val=0;     
          if(output)     
          {
              //RFile fs;
              //RFs rFs;
              //rFs.Connect();
              //rFs.Delete(_L("c:\\getheaderiter3_1.txt")); 
              //fs.Create(r//fs, _L("c:\\getheaderiter3_1.txt"), EFileShareExclusive|EFileWrite)  ;

              CLiwIterable* iterlist = output->Value().AsIterable();

              TLiwVariant data;
            
              while( iterlist->NextL(data))
                  {
                  
                  const CLiwMap* Map = data.AsMap(); 
                  
                  TLiwVariant mtmtype;
                  Map->FindL(_L8("MessageType"),mtmtype);
                  TPtrC  mtm = mtmtype.AsDes(); 
                  if(iTestid==ESMS)
                    {
                    if(mtm.FindF(_L("SMS")) == KErrNotFound )   
                    val++;
                    }
                  
                  if(iTestid==EMMS)
                    {
                    if(mtm.FindF(_L("MMS")) == KErrNotFound )   
                    val++;
                    }
                   
                  
                  TBuf8<50> buf;
                  buf.Copy(mtm)   ;
                  //fs.Write(_L8("Mtm Id :"));
                  //fs.Write(buf);
                  //fs.Write(_L8("\n"));   /// writing mtm type 
                  mtmtype.Reset();
                  
                  TLiwVariant sender;
                  Map->FindL(_L8("Sender"),sender);
                  TPtrC  send = sender.AsDes(); 
                  
                  //if(send.FindF(_L("9008032761")) == KErrNotFound)
                  //   val++;
                  
                  
                  buf.Copy(send)  ;
                  //fs.Write(_L8("Sender :"));
                  //fs.Write(buf);
                  //fs.Write(_L8("\n"));   /// writing sender 
                  sender.Reset();
                  TLiwVariant messageid;
                  Map->FindL(_L8("MessageId"),messageid);
                  TInt  id = (TInt)messageid.AsTInt32();
              
                  
                  
                  buf.Num(id) ;
                  //fs.Write(_L8("Message id :"));
                  //fs.Write(buf);
                  //fs.Write(_L8("\n"));   /// writing messageid
                  messageid.Reset();
                  
                  TLiwVariant date;
                  Map->FindL(_L8("Time"),date);
                  
                  
                  TTime date1 =(TTime) date.AsTTime();
                  
                  
                  TDateTime date2 = date1.DateTime();
              
                  buf.Num(date2.Day());
                  //fs.Write(_L8("Day:"));
                  //fs.Write(buf);
                  //fs.Write(_L8("\t"));   /// writing day

                  buf.Num(date2.Month());
                  //fs.Write(_L8("Month:"));
                  //fs.Write(buf);
                  //fs.Write(_L8("\t"));   /// writing month
                  
                  buf.Num(date2.Year());
                  //fs.Write(_L8("Year:"));
                  //fs.Write(buf);
                  //fs.Write(_L8("\n"));   /// writing year
                  date.Reset();

                  TLiwVariant unreadflag;
                  Map->FindL(_L8("Unread"),unreadflag);
                  TBool  unread = (TBool)unreadflag.AsTBool(); 
                  
                  
                  
                  buf.Num(unread) ;
                  //fs.Write(_L8("Unread flag :"));
                  //fs.Write(buf);
                  //fs.Write(_L8("\n"));   /// writing unread
                  unreadflag.Reset();
                  TLiwVariant priorityflag;
                  Map->FindL(_L8("Priority"),priorityflag);
                  TPtrC  priority = priorityflag.AsDes(); 
                  
                  
                  TLiwVariant bodytext;
                  Map->FindL(_L8("BodyText"),bodytext);
                  TPtrC  bodytxt = bodytext.AsDes(); 
                  bodytext.Reset();
                  
                  buf.Copy(priority)  ;
                  //fs.Write(_L8("Priority Flag :"));
                  //fs.Write(buf);
                  //fs.Write(_L8("\n"));   /// writing priority
                  priorityflag.Reset();
                  data.Reset(); /// upto here we get map by iterable list   

                  }
              //fs.Close();   
              //rfs.Close();
              
              }
           
              CActiveScheduler::Stop();
             if(0==val)
             iResult= KErrNone;
             else
             iResult= KErrGeneral;
           

    }

// -----------------------------------------------------------------------------
// Ctmsgget_async::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctmsgget_async::ExampleL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Ktmsgget_async, "tmsgget_async" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktmsgget_async, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Ktmsgget_async, 
                                KParam, i, &string );
        i++;
        }

    return KErrNone;

    }


TInt Ctmsgget_async::getlist_asyncsmsL(CStifItemParser& aItem )
   {
   iTestid = ESMS;
   __UHEAP_MARK;
   // Iter-3 test work
   CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
       
       CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
       CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
       
       CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
       crit->SetServiceClass(TUid::Uid(KLiwClassBase));
       
       RCriteriaArray a;
       
       a.AppendL(crit);    
       
       iServiceHandler->AttachL(a);
       
       iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
       
       delete crit;
       crit = NULL;
       a.Reset();
       
       TInt pos = 0;
       MLiwInterface* interface = NULL;
       _LIT8(KDataSource, "IMessaging");
       outParamList->FindFirst(pos,KDataSource );
       if(pos != KErrNotFound)
           {
           interface = (*outParamList)[pos].Value().AsInterface(); 
           }

       outParamList->Reset();
       // Iter-2 same
       inParamList->Reset();


       _LIT8(KCmd,"GetList");

    // Newly added code
       TLiwVariant content(_L("Inbox"));
       TLiwGenericParam element1 ; 
       element1.SetNameAndValueL(_L8("Type"),content);
       inParamList->AppendL(element1);
       content.Reset();
       element1.Reset();
       
       CLiwDefaultMap* map = CLiwDefaultMap::NewL();
       CleanupStack::PushL(map);

       CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
       CleanupStack::PushL(mtmtypelist);
       
       
       TLiwVariant smsmtm(KMessageTypeSMS); // how the user wud gv this param
       mtmtypelist->AppendL(smsmtm);
       smsmtm.Reset();
       TLiwVariant mmsmtm(KMessageTypeMMS);// how the user wud gv this param
       //mtmtypelist->AppendL(mmsmtm);
       mmsmtm.Reset();
       
       TLiwVariant add1(mtmtypelist);
       
       map->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
       mtmtypelist->DecRef();
       CleanupStack::Pop(mtmtypelist);
       add1.Reset(); 
       
       CLiwDefaultList* senderlist = CLiwDefaultList::NewL();
       CleanupStack::PushL(senderlist);
              
       HBufC* address1 = HBufC::NewL(20)   ;
       CleanupStack::PushL(address1);
       address1->Des().Copy(_L("9008032761"));
       TLiwVariant addres1(address1);
       //senderlist->AppendL(addres1);
       addres1.Reset();
       CleanupStack::PopAndDestroy(address1);

       TLiwVariant from(senderlist);
       map->InsertL(_L8("SenderList"),from); // Sender list
       from.Reset();

      CleanupStack::Pop(senderlist);
      senderlist->DecRef();
              
              
              

      TDateTime start(2009,EJanuary,22,0,0,0,0);
      TTime startdate(start);
      TLiwVariant date1(startdate);
      map->InsertL(_L8("StartDate"),date1);
      date1.Reset();
      
      TDateTime end(2010,EDecember,23,0,0,0,0);
      TTime enddate(end) ; 
      TLiwVariant date2(enddate);
      map->InsertL(_L8("EndDate"),date2);
      date2.Reset();
      TLiwVariant filterparam(map);
      TLiwGenericParam element ;  
      element.SetNameAndValueL(_L8("Filter"),filterparam);
      filterparam.Reset();
   
   
     inParamList->AppendL(element);
     element.Reset();
     map->DecRef();
     CleanupStack::Pop(map);
     
     CLiwDefaultMap* sortmap = CLiwDefaultMap::NewL();
      CleanupStack::PushL(sortmap);
      
      HBufC* sort1 = HBufC::NewL(20)  ;
      CleanupStack::PushL(sort1);
      sort1->Des().Copy(_L("Date"));
      TLiwVariant sort(sort1);
      sortmap->InsertL(_L8("Key"), sort);
      sort.Reset();
      CleanupStack::PopAndDestroy(sort1);

   
      HBufC* order1 = HBufC::NewL(20) ;
      CleanupStack::PushL(order1);
      order1->Des().Copy(_L("Ascending"));
      TLiwVariant order(order1);
      sortmap->InsertL(_L8("Order"), order);
      order.Reset();
      CleanupStack::PopAndDestroy(order1);
      

      TLiwVariant sortordermap(sortmap);
      TLiwGenericParam element2 ; 
      element2.SetNameAndValueL(_L8("SortOrder"),sortordermap);
      sortordermap.Reset();
      
      
      inParamList->AppendL(element2);
      element2.Reset();
      
      
      sortmap->DecRef();
      CleanupStack::Pop(sortmap);
      
     
     interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,KLiwOptASyncronous,this);
     pos = 0 ;
     const TLiwGenericParam* errcode=outParamList->FindFirst(pos,KErrCode);
     TInt err = errcode->Value().AsTInt32();
     if(!err)
        CActiveScheduler::Start();
     else
        iResult = KErrGeneral;
   
    TInt index=0;

    interface->Close();
    iServiceHandler->Reset();
    delete iServiceHandler;

    __UHEAP_MARKEND;    

    if(0 == iResult)
     return KErrNone;
    else
     return KErrGeneral;
       

   }

TInt Ctmsgget_async::getlist_asyncmmsL(CStifItemParser& aItem )
   {
   iTestid = EMMS;
   __UHEAP_MARK;
   // Iter-3 test work
   CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
       
       CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
       CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
       
       CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
       crit->SetServiceClass(TUid::Uid(KLiwClassBase));
       
       RCriteriaArray a;
       
       a.AppendL(crit);    
       
       iServiceHandler->AttachL(a);
       
       iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
       
       delete crit;
       crit = NULL;
       a.Reset();
       
       TInt pos = 0;
       MLiwInterface* interface = NULL;
       _LIT8(KDataSource, "IMessaging");
       outParamList->FindFirst(pos,KDataSource );
       if(pos != KErrNotFound)
           {
           interface = (*outParamList)[pos].Value().AsInterface(); 
           }

       outParamList->Reset();
       // Iter-2 same
       inParamList->Reset();


       _LIT8(KCmd,"GetList");

    // Newly added code
       TLiwVariant content(_L("Inbox"));
       TLiwGenericParam element1 ; 
       element1.SetNameAndValueL(_L8("Type"),content);
       inParamList->AppendL(element1);
       content.Reset();
       element1.Reset();
       
       CLiwDefaultMap* map = CLiwDefaultMap::NewL();
       CleanupStack::PushL(map);

       CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
       CleanupStack::PushL(mtmtypelist);
       
       TLiwVariant mmsmtm(KMessageTypeMMS);// how the user wud gv this param
       mtmtypelist->AppendL(mmsmtm);
       mmsmtm.Reset();
       
       TLiwVariant add1(mtmtypelist);
       
       map->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
       mtmtypelist->DecRef();
       CleanupStack::Pop(mtmtypelist);
       add1.Reset(); 
       
       CLiwDefaultList* senderlist = CLiwDefaultList::NewL();
       CleanupStack::PushL(senderlist);
              
       HBufC* address1 = HBufC::NewL(20)   ;
       CleanupStack::PushL(address1);
       address1->Des().Copy(_L("9008032761"));
       TLiwVariant addres1(address1);
       //senderlist->AppendL(addres1);
       addres1.Reset();
       CleanupStack::PopAndDestroy(address1);

       TLiwVariant from(senderlist);
       map->InsertL(_L8("SenderList"),from); // Sender list
       from.Reset();

      CleanupStack::Pop(senderlist);
      senderlist->DecRef();
              
              
              

      TDateTime start(2009,EJanuary,22,0,0,0,0);
      TTime startdate(start);
      TLiwVariant date1(startdate);
      map->InsertL(_L8("StartDate"),date1);
      date1.Reset();
      
      TDateTime end(2010,EDecember,23,0,0,0,0);
      TTime enddate(end) ; 
      TLiwVariant date2(enddate);
      map->InsertL(_L8("EndDate"),date2);
      date2.Reset();
      TLiwVariant filterparam(map);
      TLiwGenericParam element ;  
      element.SetNameAndValueL(_L8("Filter"),filterparam);
      filterparam.Reset();
   
   
     inParamList->AppendL(element);
     element.Reset();
     map->DecRef();
     CleanupStack::Pop(map);
     
     CLiwDefaultMap* sortmap = CLiwDefaultMap::NewL();
      CleanupStack::PushL(sortmap);
      
      HBufC* sort1 = HBufC::NewL(20)  ;
      CleanupStack::PushL(sort1);
      sort1->Des().Copy(_L("Date"));
      TLiwVariant sort(sort1);
      sortmap->InsertL(_L8("Key"), sort);
      sort.Reset();
      CleanupStack::PopAndDestroy(sort1);

   
      HBufC* order1 = HBufC::NewL(20) ;
      CleanupStack::PushL(order1);
      order1->Des().Copy(_L("Ascending"));
      TLiwVariant order(order1);
      sortmap->InsertL(_L8("Order"), order);
      order.Reset();
      CleanupStack::PopAndDestroy(order1);
      

      TLiwVariant sortordermap(sortmap);
      TLiwGenericParam element2 ; 
      element2.SetNameAndValueL(_L8("SortOrder"),sortordermap);
      sortordermap.Reset();
      
      
      inParamList->AppendL(element2);
      element2.Reset();
      
      
      sortmap->DecRef();
      CleanupStack::Pop(sortmap);
     
     interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,KLiwOptASyncronous,this);
     pos = 0 ;
     const TLiwGenericParam* errcode=outParamList->FindFirst(pos,KErrCode);
     TInt err = errcode->Value().AsTInt32();
     if(!err)
        CActiveScheduler::Start();
     else
        iResult = KErrGeneral;
   
    TInt index=0;

    interface->Close();
    iServiceHandler->Reset();
    delete iServiceHandler;

    __UHEAP_MARKEND;    

    if(0 == iResult)
     return KErrNone;
    else
     return KErrGeneral;
       

   }


TInt Ctmsgget_async::getlist_asyncstressL(CStifItemParser& aItem )
   {
   iTestid = ESMS;
   __UHEAP_MARK;
   // Iter-3 test work
   CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
       
       CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
       CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
       
       CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
       crit->SetServiceClass(TUid::Uid(KLiwClassBase));
       
       RCriteriaArray a;
       
       a.AppendL(crit);    
       
       iServiceHandler->AttachL(a);
       
       iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
       
       delete crit;
       crit = NULL;
       a.Reset();
       
       TInt pos = 0;
       MLiwInterface* interface = NULL;
       _LIT8(KDataSource, "IMessaging");
       outParamList->FindFirst(pos,KDataSource );
       if(pos != KErrNotFound)
           {
           interface = (*outParamList)[pos].Value().AsInterface(); 
           }

       outParamList->Reset();
       // Iter-2 same
       inParamList->Reset();


       _LIT8(KCmd,"GetList");

    // Newly added code
       TLiwVariant content(_L("Inbox"));
       TLiwGenericParam element1 ; 
       element1.SetNameAndValueL(_L8("Type"),content);
       inParamList->AppendL(element1);
       content.Reset();
       element1.Reset();
       
       CLiwDefaultMap* map = CLiwDefaultMap::NewL();
       CleanupStack::PushL(map);

       CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
       CleanupStack::PushL(mtmtypelist);
       
       
       TLiwVariant smsmtm(KMessageTypeSMS); // how the user wud gv this param
       mtmtypelist->AppendL(smsmtm);
       smsmtm.Reset();
       TLiwVariant mmsmtm(KMessageTypeMMS);// how the user wud gv this param
       //mtmtypelist->AppendL(mmsmtm);
       mmsmtm.Reset();
       
       TLiwVariant add1(mtmtypelist);
       
       map->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
       mtmtypelist->DecRef();
       CleanupStack::Pop(mtmtypelist);
       add1.Reset(); 
       
       CLiwDefaultList* senderlist = CLiwDefaultList::NewL();
       CleanupStack::PushL(senderlist);
              
       HBufC* address1 = HBufC::NewL(20)   ;
       CleanupStack::PushL(address1);
       address1->Des().Copy(_L("9008032761"));
       TLiwVariant addres1(address1);
       //senderlist->AppendL(addres1);
       addres1.Reset();
       CleanupStack::PopAndDestroy(address1);

       TLiwVariant from(senderlist);
       map->InsertL(_L8("SenderList"),from); // Sender list
       from.Reset();

      CleanupStack::Pop(senderlist);
      senderlist->DecRef();
              
              
              

      TDateTime start(2009,EJanuary,22,0,0,0,0);
      TTime startdate(start);
      TLiwVariant date1(startdate);
      map->InsertL(_L8("StartDate"),date1);
      date1.Reset();
      
      TDateTime end(2010,EDecember,23,0,0,0,0);
      TTime enddate(end) ; 
      TLiwVariant date2(enddate);
      map->InsertL(_L8("EndDate"),date2);
      date2.Reset();
      TLiwVariant filterparam(map);
      TLiwGenericParam element ;  
      element.SetNameAndValueL(_L8("Filter"),filterparam);
      filterparam.Reset();
   
   
     inParamList->AppendL(element);
     element.Reset();
     map->DecRef();
     CleanupStack::Pop(map);
     
     CLiwDefaultMap* sortmap = CLiwDefaultMap::NewL();
      CleanupStack::PushL(sortmap);
      
      HBufC* sort1 = HBufC::NewL(20)  ;
      CleanupStack::PushL(sort1);
      sort1->Des().Copy(_L("Date"));
      TLiwVariant sort(sort1);
      sortmap->InsertL(_L8("Key"), sort);
      sort.Reset();
      CleanupStack::PopAndDestroy(sort1);

   
      HBufC* order1 = HBufC::NewL(20) ;
      CleanupStack::PushL(order1);
      order1->Des().Copy(_L("Ascending"));
      TLiwVariant order(order1);
      sortmap->InsertL(_L8("Order"), order);
      order.Reset();
      CleanupStack::PopAndDestroy(order1);
      

      TLiwVariant sortordermap(sortmap);
      TLiwGenericParam element2 ; 
      element2.SetNameAndValueL(_L8("SortOrder"),sortordermap);
      sortordermap.Reset();
      
      
      inParamList->AppendL(element2);
      element2.Reset();
      
      
      sortmap->DecRef();
      CleanupStack::Pop(sortmap);
      TInt i=0;
      pos = 0 ;
     for(i=0;i<20;i++)
     {
     interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,KLiwOptASyncronous,this);
     
     const TLiwGenericParam* errcode=outParamList->FindFirst(pos,KErrCode);
     TInt err = errcode->Value().AsTInt32();
     if(!err)
        CActiveScheduler::Start();
     else
        iResult = KErrGeneral;
     }
   
    TInt index=0;

    interface->Close();
    iServiceHandler->Reset();
    delete iServiceHandler;

    __UHEAP_MARKEND;    

    if(0 == iResult)
     return KErrNone;
    else
     return KErrGeneral;
       

   }

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  [End of File] - Do not remove
