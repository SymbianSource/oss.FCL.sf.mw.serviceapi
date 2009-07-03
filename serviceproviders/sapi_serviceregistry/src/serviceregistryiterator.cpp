/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implements CLiwIterable type
*
*/


#include"serviceregistryiterator.h"

#include "serviceregistryservice.hrh"



// Two-phased constructor.     
 
CSvcRegIterator* CSvcRegIterator :: NewL()
    {	
    return(new(ELeave) CSvcRegIterator());	
    }


/**
 * Default constructor. 
 */
CSvcRegIterator::CSvcRegIterator():iCount(0), 
                                   iIndex(0)                                                           
    {
    
    }

/**
 * destructor. 
 */
CSvcRegIterator::~CSvcRegIterator()									
    {
    if(iProviderDataList)
        {
        iProviderDataList->ResetAndDestroy();
        delete iProviderDataList;	    	
        } 
    }
    
//sets the provider list     
void CSvcRegIterator::SetProviderDataList(RCriteriaArray* aList)
    {
    iProviderDataList = aList;          
    }



//this methods fills the metadata map of the providers.If the end of the list is reached returns false.
TBool CSvcRegIterator::NextL(TLiwVariant& aItem)
    {                     
    if(iIndex < iProviderDataList->Count())
        {           
        CLiwDefaultMap* pMap =  CLiwDefaultMap :: NewL();
        CleanupStack::PushL(pMap);
        
        CLiwDefaultList* verList =  CLiwDefaultList :: NewL();
        CleanupStack::PushL(verList);
        
        CLiwCriteriaItem* provInfo = (*iProviderDataList)[iIndex++];
        
        //retrieving the content type or the interface name of the provider (e.g IDataSource)   
        TPtrC8 intfName = provInfo-> ServiceCmdStr();
        
        HBufC* infaceName = HBufC :: NewL(intfName.Length());        
        infaceName->Des().Copy(intfName);
        CleanupStack::PushL(infaceName);
        
        pMap->InsertL(KInterfaceName, TLiwVariant(infaceName));
                        
        //retrieving the service command name of the provider (e.g s60.Messaging)
        TPtrC8 servName = provInfo-> ContentType();  
        
        HBufC* svcName = HBufC :: NewL(servName.Length());        
        svcName->Des().Copy(servName);
        CleanupStack::PushL(svcName);      
        
        pMap->InsertL(KServiceName, TLiwVariant(svcName));              
                       
        TLiwVariant provMetadata;
        provInfo->GetMetaDataOptions(provMetadata);      
        
        //getting metadata from the provider (contains version information)
        const CLiwMap* metaDataMap = provMetadata.AsMap(); 

        if(metaDataMap)
            {           
            TLiwVariant versionVar;            
            //If false, then there is no version information in the provider metadata.
            if(metaDataMap->FindL(KVersion, versionVar))
                {
               /*
                Structure of Version information in metadata of the provider. 
                -------------------------------------
                
                |   key   |        value   |
                |     |      |
                |   ver   |      (List) 2.2   |
                -------------------------------------
                */                  
                const CLiwList* pVersionList = versionVar.AsList();
                if(pVersionList)
                    {
                    TLiwVariant verCheck;
                    for(TInt idx=0; idx < pVersionList->Count(); ++idx)         
                        {
                        if(pVersionList->AtL(idx,verCheck))    
                            { 
                            verList->AppendL(TLiwVariant(verCheck.AsTReal()));
                            }
                        verCheck.Reset();
                        }
                    }
                }
            versionVar.Reset();
            }
        provMetadata.Reset();
        
        //insert the version map into the map.
        pMap->InsertL(KVersionList, TLiwVariant(verList));
        verList->DecRef();
        
        aItem.SetL(pMap);        
        pMap->DecRef();
        
        CleanupStack::PopAndDestroy(svcName);
        CleanupStack::PopAndDestroy(infaceName);         
        CleanupStack::Pop(verList);        
        CleanupStack::Pop(pMap);
        return ETrue;
        }      
    return EFalse;
}
    
//Resets the iterator to point to the starting of the list.   
void CSvcRegIterator :: Reset()
    {
    iIndex = 0;
    }
