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




#ifndef XMLCONVERTOR_H 
#define XMLCONVERTOR_H 

//  INCLUDES

#include <liwservicehandler.h>
#include <liwgenericparam.h>


#include <gmxmlparser.h>
#include <gmxmlnode.h>

class CLiwGenericParamList;
class CLiwDefaultMap;
class CLiwDefaultList;

using namespace LIW;




class CXmlConvertor :public CBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CXmlConvertor* NewL();

        /**
        * Destructor.
        */
        virtual ~CXmlConvertor();

  
        void BuildOutputTreeL(CLiwGenericParamList& aOutParamList,TPtrC& aPtr);

    private:

       
        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

       /*Only for generatingXmlFile */
       
       const TDesC8& GetParamAsString(TGenericParamId aParamID);
       
       void  AppendOutParamL(CMDXMLDocument* aDocNode, CMDXMLElement* aParentNode, 
						     const TLiwVariant& aParamVar);
	   
	   void  ToStringL(CMDXMLElement* aRootNode,TPtrC& aPtr); 
	   
	   void  WriteElementL(CMDXMLElement* aElemNode);
	   
	   void  WriteStartElementTagL(CMDXMLElement* aElemNode);
	   
	   void  WriteEndElementTagL(CMDXMLElement* aElemNode);
	   
	   void  WriteAttributeTagL(CMDXMLElement* aElemNode);
	   
	   void  AppendStringL(const TDesC& aStr);
	   
	   TInt  GetLengthToStoreInt(TInt aNum);
	   
	   TInt64 GetLengthToStoreInt64(TInt64 aNum);

	
	    /** Contains the output buffer.*/
       HBufC* iOutputBuffer;
	
    
    };

#endif      

// End of File
