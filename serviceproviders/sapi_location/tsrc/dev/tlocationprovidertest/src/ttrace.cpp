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
#include <Stiftestinterface.h>
#include <LbsRequestor.h>
#include <LiwServiceHandler.h>
#include <LiwCommon.h>

#include "tcomplugin.h"


_LIT(LogFileName , "C:\\Notifications.txt") ;

//---------------------------------------------------------------------------------------------------------
/** 
  *@ This call back interface is for testing Trace 
 */
 //---------------------------------------------------------------------------------------------------------
  
 class LocUpdateCallBack : public MLiwNotifyCallback
 {
   TInt iCount ;
   TInt iRetStatus ;
    public :
    	TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList);
    
    	LocUpdateCallBack() :iCount(0) , iRetStatus(KErrGeneral)  //Default constructor 
    	{
    		;
    	}
  };
  
  
  
TInt LocUpdateCallBack ::  HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList)
{

   TBuf8<50> data ;
   TRealFormat format ;

	iCount++ ;

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
		//LocMap->DecRef() ;
	 	

	LogFile.Close() ;
	LogSession.Close() ;
	
	if(iCount)
	{
		iRetStatus = KErrNone ;
		CActiveScheduler *Current = CActiveScheduler :: Current() ;
		Current->Stop() ;
		
	}
	
	return KErrNone ;
}
   
    	
TInt GetLocFunctionL()
{
 	__UHEAP_MARK;
	LocUpdateCallBack MyUpdates ;
	
	
	
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
    
    


	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDataSource , KService);
	

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);
	
	TRAPD (err ,ServiceHandler->AttachL(a) );
   
	
	
	
	
	
	
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);

	 
 	 

	TInt pos = 0;
	
	const TLiwGenericParam *errorprm = outputlist->FindFirst(pos , KErrorCode) ;
	
	if(!errorprm)
	{
		return KErrGeneral ;
	}
	

	_LIT8(KDataSource, "ILocation");
	 
	 pos = 0 ;

 	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos,KLocationInterface);
	
	if(!genericparm)
	{
		return KErrGeneral ;
	}
	
   MLiwInterface* locinterface = (genericparm->Value()).AsInterface();
  
  
   

  // CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;

    

	CLiwGenericParamList *InputList = CLiwGenericParamList :: NewL() ;
	CLiwGenericParamList *OutParmList = CLiwGenericParamList :: NewL() ;
	TBuf8<20>CmdBuf(KCmdTraceLocation) ;
	

	locinterface->ExecuteCmdL(CmdBuf , *InputList , *OutParmList ,KLiwOptASyncronous ,  &MyUpdates);
    
   CActiveScheduler :: Start() ;
    
   
    
    
    locinterface->Close();
     	
    delete InputList ;
    delete  OutParmList ;
    delete Scheduler ;
    delete crit;
    a.Reset();
    a.Close();
    delete ServiceHandler ;
    __UHEAP_MARKEND;
    return 0 ; 
}

TInt GetLocUpdates(TAny */*Arg*/)
{
//;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TInt val = 0 ;
   
  //Install a new active scheduler to this thread 
  TRAPD(err , (val =GetLocFunctionL())) ;
   
    delete cleanup ;
    if(err)
        {
            return err ;
        }
    return val ;
}

