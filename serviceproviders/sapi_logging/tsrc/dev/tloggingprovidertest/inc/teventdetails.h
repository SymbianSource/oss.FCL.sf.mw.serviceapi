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

#ifndef EVENTDETAILS_H
#define EVENTDETAILS_H

#include "tconstants.h"



class CEventDetails : public CBase
    {
        public :
        
        /**
         * NewL: Two phased construction
         */
         
             IMPORT_C static CEventDetails *NewL() ;

            /**
             * NewLC: Creates an instance of CLoggingServiceClass
             * Two Phased constructor
             * returns newly allocated object.
             */
             
             static CEventDetails* NewLC() ;
             
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
			   	  return iEventType ;
			   	  }
			   	  
			 /**
			  * SetDurationType, set the request type
			  *
			  * @param aParseValue
			  */
			   	      
			  inline void SetDurationType(TInt32 aParseValue)
			   	  {
			   	  
			   	  iDuration = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetDurationType, gets the request type of 
			  */
			   	      
			  inline TInt32 GetDurationType(void)  	
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
			   	      
			  inline void SetLinkType(TInt32 aParseValue)
			   	  {
			   	  iLink = aParseValue ;
			   	  }
			   	  
	         /**
			  * GetLinkType, gets the request type of 
			  */
			   	      
			  inline TInt32 GetLinkType(void)  	
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
			   	      
			  inline void SetDirectionType(TInt32 aDirection)
			   	  {
			   	  iDirection = aDirection ;
			   	  }
			   	  
	         /**
			  * GetDirectionType, gets the request type of 
			  */
			   	      
			  inline TInt32 GetDirectionType(void)  	
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
			   	  
			   	  
			  inline void SetDataType(TDesC& aString)
			   	  {
			   	  iData=aString ;
			   	  }
			   	  
	         /**
			  * GetDataType, gets the request type of 
			  */
			   	      
			  inline TDesC& GetDataType(void)  	
			   	  {
			   	  
			   	  return iData ;
			   	  }   	       	   	     	   	     	   	     	  	     	   	   	     	   	   	  	   	     	   	   	  	     	   	    	   	    	   	    	   	  
			   	    	   	     	   	     	   	     	   	     	  	     	   	   	     	   	   	  	   	     	   	   	  	     	   	    	   	    	   	    	   	  
			   	  
			/**
             * Default Destructor
             */
             
            ~CEventDetails() ;  
        
        protected:     
         
            
        /**
         * Default constructor
         */

        CEventDetails() ;
        
        private :
        
      
          TInt32  iEventType ; 
          TInt32 iDuration;
          TInt32 iContact;
          TInt32 iLink;
         
          TTime iTime;
          TBuf<KLogMaxSubjectLength> iSubject;
          TBuf<KLogMaxNumberLength> iNumber;
          TBuf<KLogMaxRemotePartyLength> iRemoteParty;
          TInt iDirection;
          TBuf<KLogMaxDescriptionLength> iDescription;
          TInt iStatus;
         // TBuf<KLogMaxSharedStringLength> iEventData;
         TBuf<KLogMaxSharedStringLength> iData; 
         
          
     };
    
    #endif