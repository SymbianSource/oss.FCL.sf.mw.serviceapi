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




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "getheader.h"

#include <e32base.h>
////#include <senduiconsts.h>
#include "messaginginterface.h"
#include <BADESCA.H>
#include <f32file.h>
#include<LiwServiceHandler.h>
#include<MSVSTD.H>
#include "messageheader.h"


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
// Csapi_getheader::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Csapi_getheader::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Csapi_getheader::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
       {  
		// Copy this line for every implemented function.
		// First string is the function name used in TestScripter script file.
		// Second is the actual implementation member function. 
      
       ENTRY( "t5to10asynccallsandunloadL", Csapi_getheader::t5to10asynccallsandunloadL ),
       ENTRY( "whilerandomlooprandomswitchL", Csapi_getheader::whilerandomlooprandomswitchL ),
       ENTRY( "getlistsenderlistnumberofnumbersL", Csapi_getheader::getlistsenderlistnumberofnumbersL ),
       ENTRY( "sendtolistnumberofnumbersL", Csapi_getheader::sendtolistnumberofnumbersL ),
       ENTRY( "sendcclistnumberofnumbersL", Csapi_getheader::sendcclistnumberofnumbersL ),
       ENTRY( "sendattachmentsnumberofattachments", Csapi_getheader::sendattachmentsnumberofattachments ),
       };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

class CSendLiwNotify: public MLiwNotifyCallback
	{
	TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList)
		{
		int i;
		i =10+ 100;
		++i;
		i++;
		//CActiveScheduler::Stop();
		}
	};
	
_LIT8(KService, "Service.Messaging");
_LIT8(KIDataSource,"IMessaging");

TInt Csapi_getheader::t5to10asynccallsandunloadL( CStifItemParser& aItem )
	{
	__UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);    

    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    _LIT8(KDataSource, "IMessaging");
    outParamList->FindFirst(pos,KDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete crit;
	crit = NULL;
	a.Reset();
	_LIT8( KCmd, "Send" );
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText SMS async") )));

	CSendLiwNotify* cobject = new CSendLiwNotify();
	int err = KErrNone;
	
	for( int i=0; i<5; ++i)
		{
		TRAP(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,1,cobject ));
		//CActiveScheduler::Start();
 		outParamList->Reset();		
		}
	inParamList->Reset();
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

	delete cobject; 	
	

    __UHEAP_MARKEND;
    
    return err;
	}

#include <e32math.h>	

TInt Csapi_getheader::whilerandomlooprandomswitchL( CStifItemParser& aItem )
	{
	/*
	_LIT8( KSendCmd, "Send" );
	TInt err = KErrNone;
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
	
	CLiwDefaultMap* map;
	CLiwDefaultList* reclist;
	TInt loop = 100;
	
	
	TInt divisor = 100;
	aItem.GetNextInt( divisor );
	Math m;
	TUint whilecount = ( m.Random()%divisor ) /2;
	while( whilecount-- )
		{
		TUint switchchoice = m.Random()%10;
		switch( switchchoice )
			{
				case 0: //send 100 sms 
                        inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
                        inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
                        inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText SMS Performance test") )));
                        
                        map = CLiwDefaultMap::NewL();
                        CleanupStack::PushL(map);
                        reclist = CLiwDefaultList::NewL();
                        CleanupStack::PushL(reclist);

                        TUint64 num = 9008032761;
                        TBuf<10> ccnum;
                        for( int i=0; i<loop; ++i, ++num )
                            {		
                            ccnum.Num( num );
                            reclist->AppendL(TLiwVariant( ccnum ));	
                            }
                        
                        TLiwVariant recps(reclist);
                        map->InsertL(_L8("To"),recps);
                        recps.Reset();
                        reclist->DecRef();
                        CleanupStack::Pop(reclist);	 
                        inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
                        map->DecRef();
                        CleanupStack::Pop(map);
                        
                        TRAP(err,interface->ExecuteCmdL( KSendCmd ,*inParamList ,*outParamList,0,NULL ));
                        
                        outParamList->Reset();		
                        inParamList->Reset();
                        break;
						
				case 1: //send 100 mms 
				        inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("MMS") )));
                        inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
                        inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText MMS Performance test") )));
                        
                        map = CLiwDefaultMap::NewL();
                        CleanupStack::PushL(map);
                        reclist = CLiwDefaultList::NewL();
                        CleanupStack::PushL(reclist);

                        TUint64 num1 = 9008032761;
                        TBuf<10> ccnum2;
                        for( int i=0; i<loop; ++i, ++num1 )
                            {		
                            ccnum2.Num( num1 );
                            reclist->AppendL(TLiwVariant( ccnum2 ));	
                            }
                        
                        TLiwVariant recps1(reclist);
                        map->InsertL(_L8("To"),recps);
                        recps.Reset();
                        reclist->DecRef();
                        CleanupStack::Pop(reclist);	 
                        inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
                        map->DecRef();
                        CleanupStack::Pop(map);
                        
                        TRAP(err,interface->ExecuteCmdL( KSendCmd ,*inParamList ,*outParamList,0,NULL ));
                        
                        outParamList->Reset();		
                        inParamList->Reset();
                        break;
				
				case 2: //get messages 
				        
				        break;
				        				
				case 3: //change messagestatus 
				        
				        break;
				        
				case 4: //delete message 
				        
				        
				case 5: //register notification 
				        
				        break;
				        
				case 6: //cancel notification 
				        
				        break;
				        
				case 7: //get messages with options 
				        
				        break;
				        
				case 8: //send message with 100 attachments 
                        inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("MMS") )));
                        inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
                        inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText of MMS bulk Attachments Performance") )));
                        
                        map = CLiwDefaultMap::NewL();
                        CleanupStack::PushL(map);
                        
                        
                        CLiwDefaultMap* attachmentmap1 = CLiwDefaultMap::NewL();
                        CleanupStack::PushL(attachmentmap1);	
                        HBufC* filename1 = HBufC::NewL(80)	;
                        CleanupStack::PushL(filename1);
                        filename1->Des().Copy(_L("c:\\data\\images\\Test2.jpg"));
                        TLiwVariant file1(filename1);
                        attachmentmap1->InsertL(_L8("FileName"),file1);
                        file1.Reset();
                        CleanupStack::PopAndDestroy(filename1);
                        
                        HBufC* mimetype1 = HBufC::NewL(20)	;
                        CleanupStack::PushL(mimetype1);
                        mimetype1->Des().Copy(_L("image/jpeg"));
                        TLiwVariant mime1(mimetype1);
                        attachmentmap1->InsertL(_L8("MimeType"),mime1);
                        mime1.Reset();
                        CleanupStack::PopAndDestroy(mimetype1);
                        
                        
                        CLiwDefaultList* attachmentlist = CLiwDefaultList::NewL();	
                        CleanupStack::PushL(attachmentlist);	
                        TLiwVariant attachment1(attachmentmap1);
                        
                        TInt loop = 1000;
                        aItem.GetNextInt(loop);
                        
                        for( int i=0; i<loop ; ++i )
                        	{		
                        	attachmentlist->AppendL(attachment1);
                        	}
                        attachment1.Reset();
                        
                        TLiwVariant attachments(attachmentlist);
                         //attachment list added to message info ,map  
                        map->InsertL(_L8("AttachmentList"),attachments);
                        attachments.Reset();
                        attachmentlist->DecRef();
                        CleanupStack::Pop(attachmentlist);	
                        attachmentmap1->DecRef();    
                        CleanupStack::Pop(attachmentmap1);
                        
                        inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
                        map->DecRef();
                        CleanupStack::Pop(map);
                        int err = KErrNone;	
                        TRAP(err,interface->ExecuteCmdL( KSendCmd ,*inParamList ,*outParamList,0,NULL ));
                        
                        outParamList->Reset();		
                        inParamList->Reset();
				        break;
				        
				case 9: //get messages with options 
				        
				default: 
				        break;
			}
		}	
		
	outParamList->Reset();		
	inParamList->Reset();
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;


    __UHEAP_MARKEND;
    
    return err;*/ return KErrNone;	
	}
	
TInt Csapi_getheader::getlistsenderlistnumberofnumbersL( CStifItemParser& aItem )
	{
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

    
    
    
     

    CLiwDefaultList* senderlist = CLiwDefaultList::NewL();
    CleanupStack::PushL(senderlist);
    
    TInt num = 100;
    aItem.GetNextInt(num);
    
    HBufC* address1 = HBufC::NewL(20);
    CleanupStack::PushL(address1);
    address1->Des().Copy(_L("9008032761"));
    TLiwVariant addres1(address1);
    for( int i = 0; i<num; ++i )
    	{
    	senderlist->AppendL(addres1);
    	}
    addres1.Reset();
  	CleanupStack::PopAndDestroy(address1);

    TLiwVariant from(senderlist);
    map->InsertL(_L8("SenderList"),from); // Sender list
    from.Reset();

    CleanupStack::Pop(senderlist);
    senderlist->DecRef();
    
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Filter"),filterparam);
	filterparam.Reset();
	
	
	inParamList->AppendL(element);
	element.Reset();
	
    map->DecRef();
    CleanupStack::Pop(map);

	TInt err = 0;
	TRAP(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList));
    pos = 0 ;
    
    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	
	TInt val=0;     
	if(output)     
		{
		//RFile //fs;
	    //R//fs r//fs;
	    //r//fs.Connect();
	    //r//fs.Delete(_L("c:\\getheaderiter3_1.txt")); 
	    //fs.Create(r//fs, _L("c:\\getheaderiter3_1.txt"), EFileShareExclusive|EFileWrite)  ;

		CLiwIterable* iterlist = output->Value().AsIterable();

	    TLiwVariant data;
      
        while( iterlist->NextL(data))
			{
			
			const CLiwMap* Map = data.AsMap(); 
			
			TLiwVariant mtmtype;
			Map->FindL(_L8("MessageType"),mtmtype);
			TPtrC  mtm = mtmtype.AsDes(); 
		    
		    if(mtm.FindF(_L("SMS")) == KErrNotFound )	
		      val++;
		     
			
			TBuf8<50> buf;
		    buf.Copy(mtm)	;
			//fs.Write(_L8("Mtm Id :"));
			//fs.Write(buf);
			//fs.Write(_L8("\n"));	 /// writing mtm type 
			mtmtype.Reset();
			
			TLiwVariant sender;
			Map->FindL(_L8("Sender"),sender);
			TPtrC  send = sender.AsDes(); 
			
			//if(send.FindF(_L("9008032761")) == KErrNotFound)
			//   val++;
			
			
		    buf.Copy(send)	;
			//fs.Write(_L8("Sender :"));
			//fs.Write(buf);
			//fs.Write(_L8("\n"));	 /// writing sender 
			sender.Reset();
			TLiwVariant messageid;
			Map->FindL(_L8("MessageId"),messageid);
	    	TInt  id = (TInt)messageid.AsTInt32();
	    
			
			
		    buf.Num(id)	;
			//fs.Write(_L8("Message id :"));
			//fs.Write(buf);
			//fs.Write(_L8("\n"));	 /// writing messageid
			messageid.Reset();
			
			TLiwVariant date;
			Map->FindL(_L8("Time"),date);
			
			
			TTime date1 =(TTime) date.AsTTime();
			
			
			TDateTime date2 = date1.DateTime();
		
			buf.Num(date2.Day());
			//fs.Write(_L8("Day:"));
			//fs.Write(buf);
			//fs.Write(_L8("\t"));	 /// writing day

			buf.Num(date2.Month());
			//fs.Write(_L8("Month:"));
			//fs.Write(buf);
			//fs.Write(_L8("\t"));	 /// writing month
			
			buf.Num(date2.Year());
			//fs.Write(_L8("Year:"));
			//fs.Write(buf);
			//fs.Write(_L8("\n"));	 /// writing year
			date.Reset();

			TLiwVariant unreadflag;
			Map->FindL(_L8("Unread"),unreadflag);
			TBool  unread = (TBool)unreadflag.AsTBool(); 
			
			
			
		    buf.Num(unread)	;
			//fs.Write(_L8("Unread flag :"));
			//fs.Write(buf);
			//fs.Write(_L8("\n"));	 /// writing unread
			unreadflag.Reset();
			TLiwVariant priorityflag;
			Map->FindL(_L8("Priority"),priorityflag);
			TPtrC  priority = priorityflag.AsDes(); 
			
			
			TLiwVariant bodytext;
			Map->FindL(_L8("BodyText"),bodytext);
			TPtrC  bodytxt = bodytext.AsDes(); 
			bodytext.Reset();
			
		    buf.Copy(priority)	;
			//fs.Write(_L8("Priority Flag :"));
			//fs.Write(buf);
			//fs.Write(_L8("\n"));	 /// writing priority
			priorityflag.Reset();
			data.Reset(); /// upto here we get map by iterable list   

	  		}
	  	//fs.Close();	
	  	//r//fs.Close();
		
		}
	
     TInt index=0;

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	if(0 == val)
	  return KErrNone;
	else
	  return KErrGeneral;	
	
	}
	
TInt Csapi_getheader::sendtolistnumberofnumbersL( CStifItemParser& aItem )
	{
	__UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);    

    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    _LIT8(KDataSource, "IMessaging");
    outParamList->FindFirst(pos,KDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete crit;
	crit = NULL;
	a.Reset();
	_LIT8( KCmd, "Send" );
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText SMS async") )));
	
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);
	CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
  	CleanupStack::PushL(reclist);	
	
	TInt loop = 1000;
    aItem.GetNextInt(loop);
    
	TUint64 num = 9008032762;
	TBuf<10> ccnum;
	for( int i=0; i<loop; ++i, ++num )
		{		
		ccnum.Num( num );
		reclist->AppendL(TLiwVariant( ccnum ));	
		}

	TLiwVariant recps(reclist);
	map->InsertL(_L8("To"),recps);
    recps.Reset();
    reclist->DecRef();
	CleanupStack::Pop(reclist);	 
	inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
	map->DecRef();
	CleanupStack::Pop(map);
	int err = KErrNone;	
	TRAP(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));
	
	outParamList->Reset();		
	inParamList->Reset();
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;


    __UHEAP_MARKEND;
    
    return err;
	}
	
TInt Csapi_getheader::sendcclistnumberofnumbersL( CStifItemParser& aItem )
	{
	__UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);    

    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    _LIT8(KDataSource, "IMessaging");
    outParamList->FindFirst(pos,KDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete crit;
	crit = NULL;
	a.Reset();
	_LIT8( KCmd, "Send" );
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText SMS async") )));
	
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);
	CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
  	CleanupStack::PushL(reclist);	
	
	TInt loop = 1000;
    aItem.GetNextInt(loop);
    
	TUint64 num = 9008032762;
	TBuf<10> ccnum;
	for( int i=0; i<loop; ++i, ++num )
		{		
		ccnum.Num( num );
		reclist->AppendL(TLiwVariant( ccnum ));	
		}

	TLiwVariant recps(reclist);
	map->InsertL(_L8("Cc"),recps);
    recps.Reset();
    reclist->DecRef();
	CleanupStack::Pop(reclist);	 
	inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
	map->DecRef();
	CleanupStack::Pop(map);
	int err = KErrNone;	
	TRAP(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));
	
	outParamList->Reset();		
	inParamList->Reset();
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;


    __UHEAP_MARKEND;
    
    return err;	
	}
	
TInt Csapi_getheader::sendattachmentsnumberofattachments( CStifItemParser& aItem )
	{
	__UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
      
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);    

    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    _LIT8(KDataSource, "IMessaging");
    outParamList->FindFirst(pos,KDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	delete crit;
	crit = NULL;
	a.Reset();
	_LIT8( KCmd, "Send" );
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("MMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText SMS async") )));
	
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);
	
	
	CLiwDefaultMap* attachmentmap1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(attachmentmap1);	
    HBufC* filename1 = HBufC::NewL(80)	;
    CleanupStack::PushL(filename1);
    filename1->Des().Copy(_L("c:\\data\\images\\Test2.jpg"));
    TLiwVariant file1(filename1);
    attachmentmap1->InsertL(_L8("FileName"),file1);
    file1.Reset();
    CleanupStack::PopAndDestroy(filename1);
  
    HBufC* mimetype1 = HBufC::NewL(20)	;
    CleanupStack::PushL(mimetype1);
    mimetype1->Des().Copy(_L("image/jpeg"));
    TLiwVariant mime1(mimetype1);
    attachmentmap1->InsertL(_L8("MimeType"),mime1);
    mime1.Reset();
    CleanupStack::PopAndDestroy(mimetype1);

	
	CLiwDefaultList* attachmentlist = CLiwDefaultList::NewL();	
  	CleanupStack::PushL(attachmentlist);	
	TLiwVariant attachment1(attachmentmap1);
	
	TInt loop = 1000;
    aItem.GetNextInt(loop);

	for( int i=0; i<loop ; ++i )
		{		
		attachmentlist->AppendL(attachment1);
		}
	attachment1.Reset();
	
    TLiwVariant attachments(attachmentlist);
     //attachment list added to message info ,map  
	map->InsertL(_L8("AttachmentList"),attachments);
    attachments.Reset();
    attachmentlist->DecRef();
	CleanupStack::Pop(attachmentlist);	
	attachmentmap1->DecRef();    
    CleanupStack::Pop(attachmentmap1);
	
	inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
	map->DecRef();
	CleanupStack::Pop(map);
	int err = KErrNone;	
	TRAP(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));
	
	outParamList->Reset();		
	inParamList->Reset();
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;


    __UHEAP_MARKEND;
    
    return err;	
	}
	
