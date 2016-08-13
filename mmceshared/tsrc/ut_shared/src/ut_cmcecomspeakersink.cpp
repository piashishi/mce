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
#include "ut_cmcecomspeakersink.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"
#include "mcecomspeakersink.h"
#include "mcecomaudiostream.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComSpeakerSink* UT_CMceComSpeakerSink::NewL()
    {
    UT_CMceComSpeakerSink* self = UT_CMceComSpeakerSink::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComSpeakerSink* UT_CMceComSpeakerSink::NewLC()
    {
    UT_CMceComSpeakerSink* self = new( ELeave ) UT_CMceComSpeakerSink();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComSpeakerSink::~UT_CMceComSpeakerSink()
    {
    }

// Default constructor
UT_CMceComSpeakerSink::UT_CMceComSpeakerSink()
    {
    }

// Second phase construct
void UT_CMceComSpeakerSink::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComSpeakerSink::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    iSpeaker = CMceComSpeakerSink::NewL();
    } 

void UT_CMceComSpeakerSink::Teardown()
    {
    delete iSpeaker;
    
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_InternalizeFlatLL()
    {
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_ExternalizeFlatLL()
    {
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_EventReceivedLL()
    {
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_CloneLL()
    {
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_UpdateLL()
    {
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_CreateEndpointProxyLL()
    {
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_UsesEndpointProxyL()
    {
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_ReusableL()
    {
    // Normally speaker is not reusable
    CMceComMediaStream* stream = CMceComAudioStream::NewLC();
    EUNIT_ASSERT( !iSpeaker->Reusable( *stream ) );
    
    // When bundled, speaker is reusable
    iSpeaker->SetupEndpointProxyL( NULL );
    EUNIT_ASSERT( iSpeaker->Reusable( *stream ) );
    
    CleanupStack::PopAndDestroy( stream );
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_MccTypeL()
    {
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_InitParamLL()
    {
    }

void UT_CMceComSpeakerSink::UT_CMceComSpeakerSink_PrepareLL()
    {
    }



	
//  TEST TABLE
EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComSpeakerSink,
    "CMceComSpeakerSink tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComSpeakerSink",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComSpeakerSink",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComSpeakerSink",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_EventReceivedLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComSpeakerSink",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_CloneLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComSpeakerSink",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_UpdateLL, Teardown)

EUNIT_TEST (
    "CreateEndpointProxyL test",
    "CMceComSpeakerSink",
    "CreateEndpointProxyL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_CreateEndpointProxyLL, Teardown)

EUNIT_TEST (
    "UsesEndpointProxy test",
    "CMceComSpeakerSink",
    "UsesEndpointProxy",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_UsesEndpointProxyL, Teardown)

EUNIT_TEST (
    "Reusable test",
    "CMceComSpeakerSink",
    "Reusable",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_ReusableL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComSpeakerSink",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_MccTypeL, Teardown)

EUNIT_TEST (
    "InitParamL test",
    "CMceComSpeakerSink",
    "InitParamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_InitParamLL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComSpeakerSink",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSpeakerSink_PrepareLL, Teardown)

EUNIT_END_TEST_TABLE




//  END OF FILE
