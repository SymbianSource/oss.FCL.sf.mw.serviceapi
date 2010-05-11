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




// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <LiwServicehandler.h>
#include "landmarks_inputparams.h"

using namespace LIW;

_LIT(KLandmark, "Landmark" );
_LIT(KCategory, "Category" );
_LIT(KDatabase, "Database" );
_LIT(KMultiple, "Multiple" );
_LIT(KDefault, "Default" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Clandmarks_inputparams::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Clandmarks_inputparams::Delete() 
    {
    iLandmarkIf->Close();
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewLC(1, _L8("IDataSource"), _L8("Service.Landmarks"));
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    RCriteriaArray a;
    CleanupClosePushL(a);
    a.AppendL(crit);
    iServiceHandler->DetachL(a);
    CleanupStack::PopAndDestroy(&a);
    CleanupStack::PopAndDestroy(crit);
    delete iServiceHandler;
    }

void Clandmarks_inputparams::InitL()
{
    iServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewLC(1, _L8("IDataSource"), _L8("Service.Landmarks"));
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    RCriteriaArray a;
    CleanupClosePushL(a);
    a.AppendL(crit);
    iServiceHandler->AttachL(a);
    iServiceHandler->ExecuteServiceCmdL(*crit,inList,outList);
    CleanupStack::PopAndDestroy(&a);
    CleanupStack::PopAndDestroy(crit);
  
    //retrieve the interface handle
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("IDataSource")); 
    
    if( outParam )
        {
        iLandmarkIf = outParam->Value().AsInterface();
        }
    
    inList.Reset();
    outList.Reset();
}
// -----------------------------------------------------------------------------
// Clandmarks_inputparams::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //ENTRY( "Example", Clandmarks_inputparams::ExampleL ),
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove
        ENTRY( "GetList", Clandmarks_inputparams::GetListL ),
        ENTRY( "Add", Clandmarks_inputparams::AddL ),
        ENTRY( "Delete", Clandmarks_inputparams::DeleteL ),
        ENTRY( "Import", Clandmarks_inputparams::ImportL ),
        ENTRY( "Export", Clandmarks_inputparams::ExportL ),
        ENTRY( "Organise", Clandmarks_inputparams::OrganiseL ),
        ENTRY( "Cancel", Clandmarks_inputparams::CancelL ),
        ENTRY( "Liw", Clandmarks_inputparams::LiwL ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Clandmarks_inputparams::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::HandleNotifyL(
        TInt aCmdId,
        TInt aEventId,
        CLiwGenericParamList& aEventParamList,
        const CLiwGenericParamList& aInParamList)
    {
    return KErrNone;
    }
// -----------------------------------------------------------------------------
// Clandmarks_inputparams::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::GetListL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Klandmarks_inputparams, "landmarks_inputparams" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Klandmarks_inputparams, KExample );
    // Print to log file
    iLog->Log( KExample );
    TInt i = 0;
    TOperation oper = NoOp;
    TType type = NoType;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Klandmarks_inputparams, 
                                KParam, i, &string );
        if( string == KMultiple )
        {
            oper = Multiple;
        }
        if( string == KDefault )
        {
            oper = Default;
        }
        if( string == KLandmark )
        {
            type = Landmark;
        }
        if( string == KCategory )
        {
            type = Category;
        }
        if( string == KDatabase )
        {
            type = Database;
        }
        i++;
        }
    TInt err = KErrGeneral;
    
    switch( oper )
    {
    case Default:
        {
            switch( type )
            {
            case Landmark: err = GetLandmarkDefL();
                           break;
            case Category: //err = GetCategoryDefL();
                           break;
            case Database: //err = GetDatabaseDefL();
                           break;
            }
        }
        break;
    default:
        {
            switch( type )
            {
            case Landmark: err = GetLandmarkL();
                           break;
            case Category: err = GetCategoryL();
                           break;
            case Database: err = GetDatabaseL();
                           break;
            }
        }
    }
    return err;

    }

TInt Clandmarks_inputparams::GetLandmarkL()
{
	//__UHEAP_MARK;
	InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();
    
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Landmark"))));
    
    //Filter Optional
    CLiwDefaultMap* filter = CLiwDefaultMap::NewL();
    CleanupStack::PushL(filter);
    
    filter->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
    filter->InsertL(_L8("MaximumMatches"),TLiwVariant((TInt32)10));
    filter->InsertL(_L8("PreviousMatchesOnly"),TLiwVariant((TBool)FALSE));
    filter->InsertL(_L8("LandmarkName"),TLiwVariant(_L("A*")));
    filter->InsertL(_L8("LandmarkDesc"),TLiwVariant(_L("D?")));
    
    CLiwDefaultMap* position = CLiwDefaultMap::NewL();
    CleanupStack::PushL(position);
    position->InsertL(_L8("Latitude"),TLiwVariant(14.23));
    position->InsertL(_L8("Longitude"),TLiwVariant(85.31));
    filter->InsertL(_L8("LandmarkPosition"),TLiwVariant(position));
    
    
    filter->InsertL(_L8("CoverageRadiusOption"),TLiwVariant((TBool)FALSE));
    filter->InsertL(_L8("CategoryName"),TLiwVariant(_L("Hotel")));
    
    CLiwDefaultMap* area = CLiwDefaultMap::NewL();
    CleanupStack::PushL(area);
    area->InsertL(_L8("NorthLatitude"),TLiwVariant(12.12));
    area->InsertL(_L8("SouthLatitude"),TLiwVariant(11.13));
    area->InsertL(_L8("EastLongitude"),TLiwVariant(14.14));
    area->InsertL(_L8("WestLongitude"),TLiwVariant(13.15));
    filter->InsertL(_L8("BoundedArea"),TLiwVariant(area));
    
    
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(filter)));
    
    //Sort Optional
    CLiwDefaultMap* sort = CLiwDefaultMap::NewL();
    CleanupStack::PushL(sort);
    
    sort->InsertL(_L8("Key"),TLiwVariant(_L("LandmarkName")));
    sort->InsertL(_L8("Order"),TLiwVariant(_L("Ascending")));
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(sort)));
    
    
    
    iLandmarkIf->ExecuteCmdL(_L8("getList"),inList,outList,0,0);  
    
    
    CleanupStack::Pop(sort);
    sort->DecRef();  
    CleanupStack::Pop(area);
    area->DecRef();
    CleanupStack::Pop(position);
    position->DecRef();  
    CleanupStack::Pop(filter);
    filter->DecRef();    
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    Delete();
    //__UHEAP_MARKEND;
    return index;
}

TInt Clandmarks_inputparams::GetLandmarkDefL()
{
    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();
    
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Landmark"))));
    
    //Filter Optional
    CLiwDefaultMap* filter = CLiwDefaultMap::NewL();
    CleanupStack::PushL(filter);
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(filter)));
    
    
    iLandmarkIf->ExecuteCmdL(_L8("GetList"),inList,outList,0,0);  
    
    CleanupStack::Pop(filter);
    filter->DecRef();
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    if( !index )
    {
        outParam = outList.FindFirst(index,_L8("ReturnValue")); 
        CLiwIterable* iter = outParam->Value().AsIterable();
        CheckAscending(Landmark,iter);
    }
    inList.Reset();
    outList.Reset();
    Delete();
    //__UHEAP_MARKEND;
    return index;
}

TInt Clandmarks_inputparams::GetCategoryL()
{
    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();

    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Category"))));
    
    //Filter Optional
    CLiwDefaultMap* filter = CLiwDefaultMap::NewL();
    CleanupStack::PushL(filter);
    
    filter->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
    filter->InsertL(_L8("MaximumMatches"),TLiwVariant((TInt32)10));
    filter->InsertL(_L8("PreviousMatchesOnly"),TLiwVariant((TBool)FALSE));
    filter->InsertL(_L8("CategoryName"),TLiwVariant(_L("A*")));

    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(filter)));
    
    //Sort Optional
    CLiwDefaultMap* sort = CLiwDefaultMap::NewL();
    CleanupStack::PushL(sort);
    
    sort->InsertL(_L8("Key"),TLiwVariant(_L("CategoryName")));
    sort->InsertL(_L8("Order"),TLiwVariant(_L("Ascending")));
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(sort)));

    iLandmarkIf->ExecuteCmdL(_L8("GetList"),inList,outList,0,0);  
        
    CleanupStack::Pop(sort);
    sort->DecRef();
    CleanupStack::Pop(filter);
    filter->DecRef();
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    
    Delete();
    //__UHEAP_MARKEND;
    return index;
}

TInt Clandmarks_inputparams::GetDatabaseL()
{
    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();
    ////__UHEAP_MARK;
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Database"))));
    
    //Filter Optional
    CLiwDefaultMap* filter = CLiwDefaultMap::NewL();
    CleanupStack::PushL(filter);
    
    filter->InsertL(_L8("DbProtocol"),TLiwVariant(_L("file")));
    
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(filter)));
    
    //Sort Optional
    CLiwDefaultMap* sort = CLiwDefaultMap::NewL();
    CleanupStack::PushL(sort);
    
    sort->InsertL(_L8("Key"),TLiwVariant(_L("DatabaseURI")));
    sort->InsertL(_L8("Order"),TLiwVariant(_L("Ascending")));
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(sort)));
    
    
    
    iLandmarkIf->ExecuteCmdL(_L8("GetList"),inList,outList,0,0);  
    
    CleanupStack::Pop(sort);
    sort->DecRef();
    CleanupStack::Pop(filter);
    filter->DecRef();
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    Delete();
    //__UHEAP_MARKEND;
    return index;
}
/// -----------------------------------------------------------------------------
// Clandmarks_inputparams::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::AddL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Klandmarks_inputparams, "landmarks_inputparams" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Klandmarks_inputparams, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TBool isMultiple = EFalse;
    TBool isLandmark = EFalse;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Klandmarks_inputparams, 
                                KParam, i, &string );
        if( string == KMultiple )
        {
            isMultiple = ETrue;
        }
        if( isMultiple && string == KLandmark )
        {
            isLandmark = ETrue;
        }
        i++;
        }

    TInt err = KErrGeneral;
    
    if( string == KLandmark )
    {
        err = AddLandmarkL();
    }
    if( string == KCategory )
    {
        err = AddCategoryL();
    }
    
    TInt32 count = 0;
    if( isMultiple )
    {
        TLex lexstring(string);
        lexstring.Val(count);
        if( isLandmark )
        {
            err = AddLmL(count);
        }
        else
        {
            err = AddCatL(count);
        }
    }
    return err;

    }

TInt Clandmarks_inputparams::AddLmL( TInt32 count )
{
    //__UHEAP_MARK;
    InitL();
    TInt err = KErrGeneral;
    while( count )
    {
    	err = KErrGeneral;
        CLiwGenericParamList& inList = iServiceHandler->InParamListL();
        CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
        inList.Reset();
        outList.Reset();    
        //Type mandatory
        inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Landmark"))));
        
        //Data mandatory
        CLiwDefaultMap* data = CLiwDefaultMap::NewL();
        CleanupStack::PushL(data);
        
        data->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
        TBuf<256> lmName;
        lmName.Copy(_L("Lm"));
        TInt32 append = User::NTickCount();
        lmName.AppendNum(append);
        data->InsertL(_L8("LandmarkName"),TLiwVariant(lmName));
        
        data->InsertL(_L8("LandmarkDesc"),TLiwVariant(_L("Space")));
        
        CLiwDefaultMap* position = CLiwDefaultMap::NewL();
        CleanupStack::PushL(position);
        position->InsertL(_L8("Latitude"),TLiwVariant(14.23));
        position->InsertL(_L8("Longitude"),TLiwVariant(85.31));
        position->InsertL(_L8("Altitude"),TLiwVariant(8.31));
        position->InsertL(_L8("HAccuracy"),TLiwVariant(8.51));
        position->InsertL(_L8("VAccuracy"),TLiwVariant(0.85));
        position->InsertL(_L8("TStamp"),TLiwVariant(853.1));
        data->InsertL(_L8("LandmarkPosition"),TLiwVariant(position));
        
        data->InsertL(_L8("CoverageRadius"),TLiwVariant(50.23));
                
        CLiwDefaultMap* fields = CLiwDefaultMap::NewL();
        CleanupStack::PushL(fields);
        fields->InsertL(_L8("Street"),TLiwVariant(_L("street")));
        fields->InsertL(_L8("BuildingName"),TLiwVariant(_L("Building")));
        fields->InsertL(_L8("District"),TLiwVariant(_L("district")));
        fields->InsertL(_L8("City"),TLiwVariant(_L("city")));
        fields->InsertL(_L8("AreaCode"),TLiwVariant(_L("area")));
        fields->InsertL(_L8("Telephone"),TLiwVariant(_L("1234")));
        fields->InsertL(_L8("Country"),TLiwVariant(_L("in")));
        
        data->InsertL(_L8("LandmarkFields"),TLiwVariant(fields));
    
        inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(data)));
        
        iLandmarkIf->ExecuteCmdL(_L8("Add"),inList,outList,0,0);  
        
        
        CleanupStack::Pop(fields);
        fields->DecRef();
        CleanupStack::Pop(position);
        position->DecRef();
        CleanupStack::Pop(data);
        data->DecRef(); 
        
        TInt index = 0;
        const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
        
        if( outParam )
            {
            err = outParam->Value().AsTInt32();
            }
        inList.Reset();
        outList.Reset();
        if( err )
        {
            User::Leave(err);
        }
        
        --count;
    }
    // Delete resources allocated from test methods
    Delete();
    //__UHEAP_MARKEND;
    return err;

}
TInt Clandmarks_inputparams::AddCatL( TInt32 count )
{
    return KErrNone;
}
TInt Clandmarks_inputparams::AddLandmarkL()
{
    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();    
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Landmark"))));
    
    //Data mandatory
    CLiwDefaultMap* data = CLiwDefaultMap::NewL();
    CleanupStack::PushL(data);
    
    data->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
    data->InsertL(_L8("LandmarkName"),TLiwVariant(_L("Lm")));
    /*
    CLiwDefaultList* category = CLiwDefaultList::NewL();
    CleanupStack::PushL(category);
    category->AppendL(TLiwVariant(_L("0")));
    data->InsertL(_L8("CategoryInfo"),TLiwVariant((category)));*/
    
    data->InsertL(_L8("LandmarkDesc"),TLiwVariant(_L("Space")));
    
    CLiwDefaultMap* position = CLiwDefaultMap::NewL();
    CleanupStack::PushL(position);
    position->InsertL(_L8("Latitude"),TLiwVariant(14.23));
    position->InsertL(_L8("Longitude"),TLiwVariant(85.31));
    position->InsertL(_L8("Altitude"),TLiwVariant(8.31));
    position->InsertL(_L8("HAccuracy"),TLiwVariant(8.51));
    position->InsertL(_L8("VAccuracy"),TLiwVariant(0.85));
    position->InsertL(_L8("TStamp"),TLiwVariant(853.1));
    data->InsertL(_L8("LandmarkPosition"),TLiwVariant(position));
    
    data->InsertL(_L8("CoverageRadius"),TLiwVariant(50.23));
    data->InsertL(_L8("IconFile"),TLiwVariant(_L("try.mbm")));
    data->InsertL(_L8("IconIndex"),TLiwVariant((TInt32)0));
    data->InsertL(_L8("IconMaskIndex"),TLiwVariant((TInt32)0));
    
    CLiwDefaultMap* fields = CLiwDefaultMap::NewL();
    CleanupStack::PushL(fields);
    fields->InsertL(_L8("Street"),TLiwVariant(_L("street")));
    fields->InsertL(_L8("BuildingName"),TLiwVariant(_L("Building")));
    fields->InsertL(_L8("District"),TLiwVariant(_L("district")));
    fields->InsertL(_L8("City"),TLiwVariant(_L("city")));
    fields->InsertL(_L8("AreaCode"),TLiwVariant(_L("area")));
    fields->InsertL(_L8("Telephone"),TLiwVariant(_L("1234")));
    fields->InsertL(_L8("Country"),TLiwVariant(_L("in")));
    
    data->InsertL(_L8("LandmarkFields"),TLiwVariant(fields));

    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(data)));
    
    iLandmarkIf->ExecuteCmdL(_L8("Add"),inList,outList,0,0);  
    
    CleanupStack::Pop(fields);
    fields->DecRef();
    CleanupStack::Pop(position);
    position->DecRef();
    CleanupStack::Pop(data);
    data->DecRef();   
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    // Delete resources allocated from test methods
    
    if( index == 1012 )
    {
        index = 0;
    }
    Delete();
    //__UHEAP_MARKEND;
    if( index == 1002 )
    {
        index = 0;
    }
    return index;
}
TInt Clandmarks_inputparams::AddCategoryL()
{
    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();

    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Category"))));
    
    //Data mandatory
    CLiwDefaultMap* data = CLiwDefaultMap::NewL();
    CleanupStack::PushL(data);
    
    data->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
    //unique category name
    TBuf<256> catName;
    catName.Copy(_L("Cat"));
    TInt32 append = User::NTickCount();
    catName.AppendNum(append);
    data->InsertL(_L8("CategoryName"),TLiwVariant(catName));
    data->InsertL(_L8("IconFile"),TLiwVariant(_L("try.mbm")));
    data->InsertL(_L8("IconIndex"),TLiwVariant((TInt32)0));
    data->InsertL(_L8("IconMaskIndex"),TLiwVariant((TInt32)0));

    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(data)));
    
    iLandmarkIf->ExecuteCmdL(_L8("Add"),inList,outList,0,0);  
    
    CleanupStack::Pop(data);
    data->DecRef();  
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    // Delete resources allocated from test methods
    Delete();
    //__UHEAP_MARKEND;
    return index;
}
// -----------------------------------------------------------------------------
// Clandmarks_inputparams::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::DeleteL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Klandmarks_inputparams, "landmarks_inputparams" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Klandmarks_inputparams, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Klandmarks_inputparams, 
                                KParam, i, &string );
        i++;
        }
    
    TInt err = KErrGeneral;
    
    if( string == KLandmark )
    {
        err = DeleteLandmarkL();
    }
    if( string == KCategory )
    {
        err = DeleteCategoryL();
    }
    return err;
    }

TInt Clandmarks_inputparams::DeleteLandmarkL()
{
    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();
    ////__UHEAP_MARK;
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Landmark"))));
    
    //Data mandatory
    CLiwDefaultMap* data = CLiwDefaultMap::NewL();
    CleanupStack::PushL(data);
    
    data->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
    data->InsertL(_L8("id"),TLiwVariant(_L("0")));

    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(data)));
    
    iLandmarkIf->ExecuteCmdL(_L8("Delete"),inList,outList,0,0);  
    
    CleanupStack::Pop(data);
    data->DecRef();  
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    Delete();
    //__UHEAP_MARKEND;
    return index;
}

TInt Clandmarks_inputparams::DeleteCategoryL()
{
    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();
    ////__UHEAP_MARK;
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Category"))));
    
    //Data mandatory
    CLiwDefaultMap* data = CLiwDefaultMap::NewL();
    CleanupStack::PushL(data);
    
    data->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
    data->InsertL(_L8("id"),TLiwVariant(_L("0")));

    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(data)));
    
    iLandmarkIf->ExecuteCmdL(_L8("Delete"),inList,outList,0,0);  
    
    CleanupStack::Pop(data);
    data->DecRef();  
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    Delete();
    //__UHEAP_MARKEND;
    return index;
}
// -----------------------------------------------------------------------------
// Clandmarks_inputparams::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::ImportL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Klandmarks_inputparams, "landmarks_inputparams" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Klandmarks_inputparams, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Klandmarks_inputparams, 
                                KParam, i, &string );
        i++;
        }

    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();
    ////__UHEAP_MARK;
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Landmark"))));
    
    //Data mandatory
    CLiwDefaultMap* data = CLiwDefaultMap::NewL();
    CleanupStack::PushL(data);
    
    data->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
    data->InsertL(_L8("SourceFile"),TLiwVariant(_L("c:\\file.lmx")));
    data->InsertL(_L8("MimeType"),TLiwVariant(_L("application/vnd.nokia.landmarkcollection+xml")));

    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(data)));
    
    iLandmarkIf->ExecuteCmdL(_L8("Import"),inList,outList,0,0);  
    
    CleanupStack::Pop(data);
    data->DecRef();  
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    Delete();
    //__UHEAP_MARKEND;
    if( index == 1012 )
    {
        index = 0;
    }
    return index;


    }

// -----------------------------------------------------------------------------
// Clandmarks_inputparams::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::ExportL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Klandmarks_inputparams, "landmarks_inputparams" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Klandmarks_inputparams, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Klandmarks_inputparams, 
                                KParam, i, &string );
        i++;
        }

    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();
    ////__UHEAP_MARK;
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Landmark"))));
    
    //Data mandatory
    CLiwDefaultMap* data = CLiwDefaultMap::NewL();
    CleanupStack::PushL(data);
    
    data->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
    TBuf<256> fileName;
    fileName.Copy(_L("Lm"));
    TInt32 append = User::NTickCount();
    fileName.AppendNum(append);
    data->InsertL(_L8("DestinationFile"),TLiwVariant(fileName));
    
    CLiwDefaultList* list = CLiwDefaultList::NewL();
    CleanupStack::PushL(list);
    list->AppendL(TLiwVariant(_L("0")));
    data->InsertL(_L8("IdList"),TLiwVariant(list));
    
    data->InsertL(_L8("MimeType"),TLiwVariant(_L("application/vnd.nokia.landmarkcollection+xml")));

    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(data)));
    
    iLandmarkIf->ExecuteCmdL(_L8("Export"),inList,outList,0,0);  
    
    CleanupStack::Pop(list);
    list->DecRef();  
    CleanupStack::Pop(data);
    data->DecRef();  
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    Delete();
    //__UHEAP_MARKEND;
    if( index == 1012 )
    {
        index = 0;
    }
    return index;

    }

// -----------------------------------------------------------------------------
// Clandmarks_inputparams::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::OrganiseL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Klandmarks_inputparams, "landmarks_inputparams" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Klandmarks_inputparams, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Klandmarks_inputparams, 
                                KParam, i, &string );
        i++;
        }
    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();
    ////__UHEAP_MARK;
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Landmark"))));
    
    //Data mandatory
    CLiwDefaultMap* data = CLiwDefaultMap::NewL();
    CleanupStack::PushL(data);
    
    data->InsertL(_L8("DatabaseURI"),TLiwVariant(_L("c:eposlm.ldb")));
    data->InsertL(_L8("id"),TLiwVariant(_L("0")));
    
    CLiwDefaultList* list = CLiwDefaultList::NewL();
    CleanupStack::PushL(list);
    list->AppendL(TLiwVariant(_L("0")));
    data->InsertL(_L8("IdList"),TLiwVariant(list));
    
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(data)));
    
    //OperationType mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(_L("Associate"))));
    
    iLandmarkIf->ExecuteCmdL(_L8("Organise"),inList,outList,0,0);  
    
    CleanupStack::Pop(list);
    list->DecRef();  
    CleanupStack::Pop(data);
    data->DecRef();
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    Delete();
    //__UHEAP_MARKEND;
    if( index == 1012 )
    {
        index = 0;
    }
    return index;

    }

// -----------------------------------------------------------------------------
// Clandmarks_inputparams::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::CancelL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Klandmarks_inputparams, "landmarks_inputparams" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Klandmarks_inputparams, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Klandmarks_inputparams, 
                                KParam, i, &string );
        i++;
        }
    //__UHEAP_MARK;
    InitL();
    CLiwGenericParamList& inList = iServiceHandler->InParamListL();
    CLiwGenericParamList& outList = iServiceHandler->OutParamListL();
    inList.Reset();
    outList.Reset();
    ////__UHEAP_MARK;
    //Type mandatory
    inList.AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant((TInt32)0)));
    
    iLandmarkIf->ExecuteCmdL(_L8("Cancel"),inList,outList,KLiwOptCancel,0);  
    
    
    TInt index = 0;
    const TLiwGenericParam* outParam = outList.FindFirst(index,_L8("ErrorCode")); 
    
    if( outParam )
        {
        index = outParam->Value().AsTInt32();
        }
    inList.Reset();
    outList.Reset();
    Delete();
    //__UHEAP_MARKEND;
    return index;

    }

void OperationsL(CLiwMap* map)
{
    TLiwVariant var;
    map->FindL(KNullDesC8,var);
    //User::Leave(0);
    var.Reset();
}

// -----------------------------------------------------------------------------
// Clandmarks_inputparams::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Clandmarks_inputparams::LiwL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Klandmarks_inputparams, "landmarks_inputparams" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Klandmarks_inputparams, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Klandmarks_inputparams, 
                                KParam, i, &string );
        i++;
        }
    //__UHEAP_MARK;
    _LIT(KName,"Name");
    TLiwVariant variant(KName());
    CLiwGenericParamList* param = CLiwGenericParamList::NewLC();
    CLiwMap* map = CLiwDefaultMap::NewL();
    CleanupStack::PushL(map);
    map->InsertL(KNullDesC8,variant);
    TRAP_IGNORE(OperationsL(map));
    param->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(map)));
     
    CleanupStack::Pop(map);
    map->DecRef();
    TLiwGenericParam outParam;
    param->AtL(0,outParam);
    const CLiwMap* outMap = outParam.Value().AsMap();
    CleanupStack::PopAndDestroy(param);
    //__UHEAP_MARKEND;
    return KErrNone;
    }

TInt Clandmarks_inputparams::CheckAscending(TType aType, CLiwIterable* aIter)
    {
    HBufC* curr = NULL;
    HBufC* prev = NULL;
    TLiwVariant var;
    while( aIter->NextL(var) )
    {
        const CLiwMap* map = var.AsMap();
        TLiwVariant variant;
        if( map->FindL(_L8("LandmarkName"),variant ) )
        {
            curr = variant.AsDes().AllocL();
            
        }
        
        if( prev )
        {
            TInt32 val = curr->Compare(*prev);
            if( val < 0 )
	        {
	           delete curr;
	           delete prev;
	            return KErrGeneral;
	        }
	        delete prev;	        
        }
        prev = curr;
        variant.Reset();
        var.Reset();
    }
   return 0;    
    }
    
TInt Clandmarks_inputparams::CheckDescending(TType aType, CLiwIterable* aIter)
    {
    HBufC* curr = NULL;
    HBufC* prev = NULL;
    TLiwVariant var;
    while( aIter->NextL(var) )
    {
        const CLiwMap* map = var.AsMap();
        TLiwVariant variant;
        if( map->FindL(_L8("LandmarkName"),variant ) )
        {
            curr = variant.AsDes().AllocL();
            
        }
        
        if( prev )
        {
            TInt32 val = curr->Compare(*prev);
            if( val > 0 )
	        {
	           delete curr;
	           delete prev;
	            return KErrGeneral;
	        }
	        delete prev;	        
        }
        prev = curr;
        variant.Reset();
        var.Reset();
    }
   return 0;    
    }
// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  [End of File] - Do not remove
