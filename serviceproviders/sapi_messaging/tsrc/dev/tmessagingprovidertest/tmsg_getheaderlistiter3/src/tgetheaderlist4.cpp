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

 

#include <e32base.h>
////#include <senduiconsts.h>
#include "messaginginterface.h"
#include <badesca.h>
#include "getheader.h"
#include <f32file.h>
#include<liwservicehandler.h>
#include<msvstd.h>
#include "messageheader.h"
#ifdef MAIN
#define getheader_test4 main
#endif

_LIT8(KService, "Service.Messaging");
_LIT8(KIDataSource,"IMessaging");
      

int getheader_test4(int, char**)
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
    
    HBufC* address1 = HBufC::NewL(20)	;
    CleanupStack::PushL(address1);
    address1->Des().Copy(_L("9008032761"));
    TLiwVariant addres1(address1);
    senderlist->AppendL(addres1);
    addres1.Reset();
   CleanupStack::PopAndDestroy(address1);

    TLiwVariant from(senderlist);
    map->InsertL(_L8("SenderList"),from); // Sender list
    from.Reset();

   CleanupStack::Pop(senderlist);
   senderlist->DecRef();
    
    
    HBufC* subject = HBufC::NewL(20);
    subject->Des().Copy(_L8("MMS"));
    
    TLiwVariant sub(subject);
    map->InsertL(_L8("Subject"),sub); // subject is null
    sub.Reset();
    delete subject;


    TDateTime start(2006,EJanuary,22,0,0,0,0);
    TTime startdate(start);
    TLiwVariant date1(startdate);
    map->InsertL(_L8("StartDate"),date1);
    date1.Reset();
    
    TDateTime end(2007,EDecember,23,0,0,0,0);
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
	
	HBufC* sort1 = HBufC::NewL(20)	;
    CleanupStack::PushL(sort1);
    sort1->Des().Copy(_L("Date"));
    TLiwVariant sort(sort1);
   	sortmap->InsertL(_L8("Key"), sort);
    sort.Reset();
    CleanupStack::PopAndDestroy(sort1);

 
	HBufC* order1 = HBufC::NewL(20)	;
    CleanupStack::PushL(order1);
    order1->Des().Copy(_L("Ascending"));
    TLiwVariant order(order1);
   	sortmap->InsertL(_L8("Order"), order);
    order.Reset();
    CleanupStack::PopAndDestroy(order1);
	

    TLiwVariant sortordermap(sortmap);
	TLiwGenericParam element1 ;	
	element1.SetNameAndValueL(_L8("SortOrder"),sortordermap);
	sortordermap.Reset();
	
	
	inParamList->AppendL(element1);
	element1.Reset();
	
	
    sortmap->DecRef();
    CleanupStack::Pop(sortmap);

	
    
    
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
	    //r//fs.Delete(_L("c:\\getheaderiter3_4.txt")); 
	    //fs.Create(r//fs, _L("c:\\getheaderiter3_4.txt"), EFileShareExclusive|EFileWrite)  ;

		CLiwIterable* iterlist = output->Value().AsIterable();

	    TLiwVariant data;
      
        while( iterlist->NextL(data))
			{
			
			const CLiwMap* Map = data.AsMap(); 
			
			TLiwVariant mtmtype;
			Map->FindL(_L8("MessageType"),mtmtype);
			TPtrC  mtm = mtmtype.AsDes(); 
		    
		    if(mtm.FindF(_L("MMS")) == KErrNotFound)	
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
			
			if(send.FindF(_L("9008032761")) == KErrNotFound)
			   val++;
			
			
		    buf.Copy(send)	;
			//fs.Write(_L8("Sender :"));
			//fs.Write(buf);
			//fs.Write(_L8("\n"));	 /// writing sender 
			sender.Reset();
		
			TLiwVariant subject1;
			Map->FindL(_L8("Subject"),subject1);
			TPtrC  subjectdes = subject1.AsDes(); 
			
		    if(subjectdes.FindF(_L("MMS")) == KErrNotFound)
			   val++;
	
			
		    buf.Copy(subjectdes)	;
			//fs.Write(_L8("Subject :")); /// writing subject

			//fs.Write(buf);
			//fs.Write(_L8("\n"));	
			subject1.Reset();
			
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
			
			TLiwVariant attachmentflag;
			Map->FindL(_L8("Attachment"),attachmentflag);
			TBool  attachment = (TBool)attachmentflag.AsTBool(); 
			
			
		
		    buf.Num(attachment)	;
			//fs.Write(_L8("Attachment Flag :"));
			//fs.Write(buf);
			//fs.Write(_L8("\n"));	 /// writing attachment
			attachmentflag.Reset();
		
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
