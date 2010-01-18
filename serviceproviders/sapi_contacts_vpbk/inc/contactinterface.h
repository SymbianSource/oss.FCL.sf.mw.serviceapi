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
* Description:  Provides interface between the AIW FrameWork and Service Provider.
*
*/

#ifndef C_CCONTACTINTERFACE_H
#define C_CCONTACTINTERFACE_H

//System includes
#include <liwvariant.h>
#include <centralrepository.h>

// User Includes
#include "contactinterface.hrh"
#include "singlecontact.h"
#include "contactcallbackmap.h"
const TInt KInitialStoreUriSize = 1;
const TUint32 KPhonebookDefaultSavingStoreUri               = 0x00000001;
const TUint32 KCRUidPhonebook = 0x101f8794;
const TUint32 KCRUidPhonebookStoreConfiguration             = 0x1020727f;


// Forward Declarations
class CContactService;
class CContactInterfaceCallback;
class CRepository;
/**
 * CContactInterface - Provides interface between the AIW FrameWork
 * and Service Provider.
 */
class CContactInterface : public CBase, public MLiwInterface
    {
   	public:// Construction and destruction
        /**
         * Two-phased constructor.
         * @return CCntactInterface*
         */
        IMPORT_C static CContactInterface* NewL();
        /**
         * Destructor
         */
        virtual ~CContactInterface();
		/**
         * Gets the max length of the field
         * @return TInt Max Length for the field.
         */
		static TInt GetFieldMaxLength( TInt aFieldKeyID, TDesC& aDbUri );

    private:
        /**
         * Default constructor.
         */
        CContactInterface();
        /**
         * Symbian OS constructor.
         * @return void
         */
        void ConstructL();

    public:
       /**
        * provides a concrete implementation for the supported service
        * command aCmdName.
        *
        * @param aCmdName the name of the service command which the consumer wants to invoke
        * @param aInParamList the input parameter list, can be empty list
        * @param [in,out] aOutParamList the output parameter list.Return Code is
        * passed through this list
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        * @return void
        */
        virtual void ExecuteCmdL(const TDesC8& aCmdName,
                                 const CLiwGenericParamList& aInParamList,
                                 CLiwGenericParamList& aOutParamList,
                                 TUint aCmdOptions = 0,
                                 MLiwNotifyCallback* aCallback = 0);
       /**
        * provides a concrete implementation
        * for this method.Deletes the interface handle.
        * The consumer application should call this method if there
        * are no more service commands to be executed on the interface.        
        * @return void
        */
        virtual void Close();

        /**
         * SapiError
         * This function maps sapi error.         
         * @param aSymbianErr symbian error code.
         * @return integer error code.
         */      		
		static TInt SapiError(TInt aSymbianErr);

	private:
		
	   /**
		 * ContactIDUTFToStream :Converts the UTF ID back to stream
		 * @param aContactIDUTF the id to be converted.		 
	 	 */
	 	HBufC8* ContactIDUTFToStreamL(TDesC& aContactIDUTF); 
	   /**
		 * ProcessAddDataL : This function retrieves the data from the map and
		 * constructs singleContact
		 * @param aMap a map containing the contact data to be added.		 
		 * @param aContact a CSingleContact class pointer which is to be constructed.
	 	 */  
 		void ProcessAddDataL(const CLiwMap* aMap, 							  
 							 CSingleContact* aContact,
 							 CLiwGenericParamList& aOutParamList);
	  /**
        * Processes the command and calls the corresponding service command.
        *              
        * @param aCmdName the name of the service command which the consumer wants to invoke
        * @param aInParamList the input parameter list, can be empty list
        * @param [in,out] aOutParamList the output parameter list.Return Code is
        * passed through this list
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application        
        * @return void
        */
		void ProcessCmdL(const TDesC8& aCmdName,
                         const CLiwGenericParamList& aInParamList,
                         CLiwGenericParamList& aOutParamList,
                         TUint aCmdOptions,
                         MLiwNotifyCallback* aCallback);
  
  /**
        * Parses  the input list and calls the Cancel on the given transaction id
        *                      
        * @param aInParamList the input parameter list, can be empty list
        * @param [in,out] aOutParamList the output parameter list.Return Code is
        * passed through this list
        * @param aCallback callback to be registered by consumer application. 
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.               
        * @param aTransId the transaction id for this call.
        * @return void.
        */                 
        TInt CancelCommandL(const CLiwGenericParamList& aInParamList,
			                CLiwGenericParamList& aOutParamList);                             
                       
       /**
        * Parses  the input list and calls the Getlist API.
        *                      
        * @param aInParamList the input parameter list, can be empty list
        * @param [in,out] aOutParamList the output parameter list.Return Code is
        * passed through this list
        * @param aCallback callback to be registered by consumer application. 
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.               
        * @param aTransId the transaction id for this call.
        * @return void.
        */                 
        void GetListCommandL(const CLiwGenericParamList& aInParamList,
                             CLiwGenericParamList& aOutParamList,
                             MLiwNotifyCallback* aCallback,
                             TUint aCmdOptions,
                             TInt aTransId,
                             TCmdType aVal);
       /**
        * Parses  the input list and calls the Add API.
        *                      
        * @param aInParamList the input parameter list, can be empty list        
        * passed through this list
        * @param aCallback callback to be registered by consumer application. 
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aTransId the transaction id for this call.               
        * @return integer error code.
        */  
        void AddCommandL(const CLiwGenericParamList& aInParamList,                         
                         CLiwGenericParamList& aOutParamList,                         
                         MLiwNotifyCallback* aCallback,
                         TUint aCmdOptions,
                         TInt aTransId);
       /**
        * Parses  the input list and calls the Import API.
        *                      
        * @param aInParamList the input parameter list, can be empty list.                
        * @param aCallback callback to be registered by consumer application. 
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aTransId the transaction id for this call.               
        * @return integer error code.
        */                   
        void ImportCommandL(const CLiwGenericParamList& aInParamList,                           
                            CLiwGenericParamList& aOutParamList,                           
                            MLiwNotifyCallback* aCallback,
                            TUint aCmdOptions,
                            TInt aTransId);
       /**
        * Parses  the input list and calls the Export API.
        *                      
        * @param aInParamList the input parameter list, can be empty list.                
        * @param aCallback callback to be registered by consumer application. 
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aTransId the transaction id for this call.               
        * @return integer error code.
        */                      
        void ExportCommandL(const CLiwGenericParamList& aInParamList,                            
                            CLiwGenericParamList& aOutParamList,                            
                            MLiwNotifyCallback* aCallback,
                            TUint aCmdOptions,
                            TInt aTransId);
        
       /**
        * Parses  the input list and calls the Organise API.
        *                      
        * @param aInParamList the input parameter list, can be empty list.                
        * @param aCallback callback to be registered by consumer application. 
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aTransId the transaction id for this call.               
        * @return integer error code.
        */                      
        void OrganiseGroupCommandL(const CLiwGenericParamList& aInParamList,                                   
                                   CLiwGenericParamList& aOutParamList,                                    
                                   MLiwNotifyCallback* aCallback,
                                   TUint aCmdOptions,
                                   TInt aTransId);
       /**
        * Parses  the input list and calls the Delete API.
        *                      
        * @param aInParamList the input parameter list, can be empty list                
        * @param aCallback callback to be registered by consumer application. 
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aTransId the transaction id for this call.               
        * @return integer error code.
        */                              
        void DeleteCommandL(const CLiwGenericParamList& aInParamList,                            
                            CLiwGenericParamList& aOutParamList,                            
                            MLiwNotifyCallback* aCallback,
                            TUint aCmdOptions,
                            TInt aTransId);                                                               
                                                                                                                                  
		MLiwNotifyCallback* Callback( TInt32 aTransactionId );                                 
	private:
	    TPtrC GetDefaultDBUri();
	private:
        // POINTER MEMBER
        /**
         * contact service implementation object.
         * OWN.
         */
        CContactService* iContactService;

        /**
         * iCallbackMap
         * Array of objects.
         */
        RPointerArray<CContactCallbackMap> iCallbackMap;      

        HBufC* iErrorMess;
        //this is used only for add api due to reset problem with TLiwVariant
        HBufC* iDburi;
        
        CRepository *iRepository;
  
    };

#endif // C_CCONTACTINTERFACE_H
