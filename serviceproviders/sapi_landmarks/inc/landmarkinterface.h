/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CLandmarkInterface class
*
*/


#ifndef __LANDMARKINTERFACE_H__
#define __LANDMARKINTERFACE_H__

//INCLUDES
#include <e32def.h>
#include <e32base.h>
#include <liwvariant.h>

//FORWARD DECLARATION
class CLandmarkService;
class CLandmarkObserver;
class CLandmarkCallbackMap;

/**
* CLandmarkInterface
* This class inherits from MLiwInterface and implements the
* ExecuteCmdL( const TDesC8& aCmdName,
*              const CLiwGenericParamList& aInParamList,
*              CLiwGenericParamList& aOutParamList, TUint aCmdOptions = 0,
*              MLiwNotifyCallback* aCallback = 0) and
* Close() functions. The member functions of this class parses the input parameters,
* constructs proper structures and calls the corresponding service class functions
* based on the input arguments.
*/
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkInterface): public CBase, public MLiwInterface
    {
    public:
        /**
		* TParamIndex
		* Specifies whether the id passed is a landmark id or a category id.
		*/
		enum TParamIndex
			{
			EIndex0 = 0,        
			EIndex1,
			EIndex2,
			EIndex3
			};
			
    public://New Methods

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CLandmarkInterface object.
        * @return A pointer to the created instance of CLandmarkInterface.
        */
        static CLandmarkInterface* NewL();
       
    public: // from MLiwInterface

        // The consumer application should call this method to execute a service
        // command directly on the interface. The service provider should
        // provide a concrete implementation for the supported service
        // command aCmdName. The consumer application should fill in the necessary
        // parameters in \em aInParamList.
        
        void ExecuteCmdL(  const TDesC8& aCmdName,
            const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions = 0,
            MLiwNotifyCallback* aCallback = 0);

        // The service provider should provide a concrete implementation
        // for this method. The internal state of the service provider
        // implemeting \c MLiwInterface can be reset within this method.
        // The consumer application should call this method if there
        // are no more service commands to be executed on the interface.
        void Close();
        
        /**
        * Callback
        * This function returns the callback for the corresponding asynchronous request whose
        * transaction id is passed.
        *
        * @param aTransactionId Transaction id of asynchronous request whose callback is required..
        * @return The callback of the asynchronous request.
        */
        MLiwNotifyCallback* Callback( TInt32 aTransactionId );
        
        /**
        * SetActiveL
        * This function sets the requested database to active. The URI of the database should
        * be passed in the input parameter list.
        *
        * @param aInParamList the input parameter list.
        */
        void SetActiveL( const CLiwGenericParamList& aInParamList );   
        
        /**
        * SapiError
        * This function maps sapi error.
        *
        * @param aSymbianErr symbian error code.
        *
        */       
        TInt SapiError ( TInt aSymbianErr );

    private:

        /**
        * ConstructL
        * 2nd phase constructor.
        * Perform the second phase construction of CLandmarkInterface object.
        */
        void ConstructL();

        /**
        * C++ default constructor.
        * By default Symbian OS constructor is private.
        */
        CLandmarkInterface();
        
         /**
        * ~CLandmarkInterface
        * Destructor.
        */
        ~CLandmarkInterface();

    private:// delegator functions

        /**
        * SwitchCmdL
        * This function delegates the control to other functions based on the command.
        *
        * @param aCmdName the name of the service command which the consumer wants to invoke.
        * @param aInParamList the input parameter list.
        * @param [in,out] aOutParamList the output parameter list, can be empty list or may contain the errors.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void SwitchCmdL( const TDesC8& aCmdName,
            const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

        /**
        * GetListL
        * This function delegates the control to other functions based on the
        * content type of the object requested for retrieval.
        *
        * @param aInParamList the input parameter list. This is parsed and appropriate
        * functions are called based on the type of item to be retrieved (KContentType).
        * @param [in,out] aOutParamList the output parameter list, may contain an iterable instance, an error or be empty.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void GetListL( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

        /**
        * AddL
        * This function delegates the control to other functions based on the
        * content type of the object requested for addition to database.
        *
        * @param aInParamList the input parameter list. This is parsed and appropriate
        * functions are called based on the type of item to be added (KContentType).
        * @param [in,out] aOutParamList the output parameter list, may contain the iterable instance.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void AddL( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

        /**
        * RemoveL
        * This function deletes an item from database based on the type of item.
        *
        * @param aInParamList the input parameter list. This contains the details about the item to be removed.
        * @param [in,out] aOutParamList the output parameter list, is an empty list.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void RemoveL( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

        /**
        * ImportL
        * This function imports landmarks from a file to the database.
        *
        * @param aInParamList the input parameter list.
        * @param [in,out] aOutParamList the output parameter list, may contain the iterable instance.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void ImportL( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

        /**
        * ExportL
        * This function exports a set of landmarks from database to a file.
        *
        * @param aInParamList the input parameter list.
        * @param [in,out] aOutParamList the output parameter list, is an empty list.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void ExportL( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

        /**
        * OrganiseL
        * This function links/unlinks a landmark category to a set of landmarks.
        *
        * @param aInParamList the input parameter list.
        * @param [in,out] aOutParamList the output parameter list, is an empty list.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void OrganiseL( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );
        
        /**
        * Cancel
        * This function cancels a previously requested aynchronous request
        * based on transaction id.
        *
        * @param aInParamList the input parameter list.
        * @param [in,out] aOutParamList the output parameter list, is an empty list.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void Cancel( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

        /**
        * NewTemplateL
        * This function returns a template of the requested type.
        *
        * @param aInParamList the input parameter list.
        * @param [in,out] aOutParamList the output parameter list, contains the template and error code.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void NewTemplateL( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

    private:// helper functions

        /**
        * GetLandmarksL
        * This function retrieves a set of landmarks based on a filter.
        *
        * @param aInParamList the input parameter list.
        * @param [in,out] aOutParamList the output parameter list, may contain the iterable instance.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void GetLandmarksL( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

        /**
        * GetCategoriesL
        * This function retrieves a set of landmark categories based on a filter.
        *
        * @param aInParamList the input parameter list.
        * @param [in,out] aOutParamList the output parameter list, may contain the iterable instance.
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *
        *
        *
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */
        void GetCategoriesL( const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
            MLiwNotifyCallback* aCallback );

        /**
        * GetListDatabasesL
        * This function retrieves a set of landmark databases based on a filter.
        *
        * @param aInParamList the input parameter list.
        * @param [in,out] aOutParamList may contain the iterable instance.
        *
        * @see CLiwGenericParamList
        *
        */
        void GetListDatabasesL (const CLiwGenericParamList& aInParams,
            CLiwGenericParamList& aOutParamList );

        /**
        * AddLandmarksL
        * This function adds a landmark to a landmark database.
        *
        * @param aInParamList the input parameter list.
        *
        * @see CLiwGenericParamList
        *
        */
        void AddLandmarksL( const CLiwGenericParamList& aInParamList,
                CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
                MLiwNotifyCallback* aCallback );

        /**
        * AddCategoryL
        * This function adds a landmark category to a landmark database.
        *
        * @param aInParamList the input parameter list.
        *
        * @see CLiwGenericParamList
        *
        */
        void AddCategoryL ( const CLiwGenericParamList& aInParamList,
                CLiwGenericParamList& aOutParamList, TUint aCmdOptions,
                MLiwNotifyCallback* aCallback );

        /**
        * AddDatabaseL
        * This function adds a landmark database.
        *
        * @param aInParamList the input parameter list.
        *
        * @see CLiwGenericParamList
        *
        */
        void AddDatabaseL ( const CLiwGenericParamList& aInParams );      
        
        void ErrorMessageL( const TDesC8& aServiceCmd, const TDesC8& aKey );
        
        void ValidateParamL( const TDesC8& aServiceCmd, 
                const TDesC8& aKey, 
                const TLiwVariant& aVariant, 
                LIW::TVariantTypeId aType );
        
        TBool ValidateParamL( const TDesC8& aServiceCmd, 
                const TDesC8& aKey, 
                const CLiwMap* aMap,
                LIW::TVariantTypeId aType,
                TBool isMandatory,
                TLiwVariant& aOutVariant );
        
    private:// Data

        /**
        * iService
        * The handle to the CLandmarkService object.
        */
        CLandmarkService* iService;

        /**
        * iObserver
        * MLandmarkObserver instance.
        */
        CLandmarkObserver* iObserver;

        /**
        * iCallbackMap
        * Array of CLandmarkCallbackMap objects.
        */
        RPointerArray<CLandmarkCallbackMap> iCallbackMap;
        
        /**
         * iErrMsg
         * The pointer to the error message.
         */
        HBufC* iErrMsg;
        
        /**
         * iId
         * The id of the added/modified landmark/category.
         */
        HBufC* iId;
    };

#endif // __LANDMARKINTERFACE_H__
