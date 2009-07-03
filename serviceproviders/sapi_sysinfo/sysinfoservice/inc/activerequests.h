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
* Description:  describes system information notifiers.
*
*/


#ifndef __ACTIVEREQUESTS_H__
#define __ACTIVEREQUESTS_H__

//INCLUDES
#include <e32property.h>
#include "sysinfo.h"
#include "sysrequest.h"

// CONSTANT DECLARATIONS

// FORWARD DECLARATIONS
class   CRepository;

/**
*  @ref CActiveRequest base class to be extended for implementing asynchronous requests.
*	static member function CreateActiveRequestL() is a factory method to create CActiveRequest
*	object to handle specified asynchronous operation.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CActiveRequest) : public CActive
    {
    public:
    /**
    * Issues asynchronous request. funtionality need to provided by implementing class.
    */
    virtual TInt Request() = 0;
    /**
    * @return Transaction ID associated with the asynchronous request.
    */
    inline TInt32  TransactionID() const;
    /**
    * @return type of request this object handling.
    */
    inline TSysRequest::TRequestType  RequestType() const;
    /**
    * Destructor.
    */
    ~CActiveRequest();

    public:	
    /**
    * This is an factory method to create asynchronous request based on request 
    * specified in aSysRequest.
    *
    * @param aSysRequest Input request consists of SA, Type of request, TID 
    *	and SystemData if any.
    *
    * @param aActiveObj On return aActiveObj consists of active object that will 
    *	handle requested asynchronus operation.
    *
    * @error	@p KErrNotFound	If requested SA not found.
    *			@p KErrNotSupported	If specified requeust type doesn't qualify with  
    *				requested SA specification.
    *			@p KErrArgument	if specified input SystemData doesn't comply 
    *				system attribute specification. 
    */
    static void CreateActiveRequestL( const TSysRequest& aSysRequest,
                                        CActiveRequest*& aActiveObj );

    protected:
    /**
    * C++ default constructor.
    */
    CActiveRequest(TSysRequest::TRequestType aReqType,TInt32 aTransID,
                                            ISystemObserver* aObsrvr);
    /**
    * returns observer.
    */
    inline ISystemObserver* SystemObserver();

    /**
    * This function creates active objects that handles network related
    * system attributes.
    *
    * @param aSysRequest Input request consists of SA, Type of request, TID 
    *                   and SystemData if any.
    *
    * @param aActiveObj On return aActiveObj consists of active object that will 
    *                   handle requested asynchronus operation.
    *
    * @error    @p KErrNotSupported	If specified requeust type doesn't qualify with  
    *               requested SA specification.
    *           @p KErrArgument	if specified input SystemData doesn't comply 
    *               system attribute specification. 
    */
    static void CreateNetworkRequestL(const TSysRequest& aSysRequest,
                                        CActiveRequest*& aActiveObj);

    /**
    * This function creates active objects that handles General Entity related
    * system attributes.
    *
    * @param aSysRequest Input request consists of SA, Type of request, TID 
    *	and SystemData if any.
    *
    * @param aActiveObj On return aActiveObj consists of active object that will 
    *	handle requested asynchronus operation.
    *
    * @error    @p KErrNotSupported	If specified requeust type doesn't qualify with  
    *               requested SA specification.
    *           @p KErrArgument	if specified input SystemData doesn't comply 
    *               system attribute specification. 
    */
    static void CreateGeneralRequestL(const TSysRequest& aSysRequest,
    CActiveRequest*& aActiveObj);

    /**
    * This function creates active objects that handles Display Entity related
    * system attributes.
    *
    * @param aSysRequest Input request consists of SA, Type of request, TID 
    *	and SystemData if any.
    *
    * @param aActiveObj On return aActiveObj consists of active object that will 
    *	handle requested asynchronus operation.
    *
    * @error    @p KErrNotSupported	If specified requeust type doesn't qualify with  
    *               requested SA specification.
    *           @p KErrArgument	if specified input SystemData doesn't comply 
    *               system attribute specification. 
    */
    static void CreateDisplayRequestL(const TSysRequest& aSysRequest,
                                        CActiveRequest*& aActiveObj);

    private:
    //	Transaction ID
    TInt32                      iTransactionID;

    //	Request Type.
    TSysRequest::TRequestType   iRequestType;
    //
    ISystemObserver*            iObserver;
    };

#include "activerequest.inl"

/**
*  @ref ActiveStore This class maintains pointer reference of all ongoing 
*	active requests. Offers funtionality to add or remove an active 
*	request to/from the list. An active object request is identified by this 
*	unique Transaction ID.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
class ActiveStore
    {
    public:
    /**
    * This function appends a new active request to the active store.
    *
    * @param aActiveReq Input active request to be appended.
    *
    * @error @p KErrAlreadyExists  
    *               if Transaction ID specified already exists.
    */
    static void AddRequestL(const CActiveRequest* aActiveReq);
    /**
    * This function removes an active request in active store.
    *
    * @param aActiveReq Input active request to be appended.
    *
    * @return   @p KErrNone on success.
    *           @p KErrNotFound if specified transaction id doesn't exists.
    *				
    */		
    static TInt RemoveRequest(TInt32 aTransID);
    
    private:
    /**
    * This function releases or removes all requests stored.
    */		
    static void ReleaseResources();
    
    private:
    //pointer array of active requests.
    static RPointerArray<CActiveRequest>  iHandlers;

    friend class CSysInfoService;
    };

/**
*  @ref CCenrepNotifier active object class to handle asynchronous notifications
*       of central repository key value changes.
*
*  @lib sysinfoservice.lib
*  @since 3.2
*/
NONSHARABLE_CLASS(CCenrepNotifier): public CActiveRequest
    {
    public:	// Constructors and destructor

    // Enumeration of supported commands by CCenrepNotifier.
    enum TCommand  {
        EPridictiveText,
        EInputLanguage,
        EBlueTooth,
        EVibra,
        EKeyLock,
        };

    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CCenrepNotifier* NewL( const TSysRequest& aRequest, 
                                            TCommand aCommand);
    /**
    * Destructor.
    */
    ~CCenrepNotifier();

    private:
    /**
    * C++ default constructor.
    */
    CCenrepNotifier(TSysRequest::TRequestType aReqType, TInt32 aTransID, 
                            TCommand aCommand, ISystemObserver* aObsrver);

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL(const TSysRequest& aRequest);

    public:	
    /**
    * Issues notification request.
    */
    TInt Request();

    protected: // from CActive
    
    void RunL();

    void DoCancel();

    private:	// DATA
    /**
    *	Local copy of Entity.
    */
    HBufC*          iEntity;

    /**
    *	Local copy of Key.
    */
    HBufC*          iKey;

    /**
    *	Handle to repository.
    */
    CRepository* 	iCenrep;

    /**
    *	Repository UID
    */
    TUid            iRepositoryUid;

    /**
    *	Repository KEY
    */
    TUint 			iRepositoryKey;

    /**
    *	Repository KEY
    */
    TInt			iValue;

    /**
    *	Supported command
    */
    TCommand		iCommand;
    };

/**
*  @ref CPubSubNotifier active object class to handle publish & subscribe key value 
*   changes.
*  @lib   sysinfoservice.lib
*  @since 3.2
*/
NONSHARABLE_CLASS(CPubSubNotifier): public CActiveRequest
    {
    public:	// Constructors and destructor

    // Enumeration of supported commands by CPubSubNotifier.
    enum TCommand
        {
        ERegistrationStatus,
        ENetworkMode,
        EChargingStatus,
        EFlipStatus,
        EGripStatus,
        EInfraRed,
        EMemoryCard
        };

    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CPubSubNotifier* NewL(const TSysRequest& aRequest, TCommand aCommand);
    /**
    * Destructor.
    */
    ~CPubSubNotifier();

    private:

    /**
    * C++ default constructor.
    */
    CPubSubNotifier( TSysRequest::TRequestType aReqType, TInt32 aTransID, 
                            TCommand aCommand, ISystemObserver* aObsrver);

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL( const TSysRequest& aRequest);

    public:	
    /**
    * Issues notification request.
    */
    TInt Request();

    protected: // from CActive

    void RunL();

    void DoCancel();

    private:	// DATA
    /**
    *	Local copy of Entity.
    */
    HBufC*      iEntity;

    /**
    *	Local copy of Key.
    */
    HBufC*      iKey;

    /**
    *	RProperty handle.
    */
    RProperty   iProperty;

    /**
    *	RProperty category UID.
    */
    TUid        iPropertyUid;

    /**
    *	RProperty KEY of any category.
    */
    TUint       iPropertyKey;

    /**
    *	RProperty category,KEY value.
    */
    TInt        iValue;

    /**
    *	CPubSubNotifier supported input command.
    */
    TCommand    iCommand;
    };

/**
*  @ref CCriticalMemNotifier active object class to handle critical memory 
*   notifications of drive.
*  @lib   sysinfoservice.lib 
*  @since 3.2
*/

NONSHARABLE_CLASS(CCriticalMemNotifier): public CActiveRequest
    {
    public:	// Constructors and destructor

    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CCriticalMemNotifier* NewL(const TSysRequest& aRequest);

    /**
    * Destructor.
    */
    ~CCriticalMemNotifier();

    private:

    /**
    * C++ default constructor.
    */
    CCriticalMemNotifier(TSysRequest::TRequestType aReqType, TInt32 aTransID,
                                                    ISystemObserver* aObsrver);

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL(const TSysRequest& aRequest);

    public:	

    TInt Request();

    protected: // from CActive

    void RunL();

    void DoCancel();

    private:	// DATA

    /**
    *	Session handle to file server.
    */
    RFs         iFs;

    /**
    *	Drive number
    */
    TInt        iDrvNumber;

    /**
    *	Critical memory associcated with the drive.
    */
    TInt        iCriticalFreeMemory;
    };


#endif __ACTIVE_REQUESTS_H__