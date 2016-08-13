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
#include "ut_cmcecomh263codec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mceh263codec.h>
#include "mcemediamanager.h"
#include "mcecomh263codec.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComH263Codec* UT_CMceComH263Codec::NewL()
    {
    UT_CMceComH263Codec* self = UT_CMceComH263Codec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComH263Codec* UT_CMceComH263Codec::NewLC()
    {
    UT_CMceComH263Codec* self = new( ELeave ) UT_CMceComH263Codec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComH263Codec::~UT_CMceComH263Codec()
    {
    }

// Default constructor
UT_CMceComH263Codec::UT_CMceComH263Codec()
    {
    }

// Second phase construct
void UT_CMceComH263Codec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComH263Codec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    TMceComVideoCodecFactory factory;
    iCodec = static_cast<CMceComH263Codec*>( 
        factory.CreateCodecLC( KMceSDPNameH263() ) );
    CleanupStack::Pop( iCodec );
    
    
    } 

void UT_CMceComH263Codec::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
	delete iCodec;
    }

void UT_CMceComH263Codec::UT_CMceComH263Codec_NewLL()
    {
    delete iCodec;
    iCodec = NULL;
    iCodec = CMceComH263Codec::NewL( KMceSDPNameH263() );
    EUNIT_ASSERT( iCodec->iState == CMceCodec::EEnabled );
    
    delete iCodec;
    iCodec = NULL;
    
    // Mode 1998 codec gets disabled at construction
    iCodec = CMceComH263Codec::NewL( KMceSDPNameH2631998() );
    EUNIT_ASSERT( iCodec->iState == CMceCodec::EDisabled );
    
    }

void UT_CMceComH263Codec::UT_CMceComH263Codec_SetBitrateL()
    {
    iCodec->iBitrate = 0;
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceH263Level10Bitrate ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceH263Level10Bitrate );
    EUNIT_ASSERT( iCodec->SetBitrate( 0 ) != KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceH263Level10Bitrate );
    
    }

void UT_CMceComH263Codec::UT_CMceComH263Codec_SetAllowedBitratesL()
    {
    iCodec->iBitrate = KMceH263DefaultBitrate;
    iCodec->iMaxBitRate = KMceH263DefaultMaxBitrate;

    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 0 ) != KErrNone );
    
    EUNIT_ASSERT( iCodec->iBitrate == KMceH263DefaultBitrate );
    EUNIT_ASSERT( iCodec->iMaxBitRate == KMceH263DefaultMaxBitrate );
    
    iCodec->iBitrate = KMceH263Level10Bitrate;
    iCodec->iMaxBitRate = KMceH263Level10Bitrate;
    
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedH263BitrateAll ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceH263Level10Bitrate );
    EUNIT_ASSERT( iCodec->iMaxBitRate == KMceH263Level45Bitrate );
    
    iCodec->iBitrate = KMceH263Level45Bitrate;
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedH263Bitrate10 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceH263Level10Bitrate );
    EUNIT_ASSERT( iCodec->iMaxBitRate == KMceH263Level10Bitrate );
    
    }

void UT_CMceComH263Codec::UT_CMceComH263Codec_GetMaxBitRateL()
    {
    
    iCodec->iAllowedBitrates = KMceAllowedH263Bitrate10;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceH263Level10Bitrate );
    iCodec->iAllowedBitrates = KMceAllowedH263BitrateAll;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceH263Level45Bitrate );
    iCodec->iAllowedBitrates = 0;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == 0 );
    
    }

void UT_CMceComH263Codec::UT_CMceComH263Codec_SetMaxBitrateL()
    {
    const TUint KNotAllowedBitrate = 0xFFFF;
    
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KMceH263Level10Bitrate ) == KErrNone );
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KMceH263Level45Bitrate ) == KErrNone );
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KNotAllowedBitrate ) != KErrNone );
    
    }

void UT_CMceComH263Codec::UT_CMceComH263Codec_ResolveAllowedBitratesL()
    {
    
    TUint allowedBitrates = 0;

    const TUint KAllowedBitrate1 = KMceH263Level10Bitrate;
    const TUint KAllowedBitrate2 = KMceH263Level45Bitrate;
    const TUint KNotAllowedBitrate = KMceH263Level45Bitrate + 1;

    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate1, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedH263Bitrate10 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate2, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedH263BitrateAll );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KNotAllowedBitrate,  allowedBitrates ) != KErrNone ); 
    
    }

void UT_CMceComH263Codec::UT_CMceComH263Codec_CloneLL()
    {
    CMceComVideoCodec* clone = NULL;
    clone = iCodec->CloneL();
    delete clone;
    }



	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComH263Codec,
    "CMceComH263Codec tests",
    "UNIT" )

    
EUNIT_TEST (
    "NewL test",
    "CMceComH263Codec",
    "NewL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComH263Codec_NewLL, Teardown)

EUNIT_TEST (
    "SetBitrate test",
    "CMceComH263Codec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComH263Codec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComH263Codec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComH263Codec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComH263Codec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComH263Codec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "SetMaxBitrate test",
    "CMceComH263Codec",
    "SetMaxBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComH263Codec_SetMaxBitrateL, Teardown)

EUNIT_TEST (
    "ResolveAllowedBitrates test",
    "CMceComH263Codec",
    "ResolveAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComH263Codec_ResolveAllowedBitratesL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComH263Codec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComH263Codec_CloneLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
