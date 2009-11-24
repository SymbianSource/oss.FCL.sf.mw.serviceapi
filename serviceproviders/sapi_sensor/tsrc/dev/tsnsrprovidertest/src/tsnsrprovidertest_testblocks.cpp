/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include <liwservicehandler.h>
#include <liwbufferextension.h>


#include "tsnsrprovidertest.h"
#include "txmlconvertor.h"

#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>

#include "tsnsrprovidertestobserver.h"
#include "txmlconvertor.h"
_LIT8(KErrorCode,"ErrorCode");




void CProviderTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Csapi_getheader:RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CProviderTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
       
         ENTRY( "CheckInputArgumentType", CProviderTest::CheckInputArgumentType ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }




 // -----------------------------------------------------------------------------
// CAppManagerTest:CheckInputArgumentType
// 
// -----------------------------------------------------------------------------
//
TInt CProviderTest::CheckInputArgumentType( CStifItemParser& aItem  )
    {
    
    __UHEAP_MARK;
 	TPtrC16 serice16;
 	TPtrC16 Interface16;
 	TPtrC16 command16;
 	TInt servicecmdpptions;
 	TPtrC16 callback;
 	TPtrC16 nextcmd;	
 	
 	TInt expected;
 	TInt err;
    CProviderObserver* callbackobj = NULL;
 		
 	TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail
 	
    
   do
   {
    aItem.GetNextString(serice16);
 	aItem.GetNextString(Interface16);
 	aItem.GetNextString(command16);
 	aItem.GetNextInt(servicecmdpptions);
 	aItem.GetNextString(callback);
 	
 
    
 	
    iLog->Log(_L("read varibale "));  
            
  /*-------------------------------------------------------------------------------------------*/
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);//1
    
    if ( iServiceHandler ) 
        iLog->Log(_L("Got Service Handler "));  
    else
        iLog->Log(_L("Didn't get service handler"));  

    
    //Take the Interface name and provider from cfg file
    TBuf8<30> interface8;
    TBuf8<30> service8;
    interface8.Copy(Interface16);
    service8.Copy(serice16);
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,interface8,service8);
    iLog->Log(_L("Create criterai Item"));
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);//2

        
    RCriteriaArray critArray;
    iLog->Log(_L("Append in Crit"));
    critArray.AppendL(crit);
    CleanupClosePushL(critArray);//3

    iServiceHandler->AttachL(critArray);
    
    
    iLog->Log(_L("Creating Output"));
    CLiwGenericParamList* output = CLiwGenericParamList::NewL();
	CleanupStack::PushL(output);//4
	CLiwGenericParamList* input = CLiwGenericParamList::NewL();
	CleanupStack::PushL(input);//5

    iLog->Log(_L("call Service cmd L"));
    iServiceHandler->ExecuteServiceCmdL(*crit, *input, *output);

    iLog->Log(_L("Service cmdl is over"));
    
    // Create the Instance of SAPI class and the Input Param and output Param
    TInt pos = 0;
    MLiwInterface* Interface = NULL;
    output->FindFirst(pos,interface8 );
    if(pos != KErrNotFound)
        {
        Interface = (*output)[pos].Value().AsInterface();
        }
    output->Reset();

    CleanupClosePushL(*Interface);//6
    iLog->Log(_L("got Interface"));
    input->Reset();
  

  if (FillInputParmaeterList( aItem, input) == KErrNone )
    {
    //Call Service 
    //PrintInputParameterList(input);
    TBuf8<30> command8;
    command8.Copy(command16);  
     
     if(callback.CompareF(_L("NULL"))==0)
        {
        //without call back 
        Interface->ExecuteCmdL(command8,*input,*output,servicecmdpptions, NULL);
        
        }
     else
        
        {
         //need to change the observer  
         callbackobj = CProviderObserver::NewL(); 
         //CleanupStack::PushL( callbackobj); 
         Interface->ExecuteCmdL(command8,*input,*output,servicecmdpptions, callbackobj); 
         //CleanupStack::PopAndDestroy( );
        }

    aItem.GetNextInt(expected);
    const TLiwGenericParam* p= NULL;
    p = output->FindFirst(pos, KErrorCode); // Finding Error Code
    if(p)
        {
     	err = p->Value().AsTInt32();
     	
     	if(err == 0 )
     	    {
     	     // Requested Accepted by the provider
     	     if( (callback != NULL) && (KLiwOptASyncronous == servicecmdpptions) )
     	        {
     	         // need to wait for callback 
     	        CActiveSchedulerWait* wait = new CActiveSchedulerWait();
                CleanupStack::PushL( wait);
                callbackobj->SetWait( wait );
                wait->Start();
     	        CleanupStack::PopAndDestroy();//Active Wait Scheduler	
     	        }
     	     
     	    }
     	
     	input->Reset();
     	output->Reset();
    	iLog->Log(_L("Got Error Code "));
            
        if(expected != err)
		    {
		    result = KErrGeneral;	
		    }
        }
     else
        result = KErrNone;    
    }  
  else
    {
        //Input Parameter List is not properly entered in Cfg file
        PrintInputParameterList(input);
        result = KErrGeneral;
    }
    
   output->Reset();
   input->Reset();	
   delete callbackobj;
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );
   CleanupStack::PopAndDestroy( );

	__UHEAP_MARKEND;
	if( result )		
		return result;
	

   aItem.GetNextString(nextcmd);	
	
   }while( nextcmd.CompareF(_L("Done") ) != 0);   
 
 return result;
   }
	 
       




TInt CProviderTest::FillInputParmaeterList( CStifItemParser& aItem , CLiwGenericParamList* input  )     
    
{
 
    TInt intValue;
    TPtrC16 value16;
    TBuf8<40> value8;
    TLiwVariant value;
    TLiwGenericParam valueParam;
	TBuf8<40> next8 ;
	TPtrC next16;
 	TPtrC16 dataType;
     
    aItem.GetNextString(next16);               
    while( next16.CompareF(_L("Finish"))!= 0)
        {
        aItem.GetNextString(dataType);
        //Convert variable name into 8 bit key
        next8.Copy(next16);
  
      	if(dataType.CompareF(_L("Int") )== 0)
       		{
       	    //Value should be Integer 
       	    aItem.GetNextInt(intValue);
       	    value.SetL((TInt32)intValue);
            valueParam.SetNameAndValueL(next8, value);
	        input->AppendL(valueParam);
	        value.Reset();
	        valueParam.Reset();
      		}
 
        else if ( dataType.CompareF(_L("String") ) == 0)
        	{
             //Value should be 8 bit
             aItem.GetNextString(value16);
             value8.Copy(value16);
       		 value.SetL(value8);
             valueParam.SetNameAndValueL(next8, value);
	         input->AppendL(valueParam); 
	         value.Reset();
	         valueParam.Reset();
        	}
        else if ( dataType.CompareF(_L("UnicodeString") ) == 0)
        	{
        	 //Value should be 16 bit string
        	 aItem.GetNextString(value16);
             value.SetL(value16);
             valueParam.SetNameAndValueL(next8, value);
	         input->AppendL(valueParam); 
	         value.Reset();
	         valueParam.Reset();
        	}
        else if ( dataType.CompareF(_L("Map")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultMap *map = CLiwDefaultMap::NewL();
        	value.SetL(map);
        	valueParam.SetNameAndValueL(next8, value);
            input->AppendL(valueParam);
            map->DecRef();
            value.Reset();
            valueParam.Reset();
            
            if( FillMap(aItem,map) !=KErrNone)
                return KErrGeneral; 
    	
        	}
        else if ( dataType.CompareF(_L("List")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultList *list = CLiwDefaultList::NewL();
        	value.SetL(list);
        	valueParam.SetNameAndValueL(next8, value);
            input->AppendL(valueParam);
            list->DecRef();
            value.Reset();
            valueParam.Reset();
            
            if( FillList(aItem,list) !=KErrNone)
                return KErrGeneral; 
        	}
        else
        	{
            return KErrGeneral;
        	}
       aItem.GetNextString(next16);
       }//While loop 
    
       
    return KErrNone;

}
    




TInt CProviderTest::FillMap( CStifItemParser& aItem , CLiwDefaultMap* aMap  )     
    
{
 
    TInt intValue;
    TPtrC16 value16;
    TBuf8<40> value8;
    TLiwVariant value;
   	TBuf8<40> next8 ;
	TPtrC next16;
 	TPtrC16 dataType;
     
    aItem.GetNextString(next16);               
    while( next16.CompareF(_L("End"))!= 0)
        {
        aItem.GetNextString(dataType);
        //Convert variable name into 8 bit key
        next8.Copy(next16);
        
  	
      	if(dataType.CompareF(_L("Int") )== 0)
       		{
       	    //Value should be Integer 
       	    aItem.GetNextInt(intValue);
       	    value.SetL((TInt32)intValue);
       	    aMap->InsertL(next8,value);
       	    value.Reset();
      		}

      	else if(dataType.CompareF(_L("Bool") )== 0)
       		{
       	    //Value should be Integer 
       	    aItem.GetNextInt(intValue);
       	    value.SetL((TBool)intValue);
       	    aMap->InsertL(next8,value);
       	    value.Reset();
      		}

      	else if(dataType.CompareF(_L("UInt") )== 0)
       		{
       	    //Value should be Integer 
       	    aItem.GetNextInt(intValue);
       	    value.SetL((TUint)intValue);
       	    aMap->InsertL(next8,value);
       	    value.Reset();
      		}
 
        else if ( dataType.CompareF(_L("String") ) == 0)
        	{
            //Value should be 8 bit
            aItem.GetNextString(value16);
            value8.Copy(value16);
       		value.SetL(value8);
            aMap->InsertL(next8,value);
            value.Reset();
        	}
        else if ( dataType.CompareF(_L("UnicodeString") ) == 0)
        	{
        	//Value should be 16 bit string
        	aItem.GetNextString(value16);
            value.SetL(value16);
            aMap->InsertL(next8,value);
            value.Reset();
        	}
        else if ( dataType.CompareF(_L("Map")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultMap *map = CLiwDefaultMap::NewL();
        	value.SetL(map);
        	aMap->InsertL(next8,value);
            map->DecRef();
            value.Reset();
            
            if( FillMap(aItem,map) !=KErrNone)
                return KErrGeneral; 
    	
        	}
        else if ( dataType.CompareF(_L("List")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultList *list = CLiwDefaultList::NewL();
        	value.SetL(list);
        	aMap->InsertL(next8,value);
            list->DecRef();
            value.Reset();
            
            
            if( FillList(aItem,list) !=KErrNone)
                return KErrGeneral; 
        	}
        else
        	{
            return KErrGeneral;
        	}
       aItem.GetNextString(next16);
       }//While loop 
    
       
    return KErrNone;

}
   
   
   
TInt CProviderTest::FillList( CStifItemParser& aItem , CLiwDefaultList* aList  )     
    
{
 
    TInt intValue;
    TPtrC16 value16;
    TBuf8<40> value8;
    TLiwVariant value;
   	TBuf8<40> next8 ;
	TPtrC next16;
 	TPtrC16 dataType;
     
    aItem.GetNextString(dataType);               
    while( dataType.CompareF(_L("End"))!= 0)
        {
        //aItem.GetNextString(dataType);
       
      	if(dataType.CompareF(_L("Int") )== 0)
       		{
       	    //Value should be Integer 
       	    aItem.GetNextInt(intValue);
       	    value.SetL((TInt32)intValue);
       	    aList->AppendL(value);
       	    value.Reset();
      		}
 
        else if ( dataType.CompareF(_L("String") ) == 0)
        	{
            //Value should be 8 bit
            aItem.GetNextString(value16);
            value8.Copy(value16);
       		value.SetL(value8);
            aList->AppendL(value);
            value.Reset();
        	}
        else if ( dataType.CompareF(_L("UnicodeString") ) == 0)
        	{
        	//Value should be 16 bit string
        	aItem.GetNextString(value16);
            value.SetL(value16);
            aList->AppendL(value);
            value.Reset();
        	}
        else if ( dataType.CompareF(_L("Map")) == 0)
        	{
        	//Value should be map
        	CLiwDefaultMap *map = CLiwDefaultMap::NewL();
        	value.SetL(map);
        	aList->AppendL(value);
            map->DecRef();
            value.Reset();
            
            if( FillMap(aItem,map) !=KErrNone)
                return KErrGeneral; 
    	
        	}
        else if ( dataType.CompareF(_L("List")) == 0)
        	{
        	//Value should be List
          	CLiwDefaultList *list = CLiwDefaultList::NewL();
        	value.SetL(list);
        	aList->AppendL(value);
            list->DecRef();
            value.Reset();
            
            if( FillList(aItem,list) !=KErrNone)
                return KErrGeneral; 
        	
        	}
        else
        	{
            return KErrGeneral;
        	}
       aItem.GetNextString(dataType);
       }//While loop 
    
       
    return KErrNone;

}
    
    
void CProviderTest::PrintInputParameterList( CLiwGenericParamList* input  ) 
{
    
 // Show the Input List
 RFs fs;
 RFile file;  
 User::LeaveIfError(fs.Connect());
 
 CleanupClosePushL(fs);//1
 TInt errfile=0;
 TEntry entry;
        			
        			
        			
 if( fs.Entry(_L("c:\\Data\\Provider\\"),entry) != KErrNone)
    {
    TInt ret = fs.MkDir(_L("c:\\Data\\Provider\\")); 
    }
        			
 TBuf<100> flname(_L("c:\\Data\\Provider\\InputList.xml"));

 errfile =file.Replace(fs,flname, EFileWrite | EFileStreamText); 
 CleanupClosePushL(file);//2
 
 
/*------------------------------------------------------------------------------*/
 //Generate Xml file 
 TPtrC filebuf;

 
 CXmlConvertor* convertor = CXmlConvertor::NewL();
 CleanupStack::PushL(convertor);
 convertor->BuildOutputTreeL(*input,filebuf);
 
 HBufC8* heapBuffer = HBufC8::NewL(filebuf.Length());
 TPtr8  filebuf8(heapBuffer->Des());
 filebuf8.Copy(filebuf);
 
 file.Write(filebuf8);
 
 delete heapBuffer;
 CleanupStack::PopAndDestroy(); 
 
/*------------------------------------------------------------------------------*/ 
 

 CleanupStack::PopAndDestroy();//File   1
 CleanupStack::PopAndDestroy();//File Session  2       		   
}





//Output parameter processing

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
