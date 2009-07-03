/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef SERVICEINTERFACE_H
#define SERVICEINTERFACE_H

#include <liwcommon.h>
#include <LiwVariant.h>
#include <LiwGenericParam.h>
#include <LiwServiceHandler.h>


// CLASS DECLARATION
class CSvcRegIterator;

/**
 *  Service interface class for ServiceRegistry SAPI.
 *  Checks the requested command and delegates query to correct core class method.
 */
class CServiceInterface : public CActive, public MLiwInterface
    {
    	
public:
	
    /**
     * Two-phased constructor.
     * @return CServiceInterface* Returns the instance of
     *                  CServiceInterface.
     */
    static CServiceInterface* NewL();

    /**
     * Destructor.
     */
    ~CServiceInterface();

    static void RCriteriaArrayCleanup( TAny* aParam ) ;
    /**
     * This function handles the request of consumer.
     * @param aCmdName Command name of SAPI
     * @param aInParamList  Contains argument on which operation has to
     *                       be performed
     * @param aOutParamList Result of given command will be
     *                       stored in the output parameter list
     * @param aCmdOptions Set option for asynchronous request or
     *                     for canceling the asynchronous request
     * @param aCallback Contains the callback for Asynchronous request
     */
    void ExecuteCmdL( const TDesC8& aCmdName,
                      const CLiwGenericParamList& aInParamList,
                      CLiwGenericParamList& aOutParamList,
                      TUint aCmdOptions = 0,
                      MLiwNotifyCallback* aCallback = 0 );
                            
    /**
     * This function handles the request of consumer.
     * @param aCmdName Command name of SAPI
     * @param aInParamList  Contains argument on which operation has to
     *                       be performed
     * @param aOutParamList Result of given command will be
     *                       stored in the output parameter list
     * @param aCmdOptions Set option for asynchronous request or
     *                     for canceling the asynchronous request
     * @param aCallback Contains the callback for Asynchronous request
     */
    void ExecuteServiceCommandL( const TDesC8& aCmdName,
                                 const CLiwGenericParamList& aInParamList,
                                 CLiwGenericParamList& aOutParamList,
                                 TUint aCmdOptions = 0,
                                 MLiwNotifyCallback* aCallback = 0 );
                               
    /**
     * Close function called by consumer when it wants to delete the interface.
     * This function will release all the internal resources.
     * @return void
     */
    void Close() {delete this;}
    
private:
	
    /**
     * Constructor.
     */    
    CServiceInterface();
    
    /**
     * Two-phased constructor.
     * @return void
     */
    void ConstructL();    
    /**
     * This function processes the command and calls right service function.
     * @param aCmdName Command name of SAPI
     * @param aInParamList  Contains argument on which operation has to
     *                       be performed
     * @param aOutParamList Result of given command will be
     *                       stored in the output parameter list
     * @param aCmdOptions Set option for asynchronous request or
     *                     for canceling the asynchronous request
     * @param aCallback Contains the callback for Asynchronous request
     */
    void ProcessCommandL( const TDesC8& aCmdName,
                          const CLiwGenericParamList& aInParamList,
                          CLiwGenericParamList& aOutParamList,
                          TUint aCmdOptions,
                          MLiwNotifyCallback* aCallback );
    /**
     * Gets the list of ServiceProviders.
     * @param aInParamList Input parameter list.
     * @param aOutParamList Output parameter list.
     * @param aTransactionId: Transaction Id received from LIW 
     * @param aCallBack: Client callback interface used to notify asynchronous call results.
     */
    void GetListL( const CLiwGenericParamList& aInParamList, 
                   CLiwGenericParamList& aOutParamList, 
                   TInt32 aTransactionId, 
                   MLiwNotifyCallback* aCallBack );
                         
    void ListServiceProvidersL(TInt32 aError);        
                            
    virtual void DoCancel(); 
    
    virtual void RunL(); 
    
    friend void GetListProviderL(CServiceInterface* aInterface);                                          
private:
	
    /**
     * Stores the instance of SAPI Core Class.
     */
     MLiwNotifyCallback* iCallback;
            
    //trasaction ID.
    TInt32 iTransactionId;
    
    //Descriptor to hold the service name
    HBufC8* iServiceName;
    
    //Descriptor to hold the interface name    
    HBufC8* iInterfaceName;    
    
    //Min version number. 
    TReal iMinVersion;
    
    //Max version number.
    TReal iMaxVersion;
    
    //Referance to top the Input Parameter list passed by consumer.
    const CLiwGenericParamList* iInParamList;
        
    //handle to the service handler.
    CLiwServiceHandler* iServiceHandler;
    //pointer to the iterator
    CSvcRegIterator* iIterator; 
    //Thread handle
    RThread iThread;            
    };
    
#endif // SERVICEINTERFACE_H
