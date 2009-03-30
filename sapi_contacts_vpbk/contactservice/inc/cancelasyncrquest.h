/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  an interface to handle cancel of async requests
*
*/


/**
 * An abstract class which is to be implemented by all observers to support cancel.
 */

#ifndef M_CANCELASYNC_H
#define M_CANCELASYNC_H

class MCancelAsync
{
	public:
   /**
	* To be implemented by all the observers for supporting 
	* cancel operation customised to each of the observer 
	* classes.
	*/
	
	virtual void Cancel()=0;
	
};


#endif //M_CANCELASYNC