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
* Description:  Implements callback methods which is called my core dll call
*									callback methods.
*
*/

#include <liwserviceifbase.h>
#include <LiwCommon.h>
#include "locationinterface.h"
#include "locationservice.h"
#include "locationcb.h"

using namespace LIW;

/**
 * Default constructor
 */
 
LocationInterfaceCB ::LocationInterfaceCB():iCallBack(NULL), 
iOutParmList(NULL),
iInParmList(NULL),
iTransactionId(0)
        {

        }

/**
 * OverLoaded constructor which accepts the callback adderss 
 * and registers it 
 */
 
LocationInterfaceCB :: LocationInterfaceCB( MLiwNotifyCallback* aCallBack ,
										const CLiwGenericParamList* aInParmList ,	
     				      				TPositionModuleInfo* aPositionModuleInfo ,
     				      				TInt32 aTransactionId ) : iCallBack(aCallBack), 
     				      										 iTransactionId(aTransactionId)
    {
    iModuleInfo = aPositionModuleInfo	;
    
    //Extract the location info category from inputparamlist
    TInt index = 0;
    const TLiwGenericParam *smapparam = aInParmList->FindFirst(index , KLocationInfoCategory) ;
    TPtrC argposInfoCategory(KLocationBasicinfo) ;
    
    if(index != KErrNotFound)
        {
         
        //posInfoCategory =  (smapparam->Value()).AsDes() ; 
        argposInfoCategory.Set( (smapparam->Value()).AsDes() );           
        }
    
    
    iLocinfoCategory = EBasicInfo;
    if ( argposInfoCategory == KLocationGenericInfo )
        {
            iLocinfoCategory = EGenericInfo;
        }
    }

/**
 * Default destructor 
 */
LocationInterfaceCB :: ~LocationInterfaceCB()
    {

    delete iOutParmList;

    }
/**
 * overloaded NewL function for creating local call back objects
 * as required by locationinterface.cpp 
 */
 
LocationInterfaceCB *LocationInterfaceCB :: NewL(MLiwNotifyCallback* aCallBack  ,
												const CLiwGenericParamList* aInParmList ,  
												TPositionModuleInfo* aPositionModuleInfo,
												TInt32 aTransactionid  ) 
    {
    LocationInterfaceCB *self = new(ELeave) LocationInterfaceCB(aCallBack , aInParmList ,
    															aPositionModuleInfo, aTransactionid) ;
    CleanupStack::PushL(self);

    //Store the outparam and in param list

    self->iOutParmList = CLiwGenericParamList::NewL();

    //Currently we dont use inputparam list, but when need it has to be 
    //initalised as done above for iOutParamList
    self->iInParmList = self->iOutParmList;

    CleanupStack::Pop(self);
     return self ;
    }

/**
 * implementation of HandleNotifyL function derived from LocationInterfaceCB
 */
 
 TInt LocationInterfaceCB :: HandleNotifyL(HPositionGenericInfo* aGenericInfo , TInt aError) 
    {

   	iOutParmList->Reset() ;
    TInt err = CLocationInterface :: ConvertToSapiError(aError) ;
    
    TLiwGenericParam errorParm(KErrorCode , TLiwVariant((TInt32)err)) ;
    iOutParmList->AppendL(errorParm) ;

    if(aError) //if Error then return the error code to user
        {

        iCallBack->HandleNotifyL(iTransactionId , KLiwEventError , *iOutParmList , *iInParmList) ;
        //delete this ;
        return KErrGeneral ;
        }
        
   
   	TRAPD(error , HandleL(aGenericInfo , aError))
    
    if(error != KErrNone)
    	{
    	 iCallBack->HandleNotifyL(iTransactionId , KLiwEventError , *iOutParmList , *iInParmList) ;
         //delete this ;
         return KErrGeneral ;
    	}
    
     	
  
   //For GetLocation notify user with EventCompleted Notification and for trace
   //Notify user with Event in progress notification
    if(iRequestType == KGetLocationCB)
        {
        iCallBack->HandleNotifyL(iTransactionId , KLiwEventCompleted , *iOutParmList , *iInParmList ) ;
        }
    else
        {
        iCallBack->HandleNotifyL(iTransactionId , KLiwEventInProgress , *iOutParmList , *iInParmList ) ; 
        }    

   

    return KErrNone ;
    }
 
 /**
  * LocationInterfaceCB :: HandleL(): An internal utility function that encapsulates 
  * all the leaving methods. This function is called by HandleNotifyL method
  */  
    
void LocationInterfaceCB :: HandleL(HPositionGenericInfo* aGenericInfo , TInt /*aError*/)  
	{
    CLiwDefaultMap *result = CLiwDefaultMap::NewL() ;
    CleanupStack :: PushL(result) ;
    //Now insert the collected position informaiton(latitude, longitude , and altitude into a default map 
    TPosition pos ;

    aGenericInfo->GetPosition(pos) ;

    TReal32 Val = pos.Longitude() ;

    result->InsertL(KLongitudeKey , TLiwVariant((TReal)Val)) ; //Inserting longitude 


    Val = pos.Latitude() ;
    result->InsertL(KLatitudeKey , TLiwVariant((TReal)Val)) ; //Inserting latitude into map    

    Val = pos.Altitude() ;
    if (!(Math::IsNaN(Val)))
        {
        result->InsertL(KAltitudeKey , TLiwVariant((TReal)Val))   ;  //Inserting altitude into map
        }
    //TLiwVariant resVar(result) ;
    TReal32 Val1;
    Val1 = pos.HorizontalAccuracy();
    if (!(Math::IsNaN(Val1)))
        {
        result->InsertL(KHorAccuracy, TLiwVariant((TReal)Val1)) ;
        }

    Val1 = pos.VerticalAccuracy();
    if (!(Math::IsNaN(Val1)))
        {
        result->InsertL(KVerAccuracy, TLiwVariant((TReal)Val1)) ;
        }
    
    TPositionModuleInfo :: TCapabilities  currCapability  = iModuleInfo->Capabilities() ;
    
    if ( iLocinfoCategory == EGenericInfo )
	    {
	    if(currCapability & TPositionModuleInfo :: ECapabilitySpeed) //Populate output param with speed info
        {
        TReal32 speedinfo = 0 ;

        if(!aGenericInfo->GetValue(EPositionFieldHorizontalSpeed , speedinfo) ) //Extract speed 
            {
            result->InsertL(KPositionFieldHorizontalSpeed,TLiwVariant((TReal)speedinfo));
            
            }

        if(!aGenericInfo->GetValue(EPositionFieldHorizontalSpeedError , speedinfo))
            {
            result->InsertL(KPositionFieldHorizontalSpeedError,TLiwVariant((TReal)speedinfo));	
            }



        }   //End of EcapabilitySpeed 


	    if(currCapability & TPositionModuleInfo :: ECapabilitySatellite) //Extract satellitinfo if any and append it
	        {																//as part of out parm list
	        TInt8 satinfo  = 0;

	        if(!aGenericInfo->GetValue(EPositionFieldSatelliteNumInView , satinfo))
	            {
	            result->InsertL(KPositionFieldSatelliteNumInView,TLiwVariant((TReal)satinfo));	
	            }
	        if(!aGenericInfo->GetValue(EPositionFieldSatelliteNumUsed , satinfo))
		        {
		        result->InsertL(KPositionFieldSatelliteNumUsed ,TLiwVariant((TReal) satinfo)) ;
		        }


	        }

	    if(currCapability & TPositionModuleInfo :: ECapabilityDirection) //Extract direction info if any and append it 
	        {                                                               // as part of out parm list
	        TReal direcinfo = 0;

	        if(!aGenericInfo->GetValue(EPositionFieldTrueCourse , direcinfo) )
	            {
	            result->InsertL(KPositionFieldTrueCourse,TLiwVariant((TReal)direcinfo));
	            //iOutParmList->AppendL(TLiwGenericParam(KPositionFieldTrueCourse , TLiwVariant((TInt32)direcinfo))) ;	
	            }


	        if(!aGenericInfo->GetValue(EPositionFieldTrueCourseError , direcinfo) )
	            {
	            result->InsertL(KPositionFieldTrueCourseError,TLiwVariant((TReal)direcinfo));
	            //iOutParmList->AppendL(TLiwGenericParam(KPositionFieldTrueCourseError , TLiwVariant((TInt32)direcinfo))) ;
	            }


	        if(!aGenericInfo->GetValue(EPositionFieldMagneticCourseError , direcinfo) )
	            {
	            result->InsertL(KPositionFieldTrueCourseError,TLiwVariant((TReal)direcinfo));
	            //iOutParmList->AppendL(TLiwGenericParam(KPositionFieldMagneticCourseError , TLiwVariant((TInt32)direcinfo))) ;
	            }

	        if(!aGenericInfo->GetValue(EPositionFieldMagneticCourse , direcinfo) )
	            {
	            result->InsertL(KPositionFieldMagneticCourse,TLiwVariant((TReal)direcinfo));
	            	
	            }

	        }


	    if(currCapability & TPositionModuleInfo :: ECapabilityCompass) //Extract compass info if any and append it 
	        {                                                               // as part of out parm list
	        TReal compassinfo ;

	        if(!aGenericInfo->GetValue(EPositionFieldHeading , compassinfo) )
	            {
	            result->InsertL(KPositionFieldHeading,TLiwVariant((TReal)compassinfo));
	            ;
	            }


	        if(!aGenericInfo->GetValue(EPositionFieldHeadingError , compassinfo) )
	            {
	            result->InsertL(KPositionFieldHeadingError,TLiwVariant((TReal)compassinfo));
	            
	            }

	        if(!aGenericInfo->GetValue(EPositionFieldMagneticHeading , compassinfo) )
	            {
	            result->InsertL(KPositionFieldMagneticHeading,TLiwVariant((TReal)compassinfo));
	            
	            }



	        if(!aGenericInfo->GetValue(EPositionFieldMagneticHeadingError , compassinfo) )
	            {
	            result->InsertL(KPositionFieldMagneticHeadingError,TLiwVariant((TReal)compassinfo));
	            	
	            }



	        }

	    /*if( currCapability & TPositionModuleInfo :: ECapabilityNmea ) //Extract Nmea info if any and append it 	
	        {                                                             //as part of out param list  
	        TUint8 numSentences ;

	        if(!aGenericInfo->GetValue(EPositionFieldNMEASentences , numSentences) )
	            {
	            result->InsertL(KPositionFieldNMEASentences,TLiwVariant((TReal)numSentences));
	            	
	            }


	        TBuf8 <20> nmeaSentences ;

	        if(!aGenericInfo->GetValue(EPositionFieldNMEASentencesStart , nmeaSentences) )
	            {
	            result->InsertL(KPositionFieldNMEASentencesStart,TLiwVariant(nmeaSentences));
	            	
	            }
	        }*/
	    
	    }
	TLiwGenericParam outParm(KLocationMap , TLiwVariant(result)) ;

    iOutParmList->AppendL(outParm) ;
    CleanupStack :: Pop(result) ;
    result->DecRef() ;


	}
    


