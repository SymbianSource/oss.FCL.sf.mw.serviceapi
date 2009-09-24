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
#include "tcontact_getIds.h"

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
_LIT(KCntDbUri, "cntdb://c:contacts.cdb");
_LIT(KCntDbUri1, "sim://global_adn");
TInt cmdFlag = 1;
TInt tCount = 0;
TInt tIdCount=0;
 HBufC8* contactid;
 CSingleContact* myContact=NULL;
 _LIT(KContactId, "id");
 
 void CContactCallback::HandleReturnId(const TInt& aError, HBufC8* aId, TInt aTransId )
     {
     CActiveScheduler::Stop();  
     iError = aError;
     }
 
 
 void CContactCallback::HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId )
     {
     CActiveScheduler::Stop();  
     iError = aError;
     tIdCount = aArray.Count();
     aArray.ResetAndDestroy();
     }
 
void CContactCallback::HandleReturnValue( TOperationEvent aEventId, const TInt& aError, TInt aTransId )
{
CActiveScheduler::Stop();  
iError= aError;  
}


 void CContactCallback:: HandleReturnIter(const TInt& aError, CContactIter* aIter, TInt aTransId )
 {
 CActiveScheduler::Stop();
 CSingleContactField* field = NULL; 
 TPtrC8 buf1;
 TPtrC buf2;
 TPtrC buf3;
 TInt count=0 ;  
 if(cmdFlag == 0)
     {     
     tCount = 0;
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
          CleanupStack::PushL(field);
           if(field!=NULL)
               {                
               field->GetFieldDataL(buf1,buf2,buf3);        
              
                   //if(buf1.CompareF(_L8("emailgen"))==0) break;                            
               }
           CleanupStack::Pop(field);
                            
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
   delete  aIter;
     }
     }
} 

 // -----------------------------------------------------------------------------
// Ctcontactgetids::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcontactgetids::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctcontactgetids::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcontactgetids::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "AddContact", Ctcontactgetids::AddContactL ),
        ENTRY( "AddGroups", Ctcontactgetids::AddGroupsL ),
        ENTRY( "GetIds_Test1", Ctcontactgetids::GetIds_Test1L ),
        ENTRY( "GetIds_Test2", Ctcontactgetids::GetIds_Test2L ),
        ENTRY( "GetIds_Test3", Ctcontactgetids::GetIds_Test3L ),
        ENTRY( "GetIds_Test4", Ctcontactgetids::GetIds_Test4L ),
        ENTRY( "GetIds_Test5", Ctcontactgetids::GetIds_Test5L ),
        ENTRY( "GetIds_Test6", Ctcontactgetids::GetIds_Test6L ), 
        ENTRY( "GetIds_Test7", Ctcontactgetids::GetIds_Test7L ), 
        ENTRY( "GetIds_Test8", Ctcontactgetids::GetIds_Test8L ),
        ENTRY( "GetIds_Test9", Ctcontactgetids::GetIds_Test9L ),
/*		ENTRY( "GetIds_Test10", Ctcontactgetids::GetIds_Test10L ),
		ENTRY( "GetIds_Test11", Ctcontactgetids::GetIds_Test11L ),*/
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt Ctcontactgetids::AddContactL( CStifItemParser& aItem )
   {

   //__UHEAP_MARK;
   icontactservice=CContactService::NewL();
   icallback=new(ELeave) CContactCallback;
   _LIT8(KFirstName,"FirstName");
   _LIT(KName,"Arnold"); 
   //instantiate service class object
   
   /* create contactitem to add */
   CSingleContact* singleContact = CSingleContact::NewL();
   CleanupStack::PushL(singleContact);
   CSingleContactField* singleContactField = CSingleContactField::NewL();
   CleanupStack::PushL(singleContactField);
   
      
   singleContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
   singleContact->AddFieldToContactL(singleContactField);
   
   /* Add the contactitem */
   icontactservice->AddL(icallback,0,singleContact);
   CActiveScheduler::Start();
  
   /* check whether add api returns the expected error code */  
 if(KErrNone == icallback->iError )
     {
     CleanupStack::Pop(singleContactField);
     CleanupStack::Pop(singleContact);
     delete singleContact;
     delete icallback;
     delete icontactservice;
     //__UHEAP_MARKEND;
     return KErrNone ;
     }
   CleanupStack::Pop(singleContactField);
   CleanupStack::Pop(singleContact);
   delete singleContact;
   delete icallback;
   delete icontactservice;
 //__UHEAP_MARKEND;
   return KErrGeneral ;  
    }

TInt Ctcontactgetids::AddGroupsL( CStifItemParser& aItem )
{
//__UHEAP_MARK;
icontactservice=CContactService::NewL();
icallback=new(ELeave) CContactCallback; 
 /* Group1 to add to phonebook */      
 _LIT(KGroup,"Group1")  ;
 
 /*Add group1 to phonebook */
 icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup);
   CActiveScheduler::Start();
   if(KErrNone != icallback->iError )
       {
   delete icallback;
      delete icontactservice;
  //__UHEAP_MARKEND;
    return KErrGeneral ;
       }
   
   _LIT(KGroup2,"Group2")  ;
   icontactservice->AddL(icallback,0,NULL,KNullDesC8,KGroup2);
     CActiveScheduler::Start();
   
/* check whether add api returns the expected error code */
if(KErrNone == icallback->iError )
    {
    delete icallback;
    delete icontactservice;
    //__UHEAP_MARKEND;
    return KErrNone ;
    }
    delete icallback;
    delete icontactservice;
//__UHEAP_MARKEND;
  return KErrGeneral ;

}
// -----------------------------------------------------------------------------
// Ctcontactgetids::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

 /*Get the list of all contact ids in phone database*/ 	   
 TInt Ctcontactgetids::GetIds_Test1L( CStifItemParser& /*aItem */)
    {
    ////__UHEAP_MARK;
    icontactservice=CContactService::NewL();
    icallback=new(ELeave) CContactCallback;
  // Print to UI
    /*_LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetIds_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );*/
    //TInt val =1;
    //cmdFlag = 0;
 //   icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri);  
 //   CActiveScheduler::Start();
    //cmdFlag = 1;
    icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri,EGetIds);
    CActiveScheduler::Start(); 
    if(icallback->iError == KErrNone)
            {
           // _LIT(KErrCode, "ErrorCode is 0");
           // iLog->Log(KErrCode);
            if(tIdCount >= tCount)
                {
  /*              _LIT(KLogInfo, "Count: ");
                iLog->Log(KLogInfo);
                TBuf8<16> logInfo;
                logInfo.Num(tIdCount);
                iLog->Log(logInfo);*/
                delete icallback;
				  delete icontactservice;
                //__UHEAP_MARKEND;
                return KErrNone;    
                }         
            }
//    delete this;
    delete icallback;
   delete icontactservice;
    //__UHEAP_MARKEND;
        return KErrGeneral;
 }


/* get all contacts from the phonebook ie contacts.cdb*/
/*TInt Ctcontactgetids::GetIds_Test2L( CStifItemParser& aItem )
{

  // Print to UI
    _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetList_Test1L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    
    cmdFlag = 0;
 icontactservice->GetListL(icallback,1,EContacts);  
 CActiveScheduler::Start();
 cmdFlag = 1;
 TInt val =1;
 _LIT(KCntDbUri, "cntdb://c:contacts.cdb");
    icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri,val);
 CActiveScheduler::Start();
 if(icallback->iError == KErrNone)
        {
        _LIT(KErrCode, "ErrorCode is 0");
        iLog->Log(KErrCode);
        if(tIdCount >= tCount)
            {
            _LIT(KLogInfo, "Count: ");
            iLog->Log(KLogInfo);
            TBuf8<16> logInfo;
            logInfo.Num(tIdCount);
            iLog->Log(logInfo);
            return KErrNone;    
            }         
        }
    return KErrGeneral;
  
    
  }
*/


/*Get the list of all the groups in the phone database*/
  TInt Ctcontactgetids::GetIds_Test2L( CStifItemParser& /*aItem*/ )
    {
    //__UHEAP_MARK;
	 icontactservice=CContactService::NewL();
	 icallback=new(ELeave) CContactCallback;
  // Print to UI
   /* _LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetIds_Test2L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    cmdFlag = 0;
  /*icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri);  
    CActiveScheduler::Start();
  if(icallback->iError != KErrNone)
      {
      return KErrGeneral;
      }*/
  cmdFlag = 1;
  TInt val =1;
  
     icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri,EGetIds);
  CActiveScheduler::Start();
  if(icallback->iError == KErrNone)
         {
         /*_LIT(KErrCode, "ErrorCode is 0");
         iLog->Log(KErrCode);*/
         if(tIdCount >= tCount)
             {
             /*_LIT(KLogInfo, "Count: ");
             iLog->Log(KLogInfo);
             TBuf8<16> logInfo;
             logInfo.Num(tIdCount);
             iLog->Log(logInfo);*/
             delete icallback;
			 delete icontactservice;
             //__UHEAP_MARKEND;
             return KErrNone;    
             }         
         }
  delete icallback;
		 delete icontactservice;
    //__UHEAP_MARKEND;
     return KErrGeneral;
     }
  
  
/*get the list of contact ids based on a search criteria*/
  TInt Ctcontactgetids::GetIds_Test3L( CStifItemParser& /*aItem*/ )
      {
      //////__UHEAP_MARK;
	   icontactservice=CContactService::NewL();
	   icallback=new(ELeave) CContactCallback;
/*  _LIT( Ktsapicontacts, "tsapicontacts" );
      _LIT( KExample, "In GetIds_Test3L" );
      TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
      // Print to log file
      iLog->Log( KExample );*/
      _LIT8(KFirstName,"FirstName");
      _LIT(KName,"Jerry"); 
      _LIT(KFirst,"First Name");
      /* create contactitem with invalid fieldname "FrstName */
      CSingleContact* singleContact = CSingleContact::NewL();
      CleanupStack::PushL(singleContact);
      CSingleContactField* singleContactField = CSingleContactField::NewL();
      CleanupStack::PushL(singleContactField);
      singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
      singleContact->AddFieldToContactL(singleContactField);
      /* Add the contactitem */
      icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,KCntDbUri);
      CActiveScheduler::Start();
      if(icallback->iError != KErrNone)
          {
          CleanupStack::Pop(singleContactField);
          CleanupStack::Pop(singleContact);
          delete singleContact;
          delete icallback;
            delete icontactservice;
        //  //__UHEAP_MARKEND;
          return KErrGeneral;
          }
      _LIT(Kname,"Lee");
      TBuf8<15> fstname(_L8("FirstName"));
      
      CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
      srchfield->AppendL(fstname);
      TPtrC searchval(_L("Jerry"));
      TOrder sortorder =EAsc;
      
      cmdFlag = 0;
      icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,searchval,srchfield,EAsc,KCntDbUri);
      CActiveScheduler::Start();
            TBuf8<15> fstName(_L8("FirstName"));
            CSearchFields *searchfield =CSearchFields :: NewL(icontactservice);
            searchfield->AppendL(fstName);
            TPtrC srchval(_L("Jerry"));
      
      TInt val =1;
      cmdFlag = 1;
      icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,srchval,searchfield,EAsc,KCntDbUri,EGetIds);
      CActiveScheduler::Start();
            
      if(icallback->iError == KErrNone)
              {
         /*     _LIT(KErrCode, "ErrorCode is 0");
              iLog->Log(KErrCode);*/
              if(tIdCount >= tCount)
                  {
                  /*_LIT(KLogInfo, "Count: ");
                  iLog->Log(KLogInfo);
                  TBuf8<16> logInfo;
                  logInfo.Num(tIdCount);
                  iLog->Log(logInfo);*/
                  CleanupStack::Pop(singleContactField);
                   CleanupStack::Pop(singleContact);
                  delete singleContact;
                  delete icallback;
                    delete icontactservice;
                  ////__UHEAP_MARKEND;
                  return KErrNone;    
                  }         
              }
      CleanupStack::Pop(singleContactField);
                CleanupStack::Pop(singleContact);
      delete singleContact;
      delete icallback;
        delete icontactservice;
      ////__UHEAP_MARKEND;
          return KErrGeneral;
      }
 
/*get the ids of all contacts in phone database in descending order*/
  TInt Ctcontactgetids::GetIds_Test4L( CStifItemParser& /*aItem*/ )
      {
      ////__UHEAP_MARK;
	   icontactservice=CContactService::NewL();
	   icallback=new(ELeave) CContactCallback;
/*      _LIT( Ktsapicontacts, "tsapicontacts" );
        _LIT( KExample, "In GetIds_Test4L" );
        TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
        // Print to log file
        iLog->Log( KExample );*/
        TInt val =1;
        cmdFlag = 0;
        icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EDesc,KCntDbUri);  
        CActiveScheduler::Start();
        cmdFlag = 1;
        icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EDesc,KCntDbUri,EGetIds);
        CActiveScheduler::Start(); 
        if(icallback->iError == KErrNone)
                {
                /*_LIT(KErrCode, "ErrorCode is 0");
                iLog->Log(KErrCode);*/
                if(tIdCount >= tCount)
                    {
                    /*_LIT(KLogInfo, "Count: ");
                    iLog->Log(KLogInfo);
                    TBuf8<16> logInfo;
                    logInfo.Num(tIdCount);
                    iLog->Log(logInfo);*/
                    delete icallback;
                      delete icontactservice;
                    //__UHEAP_MARKEND;
                    return KErrNone;    
                    }         
                }
        delete icallback;
          delete icontactservice;
        //__UHEAP_MARKEND;
        return KErrGeneral;
      }
  
  /*get all the group ids in phone db in descending order*/
  TInt Ctcontactgetids::GetIds_Test5L( CStifItemParser& /*aItem*/ )
        {
        ////__UHEAP_MARK;
		 icontactservice=CContactService::NewL();
		 icallback=new(ELeave) CContactCallback;
  /*_LIT( Ktsapicontacts, "tsapicontacts" );
    _LIT( KExample, "In GetIds_Test5L" );
    TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
    // Print to log file
    iLog->Log( KExample );
    cmdFlag = 0;*/
  /*icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,EDesc,KCntDbUri);  
  CActiveScheduler::Start();
  if(icallback->iError != KErrNone)
      {
      return KErrGeneral;
      }*/
  cmdFlag = 1;
  TInt val =1;
  
     icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,EDesc,KCntDbUri,EGetIds);
  CActiveScheduler::Start();
  if(icallback->iError == KErrNone)
         {
         /*_LIT(KErrCode, "ErrorCode is 0");
         iLog->Log(KErrCode);*/
         if(tIdCount >= tCount)
             {
             /*_LIT(KLogInfo, "Count: ");
             iLog->Log(KLogInfo);
             TBuf8<16> logInfo;
             logInfo.Num(tIdCount);
             iLog->Log(logInfo);*/
             delete icallback;
               delete icontactservice;
             //__UHEAP_MARKEND;
             return KErrNone;    
             }         
         }
  delete icallback;
    delete icontactservice;
    //__UHEAP_MARKEND;
     return KErrGeneral;
     }
  

  /*get the list of all contact ids in sim database*/
  TInt Ctcontactgetids::GetIds_Test6L( CStifItemParser& /*aItem*/ )
        {
        ////__UHEAP_MARK;
		 icontactservice=CContactService::NewL();
		 icallback=new(ELeave) CContactCallback;
        /*_LIT( Ktsapicontacts, "tsapicontacts" );
          _LIT( KExample, "In GetIds_Test6L" );
          TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
          // Print to log file
          iLog->Log( KExample );*/
          TInt val =1;
          cmdFlag = 0;
          icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri1);  
          CActiveScheduler::Start();
          cmdFlag = 1;
          icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc,KCntDbUri1,EGetIds);
          CActiveScheduler::Start(); 
          if(icallback->iError == KErrNone)
                  {
                  /*_LIT(KErrCode, "ErrorCode is 0");
                  iLog->Log(KErrCode);*/
                  if(tIdCount >= tCount)
                      {
                      /*_LIT(KLogInfo, "Count: ");
                      iLog->Log(KLogInfo);
                      TBuf8<16> logInfo;
                      logInfo.Num(tIdCount);
                      iLog->Log(logInfo);*/
                      delete icallback;
                        delete icontactservice;
                      //__UHEAP_MARKEND;
                      return KErrNone;    
                      }         
                  }
          delete icallback;
           delete icontactservice;
          //__UHEAP_MARKEND;
          return KErrGeneral;
        }
  
  TInt Ctcontactgetids::GetIds_Test7L( CStifItemParser& /*aItem*/ )
        {
        ////__UHEAP_MARK;
		 icontactservice=CContactService::NewL();
		 icallback=new(ELeave) CContactCallback;
        /*_LIT( Ktsapicontacts, "tsapicontacts" );
            _LIT( KExample, "In GetIds_Test7L" );
            TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
            // Print to log file
            iLog->Log( KExample );*/
       /*     _LIT8(KFirstName,"FirstName");
            _LIT(KName,"Tom"); 
            _LIT(KFirst,"First Name");
        
            CSingleContact* singleContact = CSingleContact::NewL();
            CSingleContactField* singleContactField = CSingleContactField::NewL();
            singleContactField->SetFieldParamsL(KFirstName,KFirst,KName);
            singleContact->AddFieldToContactL(singleContactField);
            // Add the contactitem 
            icontactservice->AddL(icallback,0,singleContact,KNullDesC8,KNullDesC,KCntDbUri1);
            CActiveScheduler::Start();
            if(icallback->iError != KErrNone)
                {
                return KErrGeneral;
                }*/
            _LIT(Kname,"Lee");
            TBuf8<15> fstname(_L8("FirstName"));
            
            CSearchFields *srchfield =CSearchFields :: NewL(icontactservice);
            srchfield->AppendL(fstname);
            TPtrC searchval(_L("Arnold"));
            TOrder sortorder =EAsc;
            
            cmdFlag = 0;
            icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,searchval,srchfield,EAsc,KCntDbUri,EGetList);
            CActiveScheduler::Start();
            if(icallback->iError != KErrNone)
                {
                /*_LIT( KErrorMsg, "The GetList returned non zero error" );
                iLog->Log( KErrorMsg );
                TBuf<25> errorcodedes(KNullDesC);
                errorcodedes.Num(icallback->iError);
                iLog->Log(_L("Error code:"));
                iLog->Log(errorcodedes); */
                delete icallback;
                 delete icontactservice;		
                //__UHEAP_MARKEND;
                return KErrGeneral;
                }
                  TBuf8<15> fstName(_L8("FirstName"));
                  CSearchFields *searchfield =CSearchFields :: NewL(icontactservice);
                  searchfield->AppendL(fstName);
                  TPtrC srchval(_L("Arnold"));
            
            TInt val =1;
            cmdFlag = 1;
            icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,srchval,searchfield,ENULL,KCntDbUri1,EGetIds);
            CActiveScheduler::Start();
                  
            if(icallback->iError == KErrNone)
                    {
                    /*_LIT(KErrCode, "ErrorCode is 0");
                    iLog->Log(KErrCode);*/
                    if(tIdCount >= 0)
                        {
                       /* _LIT(KLogInfo, "Count: ");
                        iLog->Log(KLogInfo);
                        TBuf8<16> logInfo;
                        logInfo.Num(tIdCount);
                        iLog->Log(logInfo);*/
                        delete icallback;
                        delete icontactservice;
                        //__UHEAP_MARKEND;
                        return KErrNone;    
                        }         
                    }
            /*_LIT( KErrorMsg2, "The GetIds returned non zero error" );
             iLog->Log( KErrorMsg2 );
			 delete icontactservice;*/
            delete icallback;
            delete icontactservice;
             //__UHEAP_MARKEND;
             return KErrGeneral;
        }
  /*get the ids of all contacts in phone database in default order*/
    TInt Ctcontactgetids::GetIds_Test8L( CStifItemParser& /*aItem*/ )
        {
        ////__UHEAP_MARK;
		 icontactservice=CContactService::NewL();
		 icallback=new(ELeave) CContactCallback;
        /*_LIT( Ktsapicontacts, "tsapicontacts" );
          _LIT( KExample, "In GetIds_Test8L" );
          TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
          // Print to log file
          iLog->Log( KExample );*/
          TInt val =1;
          cmdFlag = 0;
          icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,ENULL,KCntDbUri);  
          CActiveScheduler::Start();
          cmdFlag = 1;
          icontactservice->GetListL(icallback,1,EContacts,KNullDesC8,KNullDesC,NULL,ENULL,KCntDbUri,EGetIds);
          CActiveScheduler::Start(); 
          if(icallback->iError == KErrNone)
                  {
                  /*_LIT(KErrCode, "ErrorCode is 0");
                  iLog->Log(KErrCode);*/
                  if(tIdCount >= tCount)
                      {
                      /*_LIT(KLogInfo, "Count: ");
                      iLog->Log(KLogInfo);
                      TBuf8<16> logInfo;
                      logInfo.Num(tIdCount);
                      iLog->Log(logInfo);*/
                      delete icallback;
                      delete icontactservice;
                      //__UHEAP_MARKEND;
                      return KErrNone;    
                      }         
                  }
          delete icallback;
          delete icontactservice;
          //__UHEAP_MARKEND;
          return KErrGeneral;
        }
 /*get the list of all group ids in default sort order*/
    TInt Ctcontactgetids::GetIds_Test9L( CStifItemParser& /*aItem*/ )
       {
       ////__UHEAP_MARK;
	    icontactservice=CContactService::NewL();
	    icallback=new(ELeave) CContactCallback;
     // Print to UI
       /*_LIT( Ktsapicontacts, "tsapicontacts" );
       _LIT( KExample, "In GetIds_Test9L" );
       TestModuleIf().Printf( 0, Ktsapicontacts, KExample );
       // Print to log file
       iLog->Log( KExample );
       cmdFlag = 0;*/
 /*    icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,ENULL,KCntDbUri);  
     CActiveScheduler::Start();
     if(icallback->iError != KErrNone)
         {
         return KErrGeneral;
         }*/
     cmdFlag = 1;
     TInt val =1;
     
        icontactservice->GetListL(icallback,1,EGroups,KNullDesC8,KNullDesC,NULL,ENULL,KCntDbUri,EGetIds);
     CActiveScheduler::Start();
     if(icallback->iError == KErrNone)
            {
            /*_LIT(KErrCode, "ErrorCode is 0");
            iLog->Log(KErrCode);*/
            if(tIdCount >= tCount)
                {
                /*_LIT(KLogInfo, "Count: ");
                iLog->Log(KLogInfo);
                TBuf8<16> logInfo;
                logInfo.Num(tIdCount);
                iLog->Log(logInfo);*/
                delete icallback;
                delete icontactservice;
                ////__UHEAP_MARKEND;
                return KErrNone;    
                }         
            }
     delete icallback;
     delete icontactservice;
        ////__UHEAP_MARKEND;
        return KErrGeneral;
        }
//  End of File
