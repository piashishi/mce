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
#include "ut_cmcecommediasink.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComMediaSink* UT_CMceComMediaSink::NewL()
    {
    UT_CMceComMediaSink* self = UT_CMceComMediaSink::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComMediaSink* UT_CMceComMediaSink::NewLC()
    {
    UT_CMceComMediaSink* self = new( ELeave ) UT_CMceComMediaSink();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComMediaSink::~UT_CMceComMediaSink()
    {
    }

// Default constructor
UT_CMceComMediaSink::UT_CMceComMediaSink()
    {
    }

// Second phase construct
void UT_CMceComMediaSink::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComMediaSink::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComMediaSink::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_InternalizeFlatLL()
    {
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_ExternalizeFlatLL()
    {
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_EventReceivedLL()
    {
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_UpdateLL()
    {
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_CloneLL()
    {
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_UseRTCPL()
    {
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_TypeL()
    {
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_FactoryL()
    {
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_SetSSRCL()
    {
    }

void UT_CMceComMediaSink::UT_CMceComMediaSink_MccTypeL()
    {
    }


	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComMediaSink,
    "CMceComMediaSink tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComMediaSink",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComMediaSink",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComMediaSink",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_EventReceivedLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComMediaSink",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_UpdateLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComMediaSink",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_CloneLL, Teardown)

EUNIT_TEST (
    "UseRTCP test",
    "CMceComMediaSink",
    "UseRTCP",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_UseRTCPL, Teardown)

EUNIT_TEST (
    "Type test",
    "CMceComMediaSink",
    "Type",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_TypeL, Teardown)

EUNIT_TEST (
    "Factory test",
    "CMceComMediaSink",
    "Factory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_FactoryL, Teardown)

EUNIT_TEST (
    "SetSSRC test",
    "CMceComMediaSink",
    "SetSSRC",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_SetSSRCL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComMediaSink",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSink_MccTypeL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
