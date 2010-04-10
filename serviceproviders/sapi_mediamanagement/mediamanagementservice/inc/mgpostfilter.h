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
* Description:  It filter the media items as per the filter value sets
*
*/




#ifndef __CMGPOSTFILTER_H
#define __CMGPOSTFILTER_H

#include <MCLFPostFilter.h>
#include <e32base.h>



// CLASS DECLARATION

/**
*  PostFilter class for Media Management.It filters the media items as per the 
*  filter values set
*  
*  @since  Series60 v3.2
*/
NONSHARABLE_CLASS( CPostFilter ) : public CBase ,public MCLFPostFilter 
    {
    
    public: 
    	 /**
        * Returns the instance of CPostFilter.
        * @since  Series60 v3.2
        * @param  void
        * @return CPostFilter* return the instance of CPostFilter class 
        */
        static CPostFilter* NewL();
        
        /**
    	* Destructor.
    	*/
        virtual ~CPostFilter();
         
        /**
        * Method to filter item list. This method is called when
        * the filtering process is executed by list model refresh.
        * @since  Series60 v3.2
        * @param aItemList Source list, contains all items that are in
        *        the list model
        * @param aFilteredItemList Filtered/destination list, contains all items
        *         that will be in the list model after filtering.
        * @return void
        */
        virtual void FilterItemsL( const TArray<MCLFItem*>& aItemList,
                                   RPointerArray<MCLFItem>& aFilteredItemList );
                                   
        /**
        * This function will set the metadata on which the FilterItemsL function
        * will filter the items in the list model.
        * @since  Series60 v3.2
        * @param aMetaDataId Id of filter criteria as per CLF framework
        * @param aMetaDataType Datatype of the above Id	
        * @return void
        */
        void SetFilterMetaData(const TCLFDefaultFieldId& aMetaDataId,
                               const TCLFItemDataType& aMetaDataType);
        
        /**
        * This Function will set the filter values of the metadata given
        * in SetFilterMetaData function 
        * Leave with KErrArgument if any arguments are out of range
        * @since  Series60 v3.2
        * @param aStartVal Start Value for filter criteria
        *		 (i.e FilterCriteria >= aStartVal)
        * @param aEndVal   End Value for filter criteria
        *   	 (i.e FilterCriteria < aEndVal)
        */
        void SetFilterValueL(const TDesC& aStartVal,const TDesC& aEndVal);
        
        
         /**
        * It will clear  filter metadata field.
        * @since  Series60 v3.2
        * @param  void 
        * @return void 
        */
        void Clear();
        
   private: 
   		/**
        * Constructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */    
        CPostFilter();
        
        /**
        * This function will check if the given aItem matches with the set 
        * filtered values or not.
        * @since  Series60 v3.2
        * @param aItem media item
        * @return -1 If aItem does not match with the set filter values ,0 If it match.
        */
        TInt CompareItem(MCLFItem* aItem);
   
   private:
   		/**
     	* Contains the meta data on which filteration will be performed.
     	*/     
        TCLFDefaultFieldId iFilterMetaData;
        
        /**
     	* Contains the data type of meta data 
     	*/     
        TCLFItemDataType iFilterDataType;
        
        /**
     	* Value of Filter MetaData.
     	*/
        HBufC* iFilterVal;
        
         /**
     	* Starting Value of Filter MetaData if its DataType is Time.
     	*/
        TTime iStartTime;
        
        /**
     	* Ending Value of Filter MetaData if its DataType is Time.
     	*/
        TTime iEndTime;
        
         /**
     	* Starting Value of Filter MetaData if its DataType is Integer.
     	*/
        TInt32 iStartIntVal;
        
         /**
     	* Ending Value of Filter MetaData if its DataType is Integer.
     	*/
        TInt32 iEndIntVal;
        
        

    };


#endif // __CMGPOSTFILTER_H
