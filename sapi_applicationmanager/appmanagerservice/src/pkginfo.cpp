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
* Description:  This Class provides information of Application installed on phone.
*				 				 
*
*/


#include <javaregistryentrytype.h>
#include <e32cmn.h>
#include "pkginfo.h"

_LIT(KHEXAdd,"0x");

_LIT(KSEPERATOR , ":");

_LIT(KEDRIVE,"E");

_LIT(KCDRIVE,"C");

 //(8*8) + (2 * 8) = 64 + 16 = 80 , 10 bytes + 1 = 11 bytes
const TInt KUidLength = 20;
// (1* 8) + (1 * 8) + (1* 8) = 24 , 3 bytes + 1 = 4 bytes
const TInt KVersionLength = 4;

const TInt KdriveLen = 1 ;

const TInt KDeriveE = 4;
// -----------------------------------------------------------------------------
// CAppInfo::NewL
// Returns the instance of CPkgInfo class.
// -----------------------------------------------------------------------------
CPkgInfo* CPkgInfo::NewL( Swi::RSisRegistrySession* aSisRegSession)
	{
	CPkgInfo* self = new(ELeave) CPkgInfo(aSisRegSession);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}


// -----------------------------------------------------------------------------
// CAppInfo::CPkgInfo
// C++ constructor
// -----------------------------------------------------------------------------
CPkgInfo::CPkgInfo( Swi::RSisRegistrySession* aSisRegSession):iSisRegSession(aSisRegSession)
	{
		
	}


// -----------------------------------------------------------------------------
// CAppInfo::NewL
// Returns the instance of CPkgInfo class.
// -----------------------------------------------------------------------------
CPkgInfo* CPkgInfo::NewL( Java::CJavaRegistry* aJavaReg)
	{
	CPkgInfo* self = new(ELeave) CPkgInfo(aJavaReg);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}
// -----------------------------------------------------------------------------
// CAppInfo::CPkgInfo
// C++ constructor
// -----------------------------------------------------------------------------
CPkgInfo::CPkgInfo(Java::CJavaRegistry* aJavaReg):iJavaReg(aJavaReg)
	{
		
	}

// -----------------------------------------------------------------------------
// CAppInfo::ConstructL
// Two-Phase constructor
// -----------------------------------------------------------------------------
void CPkgInfo::ConstructL()
	{
	iKeyArray =  new(ELeave) CDesC8ArraySeg( KArrayGranularity );
	//Inserting the Keys
	iKeyArray->AppendL(KPkgName);
	iKeyArray->AppendL(KUid);
	iKeyArray->AppendL(KVersion);
	iKeyArray->AppendL(KVendor);
	iKeyArray->AppendL(KDrive);
	
	for(TInt index = 0 ; index < iKeyArray->Count() ;index++)
		{
		iKeyValArray.AppendL(NULL);
		}
	
	}

// -----------------------------------------------------------------------------
// CAppInfo::~CPkgInfo
// Destructor
// -----------------------------------------------------------------------------
CPkgInfo::~CPkgInfo()
	{
	
	if(iKeyArray)
		{
		iKeyArray->Reset();
		delete 	iKeyArray;
		}
	

	iKeyValArray.ResetAndDestroy();


	iSisRegEntry.Close();

	if(iJavaRegEntry)	
		{
		delete iJavaRegEntry;	
		}

	iSisRegSession = NULL;

	iJavaReg = NULL; 
	}


// -----------------------------------------------------------------------------
// CAppInfo::AtL 
// This function gives the key value at a given index
// -----------------------------------------------------------------------------
TBool  CPkgInfo::AtL(TInt aIndex, TDes8& aKeyVal)	 
	{

	 if(0<= aIndex < iKeyArray->Count() )
		 {
		 aKeyVal.Copy((*iKeyArray)[aIndex]);
		 return ETrue;	
		 }
	 else
		 {
		 return EFalse;	
		 }
	}

// -----------------------------------------------------------------------------
// CAppInfo::Count 
// This function gives the number of keys
// -----------------------------------------------------------------------------
TInt CPkgInfo::Count()	const
	{
	return iKeyArray->Count();
	}

// -----------------------------------------------------------------------------
// CAppInfo::SetEntryL 
// This function sets the appropriate entry as per uid 
// -----------------------------------------------------------------------------
void CPkgInfo::SetEntryL(TUid aUid,TBool& aErrflg) 
	{
    
    //It will accept the UID and also validate (i.e if that application currently prsent or not)
	if( iJavaReg )
		{
		iJavaRegEntry = iJavaReg->RegistryEntryL(aUid);
	
		if( iJavaRegEntry )
			{
		aErrflg = (Java::EGeneralPackage <= iJavaRegEntry->Type()< Java::EGeneralApplication);
			if(aErrflg == EFalse)
			{
			delete iJavaRegEntry ;
			iJavaRegEntry = NULL ;				
				}
			}
		else
			{
			aErrflg = EFalse;
			}	
		}
	else 
		{

		User::LeaveIfError(iSisRegEntry.Open(*iSisRegSession,aUid));

		aErrflg = (iSisRegEntry.IsPresentL() && !iSisRegEntry.IsInRomL());
		if( aErrflg == EFalse )
			{
			iSisRegEntry.Close();				 	
			}
			 
		}
		
	}
		

// -----------------------------------------------------------------------------
// CAppInfo::FindL 
// This function finds the value as per key given in argument.
// -----------------------------------------------------------------------------
 TBool  CPkgInfo::FindL(const TDesC8& aKey, TPtrC& aVal)
	{
	TBool retValue = EFalse;
	if(iJavaReg)
		{
		retValue = GetJavaInfoL(aKey,aVal);	
	
		} // for iJavaRegEntry
	else 
		{
		
		retValue = GetSisxInfoL(aKey,aVal);
	}
	return retValue;
	}
	
// -----------------------------------------------------------------------------
// CPkgInfo::GetJavaInfo 
// Gives the value as per key input for java installed packages
// -----------------------------------------------------------------------------
TBool CPkgInfo::GetJavaInfoL(const TDesC8& aKey, TPtrC& aVal)	
	{
	TBool retVal = ETrue;
	TInt index = -1 ;
	
	if(aKey.CompareF(KPkgName)==KErrNone)
		{
		
		iKeyArray->Find(KPkgName,index);
		
		if(index >= 0)
			{
			if(NULL == iKeyValArray[index] ) 
				{
				// create heap object 

				HBufC* keyval = HBufC::NewL(iJavaRegEntry->Name().Length());
				
				TPtr val(keyval->Des());
				
				val.Append(iJavaRegEntry->Name());

			
				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do
			
				}

			aVal.Set(*iKeyValArray[index]); // Seting the TPtrC with the keyval in array

			}
		
		}
	else if(aKey.CompareF(KUid) == KErrNone)
		{
		

		iKeyArray->Find(KUid,index);
		
		if(index >= 0)
			{
			if(NULL == iKeyValArray[index]) 
				{
				// Taking buffer for manipulation

				HBufC* keyval = HBufC::NewL(KUidLength);
				
				TPtr val(keyval->Des());
				val.Append(KHEXAdd);
				val.AppendNum(iJavaRegEntry->Uid().iUid,EHex);



				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do

				}

			aVal.Set(*iKeyValArray[index]); // Seting the TPtrC with the keyval in array
				
			}

		
		}
	else if(aKey.CompareF(KVersion) == KErrNone)
		{
		
		iKeyArray->Find(KVersion,index);
		
		if(index >= 0)
			{
			if(NULL == iKeyValArray[index]) 
				{
				// Taking buffer for manipulation


				HBufC* keyval = HBufC::NewL(KVersionLength);
				TAppVersion ver = ((Java::CJavaRegistryPackageEntry*)iJavaRegEntry)->Version();
				
				TPtr val(keyval->Des());
				
				val.AppendNum(ver.iMajor);
				val.Append(KSEPERATOR);
				val.AppendNum(ver.iMinor);

				
				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do

				}

			aVal.Set(*iKeyValArray[index]); // Seting the TPtrC with the keyval in array
				
			}

		}
	else if(aKey.CompareF(KVendor) == KErrNone)
		{

		iKeyArray->Find(KVendor,index);
	
		if(index >= 0)	
			{
			if(NULL == iKeyValArray[index]) 
				{
				// Taking buffer for manipulation
				HBufC* keyval = HBufC::NewL(((Java::CJavaRegistryPackageEntry*)iJavaRegEntry)->Vendor().Length());
				
				TPtr val(keyval->Des());
				
				val.Append(((Java::CJavaRegistryPackageEntry*)iJavaRegEntry)->Vendor());

				
				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do

				}

			aVal.Set(*iKeyValArray[index]); // Seting the TPtrC with the keyval in array
				
			}




		}
	else if(aKey.CompareF(KDrive) == KErrNone)
		{

		iKeyArray->Find(KDrive,index);

		if(index >= 0)
			{
			if(NULL == iKeyValArray[index]) // chk the condition depend on how we initialise the array in constructor
				{
		
				HBufC* keyval = HBufC::NewL(KdriveLen);
				TPtr val(keyval->Des());
				
				
				TInt x = iJavaRegEntry->Drive();
				
				if(KDeriveE == x)
					{
					val.Append(KEDRIVE);	
					
					}
				else
					{
					val.Append(KCDRIVE);
					
					}
		
				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do
				}

			aVal.Set(*iKeyValArray[index]); // Seting the TPtrC with the keyval in array
				
			}

		}
	else
		{

		retVal = EFalse;
			
		}	

	return retVal; 
	
	}
	
// -----------------------------------------------------------------------------
// CPkgInfo::GetSisxInfo
// Gives the value as per key input for S60(Sisx) installed packages
// -----------------------------------------------------------------------------
TBool CPkgInfo::GetSisxInfoL(const TDesC8& aKey, TPtrC& aVal)	
	{
	TBool retVal= ETrue;
	TInt index = -1;


	if(aKey.CompareF(KPkgName)==KErrNone)
		{

		iKeyArray->Find(KPkgName,index);		
		
		if(index >= 0)
			{
			if(NULL == iKeyValArray[index]) 
				{

				HBufC* keyval = HBufC::NewL(iSisRegEntry.PackageNameL()->Length());

				TPtr val(keyval->Des());

				val.Append(*(iSisRegEntry.PackageNameL()));
							
				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do		
				
				}
			
			aVal.Set(*iKeyValArray[index]);
				
			}
		
		}
	else if(aKey.CompareF(KUid) == KErrNone)
		{

		iKeyArray->Find(KUid,index);		
		
		if(index >= 0)
			{
			if(NULL == iKeyValArray[index]) 
				{

				HBufC* keyval = HBufC::NewL(KUidLength);

				TPtr val(keyval->Des());

				val.Append(KHEXAdd);
				val.AppendNum(iSisRegEntry.UidL().iUid,EHex);			
				
			
				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do		
				
				}
			
			aVal.Set(*iKeyValArray[index]);
				
			}

		}
	else if(aKey.CompareF(KVersion) == KErrNone)
		{


		iKeyArray->Find(KVersion,index);		
		
		if(index >= 0)
			{
			if(NULL == iKeyValArray[index]) 
				{

				HBufC* keyval = HBufC::NewL(KVersionLength);

				TVersion ver = iSisRegEntry.VersionL();
				
				TPtr val(keyval->Des());

				val.Num(ver.iMajor);

				val.Append(KSEPERATOR);

				val.AppendNum(ver.iMinor);

				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do		
				
				}
			
			aVal.Set(*iKeyValArray[index]);
				
			}

		}
	else if(aKey.CompareF(KVendor) == KErrNone)	
		{


		iKeyArray->Find(KVendor,index);		
		
		if(index >= 0)
			{
			if(NULL == iKeyValArray[index]) 
				{
				HBufC* keyval = HBufC::NewL(iSisRegEntry.UniqueVendorNameL()->Length());

				TPtr val(keyval->Des());

				val.Append(*(iSisRegEntry.UniqueVendorNameL()));			
				
				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do		
				
				}
			
			aVal.Set(*iKeyValArray[index]);
				
			}

		}
	else if(aKey.CompareF(KDrive) == KErrNone)
		{
	
		iKeyArray->Find(KDrive,index);		

		if(index >= 0)
			{
			if(NULL == iKeyValArray[index]) 
				{

				HBufC* keyval = HBufC::NewL(KdriveLen);
				TPtr val(keyval->Des());

				if( iSisRegEntry.SelectedDriveL() == 'c' || iSisRegEntry.SelectedDriveL() == 'C' )
					{
					val.Append(KCDRIVE);
					}
				else 
					{
					RPointerArray<HBufC> files ;
					iSisRegEntry.FilesL(files);
					// Check the disk from files
					// if all have C, the software is installed to phone
					// else it is installed to memory card
					TInt count = files.Count();

					TInt allFilesInCZ = 0;
					for ( TInt index = 0; index < count; index++ )
						{
						TPtrC firstChar = files[index]->Des().Left(1);
						// Note here find the contents of file and see what we can get


						if ( ( firstChar.Compare( KDriveC ) == KErrNone ) || 
						     ( firstChar.Compare( KDrivec ) == KErrNone ) ||
						     ( firstChar.Compare( KDrivez ) == KErrNone ) ||
						     ( firstChar.Compare( KDriveZ ) == KErrNone ) )
							    {
							    allFilesInCZ++;
							    }    		    
						}  // for

					if ( allFilesInCZ == count )
						{
						// Phone memory
						val.Append(KCDRIVE);		   

						}
					else
						{
						// Memory card
						val.Append(KEDRIVE);		
						}
					files.Close();
					}

				
				iKeyValArray.Insert(keyval,index); // it can b made as leaving function so what to do		
				
				}


			aVal.Set(*iKeyValArray[index]);
				
			}

		}
	else
		{

		retVal = EFalse;				
		}	
			
	return retVal;	

		
	}
	
	


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
