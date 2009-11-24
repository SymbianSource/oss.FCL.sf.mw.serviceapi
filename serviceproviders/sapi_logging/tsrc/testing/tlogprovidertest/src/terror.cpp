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

#include <liwservicehandler.h>
#include <liwcommon.h>
#include <logcli.h>
#include <logwrap.h>
#include "tlogprovidertest.h"
#include "serviceerrno.h"
//#include "logginginterface.h"
TInt sapierrors()
{

 //if(SErrServiceNotSupported == ConvertToSapiError(KErrNotSupported))


 if(1000==SErrInvalidServiceArgument)
        if(1001== SErrUnknownArgumentName )
        if(1002==SErrBadArgumentType )
        if(1003 == SErrMissingArgument )
        if(1004 ==SErrServiceNotSupported )
        if(1005==SErrServiceInUse )
        if(1006==SErrServiceNotReady )
        if(1007==SErrNoMemory )
        if(1008==SErrHardwareNotAvailable)
        if(1009 ==SErrServerBusy)
        if(1010==SErrEntryExists )
        if(1011== SErrAccessDenied )
        if(1012==SErrNotFound )
        if(1013==SErrUnknownFormat )
        if(1014==SErrGeneralError )
        if(1015==SErrCancelSuccess)
        if(1016==SErrServiceTimedOut)

return KErrNone;
else
return KErrGeneral;
	
}


