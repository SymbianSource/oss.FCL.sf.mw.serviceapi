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


//  Include Files  

#include <e32std.h>		 // GLDEF_C
#include "tcontactsgetidsprovidertest.h"		// panic codes
#include "tcontactsgetidsprovidertest.hrh"
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <liwservicehandler.h>




using namespace LIW;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctcontactsgetidsprovidertest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcontactsgetidsprovidertest::Delete() 
    {  
    TInt count = iExpectedOutPutArray.Count();
    for(TInt index =0 ;index<count;index++)
        {
        iExpectedOutPutArray[index]->DecRef();          
        }    
    iExpectedOutPutArray.Close();    
    iIface->Close();   
    delete iServicehandler;   
    delete iInList;
    delete iOutList;   
    }


/* --------------------------------------------------------------------------
 Ctcontactsgetidsprovidertest :: LoadServiceL
 Loads the mediamanagement service.
-----------------------------------------------------------------------------
*/
void Ctcontactsgetidsprovidertest :: LoadServiceL()
    {
    TInt pos = 0;           
    iInList = CLiwGenericParamList::NewL();    
    
    iOutList = CLiwGenericParamList::NewL();    
    
    iServicehandler = CLiwServiceHandler::NewL();  
    
    CLiwCriteriaItem* criteria = CLiwCriteriaItem::NewL(1, 
                                                        KIDataSource, 
                                                        KService);    
    CleanupStack :: PushL(criteria);    
    
    criteria->SetServiceClass(TUid::Uid(KLiwClassBase));    
    RCriteriaArray critArray;
    critArray.AppendL(criteria);
    
    iServicehandler->AttachL(critArray);
    iServicehandler->ExecuteServiceCmdL(*criteria, 
                                       *iInList, 
                                       *iOutList);   
    
    iOutList->FindFirst( pos, KIDataSource );
    if(pos != KErrNotFound)
        {        
        iIface = (*iOutList)[pos].Value().AsInterface();
        }
    else
        {
        User::Leave(KErrNotFound);
        }                                             
    iInList->Reset();
    iOutList->Reset();    
    CleanupStack :: PopAndDestroy(criteria); 
    critArray.Close();
    }           


// -----------------------------------------------------------------------------
// Ctcontactsgetidsprovidertest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcontactsgetidsprovidertest::RunMethodL(CStifItemParser& aItem) 
    {
    static TStifFunctionInfo const KFunctions[] =
        {          
        ENTRY("GetIdsL", Ctcontactsgetidsprovidertest::GetIdsL),      
        ENTRY("AddContactAndGrp", Ctcontactsgetidsprovidertest::AddL)
        };
    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );
    return RunInternalL( KFunctions, count, aItem );
    }
    
// -----------------------------------------------------------------------------
// Callback:: HandleNotifyL
// Call Back Function Called by the Contacts SAPI.
// -----------------------------------------------------------------------------
//        
 TInt Ctcontactsgetidsprovidertest:: HandleNotifyL(TInt /*aCmdId*/,
                               TInt aEventId,
                               CLiwGenericParamList& aEventParamList,
                               const CLiwGenericParamList& /*aInParamList*/)
  { 
  TInt pos = 0;
  TInt error = KErrGeneral;
  iResult = KErrGeneral;
  
  TBuf<25> errorcodedes(KNullDesC);
  const TLiwGenericParam* errorCode = NULL;
  const TLiwGenericParam* resultList = NULL;
  CLiwIterable* iterator = NULL;
  
  CActiveScheduler::Stop();
  
  errorCode = aEventParamList.FindFirst(pos, KErrorCode); // Finding Error Code
  resultList = aEventParamList.FindFirst(pos, KResponse); // Finding Iterator for the result list
    
  if(errorCode)
      {
      error = errorCode->Value().AsTInt32();
      errorcodedes.Num(error);
      iLog->Log(_L("Error code:"));
      iLog->Log(errorcodedes);      
      }
  if(iExpErrorCode != error)
      {
      iLog->Log(_L("Expected Error code does not match"));
      User::Leave(KErrGeneral);
      }
  iResult = KErrNone;
  /* if(resultList)
      {
 //     iterator = resultList->Value().AsIterable();
   //   if(IsExpectedResult(iterator))
     //     {
          
       //   }
      }
  else
      {
      if(iExpectedOutPutArray.Count() != 0)
          {
          iLog->Log(_L("Result Iterator Not Found"));
          User::Leave(KErrNotFound);
          }
      } */
	return 0;
  }
 TInt Ctcontactsgetidsprovidertest::AddL( CStifItemParser& aItem )
     {  
     TInt error = KErrGeneral;
     TBuf<25> errcodedes(KNullDesC);
     LoadServiceL(); 
     aItem.GetNextInt(iExpErrorCode);
     CLiwDefaultMap* pMap = CLiwDefaultMap::NewL();    
        
    CLiwDefaultMap* fieldMap = CLiwDefaultMap::NewL();     
    TInt pos = 0;             
    fieldMap->InsertL(KFieldLabel,TLiwVariant(_L("firstname")));
        
    fieldMap->InsertL(KFieldValue,TLiwVariant(_L("Arnold")));
    //pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
    
    
    pMap->InsertL(KContactId, TLiwVariant( _L("")));
    pMap->InsertL(KFirstName, TLiwVariant(fieldMap));
    
    const TLiwGenericParam paramContentType(KType, TLiwVariant( _L("Contact"))); 
    const TLiwGenericParam paramAddData(KData, TLiwVariant(pMap)); ;
        
    iInList ->AppendL( paramContentType );
    iInList ->AppendL( paramAddData );   
     iIface->ExecuteCmdL(command9,
                         *iInList,
                         *iOutList); 
                         //KLiwOptASyncronous,
//                         this);    
     const TLiwGenericParam* p = iOutList->FindFirst(pos,
                                                     KErrorCode); // Finding Error Code
     if(p)
         {
         TInt retcode = p->Value().AsTInt32();
         errcodedes.Num(retcode);
         iLog->Log(_L("return  code:"));
         iLog->Log(errcodedes);    
         if(iExpErrorCode == retcode)
                 {
                 iLog->Log(errcodedes);
                 iResult = KErrNone;
                 }
             else
                 {
                 User::Leave(KErrGeneral);
                 }             
             }
            
     iInList->Reset();
     iOutList->Reset();
     iLog->Log(_L(""));
     
     
     pMap = CLiwDefaultMap::NewL();
     pos = 0;

     pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
     pMap->InsertL(KGroupId, TLiwVariant(_L8("")));
     pMap->InsertL(KGroupLabel, TLiwVariant(_L("Group1")));

     const TLiwGenericParam paramContentType1(KType, TLiwVariant( _L("Group")));
     const TLiwGenericParam paramAddData1(KData, TLiwVariant(pMap)); ;

     iInList ->AppendL( paramContentType1 );
     iInList ->AppendL( paramAddData1 );
     iIface->ExecuteCmdL(command9,
                              *iInList,
                              *iOutList);
                           //   KLiwOptASyncronous,
                             // this);  

     p = iOutList->FindFirst( pos, KErrorCode );
     TLiwVariant err = p->Value();
     TInt code = err.AsTInt32();

     if(p)
      {
      TInt retcode = p->Value().AsTInt32();
      errcodedes.Num(retcode);
      iLog->Log(_L("return  code:"));
      iLog->Log(errcodedes);    
      if(iExpErrorCode == retcode)
              {
              iLog->Log(errcodedes);
              iResult = KErrNone;
              }
          else
              {
              User::Leave(KErrGeneral);
              }             
      }
             
      iInList->Reset();
      iOutList->Reset();
      iLog->Log(_L(""));

       pMap = CLiwDefaultMap::NewL();
       pos = 0;

       pMap->InsertL(KDBUri, TLiwVariant( _L("cntdb://c:contacts.cdb")));
       pMap->InsertL(KGroupId, TLiwVariant(_L8("")));
       pMap->InsertL(KGroupLabel, TLiwVariant(_L("Group2")));

       const TLiwGenericParam paramContentType2(KType, TLiwVariant( _L("Group")));
       const TLiwGenericParam paramAddData2(KData, TLiwVariant(pMap)); ;

       iInList ->AppendL( paramContentType2 );
       iInList ->AppendL( paramAddData2 );
       iIface->ExecuteCmdL(command9,
                                *iInList,
                                *iOutList);
                            //    KLiwOptASyncronous,
                              //  this);  

       p = iOutList->FindFirst( pos, KErrorCode );
       if(p)
        {
        TInt retcode = p->Value().AsTInt32();
        errcodedes.Num(retcode);
        iLog->Log(_L("return  code:"));
        iLog->Log(errcodedes);    
        if(iExpErrorCode == retcode)
                {
                iLog->Log(errcodedes);
                iResult = KErrNone;
                }
            else
                {
                User::Leave(KErrGeneral);
                }             
        }
               
        iInList->Reset();
        iOutList->Reset();
        iLog->Log(_L(""));
   
         
         
     return iResult;
     }

 
/* --------------------------------------------------------------------------
 Ctmediaprovidertesting :: GetImageFilesL
 Calls the Getlist of Media management SAPI.
-----------------------------------------------------------------------------
*/
TInt Ctcontactsgetidsprovidertest::GetIdsL( CStifItemParser& aItem )
    {  
    TInt error = KErrGeneral;
    TBuf<25> errcodedes(KNullDesC);
    LoadServiceL(); 
    
    ParseStiffInput(aItem);
    
    iIface->ExecuteCmdL(command8,
                        *iInList,
                        *iOutList,
                        KLiwOptASyncronous,
                        this);    
    TInt pos = 0;
    const TLiwGenericParam* p = iOutList->FindFirst(pos,
                                                    KErrorCode); // Finding Error Code
    if(p)
        {
        TInt retcode = p->Value().AsTInt32();
        errcodedes.Num(retcode);
        iLog->Log(_L("return  code:"));
        iLog->Log(errcodedes);    
        if(KErrNone == retcode)
            {
            CActiveScheduler::Start();     
            }
        else
            {
            if(iExpErrorCode == retcode)
                {
                iResult = KErrNone;
                }
            else
                {
                User::Leave(KErrGeneral);
                }             
            }
        }   
    iInList->Reset();
    iOutList->Reset();
    iLog->Log(_L(""));
    return iResult;
    }


void  Ctcontactsgetidsprovidertest::ParseStiffInput(CStifItemParser& aItem)
    {
       TBuf<25> errorCode(KNullDesC);
       
       TPtrC16 expectedStart(KNullDesC);
       TPtrC16 type(KNullDesC);    
       TPtrC16 dburi(KNullDesC);
       TPtrC16 srchval(KNullDesC);    
       TPtrC16 sortorder(KNullDesC); 
       
       aItem.GetNextString(type);
       aItem.GetNextString(dburi);
       aItem.GetNextString(srchval);
       aItem.GetNextString(sortorder);
       
       aItem.GetNextInt(iExpErrorCode);
//       aItem.GetNextString(expectedStart);

       
  /*     if(type.CompareF(KContactType) == 0)
          { 
          itype = EContacts;
          }
       else if(type.CompareF(KGroupType) == 0)
          {
          itype = EGroups;
          }
       //check for expected key 
       //if it is there then get the expected result and put it into the map.
       if(expectedStart.CompareF(KExpectedStart) == 0)
           {                   
           SetExpectedOutputMap(aItem);           
           } */
       iLog->Log(_L("The Input Parameters are:"));    
       iLog->Log(type);
       iLog->Log(dburi);
       iLog->Log(srchval);
       iLog->Log(sortorder);

       errorCode.Num(iExpErrorCode);
       iLog->Log(_L("Expected Error code:"));
       iLog->Log(errorCode);
           
       CLiwDefaultMap *sortMap = NULL;    
       
       //set the content type to the fileinfo.
       if(type.Compare(_L("NULL")) != 0)
           {
           if(type.Compare(_L("NULLVALUE")) == 0) type.Set(KNullDesC); 
           const TLiwGenericParam paramContentType(KType, TLiwVariant(type)); 
           iInList->AppendL(paramContentType);
           }
          
       CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
       CleanupStack::PushL(filterMap);
               
       TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));  
       iInList->AppendL(filterParam);
       filterMap->DecRef();    
       
       //Set the DBUri input if it is specified.
       if(dburi.Compare(_L("NULL")) != 0)
           {
           if(dburi.Compare(_L("NULLVALUE")) == 0) dburi.Set(KNullDesC);            
           filterMap->InsertL(KDBUri,TLiwVariant(dburi));
           }
       //Get the contact or group id if it is specified.
 /*      if(cntorgrpid.Compare(_L("NULL")) != 0)
           {
           if(cntorgrpid.Compare(_L("NULLVALUE")) == 0) cntorgrpid.Set(KNullDesC);
           filterMap->InsertL(KCntOrGrpId,TLiwVariant(cntorgrpid));   
           } */
       //Get the search valu input if it is specified.     
       if(srchval.Compare(_L("NULL")) != 0)
           {
           if(srchval.Compare(_L("NULLVALUE")) == 0) srchval.Set(KNullDesC);
           filterMap->InsertL(KSearchVal,TLiwVariant(srchval));
           }      
       if(sortorder.Compare(_L("NULL")) != 0)
           {
           sortMap = CLiwDefaultMap::NewL();
           CleanupStack::PushL(sortMap);
           if(sortorder.Compare(_L("NULLVALUE"))== 0) sortorder.Set(KNullDesC);
           sortMap->InsertL(KSortOrder,TLiwVariant(sortorder));
           TLiwGenericParam sortParam(KSort, TLiwVariant(sortMap));
           iInList->AppendL(sortParam);     
           sortMap->DecRef(); 
           }
       //end of input params now look for expected params           
       if(sortMap)
           {
           CleanupStack::Pop(sortMap);
           }
       CleanupStack::Pop(filterMap); 
    }
    


/* --------------------------------------------------------------------------
 Ctcontactsgetidsprovidertest :: SetExpectedImageOutputMap.
 This method fills the expected output map.
-----------------------------------------------------------------------------
*/
void Ctcontactsgetidsprovidertest :: SetExpectedOutputMap(CStifItemParser& aItem)
    {
  /*  TPtrC16 nextString(KNullDesC);   
        
    iLog->Log(_L("Inside SetExpectedOutputMap"));
    
    aItem.GetNextString(nextString);
    /*
     * The expected output is in the format. 
     * [ExpectredStart StartMap Key Value[...]EndMap[...]ExpectedEnd].     
     */
 /*   while(nextString.CompareF(KExpectedEnd)!=0)
        {
        if(nextString.CompareF(KMapStart) == 0)
            {
            CLiwDefaultMap* expectedOutPutMap = CLiwDefaultMap::NewL(); 
            CleanupStack::PushL(expectedOutPutMap);
            aItem.GetNextString(nextString);
            
            while(nextString.CompareF(KMapEnd)!= 0)
                {
                TPtrC key;
                TPtrC value;                
                TBuf8<255> insertKey;                
                                
                key.Set(nextString);
                insertKey.Copy(key);
                
                if(key.CompareF(_L("FileSize"))==0)
                    {
                    TInt fileSize = -1;
                    aItem.GetNextInt(fileSize);                    
                    expectedOutPutMap->InsertL(insertKey, (TInt32)fileSize);                    
                    }
                else
                    {
                    aItem.GetNextString(nextString);
                    value.Set(nextString);
                    expectedOutPutMap->InsertL(insertKey, value);
                    }
                aItem.GetNextString(nextString);
                }
            
            iExpectedOutPutArray.Append(expectedOutPutMap);                        
            CleanupStack::Pop(expectedOutPutMap);
            }
        aItem.GetNextString(nextString);
        }*/  
    }

