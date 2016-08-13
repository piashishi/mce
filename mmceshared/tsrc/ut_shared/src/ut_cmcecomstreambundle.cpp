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
#include "ut_cmcecomstreambundle.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComStreamBundle* UT_CMceComStreamBundle::NewL()
    {
    UT_CMceComStreamBundle* self = UT_CMceComStreamBundle::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComStreamBundle* UT_CMceComStreamBundle::NewLC()
    {
    UT_CMceComStreamBundle* self = new( ELeave ) UT_CMceComStreamBundle();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComStreamBundle::~UT_CMceComStreamBundle()
    {
    }

// Default constructor
UT_CMceComStreamBundle::UT_CMceComStreamBundle()
    {
    }

// Second phase construct
void UT_CMceComStreamBundle::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComStreamBundle::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComStreamBundle::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_CMceComStreamBundle::UT_CMceComStreamBundle_TypeL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_AddStreamLL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_RemoveStreamLL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_StreamsL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_AddedLL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_SerializationIdL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_InternalizeFlatLL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_ExternalizeFlatLL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_InternalizeLL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_ExternalizeLL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_IdL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_BaseFactoryL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_InitializeLL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_UpdateLL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_CloneL()
    {
    }

void UT_CMceComStreamBundle::UT_CMceComStreamBundle_CloneL1L()
    {
    }


	
//  TEST TABLE
EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComStreamBundle,
    "CMceComStreamBundle tests",
    "UNIT" )

EUNIT_TEST (
    "Type test",
    "CMceComStreamBundle",
    "Type",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_TypeL, Teardown)

EUNIT_TEST (
    "AddStreamL test",
    "CMceComStreamBundle",
    "AddStreamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_AddStreamLL, Teardown)

EUNIT_TEST (
    "RemoveStreamL test",
    "CMceComStreamBundle",
    "RemoveStreamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_RemoveStreamLL, Teardown)

EUNIT_TEST (
    "Streams test",
    "CMceComStreamBundle",
    "Streams",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_StreamsL, Teardown)

EUNIT_TEST (
    "AddedL test",
    "CMceComStreamBundle",
    "AddedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_AddedLL, Teardown)

EUNIT_TEST (
    "SerializationId test",
    "CMceComStreamBundle",
    "SerializationId",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_SerializationIdL, Teardown)

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComStreamBundle",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComStreamBundle",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "InternalizeL test",
    "CMceComStreamBundle",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_InternalizeLL, Teardown)

EUNIT_TEST (
    "ExternalizeL test",
    "CMceComStreamBundle",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_ExternalizeLL, Teardown)

EUNIT_TEST (
    "Id test",
    "CMceComStreamBundle",
    "Id",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_IdL, Teardown)

EUNIT_TEST (
    "BaseFactory test",
    "CMceComStreamBundle",
    "BaseFactory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_BaseFactoryL, Teardown)

EUNIT_TEST (
    "InitializeL test",
    "CMceComStreamBundle",
    "InitializeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_InitializeLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComStreamBundle",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_UpdateLL, Teardown)

EUNIT_TEST (
    "Clone test",
    "CMceComStreamBundle",
    "Clone",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_CloneL, Teardown)

EUNIT_TEST (
    "CloneL(a) test",
    "CMceComStreamBundle",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComStreamBundle_CloneL1L, Teardown)

EUNIT_END_TEST_TABLE




//  END OF FILE
