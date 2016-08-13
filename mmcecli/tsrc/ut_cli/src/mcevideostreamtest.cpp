/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32def.h>
#include <e32base.h>
#include <digia/eunit/EUnitMacros.h>
#include "mcevideostreamtest.h"
#include "mcevideostream.h"
#include "mcetestdefs.h"


// ----------------------------------------------------------------------------
// CMceVideoStreamTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceVideoStreamTest::setUpL()
    {
    iVideoStream = CMceVideoStream::NewL();
    }

// ----------------------------------------------------------------------------
// CMceVideoStreamTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceVideoStreamTest::tearDown()
    {
    delete iVideoStream;
    }

// ----------------------------------------------------------------------------
// CMceVideoStreamTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceVideoStreamTest::suiteL()
    {
    CMceVideoStreamTest* suite = new CMceVideoStreamTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }
    
EUNIT_BEGIN_TEST_TABLE( 
    CMceVideoStreamTest,
    "CMceVideoStreamTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceVideoStreamTest", setUpL, ConstructionTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceVideoStreamTest:: ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceVideoStreamTest::ConstructionTestL()
    {    
    }
