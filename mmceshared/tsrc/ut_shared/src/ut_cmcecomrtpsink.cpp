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




//  CLASS HEADER
#include "ut_cmcecomrtpsink.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComRtpSink* UT_CMceComRtpSink::NewL()
    {
    UT_CMceComRtpSink* self = UT_CMceComRtpSink::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComRtpSink* UT_CMceComRtpSink::NewLC()
    {
    UT_CMceComRtpSink* self = new( ELeave ) UT_CMceComRtpSink();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComRtpSink::~UT_CMceComRtpSink()
    {
    }

// Default constructor
UT_CMceComRtpSink::UT_CMceComRtpSink()
    {
    }

// Second phase construct
void UT_CMceComRtpSink::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComRtpSink::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComRtpSink::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_InternalizeFlatLL()
    {
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_ExternalizeFlatLL()
    {
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_EventReceivedLL()
    {
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_CloneLL()
    {
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_UpdateLL()
    {
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_UseRTCPL()
    {
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_SetSSRCL()
    {
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_IsEnabledL()
    {
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_MccTypeL()
    {
    }

void UT_CMceComRtpSink::UT_CMceComRtpSink_PrepareLL()
    {
    }




	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComRtpSink,
    "CMceComRtpSink tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComRtpSink",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComRtpSink",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComRtpSink",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_EventReceivedLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComRtpSink",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_CloneLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComRtpSink",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_UpdateLL, Teardown)

EUNIT_TEST (
    "UseRTCP test",
    "CMceComRtpSink",
    "UseRTCP",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_UseRTCPL, Teardown)

EUNIT_TEST (
    "SetSSRC test",
    "CMceComRtpSink",
    "SetSSRC",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_SetSSRCL, Teardown)

EUNIT_TEST (
    "IsEnabled test",
    "CMceComRtpSink",
    "IsEnabled",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_IsEnabledL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComRtpSink",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_MccTypeL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComRtpSink",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSink_PrepareLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
