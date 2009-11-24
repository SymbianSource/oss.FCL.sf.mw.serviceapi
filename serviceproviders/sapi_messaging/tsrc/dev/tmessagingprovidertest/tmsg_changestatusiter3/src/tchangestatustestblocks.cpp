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
#include <msvids.h> 
////#include <senduiconsts.h>
#include <liwcommon.h>
#include<liwservicehandler.h>

#include "messagingservicehandler.h"

#include "tchangestatustest.h"

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTChangeStatusTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTChangeStatusTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        
        ENTRY( "ChangeStatusSms",    CTChangeStatusTest::ChangeStatusSms),
        ENTRY( "ChangeStatusMms",    CTChangeStatusTest::ChangeStatusMms),
        ENTRY( "ChangeStatusInvalid",    CTChangeStatusTest::ChangeStatusInvalid),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

_LIT8(KTestInterface, "IMessaging");
_LIT8(KTestContent,"Service.Messaging");
_LIT8(KCmd,"ChangeStatus");
_LIT8(KMsgId,"MessageId");
_LIT8(KStatus,"Status");
_LIT8(KErrorCode,"ErrorCode");


_LIT8(KCmdGetHeaderList,	"GetList");

_LIT8(KFilter,"Filter");
_LIT8(KSenderList,"SenderList");
_LIT8(KSortOrder,	"SortOrder" );
_LIT8(KMessageList,			"MessageList" );

_LIT8(KMessageId,"MessageId");

_LIT8(KMap,"Status");
_LIT8(KMtmList,				"MessageTypeList" );
_LIT8(KUnreadFlag, 			"Unread");

_LIT(KMsgTypeSMS, 	"SMS");
_LIT(KMsgTypeMMS, 	"MMS");
_LIT(KMsgStatusUnread,	"Unread");
_LIT(KMsgStatusRead,	"Read");

TInt  CTChangeStatusTest::ChangeStatusInvalid(CStifItemParser& /*aItem*/)
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
		TLiwGenericParam msgflag;
		TLiwVariant flagval;
		
		msgidvalue.Set(-1);
		msgid.SetNameAndValueL(KMsgId,msgidvalue);

		
		flagval.Set((TDesC)KMsgStatusUnread);
		msgflag.SetNameAndValueL(KStatus,flagval);



		inparam->AppendL(msgid);

		inparam->AppendL(msgflag);
		
		msgid.Reset();
		msgidvalue.Reset();
		msgflag.Reset();
		flagval.Reset();

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
	 
	 
	 
TInt  CTChangeStatusTest::ChangeStatusSms(CStifItemParser& /*aItem*/)
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
		TBool messageunread = ETrue;
		
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
				    	testmessageid = messageid.AsTInt32();
						messageid.Reset();
						
						TLiwVariant unread;
						Map->FindL(KUnreadFlag,unread);
				    	messageunread = unread.AsTBool();
						unread.Reset();
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
			TLiwGenericParam msgflag;
			
			msgidvalue.Set(TInt32(testmessageid));
			msgid.SetNameAndValueL(KMsgId,msgidvalue);
			inParamList->AppendL(msgid);
			msgidvalue.Reset();
			msgid.Reset();
			
			if ( messageunread )
				msgflag.SetNameAndValueL(KStatus,TLiwVariant(KMsgStatusRead));
			else
				msgflag.SetNameAndValueL(KStatus,TLiwVariant(KMsgStatusUnread));
				
			inParamList->AppendL(msgflag);
			
			msgflag.Reset();

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
		    filtermap->InsertL(KMessageId, filterid); // Mtmtype is added
		    filterid.Reset();	
	    

		    TLiwVariant filterparam(filtermap);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
			
		    filtermap->DecRef();
		    CleanupStack::Pop(filtermap);
		    

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
		      			{
						const CLiwMap* Map = data.AsMap(); 
						
						if ( Map )
							{
							TLiwVariant messageid;
							Map->FindL(_L8("MessageId"),messageid);
					    	TMsvId newtestmessageid = messageid.AsTInt32();
							messageid.Reset();
							
							TLiwVariant unread;
							Map->FindL(KUnreadFlag,unread);
					    	TBool newmessageunread = unread.AsTBool();
							unread.Reset();
							
							if (( messageunread != newmessageunread) && (testmessageid == newtestmessageid ))
							 	result = KErrNone;
							else
								result = KErrGeneral;
							}
		      			}
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
	 
	 


TInt  CTChangeStatusTest::ChangeStatusMms(CStifItemParser& /*aItem*/)
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
		TBool messageunread = ETrue;
		
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
						
						TLiwVariant unread;
						Map->FindL(KUnreadFlag,unread);
				    	messageunread = unread.AsTBool();
						unread.Reset();
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
			TLiwGenericParam msgflag;
			
			msgidvalue.Set(TInt32(testmessageid));
			msgid.SetNameAndValueL(KMsgId,msgidvalue);
			inParamList->AppendL(msgid);
			msgidvalue.Reset();
			msgid.Reset();
			
			if ( messageunread )
				msgflag.SetNameAndValueL(KStatus,TLiwVariant(KMsgStatusRead));
			else
				msgflag.SetNameAndValueL(KStatus,TLiwVariant(KMsgStatusUnread));
				
			inParamList->AppendL(msgflag);
			
			msgflag.Reset();

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
		    filtermap->InsertL(KMessageId, filterid); // Mtmtype is added
		    filterid.Reset();	
	    

		    TLiwVariant filterparam(filtermap);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
			
		    filtermap->DecRef();
		    CleanupStack::Pop(filtermap);
		    

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
		      			{
						const CLiwMap* Map = data.AsMap(); 
						
						if ( Map )
							{
							TLiwVariant messageid;
							Map->FindL(_L8("MessageId"),messageid);
					    	TMsvId newtestmessageid = (TInt)messageid.AsTInt32();
							messageid.Reset();
							
							TLiwVariant unread;
							Map->FindL(KUnreadFlag,unread);
					    	TBool newmessageunread = unread.AsTBool();
							unread.Reset();
							
							if (( messageunread != newmessageunread) && (testmessageid == newtestmessageid ))
							 	result = KErrNone;
							else
								result = KErrGeneral;
							}
		      			}
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
	 
	 
	 
	 
