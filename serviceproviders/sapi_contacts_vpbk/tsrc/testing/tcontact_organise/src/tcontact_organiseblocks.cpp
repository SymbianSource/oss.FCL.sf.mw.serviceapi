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
#include "tContact_organise.h"


 TInt handleiter_cnt;
 

 CSingleContact* myContact=NULL;
 TBuf<25> KCompare ;
 TBuf8<100> contactid ;
 enum flag {GROUP = 1,CONTACT }status;
 void CContactCallback::HandleReturnArray( const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId )
     {
     CActiveScheduler::Stop();
     iError= aError ;
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
   TPtrC8 buf1;
   TPtrC buf2;
   TPtrC buf3;
   TInt count=0 ;	     
    HBufC8* tmpid;
  RPointerArray<TDesC8> idarray ; 
  TPtrC grouplabel;
   
if(aError==KErrNone)
{
   aIter->NextL(myContact,tmpid);

  while(myContact)
 {
   if(myContact)
     {
     contactid = *tmpid ;
   CleanupStack::PushL(myContact);
   //CleanupStack::PushL(tmpid); 
  
      // count++; 
        TInt len,i ;
     len=myContact->FieldCount();
   //        *contactid = myContact->GetContactId() ;
       for(i=0;i<len;i++)
     {
      field = myContact->FieldAt(i);
      if(field!=NULL)
      {       
        if(status==GROUP)
        {         
         field->GetFieldDataL(grouplabel,idarray);                
         if(grouplabel.Compare(KCompare)==0) break;                            
         }
       else
       {
         field->GetFieldDataL(buf1,buf2,buf3);
       }   
     }
                          
     } //for 
       
     // CleanupStack::PopAndDestroy(tmpid);
      CleanupStack::PopAndDestroy(myContact);      
           
     }
   
   if(grouplabel.Compare(KCompare)==0) break;                
   aIter->NextL(myContact,tmpid);

                    
 } //while
} //if

 delete aIter ;        

} 

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

// -----------------------------------------------------------------------------
// Ctmanualother::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctmanualother:: Delete() 
    {  }

// -----------------------------------------------------------------------------
// Ctmanualother::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctmanualother::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
       ENTRY( "Add_to_group1", Ctmanualother::Add_to_group1L ),  
       ENTRY( "Add_to_group2", Ctmanualother::Add_to_group2L ),
       ENTRY( "Add_to_group3", Ctmanualother::Add_to_group3L ),
       ENTRY( "Delete_from_group2", Ctmanualother::Delete_from_group2L ),
       ENTRY( "Delete_from_group3", Ctmanualother::Delete_from_group3L ),
       ENTRY( "Delete_from_group4", Ctmanualother::Delete_from_group4L ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctmanualother::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

  /*Adding a contact to the group */  
 TInt Ctmanualother::Add_to_group1L( CStifItemParser& aItem )
 {
 
  _LIT( Ktsapicontacts, "torganise");
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
   TInt count= KErrGeneral;
   RPointerArray<TDesC8> ptr;              
  _LIT(KGroup,"GroupA")  ;
   _LIT(KNull,"*****")  ;
   
  aItem.GetNextInt(count) ;
   
   /* add group4 to phonebook */
  icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
  CActiveScheduler::Start();
  
  status = GROUP ;
  KCompare=KGroup ;
  
  /* get contactid of groupA ,store it in cid*/
  icontactservice->GetListL(icallback,1,EGroups);
  CActiveScheduler::Start();
  
 // HBufC8* cid =HBufC8 :: NewL(30);
  
  TBuf8<100> groupid = contactid ;
  
  status=CONTACT ;  
  KCompare = KNull;
  
  /* get  the contactid of any contact */
  icontactservice->GetListL(icallback,2,EContacts);
  CActiveScheduler::Start();
   
 
    
  HBufC8* contactId1 = contactid.AllocLC();
  CleanupStack::Pop();
   /* Append the contactid to ptr */
  ptr.AppendL(contactId1); 						  
      
 
      
 
 /* Add 2 contacts,1 valid ,1 invalid contact from the  group4 */
 icontactservice->OrganiseGroupsL(icallback,3,groupid,ptr,ETrue);
 CActiveScheduler::Start();								    

  if(count == icallback->iError )
     return KErrNone ;
      
    return KErrGeneral ;
 
      
 
 }

 

 /*Add 2 contacts to group, 1 existing,other non existing */  
 TInt Ctmanualother::Add_to_group2L( CStifItemParser& aItem )
 {
 
  _LIT( Ktsapicontacts, "torganise");
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
   TInt count= KErrGeneral;
   RPointerArray<TDesC8> ptr ;              
  _LIT(KGroup,"Group4")  ;
   _LIT(KNull,"*****")  ;
   
  aItem.GetNextInt(count) ;
   
   
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
    
    /* Add the contactitem */
    icontactservice->AddL(icallback,0,singleContact);
    CActiveScheduler::Start();
    
   /* add group4 to phonebook */
  icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
  CActiveScheduler::Start();
  
  status = GROUP ;
  KCompare=KGroup ;
  
  /* get contactid of group4 ,store it in cid*/
  icontactservice->GetListL(icallback,1,EGroups);
  CActiveScheduler::Start();
  
 // HBufC8* cid =HBufC8 :: NewL(30);
  
  TBuf8<100> groupid = contactid ;
  
  status=CONTACT ;  
  KCompare = KNull;
  
  /* get  the contactid of any contact */
  icontactservice->GetListL(icallback,2,EContacts);
  CActiveScheduler::Start();
   
 
    
  HBufC8* contactId1 = contactid.AllocLC();
  CleanupStack::Pop();
   /* Append the contactid to ptr */
  TRAPD(err1,ptr.AppendL(contactId1)); 						  
      
       								    
   								  
  /* delete that contact from phonebook*/  
  icontactservice->DeleteL(icallback,2,ptr);
  CActiveScheduler::Start();
 
 
 /* get  the contactid of any other contact */
  icontactservice->GetListL(icallback,2,EContacts);
  CActiveScheduler::Start();
  
  ptr.Reset(); 
  /* append one more contactid to ptr */    
  HBufC8* contactId2 = contactid.AllocLC();
  CleanupStack::Pop();
   /* Append the contactid to ptr */
    TRAPD(err2,ptr.AppendL(contactId2)); 						  
      
 
 /* Add 2 contacts,1 valid ,1 invalid contact from the  group4 */
 icontactservice->OrganiseGroupsL(icallback,3,groupid,ptr,ETrue);
 CActiveScheduler::Start();								    

  if(!icallback->iError )
     return KErrNone ;
      
    return KErrGeneral ;
 
      
 
 }
 /*	 Add 1 nonexitent contact to group 5 */
 TInt Ctmanualother::Add_to_group3L( CStifItemParser& aItem )
 {
 
  _LIT( Ktsapicontacts, "torganise");
  _LIT( KExample, "In GetList_Test1L" );
  TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
  iLog->Log( KExample );
    
  TInt count= KErrGeneral;
  RPointerArray<TDesC8> ptr ;              
  _LIT(KGroup,"Group5")  ;
  _LIT(KNull,"*****")  ;
   
  aItem.GetNextInt(count) ;
  
   /* add group5 to phonebook */    
 icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
 CActiveScheduler::Start();
 
  status = GROUP ;
  KCompare=KGroup ; 
  
  /* get contactid of group5 ,store it in cid*/
  icontactservice->GetListL(icallback,1,EGroups);
  CActiveScheduler::Start();
  
   
  TBuf8<100> groupid = contactid ;
 

  status = CONTACT ;
  KCompare = KNull ;
  
  /* get  the contactid of any contact */
 icontactservice->GetListL(icallback,2,EContacts);
  CActiveScheduler::Start();
   
      
  TBuf8<100> cid = contactid ;
    
  HBufC8* contactId1 = contactid.AllocLC();
  CleanupStack::Pop();
   /* Append the contactid to ptr */
  TRAPD(err1,ptr.AppendL(contactId1)); 						  
      
      								    
 /* delete that contact from phonebook*/  								    
 icontactservice->DeleteL(icallback,3,ptr);
  CActiveScheduler::Start();
 
 /* Add that contact to group5 */
 icontactservice->OrganiseGroupsL(icallback,4,groupid,ptr,ETrue);
 CActiveScheduler::Start();								    

  if(count == icallback->iError )
     return KErrNone ;
      
    return KErrGeneral ;
 
 
}


 
 
 /* disassociate a contact from group */    
TInt Ctmanualother::Delete_from_group2L( CStifItemParser& aItem )
 {
  
  
   // Print to UI
  _LIT( Ktsapicontacts, "torganise" );
  _LIT( KExample, "In GetList_Test1L" );
  TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
  TInt count= KErrGeneral;
  RPointerArray<TDesC8> ptr ;              
  _LIT(KGroup,"Group3")  ;
  _LIT(KNull,"*****")  ;
   
 aItem.GetNextInt(count) ;
 
 status = GROUP;
 KCompare = KGroup ;
 
  /* add group3 to phonebook */  
 icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
  CActiveScheduler::Start();
  
  /* get contactid of group3 ,store it in cid*/
 icontactservice->GetListL(icallback,1,EGroups);
  CActiveScheduler::Start();
  
 TBuf8<100> groupid = contactid ;
 
  status = CONTACT ;
  KCompare = KNull ;
  
  /* get  the contactid of any contact */
  icontactservice->GetListL(icallback,2,EContacts);
   CActiveScheduler::Start();
   
    
 
  HBufC8* contactId1 = contactid.AllocLC();
  CleanupStack::Pop();
  /* Append the contactid to ptr */
  TRAPD(err1,ptr.AppendL(contactId1)); 									    
   								    
 
 /* Add the contact to the group */
 icontactservice->OrganiseGroupsL(icallback,3,groupid,ptr,ETrue);
 CActiveScheduler::Start();	
 
 /* delete the contact from group */
 icontactservice->OrganiseGroupsL(icallback,4,groupid,ptr,EFalse);
 CActiveScheduler::Start();								    

  if(count == icallback->iError )
     return KErrNone ;
      
    return KErrGeneral ; 
  
}

  /* disassociate the same contact from group twice */    
TInt Ctmanualother::Delete_from_group3L( CStifItemParser& aItem )
 {
  
  
   // Print to UI
  _LIT( Ktsapicontacts, "torganise" );
  _LIT( KExample, "In GetList_Test1L" );
  TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
  TInt count= KErrGeneral;
  RPointerArray<TDesC8> ptr ;              
  _LIT(KGroup,"Group6")  ;
  _LIT(KNull,"*****")  ;
   
 aItem.GetNextInt(count) ;
 
 status = GROUP;
 KCompare = KGroup ;
  
   /* add group6 to phonebook */ 
 icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
  CActiveScheduler::Start();
  
   /* get contactid of group6 ,store it in cid*/
 icontactservice->GetListL(icallback,1,EGroups);
  CActiveScheduler::Start();
  
  
 TBuf8<100> groupid = contactid ;
 
  status = CONTACT ;
  KCompare = KNull ;
  
   
 /* get  the contactid of any contact */ 
  icontactservice->GetListL(icallback,2,EContacts);
   CActiveScheduler::Start();
   
 HBufC8* contactId1 = contactid.AllocLC();
 CleanupStack::Pop();
 /* Append the contactid to ptr */
 TRAPD(err1,ptr.AppendL(contactId1)); 								    
   								    
/* Add the contact to the group */
 icontactservice->OrganiseGroupsL(icallback,3,groupid,ptr,ETrue);
 CActiveScheduler::Start();	
 
  /* delete the contact from group */
 icontactservice->OrganiseGroupsL(icallback,4,groupid,ptr,EFalse);
 CActiveScheduler::Start();	
 
  /* delete the same contact from group */
 icontactservice->OrganiseGroupsL(icallback,5,groupid,ptr,EFalse);
 CActiveScheduler::Start();								    

  if(count == icallback->iError )
    return KErrNone ;
      
   return KErrGeneral ; 
  

 }

/* dissociate non existent contact from group */
TInt Ctmanualother::Delete_from_group4L( CStifItemParser& aItem )
 {
 
 _LIT( Ktsapicontacts, "torganise");
  _LIT( KExample, "In GetList_Test1L" );
  TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
  iLog->Log( KExample );
    
  TInt count= KErrGeneral;
  RPointerArray<TDesC8> ptr ;              
  _LIT(KGroup,"Group7")  ;
  _LIT(KNull,"*****")  ;
   
  aItem.GetNextInt(count) ;
  
   /* add group7 to phonebook */    
 icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
 CActiveScheduler::Start();
 
  status = GROUP;
 KCompare = KGroup ;
  
  /* get contactid of group7 ,store it in cid*/
  icontactservice->GetListL(icallback,1,EGroups);
  CActiveScheduler::Start();
  
  TBuf8<100> groupid = contactid ;
 
  status = CONTACT ;
  KCompare = KNull ;
  
  /* get  the contactid of any contact */
 icontactservice->GetListL(icallback,2,EContacts);
  CActiveScheduler::Start();
   
  HBufC8* contactId1 = contactid.AllocLC();
  CleanupStack::Pop();
 /* Append the contactid to ptr */
 TRAPD(err1,ptr.AppendL(contactId1)); 
 		    
 /* delete that contact from phonebook*/  								    
 icontactservice->DeleteL(icallback,3,ptr);
  CActiveScheduler::Start();
 
 /* Delete that contact to group7 */
 icontactservice->OrganiseGroupsL(icallback,4,groupid,ptr,EFalse);
 CActiveScheduler::Start();								    

  if(count == icallback->iError )
     return KErrNone ;
      
    return KErrGeneral ;

}





















// -----------------------------------------------------------------------------
// Ctmanualother::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctmanualother::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
