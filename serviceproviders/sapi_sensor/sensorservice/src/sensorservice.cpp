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
* Description:  This file contains implementation for the core class of sensor service API
*
*/


#include "sensorservice.h"
#include "sensorservice.hrh"


/*
-----------------------------------------------------------------------------
    CSensorService::CSensorService()
    Description   : Symbian default Constructor can NOT contain
                    any code that might leave.
    Return values : N/A
-----------------------------------------------------------------------------
*/
CSensorService::CSensorService()
	{
	}

/*
-----------------------------------------------------------------------------
    void CSensorService::ConstructL()
    Description        : Symbian 2nd phase constructor can leave.
    Return values      : N/A
-----------------------------------------------------------------------------
*/

void CSensorService::ConstructL()
	{
	}



/*
-----------------------------------------------------------------------------
    CSensorService* CSensorService::NewL()
    Description                   : Two-phased constructor.
    Return values                 : CSensorChannelService* object pointer
-----------------------------------------------------------------------------
*/

EXPORT_C CSensorService* CSensorService :: NewL()
	{
	CSensorService* self = new(ELeave) CSensorService();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;			
	}


/*
-----------------------------------------------------------------------------
    CSensorService::~CSensorService()
    Description   : Destructor, free allocated resources
    Return values : N/A
-----------------------------------------------------------------------------
*/

CSensorService::~CSensorService()
	{
	TInt count = iChannelList.Count();
	for (TInt i=0;i<count;i++)
		{
		iChannelList[i]->CloseChannel();
			
		}
	iChannelList.ResetAndDestroy();

	if ( iChannelFinder )
		delete iChannelFinder;
	}
	
/*
-----------------------------------------------------------------------------
    CSensorService::FindSensorChannelsL()
    Description   : Finds channel which matches the search criterion
    Return values : NA
-----------------------------------------------------------------------------
*/	
EXPORT_C void CSensorService:: FindSensorChannelsL(const TInt aSearchCriterion
														 ,RSensrvChannelInfoList& aChannelInfoList)
	{
	if ( !iChannelFinder )
		{
		//Construct a channel finder.
	    iChannelFinder = CSensrvChannelFinder::NewL();
	    	
		}
    
    //Create and fill channel search criteria.
    TSensrvChannelInfo channelInfo;
    channelInfo.iChannelType = aSearchCriterion;
    
    //Find  channel
    iChannelFinder->FindChannelsL( aChannelInfoList , channelInfo );
	}
/*
-----------------------------------------------------------------------------
    CSensorService::StartGettingDataNotification()
    Description   : Register to start receiving channel data
    Return values : NA
-----------------------------------------------------------------------------
*/	
	
EXPORT_C void CSensorService::GetDataNotificationL(const TSensrvChannelInfo& aChannelInfo 
														 ,MSensrvDataListener* aDataListener)
	{
	TInt index;
	//Channel Id of the specified channel in the input parameter
	TUint32 channelId = aChannelInfo.iChannelId;
	//Find if specified channel is already opened
	if ( ( IsChannelOpen( channelId,index ) ) )
		{
		iChannelList[index]->StartDataListeningL( aDataListener, 
                                         KDesiredCount, 
                                         KMaxCount, 
                                         KBufferingPeriod );
		}	
   	//else open new channel and set data listener for it
	else
		{
		CSensrvChannel* sensorChannel = CSensrvChannel::NewL( aChannelInfo );
		CleanupStack::PushL( sensorChannel );
	
	
        //open requested channel
        sensorChannel->OpenChannelL();
    
        iChannelList.Append(sensorChannel);
        sensorChannel->StartDataListeningL( aDataListener, 
                                         KDesiredCount, 
                                         KMaxCount, 
                                         KBufferingPeriod );
        CleanupStack::Pop( sensorChannel );
		}
	}


/*
---------------------------------------------------------------------------------------
    CSensorService::StopNotificationL()
    Description   : Stop getting any previously registered notification  from a channel
    Return values : NA
---------------------------------------------------------------------------------------
*/	
	
EXPORT_C void CSensorService::StopNotificationL(TInt aNotificationType,TUint32 aChannelId )
	{
	TInt index ;
	
	if ( aChannelId == 0 )
		{
		if ( !iChannelFinder )	
			User::Leave(KErrArgument);
		}
	else if( ( IsChannelOpen( aChannelId,index ) ) )
		{
		switch( aNotificationType )
			{
			case EStopData:
				iChannelList[index]->StopDataListening();
				break;
			}
		}
	else
		 User::Leave( KErrArgument );
	}
	
/*
-----------------------------------------------------------------------------
    CSensorService::IsChannelOpen()
    Description   : Check if a channel is open
    Return values : True if specified channel is open ;False otherwise
-----------------------------------------------------------------------------
*/	
	
TBool CSensorService::IsChannelOpen(TUint32 aChannelId,TInt& aIndex)
{
	//Find Number of channel already opened
	TInt chnlCount = iChannelList.Count();
	
	//Check if aChannelId matches with any one of the opened channel
	for(TInt i=0;i<chnlCount;i++)
		{
		const TSensrvChannelInfo& channelInfo = iChannelList[i]->GetChannelInfo();
		if ( channelInfo.iChannelId == aChannelId )
			{
			aIndex = i;
			return TRUE;
			}
		}
		return FALSE;
}


/*
-----------------------------------------------------------------------------
    CSensorService::GetChannelProperty()
    Description   : Get property of specified channel
    Return values : NA
-----------------------------------------------------------------------------
*/	
EXPORT_C void CSensorService::GetChannelPropertyL( const TSensrvChannelInfo& aChannelInfo, 
														  RSensrvPropertyList& aChannelPropertyList )
	{
	TInt index;
	//Channel Id of the specified channel in the inpiut parameter
	TUint32 channelId = aChannelInfo.iChannelId;
	//Find if specified channel is already opened
	if ( ( IsChannelOpen( channelId,index ) ) )
		{
		iChannelList[index]->GetAllPropertiesL( aChannelPropertyList );
		}
	//else open new channel and get property change listener for it
	else
		{
		CSensrvChannel* sensorChannel = CSensrvChannel::NewL( aChannelInfo );
        CleanupStack::PushL( sensorChannel );
        //open requested channel
        sensorChannel->OpenChannelL();
        sensorChannel->GetAllPropertiesL( aChannelPropertyList );
        sensorChannel->CloseChannel();
        CleanupStack::PopAndDestroy( sensorChannel );
		}
			
	}

