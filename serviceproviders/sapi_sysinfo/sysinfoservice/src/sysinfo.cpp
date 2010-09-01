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
* Description:  CSysInfoService class implementation
*
*/


#include <AccessoryConnection.h>
#include <AccessoryServer.h>
#include <PtiEngine.h>
#include <centralrepository.h>
#include <sysutildomaincrkeys.h>

#include "sysinfo.h"
#include "sysinfoutils.h"

// --------------------------------------------------------------------
// CSysData::CSysData()
// Constructor
// --------------------------------------------------------------------
//
CSysData::CSysData(TDataType aType):iDataType(aType)
    {
    }

// --------------------------------------------------------------------
// CSysData::~CSysData()
// Destructor
// --------------------------------------------------------------------
//
CSysData::~CSysData()
    {
    }

// --------------------------------------------------------------------
// CSysData::DataType()
// returns type of data this instance holds. @TDataType
// --------------------------------------------------------------------
//
EXPORT_C CSysData::TDataType CSysData::DataType() const
    {
    return iDataType;
    }

// --------------------------------------------------------------------
// CStatus::CStatus()
// Constructor
// --------------------------------------------------------------------
//
CStatus::CStatus(TInt aStatus):CSysData(EStatus),iStatus(aStatus)
    {
    }

// --------------------------------------------------------------------
// CStatus::~CStatus()
// Destructor
// --------------------------------------------------------------------
//
CStatus::~CStatus()
    {
    }

// --------------------------------------------------------------------
// CStatus::CStatus()
// Two-phased constructor
// --------------------------------------------------------------------
//
EXPORT_C CStatus* CStatus::NewL(TInt aStatus)
    {
    CStatus* self = new (ELeave) CStatus(aStatus);
    return self;
    }

// --------------------------------------------------------------------
// CStatus::CStatus()
// returns interger value stored which is used to represent status of
// many SA's.
// --------------------------------------------------------------------
//
EXPORT_C TInt CStatus::Status() const
    {
    return iStatus;
    }

// --------------------------------------------------------------------
// CStringData::CStringData()
// Constructor.
// --------------------------------------------------------------------
//
CStringData::CStringData():CSysData(EStringData)
    {
    }

// --------------------------------------------------------------------
// CStringData::~CStringData()
// Destructor
// --------------------------------------------------------------------
//
CStringData::~CStringData()
    {
    delete iStringData;
    }

// --------------------------------------------------------------------
// CStringData::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
EXPORT_C CStringData* CStringData::NewL(const TDesC& aString)
    {
    CStringData* self = new (ELeave) CStringData();
    CleanupStack::PushL(self);
    self->iStringData = aString.AllocL();
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------
// CStringData::StringData()
// On return aString contains string data.
// --------------------------------------------------------------------
//
EXPORT_C void CStringData::StringData(TPtrC& aString) const
    {
    aString.Set(*iStringData);
    }

// --------------------------------------------------------------------
// CVersion::CVersion()
// Constructor.
// --------------------------------------------------------------------
//
CVersion::CVersion(TInt aMajor,TInt aMinor):CSysData(EVersion),
                                        iMajorVersion(aMajor),
                                        iMinorVersion(aMinor)
    {
    }

// --------------------------------------------------------------------
// CVersion::~CVersion()
// Destructor
// --------------------------------------------------------------------
//
CVersion::~CVersion()
    {
    }

// --------------------------------------------------------------------
// CVersion::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CVersion* CVersion::NewL(TInt aMajor,TInt aMinor)
    {
    CVersion* self = new (ELeave) CVersion(aMajor,aMinor);
    return self;
    }

// --------------------------------------------------------------------
// CVersion::MajorVersion()
// returns major version number.
// --------------------------------------------------------------------
//
EXPORT_C TInt CVersion::MajorVersion() const
    {
    return iMajorVersion;
    }

// --------------------------------------------------------------------
// CVersion::MinorVersion()
// returns minor version number.
// --------------------------------------------------------------------
//
EXPORT_C TInt CVersion::MinorVersion() const 
    {
    return iMinorVersion;
    }

// --------------------------------------------------------------------
// CNetworkInfo::CNetworkInfo()
// Constructor.
// --------------------------------------------------------------------
//
CNetworkInfo::CNetworkInfo(RMobilePhone::TMobilePhoneNetworkInfoV1& aNetworkInfo,
                            RMobilePhone::TMobilePhoneLocationAreaV1& aArea)
                            :CSysData(ENetworkInfo),iNetworkInfo(aNetworkInfo),
                            iLAC(aArea)
    {
    }

// --------------------------------------------------------------------
// CNetworkInfo::~CNetworkInfo()
// Destructor
// --------------------------------------------------------------------
//
CNetworkInfo::~CNetworkInfo()
    {
    }

// --------------------------------------------------------------------
// CNetworkInfo::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CNetworkInfo* CNetworkInfo::NewL(
                        RMobilePhone::TMobilePhoneNetworkInfoV1& aNetworkInfo,
                        RMobilePhone::TMobilePhoneLocationAreaV1& aArea )
    {
    CNetworkInfo* self = new (ELeave) CNetworkInfo(aNetworkInfo,aArea);
    return self;
    }
	
// --------------------------------------------------------------------
// CNetworkInfo::NetworkName()
// returns network name.
// --------------------------------------------------------------------
//
EXPORT_C TPtrC CNetworkInfo::NetworkName()  const
    {
    return	TPtrC(iNetworkInfo.iLongName);
    }

// --------------------------------------------------------------------
// CNetworkInfo::NetworkMode()
// returns network mode.
// --------------------------------------------------------------------
//
EXPORT_C TInt CNetworkInfo::NetworkMode() const
    {
    return (iNetworkInfo.iMode - 1);
    }
	
// --------------------------------------------------------------------
// CNetworkInfo::NetworkStatus()
// returns network status.
// --------------------------------------------------------------------
//
EXPORT_C TInt CNetworkInfo::NetworkStatus() const
    {
    return (iNetworkInfo.iStatus -1);
    }

// --------------------------------------------------------------------
// CNetworkInfo::CountryCode()
// returns MCC Mobile Country Code.
// --------------------------------------------------------------------
//
EXPORT_C TPtrC CNetworkInfo::CountryCode() const
    {
    return 	TPtrC(iNetworkInfo.iCountryCode);
    }

// --------------------------------------------------------------------
// CNetworkInfo::NetworkCode()
// returns MNC Mobile Network Code.
// --------------------------------------------------------------------
//
EXPORT_C TPtrC CNetworkInfo::NetworkCode() const
    {
    return 	TPtrC(iNetworkInfo.iNetworkId);
    }	

// --------------------------------------------------------------------
// CNetworkInfo::LocationAreaCode()
// returns LAC Location Area Code.
// --------------------------------------------------------------------
//
EXPORT_C TUint CNetworkInfo::LocationAreaCode() const
    {
    return iLAC.iLocationAreaCode;
    }
	
// --------------------------------------------------------------------
// CNetworkInfo::CellId()
// returns Cell ID of a region.
// --------------------------------------------------------------------
//
EXPORT_C TUint CNetworkInfo::CellId()  const
    {
    return iLAC.iCellId;
    }

// --------------------------------------------------------------------
// CNetworkInfo::ValidLocationAreaCode()
// returns bool validates LAC and CellID data values.
// --------------------------------------------------------------------
//
EXPORT_C TBool CNetworkInfo::ValidLocationAreaCode()  const
    {
    return iLAC.iAreaKnown;
    }
	
	
// --------------------------------------------------------------------
// CAccessoryInfo::CAccessoryInfo()
// Constructor.
// --------------------------------------------------------------------
//
CAccessoryInfo::CAccessoryInfo(TAccessoryState aAccState)
                                :CSysData(EAccessoryInfo),
                                iConnectionState(aAccState)
    {
    }

// --------------------------------------------------------------------
// CAccessoryInfo::~CAccessoryInfo()
// Destructor
// --------------------------------------------------------------------
//
CAccessoryInfo::~CAccessoryInfo()
    {
    }

// --------------------------------------------------------------------
// CAccessoryInfo::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CAccessoryInfo* CAccessoryInfo::NewL(const TAccPolGenericID& aGenericID, 
                                        TAccessoryState aAccState)
    {
    CAccessoryInfo* self = new (ELeave) CAccessoryInfo(aAccState);
    self->GetAccessoryProperty(aGenericID);
    return self;
    }

// --------------------------------------------------------------------
// CAccessoryInfo::AccessoryType()
// returns type of accessory.
// --------------------------------------------------------------------
//
EXPORT_C TInt CAccessoryInfo::AccessoryType() const
    {
    return iAccessoryType;
    }

// --------------------------------------------------------------------
// CAccessoryInfo::GetAccessoryProperty()
// retrives accessory type information from aGenericID.
// --------------------------------------------------------------------
//
void CAccessoryInfo::GetAccessoryProperty(const TAccPolGenericID& aGenericID)
    {
    TUint32 deviceType = aGenericID.DeviceTypeCaps();
    TUint32 connectionType = aGenericID.PhysicalConnectionCaps();

    if(deviceType == KDTHeadset && (connectionType & KPCWired))
        {
        iAccessoryType = CAccessoryInfo::EHeadSet;
        }
    else if(deviceType == KDTHeadset && (connectionType & KPCBluetooth) )
        {
        iAccessoryType = EBTHeadSet;
        }
    else if(deviceType == KDTCarKit && (connectionType & KPCWired) )
        {
        iAccessoryType = ECarKit;
        }
    else if(deviceType == KDTCarKit && (connectionType == KPCBluetooth) )
        {
        iAccessoryType = EBTCarKit;
        }
    else
        {
        iAccessoryType = EUnknown;
        }
    }

// --------------------------------------------------------------------
// CAccessoryInfo::ConnectionState()
// returns accessory state (Connected,Disconnected).
// --------------------------------------------------------------------
//
EXPORT_C TInt CAccessoryInfo::ConnectionState() const
    {
    return iConnectionState;
    }

// --------------------------------------------------------------------
// CAccList::CAccList()
// Constructor.
// --------------------------------------------------------------------
//
CAccList::CAccList():CSysData(EAccessoryList)
    {
    }

// --------------------------------------------------------------------
// CAccList::~CAccList()
// Destructor
// --------------------------------------------------------------------
//
CAccList::~CAccList()
    {
    }

// --------------------------------------------------------------------
// CAccList::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CAccList* CAccList::NewL()
    {
    CAccList* self = new (ELeave) CAccList();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;	
    }

// --------------------------------------------------------------------
// CAccList::ConstructL()
// 2nd phase construtor
// --------------------------------------------------------------------
//
void CAccList::ConstructL()
    {
    RAccessoryServer    		AccSrv;
    RAccessoryConnection    	AccConnection;
    	
    //Connect to accessory server.
    User::LeaveIfError(AccSrv.Connect());
    //Create a session to it.
    User::LeaveIfError(AccConnection.CreateSubSession(AccSrv));
    //read list of connected accssories at this moment.
    AccConnection.GetAccessoryConnectionStatus(iAccessories);
    iCount = iAccessories.Count();
    //Close subsession.
    AccConnection.CloseSubSession();
    //Disconnect accessory server.
    AccSrv.Disconnect();
    }

// --------------------------------------------------------------------
// CAccList::AtL()
// Reads AccessoryInfo at an index. On return aAccessoryInfo consists 
// of accessory information.
// --------------------------------------------------------------------
//
EXPORT_C TBool CAccList::AtL(TInt aIndex,const CAccessoryInfo*& 
                                            aAccessoryInfo) const
    {
    TAccPolGenericID accessoryid;
    if(0 <= aIndex && aIndex < Count())
        {
        accessoryid = iAccessories.GetGenericIDL(aIndex);
        }
    else
        {
        aAccessoryInfo = NULL;
        return EFalse;
        }

    //Create CAccessoryInfo. client has the ownership.
    aAccessoryInfo = CAccessoryInfo::NewL(accessoryid,
                                            CAccessoryInfo::EConnected);
    return ETrue;
    }

// --------------------------------------------------------------------
// CAccList::[]
// Reads AccessoryInfo at an index. returns CAccessoryInfo 
// --------------------------------------------------------------------
//
EXPORT_C const CAccessoryInfo* CAccList::operator[](TInt aIndex) const
    {
    CAccessoryInfo* accessoryinfo = NULL;
    if(0 <= aIndex && aIndex < iCount)
        {
        TAccPolGenericID accessoryid;
        accessoryid = iAccessories.GetGenericIDL(aIndex);
        //Create CAccessoryInfo. client has the ownership.
        accessoryinfo = CAccessoryInfo::NewL(accessoryid,
                                            CAccessoryInfo::EConnected);
        }
    return accessoryinfo;
    }

// --------------------------------------------------------------------
// CAccList::Count()
// returns number of accessories. 
// --------------------------------------------------------------------
//
EXPORT_C TInt CAccList::Count() const
    {
    return iCount;
    }

// --------------------------------------------------------------------
// CLanguageList::CLanguageList()
// Constructor.
// --------------------------------------------------------------------
//
CLanguageList::CLanguageList():CSysData(ELanguageList)
    {
    }

// --------------------------------------------------------------------
// CLanguageList::~CLanguageList()
// Destructor
// --------------------------------------------------------------------
//
CLanguageList::~CLanguageList()
    {
    iLanguages.Close();
    }

// --------------------------------------------------------------------
// CLanguageList::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CLanguageList* CLanguageList::NewL()
    {
    CLanguageList* self;
    self = new (ELeave) CLanguageList();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------
// CLanguageList::ConstructL()
// 2nd phase construtor
// --------------------------------------------------------------------
//
void CLanguageList::ConstructL()
    {
    CPtiEngine* PtiEngine;
    PtiEngine = CPtiEngine::NewL();
    CleanupStack::PushL(PtiEngine);
    PtiEngine->GetAvailableLanguagesL(iLanguages);
    CleanupStack::PopAndDestroy(PtiEngine);
    }

// --------------------------------------------------------------------
// CLanguageList::[]
// returns language code at the index.
// --------------------------------------------------------------------
//
EXPORT_C TInt CLanguageList::operator[](TInt aIndex) const
    {
    if(0 <= aIndex && aIndex < Count())
        return iLanguages[aIndex];
    else
        return -1;
    }

// --------------------------------------------------------------------
// CLanguageList::At
// On return aEntry consists of language code at the index.
// --------------------------------------------------------------------
//
EXPORT_C TBool CLanguageList::At(TInt aIndex, TInt& aEntry) const
    {
    if(0 <= aIndex && aIndex < Count())
        {
        aEntry = iLanguages[aIndex];
        return ETrue;
        }
    return EFalse;	
    }

// --------------------------------------------------------------------
// CLanguageList::Count
// returns number of languages.
// --------------------------------------------------------------------
//
EXPORT_C TInt CLanguageList::Count() const
    {
    return iLanguages.Count();
    }

// --------------------------------------------------------------------
// CStringList::CStringList()
// Constructor.
// --------------------------------------------------------------------
//
CStringList::CStringList(CDesCArray*& aDesArray):CSysData(EStringList),
                                                iDesArray(aDesArray)
    {
    }

// --------------------------------------------------------------------
// CStringList::~CStringList()
// Destructor
// --------------------------------------------------------------------
//
CStringList::~CStringList()
    {
    delete iDesArray;
    }

// --------------------------------------------------------------------
// CStringList::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CStringList* CStringList::NewL(CDesCArray*& aDesArray)
    {
    CStringList* self = new (ELeave) CStringList(aDesArray);
    return self;
    }

// --------------------------------------------------------------------
// CStringList::[]
// returns string data at specified index.
// --------------------------------------------------------------------
//
EXPORT_C TPtrC CStringList::operator[](TInt aIndex) const
    {
    if( 0 <= aIndex && aIndex < iCount )
        return (*iDesArray)[aIndex];

    return NULL;
    }

// --------------------------------------------------------------------
// CStringList::At
// On return aEntry consists of string data at specified index.
// --------------------------------------------------------------------
//
EXPORT_C TBool CStringList::At(TInt aIndex, TPtrC& aEntry) const
    {
    if( 0 <= aIndex && aIndex < Count() )
        {
        aEntry.Set((*iDesArray)[aIndex]);
        return ETrue;
        }
    return EFalse;
    }

// --------------------------------------------------------------------
// CStringList::Count
// returns number of strings.
// --------------------------------------------------------------------
//
EXPORT_C TInt CStringList::Count() const
    {
    return iDesArray->Count();
    }

// --------------------------------------------------------------------
// CResolution::CResolution()
// Constructor.
// --------------------------------------------------------------------
//
CResolution::CResolution(TInt aXPixels, TInt aYPixels):CSysData(EResolution),
                                        iXPixels(aXPixels),iYPixels(aYPixels)
    {
    }

// --------------------------------------------------------------------
// CResolution::~CResolution()
// Destructor
// --------------------------------------------------------------------
//
CResolution::~CResolution()
    {
    }

// --------------------------------------------------------------------
// CResolution::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CResolution* CResolution::NewL(TInt aXPixels, TInt aYPixels)
    {
    CResolution* self = new (ELeave) CResolution(aXPixels,aYPixels);
    return self;
    }

// --------------------------------------------------------------------
// CResolution::XPixels()
// returns x-pixels.
// --------------------------------------------------------------------
//
EXPORT_C TInt CResolution::XPixels() const
    {
    return iXPixels;
    }

// --------------------------------------------------------------------
// CResolution::YPixels()
// returns y-pixels.
// --------------------------------------------------------------------
//
EXPORT_C TInt CResolution::YPixels() const
    {
    return iYPixels;
    }

// --------------------------------------------------------------------
// CDriveList::CDriveList()
// Constructor.
// --------------------------------------------------------------------
//
CDriveList::CDriveList():CSysData(EDriveList)
    {
    }

// --------------------------------------------------------------------
// CDriveList::~CDriveList()
// Destructor
// --------------------------------------------------------------------
//
CDriveList::~CDriveList()
    {
    iDrives.Close();
    }

// --------------------------------------------------------------------
// CDriveList::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CDriveList* CDriveList::NewL(TDriveList& aDrives)
    {
    CDriveList* self;
    self = new (ELeave) CDriveList();
    CleanupStack::PushL(self);
    self->ConstructL(aDrives);
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------
// CDriveList::ConstructL()
// 2nd phase construtor
// --------------------------------------------------------------------
//
void CDriveList::ConstructL(TDriveList& aDrives)
    {
    for  (TInt i=0; KMaxDrives > i; i++)
        //check drive is valid.
        if( aDrives[i] )
            //add the drive to list.
            iDrives.AppendL(i);

    iCount = iDrives.Count();
    }

// --------------------------------------------------------------------
// CDriveList::[]
// gets drive number at specified index.
// --------------------------------------------------------------------
//
EXPORT_C TInt CDriveList::operator[](TInt aIndex) const
    {
    if(0 <= aIndex && aIndex<iCount)
        return iDrives[aIndex];
    else
        return -1;
    }

// --------------------------------------------------------------------
// CDriveList::AtL
// gets drive number at specified index. aEntry consists of drive number.
// --------------------------------------------------------------------
//
EXPORT_C TBool CDriveList::At(TInt aIndex, TInt& aEntry) const
    {
    if( 0 <= aIndex && aIndex<iCount )
        {
        aEntry = iDrives[aIndex];
        return ETrue;
        }
    return EFalse;
    }

// --------------------------------------------------------------------
// CDriveList::Count
// returns number of drives.
// --------------------------------------------------------------------
//
EXPORT_C TInt CDriveList::Count() const
    {
    return iCount;
    }

// --------------------------------------------------------------------
// CDriveInfo::CDriveInfo()
// Constructor.
// --------------------------------------------------------------------
//
CDriveInfo::CDriveInfo(TInt aDrvNumber,TVolumeInfo& aVolumeInfo)
                            :CSysData(EDriveInfo),iDrvNumber(aDrvNumber),
                            iVolumeInfo(aVolumeInfo),iVolumeInfoValid(ETrue),
                            iCriticalSpace(-1)
    {
    }

// --------------------------------------------------------------------
// CDriveInfo::CDriveInfo()
// Constructor.
// --------------------------------------------------------------------
//
CDriveInfo::CDriveInfo(TInt aDrvNumber,TInt aCriticalSpace)
                                :CSysData(EDriveInfo),iDrvNumber(aDrvNumber),
                                iVolumeInfoValid(EFalse),
                                iCriticalSpace(aCriticalSpace)
    {
    }

// --------------------------------------------------------------------
// CDriveInfo::~CDriveInfo()
// Destructor
// --------------------------------------------------------------------
//
CDriveInfo::~CDriveInfo()
    {
    }

// --------------------------------------------------------------------
// CDriveInfo::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
EXPORT_C CDriveInfo* CDriveInfo::NewL(TInt aDriveNumber, TInt aCriticalSpace)
    {
    CDriveInfo* self;
    self = new (ELeave) CDriveInfo(aDriveNumber,aCriticalSpace);
    return self;
    }

// --------------------------------------------------------------------
// CDriveInfo::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CDriveInfo* CDriveInfo::NewL(TInt aDriveNumber, TVolumeInfo& aVolumeInfo)
    {
    CDriveInfo* self;
    self = new (ELeave) CDriveInfo(aDriveNumber,aVolumeInfo);
    return self;
    }

// --------------------------------------------------------------------
// CDriveInfo::DriveNumber
// returns drive number.
// --------------------------------------------------------------------
//
EXPORT_C TInt CDriveInfo::DriveNumber() const
    {
    return iDrvNumber;
    }

// --------------------------------------------------------------------
// CDriveInfo::CriticalSpace
// returns critical space of the drive.
// --------------------------------------------------------------------
//
EXPORT_C TInt CDriveInfo::CriticalSpace() const
    {
    TInt err(KErrNone);
    TInt criticalspace(0);
    if( -1 == iCriticalSpace )
        {
        if( EMediaRam == MediaType() )
            {
            TRAP(err,RepositoryUtil::GetRepositoryKeyL(KCRUidDiskLevel,
                                KRamDiskCriticalLevel,criticalspace));
            }
        else
            {
            TRAP(err,RepositoryUtil::GetRepositoryKeyL(KCRUidDiskLevel,
                                KDiskCriticalThreshold,criticalspace));
            }
        }
    else
        {
        criticalspace = iCriticalSpace;
        }

    return ( (KErrNone == err) ? criticalspace : err);
    }

// --------------------------------------------------------------------
// CDriveInfo::MediaType
// returns drive media type.
// --------------------------------------------------------------------
//
EXPORT_C TInt CDriveInfo::MediaType() const
    {
    return iVolumeInfo.iDrive.iType;
    }

// --------------------------------------------------------------------
// CDriveInfo::TotalSpace
// returns total space on this drive.
// --------------------------------------------------------------------
//
EXPORT_C TInt64 CDriveInfo::TotalSpace() const
    {
    return iVolumeInfo.iSize;
    }

// --------------------------------------------------------------------
// CDriveInfo::FreeSpace
// returns free space on this drive.
// --------------------------------------------------------------------
//
EXPORT_C TInt64 CDriveInfo::FreeSpace() const
    {
    return iVolumeInfo.iFree;
    }

// --------------------------------------------------------------------
// CDriveInfo::DriveName
// On return aDriveName consists name of the drive.
// --------------------------------------------------------------------
//
EXPORT_C void CDriveInfo::DriveName(TPtrC& aDriveName) const
    {
    aDriveName.Set(iVolumeInfo.iName);
    }

// --------------------------------------------------------------------
// CDriveInfo::DriveName
// returns battery state of this drive.
// --------------------------------------------------------------------
//
EXPORT_C TInt CDriveInfo::BatteryState() const
    {
    return iVolumeInfo.iDrive.iBattery;
    }

// --------------------------------------------------------------------
// CConnectionList::CConnectionList()
// Constructor.
// --------------------------------------------------------------------
//
CConnectionList::CConnectionList():CSysData(EConnectionList)
    {
    }

// --------------------------------------------------------------------
// CConnectionList::~CConnectionList()
// Destructor
// --------------------------------------------------------------------
//
CConnectionList::~CConnectionList()
    {
    iConnectionInfoArray.ResetAndDestroy();
    iConnectionInfoArray.Close();
    }

// --------------------------------------------------------------------
// CConnectionList::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CConnectionList* CConnectionList::NewL(
                            RPointerArray<CConnectionInfo>& aConnectionInfoArr)
    {
    CConnectionList* self = CConnectionList::NewLC(aConnectionInfoArr);
    CleanupStack::Pop(self);
    return self;
    }
 
// --------------------------------------------------------------------
// CConnectionList::NewLC()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CConnectionList* CConnectionList::NewLC(
                        RPointerArray<CConnectionInfo>& aConnectionInfoArr)
    {
    CConnectionList* self = new (ELeave) CConnectionList();
    CleanupStack::PushL(self);
    self->ConstructL(aConnectionInfoArr);
    return self;
    }

// --------------------------------------------------------------------
// CConnectionList::ConstructL()
// 2nd phase construtor
// --------------------------------------------------------------------
//
void CConnectionList::ConstructL(
                        RPointerArray<CConnectionInfo>& aConnectionInfoArr)
    {
    iCount = aConnectionInfoArr.Count();
    //Make a copy of available ConnectionInfo pointers.
    if(iCount > 0)
        {
        for(TInt index = 0 ; index < iCount; index++)
            {
            iConnectionInfoArray.AppendL(aConnectionInfoArr[index]);
            }
        }
    }

// --------------------------------------------------------------------
// CConnectionList::At()
// On return aConnectionInfo contains connection information.
// --------------------------------------------------------------------
//
EXPORT_C TBool CConnectionList::At(TInt aIndex,
                            const CConnectionInfo*& aConnectionInfo) const
    {
    if( 0 <= aIndex && aIndex<iCount )
        {
        aConnectionInfo = iConnectionInfoArray[aIndex];
        return ETrue;
        }
    return EFalse;
    }

// --------------------------------------------------------------------
// CConnectionList::[]
// gets CConnectionInfo at specified index.
// --------------------------------------------------------------------
//
EXPORT_C const CConnectionInfo* CConnectionList::operator[](TInt aIndex) const
    {
    return iConnectionInfoArray[aIndex];
    }

// --------------------------------------------------------------------
// CConnectionList::Count()
// returns number of connections.
// --------------------------------------------------------------------
//
EXPORT_C TInt CConnectionList::Count() const
    {
    return iCount;
    }

// --------------------------------------------------------------------
// CConnectionInfo::CConnectionInfo()
// Constructor.
// --------------------------------------------------------------------
//
CConnectionInfo::CConnectionInfo():CSysData(EConnectionInfo)
    {
    }

// --------------------------------------------------------------------
// CConnectionInfo::~CConnectionInfo()
// Destructor
// --------------------------------------------------------------------
//
CConnectionInfo::~CConnectionInfo()
    {
    delete iIAPName;
    delete iNetworkName;
    delete iConnectionName;
    }

// --------------------------------------------------------------------
// CConnectionInfo::CopyL()
// Creates new copy of the connectionInfo
// --------------------------------------------------------------------
//
CConnectionInfo* CConnectionInfo::CopyL()
    {
    CConnectionInfo* self = new (ELeave) CConnectionInfo();
    CleanupStack::PushL(self);

    self->ConstructL(iConnectionId, iIAPId, iBearerType, iConnectStatus,
                            *iIAPName, *iNetworkName, *iConnectionName);

    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------
// CConnectionInfo::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CConnectionInfo* CConnectionInfo::NewL(TUint aConnId, TUint aIAPId,
                            TInt aBearerType,
                            TConnectionState aConnectState,
                            const TDesC& aIAPName, 
                            const TDesC& aNetworkName,
                            const TDesC& aConnectionName)
    {
    CConnectionInfo* self = new (ELeave) CConnectionInfo();
    CleanupStack::PushL(self);
    self->ConstructL(aConnId, aIAPId, aBearerType, aConnectState, aIAPName,
                                            aNetworkName, aConnectionName);
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------
// CConnectionInfo::ConstructL()
// 2nd phase construtor
// --------------------------------------------------------------------
//	
void CConnectionInfo::ConstructL(TUint aConnId,TUint aIAPId,
                                TInt aBearerType,
                                TConnectionState aConnectState,
                                const TDesC& aIAPName,
                                const TDesC& aNetworkName,
                                const TDesC& aConnectionName)
    {
    iConnectionId = aConnId;
    iIAPId = aIAPId;
    iBearerType = aBearerType;
    iConnectStatus = aConnectState;
    iIAPName = aIAPName.AllocL();
    iNetworkName = aNetworkName.AllocL();
    iConnectionName = aConnectionName.AllocL();
    }
	
// --------------------------------------------------------------------
// CConnectionInfo::IAPId()
// returns IAP ID.
// --------------------------------------------------------------------
//	
EXPORT_C TUint CConnectionInfo::IAPId() const
    {
    return iIAPId;
    }

// --------------------------------------------------------------------
// CConnectionInfo::ConnectionState()
// returns Connection State.
// --------------------------------------------------------------------
//
EXPORT_C CConnectionInfo::TConnectionState CConnectionInfo::ConnectionState() 
                                                                        const
    {
    return iConnectStatus;
    }

// --------------------------------------------------------------------
// CConnectionInfo::SetConnectionState()
// changes connection state.
// --------------------------------------------------------------------
//
void CConnectionInfo::SetConnectionState(
                                CConnectionInfo::TConnectionState aState)
    {
    iConnectStatus = aState;
    }

// --------------------------------------------------------------------
// CConnectionInfo::ConnectionId()
// returns iConnection ID.
// --------------------------------------------------------------------
//	
TUint CConnectionInfo::ConnectionId() const
    {
    return iConnectionId;
    }

// --------------------------------------------------------------------
// CConnectionInfo::BearerType()
// returns BearerType.
// --------------------------------------------------------------------
//	
EXPORT_C TInt CConnectionInfo::BearerType() const
    {
    return iBearerType-1;
    }	

// --------------------------------------------------------------------
// CConnectionInfo::IAPName()
// returns IAP Name.
// --------------------------------------------------------------------
//	
EXPORT_C TPtrC CConnectionInfo::IAPName() const
    {
    return	TPtrC(*iIAPName);
    }

// --------------------------------------------------------------------
// CConnectionInfo::NetworkName()
// returns Network Name.
// --------------------------------------------------------------------
//		
EXPORT_C TPtrC CConnectionInfo::NetworkName() const
    {
    return	TPtrC(*iNetworkName);
    }
	
// --------------------------------------------------------------------
// CConnectionInfo::ConnectionName()
// returns Connection Name.
// --------------------------------------------------------------------
//		
EXPORT_C TPtrC CConnectionInfo::ConnectionName() const
    {
    return	TPtrC(*iConnectionName);
    }


// --------------------------------------------------------------------
// CCameraResolutionList::CCameraResolutionList()
// Constructor.
// --------------------------------------------------------------------
//
CCameraResolutionList::CCameraResolutionList() :
    CSysData( ECameraInfo )
    {
    }

// --------------------------------------------------------------------
// CConnectionList::~CConnectionList()
// Destructor
// --------------------------------------------------------------------
//
CCameraResolutionList::~CCameraResolutionList()
    {
    iresArray.ResetAndDestroy();
    iresArray.Close();
    }

// --------------------------------------------------------------------
// CCameraResolutionList::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CCameraResolutionList* CCameraResolutionList::NewL( RPointerArray<CResolution>& aCamResArray )
    {
    CCameraResolutionList* self = CCameraResolutionList::NewLC( aCamResArray );
    CleanupStack::Pop( self );
    return self;
    }

// --------------------------------------------------------------------
// CCameraResolutionList::NewLC()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CCameraResolutionList* CCameraResolutionList::NewLC( RPointerArray<CResolution>& aCamResArray )
    {
    CCameraResolutionList* self = new (ELeave) CCameraResolutionList();
    CleanupStack::PushL( self );
    self->ConstructL( aCamResArray );
    return self;
    }

// --------------------------------------------------------------------
// CCameraResolutionList::ConstructL()
// 2nd phase construtor
// --------------------------------------------------------------------
//
void CCameraResolutionList::ConstructL( RPointerArray<CResolution>& aCamResArray )
    {
    iCount = aCamResArray.Count();
    if ( iCount > 0 )
        {
        for ( TInt index = 0; index < iCount; index++ )
            {
            iresArray.AppendL( aCamResArray[index] );
            }
        }
    }

// --------------------------------------------------------------------
// CCameraResolutionList::At()
// On return val contains supported resolution XPixel or YPixel depending upon whether flag is 0 or 1.
// --------------------------------------------------------------------
//
EXPORT_C TBool CCameraResolutionList::At( TInt aIndex, TInt aFlag, TInt& aVal ) const
    {
    if ( 0 <= aIndex && aIndex<iCount )
        {
        if ( aFlag == 0 )
            {
            aVal = iresArray[aIndex]->XPixels();
            }
        else if ( aFlag == 1 )
            {
            aVal = iresArray[aIndex]->YPixels();
            }
        else
            {
            return EFalse;
            }
        return ETrue;
        }
    return EFalse;
    }

// --------------------------------------------------------------------
// CCameraResolutionList::[]
// gets Resolution at specified index.
// --------------------------------------------------------------------
//
EXPORT_C const CResolution* CCameraResolutionList::operator[]( TInt aIndex ) const
    {
    return iresArray[aIndex];
    }

// --------------------------------------------------------------------
// CCameraResolutionList::Count()
// returns number of resolutions supported.
// --------------------------------------------------------------------
//
EXPORT_C TInt CCameraResolutionList::Count() const
    {
    return iCount;
    }

// --------------------------------------------------------------------
// CCameraInfo::CCameraInfo()
// Constructor.
// --------------------------------------------------------------------
//
CCameraInfo::CCameraInfo() :
    CSysData( ECameraInfo )
    {
    }

// --------------------------------------------------------------------
// CCameraInfo::~CCameraInfo()
// Destructor
// --------------------------------------------------------------------
//
CCameraInfo::~CCameraInfo()
    {
    delete iResList;
    delete iMimeTypesList;
    }

// --------------------------------------------------------------------
// CCameraInfo::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CCameraInfo* CCameraInfo::NewL( CCameraResolutionList* aCamResList, CStringList* aMimeTypesList )
    {
    CCameraInfo* self = CCameraInfo::NewLC( aCamResList, aMimeTypesList );
    CleanupStack::Pop( self );
    return self;
    }

// --------------------------------------------------------------------
// CCameraInfo::NewLC()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CCameraInfo* CCameraInfo::NewLC( CCameraResolutionList* aCamResList, CStringList* aMimeTypesList )
    {
    CCameraInfo* self = new (ELeave) CCameraInfo();
    CleanupStack::PushL( self );
    self->ConstructL( aCamResList, aMimeTypesList );
    return self;
    }

// --------------------------------------------------------------------
// CCameraInfo::ConstructL()
// 2nd phase construtor
// --------------------------------------------------------------------
//
void CCameraInfo::ConstructL( CCameraResolutionList* aCamResList, CStringList* aMimeTypesList )
    {
    iResList = aCamResList;
    iMimeTypesList = aMimeTypesList;
    }

// --------------------------------------------------------------------
// CCameraInfo::ResolutionList()
// Gives a list containing supported resolutions
// --------------------------------------------------------------------
//
EXPORT_C CCameraResolutionList* CCameraInfo::ResolutionList() const
    {
    return iResList;
    }

// --------------------------------------------------------------------
// CCameraInfo::MimeTypesList()
// Gives a list containing supported mime types
// --------------------------------------------------------------------
//
EXPORT_C CStringList* CCameraInfo::MimeTypesList() const
    {
    return iMimeTypesList;
    }

// --------------------------------------------------------------------
// CVideoDecDataList::CVideoDecDataList()
// Constructor.
// --------------------------------------------------------------------
//
CVideoDecDataList::CVideoDecDataList():CSysData(EVideoDecList)
    {
    }

// --------------------------------------------------------------------
// CDriveList::~CDriveList()
// Destructor
// --------------------------------------------------------------------
//
CVideoDecDataList::~CVideoDecDataList()
    {
    for(int i=0;i<iDecData.Count();i++)
        delete iDecData[i];
    }

// --------------------------------------------------------------------
// CDriveList::NewL()
// Two-phased constructor. returns new instance of this class.
// --------------------------------------------------------------------
//
CVideoDecDataList* CVideoDecDataList::NewL()
    {
    CVideoDecDataList* self;
    self = new (ELeave) CVideoDecDataList();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------
// CDriveList::ConstructL()
// 2nd phase construtor
// --------------------------------------------------------------------
//
void CVideoDecDataList::ConstructL()
    {
    }

void CVideoDecDataList::AppendL(CVideoDecData *entry)
    {
    iDecData.AppendL(entry);
    }
// --------------------------------------------------------------------
// CDriveList::[]
// gets drive number at specified index.
// --------------------------------------------------------------------
//
EXPORT_C CVideoDecDataList::CVideoDecData *CVideoDecDataList::operator[](TInt aIndex) const
    {
    if(0 <= aIndex && aIndex<iDecData.Count())
        return iDecData[aIndex];
    else
        return NULL;
    }

// --------------------------------------------------------------------
// CDriveList::Count
// returns number of drives.
// --------------------------------------------------------------------
//
EXPORT_C TInt CVideoDecDataList::Count() const
    {
    return iDecData.Count();
    }
// End of file.		
