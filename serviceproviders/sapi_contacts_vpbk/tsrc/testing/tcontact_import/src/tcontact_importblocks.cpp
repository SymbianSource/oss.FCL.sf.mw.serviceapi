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
#include "tContact_import.h"

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

 TInt Iterator_cnt;
 
 HBufC8* contactid;
 CSingleContact* myContact=NULL;



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
    HBufC8* tmpid;
  RPointerArray<HBufC8> idarray ; 
  TBuf<100> grouplabel;
   
if(aError==KErrNone)
{
   aIter->NextL(myContact,tmpid);

  while(myContact)
 {
   Iterator_cnt++;           
   aIter->NextL(myContact,tmpid);

                    
 } //while
} //if

 delete aIter ;    
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
       ENTRY( "Import_Test1", Cteximport::Import_Test1L ),
       ENTRY( "Import_Test2", Cteximport::Import_Test2L ),
       ENTRY( "Import_Test3", Cteximport::Import_Test3L ),
       ENTRY( "Import_Test4", Cteximport::Import_Test4L ),
       ENTRY( "Import_Test5", Cteximport::Import_Test5L ),
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
TInt Cteximport::Import_Test1L( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_ValL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
   
  
            
     TPtrC String;
    /* get the filename for import */
      if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr , "Failed to read input file name");
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }
     
    
     TBuf<256> string1;
	 string1.Copy(String);
     TInt flag=0;

   /*call import */ 
    icontactservice->ImportVCardToStoreL(icallback,1,string1);
     CActiveScheduler::Start();

	 
   /* verify whther import returns the expected error */	 
     aItem.GetNextInt(flag) ;
	 if(icallback->iError == flag) 
     return KErrNone;
	 
    else
      return KErrGeneral;
 }
 
    
  /* Importing the same contact vcard file twice */
  TInt Cteximport::Import_Test2L( CStifItemParser& aItem )
 {

    // Print to UI
    	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_InvL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
   TPtrC String;
    
    /* get the filename for import */
     if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr , "Failed to read input file name") ;
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }										
     
     TBuf<256> string1;
	 string1.Copy(String);
				   
	 						   
	 TInt flag=0,cnt=0;
    
	 /*call import */  
	 icontactservice->ImportVCardToStoreL(icallback,1,string1);
     CActiveScheduler::Start();
     
     /*call import */ 
 	icontactservice->ImportVCardToStoreL(icallback,2,string1);
      CActiveScheduler::Start();
    
   TPtrC searchval(_L("import"));
   TBuf8<15> fstname(_L8("FirstName"));
   CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
   srchfield->AppendL(fstname);
   
   icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   CActiveScheduler::Start();
   
   /* verify whther import returns the expected error */	      
     aItem.GetNextInt(flag) ;
	 if(icallback->iError == flag)
	 {
	 	if(Iterator_cnt==1)
	 	return KErrNone;
	 }
     
	 
   
      return KErrGeneral;
   	 
    
 }   

TInt Cteximport::Import_Test3L( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_ValL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
   
  	TPtrC db1(_L("cntdb://c:temp.cdb"));
            
     TPtrC String;
    /* get the filename for import */
      if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr , "Failed to read input file name");
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }
     
    
     TBuf<256> string1;
	 string1.Copy(String);
     TInt flag=0;

   /*call import */ 
    icontactservice->ImportVCardToStoreL(icallback,1,string1,db1);
     CActiveScheduler::Start();

	 
   /* verify whther import returns the expected error */	 
     aItem.GetNextInt(flag) ;
	 if(icallback->iError == flag) 
     return KErrNone;
	 
    else
      return KErrGeneral;
 }
 
 /* Importing a contact and Getlist the same contact */
 
 TInt Cteximport::Import_Test4L( CStifItemParser& aItem )
    {
	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_ValL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
   
  
            
     TPtrC String;
    /* get the filename for import */
      if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr , "Failed to read input file name");
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }
     
    
     TBuf<256> string1;
	 string1.Copy(String);
     TInt flag=0;

   /*call import */ 
    icontactservice->ImportVCardToStoreL(icallback,1,string1);
     CActiveScheduler::Start();
	
	TPtrC searchval(_L("Lee"));
    TBuf8<15> fstname(_L8("LastName"));
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    srchfield->AppendL(fstname);
	icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
    CActiveScheduler::Start();
    
  //  icontactservice->GetListL(icallback,0,EContacts,KNullDesC8);
  //  CActiveScheduler::Start();
   /* verify whther import returns the expected error */	 
     aItem.GetNextInt(flag) ;
	 if(icallback->iError == flag) 
     return KErrNone;
	 
    else
      return KErrGeneral;
 }
 
 /* Importing the same contact vcard file twice */
  TInt Cteximport::Import_Test5L( CStifItemParser& aItem )
 {

    // Print to UI
    	_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In Import_InvL" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
   TPtrC String;
    
    /* get the filename for import */
     if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr , "Failed to read input file name") ;
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }										
     
     TBuf<256> string1;
	 string1.Copy(String);
				   
	 if(aItem.GetNextString(String) != KErrNone )  
     {
     	_LIT(Kerr , "Failed to read input file name") ;
     	iLog->Log(Kerr) ;
     	return KErrGeneral ;
     }										
     
     TBuf<256> string2;
	 string2.Copy(String);						   
	 TInt flag=0,cnt=0;
    
	 /*call import */  
	 icontactservice->ImportVCardToStoreL(icallback,1,string1);
     CActiveScheduler::Start();
     
     /*call import */ 
 	icontactservice->ImportVCardToStoreL(icallback,2,string2);
      CActiveScheduler::Start();
    
   TPtrC searchval(_L("first"));
   TBuf8<15> fstname(_L8("FirstName"));
   CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
   srchfield->AppendL(fstname);
   
   icontactservice->GetListL(icallback,0,EContacts,KNullDesC8,searchval,srchfield);
   CActiveScheduler::Start();
   
   /* verify whther import returns the expected error */	      
     aItem.GetNextInt(flag) ;
	 if(icallback->iError == flag)
	 {
	 	if(Iterator_cnt==2)
	 	return KErrNone;
	 }
     
	 
   
      return KErrGeneral;
   	 
    
 }   

//  End of File
