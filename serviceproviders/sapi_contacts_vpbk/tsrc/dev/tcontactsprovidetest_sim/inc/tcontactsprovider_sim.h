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


#ifndef CONTACTSUT_SIM_H
#define CONTACTSUT_SIM_H

#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <f32file.h>


#include <liwcommon.h>
#include <liwbufferextension.h>
#include <liwservicehandler.h>



// Logging path
_LIT( KContactsUTLogPath, "\\logs\\testframework\\ContactsUT\\" ); 
// Log file
_LIT( KContactsUTLogFile, "ContactsUT.txt" ); 

// CONSTANTS addcontactL

//extern int addcontactL(int, char**);
extern int getlisttestL(int, char**);
extern int getlisttest_searchL(int, char**);
extern int deletetestL(int, char**);
extern int importL(int, char**);
extern int exportL(int, char**);


// FORWARD DECLARATIONS
class CContactsUT;

// CLASS DECLARATION

/**
*  CContactsUT test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/

NONSHARABLE_CLASS(CContactsUT) : public CScriptBase,public MLiwNotifyCallback
{


	    enum TTestCase
	        {
			EGetList=10,
			ESearch,
			EDeleteContact,
			EImport,
			EExport,
			EAddContact,
			EDeleteCkh,
			EExportChk
	        };
	
	    public :  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CContactsUT* NewL( CTestModuleIf& aTestModuleIf);

        /**
        * Destructor.
        */
        virtual ~CContactsUT();

    public : // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );


	private : 

	 virtual TInt HandleNotifyL(TInt aCmdId,TInt aEventId,CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList);
 

	private :
	    virtual TInt getlisttestL( CStifItemParser& aItem );
	    virtual TInt getlisttest_searchL( CStifItemParser& aItem );
	    virtual TInt deletetestL( CStifItemParser& aItem );
	    virtual TInt importL( CStifItemParser& aItem );
	    virtual TInt exportL( CStifItemParser& aItem );
	    virtual TInt addcontactL( CStifItemParser& aItem );
	    
		void LoadService();
		void Delete(); 
    private :

        /**
        * C++ default constructor.
        */
        CContactsUT( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();
        
    private :
    
    CLiwServiceHandler* iServiceHandler;
	MLiwInterface* iIface;            
	CLiwCriteriaItem* iCriteria;
	RCriteriaArray iCriteriaArray;
	
	CLiwGenericParamList* iInparams;
	CLiwGenericParamList* iOutparams;

	CLiwGenericParamList* inList;
	CLiwGenericParamList* outList;
	TInt iErr;
	HBufC* iCntID;
	TInt iCase;
    
	
	

};

#endif