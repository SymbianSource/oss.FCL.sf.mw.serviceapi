/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Header file for sensor service API core class
*
*/


#ifndef CSENSORSERVICE_H
#define CSENSORSERVICE_H

//System include
#include <e32base.h>
#include <sensrvchannelinfo.h>
#include <sensrvchannel.h>
#include <sensrvchannelfinder.h>

//Constants used in asynchronus calls

//Desired receiving buffer size defined in a count of the 
//channel data objects
const TInt KDesiredCount = 1;

//Maximum receiving buffer size defined in a count of the
//channel data object
const TInt KMaxCount = 1;

//Specifies the maximum time in milliseconds 
//that sensor server waits between updating new data into the 
//receiving buffer
const TInt KBufferingPeriod = 0; 

/**
 *  This class acts as wrapper around functionalities provided by S60 sensor channel 
 *  API. Provides methods to find sendor channels,access channel data .Also have 
 *  methods to set and retreive channel propertiesand property change listening.
 * 
 *  @sensorservice.lib
 *  @since S60 v5.0
 */
class CSensorService : public CBase
    {

	public:
		
	     /**
		 * Symbian Two Phase construction 
		 */
		 IMPORT_C static CSensorService* NewL();

		 /**
		 * Destructor.
		 */
		 virtual ~CSensorService();

		 /**
		 * Find sensor channels based on specified criterion
		 * @since S60 v5.0
		 * @param aSearchCriterion : Specifies the search criterion based on which channel 
		 *  will be searched.
		 * @param aChannelInfoList this will be populated with channel info of all found 
		 *  channels satisfying the search criterion
		 * @return NA
		 */
		 IMPORT_C void FindSensorChannelsL(const TInt aSearchCriterion
		 								  ,RSensrvChannelInfoList& aChannelInfoList);
		 
		/**
		 * Start the channel data listening. Channel data is received into the 
		 * receiving buffer and it can be read using the GetData-function. When new 
		 * data is available in the receiving buffer, a notification is delivered 
		 * via the data listener callback interface (MSensrvDataListener).
		 * @since S60 v5.0
		 * @param aChannelInfo Refers to channel on which listening will be started
		 * @param aDataListener Data listener for the channel. Must be valid 
         * until data listening is stopped.
         * @return NA
		 */
		 IMPORT_C void GetDataNotificationL(const TSensrvChannelInfo& aChannelInfo
		 								   ,MSensrvDataListener* aDataListener);
		 						
		/**
		 * It stops any previously registered asynchronus request i.e. any previously requested listening will
		 * be stopped
		 * @since S60 v5.0
		 * @param aNotificationType  type of notification to be cancelled
		 * see respective enum type in sensorservice.hrh
		 * @param in case aNotification type is NOT EStopChannelChange this refers to
		 * channel ID on which asynch request is to be stopped otherwise it takes its default 
		 * value and need not be supplied by the consumer
		 * @return NA
		 */
		 IMPORT_C void StopNotificationL(TInt aNotificationType,TUint32 aChannelId=0);

		 /**
		 * Check if a particular channel is already open
		 * @since S60 v5.0
		 * @param achannelId channel Id which will be checked
		 * @param In case channel is open this will be filled in with index in iChannelList where
		 * this particular channel entry is stored
		 * @return True/False depending on whether channel is alredy open or not.
		 */
		 TBool IsChannelOpen(TUint32 achannelId,TInt& aIndex);
		/**
		 * Get Channel Property
		 * @since S60 v5.0
		 * @param aPropertyId referes to the property whose values are being requested
		 * @param aChannelInfo refers to channel whose property will be obtained
		 * @param aChannelPropertyList will be populated  with obtained channel properties
		 * @leave KErrNotFound - No open channel with that id for this client found,
         *                    or property does not exist.
		 */		 
		 IMPORT_C void GetChannelPropertyL(const TSensrvChannelInfo& aChannelInfo, 
										   RSensrvPropertyList& aChannelPropertyList);
		 /**
          * Get Scale Factor
          * @since S60 v5.0
          * @param aChannelInfo refers to channel whose property will be obtained
          * @param aMeasureRange will be populated  with obtained channel properties
          * @param aScaleRange will be populated  with obtained channel properties
          * @leave KErrNotFound - No open channel with that id for this client found,
          *                    or property does not exist.
          */      
		 IMPORT_C void GetScaleFactorL(const TSensrvChannelInfo& aChannelInfo, 
		                                  TSensrvProperty& aMeasureRange,
										  TSensrvProperty& aScaleRange);

	private:
	 	/**
	 	 * Constructor
	 	 * @since S60 v5.0
	 	 */
		 CSensorService();
		 void ConstructL();
		  
	 private: // data
	    /**
	     * This stores channel information whenever a channel is opened
	     */
		 RPointerArray <CSensrvChannel> iChannelList;
		/**
		 * Channel  finder object stored for reuse
		 */
		 CSensrvChannelFinder* iChannelFinder;
		 
	};


#endif // CSENSORSERVICE_H
