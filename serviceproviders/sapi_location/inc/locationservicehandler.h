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
* Description:  Header file for location SAPI core implementation.
*
*/

#ifndef LOCATIONSERVICEHANDLER_H
#define LOCATIONSERVICEHANDLER_H


#include <liwserviceifbase.h>
#include <liwcommon.h>

/**
 * InerfaceName ILocation
 * Contenttypes Service.Location
 */
 
 
_LIT8(KLsInterfaceName , "ILocation") ;
_LIT8(KLocationContents , "Service.Location") ;

/**
 * A const member which holds max supported to be stored as part of 
 * iPositionGeneric  member of class CLocServiceHandler
 */
const TUint KMaxFields = 25 ;

/**
 * This is the  service interface to access location base service provider
 * this class is inherited from CLiwServiceIfBase class
 *
 * @lib ServiceHandler.lib depenedncy
 * @see CLiwServiceIfBase in liwserviceifbase.h file
 * 
 */
class CLocServiceHandler  : public CLiwServiceIfBase
    {
    public: 
      /**
       * Method to create 
       */
       
        static CLocServiceHandler* NewL();
      
        /**
         * Default destruct 
         */ 
       virtual ~CLocServiceHandler();

    public: 
        /**
         * Called by the LIW framework to initialise provider with necessary information 
         * from the Service Handler. This method is called when the consumer makes 
         * the attach operation.         
         *
         * @param aFrameworkCallback callback handle function
         * @param aInterest consumer application's intrest
         */
        virtual void InitialiseL(
            MLiwNotifyCallback& aFrameworkCallback,
            const RCriteriaArray& aInterest);
         
      /**
       * Executes generic service commands included in criteria, derived from CLiwServiceIfBase
       * 
       * @param aCmdId Command to be executed.
       * @param aInParamList Input parameters, can be an empty list.
       * @param aOutParamList Output parameters, can be an empty list.
       * @param aCmdOptions Options for the command, see KLiwOpt* in LiwCommon.hrh.
       * @param aCallback Callback for asynchronous command handling, parameter checking, etc.
       * 
       */

        virtual void HandleServiceCmdL(
            const TInt& aCmdId,
            const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList,
            TUint aCmdOptions = 0,
            const MLiwNotifyCallback* aCallback = NULL);
         
            

    private:
        /**
         * Private default constructor
         */ 
          
        CLocServiceHandler();
        
        /**
         * Internal CmdExecute function which parses  the input parameters
         * this function is called by HandleCmdL() function 
         *
         * @param aCmdId Command to be executed.
         * @param aInParamList Input parameters, can be an empty list.
         * @param aOutParamList Output parameters, can be an empty list.
         * @param aCmdOptions Options for the command, see KLiwOpt* in LiwCommon.hrh.
         * @param aCallback Callback for asynchronous command handling, parameter checking, etc.
         * @leave KErrArgument Callback is missing when required.
         * @leave KErrNotSupported No provider supports service.
         *
         */
           
         
         void CmdExecuteL(
         		const TInt& aCmdId,
            	const CLiwGenericParamList& aInParamList,
            	CLiwGenericParamList& aOutParamList,
            	TUint aCmdOptions ,
            	const MLiwNotifyCallback* aCallback);
            	
         

    private:
         
        TBuf8<KMaxFields> iContentType;
    };



#endif //LOCATIONSERVICEHANDLER_H
