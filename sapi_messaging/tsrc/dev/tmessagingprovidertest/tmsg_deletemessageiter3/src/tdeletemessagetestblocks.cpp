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
#include <msvids.h> 
////#include <senduiconsts.h>
#include <LiwCommon.h>
#include "messaginginterface.h"
#include<LiwServiceHandler.h>

#include "TDeleteMessageTest.h"

// -----------------------------------------------------------------------------
// CTDeleteMessageTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTDeleteMessageTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTDeleteMessageTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTDeleteMessageTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        
        ENTRY( "DeleteMessageInvalid",    CTDeleteMessageTest::DeleteMessageInvalid),
        ENTRY( "DeleteMessageSms",    CTDeleteMessageTest::DeleteMessageSms),
        ENTRY( "DeleteMessageMms",    CTDeleteMessageTest::DeleteMessageMms),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

_LIT8(KTestInterface, 	"IMessaging");
_LIT8(KTestContent,		"Service.Messaging");
_LIT8(KCmd,				"Delete");
_LIT8(KErrorCode,		"ErrorCode");


_LIT8(KCmdGetHeaderList,	"GetList");

_LIT8(KFilter,				"Filter");
_LIT8(KMessageList,			"MessageList" );

_LIT8(KMessageId,"MessageId");


_LIT(KMsgTypeSMS, 	"SMS");
_LIT(KMsgTypeMMS, 	"MMS");

     
TInt  CTDeleteMessageTest::DeleteMessageInvalid(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
	CleanupStack::PushL(iServiceHandler);
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	TInt 	err = KErrNone; 
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	delete crit;
	a.Reset();
	
	TInt pos = 0;
	MLiwInterface* interface = NULL;
	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();
	if(interface)
		{
		TLiwGenericParam msgid;
		TLiwVariant  msgidvalue;
		
		msgidvalue.Set(-1);
		msgid.SetNameAndValueL(KMessageId,msgidvalue);

		inparam->AppendL(msgid);

		msgid.Reset();
		msgidvalue.Reset();

		TRAP(err,	interface->ExecuteCmdL(KCmd,*inparam,*outparam));
		
		TInt32 returnerr = 0;
		pos = 0;
		outparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
			if( (*outparam)[pos].Value().AsTInt32() != KErrNone )
				err = (TInt)((*outparam)[pos].Value().AsTInt32());
			}
		
		interface->Close();
		outparam->Reset();
		inparam->Reset();
		}

	CleanupStack::PopAndDestroy(iServiceHandler);

	__UHEAP_MARKEND;
	
	if (err != KErrNone)
		return KErrNone;
	else
		return KErrGeneral;
	}


TInt  CTDeleteMessageTest::DeleteMessageSms(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	TInt result = KErrNone;
   // RFile fs;
   // RFs rFs;
   // rFs.Connect();
   // rFs.Delete(_L("c:\\logfile_deletesms.txt")); 
   // fs.Create(rFs, _L("c:\\logfile_deletesms.txt"), EFileShareExclusive|EFileWrite)  ;
    //fs.Write(_L8("Started"));

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
	CleanupStack::PushL(iServiceHandler);
	CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;
	MLiwInterface* interface = NULL;
	outParamList->FindFirst(pos,KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outParamList)[pos].Value().AsInterface();	
		}

	outParamList->Reset();
	inParamList->Reset();

	if( interface )
		{
		pos =0;
	    TLiwVariant content(_L("Inbox"));
		TLiwGenericParam elem ;	
		elem.SetNameAndValueL(_L8("Type"),content);
		inParamList->AppendL(elem);
		content.Reset();
		elem.Reset();
			
	   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
	    CleanupStack::PushL(mtmtypelist);
	    
	    
	    TLiwVariant smsmtm(KMsgTypeSMS); // how the user wud gv this param
	    mtmtypelist->AppendL(smsmtm);
	    smsmtm.Reset();
	    
	    TLiwVariant add1(mtmtypelist);
	    
	    map->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
	    mtmtypelist->DecRef();
	    CleanupStack::Pop(mtmtypelist);
	    add1.Reset();	
    

	    TLiwVariant filterparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(_L8("Filter"),filterparam);
		filterparam.Reset();
		
		
		inParamList->AppendL(element);
		element.Reset();
		
	    map->DecRef();
	    CleanupStack::Pop(map);
	    

		TInt err = 0;
		TRAP(err,interface->ExecuteCmdL( KCmdGetHeaderList ,*inParamList ,*outParamList));
	    pos = 0 ;
	    
	    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	
		TInt32  testmessageid = 0;
		
		if(output)     
			{
			CLiwIterable* iterlist = output->Value().AsIterable();

	      	if(iterlist)
	      		{
			    TLiwVariant data;
	      		if(iterlist->NextL(data))
	      			{
					const CLiwMap* Map = data.AsMap(); 
					if ( Map )
						{
						TLiwVariant messageid;
						Map->FindL(_L8("MessageId"),messageid);
				    	testmessageid = (TInt)messageid.AsTInt32();
						messageid.Reset();
						}
	      			}
	      		data.Reset();  
	      		}
			}
		inParamList->Reset();
		outParamList->Reset();
		
    	//fs.Write(_L8("Got messageid = "));
    	TBuf8<50> tmpBuf;
    	tmpBuf.Num(testmessageid);
    	//fs.Write(_L8("Got messageid = "));
    	//fs.Write(tmpBuf);
    	//fs.Flush();
		
		if(testmessageid > 0)
			{
			TLiwGenericParam msgid;
			TLiwVariant  msgidvalue;
		
			msgidvalue.Set(testmessageid);
			msgid.SetNameAndValueL(KMessageId,msgidvalue);
			
			inParamList->AppendL(msgid);
			
			msgid.Reset();
			msgidvalue.Reset();

    	//fs.Write(_L8("Before delete"));
    	//fs.Flush();
			interface->ExecuteCmdL(KCmd,*inParamList,*outParamList);
    	//fs.Write(_L8("After delete"));
    	//fs.Flush();
			
			inParamList->Reset();
			outParamList->Reset();
			

		    TLiwVariant content(_L("Inbox"));
			TLiwGenericParam elem ;	
			elem.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(elem);
			content.Reset();
			elem.Reset();
			
		   	CLiwDefaultMap* filtermap = CLiwDefaultMap::NewL();
			CleanupStack::PushL(filtermap);

		    TLiwVariant filterid( testmessageid );
		    map->InsertL(KMessageId, filterid); // Mtmtype is added
		    filterid.Reset();	
	    

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
			
		    map->DecRef();
		    CleanupStack::Pop(map);
		    
    	//fs.Write(_L8("Before HeaderList"));
    	//fs.Flush();

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( KCmdGetHeaderList ,*inParamList ,*outParamList));
		    pos = 0 ;
			
    	//fs.Write(_L8("After HeaderList"));
    	//fs.Flush();
			
		    const TLiwGenericParam* finaloutput = outParamList->FindFirst( pos,_L8("ReturnValue"));
		
			if ( finaloutput )     
				{
				CLiwIterable* iterlist = finaloutput->Value().AsIterable();

    	//fs.Write(_L8("Got Iterable"));
    	//fs.Flush();

		      	if(iterlist)
		      		{
				    TLiwVariant data;

		      		if ( iterlist->NextL(data) )
		      			result = KErrGeneral;	
		      		
    	//fs.Write(_L8("Before reset"));
    	//fs.Flush();
		      		data.Reset();  

		      		}
				}
				
    	//fs.Write(_L8("Before param reset"));
    	//fs.Flush();
			inParamList->Reset();
			outParamList->Reset();
			}
		
		}
    	//fs.Write(_L8("Before Interface reset"));
    	//fs.Flush();
	
	interface->Close();
    	//fs.Write(_L8("After interface close"));
    	//fs.Flush();
    	
    //fs.Close();	
    //rFs.Close();	
	
	CleanupStack::PopAndDestroy( iServiceHandler );
	
	__UHEAP_MARKEND;
	
	return result;
	
	}
	
	
TInt  CTDeleteMessageTest::DeleteMessageMms(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	TInt result = KErrNone;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
	CleanupStack::PushL(iServiceHandler);
	CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;
	MLiwInterface* interface = NULL;
	outParamList->FindFirst(pos,KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outParamList)[pos].Value().AsInterface();	
		}

	outParamList->Reset();
	inParamList->Reset();

	if( interface )
		{
		pos =0;
	    TLiwVariant content(_L("Inbox"));
		TLiwGenericParam elem ;	
		elem.SetNameAndValueL(_L8("Type"),content);
		inParamList->AppendL(elem);
		content.Reset();
		elem.Reset();
			
	   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
	    CleanupStack::PushL(mtmtypelist);
	    
	    
	    TLiwVariant smsmtm(KMsgTypeMMS); // how the user wud gv this param
	    mtmtypelist->AppendL(smsmtm);
	    smsmtm.Reset();
	    
	    TLiwVariant add1(mtmtypelist);
	    
	    map->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
	    mtmtypelist->DecRef();
	    CleanupStack::Pop(mtmtypelist);
	    add1.Reset();	
    

	    TLiwVariant filterparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(_L8("Filter"),filterparam);
		filterparam.Reset();
		
		
		inParamList->AppendL(element);
		element.Reset();
		
	    map->DecRef();
	    CleanupStack::Pop(map);
	    

		TInt err = 0;
		TRAP(err,interface->ExecuteCmdL( KCmdGetHeaderList ,*inParamList ,*outParamList));
	    pos = 0 ;
	    
	    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	
		TInt32  testmessageid = 0;
		
		if(output)     
			{
			CLiwIterable* iterlist = output->Value().AsIterable();

	      	if(iterlist)
	      		{
			    TLiwVariant data;
	      		if(iterlist->NextL(data))
	      			{
					const CLiwMap* Map = data.AsMap(); 
					if ( Map )
						{
						TLiwVariant messageid;
						Map->FindL(_L8("MessageId"),messageid);
				    	testmessageid = (TInt)messageid.AsTInt32();
						messageid.Reset();
						}
	      			}
	      		data.Reset();  
	      		}
			}
		inParamList->Reset();
		outParamList->Reset();
		
		if(testmessageid > 0)
			{
			TLiwGenericParam msgid;
			TLiwVariant  msgidvalue;
		
			msgidvalue.Set(testmessageid);
			msgid.SetNameAndValueL(KMessageId,msgidvalue);
			
			inParamList->AppendL(msgid);
			
			msgid.Reset();
			msgidvalue.Reset();

			interface->ExecuteCmdL(KCmd,*inParamList,*outParamList);
			
			inParamList->Reset();
			outParamList->Reset();
			
			
		    TLiwVariant content(_L("Inbox"));
			TLiwGenericParam elem ;	
			elem.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(elem);
			content.Reset();
			elem.Reset();
				
		   	CLiwDefaultMap* filtermap = CLiwDefaultMap::NewL();
			CleanupStack::PushL(filtermap);

		    TLiwVariant filterid( testmessageid );
		    map->InsertL(KMessageId, filterid); // Mtmtype is added
		    filterid.Reset();	
	    

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
			
		    map->DecRef();
		    CleanupStack::Pop(map);
		    

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( KCmdGetHeaderList ,*inParamList ,*outParamList));
		    pos = 0 ;
			
			
		    const TLiwGenericParam* finaloutput = outParamList->FindFirst( pos,_L8("ReturnValue"));
		
			if ( finaloutput )     
				{
				CLiwIterable* iterlist = finaloutput->Value().AsIterable();

		      	if(iterlist)
		      		{
				    TLiwVariant data;

		      		if ( iterlist->NextL(data) )
		      			result = KErrGeneral;	
		      		
		      		data.Reset();  

		      		}
				}
				
			inParamList->Reset();
			outParamList->Reset();
			}
		}
	
	interface->Close();
	
	CleanupStack::PopAndDestroy( iServiceHandler );
	
	__UHEAP_MARKEND;
	
	return result;
	}

