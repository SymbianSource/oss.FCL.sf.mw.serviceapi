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
* Description: 
*
*/


#include <avkon.hrh>
#include <aknnotewrappers.h> 
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <liwservicehandler.h>
#include "appmanagerservice.h"
#include "appmanagercommon.h"
#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>

#include "appmanagerservice.h"

#include "testappmngui.pan"
#include "testappmnguiappui.h"
#include "testappmnguiappview.h"
#include "testappmngui.hrh"
#include  "testappobserver.h"

_LIT8(KContent,"Type");
_LIT8(KDocumentPath,"DocumentPath");
_LIT8(KMimeType,"MimeType");
_LIT8(KMode,"Mode");
_LIT8(KPostion,"Position");
_LIT8(KHandle,"Handle");
_LIT8(KDocument,"Document");
_LIT(KNull,"NULL");

_LIT8(KService, "Service.AppManager");
_LIT8(KIAppManager,"IAppManager");
_LIT8(KTransactionID,"TransactionID");
_LIT8(KCmdLine,"CmdLine");

_LIT8(KApplicationID,"ApplicationID");
_LIT8(KDocumentName,"DocumentName");

//Supported Operation
_LIT8(KGetList,  "GetList");
_LIT8(KLaunchApp,"LaunchApp");
_LIT8(KLaunchDoc,"LaunchDoc");

_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");
_LIT8(KOptions,"Options");

// Filter Map
_LIT8(KFilter,"Filter");

const TInt KDocMaxDigitsInHexString = 8; // 32 bits.

// ConstructL is called by the application framework
void CtestappmnguiAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CtestappmnguiAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

CtestappmnguiAppUi::CtestappmnguiAppUi()                              
    {
	// no implementation required
    }

CtestappmnguiAppUi::~CtestappmnguiAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// handle any menu commands
void CtestappmnguiAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case EtestappmnguiCommand1:
            {
           
            CAppManagerService* coreClass = CAppManagerService::NewL();
            CAppObserver *observer = CAppObserver::NewL();
            TOptions options;
            TDocument criteria;
            TBuf<100> filename;
            options.iMode.Set(_L("Chained"));
            	
            options.iDocument.Set(_L("c:\\Data\\Images\\Test1.jpg" ));
                              
            TRAPD(err,coreClass->LaunchApplicationL(_L("s60uid://0x101f4d90"),KNullDesC8 ,options,observer,1) );
            observer->wait->Start();
            delete observer;
            delete coreClass;
    

            }
            break;
            
            
       case EtestappmnguiCommand2:
            {
            CAppManagerService* coreClass = CAppManagerService::NewL();
            CAppObserver *observer = CAppObserver::NewL();
            TOptions options;
            TDocument criteria;
            TBuf<100> filename;
            options.iMode.Set(_L("Chained"));
           
            criteria.iPath.Set(_L("c:\\Data\\Images\\Test1.jpg" ));
                              
            TRAPD(err,coreClass->LaunchDocumentL(criteria,KNullDesC8 ,options,filename,observer,2) );
            observer->wait->Start();
            delete observer;
            delete coreClass;
            
           }
            break;

        default:
            Panic(EtestappmnguiBasicUi);
            break;
        }
    }


// This function is not used right now but may be used in future onec we support 
// launching thorugh buffer


TInt CtestappmnguiAppUi::GetBufferFromFile(HBufC8*& aBuffer, const TDesC& aFileName) 
	{

    RFs fsSession;
	fsSession.Connect();
	if (fsSession.IsValidName(aFileName))
	    {
	    
	    RFile temp;
	    temp.Open(fsSession,aFileName,EFileShareReadersOnly);
	    const TInt preferredBufSize = 400000;
	    HBufC8* const buffer=HBufC8::New(Max(8, preferredBufSize)); // 8 is a sensible minimum
	    if (buffer==NULL)
		    {
		    return KErrNoMemory;
		    }
		
		TPtr8 buffer_asWritable(buffer->Des());
		const TInt error=fsSession.ReadFileSection(aFileName, 0, buffer_asWritable, preferredBufSize);
		if (error!=KErrNone)
			{
		     delete buffer;
			}
		else
		    {
		    aBuffer=buffer;  
		    }
		   
			fsSession.Close();
			return error;
	    }

	return 0;
	}

