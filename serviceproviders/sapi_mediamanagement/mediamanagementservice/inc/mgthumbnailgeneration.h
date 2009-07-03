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
* Description:  This Class generates thumbnail for media (image/video)
*
*/

#ifndef MGTHUMBNAILGENERATION_H_
#define MGTHUMBNAILGENERATION_H_

#include<e32base.h>
#include<e32cmn.h>
#include<e32def.h>

const TInt KNegVal = -1;


class MThumbnailObserver;
class MResolution;
class CThumbnailManager;
class CThumbnailObserver;

/**
*  CThumbnailGeneration class This class can be used to create instance of CThumbnailGeneration
*
*  @since  Series60 v3.2
*/
class CThumbnailGeneration: public CBase
    {
    
    public :
        
        /**
         * Two-phased constructor
        * @return CThumbnailGeneration*  Returns the instance of
         *                                 CThumbnailGeneration.
         */                 
       
        
       static CThumbnailGeneration* NewL();
       /**
       * This method gives request to generate thumbnail of media file
       * @param aObserver Pointer to Observer 
       * @param aTransactionID  transaction id of thumbnail generation request
       * @param aUrl             It is url of media file whose thumbnail is to be generated
       * @param aHeight         It is required height of thumbnail
       * @param aWidth          It is required width of thumbnail
       * @ return       void 
       */      
     
       void GetThumbnailL(MThumbnailObserver* aObserver,TInt32 aTransactionID, TDesC& aUrl, TInt aHeight =KNegVal, TInt aWidth =KNegVal);

       /**
        * Destructor
        *
        */                 
       ~CThumbnailGeneration();

       /**
        * Cancel method cancels the request of thumbnail generation
        *
        */                 
       TInt Cancel(TInt32 aTransactionId);
    private :    
        /**
         * Constructor
         *
         */                 
        CThumbnailGeneration();
        /**
         * Two phase constructor
         *
         */                 
        void ConstructL();
    private:    
         
        /**
         * It gets the required size of thumbnail  
         *@param aUrl  Url of media file 
         *@param aHeight height of the thumbnail 
         *@param aWidth  width of thumbnail
         *@return TSize Size of the thumbnail
         */                 

        TSize GetthumbsizeL(TDesC& aUrl,TInt aHeight=KNegVal, TInt aWidth=KNegVal);

        /**
         * It calculates the size of thumbnail  
         *@param aRes  Resolution of media file 
         *@param aHeight height of the thumbnail 
         *@param aWidth  width of thumbnail
         *@return TSize Size of the thumbnail
         */                 
        TSize CalculateSize(TSize aRes, TInt aHeight = KNegVal, TInt aWidth = KNegVal);

        /**
         * It calculates the size of thumbnail  
         *@param aUrl  Url of media file 
         *@return MResolution* Instance of media resolution
         */          
        MResolution* GetResolutionobjL(TDesC& aUrl);
        /**
         * Checks wehter the url is valid or not
         *@param aUrl  Url of media file 
         *@return void 
         */          
        void  IsUrlValidL(TDesC& aUrl);
        /**
         * Checks wehter the url is valid or not
         *@param aThumbpath  Url of media file 
         *@param aRefDir     A refrence directory where thumbnail will be saved
         *@return TBool      If thumbnail exists then  it is true else false   
         */               
       TBool IsThumbnailExistL(const TDesC& aThumbpath,const TDesC& aRefDir);
       /**
        * Creates the thumbnail path 
        *@param aUrl    Url of the media file 
        *@param aThumbsize     Thumbnail size
        *@param aRefDir        A refrence directory where thumbnail will be saved
        *@param aThumbnailPath Path where thumbnail need to be saved 
        *@return void          
        */               
       void CreateThumbnailPathL(TDesC& aUrl, TSize aThumbsize,TDes& aRefDir ,TDes& aThumbnailPath);
    
    private:

        /**
         *Pointer to instance of CThumbnailObserver  
         */      
        CThumbnailObserver* iThumbnailObserver;

        /**
         *Pointer to instance of CThumbnailManager  
         */      
        CThumbnailManager* iThumbnailManager;
 
    };

#endif /* MGTHUMBNAILGENERATION_H_ */
