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
* Description:  CLandmarkCmdGetLandmarks class
 *
*/

#ifndef CLANDMARKCMDLINKCATEGORIES_H_
#define CLANDMARKCMDLINKCATEGORIES_H_

// INCLUDES
#include "clandmarkcmdbase.h"
#include <EPos_Landmarks.h>

class CPosLmCategoryManager;
class MLandmarkObserver;
class CLandmarkManageObjects;
class CLandmarkHandler;
class CPosLandmarkParser;
class CPosLandmarkEncoder;
class CPosLandmarkDatabase;
/**
 * CLandmarkOperation
 * This class processes the async request for retrieval of landmark categories from the landmark
 * database. It implements the StartL ( CLandmarkHandler* aHandle, TInt32 aTransactionId, CLandmarkFilter* aFilter )
 * of CLandmarkCmdBase. After completion of the aynchronous request the MLandmarkObserver instance is notified
 * and the garbage collector is set active.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkOperation) : public CActive
	{
public:
	enum TOperation
		{
		EOrganise,
		EImport,
		EExport,
		};
public:
	// New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CLandmarkOperation object.
	 * @param aObserver The pointer to the observer for this object.
	 * @param aManageObjects The pointer to the garbage collector.
	 * @return A pointer to the created instance of CLandmarkOperation.
	 */
	static CLandmarkOperation* NewL(MLandmarkObserver* aObserver,
			CLandmarkManageObjects* aManageObjects);

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Create a CLandmarkOperation object.
	 * @param aObserver The pointer to the observer for this object.
	 * @param aManageObjects The pointer to the garbage collector.
	 * @return A pointer to the created instance of CLandmarkOperation.
	 */
	static CLandmarkOperation* NewLC(MLandmarkObserver* aObserver,
			CLandmarkManageObjects* aManageObjects);

	/**
	 * ~CLandmarkOperation
	 * Destructor.
	 */
	~CLandmarkOperation();

public:
	// From CLandmarkCmdBase

	// This functions proceeds with the incremental search.
	void LinkL(TInt32 aTransactionId, TPosLmItemId aCategoryId, RArray<
			TPosLmItemId>& aLandmarkIdArray,
			CPosLmCategoryManager* aCategoryManager);

	void UnLinkL(TInt32 aTransactionId, TPosLmItemId aCategoryId, RArray<
			TPosLmItemId>& aLandmarkIdArray,
			CPosLmCategoryManager* aCategoryManager);
	
	void ImportL(TInt32 aTransactionId, CLandmarkHandler* aHandle, 
			CPosLandmarkParser& aLandmarkParser);
	
	void ExportL(TInt32 aTransactionId, CPosLandmarkDatabase* aDatabase, 
			CPosLandmarkEncoder& aLandmarkEncoder,
			const RArray<TPosLmItemId>& aLandmarkIdArray,
			const TDesC& aDestinationFile);

	TInt32 TransactionId()
		{
		return iTransactionId;
		}

private:

	/**
	 * NextStep
	 * This functions proceeds with the incremental search.
	 */
	void NextStep();

private:
	// From CActive

	// RunL.
	// This functions gets called after completion of async request.
	void RunL();

	// DoCancel.
	// This function will cancel ongoing async call.
	void DoCancel();
	
	TInt RunError(TInt aError);

private:
	// Constructors

	/**
	 * CLandmarkOperation.
	 * C++ default constructor.
	 * @param aObserver The pointer to the observer for this object.
	 * @param aManageObjects The pointer to the garbage collector.
	 */
	CLandmarkOperation(MLandmarkObserver* aObserver,
			CLandmarkManageObjects* aManageObjects);

private:
	/**
	 * iTransactionId
	 * The tranaction id assigned to aync request.
	 */
	TInt32 iTransactionId;

	/**
	 * iObserver
	 * The handle to the MLandmarkObserver.
	 */
	MLandmarkObserver* iObserver;

	/**
	 * iOperation
	 * The handle to the CPosLmOperation.
	 */
	CPosLmOperation* iOperation; //owned

	/**
	 * iManageObjects
	 * The handle to the garbage collector.
	 */
	CLandmarkManageObjects* iManageObjects;

	/**
	 * iProgress
	 * To keep track of search progress.
	 */
	TReal32 iProgress;
	CLandmarkHandler* iHandle;
	CPosLandmarkEncoder* iEncoder; //owned
	CPosLandmarkParser* iParser;//owned
	HBufC* iDestinationFile;
	CBufBase* iExportBuffer; //owned
	
	TOperation iOperationType;

	};

#endif /* CLANDMARKCMDLINKCATEGORIES_H_ */
