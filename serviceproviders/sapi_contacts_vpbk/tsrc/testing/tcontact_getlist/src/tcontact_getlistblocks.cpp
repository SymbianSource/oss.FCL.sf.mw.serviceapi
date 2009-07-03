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
#include "tContact_getlist.h"

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

// ============================ MEMBER FUNCTIONS ===============================


TInt tCount=0;
 HBufC8* contactid;
 CSingleContact* myContact=NULL;
 
void CContactCallback::HandleReturnValue( TOperationEvent aEventId, const TInt& aError, TInt aTransId )
{
  iError= aError;
  CActiveScheduler::Stop();
}


 void CContactCallback:: HandleReturnIter(const TInt& aError, CContactIter* aIter, TInt aTransId )
 {
 

    CActiveScheduler::Stop();

    CSingleContactField* field = NULL; 
    HBufC8* buf = NULL;
    TPtrC8 buf1;
    TPtrC buf2;
    TPtrC buf3;
    TInt count=0 ;	     

   
if(aError==KErrNone)
{
   aIter->NextL(myContact,contactid);

  while(myContact)
 { 	
 	tCount++;
    if(myContact)
   {
     count++; 
     TInt len,i ;
     len=myContact->FieldCount();
     for(i=0;i<len;i++)
      {
        field = myContact->FieldAt(i);
         if(field!=NULL)
             {                
             field->GetFieldDataL(buf1,buf2,buf3);                
                 //if(buf1.CompareF(_L8("emailgen"))==0) break;                            
             }
                          
       } //for 
           
   } //if
    
   aIter->NextL(myContact,contactid);

                    
 } //while
 delete  aIter;
} //if
    
 

 } 

 // -----------------------------------------------------------------------------
// Ctmanualcontacts::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctmanualcontacts::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctmanualcontacts::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctmanualcontacts::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "GetList_Test1", Ctmanualcontacts::GetList_Test1L ),
        ENTRY( "GetList_Test2", Ctmanualcontacts::GetList_Test2L ),
        ENTRY( "GetList_Test3", Ctmanualcontacts::GetList_Test3L ),
        ENTRY( "GetList_Test4", Ctmanualcontacts::GetList_Test4L ),
        ENTRY( "GetList_Test5", Ctmanualcontacts::GetList_Test5L ),
        ENTRY( "GetList_Test6", Ctmanualcontacts::GetList_Test6L ), 
        ENTRY( "GetList_Test7", Ctmanualcontacts::GetList_Test7L ), 
        ENTRY( "GetList_Test8", Ctmanualcontacts::GetList_Test8L ), 
        ENTRY( "GetList_Test9", Ctmanualcontacts::GetList_Test9L ),  
        ENTRY( "GetList_Test10", Ctmanualcontacts::GetList_Test10L ),   
        //ENTRY( "GetList_Test11", Ctmanualcontacts::GetList_Test11L ),       

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctmanualcontacts::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

 /* get database lists ,manual,only contacts.cdb will be listed*/ 	   
 TInt Ctmanualcontacts::GetList_Test1L( CStifItemParser& aItem )
    {

  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
        
        
    CContactIter* iter = CContactIter::NewL();
    icontactservice->GetListL(*iter);
    
    TPtrC buf;
     
     iter->NextL(buf);
   while(buf.Compare(KNullDesC)!=0)
      {
          iter->NextL(buf);
  	  } 

    return KErrNone ;   
  
 }


/* get all contacts from the phonebook ie contacts.cdb,manual*/
TInt Ctmanualcontacts::GetList_Test2L( CStifItemParser& aItem )
{

  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
 icontactservice->GetListL(icallback,1,EContacts);  
  
 CActiveScheduler::Start();
     
   
 return KErrNone ;   
  
    
  }


/* groups are not created,try to get grouplist,expected result NULL */
  TInt Ctmanualcontacts::GetList_Test3L( CStifItemParser& aItem )
    {

  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    _LIT(KCntDbUri, "cntdb://c:contacts_test_group.cdb");
   TBuf8<15> fstname(_L8("FirstName"));
    
    TBufC8<25> cid ;
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    TPtrC searchval(_L("Getlist_test"));  
    srchfield->AppendL(fstname);
    icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,searchval,NULL,EAsc,KCntDbUri);
  
   CActiveScheduler::Start();
     
   if(myContact ==NULL)
        return KErrNone ;   
  
    return KErrGeneral;
  }
 
 /* get group list ,groups are there but no contacts in it */
   TInt Ctmanualcontacts::GetList_Test4L( CStifItemParser& aItem )
    {

  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    _LIT(KGroup,"friends1") ;
   
       
   /*Add group1 to phonebook */
    icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
    CActiveScheduler::Start();
      
    icontactservice->GetListL(icallback,1,EGroups);
  
    CActiveScheduler::Start();
     
    if(tCount!=0)
    return KErrNone ;
    
    return KErrGeneral;
  
   
  }        

/// repeated  
  /* search for Lee in tmp.cdb */ 
  
  TInt Ctmanualcontacts::GetList_Test5L( CStifItemParser& aItem )
{

  // Print to UI
  	 _LIT(KCntDbUri1, "cntdb://c:tmp.cdb");
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
   _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Anitha"); 
   _LIT(KFirst,"First Name");
   
    //instantiate service class object
    
    /* create contactitem with invalid fieldname "FrstName */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
     
    singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
   /* Add the contactitem */ 
    
    icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,KCntDbUri1);
    CActiveScheduler::Start();
    
     
    _LIT(Kname,"Lee");
    
    TBuf8<15> fstname(_L8("FirstName"));
    
    TBufC8<25> cid ;
    CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
       
    srchfield->AppendL(fstname);
       
    
    TPtrC searchval(_L("Anitha"));
    TOrder sortorder =EAsc;
    
    icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,searchval,srchfield,EAsc,KCntDbUri1); 
  
  CActiveScheduler::Start();
     
  	  if(tCount!=0)
     return KErrNone ;
           
  
  	 return KErrGeneral ;
  }
  
//  search for invalid search field  ,ex:search for Lee as lastname in tmp.cdb 
  
 TInt Ctmanualcontacts::GetList_Test6L( CStifItemParser& aItem )
{

  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT(KCntDbUri, "cntdb://c:tmp.cdb");  	           
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Abhay"); 
   _LIT(KFirst,"First Name");
   
    //instantiate service class object
    
    /* create contactitem with invalid fieldname "FrstName */
    CSingleContact* singleContact = CSingleContact::NewL();
    CSingleContactField* singleContactField = CSingleContactField::NewL();
    
     
    singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
    singleContact->AddFieldToContactL(singleContactField);
  
    
   /* Add the contactitem */ 
    
    icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,KCntDbUri);
    CActiveScheduler::Start();
    
    
   _LIT(Kname,"Lee");
 
   TBuf8<15> lstname(_L8("LastName"));
    
   TBufC8<25> cid ;
  CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
       
  srchfield->AppendL(lstname);
       
    
  TPtrC searchval(_L("Getlist_testing"));

 icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,searchval,srchfield);
  

   CActiveScheduler::Start();  
     
     if(tCount ==0)
        return KErrNone ;   
  
    else
     return KErrGeneral;
     
  }    
  
 /* list contacts in descending order */ 
   TInt Ctmanualcontacts::GetList_Test7L( CStifItemParser& aItem )
{
	_LIT(KCntDbUri, "cntdb://c:tmp.cdb");  	    
     // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
 
  
 icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EDesc);  //,cid,KCntDbUri1,searchval,srchfield); 
  
 CActiveScheduler::Start();
     
   
 return KErrNone ;   

 } 

/* testcase :list groups in descending  order ; 
Listing in descending order can be done only on contacts not on groups,databases*/
 TInt Ctmanualcontacts::GetList_Test8L( CStifItemParser& aItem )
{

		_LIT(KCntDbUri, "cntdb://c:tmp_groups.cdb");  	    
  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
 

    icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,EDesc,KCntDbUri);  //,cid,KCntDbUri1,searchval,srchfield); 
  
    CActiveScheduler::Start();
     
   
 return KErrNone ;   

}

 /* list contacts ,ENULL cannot be used in sortingorder*/
 TInt Ctmanualcontacts::GetList_Test9L( CStifItemParser& aItem )
{

	_LIT(KCntDbUri, "cntdb://c:tmp_ENul.cdb"); 
  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
 
    
 
icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc);  //,cid,KCntDbUri1,searchval,srchfield); 
  
 CActiveScheduler::Start();
     
   
 return KErrNone ;   

}

/* list the databases, 2 databases should be listed - contacts.cdb,tmp.cdb */
TInt Ctmanualcontacts::GetList_Test10L( CStifItemParser& aItem )
{

     // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
        
 
  _LIT(KCntDbUri1, "cntdb://c:tmp.cdb");  	   
 icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri1);  //,cid,KCntDbUri1,searchval,srchfield); 
  
 CActiveScheduler::Start(); 
        
    CContactIter* iter = CContactIter::NewL();
    icontactservice->GetListL(*iter);
    
    TPtrC buf(_L(""));
     
     iter->NextL(buf);
     TInt count=0;
   while(buf.Compare(KNullDesC)!=0)
      {	  count++;
          iter->NextL(buf);
  	  } 
	if(count==2)
    return KErrNone ;   
	
	return KErrGeneral;
}


/* get group list ,groups are there in the simdatabase
   TInt Ctmanualcontacts::GetList_Test11L( CStifItemParser& aItem )
    {

  // Print to UI
  
  	_LIT(KCntDbUri, "sim://global_adn"); 
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    _LIT(KGroup,"friends1") ;
   
       
   /*Add group1 to phonebook 
    icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup,KCntDbUri);
    CActiveScheduler::Start();
      
    icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri);
  
    CActiveScheduler::Start();
     
    if(tCount!=0)
    return KErrNone ;
    
    return KErrGeneral;
  
   
  } */       


// -----------------------------------------------------------------------------
// Ctmanualcontacts::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctmanualcontacts::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
