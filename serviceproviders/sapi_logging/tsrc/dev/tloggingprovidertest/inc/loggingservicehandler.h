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
* Description:   Header file for logging SAPI core implementation.
*
*/


#ifndef LOGGINGSERVICEHANDLER_H
#define LOGGINGSERVICEHANDLER_H


#include <liwserviceifbase.h>
#include <liwCommon.h>

/**
* InterfaceName ILogging
* Contenttypes Service.Logging
*/

_LIT8(KDsInterfaceName , "IDataSource") ;
_LIT8(KLoggingContents , "Service.Logging") ;

/**
* A const member which holds max supported to be stored as part of 
* iPositionGeneric  member of class CLogServiceHandler
*/
const TUint KMaxFields = 25 ;

/**
* This is the  service interface to access logging base service provider
* this class is inherited from CLiwServiceIfBase class
*
* @lib ServiceHandler.lib depenedncy
* @see CLiwServiceIfBase in liwserviceifbase.h file
* 
*/
class CLogServiceHandler  : public CLiwServiceIfBase
    {
    public:
    
        /**
        * NewL: Two phased construction
        */
        IMPORT_C static CLogServiceHandler* NewL();

        /**
        * NewLC: Creates an instance of CLoggingServiceClass
        * Two Phased constructor
        * returns newly allocated object.
        */
        static CLogServiceHandler* NewLC() ;

        /**
        * Default destruct 
        */ 
        virtual ~CLogServiceHandler();

        /**
        * Called by the AIW framework to initialise provider with necessary information 
        * from the Service Handler. This method is called when the consumer makes 
        * the attach operation.         
        *
        * @param aFrameworkCallback callback handle function
        * @param aInterest consumer application's intrest
        */
        virtual void InitialiseL(   MLiwNotifyCallback& aFrameworkCallback,
                                    const RCriteriaArray& aInterest );

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
        virtual void HandleServiceCmdL( const TInt& aCmdId,
                                        const CLiwGenericParamList& aInParamList,
                                        CLiwGenericParamList& aOutParamList,
                                        TUint aCmdOptions = 0,
                                        const MLiwNotifyCallback* aCallback = NULL);

    protected:
    
        /**
        *  default constructor
        */ 

        CLogServiceHandler();

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
        void CmdExecuteL(   const TInt& aCmdId,
                            const CLiwGenericParamList& aInParamList,
                            CLiwGenericParamList& aOutParamList,
                            TUint aCmdOptions ,
                            const MLiwNotifyCallback* aCallback );

    private:

        TBuf8<KMaxFields> iContentType;
    
    };



#endif //LOGGINGSERVICEHANDLER_H
