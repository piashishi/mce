/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  
*
*/

#include <e32const.h>
#include <cppunit/TestSuite.h>
#include "CMceComSessionTest.h"
#include "CMceComAudioStreamTest.h"


#ifdef _BullseyeCoverage
GLDEF_C int __stdcall __E32Dll(void*, unsigned, void*)
	{
	return(KErrNone);
	}
#else
#ifndef EKA2
// Starting point of the DLL (Removed in EKA2) 
GLDEF_C TInt E32Dll(TDllReason)
	{
	return(KErrNone);
	}
#endif
#endif _BullseyeCoverage



// Exactly one exported function returning the suite of 
// test functions for the test runner in the framework.
// (Always needed)
//
EXPORT_C MTest* CreateTestL ()
	{
    CTestSuite *suite = CTestSuite::NewL(_L8("MceCommonTestSuite"));
    
	suite->addTestL( CMceComSessionTest::suiteL() );
	suite->addTestL( CMceComAudioStreamTest::suiteL() );
	return suite;	
	}
