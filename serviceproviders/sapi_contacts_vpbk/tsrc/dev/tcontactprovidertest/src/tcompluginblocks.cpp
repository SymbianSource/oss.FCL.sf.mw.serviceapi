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
#include <StifTestInterface.h>

#include <liwservicehandler.h>
#include <liwcommon.h>

#include <VPbkEng.rsg>
#include <e32def.h>

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

#include "tcomplugin.h"

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

_LIT8( KCancel, "Cancel" );

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
_LIT8(KXSPID, "IMPP");


//----------------------------------------------------------------------------
// CTestProvider :: Delete()
//----------------------------------------------------------------------------
void CTestProvider::Delete() 
    {
    iIface->Close();
    iCriteriaArray.Close();
    delete iServiceHandler;    
    delete iInparams;
    delete iOutparams;
    delete iCriteria;
    delete inList;
    delete outList;
    iIdArrayList.ResetAndDestroy();
    delete iCntID;
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
       	ENTRY("Export" , CTestProvider:: ExportL),
       	ENTRY("Import" , CTestProvider:: ImportL),
       	ENTRY("ModifyContact" , CTestProvider:: ModifyContact),
       	ENTRY("ModifyGroup" , CTestProvider:: ModifyGroup),
       	ENTRY("GetContactALLPosBased" , CTestProvider:: GetContactALLPosBased),
       	ENTRY("GetContactSearchPosBased" , CTestProvider:: GetContactSearchPosBased),
       	ENTRY("GetGroupPosBased" , CTestProvider:: GetGroupPosBased),
       	ENTRY("GetDatabasePosBased" , CTestProvider:: GetDatabasePosBased),
       	ENTRY("AddContactPosBased" , CTestProvider:: AddContactPosBased),
       	ENTRY("AddGroupPosBased" , CTestProvider:: AddGroupPosBased),
       	ENTRY("DeleteContactPosBased" , CTestProvider:: DeleteContactPosBased),
       	ENTRY("OrganiseAddPosBased" , CTestProvider :: OrganiseAddPosBased ),
       	ENTRY("OrganiseDeletePosbased" , CTestProvider :: OrganiseDeletePosbased),
       	ENTRY("ModifyContactPosBased" , CTestProvider :: ModifyContactPosBased),
       	ENTRY("ModifyGroupPosBased" , CTestProvider :: ModifyGroupPosBased),
       	ENTRY("ExportPosBased" , CTestProvider :: ExportPosBased),
       	ENTRY("ImportPosBased" , CTestProvider :: ImportPosBased),        	       	
       	ENTRY("CancelGetList" , CTestProvider :: CancelGetList),   
       	ENTRY("CancelAddContact" , CTestProvider :: CancelAddContact),   
       	ENTRY("CancelOrganiseAdd" , CTestProvider :: CancelOrganiseAdd),
       	ENTRY("CancelDeleteContact" , CTestProvider :: CancelDeleteContact),      	
       	ENTRY("CancelExport" , CTestProvider :: CancelExportL),   
       	ENTRY("CancelImport" , CTestProvider :: CancelImportL),
       	ENTRY("AddContactASyncTest" , CTestProvider :: AddContactASyncTestL),
       	ENTRY("AddGroupASyncTest" , CTestProvider :: AddGroupASyncTestL),
       	ENTRY("GetListNewFieldsTest" , CTestProvider :: GetListNewFieldsTestL)
       	
       	   
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
    
TInt CTestProvider :: HandleNotifyL(TInt aCmdId,
                    	            TInt aEventId,
                    	            CLiwGenericParamList& aEventParamList,
                    	            const CLiwGenericParamList& aInParamList)
                	        	
    {
    
    if (iCancelled != 1)
    	{
    	CActiveScheduler::Stop();
    	iCancelled  = 0;	
    	}
    
    TInt pos = 0;   
    const TLiwGenericParam* param;
    
    param = aEventParamList.FindFirst( pos, KExitCode );    
    
    TLiwVariant err = param->Value();
    
    TInt code = err.AsTInt32();
    
    if(iCase == EModifyContactComplete)
        {
        //call the get list once again to check whether the contact is modified
        CStifItemParser* stiff;
        iCase = EModifyContactVerify;
        //this time call the getlist with the contact id to get only the modified contact
        GetContactALL(*stiff);    
        }
    else if(iCase == EGetAllContacts ||iCase == EDeleteContact 
            || iCase == EOrganizeAddcntid || iCase == EVerifyImport 
            || iCase == EModifyContact || iCase == EModifyContactVerify)
        {   
        
        if (aEventId == KLiwEventCanceled)
        	{
        	iResult = KErrNone;	
        	}
        else
        	{
        	pos = 0;
        TBool tResult = EFalse;
        TBool bResult = EFalse;
        TBool findResult = EFalse;
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
            if(iCase == EDeleteContact)
                {
                *iCntID = ptr;
                break;    
                }
            if(iCase == EOrganizeAddcntid)
                {
                TDesC* ptrtoCntId;
                TInt count = iIdArrayList.Count();
                for(TInt i = 0; i<count ; i++)
                    {
                    ptrtoCntId = iIdArrayList[i];
                    if( *ptrtoCntId == ptr )
                        {
                        findResult = ETrue; 
                        break;   
                        }
                    }
                if(findResult)
                    {
                    findResult = EFalse;
                    continue;    
                    }
                else
                    {
                    *iCntID = ptr; 
                    break;    
                    }                    
                }                        
            if(map->FindL(KFirstName,mapfield))
            mapField = mapfield.AsMap();
            
            TInt count = mapField->Count();            
            mapField->FindL(KFieldValue,firstname);
            firstName = firstname.AsDes();
            if(iCase == EModifyContact )
                {
                if((firstName.CompareF(_L("Arnold")) == 0))
                    {
                    *iCntID=ptr; 
                    break;                     
                    }
                else
                    {
                    continue;    
                    }    
                }
            if(iCase == EModifyContactVerify )
                {
                if((firstName.CompareF(_L("Modified Arnold")) == 0))
                    {
                    iResult = KErrNone; 
                    break;                     
                    }
                else
                    {
                    continue;    
                    }    
                }    
            if(iCase == EVerifyImport )
                {
                if((firstName.CompareF(_L("Monica Bellucci")) == 0) || (firstName.CompareF(_L("Kate Winslet")) == 0))
                    {
                    iResult = KErrNone;
                    break;
                    }
                else
                    {
                    continue;    
                    }        
                }
            if(firstName.CompareF(_L("Johnny")) == 0)       
                {
                tResult = ETrue;    
                }
            if(firstName.CompareF(_L("Arnold")) == 0)       
                {
                bResult = ETrue;    
                }                                                       
            }
            if(tResult && bResult)
                {
                iResult = KErrNone;    
                }
            if( iCase == EDeleteContact )
                {
                iCase = EDeleteVerify;
                }
                
            iterator.Reset();              
                   		
        	}
                         
        }
    else if(iCase == EGetContactSearch)
        {    
        pos = 0;
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
        while(1)
            {
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
                if(firstName.CompareF(_L("Johnny")) == 0)       
                    {
                    iResult = KErrNone;    
                    }    
                }
            else
                {
                break;                    
                }
            }
         
        }
    else if(iCase == EDeleteVerify)
        {
        if (aEventId == KLiwEventCanceled)
        	{
        	iResult = KErrNone;	
        	}
        else if(aEventId == KLiwEventCompleted && code == KErrNone)//KLiwEventCompleted
            {
            iResult = KErrNone;             
            }
        else
            {
            iResult = code;    
            }  
        }
   	 else if(iCase == EGetGroup || iCase ==  EVerifyGroupAdd || iCase ==  EVerifyOrganizeDelete)
        {
        pos = 0;
        
        TBuf<255> groupName;
        TLiwVariant cntId;
        TLiwVariant groupLabel;
        TLiwVariant contents;
        TLiwVariant entry;
        const CLiwMap* map = NULL; 
        const CLiwList* list =NULL;       
               
        param = aEventParamList.FindFirst(pos, KReturnValue);
        TLiwVariant iterator = param->Value();
        CLiwIterable* iter = iterator.AsIterable();   
        while(iter->NextL(entry))         
            {            
            map = entry.AsMap();
            TInt count1 = map->Count(); 
                  
            map->FindL(KGroupId, cntId);                   
            TPtrC ptr = cntId.AsDes();            
            if(map->FindL(KGroupLabel,groupLabel))
                {
                groupName = groupLabel.AsDes();
                iGrpID.Set(ptr);                     
                }
            if(groupName == _L("Test"))
                {
                if(map->FindL(KContents,contents))
                    {
                    iResult = KErrNone;
                    list = contents.AsList();
                    TInt count = list->Count();
                    for(TInt i=0; i<count ; i++)
        				{
        				TLiwVariant cntId;
        				list->AtL(i, cntId) ;
        				TPtrC cntid = cntId.AsDes() ;
        				HBufC* cnt = HBufC::NewL(cntid.Length());
        				*cnt = cntid;
        				iIdArrayList.AppendL(cnt);
        				}                
                                        
                    }
                if(iCase == EVerifyGroupAdd)
                    {
                    TInt count = iIdArrayList.Count();
                    for(TInt i = 0; i<count; i++)
                        {
                        if(*iCntID == *(iIdArrayList[i]))
                            {
                            iResult = KErrNone;
                            break;    
                            }
                        }
                    }
                if(iCase == EVerifyOrganizeDelete)
                    {
                    iResult = KErrNone;
                    TInt count = iIdArrayList.Count();
                    for(TInt i = 0; i<count; i++)
                        {
                        if(*iCntID == *(iIdArrayList[i]))
                            {
                            iResult = KErrGeneral;
                            break;    
                            }
                        }
                    }    
                break;     
                }
                                                                  
            }
            
         
        }        
    else if(iCase == EAddGroup )
        {
        if(aEventId == KLiwEventCompleted && code == KErrNone )
            {
            iResult = KErrNone;    
            }
        }
    else if(iCase == EOrganizeAdd )
        {
        
        if (aEventId == KLiwEventCanceled)
        	{
        	iResult = KErrNone;	
        	}	
        else if(aEventId == KLiwEventCompleted && code == KErrNone )
            {
            iCase = EVerifyGroupAdd;
            CStifItemParser* stiff;
            iIdArrayList.ResetAndDestroy();
            GetGroup(*stiff);            
            }
        else
            {
            iResult = code;    
            }
        }
    else if(iCase == EExportVcard )
        {
        if (aEventId == KLiwEventCanceled)
        	{
        	iResult = KErrNone;	
        	}	
        else if(aEventId == KLiwEventCompleted && code == KErrNone )
            {
            iResult = KErrNone;             
            }
        else
            {
            iResult = code;    
            }        
        }
        
    else if(iCase == EImportVcard)
        {
        if (aEventId == KLiwEventCanceled)
        	{
        	iResult = KErrNone;	
        	}	
         else if(aEventId == KLiwEventCompleted && code == KErrNone )
            {
            iCase = EVerifyImport;
            CStifItemParser* stiff;
            GetContactALL(*stiff);
            }
        else
            {
            iResult = code;    
            }           
        } 
    else if( iCase == EOrganizeDelete )
        {
        if(aEventId == KLiwEventCompleted && code == KErrNone )
            {
            iCase = EVerifyOrganizeDelete;
            CStifItemParser* stiff;
            iIdArrayList.ResetAndDestroy();
            GetGroup(*stiff);
            }
        else
            {
            iResult = code;    
            }     
        }
     else if( iCase == EAddContact )
        {
        if (aEventId == KLiwEventCanceled)
        	{
        	iResult = KErrNone;	
        	}	
        else if(aEventId == KLiwEventCompleted && code == KErrNone )
            {
            iResult = KErrNone;
            }
        else
            {
            iResult = code;    
            }     
        }
     else if(iCase == EAddContactASyncTest || iCase == EAddGroupASyncTest)
         {
         if(aEventId == KLiwEventCompleted && code == KErrNone)
             {
                 TInt pos = 0;   
                 const TLiwGenericParam* param;
                 
                 param = aEventParamList.FindFirst( pos, KReturnValue );    
                 
                 TLiwVariant cntId = param->Value();
                 
                 TPtrC idVal = cntId.AsDes();
                 if(idVal.Compare(KNullDesC) != 0)
                     {
                     iResult = KErrNone;
                     }
                 else
                     {
                     iResult = KErrGeneral;
                     }            
             }
         else
             {
             iResult = code;
             }
         }
     else if(iCase == EGetListNewFieldsTest)
         {
         iResult = KErrNone;
         if(aEventId == KLiwEventCompleted && code == KErrNone)
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
          
          param = aEventParamList.FindFirst(pos, KReturnValue);
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
                      return;
                      }    
                  
                  if(map->FindL(KSecondName,mapfield))
                  mapField = mapfield.AsMap();                
                  count = mapField->Count();
                  mapField->FindL(KFieldValue,secname);
                  secName = secname.AsDes();
                  if(secName.CompareF(_L("Doll")) != 0)       
                      {
                      iResult = KErrGeneral;
                      return;
                      }    
                  
                  if(map->FindL(KCallerObjImg,mapfield))
                    mapField = mapfield.AsMap();                
                    count = mapField->Count();
                    mapField->FindL(KFieldValue,callerobjimg);
                    callerObjImg = callerobjimg.AsDes();
                    if(callerObjImg.CompareF(_L("C:\\data\\images\\pic.jpg")) != 0)       
                        {
                        iResult = KErrGeneral;
                        return;
                        }
                    if(map->FindL(KNote,mapfield))
                    mapField = mapfield.AsMap();                
                    count = mapField->Count();
                    mapField->FindL(KFieldValue,note);
                    Note = note.AsDes();
                    if(Note.CompareF(_L("Lead role in Barbie, the island princess")) != 0)       
                        {
                        iResult = KErrGeneral;
                        return;
                        }
            
                    if(map->FindL(KXSPID,mapfield))
                        mapField = mapfield.AsMap();                
                    //count = mapField->Count();
                    mapField->FindL(KFieldValue,xspidarr);
                    xspid = xspidarr.AsList();
                    for(TInt index =0;index<xspid->Count(); index++)
                        {
                        TLiwVariant xspidVal;
                        if(xspid->AtL(index,xspidVal))
                        {
                        TPtrC ptrVal = xspidVal.AsDes();
                        if(ptrVal.CompareF(_L("Yahoo:Barbie@yahoo.co.in")) != 0 && ptrVal.CompareF(_L("Google:Barbie@gmail.com")) != 0)
                        {
                            iResult = KErrGeneral;
                            return;
                        }
                        }
                    }
              
          }
          }
         else
          {
          iResult = code;
          }
         }
     }

void CTestProvider::LoadService()
    {
    TInt pos = 0;
    iCntID = HBufC::NewL(255);
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

    //__UHEAP_MARK;
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
    //__UHEAP_MARKEND;  
      
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
	
TInt CTestProvider :: GetContactALL(CStifItemParser& /*aItem */)
    {
    AddOneContactL(_L("Arnold"));
    AddOneContactL(_L("Johnny"));
    CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();    
    if(inList && inList->Count())
    	inList->Reset();
    
    //__UHEAP_MARK;    
    iResult = KErrGeneral;
    if(iCase != EOrganizeAddcntid && iCase != EDeleteContact 
    && iCase != EVerifyImport && iCase != EModifyContact && iCase != EModifyContactVerify)
        {
        LoadService(); 
        iCase = EGetAllContacts;   
        }
      
    TInt pos = 0;
    if(iCase == EModifyContactVerify)
        {
        map =  CLiwDefaultMap :: NewL();
        CleanupStack::PushL(map);        
        map->InsertL( KContactId,*iCntID );
        const TLiwGenericParam paramGetlistData(KFilter, TLiwVariant(map));
        inList->AppendL( paramGetlistData ); 
        }       
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));    
    inList->AppendL( paramContentType );    
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);     
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();    
    
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        } 
          
    inList->Reset();    
    outList->Reset(); 
    if(iCase == EModifyContactVerify)
        {        
        CleanupStack::Pop(map);
        map->DecRef();                
        }     
    //__UHEAP_MARKEND;            
    return iResult;
    }


TInt CTestProvider :: GetContactSearch(CStifItemParser& /*aItem */)
    {    
    AddOneContactL(_L("Johnny"));    
    _LIT8(KFilter, "Filter");
    _LIT8(KSearchVal, "SearchVal");
    iResult = KErrGeneral;   
    LoadService(); 
    TInt pos = 0;
    iCase = EGetContactSearch;
      	
    //const TLiwGenericParam paramGetListSortOrder;
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType );
    
    CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();    
    CleanupStack::PushL(map);
    map->InsertL(KSearchVal,_L("j"));
    
    const TLiwGenericParam paramData(KFilter, TLiwVariant(map));    
    inList ->AppendL( paramData );
    
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
        
    if(code == SErrNone)
        {
        CActiveScheduler::Start(); 
        }
    
    CleanupStack::Pop(map);
    map->DecRef(); 
    inList->Reset();
    outList->Reset();   
    return iResult;                   
    }
    
    
TInt CTestProvider :: AddContact(CStifItemParser& /*aItem */)
    {
    
    iResult = KErrGeneral;
    iCase = EAddContact;    
    LoadService();        
        							
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();    
    
    CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();     
    TInt pos = 0;  	          
    fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));
    	
    fieldMap->InsertL(KFieldValue,TLiwVariant(_L("Johnny")));
    //pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    
    
    pMap->InsertL(KContactId, TLiwVariant( _L("")));
    pMap->InsertL(KFirstName, TLiwVariant(fieldMap));
    
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
    pMap->DecRef();
    fieldMap->DecRef();
    fieldMap->DecRef();
    
    inList->Reset();
    outList->Reset(); 
                   
    return iResult;
    }


TInt CTestProvider :: OrganiseAdd(CStifItemParser& /*aItem */)
    {
    CStifItemParser* astiff = NULL;     
 	 
    //LoadService();
    iResult = KErrGeneral;
    iCase = EGetGroup;
    
    GetGroup(*astiff); 
    iCase = EOrganizeAddcntid; 
      
    GetContactALL(*astiff);

    iCase = EOrganizeAdd;
    
   
    //LoadService();							
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    CLiwDefaultList* list = CLiwDefaultList::NewL(); 
    
    list->AppendL(TLiwVariant(*iCntID));
    
    TInt pos = 0;  	          
    
    //pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KGroupId, TLiwVariant(iGrpID));    
    pMap->InsertL(KList, TLiwVariant(list));
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group"))); 
    
    const TLiwGenericParam paramOperationType(KOperationType, TLiwVariant( _L("Associate")));
    const TLiwGenericParam paramOrganizeData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramOperationType );
    inList ->AppendL( paramOrganizeData );  
     
    iIface->ExecuteCmdL(KCmdOrganiseGroups, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }
    
    pMap->DecRef();
    list->DecRef();  
    list->DecRef();
     
    inList->Reset();
    outList->Reset(); 
    return iResult;
    }

TInt CTestProvider :: OrganiseDelete(CStifItemParser& /*aItem */)
    {
    CStifItemParser* astiff = NULL ;     
 	 
    //LoadService();
    iResult = KErrGeneral;
    iCase = EGetGroup;
    
    GetGroup(*astiff); 
    iCase = EOrganizeDelete; 
      
        
   
    //LoadService();							
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    CLiwDefaultList* list = CLiwDefaultList::NewL(); 
    if(iIdArrayList.Count()>0)
    *iCntID = *iIdArrayList[0];
    
    list->AppendL(TLiwVariant(*iCntID));
    
    TInt pos = 0;  	          
    
    //pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KGroupId, TLiwVariant(iGrpID));    
    pMap->InsertL(KList, TLiwVariant(list));
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group"))); 
    
    const TLiwGenericParam paramOperationType(KOperationType, TLiwVariant(KDissociate));
    const TLiwGenericParam paramOrganizeData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramOperationType );
    inList ->AppendL( paramOrganizeData );  
     
    iIface->ExecuteCmdL(KCmdOrganiseGroups, *inList, *outList, KLiwOptASyncronous, this);
        
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
    return iResult;
    }


TInt CTestProvider :: ModifyContact(CStifItemParser& aItem )
    {
    /**The testing logic goes this way first load the contact service.
      *Then,get one contact id by using getlist api, this call GetContactALL(aItem); does that.
      *change the first name and add it again(do operatoin for edit).
      *call the getlist api using the same contact id this time.
      *check for the changed first name.
      */    
    //load the service
    LoadService();
    iCase = EModifyContact;
    //get the contact to be modified the contact is retrieved in the callback HandleNotifyL
    GetContactALL(aItem); 
    //get the contact to be modified the contact is retrieved in the callback HandleNotifyL    
    iResult = KErrGeneral;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    
    CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();     
    TInt pos = 0;  	          
    fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));
    	
    fieldMap->InsertL(KFieldValue,TLiwVariant(_L("Modified Arnold")));
    //pMap->InsertL(KDBUri, TLiwVariant( _L("")));
    
    
    pMap->InsertL(KContactId, TLiwVariant(iCntID));
    pMap->InsertL(KFirstName, TLiwVariant(fieldMap));
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap)); ;
        
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData ); 
    
     
    iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    //change the case to verify the operation.
    iCase = EModifyContactComplete;       
    if(code == SErrNone)
        {        
        CActiveScheduler::Start();  
        }           
    pMap->DecRef();
    fieldMap->DecRef();
    fieldMap->DecRef();
    
    inList->Reset();
    outList->Reset(); 
                   
    return iResult;   
    }
    
    

TInt CTestProvider :: GetGroup(CStifItemParser & /*aItem */)
    {
    AddOneGroupL(_L("Test"));
    iResult = KErrGeneral;
    iIdArrayList.ResetAndDestroy();
    if(iCase != EVerifyGroupAdd && iCase != EVerifyOrganizeDelete)
        {
        LoadService(); 
        iCase = EGetGroup;   
        }
      
    TInt pos = 0;      	    
	inList->Reset();
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group")));    
    inList ->AppendL( paramContentType );
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    if(code == SErrNone)
        {
        CActiveScheduler::Start();   
        }       
    return iResult;        
    }


TInt CTestProvider :: GetDatabase(CStifItemParser& /*aItem*/)
	{
	iResult = KErrGeneral;
	LoadService();  
    TInt pos = 0;
    iCase = EGetDatabase;  	    
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Database")));    
    inList ->AppendL( paramContentType );
    
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
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
            iResult = KErrNone;
            break;    
            }
          
        }
   
    
    inList->Reset();
    outList->Reset();
     
    return iResult ;            
    }
 
TInt CTestProvider :: ModifyGroup(CStifItemParser& /*aItem*/)
	{
    }

TInt CTestProvider :: ExportL( CStifItemParser& aItem )
	{
	iCase = EDeleteContact;
	
	iResult = KErrGeneral;
	LoadService();          
    GetContactALL(aItem);
    
    iCase =  EExportVcard;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
    
    TInt ferr = iFileHandle.Open(iFSession,_L("c:\\vcardExport.vcf"),EFileRead | EFileWrite );
	
	if( KErrNone == ferr )
		{
		iFileHandle.Close();

		iFSession.Delete(_L("c:\\vcardExport.vcf"));
		}    
    TInt pos = 0;  	          
    TBuf<255> cntIdunicode;
    cntIdunicode.Copy(*iCntID);
    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KContactId, TLiwVariant(cntIdunicode));
    
    pMap->InsertL(KDestFileNameParam, TLiwVariant( _L("c:\\vcardExport.vcf")));    
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData ); 
      
    iIface->ExecuteCmdL(KCmdExport, *inList, *outList, KLiwOptASyncronous, this);
        
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
    return iResult;
	
	
    }
TInt CTestProvider :: ImportL(CStifItemParser& /*aItem*/)
	{		
	iResult = KErrGeneral;
	LoadService();              
    iCase =  EImportVcard;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
        
    TInt pos = 0;  	          
    
    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));    
    
    pMap->InsertL(KSourceFileNameParam, TLiwVariant( _L("c:\\vcardimport.vcf")));    
    
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
    return iResult;
    }
    
TInt CTestProvider :: DeleteContact(CStifItemParser& /*aItem*/)
	{
	iCase = EDeleteContact;
	LoadService();  
    TInt pos = 0;
    CLiwMap* mapContactId = CLiwDefaultMap::NewL();
    //iCase = EGetAllContacts;  	
    //const TLiwGenericParam paramGetListSortOrder;
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType );
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    if(code == SErrNone)
        {
        CActiveScheduler::Start(); 
        }
    const TLiwGenericParam paramContent(KType, TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContent );
    CLiwDefaultList* list = CLiwDefaultList :: NewL();    
    list->AppendL(TLiwVariant(*iCntID));
    mapContactId->InsertL(KDBUri, TLiwVariant(_L("cntdb://c:contacts.cdb")));
    mapContactId->InsertL(KList,TLiwVariant(list));
    const TLiwGenericParam paramDeleteData(KData, TLiwVariant(mapContactId));
    inList ->AppendL( paramDeleteData ); 
    iIface->ExecuteCmdL(KCmdDelete, *inList, *outList, KLiwOptASyncronous, this);
    
    pos = 0;
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
    return iResult;         	
    }

/*
 * This is a manual test case were the service was available when the 
 * request was made and then   Lost the service (Contact to location servier lost
 */
 
  
TInt CTestProvider :: AddGroup(CStifItemParser& /*aItem*/)
    {           
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
    iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    if(code == SErrNone)
        {
        CActiveScheduler::Start();  
        }
    pMap->DecRef();    
    return iResult;	
    }


/**
 *Cancel test, to test cancel functionality
 */
TInt CTestProvider :: GetContactALLPosBased(CStifItemParser& /*aItem*/)
    {
    AddOneContactL(_L("Arnold"));
    AddOneContactL(_L("Johnny"));
    iResult = KErrGeneral;
    if(iCase != EOrganizeAddcntid && iCase != EDeleteContact && iCase != EVerifyImport)
        {
        LoadService(); 
        iCase = EGetAllContacts;   
        }
      
    TInt pos = 0;
      	
    //const TLiwGenericParam paramGetListSortOrder;
    
    const TLiwGenericParam paramContentType(_L8(""), TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType );
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();

    if(code == SErrNone)
        {
        CActiveScheduler::Start();  
        }
    inList->Reset();
    outList->Reset();
        
    return iResult;
    }
    	  
TInt CTestProvider :: GetContactSearchPosBased(CStifItemParser& /*aItem*/)
    {    
    AddOneContactL(_L("Johnny"));
   _LIT8(KFilter, "Filter");
    _LIT8(KSearchVal, "SearchVal");
    iResult = KErrGeneral;   
    LoadService(); 
    TInt pos = 0;
    iCase = EGetContactSearch;
      	
    //const TLiwGenericParam paramGetListSortOrder;
    
    const TLiwGenericParam paramContentType(_L8(""), TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType );
    
    CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();    
    CleanupStack::PushL(map);
    map->InsertL(KSearchVal,_L("j"));
    									 
    const TLiwGenericParam paramData(_L8(""), TLiwVariant(map));    
    inList ->AppendL( paramData );
    TInt count = inList->Count();
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
        
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }
    inList->Reset();
    outList->Reset();
    CleanupStack::Pop(map);
    map->DecRef();
    return iResult;     
    }	  
/**
 *Cancel test, to test cancel functionality
 */
TInt CTestProvider :: GetGroupPosBased(CStifItemParser& /*aItem*/)
    {
    AddOneGroupL(_L("Test"));
    iResult = KErrGeneral;
    if(iCase != EVerifyGroupAdd && iCase != EVerifyOrganizeDelete)
        {
        LoadService(); 
        iCase = EGetGroup;   
        }
      
    TInt pos = 0;      	    
    
    const TLiwGenericParam paramContentType(_L8(""), TLiwVariant( _L("Group")));    
    inList ->AppendL( paramContentType );
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    if(code == SErrNone)
        {
        CActiveScheduler::Start(); 
        }       
    return iResult;   
    }

/**
 *Cancel test, with wrong notification
 */
TInt CTestProvider :: GetDatabasePosBased(CStifItemParser& /*aItem*/)
    {
    iResult = KErrGeneral;
    LoadService();  
    TInt pos = 0;
    iCase = EGetDatabase;  	    
    
    const TLiwGenericParam paramContentType(_L8(""), TLiwVariant( _L("Database")));    
    inList ->AppendL( paramContentType );
    
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
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
            iResult = KErrNone;
            break;    
            }
          
        }
    
    inList->Reset();
    outList->Reset();
     
    return iResult ; 
   	
    }



/**
 *Cancel test, with wrong notification issues a Trace request and then calls for getlocation 
 * cancellation
 */
TInt CTestProvider :: AddContactPosBased(CStifItemParser& /*aItem*/)
    {
    iResult = KErrGeneral;
    iCase = EAddContact;    
    LoadService();							
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL(); 
    TInt pos = 0;  	          
    fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));	
    fieldMap->InsertL(KFieldValue,TLiwVariant(_L("Arnold")));
    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    
    pMap->InsertL(KContactId, TLiwVariant( _L("")));
    pMap->InsertL(KFirstName, TLiwVariant(fieldMap));
    
    const TLiwGenericParam paramContentType(_L8(""), TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(_L8(""), TLiwVariant(pMap)); ;
       
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
    inList->Reset();
    outList->Reset(); 
    pMap->DecRef();
    fieldMap->DecRef();   
    return iResult;	
    }


TInt CTestProvider :: AddGroupPosBased(CStifItemParser& /*aItem*/)
    {
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
    iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }
    pMap->DecRef();     
    return iResult;
    }
    
/**
 *Cancel test, Normal cancel test for getlocation 
 */
TInt CTestProvider :: DeleteContactPosBased(CStifItemParser& /*aItem*/)
    {	
	iCase = EDeleteContact;
	LoadService();  
    TInt pos = 0;
    CLiwMap* mapContactId = CLiwDefaultMap::NewL();
    //iCase = EGetAllContacts;  	
    //const TLiwGenericParam paramGetListSortOrder;
    
    const TLiwGenericParam paramContentType(_L8(""), TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType );
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    if(code == SErrNone)
        {
        CActiveScheduler::Start();    
        }
    const TLiwGenericParam paramContent(_L8(""), TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContent );
    CLiwDefaultList* list = CLiwDefaultList :: NewL();    
    list->AppendL(TLiwVariant(*iCntID));
    mapContactId->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    mapContactId->InsertL(KList,TLiwVariant(list));
    const TLiwGenericParam paramDeleteData(_L8(""), TLiwVariant(mapContactId));
    inList ->AppendL( paramDeleteData );
     
    iIface->ExecuteCmdL(KCmdDelete, *inList, *outList, KLiwOptASyncronous, this);
    
    pos = 0;
    param = outList->FindFirst( pos, KExitCode );
    err = param->Value();
    code = err.AsTInt32();
            
    if(code == SErrNone)
        {
        CActiveScheduler::Start();   
        }       	
    mapContactId->DecRef();
    inList->Reset();
    outList->Reset();
    list->DecRef();
    return iResult;
    }
    
/**
 * GetLocation Timeout
 */
TInt CTestProvider :: OrganiseAddPosBased(CStifItemParser& /*aItem*/)
    {
     AddOneContactL(_L("Arnold"));
     AddOneContactL(_L("Johnny"));
     
     AddOneGroupL(_L("Test"));
     
     CStifItemParser* astiff = NULL ;     
 	 
    //LoadService();
    iResult = KErrGeneral;
    iCase = EGetGroup;
    
    GetGroup(*astiff); 
    iCase = EOrganizeAddcntid; 
      
    GetContactALL(*astiff);

    iCase = EOrganizeAdd;
    
   
    //LoadService();							
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    CLiwDefaultList* list = CLiwDefaultList::NewL(); 
    
    list->AppendL(TLiwVariant(*iCntID));
    
    TInt pos = 0;  	          
    
    //pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KGroupId, TLiwVariant(iGrpID));    
    pMap->InsertL(KList, TLiwVariant(list));
    
    const TLiwGenericParam paramContentType(_L8(""), TLiwVariant( _L("Group"))); 
    
    const TLiwGenericParam paramOperationType(_L8(""), TLiwVariant( _L("Associate")));
    const TLiwGenericParam paramOrganizeData(_L8(""), TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramOrganizeData );
    inList ->AppendL( paramOperationType );
      
     
    iIface->ExecuteCmdL(KCmdOrganiseGroups, *inList, *outList, KLiwOptASyncronous, this);
     
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();  
        }    
    pMap->DecRef();
    list->DecRef();
    list->DecRef();
    
    inList->Reset();
    outList->Reset();    
    return iResult;    
    }

/**
 *Normal Trace cancell test.
 */
TInt CTestProvider :: OrganiseDeletePosbased(CStifItemParser& /*aItem*/)
    {
     AddOneGroupL(_L("Test"));
     CStifItemParser* astiff = NULL ;     
 	 
    //LoadService();
    iResult = KErrGeneral;
    iCase = EGetGroup;
    
    GetGroup(*astiff); 
    iCase = EOrganizeDelete; 
      
        
   
    //LoadService();							
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    CLiwDefaultList* list = CLiwDefaultList::NewL(); 
    if(iIdArrayList.Count()>0)
    *iCntID = *iIdArrayList[0];
    
    list->AppendL(TLiwVariant(*iCntID));
    
    TInt pos = 0;  	          
    
    //pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KGroupId, TLiwVariant(iGrpID));    
    pMap->InsertL(KList, TLiwVariant(list));
    
    const TLiwGenericParam paramContentType(_L8(""), TLiwVariant( _L("Group"))); 
    
    const TLiwGenericParam paramOperationType(_L8(""), TLiwVariant(KDissociate));
    const TLiwGenericParam paramOrganizeData(_L8(""), TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramOrganizeData );
    inList ->AppendL( paramOperationType );
      
     
    iIface->ExecuteCmdL(KCmdOrganiseGroups, *inList, *outList, KLiwOptASyncronous, this);
        
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
    list->DecRef();   
    return iResult;   
    }

/**
 *Math Operation Find distance : Position based parameter
 */
 TInt CTestProvider :: ModifyContactPosBased(CStifItemParser& /*aItem*/)
     {
     	
     }
/**
 * Math operation BearingTo Test
 */
 
 TInt CTestProvider ::ModifyGroupPosBased(CStifItemParser& /*aItem*/) 
    {
    }
    
 TInt CTestProvider :: ExportPosBased(CStifItemParser& aItem)
     {
     AddOneContactL(_L("Arnold"));
     AddOneContactL(_L("Johnny"));
     iCase = EDeleteContact;
	
    iResult = KErrGeneral;
    LoadService();          
    GetContactALL(aItem);

    TInt ferr = iFileHandle.Open(iFSession,_L("c:\\vcardExportposbased.vcf"),EFileRead | EFileWrite );
	
	if( KErrNone == ferr )
		{
		iFileHandle.Close();

		iFSession.Delete(_L("c:\\vcardExportposbased.vcf"));
		}  
		
    iCase =  EExportVcard;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
        
    TInt pos = 0;  	          

    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KContactId, TLiwVariant(*iCntID));

    pMap->InsertL(KDestFileNameParam, TLiwVariant( _L("c:\\vcardExportposbased.vcf")));    

    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData ); 
      
    iIface->ExecuteCmdL(KCmdExport, *inList, *outList, KLiwOptASyncronous, this);
        
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
    return iResult;	
    }
/**
 * Math operation BearingTo Test
 */
 
 TInt CTestProvider ::ImportPosBased(CStifItemParser& /*aItem*/) 
    {
    iIdArrayList.ResetAndDestroy();
    iResult = KErrGeneral;
	LoadService();              
    iCase =  EImportVcard;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
        
    TInt pos = 0;  	          
    
    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));    
    
    pMap->InsertL(KSourceFileNameParam, TLiwVariant( _L("c:\\vcardimport.vcf")));    
    
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
    return iResult;
	
	
    }
 
     
     
TInt CTestProvider ::CancelGetList(CStifItemParser& /*aItem*/) 
	{
	AddOneContactL(_L("Arnold"));
    AddOneContactL(_L("Johnny"));
    iResult = KErrGeneral;
    if(iCase != EOrganizeAddcntid && iCase != EDeleteContact && iCase != EVerifyImport)
        {
        LoadService(); 
        iCase = EGetAllContacts;   
        }
      
    TInt pos = 0;
      	
    //const TLiwGenericParam paramGetListSortOrder;
    
    const TLiwGenericParam paramContentType(_L8(""), TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType );
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
     
   
       
  //  const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    //TLiwVariant err = param->Value();
    //TInt code = err.AsTInt32();

   // if(code == SErrNone)
        
    const TLiwGenericParam* param = outList->FindFirst(pos, KTransactionID);
    
    inList->Reset(); 
    outList->Reset();
    
    if (param)
    	{
    	TInt32 transid =  param->Value().AsTInt32();
    
        TLiwGenericParam paramtransactionId(KTransactionID, TLiwVariant(transid));
	
		
		inList->AppendL( paramtransactionId );    
		
		iCancelled = 1;
		iIface->ExecuteCmdL(KCancel, *inList, *outList,KLiwOptCancel, this);
		paramtransactionId.Reset();		

		
		inList->Reset();
		outList->Reset();
		
   //     CActiveScheduler::Start(); 	
        	
          
        }
    inList->Reset();
    outList->Reset();
        
    return iResult;
	}
	

TInt CTestProvider ::CancelAddContact(CStifItemParser& /*aItem*/) 
	{
//	iResult = KErrNone;
    iCase = EAddContact;    
    LoadService();        
        							
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();    
    
    CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();     
    TInt pos = 0;  	          
    fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));
    	
    fieldMap->InsertL(KFieldValue,TLiwVariant(_L("Johnny")));
    //pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    
    
    pMap->InsertL(KContactId, TLiwVariant( _L("")));
    pMap->InsertL(KFirstName, TLiwVariant(fieldMap));
    
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
        pos = 0;
        param = outList->FindFirst(pos, KTransactionID);
    	if (param)
    		{
    		inList->Reset(); 
		    outList->Reset();
	    
	        TInt32 transid =  param->Value().AsTInt32();
	    
	        TLiwGenericParam paramtransactionId(KTransactionID, TLiwVariant(transid));
		
			
			inList->AppendL( paramtransactionId );    
			
			iCancelled = 1;
			iIface->ExecuteCmdL(KCancel, *inList, *outList,KLiwOptCancel, this);
			paramtransactionId.Reset();		

			
			inList->Reset();
			outList->Reset();	
    		}
    	else
    		{
    			
    		}
        }           
    pMap->DecRef();
    fieldMap->DecRef();
    fieldMap->DecRef();
    
    inList->Reset();
    outList->Reset(); 
                   
    return iResult;
	}
	
	
	
 TInt CTestProvider :: CancelOrganiseAdd(CStifItemParser& /*aItem */)
    {
    CStifItemParser* astiff = NULL;     
 	 
    //LoadService();
    iResult = KErrGeneral;
    iCase = EGetGroup;
    
    GetGroup(*astiff); 
    iCase = EOrganizeAddcntid; 
      
    GetContactALL(*astiff);

    iCase = EOrganizeAdd;
    
   
    //LoadService();							
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    CLiwDefaultList* list = CLiwDefaultList::NewL(); 
    
    list->AppendL(TLiwVariant(*iCntID));
    
    TInt pos = 0;  	          
    
    //pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KGroupId, TLiwVariant(iGrpID));    
    pMap->InsertL(KList, TLiwVariant(list));
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group"))); 
    
    const TLiwGenericParam paramOperationType(KOperationType, TLiwVariant( _L("Associate")));
    const TLiwGenericParam paramOrganizeData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramOperationType );
    inList ->AppendL( paramOrganizeData );  
     
    iIface->ExecuteCmdL(KCmdOrganiseGroups, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        pos = 0;
         param = outList->FindFirst(pos, KTransactionID);
        if (param)
    		{
    		inList->Reset(); 
		    outList->Reset();
	    
	        TInt32 transid =  param->Value().AsTInt32();
	    
	        TLiwGenericParam paramtransactionId(KTransactionID, TLiwVariant(transid));
		
			
			inList->AppendL( paramtransactionId );    
			
			iCancelled = 1;
			iIface->ExecuteCmdL(KCancel, *inList, *outList,KLiwOptCancel, this);
			
			paramtransactionId.Reset();		

			
			inList->Reset();
			outList->Reset();	
    		}
    	else
    		{
    			
    		} 
        }
    
    pMap->DecRef();
    list->DecRef();  
    list->DecRef();
     
    inList->Reset();
    outList->Reset(); 
    return iResult;
    }

TInt CTestProvider :: CancelExportL( CStifItemParser& aItem )
	{
	iCase = EDeleteContact;
	
	iResult = KErrGeneral;
	LoadService();          
    GetContactALL(aItem);
    
    iCase =  EExportVcard;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
    
    TInt ferr = iFileHandle.Open(iFSession,_L("c:\\vcardExport.vcf"),EFileRead | EFileWrite );
	
	if( KErrNone == ferr )
		{
		iFileHandle.Close();

		iFSession.Delete(_L("c:\\vcardExport.vcf"));
		}    
    TInt pos = 0;  	          
    TBuf<255> cntIdunicode;
    cntIdunicode.Copy(*iCntID);
    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KContactId, TLiwVariant(cntIdunicode));
    
    pMap->InsertL(KDestFileNameParam, TLiwVariant( _L("c:\\vcardExport.vcf")));    
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap));
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData ); 
      
    iIface->ExecuteCmdL(KCmdExport, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        pos = 0;
        param = outList->FindFirst(pos, KTransactionID);
        if (param)
    		{
    		inList->Reset(); 
		    outList->Reset();
	    
	        TInt32 transid =  param->Value().AsTInt32();
	    
	        TLiwGenericParam paramtransactionId(KTransactionID, TLiwVariant(transid));
		
			
			inList->AppendL( paramtransactionId );    
			
			iCancelled = 1;
			iIface->ExecuteCmdL(KCancel, *inList, *outList,KLiwOptCancel, this);
			
			paramtransactionId.Reset();		

			
			inList->Reset();
			outList->Reset();	
    		}
    	else
    		{
    			
    		} 
        }
    inList->Reset();
    outList->Reset();
    pMap->DecRef();    
    return iResult;
	
	
    }

TInt CTestProvider :: CancelImportL(CStifItemParser& /*aItem*/)
	{		
	iResult = KErrGeneral;
	LoadService();              
    iCase =  EImportVcard;
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();
        
    TInt pos = 0;  	          
    
    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));    
    
    pMap->InsertL(KSourceFileNameParam, TLiwVariant( _L("c:\\vcardimport.vcf")));    
    
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
        pos = 0;
        param = outList->FindFirst(pos, KTransactionID);
        if (param)
    		{
    		inList->Reset(); 
		    outList->Reset();
	    
	        TInt32 transid =  param->Value().AsTInt32();
	    
	        TLiwGenericParam paramtransactionId(KTransactionID, TLiwVariant(transid));
		
			
			inList->AppendL( paramtransactionId );    
			
			iCancelled = 1;
			iIface->ExecuteCmdL(KCancel, *inList, *outList,KLiwOptCancel, this);
			
			paramtransactionId.Reset();		

			
			inList->Reset();
			outList->Reset();	
    		}
    	else
    		{
    			
    		} 
        }
    inList->Reset();
    outList->Reset();
    pMap->DecRef();    
    return iResult;
    }
    
    
    
    
TInt CTestProvider :: CancelDeleteContact(CStifItemParser& /*aItem*/)
	{
	iCase = EDeleteContact;
	LoadService();  
    TInt pos = 0;
    CLiwMap* mapContactId = CLiwDefaultMap::NewL();
    //iCase = EGetAllContacts;  	
    //const TLiwGenericParam paramGetListSortOrder;
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType );
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    if(code == SErrNone)
        {
        CActiveScheduler::Start(); 
        }
    const TLiwGenericParam paramContent(KType, TLiwVariant( _L("Contact")));
    inList ->AppendL( paramContent );
    CLiwDefaultList* list = CLiwDefaultList :: NewL();    
    list->AppendL(TLiwVariant(*iCntID));
    mapContactId->InsertL(KDBUri, TLiwVariant(_L("cntdb://c:contacts.cdb")));
    mapContactId->InsertL(KList,TLiwVariant(list));
    const TLiwGenericParam paramDeleteData(KData, TLiwVariant(mapContactId));
    inList ->AppendL( paramDeleteData ); 
    iIface->ExecuteCmdL(KCmdDelete, *inList, *outList, KLiwOptASyncronous, this);
    
    
    pos = 0;
    
    param = outList->FindFirst( pos, KExitCode );
    err = param->Value();
    code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        pos = 0;
        param = outList->FindFirst(pos, KTransactionID);
        if (param)
    		{
    		inList->Reset(); 
		    outList->Reset();
	    
	        TInt32 transid =  param->Value().AsTInt32();
	    
	        TLiwGenericParam paramtransactionId(KTransactionID, TLiwVariant(transid));
		
			
			inList->AppendL( paramtransactionId );    
			
			iCancelled = 1;
			iIface->ExecuteCmdL(KCancel, *inList, *outList,KLiwOptCancel, this);
			
			paramtransactionId.Reset();		

			
			inList->Reset();
			outList->Reset();	
    		}
    	else
    		{
    			
    		} 
        } 
    inList->Reset();
    outList->Reset();
    mapContactId->DecRef();
    list->DecRef(); 
    return iResult;         	
    }
    
    


TInt CTestProvider :: AddContactASyncTestL(CStifItemParser& /*aItem */)
    {
    
    iResult = KErrGeneral;
    iCase = EAddContactASyncTest;    
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
     
    iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
           
    if(code == SErrNone)
        {
        CActiveScheduler::Start();   
        }           
    pMap->DecRef();
    fieldMap->DecRef();
    fieldMap->DecRef();
    
    inList->Reset();
    outList->Reset(); 
                   
    return iResult;
    }


TInt CTestProvider :: AddGroupASyncTestL(CStifItemParser& /*aItem*/)
    {           
    LoadService();                          
    CLiwDefaultMap* pMap = CLiwDefaultMap::NewL(); 
    iCase = EAddGroupASyncTest;
    TInt pos = 0;                 
    
    pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    pMap->InsertL(KGroupId, TLiwVariant(_L8("")));
    pMap->InsertL(KGroupLabel, TLiwVariant(_L("TestAddGroup")));
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Group"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap)); ;
       
    inList ->AppendL( paramContentType );
    inList ->AppendL( paramAddData );   
    iIface->ExecuteCmdL(KCmdAdd, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
    
    inList->Reset();
    outList->Reset();
    
    if(code == SErrNone)
        {
        CActiveScheduler::Start();  
        }
    pMap->DecRef();    
    return iResult; 
    }
TInt CTestProvider :: AddOneContactNewFieldsL()
    {
    //LoadService();        
                                    
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

    
TInt CTestProvider :: GetListNewFieldsTestL(CStifItemParser& /*aItem */)
    {    
    LoadService(); 
    TInt addRes = AddOneContactNewFieldsL();
    if(addRes != KErrNone)
        {
        return KErrGeneral;
        }
    
    _LIT8(KFilter, "Filter");
    _LIT8(KSearchVal, "SearchVal");
    iResult = KErrGeneral;   
    
    TInt pos = 0;
    iCase = EGetListNewFieldsTest;
        
    //const TLiwGenericParam paramGetListSortOrder;
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact")));    
    inList ->AppendL( paramContentType );
    
    CLiwDefaultMap* map =  CLiwDefaultMap :: NewL();    
    CleanupStack::PushL(map);
    map->InsertL(KSearchVal,_L("Barbie"));
    
    const TLiwGenericParam paramData(KFilter, TLiwVariant(map));    
    inList ->AppendL( paramData );
    
    iIface->ExecuteCmdL(KCmdGetList, *inList, *outList, KLiwOptASyncronous, this);
        
    const TLiwGenericParam* param = outList->FindFirst( pos, KExitCode );
    TLiwVariant err = param->Value();
    TInt code = err.AsTInt32();
        
    if(code == SErrNone)
        {
        CActiveScheduler::Start(); 
        }
    
    CleanupStack::Pop(map);
    map->DecRef(); 
    inList->Reset();
    outList->Reset();   
    return iResult;                   
    }
