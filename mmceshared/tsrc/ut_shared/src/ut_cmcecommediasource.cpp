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
#include "ut_cmcecommediasource.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComMediaSource* UT_CMceComMediaSource::NewL()
    {
    UT_CMceComMediaSource* self = UT_CMceComMediaSource::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComMediaSource* UT_CMceComMediaSource::NewLC()
    {
    UT_CMceComMediaSource* self = new( ELeave ) UT_CMceComMediaSource();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComMediaSource::~UT_CMceComMediaSource()
    {
    }

// Default constructor
UT_CMceComMediaSource::UT_CMceComMediaSource()
    {
    }

// Second phase construct
void UT_CMceComMediaSource::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComMediaSource::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComMediaSource::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_CMceComMediaSource::UT_CMceComMediaSource_InternalizeFlatLL()
    {
    }

void UT_CMceComMediaSource::UT_CMceComMediaSource_ExternalizeFlatLL()
    {
    }

void UT_CMceComMediaSource::UT_CMceComMediaSource_EventReceivedLL()
    {
    }

void UT_CMceComMediaSource::UT_CMceComMediaSource_UpdateLL()
    {
    }

void UT_CMceComMediaSource::UT_CMceComMediaSource_CloneLL()
    {
    }

void UT_CMceComMediaSource::UT_CMceComMediaSource_UseRTCPL()
    {
    }

void UT_CMceComMediaSource::UT_CMceComMediaSource_TypeL()
    {
    }

void UT_CMceComMediaSource::UT_CMceComMediaSource_FactoryL()
    {
    }

void UT_CMceComMediaSource::UT_CMceComMediaSource_MccTypeL()
    {
    }




	
//  TEST TABLE
EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComMediaSource,
    "CMceComMediaSource tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComMediaSource",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSource_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComMediaSource",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSource_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComMediaSource",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSource_EventReceivedLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComMediaSource",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSource_UpdateLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComMediaSource",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSource_CloneLL, Teardown)

EUNIT_TEST (
    "UseRTCP test",
    "CMceComMediaSource",
    "UseRTCP",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSource_UseRTCPL, Teardown)

EUNIT_TEST (
    "Type test",
    "CMceComMediaSource",
    "Type",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSource_TypeL, Teardown)

EUNIT_TEST (
    "Factory test",
    "CMceComMediaSource",
    "Factory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSource_FactoryL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComMediaSource",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaSource_MccTypeL, Teardown)

EUNIT_END_TEST_TABLE




//  END OF FILE
