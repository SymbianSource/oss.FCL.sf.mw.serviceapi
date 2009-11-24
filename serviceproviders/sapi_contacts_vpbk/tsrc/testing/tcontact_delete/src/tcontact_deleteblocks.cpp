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
#include <StifTestInterface.h>
#include "tcontact_delete.h"

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

void CContactCallback::HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }

void CContactCallback::HandleReturnId( const TInt& aError, HBufC8* acntId, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }
    
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
    TBuf8<100> buf1;
    TBuf<100> buf2;
    TBuf<100> buf3;
    TInt count=0 ;	     
iError= aError ;
   
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
        ENTRY( "Delete_Test1", Ctdeleteadd::Delete_Test1L ),
        ENTRY( "Delete_Test2", Ctdeleteadd::Delete_Test2L ),
        ENTRY( "Delete_Test3", Ctdeleteadd::Delete_Test3L ),
        ENTRY( "Delete_Test4", Ctdeleteadd::Delete_Test4L ),
        ENTRY( "Delete_Test5", Ctdeleteadd::Delete_Test5L ),
        ENTRY( "Delete_Test6", Ctdeleteadd::Delete_Test6L ),
        ENTRY( "Delete_Test7", Ctdeleteadd::Delete_Test7L ),
        ENTRY( "Delete_Test8", Ctdeleteadd::Delete_Test8L ),
        ENTRY( "Delete_Test9", Ctdeleteadd::Delete_Test9L ),
        ENTRY( "Delete_Test10", Ctdeleteadd::Delete_Test10L ),
        ENTRY( "Delete_Test11", Ctdeleteadd::Delete_Test11L ),
        ENTRY( "Delete_Test12", Ctdeleteadd::Delete_Test12L ),
        ENTRY( "Delete_Test13", Ctdeleteadd::Delete_Test13L ),
        
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctdeleteadd::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

/* deleting single contact from default database*/
TInt Ctdeleteadd::Delete_Test1L( CStifItemParser& aItem )
    {
    
     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Andrew"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
            
    /* Add the contactitem */
   // icontactservice->AddL(icallback,0,singleContact);
   // CActiveScheduler::Start();

   /* get the contactid of any contact  from phonebook */
    icontactservice->GetListL(icallback,1,EContacts) ;
    CActiveScheduler::Start();
    
    HBufC8* contactId = contactid.AllocLC();
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);    
    idArray.AppendL(contactId);    
    
    TInt err1,err2;
     TRAP(err1,icontactservice->DeleteL(icallback,0,idArray));
    if(err1)
    {
    	CleanupStack::PopAndDestroy(&idArray);//singleContactField      
        CleanupStack::PopAndDestroy(contactId);
    	return KErrNone;
    }
    
    iLog->Log(_L("DeleteL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start(); 
   
   
    CleanupStack::PopAndDestroy(&idArray);//singleContactField      
    
    CleanupStack::PopAndDestroy(contactId);
    
    aItem.GetNextInt(flag) ;
    
    /* check whether delete api returns the expected error code */
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral;
               
    }

/* Deleting non existent contact from default db */
  TInt Ctdeleteadd::Delete_Test2L( CStifItemParser& aItem )
    {

     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Bill"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
          
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
   
   
   /* get the contactid of any contact  from phonebook */
   icontactservice->GetListL(icallback,0,EContacts)  ;
   CActiveScheduler::Start();
    

    RPointerArray<TDesC8> ptr ;
    
    HBufC8* contactId = contactid.AllocLC();
   /* Append the contactid to ptr */
    TRAPD(err,ptr.AppendL(contactId));   						  

   /* detele the contact from phonebook */		
 	icontactservice->DeleteL(icallback,0,ptr);
    CActiveScheduler::Start();
    //CleanupStack::PopAndDestroy(contactId);
    
 	/* detele the same contact from phonebook */	
 	icontactservice->DeleteL(icallback,0,ptr);
    CActiveScheduler::Start();
    CleanupStack::PopAndDestroy(contactId);

  /* check whether delete api returns the expected error code */
    aItem.GetNextInt(flag) ;
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral;
          
    }

  /* Deleting group from default db*/
  TInt Ctdeleteadd::Delete_Test3L( CStifItemParser& aItem )
    {
    
     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );
    
   /* Group1 to add to phonebook */      
    _LIT(KGroup,"friends1") ;
   
       
   /*Add group1 to phonebook */
    icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
    CActiveScheduler::Start();
     

    /* get the contactid of any group  from phonebook */
    icontactservice->GetListL(icallback,1,EGroups)  ;
     CActiveScheduler::Start();
    
     RPointerArray<TDesC8> ptr ;
        
    HBufC8* contactId = contactid.AllocLC();
   /* Append the contactid to ptr */
    TRAPD(err,ptr.AppendL(contactId));   	  						  
	
 	/* delete the group from phonebook */
 	icontactservice->DeleteL(icallback,2,ptr);
	CActiveScheduler::Start();
    CleanupStack::PopAndDestroy(contactId);
    
    /* check whether delete api returns the expected error code */ 
    aItem.GetNextInt(flag) ;
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral; 
    
    }
    
  
    
    /* deleting the group twice from default db*/
     TInt Ctdeleteadd::Delete_Test4L( CStifItemParser& aItem )
    {
    
    
    TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

   /* Group1 to add to phonebook */      
   _LIT(KGroup,"Friends2")  ;
   
    /*Add group1 to phonebook */
   icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
   CActiveScheduler::Start();
     
 
   /* get the contactid of any group  from phonebook */
   icontactservice->GetListL(icallback,1,EGroups);
   CActiveScheduler::Start();
    

   RPointerArray<TDesC8> ptr;
   HBufC8* contactId = contactid.AllocLC();
  /* Append the contactid to ptr */
   TRAPD(err,ptr.AppendL(contactId));    						  
	
	/* delete the group from phonebook */
 	icontactservice->DeleteL(icallback,2,ptr);
 	 CActiveScheduler::Start();
 	 
 	/* delete the group from phonebook */
 	icontactservice->DeleteL(icallback,3,ptr);
	CActiveScheduler::Start();
    CleanupStack::PopAndDestroy(contactId);
    
     /* check whether delete api returns the expected error code */
    aItem.GetNextInt(flag) ;
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral;
    
    }
  
  /* deleting single contact from testcontacts2.cdb*/
    TInt Ctdeleteadd::Delete_Test5L( CStifItemParser& aItem )
    {
    
     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TPtrC db1(_L("cntdb://c:testgroup.cdb"));
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Andrew"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
            
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,db1);
    CActiveScheduler::Start();

   /* get the contactid of any contact  from phonebook */
    icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,db1) ;
    CActiveScheduler::Start();
    
    HBufC8* contactId = contactid.AllocLC();
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);    
    idArray.AppendL(contactId);    
    
   
    icontactservice->DeleteL(icallback,0,idArray,db1);
    iLog->Log(_L("DeleteL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start(); 
   
   
    CleanupStack::PopAndDestroy(&idArray);//singleContactField      
    
    CleanupStack::PopAndDestroy(contactId);
    
    aItem.GetNextInt(flag) ;
    
    /* check whether delete api returns the expected error code */
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral;
               
    }
    
   /* deleting  contact twice from testcontacts2.cdb*/ 
     TInt Ctdeleteadd::Delete_Test6L( CStifItemParser& aItem )
    {

     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    TPtrC db1(_L("cntdb://c:testgroup.cdb"));
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Bill"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
          
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,db1);
    CActiveScheduler::Start();
   
   
   /* get the contactid of any contact  from phonebook */
   icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,db1) ;
   CActiveScheduler::Start();
    

    RPointerArray<TDesC8> ptr ;
    
    HBufC8* contactId = contactid.AllocLC();
   /* Append the contactid to ptr */
    TRAPD(err,ptr.AppendL(contactId));   						  

   /* detele the contact from phonebook */		
 	icontactservice->DeleteL(icallback,0,ptr,db1);
    CActiveScheduler::Start();
    //CleanupStack::PopAndDestroy(contactId);
    
 	/* detele the same contact from phonebook */	
 	icontactservice->DeleteL(icallback,0,ptr,db1);
    CActiveScheduler::Start();
    CleanupStack::PopAndDestroy(contactId);

  /* check whether delete api returns the expected error code */
    aItem.GetNextInt(flag) ;
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral;
          
    }
  
  /* Deleting group from testdefault db*/
  TInt Ctdeleteadd::Delete_Test7L( CStifItemParser& aItem )
    {
    
     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );
    TPtrC db1(_L("cntdb://c:testgroup.cdb"));
   /* Group1 to add to phonebook */      
    _LIT(KGroup,"friends1") ;
   
       
   /*Add group1 to phonebook */
    icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup,db1);
    CActiveScheduler::Start();
     

    /* get the contactid of any group  from phonebook */
    icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,EAsc,db1)  ;
     CActiveScheduler::Start();
    
     RPointerArray<TDesC8> ptr ;
        
    HBufC8* contactId = contactid.AllocLC();
   /* Append the contactid to ptr */
    TRAPD(err,ptr.AppendL(contactId));   	  						  
	
 	/* delete the group from phonebook */
 	icontactservice->DeleteL(icallback,2,ptr,db1);
	CActiveScheduler::Start();
    CleanupStack::PopAndDestroy(contactId);
    
    /* check whether delete api returns the expected error code */ 
    aItem.GetNextInt(flag) ;
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral; 
    
    }  

/* deleting the group twice from testdefault db*/
     TInt Ctdeleteadd::Delete_Test8L( CStifItemParser& aItem )
    {
    
    
    TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );

   /* Group1 to add to phonebook */      
   _LIT(KGroup,"Friends2")  ;
   TPtrC db1(_L("cntdb://c:testgroup.cdb"));
    /*Add group1 to phonebook */
   icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup,db1);
   CActiveScheduler::Start();
     
 
   /* get the contactid of any group  from phonebook */
   icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,EAsc,db1);
   CActiveScheduler::Start();
    

   RPointerArray<TDesC8> ptr;
   HBufC8* contactId = contactid.AllocLC();
  /* Append the contactid to ptr */
   TRAPD(err,ptr.AppendL(contactId));    						  
	
	/* delete the group from phonebook */
 	icontactservice->DeleteL(icallback,2,ptr,db1);
 	 CActiveScheduler::Start();
 	 
 	/* delete the group from phonebook */
 	icontactservice->DeleteL(icallback,3,ptr,db1);
	CActiveScheduler::Start();
    CleanupStack::PopAndDestroy(contactId);
    
     /* check whether delete api returns the expected error code */
    aItem.GetNextInt(flag) ;
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral;
    
    }
    
    /* deleting single contact from default database*/
TInt Ctdeleteadd::Delete_Test9L( CStifItemParser& aItem )
    {
    
     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Andrew"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
            
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();

   /* get the contactid of any contact  from phonebook */
    icontactservice->GetListL(icallback,1,EContacts) ;
    CActiveScheduler::Start();
    
    HBufC8* contactId = contactid.AllocLC();
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);    
    idArray.AppendL(contactId);    
    
   	_LIT(KGroup,"friends1") ;
   
       
   /*Add group1 to phonebook */
    icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
    CActiveScheduler::Start();
     

    /* get the contactid of any group  from phonebook */
    icontactservice->GetListL(icallback,1,EGroups)  ;
     CActiveScheduler::Start();
    
    //RPointerArray<TDesC8> ptr ;
        
    HBufC8* contactId1 = contactid.AllocLC();
   /* Append the contactid to ptr */
    TRAPD(err,idArray.AppendL(contactId1));   	  			
    icontactservice->DeleteL(icallback,0,idArray);
    iLog->Log(_L("DeleteL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start(); 
   
   
    //CleanupStack::PopAndDestroy(&idArray);//singleContactField      
    CleanupStack::PopAndDestroy(contactId1);
    CleanupStack::PopAndDestroy(&idArray);
    CleanupStack::PopAndDestroy(contactId);
    
    aItem.GetNextInt(flag) ;
    
    /* check whether delete api returns the expected error code */
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral;
               
    }
    
    /* deleting  contact twice from testcontacts2.cdb without specifying the database*/ 
     TInt Ctdeleteadd::Delete_Test10L( CStifItemParser& aItem )
    {
    
     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TPtrC db1(_L("cntdb://c:testingid.cdb"));
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Andrew"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    iLog->Log(_L("AddL called\n"));        
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();

	iLog->Log(_L("Add completed\n"));
   /* get the contactid of any contact  from phonebook */
   
    iLog->Log(_L("GetlistL called\n"));
    icontactservice->GetListL(icallback,1,EContacts) ;
    CActiveScheduler::Start();
    iLog->Log(_L("Getlist completed\n"));
    
    HBufC8* contactId = contactid.AllocLC();
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);    
    idArray.AppendL(contactId);    
    
    
    //-----------------------------------
   HBufC8* invalidid = HBufC8::NewL(15);
   TPtr8 strPtr= invalidid->Des();
   TBuf8<4> data;
   data.Append(_L("xyz"));
   strPtr.Append(data);
      
   myContact->SetContactIdL(*invalidid);
   
   idArray.AppendL(invalidid);
   //------------------------------------
   
    iLog->Log(_L("DeleteL called\n"));
    TRAPD(err,icontactservice->DeleteL(icallback,0,idArray,db1));
    if (err)
    {
    	CleanupStack::PopAndDestroy(&idArray);//singleContactField      
    
    	CleanupStack::PopAndDestroy(contactId);	
    	return KErrNone;
    }
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start(); 
   
   	iLog->Log(_L("DeleteL completed\n"));
   	iLog->Log(_L("Error %d\n"),icallback->iError);
    CleanupStack::PopAndDestroy(&idArray);//singleContactField      
    
    CleanupStack::PopAndDestroy(contactId);
    
    aItem.GetNextInt(flag) ;
    
    /* check whether delete api returns the expected error code */
    if(icallback->iError == flag) 
     return KErrNone;
	 

     return KErrGeneral;
               
    }
  
 /* Adding single contact to default database, deleting it and again adding it using contactid*/
  TInt Ctdeleteadd::Delete_Test11L( CStifItemParser& aItem )
    {

	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
	_LIT(KCntDbUri1, "cntdb://c:singlecontacts.cdb");										
    TInt count =KErrGeneral ;
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Aaaa"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
   	TPtrC searchval(_L("Aaaa"));
   	TBuf8<15> fstname(_L8("FirstName"));
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    
       
    srchfield->AppendL(fstname);
   icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield,EAsc,KCntDbUri);
   CActiveScheduler::Start();
   TInt err1;
    
    HBufC8* contactId = contactid.AllocLC();
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);    
    idArray.AppendL(contactId);    
    
   
    icontactservice->DeleteL(icallback,0,idArray);
    iLog->Log(_L("DeleteL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start(); 
   
   
    CleanupStack::PopAndDestroy(&idArray);//singleContactField      
    
    CleanupStack::PopAndDestroy(contactId);
    
   TRAP(err1,icontactservice->AddL(icallback,0,myContact,KNullDesC8,KNullDesC,KCntDbUri1));
   if(err1!=0)
   return KErrNone ;
   CActiveScheduler::Start();
   //icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,KCntDbUri1);
   //CActiveScheduler::Start(); 
    /* check whether add api returns the expected error code */  
  if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;  


	 }

/* trying to delete without any contactid from default database*/
TInt Ctdeleteadd::Delete_Test12L( CStifItemParser& aItem )
    {
    
     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Andrew"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
            
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();

   /* get the contactid of any contact  from phonebook */
    icontactservice->GetListL(icallback,1,EContacts) ;
    CActiveScheduler::Start();
    
    //HBufC8* contactId = contactid.AllocLC();
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);    
    //idArray.AppendL(contactId);    
    
    TInt err1,err2;
    TRAP(err1,icontactservice->DeleteL(icallback,0,idArray));
    if (err1 || err2)
    {
    	CleanupStack::PopAndDestroy(&idArray);//singleContactField 
    	return KErrNone;     
    	
    }
    
     return KErrGeneral;
               
    }

/* trying to delete with invalid contactid from default database*/
TInt Ctdeleteadd::Delete_Test13L( CStifItemParser& aItem )
    {
    
     TInt flag = 0 ;
    // Print to UI
    _LIT( Ktdeleteadd, "tdeleteadd" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktdeleteadd, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Andrew"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
            
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();

   /* get the contactid of any contact  from phonebook */
    icontactservice->GetListL(icallback,1,EContacts) ;
    CActiveScheduler::Start();
    
    //HBufC8 contactId;
    //contactId= "hi";
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);    
    //idArray.AppendL(contactId);    
    
    TInt err1,err2;
    TRAP(err1,icontactservice->DeleteL(icallback,0,idArray));
    if(err1 || err2)
    {
    	CleanupStack::PopAndDestroy(&idArray);//singleContactField
    	return KErrNone; 	
    }
    
    return KErrGeneral;
               
    }
	    
	    
    
 

//  End of File
