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
#include "UT_CMceComCnCodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"
#include "mcecomaudiostream.h"
#include "mcecommicsource.h"
#include "mcecomrtpsink.h"
#include "mcecomsession.h"
#include "mcecomfactory.h"
#include "mcecomaudiocodec.h"
#include <mmcccodecinformationfactory.h>
#include "mmcccodeccn.h"
#include "mcecncodec.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComCnCodec* UT_CMceComCnCodec::NewL()
    {
    UT_CMceComCnCodec* self = UT_CMceComCnCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComCnCodec* UT_CMceComCnCodec::NewLC()
    {
    UT_CMceComCnCodec* self = new( ELeave ) UT_CMceComCnCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComCnCodec::~UT_CMceComCnCodec()
    {
    }

// Default constructor
UT_CMceComCnCodec::UT_CMceComCnCodec()
    {
    }

// Second phase construct
void UT_CMceComCnCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComCnCodec::SetupL()
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
    CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNameiLBC() );
    stream->AddCodecL( codec );
    CleanupStack::Pop( codec );
    iOtherCodec = codec;
    
    CMceComAudioCodec* cnCodec = factory.CreateCodecLC( KMceSDPNameCn() );
    stream->AddCodecL( cnCodec );
    CleanupStack::Pop( cnCodec );
    iCnCodec = cnCodec;
    
    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    iStream = stream;
    
    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    
    // Cn affects to other codecs
    EUNIT_ASSERT( iOtherCodec->iComfortNoiseEnabled );
    } 

void UT_CMceComCnCodec::Teardown()
    {
	CMceComSession::Delete( iSession, *iManager );
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_CMceComCnCodec::UT_CMceComCnCodec_SetBitrateL()
    {
    }

void UT_CMceComCnCodec::UT_CMceComCnCodec_SetAllowedBitratesL()
    {
    }

void UT_CMceComCnCodec::UT_CMceComCnCodec_GetMaxBitRateL()
    {
    }

void UT_CMceComCnCodec::UT_CMceComCnCodec_CloneLL()
    {
    }

void UT_CMceComCnCodec::DoMccEncodeL()
    {
    // Encode other codec to test how existence of cn affects to other codecs
    // Only iLBC and G.711 codecs supports generic comfort noise
    CMccCodecInformationFactory* factory = CMccCodecInformationFactory::NewL();
    CleanupStack::PushL( factory );
    CMccCodecInformation* mccCodec = factory->CreateCodecInformationL( KMceSDPNameiLBC );
    CleanupStack::PushL( mccCodec );
    
    iOtherCodec->DoMccEncodeL( *mccCodec, *iSession->MccStreams()[ 0 ] );
    EUNIT_ASSERT( mccCodec->ComfortNoiseGeneration() == KMceDefaultCnPayloadType );
    
    iCnCodec->iPayloadType = KMceDefaultCnPayloadType2;
    iOtherCodec->DoMccEncodeL( *mccCodec, *iSession->MccStreams()[ 0 ] );
    EUNIT_ASSERT( mccCodec->ComfortNoiseGeneration() == KMceDefaultCnPayloadType2 );
    
    CleanupStack::PopAndDestroy( mccCodec );
    CleanupStack::PopAndDestroy( factory );
    }

//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComCnCodec,
    "CMceComCnCodec tests",
    "UNIT" )

EUNIT_TEST (
    "SetBitrate test",
    "CMceComCnCodec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCnCodec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComCnCodec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCnCodec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComCnCodec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCnCodec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComCnCodec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCnCodec_CloneLL, Teardown)

EUNIT_TEST (
    "DoMccEncodeL test",
    "CMceComCnCodec",
    "DoMccEncodeL",
    "FUNCTIONALITY",
    SetupL, DoMccEncodeL, Teardown)
    
EUNIT_END_TEST_TABLE



//  END OF FILE
