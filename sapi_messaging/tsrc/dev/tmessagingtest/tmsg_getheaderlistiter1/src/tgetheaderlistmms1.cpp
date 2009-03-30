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
#include "messagingservice.h"
#include <BADESCA.H>
#include "getheader.h"
#include <f32file.h>
#include "messageheader.h"
#ifdef MAIN
#define getheadermms_test1 main
#endif

int getheadermms_test1(int, char**)
	{

    __UHEAP_MARK;
    CMessagingService* test = (CMessagingService* ) CMessagingService::NewL() ; 
	CleanupStack::PushL(test);	

     CFilterParamInfo* filterParams = CFilterParamInfo::NewL();
    CleanupStack::PushL(filterParams);

	_LIT(Kaddr1, "9008032761");
    filterParams->AddFromL(Kaddr1);

    filterParams->SetSortType(EMsvSortByNone);
 
    filterParams->AddMtmL(_L("MMS"));
   _LIT(KSubject, "Hi this is MMS");
    filterParams->SetSubjectL(KSubject);

    
    CMsvEntrySelection* entryselection = NULL ;
   
  
  
   TRAPD(errcode, test->GetIdListL(filterParams,0,NULL,entryselection));

   if(errcode != KErrNone)
      return errcode;

  
   if(entryselection)
		CleanupStack::PushL(entryselection);
   

    	
	TInt index = 0;
	TInt val = 0;
	TInt iter=0;
	for(;;)
	{
		CMessageHeader* header = NULL;
		test->GetNextHeaderL(filterParams, entryselection, index, NULL, header);
		if(header)
			{
		     iter++;
		     if((header->Mtm().FindF(_L("MMS")) != KErrNotFound) && (header->From().FindF(_L("9008032761")) != KErrNotFound)
		      && (header->Subject().FindF(KSubject)) != KErrNotFound )	
		        val++;
		      
			delete header;
			}
		else
		    break;	
		
	}
	
	

    if(entryselection)
    	CleanupStack::PopAndDestroy(entryselection);
    	     
	CleanupStack::PopAndDestroy(filterParams);
    CleanupStack::PopAndDestroy(test);
     __UHEAP_MARKEND;  
	
	if(iter == val)
		return KErrNone;
	else
		return KErrGeneral;

  

	}
