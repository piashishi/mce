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
#include "ut_cmcecomrtpsource.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComRtpSource* UT_CMceComRtpSource::NewL()
    {
    UT_CMceComRtpSource* self = UT_CMceComRtpSource::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComRtpSource* UT_CMceComRtpSource::NewLC()
    {
    UT_CMceComRtpSource* self = new( ELeave ) UT_CMceComRtpSource();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComRtpSource::~UT_CMceComRtpSource()
    {
    }

// Default constructor
UT_CMceComRtpSource::UT_CMceComRtpSource()
    {
    }

// Second phase construct
void UT_CMceComRtpSource::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComRtpSource::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComRtpSource::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }

void UT_CMceComRtpSource::UT_CMceComRtpSource_InternalizeFlatLL()
    {
    }

void UT_CMceComRtpSource::UT_CMceComRtpSource_ExternalizeFlatLL()
    {
    }

void UT_CMceComRtpSource::UT_CMceComRtpSource_EventReceivedLL()
    {
    }

void UT_CMceComRtpSource::UT_CMceComRtpSource_CloneLL()
    {
    }

void UT_CMceComRtpSource::UT_CMceComRtpSource_UpdateLL()
    {
    }

void UT_CMceComRtpSource::UT_CMceComRtpSource_InactivityTimerL()
    {
    }

void UT_CMceComRtpSource::UT_CMceComRtpSource_MccTypeL()
    {
    }

void UT_CMceComRtpSource::UT_CMceComRtpSource_InitParamLL()
    {
    }

void UT_CMceComRtpSource::UT_CMceComRtpSource_PrepareLL()
    {
    }



	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComRtpSource,
    "CMceComRtpSource tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComRtpSource",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSource_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComRtpSource",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSource_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComRtpSource",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSource_EventReceivedLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComRtpSource",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSource_CloneLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComRtpSource",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSource_UpdateLL, Teardown)

EUNIT_TEST (
    "InactivityTimer test",
    "CMceComRtpSource",
    "InactivityTimer",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSource_InactivityTimerL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComRtpSource",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSource_MccTypeL, Teardown)

EUNIT_TEST (
    "InitParamL test",
    "CMceComRtpSource",
    "InitParamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSource_InitParamLL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComRtpSource",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRtpSource_PrepareLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
