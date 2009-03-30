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

#include <LiwServiceHandler.h>
#include <Liwbufferextension.h>
#include <gmxmldocument.h>
#include <gmxmlelement.h>
#include <gmxmlcharacterdata.h>
#include <charconv.H>
#include <gmxmltext.h>

#include "txmlconvertor.h"

#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>

#include "tprovidertest_vpbk_observer.h"

_LIT8(KErrorCode,"ErrorCode");


// Define constants
const TInt KTYPE_ID_LEN = 7;
const TInt KENTRY_LEN = 5;
const TInt KINT_LEN = 3;
const TInt KBOOL_LEN = 4;
const TInt KDATE_LEN = 4;
const TInt KFLOAT_LEN = 5;
const TInt KMAX_LEN = 255;
const TInt KSTRING_LEN = 8;
const TInt KLIST_LEN = 4;
const TInt KITER_LEN = 8;
const TInt KMAP_LEN = 3;
const TInt KKEY_LEN = 3;
const TInt KNAME_LEN = 4;
const TInt KPARAMS_LEN = 6;
const TInt KPARAM_LEN = 5;
const TInt KDateLen = 25;

const TInt KMaxOutputLen = 1000;



_LIT(KAttribute, "type_id");
_LIT(KKeyAttribute, "name");
_LIT(KInt, "int");
_LIT(KFloat, "float");
_LIT(KString, "string");
_LIT(KString8, "string8");
_LIT(KList, "list");
_LIT(KMap, "map");
_LIT(KKey, "key");
_LIT(KBool, "bool");
_LIT(KDate, "date");

_LIT(KEntry, "entry");
_LIT(KIterator, "iterator");
_LIT(KOpenTag, "<");
_LIT(KFinalCloseTag, "/>");
_LIT(KCloseTag, ">");
_LIT(KOpenTagSlash, "</");
_LIT(KParams, "params");
_LIT(KParam, "param");
_LIT(KNameAttribute, "name");
_LIT(KSTDDATE, "19700001:000000.000000");



// Converts the output params from LIW specific data type to xml based flash
// specific data type.

void CXmlConvertor::BuildOutputTreeL(CLiwGenericParamList& aOutParamList,TPtrC& aPtr)
    {
    CMDXMLDocument* pDocNode = CMDXMLDocument::NewLC();
    if (pDocNode)
    	{
	    TBuf<KPARAMS_LEN> paramsNode(KParams);
	    CMDXMLElement* pParamsNode = CMDXMLElement::NewLC(ETrue,pDocNode,paramsNode);

		if (pParamsNode)
			{
		    for(TInt i=0; i < aOutParamList.Count(); ++i)
		        {
		        //create <param name=""/> tag
		        TBuf<KPARAM_LEN> paramNode(KParam);
		        CMDXMLElement* pParamNode = CMDXMLElement::NewLC(ETrue,pDocNode,paramNode);
		        if (pParamNode)
		        	{
			        TBuf<KMAX_LEN> paramName;
			        TLiwGenericParam outParam = aOutParamList[i];

			        if(outParam.Name().Length()!=0)
			        	{
			        	paramName.Copy(outParam.Name());
			        	}
			        else
			        	{
			        	TInt semID = outParam.SemanticId();
			        	const TDesC8& strParam = this->GetParamAsString(semID);
			        	paramName.Copy(strParam);
			        	}

			        TBuf<KNAME_LEN> nameAttr(KKeyAttribute);
			        //Create an attribute "name"
			        pParamNode->SetAttributeL(nameAttr,paramName);

			        pParamsNode->AppendChild(pParamNode);

			        AppendOutParamL(pDocNode,pParamNode,outParam.Value());
			        CleanupStack::Pop(pParamNode);
		        	}
		        }
		    // Convert the output to string.
		    ToStringL(pParamsNode, aPtr);

		    CleanupStack::PopAndDestroy(pParamsNode);
			}
	    CleanupStack::PopAndDestroy(pDocNode);
    	}
    }


// Converts the TGenericParamId passed by the service provider
// to string, as we can pass only string values to flash content.
const TDesC8& CXmlConvertor::GetParamAsString(TGenericParamId aParamID)
    {
    switch(aParamID)
        {
        case EGenericParamError:
        	{
           	return KErrorCode();
        	}

        //Convert other generic param IDs if required
        default:
        	break;
        }
    return KNullDesC8();
    }







//Output parameter processing
// Appends the value in TLiwVariant to the XML tree.
void CXmlConvertor::AppendOutParamL(CMDXMLDocument* aDocNode, CMDXMLElement* aParentNode,
								 const TLiwVariant& aParamVar)
    {
        if (aDocNode && aParentNode)
    	{
	    TBuf<KTYPE_ID_LEN> typeIdAttr(KAttribute);
	    TBuf<KENTRY_LEN> entryNode(KEntry);
	    CMDXMLElement* pEntryNode = CMDXMLElement::NewL(ETrue,aDocNode,entryNode);
	    if (pEntryNode)
	    	{
		    CleanupStack::PushL(pEntryNode);

		    if(aParamVar.TypeId()==EVariantTypeTInt32)
		        {
		        //Form attribute "name" with value "int"
		        TBuf<KINT_LEN> typeIdValue(KInt);
		        pEntryNode->SetAttributeL(typeIdAttr,typeIdValue);

		        //Create text node with value equivalent to aParamVar.AsTInt32()
		        CMDXMLText* pValueNode = CMDXMLText::NewL(aDocNode);
		        CleanupStack::PushL(pValueNode);

		        TInt intValue = aParamVar.AsTInt32();
		        TInt len = GetLengthToStoreInt(intValue);
		        HBufC* hInt = HBufC::NewLC(len+1);
		        TPtr intPtr(hInt->Des());
		        intPtr.Num(intValue);

				pValueNode->SetDataL(intPtr);
		        pEntryNode->AppendChild(pValueNode);

		        CleanupStack::PopAndDestroy(hInt);
		        CleanupStack::Pop(pValueNode);
		        }
		   else if(aParamVar.TypeId()==EVariantTypeTBool)
		        {
		        //Form attribute "name" with value "bool"
		        TBuf<KBOOL_LEN> typeIdValue(_L("bool"));
		        pEntryNode->SetAttributeL(typeIdAttr,typeIdValue);

		        //Create text node with value equivalent to aParamVar.AsTBool()
		        CMDXMLText* pValueNode=CMDXMLText::NewL(aDocNode);
		        CleanupStack::PushL(pValueNode);

				TBuf<KMAX_LEN> value;
		        value.Num(aParamVar.AsTBool());

		        pValueNode->SetDataL(value);
		        pEntryNode->AppendChild(pValueNode);
		        CleanupStack::Pop(pValueNode);
		        }
		   else if(aParamVar.TypeId()==EVariantTypeDesC8)
		        {
		        //Form attribute "name" with value "string"
		        TBuf<KSTRING_LEN> typeIdValue(KString8);
		        pEntryNode->SetAttributeL(typeIdAttr,typeIdValue);

		        //Create text node with value equivalent to aParamVar.AsDes()
		        CMDXMLText* pValueNode=CMDXMLText::NewL(aDocNode);
		        CleanupStack::PushL(pValueNode);

		        TPtrC8 pValue;
		        aParamVar.Get(pValue);
		        HBufC* heapBuffer = HBufC::NewL( pValue.Length() );
	            CleanupStack::PushL( heapBuffer );
	            TPtr value( heapBuffer->Des() );
	            value.Copy( pValue );
		        pValueNode->SetDataL(value);
		        CleanupStack::PopAndDestroy();    

		        pEntryNode->AppendChild(pValueNode);
		        CleanupStack::Pop(pValueNode);
		        }
		        
		   else if(aParamVar.TypeId()==EVariantTypeTTime)
		        {
		        //Form attribute "name" with value "date"
		        TBuf<KDATE_LEN> typeIdValue(_L("date"));
		        pEntryNode->SetAttributeL(typeIdAttr,typeIdValue);

		        //Create text node with value equivalent to aParamVar.AsTTime()
		        CMDXMLText* pValueNode=CMDXMLText::NewL(aDocNode);
		        CleanupStack::PushL(pValueNode);

				// Convert the date as ActionScript requires that the date be passed as
				// milliseconds since midnight January 1, 1970.
				TBuf<KDateLen> dateBuf(KSTDDATE);
				TTime std(dateBuf);

		        TTime timeVal = aParamVar.AsTTime();

		        //Convert microseconds to milliseconds.
		        TTimeIntervalMicroSeconds timeMS = timeVal.MicroSecondsFrom(std);
		        TInt64 timeInt = timeMS.Int64();
		        timeInt = timeInt/1000;

		        TInt64 len = GetLengthToStoreInt64(timeInt);
		        HBufC* hInt = HBufC::NewLC(len);
		        TPtr intPtr(hInt->Des());
		        intPtr.Num(timeInt);

		        pValueNode->SetDataL(intPtr);

		        pEntryNode->AppendChild(pValueNode);

		        CleanupStack::PopAndDestroy(hInt);
		        CleanupStack::Pop(pValueNode);
		        }
		    else if(aParamVar.TypeId()==EVariantTypeTReal)
		        {
		        //Form attribute "name" with value "float"
		        TBuf<KFLOAT_LEN> typeIdValue(KFloat);
		        pEntryNode->SetAttributeL(typeIdAttr,typeIdValue);

		        //Create text node with value equivalent to aParamVar.AsReal()
		        CMDXMLText* pValueNode=CMDXMLText::NewL(aDocNode);
		        CleanupStack::PushL(pValueNode);

		        TRealFormat format;
				format.iType = KRealFormatGeneral;

				TBuf<KMAX_LEN> value;
				value.Num(aParamVar.AsTReal(),format);


		        pValueNode->SetDataL(value);
		        pEntryNode->AppendChild(pValueNode);
		        CleanupStack::Pop(pValueNode);
		        }
		    else if(aParamVar.TypeId()==EVariantTypeDesC)
		        {
		        //Form attribute "name" with value "string"
		        TBuf<KSTRING_LEN> typeIdValue(KString);
		        pEntryNode->SetAttributeL(typeIdAttr,typeIdValue);

		        //Create text node with value equivalent to aParamVar.AsDes()
		        CMDXMLText* pValueNode=CMDXMLText::NewL(aDocNode);
		        CleanupStack::PushL(pValueNode);

		        TPtrC pValue=aParamVar.AsDes();
		        pValueNode->SetDataL(pValue);

		        pEntryNode->AppendChild(pValueNode);
		        CleanupStack::Pop(pValueNode);
		        }
		    else if( aParamVar.TypeId()==EVariantTypeList)
		        {
		        //Form attribute "name" with value "list"
		        TBuf<KLIST_LEN> typeIdValue(KList);
		        pEntryNode->SetAttributeL(typeIdAttr,typeIdValue);
		        const CLiwList* pList=aParamVar.AsList();
		        if ( pList )
		       		{
			        CleanupStack::PushL(const_cast<CLiwList*>(pList));
			        for(TInt l=0; l != pList->Count(); ++l)
			            {
			            TLiwVariant listEntry;
			            pList->AtL(l,listEntry);
			            this->AppendOutParamL(aDocNode,pEntryNode,listEntry);
			            listEntry.Reset();
			            }
			        CleanupStack::Pop(const_cast<CLiwList*>(pList));
		       		}
		        }
		    else if(aParamVar.TypeId()==EVariantTypeIterable)
		        {
		        //Handling is same as that of list, accessor
		        //method is different (AsIterable)
		        //Form attribute "name" with value "iterator"

		        TBuf<KITER_LEN> typeIdValue(KIterator);
		        pEntryNode->SetAttributeL(typeIdAttr,typeIdValue);

		        CLiwIterable* pIter=aParamVar.AsIterable();
		        if (pIter)
		        	{
			        CleanupStack::PushL(pIter);

			        TLiwVariant entry;
			        while(EFalse != pIter->NextL(entry))
			            {
			            this->AppendOutParamL(aDocNode,pEntryNode,entry);
			            entry.Reset();
			            }
			        entry.Reset();
			        CleanupStack::Pop(pIter);
		        	}
		        }
		    else if(aParamVar.TypeId()==EVariantTypeMap)
		        {
		        //Form attribute "name" with value "list"
		        TBuf<KMAP_LEN> typeIdValue(KMap);
		        pEntryNode->SetAttributeL(typeIdAttr,typeIdValue);
		        const CLiwMap* pMap=aParamVar.AsMap();
		        if ( pMap )
		        	{
			        CleanupStack::PushL(const_cast<CLiwMap*>(pMap));
			        for(TInt m=0; m!=pMap->Count();++m)
			            {
			            TBuf8<KMAX_LEN> mapKey;
			            pMap->AtL(m,mapKey);
			            TBuf<KMAX_LEN> mapKey16;
			            mapKey16.Copy(mapKey);

			            //Add key node as child of entry node
			            TBuf<KKEY_LEN> keyNode(KKey);
			            TBuf<KNAME_LEN> nameAttr(KKeyAttribute);
			            CMDXMLElement* pKeyNode = CMDXMLElement::NewL(ETrue,aDocNode,keyNode);
			            if (pKeyNode)
			            	{
				            CleanupStack::PushL(pKeyNode);
				            pKeyNode->SetAttributeL(nameAttr,mapKey16);
				            pEntryNode->AppendChild(pKeyNode);

				            TLiwVariant fndEntry;
				            TBool found = pMap->FindL(mapKey,fndEntry);
				            if ( found )
				            	{
				            	this->AppendOutParamL(aDocNode,pKeyNode,fndEntry);
				            	fndEntry.Reset();
				            	}
				            CleanupStack::Pop(pKeyNode);
			            	}
			            }
			           CleanupStack::Pop(const_cast<CLiwMap*>(pMap));
		        	}
		        }
		    aParentNode->AppendChild(pEntryNode);
		    CleanupStack::Pop(pEntryNode);
	    	}
    	}
    }




// The ouput XML tree contains the output params. This function converts the output to the
// string representation of the xml based flash specific data type.
void CXmlConvertor::ToStringL(CMDXMLElement* aRootNode,TPtrC& aPtr)
    {
    delete iOutputBuffer;
    iOutputBuffer = NULL;
    iOutputBuffer = HBufC::NewL(KMaxOutputLen);
    WriteElementL(aRootNode);
    aPtr.Set(*iOutputBuffer);
    }

// This function writes the contents of the XML node to the output.
void CXmlConvertor::WriteElementL(CMDXMLElement* aElemNode)
    {
    if (aElemNode)
    	{
	    //write start element tag i.e <element_name>
	    WriteStartElementTagL(aElemNode);
	    if(aElemNode->HasChildNodes()==0)
	        {
	        AppendStringL(KFinalCloseTag);
	        return;
	        }
	    else //write end element tag i.e </element_name>
	        {
	        AppendStringL(KCloseTag);

	        for(CMDXMLNode* pCurrNode = aElemNode->FirstChild();
	                NULL != pCurrNode;
	        	    pCurrNode = pCurrNode->NextSibling()
	                )
	            {
	            if(CMDXMLNode::EElementNode==pCurrNode->NodeType())
	                {
	                WriteElementL((CMDXMLElement*)pCurrNode);
	                }
	            else if(CMDXMLNode::ETextNode==pCurrNode->NodeType())
	                {
	                AppendStringL(((CMDXMLCharacterData*)pCurrNode)->Data());
	                }
	            }

	        WriteEndElementTagL(aElemNode);
	        }
    	}
    }

  // This function writes the start element tag and the attributes of the node
// to the output.
void CXmlConvertor::WriteStartElementTagL(CMDXMLElement* aElemNode)
    {
    if (aElemNode)
    	{
	    AppendStringL(KOpenTag); //<
	    AppendStringL(aElemNode->NodeName()); //<element_name
	    if(aElemNode->NumAttributes()>0)
	        {
	        WriteAttributeTagL(aElemNode);
	        }
    	}
    }

    // This function writes the end element tag to the output.
void CXmlConvertor::WriteEndElementTagL(CMDXMLElement* aElemNode)
    {
    if(aElemNode && aElemNode->HasChildNodes())
        {
        AppendStringL(KOpenTagSlash);
        AppendStringL(aElemNode->NodeName());
        AppendStringL(KCloseTag);
        }
    else
        {
        AppendStringL(KFinalCloseTag);
        }
    }


    // This function writes the attributes of the node to the output.
void CXmlConvertor::WriteAttributeTagL(CMDXMLElement* aElemNode)
    {
    //Add a space before adding attr
    if(aElemNode && aElemNode->NumAttributes()>0)
        {
        TPtrC attributeValue;
        TPtrC attributeName;
        for(TInt i=0; i!=aElemNode->NumAttributes(); ++i)
            {
            AppendStringL(KSingleSpace);
            aElemNode->AttributeDetails(i, attributeName, attributeValue);
            AppendStringL(attributeName);
            AppendStringL(KEqualSign);

            AppendStringL(KQuotation);
            AppendStringL(attributeValue);
            AppendStringL(KQuotation);
            }
        }
    }



    // Appends the output to the output buffer.
void CXmlConvertor::AppendStringL(const TDesC& aStr)
	{
	TPtr bufPtr(iOutputBuffer->Des());
	TInt maxLen = bufPtr.MaxLength();

	TInt outLen = iOutputBuffer->Length();
	TInt strLen = aStr.Length();

	TInt remLen = maxLen - outLen;
	// ReAlloc if more space is required.
	if ( strLen > remLen)
		{
		iOutputBuffer = iOutputBuffer->ReAllocL(maxLen+strLen);
		}
	TPtr outPtr(iOutputBuffer->Des());
	outPtr.Append(aStr);
	}


// Calculates the length of the string needed to store the integer.
TInt CXmlConvertor::GetLengthToStoreInt(TInt aNum)
	{
	TInt num = Abs(aNum);
	TInt len = 0;
	while(num)
		{
		len++;
		num=num/10;
		}
	return len;
	}


// Calculates the length of the string needed to store the 64 bit integer.
TInt64 CXmlConvertor::GetLengthToStoreInt64(TInt64 aNum)
	{
	TInt64 len = 0;
	while(aNum)
		{
		len++;
		aNum=aNum/10;
		}
	return len;
	}



CXmlConvertor:: ~CXmlConvertor()
    {
     if (iOutputBuffer)
    	{
    	delete iOutputBuffer;
    	iOutputBuffer = NULL;
    	}
    }
    

CXmlConvertor* CXmlConvertor:: NewL()
    {
     CXmlConvertor* temp = new(ELeave)CXmlConvertor();
     CleanupStack::PushL(temp);
     temp->ConstructL();
     CleanupStack::Pop(temp);
     return temp;
     }
     
     
void CXmlConvertor:: ConstructL()
    {
    
     }
// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
