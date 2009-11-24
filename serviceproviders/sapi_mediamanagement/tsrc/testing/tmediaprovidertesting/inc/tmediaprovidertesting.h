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



#ifndef TMEDIAPROVIDERTESTING_H
#define TMEDIAPROVIDERTESTING_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <TestclassAssert.h>

#include <liwcommon.h>
#include <liwbufferextension.h>
#include <liwservicehandler.h>

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KtmediaprovidertestingLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KtmediaprovidertestingLogFile, "tmediaprovidertesting.txt" ); 
_LIT( KtmediaprovidertestingLogFileWithTitle, "tmediaprovidertesting_[%S].txt" );

class Ctmediaprovidertesting;

/**
*  Ctmediaprovidertesting test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctmediaprovidertesting) : public CScriptBase, public MLiwNotifyCallback
	{
	public: 
		enum TFileType
			{
			EOtherFile,
			EMusicFile,
			EStreamingURLFile,
			EImageFile
			};
	public:  // Constructors and destructor
	
  	/**
  	* Two-phased constructor.
  	*/
  	static Ctmediaprovidertesting* NewL( CTestModuleIf& aTestModuleIf );
  	
  	/**
  	* Destructor.
  	*/
  	virtual ~Ctmediaprovidertesting();
	
	
	public: // New functions
		/**
		* A static method which compares two result maps. This mehtod compares image,sound and video maps.         
		* @return ETrue OR EFalse.
		*/
		TBool Ctmediaprovidertesting::CompareMaps(CLiwMap* aExpectedMap, 
		                                          const CLiwMap* aResultMap);    
		/**
		* A static method which compares two strings from the maps.
		* @param  aKey key value to be compared.
		* @param  aExpectedMap the expected result map.
		* @param  aResultMap the fetched result map.       
		* @return ETrue OR EFalse.
		*/ 
		TBool Ctmediaprovidertesting::CompareStringResult(const TDesC8& aKey,
			                                              CLiwMap* aExpectedMap,
			                                              const CLiwMap* aResultMap);
		
		/**
		* A static method which compares two TTime values from the maps.
		* @param  aKey key value to be compared.
		* @param  aExpectedMap the expected result map.
		* @param  aResultMap the fetched result map.       
		* @return ETrue OR EFalse.
		*/
		TBool Ctmediaprovidertesting::CompareTTimeResult(const TDesC8& aKey,
							                             CLiwMap* aExpectedMap,
							                             const CLiwMap* aResultMap);
		
		/**
		* A static method which compares two TTime values from the maps.
		* @param  aKey key value to be compared.
		* @param  aExpectedMap the expected result map.
		* @param  aResultMap the fetched result map.       
		* @return ETrue OR EFalse.
		*/
		TBool Ctmediaprovidertesting::CompareTIntResult(const TDesC8& aKey,
		                                                CLiwMap* aExpectedMap,
		                                                const CLiwMap* aResultMap);
	public: // Functions from base classes
		
		/**
		* From CScriptBase Runs a script line.        
		* @param aItem Script line containing method name and parameters.
		* @return Symbian OS error code.
		*/
		virtual TInt RunMethodL(CStifItemParser& aItem);
		
		/**
		* From the  MLiwNotifyCallback interface it is called by the media management service.      
		* @param aCmdId Script line containing method name and parameters.
		* @return Symbian OS error code.
		*/
		TInt HandleNotifyL(TInt aCmdId,
        		           TInt aEventId,
        		           CLiwGenericParamList& aEventParamList,
        		           const CLiwGenericParamList& aInParamList);
	private:
		
		/**
		* C++ default constructor.
		*/
		Ctmediaprovidertesting(CTestModuleIf& aTestModuleIf);
		/**
		* By default Symbian 2nd phase constructor is private.
		*/
		void ConstructL();
		/**
		* Frees all resources allocated from test methods.        
		*/
		void Delete();        
		/**
		* Test methods are listed below. 
		*/		
		/**
		* Example test method.
		* @since ?Series60_version
		* @param aItem Script line containing parameters.
		* @return Symbian OS error code.
		*/
		TInt GetFilesListL(CStifItemParser& aItem);
		
        /**
        * Example test method.
        * @since ?Series60_version
        * @param aItem Script line containing parameters.
        * @return Symbian OS error code.
        */
        TInt GetListBackToBackCallL(CStifItemParser& aItem);
		
		
		
		/**
		* loades the media management service.
		* @return MLiwInterface pointer.
		*/
		void LoadServiceL();
		/**
		* This method checks whether the obtained result and the expected results match.     
		* @param aResultlist a list of maps as iterator to be compared with expected output.
		* @return Symbian OS error code.
		*/
		TBool IsExpectedResult(CLiwIterable* aResultlist);        
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
		TFileType iFiletype;	
		
		// Number of back to back async request given
		TInt iNumberApiCall ;
	};
#endif      // TMEDIAPROVIDERTESTING_H
// End of File
