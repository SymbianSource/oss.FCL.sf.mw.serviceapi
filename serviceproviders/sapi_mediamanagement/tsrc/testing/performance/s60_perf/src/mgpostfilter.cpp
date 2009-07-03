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
* Description:   It filter the media items as per the filter value sets
*
*/




#include <mclfitem.h>
#include "mgpostfilter.h"

const TInt32 KLargestSigned32 = 0x7fffffff;
const TInt64 KLargestSigned64 = 0x7fffffffffffffff;

// -----------------------------------------------------------------------------
// CPostFilter::NewL
// Returns the instance of CPostFilter.
// -----------------------------------------------------------------------------
CPostFilter* CPostFilter::NewL()
	{

	CPostFilter* self = new (ELeave) CPostFilter();
	return self;
	}



// -----------------------------------------------------------------------------
// CPostFilter::~CPostFilter
// Destructor
// -----------------------------------------------------------------------------

CPostFilter::~CPostFilter()
	{
	      delete iFilterVal;
	}

// -----------------------------------------------------------------------------
// CPostFilter::FilterItemsL
// Method to filter source list. This method is called when
// the filtering process is executed by list model refresh method.
// -----------------------------------------------------------------------------
void CPostFilter::FilterItemsL( const TArray<MCLFItem*>& aItemList,
                                RPointerArray<MCLFItem>& aFilteredItemList )
    {
	// It will filter the Items
	MCLFItem* item = NULL;

    for( TInt i = 0 ; i < aItemList.Count() ; ++i )
        {
        item = aItemList[i];

        if( 0 == CompareItem( item ))
            {
            // item should be include in result
            aFilteredItemList.AppendL( item );
            }
        }
	}

// -----------------------------------------------------------------------------
// CPostFilter::SetFilterMetaData
// method to set the filter metadata
// -----------------------------------------------------------------------------
void CPostFilter::SetFilterMetaData(const TCLFDefaultFieldId& aMetaDataId,
									const TCLFItemDataType& aMetaDataType)
	{
	iFilterMetaData = aMetaDataId;
    iFilterDataType = aMetaDataType;
 	}

// -----------------------------------------------------------------------------
// CPostFilter::SetFilterValue
// Method to set the filter value
// return KErrCancel if the FilterMetaData is not Set
// return KErrArgument if the Start or End Value is not Supported
// return KErrNone if sucessful
// -----------------------------------------------------------------------------
void CPostFilter::SetFilterValueL(const TDesC& aStartVal,
								  const TDesC& aEndVal)
	{
	// check the filter values as per the meta data ...
	// If any abnormal values come it will return proper error code..
	switch ( iFilterDataType )
        {
        case ECLFItemDataTypeDesC:
            {
            //Filter Id and Value Not NULL
            if( 0 != aStartVal.CompareF( KNullDesC ) )
               	{
            	iFilterVal = aStartVal.AllocL();
            	}
            else
                {
                User::Leave( KErrArgument );
                }
            break;
            }

        case ECLFItemDataTypeTTime:
	        {
	        if( ( 0 == aStartVal.CompareF( KNullDesC ) ) &&
	        ( 0 == aEndVal.CompareF( KNullDesC ) ) )
	            {
	        	User::Leave( KErrArgument );
	            }
	        if( 0 != aStartVal.CompareF( KNullDesC ) )
    			{
    			// check whether start time is in correct format
	            if( KErrNone != iStartTime.Set( aStartVal ) )
	            	{
	            	User::Leave( KErrArgument );
	            	}
	            }

	        if( 0 != aEndVal.CompareF( KNullDesC ) )
	            {
	            // check whether end time is in correct format
	            if( KErrNone != iEndTime.Set( aEndVal ) )
	                {
	            	User::Leave( KErrArgument );
	            	}
	            }

	        if( iStartTime > iEndTime )
	            {
	        	User::Leave( KErrArgument );
	            }

	        break;
	        }

	    case ECLFItemDataTypeTInt32:
	        {
	        TLex lex;
	        if( ( 0 == aStartVal.CompareF( KNullDesC ) ) &&
	        ( 0 == aEndVal.CompareF( KNullDesC ) ) )
	            {
	        	User::Leave( KErrArgument );
	            }
	        if( 0 != aStartVal.CompareF( KNullDesC ) )
    			{
    			lex = aStartVal;
    			//check if start value was valid
	            if( KErrNone != lex.Val( iStartIntVal ) )
	                {
	            	User::Leave( KErrArgument );
	            	}
    			}

	        if( 0 != aEndVal.CompareF( KNullDesC ) )
            	{
            	lex = aEndVal;
            	//check if end value given was valid
	            if( KErrNone != lex.Val( iEndIntVal ) )
	               	{
            	    User::Leave( KErrArgument );
            		}
            	}
            	
            if( iStartIntVal > iEndIntVal 
            	|| iStartIntVal<0 
            	|| iEndIntVal<0)
	        	{
       	        User::Leave( KErrArgument );
            	}

	        break;
	        }

	   default:
	        {
	       	User::Leave( KErrArgument );
	        }
       	}//End Switch Case
       
    }// End Function


// -----------------------------------------------------------------------------
// CPostFilter::CPostFilter
// Constructor
// -----------------------------------------------------------------------------
CPostFilter::CPostFilter():
             iFilterMetaData( ECLFFieldIdNull ),
		     iFilterVal(NULL),
			 iStartTime( 0 ),
			 iEndTime( KLargestSigned64 ),
			 iStartIntVal( 0 ),
			 iEndIntVal( KLargestSigned32 )
	{

	}





// -----------------------------------------------------------------------------
// CPostFilter::Clear
// It will clear  the filter metadata field
// -----------------------------------------------------------------------------
void CPostFilter::Clear()
	{
	 iFilterMetaData = ECLFFieldIdNull;
	 iFilterDataType = ECLFItemDataTypeNull;
	 iStartIntVal=0;
	 iEndIntVal =KLargestSigned32;
	 iStartTime = 0;
	 iEndTime =KLargestSigned64;


	 delete iFilterVal;
	 iFilterVal = NULL;

	}


// -----------------------------------------------------------------------------
// CPostFilter::CompareItem
// This function will check if the given aItem matches with the set
// filtered values or not.
// @return -1 If aItem does not match with the set filter values ,0 If it match.
// -----------------------------------------------------------------------------
TInt CPostFilter::CompareItem( MCLFItem*  aItem )
	{
	 //this function matches the aItem with the filter values.
     TInt retValue = 0;
	 // If no filter MetaData skip the function
	 if( ECLFFieldIdNull !=  iFilterMetaData  )
	 {
	 switch ( iFilterDataType )
    	{
       	case ECLFItemDataTypeDesC:
       		{
            if( 0 != ( *iFilterVal ).CompareF( KNullDesC ) )
    			{
		        TPtrC itemVal;
	            if( KErrNone == aItem->GetField( iFilterMetaData, itemVal ) )
	            	{
	            	if( 0 != itemVal.CompareF( *iFilterVal ) )
	            		{
	            		retValue = -1;
	            		}
	            	}
	            else
	            	{
	            	retValue = -1;
	            	}
		        }
		    break;
         	}// case ECLFItemDataTypeDesC


      	case ECLFItemDataTypeTTime:
	        {
	        TTime itemVal;
	        if( KErrNone == aItem->GetField( iFilterMetaData, itemVal ) )
	        	{
	            if( !(( itemVal >= iStartTime ) && ( itemVal <= iEndTime )) )
	                {
	            	retValue = -1;
	                }
	            	
	            }
	        else
	         	{
	            retValue = -1;
	         	}
            break;
	        }// case ECLFItemDataTypeTTime


	    case ECLFItemDataTypeTInt32:
	    	{
         	TInt32 itemVal;
	       	if( KErrNone == aItem->GetField( iFilterMetaData, itemVal ) )
	       		{
	        	if( !(( itemVal >= iStartIntVal ) && ( itemVal <= iEndIntVal )))
	        	    {
	        	    retValue = -1;
	        	    }
            	}
	        else
	        	{
	            retValue = -1;
	        	}
	        break;
	        }// case ECLFItemDataTypeTInt32

	    default:
	        {
	       	retValue = -1;
	       	break;
            }
        
        }//End Switch Case
	 }
    return retValue;
	}


