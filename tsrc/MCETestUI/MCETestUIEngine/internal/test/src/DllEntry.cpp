//
// DllEntry.cpp
//
// Copyright (c) 2005 Nokia Corporation. All rights reserved.
//


#include <cppunit/TestSuite.h>
#include "CMCETestUIEngineTest.h"

#ifndef EKA2
// Starting point of the DLL (Removed in EKA2)
GLDEF_C TInt E32Dll(TDllReason)
	{
	return(KErrNone);
	}
#endif


// Exactly one exported function returning the suite of 
// test functions for the test runner in the framework (Always needed).
//
EXPORT_C MTest* CreateTestL ()
	{
	// Always use NewL (Do not use NewLC) !!!
    CTestSuite *suite = CTestSuite::NewL(_L8("MCETestUIEngineTests"));
			
	suite->addTestL(CMCETestUIEngineTest::suiteL());
		
	return suite;
	}
