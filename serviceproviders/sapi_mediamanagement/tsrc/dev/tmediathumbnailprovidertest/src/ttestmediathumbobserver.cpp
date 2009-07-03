/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This Class is observer for the Launching Application
*
*/


#include <e32const.h>
#include<e32cmn.h>
#include<e32base.h>
#include "ttestmediathumbobserver.h"
#include"imageresolution.h"
#include"mginterface.h"
_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");

// -----------------------------------------------------------------------------
// CThumbnailObserver::NewL
// Returns the instance of CLauncherObserver.
// -----------------------------------------------------------------------------
CThumbnailObserver* CThumbnailObserver::NewL(CActiveSchedulerWait * aWait,TInt aWidth, TInt aHeight)
	{
	CThumbnailObserver* self = new( ELeave ) CThumbnailObserver(aWait,aWidth,aHeight);
	return self;
	}


// ---------------------------------------------------------------------------
// call back
// ---------------------------------------------------------------------------
//
TInt CThumbnailObserver :: HandleNotifyL( TInt /*aCmdId*/, TInt aEventId, CLiwGenericParamList& aEventParamList,const CLiwGenericParamList& /*aInParamList*/)
    {
    
    RFs fs;
    
    fs.Connect();
    
    RFile file;
    
    file.Replace(fs,_L("C:\\Data\\CallbackLog.txt"),EFileWrite | EFileStreamText);
    
    file.Write(_L8("In callback\n"));
 
    
    
    iCancel = EFalse;
    if ( aEventId == KLiwEventCanceled  )
        {
            iCancel = ETrue;
            file.Write(_L8("cancel \n"));
            file.Close();
            fs.Close();
            return 0 ;
        }
    iWait->AsyncStop();
    file.Write(_L8("schedular is stopped \n"));
    if ( aEventId == KLiwEventCompleted )   
        {
        const TLiwGenericParam* p= NULL;
        TInt pos = 0;
        file.Write(_L8("Event completed \n"));    
        p = aEventParamList.FindFirst(pos, KErrorCode ); // Finding Error Code
        
        if(p)
            {
            iErrorReturn = p->Value().AsTInt32();
            }
        else
            {
            iErrorReturn = KErrGeneral; 
            }
      
  
        pos = 0;
         p = aEventParamList.FindFirst(pos, KResponse ); // Finding thumbanilurl
         
         if( p )
             {
             iThumbnailPath = p->Value().AsDes().Alloc();
             }
         file.Write(_L8("Got Thumbnail path \n"));
        
        }
    // Getting thumbanil path ;
   
    if((iWidth>0) && (iHeight>0) && (iErrorReturn == KErrNone) )
    	{
    		CImageResolution* imageresolution = CImageResolution::NewL(*iThumbnailPath);
    		CleanupStack::PushL(imageresolution);
    		TSize sz(0,0);
    		imageresolution->getresolutionL(sz);
    	
    	if((sz.iHeight == iHeight) && (sz.iWidth == iWidth))
    	{
    		iErrorReturn = KErrNone;
    	
    	}else
    	    iErrorReturn = KErrGeneral;
 
    	CleanupStack::PopAndDestroy(imageresolution);
   } 
   
    file.Close();
    
    fs.Close();
   
   return iErrorReturn;
    }




// ---------------------------------------------------------------------------
// consturctor
// ---------------------------------------------------------------------------
//
CThumbnailObserver::CThumbnailObserver(CActiveSchedulerWait * aWait,TInt aWidth, TInt aHeight )
	{
	 iWait = aWait;
	 iReason = 10 ; //Reason of failure can be either 0 or some negative valuw which incater 
	 //error but it cant be greater than 0 
	 iThumbnailPath = NULL;
	 iWidth = aWidth;
	 iHeight = aHeight;
	}
