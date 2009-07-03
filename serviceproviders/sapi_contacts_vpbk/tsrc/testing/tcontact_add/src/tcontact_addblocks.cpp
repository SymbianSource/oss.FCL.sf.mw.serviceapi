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
#include "tContact_add.h"

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

 TInt Iterator_cnt=0;

 //HBufC8 *contactid ;
 HBufC8* contactid=NULL;
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
    HBufC8* buf = NULL;
    TBuf8<100> buf1;
    TBuf<100> buf2;
    TBuf<100> buf3;
    TInt count=0 ;	     
	
   
if(aError==KErrNone)
{
   aIter->NextL(myContact,contactid);
}
delete aIter;
return; 
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
        ENTRY( "Add_Test1",  Ctdeleteadd::Add_Test1L ),
        ENTRY( "Add_Test2",  Ctdeleteadd::Add_Test2L ),
        ENTRY( "Add_Test3",  Ctdeleteadd::Add_Test3L ),
        ENTRY( "Add_Test4",  Ctdeleteadd::Add_Test4L ),
        ENTRY( "Add_Test5",  Ctdeleteadd::Add_Test5L ),
        ENTRY( "Add_Test6",  Ctdeleteadd::Add_Test6L ), 
        ENTRY( "Add_Test7",  Ctdeleteadd::Add_Test7L ), 
        ENTRY( "Add_Test8",  Ctdeleteadd::Add_Test8L ), 
        //ENTRY( "Add_Test9",  Ctdeleteadd::Add_Test9L ), 
        ENTRY( "Add_Test10", Ctdeleteadd::Add_Test10L ), 
        ENTRY( "Add_Test11", Ctdeleteadd::Add_Test11L ), 
        ENTRY( "Add_Test12", Ctdeleteadd::Add_Test12L ),
        ENTRY( "Add_Test13", Ctdeleteadd::Add_Test13L ),
        
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

	    
    
 /* Adding single contact to default database*/
  TInt Ctdeleteadd::Add_Test1L( CStifItemParser& aItem )
    {


    TInt count =KErrGeneral ;
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Aaaa"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
    aItem.GetNextInt(count);
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
   
    /* check whether add api returns the expected error code */  
  if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;  


	 }

  /* Adding contact with invalid fieldname */
 TInt Ctdeleteadd::Add_Test2L( CStifItemParser& aItem )
    {


    TInt count =KErrGeneral ;
    _LIT8(KFirstName,"FrstName");
    _LIT(KName,"Aaaa"); 
    //instantiate service class object
    
    /* create contactitem with invalid fieldname "FrstName */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
     
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
   /* Add the contactitem */ 
    aItem.GetNextInt(count) ;
    TRAPD(err, icontactservice->AddL(icallback,0,singleContact))
    CActiveScheduler::Start();
     
  /* check whether Add api returns the expected error code */      
 if(-1 == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;

 }
 
 /* adding contact with more fields */
 TInt Ctdeleteadd::Add_Test3L( CStifItemParser& aItem )
 {
 
 
    TInt count =KErrGeneral ;
    _LIT8(KFirstName,"FirstName");
    _LIT(KFName,"XYZ");
    _LIT8(KLastName,"LastName");
    _LIT(KLName,"123");
    _LIT8(KPrefix,"Prefix");
    _LIT(KPfix,"Z");
    _LIT8(KSuffix,"Suffix");
    _LIT(KSfix,"A");
     _LIT8(KLandline,"LandPhoneHome");
    _LIT(KLandno,"08216666");
     _LIT8(KMobile,"MobilePhoneHome");
    _LIT(KMobno,"9900870");
    _LIT8(KFax,"FaxNumberHome");
    _LIT(KFaxno,"12345");
    _LIT8(KNoteField,"Note");
    _LIT(KNote,"my details");
     _LIT8(KJobTitle,"JobTitle");
    _LIT(KJob,"software engg");
    _LIT8(KEmail,"EmailWork");
    _LIT(KMail,"xyz@mail.com");
    _LIT8(KRing,"Ringtone");
    _LIT(KName,"C:\\data\\sounds\\digital\\around.mp3");  
   //instantiate service class object
     /* create contactitem to add */
    CSingleContactField* FName = CSingleContactField::NewL();
    CSingleContactField* LName = CSingleContactField::NewL();
    CSingleContactField* Pfix = CSingleContactField::NewL();
     CSingleContactField* Sfix = CSingleContactField::NewL();
    CSingleContactField* Landno = CSingleContactField::NewL();
     CSingleContactField* Mobno = CSingleContactField::NewL();
    CSingleContactField* Faxno = CSingleContactField::NewL();
   CSingleContactField* Note = CSingleContactField::NewL(); 
    CSingleContactField* Job = CSingleContactField::NewL();     
    CSingleContactField* Mail = CSingleContactField::NewL();
    CSingleContactField* Ring = CSingleContactField::NewL();
      
    CSingleContact* singleContact = CSingleContact::NewL();
    
       
    FName->SetFieldParamsL(KFirstName,KNullDesC,KFName);
    singleContact->AddFieldToContactL(FName);
    
    LName->SetFieldParamsL(KLastName,KNullDesC,KLName);
    singleContact->AddFieldToContactL(LName);
    
    Pfix->SetFieldParamsL(KPrefix,KNullDesC,KPfix);
    singleContact->AddFieldToContactL(Pfix);
    
    Sfix->SetFieldParamsL(KSuffix,KNullDesC,KSfix);
    singleContact->AddFieldToContactL(Sfix);
    
    Landno->SetFieldParamsL(KLandline,KNullDesC,KLandno);
    singleContact->AddFieldToContactL(Landno);
    
    Mobno->SetFieldParamsL(KMobile,KNullDesC,KMobno);
    singleContact->AddFieldToContactL(Mobno);
    
    Faxno->SetFieldParamsL(KFax,KNullDesC,KFaxno);
    singleContact->AddFieldToContactL(Faxno);
    
    Note->SetFieldParamsL(KNoteField,KNullDesC,KNote);    
    singleContact->AddFieldToContactL(Note);
    
    Job->SetFieldParamsL(KJobTitle,KNullDesC,KJob);
    singleContact->AddFieldToContactL(Job);
    
    Mail->SetFieldParamsL(KEmail,KNullDesC,KMail);
    singleContact->AddFieldToContactL(Mail);
    
    Ring->SetFieldParamsL(KRing,KNullDesC,KName);
    singleContact->AddFieldToContactL(Ring);
  
    
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
   
   TPtrC String;

//   TPtrC db1(_L("cntdb://c:testcontacts2.cdb"));
   
   /* get the filename for export */
     if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr ,"Failed to read input file name") ;
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }										
     
     TBuf<256> string1;
	 string1.Copy(String);
   
   icontactservice->GetListL(icallback,1,EContacts,KNullDesC8) ;
   CActiveScheduler::Start();
 	 
	
  icontactservice->ExportVCardL(icallback,2,string1,*contactid);
  CActiveScheduler::Start();
  
  
   	
    /* check whether add api returns the expected error code */  
  if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;   
 

 }

 
  /* Adding a group */
 TInt Ctdeleteadd::Add_Test4L( CStifItemParser& aItem )
  {

      // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
   
    TInt count;
   
   /* Group1 to add to phonebook */      
   _LIT(KGroup,"Group10")  ;
   
   aItem.GetNextInt(count) ;
   
   /*Add group1 to phonebook */
   icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
     CActiveScheduler::Start();
     
  /* check whether add api returns the expected error code */
 if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;

 }
 
  
  
   
  /* Adding the same group name twice */
 TInt Ctdeleteadd::Add_Test5L( CStifItemParser& aItem )
  {

      // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
   
    TInt count;
   
   /* Group1 to add to phonebook */      
   _LIT(KGroup,"Group1")  ;
   
   aItem.GetNextInt(count) ;
   
   /*Add group1 to phonebook */
   icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
     CActiveScheduler::Start();
     
  /* Add the same group1 to phonebook */   
   icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
   CActiveScheduler::Start();

  /* check whether add api returns the expected error code */
 if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;

 }
 
/* Adding same contact twice to default database*/
  TInt Ctdeleteadd::Add_Test6L( CStifItemParser& aItem )
    {


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
    
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
   
    /* check whether add api returns the expected error code */  
  if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;  


	 }

// same contact twice to different database
  TInt Ctdeleteadd::Add_Test7L( CStifItemParser& aItem )
    {

	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");			
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
    icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,KCntDbUri);
    CActiveScheduler::Start();
    
    icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,KCntDbUri);
    CActiveScheduler::Start();
   
    /* check whether add api returns the expected error code */  
  if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;  


	 }	 
 
/* Adding single contact to default database with the same key and different label*/

  TInt Ctdeleteadd::Add_Test8L( CStifItemParser& aItem )
    {


    TInt count =KErrGeneral ;
    
    _LIT8(KLandline,"LandPhoneHome");
    _LIT8(Anni,"Anniversary");
    _LIT(KLandno1,"08216666");
    
    _LIT(KLandno2,"08216667");
    _LIT(Land1,"no.1");
    _LIT(Land2,"no.2");
    //instantiate service class object
    
    /* create contactitem to add */ 
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField1 = CSingleContactField::NewL();
    CSingleContactField* singleContactField2 = CSingleContactField::NewL();
       
    singleContactField1->SetFieldParamsL(KLandline,Land1,KLandno1);
    singleContactField2->SetFieldParamsL(KLandline,Land2,KLandno2);
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
    
    CSingleContactField* singleContactField3 = CSingleContactField::NewL();
    CSingleContactField* singleContactField4 = CSingleContactField::NewL();
       
    singleContactField3->SetFieldParamsL(KLandline,Land1,KLandno1);
    singleContactField4->SetFieldParamsL(KLandline,Land2,KLandno2);
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
   
    /* check whether add api returns the expected error code */  
  if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;  


	 }
	 
	 /* adding a thumbnail*/
//TInt Ctdeleteadd::Add_Test9L( CStifItemParser& aItem )
//    {

//
//    TInt count =KErrGeneral ;
//   _LIT8(Thumbnail,"ThumbNailPic");
//    _LIT(KName,"C:\\data\\Images\\Pictures\\blue.png"); 
//    //instantiate service class object
    
//    /* create contactitem to add */
//    CSingleContact* singleContact = CSingleContact::NewL();
//   CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
//    singleContactField->SetFieldParamsL(Thumbnail,KNullDesC,KName);
//    singleContact->AddFieldToContactL(singleContactField);
  
    
//   aItem.GetNextInt(count) ;
    
//   /* Add the contactitem */
//   icontactservice->AddL(icallback,0,singleContact);
//    CActiveScheduler::Start();
   
//    /* check whether add api returns the expected error code */  
//  if(count == icallback->iError )
//      return KErrNone ;
      
//    return KErrGeneral ;  


//	 }
	 

/* Adding single contact to default database using contactid*/
  TInt Ctdeleteadd::Add_Test10L( CStifItemParser& aItem )
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
   iLog->Log(_L("Calling GetList"));
   icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield,EAsc,KCntDbUri);
   CActiveScheduler::Start();
   iLog->Log(_L("End of GetList"));
   TInt err1,err2;
   iLog->Log(_L("Calling Add")); 
   
   /*
   //-----------------------------------
   HBufC8* invalidid = HBufC8::NewL(15);
   TPtr8 strPtr= invalidid->Des();
   TBuf8<4> data;
   data.Append(_L("xyz"));
   strPtr.Append(data);
      
   myContact->SetContactId(invalidid);
   
   //------------------------------------
   */
   
   TRAP(err1,icontactservice->AddL(icallback,0,myContact,KNullDesC8,KNullDesC,KCntDbUri1));
   if(err1!=0 )
   {
   	iLog->Log(_L("Error returned while calling add")); 
   	return KErrNone ;
   }
   
   iLog->Log(_L("Starting Schudular")); 
   CActiveScheduler::Start();
   iLog->Log(_L("Error %d\n"),icallback->iError);
   iLog->Log(_L("Add successful")); 
   
   
  if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;  


	 }
	 
	 /* Adding a group and contact together*/
 TInt Ctdeleteadd::Add_Test11L( CStifItemParser& aItem )
  {

      // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
   
    TInt count;
   
   /* Group1 to add to phonebook */      
   _LIT(KGroup,"Group10")  ;
   
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Aaaa"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
   
   aItem.GetNextInt(count) ;
   
   /*Add group1 to phonebook */
   TInt err1;
   TRAPD(err,icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KGroup));
   if(err || err1)
   return KErrNone;
    CActiveScheduler::Start();
     
  /* check whether add api returns the expected error code */
 if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;

 }


/* Adding single contact to virtual database with the same key and different label*/

  TInt Ctdeleteadd::Add_Test12L( CStifItemParser& aItem )
    {


    TInt count =KErrGeneral ;
    _LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    _LIT8(KLandline,"LandPhoneHome");
    _LIT8(Anni,"Anniversary");
    _LIT(KLandno1,"08216666");
    
    _LIT(KLandno2,"08216667");
    _LIT(Land1,"no.1");
    _LIT(Land2,"no.2");
    //instantiate service class object
    
    /* create contactitem to add */ 
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField1 = CSingleContactField::NewL();
    CSingleContactField* singleContactField2 = CSingleContactField::NewL();
       
    singleContactField1->SetFieldParamsL(KLandline,Land1,KLandno1);
    singleContactField2->SetFieldParamsL(KLandline,Land2,KLandno2);
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
    
    CSingleContactField* singleContactField3 = CSingleContactField::NewL();
    CSingleContactField* singleContactField4 = CSingleContactField::NewL();
       
    singleContactField3->SetFieldParamsL(KLandline,Land1,KLandno1);
    singleContactField4->SetFieldParamsL(KLandline,Land2,KLandno2);
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,KCntDbUri);
    CActiveScheduler::Start();
   
    /* check whether add api returns the expected error code */  
  if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;  

 
	 }
	 
	 
	 /* Adding single contact to virtual database with the same key and same label*/

  TInt Ctdeleteadd::Add_Test13L( CStifItemParser& aItem )
    {


    TInt count =KErrGeneral ;
    _LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    _LIT8(KLandline,"LandPhoneHome");
    _LIT8(Anni,"Anniversary");
    _LIT(KLandno1,"abc");
    
    _LIT(KLandno2,"cba");
    _LIT(Land1,"no.1");
    _LIT(Land2,"no.2");
    //instantiate service class object
    
    /* create contactitem to add */ 
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField1 = CSingleContactField::NewL();
    CSingleContactField* singleContactField2 = CSingleContactField::NewL();
       
    singleContactField1->SetFieldParamsL(KLandline,Land1,KLandno1);
    singleContactField2->SetFieldParamsL(KLandline,Land1,KLandno2);
    singleContact->AddFieldToContactL(singleContactField1);
  	singleContact->AddFieldToContactL(singleContactField2);
    
    CSingleContactField* singleContactField3 = CSingleContactField::NewL();
    CSingleContactField* singleContactField4 = CSingleContactField::NewL();
       
    singleContactField3->SetFieldParamsL(KLandline,Land1,KLandno1);
    singleContactField4->SetFieldParamsL(KLandline,Land1,KLandno2);
    singleContact->AddFieldToContactL(singleContactField3);
  	singleContact->AddFieldToContactL(singleContactField4);
    aItem.GetNextInt(count) ;
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,KCntDbUri);
    CActiveScheduler::Start();
   
    /* check whether add api returns the expected error code */  
  if(count == icallback->iError )
      return KErrNone ;
      
    return KErrGeneral ;  

 
	 }
	 


//  End of File
