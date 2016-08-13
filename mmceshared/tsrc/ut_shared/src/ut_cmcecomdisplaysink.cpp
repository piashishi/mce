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
#include "ut_cmcecomdisplaysink.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComDisplaySink* UT_CMceComDisplaySink::NewL()
    {
    UT_CMceComDisplaySink* self = UT_CMceComDisplaySink::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComDisplaySink* UT_CMceComDisplaySink::NewLC()
    {
    UT_CMceComDisplaySink* self = new( ELeave ) UT_CMceComDisplaySink();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComDisplaySink::~UT_CMceComDisplaySink()
    {
    }

// Default constructor
UT_CMceComDisplaySink::UT_CMceComDisplaySink()
    {
    }

// Second phase construct
void UT_CMceComDisplaySink::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComDisplaySink::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComDisplaySink::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_InternalizeFlatLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_ExternalizeFlatLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_EventReceivedLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_CloneLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_UpdateLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_CreateEndpointProxyLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_UsesEndpointProxyL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_DisplayRectL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_SetDisplayRectL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_ToRectL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_ToPointAndSizeL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_MccTypeL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_InitParamLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_DoInitParamLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_EnableLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_DisableLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_PrepareLL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_SetViewFinderL()
    {
    }

void UT_CMceComDisplaySink::UT_CMceComDisplaySink_MccParameterNameL()
    {
    }



	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComDisplaySink,
    "CMceComDisplaySink tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComDisplaySink",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComDisplaySink",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComDisplaySink",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_EventReceivedLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComDisplaySink",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_CloneLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComDisplaySink",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_UpdateLL, Teardown)

EUNIT_TEST (
    "CreateEndpointProxyL test",
    "CMceComDisplaySink",
    "CreateEndpointProxyL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_CreateEndpointProxyLL, Teardown)

EUNIT_TEST (
    "UsesEndpointProxy test",
    "CMceComDisplaySink",
    "UsesEndpointProxy",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_UsesEndpointProxyL, Teardown)

EUNIT_TEST (
    "DisplayRect test",
    "CMceComDisplaySink",
    "DisplayRect",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_DisplayRectL, Teardown)

EUNIT_TEST (
    "SetDisplayRect test",
    "CMceComDisplaySink",
    "SetDisplayRect",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_SetDisplayRectL, Teardown)

EUNIT_TEST (
    "ToRect test",
    "CMceComDisplaySink",
    "ToRect",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_ToRectL, Teardown)

EUNIT_TEST (
    "ToPointAndSize test",
    "CMceComDisplaySink",
    "ToPointAndSize",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_ToPointAndSizeL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComDisplaySink",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_MccTypeL, Teardown)

EUNIT_TEST (
    "InitParamL test",
    "CMceComDisplaySink",
    "InitParamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_InitParamLL, Teardown)

EUNIT_TEST (
    "DoInitParamL test",
    "CMceComDisplaySink",
    "DoInitParamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_DoInitParamLL, Teardown)

EUNIT_TEST (
    "EnableL test",
    "CMceComDisplaySink",
    "EnableL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_EnableLL, Teardown)

EUNIT_TEST (
    "DisableL test",
    "CMceComDisplaySink",
    "DisableL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_DisableLL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComDisplaySink",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_PrepareLL, Teardown)

EUNIT_TEST (
    "SetViewFinder test",
    "CMceComDisplaySink",
    "SetViewFinder",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_SetViewFinderL, Teardown)

EUNIT_TEST (
    "MccParameterName test",
    "CMceComDisplaySink",
    "MccParameterName",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDisplaySink_MccParameterNameL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
