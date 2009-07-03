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
* Description:  This Class is used to create instance of CVideoPlayerUtility
*
*/


#ifndef MGMEDIACONTAINER_H_
#define MGMEDIACONTAINER_H_


#include<COECNTRL.H>
#include<W32STD.H>
#include<e32std.h>
#include<e32base.h>
// CLASS DECLARATION

/**
*  CMediaContainer class This class can be used to create instance of CVideoPlayerUtility
*
*  @since  Series60 v3.2
*/
class CMediaContainer : public CCoeControl
    {
     public:
         /**
          * Two-phased constructor
         * @return CImageResolution*  Returns the instance of
          *                                 CImageResolution.
          */                 
         
         static CMediaContainer* NewL(TRect& aRect); 
        /**
        * Symbian ConstructL
        * 
        */      
         void ConstructL(TRect& aRect);
          /**
        * C++ Constructor
   
        * 
        */      
        CMediaContainer();
        /**
          * Destructor
          * @since  Series60 v3.2
          * @param  aUrl Url of the image file
          * 
          */      
        ~CMediaContainer();

        
     public:  
      /**
      * Protectes members of CCoeControl class
      * @since  Series60 v3.2
       * 
     */      
      void Draw(const TRect& aRect) const;
      /**
      * Protectes members of CCoeControl class
      * @since  Series60 v3.2
       * 
     */      
      
       RWindow& ClientWindow(){
       return Window();
       }
       /**
       * Protectes members of CCoeControl class
       * @since  Series60 v3.2
        * 
      */      

       TRect VideoRect() const
       {
       return iVideoRect;
       }
       /**
       * Protectes members of CCoeControl class
       * @since  Series60 v3.2
        * 
      */      

       RWsSession& ClientWsSession()
           {
           return ControlEnv()->WsSession();
           }
       /**
       * Protectes members of CCoeControl class
       * @since  Series60 v3.2
        * 
      */      

       CWsScreenDevice& ScreenDevice()
           {
           return *(ControlEnv()->ScreenDevice());
           }
     private: 
         /**
          *Instance of TRect  
        */      

         TRect iVideoRect;
    };

#endif /* MGMEDIACONTAINER_H_ */
