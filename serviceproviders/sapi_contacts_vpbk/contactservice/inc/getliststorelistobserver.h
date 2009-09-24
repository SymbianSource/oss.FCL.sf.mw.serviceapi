/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Observer for getlist api of contact service.
*
*/


#ifndef C_GETLISTSTORELISTOBSERVER_H
#define C_GETLISTSTORELISTOBSERVER_H

#include <CVPbkContactManager.h>
#include <MVPbkContactStoreObserver.h>

#include "contactservice.h"
#include "contactcallback.h"
#include "contactservice.hrh"

class CContactService;
class CContactIter;
class CContactViewObserver;
const TInt KMaxUriLen = 0x1000;

/**
 * This class has methods for handling the return from Async open of a contacts database.
 */
 
class CGetListStoreListObserver:public CBase,
								public MVPbkContactStoreListObserver,
								public MCancelAsync
{

   

public:

    static CGetListStoreListObserver* NewL(const TDesC& aUri,
										   const TDesC8& aContactId, 
										   const TDesC& aSearchVal, 
										   CSearchFields* aSearchFields,
										   TOrder aSortOrder,
										   MContactCallback *aCallback,
										   CContactService *aContactService,
										   CContactIter* aIter,
										   Ttype atype,
										   TInt aTransId,
										   MVPbkContactStore* aContactStore,
										   TCmdType val);
   
    ~CGetListStoreListObserver();

	/*
	 * Implementation of Cancel of MCancelAsync
	 */
	void Cancel();

private: // from MVPbkContactStoreListObserver

     void ConstructL(const TDesC8& aContactId, const TDesC& aSearchVal);
    /**
     * An indication that the contact store is ready.
     *
     * @param aContactStore A reference to the store sending the indication.
     * @return None.
     */
    void StoreReady( MVPbkContactStore& aContactStore );

    /**
     * An indication that the contact store is not ready.
     *
     * @param aContactStore A reference to the store sending the indication.
     * @param aReason An error code defining the reason for unavailability.
     * @return None.
     */
    void StoreUnavailable( MVPbkContactStore& aContactStore,
                           TInt aReason );

    /**
     * An indication for a contact store event.
     *
     * @param aContactStore A reference to the store sending the indication.
     * @param aStoreEvent The contact store event.
     * @return None.
     */
    void HandleStoreEventL( MVPbkContactStore& aContactStore,
                            TVPbkContactStoreEvent aStoreEvent );

    /**
     * An indication that the contact store is opened successfully.
     *
     * @return None.
     */
    void OpenComplete();
    
private:

    CGetListStoreListObserver(const TDesC& aUri,
            				  const TDesC8& aContactId, const TDesC& aSearchVal, 
            				  CSearchFields* aSearchFields,
            				  TOrder aSortOrder,MContactCallback *aCallback,
            				   CContactService *aContactService,
            				  CContactIter* aIter, enum Ttype atype, 
            				  TInt aTransId,MVPbkContactStore* aContactStore, TCmdType val);
    				 
   /**
	*  Sets the view of the database and also creates a filtered view
	*/
    void CreateAndFilterViewL(MVPbkContactStore& aContactStore);
  
  
 private: 
 	//Store Uri  
    TBufC<KMaxUriLen> iUri;
    
    //ContactId
    HBufC8* iContactId; 
    
    //Search Value
    HBufC* iSearchVal;
    
    //Fields to search in
	CSearchFields* iSearchFields;
	//Default list for search fields
	CVPbkFieldTypeRefsList* iFieldsList;
	//Order in which the result is to be sorted
    TOrder iSortOrder;   
    
    //Callback function
    MContactCallback *iCallback;
    
    //Pointer to Contact service
 	CContactService *iContactService;    
    //Output param
    CContactIter* iIter;
    
    //Search on Contacts/Groups/Databases
    Ttype iType;
    
    //Transaction Id
    TInt iTransId;
    
    /*
     * Pointer to contact store instance.
     */ 
     MVPbkContactStore* iContactStore;
     
     /*
      * RetrieveL() Handle
      */
	 MVPbkContactOperationBase* iRetOp;
	 TCmdType iVal;
};

#endif//C_GETLISTSTORELISTOBSERVER_H