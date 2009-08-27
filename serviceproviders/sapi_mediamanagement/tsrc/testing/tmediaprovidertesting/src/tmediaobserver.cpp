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
* Description:  ?Description
*
*/


// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <LiwServiceHandler.h>
#include<e32cmn.h>


#include "tmediaprovidertesting.h"
#include "tmediaprovidertesting.hrh"
#include "tmediaobserver.h"

_LIT(KFilenm,"C:\\Data\\Output");
/* --------------------------------------------------------------------------
 CMediaObserver :: SetInput
 Fills the input parameter list.
 The format of the cfg input is 
 key startRange endRange sortKey sortOrder errorcode 
 [Expected fileName fileExtension drive fileSize fileDate fileNameAndPath mimeType
 [Next "next map data"]]. 
-----------------------------------------------------------------------------
*/
void  CMediaObserver::ParseStiffInput(CStifItemParser& aItem)
 {  
     
     iFile.Write(_L8("In ParseStiffInput parsing input \n"));
 
    TPtrC16 expectedStart(KNullDesC);
    TPtrC16 key(KNullDesC);    
    TPtrC16 startRange(KNullDesC);
    TPtrC16 endRange(KNullDesC);
    TPtrC16 sortKey(KNullDesC);
    TPtrC16 sortOrder(KNullDesC);      
    TPtrC16 inpType(KNullDesC);
    TPtrC16 inpFileType(KNullDesC);
    
    aItem.GetNextString(inpType);
    aItem.GetNextString(inpFileType);
    aItem.GetNextString(key);
    aItem.GetNextString(startRange);
    aItem.GetNextString(endRange);
    aItem.GetNextString(sortKey);
    aItem.GetNextString(sortOrder);    
    aItem.GetNextInt(iExpErrorCode);
    aItem.GetNextString(expectedStart);
    
    TBuf8<100> buf;
    buf.Copy(inpType);
    buf.Append(_L8("\n"));
    iFile.Write(buf);
    buf.Zero();
    
    
    buf.Copy(inpFileType);
    buf.Append(_L8("\n"));
    iFile.Write(buf);
    buf.Zero();
    
    buf.Copy(key);
    buf.Append(_L8("\n"));
    iFile.Write(buf);
    buf.Zero();

    buf.Copy(startRange);
    buf.Append(_L8("\n"));
    iFile.Write(buf);
    buf.Zero();
    
    buf.Copy(endRange);
    buf.Append(_L8("\n"));
    iFile.Write(buf);
    buf.Zero();
    
    buf.Copy(sortKey);
    buf.Append(_L8("\n"));
    iFile.Write(buf);
    buf.Zero();
    
    buf.Copy(sortOrder);
    buf.Append(_L8("\n"));
    iFile.Write(buf);
    buf.Zero();
    
    buf.Num(iExpErrorCode);
    buf.Append(_L8("\n"));
    iFile.Write(buf);
    buf.Zero();

    buf.Copy(expectedStart);
    buf.Append(_L8("\n"));
    iFile.Write(buf);
    buf.Zero();
    
    if(inpFileType.CompareF(KFileTypeStreamingURL) == 0)
       { 
       iFiletype = EStreamingURLFile;
       }
    else if(inpFileType.CompareF(KFileTypeMusic) == 0)
       {
       iFiletype = EMusicFile;
       }
    //check for expected key 
    //if it is there then get the expected result and put it into the map.
    if(expectedStart.CompareF(KExpectedStart) == 0)
        {                   
        SetExpectedOutputMap(aItem);           
        }
  /*  iLog->Log(_L("The Input Parameters are:"));    
    iLog->Log(key);
    iLog->Log(startRange);
    iLog->Log(endRange);
    iLog->Log(sortKey);
    iLog->Log(sortOrder);    
    */    
    CLiwDefaultMap *sortMap = NULL;    
    
    //set the content type to the fileinfo.
    if(inpType.Compare(_L("NULL")) != 0)
        {
        if(inpType.Compare(_L("NULLVALUE")) == 0) inpType.Set(KNullDesC); 
        const TLiwGenericParam paramContentType(KType, TLiwVariant(inpType)); 
        iInList->AppendL(paramContentType);
        }
       
    CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
    CleanupStack::PushL(filterMap);
            
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));	
	iInList->AppendL(filterParam);
	filterMap->DecRef();	
	
	//Set the file type to image.
	if(inpFileType.Compare(_L("NULL")) != 0)
        {
        if(inpFileType.Compare(_L("NULLVALUE")) == 0) inpFileType.Set(KNullDesC);            
        filterMap->InsertL(KFileType,TLiwVariant(inpFileType));
        }
	//Get the key if it is specified. 	
    if(key.Compare(_L("NULL")) != 0)
        {
        if(key.Compare(_L("NULLVALUE")) == 0) key.Set(KNullDesC);
        filterMap->InsertL(KKey,TLiwVariant(key));   
        }
    //Get the startRange if it is specified.     
    if(startRange.Compare(_L("NULL")) != 0)
        {
        if(startRange.Compare(_L("NULLVALUE")) == 0) startRange.Set(KNullDesC);
        filterMap->InsertL(KStartRange,TLiwVariant(startRange));
        }
    //Get the endRange if it is specified.    
    if(endRange.Compare(_L("NULL")) != 0)  
        {
        if(endRange.Compare(_L("NULLVALUE")) == 0) endRange.Set(KNullDesC);
        filterMap->InsertL(KEndRange,TLiwVariant(endRange));	 
        }
    //only if the sort key is specified create the map      
    if(sortKey.Compare(_L("NULL")) != 0)
        {
        sortMap = CLiwDefaultMap::NewL();
        CleanupStack::PushL(sortMap);
        if(sortKey.Compare(_L("NULLVALUE"))== 0) sortKey.Set(KNullDesC);
        sortMap->InsertL(KKey,TLiwVariant(sortKey));
        TLiwGenericParam sortParam(KSort, TLiwVariant(sortMap));
        iInList->AppendL(sortParam);     
        sortMap->DecRef(); 
        }
    //get the sort order if it is specified.    
    if(sortOrder.Compare(_L("NULL")) != 0)
        {        
        if(!sortMap)
            {
            sortMap = CLiwDefaultMap::NewL();
            CleanupStack::PushL(sortMap); 
            if(sortOrder.Compare(_L("NULLVALUE"))== 0) sortOrder.Set(KNullDesC);
            TLiwGenericParam sortParam(KSort, TLiwVariant(sortMap));
            iInList->AppendL(sortParam);     
            sortMap->DecRef(); 
            }                         
        sortMap->InsertL(KOrder,TLiwVariant(sortOrder));
        }
    //end of input params now look for expected params           
	if(sortMap)
	    {
	    CleanupStack::Pop(sortMap);
	    }
	CleanupStack::Pop(filterMap); 
}

/* --------------------------------------------------------------------------
 CMediaObserver :: SetExpectedImageOutputMap.
 This method fills the expected output map.
-----------------------------------------------------------------------------
*/
void CMediaObserver :: SetExpectedOutputMap(CStifItemParser& aItem)
    {
    TPtrC16 nextString(KNullDesC);   
      
    iFile.Write(_L8("Inside SetExpectedOutputMap\n"));
  //  iLog->Log(_L("Inside SetExpectedOutputMap"));
    
    aItem.GetNextString(nextString);
    /*
     * The expected output is in the format. 
     * [ExpectredStart StartMap Key Value[...]EndMap[...]ExpectedEnd].     
     */
    while(nextString.CompareF(KExpectedEnd)!=0)
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
                iFile.Write(_L8("Key : "));
                iFile.Write(insertKey);
                iFile.Write(_L8("\n"));
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
                    TBuf8<70> buf;
                    buf.Append(value);
                    buf.Append(_L8("\n"));
                    iFile.Write(buf);
                    
                    expectedOutPutMap->InsertL(insertKey, value);
                    }
                aItem.GetNextString(nextString);
                }
            
            iExpectedOutPutArray.Append(expectedOutPutMap);                        
            CleanupStack::Pop(expectedOutPutMap);
            }
        aItem.GetNextString(nextString);
        }  
    }

/* --------------------------------------------------------------------------
 CMediaObserver :: IsExpectedResult.
 This method checks whether the obtained result and the expected results match. .
-----------------------------------------------------------------------------
*/
TBool  CMediaObserver::IsExpectedResult(CLiwIterable* aResultlist)
    {
    TLiwVariant fileDetails;
    TBool foundMap = EFalse;
    TInt prevFoundIndex = -1;
    TInt index = 0;
    iFile.Write(_L8("Inside IsExpectedResult\n"));
    // iLog->Log(_L("Inside IsExpectedResult"));
    
    for(TInt i = 0; i<iExpectedOutPutArray.Count(); i++)
        
        {        
        index = 0; 
        while(aResultlist->NextL(fileDetails))
            {            
            const CLiwMap* map =  fileDetails.AsMap();
            if(map)
                {
                iFile.Write(_L8("Map found from iterator\n"));
        //        iLog->Log(_L("Map found from iterator"));// Lok
                //compare the two maps the result and the expected one.
                if(CMediaObserver :: CompareMaps(iExpectedOutPutArray[i], map))
                    {
                    aResultlist->Reset();
                    foundMap = ETrue;                                        
                    if(index<prevFoundIndex)
                        {
                        iFile.Write(_L8("Result Not in Expected sort order\n"));
               //         iLog->Log(_L("Result Not in Expected sort order"));
                        User::Leave(KErrGeneral);
                        }                                   
                    iFile.Write(_L8("Map is in sorted order with position\n"));
              //      iLog->Log(_L("Map is in sorted order with positio ")); // Lok
                    TBuf8<10>buf;
                    buf.Num(index);
                    iFile.Write(buf);
                    //  iLog->Log(buf);
                    buf.Zero();
                    prevFoundIndex = index;
                    break;
                    }                
                }
            index++;
            }
        if(foundMap)
            {
            foundMap = EFalse;
            }
        else
            {
            iFile.Write(_L8("Expected map not found in the result list\n"));
         //   iLog->Log(_L("Expected map not found in the result list"));
            return EFalse;            
            }
        }
    return ETrue;
    }

/* --------------------------------------------------------------------------
 CMediaObserver :: CompareMaps.
 A static method which compares two maps.
-----------------------------------------------------------------------------
*/
TBool CMediaObserver::CompareMaps(CLiwMap* aExpectedMap,
                                          const CLiwMap* aResultMap)
    {  
    iFile.Write(_L8("Inside CompareMaps\n"));
 //   iLog->Log(_L("Inside CompareMaps"));
    if(!CompareStringResult(KType, aExpectedMap, aResultMap))
        {
        return EFalse;
        }   
    if(!CompareStringResult(KMgFileName, aExpectedMap, aResultMap))
        {
        return EFalse;
        }
    if(!CompareStringResult(KMgDrive, aExpectedMap, aResultMap))
        {
        return EFalse;
        } 
    if(!CompareTIntResult(KMgFileSize, aExpectedMap, aResultMap))
        {
        return EFalse;
        }    
   if(!CompareStringResult(KMgMimeType, aExpectedMap, aResultMap))
        {
        return EFalse;
        }                          
   if(!CompareStringResult(KMgFileNameAndPath, aExpectedMap, aResultMap))
        {
        return EFalse;
        }
    if(!CompareTTimeResult(KMgFileDate, aExpectedMap, aResultMap))
        {
        return EFalse;
        }    
    //In case of streamingURL file check for few additional keys. 
    if(iFiletype == EStreamingURLFile)
       {       
       if(!CompareStringResult(KMgLinkFirstURL, aExpectedMap, aResultMap))
               {
               return EFalse;
               }            
       }
    //In case of Music file check for few additional keys. 
   if(iFiletype == EMusicFile)
       {
       if(!CompareStringResult(KMgComposer, aExpectedMap, aResultMap))
               {
               return EFalse;
               }   
          
           if(!CompareStringResult(KMgArtist, aExpectedMap, aResultMap))
               {
               return EFalse;
               } 
           if(!CompareStringResult(KMgAlbum, aExpectedMap, aResultMap))
               {
               return EFalse;
               }                
            
          if(!CompareStringResult(KMgGenre, aExpectedMap, aResultMap))
               {
               return EFalse;
               }    
          if(!CompareTIntResult(KMgTrackNumber, aExpectedMap, aResultMap))
                         {
                         return EFalse;
                         }
          if(!CompareStringResult(KMgSongName, aExpectedMap, aResultMap))
               {
               return EFalse;
               }
       }   
    return ETrue;  
    }
 

/* --------------------------------------------------------------------------
 CMediaObserver :: CompareStringResult.
 A static method which compares two string results from the maps.
-----------------------------------------------------------------------------
*/
TBool CMediaObserver::CompareStringResult(const TDesC8& aKey,
                                                  CLiwMap* aExpectedMap,
                                                  const CLiwMap* aResultMap)
    {
    TLiwVariant expValue;
    TLiwVariant resValue;       
    TBool equal = EFalse; 
    
    iFile.Write(_L8("Inside CompareStringResult\n"));
   // iLog->Log(_L("Inside CompareStringResult"));
    
    if(!aExpectedMap->FindL(aKey, expValue))
        {
        return ETrue;
        }
    aResultMap->FindL(aKey, resValue);
       
    TPtrC expPtr = expValue.AsDes();
    TPtrC resPtr = resValue.AsDes();
    TBuf8<100> buf;
    buf.Copy(expPtr);
    iFile.Write(_L8("Expected Value\n"));
    iFile.Write(buf);
    buf.Zero();
    buf.Copy(resPtr);
    iFile.Write(_L8("\nResult Value\n"));
    iFile.Write(buf);
    iFile.Write(_L8("\n"));
    buf.Zero();
    
    if(expPtr.CompareF(_L("NULL"))!=0)
        {
        if(expPtr.CompareF(resPtr) == 0)
            {
            equal = ETrue;
            }        
        }
    
    expValue.Reset();
    resValue.Reset();
    
    return equal;
    }  

/* --------------------------------------------------------------------------
 CMediaObserver :: CompareTTimeResult.
 A static method which compares two TTime results from the maps.
-----------------------------------------------------------------------------
*/
TBool CMediaObserver::CompareTTimeResult(const TDesC8& aKey,
                                                 CLiwMap* aExpectedMap,
                                                 const CLiwMap* aResultMap)
    {
   // iLog->Log(_L("Inside CompareStringResult"));
    TLiwVariant expValue;
    TLiwVariant resValue;    
    TBool equal = EFalse; 
    TBuf<255> timeString;
        
    if(!aExpectedMap->FindL(aKey, expValue))
           {
           return ETrue;
           }
    aResultMap->FindL(aKey, resValue);
       
    TTime expTime(expValue.AsDes());
    
  /*  iLog->Log(_L("Expected Value"));
    iLog->Log(expValue.AsDes());
    */
    TTime resTime = resValue.AsTTime();    
    
    //resTime.FormatL(timeString, _L("%:0%J%:1%T%:2%S%.%*C3%:3%+B %*E%*D%X%*N%*Y %1 %2 '%3"));
    resTime.FormatL(timeString, _L("%F%Y%M%D%:0%H%T%S"));
    
 /*   iLog->Log(_L("Result Value"));
    iLog->Log(timeString);    
   */ 
    if(expTime.DateTime().Day() == resTime.DateTime().Day())
        {       
        if(expTime.DateTime().Month() == resTime.DateTime().Month())
            if(expTime.DateTime().Year() == resTime.DateTime().Year())
                //these  things can be ignored
                /*if(expTime.DateTime().Hour() == resTime.DateTime().Hour())
                if(expTime.DateTime().Minute() == resTime.DateTime().Minute())
                if(expTime.DateTime().Second() == resTime.DateTime().Second())*/
                {
                equal = ETrue;
                }
        }    
    expValue.Reset();
    resValue.Reset();
    return equal;
    }

/* --------------------------------------------------------------------------
 CMediaObserver :: CompareTIntResult.
 A static method which compares two TInt results from the maps.
-----------------------------------------------------------------------------
*/
TBool CMediaObserver::CompareTIntResult(const TDesC8& aKey,
                                                CLiwMap* aExpectedMap,
                                                const CLiwMap* aResultMap)
    {
    TLiwVariant expValue;
    TLiwVariant resValue;     
    TBool equal = EFalse; 
    TBuf<255> expIntStr;
    TBuf<255> resIntStr;
    
    if(!aExpectedMap->FindL(aKey, expValue))
           {
           return ETrue;
           }
    aResultMap->FindL(aKey, resValue);
       
    TInt expRes = expValue.AsTInt32();
    TInt resRes = resValue.AsTInt32();
    
    expIntStr.AppendNum(expRes);
    resIntStr.AppendNum(resRes);
    
 /*   iLog->Log(_L("Expected Value"));
    iLog->Log(expIntStr);
        
    iLog->Log(_L("Result Value"));    
    iLog->Log(resIntStr);
   */ 
    if(expRes == resRes)
        {
        equal = ETrue;                    
        }
    expValue.Reset();
    resValue.Reset();
    return equal;
    }
/* --------------------------------------------------------------------------
 CMediaObserver :: NewL.
 Two phase construction
-----------------------------------------------------------------------------
*/

CMediaObserver* CMediaObserver::NewL()
    {
    CMediaObserver* self = new(ELeave)CMediaObserver();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

/* --------------------------------------------------------------------------
 CMediaObserver :: CMediaObserver.
 Constructor
-----------------------------------------------------------------------------
*/
CMediaObserver::CMediaObserver():iInList(NULL),iOutList(NULL),
                                iExpErrorCode(-1),
                                iResult(0),
                                iFiletype(EOtherFile),
                                iFilename(NULL)
    {
    }

/* --------------------------------------------------------------------------
 CMediaObserver :: ConstructL
 
-----------------------------------------------------------------------------
*/
void CMediaObserver::ConstructL()
    {
    
    iInList = CLiwGenericParamList::NewL();
    iOutList = CLiwGenericParamList::NewL();
    
    User::LeaveIfError(iFs.Connect());
    count++;
    TBuf<50> filnm;
     filnm.Append(KFilenm);
     filnm.AppendNum(count);
     filnm.Append(_L(".txt"));
     iFilename = filnm.Alloc();
     User::LeaveIfError(iFile.Replace(iFs,*iFilename,EFileWrite));
    
    }

/* --------------------------------------------------------------------------
 CMediaObserver :: ~CMediaObserver.
 Destructor
-----------------------------------------------------------------------------
*/
CMediaObserver::~CMediaObserver()
    {
    TInt count = iExpectedOutPutArray.Count();
    for(TInt index =0 ;index<count;index++)
        {
        iExpectedOutPutArray[index]->DecRef();          
        }    
    iExpectedOutPutArray.Close();  
    delete iInList;
    delete iOutList;
    if(iFilename)
        delete iFilename;
    iFile.Close();
    iFs.Close();
    }
// -----------------------------------------------------------------------------
// CMediaObserver:: HandleNotifyL
// Call Back Function Called by the Media Management SAPI.
// -----------------------------------------------------------------------------
//        
 TInt CMediaObserver:: HandleNotifyL(TInt /*aCmdId*/,
                               TInt aEventId,
                               CLiwGenericParamList& aEventParamList,
                               const CLiwGenericParamList& /*aInParamList*/)
  { 
  

  
  TInt pos = 0;
  TInt error = KErrGeneral;
  iResult = KErrGeneral;
  count--;
  TBuf<25> errorcodedes(KNullDesC);
  const TLiwGenericParam* errorCode = NULL;
  const TLiwGenericParam* resultList = NULL;
  CLiwIterable* iterator = NULL;
  
  if( 0 == count)
      CActiveScheduler::Stop();
  
  errorCode = aEventParamList.FindFirst(pos, KErrorCode); // Finding Error Code
  resultList = aEventParamList.FindFirst(pos, KResponse); // Finding Iterator for the result list
  
  TBuf8<100> flbuf;
  
  if(errorCode)
      {
      error = errorCode->Value().AsTInt32();
      errorcodedes.Num(error);
      iFile.Write(_L8("Error code:"));
      //flbuf.AppendNum(error);
  //    flbuf.Append(_L8("\n"));
    //  file.Write(flbuf);
     // flbuf.Zero();
    //  iLog->Log(_L("Error code:"));
     // iLog->Log(errorcodedes);      
      }
  if(iExpErrorCode != error)
      {
    //  iLog->Log(_L("Expected Error code does not match"));
      iFile.Write(_L8("Expected Error code does not match \n"));

      User::Leave(KErrGeneral);
      }
  if(resultList)
      {
      iterator = resultList->Value().AsIterable();
      if(IsExpectedResult(iterator))
          {
          iResult = KErrNone;
          }
      }
  else
      {
      if(iExpectedOutPutArray.Count() != 0)
          {
      //    iLog->Log(_L("Result Iterator Not Found"));
          iFile.Write(_L8("Result Iterator Not Found \n"));


          User::Leave(KErrNotFound);
          }
      }

  iFile.Write(_L8("End of observer"));


  }
