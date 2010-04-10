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
* Description:  CSysinfoInterface class implementation
*
*/


#ifndef __SYSINFO_ERRMSG_H__
#define __SYSINFO_ERRMSG_H__

_LIT8(KErrorMsg,"ErrorMessage");

_LIT16(KErrInterfaceNotSupported,"Sysinfo: Requested Interface type not supported by provider");

_LIT16(KModuleName,"SysInfo: ");
_LIT16(KColon,": ");
_LIT16(KErrCmdNotSupported,"Command Not Supported");
_LIT16(KErrSystemDataMissing,"SystemData Argument Missing");
_LIT16(KErrSyncVersionNotSupported,"Sync Version Not Supported");
_LIT16(KErrASyncVersionNotSupported,"ASync Version Not Supported");
_LIT16(KErrKeyMissing,"Key: Input Parameter Missing");
_LIT16(KErrEntityMissing,"Entity: Input Parameter Missing");
_LIT16(KErrInsufficientArgs,"Insufficient Arguments to process");
_LIT16(KErrSysdataType,"Incorrect SystemData Type, SystemData Must be a Map");
_LIT16(KErrSystemAttributeValue,"Incorrect System Attribute Value corresponding to element in SystemData Map ");
_LIT16(KErrInCorrectSyncAsyncRequest,"CallBack and CmdOptions not matching");
_LIT16(KErrUnsupportedInput,"Unsupported Input parameter in SystemData Map");
_LIT16(KErrTransactionIdMissing,"Transaction ID missing");
_LIT16(KErrCallbackNotPresent,"Callback object not found");
_LIT16(KErrReadingGetInfo,"Output Data Not found");

#endif // __SYSINFO_ERRMSG_H__
