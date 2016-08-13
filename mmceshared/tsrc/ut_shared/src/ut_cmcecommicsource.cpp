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
#include "ut_cmcecommicsource.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComMicSource* UT_CMceComMicSource::NewL()
    {
    UT_CMceComMicSource* self = UT_CMceComMicSource::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComMicSource* UT_CMceComMicSource::NewLC()
    {
    UT_CMceComMicSource* self = new( ELeave ) UT_CMceComMicSource();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComMicSource::~UT_CMceComMicSource()
    {
    }

// Default constructor
UT_CMceComMicSource::UT_CMceComMicSource()
    {
    }

// Second phase construct
void UT_CMceComMicSource::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComMicSource::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComMicSource::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }

void UT_CMceComMicSource::UT_CMceComMicSource_InternalizeFlatLL()
    {
    }

void UT_CMceComMicSource::UT_CMceComMicSource_ExternalizeFlatLL()
    {
    }

void UT_CMceComMicSource::UT_CMceComMicSource_EventReceivedLL()
    {
    }

void UT_CMceComMicSource::UT_CMceComMicSource_UpdateLL()
    {
    }

void UT_CMceComMicSource::UT_CMceComMicSource_CloneLL()
    {
    }

void UT_CMceComMicSource::UT_CMceComMicSource_ReusableL()
    {
    }

void UT_CMceComMicSource::UT_CMceComMicSource_MccTypeL()
    {
    }

void UT_CMceComMicSource::UT_CMceComMicSource_PrepareLL()
    {
    }




	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComMicSource,
    "CMceComMicSource tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComMicSource",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMicSource_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComMicSource",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMicSource_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComMicSource",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMicSource_EventReceivedLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComMicSource",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMicSource_UpdateLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComMicSource",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMicSource_CloneLL, Teardown)

EUNIT_TEST (
    "Reusable test",
    "CMceComMicSource",
    "Reusable",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMicSource_ReusableL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComMicSource",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMicSource_MccTypeL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComMicSource",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMicSource_PrepareLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
