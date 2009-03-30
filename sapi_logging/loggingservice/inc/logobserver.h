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
* Description:  includes observer methods on the logdatabase.
*
*/



#ifndef LOGOBSERVER_H
#define LOGOBSERVER_H

/**
 *Forward Declarations
 */
 class CLogClient ;
 class CBase ;
 class MLogClientChangeObserver ;
 class RFs ;
 
/**
 * Observer Class Abstraction
 */
 
class CLogObserver : public CBase 
    {
    public :
    
        /**
        * Two phase constructors
        */
        static CLogObserver* NewL() ;
        static CLogObserver* NewLC() ;
        
        /**
        * ConstructL method, to construct the clients
        */
        void ConstructL() ;
        
        /**
        * SetObserver methods, sets the observer for the 
        * changes happening in the database
        */
        
        void SetObserverL(MLogClientChangeObserver* aObserver) ;
        
        /**
        * Default Destructors
        */
        
        ~CLogObserver() ;
        
        protected :
        
        /**
        * Protected Constructor
        */
        
        CLogObserver() ;
        
    private :
    
        /**
        * datamembers
        */
        RFs iFs ;
        CLogClient* iLogClient ;     
    };
#endif