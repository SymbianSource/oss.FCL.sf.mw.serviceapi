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
#include <badesca.h>
#include "getheader.h"
#include <f32file.h>
#include "messageheader.h"

#ifdef MAIN
#define getheader_test3 main
#endif



int getheader_test3(int, char**)
	{
     __UHEAP_MARK;
    CMessagingService* test = (CMessagingService* ) CMessagingService::NewL() ; 
	CleanupStack::PushL(test);	

    CFilterParamInfo* filterParams = CFilterParamInfo::NewL();
    CleanupStack::PushL(filterParams);
	_LIT(Kaddr1, "9008032761");
    

  	filterParams->AddFromL(Kaddr1);
  	
   
    
    filterParams->SetSortType( EMsvSortByDate );

	filterParams->AddMtmL(_L("SMS"));
    
    
    TDateTime start(2007,EMarch,22,0,0,0,0);
    TInt startyear = start.Year();
    TInt startmonth = start.Month();
    TInt startday = start.Day();
    
    TTime startdate(start);
    
    filterParams->SetStartDateFilter(startdate);

    TDateTime end(2007,EJune,23,0,0,0,0);
    TInt endyear = end.Year();
    TInt endmonth = end.Month();
    TInt endday = end.Day();


    TTime enddate(end) ;       

	filterParams->SetEndDate(enddate);

   
    
   CMsvEntrySelection* entryselection = NULL ;
    
   TRAPD(errcode, test->GetIdListL(filterParams,0,NULL,entryselection));
   if(entryselection)
		CleanupStack::PushL(entryselection);
	if(errcode != KErrNone)
		return errcode;
	
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
		     
		     TTime temp = header->Time();
		     
		    if((header->Mtm().FindF(_L("SMS")) != KErrNotFound) && (header->From().FindF(_L("9008032761")) != KErrNotFound)
		    && (startdate <= temp && temp <= enddate ) )
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
