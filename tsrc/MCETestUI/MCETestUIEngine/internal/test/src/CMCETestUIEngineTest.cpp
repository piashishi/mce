/*
* =============================================================================
*  Name          : CMCETestUIEngineTest.cpp
*  Part of       : MCETestUIEngine
*  Version       : 1.0
*
*  Copyright (c) 2005 Nokia Corporation. 
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation. 
* =============================================================================
*/

#include "CMCETestUIEngineTest.h"
#include "CMCETestUIEngine.h"
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>


//
// An own static function to collect the test functions into one 
// suite of tests. The framework will run the tests and free the
// memory allocated for the test suite.
// 

MTest* CMCETestUIEngineTest::suiteL ()
	{
	// Always use NewL (Do not use NewLC) !!!
    CTestSuite *suite = CTestSuite::NewL(_L8("CWPSWISAdapterTest"));

	suite->addTestL(
		CTestCaller<CMCETestUIEngineTest>::NewL( _L8( "CreationTestL" ),
    			&CreationTestL ) );
	return suite;	
	}

//
// SetUp and TearDown
//

void CMCETestUIEngineTest::setUpL ()
	{
	iEngine = CMCETestUIEngine::NewL();
	}


void CMCETestUIEngineTest::tearDown ()
	{
	delete iEngine;
	}


//
// Own test functions.
//
// The framework will do for a test function:
//
// setUpL();
// TRAPD(leaveCode, 'myTestFunction()');
// "Report leave error or assertion failure for 'myTestFunction()'".
// tearDown();
//

// NOTE!!!
// If you allocate something from the heap, remember to Push it to
// the CleanupStack! Any assertion may fail and leave.
// After that you have a memory leak if your object is not
// Pushed to CleanupStack!


void CMCETestUIEngineTest::CreationTestL()
	{
    assertL( iEngine != NULL );
	}
