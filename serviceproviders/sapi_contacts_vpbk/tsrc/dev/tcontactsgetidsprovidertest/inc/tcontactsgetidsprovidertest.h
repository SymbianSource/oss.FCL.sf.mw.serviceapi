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
* Description:   ?Description
*
*/


// This file defines the API for tcontactsgetidsprovidertest.dll

#ifndef TCONTACTSGETIDSPROVIDERTEST_H
#define TCONTACTSGETIDSPROVIDERTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <f32file.h>
#include <TestclassAssert.h>

#include <LiwCommon.h>
#include <LiwBufferExtension.h>
#include <LiwServiceHandler.h>

#include <e32base.h>	// CBase
#include <e32std.h>	 // TBuf

//  Constants
// Logging path
_LIT( KLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KLogFile, "tcontactsgetidsprovidertest.txt" ); 
_LIT( KLogFileWithTitle, "tcontactsgetidsprovidertest_[%S].txt" );

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

//  Class Definitions

class Ctcontactsgetidsprovidertest : public CScriptBase, public MLiwNotifyCallback
    {
    public:// Constructors and destructor
        enum TFileType
                    {
                    EContacts,
                    EGroups,
                    ENone
                    };
        /**
        * Two-phased constructor.
        */
        static Ctcontactsgetidsprovidertest* NewL( CTestModuleIf& aTestModuleIf );
        
        /**
        * Destructor.
        */
        virtual ~Ctcontactsgetidsprovidertest();
        
    private:
            
            /**
            * C++ default constructor.
            */
            Ctcontactsgetidsprovidertest(CTestModuleIf& aTestModuleIf);
            /**
            * By default Symbian 2nd phase constructor is private.
            */
            void ConstructL();
            /**
            * Frees all resources allocated from test methods.        
            */
            void Delete();   
            /**
            * loades the contacts service.
            * @return MLiwInterface pointer.
            */
            void LoadServiceL();
            /**
            * Test methods are listed below. 
            */      
            /**
            * Example test method.
            * @since ?Series60_version
            * @param aItem Script line containing parameters.
            * @return Symbian OS error code.
            */
            TInt GetIdsL(CStifItemParser& aItem);
            /**
            * This method parses the input from cfg file and prepare the input list.             
            * @param  aItem input list contaning input params from cfg file. 
            * @return Symbian OS error code.
            */
            void ParseStiffInput(CStifItemParser& aItem);   
            /**
            * This method parses the input from cfg file and prepare the Expected out put list.             
            * @param  aItem input list contaning input params from cfg file.
            * @return Symbian OS error code.
            */
            void SetExpectedOutputMap(CStifItemParser& aItem);
            /**
            * Method used to log version of test class
            */
            void SendTestClassVersion();
            
            TInt AddL(CStifItemParser& aItem);
    public: // Functions from base classes
            
            /**
            * From CScriptBase Runs a script line.        
            * @param aItem Script line containing method name and parameters.
            * @return Symbian OS error code.
            */
            virtual TInt RunMethodL(CStifItemParser& aItem);
            
            /**
            * From the  MLiwNotifyCallback interface it is called by the contacts service.      
            * @param aCmdId Script line containing method name and parameters.
            * @return Symbian OS error code.
            */
            TInt HandleNotifyL(TInt aCmdId,
                               TInt aEventId,
                               CLiwGenericParamList& aEventParamList,
                               const CLiwGenericParamList& aInParamList);
        
    private:    // Data
        //An array to hold the expected result maps. 
        RPointerArray <CLiwMap> iExpectedOutPutArray;
        //the expected output error code
        TInt iExpErrorCode;        
        //result of the test case.
        TInt iResult;
        //input parameter list
        CLiwGenericParamList* iInList;
        //output parameter list
        CLiwGenericParamList* iOutList;
        //service handler pointer
        CLiwServiceHandler* iServicehandler;
        //interface handle
        MLiwInterface* iIface;
        //file type 
        TFileType itype;             
    };

#endif  // __TCONTACTSGETIDSPROVIDERTEST_H__

