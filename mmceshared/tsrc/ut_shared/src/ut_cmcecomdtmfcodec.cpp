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
#include "ut_cmcecomdtmfcodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mcedtmfcodec.h>
#include "mcemediamanager.h"
#include "mcecomrtpsink.h"
#include "mcecomrtpsource.h"
#include "mcecomspeakersink.h"
#include "mcecommicsource.h"
#include "mcecomaudiocodec.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComDtmfCodec* UT_CMceComDtmfCodec::NewL()
    {
    UT_CMceComDtmfCodec* self = UT_CMceComDtmfCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComDtmfCodec* UT_CMceComDtmfCodec::NewLC()
    {
    UT_CMceComDtmfCodec* self = new( ELeave ) UT_CMceComDtmfCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComDtmfCodec::~UT_CMceComDtmfCodec()
    {
    }

// Default constructor
UT_CMceComDtmfCodec::UT_CMceComDtmfCodec()
    {
    }

// Second phase construct
void UT_CMceComDtmfCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComDtmfCodec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );

    iSession = CMceComSession::NewL();
    CMceComAudioStream* downlinkStream = CMceComAudioStream::NewLC();
    CMceComMediaSource* mediaSource = CMceComRtpSource::NewLC();
    downlinkStream->SetSourceL( mediaSource );
    CleanupStack::Pop( mediaSource );
    iDownlinkSource = mediaSource;
    CMceComMediaSink* mediaSink = CMceComSpeakerSink::NewLC();
    downlinkStream->AddSinkL( mediaSink );
    CleanupStack::Pop( mediaSink );
    iDownlinkSink = mediaSink;
    
    CMceComAudioStream* uplinkStream = CMceComAudioStream::NewLC();
    CMceComMediaSource* mediaSource2 = CMceComMicSource::NewLC();
    uplinkStream->SetSourceL( mediaSource2 );
    CleanupStack::Pop( mediaSource2 );
    iUplinkSource = mediaSource2;
    CMceComMediaSink* mediaSink2 = CMceComRtpSink::NewLC();
    uplinkStream->AddSinkL( mediaSink2 );
    CleanupStack::Pop( mediaSink2 );
    iUplinkSink = mediaSink2;
    
    TMceComAudioCodecFactory factory;
    CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNameAMR() );
    downlinkStream->AddCodecL( codec );
    CleanupStack::Pop( codec );
    
    CMceComAudioCodec* dtmfCodec = factory.CreateCodecLC( KMceSDPNameDtmf() );
    downlinkStream->AddCodecL( dtmfCodec );
    CleanupStack::Pop( dtmfCodec );
    iCodec = dtmfCodec;
    
    CMceComAudioCodec* codec2 = factory.CreateCodecLC( KMceSDPNameAMR() );
    uplinkStream->AddCodecL( codec2 );
    CleanupStack::Pop( codec2 );
    
    CMceComAudioCodec* dtmfCodec2 = factory.CreateCodecLC( KMceSDPNameDtmf() );
    uplinkStream->AddCodecL( dtmfCodec2 );
    CleanupStack::Pop( dtmfCodec2 );
    
    downlinkStream->BindL( uplinkStream );
    CleanupStack::Pop( uplinkStream );
    
    iSession->AddStreamL( downlinkStream );
    CleanupStack::Pop( downlinkStream );
    iDownlinkStream = downlinkStream;
    iUplinkStream = uplinkStream;
    
    iSession->InitializeL();
    
    // DoDecode is actually testad already over here
    iSession->PrepareL( *iManager );
    
    EUNIT_ASSERT( iSession->MccStreams().Count() == 4 );
    } 

void UT_CMceComDtmfCodec::Teardown()
    {
	CMceComSession::Delete( iSession, *iManager );
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_CMceComDtmfCodec::UT_CMceComDtmfCodec_SetBitrateL()
    {
    }

void UT_CMceComDtmfCodec::UT_CMceComDtmfCodec_SetAllowedBitratesL()
    {
    }

void UT_CMceComDtmfCodec::UT_CMceComDtmfCodec_SetCodecModeL()
    {
    const TUint KInvalidCodecMode( 10 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetCodecMode( KInvalidCodecMode ) );
    EUNIT_ASSERT( KInvalidCodecMode != iCodec->iCodecMode );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetCodecMode( EMceOutbound ) );
    EUNIT_ASSERT( EMceOutbound == iCodec->iCodecMode );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetCodecMode( EMceInbound ) );
    EUNIT_ASSERT( EMceInbound == iCodec->iCodecMode );
    }

void UT_CMceComDtmfCodec::UT_CMceComDtmfCodec_SetPayloadTypeL()
    {
    const TUint8 KInvalidPayloadType( KMinDynPayloadType - 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetPayloadType( KInvalidPayloadType ) );
    EUNIT_ASSERT( KInvalidPayloadType != iCodec->iPayloadType );
    
    EUNIT_ASSERT( KErrNone == 
        iCodec->SetPayloadType( KMinDynPayloadType ) );
    EUNIT_ASSERT( KMinDynPayloadType == iCodec->iPayloadType );
    }

void UT_CMceComDtmfCodec::UT_CMceComDtmfCodec_GetMaxBitRateL()
    {
    }

void UT_CMceComDtmfCodec::UT_CMceComDtmfCodec_DoMccValidateLL()
    {
    }

void UT_CMceComDtmfCodec::UT_CMceComDtmfCodec_CloneLL()
    {
    }
	
//  TEST TABLE
EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComDtmfCodec,
    "CMceComDtmfCodec tests",
    "UNIT" )

EUNIT_TEST (
    "SetBitrate test",
    "CMceComDtmfCodec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDtmfCodec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComDtmfCodec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDtmfCodec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "SetCodecMode test",
    "CMceComDtmfCodec",
    "SetCodecMode",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDtmfCodec_SetCodecModeL, Teardown)

EUNIT_TEST (
    "SetPayloadType test",
    "CMceComDtmfCodec",
    "SetPayloadType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDtmfCodec_SetPayloadTypeL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComDtmfCodec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDtmfCodec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "DoMccValidateL test",
    "CMceComDtmfCodec",
    "DoMccValidateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDtmfCodec_DoMccValidateLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComDtmfCodec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComDtmfCodec_CloneLL, Teardown)

    
EUNIT_END_TEST_TABLE




//  END OF FILE
