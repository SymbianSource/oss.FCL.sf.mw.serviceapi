/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <e32base.h>
#include <sensrvchannelinfo.h>
#include <sensrvchannel.h>
#include <sensrvchannelfinder.h>
#include <sensrvdatalistener.h>
#include <sensrvgeneralproperties.h>
#include <sensrvchanneldatatypes.h>
#include <sensrvtypes.h>
#include <sensrvdatalistener.h>
#include <e32cons.h>

// INCLUDE FILES
#include "tsensorservice_test.h"
#include "sensorservice.hrh"
#include "snrdatacallback.h"

_LIT(KLogAccDataFound,"Data Notification passed with %d channel having %d:%d:%d data \n");
_LIT(KLogDataFound,"Data Notification passed with %d channel having %d data \n");
_LIT(KLogChannelFound,"Find channel passed with %d channel having %d channels and error %d \n");
_LIT(KLogGetPropErr,"Getproperty %d channel having %d propertyid returns error %d and errn = %d \n ");
_LIT(KLogExpIntValue,"Expected value : %d \n" );
_LIT(KLogExpRealValue,"Expected value : %d \n ");
_LIT(KLogExpStringValue,"Expected value : %s \n ");
_LIT(KLogGotIntValue,"Resultant value : %d \n ");
_LIT(KLogGotRealValue,"Resultant value : %d \n ");
_LIT(KLogGotStringValue,"Resultant value : %s \n ");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctsensorservice_test::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsensorservice_test::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsensorservice_test::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsensorservice_test::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "FindChannels",Ctsensorservice_test::FindSensrChannel ),
	    ENTRY( "GetSensrData",Ctsensorservice_test::GetSensrData ),
	    ENTRY( "GetProperty",Ctsensorservice_test::GetProperty ),
        ENTRY( "StopChannel",Ctsensorservice_test::StopChannel ),
        ENTRY( "IsChnlOpen",Ctsensorservice_test::IsChnlOpen ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctsensorservice_test::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt flagr = 0;
RSensrvChannelConditionList iConditionList;

TInt getchanneltype( TInt  valu)
{
  TInt vret = 0;
  
  switch( valu )
   {
     case 1  : vret = TSearchCriterion( KSensrvChannelTypeIdUndefined );
                      break; 
                
     case 2  : vret = TSearchCriterion( KSensrvChannelTypeIdAccelerometerXYZAxisData );
                      break; 
                        
     case 3  : vret = TSearchCriterion( KSensrvChannelTypeIdAccelerometerWakeupData );
                      break; 
     
     case 4  : vret = TSearchCriterion( KSensrvChannelTypeIdAccelerometerDoubleTappingData );
                      break;                  
               
     case 5  : vret = TSearchCriterion( KSensrvChannelTypeIdOrientationData );
                      break;   
                      
     case 6  : vret = TSearchCriterion( KSensrvChannelTypeIdRotationData );
                      break;
     
     default : vret = valu ;                                    
   } 
   
  return vret;                        
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

TInt Ctsensorservice_test::FindSensrChannel( CStifItemParser& aItem )
    {

//    __UHEAP_MARK;
    
    RSensrvChannelInfoList channelInfoList, acceptedChannels;
    TInt i = 0,val = 0,x = 0,ch_val,svalue;
    TBool testFail( EFalse ); 
    
    TInt errv = aItem.GetNextInt( svalue ); 
    ch_val = getchanneltype( svalue );   
    
    CSensorService* sensrChannel = CSensorService::NewL();    
    TRAPD(error, sensrChannel->FindSensorChannelsL( ch_val ,channelInfoList));

    TInt count = channelInfoList.Count();     
	iLog->Log(KLogChannelFound,svalue,count,error);
    
    TSensrvChannelInfo channelInfo;
    channelInfo.iChannelType = ch_val;   
    
    for( i=0 ; i<count ; i++)
    {
      TUint32 type = channelInfoList[i].iChannelType;
      TUint32 data_type = channelInfoList[i].iChannelDataTypeId;
      
      if( channelInfoList[i].IsMatch( channelInfo ) )
            {
            acceptedChannels.Append( channelInfoList[i] );
            }           
    } 
      
    if( acceptedChannels.Count() == channelInfoList.Count() )
        {
           val = 1;
        }
        
    for( i = 0; i < channelInfoList.Count(); i++ )
      {
	    TBool found( EFalse );
	    for( x = 0; x < acceptedChannels.Count(); x++ )
	        {
	            if( acceptedChannels[x].iChannelId == channelInfoList[i].iChannelId )
	                {
	                found = ETrue;
	                break;
	                }
	        }
	        
	    if( !found )
         {
           testFail = ETrue;
         } 
	  }                   
       
    
    channelInfoList.Close(); 
    acceptedChannels.Close(); 
    delete sensrChannel;

//    __UHEAP_MARKEND;
    
    if((val == 1) && (!testFail)&&(error==0))
      return KErrNone; 
    else
      return KErrGeneral;    
           
    }
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

TInt Ctsensorservice_test::GetSensrData( CStifItemParser& aItem )
	{
	
	TInt val = 0, ch_val, svalue, listen_type ,find ,px ,py ,pz ,ori,err,errr;
	RSensrvChannelInfoList channelInfoList;
	TUint channelid = 0, di;
	CSnrDataCallBack* callbackobj = NULL;
  	
//  	__UHEAP_MARK;
  	
	TInt errv = aItem.GetNextInt( svalue );	
	ch_val = getchanneltype( svalue );
	
	CSensorService* sensrChannel = CSensorService::NewL();     
    TRAPD(error, sensrChannel->FindSensorChannelsL(ch_val,channelInfoList));
    
    if( error != KErrNone )
    	{
    	return -1;
    	}
    
    TInt count = channelInfoList.Count();
    
    TInt errv1 = aItem.GetNextInt( val );     
    TInt errv2 = aItem.GetNextInt( listen_type ); 
    
    TInt ret_code = 0;
	aItem.GetNextInt( ret_code );
   
    if((val!=9)&&(count!=0))
    {    
    	channelid = channelInfoList[val].iChannelId;    
    	callbackobj = CSnrDataCallBack::NewL(sensrChannel,channelid);
    	
    	TRAPD(errorv, sensrChannel->GetDataNotificationL(channelInfoList[val],callbackobj));
    	if(errorv == 0)
    	{
    	 CActiveScheduler :: Start() ;
        }
        else
        {
         return errorv; 
        }  
    }        
    
	TInt errv3 = aItem.GetNextInt( find ); 
	if(find == 1)
	{
	 TRAPD(error1, sensrChannel->FindSensorChannelsL(ch_val,channelInfoList));
	 TInt ct = channelInfoList.Count();
	 iLog->Log(KLogChannelFound,svalue,ct,error1);
	}	
	
	if((svalue == 2) && (val!=9))
	{
	 px = callbackobj->callback_x;
	 py = callbackobj->callback_y;
	 pz = callbackobj->callback_z;  
	 iLog->Log(KLogAccDataFound,svalue,px,py,pz);
	} 
	
	if(svalue == 3)
	{
	 di = callbackobj->callback_wake;
	 iLog->Log(KLogDataFound,svalue,di);
	} 
	
	if(svalue == 4)
	{
	 di = callbackobj->callback_dir;
	 iLog->Log(KLogDataFound,svalue,di);
	} 
	
	if(svalue == 5)
	{
	 ori = callbackobj->callback_or;
	 iLog->Log(KLogDataFound,svalue,ori);
	}
	
	if(svalue == 6)
	{
	 px = callbackobj->callback_rx;
	 py = callbackobj->callback_ry;
	 pz = callbackobj->callback_rz;
	 iLog->Log(KLogAccDataFound,svalue,px,py,pz);
	}
	
	if((svalue == 9)||(count!=0))
	{
	 if(svalue == 9)
	  channelid = 99;
	  
	 if(val == 9)
	  channelid = channelInfoList[0].iChannelId;
	  
	 if(listen_type != 3)
	 {
	   TRAP(err ,sensrChannel->StopNotificationL(listen_type,channelid));
	 }
	 else
	 {
	   TRAP(errr ,sensrChannel->StopNotificationL(listen_type));
	 }
	 	
	 if((svalue != 9) && (val != 9))
	  delete callbackobj;
	}
	
	channelInfoList.Close();  
	delete sensrChannel;
	
//	__UHEAP_MARKEND;
		
	if((err == ret_code) || (errr == ret_code))
      return KErrNone;
    else
      return KErrGeneral;  
	
	}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

TInt Ctsensorservice_test::GetProperty( CStifItemParser& aItem )
	{
	 
//	__UHEAP_MARK;
	
	CSensorService* sensrChannel = CSensorService::NewL();
    RSensrvChannelInfoList channelInfoList;
    RSensrvPropertyList  propertyList;
    TSensrvProperty property;
    TInt svalue, ch_val, val, errn = KErrGeneral;
    TInt propertyID,index = 0 ;
    TBuf8<50> bpropValue;
    TSensrvProperty iPropDataRate,iPropMeasureRange,iPropSensorDescription,iPropChannelScale;
    TSensrvProperty iPropMisc;
    
    TInt errv = aItem.GetNextInt( svalue );	
	ch_val = getchanneltype( svalue );
    
    sensrChannel->FindSensorChannelsL(ch_val,channelInfoList);
    
    TInt errv1 = aItem.GetNextInt( val );           
	 
    aItem.GetNextInt( propertyID );
    aItem.GetNextInt( index );
     
    if( propertyID == KSensrvPropIdDataRate )
         {
          TInt value(0);
          aItem.GetNextInt( value );
          iPropDataRate.SetValue( value );
          iPropDataRate.SetItemIndex( index );
         }
    else if( propertyID == KSensrvPropIdMeasureRange )
         {
          TInt intValue(0);
          aItem.GetNextInt( intValue );
          TReal value( intValue );
          iPropMeasureRange.SetValue( value );
          iPropMeasureRange.SetItemIndex( index );
         }
    else if( propertyID == KSensrvSensorDescription )
         { 
          TBuf8<KSensrvPropertyTextBufferSize> value;
          TPtrC16 ptr;
          aItem.GetNextString( ptr );
          value.Copy( ptr );
          iPropSensorDescription.SetValue( value );
          iPropSensorDescription.SetItemIndex( index );
         } 
                 
    TRAPD( errno, sensrChannel->GetChannelPropertyL(channelInfoList[val], propertyList));
    
    if( !errno )
        {        
        if( propertyID == KSensrvPropIdDataRate )
            {
            TInt expectedValue;
            TInt value1;
            iPropDataRate.GetValue( expectedValue );
            iLog->Log(KLogExpIntValue,expectedValue);
            for(TInt i = 0; i<propertyList.Count() ; i++ )
              {
               property = propertyList[i];
               if( ESensrvIntProperty == property.PropertyType())
                {
                  property.GetValue( value1 );
                  iLog->Log(KLogGotIntValue,value1);
                  if( expectedValue != value1 || iPropDataRate.PropertyItemIndex() != property.PropertyItemIndex() )
                  {
                  errn = KErrGeneral;
                  }
                  else
                  {
                  errn = 0;
                  }
                }              
               if(errn == 0)
                 break; 
              }  
            }
        else if( propertyID == KSensrvPropIdMeasureRange )
            {
            TReal expectedValue;
            TReal value2;
            iPropMeasureRange.GetValue( expectedValue );
            iLog->Log(KLogExpRealValue,expectedValue);
            for(TInt i = 0; i<propertyList.Count() ; i++ )
              {
               property = propertyList[i];
               if( ESensrvRealProperty == property.PropertyType())
                {
                  property.GetValue( value2 );
                  iLog->Log(KLogGotRealValue,value2);
                  if( expectedValue != value2 || iPropMeasureRange.PropertyItemIndex() != property.PropertyItemIndex() )
                  {
                  errn = KErrGeneral;
                  }
                  else
                  {
                  errn = 0;
                  }
                }
               if(errn == 0)
                 break;    
              }  
            }
        else if( propertyID == KSensrvSensorDescription )
            {
            TBuf8<KSensrvPropertyTextBufferSize> expectedValue;
            TBuf8<KSensrvPropertyTextBufferSize> value;
            iPropSensorDescription.GetValue( expectedValue );
            iLog->Log(KLogExpStringValue,expectedValue.PtrZ());
            for(TInt i = 0; i<propertyList.Count() ; i++ )
              {
               property = propertyList[i];
                if( ESensrvBufferProperty == property.PropertyType())
                {
                 property.GetValue( value );
                 iLog->Log(KLogGotStringValue,value.PtrZ());
                 if( expectedValue.Compare( value ) || iPropSensorDescription.PropertyItemIndex() != property.PropertyItemIndex() )
                 {
                 errn = KErrGeneral;
                 }
                 else
                 {
                 errn = 0;
                 }
                }
               if(errn == 0)
                 break;   
              }  
            }
        }
		  							
	iLog->Log(KLogGetPropErr,svalue,propertyID,errno,errn);
	
	channelInfoList.Close();   
	delete sensrChannel;
	
//	__UHEAP_MARKEND;
	
	if((errn == 0) && (errno == 0))
 		return KErrNone;
 	else
 	    return KErrGeneral;	
	
	
	}
	

TInt Ctsensorservice_test::StopChannel( CStifItemParser& aItem )
{
    
//    __UHEAP_MARK;
    
	TUint channelid = 44 ;
	TInt err = KErrGeneral, errr = KErrGeneral, ret_code = 0;
	
	CSensorService* sensrChannel = CSensorService::NewL(); 
     	
    TInt listen_type = 0;
    aItem.GetNextInt( listen_type ); 
    aItem.GetNextInt( ret_code ); 
    
    if(listen_type != 3)
	{
	  TRAP(err ,sensrChannel->StopNotificationL(listen_type,channelid));
	}
	else
	{
	  TRAP(errr ,sensrChannel->StopNotificationL(listen_type));
	}
    
    delete sensrChannel;
//    __UHEAP_MARKEND;
     
    if(err == ret_code || errr == ret_code)
      return KErrNone;
    else
      return KErrGeneral;  
    
}
    
    
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

TInt Ctsensorservice_test::IsChnlOpen( CStifItemParser& aItem )
{
    
//    __UHEAP_MARK;
    
	TInt val = 0, ch_val, svalue, flag = 0;
	RSensrvChannelInfoList channelInfoList;
	TUint channelid;
	CSnrDataCallBack* callbackobj;
	TInt errorc1 = -2, errorc2 = -2, errorc3 = -2, errorc4 = -2;
  	
	TInt errv = aItem.GetNextInt( svalue );	
	ch_val = getchanneltype( svalue );
	
	CSensorService* sensrChannel = CSensorService::NewL();     
    TRAPD(error, sensrChannel->FindSensorChannelsL(ch_val,channelInfoList));
    
    if( error != KErrNone )
    	{
    	return -1;
    	}
    
    TInt count = channelInfoList.Count();
    
    TInt errv1 = aItem.GetNextInt( val );     
    TInt errv2 = aItem.GetNextInt( flag ); 
   
    channelid = channelInfoList[val].iChannelId;    
   	callbackobj = CSnrDataCallBack::NewL(sensrChannel,channelid);
    	
   	TRAPD(errorv, sensrChannel->GetDataNotificationL(channelInfoList[val],callbackobj));
    
    if(errorv == 0)
    {
   	 CActiveScheduler :: Start() ;
    }
    else
    {
     return errorv; 
    }    
    
  if(flag == 2)
    {
        RSensrvPropertyList  propertyList;
        TRAP( errorc2, sensrChannel->GetChannelPropertyL(channelInfoList[val], propertyList));
    }
  else if(flag == 4)
    {
        TUint channelid1;
        CSnrDataCallBack* callbackobjct;
        channelid1 = channelInfoList[val].iChannelId;    
   	    callbackobjct = CSnrDataCallBack::NewL(sensrChannel,channelid1);
        TRAP(errorc4, sensrChannel->GetDataNotificationL(channelInfoList[val],callbackobjct));
        delete callbackobjct;
    }
    
    delete callbackobj;
    channelInfoList.Close();   
    delete sensrChannel;
    
    TInt ret_code = 0;
	aItem.GetNextInt( ret_code );
	
    //    __UHEAP_MARKEND;
     
    if(errorc1 == ret_code && flag == 1)
      return KErrNone;
    else if(errorc2 == ret_code && flag == 2)
      return KErrNone;
    else if(errorc3 == ret_code && flag == 3)
      return KErrNone;
    else if(errorc4 == ret_code && flag == 4)
      return KErrNone;    
    else
      return KErrGeneral;  
    
}
    
    
//  End of File
