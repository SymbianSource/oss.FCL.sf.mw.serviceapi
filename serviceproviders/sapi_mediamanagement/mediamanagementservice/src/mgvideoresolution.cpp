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
* Description:  This Class is used to find resolution of video file
*				
*
*/



#include"mgvideoresolution.h"
#include "mgmediacontainer.h"
/// Implementation for CMediaContainer

// -----------------------------------------------------------------------------
// CVideoResolution::NewL
// Returns the instance of CVideoResolution.
// -----------------------------------------------------------------------------

CVideoResolution* CVideoResolution::NewL(TDesC& aUrl)
    {
    CVideoResolution* self = new(ELeave)CVideoResolution();
    CleanupStack::PushL(self);
    self->ConstructL(aUrl);
    CleanupStack::Pop(self);
    return self;
    }
// -----------------------------------------------------------------------------
// CVideoResolution::CVideoResolution
// C++ Constructor
// -----------------------------------------------------------------------------
CVideoResolution::CVideoResolution():iMediaContainer(NULL),iVideoUtility(NULL),iVideoFilePath(NULL)
{

}
// -----------------------------------------------------------------------------
// CVideoResolution::ConstructL
// Two phase constructor
// -----------------------------------------------------------------------------
void CVideoResolution::ConstructL(TDesC& aUrl)
    {
    // Creating container class instance
    TRect rect(TPoint(2,2),TSize(4,4)); 
    iMediaContainer =CMediaContainer::NewL(rect) ;

    iVideoUtility = CVideoPlayerUtility::NewL(*this,EMdaPriorityNormal,EMdaPriorityPreferenceNone,iMediaContainer->ClientWsSession(),iMediaContainer->ScreenDevice(),iMediaContainer->ClientWindow(), iMediaContainer->VideoRect(),iMediaContainer->VideoRect());

    iVideoFilePath = aUrl.AllocL();
    }
// -----------------------------------------------------------------------------
// CVideoResolution::~CVideoResolution
// Destructor
// -----------------------------------------------------------------------------
CVideoResolution::~CVideoResolution()
    {
    if(iVideoFilePath)
        {
        delete iVideoFilePath;
        }

    if(iMediaContainer)
    	{
    	delete iMediaContainer;
    	}
	if(iVideoUtility)    
    	{
    	delete iVideoUtility;
    	}
   
   
    }
// -----------------------------------------------------------------------------
// CVideoResolution::GetresolutionL
// Get Resolution 
// -----------------------------------------------------------------------------

TBool CVideoResolution::GetresolutionL(TSize& aSize)
    {
    iVideoUtility->OpenFileL(*iVideoFilePath);
    CActiveScheduler::Start();
    iVideoUtility->Prepare();
     CActiveScheduler::Start();
   iVideoUtility->VideoFrameSizeL(aSize);
   
   if(aSize == TSize(0,0))
        {
        return false;
        }
    
    return true;    
    }

// -----------------------------------------------------------------------------
// CVideoResolution::MvpuoOpenComplete
// Protected method derived from MVideoPlayerUtilityObserver
// -----------------------------------------------------------------------------

void CVideoResolution::MvpuoOpenComplete(TInt aError){
 iErr= aError;
 CActiveScheduler::Stop();
 
 }
 
// -----------------------------------------------------------------------------
// CVideoResolution::MvpuoPrepareComplete
// Protected method derived from MVideoPlayerUtilityObserver
// -----------------------------------------------------------------------------
 void CVideoResolution::MvpuoPrepareComplete(TInt aError){
 iErr= aError;
 CActiveScheduler::Stop();

 }
       
 // -----------------------------------------------------------------------------
 // CVideoResolution::MvpuoFrameReady
 // Protected method derived from MVideoPlayerUtilityObserver
 // -----------------------------------------------------------------------------

 void CVideoResolution::MvpuoFrameReady(CFbsBitmap& aFrame,TInt aError)
     {
     iErr= aError;
     CActiveScheduler::Stop();
  
     }
 // -----------------------------------------------------------------------------
 // CVideoResolution::MvpuoPlayComplete
 // Protected method derived from MVideoPlayerUtilityObserver
 // -----------------------------------------------------------------------------
  void CVideoResolution::MvpuoPlayComplete(TInt aError) {
  iErr= aError;
  CActiveScheduler::Stop();

  }
  // -----------------------------------------------------------------------------
   // CVideoResolution::MvpuoEvent
   // Protected method derived from MVideoPlayerUtilityObserver
   // -----------------------------------------------------------------------------
   void CVideoResolution::MvpuoEvent(const TMMFEvent& aEvent) {
   
   CActiveScheduler::Stop();
   }    
