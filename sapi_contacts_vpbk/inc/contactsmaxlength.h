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
* Description:  Max lengths defined based on phonebook engine observation
               : as virtual phone book does'nt ve any information about Max length
               : these are temporary limits as they can change once the 
               : fix from vpbk is available. 
               
*
*/


#ifndef C_CCONTACTSMAXLENGTH_H
#define C_CCONTACTSMAXLENGTH_H

/*
Constant literals for sim database. 
*/

_LIT(KSimDataBaseOne,"sim://global_adn");

/*
PREFIX, SUFFIX
*/
const TInt  KMaxLengthTen = 10;

/*
LASTNAME for SIM
*/
const TInt KMaLengthFourteen = 14;
/*
ADDRPOGEN, ADDRPOHOME, ADDRPOWORK, ADDRPOSTCODEGEN, ADDRPOSTCODEHOME, ADDRPOSTCODEWORK 
*/
const TInt  KMaxLengthTwenty = 20;

/*
These are the fields which ve 48 as max lentghs
MOBILEPHONEGEN, MOBILEPHONEHOME, MOBILEPHONEWORK, LANDPHONEGEN, LANDPHONEHOME, LANDPHONEWORK, 
VIDEONUMBERHOME, VIDEONUMBERWORK, VIDEONUMBERGEN, CARPHONE , PAGENUMBER, FAXNUMBERHOME, FAXNUMBERWORK, FAXNUMBERGEN
*/
const TInt  KMaxLengthFourtyEight = 48;

/*
These are the fields which ve 50 as max lentghs
LASTNAME, SECONDNAME, FIRSTNAME, DEPARTMENT, JOBTITLE, ASSTPHONE, CHILDREN, COMPANYNAME, MIDDLENAME,
MIDDLENAME, ADDRSTREETGEN, ADDRSTREETHOME, ADDRSTREETWORK, ADDRLOCALGEN, ADDRLOCALHOME, ADDRLOCALWORK, ADDRREGIONGEN, ADDRREGIONHOME, 
ADDRREGIONWORK, ADDRCOUNTRYGEN, ADDRCOUNTRYHOME, ADDRCOUNTRYWORK, ASSTNAME, SPOUSE.
*/
const TInt  KMaxLengthFifty = 50;

/*
DTMFSTRING
*/
const TInt  KMaxLengthSixty  = 60;

/*
SIP, PUSHTOTALK, VOIPHOME, VOIPWORK, VOIPGEN
*/
const TInt  KMaxLengthHundred  = 100;

/*
EMAILGEN, EMAILWORK, EMAILHOME
*/
const TInt  KMaxLengthOneHundredAndFifty = 150;
/*
ADDRLABELHOME, ADDRLABELGEN, ADDRLABELWORK 
*/
const TInt  KMaxLengthTwoHundredAndFifty = 250;

/*
LOCPRIVACY, RINGTONE
*/
const TInt  KMaxLengthTwoHundredAndFiftySix = 256;

/*
URLWORK, URLHOME, URLGEN, NOTE
*/
const TInt  KMaxLengthThousand = 1000;

#endif