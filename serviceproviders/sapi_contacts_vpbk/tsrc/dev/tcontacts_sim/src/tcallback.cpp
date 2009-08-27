/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   This Class is observer for the Launching Application
*
*/



#include <e32const.h>
#include "tcallback.h"



//#include <TPbkContactItemField.h>
//#include <CPbkFieldInfo.h>


// -----------------------------------------------------------------------------
// CCContactCallBack::NewL
// Returns the instance of CLauncherObserver.
// -----------------------------------------------------------------------------
EXPORT_C CContactCallBack* CContactCallBack::NewL(RFile* afile )
	{
	CContactCallBack* self = new( ELeave ) CContactCallBack(afile);
	
	return self;
	}


// ---------------------------------------------------------------------------
// consturctor
// ---------------------------------------------------------------------------
//
CContactCallBack::CContactCallBack(RFile* afile ):iId(NULL),iCont(NULL)
	{
	ifile = afile;
	}


CContactCallBack::~CContactCallBack()	
	{
	delete iCont;
	delete iId;
	

	}
void CContactCallBack::HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }

void CContactCallBack::HandleReturnId( const TInt& aError, HBufC8* acntId, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }
    

void CContactCallBack::HandleReturnValue(TOperationEvent aEventId, const TInt& aError, TInt aTransId )
   {
   CActiveScheduler::Stop();
   iErrCode=aError;
   TBuf8<25> filebuf;
   filebuf.Num(aError);

	//filebuf.Append(_L("\n NextL called"));
	ifile->Write(filebuf);
	filebuf.Zero();
	ifile->Flush();

    
   }

void CContactCallBack::HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId )
   {
	CActiveScheduler::Stop();
	 CSingleContact* singleContact = NULL;  
	HBufC8* buf = NULL;
	TInt count = 0; 
	iErrCode = aError;
	
	
	TBuf8<100> filebuf;
	
	while(ETrue)
		{
		aIter->NextL(singleContact,buf);
		
		filebuf.Append(_L("\n NextL called"));
		ifile->Write(filebuf);
		filebuf.Zero();
		ifile->Flush();
		
		if(singleContact)
		    {
	
		    iId = buf;

			filebuf.Append(_L("\n Id copied"));
			ifile->Write(filebuf);
			filebuf.Zero();
			ifile->Flush();
			
		    iCont = singleContact; 	

			filebuf.Append(_L("\n single contact copied"));
			ifile->Write(filebuf);
			filebuf.Zero();
		    ifile->Flush();
		    
		    TInt count(singleContact->FieldCount());

			filebuf.Append(_L("\n count calculated"));
			ifile->Write(filebuf);
			filebuf.Zero();
		    ifile->Flush();
		    while(count)
		    {
		    	
		    CSingleContactField* field = singleContact->FieldAt(--count);

			filebuf.Append(_L("\n single filed "));
			ifile->Write(filebuf);
			filebuf.Zero();
			ifile->Flush();

		    TPtrC8 fieldKey;
		    TPtrC label;
		    TPtrC value;
		    field->GetFieldDataL(fieldKey,label,value);

			filebuf.Append(_L("\n gets field value  "));
			ifile->Write(filebuf);
			filebuf.Zero();
		    ifile->Flush();
		    
			filebuf.Append(fieldKey);
			ifile->Write(filebuf);
			filebuf.Zero();
		    ifile->Flush();

	       
	        if (fieldKey == KLastName && value == KName)
		       {
		        iErrCode = KErrNone;

			filebuf.Append(_L("\n got contact item  "));
			ifile->Write(filebuf);
			filebuf.Zero();
		    ifile->Flush();    
		        }
		    else if (fieldKey == KFirstName) 
		        {
		        break;    
		        }
		  
		    }
		    
		    
		    } 

	if(!singleContact)
	    {
	    break;
	    }

	// delete singleContact;
        }
   
	if(iErrCode != KErrNone )
	{
	iErrCode = KErrNotFound;	
	}

    delete aIter;
	filebuf.Append(_L("\n iteratro deleted  "));
	ifile->Write(filebuf);
	filebuf.Zero();
	ifile->Flush();
   }
	