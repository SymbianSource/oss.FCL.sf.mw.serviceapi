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
#include <StifTestInterface.h>

#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>

#include "tcontactssim.h"
#include "tcallback.h"


_LIT( KCntDbUri, "cntdb://c:contacts.cdb" );

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// Csapi_getheader:RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CContactsUT::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
         ENTRY( "addcontact", CContactsUT::addcontactL ),
         ENTRY( "getlisttest", CContactsUT::getlisttestL ),
         ENTRY( "getlisttest_search", CContactsUT::getlisttest_searchL ),
         ENTRY(	"deletetest" , CContactsUT::deletetestL ),
         ENTRY(	"importtest" , CContactsUT::importL ),         
         ENTRY(	"exporttest" , CContactsUT::exportL ),         
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
// -----------------------------------------------------------------------------
// CContactsUT:addcontactL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::addcontactL( CStifItemParser& aItem  )
    {
    
  

	RFs fs;
	RFile file;  
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TInt errfile =file.Replace(fs,_L("C:\\Data\\tcontacts_addlog.txt"), EFileWrite | EFileStreamText); 
	CleanupClosePushL(file);
	
	TBuf8<100> filebuf;

	filebuf.Append(_L8("\n Starting logs"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();
	
	
	
	
	CContactService* icontactservice = CContactService::NewL();
	CleanupStack::PushL(icontactservice);
	
	CContactCallBack* callback = CContactCallBack::NewL(&file);
	CleanupStack::PushL(callback);

    CSingleContact* cont = CSingleContact::NewL();
    
    cont->SetContactIdL(KNullDesC8);
    //delete test;
    
    CSingleContactField* field =CSingleContactField::NewL();
  
    field->SetFieldParamsL(KLastName,KNullDesC,KName);	
   
    cont->AddFieldToContactL(field);


    TRAPD(err,icontactservice->AddL(callback,0,cont,KNullDesC8,KNullDesC,KCntSimDbUri));
    CActiveScheduler::Start();

	TInt result(callback->iErrCode);
	
	CleanupStack::PopAndDestroy(callback);
	CleanupStack::PopAndDestroy(icontactservice);
	CleanupStack::PopAndDestroy();
	CleanupStack::PopAndDestroy();

	

	return result;

	
    }

// -----------------------------------------------------------------------------
// CContactsUT:getlisttestL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::getlisttestL( CStifItemParser& aItem  )
    {
    
//    __UHEAP_MARK;
	
	RFs fs;
	RFile file;  
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TInt errfile =file.Replace(fs,_L("C:\\Data\\tcontacts_simlog.txt"), EFileWrite | EFileStreamText); 
	CleanupClosePushL(file);
	
	TBuf8<100> filebuf;

	filebuf.Append(_L8("\n Starting logs"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

	
	CContactService* icontactservice =  CContactService::NewL();
	CleanupStack::PushL(icontactservice);
	
	filebuf.Append(_L8("\n Service Class object created"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

	CContactCallBack* callback = CContactCallBack::NewL(&file);
	CleanupStack::PushL(callback);

	filebuf.Append(_L8("\n Callback  object created"));
	file.Write(filebuf);
	filebuf.Zero();
    file.Flush();


//For automation purpose
	_LIT(KFileName,"c:\\data\\Import.vcf");
	TBuf<50> flnm(KFileName);

   TRAPD(err,icontactservice->ImportVCardToStoreL(callback,0,flnm,KCntSimDbUri));
   	
   	filebuf.Append(_L8("\nImportVCard is called\n"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

   
   CActiveScheduler::Start(); 



	TInt result(callback->iErrCode);

   	filebuf.Num(callback->iErrCode);
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();
	
	if(result != KErrNone)
	return result;



    TRAPD(err1,icontactservice->GetListL(callback,0,EContacts,KNullDesC8,KCntSimDbUri));
   	filebuf.Append(_L8("\n API called"));
	file.Write(filebuf);
	filebuf.Zero();
    file.Flush();
    
    CActiveScheduler::Start();

	result=callback->iErrCode;
 	
 	filebuf.Append(_L8("\n Error result"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();
	
 	filebuf.Num(result);
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();
	
	
	CleanupStack::PopAndDestroy(callback);
	CleanupStack::PopAndDestroy(icontactservice);

	CleanupStack::PopAndDestroy();//file
	CleanupStack::PopAndDestroy();//fs
	
	
	
//	__UHEAP_MARKEND;		
	return result;

	
    }

// -----------------------------------------------------------------------------
// CContactsUT:getlisttest_searchL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt CContactsUT::getlisttest_searchL(CStifItemParser& aItem)
	{
//	__UHEAP_MARK;
 
	RFs fs;
	RFile file;  
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TInt errfile =file.Replace(fs,_L("C:\\Data\\tcontacts_search.txt"), EFileWrite | EFileStreamText); 
	CleanupClosePushL(file);
	
	TBuf8<100> filebuf;
	
	
	CContactService* icontactservice = CContactService::NewL();
	CleanupStack::PushL(icontactservice);
	
	CContactCallBack* callback = CContactCallBack::NewL(&file);
	CleanupStack::PushL(callback);



//For automation purpose
	_LIT(KFileName,"c:\\data\\Import.vcf");
	TBuf<50> flnm(KFileName);

   TRAPD(err,icontactservice->ImportVCardToStoreL(callback,0,flnm,KCntSimDbUri));
   	
   	filebuf.Append(_L8("\nImportVCard is called\n"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

   
   CActiveScheduler::Start(); 



	TInt result(callback->iErrCode);

   	filebuf.Num(callback->iErrCode);
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();
	
	if(result != KErrNone)
	return result;





	
	
    TBuf<10> serch(_L("A"));
    TRAPD(err1,icontactservice->GetListL(callback,0,EContacts,KNullDesC8,serch,NULL,EAsc,KCntSimDbUri));
    CActiveScheduler::Start();

   result=callback->iErrCode;
	
	CleanupStack::PopAndDestroy(callback);
	CleanupStack::PopAndDestroy(icontactservice);

	CleanupStack::PopAndDestroy();//file
	CleanupStack::PopAndDestroy();//fs
	

	
//	__UHEAP_MARKEND;
	return result;
	
		
	}

// -----------------------------------------------------------------------------
// CContactsUT:deletetestL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::deletetestL(CStifItemParser& aItem)
	{
	
//	__UHEAP_MARK;

	RFs fs;
	RFile file;  
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TInt errfile =file.Replace(fs,_L("C:\\Data\\tcontacts_delete.txt"), EFileWrite | EFileStreamText); 
	CleanupClosePushL(file);
	
	TBuf8<100> filebuf;

	
	CContactService* icontactservice = CContactService::NewL();
	CleanupStack::PushL(icontactservice);



	filebuf.Append(_L8("\n Core Class object created"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

	
	CContactCallBack* callback = CContactCallBack::NewL(&file);
	CleanupStack::PushL(callback);

	filebuf.Append(_L8("\n Callback object created"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();


//For automation purpose
	_LIT(KFileName,"c:\\data\\Import.vcf");
	TBuf<50> flnm(KFileName);

   TRAPD(err,icontactservice->ImportVCardToStoreL(callback,0,flnm,KCntSimDbUri));
   	
   	filebuf.Append(_L8("\nImportVCard is called\n"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

   
   CActiveScheduler::Start(); 



	TInt result(callback->iErrCode);

   	filebuf.Num(callback->iErrCode);
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();
	
	if(result != KErrNone)
	return result;







// GetList for getting one contact item
    TBuf<10> serch(_L("A"));
    TRAPD(err1,icontactservice->GetListL(callback,0,EContacts,KNullDesC8,serch,NULL,EAsc,KCntSimDbUri));
  
  	filebuf.Append(_L8("\n GetList is called"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

  
    CActiveScheduler::Start();
  
    if(callback->iErrCode == KErrNone)
	    {

	     RPointerArray<TDesC8> contactIdArray;
	     contactIdArray.Append(callback->iId);
	     
	     TRAPD(err,icontactservice->DeleteL(callback,0,contactIdArray,KCntSimDbUri));

		filebuf.Append(_L8("\n Delete is called\n"));
		file.Write(filebuf);
		filebuf.Zero();
		file.Flush();
					  
	     CActiveScheduler::Start();
	    	
	    }



	result=callback->iErrCode;
	
	filebuf.Num(callback->iErrCode);
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

	
	CleanupStack::PopAndDestroy(callback);
	CleanupStack::PopAndDestroy(icontactservice);

	CleanupStack::PopAndDestroy();//file
	CleanupStack::PopAndDestroy();//fs

	
//	__UHEAP_MARKEND;
	return result;
		
	}


// -----------------------------------------------------------------------------
// CContactsUT:importL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::importL(CStifItemParser& aItem)
	{

//	__UHEAP_MARK;

	RFs fs;
	RFile file;  
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TInt errfile =file.Replace(fs,_L("C:\\Data\\tcontacts_import.txt"), EFileWrite | EFileStreamText); 
	CleanupClosePushL(file);
	
	TBuf8<100> filebuf;

	
	CContactService* icontactservice = CContactService::NewL();
	CleanupStack::PushL(icontactservice);
	
	filebuf.Append(_L8("\n Core class object is created"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

	
	CContactCallBack* callback = CContactCallBack::NewL(&file);
	CleanupStack::PushL(callback);

	filebuf.Append(_L8("\nCallback object is created"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

// pre condition that Import.vcf should b present .
	_LIT(KFileName,"c:\\data\\Import.vcf");
	TBuf<50> flnm(KFileName);

   TRAPD(err,icontactservice->ImportVCardToStoreL(callback,0,flnm,KCntSimDbUri));
   	
   	filebuf.Append(_L8("\nImportVCard is called\n"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

   
   CActiveScheduler::Start(); 



	TInt result(callback->iErrCode);

   	filebuf.Num(callback->iErrCode);
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

	
	CleanupStack::PopAndDestroy(callback);
	CleanupStack::PopAndDestroy(icontactservice);



	CleanupStack::PopAndDestroy();//file
	CleanupStack::PopAndDestroy();//fs

//	__UHEAP_MARKEND;
	return result;	
	
		
	}

// -----------------------------------------------------------------------------
// CContactsUT:exportL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::exportL(CStifItemParser& aItem)
	{

//	__UHEAP_MARK;


	RFs fs;
	RFile file;  
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TInt errfile =file.Replace(fs,_L("C:\\Data\\tcontacts_export.txt"), EFileWrite | EFileStreamText); 
	CleanupClosePushL(file);
	
	TBuf8<100> filebuf;

	CContactService* icontactservice = CContactService::NewL();
	CleanupStack::PushL(icontactservice);

	filebuf.Append(_L8("\n Core class object is created"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();


	
	CContactCallBack* callback = CContactCallBack::NewL(&file);
	CleanupStack::PushL(callback);


	filebuf.Append(_L8("\n Callback object is created"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();


//For automation purpose
	_LIT(KFileName,"c:\\data\\Import.vcf");
	TBuf<50> flnm(KFileName);

   TRAPD(err,icontactservice->ImportVCardToStoreL(callback,0,flnm,KCntSimDbUri));
   	
   	filebuf.Append(_L8("\nImportVCard is called\n"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

   
   CActiveScheduler::Start(); 



	TInt result(callback->iErrCode);

   	filebuf.Num(callback->iErrCode);
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();
	
	if(result != KErrNone)
	return result;







// GetList for getting one contact item
    TBuf<10> serch(_L("A"));
    TRAPD(err1,icontactservice->GetListL(callback,0,EContacts,KNullDesC8,serch,NULL,EAsc,KCntSimDbUri));

	filebuf.Append(_L8("\nGetList is called"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();


    CActiveScheduler::Start();
  
    if(callback->iErrCode == KErrNone)
    {

    _LIT(KFileName,"c:\\data\\Export.vcf");
    TBuf<50> flnm1(KFileName);
    TInt ret=0;
	
    TRAPD(err,icontactservice->ExportVCardL(callback,0,flnm1,*(callback->iId),KCntSimDbUri));
    
   	filebuf.Append(_L8("\nExportVCard is called"));
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

    
    CActiveScheduler::Start();
    	
    }
     

result=callback->iErrCode;
	
  	filebuf.Num(callback->iErrCode);
	file.Write(filebuf);
	filebuf.Zero();
	file.Flush();

	
	
	CleanupStack::PopAndDestroy(callback);
	CleanupStack::PopAndDestroy(icontactservice);

	CleanupStack::PopAndDestroy();//file
	CleanupStack::PopAndDestroy();//fs

	
//	__UHEAP_MARKEND;
	return result;

		
	}