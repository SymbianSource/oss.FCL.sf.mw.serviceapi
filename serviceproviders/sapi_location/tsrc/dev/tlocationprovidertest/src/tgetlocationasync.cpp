/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <lbsrequestor.h>
#include <liwservicehandler.h>
#include <liwcommon.h>
#include "tcomplugin.h"

using namespace LIW;

_LIT(LogFileName , "C:\\Notifications.txt") ;

class ASyncLocCB : public MLiwNotifyCallback
{
	
	public :
	TInt iRetStatus ;
		
		TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList) ;

		ASyncLocCB() : iRetStatus(KErrGeneral)  //Default constructor 
			{
				;
			}
	
};



TInt ASyncLocCB :: HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList)

{
    __UHEAP_MARK ;
	TBuf8<50> data ;
   TRealFormat format ;


	RFile LogFile ;
	RFs LogSession ;
	TBuf8<50> Buffer(_L8("Latitude = ")) ;



	LogSession.Connect() ;

	if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
	{
		LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

	}


	TInt End = 0 ;
	TInt index = 0 ;
	const TLiwGenericParam *GenericParam =  aEventParamList.FindFirst(index , KErrorCode) ;

	if(!GenericParam)
	{
		return KErrGeneral ;
	}

	if((GenericParam->Value()).AsTInt32() != KErrNone)
	{
		return (GenericParam->Value()).AsTInt32() ;
	}
		
	index = 0 ;

	LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 
		const TLiwGenericParam *MapParam = aEventParamList.FindFirst(index ,KLocationMap) ;
		
		if(!MapParam)
		{
			return KErrGeneral ;
		}

		TLiwVariant Variant ;

		Variant = MapParam->Value() ;
		const CLiwMap *LocMap = Variant.AsMap() ;

		TLiwVariant PosVariant ;

		LocMap->FindL(KLongitudeKey , PosVariant) ;


	TReal64 LongData = (TReal64)PosVariant.AsTReal() ; //Longitude
		data.Num(LongData , format) ;
		LogFile.Write(_L8("\n")) ;
		LogFile.Write(_L8("Logitude = ")) ;
		LogFile.Write(data) ;

		LocMap->FindL(KLatitudeKey ,PosVariant) ; //Latitude 

	TReal64 LatData = (TReal64)PosVariant.AsTReal() ;
		data.Num(LatData , format) ;
		LogFile.Write(_L8("   Latitude = ")) ;
		LogFile.Write(data) ;

		LocMap->FindL(KAltitudeKey , PosVariant) ; //Altitude
	TReal32 AltData = PosVariant.AsTReal() ;
		data.Num(AltData , format) ;

		LogFile.Write(_L8("   Altitude = "))	 ;
		LogFile.Write(data) ;
	//	LocMap->DecRef() ;
    TLiwVariant Accuracy;
    index = LocMap->FindL(_L8("HorizontalAccuracy"),Accuracy);

    if(index)
        {
        TReal32 AccuracyVal = Accuracy.AsTReal();
        data.Num(AccuracyVal , format) ;

        LogFile.Write(_L8("Horizontal Acc = ")) ;
        LogFile.Write(data) ;
        }

    Accuracy.Reset();
    index = LocMap->FindL(_L8("VerticalAccuracy"),Accuracy);

    if(index)
        {
        TReal32 AccuracyVal = Accuracy.AsTReal();
        data.Num(AccuracyVal , format) ;

        LogFile.Write(_L8("Vertical Acc = ")) ;
        LogFile.Write(data) ;
        }
 const TLiwGenericParam *Speed = aEventParamList.FindFirst(index , _L8("HorizontalSpeed")) ;
	  
	  if(index != -1)
	  {
		Variant = Speed->Value() ;
		TReal speed =  Variant.AsTReal() ;

		data.Num(speed , format) ;

		LogFile.Write(_L8("Speed = ")) ;
		LogFile.Write(data) ;

	  }
	  
	  const TLiwGenericParam *SpeedError = aEventParamList.FindFirst(index , _L8("HorizontalSpeedError")) ;
	  
	 
	  if(index != -1)
	  {
		Variant = SpeedError->Value() ;
		TReal speed =  Variant.AsTReal() ;

		data.Num(speed , format) ;

		LogFile.Write(_L8("Speed = ")) ;
		LogFile.Write(data) ;

	  }
	  
	  index = 0 ;
	  
	  const TLiwGenericParam *SatInfo = aEventParamList.FindFirst(index , _L8("SatelliteNumView")) ;
	  
	  if(index != -1 )
	  {
	  	Variant = SatInfo->Value() ;
	  	
	  	TInt satnumView = Variant.AsTInt32() ;
	  	data.Num(satnumView , format);
	  	
	  	LogFile.Write(_L8("Satellite information")) ;
	  	
	  	LogFile.Write(_L8("Number of visible satellites ")) ;
	  	LogFile.Write(data) ;
	  }
	  
	  index = 0 ;
	  
	  const TLiwGenericParam *SatInfoview = aEventParamList.FindFirst(index , _L8("SatelliteNumViewUsed")) ;
	  
	  if(index != -1 )
	  {
	  	Variant = SatInfoview->Value() ;
	  	
	  	TInt satnumViewUsed = Variant.AsTInt32() ;
	  	data.Num(satnumViewUsed , format);
	  	
	  	LogFile.Write(_L8("\nSatellite information")) ;
	  	
	  	LogFile.Write(_L8("\nSatelliteNumViewUsed")) ;
	  	LogFile.Write(data) ;
	  }
	  
	  index = 0 ;
	  
	  const TLiwGenericParam *Heading = aEventParamList.FindFirst(index ,_L8("Heading") ) ;
	  
	  if(-1 != index)
	  {
	  	Variant = Heading->Value() ;
	  	
	  	TReal heading = Variant.AsTReal() ;
	  	data.Num(heading , format);
	  	
	  	LogFile.Write(_L8("\ncompass information")) ;
	  	
	  	LogFile.Write(_L8("\nHeading")) ;
	  	LogFile.Write(data) ;
	  }
	  
	  index = 0 ;
	  
	  if(Heading)
	  {
		  	const TLiwGenericParam *HeadingError = aEventParamList.FindFirst(index , _L8("HeadingError") ) ;
		  	
		  	if(-1 != index)
		  	{
			  	Variant = HeadingError->Value() ;
			  	
			  	TReal heading = Variant.AsTReal() ;
			  	data.Num(heading , format);
			  	
			  	LogFile.Write(_L8("\ncompass information")) ;
			  	
			  	LogFile.Write(_L8("\nHeading Error")) ;
			  	LogFile.Write(data) ;
		  		
		  	}
		  	index = 0 ;
		  	const TLiwGenericParam *MagneticHeading = aEventParamList.FindFirst(index , _L8("MagneticHeading") ) ;
		  	
		  	if(-1 != index)
		  	{
			  	Variant = MagneticHeading->Value() ;
			  	
			  	TReal heading = Variant.AsTReal() ;
			  	data.Num(heading , format);
			  	
			  	LogFile.Write(_L8("\ncompass information")) ;
			  	
			  	LogFile.Write(_L8("\n MagneticHeading ")) ;
			  	LogFile.Write(data) ;
			  		
		  	}
		  	
		  	index = 0 ;
		  	const TLiwGenericParam *MagneticHeadingError = aEventParamList.FindFirst(index , _L8("MagneticHeadingError") ) ;
		  	
		  	if(-1 != index)
		  	{
			  	Variant = MagneticHeadingError->Value() ;
			  	
			  	TReal heading = Variant.AsTReal() ;
			  	data.Num(heading , format);
			  	
			  	LogFile.Write(_L8("\ncompass information")) ;
			  	
			  	LogFile.Write(_L8("\nMagneticHeading Error")) ;
			  	LogFile.Write(data) ;
			  		
		  	}
	  

	  } //End of Heading
	  
	  index = 0 ;
	  
	  const TLiwGenericParam *TrueCourse = aEventParamList.FindFirst(index , _L8("TrueCourse") ) ;
	  
	  if(-1 != index)
	  {
	  	
		  	Variant = TrueCourse->Value() ;
		  	
		  	TReal heading = Variant.AsTReal() ;
		  	data.Num(heading , format);
		  	
		  	LogFile.Write(_L8("\nDirection ")) ;
		  	
		  	LogFile.Write(_L8("\n TrueCourse Error")) ;
		  	LogFile.Write(data) ;
		  	
		  	index = 0 ;    
		  	
		  	 const TLiwGenericParam *TrueCourseError = aEventParamList.FindFirst(index , _L8("TrueCourseError") ) ;
		  	 
		  	 if(-1 != index)
		  	 {
			  	Variant = TrueCourseError->Value() ;
			  	
			  	TReal heading = Variant.AsTReal() ;
			  	data.Num(heading , format);
			  	
			  	LogFile.Write(_L8("\ncompass information")) ;
			  	
			  	LogFile.Write(_L8("\nMagneticHeading Error")) ;
			  	LogFile.Write(data) ;
			  		
		  	 }
		  	 
		  	
	  }
	  
	  index = 0 ;
	  const TLiwGenericParam *MagneticCourse = aEventParamList.FindFirst(index , _L8("MagneticCourse") ) ;
	  
	
	   if(-1 != index)
	  	 {
		  	Variant = MagneticCourse->Value() ;
		  	
		  	TReal heading = Variant.AsTReal() ;
		  	data.Num(heading , format);
		  	
		  	LogFile.Write(_L8("\ncompass information")) ;
		  	
		  	LogFile.Write(_L8("\nMagneticCourse ")) ;
		  	LogFile.Write(data) ;
		  	
		  	index = 0 ;
		  	
		    const TLiwGenericParam *MagneticCourseError  = aEventParamList.FindFirst(index , _L8("MagneticCourseError") ) ;
		  
		  	 if(-1 != index)
		  	 {
			  	Variant = MagneticCourseError->Value() ;
			  	
			  	TReal heading = Variant.AsTReal() ;
			  	data.Num(heading , format);
			  	
			  	LogFile.Write(_L8("\ncompass information")) ;
			  	
			  	LogFile.Write(_L8("\n MagneticCourseError Error")) ;
			  	LogFile.Write(data) ;
			  		
		  	 }
	  	 
		  		
	  	 }
		  	 
		  	 
		/*index = 0 ;
		const TLiwGenericParam *NmeaNum = aEventParamList.FindFirst(index , _L8("NMEASentence") ) ;  	 
	  
	  
	  if(-1 != index)
	  	 {
		  	Variant = NmeaNum->Value() ;
		  	
		  	TInt32 NMEASentence = Variant.AsTInt32() ;
		  	data.Num(NMEASentence , format);
		  	
		  	LogFile.Write(_L8("\nNMEA Information")) ;
		  	
		  	LogFile.Write(_L8("\n number of NMEA Sentences ")) ;
		  	LogFile.Write(data) ;
		  	
		  	index = 0 ;
		  	
		    const TLiwGenericParam *MagneticCourseError  = aEventParamList.FindFirst(index , _L8("NMEASentenceStart") ) ;
		  
		  	 if(-1 != index)
		  	 {
			  	Variant = MagneticCourseError->Value() ;
			  	
			  //	TDes8 heading = Variant.AsDes() ;
			  	
			  //	LogFile.Write(_L8("\nNMEA information")) ;
			  	
			  //	LogFile.Write(_L8("\n NMEA Sentences")) ;
			  //	LogFile.Write(data) ;
			  		
		  	 }
	  	 }*/
	


	LogFile.Close() ;
	LogSession.Close() ;
	iRetStatus = KErrNone ;
	CActiveScheduler *Current = CActiveScheduler :: Current() ;
	Current->Stop() ;
    __UHEAP_MARKEND ;
	
	return KErrNone ;
}



TInt GetLocAsynchFunctionL()
{
	__UHEAP_MARK;
	TInt start = User::CountAllocCells();
	ASyncLocCB MyUpdates ;
	
	_LIT8(KService, "Service.Location");
    _LIT8(KIDataSource,"ILocation");

	
	
    CActiveScheduler *Scheduler  = CActiveScheduler :: Current() ;
    
    if(!Scheduler)
    {
    	Scheduler = new CActiveScheduler ;
    }
    
   
    CActiveScheduler :: Install(Scheduler) ;
     
    
	

	CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
  
    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
    
    


	//CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource, KService);
	

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);
	
	ServiceHandler->AttachL(a) ;
   
	
	
	
	
	
	
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);

	 
 	 

	TInt pos = 0;
	
	const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;
	
	if(!errorprm)
	{
		//_LIT(Klog , "Success/Failure error code missing from outputlist") ;
		//iLog->Log(Klog) ;
		return KErrGeneral ;
	}
	

	_LIT8(KDataSource, "ILocation");
	 
	 pos = 0 ;

 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KIDataSource );
	
	if(!genericparm)
	{
		//_LIT(KLog , "Interface not found");
		//iLog->Log(KLog) ;
		return KErrGeneral ;
	}
	
   MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
  // CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;
  
	
	TBuf8<20>CmdBuf(KCmdGetLocation) ;
	
	outputlist->Reset() ;
    inputlist->Reset() ;
	locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist ,KLiwOptASyncronous ,  &MyUpdates);
    
    CActiveScheduler :: Start() ;
    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist ,KLiwOptASyncronous ,  &MyUpdates);


    CActiveScheduler :: Start() ;
    delete Scheduler ;
    
    locinterface->Close();
    delete ServiceHandler;
    a.ResetAndDestroy();
    a.Close();
    //delete inputlist ;
    //delete  outputlist ;
    
    //delete ServiceHandler;
    TInt end = User::CountAllocCells();
    __UHEAP_MARKEND;
    return MyUpdates.iRetStatus ;  
}




TInt FindLocationAsynch(TAny * /*Arg*/)
{
//	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
  
    TInt ret = 0 ;
    TRAPD(err , (ret = GetLocAsynchFunctionL()) );
    delete cleanup ;
 //    __UHEAP_MARKEND;   

	 if(err)
	 {
	 	return err ;
	 }
	return ret ; 
}
TInt GetLocAsynchPosBased(TAny * /*Arg*/)
    {
    CTrapCleanup* cleanup = CTrapCleanup::New();

    TInt ret = 0 ;
    TRAPD(err , (ret = GetLocAsynchPosBasedL()) );
    delete cleanup ;
    //    __UHEAP_MARKEND;   

    if(err)
        {
        return err ;
        }
    return ret ; 
    }

TInt GetLocAsynchPosBasedL()
    {
    __UHEAP_MARK;


    TInt start = User::CountAllocCells();
    ASyncLocCB MyUpdates ;

    _LIT8(KService, "Service.Location");
    _LIT8(KIDataSource,"ILocation");



    CActiveScheduler *Scheduler  = CActiveScheduler :: Current() ;

    if(!Scheduler)
        {
        Scheduler = new CActiveScheduler ;
        }


    CActiveScheduler :: Install(Scheduler) ;

    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    //CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;


    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);    

    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        //_LIT(Klog , "Success/Failure error code missing from outputlist") ;
        //iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KIDataSource );

    if(!genericparm)
        {
        //_LIT(KLog , "Interface not found");
        //iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
    // CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;


    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT(KClass,"GenericLocationInfo");
    inputlist->AppendL( TLiwGenericParam( KNullDesC8,TLiwVariant( KClass )  ) );
    CLiwDefaultMap* updatemap = CLiwDefaultMap::NewL();

    _LIT8(KInterval,"UpdateInterval");
    _LIT8(KTimeout,"UpdateTimeOut");
    _LIT8(KAge,"UpdateMaxAge");
    _LIT8(KPartial,"PartialUpdates");
    const TInt KTime = 1000000;

    updatemap->InsertL(KInterval , TLiwVariant(TInt32(2*KTime)));
    updatemap->InsertL(KTimeout , TLiwVariant(TInt32(30*KTime)));
    updatemap->InsertL(KAge , TLiwVariant(TInt32(0)));
    updatemap->InsertL(KPartial , TLiwVariant(TBool(FALSE)));

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(updatemap)));
    updatemap->DecRef();


    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist ,KLiwOptASyncronous ,  &MyUpdates);

    CActiveScheduler :: Start() ;
    delete Scheduler ;

    locinterface->Close();
    delete ServiceHandler;
    a.ResetAndDestroy();
    a.Close();
    //delete inputlist ;
    //delete  outputlist ;

    //delete ServiceHandler;
    TInt end = User::CountAllocCells();

    __UHEAP_MARKEND;
    return MyUpdates.iRetStatus ;  
    }



TInt GetLocAsynchWrongVal(TAny * /*Arg*/)
    {
    CTrapCleanup* cleanup = CTrapCleanup::New();

    TInt ret = 0 ;
    TRAPD(err , (ret = GetLocAsynchWrongValL()) );
    delete cleanup ;
    //    __UHEAP_MARKEND;   

    if(err)
        {
        return err ;
        }

    return ret = 0 ; 
    }

TInt GetLocAsynchWrongValL()
    {

    __UHEAP_MARK;
    //TInt start = User::CountAllocCells();

    ASyncLocCB MyUpdates ;
    TInt errRet = 0;
    _LIT8(KService, "Service.Location");
    _LIT8(KIDataSource,"ILocation");


    CActiveScheduler *Scheduler  = CActiveScheduler :: Current() ;

    if(!Scheduler)
        {
        Scheduler = new CActiveScheduler ;
        }


    CActiveScheduler :: Install(Scheduler) ;




    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();

    // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());




    //CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KContents, KService);
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource, KService);


    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);

    ServiceHandler->AttachL(a) ;


    ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);    

    TInt pos = 0;

    const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;

    if(!errorprm)
        {
        //_LIT(Klog , "Success/Failure error code missing from outputlist") ;
        //iLog->Log(Klog) ;
        return KErrGeneral ;
        }


    _LIT8(KDataSource, "ILocation");

    pos = 0 ;

    const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KIDataSource );

    if(!genericparm)
        {
        //_LIT(KLog , "Interface not found");
        //iLog->Log(KLog) ;
        return KErrGeneral ;
        }

    MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
    // CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;


    TBuf8<20>CmdBuf(KCmdGetLocation) ;

    outputlist->Reset() ;
    inputlist->Reset() ;
    _LIT(KClass,"GenericLocationInfo");
    inputlist->AppendL( TLiwGenericParam( KNullDesC8,TLiwVariant( KClass )  ) );

    TInt updatemap = 12;

    inputlist->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(updatemap)));



    locinterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist ,KLiwOptASyncronous ,  &MyUpdates);


    pos = 0 ;

    const TLiwGenericParam *ErrorParm =  outputlist->FindFirst(pos ,KErrorCode ) ;

    if(!ErrorParm)
        {
        _LIT(Klog, "Success/Failure state not known") ;
        //iLog->Log(Klog) ;
        return KErrGeneral ;
        }

    if((ErrorParm->Value()).AsTInt32() != SErrBadArgumentType )
        {
        _LIT(KLog , "ExecutecmdL failed ");
        //iLog->Log(KLog) ;
        errRet =   KErrGeneral;
        }



    delete Scheduler ;

    locinterface->Close();
    delete ServiceHandler;
    a.ResetAndDestroy();
    a.Close();


    //delete inputlist ;
    //delete  outputlist ;

    //delete ServiceHandler;
    //TInt end = User::CountAllocCells();
    __UHEAP_MARKEND;
    return errRet;  
    }
