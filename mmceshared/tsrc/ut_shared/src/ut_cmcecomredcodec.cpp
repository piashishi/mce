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
#include "ut_cmcecomredcodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"
#include "mcecomaudiostream.h"
#include "mcecommicsource.h"
#include "mcecomrtpsink.h"
#include "mcecomsession.h"
#include "mcecomfactory.h"
#include "mcecomaudiocodec.h"
#include "mcecomredcodec.h"

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComRedCodec* UT_CMceComRedCodec::NewL()
    {
    UT_CMceComRedCodec* self = UT_CMceComRedCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComRedCodec* UT_CMceComRedCodec::NewLC()
    {
    UT_CMceComRedCodec* self = new( ELeave ) UT_CMceComRedCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComRedCodec::~UT_CMceComRedCodec()
    {
    }

// Default constructor
UT_CMceComRedCodec::UT_CMceComRedCodec()
    {
    }

// Second phase construct
void UT_CMceComRedCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComRedCodec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );

    iSession = CMceComSession::NewL();
    CMceComAudioStream* stream = CMceComAudioStream::NewLC();
    CMceComMediaSource* mediaSource = CMceComMicSource::NewLC();
    stream->SetSourceL( mediaSource );
    CleanupStack::Pop( mediaSource );
    iSource = mediaSource;
    CMceComMediaSink* mediaSink = CMceComRtpSink::NewLC();
    stream->AddSinkL( mediaSink );
    CleanupStack::Pop( mediaSink );
    iSink = mediaSink;
    
    TMceComAudioCodecFactory factory;
    CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNameAMR() );
    stream->AddCodecL( codec );
    CleanupStack::Pop( codec );
    
    CMceComAudioCodec* redCodec = factory.CreateCodecLC( KMceSDPNameRed() );
    stream->AddCodecL( redCodec );
    CleanupStack::Pop( redCodec );
    iCodec = static_cast<CMceComRedCodec*>( redCodec );
    
    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    iStream = stream;
    
    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    } 

void UT_CMceComRedCodec::Setup2L()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );

    iSession = CMceComSession::NewL();
    CMceComAudioStream* stream = CMceComAudioStream::NewLC();
    CMceComMediaSource* mediaSource = CMceComMicSource::NewLC();
    stream->SetSourceL( mediaSource );
    CleanupStack::Pop( mediaSource );
    iSource = mediaSource;
    CMceComMediaSink* mediaSink = CMceComRtpSink::NewLC();
    stream->AddSinkL( mediaSink );
    CleanupStack::Pop( mediaSink );
    iSink = mediaSink;
    
    TMceComAudioCodecFactory factory;
    
    CMceComAudioCodec* redCodec = factory.CreateCodecLC( KMceSDPNameRed() );
    stream->AddCodecL( redCodec );
    CleanupStack::Pop( redCodec );
    iCodec = static_cast<CMceComRedCodec*>( redCodec );
    
    CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNameAMR() );
    stream->AddCodecL( codec );
    CleanupStack::Pop( codec );
    
    CMceComAudioCodec* codec2 = factory.CreateCodecLC( KMceSDPNameiLBC() );
    stream->AddCodecL( codec2 );
    CleanupStack::Pop( codec2 );

    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    iStream = stream;
    
    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    } 
    
void UT_CMceComRedCodec::Teardown()
    {
    CMceComSession::Delete( iSession, *iManager );
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_CMceComRedCodec::UT_CMceComRedCodec_SetBitrateL()
    {
    }

void UT_CMceComRedCodec::UT_CMceComRedCodec_SetAllowedBitratesL()
    {
    }

void UT_CMceComRedCodec::UT_CMceComRedCodec_SetPayloadTypeL()
    {
    const TUint8 KInvalidPayloadType( KMinDynPayloadType - 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetPayloadType( KInvalidPayloadType ) );
    EUNIT_ASSERT( KInvalidPayloadType != iCodec->iPayloadType );
    
    EUNIT_ASSERT( KErrNone == 
        iCodec->SetPayloadType( KMinDynPayloadType ) );
    EUNIT_ASSERT( KMinDynPayloadType == iCodec->iPayloadType );
    }

void UT_CMceComRedCodec::UT_CMceComRedCodec_GetMaxBitRateL()
    {
    }

void UT_CMceComRedCodec::UT_CMceComRedCodec_CloneLL()
    {
    }

void UT_CMceComRedCodec::UT_CMceComRedCodec_DoDecodeAudioLL()
    {
    EUNIT_ASSERT( iStream->CodecCount() == 2 );
    iCodec->DoDecodeAudioL( 1, iSession->MccStreams(), *iStream, *iManager );
    EUNIT_ASSERT( iStream->CodecL( 0 )->iRedCount == 0 );
    EUNIT_ASSERT( iStream->CodecL( 1 )->iRedCount == 0 );
    
    TBuf8<20> fmtp;
    fmtp.AppendNum( iStream->CodecL( 0 )->iPayloadType );
    fmtp.Append( _L8("/") );
    fmtp.AppendNum( iStream->CodecL( 0 )->iPayloadType );
    iStream->CodecL( 1 )->SetFmtpAttributeL( fmtp, ETrue );
    iCodec->DoDecodeAudioL( 1, iSession->MccStreams(), *iStream, *iManager );
    EUNIT_ASSERT( iStream->CodecL( 0 )->iRedCount == 1 );
    EUNIT_ASSERT( iStream->CodecL( 1 )->iRedCount == 0 );
    }

void UT_CMceComRedCodec::UT_CMceComRedCodec_DoDecodeAudioL2L()
    {
    // If red is preferred send codec, next sending capable codec is enabled
    // for sending
    EUNIT_ASSERT( iStream->CodecCount() == 3 );
    iCodec->DoDecodeAudioL( 0, iSession->MccStreams(), *iStream, *iManager );
    EUNIT_ASSERT( iStream->CodecL( 0 )->iRedCount == 0 );
    EUNIT_ASSERT( iStream->CodecL( 1 )->iRedCount == 0 );
    EUNIT_ASSERT( iStream->CodecL( 1 )->iIsEnabled );
    EUNIT_ASSERT( iStream->CodecL( 2 )->iRedCount == 0 );
    
    // If red is preferred send codec, next mapped sending capable codec is
    // enabled for sending
    TBuf8<20> fmtp;
    fmtp.AppendNum( iStream->CodecL( 2 )->iPayloadType );
    fmtp.Append( _L8("/") );
    fmtp.AppendNum( iStream->CodecL( 2 )->iPayloadType );
    iStream->CodecL( 0 )->SetFmtpAttributeL( fmtp, ETrue );
    iCodec->DoDecodeAudioL( 0, iSession->MccStreams(), *iStream, *iManager );
    EUNIT_ASSERT( iStream->CodecL( 0 )->iRedCount == 0 );
    EUNIT_ASSERT( iStream->CodecL( 1 )->iRedCount == 0 );
    EUNIT_ASSERT( iStream->CodecL( 2 )->iRedCount == 1 );
    EUNIT_ASSERT( iStream->CodecL( 2 )->iIsEnabled );
    }

	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComRedCodec,
    "CMceComRedCodec tests",
    "UNIT" )

EUNIT_TEST (
    "SetBitrate test",
    "CMceComRedCodec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRedCodec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComRedCodec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRedCodec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "SetPayloadType test",
    "CMceComRedCodec",
    "SetPayloadType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRedCodec_SetPayloadTypeL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComRedCodec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRedCodec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComRedCodec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRedCodec_CloneLL, Teardown)

EUNIT_TEST (
    "DoDecodeAudioL test",
    "CMceComRedCodec",
    "DoDecodeAudioL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComRedCodec_DoDecodeAudioLL, Teardown)

EUNIT_TEST (
    "DoDecodeAudioL2 test",
    "CMceComRedCodec",
    "DoDecodeAudioL2",
    "FUNCTIONALITY",
    Setup2L, UT_CMceComRedCodec_DoDecodeAudioL2L, Teardown)
    
EUNIT_END_TEST_TABLE



//  END OF FILE
