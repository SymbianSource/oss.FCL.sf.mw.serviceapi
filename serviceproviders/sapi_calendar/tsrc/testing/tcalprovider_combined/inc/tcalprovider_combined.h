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




#ifndef TCALPROVIDER_COMBINED_H
#define TCALPROVIDER_COMBINED_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <Liwgenericparam.h>
#include <Liwservicehandler.h>
#include <Liwvariant.h>
//#include <MVPbkContactStoreListObserver.h>
//#include <MVPbkContactObserver.h>
//#include <MVPbkContactFindObserver.h>
//#include <MVPbkSingleContactOperationObserver.h>
//#include <MVPbkBatchOperationObserver.h>
//#include <MVPbkStoreContact.h>
#include "tconstants.h"
#include <e32svr.h>
#include <f32file.h>
#include <StifParser.h>
#include <e32std.h>
#include <Stiftestinterface.h>
#include <utf.h>

/*#include "sensorservice.h"
#include "sensorservice.hrh"
#include "sensrtestthread.h"

_LIT8(KSensorIDataSource , "ISensor");
_LIT8(KSensorService , "Service.Sensor") ;*/



_LIT( KTcompluginLogPath, "\\logs\\testframework\\Tcomplugin\\" ); 
// Log file
_LIT( KTcompluginLogFile, "Tcomplugin.txt" ); 

_LIT8(KLocationContents , "Service.Location");
 _LIT8(KLocationInterface , "ILocation") ;
 _LIT8(KDataSourceloc , "ILocation") ;
_LIT8(KGetLocation , "GetLocation") ;
_LIT8(KTraceLocation ,"Trace") ;
_LIT8(KContents , "ILocation") ;
_LIT8( KCancelType , "CancelRequestType") ;
_LIT8(KLsInterfaceName , "ILocation") ; 


/**
 * Error Indntifier in Output parameter list
 */
 _LIT8(KErrorCodeloc , "ErrorCode") ; 
 
 /**
  * Location SAPI result parmater identifiers
  */
 _LIT8(KLocationMap , "ReturnValue") ; 
 
 /**
 * Key for locating location information in CLiwGenericParamList
 */
_LIT8(KLongitudeKey,"Longitude") ;
_LIT8(KLatitudeKey , "Latitude") ;
_LIT8(KAltitudeKey , "Altitude") ;


_LIT8( KCmdSetIdentity, "SetIdentity");

/**
 * For Requestor identity information
 */
_LIT8(KRequestorList,"RequestorIdentityList");
_LIT8(KRequestorMap,"RequestorInfo");
_LIT8(KRequestMapType,"RequestType");
_LIT8(KRequestMapFormat,"RequestFormat");
_LIT8(KRequestMapData,"RequestData");

/**
 * Various command for Location service
 */
 
_LIT8( KCmdGetLocation , "GetLocation" ) ;
_LIT8( KCmdTraceLocation, "Trace" ) ;
_LIT8( KCmdCancelRequest, "CancelNotification" ) ;
_LIT8( KCmdCalc , "Calculate" ) ;

_LIT8( KRequestTrace ,"TraceCancel") ;
_LIT8( KRequestGetLoc , "GetLocCancel" ) ;
_LIT8( KRequestCalculate , "Calculate") ;


/**
 * Update Options
 */
_LIT8(KUpdateOptionMap,"Updateoptions");
_LIT8(KUpdateOptionInterval,"UpdateInterval");
_LIT8(KUpdateOptionTimeOut,"UpdateTimeOut");
_LIT8(KUpdateOptionMaxAge,"UpdateMaxAge");
_LIT8(KPartialUpdates , "PartialUpdates");

/**
 * Math operations request identifiers 
 */
_LIT8( KRequestDistance , "FindDistance") ;
_LIT8(KRequestBearingTo,"FindBearingTo");
_LIT8(KRequestMove,"MoveCoordinates");
_LIT8(KDistanceParmSource , "DistanceParamSource") ;
_LIT8(KDistanceMove , "MoveByThisDistance");
_LIT8(KBearingMove , "MoveByThisBearing");
_LIT8(KDistanceParmDestination , "DistanceParamDestination") ;
_LIT8(KMathOpResult,"MathResult");
_LIT8(	KMathRequest , "MathRequest") ;


_LIT8(KGetList,"GetList");

//Just for comparison with cfg file
_LIT8(KNull8,"NULL");
_LIT(KNull,"NULL");

//Input Keys/arguments
_LIT8(KDsName,"Type");// used by interface class
_LIT8(KFileType,"FileType");
_LIT8(KKey,"Key");
_LIT8(KOrder,"Order");


// Sorting Map
_LIT8(KSort,"Sort");

//Output Keys/arguments
_LIT8(KErrorCodem,"ErrorCode");
_LIT8(KResponse,"ReturnValue");

_LIT8(KMediaService, "Service.MediaManagement");
_LIT8(KMediaIDataSource,"IDataSource");
_LIT8(KErCode,"ErrorCode");
_LIT( KMediaMgmtLogFile, "MediaMgmt.txt" ); 
_LIT( KResultFile, "Result.txt" ); 
_LIT( KMediaMgmtLogPath, "\\logs\\testframework\\MediaMgmt\\" ); 
_LIT8(KMessageParam,	"MessageParam");

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( Ktcalprovider_combinedLogPath, "\\logs\\testframework\\tcalprovider_combined\\" ); 
// Log file
_LIT( Ktcalprovider_combinedLogFile, "tcalprovider_combined.txt" ); 
_LIT( Ktcalprovider_combinedLogFileWithTitle, "tcalprovider_combined_[%S].txt" );


_LIT( KContactsUTLogPath, "\\logs\\testframework\\ContactsUT\\" ); 
// Log file
_LIT( KContactsUTLogFile, "ContactsUT.txt" ); 

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Ctcalprovider_combined;
class CLiwServiceHandler;
class CPosLandmarkDatabase;
class CPosLmCategoryManager;
class CPosLmDatabaseManager;
class CVPbkContactManager;
class MVPbkContactStoreList;
class MVPbkStoreContact;
class MVPbkContactOperationBase;

class CVPbkContactLinkArray;
class CEventDetails;
class CFilterDetails;


// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Ctcalprovider_combined test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctcalprovider_combined) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctcalprovider_combined* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctcalprovider_combined();

    public: // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    public: // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );

    protected:  // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    protected:  // Functions from base classes

        /**
        * From ?base_class ?member_description
        */
        //?type ?member_function();

    private:

        /**
        * C++ default constructor.
        */
        Ctcalprovider_combined( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        // Prohibit copy constructor if not deriving from CBase.
        // ?classname( const ?classname& );
        // Prohibit assigment operator if not deriving from CBase.
        // ?classname& operator=( const ?classname& );

        /**
        * Frees all resources allocated from test methods.
        * @since ?Series60_version
        */
        void Delete();
		void RemoveAllCategories ( CPosLmCategoryManager* aHandle );
		TInt AddLandmarkL( CStifItemParser& aItem );
		TInt ConvertHexStringToInt32(const TDesC& aHexString,TInt32& aInt32 );
	//	void RemoveAllLandmarks ( CPosLandmarkDatabase* aLandmarkHandle );
    
        /**
        * Test methods are listed below. 
        */

        /**
        * Example test method.
        * @since ?Series60_version
        * @param aItem Script line containing parameters.
        * @return Symbian OS error code.
        */
        virtual TInt operations1( CStifItemParser& aItem );
        virtual TInt Cal_ops2( CStifItemParser& aItem );
        //virtual TInt Cal_ops3( CStifItemParser& aItem );
        virtual TInt Cal_ops4( CStifItemParser& aItem );
        virtual TInt Cal_ops5( CStifItemParser& aItem );
        virtual TInt Cal_ops6( CStifItemParser& aItem );
        virtual TInt Cal_ops7( CStifItemParser& aItem );
        //virtual TInt Cal_ops8( CStifItemParser& aItem );
        //virtual TInt Cal_ops9( CStifItemParser& aItem );
        virtual TInt Cal_ops10( CStifItemParser& aItem );
        virtual TInt Cal_ops11( CStifItemParser& aItem );
      //  virtual TInt Cal_ops12( CStifItemParser& aItem );
      //  virtual TInt Cal_ops13( CStifItemParser& aItem );
        //virtual TInt Cal_ops12( CStifItemParser& aItem );
        //virtual TInt Cal_ops13( CStifItemParser& aItem );
        
        //ADD NEW METHOD DEC HERE

    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        
        RFs iFSession;
        RFile iFileHandle;
        RPointerArray<TDesC> iIdArrayList;
        HBufC* iCntID;
            
        CLiwServiceHandler* iServiceHandler; 
        //handle to the service Interface for landmarks
        MLiwInterface* iIflandmarks;       
        // Reserved pointer for future extension
        //TAny* iReserved;

    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
        //?friend_class_declaration;

    };
    
struct ParamPass
    {
    	CStifItemParser* it;
    	CStifLogger *log; 
    	//TInt CmdId ; // 0 for GetFiles and 1 GetFilesInfo
    	
    };
            
class Callback : public MLiwNotifyCallback   
{
	struct ParamPass *arg;
	public:
	
	Callback(ParamPass *aArg):arg(aArg)
	{
		
	}
	TInt HandleNotifyL(TInt aCmdId,TInt aEventId,CLiwGenericParamList& aEventParamList,const CLiwGenericParamList& aInParamList);
        
};
TInt ThreadFunction (TAny *a);    
TInt GetFilesAsynchL( TAny *ParamPass );    

class CEventDet : public CBase
    {
        public :
        
        /**
         * NewL: Two phased construction
         */
         
             IMPORT_C static CEventDet *NewL() ;

            /**
             * NewLC: Creates an instance of CLoggingServiceClass
             * Two Phased constructor
             * returns newly allocated object.
             */
             
             static CEventDet* NewLC() ;
             
             /**
			  * SetEventType, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetEventType(TUint aParseValue)
			   	  {
			   	  iEventType = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetEventtType, gets the request type of 
			  */
			   	      
			  inline TUint GetEventType(void)  	
			   	  {
			   	  return iEventType ;
			   	  }
			   	  
			 /**
			  * SetDurationType, set the request type
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetDurationType(TUint32 aParseValue)
			   	  {
			   	  
			   	  iDuration = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetDurationType, gets the request type of 
			  */
			   	      
			  inline TUint32 GetDurationType(void)  	
			   	  {
			   	  //if(iDuration!=0)
			   	  return iDuration ;
			   	  //else
			   	 // return KErrNotFound;
			   	  }
			   	  
			 /**
			  * SetContactType, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetContactType(TInt32 aParseValue)
			   	  {
			   	  iContact = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetContactType, gets the request type of 
			  */
			   	      
			  inline TInt32 GetContactType(void)  	
			   	  {
			   	  //if(iContact!=0)
			   	  return iContact ;
			   	  //else
			   	  //return KErrNotFound;
			   	  }
			   	  
			 /**
			  * SetLinkType, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetLinkType(TUint32 aParseValue)
			   	  {
			   	  iLink = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetLinkType, gets the request type of 
			  */
			   	      
			  inline TUint32 GetLinkType(void)  	
			   	  {
			   	  //if(iLink!=0)
			   	  return iLink ;
			   	 // else
			   	 // return KErrNotFound;
			   	  
			   	  }
			   	  
			 /**
			  * SetTimer, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetTimer(TTime aParseValue)
			   	  {
			   	  iTime = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetLinkType, gets the request type of 
			  */
			   	      
			  inline TTime GetTimer(void)  	
			   	  {
			   	  //if(iTime!=0)
			   	  return iTime ;
			   	  //else
			   	 // return KErrNotFound;
			   	  } 
			   	  
			 /**
			  * SetSubjecttype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetSubjectType(TDesC& aString)
			   	  {
			   	  iSubject=aString ;
			   	  }
			   	  
	         /**
			  * GetSubjectType, gets the request type of 
			  */
			   	      
			  inline TDesC& GetSubjectType(void)  	
			   	  {
			   	   return iSubject ;
			   	  }
			   	  
			 /**
			  * SetNumbertype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetNumberType(TDesC& aString)
			   	  {
			   	  iNumber=aString ;
			   	  }
			   	  
	         /**
			  * GetNumberType, gets the request type of 
			  */
			   	      
			  inline TDesC& GetNumberType(void)  	
			   	  {
			   	  
			   	  return iNumber ;
			   	  }
			   	  
			   	  
			 /**
			  * SetRemotepartytype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetRemotePartyType(TDesC& aString)
			   	  {
			   	  iRemoteParty=aString ;
			   	  }
			   	  
	         /**
			  * GetRemotePartyType, gets the request type of 
			  */
			   	      
			  inline TDesC& GetRemotePartyType(void)  	
			   	  {
			   	  
			   	  return iRemoteParty ;
			   	  } 
			   	  
			   	  
			 /**
			  * SetDirectiontype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetDirectionType(TInt aDirection)
			   	  {
			   	  iDirection = aDirection ;
			   	  }
			   	  
	         /**
			  * GetDirectionType, gets the request type of 
			  */
			   	      
			  inline TInt GetDirectionType(void)  	
			   	  {
			   	  
			   	  return iDirection ;
			   	  }
			   	  
			 /**
			  * SetDescriptiontype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetDescriptionType(TDesC& aString)
			   	  {
			   	  iDescription=aString ;
			   	  }
			   	  
	         /**
			  * GetDescriptionType, gets the request type of 
			  */
			   	      
			  inline TDesC& GetDescriptionType(void)  	
			   	  {
			   	  
			   	  return iDescription ;
			   	  }
			   	  
			 /**
			  * SetStatustype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetStatusType(TInt aStatus)
			   	  {
			   	  iStatus = aStatus ;
			   	  }
			   	  
	         /**
			  * GetStatusType, gets the request type of 
			  */
			   	      
			  inline TInt GetStatusType(void)  	
			   	  {
			   	  
			   	  return iStatus ;
			   	  } 	     	   	     	   	     	   	     	  	     	   	   	     	   	   	  	   	     	   	   	  	     	   	    	   	    	   	    	   	  
			   	    	   	     	   	     	   	     	   	     	  	     	   	   	     	   	   	  	   	     	   	   	  	     	   	    	   	    	   	    	   	  
			   	  
			/**
             * Default Destructor
             */
             
            ~CEventDet() ;  
        
        protected:     
         
            
        /**
         * Default constructor
         */

        CEventDet() ;
        
        private :
        
      
          TUint  iEventType ; 
          TUint32 iDuration;
          TInt32 iContact;
          TUint32 iLink;
         // TUint8 iLogflags;
          TTime iTime;
          TBuf<KLogMaxSubjectLength> iSubject;
          TBuf<KLogMaxNumberLength> iNumber;
          TBuf<KLogMaxRemotePartyLength> iRemoteParty;
          TInt iDirection;
          TBuf<KLogMaxDescriptionLength> iDescription;
          TInt iStatus;
         // TBuf<KLogMaxSharedStringLength> iEventData;
         
         
          
     };
     
     
class CFilterDetails : public CBase
    {
        public :
        
            /**
             * NewL: Two phased construction
             */
         
            IMPORT_C static CFilterDetails *NewL() ;

            /**
             * NewLC: Creates an instance of CLoggingServiceClass
             * Two Phased constructor
             * returns newly allocated object.
             */
             
             static CFilterDetails* NewLC() ;
             
             /**
			  * SetEventId, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetEventId(TInt32 aParseValue)
			   	  {
			   	  iEventId = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetEventId, gets the request type of 
			  */
			   	      
			  inline TInt32 GetEventId(void)  	
			   	  {
			   	  return iEventId ;
			   	  }
             
            
             /**
			  * SetEventType, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetEventType(TUid aParseValue)
			   	  {
			   	  iEventType = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetEventtType, gets the request type of 
			  */
			   	      
			  inline TUid GetEventType(void)  	
			   	  {
			   	  //if(iEventType.iUid >=0 || iEventType.iUid<=11)
			   	  return iEventType ;
			   	 
			   	  
			   	  }
			   	  
			 /**
			  * SetContactType, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetContactType(TInt32 aParseValue)
			   	  {
			   	  iContact = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetContactType, gets the request type of 
			  */
			   	      
			  inline TInt32 GetContactType(void)  	
			   	  {
			   	  return iContact ;
			   	  }
			   	  
			 /**
			  * SetTimer, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetTimer(TTime aParseValue)
			   	  {
			   	  iEndTime = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetLinkType, gets the request type of 
			  */
			   	      
			  inline TInt64 GetTimer(void)  	
			   	  {
			   	  
			   	  return iEndTime.Int64() ;
			   	  }  
			   	  
			   	  
			 /**
			  * SetNumbertype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetNumberType(TDesC& aString)
			   	  {
			   	  iNumber=aString ;
			   	  }
			   	  
	         /**
			  * GetNumberType, gets the request type of 
			  */
			   	      
			  inline TDesC& GetNumberType(void)  	
			   	  {
			   	  
			   	  return iNumber ;
			   	  }
			   	  
			   	  
			 /**
			  * SetRemotepartytype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetRemotePartyType(TDesC& aString)
			   	  {
			   	  iRemoteParty=aString ;
			   	  }
			   	  
	         /**
			  * GetRemotePartyType, gets the request type of 
			  */
			   	      
			  inline TDesC& GetRemotePartyType(void)  	
			   	  {
			   	  
			   	  return iRemoteParty ;
			   	  } 
			   	  
			   	  
			 /**
			  * SetDirectiontype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetDirectionType(TInt aDirection)
			   	  {
			   	  iDirection =  aDirection ;
			   	  }
			   	  
			 /**
			  * GetDirectionType, gets the request type of 
			  */
			   	      
			  inline TInt GetDirectionType(void)  	
			   	  {
			   	  
			   	  return iDirection ;
			   	  }
			   	  
			 /**
			  * SetStatustype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetStatusType(TInt aStatus)
			   	  {
			   	  iStatus = aStatus ;
			   	  }
			   	  
	         /**
			  * GetStatusType, gets the request type of 
			  */
			   	      
			  inline TInt GetStatusType(void)  	
			   	  {
			   	  
			   	  return iStatus ;
			   	  } 
			   	  
			 /**
			  * SetRecentEvent, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetRecentList(TInt32 aParseValue)
			   	  {
			   	  iRecentList = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetRecentEvent, gets the request type of 
			  */
			   	      
			  inline TInt32 GetRecentList(void)  	
			   	  {
			   	  return iRecentList ;
			   	  }
			   	  
			   	  
			   	  
			   	  inline void SetAllEvent(TBool aValue)	
			   	  {
			   	    iAllEvent=aValue;
			   	  }
			   	  
			   	  inline TBool GetAllEvent()
			   	  {
			   	    return iAllEvent;
			   	  }
			   	    	   	     	   	       	    	    	  	    	   
			   	  
			/**
             * Default Destructor
             */
             
            ~CFilterDetails() ; 
             	   
        
        protected:     
         
            
            /**
             * Default constructor
             */

            CFilterDetails() ;
            
        private :
        
        
             TInt32 iEventId;        
             TUid  iEventType ; 
             TInt32 iContact;
             TTime iEndTime;
             TBool iAllEvent;
             TInt32 iRecentList;
             
             TBuf<KLogMaxNumberLength> iNumber;
             TBuf<KLogMaxRemotePartyLength> iRemoteParty;
             TInt  iDirection;
        
             TInt iStatus;   
             
             
             
};
    
#endif      // TCALPROVIDER_COMBINED_H

// End of File
