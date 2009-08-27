/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
#include <LiwServiceHandler.h>
#include <LiwCommon.h>
#include <VPbkEng.rsg>


#include <MVPbkContactFieldTextData.h>
#include <MVPbkContactStoreList.h>
#include <MVPbkContactOperationBase.h>
#include <MVPbkContactLink.h>
#include <CVPbkContactLinkArray.h>
#include <MVPbkContactGroup.h>
#include <CVPbkContactManager.h>
#include <MVPbkContactStoreList.h>
#include <MVPbkContactStore.h>
#include <TVPbkContactStoreUriPtr.h>
#include <CVPbkFieldTypeRefsList.h>
#include <MVPbkContactFieldTextData.h>
#include<f32file.h>


#include "Tcomplugin.h"
_LIT(LogFileName , "C:\\Notifications.txt") ;

_LIT(KError,"Error code is");
_LIT(KSuccess,"Successful");
_LIT(KNewLine,"\n");
_LIT(KServiceOpen,"Service handle created");
_LIT(KServiceClose,"Service handle deleted");
_LIT(KPhoneNumber,"9886431364");
 _LIT(KGroup1,"Test1");




_LIT8( KIDataSource,"IDataSource" );
_LIT8( KExitCode, "ErrorCode" );
_LIT8( KService, "Service.Contact" );

//commands that can be performed on the contacts database.
_LIT8( KCmdImport, "Import" );
_LIT8( KCmdExport, "Export" );
_LIT8( KCmdGetList, "GetList");
_LIT8( KCmdAdd, "Add" );
_LIT8( KCmdDelete, "Delete" );
_LIT8( KCmdOrganiseGroups, "Organise" );

// Constant for the appending Error code
_LIT8( KErrorCode, "ErrorCode" );

// Constant for the appending TransactionID
_LIT8( KTransactionID, "TransactionID" );

//Constant for appending Iterator
_LIT8( KReturnValue, "ReturnValue");

_LIT8(KSourceFileNameParam, "SourceFile");
_LIT8(KDestFileNameParam, "DestinationFile");
_LIT8(KGroupId,"id");


_LIT8(KFieldLabel, "Label");
_LIT8(KFieldValue, "Value");
_LIT8(KFieldNext, "Next");
_LIT8(KGroupLabel, "GroupLabel");
_LIT8(KContents, "Contents");

_LIT8(KList, "IdList");
_LIT8(KContact, "Contact");
_LIT8(KGroup, "Group");
_LIT8(KDatabase, "Database");

_LIT8(KDBUri, "DBUri");
_LIT8(KSearchVal, "SearchVal");
_LIT8(KContactId, "id");
_LIT8(KType, "Type");
_LIT8(KFilter, "Filter");
_LIT8(KSort, "Sort");
_LIT8(KOrder, "Order");
_LIT8(KData, "Data");
_LIT8(KOperationType, "OperationType");

_LIT(KAssociate, "Associate");
_LIT(KDissociate, "Disassociate");

_LIT(KAscending, "Ascending");
_LIT(KDescending, "Descending");

//Field Keys
_LIT8(KSync, "Sync");
_LIT8(KLastName, "LastName");
_LIT8(KLastNameReading, "LastNameReading");
_LIT8(KFirstName, "FirstName");
_LIT8(KFirstNameReading, "FirstNameReading");
_LIT8(KPrefix, "Prefix");
_LIT8(KSuffix, "Suffix");
_LIT8(KSecondName, "SecondName");
_LIT8(KLandPhoneHome, "LandPhoneHome");
_LIT8(KMobilePhoneHome, "MobilePhoneHome");
_LIT8(KVideoNumberHome, "VideoNumberHome");
_LIT8(KFaxNumberHome, "FaxNumberHome");
_LIT8(KVoipHome, "VoipHome");
_LIT8(KEmailHome, "EmailHome");
_LIT8(KURLHome, "URLHome");
_LIT8(KAddrLabelHome, "AddrLabelHome");
_LIT8(KAddrPOHome, "AddrPOHome");
_LIT8(KAddrEXTHome, "AddrEXTHome");
_LIT8(KAddrStreetHome, "AddrStreetHome");
_LIT8(KAddrLocalHome, "AddrLocalHome");
_LIT8(KAddrRegionHome, "AddrRegionHome");
_LIT8(KAddrPostCodeHome, "AddrPostCodeHome");
_LIT8(KAddrCountryHome, "AddrCountryHome");
_LIT8(KJobTitle, "JobTitle");
_LIT8(KCompanyName,"CompanyName");
_LIT8(KLandPhoneWork, "LandPhoneWork");
_LIT8(KMobilePhoneWork, "MobilePhoneWork");
_LIT8(KVideoNumberWork, "VideoNumberWork");
_LIT8(KFaxNumberWork, "FaxNumberWork");
_LIT8(KVoipWork, "VoipWork");
_LIT8(KEmailWork, "EmailWork");
_LIT8(KURLWork, "URLWork");
_LIT8(KAddrLabelWork, "AddrLabelWork");
_LIT8(KAddrPOWork, "AddrPOWork");
_LIT8(KAddrEXTWork, "AddrEXTWork");
_LIT8(KAddrStreetWork, "AddrStreetWork");
_LIT8(KAddrLocalWork, "AddrLocalWork");
_LIT8(KAddrRegionWork, "AddrRegionWork");
_LIT8(KAddrPostCodeWork, "AddrPostCodeWork");
_LIT8(KAddrCountryWork, "AddrCountryWork");
_LIT8(KLandPhoneGen, "LandPhoneGen");
_LIT8(KMobilePhoneGen, "MobilePhoneGen");
_LIT8(KVideoNumberGen, "VideoNumberGen");
_LIT8(KFaxNumberGen, "FaxNumberGen");
_LIT8(KVOIPGen, "VOIPGen");
_LIT8(KPOC, "POC");
_LIT8(KSWIS, "SWIS");
_LIT8(KSIP, "SIP");
_LIT8(KEmailGen, "EmailGen");
_LIT8(KURLGen, "URLGen");
_LIT8(KAddrLabelGen, "AddrLabelGen");
_LIT8(KAddrPOGen, "AddrPOGen");
_LIT8(KAddrExtGen, "AddrExtGen");
_LIT8(KAddrStreetGen, "AddrStreetGen");
_LIT8(KAddrLocalGen, "AddrLocalGen");
_LIT8(KAddrRegionGen, "AddrRegionGen");
_LIT8(KAddrPostCodeGen, "AddrPostCodeGen");
_LIT8(KAddrCountryGen, "AddrCountryGen");
_LIT8(KPageNumber, "PageNumber");
_LIT8(KDTMFString, "DTMFString");
_LIT8(KWVAddress, "WVAddress");
_LIT8(KDate, "Date");
_LIT8(KNote, "Note");
_LIT8(KThumbNailPic, "ThumbNailPic");
_LIT8(KRingtone, "Ringtone");
_LIT8(KCallerObjImg, "CallerObjImg");
_LIT8(KCallerObjText, "CallerObjText");
_LIT8(KMiddleName, "MiddleName");
_LIT8(KDepartment, "Department");
_LIT8(KAsstName, "AsstName");
_LIT8(KSpouse, "Spouse");
_LIT8(KChildren, "Children");
_LIT8(KAsstPhone, "AsstPhone");
_LIT8(KCarPhone, "CarPhone");
_LIT8(KAnniversary, "Anniversary");
_LIT8(KSyncClass, "SyncClass");
_LIT8(KLOCPrivacy, "LOCPrivacy");
_LIT8(KGenLabel, "GenLabel");
_LIT8(KXSPID, "IMPP");

//----------------------------------------------------------------------------
// CTestProvider :: Delete()
//----------------------------------------------------------------------------
void CTestProvider::Delete()
    {
    iIface->Close();
    iFSession.Close();
    iCriteriaArray.Close();
    delete iServiceHandler;
    delete iInparams;
    delete iOutparams;
    delete iCriteria;
    delete inList;
    delete outList;
    iIdArrayList.ResetAndDestroy();
    }

// -----------------------------------------------------------------------------
// CTestProvider::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTestProvider::RunMethodL(
    CStifItemParser& aItem )
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.

        ENTRY("GetContactALL" , CTestProvider :: GetContactALL),
        ENTRY("GetContactSearch" , CTestProvider :: GetContactSearch),
        ENTRY("GetGroup" , CTestProvider :: GetGroup),
        ENTRY("GetDatabase" , CTestProvider :: GetDatabase),
        ENTRY("AddContact" , CTestProvider :: AddContact),
        ENTRY("DeleteContact" , CTestProvider :: DeleteContact),
        ENTRY("AddGroup" , CTestProvider :: AddGroup),
       	ENTRY("OrganiseAdd" , CTestProvider :: OrganiseAdd),
       	ENTRY("OrganiseDelete" , CTestProvider:: OrganiseDelete),
       //	ENTRY("ModifyContact" , CTestProvider:: ModifyContact),
       	//ENTRY("ModifyGroup" , CTestProvider:: ModifyGroup),
       	ENTRY("ExportVCard" , CTestProvider :: ExportVCard),
       	ENTRY("ImportVCard" , CTestProvider :: ImportVCard),
       	ENTRY("GetListNewFieldsTestSync" , CTestProvider :: GetListNewFieldsTestSync),
       	ENTRY("AddContactNewFieldsSynTest" , CTestProvider :: AddContactNewFieldsSynTest),
       	ENTRY("AddGroupSynTest" , CTestProvider :: AddGroupSynTest),
       	
       	

        };

    const TInt count = sizeof( KFunctions ) /
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt CTestProvider :: HandleNotifyL(
                	        	TInt aCmdId,
                	            TInt aEventId,
                	            CLiwGenericParamList& aEventParamList,
                	            const CLiwGenericParamList& aInParamList)
    {
    CActiveScheduler::Stop();
    // __UHEAP_MARK;
    TInt countheap3 =User::CountAllocCells();
	TInt pos = 0;
	//TBool tResult, bResult;
    const TLiwGenericParam* param = aEventParamList.FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
	err.Reset();

    TBool tResult = EFalse;
    TBool bResult = EFalse;
    TBuf<255> firstName;
    TLiwVariant cntId;
    TLiwVariant mapfield;
    TLiwVariant firstname;
    TLiwVariant entry;
    const CLiwMap* map = NULL;
    const CLiwMap* mapField = NULL;

    param = aEventParamList.FindFirst(pos, KReturnValue);
    TLiwVariant iterator = param->Value();
    CLiwIterable* iter = iterator.AsIterable();

    while(iter->NextL(entry))
    {

    map = entry.AsMap();
    TInt count1 = map->Count();
    map->FindL(KContactId, cntId);
    TPtrC ptr = cntId.AsDes();
/*	if(iCase == EOrganizeAddcntid)
		{
		iCntID.Set(ptr);
		}
*/
    if(map->FindL(KFirstName,mapfield))
    mapField = mapfield.AsMap();

    TInt count = mapField->Count();

    mapField->FindL(KFieldValue,firstname);
    firstName = firstname.AsDes();

    if(firstName.CompareF(_L("Arnold")) == 0)
        {
        tResult = ETrue;
        }
    if(firstName.CompareF(_L("Johnny")) == 0)
	    {
	    bResult = ETrue;
	    }

    firstname.Reset();
    mapfield.Reset();
    entry.Reset();
    cntId.Reset();
    }

	 
	iterator.Reset();
  inList->Reset();
    outList->Reset();
  	TInt countheap4 =User::CountAllocCells();
//	__UHEAP_MARKEND;
    }




void CTestProvider::LoadService()
    {
    TInt pos = 0;

    inList = CLiwGenericParamList::NewL();
    outList = CLiwGenericParamList::NewL();

    iServiceHandler = CLiwServiceHandler::NewL();

    iInparams = &(iServiceHandler->InParamListL());
    iOutparams = &(iServiceHandler->OutParamListL());

    iCriteria = CLiwCriteriaItem::NewL( 1, KIDataSource, KService );
    iCriteria->SetServiceClass(TUid::Uid( KLiwClassBase ));

    iCriteriaArray.AppendL( iCriteria );
    iServiceHandler->AttachL( iCriteriaArray );

    iServiceHandler->ExecuteServiceCmdL( *iCriteria, *iInparams, *iOutparams );

    iOutparams->FindFirst( pos, KIDataSource );
    if(pos != KErrNotFound)
        {
        //LogMessage(_L8("Service Loaded\n"));
        iIface = ( *iOutparams )[pos].Value().AsInterface();
        }
    else
        {
        //LogMessage(_L8("Service Not found\n"));
        }
    if( iInparams )
       {
       iInparams->Reset();
       iInparams = NULL;
       }
    if( iOutparams )
       {
       iOutparams->Reset();
       iOutparams = NULL;   }
    if( iCriteria )
       {
        delete iCriteria;
        iCriteria = NULL;
       }
    }



void CTestProvider::HandleError( const TInt& aError,TInt /*aTransId*/ )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In Handle Error\n");
    iLog->Log(KFunc);
    iErr = aError;
    TBuf<5> buf;
    buf.Num(aError);
    iLog->Log(KError);
    iLog->Log(buf);
    iLog->Log(KNewLine);
    }

void CTestProvider::HandleRetrieveContact( MVPbkStoreContact* /*aStoreContact*/, TInt /*aTransId*/ )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In Handle Retrieve Contact\n");
    iLog->Log(KFunc);
    }

void CTestProvider::ContactOperationCompleted(TContactOpResult aResult)
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In ContactOperationCompleted \n");
    iLog->Log(KFunc);
    TBuf<5> buf;
    buf.Num(aResult.iOpCode);
    iLog->Log(KSuccess);
    iLog->Log(buf);
    iLog->Log(KNewLine);
    }

void CTestProvider::ContactOperationFailed
            (TContactOp /*aOpCode*/, TInt aErrorCode, TBool /*aErrorNotified*/)
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In ContactOperationFailed \n");
    iLog->Log(KFunc);
    TBuf<5> buf;
    buf.Num(aErrorCode);
    iLog->Log(KError);
    iLog->Log(buf);
    iLog->Log(KNewLine);
    }

void CTestProvider::FindCompleteL( MVPbkContactLinkArray* aResults )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In FindCompleteL \n");
    iLog->Log(KFunc);
//    iFindResults = aResults;
    delete iFindResults;
    iFindResults = aResults;
    iLog->Log(KSuccess);
    }
void CTestProvider::FindFailed( TInt aError )
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

void CTestProvider::VPbkSingleContactOperationComplete(
                MVPbkContactOperationBase& aOperation,
                MVPbkStoreContact* aContact )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In VPbkSingleContactOperationComplete \n");
    iLog->Log(KFunc);
    iLog->Log(KSuccess);
    }


void CTestProvider::VPbkSingleContactOperationFailed(
                MVPbkContactOperationBase& aOperation,
                TInt aError )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In VPbkSingleContactOperationFailed \n");
    iLog->Log(KFunc);
    TBuf<5> buf;
    buf.Num(aError);
    iLog->Log(KError);
    iLog->Log(buf);
    iLog->Log(KNewLine);
    }

void CTestProvider::StepComplete(
                MVPbkContactOperationBase& /*aOperation*/,
                TInt /*aStepSize*/ )
    {
    _LIT(KFunc,"In StepComplete \n");
    iLog->Log(KFunc);
    iLog->Log(KSuccess);
    iLog->Log(KNewLine);
    }

TBool CTestProvider::StepFailed(
                MVPbkContactOperationBase& /*aOperation*/,
                TInt /*aStepSize*/, TInt /*aError*/ )
    {
    _LIT(KFunc,"In StepFailed \n");
    iLog->Log(KFunc);
    return EFalse;
    }

void CTestProvider::OperationComplete(
                MVPbkContactOperationBase& /*aOperation*/ )
    {
    CActiveScheduler::Stop();
    _LIT(KFunc,"In OperationComplete \n");
    iLog->Log(KFunc);
    iErr = KErrNone;
    iLog->Log(KSuccess);
    iLog->Log(KNewLine);
    }


void CTestProvider::AddOneContactL(const TDesC& aName)
  	{
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In AddOneContactL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

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
    CleanupStack::PopAndDestroy(fieldTypeRefList);
    __UHEAP_MARKEND;

    }

void CTestProvider::AddOneGroupL(const TDesC& aName)
	{
	// Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In AddOneGroupL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

//	__UHEAP_MARK;
	iGroup = iStore->CreateNewContactGroupLC();
	iGroup->SetGroupLabelL(aName);
	iGroup->CommitL(*this);
	CActiveScheduler::Start();
	CleanupStack::Pop();
	delete iGroup;
	iGroup = NULL;
//	__UHEAP_MARKEND;
	}

void CTestProvider::DeleteAllContactsL()
	{
    // Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In DeleteAllContactsL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

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

void  CTestProvider::DeleteAllGroupsL()
	{
	// Print to UI
    _LIT( KContactsTest, "ContactsUT" );
    _LIT( KExample, "In DeleteAllGroupsL" );
    TestModuleIf().Printf( 0, KContactsTest, KExample );
    // Print to log file
    iLog->Log( KExample );

//	__UHEAP_MARK;
	iFindResults = iStore->ContactGroupsLC();
	CleanupStack::Pop(); //iFindResults
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
    CleanupStack::PopAndDestroy(iContactToDelete);//iContactToDelete
    iContactToDelete = NULL;



 //   __UHEAP_MARKEND;
	}

TInt CTestProvider::GetListContactL()
	{
	__UHEAP_MARK;
	iOp = iContactManager->MatchPhoneNumberL(
	        KPhoneNumber, KPhoneNumber().Length(), *this );
    CActiveScheduler::Start();
    delete iOp;
    iOp = NULL;

	TInt count(iFindResults->Count());
	delete iFindResults;
    iFindResults = NULL;
    __UHEAP_MARKEND;
    return count;

	}

TInt CTestProvider::GetListGroupL()
	{
//	__UHEAP_MARK;
	iFindResults = iStore->ContactGroupsLC();
    TInt count(iFindResults->Count());
    CleanupStack::Pop(); //iFindResults
    delete iFindResults;
    iFindResults = NULL;
 //   __UHEAP_MARKEND;
    return count;
	}




TInt CTestProvider :: GetContactALL(CStifItemParser& /*aItem */)
    {

    TBuf<20> name1(_L("Arnold"));
    TBuf<20> name2(_L("Johnny"));

    AddOneContactL(name1);
    AddOneContactL(name2);



    ires = KErrGeneral;

    TInt countheap1 =User::CountAllocCells();
    if(iCase != EOrganizeAddcntid && iCase != EDeleteContact && iCase != EVerifyImport)
        {
        LoadService();
        iCase = EGetAllContacts;
        }
    TInt pos = 0;

    //const TLiwGenericParam paramGetListSortOrder;

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContentType );

    TInt countheap2 =User::CountAllocCells();

    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList,0, NULL);


	    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();

    TBool tResult = EFalse;
    TBool bResult = EFalse;
    TBuf<255> firstName;
    TLiwVariant cntId;
    TLiwVariant mapfield;
    TLiwVariant firstname;
    TLiwVariant entry;
    const CLiwMap* map = NULL;
    const CLiwMap* mapField = NULL;

    param = outList->FindFirst(pos, KReturnValue);
    TLiwVariant iterator = param->Value();
    CLiwIterable* iter = iterator.AsIterable();

    while(iter->NextL(entry))
    {

    map = entry.AsMap();
    TInt count1 = map->Count();
    map->FindL(KContactId, cntId);
    TPtrC ptr = cntId.AsDes();

	if(iCase == EOrganizeAddcntid)
		{

		iCntID.Set(ptr);
		break;
		}

    if(map->FindL(KFirstName,mapfield))
    mapField = mapfield.AsMap();

    TInt count = mapField->Count();
    firstname.Reset();
    mapField->FindL(KFieldValue,firstname);
    firstName = firstname.AsDes();

    if(firstName.CompareF(_L("Arnold")) == 0)
        {
        tResult = ETrue;
        }
    if(firstName.CompareF(_L("Johnny")) == 0)
	    {
	    bResult = ETrue;
	    }
    entry.Reset();
    }

	 
    inList->Reset();
    outList->Reset();

	if(tResult && bResult)
		{
		return SErrNone;

		}
	else
		return SErrGeneralError;

    }


TInt CTestProvider :: GetContactSearch(CStifItemParser& /*aItem */)
    {

    //__UHEAP_MARK;

    TBuf<20> name1(_L("Johnny"));

    AddOneContactL(name1);


    LoadService();
    TInt pos = 0;
    iCase = EGetContactSearch;

    //const TLiwGenericParam paramGetListSortOrder;

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContentType );

    CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();
    CleanupStack::PushL(map);
    map->InsertL(KSearchVal,_L("J"));

    const TLiwGenericParam paramData(KFilter, TLiwVariant(map));
    inList ->AppendL( paramData );

    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, 0/*KLiwOptASyncronous*/,NULL /*this*/);
    CleanupStack::Pop(map) ;
    map->DecRef();

    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();


    TBuf<255> firstName;
    TLiwVariant cntId;
    TLiwVariant mapfield;
    TLiwVariant firstname;
    TLiwVariant entry;
    const CLiwMap* map1 = NULL;
    const CLiwMap* mapField = NULL;
    TBool tResult = EFalse;
    param = outList->FindFirst(pos, KReturnValue);
    TLiwVariant iterator = param->Value();
    CLiwIterable* iter = iterator.AsIterable();

    while(iter->NextL(entry))
	    {
	    map1 = entry.AsMap();
	    TInt count1 = map1->Count();
	    map1->FindL(KContactId, cntId);
	    TPtrC8 ptr = cntId.AsData();

	    if(map1->FindL(KFirstName,mapfield))
	    mapField = mapfield.AsMap();

	    TInt count = mapField->Count();
	    firstname.Reset();
	    mapField->FindL(KFieldValue,firstname);
	    firstName = firstname.AsDes();

	    if(firstName.CompareF(_L("Johnny")) == 0)
	        {
	        tResult = ETrue;
	        }

	    }	
    inList->Reset();
    outList->Reset();

    //__UHEAP_MARKEND;
 	if(tResult)
 		return SErrNone;
 	else
 		return SErrGeneralError;


    }


TInt CTestProvider :: AddContact(CStifItemParser& /*aItem */)
    {
  //  __UHEAP_MARK;

    iCase = EAddContact;

    LoadService();

    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
    CleanupStack::PushL(pMap);

    CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();
    CleanupStack::PushL(fieldMap);

    TInt pos = 0;
    fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));
    fieldMap->InsertL(KFieldValue,TLiwVariant(_L("Arnold")));
    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));

    pMap->InsertL(KContactId, TLiwVariant( _L("")));
    pMap->InsertL(KFirstName, TLiwVariant(fieldMap));

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap)); ;

    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData );

    iIface->ExecuteCmdL(KCmdAdd, *inList, *outList,0 /*KLiwOptASyncronous*/, NULL/*this*/);



	CleanupStack::Pop(fieldMap);
	CleanupStack::Pop(pMap);
	fieldMap->DecRef();
	fieldMap->DecRef();
	pMap->DecRef();

    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    err.Reset();




    inList->Reset();
    outList->Reset();

 //   __UHEAP_MARKEND;
    return code;

    }


TInt CTestProvider :: OrganiseAdd(CStifItemParser& /*aItem */)
    {
   // LoadService();
    //__UHEAP_MARK;
        CStifItemParser* astiff = NULL ;

    //LoadService();
    ires = KErrGeneral;
    iCase = EGetGroup;

    GetGroup(*astiff);

    iCase = EOrganizeAddcntid;

    GetContactALL(*astiff);

    iCase = EOrganizeAdd;


    //LoadService();
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
    CLiwDefaultList* list = CLiwDefaultList::NewL();

    list->AppendL(TLiwVariant(iCntID));

    TInt pos = 0;

    //pMap->InsertL(KDatabaseUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KGroupId, TLiwVariant(iGrpID));
    pMap->InsertL(KList, TLiwVariant(list));

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group")));

    const TLiwGenericParam paramOperationType(KOperationType, TLiwVariant( _L("Associate")));
    const TLiwGenericParam paramOrganizeData(KData, TLiwVariant(pMap));

    inList ->AppendL( paramContentType );
    inList ->AppendL( paramOperationType );
    inList ->AppendL( paramOrganizeData );

    iIface->ExecuteCmdL(KCmdOrganiseGroups, *inList, *outList, 0, NULL);

	list->DecRef();
	list->DecRef();

	pMap->DecRef();



    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();


	ires = code;

    inList->Reset();
    outList->Reset();

  //  __UHEAP_MARKEND;

    return ires;




    }

TInt CTestProvider :: OrganiseDelete(CStifItemParser& /*aItem */)
    {
  //  __UHEAP_MARK;
    LoadService();

	CStifItemParser* astiff = NULL ;

	//LoadService();
	ires = KErrGeneral;
	iCase = EOrganizeDelete;

	GetGroup(*astiff);
	iCase = EOrganizeDelete;



	//LoadService();
	CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
	CLiwDefaultList* list = CLiwDefaultList::NewL();
	if(iIdArrayList.Count()>0)
	iCntID.Set(*iIdArrayList[0]);

	list->AppendL(TLiwVariant(iCntID));

	TInt pos = 0;

	//pMap->InsertL(KDatabaseUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
	pMap->InsertL(KGroupId, TLiwVariant(iGrpID));
	pMap->InsertL(KList, TLiwVariant(list));

	const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group")));

	const TLiwGenericParam paramOperationType(KOperationType, TLiwVariant(KDissociate));
	const TLiwGenericParam paramOrganizeData(KData, TLiwVariant(pMap));

	inList ->AppendL( paramContentType );
	inList ->AppendL( paramOperationType );
	inList ->AppendL( paramOrganizeData );

	iIface->ExecuteCmdL(KCmdOrganiseGroups, *inList, *outList, 0, NULL);

	const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
	TLiwVariant err = param->Value();
	TInt code = err.AsTInt32();


	ires = code;

	inList->Reset();
	outList->Reset();

//	__UHEAP_MARKEND;
	return ires;


    }

//TInt CTestProvider :: ModifyContact(CStifItemParser& /*aItem */)
    /*{
    LoadService();

    }*/
TInt CTestProvider :: GetGroup(CStifItemParser & /*aItem */)
    {
 //   __UHEAP_MARK;



 	/* Adding one group using VPBkphonebook */
 	_LIT(KGroupName,"Test");
 	TBuf<10> grpnm(KGroupName);
 	AddOneGroupL(grpnm);


    ires = KErrGeneral;
    if(iCase != EVerifyGroupAdd && iCase != EOrganizeDelete)
        {
        LoadService();
        iCase = EGetGroup;
        }

    TInt pos = 0;

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group")));
    inList ->AppendL( paramContentType );
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, 0, NULL);



    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
	pos = 0;
	if(iCase == EGetGroup || iCase == EOrganizeDelete )
		{
	    param = outList->FindFirst(pos, KReturnValue);
	    TLiwVariant iterator = param->Value();
	    CLiwIterable* iter = iterator.AsIterable();

	    TLiwVariant entry;
	    while(iter->NextL(entry))
		    {
		    const CLiwMap*    map1 = entry.AsMap();
		    TLiwVariant cntId;
		    map1->FindL(KGroupId, cntId);
		    TLiwVariant groupLabel;
          	map1->FindL(KGroupLabel,groupLabel);
            TBuf<255> groupName;
            groupName = groupLabel.AsDes();
            if(groupName == _L("Test"))
	            {
			    TPtrC ptr = cntId.AsDes();

			    iGrpID.Set(ptr);
			    TLiwVariant contents;
                if(map1->FindL(KContents,contents))
                    {
                    const CLiwList* list =NULL;
                    list = contents.AsList();
                    TInt count = list->Count();
                    for(TInt i=0; i<count ; i++)
        				{
        				TLiwVariant cntId;
        				list->AtL(i, cntId) ;
        				TPtrC  cntid = cntId.AsDes() ;
        				HBufC* cnt = HBufC::NewL(cntid.Length());
        				*cnt = cntid;
        				iIdArrayList.AppendL(cnt);
        				}

                    }
			    break;

	            }

		    }

		}



    ires = code;

    inList->Reset();
    outList->Reset();

 //   __UHEAP_MARKEND;
    return ires;
    }


TInt CTestProvider :: GetDatabase(CStifItemParser& /*aItem*/)
	{
//	__UHEAP_MARK;
	TInt result= SErrGeneralError;
	LoadService();
    TInt pos = 0;
    ires = KErrGeneral;
    iCase = EGetDatabase;

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Database")));
    inList ->AppendL( paramContentType );

    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, 0, NULL);

    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();

    pos = 0;
    TLiwVariant dbname;
    TLiwVariant entry;
    const CLiwMap* map = NULL;

    param = outList->FindFirst(pos, KReturnValue);
    TLiwVariant iterator = param->Value();
    CLiwIterable* iter = iterator.AsIterable();

    while(iter->NextL(entry))
    {
    map = entry.AsMap();

    map->FindL(KDBUri, dbname);
    TPtrC dbNmae = dbname.AsDes();

    if(dbNmae == _L("cntdb://c:contacts.cdb"))
        {
        result = SErrNone;
        entry.Reset();
        break;
        }
   	entry.Reset();
    }

     
    inList->Reset();
    outList->Reset();

  //  __UHEAP_MARKEND;
    return result ;

    }



TInt CTestProvider :: DeleteContact(CStifItemParser& /*aItem*/)
	{
//	__UHEAP_MARK;

    TBuf<20> name1(_L("Johnny"));

    AddOneContactL(name1);




	iCase = EDeleteContact;
	LoadService();
    TInt pos = 0;

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContentType );

    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, 0, NULL);

    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();

	param = outList->FindFirst(pos, KReturnValue);
	TLiwVariant iterator = param->Value();
	CLiwIterable* iter = iterator.AsIterable();

	TLiwVariant entry;
	iter->NextL(entry);

	const CLiwMap* map = entry.AsMap();
	TInt count1 = map->Count();

	TLiwVariant cntId;
	map->FindL(KContactId, cntId);
	TPtrC ptr = cntId.AsDes();


    entry.Reset();
    iterator.Reset();

    inList->Reset();
    outList->Reset();

    const TLiwGenericParam paramContent(KType, TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContent );

    CLiwDefaultList* list = CLiwDefaultList :: NewL();
    CleanupStack::PushL(list);

    list->AppendL(TLiwVariant(ptr));

    CLiwDefaultMap* mapContactId = CLiwDefaultMap::NewL();

    CleanupStack::PushL(mapContactId);

    mapContactId->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    mapContactId->InsertL(KList,TLiwVariant(list));

    const TLiwGenericParam paramDeleteData(KData, TLiwVariant(mapContactId));
    inList ->AppendL( paramDeleteData );

    TRAPD(err1,iIface->ExecuteCmdL(KCmdDelete, *inList, *outList, 0, NULL));


    CleanupStack::Pop(mapContactId);
    mapContactId->DecRef();

    CleanupStack::Pop(list);
    list->DecRef();
    list->DecRef();
    cntId.Reset();

	 pos = 0;
    param = outList->FindFirst( pos, KExitCode );
    err = param->Value();
    code = err.AsTInt32();





    inList->Reset();
    outList->Reset();

   return code;

 //   __UHEAP_MARKEND;
    }

/*
 * This is a manual test case were the service was available when the
 * request was made and then   Lost the service (Contact to location servier lost
 */


TInt CTestProvider :: AddGroup(CStifItemParser& /*aItem*/)
    {
//    __UHEAP_MARK;

    LoadService();
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
    iCase = EAddGroup;
    TInt pos = 0;

    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KGroupId, TLiwVariant(_L8("")));
    pMap->InsertL(KGroupLabel, TLiwVariant(_L("Test")));

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group")));
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap)); ;

    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData );
    iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, 0, NULL);

    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();

    ires = code;
    inList->Reset();
    outList->Reset();

//	__UHEAP_MARKEND;
    return ires;
    }


/**
 * Export VCard
 */

 TInt CTestProvider ::ExportVCard(CStifItemParser& /*aItem*/)
    {
 	//__UHEAP_MARK;
 	LoadService();
	_LIT(KFileName,"C:\\data\\Export.vcf");
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContentType );


 	TRAPD(err,iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, 0, NULL));

 	TInt pos= 0;
	const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
	TLiwVariant errcode = param->Value();
	TInt code = errcode.AsTInt32();
	errcode.Reset();


	TInt ferr = iFileHandle.Open(iFSession,KFileName,EFileRead | EFileWrite );

	if( KErrNone == ferr )
		{
		iFileHandle.Close();

		iFSession.Delete(KFileName);
		}


	if(code == SErrNone)
		{


		param = outList->FindFirst(pos, KReturnValue);
		TLiwVariant iterator = param->Value();
		CLiwIterable* iter = iterator.AsIterable();

		TLiwVariant entry;
		iter->NextL(entry);

		const CLiwMap* map = entry.AsMap();
		TInt count1 = map->Count();

		TLiwVariant cntId;
		map->FindL(KContactId, cntId);
		TPtrC ptr = cntId.AsDes();



	    CLiwDefaultMap* inMap = CLiwDefaultMap::NewL();
	    CleanupStack::PushL(inMap);

	    inMap->InsertL(KDBUri,TLiwVariant(_L("cntdb://c:contacts.cdb")));



	    inMap->InsertL(KContactId,TLiwVariant(ptr));

	    cntId.Reset();
	    entry.Reset();

	    iterator.Reset();

	    inMap->InsertL(KDestFileNameParam,TLiwVariant(_L("C:\\data\\Export.vcf")));

	    TLiwGenericParam element ;
		element.SetNameAndValueL(KData,TLiwVariant(inMap));



		inList->AppendL(element);
		element.Reset();




		outList->Reset();


		TRAPD(err,iIface->ExecuteCmdL(KCmdExport, *inList, *outList, 0, NULL));

		CleanupStack::Pop(inMap);
		inMap->DecRef();
		pos =0;
		const TLiwGenericParam* param1 = outList->FindFirst( pos, KExitCode );

		TLiwVariant errcode2 = param1->Value();
		TInt code1 = errcode2.AsTInt32();
		errcode2.Reset();

		inList->Reset();
		outList->Reset();



	TInt ferr = iFileHandle.Open(iFSession,KFileName,EFileRead | EFileWrite );

	if( KErrNone == ferr )
		{
		iFileHandle.Close();
		return SErrNone;
		}
	else
		return SErrGeneralError;


/*		if(code1 != SErrNone)
			return code1;
		else
			return SErrNone;

*/

		}
	else
		return code;

 	//__UHEAP_MARKEND;


    }


 TInt CTestProvider ::ImportVCard(CStifItemParser& /*aItem*/)
    {
    //__UHEAP_MARK;
    LoadService();

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContentType );

    CLiwDefaultMap* inMap = CLiwDefaultMap::NewL();
    CleanupStack::PushL(inMap);

    inMap->InsertL(KDBUri,TLiwVariant(_L("cntdb://c:contacts.cdb")));

	inMap->InsertL(KSourceFileNameParam,TLiwVariant(_L("C:\\data\\Import.vcf")));

    TLiwGenericParam element ;
	element.SetNameAndValueL(KData,TLiwVariant(inMap));

	inList->AppendL(element);
	element.Reset();

	TRAPD(err,iIface->ExecuteCmdL(KCmdImport, *inList, *outList, 0, NULL));

	CleanupStack::Pop(inMap);
	inMap->DecRef();

	TInt pos =0;
	const TLiwGenericParam* param1 = outList->FindFirst( pos, KExitCode );

	TLiwVariant errcode2 = param1->Value();
	TInt code = errcode2.AsTInt32();
	errcode2.Reset();

	inList->Reset();
	outList->Reset();

	if(code != SErrNone)
		return code;
	else
		return SErrNone;




    //__UHEAP_MARKEND;
    }
 
 

 TInt CTestProvider :: AddOneContactNewFieldsL()
     {                                     
     CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();    
         
        TInt pos = 0;             
        pMap->InsertL(KContactId, TLiwVariant( _L("")));
           CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();    
           fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));
               
           fieldMap->InsertL(KFieldValue,TLiwVariant(_L("Barbie")));
           
           pMap->InsertL(KFirstName, TLiwVariant(fieldMap));

           CLiwDefaultMap* fieldPrefixMap = CLiwDefaultMap::NewL();    
           fieldPrefixMap->InsertL(KFieldLabel,TLiwVariant(_L("Prefix")));
                   
           fieldPrefixMap->InsertL(KFieldValue,TLiwVariant(_L("Princess")));
           
           pMap->InsertL(KPrefix, TLiwVariant(fieldPrefixMap));
           
           CLiwDefaultMap* fieldNoteMap = CLiwDefaultMap::NewL();    
           
           fieldNoteMap->InsertL(KFieldLabel,TLiwVariant(_L("Note")));
                       
           fieldNoteMap->InsertL(KFieldValue,TLiwVariant(_L("Lead role in Barbie, the island princess")));
           
           pMap->InsertL(KNote, TLiwVariant(fieldNoteMap));

CLiwDefaultMap* anniMap = CLiwDefaultMap::NewL();    
    anniMap->InsertL(KFieldLabel,TLiwVariant(_L("Anniversary")));
    anniMap->InsertL(KFieldValue,TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
    pMap->InsertL(KAnniversary, TLiwVariant(anniMap));
    
    
    CLiwDefaultMap* dateMap = CLiwDefaultMap::NewL();    
    dateMap->InsertL(KFieldLabel,TLiwVariant(_L("Date")));
    dateMap->InsertL(KFieldValue,TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
       pMap->InsertL(KDate, TLiwVariant(dateMap));
               
 
                                       
           CLiwDefaultMap* fieldSecNameMap = CLiwDefaultMap::NewL();    
           fieldSecNameMap->InsertL(KFieldLabel,TLiwVariant(_L("SecondName")));
               
           fieldSecNameMap->InsertL(KFieldValue,TLiwVariant(_L("Doll")));
           
           pMap->InsertL(KSecondName, TLiwVariant(fieldSecNameMap));
               
           CLiwDefaultMap* fieldPhotoMap = CLiwDefaultMap::NewL();    
           fieldPhotoMap->InsertL(KFieldLabel,TLiwVariant(_L("CallerObjImg")));
                   
           fieldPhotoMap->InsertL(KFieldValue,TLiwVariant(_L("C:\\data\\images\\pic.jpg")));
           
           pMap->InsertL(KCallerObjImg, TLiwVariant(fieldPhotoMap));
               
           CLiwDefaultMap* fieldXspidMap = CLiwDefaultMap::NewL();    
           CLiwList* list = CLiwDefaultList::NewL();
           list->AppendL(TLiwVariant(_L("Yahoo:barbie@yahoo.co.in")));
           list->AppendL(TLiwVariant(_L("Google:barbie@gmail.com")));
           fieldXspidMap->InsertL(KFieldLabel,TLiwVariant(_L("IMPP")));
               
           fieldXspidMap->InsertL(KFieldValue,TLiwVariant(list));
           
           pMap->InsertL(KXSPID, TLiwVariant(fieldXspidMap));
           
     const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
     const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap)); ;
         
     inList ->AppendL( paramContentType );
     inList ->AppendL( paramAddData );    
      
     iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, 0, NULL);
         
     const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
     TLiwVariant err = param->Value();
     TInt code = err.AsTInt32();
            
            
     pMap->DecRef();
     fieldMap->DecRef();
     fieldMap->DecRef();
     
     inList->Reset();
     outList->Reset(); 
     if(code == SErrNone)
             {
             return KErrNone;  
             }            
     return KErrGeneral;
     }

     
 TInt CTestProvider :: GetListNewFieldsTestSync(CStifItemParser& /*aItem */)
     {    
     LoadService();
     TInt addRes = AddOneContactNewFieldsL();
     if(addRes != KErrNone)
         {
         return KErrGeneral;
         }
     
     _LIT8(KFilter, "Filter");
     _LIT8(KSearchVal, "SearchVal");
     TInt iResult = KErrNone;   
     TInt pos = 0;
         
     //const TLiwGenericParam paramGetListSortOrder;
     
     const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));    
     inList ->AppendL( paramContentType );
     
     CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();    
     CleanupStack::PushL(map);
     map->InsertL(KSearchVal,_L("Barbie"));
     
     const TLiwGenericParam paramData(KFilter, TLiwVariant(map));    
     inList ->AppendL( paramData );
     
     iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, 0, NULL);
         
     const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
     TLiwVariant err = param->Value();
     TInt code = err.AsTInt32();
         
     if(code == SErrNone)
         {
         TInt pos = 0;
                  TBuf<255> firstName;
                  TBuf<255> secName;
                  TBuf<255> callerObjImg;
                  TBuf<255> Note;
                  TLiwVariant cntId;
                  TLiwVariant mapfield;
                  TLiwVariant firstname;
                  TLiwVariant secname;
                  TLiwVariant callerobjimg;
                  TLiwVariant xspidarr;
                  TLiwVariant note;
                  TLiwVariant entry;
                  const CLiwMap* map = NULL;
                  const CLiwMap* mapField = NULL;
                  const CLiwList* xspid = NULL;
                  
                  param = outList->FindFirst(pos, KReturnValue);
                  TLiwVariant iterator = param->Value();
                  CLiwIterable* iter = iterator.AsIterable();
                      if(iter->NextL(entry))
                          {
                          map = entry.AsMap();
                          TInt count1 = map->Count();       
                          map->FindL(KContactId, cntId);                   
                          TPtrC8 ptr = cntId.AsData();                 
                          if(map->FindL(KFirstName,mapfield))
                          mapField = mapfield.AsMap();
                          
                          TInt count = mapField->Count();
                          firstname.Reset();
                          mapField->FindL(KFieldValue,firstname);
                          firstName = firstname.AsDes();
                          if(firstName.CompareF(_L("Barbie")) != 0)       
                              {
                              iResult = KErrGeneral;
                              }    
                          
                          if(map->FindL(KSecondName,mapfield))
                          mapField = mapfield.AsMap();                
                          count = mapField->Count();
                          mapField->FindL(KFieldValue,secname);
                          secName = secname.AsDes();
                          if(secName.CompareF(_L("Doll")) != 0)       
                              {
                              iResult = KErrGeneral;
                              }    
                          
                          if(map->FindL(KCallerObjImg,mapfield))
                            mapField = mapfield.AsMap();                
                            count = mapField->Count();
                            mapField->FindL(KFieldValue,callerobjimg);
                            callerObjImg = callerobjimg.AsDes();
                            if(callerObjImg.CompareF(_L("C:\\data\\images\\pic.jpg")) != 0)       
                                {
                                iResult = KErrGeneral;
                                }
                            if(map->FindL(KNote,mapfield))
                            mapField = mapfield.AsMap();                
                            count = mapField->Count();
                            mapField->FindL(KFieldValue,note);
                            Note = note.AsDes();
                            if(Note.CompareF(_L("Lead role in Barbie, the island princess")) != 0)       
                                {
                                iResult = KErrGeneral;
                                }
                    
                            if(map->FindL(KXSPID,mapfield))
                                mapField = mapfield.AsMap();                
                            //count = mapField->Count();
                            mapField->FindL(KFieldValue,xspidarr);
                            xspid = xspidarr.AsList();
                            TInt xspidcount = xspid->Count();
                            for(TInt index =0;index < xspidcount; index++)
                                {
                                TLiwVariant xspidVal;
                                if(xspid->AtL(index,xspidVal))
                                {
                                TPtrC ptrVal = xspidVal.AsDes();
                                if(ptrVal.CompareF(_L("Yahoo:Barbie@yahoo.co.in")) != 0 && ptrVal.CompareF(_L("Google:Barbie@gmail.com")) != 0)
                                {
                                    iResult = KErrGeneral;
                                    break;
                                }
                                }
                            }
                      
                  }
         }
     
     CleanupStack::Pop(map);
     map->DecRef(); 
     inList->Reset();
     outList->Reset();   
     return iResult;                   
     }
 
 
 

 TInt CTestProvider :: AddContactNewFieldsSynTest(CStifItemParser& /*aItem */)
     {
     LoadService();        
                                     
     CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();    
         
        TInt pos = 0;             
        pMap->InsertL(KContactId, TLiwVariant( _L("")));
           CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();    
           fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));
               
           fieldMap->InsertL(KFieldValue,TLiwVariant(_L("Barbie")));
           
           pMap->InsertL(KFirstName, TLiwVariant(fieldMap));

           CLiwDefaultMap* fieldPrefixMap = CLiwDefaultMap::NewL();    
           fieldPrefixMap->InsertL(KFieldLabel,TLiwVariant(_L("Prefix")));
                   
           fieldPrefixMap->InsertL(KFieldValue,TLiwVariant(_L("Princess")));
           
           pMap->InsertL(KPrefix, TLiwVariant(fieldPrefixMap));
           
           CLiwDefaultMap* fieldNoteMap = CLiwDefaultMap::NewL();    
           
           fieldNoteMap->InsertL(KFieldLabel,TLiwVariant(_L("Note")));
                       
           fieldNoteMap->InsertL(KFieldValue,TLiwVariant(_L("Sister of Princess Barbie")));
           
           pMap->InsertL(KNote, TLiwVariant(fieldNoteMap));
           

CLiwDefaultMap* anniMap = CLiwDefaultMap::NewL();    
    anniMap->InsertL(KFieldLabel,TLiwVariant(_L("Anniversary")));
    anniMap->InsertL(KFieldValue,TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
    pMap->InsertL(KAnniversary, TLiwVariant(anniMap));
    
    
    CLiwDefaultMap* dateMap = CLiwDefaultMap::NewL();    
    dateMap->InsertL(KFieldLabel,TLiwVariant(_L("Date")));
    dateMap->InsertL(KFieldValue,TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
       pMap->InsertL(KDate, TLiwVariant(dateMap));
               
                                       
           CLiwDefaultMap* fieldSecNameMap = CLiwDefaultMap::NewL();    
           fieldSecNameMap->InsertL(KFieldLabel,TLiwVariant(_L("SecondName")));
               
           fieldSecNameMap->InsertL(KFieldValue,TLiwVariant(_L("Doll")));
           
           pMap->InsertL(KSecondName, TLiwVariant(fieldSecNameMap));
               
           CLiwDefaultMap* fieldPhotoMap = CLiwDefaultMap::NewL();    
           fieldPhotoMap->InsertL(KFieldLabel,TLiwVariant(_L("CallerObjImg")));
                   
           fieldPhotoMap->InsertL(KFieldValue,TLiwVariant(_L("C:\\data\\images\\pic.jpg")));
           
           pMap->InsertL(KCallerObjImg, TLiwVariant(fieldPhotoMap));
               
           CLiwDefaultMap* fieldXspidMap = CLiwDefaultMap::NewL();    
           CLiwList* list = CLiwDefaultList::NewL();
           list->AppendL(TLiwVariant(_L("Yahoo:kelly@yahoo.co.in")));
           list->AppendL(TLiwVariant(_L("Google:kelly@gmail.com")));
           fieldXspidMap->InsertL(KFieldLabel,TLiwVariant(_L("IMPP")));
               
           fieldXspidMap->InsertL(KFieldValue,TLiwVariant(list));
           
           pMap->InsertL(KXSPID, TLiwVariant(fieldXspidMap));
           
                 
     
     
     
     const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
     const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap)); ;
         
     inList ->AppendL( paramContentType );
     inList ->AppendL( paramAddData );    
     
      
     iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, 0, NULL);
         
     const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
     TLiwVariant err = param->Value();
     TInt code = err.AsTInt32();
            
            

     if(code == SErrNone)
             {
             pos =0;
              param = outList->FindFirst( pos, KReturnValue );    
              
              TLiwVariant cntId = param->Value();
              
              TPtrC idVal = cntId.AsDes();
              if(idVal.Compare(KNullDesC) != 0)
                  {
                  pMap->DecRef();
                  fieldMap->DecRef();
                  fieldMap->DecRef();
                  
                  inList->Reset();
                  outList->Reset(); 
                  return KErrNone;
                  }
              else
                  {
                  pMap->DecRef();
                  fieldMap->DecRef();
                  fieldMap->DecRef();
                  
                  inList->Reset();
                  outList->Reset(); 
                  return KErrGeneral;
                  }          
             }           
     pMap->DecRef();
     fieldMap->DecRef();
     fieldMap->DecRef();
     
     inList->Reset();
     outList->Reset(); 
     return KErrGeneral;
     }


 

 TInt CTestProvider :: AddGroupSynTest(CStifItemParser& /*aItem*/)
     {           
     LoadService();                          
     CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
     TInt pos = 0;                 
     
     pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
     pMap->InsertL(KGroupId, TLiwVariant(_L8("")));
     pMap->InsertL(KGroupLabel, TLiwVariant(_L("TestAddSyncGroup")));
     
     const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group"))); 
     const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap)); ;
        
     inList ->AppendL( paramContentType );
     inList ->AppendL( paramAddData );   
     iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, 0, NULL);
         
     const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
     TLiwVariant err = param->Value();
     TInt code = err.AsTInt32();
 
     
     if(code == SErrNone)
         { 
          pos =0;   
          param = outList->FindFirst( pos, KReturnValue );    
          
          TLiwVariant cntId = param->Value();
          
          TPtrC idVal = cntId.AsDes();
          if(idVal.Compare(KNullDesC) != 0)
              {
              
              inList->Reset();
              outList->Reset();
              return KErrNone;
              }
          else
              {
              
              inList->Reset();
              outList->Reset();
              return KErrGeneral;
              }        
         }
     
     inList->Reset();
     outList->Reset();
     return KErrGeneral;
     
     }
