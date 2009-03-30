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
* Description:   This Class provides information of the packages installed on 
*                the phone by user.
*
*/



#include "pkginfo.h"
#include "installpkgiterator.h"


// -----------------------------------------------------------------------------
// CInstallPkgIterator::NewL
// Returns the instance of CInstallPkgIterator class.
// -----------------------------------------------------------------------------
CInstallPkgIterator* CInstallPkgIterator::NewL()
	{
	CInstallPkgIterator* self = new(ELeave)CInstallPkgIterator();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CInstallPkgIterator::CInstallPkgIterator
// C++ Constructor
// -----------------------------------------------------------------------------
CInstallPkgIterator::CInstallPkgIterator():iJavaReg(NULL),iCurrent(0)
	{
	
		
	}

// -----------------------------------------------------------------------------
// CInstallPkgIterator::ConstructL
// Two-phase constructor
// -----------------------------------------------------------------------------
	
void CInstallPkgIterator::ConstructL()
	{
	
	User::LeaveIfError( iSisRegSession.Connect() );
	
	iJavaReg = Java::CJavaRegistry::NewL();
	
	//Getting the uids of all native application
	iSisRegSession.InstalledUidsL(iSisxUids);
	
	
	//Getting the uids of non-native means java application
	iJavaReg->GetRegistryEntryUidsL( Java::EMidp2MidletSuite ,iJavaUids );
		
	}

// -----------------------------------------------------------------------------
// CInstallPkgIterator::~CInstallPkgIterator
// Destructor
// -----------------------------------------------------------------------------

CInstallPkgIterator::~CInstallPkgIterator()
	{

		iSisxUids.Reset();
			
		iJavaUids.Reset();

	    iSisRegSession.Close();
	    
	    delete iJavaReg;
		    
	}
	

// -----------------------------------------------------------------------------
// CInstallPkgIterator::NextL
// It gives the instance of MInfoMap which contains the information about next package 
// iterator list.
// -----------------------------------------------------------------------------
	
 TBool CInstallPkgIterator::NextL( MInfoMap*& aInfo )
	{
	
	TBool flg = EFalse;
	
    //First it will return all native application
	if(  iSisxUids.Count() > iCurrent )
		{
    	CPkgInfo* pkg =  CPkgInfo::NewL(&iSisRegSession);
		
		CleanupStack::PushL(pkg);
		
	    while(flg == EFalse)
	    	{
	    	pkg->SetEntryL( iSisxUids[iCurrent], flg );	
	    	iCurrent++;
	    	
	    	if(iCurrent >= iSisxUids.Count() )
	    		break;
	    	}
		CleanupStack::Pop(pkg);

		if(flg == EFalse)
			{
			delete pkg;
			pkg = NULL;
			}
		else
			{
			aInfo = pkg;	
			}	
	
		}
		
		
	//After finishing native application it will return non-native application	
	 if( ( ( iJavaUids.Count() + iSisxUids.Count()-1 )>= iCurrent) && (flg ==EFalse))
		{
		
		CPkgInfo* pkg = CPkgInfo::NewL(iJavaReg);
		
		CleanupStack::PushL(pkg);



	    while(flg == EFalse)
	    	{

	    	pkg->SetEntryL( iJavaUids[iCurrent-iSisxUids.Count()], flg );	
	    	iCurrent++;

	    	if(iCurrent >= ( iJavaUids.Count() + iSisxUids.Count()-1 ) )
	        	break;
	    	
	    	}

		
		CleanupStack::Pop(pkg);
		if(flg == EFalse)
			{
			delete pkg;
		
			}
		else
			{
			aInfo = pkg;	
			}	
		}	


		return flg;	
	}
// -----------------------------------------------------------------------------
// CInstallPkgIterator::Reset
// It resets the iterator
// -----------------------------------------------------------------------------

void CInstallPkgIterator::Reset()
{

 iCurrent = 0;
	
}	


