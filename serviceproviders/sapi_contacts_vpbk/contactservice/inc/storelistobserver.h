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
* Description:  store list observer.
*
*/


#ifndef C_STORELISTOBSERVER_H
#define C_STORELISTOBSERVER_H


#include <mvpbkcontactstoreListobserver.h>    //base class for vCardEng
#include <CVPbkVCardEng.h>
#include <MVPbkContactStore.h>


class CVPbkVCardEng;
class MVPbkStoreContact;
class CContactService;

class MContactStoreListObserver:public MVPbkContactStoreListObserver
{
  public:virtual void SetEngine(CVPbkVCardEng* aEngine)=0;
         virtual void SetContactStore(MVPbkContactStore* aContactStore)=0;
         virtual void SetContactService(CContactService* aContactService)=0;
	    
  protected:  // Destructor
        virtual ~MContactStoreListObserver() { }
};



#endif //// C_STORELISTOBSERVER_H