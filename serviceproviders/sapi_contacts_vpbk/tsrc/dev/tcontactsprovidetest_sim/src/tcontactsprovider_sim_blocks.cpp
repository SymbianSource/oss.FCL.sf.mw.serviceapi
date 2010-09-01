/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>

#include <liwservicehandler.h>
#include <liwcommon.h>

#include "serviceerrno.h"

#include "tcontactsprovider_sim.h"


_LIT(KCntSimDbUri,"sim://global_adn");

// _LIT8(KFirstName,"FirstName");
_LIT(KName,"Arnold"); 
_LIT8(KNumber,"MobilePhoneGen");
_LIT(KPhoneNumber,"09918765432");




_LIT(KError,"Error code is");
_LIT(KSuccess,"Successful");
_LIT(KNewLine,"\n");
_LIT(KServiceOpen,"Service handle created");
_LIT(KServiceClose,"Service handle deleted");

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
_LIT8(KFieldValue, " Value");
_LIT8(KFieldNext, "Next");
_LIT8(KGroupLabel, "GroupLabel");
_LIT8(KContents, "Contents");
_LIT8(KContactId, "id");

_LIT8(KList, "IdList"); 
_LIT8(KContact, "Contact");
_LIT8(KGroup, "Group");
_LIT8(KDatabase, "Database");
		    
_LIT8(KDBUri, "DBUri");
_LIT8(KSearchVal, "SearchVal");
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




void CContactsUT::Delete() 
    {
    iIface->Close();
    iCriteriaArray.Close();
    delete iServiceHandler;    
    delete iInparams;
    delete iOutparams;
    delete iCriteria;
    delete inList;
    delete outList;
    delete iCntID;
    }




void CContactsUT::LoadService()
    {
    TInt pos = 0;
    //iCntID = HBufC::NewL(255);
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



 TInt CContactsUT::HandleNotifyL(TInt aCmdId,TInt aEventId,CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList)
            
	 {
	    RFs fs;
		RFile file;  
		User::LeaveIfError(fs.Connect());		
	    CleanupClosePushL(fs);
		TInt errfile =file.Replace(fs,_L("C:\\tcontacts_simlog2.txt"), EFileWrite | EFileStreamText); 				
		file.Write(_L8("\n Starting logs"));	
		file.Flush(); 
		CActiveScheduler::Stop();

		TInt pos = 0;   
		const TLiwGenericParam* param;

		param = aEventParamList.FindFirst( pos, KExitCode );    
 
		TLiwVariant err = param->Value();
		
		TInt code = err.AsTInt32();
		TBuf8<225> error;
		error.Num(code);
        file.Write(error);	
		file.Flush(); 
	 	error.Zero();
	 	
	 	iErr = KErrGeneral;
	 	
	 if((iCase == EGetList || iCase == ESearch || iCase == EDeleteContact || iCase ==EExport) && (code ==SErrNone))
		 {		  
		
		   param = aEventParamList.FindFirst(pos, KReturnValue);
		
			TBool tResult = EFalse;
			
			TBool findResult = EFalse;
			TLiwVariant err = param->Value();
			TLiwVariant cntId;
			TLiwVariant mapfield;
			TLiwVariant firstname;
			TBuf<255> firstName;
			TLiwVariant entry;
			const CLiwMap* map = NULL;
			const CLiwMap* mapField = NULL;

	     TLiwVariant iterator = param->Value();
         CLiwIterable* iter = iterator.AsIterable();            
         TBuf8<255> buf;
         
        while(iter->NextL(entry))
            { 
            file.Write(_L8("\n iterator nextl called"));	
		    file.Flush();                                           
            map = entry.AsMap();
            TInt count1 = map->Count();                       
            map->FindL(KContactId, cntId);                                 
            TPtrC ptr = cntId.AsDes();                
			
			file.Write(_L8("Count1 "));
			buf.Num(count1);
			file.Write(buf);	
		    file.Flush();                                           
			buf.Zero();
// count log
            if(iCase == EDeleteContact || iCase ==EExport  )
            {
            iCntID = ptr.AllocL();
            
            file.Write(_L8("Contactid is assinged as  "));
			buf.Copy(*iCntID);
			file.Write(buf);	
		    file.Flush();                                           
            
            break;	
            }
            
            file.Write(_L8("\n contact id"));	
		    file.Flush(); 
            if(map->FindL(KLastName,mapfield))
            mapField = mapfield.AsMap();
            
            TInt count = mapField->Count(); 

        	file.Write(_L8("Count2 "));
			buf.Num(count1);
			file.Write(buf);	
		    file.Flush();                                           
			buf.Zero();
         
            mapField->FindL(KFieldValue,firstname);
            firstName = firstname.AsDes();
            buf.Copy(firstName);
            file.Write(buf);	
		    file.Flush();
		    buf.Zero();	
		    if(iCase == EGetList)
		    {
        	if(firstName.CompareF(_L("Arnold")) == 0)       
                {
                tResult = ETrue;    
               }                 

		    }
		    
		    if(iCase == ESearch)
		    {
        	if(firstName.CompareF(_L("Monica Bellucc")) == 0)       
                {
                tResult = ETrue;    
               }                 
		    	
		    }
            mapfield.Reset();             
            firstname.Reset();                                      
            entry.Reset();  
            }         
		 
			if(tResult)
				{
				iErr = KErrNone;    
				}
 
            iterator.Reset();              
            delete iter;                       
		 
		 
        	file.Write(_L8("iterator deleted\n"));
		    file.Flush();                                           
		

		 
		 	
		 }
	 

   		if( iCase == EExportChk || iCase == EImport || iCase == EDeleteCkh || iCase == EAddContact )
	        {
	        if(aEventId == KLiwEventCompleted && code == KErrNone )
	            {
	            iErr = KErrNone;             
	            }
	        else
	            {
	            iErr = code;    
	            }        
      		error.Num(iErr);
	        file.Write(_L8("Error for import  : "));
	        file.Write(error);	
			file.Flush(); 
		 	error.Zero();
	      
	        }
	



	 file.Write(_L8("\n Last statement"));	
     file.Flush();  
    file.Close();
   CleanupStack::PopAndDestroy();
	 return 0;	
	 }




















// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// Csapi_getheader:RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CContactsUT::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
         ENTRY( "addcontact", CContactsUT::addcontactL ),
         ENTRY( "getlisttest", CContactsUT::getlisttestL ),
         ENTRY( "getlisttest_search", CContactsUT::getlisttest_searchL ),
         ENTRY(	"deletetest" , CContactsUT::deletetestL ),
         ENTRY(	"importtest" , CContactsUT::importL ),         
         ENTRY(	"exporttest" , CContactsUT::exportL ),         
       
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
// -----------------------------------------------------------------------------
// CContactsUT:addcontactL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::addcontactL( CStifItemParser& aItem  )
    {

    iErr = KErrGeneral;
    iCase = EAddContact;    
    LoadService();        
        							
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    
    CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();     
    TInt pos = 0;  	          
    fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("Mobile")));
    	
    fieldMap->InsertL(KFieldValue,TLiwVariant(_L("9980161669")));
    pMap->InsertL(KDBUri, TLiwVariant( _L("sim://global_adn")));
    
    
    pMap->InsertL(KContactId, TLiwVariant( _L("")));
    pMap->InsertL(KMobilePhoneGen, TLiwVariant(fieldMap)); // doubt here 
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap)); ;
        
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData ); 
    
     
    iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }           
  
    fieldMap->DecRef();
    fieldMap->DecRef();
    pMap->DecRef();
 
    inList->Reset();
    outList->Reset(); 
                   
    return iErr;
    

    }

// -----------------------------------------------------------------------------
// CContactsUT:getlisttestL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::getlisttestL( CStifItemParser& aItem  )
    {
    

	RFs fs;
	RFile file;  
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TInt errfile =file.Replace(fs,_L("C:\\tcontacts_simlog.txt"), EFileWrite | EFileStreamText); 				
	file.Write(_L8("\n Starting logs"));	
	file.Flush();
	
	LoadService();		
	iErr = KErrNone;
	file.Write(_L8("\n Loaded service"));	
	file.Flush();
	
	// For Automation 
	

	
    iCase =  EImport;
      
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
        
    TInt pos = 0;  	          
    
    pMap->InsertL(KDBUri, TLiwVariant( _L("sim://global_adn")));    
    
    pMap->InsertL(KSourceFileNameParam, TLiwVariant( _L("c:\\data\\Import.vcf")));    
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData ); 
      
    iIface->ExecuteCmdL(KCmdImport, *inList, *outList, KLiwOptASyncronous, this);
    
   	file.Write(_L8("\n Import is called for autoamtion"));	
	file.Flush();

        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
	TBuf8<20> errbuf;
	errbuf.Num(code);
   	file.Write(_L8("\n Error for import  "));	
   	file.Write(errbuf);
	file.Flush();
	errbuf.Zero();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }
	errbuf.Num(iErr);
   	file.Write(_L8("\n Error from callback for import  "));	   	
   	file.Write(errbuf);
	file.Flush();
	errbuf.Zero();

	
    inList->Reset();
    outList->Reset();
    pMap->DecRef();    
   

   if(iErr ==KErrNone)
   {         
   // Test case of getlist started	
	iCase = EGetList;
	
    pos = 0;

    const TLiwGenericParam paramContentType1(KType, TLiwVariant( _L("Contact")));    

    inList->AppendL( paramContentType1 );   
    
    CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();    
    CleanupStack::PushL(map);
	map->InsertL(KDBUri, TLiwVariant(_L("sim://global_adn")));
	
    const TLiwGenericParam paramDeleteData(KFilter, TLiwVariant(map));
    inList ->AppendL( paramDeleteData ); 

     
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);     
    
    const TLiwGenericParam* param1 = outList->FindFirst( pos, KExitCode );

    TLiwVariant err1 = param1->Value();
    TInt code1 = err1.AsTInt32();
    TBuf8<225> error;
    error.Num(code1);
    file.Write(error);	
	file.Flush();
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }                  
  	err.Reset();
    CleanupStack::Pop(map);
  	map->DecRef();
  	
    inList->Reset();    
    outList->Reset();
    error.Zero();
    error.Num(iErr);    
    file.Write(error);	
	file.Flush();
    }
	file.Close();
	CleanupStack::PopAndDestroy();
		
	return iErr;

	
    }

// -----------------------------------------------------------------------------
// CContactsUT:getlisttest_searchL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt CContactsUT::getlisttest_searchL(CStifItemParser& aItem)
	{
//	__UHEAP_MARK;
 
	RFs fs;
	RFile file;  
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TInt errfile =file.Replace(fs,_L("C:\\tcontacts_search.txt"), EFileWrite | EFileStreamText); 				
	file.Write(_L8("\n Starting logs"));	
	file.Flush();
	


    _LIT8(KFilter, "Filter");
    _LIT8(KSearchVal, "SearchVal");
    
    //_LIT8(KKeys, "Keys");
    iErr = KErrGeneral;   
    LoadService(); 
    
    
   	file.Write(_L8("\n Load Service Called"));	
	file.Flush();




	
    iCase =  EImport;
      
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
        
    TInt pos = 0;  	          
    
    pMap->InsertL(KDBUri, TLiwVariant( _L("sim://global_adn")));    
    
    pMap->InsertL(KSourceFileNameParam, TLiwVariant( _L("c:\\data\\Import1.vcf")));    
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData ); 
      
    iIface->ExecuteCmdL(KCmdImport, *inList, *outList, KLiwOptASyncronous, this);
    
   	file.Write(_L8("\n Import is called for autoamtion"));	
	file.Flush();

        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
	TBuf8<20> errbuf;
	errbuf.Num(code);
   	file.Write(_L8("\n Error for import  "));	
   	file.Write(errbuf);
	file.Flush();
	errbuf.Zero();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }
	errbuf.Num(iErr);
   	file.Write(_L8("\n Error from callback for import  "));	
   	file.Write(errbuf);
	file.Flush();
	errbuf.Zero();

	
    inList->Reset();
    outList->Reset();
    pMap->DecRef();    
   

   
	if(iErr == KErrNone)
	{	        
    pos = 0;
    iCase = ESearch;
      	
   
    const TLiwGenericParam paramContentType1(KType, TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType1 );
    
    CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();    
    CleanupStack::PushL(map);
    map->InsertL(KSearchVal,TLiwVariant(_L("M")));
//    map->InsertL(KKeys,TLiwVariant(KLastName));
    map->InsertL(KDBUri, TLiwVariant(_L("sim://global_adn")));
    
    const TLiwGenericParam paramData(KFilter, TLiwVariant(map));    
    inList ->AppendL( paramData );
    

    
    
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
	
   	file.Write(_L8("\n Executecmd is called"));	
	file.Flush();

        
    const TLiwGenericParam* param1 = outList->FindFirst( pos, KExitCode );
    err.Reset();
    err = param1->Value();
    TInt code1 = err.AsTInt32();
    
    TBuf8<50> buf;
    buf.Num(code1); 
   	file.Write(_L8("\n Error1 : "));
   	file.Write(buf);	
	file.Flush();
	buf.Zero();
        
    if(code1 == SErrNone)
        {
        CActiveScheduler::Start();    
        }
    


    CleanupStack::Pop(map);
    map->DecRef(); 
    inList->Reset();
    outList->Reset();   
   
    buf.Num(iErr);
    file.Write(_L8("\n Error2 : "));
   	file.Write(buf);	
	file.Flush();
	buf.Zero();
   }
   file.Close();
   CleanupStack::PopAndDestroy(); // closing rFs;
	
   	//__UHEAP_MARKEND;
    return iErr;                   
	
	
	
	
	


		
	}

// -----------------------------------------------------------------------------
// CContactsUT:deletetestL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::deletetestL(CStifItemParser& aItem)
	{

	iCase = EDeleteContact;
	iErr = KErrGeneral;   
	LoadService();  
    
    //For Automation

	
    iCase =  EImport;
      
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
        
    TInt pos = 0;  	          
    
    pMap->InsertL(KDBUri, TLiwVariant( _L("sim://global_adn")));    
    
    pMap->InsertL(KSourceFileNameParam, TLiwVariant( _L("c:\\data\\Import.vcf")));    
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData ); 
      
    iIface->ExecuteCmdL(KCmdImport, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }
    inList->Reset();
    outList->Reset();
    pMap->DecRef();    

    
    if(iErr != KErrGeneral)
     return iErr;
   
    
    const TLiwGenericParam paramContentType1(KType, TLiwVariant( _L("Contact"))); 
    inList->AppendL( paramContentType1 );
    
    
    CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();    
    CleanupStack::PushL(map);
	map->InsertL(KDBUri, TLiwVariant(_L("sim://global_adn")));
	
    const TLiwGenericParam paramDeleteData(KFilter, TLiwVariant(map));
    inList ->AppendL( paramDeleteData ); 
    
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);

  	 pos = 0;        
    const TLiwGenericParam* param1 = outList->FindFirst( pos, KExitCode );
    TLiwVariant err1 = param1->Value();
    TInt code1 = err1.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    CleanupStack::Pop(map);
  	map->DecRef();

    if(code1 == SErrNone)
        {
        CActiveScheduler::Start();    
           
        }
        
   	iCase = EDeleteCkh; 
   	   
    const TLiwGenericParam paramContent2(KType, TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContent2 );
    CLiwDefaultList* list = CLiwDefaultList :: NewL();    
    list->AppendL(TLiwVariant(*iCntID));
 	
 	CLiwMap* mapContactId = CLiwDefaultMap::NewL();
    mapContactId->InsertL(KDBUri, TLiwVariant(_L("sim://global_adn")));
    mapContactId->InsertL(KList,TLiwVariant(list));

    const TLiwGenericParam paramDeleteData1(KData, TLiwVariant(mapContactId));
    inList ->AppendL( paramDeleteData1 ); 
    iIface->ExecuteCmdL(KCmdDelete, *inList, *outList, KLiwOptASyncronous, this);
    
    
    param = outList->FindFirst( pos, KExitCode );
    err = param->Value();
    code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        } 
    inList->Reset();
    outList->Reset();
    mapContactId->DecRef();
    list->DecRef(); 
    
    return iErr;   	


	}


// -----------------------------------------------------------------------------
// CContactsUT:importL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::importL(CStifItemParser& aItem)
	{
		
	iErr = KErrGeneral;
	LoadService();              
    iCase =  EImport;
    
   // __UHEAP_MARK;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
        
    TInt pos = 0;  	          
    
    pMap->InsertL(KDBUri, TLiwVariant( _L("sim://global_adn")));    
    
    pMap->InsertL(KSourceFileNameParam, TLiwVariant( _L("c:\\data\\Import.vcf")));    
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData ); 
      
    iIface->ExecuteCmdL(KCmdImport, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }
    inList->Reset();
    outList->Reset();
    pMap->DecRef();    
    
   // __UHEAP_MARKEND;
    
    return iErr;
    	
	
	
	
	
	
	
	}

// -----------------------------------------------------------------------------
// CContactsUT:exportL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CContactsUT::exportL(CStifItemParser& aItem)
	{

	RFs fs;
	RFile file;  
	User::LeaveIfError(fs.Connect());
	CleanupClosePushL(fs);

	TInt errfile =file.Replace(fs,_L("C:\\tcontacts_export.txt"), EFileWrite | EFileStreamText); 				
	file.Write(_L8("\n Starting logs"));	
	file.Flush();




	
	iErr = KErrNone;   
	LoadService();  
	
	//For Autoamtion

	

	iCase =  EImport;
      
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
        
    TInt pos = 0;  	          
    
    pMap->InsertL(KDBUri, TLiwVariant( _L("sim://global_adn")));    
    
    pMap->InsertL(KSourceFileNameParam, TLiwVariant( _L("c:\\data\\Import.vcf")));    
    
    const TLiwGenericParam paramContentType1(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData1(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType1 );
    inList ->AppendL( paramAddData1 ); 
      
    iIface->ExecuteCmdL(KCmdImport, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }
    inList->Reset();
    outList->Reset();
    pMap->DecRef();    
   
   if(iErr == KErrNone)
   {	
	iCase = EExport;
     pos = 0;
    
   
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType );
    
    CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();    
    CleanupStack::PushL(map);
	map->InsertL(KDBUri, TLiwVariant(_L("sim://global_adn")));
	
    const TLiwGenericParam paramDeleteData(KFilter, TLiwVariant(map));
    inList ->AppendL( paramDeleteData ); 

   iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param1 = outList->FindFirst( pos, KExitCode );
    err.Reset();
    err = param1->Value();
    TInt code1 = err.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    CleanupStack::Pop(map);
  	map->DecRef();

	TBuf8<255> buf;
	file.Write(_L8("\n GetList called and return error is : "));	
	buf.Num(code1);
	file.Write(buf);
	file.Flush();
	buf.Zero();
   
    
    
    if(code1 == SErrNone)
        {
        CActiveScheduler::Start();    
       }
        
   	iCase = EExportChk; 
   	
   	
   	   
 
    const TLiwGenericParam paramContent(KType, TLiwVariant( _L("Contact")));
    inList->AppendL( paramContent );
    
    TBuf<255> cntIdunicode;
    cntIdunicode.Copy(*iCntID);
    buf.Copy(cntIdunicode);
    
   	file.Write(_L8("\n Contact Id copied : "));
   	file.Write(buf);	
	
	file.Flush();
	buf.Zero();
 
    
    
    CLiwMap* pMap1 = CLiwDefaultMap::NewL();
    pMap1->InsertL(KDBUri, TLiwVariant( _L("sim://global_adn")));
    pMap1->InsertL(KContactId, TLiwVariant(cntIdunicode));
    
    pMap1->InsertL(KDestFileNameParam, TLiwVariant( _L("c:\\data\\Export.vcf")));    

   const TLiwGenericParam paramContentType2(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap1));
       
    inList ->AppendL( paramContentType2 );
    inList ->AppendL( paramAddData ); 
      
    iIface->ExecuteCmdL(KCmdExport, *inList, *outList, KLiwOptASyncronous, this);
    
    file.Write(_L8("\n Contact Id copied : "));
  	file.Flush();

    
        
    param = outList->FindFirst( pos, KExitCode );
    err.Reset();
    err = param->Value();
    TInt code2 = err.AsTInt32();

    file.Write(_L8("\n Error code : "));
  	buf.Num(code2);
  	file.Write(buf);
  	file.Flush();
  	buf.Zero();

           
    if(code2 == SErrNone)
        {
        CActiveScheduler::Start();    
        }
    inList->Reset();
    outList->Reset();
    pMap1->DecRef();    
    
    file.Write(_L8("\n Error code after retunring of call back iErr : "));
  	buf.Num(iErr);
  	file.Write(buf);
  	file.Flush();
  	buf.Zero();
  }
  file.Close();
  CleanupStack::PopAndDestroy(); // rFs closing
    
    
   // __UHEAP_MARKEND;
    return iErr;
    
	
	}