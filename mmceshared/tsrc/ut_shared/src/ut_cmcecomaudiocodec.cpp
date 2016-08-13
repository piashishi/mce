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
#include "ut_cmcecomaudiocodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mmcccodecinformationfactory.h>
#include "mcecomaudiocodec.h"
#include "mcemediamanager.h"
#include "mmcccodecinformation.h"
#include "mmcccodecg729.h"
#include "mcecomaudiostream.h"
#include "mcecommediasource.h"
#include "mcecommediasink.h"
#include "mcecomfactory.h"

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComAudioCodec* UT_CMceComAudioCodec::NewL()
    {
    UT_CMceComAudioCodec* self = UT_CMceComAudioCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComAudioCodec* UT_CMceComAudioCodec::NewLC()
    {
    UT_CMceComAudioCodec* self = new( ELeave ) UT_CMceComAudioCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComAudioCodec::~UT_CMceComAudioCodec()
    {
    delete iManager;
	delete iServer;
	delete iCodec;
    }

// Default constructor
UT_CMceComAudioCodec::UT_CMceComAudioCodec()
    {
    }

// Second phase construct
void UT_CMceComAudioCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComAudioCodec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    TMceComAudioCodecFactory factory;
    iCodec = factory.CreateCodecLC( KMceSDPNameAMR() );
    CleanupStack::Pop( iCodec );
    } 

void UT_CMceComAudioCodec::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
	delete iCodec;
	iCodec = NULL;
    }


void UT_CMceComAudioCodec::UT_CMceComAudioCodec_SetSamplingFreqL()
    {
    const TUint KInvalidSamplingFreq( 5000 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->CMceComAudioCodec::SetSamplingFreq( KInvalidSamplingFreq ) );
    EUNIT_ASSERT( KInvalidSamplingFreq != iCodec->iSamplingFreq );
    
    const TUint KValidSamplingFreq( 8000 );
    EUNIT_ASSERT( KErrNone == 
        iCodec->CMceComAudioCodec::SetSamplingFreq( KValidSamplingFreq ) );
    EUNIT_ASSERT( KValidSamplingFreq == iCodec->iSamplingFreq );
    }


void UT_CMceComAudioCodec::UT_CMceComAudioCodec_SetPTimeL()
    {
    const TUint KInvalidPTime1( 0 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->CMceComAudioCodec::SetPTime( KInvalidPTime1 ) );
    EUNIT_ASSERT( KInvalidPTime1 != iCodec->iPTime );
    
    const TUint KInvalidPTime2( iCodec->iMaxPTime + 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->CMceComAudioCodec::SetPTime( KInvalidPTime2 ) );
    EUNIT_ASSERT( KInvalidPTime2 != iCodec->iPTime );
    
    const TUint KValidPTime( 20 );
    EUNIT_ASSERT( KErrNone == 
        iCodec->CMceComAudioCodec::SetPTime( KValidPTime ) );
    EUNIT_ASSERT( KValidPTime == iCodec->iPTime );
    }


void UT_CMceComAudioCodec::UT_CMceComAudioCodec_SetMaxPTimeL()
    {
    const TUint KInvalidMaxPTime1( 0 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->CMceComAudioCodec::SetMaxPTime( KInvalidMaxPTime1 ) );
    EUNIT_ASSERT( KInvalidMaxPTime1 != iCodec->iMaxPTime );
    
    const TUint KInvalidMaxPTime2( iCodec->iPTime - 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->CMceComAudioCodec::SetMaxPTime( KInvalidMaxPTime2 ) );
    EUNIT_ASSERT( KInvalidMaxPTime2 != iCodec->iMaxPTime );
    
    const TUint KValidMaxPTime( 20 );
    EUNIT_ASSERT( KErrNone == 
        iCodec->CMceComAudioCodec::SetMaxPTime( KValidMaxPTime ) );
    EUNIT_ASSERT( KValidMaxPTime == iCodec->iMaxPTime );
    }

    
void UT_CMceComAudioCodec::UT_CMceComAudioCodec_InternalizeFlatLL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_ExternalizeFlatLL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_UpdateLL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_CloneLL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_FactoryL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_operatorAssignL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_DoMccDecodeLL()
    {
    CMccCodecInformation* mccCodec = CMCCCodecG729::NewL();
    CleanupStack::PushL( mccCodec );

    CMCCCodecG729& mcccodeg729 = static_cast<CMCCCodecG729&>( *mccCodec );

    mcccodeg729.SetBitrate( KG729Bitrate );
    mcccodeg729.SetSamplingFreq( KG729SampleRate );
    mcccodeg729.SetRedCount( KMaxGenRedCount );
    mcccodeg729.SetRedundancyPT( 128 );
    mcccodeg729.SetComfortNoiseGeneration( KPayloadTypeUndefined );
    mcccodeg729.EnableVAD( EFalse );

    iCodec->CMceComAudioCodec::DoMccDecodeL( *mccCodec );
    EUNIT_ASSERT( KG729Bitrate == iCodec->iBitrate );
    EUNIT_ASSERT( KG729SampleRate == iCodec->iSamplingFreq );
    EUNIT_ASSERT( 128 == iCodec->iRedPayloadType );
    EUNIT_ASSERT( KMaxGenRedCount == iCodec->iRedCount );
    EUNIT_ASSERT( KPayloadTypeUndefined == iCodec->iComfortNoiseEnabled );
    EUNIT_ASSERT( EFalse == iCodec->iEnableVAD );

    mcccodeg729.EnableVAD( ETrue );
    iCodec->CMceComAudioCodec::DoMccDecodeL( *mccCodec );
    EUNIT_ASSERT( ETrue == iCodec->iEnableVAD );

    CleanupStack::PopAndDestroy( mccCodec );
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_DoMccEncodeLL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_DoMccValidateLL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_DoMccAdjustLL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_DoMccRequireSignallingL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_DoSetDefaultFmtpAttributeLL()
    {
    }

void UT_CMceComAudioCodec::UT_CMceComAudioCodec_DoMccEncodeComfortNoiseLL()
    {
	CMceComAudioStream* stream = CMceComAudioStream::NewLC();

	CMceComMediaSource* mediaSource = CMceComMediaSource::NewLC();
	stream->SetSourceL(mediaSource);
	CleanupStack::Pop(mediaSource);

	CMceComMediaSink* mediaSink = CMceComMediaSink::NewLC();
	stream->AddSinkL(mediaSink);
	CleanupStack::Pop(mediaSink);

	TMceComAudioCodecFactory factory;
	CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNamePCMU() );
	codec->iPTime = 0;
	codec->iMaxPTime = 0;
	stream->AddCodecL(codec);
	CleanupStack::Pop(codec);

	CMceSrvStream* srvStream = CMceSrvStream::NewL(*iManager, *stream,
			*mediaSource, *mediaSink, *codec);
	CleanupStack::PushL(srvStream);
	
	CMccCodecInformationFactory* mccCodecFactory =
	        CMccCodecInformationFactory::NewL();
	    CleanupStack::PushL( mccCodecFactory );
	CMccCodecInformation* mccCodec = mccCodecFactory->CreateCodecInformationL(
			KMceSDPNamePCMU() );
	CleanupStack::PushL(mccCodec);
	
	
	iCodec->CMceComAudioCodec::DoMccEncodeComfortNoiseL(*mccCodec, *srvStream);
	EUNIT_ASSERT( EFalse == iCodec->iComfortNoiseEnabled );
	EUNIT_ASSERT( 120 == mccCodec->KeepAlivePT() );
	
	codec = factory.CreateCodecLC(KMceSDPNameCn());
	codec->iIsNegotiated = ETrue;
	codec->iPTime = 0;
	codec->iMaxPTime = 0;
	stream->AddCodecL(codec);
	CleanupStack::Pop(codec);
	
	iCodec->CMceComAudioCodec::DoMccEncodeComfortNoiseL(*mccCodec, *srvStream);
	EUNIT_ASSERT( ETrue == iCodec->iComfortNoiseEnabled );
	
	CleanupStack::PopAndDestroy(4); // stream, srvStream, mccCodecFactory, mccCodec
    }


	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComAudioCodec,
    "CMceComAudioCodec tests",
    "UNIT" )

EUNIT_TEST (
    "SetSamplingFreq test",
    "CMceComAudioCodec",
    "SetSamplingFreq",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_SetSamplingFreqL, Teardown)

EUNIT_TEST (
    "SetPTime test",
    "CMceComAudioCodec",
    "SetPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_SetPTimeL, Teardown)

EUNIT_TEST (
    "SetMaxPTime test",
    "CMceComAudioCodec",
    "SetMaxPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_SetMaxPTimeL, Teardown)
    
EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComAudioCodec",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComAudioCodec",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComAudioCodec",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_UpdateLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComAudioCodec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_CloneLL, Teardown)

EUNIT_TEST (
    "Factory test",
    "CMceComAudioCodec",
    "Factory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_FactoryL, Teardown)

EUNIT_TEST (
    "operatorAssign test",
    "CMceComAudioCodec",
    "operatorAssign",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_operatorAssignL, Teardown)

EUNIT_TEST (
    "DoMccDecodeL test",
    "CMceComAudioCodec",
    "DoMccDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_DoMccDecodeLL, Teardown)

EUNIT_TEST (
    "DoMccEncodeL test",
    "CMceComAudioCodec",
    "DoMccEncodeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_DoMccEncodeLL, Teardown)

EUNIT_TEST (
    "DoMccValidateL test",
    "CMceComAudioCodec",
    "DoMccValidateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_DoMccValidateLL, Teardown)

EUNIT_TEST (
    "DoMccAdjustL test",
    "CMceComAudioCodec",
    "DoMccAdjustL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_DoMccAdjustLL, Teardown)

EUNIT_TEST (
    "DoMccRequireSignalling test",
    "CMceComAudioCodec",
    "DoMccRequireSignalling",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_DoMccRequireSignallingL, Teardown)

EUNIT_TEST (
    "DoSetDefaultFmtpAttributeL test",
    "CMceComAudioCodec",
    "DoSetDefaultFmtpAttributeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioCodec_DoSetDefaultFmtpAttributeLL, Teardown)

EUNIT_TEST (
   "DoMccEncodeComfortNoiseL test",
   "CMceComAudioCodec",
   "DoMccEncodeComfortNoiseL",
   "FUNCTIONALITY",
   SetupL, UT_CMceComAudioCodec_DoMccEncodeComfortNoiseLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
