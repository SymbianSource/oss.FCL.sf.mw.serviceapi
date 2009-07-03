/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  describes system information utilities.
*
*/


#ifndef __SYSINFO_H__
#define __SYSINFO_H__

#include <BADESCA.H>
#include <f32file.h>
#include <AccPolGenericIDArray.h>
#include <etelmm.h>

class ISystemObserver;


/**
*   @ref CSysData is base class which can be extend to implement variety of 
*   system data representations.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CSysData) : public CBase
    {
    public:
    // Enumeration of supported i/o data types.
    enum TDataType
        {
        EStatus,
        EVersion,
        EConnectionList,
        EConnectionInfo,
        ENetworkInfo,
        EDriveInfo,
        ELanguageList,
        EDriveList,
        EAccessoryList,
        EAccessoryInfo,
        EResolution,
        EStringList,
        EStringData,
        };
    public:
    /**
    * virtual Destructor.
    */
    virtual ~CSysData ();

    /**
    * @return type of data stored.
    */
    IMPORT_C TDataType DataType() const;

    protected:

    /**
    * C++ default constructor.
    */
    CSysData(TDataType aType);		
    private:

    /**
    * Data type
    */
    TDataType   iDataType;
    };

/**
*  @ref CStatus is an integer data used in general for representing status 
*   information of some System Attributes. Typically ON,OFF state, battery 
*   level and so on.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CStatus) : public CSysData
    {
    public:

    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    IMPORT_C static CStatus* NewL(TInt aStatus);

    /**
    * @return   status information
    */    
    IMPORT_C TInt Status() const;

    /**
    * Destructor.
    */
    ~CStatus();

    private:

    /**
    * C++ default constructor.
    */
    CStatus(TInt aStatus);

    private:
    /**
    * Status value.
    */
    TInt    iStatus;
    };

/**
*  @ref CResolution screen resolution of device specified in X,Y Pixels.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CResolution) : public CSysData
    {
    public:

    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CResolution* NewL(TInt aXPixels, TInt aYPixels);

    /**
    * @return X-Pixels.
    */
    IMPORT_C TInt XPixels() const;

    /**
    * @return Y-Pixels.
    */
    IMPORT_C TInt YPixels() const;

    /**
    * Destructor.
    */
    ~CResolution();

    private:
    /**
    * C++ default constructor.
    */
    CResolution (TInt aXPixels, TInt aYPixels);

    private:
    /**
    * X-Pixels.
    */
    TInt    iXPixels;
    /**
    * Y-Pixels.
    */
    TInt    iYPixels;
    };

/**
*  @ref CAccessoryInfo provides accessory information i.e  ACCESSORY TYPE
*  @ref TAccessoryType and its connection status @ref TAccessoryState.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CAccessoryInfo):public CSysData
    {
    public:

    typedef	enum{
        /** Unknown. */
        EUnknown=-1,
        /** Headset */
        EHeadSet,
        /** Bluetooth headset */
        EBTHeadSet,
        /** Carkit */
        ECarKit,
        /** Bluetooth carkit */
        EBTCarKit
        }TAccessoryType;
    
    typedef enum{
        /** Accessory connected */
        EDisconnected,
        /** Accessory disconnected */
        EConnected
        }TAccessoryState;

    public:

    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CAccessoryInfo* NewL(const TAccPolGenericID& aGenericID, 
                                        TAccessoryState aAccState);

    /**
    * Destructor.
    */
    ~CAccessoryInfo();
    
    public:
    /**
    * @return ACCESSORY TYPE
    */
    IMPORT_C TInt AccessoryType() const;
    /**
    * @return Connection state.
    */
    IMPORT_C TInt ConnectionState() const;

    private:
    /**
    * C++ default constructor.
    */
    CAccessoryInfo(TAccessoryState aAccState);
    /**
    * Deduce accessory type from aGenericID.
    */
    void GetAccessoryProperty( const TAccPolGenericID& aGenericID );

    private:
    /**
    * Accessory type
    */
    TInt    iAccessoryType;
    /**
    * Connection State.
    */
    TInt    iConnectionState;
    };

/**
*  @ref CAccList provides access to read list of accessories.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CAccList): public CSysData
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CAccList* NewL();

    /**
    * @return @ref CAccessoryInfo client owns created instance.
    */
    IMPORT_C const CAccessoryInfo* operator[](TInt aIndex) const;

    /**
    * On return aAccInfo has new CAccessoryInfo instance ownership given to
    * client.
    */
    IMPORT_C TBool AtL(TInt aIndex,const CAccessoryInfo*& aAccInfo) const;

    /**
    * @return number of accessories in the list.
    */
    IMPORT_C TInt Count () const;

    /**
    * Destructor.
    */
    ~CAccList();
    private:

    /**
    * C++ default constructor.
    */
    CAccList();
    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL();
    
    private:
    /**
    * Accessory ID Array.
    */
    TAccPolGenericIDArray   iAccessories;

    /**
    * number of accessories.
    */
    TInt                    iCount;
    };

/**
*  @ref CStringData string data represented using this class.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CStringData): public CSysData
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    IMPORT_C static CStringData* NewL(const TDesC& aString);

    /**
    * On return aString contains string data.
    */
    IMPORT_C void StringData(TPtrC& aString) const;

    /**
    * Destructor.
    */
    ~CStringData();

    private:
    /**
    * C++ default constructor.
    */
    CStringData();

    private:
    /**
    * String data.
    */
    HBufC*      iStringData;
    }; 

/**
*  @ref CVersion Major and Minor version information.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CVersion): public CSysData
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CVersion* NewL(TInt aMajor,TInt aMinor);

    /**
    * @return Manjor Version number.
    */
    IMPORT_C TInt MajorVersion() const;

    /**
    * @return Minor Version number.
    */
    IMPORT_C TInt MinorVersion() const;
    /**
    * Destructor.
    */
    ~CVersion();

    private:

    /**
    * C++ default constructor.
    */
    CVersion(TInt aMajor,TInt aMinor);

    private:
    /**
    * Major Version.
    */
    TInt    iMajorVersion;
    /**
    * Minor Version.
    */
    TInt    iMinorVersion;
    }; 

/**
*  @ref CConnectionInfo provides access to read connection information i.e Connection type,
* 	Access point ID, Network name and Access point name.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CConnectionInfo) : public CSysData
    {
    public:
    typedef enum{
        /** disconnected */
        EDisconnected,
        /** connected */
        EConnected
    }TConnectionState;
    
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    IMPORT_C static CConnectionInfo* NewL(TUint aConnId, TUint aIAPId,
                                            TInt aBearerType,
                                            TConnectionState aConnectStatus,
                                            const TDesC& aIAPName,
                                            const TDesC& aNetworkName,
                                            const TDesC& aConnectionName);

    /**
    * Destructor.
    */
    ~CConnectionInfo();

    /**
    * @return A new instance of this class object.
    */    
    CConnectionInfo* CopyL();

    public:
    TUint ConnectionId() const;

    IMPORT_C TUint IAPId() const;

    IMPORT_C TInt BearerType()const;

    IMPORT_C TPtrC IAPName() const;

    IMPORT_C TPtrC NetworkName() const;

    IMPORT_C TPtrC ConnectionName() const;

    IMPORT_C TConnectionState ConnectionState() const;

    void SetConnectionState(CConnectionInfo::TConnectionState aState);

    private:
    /**
    * C++ default constructor.
    */
    CConnectionInfo ();

    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL(TUint aConnId, TUint aIAPId,
                        TInt aBearerType,
                        TConnectionState aConnectStatus,
                        const TDesC& aIAPName,
                        const TDesC& aNetworkName,
                        const TDesC& aConnectionName);
    private:

    TUint                   iConnectionId;

    TConnectionState        iConnectStatus;

    TUint                   iIAPId;

    TInt                    iBearerType;

    HBufC*                  iIAPName;

    HBufC*                  iNetworkName;

    HBufC*                  iConnectionName;
    };

/**
*  @ref CConnectionList this class lists connections. provides access to 
*   each connection information.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CConnectionList) : public CSysData
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CConnectionList* NewL(
                    RPointerArray<CConnectionInfo>& aConnectionInfoArr);
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CConnectionList* NewLC(
                    RPointerArray<CConnectionInfo>& aConnectionInfoArr);
    /**
    * On return aConnectionInfo contains connection information. aConnectionInfo  
    * ownership not given to user.
    */
    IMPORT_C TBool At(TInt aIndex,const CConnectionInfo*& aConnectionInfo) const;

    /**
    * @return ConnectionInfo at index.
    */
    IMPORT_C const CConnectionInfo* operator[](TInt aIndex) const;
    /**
    * @return number of connections.
    */
    IMPORT_C TInt Count() const;

    /**
    * Destructor.
    */
    ~CConnectionList();
    
    private:
    /**
    * C++ default constructor.
    */
    CConnectionList();
    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL(RPointerArray<CConnectionInfo>& aConnectionInfoArr);
    
    private:
    // Pointer Array to hold list of connections.
    RPointerArray<CConnectionInfo> iConnectionInfoArray;
    // Number of Connections.
    TInt                            iCount;
    };

/**
*  @ref CNetworkInfo client interface to read network details ie, Network name,
*	network type, status, MCC (Mobile Country Code), MNC (Mobile Network Code),
*	LAC (Location Area Code) and CellID.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CNetworkInfo): public CSysData
    {
    public:

    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CNetworkInfo* NewL(RMobilePhone::TMobilePhoneNetworkInfoV1& aNetworkInfo,
                                    RMobilePhone::TMobilePhoneLocationAreaV1& aArea);

    /**
    * Destructor.
    */
    ~CNetworkInfo();
    
    public:
    /**
    * @return Network name.
    */
    IMPORT_C TPtrC NetworkName() const;
    /**
    * @return Network Mode.
    */		
    IMPORT_C TInt NetworkMode()const;
    /**
    * @return Network Status.
    */
    IMPORT_C TInt NetworkStatus() const;
    /**
    * @return MCC Mobile Country Code.
    */
    IMPORT_C TPtrC CountryCode() const;
    /**
    * @return MNC Mobile Network Code.
    */
    IMPORT_C TPtrC NetworkCode() const;
    /**
    * @return LAC Location Area Code.
    */
    IMPORT_C TUint LocationAreaCode() const;
    /**
    * @return CellID
    */
    IMPORT_C TUint CellId() const;
    /**
    * @return Identifier for validating LAC & CellID
    */
    IMPORT_C TBool ValidLocationAreaCode() const;

    private:
    /**
    * C++ default constructor.
    */
    CNetworkInfo(RMobilePhone::TMobilePhoneNetworkInfoV1& aNetworkInfo,
                    RMobilePhone::TMobilePhoneLocationAreaV1& aArea);
    private:
    //Network Information
    RMobilePhone::TMobilePhoneNetworkInfoV1  iNetworkInfo;
    //Location information.
    RMobilePhone::TMobilePhoneLocationAreaV1 iLAC;
    };

/**
*  @ref CLanguageList language list class
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CLanguageList): public CSysData
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CLanguageList* NewL();
    /**
    * @return Language Code.
    */
    IMPORT_C TInt operator[](TInt aIndex) const;
    /**
    * On return aEntry contains Language Code.
    */
    IMPORT_C TBool At(TInt aIndex, TInt& aEntry) const;
    /**
    * @return language count.
    */
    IMPORT_C TInt Count() const;

    /**
    * Destructor.
    */
    ~CLanguageList();

    private:
    /**
    * C++ default constructor.
    */
    CLanguageList();
    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL();

    private:
    /**
    * array consists of language codes.
    */
    RArray<TInt>    iLanguages;
    };

/**
*  @ref CDriveList drive list.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CDriveList): public CSysData
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CDriveList* NewL(TDriveList& aDrives);
    /**
    * @return drive number.
    */
    IMPORT_C TInt operator[](TInt aIndex) const;
    /**
    * On return aEntry contains drive number.
    */
    IMPORT_C TBool At(TInt aIndex, TInt& aEntry) const;
    /**
    * @return number of drives.
    */
    IMPORT_C TInt Count() const;

    /**
    * Destructor.
    */
    ~CDriveList();

    private:
    /**
    * C++ default constructor.
    */
    CDriveList();
    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL(TDriveList& aDrives);

    private:
    RArray<TInt>    iDrives;
    TInt            iCount;
    };

/**
*   @ref CDriveInfo details drive information ie, Drive name, Total space, 
*   Free space, Media type, critical free space and battery status.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CDriveInfo): public CSysData
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    IMPORT_C static CDriveInfo* NewL(TInt aDriveNumber, TInt aCriticalSpace=-1);

    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CDriveInfo* NewL(TInt aDriveNumber, TVolumeInfo& aVolumeInfo);

    /**
    * Destructor.
    */
    ~CDriveInfo();
    public:
    IMPORT_C TInt DriveNumber() const;
    IMPORT_C TInt CriticalSpace() const;
    IMPORT_C TInt MediaType() const;
    IMPORT_C TInt64 TotalSpace() const;
    IMPORT_C TInt64 FreeSpace() const;
    IMPORT_C void DriveName(TPtrC& aDriveName) const;
    IMPORT_C TInt BatteryState() const;

    private:
    /**
    * C++ default constructor.
    */
    CDriveInfo(TInt aDrvNumber,TInt aCriticalSpace);
    /**
    * C++ default constructor.
    */
    CDriveInfo(TInt aDrvNumber,TVolumeInfo& aVolumeInfo);
    /**
    * Symbian 2nd phase constructor.
    */
    void ConstructL();

    private:
    TInt            iDrvNumber;
    TVolumeInfo     iVolumeInfo;
    TInt            iVolumeInfoValid;
    TInt            iCriticalSpace;
    };

/**
*  @ref CStringList list of strings
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CStringList): public CSysData
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CStringList* NewL(CDesCArray*& aDesArray);
    /**
    * @return string data.
    */
    IMPORT_C TPtrC operator[](TInt aIndex) const;
    /**
    * @On return aEntry consists of string data.
    */
    IMPORT_C TBool At(TInt aIndex, TPtrC& aEntry) const;
    /**
    * @return number of strings.
    */		
    IMPORT_C TInt Count() const;
    /**
    * Destructor.
    */
    ~CStringList();

    private:
    /**
    * C++ default constructor.
    */
    CStringList(CDesCArray*& aDesArray);
    private:
    CDesCArray*     iDesArray;
    TInt            iCount;
    };


#endif __SYSINFO_H__
