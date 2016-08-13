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
#include "ut_cmcecomg729codec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mceg729codec.h>
#include "mcecomg729codec.h"
#include "mcemediamanager.h"

const TUint KMceTestG72FrameSize = 10;

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComG729Codec* UT_CMceComG729Codec::NewL()
    {
    UT_CMceComG729Codec* self = UT_CMceComG729Codec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComG729Codec* UT_CMceComG729Codec::NewLC()
    {
    UT_CMceComG729Codec* self = new( ELeave ) UT_CMceComG729Codec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComG729Codec::~UT_CMceComG729Codec()
    {
    delete iManager;
    delete iServer;
    delete iCodec;
    }

// Default constructor
UT_CMceComG729Codec::UT_CMceComG729Codec()
    {
    }

// Second phase construct
void UT_CMceComG729Codec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComG729Codec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );

    TMceComAudioCodecFactory factory;
    iCodec = static_cast<CMceComG729Codec*>( 
        factory.CreateCodecLC( KMceSDPNameG729() ) );
    CleanupStack::Pop( iCodec );
    } 

void UT_CMceComG729Codec::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    delete iCodec;
	iCodec = NULL;
    }

void UT_CMceComG729Codec::UT_CMceComG729Codec_SetBitrateL()
    {
    }

void UT_CMceComG729Codec::UT_CMceComG729Codec_SetAllowedBitratesL()
    {
    }

void UT_CMceComG729Codec::UT_CMceComG729Codec_SetCodecModeL()
    {
    const TUint KInvalidCodecMode( 10 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetCodecMode( KInvalidCodecMode ) );
    EUNIT_ASSERT( KInvalidCodecMode != iCodec->iCodecMode );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetCodecMode( KG729CodecMode ) );
    EUNIT_ASSERT( KG729CodecMode == iCodec->iCodecMode );
    }
    
void UT_CMceComG729Codec::UT_CMceComG729Codec_GetMaxBitRateL()
    {
    }

void UT_CMceComG729Codec::UT_CMceComG729Codec_SetPTimeL()
    {
    const TUint KInvalidPTime( KMceTestG72FrameSize + 1 );
    EUNIT_ASSERT( KErrNotSupported == iCodec->SetPTime( KInvalidPTime ) );
    EUNIT_ASSERT( KInvalidPTime != iCodec->iPTime );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetPTime( KMceG729DefaultPtime ) );
    EUNIT_ASSERT( KMceG729DefaultPtime == iCodec->iPTime );
    }

void UT_CMceComG729Codec::UT_CMceComG729Codec_SetMaxPTimeL()
    {
    const TUint KInvalidMaxPTime( KMceG729DefaultMaxPtime + 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetMaxPTime( KInvalidMaxPTime ) );
    EUNIT_ASSERT( KInvalidMaxPTime != iCodec->iMaxPTime );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetMaxPTime( KMceG729DefaultMaxPtime ) );
    EUNIT_ASSERT( KMceG729DefaultMaxPtime == iCodec->iMaxPTime );
    }


void UT_CMceComG729Codec::UT_CMceComG729Codec_CloneLL()
    {
    }


	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComG729Codec,
    "CMceComG711Codec tests",
    "UNIT" )

EUNIT_TEST (
    "SetBitrate test",
    "CMceComG711Codec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG729Codec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComG711Codec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG729Codec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "SetCodecMode test",
    "CMceComG729Codec",
    "SetCodecMode",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG729Codec_SetCodecModeL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComG711Codec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG729Codec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "SetPTime test",
    "CMceComG729Codec",
    "SetPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG729Codec_SetPTimeL, Teardown)

EUNIT_TEST (
    "SetMaxPTime test",
    "CMceComG729Codec",
    "SetMaxPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG729Codec_SetMaxPTimeL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComG711Codec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG729Codec_CloneLL, Teardown)

EUNIT_END_TEST_TABLE

