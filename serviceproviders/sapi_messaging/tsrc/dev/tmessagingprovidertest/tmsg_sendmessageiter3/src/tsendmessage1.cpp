/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

 
// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <e32base.h>
////#include <senduiconsts.h>
#include "messaginginterface.h"
#include <BADESCA.H>
#include "sendmessage.h"
#include <f32file.h>
#include "messageheader.h"
#include<LiwServiceHandler.h>
#ifdef MAIN
#define sendmessage_test1 main
#endif

TInt32 GetTemplateId(MLiwInterface *aObj ,CLiwGenericParamList* aInputlist, CLiwGenericParamList* aOutputlist, TBool aSMS );

_LIT8(KService, 		"Service.Messaging");
_LIT8(KIDataSource,		"IMessaging");
_LIT8(KCmd,				"Send");
_LIT8(KTo,				"To");
_LIT8(KBodyText,		"BodyText");
_LIT8(KAttachmentname,	"Attachment");
_LIT8(KMimeType,		"MimeType");
_LIT8(KMessageParam,	"MessageParam");
_LIT8(KType,            "MessageType");
_LIT8(KErrCode,"ErrorCode");

// Positive test case with Type, Number and BodyText
int sendmessage_test1(int, char**)
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
	
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText for Positional Param") )));

		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
		map->DecRef();
		CleanupStack::Pop(map);
	
	TRAPD(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}
	
	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

// Negative test case with Type, Number and BodyText + Subject(NotSuported for SMS)
int sendmessage_test2(int, char**)
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
	
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText for Positional Param") )));
	inParamList->AppendL(TLiwGenericParam( _L8("Subject"), TLiwVariant( _L("SMS Subject") )));
	
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
		map->DecRef();
		CleanupStack::Pop(map);

	TRAPD(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}

	if( err == 1004 )
		err = KErrNone;
	else
		err = KErrGeneral;
	
	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

// Negative test case with Type, Number and BodyText + Attachment(NotSuported for SMS)
int sendmessage_test3(int, char**)
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
	
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText for Positional Param") )));
	inParamList->AppendL(TLiwGenericParam( _L8("Subject"), TLiwVariant( _L("") )));// Null Subject
	inParamList->AppendL(TLiwGenericParam( _L8("Attachment"), TLiwVariant( _L("C:\\Data\\Images\\test1.jpg") )));// Null Subject
	inParamList->AppendL(TLiwGenericParam( _L8("MimeType"), TLiwVariant( _L("image/jpg") )));// Null Subject

		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
		map->DecRef();
		CleanupStack::Pop(map);
	
	TRAPD(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

// Positive test case with Type, Number and BodyText + TemplateId
int sendmessage_test4(int, char**)
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
	
	TInt32 tmplateId = GetTemplateId(interface, inParamList, outParamList, ETrue );
	
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText for Positional Param") )));
	inParamList->AppendL(TLiwGenericParam( _L8("Subject"), TLiwVariant( _L("") )));// Null Subject
	inParamList->AppendL(TLiwGenericParam( _L8("Attachment"), TLiwVariant( _L("") )));// Null attachment name
	inParamList->AppendL(TLiwGenericParam( _L8("MimeType"), TLiwVariant( _L("") )));// Null mimetype
	
	if(tmplateId > 0)
		{
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);
		
		TLiwVariant liwmessageid(tmplateId);
		map->InsertL(_L8("TemplateId"),liwmessageid);
		liwmessageid.Reset();

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));// Null mimetype
		map->DecRef();
		CleanupStack::Pop(map);
		}

	TRAPD(err,interface->ExecuteCmdL( KCmd, *inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

// Positive test case with Type, Number and BodyText + TemplateId of MMS
int sendmessage_test5(int, char**)
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
	
	TInt32 tmplateId = GetTemplateId( interface, inParamList, outParamList, EFalse );
	
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("BodyText for Positional Param") )));
	inParamList->AppendL(TLiwGenericParam( _L8("Subject"), TLiwVariant( _L("Subject") )));// Null Subject
	inParamList->AppendL(TLiwGenericParam( _L8("Attachment"), TLiwVariant( _L("") )));// Null attachment name
	inParamList->AppendL(TLiwGenericParam( _L8("MimeType"), TLiwVariant( _L("") )));// Null mimetype
	
	if(tmplateId > 0)
		{
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);
		
		TLiwVariant liwmessageid(tmplateId);
		map->InsertL(_L8("TemplateId"),liwmessageid);
		liwmessageid.Reset();

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));// Null mimetype
		map->DecRef();
		CleanupStack::Pop(map);
		}

	TRAPD(err,interface->ExecuteCmdL( KCmd, *inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}
 		
	if(err == 1004)
		err = KErrNone;

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

// Positive test case with Type, Number, BodyText and Subject
int sendmessage_test6(int, char**)
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
	
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("MMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L(" BodyText for MMS ") )));
	inParamList->AppendL(TLiwGenericParam( _L8("Subject"), TLiwVariant( _L("MMS Subject") )));
	
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
		map->DecRef();
		CleanupStack::Pop(map);

	TRAPD(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}
	
	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

// Negative test case with Type, Number and BodyText + Subject with one attachment on root level
int sendmessage_test7(int, char**)
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
	
	inParamList->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("MMS") )));
	inParamList->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("MMS with one attachment on root level") )));
	inParamList->AppendL(TLiwGenericParam( _L8("Subject"), TLiwVariant( _L("MMS Subject") )));
	inParamList->AppendL(TLiwGenericParam( _L8("Attachment"), TLiwVariant( _L("C:\\Data\\Images\\test1.jpg") )));// Null Subject
	inParamList->AppendL(TLiwGenericParam( _L8("MimeType"), TLiwVariant( _L("image/jpg") )));// Null Subject
	
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( _L8("MessageParam"), TLiwVariant( map )));
		map->DecRef();
		CleanupStack::Pop(map);

	TRAPD(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

// Positive test case with Type, Number and BodyText + Attachment with one attachment on root level and one in MessageParam
int sendmessage_test8(int, char**)
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
	
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("MMS") )));
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("MMS with 2 attach. One at root level and one inside MessageParam") )));
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("MMS Subject") )));// Null Subject
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("C:\\Data\\Images\\test1.jpg") )));// Null Subject
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("image/jpg") )));// Null Subject

	{
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
		attachmentlist->AppendL(attachment1);
		attachment1.Reset();
		
	    TLiwVariant attachments(attachmentlist);
	     //attachment list added to message info ,map  
		map->InsertL(_L8("AttachmentList"),attachments);
	    attachments.Reset();
	    attachmentlist->DecRef();
		CleanupStack::Pop(attachmentlist);	
		attachmentmap1->DecRef();    
	    CleanupStack::Pop(attachmentmap1);

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( map )));// Null mimetype
		map->DecRef();
		CleanupStack::Pop(map);
	}
	
	TRAPD(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

// Positive test case with Type, Number and BodyText + TemplateId
int sendmessage_test9(int, char**)
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
	
	TInt32 tmplateId = GetTemplateId(interface, inParamList, outParamList, ETrue );
	
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("MMS") )));
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("MMS with SMS template id ") )));
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("MMS Subject") )));// Null Subject
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("") )));// Null attachment name
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("") )));// Null mimetype
	
	if(tmplateId > 0)
		{
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);
		
		TLiwVariant liwmessageid(tmplateId);
		map->InsertL(_L8("TemplateId"),liwmessageid);
		liwmessageid.Reset();

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( map )));// Null mimetype
		map->DecRef();
		CleanupStack::Pop(map);
		}

	TRAPD(err,interface->ExecuteCmdL( KCmd, *inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

// Positive test case with Type, Number and BodyText + TemplateId of MMS
int sendmessage_test10(int, char**)
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
	
	TInt32 tmplateId = GetTemplateId( interface, inParamList, outParamList, EFalse );
	
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("MMS") )));
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("9008032761") )));
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("MMS with MMS template ID ") )));
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("Subject") )));// Null Subject
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("") )));// Null attachment name
	inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( _L("") )));// Null mimetype
	
	if(tmplateId > 0)
		{
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);
		
		TLiwVariant liwmessageid(tmplateId);
		map->InsertL(_L8("TemplateId"),liwmessageid);
		liwmessageid.Reset();

		CLiwDefaultList* reclist = CLiwDefaultList::NewL();	
	  	CleanupStack::PushL(reclist);	
		reclist->AppendL(TLiwVariant(_L("9008032762")));
		
	    TLiwVariant recps(reclist);
		map->InsertL(_L8("To"),recps);
	    recps.Reset();
	    reclist->DecRef();
		CleanupStack::Pop(reclist);	
	     
		inParamList->AppendL(TLiwGenericParam( KNullDesC8, TLiwVariant( map )));// Null mimetype
		map->DecRef();
		CleanupStack::Pop(map);
		}

	TRAPD(err,interface->ExecuteCmdL( KCmd, *inParamList ,*outParamList,0,NULL ));
 	
 	if(err == KErrNone)
 		{
 		TInt index = 0;
		const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
	   	err = err1->Value().AsTInt32();
 		}
 		

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
    
    return err;
	
	}

int sendmessage_test11(int, char**)
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
    
    TInt32 tmplateId = GetTemplateId( interface, inParamList, outParamList, EFalse );
    
    inParamList->AppendL(TLiwGenericParam( KType, TLiwVariant( _L("SMS") )));
    inParamList->AppendL(TLiwGenericParam( KTo, TLiwVariant( _L("9008032761") )));
    inParamList->AppendL(TLiwGenericParam( KBodyText, TLiwVariant( _L("SMS with MMS template ID ") )));
    
    
    if(tmplateId > 0)
        {
        CLiwDefaultMap* map = CLiwDefaultMap::NewL();
        CleanupStack::PushL(map);
        
        TLiwVariant liwmessageid(tmplateId);
        map->InsertL(_L8("TemplateId"),liwmessageid);
        liwmessageid.Reset();

        CLiwDefaultList* reclist = CLiwDefaultList::NewL(); 
        CleanupStack::PushL(reclist);   
        reclist->AppendL(TLiwVariant(_L("9008032762")));
        
        TLiwVariant recps(reclist);
        map->InsertL(_L8("To"),recps);
        recps.Reset();
        reclist->DecRef();
        CleanupStack::Pop(reclist); 
         
        inParamList->AppendL(TLiwGenericParam( KMessageParam, TLiwVariant( map )));// Null mimetype
        map->DecRef();
        CleanupStack::Pop(map);
        }

    TRAPD(err,interface->ExecuteCmdL( KCmd, *inParamList ,*outParamList,0,NULL ));
    
    if(err == KErrNone)
        {
        TInt index = 0;
        const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
        err = err1->Value().AsTInt32();
        }
        

    inParamList->Reset();
    outParamList->Reset();

    interface->Close();
    iServiceHandler->Reset();
    delete iServiceHandler;

    __UHEAP_MARKEND;
    if(tmplateId)
        {
        if( err==1004 )
         return KErrNone;
        else
         return KErrGeneral;
        }
    else
        return err;
    
    }

TInt32 GetTemplateId(MLiwInterface *aObj ,CLiwGenericParamList* aInputlist, CLiwGenericParamList* aOutputlist, TBool aSMS )
	{
	_LIT8(KCmd,"GetList");
	aInputlist->Reset();
	aOutputlist->Reset();

	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
    CleanupStack::PushL(mtmtypelist);
    
    TLiwVariant content(_L("Inbox"));
	TLiwGenericParam elem ;	
	elem.SetNameAndValueL(_L8("Type"),content);
	aInputlist->AppendL(elem);
	content.Reset();
	elem.Reset();

	if(aSMS)
		{
	    TLiwVariant mmsmtm(KMessageTypeSMS);// how the user wud gv this param
	    mtmtypelist->AppendL(mmsmtm);
	    mmsmtm.Reset();
		}
	else
		{
	    TLiwVariant mmsmtm(KMessageTypeMMS);// how the user wud gv this param
	    mtmtypelist->AppendL(mmsmtm);
	    mmsmtm.Reset();
		}
    
    TLiwVariant add1(mtmtypelist);
    
    map->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
    add1.Reset();	
    CleanupStack::Pop(mtmtypelist);
    mtmtypelist->DecRef();
    

    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Filter"),filterparam);
	filterparam.Reset();
	
	
	aInputlist->AppendL(element);
	element.Reset();
	
    map->DecRef();
    CleanupStack::Pop(map);

	
	TInt err ;
	TRAP(err,aObj->ExecuteCmdL( KCmd ,*aInputlist ,*aOutputlist,0,NULL ));
    TInt pos=0;
    TInt32  id = 0;
    const TLiwGenericParam* output = aOutputlist->FindFirst( pos,_L8("ReturnValue"));
    if(output)
    	{
		CLiwIterable* iterlist = output->Value().AsIterable();
		  if(iterlist)
		  	{
			TLiwVariant data1;	
			iterlist->NextL(data1);

			const CLiwMap* map1 = data1.AsMap(); 
			if (map1)
				{
				TLiwVariant messageidinput;
				if(map1->FindL(_L8("MessageId"),messageidinput))
					{
					id =  messageidinput.AsTInt32();
					messageidinput.Reset();
					data1.Reset();
					}
				messageidinput.Reset();	
				}
			data1.Reset();	
		  	}
    	}
		
	aInputlist->Reset();
	aOutputlist->Reset();
	return id;		
	}
