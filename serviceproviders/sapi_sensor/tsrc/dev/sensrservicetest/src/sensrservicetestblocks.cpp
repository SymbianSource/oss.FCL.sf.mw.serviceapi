/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/


#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <e32base.h>
//#include <stdio.h>

// INCLUDE FILES
#include "sensrservicetest.h"
#include "sensrdatacallback.h"

_LIT(KLogChannelNotFound,"Channel not found - %d\n");
_LIT(KLogFindChannelFail,"Find channel failed for %d channel with %d error\n");
_LIT(KLogChannelFound,"Find channel passed with %d channel having %d channels\n");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSensrServiceTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CSensrServiceTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CSensrServiceTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CSensrServiceTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestFindChannels",CSensrServiceTest::TestFindSensrChannel ),
        ENTRY( "TestListenData",CSensrServiceTest::TestListenData ),
        ENTRY( "TestGetProperty",CSensrServiceTest::TestGetProperty ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt CSensrServiceTest::TestFindSensrChannel( CStifItemParser& aItem )
    {
	__UHEAP_MARK;
    CSensorService* sensrChannel = CSensorService::NewL();
    RSensrvChannelInfoList channelInfoList;
    TInt channel;
    aItem.GetNextInt(channel);
    
    TRAPD(leavecode,(sensrChannel->FindSensorChannelsL(channel ,channelInfoList)));
   
    //TInt error = sensrChannel->FindSensorChannelsL(channel ,channelInfoList);
    
    if(leavecode == KErrNotFound)
    {
    	iLog->Log(KLogChannelNotFound,channel);
    	leavecode = KErrNone;
    }
    else if(leavecode)
    {
    	iLog->Log(KLogFindChannelFail,channel,leavecode);
    }
    else
    {
    	TInt count = channelInfoList.Count();
    	iLog->Log(KLogChannelFound,channel,count);
    }
    channelInfoList.Close();
    delete sensrChannel;
	__UHEAP_MARKEND;        
    return leavecode; 
    }


TInt CSensrServiceTest::TestListenData( CStifItemParser& aItem )
	{
	__UHEAP_MARK;
	CActiveScheduler* sched = NULL;
	TInt channelid;
    aItem.GetNextInt(channelid);
    
    CSensorService* sensrChannel = CSensorService::NewL();
    RSensrvChannelInfoList channelInfoList;
    int error;
    TRAP(error,(sensrChannel->FindSensorChannelsL(channelid,channelInfoList)));
    
    if(error == KErrNotFound)
    	{
    	iLog->Log(_L("Channel not found - %d"),channelid);
    	delete sensrChannel;
    	return KErrNotFound;
  		}
  	else if ( error != KErrNone )
	  	{
		iLog->Log(_L("FindSensorChannel failed for %d channel"),channelid);
		delete sensrChannel;
		return error;
	  	}
	  	
    TInt count = channelInfoList.Count();

    CSensrDataCallBack* callbackobj = CSensrDataCallBack::NewL(sensrChannel,channelid);
    if ( !error )
	    {
		TRAP(error,(sensrChannel->GetDataNotificationL(channelInfoList[0],callbackobj)));
    	sched = CActiveScheduler::Current();
    	sched->Start();
    	}
    
    delete callbackobj;
    channelInfoList.Close();
    delete sensrChannel;
	__UHEAP_MARKEND;        
	return error;	

	}

TInt CSensrServiceTest::TestGetProperty( CStifItemParser& aItem )
{
	__UHEAP_MARK;
    CSensorService* sensrChannel = CSensorService::NewL();
    RSensrvChannelInfoList channelInfoList;
    RSensrvPropertyList channelPropertyList;
    TInt channel;
    aItem.GetNextInt(channel);
    TRAPD(error,(sensrChannel->FindSensorChannelsL(channel,channelInfoList)));

    //TInt error = sensrChannel->FindSensorChannelsL(channel,channelInfoList);
    
    if(error == KErrNotFound)
    {
    	iLog->Log(KLogChannelNotFound,channel);
    	return KErrNone;
    }
    	
    else if(error)
    {
    	iLog->Log(KLogFindChannelFail,channel,error);
    	return error;
    }
    	

    TInt count = channelInfoList.Count();

    for(TInt i=0;i < count;i++)
    {
		TRAPD(error,(sensrChannel->GetChannelPropertyL(channelInfoList[i]
		   										 ,channelPropertyList)));
		
		if(error)
		{
			channelPropertyList.Close();
    		channelInfoList.Close();
		    delete sensrChannel;
    		return error;
		}
		
		TSensrvProperty property;
		TUint propertyId;
    	TInt propValue,minValue,maxValue,propType ;
    	TReal rpropValue,rminValue,rmaxValue;
    	TBuf8<50> bpropValue;
		TInt32 itemIndex;
    	TBool readOnly;
		
		TInt propCount = channelPropertyList.Count();
		
		iLog->Log(_L("Channel id = %d"),channelInfoList[i].iChannelId);
		iLog->Log(_L("Property count= %d"),propCount);
		iLog->Log(_L("PropId     PropType     Val     Min     Max     Ind     RD"));
		
		for (TInt j=0;j < propCount; j++)
	    {
	    	property = channelPropertyList[j];
	    	propertyId = property.GetPropertyId();
	    	propType = property.PropertyType();
	    	
	    	itemIndex = property.PropertyItemIndex();
            readOnly = property.ReadOnly();
	    		    	
	    	if(propType == ESensrvIntProperty)
		    {
		    	property.GetValue(propValue);
		    	property.GetMinValue(minValue);
	    		property.GetMaxValue(maxValue);	
	    		iLog->Log(_L("%d     %d     %d     %d     %d     %d     %d"),
	    					propertyId,propType,propValue,minValue,maxValue,itemIndex,readOnly);
		    }
			else if (propType == ESensrvRealProperty)
			{
				property.GetValue(rpropValue);
	    		property.GetMinValue(rminValue);
	    		property.GetMaxValue(rmaxValue);
	    		iLog->Log(_L("%d     %d     %d     %d     %d     %d     %d"),
	    					propertyId,propType,rpropValue,rminValue,rmaxValue,itemIndex,readOnly);
				
			}
			else if (propType == ESensrvBufferProperty)
			{
				property.GetValue(bpropValue);
				iLog->Log(_L("%d     %d     buf     %d     %d"),propertyId,propType,itemIndex,readOnly);
			}	
	    }
    }

    channelPropertyList.Close();
    channelInfoList.Close();
    delete sensrChannel;
	__UHEAP_MARKEND;        
    return error; 

}
