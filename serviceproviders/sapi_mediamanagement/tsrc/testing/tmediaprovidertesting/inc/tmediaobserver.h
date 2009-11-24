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

#ifndef _TMEDIAPROVIDERTESTING_H__
#define _TMEDIAPROVIDERTESTING_H__

#include <liwcommon.h>
#include <liwbufferextension.h>
#include <liwservicehandler.h>
#include <e32base.h>
extern TInt count;
class CMediaObserver : public CBase , public MLiwNotifyCallback
{
	public :
		enum TFileType
			{
			EOtherFile,
			EMusicFile,
			EStreamingURLFile
			};
	public:
	
	static CMediaObserver* NewL();

 		/**
  	* Destructor.
  	*/
  	virtual ~CMediaObserver();	
  	
	private :
	    void ConstructL();
	    
	    CMediaObserver();
  	
	public: // New functions
		/**
		* A static method which compares two result maps. This mehtod compares image,sound and video maps.         
		* @return ETrue OR EFalse.
		*/
		TBool CMediaObserver::CompareMaps(CLiwMap* aExpectedMap, 
		                                          const CLiwMap* aResultMap);    
		/**
		* A static method which compares two strings from the maps.
		* @param  aKey key value to be compared.
		* @param  aExpectedMap the expected result map.
		* @param  aResultMap the fetched result map.       
		* @return ETrue OR EFalse.
		*/ 
		TBool CMediaObserver::CompareStringResult(const TDesC8& aKey,
			                                              CLiwMap* aExpectedMap,
			                                              const CLiwMap* aResultMap);
		
		/**
		* A static method which compares two TTime values from the maps.
		* @param  aKey key value to be compared.
		* @param  aExpectedMap the expected result map.
		* @param  aResultMap the fetched result map.       
		* @return ETrue OR EFalse.
		*/
		TBool CMediaObserver::CompareTTimeResult(const TDesC8& aKey,
							                             CLiwMap* aExpectedMap,
							                             const CLiwMap* aResultMap);
		
		/**
		* A static method which compares two TTime values from the maps.
		* @param  aKey key value to be compared.
		* @param  aExpectedMap the expected result map.
		* @param  aResultMap the fetched result map.       
		* @return ETrue OR EFalse.
		*/
		TBool CMediaObserver::CompareTIntResult(const TDesC8& aKey,
		                                                CLiwMap* aExpectedMap,
		                                                const CLiwMap* aResultMap);



public:
	/**
		* From the  MLiwNotifyCallback interface it is called by the media management service.      
		* @param aCmdId Script line containing method name and parameters.
		* @return Symbian OS error code.
		*/
		TInt HandleNotifyL(TInt aCmdId,
        		           TInt aEventId,
        		           CLiwGenericParamList& aEventParamList,
        		           const CLiwGenericParamList& aInParamList);
public:
    
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

		
		
	public:
			//An array to hold the expected result maps. 
		RPointerArray <CLiwMap> iExpectedOutPutArray;
        //input parameter list
        CLiwGenericParamList* iInList;

        //input parameter list
         CLiwGenericParamList* iOutList;

		
		//the expected output error code
		TInt iExpErrorCode;        
		//result of the test case.
		TInt iResult;
		//file type 
		TFileType iFiletype;	
		   //Filename
		        HBufC* iFilename;
		RFs iFs;
		RFile iFile;
		
	
};















#endif // _TMEDIAPROVIDERTESTING_H__
