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
#include "ut_cmcecomfilesink.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComFileSink* UT_CMceComFileSink::NewL()
    {
    UT_CMceComFileSink* self = UT_CMceComFileSink::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComFileSink* UT_CMceComFileSink::NewLC()
    {
    UT_CMceComFileSink* self = new( ELeave ) UT_CMceComFileSink();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComFileSink::~UT_CMceComFileSink()
    {
    }

// Default constructor
UT_CMceComFileSink::UT_CMceComFileSink()
    {
    }

// Second phase construct
void UT_CMceComFileSink::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComFileSink::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComFileSink::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }

void UT_CMceComFileSink::UT_CMceComFileSink_InternalizeFlatLL()
    {
    }

void UT_CMceComFileSink::UT_CMceComFileSink_ExternalizeFlatLL()
    {
    }

void UT_CMceComFileSink::UT_CMceComFileSink_CloneLL()
    {
    }

void UT_CMceComFileSink::UT_CMceComFileSink_UpdateLL()
    {
    }

void UT_CMceComFileSink::UT_CMceComFileSink_MccTypeL()
    {
    }

void UT_CMceComFileSink::UT_CMceComFileSink_InitParamLL()
    {
    }


	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComFileSink,
    "CMceComFileSink tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComFileSink",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSink_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComFileSink",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSink_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComFileSink",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSink_CloneLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComFileSink",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSink_UpdateLL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComFileSink",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSink_MccTypeL, Teardown)

EUNIT_TEST (
    "InitParamL test",
    "CMceComFileSink",
    "InitParamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSink_InitParamLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE

