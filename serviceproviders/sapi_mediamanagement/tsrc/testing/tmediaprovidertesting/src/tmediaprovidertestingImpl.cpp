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
#include <StifTestInterface.h>
#include <liwservicehandler.h>

#include "tmediaprovidertesting.h"
#include "tmediaprovidertesting.hrh"


/* --------------------------------------------------------------------------
 Ctmediaprovidertesting :: SetInput
 Fills the input parameter list.
 The format of the cfg input is 
 key startRange endRange sortKey sortOrder errorcode 
 [Expected fileName fileExtension drive fileSize fileDate fileNameAndPath mimeType
 [Next "next map data"]]. 
-----------------------------------------------------------------------------
*/
void  Ctmediaprovidertesting::ParseStiffInput(CStifItemParser& aItem)
 {  
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
    
    if(inpFileType.CompareF(KFileTypeStreamingURL) == 0)
       { 
       iFiletype = EStreamingURLFile;
       }
    else if(inpFileType.CompareF(KFileTypeMusic) == 0)
       {
       iFiletype = EMusicFile;
       }
    else if(inpFileType.CompareF(KFileTypeImage) == 0)
       {
       iFiletype = EImageFile;
       iLog->Log(_L("file type is image"));
       }
    //check for expected key 
    //if it is there then get the expected result and put it into the map.
    if(expectedStart.CompareF(KExpectedStart) == 0)
        {                   
        SetExpectedOutputMap(aItem);           
        }
    iLog->Log(_L("The Input Parameters are:"));    
    iLog->Log(key);
    iLog->Log(startRange);
    iLog->Log(endRange);
    iLog->Log(sortKey);
    iLog->Log(sortOrder);    
        
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
 Ctmediaprovidertesting :: SetExpectedImageOutputMap.
 This method fills the expected output map.
-----------------------------------------------------------------------------
*/
void Ctmediaprovidertesting :: SetExpectedOutputMap(CStifItemParser& aItem)
    {
    TPtrC16 nextString(KNullDesC);   
        
    iLog->Log(_L("Inside SetExpectedOutputMap"));
    
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
                
                if(key.CompareF(_L("FileSize"))==0)
                    {
                    TInt fileSize = -1;
                    aItem.GetNextInt(fileSize);                    
                    expectedOutPutMap->InsertL(insertKey, (TInt32)fileSize);                    
                    }
                else if(key.CompareF(_L("XPixels"))==0 || key.CompareF(_L("YPixels"))==0)
                    {
                    TInt resolution = -1;
                    aItem.GetNextInt(resolution);
                    expectedOutPutMap->InsertL(insertKey, (TInt32)resolution);
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
        }  
    }

/* --------------------------------------------------------------------------
 Ctmediaprovidertesting :: IsExpectedResult.
 This method checks whether the obtained result and the expected results match. .
-----------------------------------------------------------------------------
*/
TBool  Ctmediaprovidertesting::IsExpectedResult(CLiwIterable* aResultlist)
    {
    TLiwVariant fileDetails;
    TBool foundMap = EFalse;
    TInt prevFoundIndex = -1;
    TInt index = 0;
    iLog->Log(_L("Inside IsExpectedResult"));
    
    for(TInt i = 0; i<iExpectedOutPutArray.Count(); i++)
        
        {        
        index = 0; 
        while(aResultlist->NextL(fileDetails))
            {            
            const CLiwMap* map =  fileDetails.AsMap();
            if(map)
                {
                iLog->Log(_L("Map found from iterator"));// Lok
                //compare the two maps the result and the expected one.
                if(Ctmediaprovidertesting :: CompareMaps(iExpectedOutPutArray[i], map))
                    {
                    aResultlist->Reset();
                    foundMap = ETrue;                                        
                    if(index<prevFoundIndex)
                        {
                        iLog->Log(_L("Result Not in Expected sort order"));
                        User::Leave(KErrGeneral);
                        }                                   
                    iLog->Log(_L("Map is in sorted order with position ")); // Lok
                    TBuf<10>buf;
                    buf.Num(index);
                    iLog->Log(buf);
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
            iLog->Log(_L("Expected map not found in the result list"));
            return EFalse;            
            }
        }
    return ETrue;
    }

/* --------------------------------------------------------------------------
 Ctmediaprovidertesting :: CompareMaps.
 A static method which compares two maps.
-----------------------------------------------------------------------------
*/
TBool Ctmediaprovidertesting::CompareMaps(CLiwMap* aExpectedMap,
                                          const CLiwMap* aResultMap)
    {  
    iLog->Log(_L("Inside CompareMaps"));
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
    
    //Image Files 
    if(iFiletype == EImageFile)
       {    
       if(!CompareTIntResult(KXPixels, aExpectedMap, aResultMap))
               {
               iLog->Log(_L("Expected and Returned XPixel values do not match"));
               return EFalse;
               }            

       if(!CompareTIntResult(KYPixels, aExpectedMap, aResultMap))
               {
               iLog->Log(_L("Expected and Returned YPixel values do not match"));
               return EFalse;
               }            
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
 Ctmediaprovidertesting :: CompareStringResult.
 A static method which compares two string results from the maps.
-----------------------------------------------------------------------------
*/
TBool Ctmediaprovidertesting::CompareStringResult(const TDesC8& aKey,
                                                  CLiwMap* aExpectedMap,
                                                  const CLiwMap* aResultMap)
    {
    TLiwVariant expValue;
    TLiwVariant resValue;       
    TBool equal = EFalse; 
    
    iLog->Log(_L("Inside CompareStringResult"));
    
    if(!aExpectedMap->FindL(aKey, expValue))
        {
        return ETrue;
        }
    aResultMap->FindL(aKey, resValue);
       
    TPtrC expPtr = expValue.AsDes();
    TPtrC resPtr = resValue.AsDes();
    
    iLog->Log(_L("Expected Value"));
    iLog->Log(expPtr);
    
    iLog->Log(_L("Result Value"));
    iLog->Log(resPtr);
    
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
 Ctmediaprovidertesting :: CompareTTimeResult.
 A static method which compares two TTime results from the maps.
-----------------------------------------------------------------------------
*/
TBool Ctmediaprovidertesting::CompareTTimeResult(const TDesC8& aKey,
                                                 CLiwMap* aExpectedMap,
                                                 const CLiwMap* aResultMap)
    {
    iLog->Log(_L("Inside CompareTTimeResult"));
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
    
    iLog->Log(_L("Expected Value"));
    iLog->Log(expValue.AsDes());
    
    TTime resTime = resValue.AsTTime();    
    
    //resTime.FormatL(timeString, _L("%:0%J%:1%T%:2%S%.%*C3%:3%+B %*E%*D%X%*N%*Y %1 %2 '%3"));
    resTime.FormatL(timeString, _L("%F%Y%M%D%:0%H%T%S"));
    
    iLog->Log(_L("Result Value"));
    iLog->Log(timeString);    
    
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
 Ctmediaprovidertesting :: CompareTIntResult.
 A static method which compares two TInt results from the maps.
-----------------------------------------------------------------------------
*/
TBool Ctmediaprovidertesting::CompareTIntResult(const TDesC8& aKey,
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
    
    iLog->Log(_L("Expected Value"));
    iLog->Log(expIntStr);
        
    iLog->Log(_L("Result Value"));    
    iLog->Log(resIntStr);
    
    if(expRes == resRes)
        {
        equal = ETrue;                    
        }
    expValue.Reset();
    resValue.Reset();
    return equal;
    }
