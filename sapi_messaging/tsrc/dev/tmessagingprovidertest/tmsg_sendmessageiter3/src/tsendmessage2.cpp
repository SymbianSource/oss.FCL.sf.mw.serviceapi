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
#include <messaginginterface.h>
#include <BADESCA.H>
#include "sendmessage.h"
#include <f32file.h>
#include<LiwServiceHandler.h>
#include <messageheader.h>
#ifdef MAIN 
#define sendmessage_test2 main
#endif

/*

int sendmessage_test2(int, char**)
{
	__UHEAP_MARK;
    
    TInt cells = User::CountAllocCells();
    RFile fs;
    RFs rFs;
    rFs.Connect();
    rFs.Delete(_L("c:\\logfile_sendmessage2.txt")); 
    fs.Create(rFs, _L("c:\\logfile_sendmessage2.txt"), EFileShareExclusive|EFileWrite)  ;
 
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();  
      
	TBuf8<50> buf1;
	fs.Write(_L8("ServiceHandler is created"));
	
	fs.Write(_L8("\n"));	 /// writing mtm type 

    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());

    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    
	

	fs.Write(_L8("Input param list and output paramlist created"));
	
	fs.Write(_L8("\n"));	 /// writing mtm type 
    
    
    _LIT8(KService, "Service.Messaging");
    _LIT8(KIDataSource,"IMessaging");
      
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));





	fs.Write(_L8("Criteria is  created"));
	
	fs.Write(_L8("\n"));	 /// writing mtm type 
    
    RCriteriaArray a;
    a.AppendL(crit);    

	

	fs.Write(_L8("Criteria appended"));
	
	fs.Write(_L8("\n"));	 /// writing mtm type 


    iServiceHandler->AttachL(a);


	fs.Write(_L8("AttachL is called on servicehandler"));
	
	fs.Write(_L8("\n"));	 /// writing mtm type 

    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	


	fs.Write(_L8("ExecuteServiceCmdL is called"));
	
	fs.Write(_L8("\n"));	 /// writing mtm type 
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    _LIT8(KDataSource, "IMessaging");
    outParamList->FindFirst(pos,KDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
     
	
		fs.Write(_L8("interface is created"));
		
		fs.Write(_L8("\n"));	 /// writing mtm type 

        
        
        }

outParamList->Reset();
// Iter-2 same
	delete crit;
	crit = NULL;
	a.Reset();



 _LIT8(KCmd,"Send");
 
  
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);
	
    HBufC* messagetype = HBufC::NewL(4)	;
  	CleanupStack::PushL(messagetype);
  	messagetype->Des().Copy(_L("MMS"));
    TLiwGenericParam element1 ;
    TLiwVariant  type(messagetype);
    element1.SetNameAndValueL(_L8("MessageType"),type);
    inParamList->AppendL(element1);
    element1.Reset();
    type.Reset();
    CleanupStack::PopAndDestroy(messagetype);
  
   cells = User::CountAllocCells();
	
    CLiwDefaultList* recipientTolist = CLiwDefaultList::NewL();
    CleanupStack::PushL(recipientTolist);
   
    HBufC* address1 = HBufC::NewL(20);
    CleanupStack::PushL(address1);
    address1->Des().Copy(_L8("9008032762"));
    TLiwVariant add1(address1);
    recipientTolist->AppendL(add1);
    add1.Reset();

    HBufC* address2 = HBufC::NewL(20)	;
    CleanupStack::PushL(address2);
    address2->Des().Copy(_L8("9008032762"));
    TLiwVariant add2(address2);
    recipientTolist->AppendL(add2);
    add2.Reset();

    TLiwVariant tolist(recipientTolist);
    map->InsertL(_L8("To"),tolist);
    tolist.Reset();
    CleanupStack::PopAndDestroy(address2);
    CleanupStack::PopAndDestroy(address1);
    CleanupStack::Pop(recipientTolist);
    recipientTolist->DecRef();
    
    CLiwDefaultList* recipientCclist = CLiwDefaultList::NewL();
    CleanupStack::PushL(recipientCclist);
    
    HBufC* address3 = HBufC::NewL(20)	;
    CleanupStack::PushL(address3);
    address3->Des().Copy(_L("9008032761"));
    TLiwVariant add3(address3);
    //recipientCclist->AppendL(add3);
    add3.Reset(); 
     
    TLiwVariant cclist(recipientCclist);
    map->InsertL(_L8("Cc"),cclist);
    cclist.Reset();
    
    CleanupStack::PopAndDestroy(address3);
    CleanupStack::Pop(recipientCclist);
    recipientCclist->DecRef();
    
    
    
    HBufC* bodytext = HBufC::NewL(40)	;
    CleanupStack::PushL(bodytext);
    bodytext->Des().Copy(_L("Hi this is first MMS"));
    TLiwVariant body(bodytext);
    map->InsertL(_L8("BodyText"),body);
    body.Reset();
    CleanupStack::PopAndDestroy(bodytext);
    
    HBufC* subject = HBufC::NewL(20)	;
    CleanupStack::PushL(subject);
    subject->Des().Copy(_L(" MMS Subject "));
    TLiwVariant sub(subject);
    map->InsertL(_L8("Subject"),sub);
    sub.Reset();
    CleanupStack::PopAndDestroy(subject);
    
    
    TLiwVariant editor(EFalse);
    map->InsertL(_L8("LaunchEditor"),editor);
    editor.Reset();
    

	CLiwDefaultMap* attachmentmap1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(attachmentmap1);
	
    HBufC* filename1 = HBufC::NewL(40)	;
    CleanupStack::PushL(filename1);
    filename1->Des().Copy(_L("c:\\data\\images\\test1.jpg"));
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
    
	
	CLiwDefaultMap* attachmentmap2 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(attachmentmap2);
	
    HBufC* filename2 = HBufC::NewL(40)	;
    CleanupStack::PushL(filename2);
    filename2->Des().Copy(_L("c:\\data\\images\\test2.jpg"));
    TLiwVariant file2(filename2);
    attachmentmap2->InsertL(_L8("FileName"),file2);
    file2.Reset();    
    CleanupStack::PopAndDestroy(filename2);
    
    HBufC* mimetype2 = HBufC::NewL(20)	;
    CleanupStack::PushL(mimetype2);
    mimetype2->Des().Copy(_L("image/jpeg"));
    TLiwVariant mime2(mimetype2);
    attachmentmap2->InsertL(_L8("MimeType"),mime2);
  	mime2.Reset();
    CleanupStack::PopAndDestroy(mimetype2);

	
	//Attachemtn list containing maps
	CLiwDefaultList* attachmentlist = CLiwDefaultList::NewL();	
  	CleanupStack::PushL(attachmentlist);	
	TLiwVariant attachment1(attachmentmap1);
	attachmentlist->AppendL(attachment1);
	attachment1.Reset();

	
	
	TLiwVariant attachment2(attachmentmap2);
//	attachmentlist->AppendL(attachment2);
    attachment2.Reset();
    TLiwVariant attachments(attachmentlist);
     //attachment list added to message info ,map  
	map->InsertL(_L8("AttachmentList"),attachments);
    attachments.Reset();
    
	CleanupStack::Pop(attachmentlist);	
	attachmentlist->DecRef();
	CleanupStack::Pop(attachmentmap2);
	attachmentmap2->DecRef();
	CleanupStack::Pop(attachmentmap1);
    attachmentmap1->DecRef();    
     
    TLiwGenericParam element ;
    TLiwVariant messageparam(map);
	
	element.SetNameAndValueL(_L8("MessageParam"),messageparam);
	inParamList->AppendL(element);	
	messageparam.Reset();
	element.Reset();

	CleanupStack::Pop(map);	
	map->DecRef();
	TRAPD(err,interface->ExecuteCmdL( KCmd ,*inParamList ,*outParamList,0,NULL ));

	
	     TInt index=0;
    // TLiwVariant err1; 
    _LIT8(KErrCode,"ErrorCode");
 const TLiwGenericParam* err1 = outParamList->FindFirst(index,KErrCode);
   TInt32 errcode = err1->Value().AsTInt32();
   
  TBuf8<50> cod;
  cod.Num(TInt(errcode));
     
 	fs.Write(_L8("Error code is received: "));
	fs.Write(cod);
	fs.Write(_L8("\n"));	 /// writing mtm type     
     
    
    	fs.Close();	
	  	rFs.Close();
	  	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

	cells = User::CountAllocCells();	
	
 
    __UHEAP_MARKEND;
    
    if(errcode == 0)
    	return KErrNone;
    else
    	return KErrGeneral;
}
*/