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
#include "tcontact_export.h"

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
 
 HBufC8* contactid=NULL;
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
  iError= aError;
  CActiveScheduler::Stop();
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
    } 

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Cteximport::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Cteximport::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Cteximport::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Cteximport::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
       
       ENTRY( "Export_Test1", Cteximport::Export_Test1L ),
       ENTRY( "Export_Test2", Cteximport::Export_Test2L ),
       ENTRY( "Export_Test3", Cteximport::Export_Test3L ),
       ENTRY( "Export_Test4", Cteximport::Export_Test4L ),
       ENTRY( "Export_Test5", Cteximport::Export_Test5L ),
	   ENTRY( "Export_Test6", Cteximport::Export_Test6L ),
	   ENTRY( "Export_Test7", Cteximport::Export_Test7L ),
	   ENTRY( "Export_Test8", Cteximport::Export_Test8L ),
	   //ENTRY( "Export_Test9", Cteximport::Export_Test9L ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Cteximport::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

  /* export a single contact to a new file ; only filename specified */
TInt Cteximport::Export_Test1L( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_InvL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
    TPtrC String;
  
   
   /* get the filename for export */
     if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr ,"Failed to read input file name") ;
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }										
     
     TBuf<256> string1;
	 string1.Copy(String);
 						   
	 						   
	 TInt flag=0,cnt=0;
	 
	 /*call getlist to get the contactid for export */ \
	 TInt err1, err2;
  TRAP(err1,icontactservice->GetListL(icallback,1,EContacts,KNullDesC8));
   CActiveScheduler::Start();
 	 
	/*call export */ 
  
  TRAP(err1,icontactservice->ExportVCardL(icallback,2,string1,KNullDesC8));
  if(err1 || err2)
  return KErrNone;
  CActiveScheduler::Start();
 
 
 /* verify whther export returns the expected error */	 
   aItem.GetNextInt(flag) ;
   if(icallback->iError)
   return KErrNone;
   if(icallback->iError == flag) 
   return KErrNone;

 }   

/* exporting 2 contacts */
TInt Cteximport::Export_Test2L( CStifItemParser& aItem )
  {

    // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_InvL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
    TPtrC String;
    
  
    /* get the filename for export */ 
     if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr , "Failed to read input file name") ;
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }										
     
     TBuf<256> string1,string2,string3;
	 string1.Copy(String);
	 
   if(aItem.GetNextString(String) != KErrNone )  
    {
     	_LIT(Kerr , "Failed to read input file name") ;
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }										
     
    string2.Copy(String); 
    
    if(aItem.GetNextString(String) != KErrNone )  
    {
     	_LIT(Kerr , "Failed to read input file name") ;
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }										
     
    string3.Copy(String); 
	 TInt flag=0,cnt=0;
	 
	 
	 icontactservice->ImportVCardToStoreL(icallback,1,string3);
     CActiveScheduler::Start();
     
  /*call getlist to get the contactid for export */ 
  icontactservice->GetListL(icallback,1,EContacts)  ;
   CActiveScheduler::Start();
   
/*call export */	 
icontactservice->ExportVCardL(icallback,1,string1,*contactid);
 CActiveScheduler::Start();
 
icontactservice->ExportVCardL(icallback,2,string2,*contactid);
CActiveScheduler::Start();


/* verify whther export returns the expected error */	 
   aItem.GetNextInt(flag) ;
if(icallback->iError == flag) 
   return KErrNone;
	 
   return KErrGeneral;
               
     
 } 
   
  
  /* exporting non existent contact */
 TInt Cteximport::Export_Test3L( CStifItemParser& aItem )
 {

    // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_InvL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
   TPtrC String;
   
 
   
  /* get the filename for export */ 
     if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr , "Failed to read input file name") ;
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }										
     
     TBuf<256> string1;
	 string1.Copy(String);
	 
	 						   
	 TInt flag=0,cnt=0;
	 
	 
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Goat"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
    
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
   

  /*call getlist to get the contactid for export */ 	 
   icontactservice->GetListL(icallback,1,EContacts)  ;
     CActiveScheduler::Start();
	 
 
    RPointerArray<TDesC8> ptr ; //= new (ELeave) CArrayFixFlat<TDesC8>(1);
    ptr.Append(contactid);   						  
	
	icontactservice->DeleteL(icallback,2,ptr);
	
	 CActiveScheduler::Start();
	 
	/*call export */ 
    icontactservice->ExportVCardL(icallback,2,string1,*contactid);
	CActiveScheduler::Start();
      
     /* verify whther export returns the expected error */	 
     aItem.GetNextInt(flag) ;
	 if(icallback->iError) 
     return KErrNone;
	 

     return KErrGeneral;
               
	 
    
    }    
    
/*Exporting single contact to a file with existing filename */  
 TInt Cteximport::Export_Test4L( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_InvL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
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
 						   
	 						   
	 TInt flag=0,cnt=0;

	_LIT8(KFirstName,"FirstName");
    _LIT(KName,"Nokia"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
    
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    	
  /*call getlist to get the contactid for export */ 	 
  icontactservice->GetListL(icallback,1,EContacts,KNullDesC8)  ;
   CActiveScheduler::Start();
 	 
	
 icontactservice->ExportVCardL(icallback,2,string1,*contactid);
  CActiveScheduler::Start();
  
  icontactservice->ExportVCardL(icallback,2,string1,*contactid);
  CActiveScheduler::Start();
  
 
 /* verify whther export returns the expected error */	  
   aItem.GetNextInt(flag) ;
 if(icallback->iError==flag) 
     return KErrNone;


   return KErrGeneral;
               
  
 }   

/* Negative testcase when the file name to be exported is not specified*/

TInt Cteximport::Export_Test5L( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_InvL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
     TBuf<256> string2;
	  
	 TInt flag=0,cnt=0;
	 
	 /*call getlist to get the contactid for export */ 
  icontactservice->GetListL(icallback,1,EContacts,KNullDesC8)  ;
   CActiveScheduler::Start();
 	 
	/*call export */ 
 icontactservice->ExportVCardL(icallback,2,string2,*contactid);
  CActiveScheduler::Start();
 
 
 /* verify whther export returns the expected error */	 
   
 if(icallback->iError !=0) 
     return KErrNone;

	 
   return KErrGeneral;
               
  
 }   

/* exporting from a different database*/

TInt Cteximport::Export_Test6L( CStifItemParser& aItem )
    {

	    // Print to UI
	    _LIT( Ktsapicontacts, "tsapicontacts" );
	    _LIT( KExample, "In Import_InvL" );
	    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
	    // Print to log file
	    iLog->Log( KExample );
	    
	    TPtrC String;
  
   
	   /* get the filename for export */
	     if(aItem.GetNextString(String) != KErrNone )  
	     {
	     	_LIT(Kerr ,"Failed to read input file name") ;
	     	iLog->Log(Kerr) ;
	     	return KErrGeneral ;
	     }										
	     
	     TBuf<256> string1;
		 string1.Copy(String);
	 
		 TPtrC db1(_L("cntdb://c:temp.cdb")); 
		 TInt flag=0,cnt=0;
		 
		 _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Goat"); 
    //instantiate service class object
    
    /* create contactitem to add */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
       
    singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
    
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,db1);
    CActiveScheduler::Start();
		 /*call getlist to get the contactid for export */ 
	     icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,db1)  ;
	   CActiveScheduler::Start();
	 	 
		/*call export */ 
	 icontactservice->ExportVCardL(icallback,2,string1,*contactid,db1);
	  CActiveScheduler::Start();
	 
	 
	 /* verify whther export returns the expected error */	 
	 aItem.GetNextInt(flag) ;
 	 if(icallback->iError == flag) 
	     return KErrNone;

		 
	   return KErrGeneral;
               
  
 }   





TInt Cteximport::Export_Test7L( CStifItemParser& aItem )
    {

	    // Print to UI
	    _LIT( Ktsapicontacts, "tsapicontacts" );
	    _LIT( KExample, "In Import_InvL" );
	    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
	    // Print to log file
	    iLog->Log( KExample );
	    
	    TPtrC String;
  
   
	   /* get the filename for export */
	     if(aItem.GetNextString(String) != KErrNone )  
	     {
	     	_LIT(Kerr ,"Failed to read input file name") ;
	     	iLog->Log(Kerr) ;
	     	return KErrGeneral ;
	     }										
	     
	     TBuf<256> string1;
		 string1.Copy(String);
	 
		 TPtrC db1(_L("cntdb://c:temp.cdb")); 
		 TInt flag=0,cnt=0;
		 
		 _LIT(KGroup,"Group10")  ;
   
  
   		/*Add group1 to phonebook */
   		icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
     	CActiveScheduler::Start();
     	
		 /*call getlist to get the contactid for export */ 
	     icontactservice->GetListL(icallback,1,EGroups,KNullDesC8)  ;
	   CActiveScheduler::Start();
	 	 
		/*call export */ 
		TInt err1;
	 TRAP(err1,icontactservice->ExportVCardL(icallback,2,string1,*contactid));
	  if(!err1)
	  CActiveScheduler::Start();
	 
	 
	 /* verify whther export returns the expected error */	 
	 aItem.GetNextInt(flag) ;
 	 if(!icallback->iError) 
	     return KErrNone;

		 
	   return KErrGeneral;
               
  
 }   

/* exporting of a database*/

TInt Cteximport::Export_Test8L( CStifItemParser& aItem )
    {

	    // Print to UI
	    _LIT( Ktsapicontacts, "tsapicontacts" );
	    _LIT( KExample, "In Import_InvL" );
	    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
	    // Print to log file
	    iLog->Log( KExample );
	    
	    TPtrC String;
  
   
	   /* get the filename for export */
	     if(aItem.GetNextString(String) != KErrNone )  
	     {
	     	_LIT(Kerr ,"Failed to read input file name") ;
	     	iLog->Log(Kerr) ;
	     	return KErrGeneral ;
	     }										
	     
	     TBuf<256> string1;
		 string1.Copy(String);
	 
		 TPtrC db1(_L("cntdb://c:temp.cdb")); 
		 TInt flag=0,cnt=0;
		 
		 
		 /*call getlist to get the contactid for export */ 
		 int err;
	    TRAP(err,icontactservice->GetListL(icallback,1,EDatabase,KNullDesC8)) ;
	    if(err)
	    return KErrNone;
	    
	   CActiveScheduler::Start();
	 	 
		/*call export */ 
	 icontactservice->ExportVCardL(icallback,2,string1,*contactid);
	  CActiveScheduler::Start();
	 
	 
	 /* verify whther export returns the expected error */	 
	 aItem.GetNextInt(flag) ;
 	 if(icallback->iError == flag) 
	     return KErrNone;

		 
	   return KErrGeneral;
               
  
 }   

/* importing and exporting thumbnail  */
//TInt Cteximport::Export_Test9L( CStifItemParser& aItem )
//    {

//	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
//    _LIT( Ktsapicontacts, "tsapicontacts" );
//    _LIT( KExample, "In Import_ValL" );
//    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
//    // Print to log file
//   iLog->Log( KExample );
   
  
            
//     TPtrC String;
    /* get the filename for import */
//      if(aItem.GetNextString(String) != KErrNone )  
//     {
//     	_LIT(Kerr , "Failed to read input file name");
//     	iLog->Log(Kerr) ;
//     	return KErrGeneral ;
//     }
     
    
//     TBuf<256> string1;
//	 string1.Copy(String);
//     TInt flag=0;

   /*call import */ 
//    icontactservice->ImportVCardToStoreL(icallback,1,string1);
//     CActiveScheduler::Start();
     
//    TBuf8<15> fstname(_L8("ThumbNailPic"));
//    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
//    srchfield->AppendL(fstname);
//    icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,KCntDbUri,KNullDesC,srchfield);
//    CActiveScheduler::Start();
    
    
   /* get the filename for export */
//     if(aItem.GetNextString(String) != KErrNone )  
//     {
//     	_LIT(Kerr ,"Failed to read input file name") ;
//     	iLog->Log(Kerr) ;
//     	return KErrGeneral ;
//     }										
     
//   	 string1.Copy(String);
	 
//    icontactservice->ExportVCardL(icallback,1,string1,*contactid);
//	CActiveScheduler::Start();
	
//	aItem.GetNextInt(flag) ;
// 	if(icallback->iError == flag) 
//	     return KErrNone;

		 
//	return KErrGeneral;
     
     

// }   

    
// -----------------------------------------------------------------------------
// Cteximport::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Cteximport::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
