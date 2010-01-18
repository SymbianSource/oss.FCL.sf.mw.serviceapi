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
* Description:  Provides interface between the AIW FrameWork and Service Provider.
*
*/

#include <liwvariant.h>
#include <liwgenericparam.h>
#include <liwcommon.h>

#include <CVPbkContactLinkArray.h>
#include <CVPbkContactStoreUriArray.h>
#include <CVPbkContactManager.h>
#include <MVPbkContactStoreList.h>
#include <TVPbkContactStoreUriPtr.h>
#include <MVPbkContactLink.h>

#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>
#include <e32svr.h>

// User Includes
#include "contactservice.h"
#include "contactinterface.h"
#include "contactinterfacecallback.h"
#include "searchfields.h"
#include "contactservice.hrh"
#include "contacterrormessage.hrh"
#include "../../inc/serviceerrno.h"
#include "contactsmaxlength.h"
#include <centralrepository.h>
using namespace LIW;

#define KMissingArg -100

/*
-----------------------------------------------------------------------------
    CContactInterface::CContactInterface()
    Description    : Constructor
    Return values  : N/A
-----------------------------------------------------------------------------
*/
CContactInterface::CContactInterface()
                : iContactService( NULL ),
                  iErrorMess(NULL),
                  iDburi(NULL)
    {
    }

/*
-----------------------------------------------------------------------------
    void CContactInterface::ConstructL()
    Description         : Symbian 2nd phase constructor can leave.
    Return values       : N/A
-----------------------------------------------------------------------------
*/
void CContactInterface::ConstructL()
    {
    iContactService = CContactService::NewL();    
	iErrorMess = HBufC::NewL(250);    
	iRepository = CRepository::NewL( TUid::Uid(KCRUidPhonebookStoreConfiguration) );
    }
/*
-----------------------------------------------------------------------------
    CContactInterface* CContactInterface::NewL()
    Description                       : Two-phased constructor.
    Return values                     : CContactInterface object pointer

-----------------------------------------------------------------------------
*/
EXPORT_C CContactInterface* CContactInterface::NewL()
    {
    CContactInterface* self = new ( ELeave ) CContactInterface();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
/*
-----------------------------------------------------------------------------
    CContactInterface::~CContactInterface()
    Description     : Destructor, free allocated resources
    Return values   : N/A
-----------------------------------------------------------------------------
*/
CContactInterface::~CContactInterface()
    {
    delete iContactService;
    delete iErrorMess;
    delete iDburi;
    delete iRepository;
    iCallbackMap.ResetAndDestroy();
    iCallbackMap.Close();		
    }
    
/*
-----------------------------------------------------------------------------
    CContactInterface::GetFieldMaxLength()
    Description     : Gets the max length of the field.
    Return values   : MaxLength
-----------------------------------------------------------------------------
*/    
    
TInt CContactInterface :: GetFieldMaxLength(TInt aFieldKeyID, TDesC& aDbUri)
    {
    TInt fieldmaxlength = -1;
    switch(aFieldKeyID)
        {
            case R_VPBK_FIELD_TYPE_LASTNAME     :
            case R_VPBK_FIELD_TYPE_FIRSTNAME    :
            case R_VPBK_FIELD_TYPE_SECONDNAME   :
            case R_VPBK_FIELD_TYPE_DEPARTMENT   :
            case R_VPBK_FIELD_TYPE_JOBTITLE	    : 
        	case R_VPBK_FIELD_TYPE_ASSTNAME    	:
            case R_VPBK_FIELD_TYPE_ASSTPHONE    :
        	case R_VPBK_FIELD_TYPE_SPOUSE		:
            case R_VPBK_FIELD_TYPE_CHILDREN	    :
            case R_VPBK_FIELD_TYPE_COMPANYNAME  :
            case R_VPBK_FIELD_TYPE_MIDDLENAME   :           
            case R_VPBK_FIELD_TYPE_ADDRSTREETGEN:
            case R_VPBK_FIELD_TYPE_ADDRSTREETHOME:
            case R_VPBK_FIELD_TYPE_ADDRSTREETWORK:
            case R_VPBK_FIELD_TYPE_ADDRLOCALGEN	:
            case R_VPBK_FIELD_TYPE_ADDRLOCALHOME:
            case R_VPBK_FIELD_TYPE_ADDRLOCALWORK:
            case R_VPBK_FIELD_TYPE_ADDRREGIONGEN:
            case R_VPBK_FIELD_TYPE_ADDRREGIONHOME:
            case R_VPBK_FIELD_TYPE_ADDRREGIONWORK:            
            case R_VPBK_FIELD_TYPE_ADDRCOUNTRYGEN:
            case R_VPBK_FIELD_TYPE_ADDRCOUNTRYHOME:
            case R_VPBK_FIELD_TYPE_ADDRCOUNTRYWORK:
        	case R_VPBK_FIELD_TYPE_ADDREXTGEN:
        	case R_VPBK_FIELD_TYPE_ADDREXTHOME:
        	case R_VPBK_FIELD_TYPE_ADDREXTWORK:            
                {
                // a very bad fix for sim case 
                if(aFieldKeyID == R_VPBK_FIELD_TYPE_LASTNAME && (aDbUri.CompareF(KSimDataBaseOne) == 0))
                    {
                    //comparing the database uri for sim and setting the length
                    fieldmaxlength = KMaLengthFourteen;                        
                    }
                else
                    {
                    fieldmaxlength = KMaxLengthFifty;     
                    }                                                    
                break;
                }
                
           case R_VPBK_FIELD_TYPE_MOBILEPHONEGEN  :
           case R_VPBK_FIELD_TYPE_MOBILEPHONEHOME :
           case R_VPBK_FIELD_TYPE_MOBILEPHONEWORK :
           case R_VPBK_FIELD_TYPE_LANDPHONEGEN	  :
           case R_VPBK_FIELD_TYPE_LANDPHONEHOME	  :
           case R_VPBK_FIELD_TYPE_LANDPHONEWORK   :
           case R_VPBK_FIELD_TYPE_VIDEONUMBERHOME :
           case R_VPBK_FIELD_TYPE_VIDEONUMBERWORK :
           case R_VPBK_FIELD_TYPE_VIDEONUMBERGEN  :
           case R_VPBK_FIELD_TYPE_CARPHONE		  :
           case R_VPBK_FIELD_TYPE_PAGERNUMBER	  :
           case R_VPBK_FIELD_TYPE_FAXNUMBERHOME   :
           case R_VPBK_FIELD_TYPE_FAXNUMBERWORK   :
           case R_VPBK_FIELD_TYPE_FAXNUMBERGEN	  :
               {
               fieldmaxlength = KMaxLengthFourtyEight;
               break;
               }
          case R_VPBK_FIELD_TYPE_ADDRPOGEN		  :
          case R_VPBK_FIELD_TYPE_ADDRPOHOME		  :
          case R_VPBK_FIELD_TYPE_ADDRPOWORK		  :
          case R_VPBK_FIELD_TYPE_ADDRPOSTCODEGEN  :
          case R_VPBK_FIELD_TYPE_ADDRPOSTCODEHOME :
          case R_VPBK_FIELD_TYPE_ADDRPOSTCODEWORK : 
              {
              fieldmaxlength = KMaxLengthTwenty; 
              break; 
              }
          case R_VPBK_FIELD_TYPE_PREFIX:
          case R_VPBK_FIELD_TYPE_SUFFIX:
              {
              fieldmaxlength = KMaxLengthTen;
              break;
              }
          
          case R_VPBK_FIELD_TYPE_DTMFSTRING:
              {
              fieldmaxlength =  KMaxLengthSixty;
              break;
              }
          
          case R_VPBK_FIELD_TYPE_SIP:
          case R_VPBK_FIELD_TYPE_POC:
          case R_VPBK_FIELD_TYPE_VOIPHOME:
          case R_VPBK_FIELD_TYPE_VOIPWORK:
          case R_VPBK_FIELD_TYPE_VOIPGEN:
          case R_VPBK_FIELD_TYPE_SWIS:
              {
              fieldmaxlength =  KMaxLengthHundred;
              break;
              }
          case R_VPBK_FIELD_TYPE_EMAILGEN :
          case R_VPBK_FIELD_TYPE_EMAILWORK:
          case R_VPBK_FIELD_TYPE_EMAILHOME:
		  case R_VPBK_FIELD_TYPE_IMPP:
              {
              fieldmaxlength =  KMaxLengthOneHundredAndFifty;
              break;
              }
          case R_VPBK_FIELD_TYPE_ADDRLABELHOME:
          case R_VPBK_FIELD_TYPE_ADDRLABELGEN:
          case R_VPBK_FIELD_TYPE_ADDRLABELWORK :
              {
              fieldmaxlength =  KMaxLengthTwoHundredAndFifty;
              break;
              }
          case R_VPBK_FIELD_TYPE_LOCPRIVACY:
          case R_VPBK_FIELD_TYPE_RINGTONE:
		  case R_VPBK_FIELD_TYPE_CALLEROBJIMG:
              {
              fieldmaxlength = KMaxLengthTwoHundredAndFiftySix;
              break;
              }
           case R_VPBK_FIELD_TYPE_URLWORK:
           case R_VPBK_FIELD_TYPE_URLHOME:
           case R_VPBK_FIELD_TYPE_URLGEN:
           case R_VPBK_FIELD_TYPE_NOTE:
           case R_VPBK_FIELD_TYPE_SYNCCLASS:
              {
              fieldmaxlength = KMaxLengthThousand;
              break;
              }
        }
    return fieldmaxlength;    
    }

/*
-----------------------------------------------------------------------------
    CContactInterface::ExecuteCmdL()
    Description     : This is called by the consumer with command to execute.
    Return values   : N/A
-----------------------------------------------------------------------------
*/
EXPORT_C void CContactInterface::
    ExecuteCmdL(const TDesC8& aCmdName,
                const CLiwGenericParamList& aInParamList,
                CLiwGenericParamList& aOutParamList,
                TUint aCmdOptions,
                MLiwNotifyCallback* aCallback)
    {    
    //Top level TRAP for all the api's
    TRAPD(returnCode,
          ProcessCmdL(aCmdName,
                      aInParamList,
                      aOutParamList,
                      aCmdOptions,
                      aCallback));      
    //append the appropriate error code.
    TInt32 SapiErr = SapiError(returnCode);
    aOutParamList.AppendL(TLiwGenericParam(KErrorCode,
                          TLiwVariant((TInt32)SapiErr)));
    }

/*
---------------------------------------------------------------------------
 CContactInterface::SapiError(err)
 Description      :This function is called by the user to get mapped SAPI
                   generic error code from symbian error codes.
  Return values   :Integer Value TInt.
---------------------------------------------------------------------------
*/
TInt CContactInterface::SapiError( TInt aSymbianErr )
    {
    TInt sapiErr(SErrGeneralError);

   	switch (aSymbianErr)
    	{
   		case KErrBadName:
   		case KErrArgument:
   		    {
   		    sapiErr = SErrBadArgumentType;
   		    break;
   		    }
   		case KErrNotSupported:
   		    {
   		    sapiErr = SErrServiceNotSupported;
   		    break;
   		    }
   		case KErrInUse:
   		    {
   		    sapiErr = SErrServiceInUse;
   		    break;
   		    }
   		case KErrAccessDenied:
   		    {
   		    sapiErr = SErrAccessDenied;
   		    break;
   		    }
    	case KErrNoMemory:
	    	{
    		sapiErr = SErrNoMemory;
    		break;
    		}
   		case KErrAlreadyExists:
   		    {
   		    sapiErr = SErrEntryExists;
   		    break;
   		    }
   		case KErrNotReady:
   		    {
   		    sapiErr = SErrServiceNotReady;
   		    break;
   		    }
   		case KErrNotFound:
   		    {
   		    sapiErr = SErrNotFound;
   		    break;
   		    }
    	case KErrNone:
    		{
    		sapiErr = SErrNone;
    		break;
    		}
    	case KErrPathNotFound:
    		{
    		sapiErr = SErrPathNotFound;
    		break;
    		}
    	case KMissingArg:
    		{
    		sapiErr = SErrMissingArgument;
    		break;
    		}
    	default:
    		{
    		sapiErr = SErrGeneralError;
	    	}
   	}
    return sapiErr;
    }

/*
-----------------------------------------------------------------------------
    CContactInterface::Close()
    Description     : This is called by the consumer to delete the handle.
    Return values   : N/A
-----------------------------------------------------------------------------
*/
void CContactInterface::Close()
    {
    delete this;
    }

/*
-----------------------------------------------------------------------------
    CContactInterface::ContactIDUTFToStreamL()
    Description     : This method is used to convert the UTF to stream.
    Return values   : N/A
-----------------------------------------------------------------------------
*/
HBufC8* CContactInterface::ContactIDUTFToStreamL(TDesC&  aContactIDUTF)
    {
    TInt len = aContactIDUTF.Length();    
    HBufC8* buf = HBufC8 :: NewL(len);    
    buf->Des().SetLength(len);
    TUint16* ptr =  const_cast<TUint16*>(aContactIDUTF.Ptr());
    TUint8* ptr8 = const_cast<TUint8*>(buf->Des().Ptr());
    
    for(TInt i=0; i<len; i++)
        {
        TUint c = ptr[i];
        if(c>=0x100)
         c = c & 0x00ff;        
        ptr8[i] = (TUint8)c;    
        }       
    return buf;         
    }
    
/*
-----------------------------------------------------------------------------
    CContactInterface::ProcessAddDataL(const CLiwMap* aMap,
 									   TPtrC& aDbUri,
 									   CSingleContact* aContact)
    Description     : Constructs a contact from the fields that exist in the map..
    Return values   : N/A
-----------------------------------------------------------------------------
*/

void CContactInterface::ProcessAddDataL(const CLiwMap* aMap, 										
 										CSingleContact* aContact,
 										CLiwGenericParamList& aOutParamList)
    {
    TBool xspid = EFalse;
    TBool xspidIsDes = EFalse;
    TBool atleastOneField = EFalse;
    //iDburi = HBufC::NewL(VPbkContactStoreUris::DefaultCntDbUri().Length());    
    //set the DBUri to the default value.    
    //iDburi->Des().Copy(VPbkContactStoreUris::DefaultCntDbUri());
    iDburi = GetDefaultDBUri().AllocLC();
    //get the number of entries in the map
    TInt keyCount = aMap->Count();

    for(TInt index=0;index<keyCount;index++)
        {
        //iterate through each entry in the map
        //starting from the first element

        //this variable should be reemoved
        //when the AtL signature is changed in LIW.
        TBuf8<KMaxName> fieldKey;
        TLiwVariant fieldVal;
        CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup ,&fieldVal) );

        //AtL gives us the key stored at a particular index
        aMap->AtL(index, fieldKey);
        //check whether the key is DBUri
        //if it is extract it and mark it.
        if( fieldKey.Compare(KDBUri) == 0 )
            {
            //get the DBUri from the map
            if(aMap->FindL(fieldKey, fieldVal))
                {
                if(fieldVal.AsDes().CompareF(KNullDesC)!=0)
                    { 
                    delete iDburi;
                    iDburi = NULL;                                  
                    iDburi = HBufC::NewL(fieldVal.AsDes().Length());
                    iDburi->Des().Copy(fieldVal.AsDes());                    
                    }
                }
            }
        else if( fieldKey.Compare(KContactId) == 0 )
            {
            //get the contact ID  from the map
            if(aMap->FindL(fieldKey, fieldVal))
                {
                TPtrC cntIdUnicode = fieldVal.AsDes();      
				if(cntIdUnicode == NULL)
					{
					aOutParamList.AppendL(TLiwGenericParam (KErrorMessage,
					                      TLiwVariant(KAddWrongContactId)));  	
					User::Leave(KErrArgument); 
					}
          
                HBufC8* cntid = ContactIDUTFToStreamL(cntIdUnicode);                
                aContact->SetContactIdL(*cntid);
                delete cntid;
                }
            }
        else
            {            
            //if the key is not uri and is not a contact id
            //search for the field
            if(CSearchFields::GetIdFromFieldKey(fieldKey) != -1)
             /*   {
                TBuf<25> buff;
                buff.Copy(fieldKey);
                TBuf<KMaxName> errmsg(KAddInvalidFieldKey);
                errmsg.Append(buff);                                
            	aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
            	                      TLiwVariant(errmsg)));  	
				User::Leave(KErrArgument);     
                }                          
            else*/
                {
			aMap->FindL(fieldKey,fieldVal);
       	 	if(EVariantTypeMap == fieldVal.TypeId())
                {
                const CLiwMap* pMap = fieldVal.AsMap();
                if(pMap)
                    {
                    TLiwVariant labelVar;
				    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &labelVar) );
                    
                    TLiwVariant valueVar;
				    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueVar) );

                    TLiwVariant nextVar;
                    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &nextVar) );
                    while(1)
                        {
						//Get field label and value from map
					if(pMap->FindL(KFieldLabel, labelVar))				
						{
						if(EVariantTypeDesC !=  labelVar.TypeId())	
					 		{
							TPtr16  err(iErrorMess->Des());
							TBuf<KMaxName> buf;
							buf.Copy(labelVar.AsData());							
							err.Append(KAddCnt);
							err.Append(buf);
							err.Append(KAddInvalidStr);
							aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(*iErrorMess) ) );  
							CleanupStack::Pop(&nextVar);
							nextVar.Reset();
							CleanupStack::Pop(&valueVar);
							valueVar.Reset();
							CleanupStack::Pop(&labelVar);
							labelVar.Reset();
    						CleanupStack::Pop(&fieldVal);
    						fieldVal.Reset();
    						err.Delete(0,iErrorMess->Length());
							User::Leave(KErrArgument); 														
							}							
						}
					TBool date = EFalse;                        
						//Set contact item field value
					if(pMap->FindL(KFieldValue, valueVar))	
						{
						if(fieldKey.Compare(KXspid) == 0)
						    {
						    xspid = ETrue;
						    if(EVariantTypeList != valueVar.TypeId())
						        {
						        	if(EVariantTypeDesC ==  valueVar.TypeId())
						        	{
						        	//xspidIsDes = ETrue;
						        	CLiwList* xspidList = NULL;
						        	xspidList = CLiwDefaultList::NewL();
						      /*  	TPtrC val = valueVar.AsDes();
						        	
						        	TBuf<1000> bufVal;
						        	bufVal.Copy(val);
						        	HBufC* xspidVal = bufVal.AllocLC();*/
						        	
						        	xspidList->AppendL(valueVar);
						        	valueVar.Reset();
						        	valueVar.Set(xspidList);
						        	}
						            else
						                {						                
        						        TPtr16  err(iErrorMess->Des());
                                        TBuf<KMaxName> buf;
                                        buf.Copy(valueVar.AsData());
                                        err.Append(KAddCnt);
                                        err.Append(buf);
                                        err.Append(KAddInvalidTime);
        
                                        aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(*iErrorMess) ) );  
                                        CleanupStack::Pop(&nextVar);
                                        nextVar.Reset();
                                        CleanupStack::Pop(&valueVar);
                                        valueVar.Reset();
                                        CleanupStack::Pop(&labelVar);
                                        labelVar.Reset();
                                        CleanupStack::Pop(&fieldVal);
                                        fieldVal.Reset();
                                        err.Delete(0,iErrorMess->Length());
                                        User::Leave(KErrArgument); 
						                }
						        }
						    }
                        if((fieldKey.Compare(KDate) == 0 || (fieldKey.Compare(KAnniversary) == 0))) // || (fieldKey.Compare(KBirthDay) == 0))
	                        {
	                        if(EVariantTypeTTime != valueVar.TypeId())
	                        {
							TPtr16  err(iErrorMess->Des());
							TBuf<KMaxName> buf;
							buf.Copy(valueVar.AsData());
							err.Append(KAddCnt);
							err.Append(buf);
							err.Append(KAddInvalidTime);

							aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(*iErrorMess) ) );  
							CleanupStack::Pop(&nextVar);
							nextVar.Reset();
							CleanupStack::Pop(&valueVar);
							valueVar.Reset();
							CleanupStack::Pop(&labelVar);
							labelVar.Reset();
    						CleanupStack::Pop(&fieldVal);
    						fieldVal.Reset();
    						err.Delete(0,iErrorMess->Length());
							User::Leave(KErrArgument); 														
	                        }
                        date = ETrue;
                        }
						if((EVariantTypeDesC !=  valueVar.TypeId())	&& (date == EFalse) && (xspid == EFalse))
							{
							TPtr16  err(iErrorMess->Des());
							TBuf<KMaxName> buf;
							buf.Copy(valueVar.AsData());
							err.Append(KAddCnt);
							err.Append(buf);
							err.Append(KAddInvalidStr);

							aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(*iErrorMess) ) );  
							CleanupStack::Pop(&nextVar);
							nextVar.Reset();
							CleanupStack::Pop(&valueVar);
							valueVar.Reset();
							CleanupStack::Pop(&labelVar);
							labelVar.Reset();
    						CleanupStack::Pop(&fieldVal);
    						fieldVal.Reset();
    						err.Delete(0,iErrorMess->Length());
							User::Leave(KErrArgument); 														
							}					
						}
                        CSingleContactField* field =
                            CSingleContactField::NewL();
                        CleanupStack::PushL(field);
                        if(date)
                            {
                            field->SetFieldParamsL(fieldKey,
    						                       labelVar.AsDes(),
    					    	                   KNullDesC);
    					    field->SetDateTime(valueVar.AsTTime());	                   
    	                    }
                        else if(xspid && !xspidIsDes)
                            {
                            RPointerArray<HBufC> xspidArray;
                            const CLiwList* xspidList = valueVar.AsList();
                            TInt count = xspidList->Count();
                            for(int i =0; i< count; i++)
                                {
                                    TLiwVariant xspidVal;
                                    if(xspidList->AtL(i,xspidVal))
                                        {
                                        TPtrC ptrVal = xspidVal.AsDes();
                                        HBufC *pHeap1 = ptrVal.AllocLC();
                                        xspidArray.Append(pHeap1);
                                        TInt len = pHeap1->Find(_L(":"));
                                        if(len == -1)
                                            {
                                            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                                                  TLiwVariant(KAddXspidInvalidFormat)));
                                            User::Leave(KErrArgument);
                                            }
                                        CleanupStack::Pop(pHeap1);
                                        }
                                }
                            field->SetXspidDataL(fieldKey,
                                                    labelVar.AsDes(),
                                                    xspidArray);
                            xspid = EFalse;
    	                    }
                        else 
                            {
    						field->SetFieldParamsL(fieldKey,
                                                   labelVar.AsDes(),
                                                   valueVar.AsDes());
                            	
                            }
                        aContact->AddFieldToContactL(field);
                        atleastOneField = ETrue;
                        CleanupStack::Pop(field);
                        if(pMap->FindL(KFieldNext,nextVar))
                            {
                            if(EVariantTypeMap == nextVar.TypeId())
                                {
                                pMap = nextVar.AsMap();
                                }
                            else
                            	{
				                //if the map is not found
				                //Leave with the error code
				                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
				                                      TLiwVariant(KAddNextFieldType)));
				                User::Leave(KErrArgument);
                            	}
                            }
                        else //EVariantTypeNull
                            {
                            break;
                            }
                        }  //end of while
                    CleanupStack::Pop(&nextVar);    
                    nextVar.Reset();
					CleanupStack::Pop(&valueVar);
					valueVar.Reset();
					CleanupStack::Pop(&labelVar);
					labelVar.Reset();
                    }
                else
                    {
                    //if the map is not found
                    //Leave with the error code
                    aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                          TLiwVariant(KAddInvalidFieldType)));
                    User::Leave(KErrArgument);
                    }
                }
            else
                {
				CleanupStack::Pop(&fieldVal);
				fieldVal.Reset();
				TPtr16  err(iErrorMess->Des());
				TBuf<KMaxName> fld;
				fld.Copy(fieldKey);
				err.Append(fld);
				err.Append(_L(",Invalid Type,Map is Required"));
				aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,
				                       TLiwVariant(*iErrorMess) ) );  
				err.Delete(0,iErrorMess->Length()); 
				User::Leave(KErrArgument); 

				}	
            }
            }            
		CleanupStack::Pop(&fieldVal);
		fieldVal.Reset();    
        } //end of for
    //checking for the maximum length (this is a temporary check since there is no support from vpbk)
    CSingleContactField* contactfield = NULL;
    TPtrC8 fieldKey(KNullDesC8);
    TPtrC fieldLabel(KNullDesC);
    TPtrC fieldValue(KNullDesC);
    TInt fieldCount = aContact->FieldCount(); 
    for( TInt i=0;i<fieldCount;i++ ) 
        {                
        contactfield = aContact->FieldAt(i);
        if(contactfield) 
            {
            contactfield->GetFieldDataL(fieldKey, fieldLabel, fieldValue);        
            if(fieldKey.Compare(KXspid) == 0)
                {
                RPointerArray<HBufC> xspidArr;
                contactfield->GetXspidDataL(xspidArr);
                for(TInt j=0;j<xspidArr.Count(); j++)
                    {
                    HBufC* xspidVal = xspidArr[j];      
                    //HBufC* xspidBufVal = xspidVal.AllocL();
                    if(xspidVal->Length() > GetFieldMaxLength(CSearchFields::GetIdFromFieldKey(fieldKey), *iDburi))
                        {
                        TPtr16  err(iErrorMess->Des());
                        TBuf<KMaxName> fld;
                        fld.Copy(fieldKey);             
                        err.Append(_L("Contacts : Add : Field Value too long for key : "));
                        err.Append(fld);
                        
                        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                              TLiwVariant(*iErrorMess)));
                        
                        err.Delete(0,iErrorMess->Length());
                        User::Leave(KErrArgument);    
                        }
                    }
                }
            else if(!(fieldKey.Compare(KDate) == 0 || fieldKey.Compare(KAnniversary) == 0))
			 {
	            if(fieldValue.Length() > GetFieldMaxLength(CSearchFields::GetIdFromFieldKey(fieldKey), *iDburi))
	        		{
	        		TPtr16  err(iErrorMess->Des());
	        		TBuf<KMaxName> fld;
					fld.Copy(fieldKey);				
					err.Append(_L("Contacts : Add : Field Value too long for key : "));
					err.Append(fld);
					
	        		aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
	                                      TLiwVariant(*iErrorMess)));
	                
	                err.Delete(0,iErrorMess->Length());
	        		User::Leave(KErrArgument);    
	        		}     
			 	
			 }
            }
            
        }
       
	if(atleastOneField == EFalse)
		{
        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                              TLiwVariant(KAddKeyNotSpecified)));
		User::Leave(KErrArgument);
		}				
    } //End of function : ProcessAddDataL()


/*
-----------------------------------------------------------------------------
    CContactInterface::ProcessCmdL(const TDesC8& aCmdName,
                                    const CLiwGenericParamList& aInParamList,
                                    CLiwGenericParamList& aOutParamList,
                                    TUint aCmdOptions,
                                    MLiwNotifyCallback* aCallback )
    Description     : This function processes the commands like add, delete, organise,
                     getlist.....etc.
    Return values   : N/A
-----------------------------------------------------------------------------
*/
void CContactInterface::ProcessCmdL(const TDesC8& aCmdName,
                                    const CLiwGenericParamList& aInParamList,
                                    CLiwGenericParamList& aOutParamList,
                                    TUint aCmdOptions,
                                    MLiwNotifyCallback* aCallback )
    {
    TInt returnCode = KErrNone;
    TInt transId = 0;
	//if callback parameter is not null then retrieve the transaction id.
    if(aCallback && aCmdOptions == KLiwOptASyncronous)
        {
        transId = aCallback->GetTransactionID();

        CContactCallbackMap* map =
            new (ELeave) CContactCallbackMap(transId,
                                             aCallback);
        CleanupStack::PushL(map);
        iCallbackMap.AppendL(map);
        CleanupStack::Pop(map);

        //In case of async calls, also set the transaction id
        aOutParamList.AppendL(TLiwGenericParam(KTransactionID,
                              TLiwVariant((TInt32)transId)));

        }
    else if((aCmdOptions == KLiwOptASyncronous) && (!aCallback))
    	{
    	//Leave with the error code
        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                          TLiwVariant(KCallbackNotFound)));
        User::Leave(KErrArgument);
    	}
    else if(aCallback && (aCmdOptions == 0))
	    {
        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                          TLiwVariant(KCallbackNotFound)));
        User::Leave(KErrArgument);
	    	
	    }	
    
    if( aCmdName.CompareF(KCmdCancel) == 0) // for cancel asynchronous request
	    {
		if(aCmdOptions != KLiwOptCancel)
			{
	    	//Leave with the error code
	        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
	                          TLiwVariant(KCancleCommandoptionWrong)));
	        User::Leave(KErrArgument);
				
			}
 		returnCode = CancelCommandL(aInParamList,
 									aOutParamList);
		if(returnCode != KErrNone)
			{
			//Leave with the error code
			aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
									TLiwVariant(KCancelUnsuccessful)));
			User::Leave(returnCode);
			}
    	}
    //check for the command name,...if Import proceed further.
    else if ( (aCmdName.CompareF( KCmdImport ) == 0))
        {
        ImportCommandL(aInParamList,
                       aOutParamList,
                       aCallback,
                       aCmdOptions,
                       transId);
        }
    //check for the command name,...if Export, proceed further.
    else if ( (aCmdName.CompareF( KCmdExport ) == 0))
        {
        ExportCommandL(aInParamList,
                       aOutParamList,
                       aCallback,
                       aCmdOptions,
                       transId);
        }
    //check for the command name,...if Add, proceed further.
	else if ( (aCmdName.CompareF( KCmdAdd ) == 0))
        {
        AddCommandL(aInParamList,
                    aOutParamList,
                    aCallback,
                    aCmdOptions,
                    transId);
        }
   //check for the command name,...if Delete, proceed further.
   else if ( (aCmdName.CompareF( KCmdDelete ) == 0))
        {
        DeleteCommandL(aInParamList,
                       aOutParamList,
                       aCallback,
                       aCmdOptions,
                       transId);
	    }

	   //check for the command name,...if OrganiseGroups, proceed further.
    else if ( (aCmdName.CompareF( KCmdOrganiseGroups ) == 0))
        {
        OrganiseGroupCommandL(aInParamList,
                                           aOutParamList,
            	                           aCallback,
            	                           aCmdOptions,
            	                           transId);
        }
   //Passing arguments for GetList command
   else if( aCmdName.CompareF( KCmdGetList ) == 0 )
        {
        GetListCommandL(aInParamList,
                        aOutParamList,
                        aCallback,
                        aCmdOptions,
                        transId,
                        EGetList);
        }
    //Passing arguments for GetIds command
   else if( aCmdName.CompareF( KCmdGetIds ) == 0 )
           {
           GetListCommandL(aInParamList,
                           aOutParamList,
                           aCallback,
                           aCmdOptions,
                           transId,
                           EGetIds);
           }
   else 
   		{
        //Leave with the error code
        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                          TLiwVariant(KCommandNotSupported)));
        User::Leave(KErrNotSupported);
   		}

    } //end of ProcessCmdL

/*
-----------------------------------------------------------------------------
    CContactInterface::GetListCommandL(const CLiwGenericParamList& aInParamList,
                                       CLiwGenericParamList& aOutParamList,
                                       MLiwNotifyCallback* aCallback,
                                       TUint aCmdOptions,
                                       TInt aTransId)
    Description     : This function parses the input param list
                    : and calls the Getlist API
    Return values   : N/A
-----------------------------------------------------------------------------
*/
void CContactInterface::
     GetListCommandL(const CLiwGenericParamList& aInParamList,
                     CLiwGenericParamList& aOutParamList,
                     MLiwNotifyCallback* aCallback,
                     TUint aCmdOptions,
                     TInt aTransId, TCmdType aVal)
    {    
    const TLiwGenericParam* paramContentType = NULL;
	const TLiwGenericParam* paramGetListData = NULL;
    const TLiwGenericParam* paramGetListSortOrder = NULL;

    TInt pos = 0;
	//Get the content type: it can be "contact" or "group" 
	paramContentType = aInParamList.FindFirst( pos, KType );
	if(!paramContentType)
		{
			if(aInParamList.Count()>0)
				paramContentType = &aInParamList[0] ;
			
			if(!paramContentType || paramContentType->Name().Compare(KNullDesC8) != 0)
				{
				aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KGetListContentTypeMissing) ) );  
				User::Leave(KMissingArg); 
				}		
        	if(aInParamList.Count()>1)    	
        		paramGetListData = &aInParamList[1]; 
        	
    		if(aInParamList.Count()>2)
	            paramGetListSortOrder = &aInParamList[2] ;
		}	
	pos = 0;
    //Get the filter criteria, the value of which is a Map
    paramGetListData = aInParamList.FindFirst( pos, KFilter );    
    
    pos = 0;
    paramGetListSortOrder = aInParamList.FindFirst( pos, KSort );    	
	
	TLiwVariant cnttyp = paramContentType->Value();
	if(EVariantTypeDesC !=  cnttyp.TypeId())
		{
		cnttyp.Reset();

		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KGetListWrongContentType) ) );  
		User::Leave(KErrArgument);			
		}
			 
    //Retrieve the map
    const CLiwMap* pMap = NULL;
    if(paramGetListData)
        {
        TLiwVariant getlistdata = paramGetListData->Value();
        if(EVariantTypeMap != getlistdata.TypeId() )
	        {
	        getlistdata.Reset();
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KGetListInvalidFilterType) ) );  
			User::Leave(KErrArgument);			
	        }
        pMap = getlistdata.AsMap();
	    getlistdata.Reset();
        }
		
 	const CLiwMap* sortMap = NULL;

 	if(paramGetListSortOrder)
 	{
 	TLiwVariant map =  paramGetListSortOrder->Value();
 	
 	if(EVariantTypeMap == map.TypeId())
	 	{
	 	sortMap= paramGetListSortOrder->Value().AsMap();	
	 	}
 	else
	 	{
		map.Reset();
		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KGetListInvalidSortType) ) );  
		User::Leave(KErrArgument);			
	
	 	}
 	map.Reset();	
 	}
        
    //Get the type of the list requested
    Ttype listType = EContacts;
    TPtrC contentType;

    contentType.Set(paramContentType->Value().AsDes());

	 //Based on content type set the value of the enum Ttype
	if(contentType.Compare(KDatabase) == 0)
		{
		listType = EDatabase;
		}
	else if(contentType.Compare(KGroup) == 0)
		{
		listType = EGroups;
		}
	else if(contentType.Compare(KContact) == 0)
		{
		listType = EContacts;
		}
	else
    	{ 
    	aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                              TLiwVariant(KGetListInvalidContentType)));   
    	User::Leave(KErrArgument);
    	}

	TLiwVariant uriofDb;
    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &uriofDb) );

	TLiwVariant groupId;
    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &groupId) );

    TPtrC8 ptrToCntId(KNullDesC8);
	HBufC8* cntid = NULL;
	CContactIter* iter;
	CContactIterator* iterator;
	//TPtrC dbUri(VPbkContactStoreUris::DefaultCntDbUri());
	TPtrC dbUri = GetDefaultDBUri();
	//Switch based on the Ttype var value
	switch(listType)
	    {	    
		case EDatabase:
		    if(aVal == EGetIds)
		        {
		        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
		                                      TLiwVariant(KGetIdsInvalidContentType)));
		        User::Leave(KErrArgument);
		        }
		    //In case it is GetList of dabases, the call is synchronous
			iter = CContactIter::NewL();			
			CleanupStack::PushL(iter);
			iContactService->GetListL(*iter);
		    CleanupStack::Pop(iter);
		    //Setting the output param
			if(iter)
				{
			    iterator = CContactIterator::NewL(iter);
			    CleanupStack::PushL(iterator);
		        aOutParamList.AppendL(TLiwGenericParam(KReturnValue,
		                              TLiwVariant(iterator)));
		        
		        CleanupStack::Pop(iterator);
		        iterator->DecRef();
                CleanupStack::Pop(&groupId);
                groupId.Reset();
                CleanupStack::Pop(&uriofDb);
                uriofDb.Reset();
				return;
				}
			break;
		case EGroups:
            //In case it is GetList of groups, its asynchronous
            //All that is required to get the list of groups is the database name
            //(in case its null default database is used) and callback function
            if(pMap && (EFalse != pMap->FindL(KDBUri, uriofDb)))
                 {
                 if(uriofDb.AsDes().Compare(KNullDesC)!= 0)
                     {
                     dbUri.Set(uriofDb.AsDes());
                     }
                 }
            // Get the contact id, in case it is specified single contact is retrived
            // If content is NULL, search is performed using search criteria
            // If the ID is mentioned then the search value and fields are ignored.
            if(pMap && (EFalse != pMap->FindL(KGroupId, groupId)))
                 {
                 TPtrC ptr = groupId.AsDes();
                 cntid = ContactIDUTFToStreamL(ptr);                 
                 CleanupStack::PushL(cntid);
                 if(aCmdOptions == KLiwOptASyncronous)
                    {
                	CContactInterfaceCallback* contactCallback =
                	    CContactInterfaceCallback::NewL();
                    CleanupStack :: PushL(contactCallback);
                   	 contactCallback->SetParams(aCallback,
                   	                            aTransId,
                   	                            &aInParamList);
                   	 //Call GetList in case of retrieval of a
                   	 //single contact whose id is known
                        iContactService->GetListL(contactCallback,
        										  aTransId,
        										  listType,
        										  *cntid,
        										  KNullDesC,
        										  NULL,
        										  EAsc,
        										  dbUri,aVal);

                    CleanupStack :: Pop(contactCallback);
                    CleanupStack::PopAndDestroy(cntid);  
                    }
             else
                    {
                    if(aVal == EGetList)
                    {
					//it is assumed that the call is synchronous
                    CContactIter* iter =
                    iContactService->GetListL(listType,
                                              *cntid,
                                              KNullDesC,
                                              NULL,
                                              EAsc,
                                              dbUri,
                                              aVal);
                    aOutParamList.AppendL(TLiwGenericParam( KErrorCode,
                                          TLiwVariant((TInt32)SErrNone)));
                    //Setting the output param
                    CContactIterator* iterator=CContactIterator::NewL(iter);
                    CleanupStack::PushL(iterator);
                    aOutParamList.AppendL(TLiwGenericParam(KReturnValue,
                                          TLiwVariant(iterator)));                                                             
                    CleanupStack::Pop(iterator);
                    iterator->DecRef();
                        }
                    else
                    {
                    aOutParamList.AppendL(TLiwGenericParam( KErrorCode,
                                                              TLiwVariant((TInt32)SErrBadArgumentType)));
                    aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KGetIdsBadArgGrpId) ) );
                    }
                    CleanupStack::PopAndDestroy(cntid);
                    CleanupStack::Pop(&groupId);
                    groupId.Reset();
                    CleanupStack::Pop(&uriofDb);
                    uriofDb.Reset();
                    return;
                    }
             break;
             }                 
            if(aCmdOptions == KLiwOptASyncronous)
                {
                CContactInterfaceCallback* contactCallback =
                    CContactInterfaceCallback::NewL();
                CleanupStack :: PushL(contactCallback);
                contactCallback->SetParams(aCallback,
                                           aTransId,
                                           &aInParamList);
                //Call the contactservice api
                    iContactService->GetListL(contactCallback,
                                              aTransId,
                                              listType,
                                              ptrToCntId,
                                              KNullDesC,
                                              NULL,
                                              EAsc,
                                              dbUri,
                                              aVal);

                CleanupStack :: Pop(contactCallback);
                }
            else
                {
                if(aVal == EGetList)
                {
				//it is assumed that the call is synchronous
                CContactIter* iter =
                    iContactService->GetListL(listType,
                                              ptrToCntId,
                                              KNullDesC,
    										  NULL,
    										  EAsc,
                                              dbUri,
                                              aVal);
                //Setting the output param
                CContactIterator* iterator=CContactIterator::NewL(iter);
                CleanupStack::PushL(iterator);
                aOutParamList.AppendL(TLiwGenericParam( KReturnValue,
                                      TLiwVariant(iterator) ));                                                      
                CleanupStack::Pop(iterator);
                iterator->DecRef(); 
                    }
                else
                    {
                    //call the GetIds() service api 
                    RPointerArray<HBufC8>& arrayid = 
                    iContactService->GetIdsL(listType,
                                              KNullDesC,
                                              NULL,
                                              EAsc,
                                              dbUri,
                                              aVal);

   
                        
                        
                        aOutParamList.AppendL(TLiwGenericParam( KErrorCode,
                                              TLiwVariant((TInt32)SErrNone)));
                        //Setting the output param
                        if(arrayid.Count() > 0)
                        {
                        CLiwList* iList = NULL;
                        iList = CLiwDefaultList::NewL();
                        TLiwVariant outputVal;
                        TInt count = arrayid.Count();
                        TInt i;
                        for(i=0; i<count; i++)
                            {
                            TDesC8* idVal = arrayid[i];
							HBufC* cntIdUnicode = HBufC::NewL(idVal->Length());
                            CleanupStack :: PushL(cntIdUnicode);
                            cntIdUnicode->Des().Copy(*idVal);
                            CContactInterfaceCallback::ContactIDToUTF(cntIdUnicode);      
                            outputVal.Set(*cntIdUnicode);
                            iList->AppendL(outputVal);
                            CleanupStack :: Pop(cntIdUnicode);              
                            }
                        CLiwMap* pFieldLinkedMap = CLiwDefaultMap::NewL();
                        CleanupClosePushL(*pFieldLinkedMap);
                        pFieldLinkedMap->InsertL(KIdsLabel,TLiwVariant(iList));
                        
                        aOutParamList.AppendL(TLiwGenericParam(KReturnValue, 
                                                 TLiwVariant(pFieldLinkedMap)));
                        CleanupStack::PopAndDestroy(pFieldLinkedMap);
                        arrayid.ResetAndDestroy();
                        }
                    }
               	CleanupStack::Pop(&groupId);
               	groupId.Reset();
                CleanupStack::Pop(&uriofDb);
                uriofDb.Reset();
                return;
                }
            break;
		case EContacts:
		    //In case it is GetList of contacts, its asynchronous
            //Get the database uri, if not specified default database is used
            if(pMap && (EFalse != pMap->FindL(KDBUri,uriofDb)))
                 {
                 if(uriofDb.AsDes().Compare(KNullDesC)!= 0)
                     {
                     dbUri.Set(uriofDb.AsDes());
                     }
                 }
            TLiwVariant contactId;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &contactId) );

            // Get the contact id, in case it is specified single contact is retrived
            // If content is NULL, search is performed using search criteria
            // If the ID is mentioned then the search value and fields are ignored.
            if(pMap && (EFalse != pMap->FindL(KContactId, contactId)))
                 {
                 TPtrC ptr = contactId.AsDes();
                 cntid = ContactIDUTFToStreamL(ptr);                 
                 CleanupStack::PushL(cntid);
                 if(aCmdOptions == KLiwOptASyncronous)
                    {
                	CContactInterfaceCallback* contactCallback =
                	    CContactInterfaceCallback::NewL();
                    CleanupStack :: PushL(contactCallback);
                   	 contactCallback->SetParams(aCallback,
                   	                            aTransId,
                   	                            &aInParamList);
                   	 //Call GetList in case of retrieval of a
                   	 //single contact whose id is known
					 iContactService->GetListL(contactCallback,
        										  aTransId,
        										  listType,
        										  *cntid,
        										  KNullDesC,
        										  NULL,
        										  EAsc,
        										  dbUri,
        										  aVal);
                    CleanupStack :: Pop(contactCallback);
                    CleanupStack::PopAndDestroy(cntid);  
                    }
             else
                    {
                    //it is assumed that the call is synchronous
                    if(aVal == EGetList)
                        {
				CContactIter* iter =
                    iContactService->GetListL(listType,
                                              *cntid,
                                              KNullDesC,
                                              NULL,
                                              EAsc,
                                                  dbUri,
                                                  aVal);
                    aOutParamList.AppendL(TLiwGenericParam( KErrorCode,
                                          TLiwVariant((TInt32)SErrNone)));
                    //Setting the output param
                    CContactIterator* iterator=CContactIterator::NewL(iter);
                    CleanupStack::PushL(iterator);
                    aOutParamList.AppendL(TLiwGenericParam(KReturnValue,
                                          TLiwVariant(iterator)));                                                             
                    CleanupStack::Pop(iterator);
                    iterator->DecRef(); 
                        }
                    else
                        {
                        aOutParamList.AppendL(TLiwGenericParam( KErrorCode,
                                TLiwVariant((TInt32)SErrBadArgumentType)));
                        aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,
                                TLiwVariant(KGetIdsBadArgCntId) ) );
                        }
                    CleanupStack::PopAndDestroy(cntid);
                    CleanupStack::Pop(&contactId);
                    contactId.Reset();
                    CleanupStack::Pop(&groupId);
               	    groupId.Reset();
                    CleanupStack::Pop(&uriofDb);
                    uriofDb.Reset();
                    return;
                    }
	         CleanupStack::Pop(&contactId);
	         contactId.Reset();
             break;
             }            
            CleanupStack::Pop(&contactId);
			contactId.Reset();
            TLiwVariant searchVal;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &searchVal) );

            TPtrC srchVal(KNullDesC);
            TLiwVariant searchFieldKeys;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &searchFieldKeys) );

            //Get the searchval, the value to be searched in the fields specified.
            //If the value is NULL, the whole database is listed as an output
            if(pMap && (EFalse != pMap->FindL(KSearchVal,searchVal)))
                 {
		         if(EVariantTypeDesC != searchVal.TypeId())
		         	{
		         	CleanupStack::Pop(&searchFieldKeys);
                     CleanupStack::Pop(&searchVal);
                     searchVal.Reset();
     	    		 aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KGetListInvalidSearchVal) ) );  
		    		 User::Leave(KErrArgument); 
		         	}
                 if(searchVal.AsDes().Compare(KNullDesC))
                 srchVal.Set(searchVal.AsDes());
                 }

            CSearchFields* searchFields = NULL;
            // Get the search fields, fields in which
            //the given searchval is to looked for
            // in all the contacts of the database.
            //If not specified, fields are first and last name
            // by default
					
            TLiwVariant order;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &order) );

            TPtrC sortOrder;
            TOrder srtOrder = EAsc;

            if(NULL != paramGetListSortOrder)
                {
				if(EFalse != sortMap->FindL(KOrder, order))
                    {
			    	if(EVariantTypeDesC != order.TypeId())
				    	{
					    CleanupStack::Pop(&order);
					    order.Reset();
			    		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KGetListSortOrderValue) ) );  
			    		User::Leave(KErrArgument); 
				    		
				    	}
                    sortOrder.Set(order.AsDes());

                    // Set the TOrder variable to the sort order preference
                    if( sortOrder.CompareF( KAscending ) == 0)
                        {
                        srtOrder = EAsc;
                        }
                    else if(sortOrder.CompareF( KDescending ) == 0)
                        {
                        srtOrder = EDesc;
                        }
                    else
                        {
					    CleanupStack::Pop(&order);
					    order.Reset();
                        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                        TLiwVariant(KGetListInvalidSortordVal))); 
                        User::Leave(KErrArgument);     
                        }    
                    }    
                }


            if(aCmdOptions == KLiwOptASyncronous)
                {
                CContactInterfaceCallback* contactCallback =
                    CContactInterfaceCallback::NewL();
                CleanupStack :: PushL(contactCallback);
                contactCallback->SetParams(aCallback,
                                           aTransId,
                                           &aInParamList);


                //Call to GetList in case of searching
                    iContactService->GetListL(contactCallback,
        									  aTransId,
        									  listType,
        									  ptrToCntId,
        									  srchVal,
        									  searchFields,
        									  srtOrder,
        									  dbUri,
        									  aVal);

                CleanupStack :: Pop(contactCallback);
                }
            else
                {
                //it is assumed that the call is synchronous
                if(aVal == EGetList)
                    {
                CContactIter* iter =
                    iContactService->GetListL(listType,
											  ptrToCntId,
											  srchVal,
											  searchFields,
											  srtOrder,
											  dbUri,
											  aVal);

                aOutParamList.AppendL(TLiwGenericParam(KErrorCode,
                                      TLiwVariant((TInt32)SErrNone)));

                //Setting the output param
                CContactIterator* iterator=CContactIterator::NewL(iter);
                CleanupStack::PushL(iterator);
                aOutParamList.AppendL(TLiwGenericParam(KReturnValue,
                                      TLiwVariant(iterator)));
                CleanupStack::Pop(iterator);
                iterator->DecRef();           
                    }
                else
                    {
                    RPointerArray<HBufC8>& arrayid = 
                    iContactService->GetIdsL(listType,
                                              srchVal,
                                              searchFields,
                                              srtOrder,
                                              dbUri,
                                              aVal);
                    aOutParamList.AppendL(TLiwGenericParam( KErrorCode,
                                                                TLiwVariant((TInt32)SErrNone)));
                                          //Setting the output param
                      if(arrayid.Count() > 0)
                      {
                      CLiwList* iList = NULL;
                      iList = CLiwDefaultList::NewL();
                      TLiwVariant outputVal;
                      TInt count = arrayid.Count();
                      TInt i;
                      for(i=0; i<count; i++)
                          {
                          TDesC8* idVal = arrayid[i];
                         HBufC* cntIdUnicode = HBufC::NewL(idVal->Length());
                         CleanupStack :: PushL(cntIdUnicode);
                         cntIdUnicode->Des().Copy(*idVal);
                         CContactInterfaceCallback::ContactIDToUTF(cntIdUnicode);      
                         outputVal.Set(*cntIdUnicode);
                         iList->AppendL(outputVal);
                         CleanupStack :: Pop(cntIdUnicode);
                          }
                      CLiwMap* pFieldLinkedMap = CLiwDefaultMap::NewL();
                      CleanupClosePushL(*pFieldLinkedMap);
                      pFieldLinkedMap->InsertL(KIdsLabel,TLiwVariant(iList));
                      
                      aOutParamList.AppendL(TLiwGenericParam(KReturnValue, 
                                               TLiwVariant(pFieldLinkedMap)));
                      CleanupStack::PopAndDestroy(pFieldLinkedMap);
                      arrayid.ResetAndDestroy();
                      }
                    
                    }
                CleanupStack::Pop(&order);
                order.Reset();
                CleanupStack::Pop(&searchFieldKeys);
                searchFieldKeys.Reset();
                CleanupStack::Pop(&searchVal);
                searchVal.Reset();
				CleanupStack::Pop(&groupId);
				groupId.Reset();
                CleanupStack::Pop(&uriofDb);
                uriofDb.Reset();                                                            
                return;
                }
                            
            CleanupStack::Pop(&order);
            order.Reset();
            CleanupStack::Pop(&searchFieldKeys);
            searchFieldKeys.Reset();
            CleanupStack::Pop(&searchVal);
            searchVal.Reset();
            
            break;                                  
        	}
	CleanupStack::Pop(&groupId);
	groupId.Reset();
    CleanupStack::Pop(&uriofDb);
    uriofDb.Reset();
    
    if( aCallback && aCmdOptions == KLiwOptASyncronous )
        {
        //In case of async calls, also set the transaction id
        aOutParamList.AppendL(TLiwGenericParam(KTransactionID,
                              TLiwVariant((TInt32)aTransId )));
        }
    }

/*
-----------------------------------------------------------------------------
    CContactInterface::CancelCommandL(const CLiwGenericParamList& aInParamList,
                                      MLiwNotifyCallback* aCallback,
                                      TUint aCmdOptions,
                                      TInt aTransId)
    Description     : This function parses the input param list
                    : and calls the Cancel on the given transaction id
    Return values   : TInt
-----------------------------------------------------------------------------
*/

TInt CContactInterface::CancelCommandL(const CLiwGenericParamList& aInParamList,
					        	       CLiwGenericParamList& aOutParamList)                                	   
	{
            
    TInt32 transactionID = 0;
	TInt errCode = KErrArgument;
	TInt pos = 0;
    const TLiwGenericParam* param = NULL;
    TLiwGenericParam posbasedparam;

            param = aInParamList.FindFirst( pos, KTransactionID );
            if((!param) && (aInParamList.Count()<=0))
                {
		        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
		                              TLiwVariant(KCancelTransIdMissing)));
		        User::Leave(KMissingArg);
                }
			else 
				{
                pos = 0;
                aInParamList.AtL( pos, posbasedparam );	
                
                if (posbasedparam.Value().IsEmpty() )
                    {
                    param = NULL;
                    }
                else
                    {
                    param = &posbasedparam;           
                    }
				}                 
            if( param )
			    {
			    param->Value().Get( transactionID );
                errCode = iContactService->Cancel( transactionID );
			    }
	    return errCode;	
	}

TPtrC CContactInterface::GetDefaultDBUri()
    {
       TPtrC dbUri;
       HBufC* defaultStoreUri = HBufC::NewL(KInitialStoreUriSize);
       TPtr ptr = defaultStoreUri->Des();
       TInt actualSize = 0;
       TInt ret = iRepository->Get
          (KPhonebookDefaultSavingStoreUri, ptr, actualSize);
        if (ret == KErrOverflow || ret != KErrNone)
        {
            delete defaultStoreUri;
            defaultStoreUri = NULL;
            defaultStoreUri = HBufC::NewL(actualSize);
            ptr.Set(defaultStoreUri->Des());
            TInt status = iRepository->Get(KPhonebookDefaultSavingStoreUri, ptr);
            if(status == KErrNone)
                {
                TPtrC dbUri(VPbkContactStoreUris::DefaultCntDbUri());
                delete defaultStoreUri;
                defaultStoreUri = NULL;
                return dbUri;
                }
            delete defaultStoreUri;
            defaultStoreUri = NULL;
         }   
       dbUri.Set(ptr);
       return dbUri;
    }
	
/*
-----------------------------------------------------------------------------
    CContactInterface::AddCommandL(const CLiwGenericParamList& aInParamList,
                                   MLiwNotifyCallback* aCallback,
                                   TUint aCmdOptions,
                                   TInt aTransId)
    Description     : This function parses the input param list
                    : and calls the Add API
    Return values   : TInt
-----------------------------------------------------------------------------
*/

void CContactInterface::AddCommandL(const CLiwGenericParamList& aInParamList,
                                    CLiwGenericParamList& aOutParamList,
                                    MLiwNotifyCallback* aCallback,
                                    TUint aCmdOptions,
                                    TInt aTransId)
    {
    TInt pos = 0;
    const TLiwGenericParam* paramAddData = NULL;
    const TLiwGenericParam* paramContentType = NULL;

	if(aInParamList.Count()<2)
		{
		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,
		                       TLiwVariant(KAddLessArguments) ) );  
		
		User::Leave(KMissingArg); 

		}
	//get the content type and add data.    
	paramContentType = aInParamList.FindFirst( pos, KType );
	if(!paramContentType)
		{
		paramContentType = &aInParamList[0];					    		
		if(!paramContentType || paramContentType->Name().Compare(KNullDesC8) != 0)
			{
			// Append error message 
			aOutParamList.AppendL(TLiwGenericParam (KErrorMessage,
			                      TLiwVariant(KAddContentTypeMissing)));  

			User::Leave(KMissingArg); 
			}
		}
	
	pos = 0;
    //Get the add data, the value of which is a Map
    paramAddData = aInParamList.FindFirst( pos, KData );
    if(!paramAddData)
    	{
    	paramAddData = &aInParamList[1];
    	
		if(!paramAddData || paramAddData->Name().Compare(KNullDesC8) != 0)
			{
			// Append error message 
			aOutParamList.AppendL(TLiwGenericParam ( KErrorMessage,
			                      TLiwVariant(KAddDataMissing) ) );  	
			User::Leave(KMissingArg); 
			}
    	}
    
	//get the content type.
	TLiwVariant contentTypeVar  = paramContentType->Value();
	
	if(EVariantTypeDesC != contentTypeVar.TypeId())
		{
		contentTypeVar.Reset();
		aOutParamList.AppendL(TLiwGenericParam ( KErrorMessage,
		                      TLiwVariant(KAddWrongContentType) ) );  	
		User::Leave(KErrArgument); 
			
		}

    //if content type is "Contacts" then....
    if(contentTypeVar.AsDes().CompareF(KContact) == 0 )
        {
        contentTypeVar.Reset();
        //get the liw map from the add data generic parameter.
        //if map is not null then call the function ProcesAddDataL(),
        //which will parse the map and gets dburi and creates a new contact.
        const CLiwMap* pMap = paramAddData->Value().AsMap();
        if( pMap )
            {            
            //create a new contact.
            CSingleContact* contact = CSingleContact::NewL();
            CleanupStack::PushL(contact);
            //call to ProcessAddDataL to parse the
            //map and create a new contact.
            ProcessAddDataL(pMap, contact, aOutParamList);
            
            if( aCmdOptions == KLiwOptASyncronous )
                {
                CContactInterfaceCallback* contactCallback =
                    CContactInterfaceCallback::NewL(contact);

                CleanupStack :: PushL(contactCallback);
                //set the callback parameter values.
                contactCallback->SetParams(aCallback,
                                           aTransId,
                                           &aInParamList);

                //invoke the main method of contactService
                //to add/edit a contact/group
                //into the database.
                    iContactService->AddL(contactCallback,
                                          aTransId,
                                          contact,
                                          KNullDesC8, //group id
                                          KNullDesC, //group label
                                          *iDburi);

                CleanupStack :: Pop(contactCallback);
                }
            else
                {
                //it is assumed that the call is synchronous
             
                HBufC8* cntIdVal = NULL;
                TRAPD(err, cntIdVal = iContactService->AddL(contact,
                        KNullDesC8, //group id
                        KNullDesC, //group label
                        *iDburi)); 
                          
               
                if(err == KErrNotSupported)
                    {
                    TInt errkey  = iContactService->GetErrKey();
                    TPtrC8 ptr = CSearchFields::GetFieldKeyFromId(errkey);
            		TBuf<25> buff;
                    buff.Copy(ptr);
                    TBuf<KMaxName> errmsg(KAddFieldKeyNotSupported);    		
            		errmsg.Append(buff);
                    aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                          TLiwVariant(errmsg))); 
                    User::Leave(err);                          
                    } 
 
               if(err == KErrNone)
                   {
                HBufC* cntIdUnicode = HBufC::NewL(cntIdVal->Length());
                            CleanupStack :: PushL(cntIdUnicode);
                            cntIdUnicode->Des().Copy(*cntIdVal);
                            delete cntIdVal;
                            cntIdVal = NULL;
                            CContactInterfaceCallback::ContactIDToUTF(cntIdUnicode);           
                       aOutParamList.AppendL(TLiwGenericParam(KReturnValue,TLiwVariant(*cntIdUnicode)));
                       CleanupStack :: Pop(cntIdUnicode);
                    }
                else
                    {
                    User::Leave(err);
                    }
                } 
            CleanupStack::Pop();
            CleanupStack::Pop(contact);
            } //end of if pMap
        else
            {
            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                  TLiwVariant(KAddInvalidDataType)));     
            User::Leave(KErrArgument);                          
            }     
        } //end of if contentType == KContact
    //if content type is "Groups", then....
    else if(contentTypeVar.AsDes().CompareF(KGroup)==0)
        {
        contentTypeVar.Reset();
        //get the map from the addgroup data.
        const CLiwMap* pMap = paramAddData->Value().AsMap();
        if(pMap)
            {
            TLiwVariant valueGrpid;
		    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueGrpid) );

            TLiwVariant valueGrplabel;
		    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueGrplabel));
            
			TLiwVariant valueUri;
		    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueUri) );

			//set the Db Uri to default database.
            TPtrC dbUri = GetDefaultDBUri();
            TPtrC grpIdUnicode(KNullDesC);
            TPtrC grpLabel(KNullDesC);

            HBufC8* groupId = NULL;                
            if( EFalse != pMap->FindL(KDBUri,valueUri))
            {
            if( valueUri.AsDes().CompareF(KNullDesC) != 0 )
                {
                dbUri.Set(valueUri.AsDes());
                }
            }
        if(EFalse != pMap->FindL(KGroupId,valueGrpid)) 
            {
            TInt typeofgrpId = valueGrpid.TypeId();
            TPtrC grpIdUnicode = valueGrpid.AsDes();      
			if(grpIdUnicode == NULL)
				{
				CleanupStack::Pop(&valueGrpid);
				valueGrpid.Reset();
				aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KAddInvalGrpId) ) );  	
				User::Leave(KErrArgument); 
				//Leave	
				}
            //Convert the values back to the 8 bit descriptor.
            groupId = ContactIDUTFToStreamL(grpIdUnicode);                
            }
        else
            {
            groupId = KNullDesC8().AllocL();    
            }
        //get the values for dburi, group id and group label           
        if(EFalse != pMap->FindL(KGroupLabel,valueGrplabel))
            {                
			if(EVariantTypeDesC != valueGrplabel.TypeId())	
				{
				CleanupStack::Pop(&valueUri);
                valueUri.Reset();				
				CleanupStack::Pop(&valueGrplabel);
				valueGrplabel.Reset();
				CleanupStack::Pop(&valueGrpid);
				valueGrpid.Reset();

				aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KAddInvalGrpLabel) ) );  	
				User::Leave(KErrArgument); 
				//Leave	
				}
            if( valueGrplabel.AsDes().CompareF(KNullDesC) != 0)	
				{
				grpLabel.Set(valueGrplabel.AsDes());	
				}
			else
				{
				aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KAddGroupLabelEmpty) ) );  	
				User::Leave(KErrArgument); 
				}
            }
        else
            {
            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                  TLiwVariant(KAddLabelMissing)));
                                  
            User::Leave(KErrArgument);                          
            }    
        CleanupStack :: PushL(groupId);
        //All the params are retrieved now call the main api.
        if( aCmdOptions == KLiwOptASyncronous )
            {
            CContactInterfaceCallback* contactCallback =
                CContactInterfaceCallback::NewL();

            CleanupStack :: PushL(contactCallback);
            //set the parameters for callback
            contactCallback->SetParams(aCallback,
                                       aTransId,
                                       &aInParamList);

            //invoke the main method of the contactService to Add/Edit Group.
            iContactService->AddL(contactCallback,
                                  aTransId,
                                  NULL,
                                  *groupId,
                                  grpLabel,
                                  dbUri);

            CleanupStack :: Pop(contactCallback);
            }
        else
            {
            //it is assumed that the call is synchronous
            HBufC8* grpId = NULL;
            TRAPD(err,grpId = iContactService->AddL(NULL,
                                  *groupId,
                                  grpLabel,
                                  dbUri));
            if(err == KErrNotSupported)
                {
                TInt errkey  = iContactService->GetErrKey();
                TPtrC8 ptr = CSearchFields::GetFieldKeyFromId(errkey);
        		TBuf<25> buff;
                buff.Copy(ptr);
                TBuf<KMaxName> errmsg(KAddFieldKeyNotSupported);    		
        		errmsg.Append(buff);
                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(errmsg))); 
                User::Leave(err);                          
                }
            if(err == KErrNone)
                {
                if(grpId)
                    {
                HBufC* grpIdUnicode = HBufC::NewL(grpId->Length());
                CleanupStack :: PushL(grpIdUnicode);
                grpIdUnicode->Des().Copy(*grpId);
                delete grpId;
                grpId = NULL;
                CContactInterfaceCallback::ContactIDToUTF(grpIdUnicode);           
                              
               aOutParamList.AppendL(TLiwGenericParam(KReturnValue,TLiwVariant(*grpIdUnicode)));
               CleanupStack :: Pop(grpIdUnicode);
                    }
                }
            else
                {
                User::Leave(err);
                }

                                         
            }
	        CleanupStack :: PopAndDestroy(groupId); 
	        CleanupStack::Pop(&valueUri);
	        valueUri.Reset();
	        CleanupStack::Pop(&valueGrplabel);                         
	        valueGrplabel.Reset();
			CleanupStack::Pop(&valueGrpid);
			valueGrpid.Reset();
		  }
         else
            {
            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                  TLiwVariant(KAddInvalidDataType)));    
			User::Leave(KMissingArg); 
            }     

        }
	else
	    {
        contentTypeVar.Reset();

	    aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
	                          TLiwVariant(KAddInvalidContentType)));     
        User::Leave(KErrArgument);                          
	    }
	 
    }

/*
-----------------------------------------------------------------------------
    CContactInterface::ImportCommandL(const CLiwGenericParamList& aInParamList,
                                      MLiwNotifyCallback* aCallback,
                                      TUint aCmdOptions,
                                      TInt aTransId)
    Description     : This function parses the input param list
                    : and calls the Import API
    Return values   : TInt
-----------------------------------------------------------------------------
*/
void CContactInterface::ImportCommandL(const CLiwGenericParamList& aInParamList,
                                       CLiwGenericParamList& aOutParamList,
                                       MLiwNotifyCallback* aCallback,
                                       TUint aCmdOptions,
                                       TInt aTransId)
    {
    TInt pos = 0;
    const TLiwGenericParam* paramImportData = NULL;
    const TLiwGenericParam* paramContentType = NULL;

    //get the content type and import data.
    paramContentType = aInParamList.FindFirst( pos, KType );
    
	if(!paramContentType)
		{
		
		if(aInParamList.Count()<2)
			{
					
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KImportLessArguments) ) );  	
			User::Leave(KMissingArg); 
			}
			paramContentType = &aInParamList[0] ;
			if(!paramContentType || paramContentType->Name().Compare(KNullDesC8) != 0)
				{
				// Append error message 
				aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KImportContentTypeMissing) ) );  	
				User::Leave(KMissingArg); 
				}
		}	
	pos = 0;
    //Get the delete data, the value of which is a Map
    paramImportData = aInParamList.FindFirst( pos, KData );
    if(!paramImportData)
    	{
		if(aInParamList.Count()>1)
			paramImportData = &aInParamList[1] ;
		if(!paramImportData || paramImportData->Name().Compare(KNullDesC8) != 0)
			{
			// Append error message
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KImportDataMissing) ) );  	
			User::Leave(KMissingArg); 
			}
    	}	
    
	TLiwVariant cnttent = paramContentType->Value();
	
	if(EVariantTypeDesC !=cnttent.TypeId())
		{
		cnttent.Reset();
		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KImportWrongContentType) ) );  	
		User::Leave(KErrArgument); 
			
		}
	cnttent.Reset();

    TPtrC contentType;
	contentType.Set(paramContentType->Value().AsDes());

	// Check for content type
	
	if(contentType !=KContact)
		{
			
		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KImportInvalidContentType) ) );  
		User::Leave(KErrArgument);			
		}

        //get the liw map from the import data generic parameter.
        //if map is not null then get db name, source file from the
        //contact has to be imported.
        const CLiwMap* pMap = paramImportData->Value().AsMap();
        if(NULL != pMap)
            {
            //TPtrC  dburi(VPbkContactStoreUris::DefaultCntDbUri());
            TPtrC dburi = GetDefaultDBUri();
            TLiwVariant valueFname;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueFname) );

            TLiwVariant valueUri;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueUri) );

            if( EFalse != pMap->FindL(KDBUri,valueUri))
                {
                 if(EVariantTypeDesC != valueUri.TypeId())
	                {
	                
	                CleanupStack::Pop(&valueUri);
	                valueUri.Reset();
	                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
	                                  TLiwVariant(KImportDbUriNotString)));     
	          		User::Leave(KErrArgument);			
	                	
	                }
   
                if(valueUri.AsDes().CompareF(KNullDesC)!=0)
                    {
                    dburi.Set(valueUri.AsDes());
                    }
                }
            if(EFalse != pMap->FindL(KSourceFileNameParam,valueFname))
                {
                //get the uri and filename.
                if(EVariantTypeDesC != valueFname.TypeId())
	                {
	                CleanupStack::Pop(&valueUri);
	                valueUri.Reset();
	                CleanupStack::Pop(&valueFname);
	                valueFname.Reset();
	                
	                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
	                                  TLiwVariant(KImportSrcFileNotString)));     
	          		User::Leave(KErrArgument);			
	                	
	                }
                TPtrC filename = valueFname.AsDes();
				TInt length = filename.Length();
				
				if(length > KMaxFileName)
					{
					aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
				                  TLiwVariant(KImportFileNameTooLong)));
					User::Leave(KErrBadName);
					}
                
                if( aCmdOptions == KLiwOptASyncronous )
                    {
                    CContactInterfaceCallback* contactCallback =
                        CContactInterfaceCallback::NewL();

                    CleanupStack::PushL(contactCallback);
                    //if callback is not null, set the params like
                    //callback, transid..etc
                    contactCallback->SetParams(aCallback,
                                               aTransId,
                                               &aInParamList);
                    //invoke the main method of contact service
                    //to import the contact.
                        iContactService->ImportVCardToStoreL(contactCallback,
                    										 aTransId,
                    										 filename,
                    										 dburi);
                    CleanupStack::Pop(contactCallback);

                    }
                else
                    {
                    //it is assumed that the call is synchronous
                    iContactService->ImportVCardToStoreL(filename,
                    								     dburi);
                    }
                }
            else
                {
                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                  TLiwVariant(KImportSrcFileNameMissing)));     
                User::Leave(KMissingArg);
                }    
            CleanupStack::Pop(&valueUri);    
            valueUri.Reset();
            CleanupStack::Pop(&valueFname);
            valueFname.Reset();
            }
            
        else
            {
            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                  TLiwVariant(KImportDataMapMissing)));
            User::Leave(KMissingArg);
            }    
    }

/*
-----------------------------------------------------------------------------
    CContactInterface::ExportCommandL(const CLiwGenericParamList& aInParamList,
                                      MLiwNotifyCallback* aCallback,
                                      TUint aCmdOptions,
                                      TInt aTransId)
    Description     : This function parses the input param list
                    : and calls the Export API
    Return values   : TInt
-----------------------------------------------------------------------------
*/
void CContactInterface::ExportCommandL(const CLiwGenericParamList& aInParamList,
                                       CLiwGenericParamList& aOutParamList,
                                       MLiwNotifyCallback* aCallback,
                                       TUint aCmdOptions,
                                       TInt aTransId)
    {
    TInt pos = 0;
    const TLiwGenericParam* paramExportData = NULL;
    const TLiwGenericParam* paramContentType = NULL;
    //get the content type and export data.
    paramContentType = aInParamList.FindFirst( pos, KType );

	//get the content type and export data.    
	if(!paramContentType)
		{
		
		if(aInParamList.Count()<2)
			{
					
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KExportLessArguments) ) );  	
			User::Leave(KMissingArg); 
			}
		
		paramContentType = &aInParamList[0] ;
		if(!paramContentType || paramContentType->Name().Compare(KNullDesC8) != 0)
			{
			// Append error message
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KExportContentTypeMissing) ) );  	
			User::Leave(KMissingArg); 
			}
		}
	
	pos = 0;
    //Get the export data, the value of which is a Map
    paramExportData = aInParamList.FindFirst( pos, KData );
    if(!paramExportData)
    	{
		if(aInParamList.Count()>1)
    		paramExportData = &aInParamList[1] ;
		if(!paramExportData || paramExportData->Name().Compare(KNullDesC8) != 0)
			{
			// Append error message
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KExportDataMissing) ) );  	
			User::Leave(KMissingArg); 
			}
    	}	

	TLiwVariant cnttent = paramContentType->Value();
	
	if(EVariantTypeDesC !=cnttent.TypeId())
		{
		cnttent.Reset();
		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KExportWrongContentType) ) );  	
		User::Leave(KErrArgument); 
			
		}
	cnttent.Reset();
    	


    TPtrC contentType;
	contentType.Set(paramContentType->Value().AsDes());

	// Check for content type
	if(contentType.Compare(KContact) != 0) 
		{
			
		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KExportInvalidContentType) ) );  
		User::Leave(KErrArgument);			
		}

        //get the liw map from the export data generic parameter.
        //if map is not null then get db name, contact id and dest file
        //to whi the contact has to be exported.
        const CLiwMap* pMap = paramExportData->Value().AsMap();
        if(NULL != pMap)
            {
            TLiwVariant valueFname;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueFname) );

            TLiwVariant valueUri;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueUri) );

            //TPtrC dburi(VPbkContactStoreUris::DefaultCntDbUri());
            TPtrC dburi = GetDefaultDBUri();
            if( EFalse != pMap->FindL(KDBUri,valueUri))
                {
                if(EVariantTypeDesC != valueUri.TypeId())
					{
					aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
					              TLiwVariant(KExportDbUriNotString)));
					User::Leave(KErrArgument);

					}
                if(valueUri.AsDes().CompareF(KNullDesC)!=0)
                    {
                    dburi.Set(valueUri.AsDes());
                    }
                }
            if(EFalse != pMap->FindL(KDestFileNameParam,valueFname))
                {
                
                if(EVariantTypeDesC !=valueFname.TypeId() )
					{
					aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
					                  TLiwVariant(KExportDestnFlNmWrongType)));
					User::Leave(KErrArgument);
					}
                TLiwVariant valueCntid;
                CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueCntid) );

                if(EFalse != pMap->FindL(KContactId,valueCntid))
                    {
                    //get dburi, filename and contact id parameters from the map.
					if(EVariantTypeDesC != valueCntid.TypeId())
						{
						aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
						                  TLiwVariant(KExportContactIdWrongType)));
						User::Leave(KErrArgument);

						}
						TPtrC filename = valueFname.AsDes();
						TInt length = filename.Length();
						
						if(length > KMaxFileName)
							{
							aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
						                  TLiwVariant(KExportFileNameTooLong)));
							User::Leave(KErrBadName);
							}

	                    TPtrC cntIdUnicode = valueCntid.AsDes();
                    
                    HBufC8* cntid = ContactIDUTFToStreamL(cntIdUnicode);
                    CleanupStack::PushL(cntid);                    

                    if( aCmdOptions == KLiwOptASyncronous )
                        {
                        CContactInterfaceCallback* contactCallback =
                            CContactInterfaceCallback::NewL();
                        CleanupStack :: PushL(contactCallback);
                        //if callback is not null, set the params like callback, transid..etc
                        contactCallback->SetParams(aCallback,
                                                   aTransId,
                                                   &aInParamList);
                        //invoke the main method of contact service to export the contact.
                            iContactService->ExportVCardL(contactCallback,
                                    					  aTransId,
                                    					  filename,
                                    					  *cntid ,
                                    					  dburi);
                        CleanupStack :: Pop(contactCallback);
                        }
                    else
                        {
                        //it is assumed that the call is synchronous
                        iContactService->ExportVCardL(filename,
                                                      *cntid,
                                                	  dburi);


                        }
                    CleanupStack :: PopAndDestroy(cntid);
                    } //end of if Find of cntid
                else
	                {
	                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
	                                      TLiwVariant(KExportContactIdMissing)));    
        			User::Leave(KMissingArg);
	                                      
	                } 
	            CleanupStack::Pop(&valueCntid);
                valueCntid.Reset();
                }
            else
                {
                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KExportDstFileNameMissing)));    
    		    User::Leave(KMissingArg);

                }
            CleanupStack::Pop(&valueUri);
            valueUri.Reset();
            CleanupStack::Pop(&valueFname);
            valueFname.Reset();
            }
        else
            {
            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                  TLiwVariant(KExportDataMapMissing)));    
	        User::Leave(KMissingArg);

            }    
    }

/*
-----------------------------------------------------------------------------
    CContactInterface::DeleteCommandL(const CLiwGenericParamList& aInParamList,
                                      MLiwNotifyCallback* aCallback,
                                      TUint aCmdOptions,
                                      TInt aTransId)
    Description     : This function parses the input param list
                    : and calls the Delete API
    Return values   : TInt
-----------------------------------------------------------------------------
*/
void CContactInterface::DeleteCommandL(const CLiwGenericParamList& aInParamList,
                                       CLiwGenericParamList& aOutParamList,
                                       MLiwNotifyCallback* aCallback,
                                       TUint aCmdOptions,
                                       TInt aTransId)
    {
    TInt pos = 0;
    const TLiwGenericParam* paramDeleteData = NULL;
    const TLiwGenericParam* paramContentType = NULL;

    //get the content type and delete data.
    paramContentType = aInParamList.FindFirst(pos, KType);
	if(!paramContentType)
		{

		if(aInParamList.Count()<1)
			{
					
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KDeleteLessArguments) ) );  	
			User::Leave(KMissingArg); 
			}
		if(aInParamList.Count()>0)
			paramContentType = &aInParamList[0] ;	
		if(!paramContentType || paramContentType->Name().Compare(KNullDesC8) != 0)
			{
			
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KDeleteContentTypeMissing) ) );  	
			User::Leave(KMissingArg); 
			}
		}
	
	pos = 0;
    //Get the delete data, the value of which is a Map
    paramDeleteData = aInParamList.FindFirst( pos, KData );
    if(!paramDeleteData)
    	{
    	if(aInParamList.Count()>1)
    		paramDeleteData = &aInParamList[1] ;
		if(!paramDeleteData || paramDeleteData->Name().Compare(KNullDesC8) != 0)
			{
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KDeleteDataMissing) ) );  	
			User::Leave(KMissingArg); 
			}
    	}
	
	//Get the content type
	TLiwVariant contentTypeVar  = paramContentType->Value();
	
	if(EVariantTypeDesC !=contentTypeVar.TypeId())
		{
		contentTypeVar.Reset();
		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KDeleteWrongContentType) ) );  	
		User::Leave(KErrArgument); 
		
			
		}
	
    //either gorups or contacts
    if(contentTypeVar.AsDes() == KContact || contentTypeVar.AsDes() == KGroup)
        {
        //get the map from the delete data generic parameter.
        const CLiwMap* pMap = paramDeleteData->Value().AsMap();
        if( pMap )
            {
            TLiwVariant valueList;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueList) );

            TLiwVariant valueUri;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueUri) );

            TLiwVariant valueId;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueId) );

            //TPtrC dbUri(VPbkContactStoreUris::DefaultCntDbUri());
            TPtrC dbUri = GetDefaultDBUri();
            const CLiwList* contactIdList = NULL;

            if( EFalse != pMap->FindL(KDBUri,valueUri))
                {
                if(valueUri.AsDes().CompareF(KNullDesC)!=0)
                    {
                    dbUri.Set(valueUri.AsDes());
                    }
                }
            //get the dbUri and contact id list from the map.
            if(EFalse != pMap->FindL(KList,valueList) )
                {
				if(EVariantTypeList != valueList.TypeId())
					{
					aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KDeleteInvalidTypeIdList) ) );  	
					User::Leave(KErrArgument); 
					}
                contactIdList = valueList.AsList();
				
                //get the contact id count in the list.
                TInt idCount = contactIdList->Count();
                //create the array of contact ids from the liw list.
                RPointerArray<TDesC8> contactIdArray;
                for(TInt index = 0; index < idCount; index++)
                    {
                    contactIdList->AtL(index, valueId);
					if(EVariantTypeDesC !=valueId.TypeId())
						{
						aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KDeleteInvalidIdType) ) );  	
						User::Leave(KErrArgument); 
						}
                    
                    TPtrC cntidptr = valueId.AsDes();
                    HBufC8* cntid = ContactIDUTFToStreamL(cntidptr);
                    CleanupStack :: PushL(cntid);                        
                    contactIdArray.AppendL(cntid);
                    CleanupStack :: Pop(cntid);

                    }
                if(aCmdOptions == KLiwOptASyncronous)
                    {
                    CContactInterfaceCallback* contactCallback =
                        CContactInterfaceCallback::NewL();

                    CleanupStack :: PushL(contactCallback);
                    //set the basic params of callback object.
                    contactCallback->SetParams(aCallback,
                                               aTransId,
                                               &aInParamList);
                    //invoke the main method of contactservice
                    //to delete the list
                    //contacts/groups.
                        iContactService->DeleteL(contactCallback,
                                    			 aTransId,
                                    			 contactIdArray,
                                    			 dbUri);

                    CleanupStack :: Pop(contactCallback);
                    }
                else
                    {
                    //it is assumed that the call is synchronous
                    iContactService->DeleteL(contactIdArray,
                                             dbUri);
                    }

                }//if pMap
            else
                {
                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KDeleteDataListMissing)));
				User::Leave(KMissingArg); 
                }   
            CleanupStack::Pop(&valueId);
            valueId.Reset();
            CleanupStack::Pop(&valueUri);
            valueUri.Reset();
            CleanupStack::Pop(&valueList);
            valueList.Reset();
            }
        else
            {
            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                          TLiwVariant(KDeleteDataMapMissing)));    
			User::Leave(KMissingArg); 
            } 
        contentTypeVar.Reset();
        }//if ContentType == KContact or KGroup
    else
        {
        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                          TLiwVariant(KDeleteInvalidContentType)));     
        User::Leave(KErrArgument); 
        }    
    }

/*
-----------------------------------------------------------------------------
    CContactInterface::OrganiseGroupCommandL(const CLiwGenericParamList& aInParamList,
                                             MLiwNotifyCallback* aCallback,
                                             TUint aCmdOptions,
                                             TInt aTransId)
    Description     : This function parses the input param list
                    : and calls the Organise API
    Return values   : TInt
-----------------------------------------------------------------------------
*/
void CContactInterface::OrganiseGroupCommandL(const CLiwGenericParamList& aInParamList,
                                              CLiwGenericParamList& aOutParamList,
                                              MLiwNotifyCallback* aCallback,
                                              TUint aCmdOptions,
                                              TInt aTransId)
    {
    TInt position = 0;
    const TLiwGenericParam* paramOrganiseData = NULL;
    const TLiwGenericParam* paramOperationType = NULL;
    const TLiwGenericParam* paramContentType = NULL;

    //get the content type and Organise data.
	paramContentType = aInParamList.FindFirst( position, KType );
	if(!paramContentType)
		{
		if(aInParamList.Count()<3)
			{

			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KOrganiseLessArguments) ) );  	
			User::Leave(KMissingArg); 
			}
		
	
		paramContentType = &aInParamList[0] ;
		if(!paramContentType || paramContentType->Name().Compare(KNullDesC8) != 0)
			{
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KOrganiseContentTypeMissing) ) );  	
			User::Leave(KMissingArg); 
			}
		}

	position = 0;
    //Get the orgainse  data, the value of which is a Map
    paramOrganiseData = aInParamList.FindFirst( position, KData );
    if(!paramOrganiseData)
    	{
    	if(aInParamList.Count()>2)
    		paramOrganiseData = &aInParamList[1] ;
		if(!paramOrganiseData || paramOrganiseData->Name().Compare(KNullDesC8) != 0)
			{
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KOrganiseDataMissing) ) );  	
			User::Leave(KMissingArg); 
			}
    	}	

	position = 0;
    //Get the operation type, the value of which is a Map
    paramOperationType = aInParamList.FindFirst( position, KOperationType );
    if(!paramOperationType)
    	{
    	if(aInParamList.Count() == 3)
    		paramOperationType = &aInParamList[2] ;
		if(!paramOperationType || paramOperationType->Name().Compare(KNullDesC8) != 0)
			{
			aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KOrganiseOperationTypeMissing) ) );  	
			User::Leave(KMissingArg); 
			}
    	}	    	

    //get the content type..
	TLiwVariant contentTypeVar  = paramContentType->Value();
	
	if(EVariantTypeDesC !=contentTypeVar.TypeId())
		{
		contentTypeVar.Reset();
		aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KOrganiseWrongContentType) ) );  

		User::Leave(KErrArgument); 
		}

    //if content type is " Groups", then....
   	 if( contentTypeVar.AsDes() == KGroup)
        {
        //get the pointer to map in the organise data.
        const CLiwMap* pMap = paramOrganiseData->Value().AsMap();
        if( pMap )
            {
            TLiwVariant valueGroupid;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueGroupid) );

            TLiwVariant valueList;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueList) );
            
			TLiwVariant valueUri;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueUri) );

            //TPtrC dbUri(VPbkContactStoreUris::DefaultCntDbUri());
            TPtrC dbUri = GetDefaultDBUri();
            TBool associateType = EFalse;
            HBufC8* groupId = NULL;

			if(EVariantTypeDesC != paramOperationType->Value().TypeId() )
				{
				aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KOrganiseOperationTypeWrong) ) );  	
				User::Leave(KErrArgument); 
				}

            if(paramOperationType->Value().AsDes().Compare(KAssociate)==0)
                {
                associateType = ETrue;
                }
            else if(paramOperationType->Value().AsDes().Compare(KDissociate)==0)
                {
                associateType = EFalse;
                }
            else
                {
                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                          TLiwVariant(KOrganiseDataInvalidOpType)));
                User::Leave(KErrArgument);
                }

            const CLiwList* contactIdList = NULL;
            //get the values for dburi, groupid, associatetype and id list.
            if( EFalse != pMap->FindL(KDBUri,valueUri))
                {
                if(valueUri.AsDes().CompareF(KNullDesC)!=0)
                    {
                    dbUri.Set(valueUri.AsDes());
                    }
                }
                
            if(EFalse != pMap->FindL(KGroupId,valueGroupid))
                {
			 	if(EVariantTypeDesC != valueGroupid.TypeId())
				 	{
					aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KOrganiseWrongGrpIdType) ) );  	

			        User::Leave(KErrArgument);
				 	}
                TPtrC grpid = valueGroupid.AsDes();
                groupId = ContactIDUTFToStreamL(grpid);                   
                }
            else
                {
                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                          TLiwVariant(KOrganiseGrpIdMissing)));
                User::Leave(KMissingArg);
                }
                
             if(EFalse != pMap->FindL(KList,valueList))
                {
				if(EVariantTypeList != valueList.TypeId())
					{
					aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KOrganiseWrongIdListType) ) );  	
			        User::Leave(KErrArgument);
					}
                contactIdList = valueList.AsList();
                }
            else
                {
                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                          TLiwVariant(KOrganiseDataListMissing)));
                User::Leave(KMissingArg);
                }

            CleanupStack :: PushL(groupId);
            //get the number of contact ids in the list.
            TInt idCount = contactIdList->Count();
            if(idCount == 0)
		        {
				aOutParamList.AppendL( TLiwGenericParam ( KErrorMessage,TLiwVariant(KOrganiseEmptyIdList) ) );  	
		        User::Leave(KErrArgument);
	            }
            TLiwVariant valueId;
            CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &valueId) );

            //create the contact id array and append the ids from the list to this
            //contactIdArray
            RPointerArray<TDesC8> contactIdArray;
            CleanupClosePushL(contactIdArray);
            
            for(TInt index = 0; index < idCount; index++)
                {
                contactIdList->AtL(index, valueId);
				if(EVariantTypeDesC != valueId.TypeId())
					{
		            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
		                      TLiwVariant(KOrganiseWrongIdType)));
		            User::Leave(KErrArgument);
					}
             
                TPtrC cntIdUnicode = valueId.AsDes();
                HBufC8* cntid = ContactIDUTFToStreamL(cntIdUnicode);
                CleanupStack :: PushL(cntid);                    
                contactIdArray.AppendL(cntid);
                }
            if(aCmdOptions == KLiwOptASyncronous)
                {
                CContactInterfaceCallback* contactCallback =
                    CContactInterfaceCallback::NewL();

                CleanupStack :: PushL(contactCallback);
                //Set the params of the contact callback
                contactCallback->SetParams(aCallback,
                                           aTransId,
                                           &aInParamList);
                //invoke the main method of the contactService
                //to Associate/Disassocite
                //list of contacts to/from the group.
                    iContactService->OrganiseGroupsL(contactCallback,
                        							 aTransId,
                        							 *groupId,
                        							 contactIdArray,
                        							 associateType,
                        							 dbUri);

                CleanupStack :: Pop(contactCallback);
                }
            else
                {
                //it is assumed that the call is synchronous
                iContactService->OrganiseGroupsL(*groupId,
                                				 contactIdArray,
                                				 associateType,
                                				 dbUri);
                }
            //cleanup
            CleanupStack::PopAndDestroy(contactIdArray.Count());
            CleanupStack::PopAndDestroy();
            CleanupStack::Pop(&valueId);
            valueId.Reset();
            CleanupStack::PopAndDestroy(groupId);
            CleanupStack::Pop(&valueUri);
            valueUri.Reset();
            CleanupStack::Pop(&valueList);
            valueList.Reset();
            CleanupStack::Pop(&valueGroupid);
            valueGroupid.Reset();
            }
        else
            {
            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                          TLiwVariant(KOrganiseDataMapMissing)));  
            User::Leave(KMissingArg);
                            
            }    
        contentTypeVar.Reset();
        }
    else
	    {
	    aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
	                  TLiwVariant(KOrganiseInvalidContentType)));  
	    User::Leave(KMissingArg);
	    }
    }
