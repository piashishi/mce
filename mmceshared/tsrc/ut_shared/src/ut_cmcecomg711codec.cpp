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
#include "ut_cmcecomg711codec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mceg711codec.h>
#include "mcecomg711codec.h"
#include "mcemediamanager.h"

const TUint KMceTestG711FrameSize = 10;

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComG711Codec* UT_CMceComG711Codec::NewL()
    {
    UT_CMceComG711Codec* self = UT_CMceComG711Codec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComG711Codec* UT_CMceComG711Codec::NewLC()
    {
    UT_CMceComG711Codec* self = new( ELeave ) UT_CMceComG711Codec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComG711Codec::~UT_CMceComG711Codec()
    {
    delete iManager;
	delete iServer;
    delete iCodec;
    }

// Default constructor
UT_CMceComG711Codec::UT_CMceComG711Codec()
    {
    }

// Second phase construct
void UT_CMceComG711Codec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComG711Codec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    TMceComAudioCodecFactory factory;
    iCodec = static_cast<CMceComG711Codec*>( 
        factory.CreateCodecLC( KMceSDPNamePCMU() ) );
    CleanupStack::Pop( iCodec );
    } 

void UT_CMceComG711Codec::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    delete iCodec;
	iCodec = NULL;
    }


void UT_CMceComG711Codec::UT_CMceComG711Codec_SetBitrateL()
    {
    }

void UT_CMceComG711Codec::UT_CMceComG711Codec_SetAllowedBitratesL()
    {
    }

void UT_CMceComG711Codec::UT_CMceComG711Codec_SetCodecModeL()
    {
    const TUint KInvalidCodecMode( 10 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetCodecMode( KInvalidCodecMode ) );
    EUNIT_ASSERT( KInvalidCodecMode != iCodec->iCodecMode );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetCodecMode( KMceG711PCMU ) );
    EUNIT_ASSERT( KMceG711PCMU == iCodec->iCodecMode );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetCodecMode( KMceG711PCMA ) );
    EUNIT_ASSERT( KMceG711PCMA == iCodec->iCodecMode );
    }
    
void UT_CMceComG711Codec::UT_CMceComG711Codec_GetMaxBitRateL()
    {
    }

void UT_CMceComG711Codec::UT_CMceComG711Codec_SetPTimeL()
    {
    const TUint KInvalidPTime( KMceTestG711FrameSize + 1 );
    EUNIT_ASSERT( KErrNotSupported == iCodec->SetPTime( KInvalidPTime ) );
    EUNIT_ASSERT( KInvalidPTime != iCodec->iPTime );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetPTime( KMceG711DefaultPtime ) );
    EUNIT_ASSERT( KMceG711DefaultPtime == iCodec->iPTime );
    }

void UT_CMceComG711Codec::UT_CMceComG711Codec_SetMaxPTimeL()
    {
    const TUint KInvalidMaxPTime( KMceG711DefaultMaxPtime + 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetMaxPTime( KInvalidMaxPTime ) );
    EUNIT_ASSERT( KInvalidMaxPTime != iCodec->iMaxPTime );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetMaxPTime( KMceG711DefaultMaxPtime ) );
    EUNIT_ASSERT( KMceG711DefaultMaxPtime == iCodec->iMaxPTime );
    }

void UT_CMceComG711Codec::UT_CMceComG711Codec_CloneLL()
    {
    }


	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComG711Codec,
    "CMceComG711Codec tests",
    "UNIT" )

EUNIT_TEST (
    "SetBitrate test",
    "CMceComG711Codec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG711Codec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComG711Codec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG711Codec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "SetCodecMode test",
    "CMceComG711Codec",
    "SetCodecMode",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG711Codec_SetCodecModeL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComG711Codec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG711Codec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "SetPTime test",
    "CMceComG711Codec",
    "SetPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG711Codec_SetPTimeL, Teardown)

EUNIT_TEST (
    "SetMaxPTime test",
    "CMceComG711Codec",
    "SetMaxPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG711Codec_SetMaxPTimeL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComG711Codec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComG711Codec_CloneLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
