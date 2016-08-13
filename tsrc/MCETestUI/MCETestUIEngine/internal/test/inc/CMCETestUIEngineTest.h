//
// CMCETestUIEngineTest.h
//
// Copyright (c) 2005 Nokia Corporation. All rights reserved.
//

#ifndef __CMCETESTUIENGINETEST_H__
#define __CMCETESTUIENGINETEST_H__

#include <cppunit/TestCase.h>
#include "CMCETestUIEngine.h"


class CMCETestUIEngineTest : public CTestCase
	{
public:

	// A function to collect and return a suite of tests
    static MTest* suiteL ();

	// Allocate the resources for one test function
    void setUpL ();

	// Free the resources reserved in setUpL()
	void tearDown ();

protected:

	// Own test functions that use assertions and may leave:
	void CreationTestL();
	
private:

	// The object to be tested as a member:
	CMCETestUIEngine* iEngine;
	
	};

#endif // __CMCETESTUIENGINETEST_H__
