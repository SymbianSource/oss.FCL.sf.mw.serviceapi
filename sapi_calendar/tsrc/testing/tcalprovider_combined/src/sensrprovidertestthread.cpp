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
* Description:   Contaions implementaion for sensor test thread
*  V	ersion     : %version: 3 % << Don't touch! Updated by Synergy at check-out.
*
*/




#include "sensrprovidertest.h"
#include "sensorinterface_const.hrh"
#include "serviceerrno.h"

//*************************Propertychange*****************************************
	
TInt ExecutePropertyChange(TInt aChannel)
{

	CActiveScheduler *sched = new CActiveScheduler;
    CActiveScheduler::Install(sched) ;
    
	CSensorChannelService* sensrChannel = CSensorChannelService::NewL();
    RSensrvChannelInfoList channelInfoList;
    RSensrvPropertyList channelPropertyList;
	TSensrvProperty property;
    TInt error;
    TRAP(error,(sensrChannel->FindSensorChannelsL(aChannel,channelInfoList)));
    
    if( error == KErrNotFound )
    {
    	/*FILE* fp = fopen("c:\\logs\\testframework\\SensorCallbackData.txt","a+");
	 	fprintf(fp,"%s","channel not found %d \n",aChannel);	
		fclose(fp);
    	delete sensrChannel;
    	return KErrNotFound;*/
    	//log data
	    RFile LogResult;
	    RFs LogResultSession;
	    User::LeaveIfError(LogResultSession.Connect());
	    if(LogResult.Open(LogResultSession ,_L("c:\\sensrerrorlog.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
	        {
	        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\sensrerrorlog.txt") , EFileWrite | EFileShareAny ) ;
	        }
	    TInt End = 0 ;
	    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
	    LogResult.Write(_L8("\nChannel Not Found\n"));
	    
	    LogResult.Close();
    	LogResultSession.Close();
	    delete sensrChannel;
	    return KErrNone;
  	}
  	
  	else if ( error != KErrNone )
  	{
  	/*FILE* fp = fopen("c:\\logs\\testframework\\SensorCallbackData.txt","a+");
 	fprintf(fp,"%s","Find channel failed for %d channel with %d error\n",aChannel,error);	
	fclose(fp);
	delete sched;
    
    channelInfoList.Close();
	delete sensrChannel;
	return error;*/
	
	RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\sensrerrorlog.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\sensrerrorlog.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    
    TBuf8<50> data;
	TRealFormat format;
	data.Num(aChannel,format);
	LogResult.Write(_L8("\nFind Channel Failed for "));
	LogResult.Write(data);
	LogResult.Write(_L8(" With Error code "));
	data.Num(error,format);
	LogResult.Write(_L8("\n"));
    channelInfoList.Close();
    LogResult.Close();
	LogResultSession.Close();
    delete sensrChannel;
    return error;

  	}
    TInt count = channelInfoList.Count();
    TUint channelid = channelInfoList[0].iChannelId;
    
	sensrChannel->GetChannelPropertyL(channelInfoList[0], 
									 channelPropertyList);
	
	property = channelPropertyList[0];
	TRAP(error,(sensrChannel->SetChannelPropertyL(channelInfoList[0],
											 property)));

	if(error)
    {
    	
    	/*FILE* fp = fopen("c:\\logs\\testframework\\SensorCallbackData.txt","a+");
	 	fprintf(fp,"%s","SetChannelProperty failed for %d channel with %d error\n",aChannel,error);	
		fclose(fp);*/
		RFile LogResult;
	    RFs LogResultSession;
	    User::LeaveIfError(LogResultSession.Connect());
	    if(LogResult.Open(LogResultSession ,_L("c:\\sensrerrorlog.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
	        {
	        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\sensrerrorlog.txt") , EFileWrite | EFileShareAny ) ;
	        }
	    TInt End = 0 ;
	    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
	    
	    TBuf8<50> data;
		TRealFormat format;
		data.Num(aChannel,format);
		LogResult.Write(_L8("\nSetChannelproperty Failed for channel "));
		LogResult.Write(data);
		LogResult.Write(_L8(" With Error code "));
		data.Num(error,format);
		LogResult.Write(_L8("\n"));
	    channelInfoList.Close();
	    LogResult.Close();
		LogResultSession.Close();
  	} 
	delete sched; 
    channelInfoList.Close();
    delete sensrChannel;
	return error;	
}

TInt DoPropertyChange(TAny* aPtr)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
  	TRAPD(err, err=ExecutePropertyChange((TInt)aPtr)) ;
    delete cleanup;
	return err;
}

