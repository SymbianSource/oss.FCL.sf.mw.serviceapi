/*
* ==============================================================================
*  Copyright (c) 2007 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

This readme describes the limitations for executing Calendar SAPI test cases on emulator.

Calendar Test cases doesnot work on emulator if its started in "TEXTSHELL" Mode. 
The problem is due to the Calendar server dependency on Alarm Server. In "TextShell" mode
the Alarm Server is not active, so Calendar server doesnot work. Till we get solution to 
this problem all the test cases should be executed in normal Mode.

Note: This prblem is only on emulator testing. Everything works fine on Hardware.

