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

#ifndef CALLBACK_H__
#define CALLBACK_H__

#include  <e32base.h>
#include "singlecontact.h"
#include "contactiter.h"
#include "contactcallback.h"




_LIT(KCntSimDbUri,"sim://global_adn");

// _LIT8(KFirstName,"FirstName");
_LIT(KName,"Arnold"); 
_LIT8(KNumber,"MobilePhoneGen");
_LIT(KPhoneNumber,"09918765432");


class CContactCallBack : public CBase, public MContactCallback
    {

    public:

        /**
        * 
        * @return void
        */

   virtual void HandleReturnValue( TOperationEvent aEventId, const TInt& aError, TInt aTransId );

   virtual void HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId );
 

	     /**
        * Destructor.
        */
        virtual ~CContactCallBack() ;
        
        /**
        * NewL function .
        */
        
        IMPORT_C static CContactCallBack* NewL(RFile* afile );
		
	public :		        
        
        TInt32 iErrCode;
        TInt iTransId;
   
   public :
   
   HBufC8* iId;
   CSingleContact* iCont;        
        
    private :
            
     CContactCallBack(RFile* afile );
	
	private:     
    
     RFile* ifile;
            
            
            
            
            
 

	};


#endif // CALLBACK_H__