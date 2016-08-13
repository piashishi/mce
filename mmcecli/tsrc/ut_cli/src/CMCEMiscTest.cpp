/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
#include "CMCEMiscTest.h"
#include "mcetestdefs.h"
#include "mceevents.h"

  

// ----------------------------------------------------------------------------
// CMCEMiscTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMCEMiscTest::setUpL()
    {

    
    }

// ----------------------------------------------------------------------------
// CMCEMiscTest::tearDown
// ----------------------------------------------------------------------------
//
void CMCEMiscTest::tearDown()
    {
    
    }

// ----------------------------------------------------------------------------
// CMCEMiscTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMCEMiscTest::suiteL()
    {
    CMCEMiscTest* suite = new CMCEMiscTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMCEMiscTest,
    "CMCEMiscTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMCEMiscTest", setUpL, MiscTestsL, tearDown )
EUNIT_END_TEST_TABLE 



// ----------------------------------------------------------------------------
// CMCEMiscTest::MiscTestsL
// ----------------------------------------------------------------------------
//
void CMCEMiscTest::MiscTestsL()
    {
    
    TMceComEmptyEventHandler handler;
    CMceComMediaSink* sink = NULL;
    CMceComMediaSource* source = NULL;
    CMceComRtpSink* rtpSink = NULL;
    TMceComEvent* event = NULL;
    
    TRAPD( error1, handler.HandleL( *sink, *event) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( error1 )
    EUNIT_ASSERT( error1 != KErrNone );
    TRAPD( error2, handler.HandleL( *source, *event) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( error2 )
    EUNIT_ASSERT( error2 != KErrNone );
    TRAPD( error3, handler.HandleL( *rtpSink, *event) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( error3 )
    EUNIT_ASSERT( error3 != KErrNone );    
    }
