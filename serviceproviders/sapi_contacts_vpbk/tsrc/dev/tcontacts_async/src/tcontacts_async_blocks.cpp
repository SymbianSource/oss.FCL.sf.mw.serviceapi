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
#include <VPbkEng.rsg>

#include <MVPbkContactFieldTextData.h>
#include <MVPbkContactStoreList.h>
#include <MVPbkContactOperationBase.h>
#include <MVPbkContactLink.h>
#include <CVPbkContactLinkArray.h>
#include <MVPbkContactGroup.h>
#include <utf.h>
#include <CVPbkPhoneNumberMatchStrategy.h>
#include <CVPbkContactStoreUriArray.h>
#include <TVPbkContactStoreUriPtr.h>
#include "tcontacts_async.h"
#include "singlecontact.h"

// CONSTANTS
_LIT(KError,"Error code is");
_LIT(KSuccess,"Successful");
_LIT(KNewLine,"\n");
_LIT(KServiceOpen,"Service handle created");
_LIT(KServiceClose,"Service handle deleted");
_LIT(KPhoneNumber,"9886431364");
 _LIT(KGroup1,"Test1");
 TInt KInvalidKey = -1;
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CContactsUT::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CContactsUT::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CContactsUT::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CContactsUT::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        { 
        ENTRY( "Add_contact_sapi", CContactsUT::AddContactSAPIL ),
        ENTRY( "Delete_contact_sapi", CContactsUT::DeleteContactSAPIL ),
        ENTRY( "Modify_contact_sapi", CContactsUT::ModifyContactSAPIL ),
        ENTRY( "Getlist_delete_contact", CContactsUT::GetListDeleteContactL ),
        ENTRY( "Add_getlist_contact", CContactsUT::AddContactGetListL ), 
        ENTRY( "Get_group", CContactsUT::GetGroupsL ),
        ENTRY( "Get_contact", CContactsUT::GetContactsL ),
        ENTRY( "Get_database", CContactsUT::GetDatabaseL ),
        ENTRY( "Add_contact", CContactsUT::AddL ),
        ENTRY( "Add_group", CContactsUT::AddGroupL ),
        ENTRY( "Modify_contact", CContactsUT::ModifyL ),
        ENTRY( "Modify_group", CContactsUT::ModifyGroupL ),
        ENTRY( "Delete_contact", CContactsUT::DeleteContactL ),
        ENTRY( "Delete_group", CContactsUT::DeleteGroupL ),
        ENTRY( "Organise_add", CContactsUT::OrganiseAddL ),
        ENTRY( "Organise_delete", CContactsUT::OrganiseDeleteL ),
        ENTRY( "Import", CContactsUT::ImportL ),
        ENTRY( "Export", CContactsUT::ExportL ),
        ENTRY( "Get_SearchContact", CContactsUT::GetSearchContactL ),
        ENTRY( "Get_ContactAsc", CContactsUT::GetContactsAscOrderL ),
        ENTRY( "Get_ContactDsc", CContactsUT::GetContactsDscOrderL ),
        ENTRY( "Get_ContactbyId", CContactsUT::GetListConactIdL ),
        ENTRY( "AddInvalidField", CContactsUT::AddInvalidFieldL ),
        ENTRY( "AddMultiplePhoneNumbersContact", CContactsUT::AddMultiplePhoneNumbersContactL ),
        ENTRY( "DeleteSingleContact", CContactsUT::DeleteSingleContactL ),
        ENTRY( "GetListCancelTest", CContactsUT::GetListCancelL ),
        ENTRY( "GetListSrchCancelTest", CContactsUT::GetListSrchCancelL ),
        ENTRY( "ExportCancelTest",  CContactsUT::ExportCancelL ),
        ENTRY( "AddCancelTest", CContactsUT::AddCancelL ),
        ENTRY( "ImportCancelTest", CContactsUT::ImportCancelL ),
        ENTRY( "DeleteCancelTest", CContactsUT::DeleteCancelL ),
        ENTRY( "OrganiseCancelTest", CContactsUT::OrganiseCancelL),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
void CContactsUT::HandleReturnId( const TInt& aError, HBufC8* acntId, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }

void CContactsUT::HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }
void CContactsUT::HandleReturnValue(TOperationEvent /*aEvent*/,  const TInt& aError, TInt /*aTransId*/ )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In Handle Return Value\n");
    iLog->Log(KFunc);
    if(aError == KErrArgument)
    iErr = KErrNone;
    else
    iErr = aError;
    TBuf<5> buf;
    buf.Num(aError);
    iLog->Log(KError);
    iLog->Log(buf);
    iLog->Log(KNewLine);
    }
    
void CContactsUT::HandleReturnIter(const TInt& aError, CContactIter* aIter, TInt /*aTransId*/ )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In Handle Return Iter\n");
    iLog->Log(KFunc);
    iErr = aError;
    TBuf<5> buf;
    buf.Num(aError);
    iLog->Log(KError);
    iLog->Log(buf);
    iLog->Log(KNewLine);       
    
    if(EGetContactDelete == iOperation )
        {
        iOperation = ENone;        
        CSingleContact* singleContact = NULL;  
        HBufC8* buf = NULL;
        TInt count = 0; 
        while(ETrue)
            {
            aIter->NextL(singleContact,buf);
            if(!singleContact)
                {
                break;
                }
            iBuffer = buf;
           // delete buf;
            delete singleContact;
            break;
            }
        }
    if(iOperation == EContact)
        {
        iOperation = ENone;
        iErr = KErrGeneral;
        CSingleContact* singleContact = NULL;        
        HBufC8* buf = NULL; 
        
        _LIT(KPhone,"Birbal");       
        _LIT8(KField,"FirstName");
        
        while(ETrue)
            {
            __UHEAP_MARK;
            aIter->NextL(singleContact,buf);           
            if(!singleContact)
                {
                break;
                }            
            CleanupStack::PushL(singleContact);
            //CleanupStack::PushL(buf);            
            if(!buf->Compare(*iBuffer))
                {     
                TInt count(singleContact->FieldCount());       
                CSingleContactField* field = NULL;                 
                while(count)
                    {            
                    TPtrC8 fieldKey;
                    TPtrC label;
                    TPtrC value;
                    field = singleContact->FieldAt(--count);
                    field->GetFieldDataL(fieldKey,label,value);
                    if(!fieldKey.Compare(KField))
                        {
                        field->SetFieldParamsL(KField,KNullDesC,KPhone);
                        iLog->Log(_L("Phone Contact Field modified \n"));
                        __UHEAP_MARK;
                        iServiceHandle->AddL(this,0,singleContact);
                        iLog->Log(_L("AddL called\n"));
                        iLog->Log(_L("Start Active Scheduler\n"));
                        CActiveScheduler::Start(); 
                        __UHEAP_MARKEND;
                        break;                        
                        }
                    }
                }            
              
            //CleanupStack::PopAndDestroy(buf);
            delete buf;
            CleanupStack::PopAndDestroy(singleContact);  
            __UHEAP_MARKEND;
            }
         } 
    if(EGetContact == iOperation )
        {
        iOperation = ENone;
        //iErr = KErrGeneral;
        _LIT8(KFirstName,"FirstName");
        _LIT(KName,"Kats"); 
        CSingleContact* singleContact = NULL;  
        HBufC8* buf = NULL;
        TInt count = 0; 
        while(ETrue)
            {
            aIter->NextL(singleContact,buf);
            if(!singleContact)
                {
                break;
                }
            ++count;
            TInt count(singleContact->FieldCount());            
            while(count)
                {
                CSingleContactField* field = singleContact->FieldAt(--count);
                TPtrC8 fieldKey;
                TPtrC label;
                TPtrC value;
                field->GetFieldDataL(fieldKey,label,value);
                if (fieldKey == KFirstName && value == KName)
                    {
                    iErr = KErrNone;
                    }
              //  delete field;
                }
            delete buf;
            delete singleContact;
            }
		delete buf;            
        }
    if(EContactVerify == iOperation )
        {       
        iOperation = ENone;
        iErr = KErrGeneral;
        _LIT8(KFirstName,"FirstName");
        _LIT(KName,"Tenali"); 
        CSingleContact* singleContact = NULL;  
        HBufC8* buf = NULL;
        aIter->NextL(singleContact,buf);
        if(buf->Compare(*iBuf)==0)
            {
            iErr = KErrNone;    
            }
        }    
    if(EContactId == iOperation )
        {
        iOperation = ENone;
        //iErr = KErrGeneral;
        _LIT8(KFirstName,"FirstName");
        _LIT(KName,"Tenali"); 
        CSingleContact* singleContact = NULL;  
        HBufC8* buf = NULL;
        TInt count = 0; 
        
        aIter->NextL(singleContact,buf);
        iOperation = EContactVerify;
        iBuf = buf;
        iServiceHandle->GetListL(this,0,EContacts,*buf);
        CActiveScheduler::Start();
        delete singleContact;                       
        } 
    if(ESearchContact == iOperation )
        {
        iOperation = ENone;
        iErr = KErrGeneral;
        _LIT8(KFirstName,"FirstName");
        _LIT(KName,"Tenali"); 
        CSingleContact* singleContact = NULL;  
        HBufC8* buf = NULL;
        TInt count = 0; 
        while(ETrue)
            {
            aIter->NextL(singleContact,buf);
            if(!singleContact)
                {
                break;
                }
            ++count;
            TInt count(singleContact->FieldCount());
            while(count)
                {
                CSingleContactField* field = singleContact->FieldAt(--count);
                TPtrC8 fieldKey;
                TPtrC label;
                TPtrC value;
                field->GetFieldDataL(fieldKey,label,value);
                if (fieldKey == KFirstName && value == KName)
                    {
                    iErr = KErrNone;
                    }
            else if (fieldKey == KFirstName)
                {
                break;    
                }
            }
        delete singleContact;            
        }
        }
     if(EAscContact == iOperation )
        {
        iOperation = ENone;
        iErr = KErrGeneral;
        _LIT8(KFirstName,"FirstName");
        _LIT(KNameT,"Tenali");
        _LIT(KNameB,"Birbal"); 
        TInt count1 = 0;
        TInt tCount = 0;
        TInt bCount = 0;
        CSingleContact* singleContact = NULL;  
        HBufC8* buf = NULL;
        TInt count = 0; 
        
        while(ETrue)
            {
            aIter->NextL(singleContact,buf);
            if(!singleContact)
                {
                break;
                }
            ++count;
            TInt count(singleContact->FieldCount());
            while(count)
                {
                CSingleContactField* field = singleContact->FieldAt(--count);
                TPtrC8 fieldKey;
                TPtrC label;
                TPtrC value;
                field->GetFieldDataL(fieldKey,label,value);
                if (fieldKey == KFirstName && value == KNameT)
                    {
                    ++count1;
                    tCount = count1;
                    }
                if (fieldKey == KFirstName && value == KNameB)
                    {
                    ++count1;
                    bCount = count1;
                    }    
              
                }               
            delete singleContact;
            }
            
        if(bCount>0 && tCount>0 && bCount<tCount)
                  {
                  iErr = KErrNone;  
                  }     
        }
        
    if(EDscContact == iOperation )
        {
        iOperation = ENone;
        iErr = KErrGeneral;
        _LIT8(KFirstName,"FirstName");
        _LIT(KNameT,"Tenali");
        _LIT(KNameB,"Birbal"); 
        TInt count1 = 0;
        TInt tCount = 0;
        TInt bCount = 0;
        CSingleContact* singleContact = NULL;  
        HBufC8* buf = NULL;
        TInt count = 0; 
        while(ETrue)
            {
            aIter->NextL(singleContact,buf);
            if(!singleContact)
                {
                break;
                }
            ++count;
            TInt count(singleContact->FieldCount());
            while(count)
                {
                CSingleContactField* field = singleContact->FieldAt(--count);
                TPtrC8 fieldKey;
                TPtrC label;
                TPtrC value;
                field->GetFieldDataL(fieldKey,label,value);
                if (fieldKey == KFirstName && value == KNameT)
                    {
                    ++count1;
                    tCount = count1;
                    }
                if (fieldKey == KFirstName && value == KNameB)
                    {
                    ++count1;
                    bCount = count1;
                    }                  
                }
            delete singleContact;
            }
        if(bCount>tCount)
                  {
                  iErr = KErrNone;  
                  }    
        }            
    if(EGetGroup == iOperation )
        {
        iOperation = ENone;
        iErr = KErrGeneral;
        CSingleContact* singleContact = NULL;  
        HBufC8* buf = NULL;
        TInt count = 0; 
        while(ETrue)
            {
            aIter->NextL(singleContact,buf);
            iBuffer = buf;
            if(!singleContact)
                {
                break;
                }
            ++count; 
            TInt fields(singleContact->FieldCount());
            while(fields)
                {
                CSingleContactField* field = singleContact->FieldAt(--fields);
                TPtrC groupId;
                RPointerArray<TDesC8> array;
                field->GetFieldDataL(groupId,array);
              
                
                if(groupId.Compare(KGroup1)==0)
                    {
                    iErr = KErrNone; 
                    break;   
                    }
                   
                }
                          
            }
        }
    delete aIter;  
    }

void CContactsUT::HandleRetrieveContact( MVPbkStoreContact* /*aStoreContact*/, TInt /*aTransId*/ )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In Handle Retrieve Contact\n");
    iLog->Log(KFunc);
    }

void CContactsUT::ContactOperationCompleted(TContactOpResult aResult)
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In ContactOperationCompleted \n");
    iLog->Log(KFunc);
    iErr = KErrNone;
    TBuf<5> buf;
    buf.Num(aResult.iOpCode);
    iLog->Log(KSuccess);
    iLog->Log(buf);
    iLog->Log(KNewLine);
    switch(iOperation)
        {/*
        case EContact: delete iStoreContact;
                       iStoreContact = NULL;
                       break;*/
        case EGroup: delete iGroup;
                     iGroup = NULL;
                     break;
        }          
    iOperation = ENone;
    }
void CContactsUT::ContactOperationFailed
            (TContactOp /*aOpCode*/, TInt aErrorCode, TBool /*aErrorNotified*/)
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In ContactOperationFailed \n");
    iLog->Log(KFunc);
    iErr = aErrorCode;
    TBuf<5> buf;
    buf.Num(aErrorCode);
    iLog->Log(KError);
    iLog->Log(buf);
    iLog->Log(KNewLine);
    switch(iOperation)
        {
        case EContact:/* delete iStoreContact;
                       iStoreContact = NULL;
                       break;*/
        case EGroup: delete iGroup;
                     iGroup = NULL;
                     break;
        }          
    iOperation = ENone;
    }  
            
void CContactsUT::FindCompleteL( MVPbkContactLinkArray* aResults )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In FindCompleteL \n");
    iLog->Log(KFunc);
    iErr = KErrNone;
    TInt count = aResults->Count();
    iFindResults = aResults;
    iLog->Log(KSuccess);
    }
void CContactsUT::FindFailed( TInt aError )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In FindFailed \n");
    iLog->Log(KFunc);
    iErr = aError;
    TBuf<5> buf;
    buf.Num(aError);
    iLog->Log(KError);
    iLog->Log(buf);
    iLog->Log(KNewLine);
    }
    
void CContactsUT::VPbkSingleContactOperationComplete(
                MVPbkContactOperationBase& aOperation,
                MVPbkStoreContact* aContact )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In VPbkSingleContactOperationComplete \n");
    iLog->Log(KFunc);
    iErr = KErrNone;
    
    if(iOperation == EVCard)
        {
        iDestStream.CommitL();
        delete iOp;
        iOp = NULL;
        iDestStream.Close();
        delete iResult;
        iResult = NULL;
        }
    else if(iOperation == EVCardEx)
        {        
        delete iOp;
        iOp = NULL;
        }
    else
        {
        delete iStoreContact;
        iStoreContact = NULL;
        iStoreContact = aContact;
        if( iOp == &aOperation )
            {
                delete iOp;
                iOp = NULL;
            }
        }
    iOperation = ENone;
    iLog->Log(KSuccess);
    }


void CContactsUT::VPbkSingleContactOperationFailed(
                MVPbkContactOperationBase& aOperation, 
                TInt aError )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In VPbkSingleContactOperationFailed \n");
    iLog->Log(KFunc);
    iErr = aError;
    ;
    if(iOperation == EVCard)
        {
        iDestStream.CommitL();
        delete iOp;
        iOp = NULL;
        iDestStream.Close();
        delete iBuffer;
        iBuffer = NULL;
        delete iResult;
        iResult = NULL;
        }
    else if(iOperation == EVCardEx)
        {        
        delete iOp;
        iOp = NULL;
        }
    else
        {
        delete iStoreContact;
        iStoreContact = NULL;
        if( iOp == &aOperation )
            {
                delete iOp;
                iOp = NULL;
            }
        }
    TBuf<5> buf;
    buf.Num(aError);
    iLog->Log(KError);
    iLog->Log(buf);
    iLog->Log(KNewLine);
    
    iOperation = ENone;
    }

void CContactsUT::StepComplete( 
                MVPbkContactOperationBase& /*aOperation*/,
                TInt /*aStepSize*/ )
    {
    _LIT(KFunc,"In StepComplete \n");
    iLog->Log(KFunc);
    iLog->Log(KSuccess);
    iLog->Log(KNewLine);
    }

TBool CContactsUT::StepFailed(
                MVPbkContactOperationBase& /*aOperation*/,
                TInt /*aStepSize*/, TInt /*aError*/ )
    {
    _LIT(KFunc,"In StepFailed \n");
    iLog->Log(KFunc);
    return EFalse;
    }

void CContactsUT::OperationComplete( 
                MVPbkContactOperationBase& /*aOperation*/ )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In OperationComplete \n");
    iLog->Log(KFunc);
    iErr = KErrNone;
    iLog->Log(KSuccess);
    iLog->Log(KNewLine);
    }


//Delete all contacts
void CContactsUT::DeleteAllL()
    {
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In DeleteAllL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    iErr = KErrNone;
       
    __UHEAP_MARK;    
    iOp = iContactManager->MatchPhoneNumberL(
        KPhoneNumber, KPhoneNumber().Length(), *this );    
    CActiveScheduler::Start();
    delete iOp;
    iOp = NULL;
    
    TInt count(iFindResults->Count());
    iContactToDelete = CVPbkContactLinkArray::NewLC();
    while(count)
        {  
        MVPbkContactLink* link = iFindResults->At(--count).CloneLC();
        iContactToDelete->AppendL(link);
        CleanupStack::Pop();
        }
    delete iFindResults;
    iFindResults = NULL;
        
    iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
    CActiveScheduler::Start();
    delete iOp;
    iOp = NULL;
    CleanupStack::PopAndDestroy(iContactToDelete);
    iContactToDelete = NULL;
         
    
    __UHEAP_MARKEND;          
    }
    
//Add 1 contact
void CContactsUT::AddOneContactL(TDesC& aName)
    {
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In AddOneContactL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    iErr = KErrNone;
    
    __UHEAP_MARK;
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( aName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KPhoneNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::PopAndDestroy(); // iStoreContact
    iStoreContact = NULL;
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    __UHEAP_MARKEND;    
    }
    
//Check for contact
void CContactsUT::CheckContactsL(TInt& aCount,RPointerArray<TDesC8>& aIdArray)
    {    
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In CheckContactsL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    iErr = KErrNone;
        
    //__UHEAP_MARK;
    iOp = iContactManager->MatchPhoneNumberL(
        KPhoneNumber, KPhoneNumber().Length(), *this );    
    CActiveScheduler::Start();
    delete iOp;
    iOp = NULL;
    
    aCount = iFindResults->Count();
    TInt count(aCount);
    while(count)
        {
        aIdArray.AppendL((const_cast<MVPbkContactLink&>(iFindResults->At(--count))).PackLC());
        CleanupStack::Pop();
        }
    delete iFindResults;
    iFindResults = NULL;
   // __UHEAP_MARKENDC(aCount);          
    }
    
// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::AddContactSAPIL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In AddContactSAPIL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    DeleteAllL();
    
     /**Add contact using SAPI Core class*/
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Sikandar"); 
    _LIT8(KNumber,"MobilePhoneGen");
        
    __UHEAP_MARK;
    //instantiate service class 
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    CSingleContact* singleContact = CSingleContact::NewL();
    CleanupStack::PushL(singleContact);
    iLog->Log(_L("single Contact created\n"));
    
    CSingleContactField* nameContactField = CSingleContactField::NewL();
    CleanupStack::PushL(nameContactField);
    iLog->Log(_L("Name Contact Field created \n"));
    
    CSingleContactField* phoneContactField = CSingleContactField::NewL();
    CleanupStack::PushL(phoneContactField);
    iLog->Log(_L("Phone Contact Field created \n"));
    
    nameContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(nameContactField);
    iLog->Log(_L("Name Contact Field added \n"));
    
    phoneContactField->SetFieldParamsL(KNumber,KNullDesC,KPhoneNumber);
    singleContact->AddFieldToContactL(phoneContactField);
    iLog->Log(_L("Phone Contact Field added \n"));
    
    serviceHandle->AddL(this,0,singleContact);
    iLog->Log(_L("AddL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();    
    
    CleanupStack::Pop(phoneContactField);//singleContactField	
    CleanupStack::Pop(nameContactField);//singleContactField	
    CleanupStack::PopAndDestroy(singleContact);//singleContact
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle   
    iLog->Log( KServiceClose );
    __UHEAP_MARKEND; 
    /**end */
    
    TInt count;
    RPointerArray<TDesC8> idArray;
    CheckContactsL(count,idArray);
    if(count != 1)
        {
        iErr = KErrGeneral;
        }
    idArray.ResetAndDestroy();
    
    DeleteAllL();
    return iErr;    
    }

// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::DeleteContactSAPIL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In DeleteContactSAPIL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    DeleteAllL();
    _LIT(KName,"SpiderMan");
    TPtrC name(KName);
    AddOneContactL(name);
    
    TInt count(0);
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);
    CheckContactsL(count,idArray);
    if(count != 1)
        {
        return KErrGeneral;
        }
        
    /**Delete using SAPI core class*/
    
    __UHEAP_MARK;         
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
   
    serviceHandle->DeleteL(this,0,idArray);
    iLog->Log(_L("DeleteL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start(); 
   
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle      	          
    iLog->Log( KServiceClose ); 
    __UHEAP_MARKEND;  
    /**end*/
    CleanupStack::Pop(&idArray);
    idArray.ResetAndDestroy();
        
    RPointerArray<TDesC8> idArray1;
    CleanupClosePushL(idArray1);
    CheckContactsL(count,idArray1);
    if(count)
        {
        iErr = KErrGeneral;
        }
    CleanupStack::Pop(&idArray1);
    idArray.ResetAndDestroy();
    return iErr;
        
    }
    
// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::ModifyContactSAPIL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In ModifyContactSAPIL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    DeleteAllL();
    _LIT(KName,"SuperMan");
    TPtrC name(KName);
    AddOneContactL(name);
    
    TInt count(0);
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);
    CheckContactsL(count,idArray);
    if(count != 1)
        {
        return KErrGeneral;
        }
      
    /**Get using SAPI core class*/    
    __UHEAP_MARK;         
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    serviceHandle->GetListL(this,0,EContacts,*idArray[0]);
    iLog->Log(_L("GetListL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();
    
    if(!iSingleContact)
        {
        return KErrGeneral;
        }
    
    _LIT(KName1,"SpiderMan");
    _LIT8(KFirstName,"FirstName");
    CSingleContactField* field = NULL; 
    TInt fieldCount(iSingleContact->FieldCount());                    
    while(fieldCount)
        {            
        TPtrC8 fieldKey;
        TPtrC label;
        TPtrC value;
        field = iSingleContact->FieldAt(--fieldCount);
        field->GetFieldDataL(fieldKey,label,value);
        if(!fieldKey.Compare(KFirstName) && !value.Compare(KName))
            {
            field->SetFieldParamsL(KFirstName,KNullDesC,KName1);
            iLog->Log(_L("Phone Contact Field modified \n"));            
            break;                        
            }
        }
   
    __UHEAP_MARK;
    serviceHandle->AddL(this,0,iSingleContact);
    iLog->Log(_L("AddL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();        
    __UHEAP_MARKEND;
    
    delete iSingleContact;
    iSingleContact = NULL;
    
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle      	          
    iLog->Log( KServiceClose ); 
    __UHEAP_MARKEND;  
    /**end*/
    
    
    CleanupStack::Pop(&idArray);
    idArray.ResetAndDestroy();
        
    RPointerArray<TDesC8> idArray1;
    CleanupClosePushL(idArray1);
    CheckContactsL(count,idArray1);
    if(count != 1)
        {
        iErr = KErrGeneral;
        }
    CleanupStack::Pop();
    idArray1.ResetAndDestroy();
    //to implement ..checking name
    return iErr;
        
    }

// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::ImportContactSAPIL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In ImportContactSAPIL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone; 
    _LIT(KFileName,"c:\\vcardim.vcf");
    
  /*  DeleteAllL();
    
    _LIT(KName,"SuperMan");
    TPtrC name(KName);
    AddOneContactL(name);
    
    TInt count(0);
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);
    CheckContactsL(count,idArray);
    if(count != 1)
        {
        return KErrGeneral;
        }
        
    //__UHEAP_MARK;
    MVPbkContactLinkArray* linkArray = iContactManager->CreateLinksLC(*idArray[0]);
    iVCardEngine = CVPbkVCardEng::NewL( *iContactManager );
     // Create the buffer to store the contact
    iBuffer = HBufC8::NewL( 1024 );
    TPtr8 bufferPtr( iBuffer->Des() );
    iDestStream.Open( bufferPtr );
    //export the contact from MVPbkContactLink
   // __UHEAP_MARK;
    iOp = iVCardEngine->ExportVCardL( iDestStream, linkArray->At(0), *this );
    CActiveScheduler::Start();    
    
    // __UHEAP_MARKEND;
    if( !iErr )
        {
        iDestStream.CommitL();
        }
    
    iDestStream.Close();
    if(iBuffer)
        {
        RFile file;
        CleanupClosePushL(file);            
        file.Replace(iRfs,KFileName,EFileWrite);
        file.Write(0,*iBuffer);
        CleanupStack::PopAndDestroy(&file);        
        }    
    delete iBuffer;
    iBuffer = NULL;
    delete iVCardEngine;
    iVCardEngine = NULL;   
    CleanupStack::PopAndDestroy();//linkArray      
    //__UHEAP_MARKEND;
    
    CleanupStack::Pop(&idArray);
    idArray.ResetAndDestroy();
    DeleteAllL();
    */
    DeleteAllL();
    __UHEAP_MARK;
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    TFileName importFile(KFileName);
    
    serviceHandle->ImportVCardToStoreL(this,0,importFile);
    iLog->Log(_L("ImportVCardToStoreL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();  
    
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle        
    iLog->Log( KServiceClose );   
    __UHEAP_MARKEND;
    
    TInt count = 0;
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);
    CheckContactsL(count,idArray);
    if(count != 1)
        {
        return KErrGeneral;
        }
    CleanupStack::Pop(&idArray);
    idArray.ResetAndDestroy();
    return iErr;
    }
    
// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::ExportContactSAPIL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In ExportContactSAPIL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone; 
    _LIT(KFileName,"c:\\vcardim.vcf");
    _LIT(KFileName1,"c:\\vcardim1.vcf");
    
    DeleteAllL();
    
    _LIT(KName,"SuperMan");
    TPtrC name(KName);
    AddOneContactL(name);
    
    _LIT(KName1,"SpiderMan");
    TPtrC name1(KName1);
    AddOneContactL(name1);
    
    TInt count(0);
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);
    CheckContactsL(count,idArray);
    TInt ret = iRfs.Delete(KFileName);
   // ret = iRfs.Delete(KFileName1);
   /* if(count != 1)
        {
        return KErrGeneral;
        }*/
        
   /* __UHEAP_MARK;
    RFile writeStream;
    CleanupClosePushL(writeStream);
    User::LeaveIfError(writeStream.Create(iRfs,KFileName,EFileWrite));
    while(count)
        {
        writeStream.Write(*idArray[--count]);
        }
    CleanupStack::PopAndDestroy(&writeStream);
    __UHEAP_MARKEND;
    */
    //iBuffer = HBufC8::NewL( 1024 );
    //TPtr8 bfrPtr(iBuffer->Des());
   // __UHEAP_MARK;
    //RFileReadStream readStream;
   // CleanupClosePushL(readStream);
   // User::LeaveIfError(readStream.Open(iRfs,KFileName,EFileRead));
    
    //TInt cells = User::CountAllocCells();
    __UHEAP_MARK;
    RFileWriteStream destStream;
    CleanupClosePushL(destStream);
    User::LeaveIfError(destStream.Create(iRfs,KFileName,EFileWrite));
    iVCardEngine = CVPbkVCardEng::NewL( *iContactManager );
    while(count)
        {
        MVPbkContactLinkArray* linkArray = iContactManager->CreateLinksLC(*idArray[--count]);
        const MVPbkContactLink& link = linkArray->At(0);
        iOp = iVCardEngine->ExportVCardL( destStream, link, *this );
        CActiveScheduler::Start();
        destStream.CommitL();
        CleanupStack::PopAndDestroy();
        }
    delete iVCardEngine;
    iVCardEngine = NULL;
    CleanupStack::PopAndDestroy(&destStream);
    __UHEAP_MARKEND;
    CleanupStack::Pop(&idArray);
    idArray.ResetAndDestroy();
    
    /*
    //CleanupStack::PushL(linkArray);
    cells = User::CountAllocCells();
    iVCardEngine = CVPbkVCardEng::NewL( *iContactManager );
    
    cells = User::CountAllocCells();    
    RDesWriteStream destStream;
    CleanupClosePushL(destStream);
    //User::LeaveIfError(destStream.Create(iRfs,KFileName1,EFileWrite));
    destStream.Open(bfrPtr);
    TInt links = linkArray->Count();
    while(links)
        {
        const MVPbkContactLink& link = linkArray->At(--links);
        iOp = iVCardEngine->ExportVCardL( destStream, link, *this );
        CActiveScheduler::Start();
        }
    destStream.CommitL();
    CleanupStack::PopAndDestroy(&destStream);
    
    cells = User::CountAllocCells();
    delete iVCardEngine;
    iVCardEngine = NULL;
    cells = User::CountAllocCells();
    
    CleanupStack::PopAndDestroy();
    cells = User::CountAllocCells();
    CleanupStack::PopAndDestroy(&readStream);
    
   // __UHEAP_MARKEND;
   if(iBuffer)
        {
        RFile file;
        CleanupClosePushL(file);            
        file.Replace(iRfs,KFileName,EFileWrite);
        file.Write(0,*iBuffer);
        CleanupStack::PopAndDestroy(&file);        
        }    
    delete iBuffer;
    iBuffer = NULL;
    CleanupStack::Pop(&idArray);
    idArray.ResetAndDestroy();
    /*
     // Create the buffer to store the contact
    iBuffer = HBufC8::NewL( 1024 );
    TPtr8 bufferPtr( iBuffer->Des() );
    iDestStream.Open( bufferPtr );
    //export the contact from MVPbkContactLink
   // __UHEAP_MARK;
    
    CActiveScheduler::Start();    
    
    // __UHEAP_MARKEND;
    if( !iErr )
        {
        iDestStream.CommitL();
        }
    
    iDestStream.Close();
    if(iBuffer)
        {
        RFile file;
        CleanupClosePushL(file);            
        file.Replace(iRfs,KFileName,EFileWrite);
        file.Write(0,*iBuffer);
        CleanupStack::PopAndDestroy(&file);        
        }    
    delete iBuffer;
    iBuffer = NULL;
    delete iVCardEngine;
    iVCardEngine = NULL;   
    CleanupStack::PopAndDestroy();//linkArray      
    //__UHEAP_MARKEND;
    
    CleanupStack::Pop(&idArray);
    idArray.ResetAndDestroy();
    DeleteAllL();
    */
 /*   __UHEAP_MARK;
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    TFileName exportFile(KFileName);
    
    serviceHandle->ExportVCardL(this,0,exportFile,idArray);
    iLog->Log(_L("ExportVCardL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();  
    
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle        
    iLog->Log( KServiceClose );   
    __UHEAP_MARKEND;
    *//*
    TInt count = 0;
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);
    CheckContactsL(count,idArray);
    if(count != 1)
        {
        return KErrGeneral;
        }*/
   /* CleanupStack::Pop(&idArray);
    idArray.ResetAndDestroy();*/
    return iErr;
    }
// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::GetListDeleteContactL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;      
   
    
    /**Getlist using SAPI core class*/
    
    //__UHEAP_MARK;
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    iOperation = EGetContactDelete;
    serviceHandle->GetListL(this,0,EContacts);
    iLog->Log(_L("GetListL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();
    
    //iOperation = EGetContact;
    //iServiceHandle->GetListL(this,0,EContacts,*iBuffer);
    //CActiveScheduler::Start();
     /**Delete using SAPI core class*/
    
    //  __UHEAP_MARK;    
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);    
    idArray.AppendL(iBuffer);    
    
   
    serviceHandle->DeleteL(this,0,idArray);
    iLog->Log(_L("DeleteL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start(); 
   
   
    CleanupStack::PopAndDestroy(&idArray);//singleContactField      
    
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle   
    iLog->Log( KServiceClose );
  //  __UHEAP_MARKEND;
    
  
    
    return iErr;
    }
// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::AddContactGetListL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    /**Add contact using SAPI Core class*/
       
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Kats"); 
    _LIT8(KNumber,"MobilePhoneHome");
    _LIT(KPhone,"98789");
    
   // __UHEAP_MARK;
    //instantiate service class 
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    CSingleContact* singleContact = CSingleContact::NewL();
    CleanupStack::PushL(singleContact);
    iLog->Log(_L("single Contact created\n"));
    
    CSingleContactField* nameContactField = CSingleContactField::NewL();
    CleanupStack::PushL(nameContactField);
    iLog->Log(_L("Name Contact Field created \n"));
    
    CSingleContactField* phoneContactField = CSingleContactField::NewL();
    CleanupStack::PushL(phoneContactField);
    iLog->Log(_L("Phone Contact Field created \n"));
    
    nameContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(nameContactField);
    iLog->Log(_L("Name Contact Field added \n"));
    
    phoneContactField->SetFieldParamsL(KNumber,KNullDesC,KPhone);
    singleContact->AddFieldToContactL(phoneContactField);
    iLog->Log(_L("Phone Contact Field added \n"));
    
    serviceHandle->AddL(this,0,singleContact,KNullDesC8,KNullDesC);
    iLog->Log(_L("AddL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();    
    
    CleanupStack::Pop(phoneContactField);//singleContactField	
    CleanupStack::Pop(nameContactField);//singleContactField	
    CleanupStack::PopAndDestroy(singleContact);//singleContact
  //  CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle   
   // iLog->Log( KServiceClose );
//    __UHEAP_MARKENDC(1); 
    /**end */
    
    if(iErr)
        {
        return iErr;
        }
    
    /**Getlist using SAPI core class*/
    
    //__UHEAP_MARK;
    //serviceHandle = CContactService::NewL();
  //  CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    iOperation = EGetContact;
    serviceHandle->GetListL(this,0,EContacts);
    iLog->Log(_L("GetListL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();
    
    //iOperation = EGetContact;
    //iServiceHandle->GetListL(this,0,EContacts,*iBuffer);
    //CActiveScheduler::Start();
    
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle   
    iLog->Log( KServiceClose );
  //  __UHEAP_MARKEND;
    
    if(iErr)
        {
        return iErr;
        }
    /**Delete using virtual Phonebook */ 
    
    
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhone, KPhone().Length(), *this );    
    CActiveScheduler::Start();
    
    iErr = KErrGeneral;
    TInt count(iFindResults->Count());
    while(count)
        {            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(&(const_cast<MVPbkContactLink&>(iFindResults->At(--count))));
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();
        }       
    /**end  */   
  
    
    return iErr;
    }
// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::GetGroupsL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
   /**Add 1 group using virtual phonebook */
    
   
    
	iGroup = iStore->CreateNewContactGroupLC();
	iGroup->SetGroupLabelL(KGroup1);
	iOperation = EGroup;
	iGroup->CommitL(*this);
	
	CActiveScheduler::Start();
	CleanupStack::Pop();
	 
  
  //  __UHEAP_MARK;
    iServiceHandle = CContactService::NewL();
    iLog->Log( KServiceOpen );
    
    iOperation = EGetGroup;
    iServiceHandle->GetListL(this,0,EGroups);
    iLog->Log(_L("GetListL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();
    iOperation = EGetContactDelete;
    iServiceHandle->GetListL(this, 0, EGroups, *iBuffer);
    CActiveScheduler::Start();
    
    delete iServiceHandle;//serviceHandle   
    iServiceHandle = NULL;
    iLog->Log( KServiceClose );
 //   __UHEAP_MARKEND;
    
    
    
  
    return iErr;
    
    }

TInt CContactsUT::GetDatabaseL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    
  
  //  __UHEAP_MARK;
    iServiceHandle = CContactService::NewL();
    iLog->Log( KServiceOpen );
    
    iOperation = EGetDatabase;
    
    CContactIter* iter = CContactIter::NewL();
    iServiceHandle->GetListL(*iter);
    iLog->Log(_L("GetListL called\n"));
    TPtrC DbName;
    iter->NextL(DbName);
    
    while(!DbName.Compare(KNullDesC))
        {
        iter->NextL(DbName);
        }
        
    delete iServiceHandle;//serviceHandle   
    iServiceHandle = NULL;
    iLog->Log( KServiceClose );
 //   __UHEAP_MARKEND;
    
    
    
  
    return iErr;
    
    }

// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::GetContactsL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    /**Delete using virtual Phonebook */ 
    
    _LIT(KPhone,"13579");
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhone, KPhone().Length(), *this );    
    CActiveScheduler::Start();
    
    iErr = KErrGeneral;
    TInt count1(iFindResults->Count());
    while(count1)
        {            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(&(const_cast<MVPbkContactLink&>(iFindResults->At(--count1))));
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();
        }       
    /**end  */   
    
    /**Add 2 contacts using virtual phonebook*/
    
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KFirstName,"Tenali"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KFirstNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact

    
    // Create second contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KSecondName,"Birbal"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KSecondNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact
    
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    /**end*/
  	__UHEAP_MARK;
    iServiceHandle = CContactService::NewL();
    iLog->Log( KServiceOpen );
    
    iOperation = EGetContact;
    iServiceHandle->GetListL(this,0,EContacts);
    iLog->Log(_L("GetListL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();
            
    delete iServiceHandle;//serviceHandle   
    iServiceHandle = NULL;
    iLog->Log( KServiceClose );
  	__UHEAP_MARKEND;
    return iErr;
    
    }


TInt CContactsUT::GetContactsAscOrderL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
        
    
    _LIT(KPhone,"13579");
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhone, KPhone().Length(), *this );    
    CActiveScheduler::Start();
    
    iErr = KErrGeneral;
    TInt count1(iFindResults->Count());
    while(count1)
        {            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(&(const_cast<MVPbkContactLink&>(iFindResults->At(--count1))));
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();
        }       
    /*end  */   
    
    /**Add 2 contact using virtual phonebook*/
    
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KFirstName,"Tenali"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KFirstNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact

    
    // Create second contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KSecondName,"Birbal"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KSecondNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact
    
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    /**end*/
  
  
  
  
  
    /**GetList using SAPI Core class */
  //  __UHEAP_MARK;
    iServiceHandle = CContactService::NewL();
    iLog->Log( KServiceOpen );
    
    iOperation = EAscContact;     
    iServiceHandle->GetListL(this,0,EContacts,KNullDesC8,_L(""),NULL,EAsc);
    iLog->Log(_L("GetListL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();
    
    delete iServiceHandle;//serviceHandle   
    iServiceHandle = NULL;
    iLog->Log( KServiceClose );
 
  
    return iErr;
    
    }



 TInt CContactsUT::GetContactsDscOrderL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    /**Delete using virtual Phonebook */ 
    
    _LIT(KPhone,"13579");
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhone, KPhone().Length(), *this );    
    CActiveScheduler::Start();
    
    iErr = KErrGeneral;
    TInt count1(iFindResults->Count());
    while(count1)
        {            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(&(const_cast<MVPbkContactLink&>(iFindResults->At(--count1))));
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();
        }       
    /**end  */   
    
    /**Add 2 contact using virtual phonebook*/
    
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KFirstName,"Tenali"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KFirstNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact

    
    // Create second contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KSecondName,"Birbal"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KSecondNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact
    
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    /**end*/
  
  
  
  
  
    /**GetList using SAPI Core class */
  //  __UHEAP_MARK;
    iServiceHandle = CContactService::NewL();
    iLog->Log( KServiceOpen );
    
    iOperation = EDscContact;     
    iServiceHandle->GetListL(this,0,EContacts,KNullDesC8,_L(""),NULL,EDesc);
    iLog->Log(_L("GetListL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();
    
   
    
    delete iServiceHandle;//serviceHandle   
    iServiceHandle = NULL;
    iLog->Log( KServiceClose );
 
  
    return iErr;
    
    }
    
 TInt CContactsUT::GetSearchContactL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone; 
     
        
    /**Delete using virtual Phonebook */ 
    
    _LIT(KPhone,"13579");
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhone, KPhone().Length(), *this );    
    CActiveScheduler::Start();
    
    iErr = KErrGeneral;
    TInt count1(iFindResults->Count());
    while(count1)
        {            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(&(const_cast<MVPbkContactLink&>(iFindResults->At(--count1))));
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();
        }       
    /**end  */   
    
    /**Add 2 contact using virtual phonebook*/
    
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KFirstName,"Tenali"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KFirstNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact

    
    // Create second contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KSecondName,"Birbal"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KSecondNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact
    
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    /**end*/
  
  
  
  
  
    /**GetList using SAPI Core class */
  //  __UHEAP_MARK;
    iServiceHandle = CContactService::NewL();
    iLog->Log( KServiceOpen );
    
    iOperation = ESearchContact;     
    iServiceHandle->GetListL(this,0,EContacts,KNullDesC8,_L(""),NULL,EAsc);
    iLog->Log(_L("GetListL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();
    
    
    delete iServiceHandle;//serviceHandle   
    iServiceHandle = NULL;
    iLog->Log( KServiceClose );
  
  
    return iErr;
    
    }
  TInt CContactsUT::GetListConactIdL( CStifItemParser& aItem )
    {
     // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone; 
     
        
    /**Delete using virtual Phonebook */ 
    
    _LIT(KPhone,"13579");
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhone, KPhone().Length(), *this );    
    CActiveScheduler::Start();
    
    iErr = KErrGeneral;
    TInt count1(iFindResults->Count());
    while(count1)
        {            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(&(const_cast<MVPbkContactLink&>(iFindResults->At(--count1))));
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();
        }       
    /**end  */   
    
    /**Add 2 contact using virtual phonebook*/
    
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KFirstName,"Tenali"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KFirstNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact

    
    // Create second contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KSecondName,"Birbal"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KSecondNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact
    
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    /**end*/
  
  
  
  
  
    /**GetList using SAPI Core class */
  //  __UHEAP_MARK;
    iServiceHandle = CContactService::NewL();
    iLog->Log( KServiceOpen );
    
    iOperation = EContactId;     
    iServiceHandle->GetListL(this,0,EContacts);
    iLog->Log(_L("GetListL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();
    
    
    delete iServiceHandle;//serviceHandle   
    iServiceHandle = NULL;
    iLog->Log( KServiceClose );
  
  
    return iErr;
    
    }

// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::AddL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    /**Add contact using SAPI Core class*/
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Sikandar"); 
    _LIT8(KNumber,"MobilePhoneHome");
    _LIT(KPhone,"123456");
    
   // __UHEAP_MARK;
    //instantiate service class 
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    CSingleContact* singleContact = CSingleContact::NewL();
    CleanupStack::PushL(singleContact);
    iLog->Log(_L("single Contact created\n"));
    
    CSingleContactField* nameContactField = CSingleContactField::NewL();
    CleanupStack::PushL(nameContactField);
    iLog->Log(_L("Name Contact Field created \n"));
    
    CSingleContactField* phoneContactField = CSingleContactField::NewL();
    CleanupStack::PushL(phoneContactField);
    iLog->Log(_L("Phone Contact Field created \n"));
    
    nameContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(nameContactField);
    iLog->Log(_L("Name Contact Field added \n"));
    
    phoneContactField->SetFieldParamsL(KNumber,KNullDesC,KPhone);
    singleContact->AddFieldToContactL(phoneContactField);
    iLog->Log(_L("Phone Contact Field added \n"));
    
    serviceHandle->AddL(this,0,singleContact,KNullDesC8,KNullDesC);
    iLog->Log(_L("AddL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();    
    
    CleanupStack::Pop(phoneContactField);//singleContactField	
    CleanupStack::Pop(nameContactField);//singleContactField	
    CleanupStack::PopAndDestroy(singleContact);//singleContact
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle   
    iLog->Log( KServiceClose );
  //  __UHEAP_MARKEND; 
    /**end */
    
    if(iErr)
        {
        return iErr;
        }
    
    /**Delete using virtual Phonebook */ 
    /*
    
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhone, KPhone().Length(), *this );    
    CActiveScheduler::Start();
    
    iErr = KErrGeneral;
    TInt count(iFindResults->Count());
    while(count)
        {            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(&(const_cast<MVPbkContactLink&>(iFindResults->At(--count))));
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();
        }       
    /**end  */   
  
    
    return iErr;
    
    }


// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::AddInvalidFieldL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    /**Add contact using SAPI Core class*/
    
    _LIT8(KFirstName,"FistName"); //invalid field
    _LIT(KName,"Sikandar"); 
    _LIT8(KNumber,"MobilePhoneHome");
    _LIT(KPhone,"123456");
    
   // __UHEAP_MARK;
    //instantiate service class 
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    CSingleContact* singleContact = CSingleContact::NewL();
    CleanupStack::PushL(singleContact);
    iLog->Log(_L("single Contact created\n"));
    
    CSingleContactField* nameContactField = CSingleContactField::NewL();
    CleanupStack::PushL(nameContactField);
    iLog->Log(_L("Name Contact Field created \n"));
    
    CSingleContactField* phoneContactField = CSingleContactField::NewL();
    CleanupStack::PushL(phoneContactField);
    iLog->Log(_L("Phone Contact Field created \n"));
    
    nameContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(nameContactField);
    iLog->Log(_L("Name Contact Field added \n"));
    
    phoneContactField->SetFieldParamsL(KNumber,KNullDesC,KPhone);
    singleContact->AddFieldToContactL(phoneContactField);
    iLog->Log(_L("Phone Contact Field added \n"));
    
    serviceHandle->AddL(this,0,singleContact,KNullDesC8,KNullDesC);
    iLog->Log(_L("AddL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();    
    
    CleanupStack::Pop(phoneContactField);//singleContactField	
    CleanupStack::Pop(nameContactField);//singleContactField	
    CleanupStack::PopAndDestroy(singleContact);//singleContact
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle   
    iLog->Log( KServiceClose );
  //  __UHEAP_MARKEND; 
    /**end */
    
    if( KInvalidKey == iErr )
        {
        return KErrNone;
        }
    
    
    return iErr;
    
    }



// -----------------------------------------------------------------------------
// CContactsUT::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::AddMultiplePhoneNumbersContactL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In Add" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;  
    
    /**Add contact using SAPI Core class*/
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Sikandar"); 
    _LIT8(KNumber,"MobilePhoneHome");
    _LIT(KPhone,"123456");
	_LIT8(KNumber2,"MobilePhoneWork");
    _LIT(KPhone2,"654321");
    
   // __UHEAP_MARK;
    //instantiate service class 
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    CSingleContact* singleContact = CSingleContact::NewL();
    CleanupStack::PushL(singleContact);
    iLog->Log(_L("single Contact created\n"));
    
    CSingleContactField* nameContactField = CSingleContactField::NewL();
    CleanupStack::PushL(nameContactField);
    iLog->Log(_L("Name Contact Field created \n"));
    
    CSingleContactField* phoneContactField = CSingleContactField::NewL();
    CleanupStack::PushL(phoneContactField);
    iLog->Log(_L("Phone Contact Field created \n"));
    
    CSingleContactField* workPhoneContactField = CSingleContactField::NewL();
    CleanupStack::PushL(workPhoneContactField);
    iLog->Log(_L("Work Phone Contact Field created \n"));
        
    nameContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(nameContactField);
    iLog->Log(_L("Name Contact Field added \n"));
    
    phoneContactField->SetFieldParamsL(KNumber,KNullDesC,KPhone);
    singleContact->AddFieldToContactL(phoneContactField);
    iLog->Log(_L("Phone Contact Field added \n"));
    
    workPhoneContactField->SetFieldParamsL(KNumber2,KNullDesC,KPhone2);
    singleContact->AddFieldToContactL(workPhoneContactField);
    iLog->Log(_L("Phone Contact Field added \n"));
    
    serviceHandle->AddL(this,0,singleContact,KNullDesC8,KNullDesC);
    iLog->Log(_L("AddL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();    
    
    CleanupStack::Pop(workPhoneContactField);//singleContactField	
    CleanupStack::Pop(phoneContactField);//singleContactField	
    CleanupStack::Pop(nameContactField);//singleContactField	
    CleanupStack::PopAndDestroy(singleContact);//singleContact
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle   
    iLog->Log( KServiceClose );
  //  __UHEAP_MARKEND; 
    /**end */
    
    if(iErr)
        {
        return iErr;
        }
    
    /**Delete using virtual Phonebook */ 
    /*
    
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhone, KPhone().Length(), *this );    
    CActiveScheduler::Start();
    
    iErr = KErrGeneral;
    TInt count(iFindResults->Count());
    while(count)
        {            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(&(const_cast<MVPbkContactLink&>(iFindResults->At(--count))));
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();
        }       
    /**end  */   
  
    
    return iErr;
    
    }



        
// -----------------------------------------------------------------------------
// CContactsUT::AddGroupL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::AddGroupL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In AddGroup" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;   
    
    /**Add group using SAPI core class */
    __UHEAP_MARK;
    _LIT(KGroup,"Test");  
    //instantiate service class 
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );    
      
    serviceHandle->AddL(this,0,NULL,KNullDesC8,KGroup);
    iLog->Log(_L("AddL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();    
    
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle   
    iLog->Log( KServiceClose );
    /**end */
    __UHEAP_MARKEND;
    if(iErr)
        {
        return iErr;
        }
        
    /** Check for the added group using virtual phonebook classes */
    iFindResults = iStore->ContactGroupsLC();    
    TInt count(iFindResults->Count());    
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        iOp = iContactManager->RetrieveContactL(*iResult,*this);
        CActiveScheduler::Start();
        
        if(iErr)
            {
            break;
            }
        iErr = KErrGeneral;      
        iGroup = iStoreContact->Group();
        if(!iGroup->GroupLabel().Compare(KGroup))
            {
            iErr = KErrNone;
            iContactToDelete = CVPbkContactLinkArray::NewL();
            iContactToDelete->AppendL(iResult);
            iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
            CActiveScheduler::Start();    
            break;        
            }             
        }
    CleanupStack::Pop();
    iFindResults = NULL;
    /**end */
    
    return iErr;

    }


// -----------------------------------------------------------------------------
// CContactsUT::DeleteL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::DeleteContactL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In Delete" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;
    
    /**Add 2 contacts using virtual phonebook*/
    
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KFirstName,"Tenali"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KFirstNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact

    
    // Create second contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KSecondName,"Birbal"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KSecondNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact
    
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    /**end*/
    
    /** Search for the added contacts*/
    
    // Phone number to be searched for
    _LIT( KMatchNo, "13579" );
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KMatchNo, KMatchNo().Length(), *this );
    
    CActiveScheduler::Start();    
    TInt count(iFindResults->Count());
    /**end*/
    
    /**Delete using SAPI core class*/
    
    if(count>1)
        {    
        __UHEAP_MARK;    
        RPointerArray<TDesC8> idArray;
        CleanupClosePushL(idArray);
        TInt num(count);
        while(count)
            {
            HBufC8* contactId = (const_cast<MVPbkContactLink&>(iFindResults->At(--count))).PackLC();
            idArray.AppendL(contactId);  
            }
        
        CContactService* serviceHandle = CContactService::NewL();
        CleanupStack::PushL(serviceHandle);
        iLog->Log( KServiceOpen );
       
        serviceHandle->DeleteL(this,0,idArray);
        iLog->Log(_L("DeleteL called\n"));
        iLog->Log(_L("Start Active Scheduler\n"));
        CActiveScheduler::Start(); 
       
        CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle 
        
        CleanupStack::PopAndDestroy(num);//destroy all contactIds
        CleanupStack::PopAndDestroy(&idArray);//singleContactField	
          
        iLog->Log( KServiceClose ); 
        __UHEAP_MARKEND;  
              
        }
     /**end*/
      
    return iErr;

    }


// -----------------------------------------------------------------------------
// CContactsUT::DeleteInvalidContactL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::DeleteSingleContactL( CStifItemParser& aItem )
    {
		
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In Delete" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;
    
    /**Add 2 contacts using virtual phonebook*/
    
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KFirstName,"Tenali"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KFirstNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact

    
    // Create second contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KSecondName,"Birbal"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KSecondNumber,"13579"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact
    
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    /**end*/
    
    /** Search for the added contacts*/
    
    // Phone number to be searched for
    _LIT( KMatchNo, "13579" );
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KMatchNo, KMatchNo().Length(), *this );
    
    CActiveScheduler::Start();    
    TInt count(iFindResults->Count());
    /**end*/
    
    /**Delete using SAPI core class*/
    
    if(count>1)
        {    
        __UHEAP_MARK;    
        RPointerArray<TDesC8> idArray;
        CleanupClosePushL(idArray);
        TInt num(1);
        if(count)
            {
            HBufC8* contactId = (const_cast<MVPbkContactLink&>(iFindResults->At(--count))).PackLC();
            idArray.AppendL(contactId);  
            }
        
        CContactService* serviceHandle = CContactService::NewL();
        CleanupStack::PushL(serviceHandle);
        iLog->Log( KServiceOpen );
       
        serviceHandle->DeleteL(this,0,idArray);
        iLog->Log(_L("DeleteL called\n"));
        iLog->Log(_L("Start Active Scheduler\n"));
        CActiveScheduler::Start(); 
       
        CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle 
        
        CleanupStack::PopAndDestroy(num);//destroy all contactIds
        CleanupStack::PopAndDestroy(&idArray);//singleContactField	
          
        iLog->Log( KServiceClose ); 
        __UHEAP_MARKEND;  
              
        }
     /**end*/
      
    return iErr;

    }

// -----------------------------------------------------------------------------
// CContactsUT::DeleteListL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::DeleteGroupL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In DeleteList" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    iErr = KErrNone;
     
    /**Add 2 groups using virtual phonebook */
    
    _LIT(KGroup1,"Test1");
    _LIT(KGroup2,"Test2");
	iGroup = iStore->CreateNewContactGroupLC();
	iGroup->SetGroupLabelL(KGroup1);
	iOperation = EGroup;
	iGroup->CommitL(*this);
	
	CActiveScheduler::Start();
	CleanupStack::Pop();
	
	iGroup = iStore->CreateNewContactGroupLC();
	iGroup->SetGroupLabelL(KGroup2);
	iOperation = EGroup;
	iGroup->CommitL(*this);
	
	CActiveScheduler::Start();
	CleanupStack::Pop();
    /**end */
    
    if(iErr)
        {
        return iErr;
        }
        
    /**Delete the groups using SAPI core class */
    
    /** Check for the added group using virtual phonebook classes */   
      
    iFindResults = iStore->ContactGroupsLC();    
    TInt count(iFindResults->Count());    
    if(count>1)
        {
        HBufC8* groupId;
        RPointerArray<TDesC8> idArray;  
        CleanupClosePushL(idArray);
        while(count)
            {
            iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
            iOp = iContactManager->RetrieveContactL(*iResult,*this);
            CActiveScheduler::Start();
            
            iGroup = iStoreContact->Group();
            if(!iGroup->GroupLabel().Compare(KGroup1) || !iGroup->GroupLabel().Compare(KGroup2))
                {
                groupId = iResult->PackLC();
                idArray.AppendL(groupId);
                }             
            }
        TInt num(idArray.Count());  
        if( num < 2)
            {
            return KErrGeneral;
            }
        __UHEAP_MARK;    
        CContactService* serviceHandle = CContactService::NewL();
        CleanupStack::PushL(serviceHandle);
        iLog->Log( KServiceOpen );
       
        serviceHandle->DeleteL(this,0,idArray);
        iLog->Log(_L("DeleteL called\n"));
        iLog->Log(_L("Start Active Scheduler\n"));
        CActiveScheduler::Start(); 
       
        CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle 
        __UHEAP_MARKEND;
        CleanupStack::PopAndDestroy(num);//destroy all contactIds
        CleanupStack::PopAndDestroy(&idArray);//singleContactField	
          
        iLog->Log( KServiceClose );        
        }        
    CleanupStack::Pop();
    iFindResults = NULL;
    /**end */
    
    return iErr;

    }

// -----------------------------------------------------------------------------
// CContactsUT::ModifyL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::ModifyL( CStifItemParser& aItem )
    {
   
    
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In Modify" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    iErr = KErrNone;
    
    DeleteAllL();
    _LIT(KFirstName,"Tenali");
    TPtrC ptr(KFirstName);
    AddOneContactL(ptr);
        
    /** Retrieve contact ids and modify using SAPI core class */
        
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhoneNumber, KPhoneNumber().Length(), *this );
    
    CActiveScheduler::Start(); 
       
    TInt count(iFindResults->Count());
    /**end*/
    
    /**Modify using SAPI core class*/
     
    if(count)
        {        
        while(count)
            { 
            //__UHEAP_MARK;           
            iBuffer = (const_cast<MVPbkContactLink&>(iFindResults->At(--count))).PackLC();
            CleanupStack::Pop();//iBuffer            
            iServiceHandle = CContactService::NewL();
            iLog->Log( KServiceOpen );
            
            iOperation = EContact;
            iServiceHandle->GetListL(this,0,EContacts,*iBuffer);
            iLog->Log(_L("GetListL called\n"));
            iLog->Log(_L("Start Active Scheduler\n"));
            CActiveScheduler::Start();
            
            delete iServiceHandle;//serviceHandle   
            iServiceHandle = NULL;
            iLog->Log( KServiceClose );
            //__UHEAP_MARKEND;
            }       
        
        }
     
    /** ends */
        
    return iErr;

    }

// -----------------------------------------------------------------------------
// CContactsUT::ModifyGroupL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::ModifyGroupL( CStifItemParser& aItem )
    {
   
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In ModifyGroup" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    iErr = KErrNone;
    /**Add 1 group using virtual phonebook */
    
    _LIT(KGroup1,"Modify1");
    _LIT(KGroup2,"Modify2");
    iGroup = iStore->CreateNewContactGroupLC();
	iGroup->SetGroupLabelL(KGroup1);
	iOperation = EGroup;
	iGroup->CommitL(*this);
	
	CActiveScheduler::Start();
	CleanupStack::Pop();
	/**end */
	
	/** Check for the added group using virtual phonebook classes */
    iFindResults = iStore->ContactGroupsLC();    
    TInt count(iFindResults->Count());    
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        iOp = iContactManager->RetrieveContactL(*iResult,*this);
        CActiveScheduler::Start();
        
        if(iErr)
            {
            break;
            }
        iErr = KErrGeneral;      
        iGroup = iStoreContact->Group();
        if(!iGroup->GroupLabel().Compare(KGroup1))
            {
             __UHEAP_MARK;
            CContactService* serviceHandle = CContactService::NewL();
            CleanupStack::PushL(serviceHandle);
            iLog->Log( KServiceOpen );    
              
            serviceHandle->AddL(this,0,NULL,KNullDesC8,KGroup2);
            iLog->Log(_L("ModifyGroupL called\n"));
            iLog->Log(_L("Start Active Scheduler\n"));
            CActiveScheduler::Start();    
            
            CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle   
            iLog->Log( KServiceClose ); 
            __UHEAP_MARKEND;               
            }             
        }
    CleanupStack::Pop();
    iFindResults = NULL;
    /**end */
    
    /** Check for the added group using virtual phonebook classes */
    iFindResults = iStore->ContactGroupsLC();    
    count = iFindResults->Count();    
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        iOp = iContactManager->RetrieveContactL(*iResult,*this);
        CActiveScheduler::Start();
        
        if(iErr)
            {
            break;
            }
        iErr = KErrGeneral;      
        iGroup = iStoreContact->Group();
        if(!iGroup->GroupLabel().Compare(KGroup2))
            {
            iErr = KErrNone;
            iContactToDelete = CVPbkContactLinkArray::NewL();
            iContactToDelete->AppendL(iResult);
            iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
            CActiveScheduler::Start();    
            break;        
            }             
        }
    CleanupStack::Pop();
    iFindResults = NULL;
    
    /**end */
    return iErr;

    }

// -----------------------------------------------------------------------------
// CContactsUT::OrganiseAddL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::OrganiseAddL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In OrganiseAdd" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    
    iErr = KErrNone;
    
    /** Add 1 group */
        
    _LIT(KGroup,"OrganiseTest1");
   	iGroup = iStore->CreateNewContactGroupLC();
	iGroup->SetGroupLabelL(KGroup);
	iOperation = EGroup;
	iGroup->CommitL(*this);
	
	CActiveScheduler::Start();
	CleanupStack::Pop();
	/** ends */
	
	
    if(iErr)
        {
        return iErr;
        }
        
    /** Retrieve the group id */
    HBufC8* groupId = NULL;
    iFindResults = iStore->ContactGroupsLC();    
    TInt count(iFindResults->Count());
    iErr = KErrGeneral;    
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        iOp = iContactManager->RetrieveContactL(*iResult,*this);
        CActiveScheduler::Start();
        
        iGroup = iStoreContact->Group();
        if(!iGroup->GroupLabel().Compare(KGroup))
            {
            groupId =iResult->PackLC();
            CleanupStack::Pop();//groupId
            break;           
            }             
        }
    CleanupStack::Pop();//iFindResults
    CleanupStack::PushL(groupId);
    iFindResults = NULL;
    /** ends */
    
    
    /** Add 2 contacts */
    
    DeleteAllL();
    _LIT(KFirstName,"Tenali");
    _LIT(KSecondName,"Birbal"); 
    
    TPtrC ptr1(KFirstName);
    TPtrC ptr2(KSecondName);
    
    AddOneContactL(ptr1);
    AddOneContactL(ptr2);   
    
    
        
    /** Retrieve the 2 contacts */    
    
    // Phone number to be searched for
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhoneNumber, KPhoneNumber().Length(), *this );
    
    CActiveScheduler::Start();    
    count = iFindResults->Count();
    /**end*/
    
    /**Organise using SAPI core class*/    
    if(count>1 && groupId)
        {        
        RPointerArray<TDesC8> idArray;
        CleanupClosePushL(idArray);
        TInt num(count);
        while(count)
            {
            HBufC8* contactId = (const_cast<MVPbkContactLink&>(iFindResults->At(--count))).PackLC();
            idArray.AppendL(contactId);  
            }
        __UHEAP_MARK;
        CContactService* serviceHandle = CContactService::NewL();
        CleanupStack::PushL(serviceHandle);
        iLog->Log( KServiceOpen );
        
        serviceHandle->OrganiseGroupsL(this,0,*groupId,idArray,ETrue);
        iLog->Log(_L("OrganiseGroupsL called\n"));
        iLog->Log(_L("Start Active Scheduler\n"));
        CActiveScheduler::Start();
        
       
        CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle 
        __UHEAP_MARKEND;
        CleanupStack::PopAndDestroy(num);//destroy all contactIds
        CleanupStack::PopAndDestroy(&idArray);//singleContactField	
          
        iLog->Log( KServiceClose );        
        }    
    /** ends */
    
    
    /** Check for the group and delete*/
    iFindResults = iStore->ContactGroupsLC();    
    count = iFindResults->Count();
    iErr = KErrGeneral;    
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        if(!(iResult->PackLC())->Compare(*groupId))
            {
            iOp = iContactManager->RetrieveContactL(*iResult,*this);
            CActiveScheduler::Start();
                
            iGroup = iStoreContact->Group();
            MVPbkContactLinkArray* linkArray = iGroup->ItemsContainedLC();
            if(linkArray->Count() == 2 )
                {
                iErr = KErrNone;
                }
            CleanupStack::Pop();//linkArray
            
            iContactToDelete = CVPbkContactLinkArray::NewL();
            iContactToDelete->AppendL(iResult);
            iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
            CActiveScheduler::Start();              
            }
        CleanupStack::PopAndDestroy();       
        }
    CleanupStack::Pop();
    iFindResults = NULL;
    /**end */
    CleanupStack::PopAndDestroy(groupId);  
    
    return iErr;
    }


// -----------------------------------------------------------------------------
// CContactsUT::OrganiseDeleteL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::OrganiseDeleteL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In OrganiseDelete" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    iErr = KErrNone;
    
    /** Add 1 group */
        
    _LIT(KGroup,"OrganiseTest1");
   	iGroup = iStore->CreateNewContactGroupLC();
	iGroup->SetGroupLabelL(KGroup);
	iOperation = EGroup;
	iGroup->CommitL(*this);
	
	CActiveScheduler::Start();
	CleanupStack::Pop();
	/** ends */
	
	
    if(iErr)
        {
        return iErr;
        }        
    
    
    /** Add 2 contacts */
    
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KFirstName,"Tenali"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KFirstNumber,"97531"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact

    
    // Create second contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KSecondName,"Birbal"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KSecondNumber,"97531"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KSecondNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact
    
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    /** end */
    
    
    if(iErr)
        {
        return iErr;
        }
    
    /** Retrieve the 2 contacts */    
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);
    // Phone number to be searched for
    _LIT( KMatchNo, "97531" );
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KMatchNo, KMatchNo().Length(), *this );
    
    CActiveScheduler::Start();    
    TInt count = iFindResults->Count();
    TInt num(count);
    iContactToDelete = CVPbkContactLinkArray::NewL();
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        iContactToDelete->AppendL(iResult);
        idArray.AppendL(iResult->PackLC());
        }
    /** ends */    
    
    /** Retrieve the group id */
    HBufC8* groupId = NULL;
    iFindResults = iStore->ContactGroupsLC();    
    count = iFindResults->Count();
    iErr = KErrGeneral;    
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        iOp = iContactManager->RetrieveContactL(*iResult,*this);
        CActiveScheduler::Start();
        
        iGroup = iStoreContact->Group();
        if(!iGroup->GroupLabel().Compare(KGroup))
            {
            groupId =iResult->PackLC();
            TInt count(iContactToDelete->Count());
            while(count)
                {
                iGroup->AddContactL(iContactToDelete->At(--count));
                }
            CleanupStack::Pop();
            break;           
            }             
        }
    CleanupStack::Pop();
    CleanupStack::PushL(groupId);    
    iFindResults = NULL;
    delete iContactToDelete;
    iContactToDelete = NULL;
    /** ends */        
    
    /**Organise using SAPI core class*/    
    if(groupId)
        {        
        __UHEAP_MARK;
        CContactService* serviceHandle = CContactService::NewL();
        CleanupStack::PushL(serviceHandle);
        iLog->Log( KServiceOpen );
        
        serviceHandle->OrganiseGroupsL(this,0,*groupId,idArray,EFalse);
        iLog->Log(_L("OrganiseGroupsL called\n"));
        iLog->Log(_L("Start Active Scheduler\n"));
        CActiveScheduler::Start();
        
       
        CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle        
          
        iLog->Log( KServiceClose );   
        __UHEAP_MARKEND;     
        }    
    /** ends */
    
    
    /** Check for the group */
    iFindResults = iStore->ContactGroupsLC();    
    count = iFindResults->Count();
    iErr = KErrGeneral;    
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        if(!(iResult->PackLC())->Compare(*groupId))
            {
            iContactToDelete = CVPbkContactLinkArray::NewL();
            iContactToDelete->AppendL(iResult);
            iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
            CActiveScheduler::Start();  
            }
        CleanupStack::PopAndDestroy();
        }        
    CleanupStack::Pop(); //iFindResults
    iFindResults = NULL;
    /**end */
    CleanupStack::PopAndDestroy(groupId);
    CleanupStack::PopAndDestroy(num);//destroy all contactIds
    CleanupStack::PopAndDestroy(&idArray);//singleContactField	
    
    return iErr;
    }

// -----------------------------------------------------------------------------
// CContactsUT::OrganiseDeleteL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::ImportL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In Import" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    iErr = KErrNone;
    _LIT(KFileName,"c:\\vcardex.vcf");
    
    /** Add 1 contact */    
    CVPbkFieldTypeRefsList* fieldTypeRefList = CVPbkFieldTypeRefsList::NewL();
    CleanupStack::PushL(fieldTypeRefList);
    
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_FIRSTNAME ) );
    fieldTypeRefList->AppendL( 
        *iContactManager->FieldTypes().Find( R_VPBK_FIELD_TYPE_MOBILEPHONEGEN ) );
    
    // Create first contact
    iStoreContact = iStore->CreateNewContactLC();
    
    // Create contact field for contact
    MVPbkStoreContactField* field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 0 ) );
    // Set contact field data
    _LIT(KFirstName,"Tenali"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstName );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Create contact field for contact
    field = iStoreContact->CreateFieldLC( fieldTypeRefList->FieldTypeAt( 1 ) );
    // Set contact field data
    _LIT(KFirstNumber,"45678"); 
    (MVPbkContactFieldTextData::Cast(field->FieldData())).SetTextL( KFirstNumber );
    // Add the contact field to contact
    iStoreContact->AddFieldL( field );
    CleanupStack::Pop(); // field
    
    // Commit the new created contact to contact store
    iStoreContact->CommitL( *this );
    CActiveScheduler::Start();	
    CleanupStack::Pop(); // iStoreContact

    CleanupStack::PopAndDestroy(fieldTypeRefList);
    /** end */
    
     /** Retrieve the contact */    
    
    // Phone number to be searched for
    _LIT( KMatchNo, "45678" );
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KMatchNo, KMatchNo().Length(), *this );
    
    CActiveScheduler::Start();    
    TInt count = iFindResults->Count();
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        iVCardEngine = CVPbkVCardEng::NewL( *iContactManager );
        
        // Create the buffer to store the contact
        iBuffer = HBufC8::NewL( 1024 );
        TPtr8 bufferPtr( iBuffer->Des() );
        iDestStream.Open( bufferPtr );
        
        iOperation = EVCard;
        
        //export the contact from MVPbkContactLink
        iOp = iVCardEngine->ExportVCardL( iDestStream, *iResult, *this );
        CActiveScheduler::Start();
        
        delete iVCardEngine;
        iVCardEngine = NULL;   
        
        if(iBuffer)
            {
            RFile file;
            CleanupClosePushL(file);            
            file.Replace(iRfs,KFileName,EFileWrite);
            file.Write(0,*iBuffer);
            CleanupStack::PopAndDestroy(&file);
            delete iBuffer;
            iBuffer = NULL;
            }
            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(iResult);
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();        
        }
    iFindResults = NULL;
    __UHEAP_MARK;
    //using sapi
    CContactService* serviceHandle = CContactService::NewL();
    CleanupStack::PushL(serviceHandle);
    iLog->Log( KServiceOpen );
    
    TFileName file(KFileName);
    
    serviceHandle->ImportVCardToStoreL(this,0,file);
    iLog->Log(_L("ImportVCardToStoreL called\n"));
    iLog->Log(_L("Start Active Scheduler\n"));
    CActiveScheduler::Start();  
    
    CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle        
    iLog->Log( KServiceClose );   
    __UHEAP_MARKEND;
     /**Delete using virtual Phonebook */ 
    
   
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KMatchNo, KMatchNo().Length(), *this );    
    CActiveScheduler::Start();
    iErr = KErrGeneral;
    count = iFindResults->Count();
    while(count)
        {            
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(&(const_cast<MVPbkContactLink&>(iFindResults->At(--count))));
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start();
        }       
    /**end  */   
    
    return iErr;
    }
// -----------------------------------------------------------------------------
// CContactsUT::OrganiseDeleteL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::ExportL( CStifItemParser& aItem )
    {
    
    // Print to UI
    _LIT( KContactsTest, "ContactsTest" );
    _LIT( KExample, "In Import" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KContactsTest, 
                                KParam, i, &string );
        i++;
        }
    iErr = KErrNone;
    _LIT(KFileName,"c:\\vcardim.vcf");
    RFs fs;
	CleanupClosePushL(fs);
	User::LeaveIfError(fs.Connect());
	RFile file;
	if(!file.Open(fs,KFileName,EFileRead))
	    {
	    file.Close();
		fs.Delete(KFileName);
	    }
	CleanupStack::PopAndDestroy(&fs);
	
	DeleteAllL();
	_LIT(KFirstName,"Akbar"); 
	TPtrC ptr(KFirstName);
	AddOneContactL(ptr);
	
    /** Retrieve the contact */    
    
    // Phone number to be searched for
    // Create find operation
    iOp = iContactManager->MatchPhoneNumberL(
        KPhoneNumber, KPhoneNumber().Length(), *this );
    
    CActiveScheduler::Start();    
    TInt count = iFindResults->Count();
    while(count)
        {
        iResult = &(const_cast<MVPbkContactLink&>(iFindResults->At(--count)));
        iBuffer = iResult->PackLC();
        CleanupStack::Pop();
        
      //  __UHEAP_MARK;
        //using sapi
        CContactService* serviceHandle = CContactService::NewL();
        CleanupStack::PushL(serviceHandle);
        iLog->Log( KServiceOpen );
        
        TFileName file(KFileName);
        serviceHandle->ExportVCardL(this,0,file,*iBuffer);
        iLog->Log(_L("ExportVCardL called\n"));
        iLog->Log(_L("Start Active Scheduler\n"));
        CActiveScheduler::Start();  
        
        CleanupStack::PopAndDestroy(serviceHandle);//serviceHandle        
        iLog->Log( KServiceClose );          
      //   __UHEAP_MARKEND;
         
        iContactToDelete = CVPbkContactLinkArray::NewL();
        iContactToDelete->AppendL(iResult);
        iOp = iContactManager->DeleteContactsL( *iContactToDelete, *this );
        CActiveScheduler::Start(); 
        
        delete iBuffer;
        iBuffer = NULL;   
                
        RPointerArray< MVPbkStoreContact > importedContacts;
        CleanupClosePushL(importedContacts);

        iVCardEngine = CVPbkVCardEng::NewL( *iContactManager );
        
        // Open the RFileReadStream that holds the vCard content
        iErr = iSource.Open( iRfs, KFileName, EFileRead );

        // Import the contact from RFileReadStream asynchronously
        // The operation status is reported via MVPbkSingleContactOperationObserver.
        iOp = iVCardEngine->ImportVCardL( importedContacts, *iStore, iSource, *this );
        CActiveScheduler::Start();
        
        if(!importedContacts.Count())
            {
            return KErrGeneral;
            
            }
       
        // Close iImportedContacts
        //
        importedContacts.ResetAndDestroy();
        CleanupStack::PopAndDestroy(&importedContacts);   
        }
    iFindResults = NULL;
    
       
    return iErr;
    }

  
TInt CContactsUT::GetListCancelL( CStifItemParser& /*aItem*/)
	{

	int ret=0;
	ret = getlist_cancel(0, NULL);

	if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;
	}
	
  
TInt CContactsUT::GetListSrchCancelL( CStifItemParser& /*aItem*/)
	{

	int ret=0;
	ret = getlistsrh_cancel(0, NULL);

	if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;
	}
    
    
    
TInt CContactsUT::ExportCancelL( CStifItemParser& /*aItem*/)
	{

	int ret=0;
	ret = export_cancel(0, NULL);

	if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;

		
	}

TInt CContactsUT::AddCancelL( CStifItemParser& /*aItem*/ )
	{
	int ret=0;
	ret = add_cancel(0, NULL);

	if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;
	}

TInt CContactsUT::ImportCancelL( CStifItemParser& /*aItem*/)
	{

	int ret=0;
	ret = import_cancel(0, NULL);

	if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;

		
	}

TInt CContactsUT::DeleteCancelL( CStifItemParser& /*aItem*/)
	{

	int ret=0;
	ret = delete_cancel(0, NULL);

	if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;

	}
TInt CContactsUT::OrganiseCancelL( CStifItemParser& /*aItem*/)
	{

	int ret=0;
	ret = organise_cancel(0, NULL);

	if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;

	}
//End of file
