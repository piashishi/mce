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
#include "ut_cmcecomavsink.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComAvSink* UT_CMceComAvSink::NewL()
    {
    UT_CMceComAvSink* self = UT_CMceComAvSink::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComAvSink* UT_CMceComAvSink::NewLC()
    {
    UT_CMceComAvSink* self = new( ELeave ) UT_CMceComAvSink();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComAvSink::~UT_CMceComAvSink()
    {
    }

// Default constructor
UT_CMceComAvSink::UT_CMceComAvSink()
    {
    }

// Second phase construct
void UT_CMceComAvSink::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComAvSink::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    } 

void UT_CMceComAvSink::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_CMceComAvSink::UT_CMceComAvSink_InternalizeFlatLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_ExternalizeFlatLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_EventReceivedLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_CloneLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_UpdateLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_ServesProxyClientL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_AddProxyClientLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_RemoveProxyClientL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_MccTypeL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_InitParamLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_PrepareLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_ClientEnableLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_ClientDisableLL()
    {
    }

void UT_CMceComAvSink::UT_CMceComAvSink_SetParameterLL()
    {
    }


	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComAvSink,
    "CMceComAvSink tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComAvSink",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComAvSink",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComAvSink",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_EventReceivedLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComAvSink",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_CloneLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComAvSink",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_UpdateLL, Teardown)

EUNIT_TEST (
    "ServesProxyClient test",
    "CMceComAvSink",
    "ServesProxyClient",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_ServesProxyClientL, Teardown)

EUNIT_TEST (
    "AddProxyClientL test",
    "CMceComAvSink",
    "AddProxyClientL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_AddProxyClientLL, Teardown)

EUNIT_TEST (
    "RemoveProxyClient test",
    "CMceComAvSink",
    "RemoveProxyClient",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_RemoveProxyClientL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComAvSink",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_MccTypeL, Teardown)

EUNIT_TEST (
    "InitParamL test",
    "CMceComAvSink",
    "InitParamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_InitParamLL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComAvSink",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_PrepareLL, Teardown)

EUNIT_TEST (
    "ClientEnableL test",
    "CMceComAvSink",
    "ClientEnableL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_ClientEnableLL, Teardown)

EUNIT_TEST (
    "ClientDisableL test",
    "CMceComAvSink",
    "ClientDisableL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_ClientDisableLL, Teardown)

EUNIT_TEST (
    "SetParameterL test",
    "CMceComAvSink",
    "SetParameterL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvSink_SetParameterLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
