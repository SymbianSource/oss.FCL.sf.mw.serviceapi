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
* Description:  CLandmarkDatabaseIterable class implementation
*
*/

#include <liwgenericparam.h>
#include <EPos_CPosLmDatabaseManager.h>
#include "clandmarkdatabaseiterable.h"
#include "landmarkliwparams.hrh"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CDatabaseIterable* CDatabaseIterable::NewL( CDesCArray* aDbList )
  {
  CDatabaseIterable* self = new (ELeave) CDatabaseIterable(aDbList);
  CleanupStack::PushL(self);
  self->ConstructL();
  CleanupStack::Pop(self);
  return self;
  }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CDatabaseIterable::CDatabaseIterable( CDesCArray* aDbList )
                 :iDatabaseList(aDbList),
                  iIndex(0)                  
  {
  iCount = iDatabaseList->Count();
  }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
CDatabaseIterable::~CDatabaseIterable()
  {
  delete iDatabaseList;
  delete iDbManager;
  }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CDatabaseIterable::ConstructL()
  {
  iDbManager = CPosLmDatabaseManager::NewL();
  }
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
TBool CDatabaseIterable::NextL( TLiwVariant& aEntry )
  {

  if ( iIndex < iCount )
    {
    TPtrC DbUri = (*iDatabaseList)[iIndex];
    TBuf<KMaxDriveLength> drive(KNullDesC);
    drive.FillZ();
    HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewLC(DbUri);
    iDbManager->GetDatabaseInfoL(*info);
    CLiwMap* database = CLiwDefaultMap::NewL();
    CleanupClosePushL (*database );
    const TPosLmDatabaseSettings settings = info->Settings();
    TPtrC dbname = settings.DatabaseName();
    database->InsertL(KDbUri,TLiwVariant(DbUri));
    database->InsertL(KDbName,TLiwVariant(dbname));
    database->InsertL(KDbProtocol,TLiwVariant(info->Protocol()));
    database->InsertL(KDbActive,TLiwVariant(info->IsDefault()));
    drive.Append(info->DatabaseDrive());
    database->InsertL(KDbSize,TLiwVariant((TInt32)info->Size()));
    database->InsertL(KDbDrive,TLiwVariant(drive));
    database->InsertL(KDbMedia,TLiwVariant((TInt32)info->DatabaseMedia()));
    aEntry.SetL(database);
    CleanupStack::PopAndDestroy (database );
    CleanupStack::PopAndDestroy (info );
    iIndex++;
    return ETrue;
    }
  else
    return EFalse;
  }
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CDatabaseIterable::Reset()
  {
  iIndex = 0;
  }

//end of file
