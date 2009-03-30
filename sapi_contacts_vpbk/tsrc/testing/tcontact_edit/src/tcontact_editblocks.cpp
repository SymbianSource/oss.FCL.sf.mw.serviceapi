/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include "tContact_edit.h"

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

 TInt handlerror_cnt,handleiter_cnt;

 //HBufC8 *contactid ;
TBuf8<100> contactid;
CSingleContact* myContact=NULL;



void CContactCallback::HandleReturnValue( TOperationEvent aEventId, const TInt& aError, TInt aTransId )
{
  
  CActiveScheduler::Stop();
  iError= aError ;
}


 void CContactCallback:: HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId )
 {
 

     CActiveScheduler::Stop();
	
  CSingleContactField* field = NULL; 
  HBufC8* cntMyBuf = NULL;
  HBufC8* tmpid;    
    HBufC8* buf = NULL;
    
    TInt count=0 ;	     

   
if(aError==KErrNone)
{
   aIter->NextL(myContact,cntMyBuf);

  if(myContact)
  {
       
   CleanupStack::PushL(myContact);
  //CleanupStack::PushL(cntMyBuf); 
	  
    contactid = *cntMyBuf;
      
  CleanupStack::Pop(myContact);        
   
    }
                   
} //if
 
 delete aIter;

 } 

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctdeleteadd::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctdeleteadd::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctdeleteadd::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctdeleteadd::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        
        ENTRY( "Edit_Test1", Ctdeleteadd::Edit_Test1L ), 
        ENTRY( "Edit_Test2", Ctdeleteadd::Edit_Test2L ),
        ENTRY( "Edit_Test3", Ctdeleteadd::Edit_Test3L ), 
        ENTRY( "Edit_Test4", Ctdeleteadd::Edit_Test4L ), 
        ENTRY( "Edit_Test5", Ctdeleteadd::Edit_Test5L ), 
        ENTRY( "Edit_Test6", Ctdeleteadd::Edit_Test6L ), 
        ENTRY( "Edit_Test7", Ctdeleteadd::Edit_Test7L ),
        ENTRY( "Edit_Test8", Ctdeleteadd::Edit_Test8L ),
        ENTRY( "Edit_Test9", Ctdeleteadd::Edit_Test9L ),
        ENTRY( "Edit_Test10", Ctdeleteadd::Edit_Test10L ),
        ENTRY( "Edit_Test11", Ctdeleteadd::Edit_Test11L ),
        ENTRY( "Edit_Test12", Ctdeleteadd::Edit_Test12L ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


	 
 /* Editing a contact */
 TInt Ctdeleteadd::Edit_Test1L( CStifItemParser& aItem )
 {
  
    TInt flag = 0 ,count;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

   _LIT8(KFirstName1,"FirstName");
    _LIT(KName1,"ABCDEFG"); 
   
   
   _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Anitha"); 
   _LIT(KFirst,"First Name");
   aItem.GetNextInt(count) ;
   
    //instantiate service class object
    
    /* create contactitem with invalid fieldname "FrstName */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
     
    singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
   /* Add the contactitem */ 
    aItem.GetNextInt(count) ;
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
   
   /* get the contactid of any contact  from phonebook */
   icontactservice->GetListL(icallback,1,EContacts);
   CActiveScheduler::Start();
   
   myContact->RemoveAllFields();

   
         
   singleContactField->SetFieldParamsL(KFirstName1,KNullDesC,KName1);
   myContact->AddFieldToContactL(singleContactField);
   
   //aItem.GetNextInt(count) ;
   icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
     
  /* check whether Add api returns the expected error code */      
 if(count == icallback->iError)
      return KErrNone ;
      
    return KErrNone ;
    
}

TInt Ctdeleteadd::Edit_Test2L( CStifItemParser& aItem )
 {
  
    TInt flag = 0 ,count;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

   _LIT8(KMobilePhoneHome,"MobilePhoneHome");
    _LIT(KPhone,"123456"); 
   
   aItem.GetNextInt(count) ;
   
   
   _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Edit_test2"); 
   _LIT(KFirst,"First Name");
   
   
    //instantiate service class object
    
    /* create contactitem with invalid fieldname "FrstName */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
     
    singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
   /* Add the contactitem */ 
    aItem.GetNextInt(count) ;
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
   /* get the contactid of any contact  from phonebook */
   icontactservice->GetListL(icallback,1,EContacts);
   CActiveScheduler::Start();

  
   singleContactField->SetFieldParamsL(KMobilePhoneHome,KNullDesC,KPhone);
   myContact->AddFieldToContactL(singleContactField);
   
   //aItem.GetNextInt(count) ;
   icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
     
  /* check whether Add api returns the expected error code */      
 if(count == icallback->iError)
      return KErrNone ;
      
    return KErrGeneral ;
    
}

/* Removing all fields from contact */
TInt Ctdeleteadd::Edit_Test3L( CStifItemParser& aItem )
 {
  
  	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    TInt flag = 0 ,count;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

   _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Edit_test3"); 
   _LIT(KFirst,"First Name");
   aItem.GetNextInt(count) ;
   
    //instantiate service class object
    
    /* create contactitem with invalid fieldname "FrstName */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
     
    singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
   /* Add the contactitem */ 
    aItem.GetNextInt(count) ;
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
   /* get the contactid of any contact from phonebook */
   TPtrC searchval(_L("Edit_test3"));
   TBuf8<15> fstname(_L8("FirstName"));
   CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
   srchfield->AppendL(fstname);
   icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   CActiveScheduler::Start();
   
   myContact->RemoveAllFields();
   icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
  /* check whether Add api returns the expected error code */      
 if(count == icallback->iError)
      return KErrNone ;
      
    return KErrNone ;
    
}

/* Removing all fields from contact and adding it again*/
TInt Ctdeleteadd::Edit_Test4L( CStifItemParser& aItem )
 {
  
  	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    TInt flag = 0 ,count;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

   _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Edit_test4"); 
   _LIT(KFirst,"First Name");
   aItem.GetNextInt(count) ;
   
    //instantiate service class object
    
    /* create contactitem with invalid fieldname "FrstName */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
     
    singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
   /* Add the contactitem */ 
    aItem.GetNextInt(count) ;
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
   /* get the contactid of any contact from phonebook */
   TPtrC searchval(_L("Edit_test4"));
   TBuf8<15> fstname(_L8("FirstName"));
   CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
   srchfield->AppendL(fstname);
   icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   CActiveScheduler::Start();
   
   myContact->RemoveAllFields();
   myContact->AddFieldToContactL(singleContactField);
   
   //aItem.GetNextInt(count) ;
   icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();

  /* check whether Add api returns the expected error code */      
  if(count == icallback->iError)
      return KErrNone ;
      
    return KErrNone ;
    
}

/* Overwriting the fields without removing*/
TInt Ctdeleteadd::Edit_Test5L( CStifItemParser& aItem )
 {
  
  	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    TInt flag = 0 ,count;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

   _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Edita");
    _LIT(KName1,"Editb"); 
   _LIT(KFirst,"First Name");
   aItem.GetNextInt(count) ;
   
    //instantiate service class object
    
    /* create contactitem with invalid fieldname "FrstName */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
     
    singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
   /* Add the contactitem */ 
    aItem.GetNextInt(count) ;
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
   /* get the contactid of any contact from phonebook */
   TPtrC searchval(_L("Edita"));
   TBuf8<15> fstname(_L8("FirstName"));
   CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
   srchfield->AppendL(fstname);
   icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   CActiveScheduler::Start();
   
   //CSingleContact* singleContact1 = CSingleContact::NewL();
   CSingleContactField* singleContactField1 = CSingleContactField::NewL();
   
   singleContactField1->SetFieldParamsL(KFirstName,KFirst,KName1);
   //singleContact1->AddFieldToContactL(singleContactField1);
   
   myContact->AddFieldToContactL(singleContactField1);
   
   //aItem.GetNextInt(count) ;
   icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
    
   TInt fldcnt=myContact->FieldCount();
   CSingleContactField* ResultContactField1 = CSingleContactField::NewL();
   ResultContactField1=myContact->FieldAt(0);
   ResultContactField1=myContact->FieldAt(1);
   ResultContactField1=myContact->FieldAt(2);
   
  /* check whether Add api returns the expected error code */      
  if(count == icallback->iError)
      return KErrNone ;
      
    return KErrNone ;
    
}

/* Removing the field */
TInt Ctdeleteadd::Edit_Test6L( CStifItemParser& aItem )
 {
 
 	TInt count =KErrGeneral;
    _LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    _LIT8(KFirstname,"FirstName");
    _LIT8(KHomePhone,"LandPhoneHome");
    _LIT(Kname,"Ambar");
    _LIT(Kphone,"123545");
    _LIT(Knme,"Name");
    _LIT(Phone,"Phone no.");
    //instantiate service class object
    
    /* create contactitem to add */ 
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField1 = CSingleContactField::NewL();
    CSingleContactField* singleContactField2 = CSingleContactField::NewL();
       
    singleContactField1->SetFieldParamsL(KFirstname,Knme,Kname);
    singleContactField2->SetFieldParamsL(KHomePhone,Phone,Kphone);
    
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
        
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
    TPtrC searchval(_L("Ambar"));
    TBuf8<15> fstname(_L8("FirstName"));
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    srchfield->AppendL(fstname);
    icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   	CActiveScheduler::Start();
   	
   	TInt fldcnt1=myContact->FieldCount();
    myContact->RemoveField(0);
    
    icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
   	TInt fldcnt2=myContact->FieldCount();
    /* check whether add api returns the expected error code */  
   if(fldcnt1==(fldcnt2+1))
      return KErrNone ;
      
    return KErrGeneral ; 
    
    
    }
    
    /* Removing synchronisation field */
TInt Ctdeleteadd::Edit_Test7L( CStifItemParser& aItem )
 {
 
 	TInt count =KErrGeneral;
    _LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    _LIT8(KFirstname,"FirstName");
    _LIT8(KHomePhone,"LandPhoneHome");
    _LIT8(Sync,"SyncClass");
    _LIT(Kname,"Ambar");
    _LIT(Kphone,"123545");
    _LIT(Knme,"Name");
    _LIT(Phone,"Phone no.");
    //instantiate service class object
    
    /* create contactitem to add */ 
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField1 = CSingleContactField::NewL();
    CSingleContactField* singleContactField2 = CSingleContactField::NewL();
       
    singleContactField1->SetFieldParamsL(KFirstname,Knme,Kname);
    singleContactField2->SetFieldParamsL(KHomePhone,Phone,Kphone);
    
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
        
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
    TPtrC searchval(_L("Ambar"));
    TBuf8<15> fstname(_L8("FirstName"));
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    srchfield->AppendL(fstname);
    
    TInt err1,err2;
    TRAP(err1,icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield));
   	CActiveScheduler::Start();
   	
   	TInt fldcnt1=myContact->FieldCount();
   	CSingleContactField* Resultfield = CSingleContactField::NewL();
   	TPtrC8 fieldkey;
   	TPtrC label;
   	TPtrC value;
   	for (TInt i=0; i<fldcnt1 ;i++)
   	{
   		Resultfield=myContact->FieldAt(i);
   		
   		Resultfield->GetFieldDataL(fieldkey,label,value);
   		if(!(fieldkey.Compare(Sync)))
   		myContact->RemoveField(i);
   	
   	}
    
    icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
   	
   	TInt fldcnt2=myContact->FieldCount();
    /* check whether add api returns the expected error code */  
    if(fldcnt1==(fldcnt2+1))
      return KErrNone ;
      
    return KErrGeneral ; 
    
    
    }
    
    /* Removing sync field*/
    TInt Ctdeleteadd::Edit_Test8L( CStifItemParser& aItem )
   {
 
 	TInt count =KErrGeneral;
    _LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    _LIT8(Sync,"SyncClass");  
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"TestingSync"); 
    _LIT(KFirst,"Name");
    
    //instantiate service class object
    
    /* create contactitem to add */ 
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
    
    
  	singleContact->AddFieldToContactL(singleContactField);
        
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
    TPtrC searchval(_L("TestingSync"));
    TBuf8<15> fstname(_L8("FirstName"));
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    srchfield->AppendL(fstname);
    icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
    CActiveScheduler::Start();
   	int err_getlist = icallback->iError;
   	if (err_getlist)
   	return KErrGeneral ;
   	
   	TInt fldcnt1=myContact->FieldCount();
   	CSingleContactField* Resultfield = CSingleContactField::NewL();
   	TPtrC8 fieldkey;
   	TPtrC label;
   	TPtrC value;
   	for (TInt i=0; i<fldcnt1 ;i++)
   	{
   		Resultfield=myContact->FieldAt(i);
   		
   		Resultfield->GetFieldDataL(fieldkey,label,value);
   		if(!(fieldkey.Compare(Sync)))
   		myContact->RemoveField(i);
   	
   	}
    
    icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
   	srchfield =CSearchFields :: NewL(icontactservice);
    srchfield->AppendL(fstname);
   	CContactIter* ite;
   	icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   	CActiveScheduler::Start();
   	TInt fldcnt2=myContact->FieldCount();
    /* check whether add api returns the expected error code */  
    if(fldcnt1==(fldcnt2))
      return KErrNone ;
      
    return KErrGeneral ; 
    
    
    }
    
    
    /* Trying to remove the fields one at a time */
    TInt Ctdeleteadd::Edit_Test9L( CStifItemParser& aItem )
   {
 
 	TInt count =KErrGeneral;
    _LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    _LIT8(KFirstname,"FirstName");
    _LIT8(KHomePhone,"LandPhoneHome");
    _LIT8(Sync,"SyncClass");
    _LIT(Kname,"Ambar");
    _LIT(Kphone,"123545");
    _LIT(Knme,"Name");
    _LIT(Phone,"Phone no.");
    //instantiate service class object
    
    /* create contactitem to add */ 
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField1 = CSingleContactField::NewL();
    CSingleContactField* singleContactField2 = CSingleContactField::NewL();
       
    singleContactField1->SetFieldParamsL(KFirstname,Knme,Kname);
    singleContactField2->SetFieldParamsL(KHomePhone,Phone,Kphone);
    
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
        
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
    TPtrC searchval(_L("Ambar"));
    TBuf8<15> fstname(_L8("FirstName"));
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    srchfield->AppendL(fstname);
    icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   	CActiveScheduler::Start();
   	
   	int err_getlist = icallback->iError;
   	if (err_getlist)
   	return KErrGeneral ;
   	TInt fldcnt1=myContact->FieldCount();
   	CSingleContactField* Resultfield = CSingleContactField::NewL();
   	TBuf8<20> fieldkey;
   	TBuf<20> label;
   	TBuf<20> value;
   	
   	myContact->RemoveField(0);
   	
    icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
    
   	myContact->RemoveField(0);
   	icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
    
    myContact->RemoveField(0);
   	icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
    
   	TInt fldcnt2=myContact->FieldCount();
    /* check whether add api returns the expected error code */  
    if(fldcnt1==(fldcnt2+3))
      return KErrNone ;
      
    return KErrGeneral ; 
    
    
    }
    
    
    /* Trying to remove invalid field */
TInt Ctdeleteadd::Edit_Test10L( CStifItemParser& aItem )
 {
 
 	TInt count =KErrGeneral;
    _LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    _LIT8(KFirstname,"FirstName");
    _LIT8(KHomePhone,"LandPhoneHome");
    _LIT(Kname,"Antony");
    _LIT(Kphone,"123545");
    _LIT(Knme,"Name");
    _LIT(Phone,"Phone no.");
    //instantiate service class object
    
    /* create contactitem to add */ 
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField1 = CSingleContactField::NewL();
    CSingleContactField* singleContactField2 = CSingleContactField::NewL();
       
    singleContactField1->SetFieldParamsL(KFirstname,Knme,Kname);
    singleContactField2->SetFieldParamsL(KHomePhone,Phone,Kphone);
    
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
        
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
    TPtrC searchval(_L("Antony"));
    TBuf8<15> fstname(_L8("FirstName"));
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    srchfield->AppendL(fstname);
    icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   	CActiveScheduler::Start();
   	
   	TInt fldcnt1=myContact->FieldCount();
    TInt err;
    err=myContact->RemoveField(6);
    if(err)
      return KErrNone ;
      
    return KErrGeneral ; 
    
    
    }
    
    /* Removing the middle syncfields*/
TInt Ctdeleteadd::Edit_Test11L( CStifItemParser& aItem )
 {
  	_LIT8(Sync,"SyncClass");
  	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    TInt flag = 0 ,count;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

    _LIT8(KFirstName,"LandPhoneHome");
    _LIT(KName,"9986767");
    _LIT(KName1,"12345677"); 
    _LIT(KFirst,"Phone no");
     _LIT8(KFirstname,"FirstName");
    _LIT8(KHomePhone,"LandPhoneHome");
    _LIT(Kname,"Antony");
    _LIT(Kphone,"123545");
    _LIT(Knme,"Name");
    _LIT(Phone,"Phone no.");
    aItem.GetNextInt(count) ;
   
    //instantiate service class object
    
    /* create contactitem to add */ 
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField1 = CSingleContactField::NewL();
    CSingleContactField* singleContactField2 = CSingleContactField::NewL();
       
    singleContactField1->SetFieldParamsL(KFirstname,Knme,Kname);
    singleContactField2->SetFieldParamsL(KHomePhone,Phone,Kphone);
    
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
        
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
    TPtrC searchval(_L("Antony"));
    TBuf8<15> fstname(_L8("FirstName"));
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    srchfield->AppendL(fstname);
    icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   	CActiveScheduler::Start();
   
   //CSingleContact* singleContact1 = CSingleContact::NewL();
   //CSingleContactField* singleContactField1 = CSingleContactField::NewL();
   
   singleContactField1->SetFieldParamsL(KFirstName,KFirst,KName1);
   //singleContact1->AddFieldToContactL(singleContactField1);
   if(!myContact)
   {
   	return KErrGeneral;
   }
   myContact->AddFieldToContactL(singleContactField1);
   
   //aItem.GetNextInt(count) ;
   icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
    
   TInt fldcnt1=myContact->FieldCount();
   CSingleContactField* Resultfield = CSingleContactField::NewL();
   	TPtrC8 fieldkey;
   	TPtrC label;
   	TPtrC value;
   for (TInt i=0; i<fldcnt1 ;i++)
   	{
   		Resultfield=myContact->FieldAt(i);
   		if(Resultfield)
   			Resultfield->GetFieldDataL(fieldkey,label,value);
   		
   		if(!(fieldkey.Compare(Sync)))
   		{
   		myContact->RemoveField(i);
   		break;	
   		}
   	
   	}
   	
   	icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
    
    /*Resultfield->GetFieldData(fieldkey,label,value);*/
    TPtrC searchval1(_L("12345677"));
    CSearchFields *srchfield1 =CSearchFields :: NewL(icontactservice);
    srchfield1->AppendL(fstname);
    
    /*Resultfield->GetFieldData(fieldkey,label,value);*/
    icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield1);
    CActiveScheduler::Start();
    
    
    
    TInt fldcnt2=myContact->FieldCount();
   
  /* check whether Add api returns the expected error code */      
  if(fldcnt1==(fldcnt2))
      return KErrNone ;
      
    return KErrGeneral ;
    
}

/* adding sync field*/
TInt Ctdeleteadd::Edit_Test12L( CStifItemParser& aItem )
 {
  
  	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    TInt flag = 0 ,count;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

   _LIT8(KFirstName,"FirstName");
   _LIT8(KSync,"SyncClass");
    _LIT(KName,"Anitha");
    _LIT(KName1,"private"); 
   _LIT(KFirst,"First Name");
   _LIT(Klabel,"Synchronisation");
   aItem.GetNextInt(count) ;
   
    //instantiate service class object
    
    /* create contactitem with invalid fieldname "FrstName */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
     
    singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
   /* Add the contactitem */ 
    aItem.GetNextInt(count) ;
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
   /* get the contactid of any contact from phonebook */
   TPtrC searchval(_L("Anitha"));
   TBuf8<15> fstname(_L8("FirstName"));
   CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
   srchfield->AppendL(fstname);
   icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   CActiveScheduler::Start();
   TInt fldcnt1=myContact->FieldCount();
   
   //CSingleContact* singleContact1 = CSingleContact::NewL();
   CSingleContactField* singleContactField1 = CSingleContactField::NewL();
   
   singleContactField1->SetFieldParamsL(KSync,Klabel,KName1);
   //singleContact1->AddFieldToContactL(singleContactField1);
   
   myContact->AddFieldToContactL(singleContactField1);
   
   //aItem.GetNextInt(count) ;
   icontactservice->AddL(icallback,0,myContact);
    CActiveScheduler::Start();
   
    TPtrC searchval1(_L("private"));
    CSearchFields *srchfield1 =CSearchFields :: NewL(icontactservice);
    TBuf8<15> fstname1(_L8("SyncClass"));
    srchfield1->AppendL(fstname);
    
    icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield1);
    CActiveScheduler::Start(); 
    TInt fldcnt2=myContact->FieldCount();
   
  /* check whether Add api returns the expected error code */      
  if(fldcnt1==fldcnt2-1)
      return KErrNone ;
      
    return KErrGeneral ;
    
}


// -----------------------------------------------------------------------------
// Ctdeleteadd::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctdeleteadd::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
