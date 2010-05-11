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
#include <StifTestInterface.h>
#include <f32file.h>
#include <hal.h>
#include <liwcommon.h>
#include <liwservicehandler.h>
#include <coemain.h> 

#include "tsysinfoprovidertests.h"
#include "entitykeys.h"
#include "sysinfoaiwparams.hrh"
#include "tuseractivitynotifier.h"
#include "serviceerrno.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;

_LIT(KROMInstallDir,"\\system\\install\\");
_LIT(KS60ProductIdFile,"Series60v*.sis");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysinfoprovidertests::Delete() 
    {
    if( iInterface )
	    {
		iInterface->Close();
	    }
	if(iServiceHandler)
    delete iServiceHandler ;
	
    }

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoprovidertests::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
		ENTRY( "VibraStatus",    Ctsysinfoprovidertests::VibraStatus),
	    ENTRY( "VibraSync",    Ctsysinfoprovidertests::VibraSync),
	    ENTRY( "VibraStatus1",    Ctsysinfoprovidertests::VibraStatus1),
       
        ENTRY( "SetVibraInvalidParamSysDataList",    Ctsysinfoprovidertests::SetVibraInvalidParamSysDataList),
        ENTRY( "SetVibraInvalidParamSysData",    Ctsysinfoprovidertests::SetVibraInvalidParamSysData),
        ENTRY( "SetVibraInvalidParamEntity",    Ctsysinfoprovidertests::SetVibraInvalidParamEntity),
        ENTRY( "SetVibraInvalidParamKey",    Ctsysinfoprovidertests::SetVibraInvalidParamKey),
      
        ENTRY( "VibraParamMissingEntity",    Ctsysinfoprovidertests::VibraParamMissingEntity),
        ENTRY( "VibraParamMissingKey",    Ctsysinfoprovidertests::VibraParamMissingKey),
        ENTRY( "VibraParamMissingSysData",    Ctsysinfoprovidertests::VibraParamMissingSysData),
        ENTRY( "VibraParamMissingEntityPos",    Ctsysinfoprovidertests::VibraParamMissingEntityPos),
        ENTRY( "VibraParamMissingKeyPos",    Ctsysinfoprovidertests::VibraParamMissingKeyPos),
        ENTRY( "VibraParamMissingSysDataPos",    Ctsysinfoprovidertests::VibraParamMissingSysDataPos),

        ENTRY( "WrongInterfaceName",    Ctsysinfoprovidertests::WrongInterfaceName),
        ENTRY( "LoadingInterfaceMultipletime",    Ctsysinfoprovidertests::LoadingInterfaceMultipletime),
       	ENTRY( "VibraInvalidCommand",    Ctsysinfoprovidertests::VibraInvalidCommand),
       
       ENTRY( "BtNotifyCancel",    Ctsysinfoprovidertests::BtNotifyCancel),
       ENTRY( "ActiveConnectionMissingCallback",    Ctsysinfoprovidertests::ActiveConnectionMissingCallback),
       ENTRY( "ActiveConnReqCancelMissingTransId",    Ctsysinfoprovidertests::ActiveConnReqCancelMissingTransId),

      	ENTRY( "SupportedLang",    Ctsysinfoprovidertests::SupportedLang),
     	
      	//input validation tests
      	ENTRY( "SetDisplayLang",    Ctsysinfoprovidertests::SetDisplayLang),
      	ENTRY( "SetInputLang",    Ctsysinfoprovidertests::SetInputLang),
      	ENTRY( "SetPredictiveText",    Ctsysinfoprovidertests::SetPredictiveText),
      	ENTRY( "SetVibra",    Ctsysinfoprovidertests::SetVibra),
      	ENTRY( "SetBluetoothStatus",    Ctsysinfoprovidertests::SetBluetoothStatus),
      	ENTRY( "SetInfraredStatus",    Ctsysinfoprovidertests::SetInfraredStatus),
      	ENTRY( "SetBrigthness",    Ctsysinfoprovidertests::SetBrigthness),
      	ENTRY( "SetScreenSaverTimeout",    Ctsysinfoprovidertests::SetScreenSaverTimeout),
      	ENTRY( "SetKeyGuardTimeout",    Ctsysinfoprovidertests::SetKeyGuardTimeout),
      	ENTRY( "SetAutoLockTimeout",    Ctsysinfoprovidertests::SetAutoLockTimeout),
      	ENTRY( "SetWallpaper",    Ctsysinfoprovidertests::SetWallpaper),
      	ENTRY( "SetLightTimeOut",    Ctsysinfoprovidertests::SetLightTimeOut),
      	ENTRY( "GetDriveInfoL",    Ctsysinfoprovidertests::GetDriveInfoL),
      	ENTRY( "UserInactivityNotify",    Ctsysinfoprovidertests::UserInactivityNotify),
  
      	ENTRY("GetCameraInfoTestNegative",  Ctsysinfoprovidertests::GetCameraInfoTestNegative), // During CJSE 2.0
      	ENTRY("GetCameraInfoTestWrongEntityName",  Ctsysinfoprovidertests::GetCameraInfoNegEntity),// During CJSE 2.0
      	ENTRY("GetCameraInfoTestWrongKeyName",  Ctsysinfoprovidertests::GetCameraInfoNegKey),// During CJSE 2.0
          };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

void Ctsysinfoprovidertests::Init()
{
	iServiceHandler = CLiwServiceHandler::NewL();
	iInparam = &(iServiceHandler->InParamListL());
	iOutparam = &(iServiceHandler->OutParamListL());
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *iInparam, *iOutparam); 

	delete crit;
	a.Reset();
	
	TInt pos = 0;
	
	iOutparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		//getting the iInterface handle
		iInterface = (*iOutparam)[pos].Value().AsInterface();	
		}

	iOutparam->Reset();
	iInparam->Reset();
}
	
	
//  End of File

 // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetVibraInvalidParams1
// Input SysData as List(instead of map)
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::SetVibraInvalidParamSysDataList(CStifItemParser& /*aItem*/)
	{
	
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0 ;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KKey,keyname);
	
	    //sysdata as map
	CLiwList* list = CLiwDefaultList::NewL();
	CleanupStack::PushL(list);

    TLiwVariant sysdata((TInt32)1);
    list->AppendL(sysdata); 
    sysdata.Reset();	


    TLiwVariant sysparam(list);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	list->DecRef();
	CleanupStack::Pop(list);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//get  supported language list
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == SErrNone)
	{
	const TLiwGenericParam* output = iOutparam->FindFirst( pos,KErrorCode );
	result = output->Value().AsTInt32(); 
	if(result == SErrBadArgumentType)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();
	
	__UHEAP_MARKEND;
	return result;

	}
	
 // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetVibraInvalidParams2
// Input SysData contains a string value instead of int
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::SetVibraInvalidParamSysData(CStifItemParser& /*aItem*/)
	{
	
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos =0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	
   	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KKey,keyname);
	
	    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata(KGeneral);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	


    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//get  supported language list
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == SErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrBadArgumentType)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();
	
//	iInterface->Close();
//	iInterface = NULL ;

	__UHEAP_MARKEND;
	return result;

	}

 // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetVibraInvalidParamEntity
// Entity as a int instead of string
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::SetVibraInvalidParamEntity(CStifItemParser& /*aItem*/)
	{
	
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(1);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KKey,keyname);
	
	    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)1);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	


    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//get  supported language list
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == SErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrNotFound)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();

	__UHEAP_MARKEND;
	return result;

	}

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetVibraInvalidParamKey
// Key as a int instead of string
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::SetVibraInvalidParamKey(CStifItemParser& /*aItem*/)
	{
	
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
    	
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(1);
	key.SetNameAndValueL(KKey,keyname);
	
	    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)1);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	


    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//get  supported language list
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == SErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result != SErrBadArgumentType)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();

	__UHEAP_MARKEND;
	return result;

	}
	


// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraParamMissingEntity
// without Entity Key(name based parsing).
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::VibraParamMissingEntity( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

//	TLiwGenericParam entity;
//	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
//	entityname.Set(KGeneral);
//	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)1);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

//	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
//	entity.Reset();
//	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrMissingArgument)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();
	
	__UHEAP_MARKEND;
	return result;

	}	
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraParamMissingKey
// without Key (name based parsing).
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::VibraParamMissingKey( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
//	TLiwGenericParam key;
//	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KEntity,entityname);

//	keyname.Set(KVibraActive);
//	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)1);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

//	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
//	key.Reset();
//	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrMissingArgument)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();

	__UHEAP_MARKEND;
	return result;

	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraParamMissingSysData
// without Input SysData for setInfo (name based parsing).
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::VibraParamMissingSysData( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
 	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
//	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
//	CleanupStack::PushL(map);

  //  TLiwVariant sysdata(1);
  //  map->InsertL(KStatus,sysdata); 
  //  sysdata.Reset();	

   // TLiwVariant sysparam(map);
//	TLiwGenericParam element ;	
//	element.SetNameAndValueL(KSysData,sysparam);
//	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
//	iInparam->AppendL(element);
	
//	element.Reset();

//	map->DecRef();
//	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
//	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrMissingArgument)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();

	__UHEAP_MARKEND;
	return result;

	}		
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraParamMissingEntityPos
// without Entity Key(Position based parsing).
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::VibraParamMissingEntityPos( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;

	Init();
	__UHEAP_MARK;

//	TLiwGenericParam entity;
//	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
//	entityname.Set(KGeneral);
//	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KNullDesC8,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)1);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KNullDesC8,sysparam);
	sysparam.Reset();

//	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
//	entity.Reset();
//	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrMissingArgument)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();
	
	__UHEAP_MARKEND;
	return result;

	}	
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraParamMissingKeyPos
// without Key (Position based parsing).
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::VibraParamMissingKeyPos( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   	
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
//	TLiwGenericParam key;
//	TLiwVariant  keyname;	
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KNullDesC8,entityname);

//	keyname.Set(KVibraActive);
//	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)1);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KNullDesC8,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

//	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
//	key.Reset();
//	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrMissingArgument)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();
	
	__UHEAP_MARKEND;
	return result;

	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraParamMissingSysDataPos
// without Input SysData for setInfo (Position based parsing).
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::VibraParamMissingSysDataPos( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
   	
	Init();
	
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KNullDesC8,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KNullDesC8,keyname);
	
    //sysdata as map
//	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
//	CleanupStack::PushL(map);

  //  TLiwVariant sysdata(1);
  //  map->InsertL(KStatus,sysdata); 
  //  sysdata.Reset();	

   // TLiwVariant sysparam(map);
//	TLiwGenericParam element ;	
//	element.SetNameAndValueL(KSysData,sysparam);
//	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
//	iInparam->AppendL(element);
	
//	element.Reset();

//	map->DecRef();
//	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
//	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrMissingArgument)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();
	
	__UHEAP_MARKEND;
	return result;

	}	

 // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::WrongInterfaceName
// Wrong Interface Name provided.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::WrongInterfaceName( CStifItemParser& /*aItem*/ )
{

	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
//	Init();
	__UHEAP_MARK;
	_LIT8(KIDataSource,"ISys");
	
	iServiceHandler = CLiwServiceHandler::NewL();
	iInparam = &(iServiceHandler->InParamListL());
	iOutparam = &(iServiceHandler->OutParamListL());
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	TRAPD( err,iServiceHandler->ExecuteServiceCmdL(*crit, *iInparam, *iOutparam) ); 

	delete crit;
	a.Reset();
	
	pos = 0;
	
	iOutparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		//getting the iInterface handle
		iInterface = (*iOutparam)[pos].Value().AsInterface();
		result = -1; 	
		}
    else
	    {
		result =  0;	
	    }
	
	iOutparam->Reset();
	iInparam->Reset();
    
    if( iInterface )
	    {
		iInterface->Close();
	    }
	iLog->Log(_L("before delete iServiceHandler :"));
    delete iServiceHandler ;
    iServiceHandler = NULL;
    iLog->Log(_L("after delete iServiceHandler :"));

	__UHEAP_MARKEND;
	return result;

	}
	
 // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::LoadingInterfaceMultipletime
// Loading Interface Multiple time.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::LoadingInterfaceMultipletime( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
//	Init();
	__UHEAP_MARK;
	
	iServiceHandler = CLiwServiceHandler::NewL();
	iInparam = &(iServiceHandler->InParamListL());
	iOutparam = &(iServiceHandler->OutParamListL());
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);
	TRAPD( err,iServiceHandler->ExecuteServiceCmdL(*crit, *iInparam, *iOutparam) ); 

	delete crit;
	a.Reset();
	pos = 0;
	
	iOutparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		//getting the iInterface handle
		iInterface = (*iOutparam)[pos].Value().AsInterface();
		
		iOutparam->Reset();
		iInparam->Reset();
	
	//	iInparam = &(iServiceHandler->InParamListL());
	//	iOutparam = &(iServiceHandler->OutParamListL());
		
		CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
		crit->SetServiceClass(TUid::Uid(KLiwClassBase));

		RCriteriaArray a;
		a.AppendL(crit);    

		iServiceHandler->AttachL(a);
		TRAPD( err,iServiceHandler->ExecuteServiceCmdL(*crit, *iInparam, *iOutparam) ); 

		delete crit;
		a.Reset();
	
		
	//	iServiceHandler->AttachL(a);
	//	TRAPD( err1,iServiceHandler->ExecuteServiceCmdL(*crit, *iInparam, *iOutparam) ); 
	
	//	iServiceHandler->AttachL(a);
	//	TRAP( err1,iServiceHandler->ExecuteServiceCmdL(*crit, *iInparam, *iOutparam) ); 
		pos = 0 ;
		iOutparam->FindFirst( pos, KIDataSource );
		if(pos != KErrNotFound)
			{
		    MLiwInterface* iInterface1 = (*iOutparam)[pos].Value().AsInterface();

			if(iInterface1 !=iInterface )
			{
			iLog->Log(_L(" iInterface1 !=iInterface :"));
				result = 0; 
				
			}
			else
			{
			result = -1;		iLog->Log(_L(" iInterface1 ==iInterface :"));	
			}
			
		   if( iInterface1 )
			    {
				iInterface1->Close();
			    }
			}
		else
			{
				result =-1; 
			}
		}
    else
	    {
		result =  -1;	
	    }
	
	iOutparam->Reset();
	iInparam->Reset();
	iLog->Log(_L("before iInterface->Close():"));

    if( iInterface )
	    {
		iInterface->Close();
		iInterface = NULL ;
	    }
	iLog->Log(_L("before delete iServiceHandler :"));
    delete iServiceHandler ;
    iServiceHandler = NULL ;
    iLog->Log(_L("after delete iServiceHandler :"));

	__UHEAP_MARKEND;
	return result;

	
}
	
 // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraSync
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::VibraSync( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)1);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam,KLiwOptASyncronous,NULL));
	result = err;
	if(err == KErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrBadArgumentType)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();

	__UHEAP_MARKEND;
	return result;

	}
		
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraStatus
// missing asynchronous bit in GetNotification
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::VibraStatus(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    ret = VibraNotification(iLog);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraStatus
// missing callback parameter
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::VibraStatus1(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    ret = VibraNotification1(iLog);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}
	
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraInvalidCommand
// Invalid Command name.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::VibraInvalidCommand( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "VibraInvalidCommand:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)1);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	_LIT8(KSetInfo,"SetInformation");
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	if(result == SErrServiceNotSupported)
		{
		result =  0;	
		}
    else
	    {
		result =  -1;	
	    }
	}
	iOutparam->Reset();
	iInparam->Reset();

	__UHEAP_MARKEND;
	return result;

	}


// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::BtNotifyCancel
// missing KLiwOptCancel bit
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::BtNotifyCancel(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    ret = BTAsyncReqCancel(iLog);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::ActiveConnectionMissingCallback
// missing callback parameter
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::ActiveConnectionMissingCallback(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    ret = ActiveConnection(iLog);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::ActiveConnReqCancelMissingTransId
// missing transaction id in the cancel Request.
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::ActiveConnReqCancelMissingTransId(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    ret = ActiveConnectionReqCancel(iLog);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}


// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SupportedLang
// 
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::SupportedLang(CStifItemParser& /*aItem*/)
	{

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    
	__UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
	CleanupStack::PushL(iServiceHandler);
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	TInt 	result = KErrNone; 
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	delete crit;
	a.Reset();
	
	TInt pos = 0;
	MLiwInterface* interface = NULL;
	outparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();
	
	if(interface)
		{
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KSupportedLanguages);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		
		//get supported languages list
		TRAPD(err,interface->ExecuteCmdL(KGetInfo,*inparam,*outparam));
		result = err;
		
		if(err == KErrNone)
			{
			pos = 0 ;
		    
		    const TLiwGenericParam* output = outparam->FindFirst( pos,KReturnValue );
		
				
			if(output)     
				{
				const CLiwMap* Map = output->Value().AsMap(); 
				if ( Map )
					{
					TLiwVariant data;

					if(EFalse!=Map->FindL(KLanguageList,data))
						{
						const CLiwList* langList=data.AsList();
						
						TInt32 testacctype= 0,testaccstatus= 0;
			      		if(langList)
							{
							for(TInt i=0; i != (langList->Count()+10); ++i)
								{
								TLiwVariant langVariant;
								if(langList->AtL(i,langVariant))
									{
									TInt32 langValue = langVariant.AsTInt32();
									TBuf<50> buf;
									buf.AppendNum(langValue);
									iLog->Log(buf);
									}
								//	TInt count1 = (langList->Count() + 10);
								//	langList->Remove(count1) ;
									
								}
							
							}			
						}
				
					data.Reset(); 
					}
				}
		
			}
		}
	inparam->Reset();
	outparam->Reset();
	
	interface->Close();
	
	CleanupStack::PopAndDestroy( iServiceHandler );
	
	__UHEAP_MARKEND;

	return result;
	}

	

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetDisplayLang
// 
// -----------------------------------------------------------------------------
//	
TInt Ctsysinfoprovidertests::SetDisplayLang(CStifItemParser& /*aItem*/)
    {
    CCoeEnv* coeSupported = NULL;
    coeSupported = CCoeEnv::Static();
    if (coeSupported)
        {

        TInt result =KErrNone;

        _LIT(KExample, "SetDisplayLang:");
        iLog->Log(KExample);

        TInt32 oldDisplayLang = 0, newDisplayLang = 0, changedDisplayLang = 0;

        __UHEAP_MARK;

        _LIT(KDisplayLanguage, "DisplayLanguage");

        CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
        CleanupStack::PushL(iServiceHandler);
        CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
        CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

        TInt err = KErrNone;

        CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,
                KService);
        crit->SetServiceClass(TUid::Uid(KLiwClassBase));

        RCriteriaArray a;
        a.AppendL(crit);

        iServiceHandler->AttachL(a);

        iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam);

        delete crit;
        a.Reset();

        TInt pos = 0;
        MLiwInterface* interface = NULL;
        outparam->FindFirst(pos, KIDataSource);
        if (pos != KErrNotFound)
            {
            //getting the interface handle
            interface = (*outparam)[pos].Value().AsInterface();
            }

        outparam->Reset();
        inparam->Reset();

        if (interface)
            {
            TLiwGenericParam entity;
            TLiwVariant entityname;
            TLiwGenericParam key;
            TLiwVariant keyname;

            entityname.Set(KGeneral);
            entity.SetNameAndValueL(KEntity, entityname);

            keyname.Set(KDisplayLanguage);
            key.SetNameAndValueL(KKey, keyname);

            inparam->AppendL(entity);

            inparam->AppendL(key);

            entity.Reset();
            entityname.Reset();
            key.Reset();
            keyname.Reset();

            //get current display language
            TRAPD(err, interface->ExecuteCmdL(KGetInfo, *inparam, *outparam));
            pos = 0;
            outparam->FindFirst(pos, KErrorCode);
            if (pos != KErrNotFound)
                {
                err = (TInt)((*outparam)[pos].Value().AsTInt32());
                }

            if (err != SErrNotFound)
                {
                iLog->Log(_L("Failed,Get Display language found ret err: %d"),err);
                result = KErrGeneral;
                }
            else
                {
                result = KErrNone;
                iLog->Log(_L("Passed Get Display language not found") );
                }

            outparam->Reset();
            CLiwDefaultMap* sysdatamap = CLiwDefaultMap::NewL();
            CleanupClosePushL(*sysdatamap);
            sysdatamap->InsertL(KStatus, (TInt32)10);
            inparam->AppendL(TLiwGenericParam(KSysData,
                    TLiwVariant(sysdatamap)));
            CleanupStack::PopAndDestroy(sysdatamap);

            TRAPD(err1, interface->ExecuteCmdL(KSetInfo, *inparam, *outparam));

            pos = 0;
            outparam->FindFirst(pos, KErrorCode);
            if (pos != KErrNotFound)
                {
                err = (TInt)((*outparam)[pos].Value().AsTInt32());
                }

            if (err != SErrNotFound)
                {
                iLog->Log(_L("Failed, Set Display language found ret err: %d"),err);
                result = KErrGeneral;
                }
            else
                {
                result = KErrNone;
                iLog->Log(_L("Passed, Set Display language not found") );
                }
            }

        inparam->Reset();
        outparam->Reset();

        interface->Close();

        CleanupStack::PopAndDestroy(iServiceHandler);
        __UHEAP_MARKEND;
        return result;
        }
    else
        {
        iLog->Log(_L("CCoeEnv not supported . Hence passing the test case") );
        return 0;
        }

    }

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetInputLang
// 
// -----------------------------------------------------------------------------
//	
TInt  Ctsysinfoprovidertests::SetInputLang(CStifItemParser& /*aItem*/)
	{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    
    TInt32 oldInputLang = 0 ,newInputLang = 0,changedInputLang =0;
	
	 __UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
	CleanupStack::PushL(iServiceHandler);
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	TInt 	err = KErrNone; 
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	delete crit;
	a.Reset();
	
	TInt pos = 0;
	MLiwInterface* interface = NULL;
	outparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		//get interface handle
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();
	
	if(interface)
		{
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KSupportedLanguages);
		key.SetNameAndValueL(KKey,keyname);

		//append entity and key as input parameters
		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		
		//get supported language list
		TRAPD(err1,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam));
		result = err1;
			if(err1 == KErrNone)
				{
				CLiwGenericParamList* outparam1 = CLiwGenericParamList::NewL();
				inparam->Reset();
				
				entityname.Set(KGeneral);
				entity.SetNameAndValueL(KEntity,entityname);

				keyname.Set(KInputLanguage);
				key.SetNameAndValueL(KKey,keyname);

				inparam->AppendL(entity);

				inparam->AppendL(key);
				
				entity.Reset();
				entityname.Reset();
				key.Reset();
				keyname.Reset();
				
				//get current input language
				TRAPD(err2,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam1));
				
				result = err2;
				if(err2 == KErrNone)
					{
					pos = 0 ;
					const TLiwGenericParam* output1 = outparam1->FindFirst( pos,KReturnValue );
					if(output1)     
						{
						const CLiwMap* Map = output1->Value().AsMap(); 
						if ( Map )
							{
							TLiwVariant data;
							if(EFalse!=Map->FindL(KStatus,data))
								{
								oldInputLang=data.AsTInt32();

								iLog->Log(_L("Oldinputlang"));	
								TBuf<50> buf;
								buf.AppendNum(oldInputLang);
								iLog->Log(buf);	
								}
							}//map
						}//output
					
					inparam->Reset();
					outparam1->Reset();
					
					//get new input lang from supported lang list
					pos = 0 ;
	    			const TLiwGenericParam* output = outparam->FindFirst( pos,KReturnValue );
					if(output)     
						{
						const CLiwMap* Map = output->Value().AsMap(); 
						if ( Map )
							{
							TLiwVariant data;

							if(EFalse!=Map->FindL(KLanguageList,data))
								{
								const CLiwList* langList=data.AsList();
								
								TInt32 testacctype= 0,testaccstatus= 0;
					      		if(langList)
									{
									for(TInt j= 0; j<1023; j++)
										{
										for(TInt i=0; i != langList->Count(); ++i)
											{
											TLiwVariant langVariant;
											langList->AtL(i,langVariant);
											newInputLang = langVariant.AsTInt32();
											
											if(newInputLang != j)
												{
												newInputLang = j;
												//	break;
												}

											}
										}
									}			
								}
						
							data.Reset(); 
							}//map
						}//output
						
				outparam->Reset();
				
				entityname.Set(KGeneral);
				entity.SetNameAndValueL(KEntity,entityname);

				keyname.Set(KInputLanguage);
				key.SetNameAndValueL(KKey,keyname);
				
			
				//sysdata as map
				CLiwDefaultMap* map = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map);

			    TLiwVariant sysdata(newInputLang);
			    map->InsertL(KStatus,sysdata); 
			    sysdata.Reset();	
		    

			    TLiwVariant sysparam(map);
				TLiwGenericParam element ;	
				element.SetNameAndValueL(KSysData,sysparam);
				sysparam.Reset();
				
				inparam->AppendL(entity);
				inparam->AppendL(key);

				inparam->AppendL(element);
				element.Reset();
				
			    map->DecRef();
			    CleanupStack::Pop(map);
				inparam->AppendL(entity);
				inparam->AppendL(key);

				entity.Reset();
				entityname.Reset();
				key.Reset();
				keyname.Reset();
				sysdata.Reset();
				
				//set new input language
				TRAPD(err3,	interface->ExecuteCmdL(KSetInfo,*inparam,*outparam1));
				inparam->Reset();
				outparam1->Reset();
				
				result = err3;
				if(err3 == KErrNone)
					{
					pos = 0 ;
					outparam1->FindFirst( pos, KErrorCode );
					if(pos != KErrNotFound)
						{
						result = (TInt)((*outparam1)[pos].Value().AsTInt32());
						}


					CLiwGenericParamList* outparam1 = CLiwGenericParamList::NewL();
					inparam->Reset();

					entityname.Set(KGeneral);
					entity.SetNameAndValueL(KEntity,entityname);

					keyname.Set(KInputLanguage);
					key.SetNameAndValueL(KKey,keyname);

					inparam->AppendL(entity);

					inparam->AppendL(key);

					entity.Reset();
					entityname.Reset();
					key.Reset();
					keyname.Reset();

					//get changed input language
					TRAPD(err4,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam1));

					result = err4;
					if(err4 == KErrNone)
					{
					pos = 0 ;
					outparam1->FindFirst( pos, KErrorCode );
					if(pos != KErrNotFound)
						{
						result = (TInt)((*outparam1)[pos].Value().AsTInt32());
						}

					pos = 0 ;
					const TLiwGenericParam* output1 = outparam1->FindFirst( pos,KReturnValue );
					if(output1)     
						{
						const CLiwMap* Map = output1->Value().AsMap(); 
						if ( Map )
							{
							TLiwVariant data;
							if(EFalse!=Map->FindL(KStatus,data))
								{
								changedInputLang=data.AsTInt32();

								iLog->Log(_L("changedInputLang"));	
								TBuf<50> buf;
								buf.AppendNum(changedInputLang);
								iLog->Log(buf);	
								}
							}//map
						}//output

					inparam->Reset();
					outparam1->Reset();

					if(newInputLang != changedInputLang)
						{
						result = KErrNone;
						}
					else
						{
						result =  KErrGeneral;
						}
					}//err4
					inparam->Reset();
					outparam1->Reset();
					}//err3
				}//err2
	
			}//err1
	
		}//interface
		
		if(newInputLang != changedInputLang)
			{
			result = KErrNone;
			}
		else
			{
			result =  KErrGeneral;
			}

	interface->Close();
	
	CleanupStack::PopAndDestroy( iServiceHandler );
	
	__UHEAP_MARKEND;
	return result;	
	



	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetPredictiveText
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetPredictiveText( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KPridictiveText);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)50);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
	
	if(result != SErrNone)
		{
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		result = 0;
	
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KPridictiveText);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)-5);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
	pos = 0;
		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		iOutparam->Reset();
		iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result != SErrNone)
			{
			
			result = 0;
			}

	    else
		    {
			result =  -1;	
		    }
			}
		
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}


 // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetVibra
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetVibra( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KGeneral);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KVibraActive);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)50);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result != SErrNone)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KVibraActive);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)-5);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
			pos = 0;

		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		iOutparam->Reset();
		iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result != SErrNone)
			{
			result =  0;
			}
	    else
	    {
		result =  -1;	
	    }
	}
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}
	
 // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetBluetoothStatus
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetBluetoothStatus( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KConnectivity);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KBlueTooth);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)50);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result != SErrNone)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KConnectivity);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KBlueTooth);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)-5);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
	pos = 0;
		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		iOutparam->Reset();
		iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result != SErrNone)
			{
			result =  0;
			}
	    else
	    {
		result =  -1;	
	    }
	}
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}
	
 // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetInfraredStatus
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetInfraredStatus( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KConnectivity);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KInfraRed);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)50);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result != SErrNone)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KConnectivity);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KInfraRed);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)-5);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
			pos = 0;

		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		iOutparam->Reset();
		iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result != SErrNone)
			{
			result =  0;
			}
	    else
	    {
		result =  -1;	
	    }
	}
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetInfraredStatus
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetBrigthness( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KDisplay);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KBrightness);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)0);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
		pos = 0;

	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result != SErrNone)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KDisplay);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KBrightness);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)125);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
	pos = 0;
		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		iOutparam->Reset();
		iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result != SErrNone)
			{
			result =  0;
			}
	    else
	    {
		result =  -1;	
	    }
	}
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetScreenSaverTimeout
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetScreenSaverTimeout( CStifItemParser& /*aItem*/ )
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KDisplay);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KScreenSaverTimeOut);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)-125);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result != SErrNone)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KDisplay);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KScreenSaverTimeOut);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)1225);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
	pos = 0;
		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		iOutparam->Reset();
		iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result != SErrNone)
			{
			result =  0;
			}
	    else
	    {
		result =  -1;	
	    }
	}
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetScreenSaverTimeout
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetKeyGuardTimeout( CStifItemParser& /*aItem*/)
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KDisplay);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KKeyGaurdTime);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)-100);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result != SErrNone)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KDisplay);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KKeyGaurdTime);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)5000);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
	pos = 0;
		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		iOutparam->Reset();
		iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result != SErrNone)
			{
			result =  0;
			}
	    else
	    {
		result =  -1;	
	    }
	}
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}


// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetScreenSaverTimeout
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetAutoLockTimeout( CStifItemParser& /*aItem*/)
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KDisplay);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KAutoLockTime);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)-100);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result != SErrNone)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KDisplay);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KAutoLockTime);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)5000);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
			pos = 0;

		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		iOutparam->Reset();
		iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result != SErrNone)
			{
			result =  0;
			}
	    else
	    {
		result =  -1;	
	    }
	}
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetScreenSaverTimeout
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetWallpaper( CStifItemParser& /*aItem*/)
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KDisplay);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KWallpaper);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	_LIT(KWallPaperPath,"Statuswereewwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwergregrvbrtbrbhbbyhbgrthgrtgrtttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttfcfsdvdfvfddddddddvdvhrtttttttteyeyeyeyfgvsdterrrrrrrrrrrrrrrrrrrrrrrrrrrrrrregeeeeeeeeeeeeeeeeeeeeeeergergrewghrthrtrtrtrtrtrtrtrtrtrtrtwhrrrrtttwrwthtrwwtttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttw");
    TLiwVariant sysdata(KWallPaperPath);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result != SErrNone)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KDisplay);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KWallpaper);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

		_LIT(KWallPaperPath2,"c:\\data\\Others\\sysinfo.txt");
	    TLiwVariant sysdata(KWallPaperPath2);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
			{
			iOutparam->FindFirst( pos, KErrorCode );
			if(pos != KErrNotFound)
				{
					result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
				}
			iOutparam->Reset();
			iInparam->Reset();
			
			if(result == SErrBadArgumentType)
				{
				result =  0;
				}
		    else
			    {
				result =  -1;	
			    }
			}
		}//result
	}//err
    else
	    {
		result =  -1;	
	    }

	__UHEAP_MARKEND;
	return result;

	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetScreenSaverTimeout
// with KLiwOptASyncronous bit set for a synchronous request.
// -----------------------------------------------------------------------------
//		
TInt Ctsysinfoprovidertests::SetLightTimeOut( CStifItemParser& /*aItem*/)
{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KDisplay);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KLightTimeOut);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant sysdata((TInt32)-100);
    map->InsertL(KStatus,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result != SErrNone)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KDisplay);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KLightTimeOut);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)5000);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KSetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
	pos = 0;
		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		iOutparam->Reset();
		iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result != SErrNone)
			{
			result =  0;
			}
	    else
	    {
		result =  -1;	
	    }
	}
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}
	
	
	
TInt  Ctsysinfoprovidertests::GetDriveInfoL(CStifItemParser& /*aItem*/)
	{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    TInt pos = 0;
    
    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0,changedDisplayLang = 0;
   
	Init();
	__UHEAP_MARK;

	TLiwGenericParam entity;
	TLiwVariant  entityname;
	TLiwGenericParam key;
	TLiwVariant  keyname;
	
	entityname.Set(KMemory);
	entity.SetNameAndValueL(KEntity,entityname);

	keyname.Set(KDriveInfo);
	key.SetNameAndValueL(KKey,keyname);
	
    //sysdata as map
	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	_LIT(KDrivePath,"p:\\");
    TLiwVariant sysdata(KDrivePath);
    map->InsertL(KDriveNo,sysdata); 
    sysdata.Reset();	

    TLiwVariant sysparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(KSysData,sysparam);
	sysparam.Reset();

	iInparam->AppendL(entity);

	iInparam->AppendL(key);
	iInparam->AppendL(element);
	
	element.Reset();

	map->DecRef();
	CleanupStack::Pop(map);
		
	entity.Reset();
	entityname.Reset();
	key.Reset();
	keyname.Reset();
	sysdata.Reset();
	
	//Set Vibra 
	TRAPD(err,iInterface->ExecuteCmdL(KGetInfo,*iInparam,*iOutparam));
	result = err;
	if(err == KErrNone)
	{
	pos = 0;
	iOutparam->FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
			result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
		}
	iOutparam->Reset();
	iInparam->Reset();
		
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
	if(result == SErrServiceNotReady)
		{
		result =  0;
		
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KMemory);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KDriveInfo);
		key.SetNameAndValueL(KKey,keyname);
		
	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

		_LIT(KDrivePath2,"aath:\\");
	    TLiwVariant sysdata(KDrivePath2);
	    map->InsertL(KDriveNo,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		iInparam->AppendL(entity);

		iInparam->AppendL(key);
		iInparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//Set Vibra 
		TRAPD(err,iInterface->ExecuteCmdL(KGetInfo,*iInparam,*iOutparam));
		result = err;
		if(err == KErrNone)
		{
	pos = 0;
		iOutparam->FindFirst( pos, KErrorCode );
		if(pos != KErrNotFound)
			{
				result = (TInt)((*iOutparam)[pos].Value().AsTInt32());
			}
		TBuf<50> buf;
		buf.AppendNum(result);
		iLog->Log(buf);	
		if(result == SErrBadArgumentType)
			{
			result =  0;
			}
	    else
		    {
			result =  -1;	
		    }
		}
	
		iOutparam->Reset();
		iInparam->Reset();
		
		}
    else
	    {
		result =  -1;	
	    }
	}

	__UHEAP_MARKEND;
	return result;

	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::UserInactivityNotify
// negative user inactivity time value
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::UserInactivityNotify(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    ret = UserInactivity(iLog);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::GetCameraInfoTestNegative
// negative test case general
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoprovidertests::GetCameraInfoTestNegative(CStifItemParser& aItem)
    {
    TInt retcode = 0;
    iLog->Log(_L("GetCameraInfoTest - Negative Test") );

    __UHEAP_MARK;
    TInt error = KErrNone;
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);
    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource, KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);
    iServiceHandler->AttachL(a);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam);
    delete crit;
    a.Reset();

    TInt pos = 0;
    MLiwInterface* interface = NULL;
    outparam->FindFirst(pos, KIDataSource);
    if (pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface();
        }
    outparam->Reset();
    inparam->Reset();

    if (interface)
        {
        TLiwGenericParam entity;
        TLiwVariant entityValue;
        TLiwGenericParam key;
        TLiwVariant keyValue;
        TPtrC16 Entity(KNullDesC);
        TPtrC16 Key(KNullDesC);
        TInt expectedError = 0;

        aItem.GetNextString(Entity);
        aItem.GetNextString(Key);
        aItem.GetNextInt(expectedError);

        if (Entity.Compare(_L("NULL")) == 0)
            {
            keyValue.Set(Key);
            key.SetNameAndValueL(KKey, keyValue);
            inparam->AppendL(key);
            }
        else
            if (Key.Compare(_L("NULL")) == 0)
                {
                entityValue.Set(Entity);
                entity.SetNameAndValueL(KEntity, entityValue);
                inparam->AppendL(entity);
                }
            else
                {
                entityValue.Set(Entity);
                entity.SetNameAndValueL(KEntity, entityValue);
                keyValue.Set(Key);
                key.SetNameAndValueL(KKey, keyValue);
                inparam->AppendL(entity);
                inparam->AppendL(key);
                }
        entity.Reset();
        entityValue.Reset();
        key.Reset();
        keyValue.Reset();

        //Get Image Data
        TRAP(error, interface->ExecuteCmdL(KGetInfo, *inparam, *outparam));

        pos = 0;
        const TLiwGenericParam* errorCode = outparam->FindFirst(pos,
                KErrorCode);
        if (errorCode)
            {
            retcode = errorCode->Value().AsTInt32();
            if (retcode == expectedError)
                {
                iLog->Log(_L("Got expected error code %d"), retcode);
                pos = 0;
                const TLiwGenericParam* output = outparam->FindFirst(pos,
                        KReturnValue);
                if (output)
                    {
                    const CLiwMap* Map = output->Value().AsMap();
                    if (Map)
                        {
                        TLiwVariant data1;
                        TLiwVariant data2;
                        if (EFalse != Map->FindL(KCamResList, data1))
                            {
                            const CLiwList* resolutionList = data1.AsList();
                            TInt width;
                            TInt height;
                            if (resolutionList)
                                {
                                TInt count = resolutionList->Count();
                                for (TInt i=0; i < count; i++)
                                    {
                                    TLiwVariant resolutionData;
                                    resolutionList->AtL(i, resolutionData);
                                    const CLiwMap* resolutionDataMap = resolutionData.AsMap();
                                    TLiwVariant xPix;
                                    resolutionDataMap->FindL(KXPixels, xPix);
                                    width = xPix.AsTInt32();
                                    xPix.Reset();
                                    iLog->Log(_L("Supported XPixel %d is %d -"),i, width);

                                    TLiwVariant yPix;
                                    resolutionDataMap->FindL(KYPixels, yPix);
                                    height = yPix.AsTInt32();
                                    yPix.Reset();
                                    iLog->Log(_L("Supported YPixel %d is %d -"),i, height);

                                    resolutionData.Reset();
                                    }//for
                                } //resolutionList                            
                            }//FindL
                        if (EFalse != Map->FindL(KCamMimeTypesList, data2))
                            {
                            const CLiwList* mimeList = data2.AsList();
                            if (mimeList)
                                {
                                for (TInt i=0; i != mimeList->Count(); i++)
                                    {
                                    TLiwVariant mimeData;
                                    TPtrC16 mimeType;
                                    mimeList->AtL(i, mimeData);
                                    mimeType.Set(mimeData.AsDes());

                                    iLog->Log(_L("Mimetype %d is - %s"), i,mimeType.Ptr());
                                    mimeData.Reset();
                                    }//for
                                } //mimeList
                            }//FindL
                        data1.Reset();
                        data2.Reset();
                        }//Map                    
                    }//output 
                retcode = KErrNone;
                iLog->Log(_L("Test Completed"));
                iLog->Log(_L("PASS"));
                }//retcode == expected error
            else
                {
                iLog->Log(_L("Error Code Returned = %d"), retcode);
                iLog->Log(_L("Error Code Expected = %d"), expectedError);
                iLog->Log(_L("Test Completed"));
                iLog->Log(_L("FAIL"));
                }
            }//errorCode
        }//interface    
    inparam->Reset();
    outparam->Reset();
    interface->Close();
    CleanupStack::PopAndDestroy(iServiceHandler);
    __UHEAP_MARKEND;
    iLog->Log(_L("END"));
    return retcode;
    }

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::GetCameraInfoNegEntity
// negative test case - Wrong Entity
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoprovidertests::GetCameraInfoNegEntity(CStifItemParser& aItem)
    {
    _LIT8(KEntity1, "Entity1");
    TInt retcode = 0;
    iLog->Log(_L("GetCameraInfoNegEntity - Negative Test") );

    __UHEAP_MARK;
    TInt error = KErrNone;
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);
    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource, KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);
    iServiceHandler->AttachL(a);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam);
    delete crit;
    a.Reset();

    TInt pos = 0;
    MLiwInterface* interface = NULL;
    outparam->FindFirst(pos, KIDataSource);
    if (pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface();
        }
    outparam->Reset();
    inparam->Reset();

    if (interface)
        {
        TLiwGenericParam entity;
        TLiwVariant entityName;
        TLiwVariant entityValue;
        TLiwGenericParam key;
        TLiwGenericParam keyName;
        TLiwVariant keyValue;
        TPtrC16 Entity(KNullDesC);
        TPtrC16 Key(KNullDesC);
        TInt expectedError = 0;

        aItem.GetNextString(Entity);
        aItem.GetNextString(Key);
        aItem.GetNextInt(expectedError);

        entityValue.Set(Entity);
        entity.SetNameAndValueL(KEntity1, entityValue);
        keyValue.Set(Key);
        key.SetNameAndValueL(KKey, keyValue);
        inparam->AppendL(entity);
        inparam->AppendL(key);

        entity.Reset();
        entityValue.Reset();
        key.Reset();
        keyValue.Reset();

        //Get Image Data
        TRAP(error, interface->ExecuteCmdL(KGetInfo, *inparam, *outparam));

        pos = 0;
        const TLiwGenericParam* errorCode = outparam->FindFirst(pos,
                KErrorCode);
        if (errorCode)
            {
            retcode = errorCode->Value().AsTInt32();
            if (retcode == expectedError)
                {
                iLog->Log(_L("Got expected error code %d"), retcode);
                pos = 0;
                const TLiwGenericParam* output = outparam->FindFirst(pos,
                        KReturnValue);
                if (output)
                    {
                    const CLiwMap* Map = output->Value().AsMap();
                    if (Map)
                        {
                        TLiwVariant data1;
                        TLiwVariant data2;
                        if (EFalse != Map->FindL(KCamResList, data1))
                            {
                            const CLiwList* resolutionList = data1.AsList();
                            TInt width;
                            TInt height;
                            if (resolutionList)
                                {
                                TInt count = resolutionList->Count();
                                for (TInt i=0; i < count; i++)
                                    {
                                    TLiwVariant resolutionData;
                                    resolutionList->AtL(i, resolutionData);
                                    const CLiwMap* resolutionDataMap = resolutionData.AsMap();
                                    TLiwVariant xPix;
                                    resolutionDataMap->FindL(KXPixels, xPix);
                                    width = xPix.AsTInt32();
                                    xPix.Reset();
                                    iLog->Log(_L("Supported XPixel %d is %d -"),i, width);

                                    TLiwVariant yPix;
                                    resolutionDataMap->FindL(KYPixels, yPix);
                                    height = yPix.AsTInt32();
                                    yPix.Reset();
                                    iLog->Log(_L("Supported YPixel %d is %d -"),i, height);

                                    resolutionData.Reset();
                                    }//for
                                } //resolutionList                            
                            }//FindL
                        if (EFalse != Map->FindL(KCamMimeTypesList, data2))
                            {
                            const CLiwList* mimeList = data2.AsList();
                            if (mimeList)
                                {
                                for (TInt i=0; i != mimeList->Count(); i++)
                                    {
                                    TLiwVariant mimeData;
                                    TPtrC16 mimeType;
                                    mimeList->AtL(i, mimeData);
                                    mimeType.Set(mimeData.AsDes());

                                    iLog->Log(_L("Mimetype %d is - %s"), i,mimeType.Ptr());
                                    mimeData.Reset();
                                    }//for
                                } //mimeList
                            }//FindL
                        data1.Reset();
                        data2.Reset();
                        }//Map                    
                    }//output 
                retcode = KErrNone;
                iLog->Log(_L("Test Completed"));
                iLog->Log(_L("PASS"));
                }//retcode == expected error
            else
                {
                iLog->Log(_L("Error Code Returned = %d"), retcode);
                iLog->Log(_L("Error Code Expected = %d"), expectedError);
                iLog->Log(_L("Test Completed"));
                iLog->Log(_L("FAIL"));
                }
            }//errorCode
        }//interface    
    inparam->Reset();
    outparam->Reset();
    interface->Close();
    CleanupStack::PopAndDestroy(iServiceHandler);
    __UHEAP_MARKEND;
    iLog->Log(_L("END"));
    return retcode;
    }

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::GetCameraInfoNegKey
// negative test case - Wrong Key
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoprovidertests::GetCameraInfoNegKey(CStifItemParser& aItem)
    {
    _LIT8(KKey1, "Key1");
    TInt retcode = 0;
    iLog->Log(_L("GetCameraInfoNegKey - Negative Test") );

    __UHEAP_MARK;
    TInt error = KErrNone;
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);
    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource, KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);
    iServiceHandler->AttachL(a);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam);
    delete crit;
    a.Reset();

    TInt pos = 0;
    MLiwInterface* interface = NULL;
    outparam->FindFirst(pos, KIDataSource);
    if (pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface();
        }
    outparam->Reset();
    inparam->Reset();

    if (interface)
        {
        TLiwGenericParam entity;
        TLiwVariant entityValue;
        TLiwGenericParam key;
        TLiwVariant keyValue;
        TPtrC16 Entity(KNullDesC);
        TPtrC16 Key(KNullDesC);
        TInt expectedError = 0;

        aItem.GetNextString(Entity);
        aItem.GetNextString(Key);
        aItem.GetNextInt(expectedError);

        entityValue.Set(Entity);
        entity.SetNameAndValueL(KEntity, entityValue);
        keyValue.Set(Key);
        key.SetNameAndValueL(KKey1, keyValue);
        inparam->AppendL(entity);
        inparam->AppendL(key);

        entity.Reset();
        entityValue.Reset();
        key.Reset();
        keyValue.Reset();

        //Get Image Data
        TRAP(error, interface->ExecuteCmdL(KGetInfo, *inparam, *outparam));

        pos = 0;
        const TLiwGenericParam* errorCode = outparam->FindFirst(pos,
                KErrorCode);
        if (errorCode)
            {
            retcode = errorCode->Value().AsTInt32();
            if (retcode == expectedError)
                {
                iLog->Log(_L("Got expected error code %d"), retcode);
                pos = 0;
                const TLiwGenericParam* output = outparam->FindFirst(pos,
                        KReturnValue);
                if (output)
                    {
                    const CLiwMap* Map = output->Value().AsMap();
                    if (Map)
                        {
                        TLiwVariant data1;
                        TLiwVariant data2;
                        if (EFalse != Map->FindL(KCamResList, data1))
                            {
                            const CLiwList* resolutionList = data1.AsList();
                            TInt width;
                            TInt height;
                            if (resolutionList)
                                {
                                TInt count = resolutionList->Count();
                                for (TInt i=0; i < count; i++)
                                    {
                                    TLiwVariant resolutionData;
                                    resolutionList->AtL(i, resolutionData);
                                    const CLiwMap* resolutionDataMap = resolutionData.AsMap();
                                    TLiwVariant xPix;
                                    resolutionDataMap->FindL(KXPixels, xPix);
                                    width = xPix.AsTInt32();
                                    xPix.Reset();
                                    iLog->Log(_L("Supported XPixel %d is %d -"),i, width);

                                    TLiwVariant yPix;
                                    resolutionDataMap->FindL(KYPixels, yPix);
                                    height = yPix.AsTInt32();
                                    yPix.Reset();
                                    iLog->Log(_L("Supported YPixel %d is %d -"),i, height);

                                    resolutionData.Reset();
                                    }//for
                                } //resolutionList                            
                            }//FindL
                        if (EFalse != Map->FindL(KCamMimeTypesList, data2))
                            {
                            const CLiwList* mimeList = data2.AsList();
                            if (mimeList)
                                {
                                for (TInt i=0; i != mimeList->Count(); i++)
                                    {
                                    TLiwVariant mimeData;
                                    TPtrC16 mimeType;
                                    mimeList->AtL(i, mimeData);
                                    mimeType.Set(mimeData.AsDes());

                                    iLog->Log(_L("Mimetype %d is - %s"), i,mimeType.Ptr());
                                    mimeData.Reset();
                                    }//for
                                } //mimeList
                            }//FindL
                        data1.Reset();
                        data2.Reset();
                        }//Map                    
                    }//output 
                retcode = KErrNone;
                iLog->Log(_L("Test Completed"));
                iLog->Log(_L("PASS"));
                }//retcode == expected error
            else
                {
                iLog->Log(_L("Error Code Returned = %d"), retcode);
                iLog->Log(_L("Error Code Expected = %d"), expectedError);
                iLog->Log(_L("Test Completed"));
                iLog->Log(_L("FAIL"));
                }
            }//errorCode
        }//interface    
    inparam->Reset();
    outparam->Reset();
    interface->Close();
    CleanupStack::PopAndDestroy(iServiceHandler);
    __UHEAP_MARKEND;
    iLog->Log(_L("END"));
    return retcode;
    }

