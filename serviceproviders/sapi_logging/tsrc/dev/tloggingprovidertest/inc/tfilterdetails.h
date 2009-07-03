/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

#ifndef FILTERDETAILS_H
#define FILTERDETAILS_H

#include "tconstants.h"

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
			   	      
			 /* inline void SetEventId( TDesC&  aParseValue)
			   	  {
			   	  iEventId = aParseValue ;
			   	  }*/
			   	  
			  inline void SetEventId( TDesC& aString)
			   	  {
			   	  iEventId = aString ;
			   	  }	  
			   	  
	         /**
			  * GetEventId, gets the request type of 
			  */
			   	      
			/*  inline TInt32 GetEventId(void)  	
			   	  {
			   	  return iEventId ;
			   	  }*/
              inline TDesC& GetEventId(void)  	
			   	  {
			   	  
			   	  return iEventId ;
			   	  } 
             
            
             /**
			  * SetEventType, set the request type 
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetEventType(TInt32 aParseValue)
			   	  {
			   	  iEventType = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetEventtType, gets the request type of 
			  */
			   	      
			  inline TInt32 GetEventType(void)  	
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
			   	      
			  inline void SetDirectionType(TInt32 aDirection)
			   	  {
			   	  iDirection =  aDirection ;
			   	  }
			   	  
			 /**
			  * GetDirectionType, gets the request type of 
			  */
			   	      
			  inline TInt32 GetDirectionType(void)  	
			   	  {
			   	  
			   	  return iDirection ;
			   	  }
			   	  
			 /**
			  * SetStatustype ,set the request type 
			  *
			  * @param aString
			  */
			   	      
			  inline void SetStatusType(TInt32 aStatus)
			   	  {
			   	  iStatus = aStatus ;
			   	  }
			   	  
	         /**
			  * GetStatusType, gets the request type of 
			  */
			   	      
			  inline TInt32 GetStatusType(void)  	
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
        
        
             //TInt32 iEventId;        
             TInt32  iEventType ; 
             TInt32 iContact;
             TTime iEndTime;
             TBool iAllEvent;
             TInt32 iRecentList;
             
             TBuf<20> iEventId ; 
             
             TBuf<KLogMaxNumberLength> iNumber;
             TBuf<KLogMaxRemotePartyLength> iRemoteParty;
             TInt  iDirection;
        
             TInt iStatus;   
             
             
             
};
#endif