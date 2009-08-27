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
 TBool newFields = EFalse; 
 _LIT8(KFirstNameKey,"FirstName");
 _LIT(KValue,"Barbie");
 
 void CContactCallback::HandleReturnArray(const TInt& aError,RPointerArray<HBufC8>& aArray,TInt aTransId )
     {
     CActiveScheduler::Stop();
     iError = aError;
     }

 void CContactCallback:: HandleReturnId( const TInt& aError, HBufC8* acntId, TInt aTransId )
     {
     CActiveScheduler::Stop();
     //HBufC8* cntId = acntId;
     iError = aError;
     if(aError == KErrNone)
         {
              delete acntId;
              acntId = NULL;
         }
     }
void CContactCallback::HandleReturnValue( TOperationEvent aEventId, const TInt& aError, TInt aTransId )
{
  iError= aError;
  CActiveScheduler::Stop();
}


 void CContactCallback:: HandleReturnIter(const TInt& aError, CContactIter* aIter, TInt aTransId )
 {
 

    CActiveScheduler::Stop();
iError = aError;
    CSingleContactField* field = NULL; 
    TPtrC8 buf1;
    TPtrC buf2;
    TPtrC buf3;
    TInt count=0 ;	     

   
if(aError==KErrNone)
{
   aIter->NextL(myContact,contactid);
   if(contactid)
   {   
    delete contactid;
    contactid = NULL;
   }

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
             if(newFields != EFalse)
                 {
             if(buf1.CompareF(KFirstNameKey) == 0)
                 {
                 if(buf3.CompareF(KValue) != 0)
                     {
                     iError = KErrGeneral;
                     newFields =EFalse;
                     break;
                     }
                 }
             newFields = EFalse;
             break;
                 }
                 //if(buf1.CompareF(_L8("emailgen"))==0) break;                            
             }
                          
       } //for 
           
   } //if
   if(myContact)
   {
    delete myContact;
    myContact = NULL;
   }
   aIter->NextL(myContact,contactid);
   
  if(contactid)
   {   
    delete contactid;
    contactid = NULL;
   }
                    
 } //while
 
} //if
delete  aIter;   
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
        ENTRY( "GetList_Test11", Ctmanualcontacts::GetList_Test11L ),
        ENTRY( "GetList_Test12", Ctmanualcontacts::GetList_Test12L ),   

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
	__UHEAP_MARK;
	icontactservice=CContactService::NewL();
     icallback=new(ELeave) CContactCallback;
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

     delete iter;
    delete icallback;
    delete icontactservice;
  __UHEAP_MARKEND;
    return KErrNone ;   
  
 }


/* get all contacts from the phonebook ie contacts.cdb,manual*/
TInt Ctmanualcontacts::GetList_Test2L( CStifItemParser& aItem )
{
__UHEAP_MARK;
	icontactservice=CContactService::NewL();
     icallback=new(ELeave) CContactCallback;
  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    
 icontactservice->GetListL(icallback,1,EContacts);  
  
 CActiveScheduler::Start();
         delete icallback;
    delete icontactservice;
     
 __UHEAP_MARKEND;
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
	__UHEAP_MARK;
	icontactservice=CContactService::NewL();
    //CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
    TPtrC searchval(_L("Getlist_test"));  
   // srchfield->AppendL(fstname);
    icallback=new(ELeave) CContactCallback;
	
    icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,searchval,NULL,EAsc,KCntDbUri);
  
   CActiveScheduler::Start();
   delete icallback;
  // delete srchfield;
   delete icontactservice;
   __UHEAP_MARKEND;
   if(myContact ==NULL)
   {
      return KErrNone ;   
	}
      //delete icallback;
	//delete icontactservice;
  //__UHEAP_MARKEND;
    return KErrGeneral;
  }
 
 /* get group list ,groups are there but no contacts in it */
   TInt Ctmanualcontacts::GetList_Test4L( CStifItemParser& aItem )
    {
__UHEAP_MARK;
	icontactservice=CContactService::NewL();
     icallback=new(ELeave) CContactCallback;
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
	    delete icallback;
    delete icontactservice;
  __UHEAP_MARKEND;
    return KErrNone ;
	    delete icallback;
    delete icontactservice;
  __UHEAP_MARKEND;
    
    return KErrGeneral;
  
   
  }        

/// repeated  
  /* search for Lee in tmp.cdb */ 
  
  TInt Ctmanualcontacts::GetList_Test5L( CStifItemParser& aItem )
{
__UHEAP_MARK;
	icontactservice=CContactService::NewL();
     icallback=new(ELeave) CContactCallback;
     
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
  	      {
	      delete icallback;
	      delete icontactservice;
	      delete singleContact;
	      __UHEAP_MARKEND;
	      return KErrNone ;
  	      }
           
          delete icallback;
          delete icontactservice;
          delete singleContact;
  __UHEAP_MARKEND;     
  
  	 return KErrGeneral ;
  }
  
//  search for invalid search field  ,ex:search for Lee as lastname in tmp.cdb 
  
 TInt Ctmanualcontacts::GetList_Test6L( CStifItemParser& aItem )
{
__UHEAP_MARK;
	icontactservice=CContactService::NewL();
     icallback=new(ELeave) CContactCallback;
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
	 {
	     delete icallback;
    delete icontactservice;
    delete singleContact;
  __UHEAP_MARKEND;
        return KErrNone ;   
  }
	
	    delete icallback;
    delete icontactservice;
    delete singleContact;
  __UHEAP_MARKEND;
     return KErrGeneral;
     
   
}  
  
 /* list contacts in descending order */ 
   TInt Ctmanualcontacts::GetList_Test7L( CStifItemParser& aItem )
{
__UHEAP_MARK;
	icontactservice=CContactService::NewL();
     icallback=new(ELeave) CContactCallback;
	_LIT(KCntDbUri, "cntdb://c:tmp.cdb");  	    
     // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
 
  
 icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EDesc);  //,cid,KCntDbUri1,searchval,srchfield); 
  
 CActiveScheduler::Start();
     
       delete icallback;
   delete icontactservice;
   __UHEAP_MARKEND;
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
 
__UHEAP_MARK;
	icontactservice=CContactService::NewL();
     icallback=new(ELeave) CContactCallback;
    icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,EDesc,KCntDbUri);  //,cid,KCntDbUri1,searchval,srchfield); 
  
    CActiveScheduler::Start();
     
       delete icallback;
    delete icontactservice;
  __UHEAP_MARKEND;
 return KErrNone ;   

}

 /* list contacts ,ENULL cannot be used in sortingorder*/
 TInt Ctmanualcontacts::GetList_Test9L( CStifItemParser& aItem )
{
__UHEAP_MARK;
	icontactservice=CContactService::NewL();
     icallback=new(ELeave) CContactCallback;
	_LIT(KCntDbUri, "cntdb://c:tmp_ENul.cdb"); 
  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
 
    
 
icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc);  //,cid,KCntDbUri1,searchval,srchfield); 
  
 CActiveScheduler::Start();
         delete icallback;
    delete icontactservice;
  __UHEAP_MARKEND;
   
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
        
 __UHEAP_MARK;
	icontactservice=CContactService::NewL();
     icallback=new(ELeave) CContactCallback;
  _LIT(KCntDbUri1, "cntdb://c:tmp.cdb");  	   
 icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri1);  //,cid,KCntDbUri1,searchval,srchfield); 
  
 CActiveScheduler::Start(); 
        
    CContactIter* iter = CContactIter::NewL();
    icontactservice->GetListL(*iter);
    delete iter;
	    delete icallback;
    delete icontactservice;
  __UHEAP_MARKEND;
    TPtrC buf(_L(""));
     
     iter->NextL(buf);
     TInt count=0;
   while(buf.Compare(KNullDesC)!=0)
      {	  count++;
          iter->NextL(buf);
  	  } 
	if(count==2)
	{

    return KErrNone ;   
	}
delete iter;
	    delete icallback;
    delete icontactservice;
  //__UHEAP_MARKEND;	
	return KErrGeneral;
}

/* get all contacts from the phonebook ie contacts.cdb,manual*/
TInt Ctmanualcontacts::GetList_Test11L( CStifItemParser& aItem )
{
  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test11L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    __UHEAP_MARK;
        icontactservice=CContactService::NewL();
         icallback=new(ELeave) CContactCallback;

    iLog->Log( KExample );
//    TInt count =KErrGeneral ;
        _LIT8(KFirstName,"FirstName");
        _LIT(KFName,"Barbie");
        _LIT8(KPrefix,"Prefix");
        _LIT(KPfix,"Princess");
        _LIT8(KNote,"Note");
        _LIT(KNoteVal,"Lead role in Barbie, the island princess");
        _LIT8(KAnniversary,"Anniversary");
        //_LIT(KAniiVal,"08216666");
         _LIT8(KBday,"Date");
        _LIT8(KNickName,"SecondName");
        _LIT(KNickNameVal,"Doll");
        _LIT8(KPhoto,"CallerObjImg");
        _LIT(KPhotoVal,"C:\\data\\images\\pic.jpg");
        _LIT8(KImpp,"IMPP");
        _LIT(KImppLabel,"IMPP");
        
        
       //instantiate service class object
         /* create contactitem to add */        
CSingleContact* singleContact = CSingleContact::NewL();
	CleanupStack::PushL(singleContact);
        CSingleContactField* FName = CSingleContactField::NewL();
CleanupStack::PushL(FName);
        CSingleContactField* prefix = CSingleContactField::NewL();
CleanupStack::PushL(prefix);
        CSingleContactField* note = CSingleContactField::NewL();
CleanupStack::PushL(note);
         CSingleContactField* anni = CSingleContactField::NewL();
CleanupStack::PushL(anni);
        CSingleContactField* bday = CSingleContactField::NewL();
CleanupStack::PushL(bday);
         CSingleContactField* nkname = CSingleContactField::NewL();
CleanupStack::PushL(nkname);
        CSingleContactField* photo = CSingleContactField::NewL();
CleanupStack::PushL(photo);
        CSingleContactField* xspid = CSingleContactField::NewL();
CleanupStack::PushL(xspid);
          
           
        FName->SetFieldParamsL(KFirstName,KNullDesC,KFName);
        singleContact->AddFieldToContactL(FName);
        
        prefix->SetFieldParamsL(KPrefix,KNullDesC,KPfix);
        singleContact->AddFieldToContactL(prefix);
        
        note->SetFieldParamsL(KNote,KNullDesC,KNoteVal);
        singleContact->AddFieldToContactL(note);
        
        anni->SetFieldParamsL(KAnniversary,KNullDesC,KNullDesC);
        anni->SetDateTime(TTime(TDateTime(2007,EOctober,25,0,0,0,0)));
       //anni->SetDateTime(annival);
       singleContact->AddFieldToContactL(anni);
       
       
       bday->SetFieldParamsL(KBday,KNullDesC,KNullDesC);
       bday->SetDateTime(TTime(TDateTime(2007,EOctober,25,0,0,0,0)));
       //bday->SetDateTime(bdayval);
       singleContact->AddFieldToContactL(bday);
              
        nkname->SetFieldParamsL(KNickName,KNullDesC,KNickNameVal);
        singleContact->AddFieldToContactL(nkname);
        
        photo->SetFieldParamsL(KPhoto,KNullDesC,KPhotoVal);    
        singleContact->AddFieldToContactL(photo);
        
        _LIT(KYahooId,"Yahoo:barbie@yahoo.co.in");
        //_LIT8();
        RPointerArray<HBufC> xspidarr;
        xspidarr.Append((_L("Yahoo:barbie@yahoo.co.in")).AllocL());
        xspidarr.Append((_L("Google:barbie@gmail.com")).AllocL());
        xspid->SetXspidDataL(KImpp,KImppLabel,xspidarr);
        singleContact->AddFieldToContactL(xspid);

        //aItem.GetNextInt(count) ;
        _LIT( KLog4, "before calling add" );
    iLog->Log( KLog4 );
        /* Add the contactitem */
        HBufC8* cntId;
        TRAPD(err,cntId= icontactservice->AddL(singleContact));
       
        TPtr8 cntIdPtrVal(cntId->Des());
         if(err != KErrNone)
		 {CleanupStack::Pop(xspid);
         CleanupStack::Pop(photo);
         CleanupStack::Pop(nkname);
         CleanupStack::Pop(bday);
         CleanupStack::Pop(anni);
         CleanupStack::Pop(note);
         CleanupStack::Pop(prefix);
         CleanupStack::Pop(FName);
         CleanupStack::Pop(singleContact);
         delete singleContact;
delete cntId;
		     delete icallback;
    delete icontactservice;
	_LIT( KLog1, "false case uheapmarkend" );
    iLog->Log( KLog1 );
  __UHEAP_MARKEND;
             return KErrGeneral ;
		}
         /*else
             {
             CleanupStack::Pop(xspid);
                           CleanupStack::Pop(photo);
                           CleanupStack::Pop(nkname);
                           CleanupStack::Pop(bday);
                           CleanupStack::Pop(anni);
                           CleanupStack::Pop(note);
                           CleanupStack::Pop(prefix);
                           CleanupStack::Pop(FName);
                           CleanupStack::Pop(singleContact);
                           delete singleContact;
             delete cntId;
                          delete icallback;
                 delete icontactservice;
                 _LIT( KLog1, "false case uheapmarkend" );
                 iLog->Log( KLog1 );
               __UHEAP_MARKEND;
                          return KErrNone;

             }
         */
         newFields = ETrue;
         _LIT(KCntDbUri,"cntdb://c:contacts.cdb");
         //icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri1);  
         //icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc); 
         icontactservice->GetListL(icallback,1,EContacts,cntIdPtrVal); //,KNullDesC,NULL,EAsc,KCntDbUri,EGetList);  
  
         CActiveScheduler::Start();
     
   if(icallback->iError == KErrNone)
       {
       CleanupStack::Pop(xspid);
                                  CleanupStack::Pop(photo);
                                  CleanupStack::Pop(nkname);
                                  CleanupStack::Pop(bday);
                                  CleanupStack::Pop(anni);
                                  CleanupStack::Pop(note);
                                  CleanupStack::Pop(prefix);
                                  CleanupStack::Pop(FName);
                                  CleanupStack::Pop(singleContact);
                                  delete singleContact;
delete cntId;
	       delete icallback;
    delete icontactservice;
	_LIT( KLog2, "true case uheapmarkend" );
    iLog->Log( KLog2 );
  __UHEAP_MARKEND;
 return KErrNone ;
       }
   CleanupStack::Pop(xspid);
                              CleanupStack::Pop(photo);
                              CleanupStack::Pop(nkname);
                              CleanupStack::Pop(bday);
                              CleanupStack::Pop(anni);
                              CleanupStack::Pop(note);
                              CleanupStack::Pop(prefix);
                              CleanupStack::Pop(FName);
                              CleanupStack::Pop(singleContact);
                              delete singleContact;
delete cntId;
	       delete icallback;
    delete icontactservice;
	_LIT( KLog3, "false case uheapmarkend 2" );
    iLog->Log( KLog3 );
  __UHEAP_MARKEND;
   return KErrGeneral;

    
  }


/* get all contacts from the phonebook ie contacts.cdb,manual*/
TInt Ctmanualcontacts::GetList_Test12L( CStifItemParser& aItem )
{
__UHEAP_MARK;
icontactservice=CContactService::NewL();
  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test11L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
//    TInt count =KErrGeneral ;
        _LIT8(KFirstName,"FirstName");
        _LIT(KFName,"Kelly");
        _LIT8(KPrefix,"Prefix");
        _LIT(KPfix,"Princess");
        _LIT8(KNote,"Note");
        _LIT(KNoteVal,"Sister of Princess Barbie");
        _LIT8(KAnniversary,"Anniversary");
         _LIT8(KBday,"Date");
        _LIT8(KNickName,"SecondName");
        _LIT(KNickNameVal,"Doll");
        _LIT8(KPhoto,"CallerObjImg");
        _LIT(KPhotoVal,"C:\\data\\images\\pic.jpg");
        _LIT8(KImpp,"IMPP");
        _LIT(KImppLabel,"IMPP");
        TPtrC8 fieldKey(KNullDesC8);
         TPtrC  label(KNullDesC); 
         TPtrC  value(KNullDesC);       
        _LIT(KValue,"Kelly");
       //instantiate service class object
         /* create contactitem to add */
        CSingleContact* singleContact = CSingleContact::NewL();
	CleanupStack::PushL(singleContact);
        CSingleContactField* FName = CSingleContactField::NewL();
CleanupStack::PushL(FName);
        CSingleContactField* prefix = CSingleContactField::NewL();
CleanupStack::PushL(prefix);
        CSingleContactField* note = CSingleContactField::NewL();
CleanupStack::PushL(note);
         CSingleContactField* anni = CSingleContactField::NewL();
CleanupStack::PushL(anni);
        CSingleContactField* bday = CSingleContactField::NewL();
CleanupStack::PushL(bday);
         CSingleContactField* nkname = CSingleContactField::NewL();
CleanupStack::PushL(nkname);
        CSingleContactField* photo = CSingleContactField::NewL();
CleanupStack::PushL(photo);
        CSingleContactField* xspid = CSingleContactField::NewL();
CleanupStack::PushL(xspid);
           
        FName->SetFieldParamsL(KFirstName,KNullDesC,KFName);
        singleContact->AddFieldToContactL(FName);
        
        prefix->SetFieldParamsL(KPrefix,KNullDesC,KPfix);
        singleContact->AddFieldToContactL(prefix);
        
        note->SetFieldParamsL(KNote,KNullDesC,KNoteVal);
        singleContact->AddFieldToContactL(note);
        
        anni->SetFieldParamsL(KAnniversary,KNullDesC,KNullDesC);
       //anni->SetDateTime(annival);
        anni->SetDateTime(TTime(TDateTime(2007,EOctober,25,0,0,0,0)));
       singleContact->AddFieldToContactL(anni);
       
       
       bday->SetFieldParamsL(KBday,KNullDesC,KNullDesC);
       //bday->SetDateTime(bdayval);
       bday->SetDateTime(TTime(TDateTime(2007,EOctober,25,0,0,0,0)));
       singleContact->AddFieldToContactL(bday);
              
        nkname->SetFieldParamsL(KNickName,KNullDesC,KNickNameVal);
        singleContact->AddFieldToContactL(nkname);
        
        photo->SetFieldParamsL(KPhoto,KNullDesC,KPhotoVal);    
        singleContact->AddFieldToContactL(photo);
        
        _LIT(KYahooId,"Yahoo:kelly@yahoo.co.in");
        //_LIT8();
        RPointerArray<HBufC> xspidarr;
        xspidarr.Append((_L("Yahoo:kelly@yahoo.co.in")).AllocL());
        xspidarr.Append((_L("Google:kelly@gmail.com")).AllocL());
        xspid->SetXspidDataL(KImpp,KImppLabel,xspidarr);
		
		
        singleContact->AddFieldToContactL(xspid);

  //      aItem.GetNextInt(count) ;

        /* Add the contactitem */
        HBufC8* cntId;
        TRAPD(err,cntId= icontactservice->AddL(singleContact));
        TPtr8 cntIdPtrVal(cntId->Des());
        
         if(err != KErrNone)
		 {
		 CleanupStack::Pop(xspid);
		               CleanupStack::Pop(photo);
		               CleanupStack::Pop(nkname);
		               CleanupStack::Pop(bday);
		               CleanupStack::Pop(anni);
		               CleanupStack::Pop(note);
		               CleanupStack::Pop(prefix);
		               CleanupStack::Pop(FName);
		               CleanupStack::Pop(singleContact);
		               delete singleContact;
delete cntId;
    delete icontactservice;
 __UHEAP_MARKEND;
             return KErrGeneral ;
			 }
         newFields = ETrue;
         CContactIter* iterVal;
         
         TPtr8 cntIdPtr(cntId->Des());
         TRAPD(error, iterVal = icontactservice->GetListL(EContacts,cntIdPtr));  
         
         if(error != KErrNone)
          {
          CleanupStack::Pop(xspid);
                        CleanupStack::Pop(photo);
                        CleanupStack::Pop(nkname);
                        CleanupStack::Pop(bday);
                        CleanupStack::Pop(anni);
                        CleanupStack::Pop(note);
                        CleanupStack::Pop(prefix);
                        CleanupStack::Pop(FName);
                        CleanupStack::Pop(singleContact);
                        delete singleContact;
			delete cntId;
			delete iterVal;
			_LIT( KLog1, "false case uheapmarkend 1" );
			iLog->Log( KLog1 );
			__UHEAP_MARKEND;
			  return KErrGeneral;
          }
         iterVal->NextL(myContact,contactid);
		  if(contactid)
		   {   
		    delete contactid;
		    contactid = NULL;
		   }
      if(myContact)
          {
          for(TInt i=0;i<myContact->FieldCount(); i++)
              {
          CSingleContactField* field = myContact->FieldAt(i);
          field->GetFieldDataL(fieldKey,label,value);
          if(value.Compare(KValue) == 0)
              {
              CleanupStack::Pop(xspid);
                            CleanupStack::Pop(photo);
                            CleanupStack::Pop(nkname);
                            CleanupStack::Pop(bday);
                            CleanupStack::Pop(anni);
                            CleanupStack::Pop(note);
                            CleanupStack::Pop(prefix);
                            CleanupStack::Pop(FName);
                            CleanupStack::Pop(singleContact);
                            delete singleContact;
				delete cntId;
			   delete iterVal;
			   delete myContact;
			    delete icontactservice;
				_LIT( KLog2, "true case uheapmarkend" );
			    iLog->Log( KLog2 );
			  __UHEAP_MARKEND;
           return KErrNone;
              }
              }
          delete myContact;
          }
      CleanupStack::Pop(xspid);
                    CleanupStack::Pop(photo);
                    CleanupStack::Pop(nkname);
                    CleanupStack::Pop(bday);
                    CleanupStack::Pop(anni);
                    CleanupStack::Pop(note);
                    CleanupStack::Pop(prefix);
                    CleanupStack::Pop(FName);
                    CleanupStack::Pop(singleContact);
                    delete singleContact;
delete cntId;
  delete iterVal;
    delete icontactservice;
	_LIT( KLog3, "false case uheapmarkend" );
    iLog->Log( KLog3 );
  __UHEAP_MARKEND;
    
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
