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
#include "ut_cmcecomvideocodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mceh263codec.h>
#include "mcemediamanager.h"
#include "mcecomh263codec.h"
#include <MmccCodecInformationFactory.h>
#include "mcecomavccodec.h"
#include "mcecomvideostream.h"
#include "mcecomcamerasource.h"
#include "mcecomrtpsink.h"
#include "mcecomsession.h"
#include "mcecomfactory.h"
#include "mcecomrtpsource.h"
#include "mcecomdisplaysink.h"

#include "CMccController_stub.h"

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComVideoCodec* UT_CMceComVideoCodec::NewL()
    {
    UT_CMceComVideoCodec* self = UT_CMceComVideoCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComVideoCodec* UT_CMceComVideoCodec::NewLC()
    {
    UT_CMceComVideoCodec* self = new( ELeave ) UT_CMceComVideoCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComVideoCodec::~UT_CMceComVideoCodec()
    {
    }

// Default constructor
UT_CMceComVideoCodec::UT_CMceComVideoCodec()
    {
    }

// Second phase construct
void UT_CMceComVideoCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComVideoCodec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    TMceComVideoCodecFactory factory;
    iCodec = static_cast<CMceComH263Codec*>( 
        factory.CreateCodecLC( KMceSDPNameH263() ) );
    CleanupStack::Pop( iCodec );
    
    } 

void UT_CMceComVideoCodec::Setup2L()
    {
    CMccControllerStub::OpenL();
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    iSession = CMceComSession::NewL();
    CMceComVideoStream* stream = CMceComVideoStream::NewLC();
    CMceComMediaSource* mediaSource = CMceComCameraSource::NewLC();
    stream->SetSourceL( mediaSource );
    CleanupStack::Pop( mediaSource );
    
    CMceComMediaSink* mediaSink = CMceComRtpSink::NewLC();
    stream->AddSinkL( mediaSink );
    CleanupStack::Pop( mediaSink );
    
    TMceComVideoCodecFactory factory;
    CMceComVideoCodec* codec = factory.CreateCodecLC( KMceSDPNameH264() );
    stream->AddCodecL( codec );
    CleanupStack::Pop( codec );
    iSendCodec = codec;
    
    CMceComVideoStream* stream2 = CMceComVideoStream::NewLC();
    CMceComMediaSource* mediaSource2 = CMceComRtpSource::NewLC();
    stream2->SetSourceL( mediaSource2 );
    CleanupStack::Pop( mediaSource2 );
    
    CMceComMediaSink* mediaSink2 = CMceComDisplaySink::NewLC();
    stream2->AddSinkL( mediaSink2 );
    CleanupStack::Pop( mediaSink2 );
    
    CMceComVideoCodec* codec2 = factory.CreateCodecLC( KMceSDPNameH264() );
    stream2->AddCodecL( codec2 );
    CleanupStack::Pop( codec2 );
    iReceiveCodec = codec2;
    
    stream->BindL( stream2 );
    CleanupStack::Pop( stream2 );
    
    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    
    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    }

    
void UT_CMceComVideoCodec::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    delete iCodec;
    iCodec = NULL;
    }

void UT_CMceComVideoCodec::Teardown2()
    {
   	CMceComSession::Delete( iSession, *iManager );
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
	delete iCodec;
	iCodec = NULL;
	CMccControllerStub::Close();
    }
    
void UT_CMceComVideoCodec::UT_CMceComVideoCodec_InternalizeFlatLL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_ExternalizeFlatLL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_UpdateLL()
    {
    TMceComVideoCodecFactory factory;
    CMceComAvcCodec* codec = static_cast<CMceComAvcCodec*>( 
        factory.CreateCodecLC( KMceSDPNameH264() ) );
    
    HBufC8* configKey = _L8("confkey").AllocLC();
    codec->SetConfigKeyL( configKey );
    CleanupStack::PopAndDestroy( configKey );
    
    // In receive stream, config key is not updated
    iReceiveCodec->UpdateL( *codec );
    EUNIT_ASSERT( !iReceiveCodec->IsConfigKeyValid() );
    
    // In send codec, config key is updated
    iSendCodec->UpdateL( *codec );
    EUNIT_ASSERT( iSendCodec->IsConfigKeyValid() );
    
    CleanupStack::PopAndDestroy( codec );
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_CloneLL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_FactoryL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_operatorAssignL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_DoMccDecodeLL()
    {
    CMccCodecInformationFactory* codecfactory =CMccCodecInformationFactory::NewL();
    CleanupStack::PushL( codecfactory );
    CMccCodecInformation* codecinfo = codecfactory->CreateCodecInformationL(KAVCSdpName);
    CleanupStack::PushL( codecinfo );
    TMceComVideoCodecFactory factory;
    CMceComAvcCodec* codec = static_cast<CMceComAvcCodec*>( 
        factory.CreateCodecLC( KMceSDPNameH264() ) );
    codecinfo->SetPreferredEncodingDecodingDevice(TUid::Uid( 0x20001c13 ));
    EUNIT_ASSERT( codec->iEncodingDecodingDevice == KNullUid );
    codec->DoMccDecodeL(*codecinfo);
    EUNIT_ASSERT( codec->iEncodingDecodingDevice == TUid::Uid( 0x20001c13 ) );
    CleanupStack::PopAndDestroy( 3 );
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_DoMccEncodeLL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_DoMccValidateLL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_DoMccAdjustLL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_DoMccRequireSignallingL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_DoSetDefaultFmtpAttributeLL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_GetMaxBitRateL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_SetMaxBitrateL()
    {
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_SetConfigKeyLL()
    {
    EUNIT_ASSERT( iCodec->iConfigKey == NULL );
    HBufC8* ck = NULL;
    EUNIT_ASSERT( !iCodec->SetConfigKeyL( ck ) );
    EUNIT_ASSERT( iCodec->iConfigKey == NULL );
    
    _LIT8( Kck, "CK");
    ck = Kck().AllocLC();
    
    EUNIT_ASSERT( iCodec->SetConfigKeyL( ck ) );
    EUNIT_ASSERT( *iCodec->iConfigKey == *ck );
    
    // Same key, no need to update
    EUNIT_ASSERT( !iCodec->SetConfigKeyL( ck ) );
    
    CleanupStack::PopAndDestroy( ck );
    
    _LIT8( Kck2, "CK2");
    HBufC8* ck2 = Kck2().AllocLC();
    EUNIT_ASSERT( iCodec->SetConfigKeyL( ck2 ) );
    EUNIT_ASSERT( *iCodec->iConfigKey == *ck2 );
    
    CleanupStack::PopAndDestroy( ck2 );
    }

void UT_CMceComVideoCodec::UT_CMceComVideoCodec_IsConfigKeyValidL()
    {
    EUNIT_ASSERT( !iCodec->IsConfigKeyValid() );
    HBufC8* ck = NULL;
    _LIT8( Kck, "CK");
    ck = Kck().AllocLC();
    
    EUNIT_ASSERT( iCodec->IsConfigKeyValid( ck ) );
    
    CleanupStack::PopAndDestroy( ck );
    
    }


	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComVideoCodec,
    "CMceComVideoCodec tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComVideoCodec",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComVideoCodec",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComVideoCodec",
    "UpdateL",
    "FUNCTIONALITY",
    Setup2L, UT_CMceComVideoCodec_UpdateLL, Teardown2)

EUNIT_TEST (
    "CloneL test",
    "CMceComVideoCodec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_CloneLL, Teardown)

EUNIT_TEST (
    "Factory test",
    "CMceComVideoCodec",
    "Factory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_FactoryL, Teardown)

EUNIT_TEST (
    "operatorAssign test",
    "CMceComVideoCodec",
    "operatorAssign",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_operatorAssignL, Teardown)

EUNIT_TEST (
    "DoMccDecodeL test",
    "CMceComVideoCodec",
    "DoMccDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_DoMccDecodeLL, Teardown)

EUNIT_TEST (
    "DoMccEncodeL test",
    "CMceComVideoCodec",
    "DoMccEncodeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_DoMccEncodeLL, Teardown)

EUNIT_TEST (
    "DoMccValidateL test",
    "CMceComVideoCodec",
    "DoMccValidateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_DoMccValidateLL, Teardown)

EUNIT_TEST (
    "DoMccAdjustL test",
    "CMceComVideoCodec",
    "DoMccAdjustL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_DoMccAdjustLL, Teardown)

EUNIT_TEST (
    "DoMccRequireSignalling test",
    "CMceComVideoCodec",
    "DoMccRequireSignalling",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_DoMccRequireSignallingL, Teardown)

EUNIT_TEST (
    "DoSetDefaultFmtpAttributeL test",
    "CMceComVideoCodec",
    "DoSetDefaultFmtpAttributeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_DoSetDefaultFmtpAttributeLL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComVideoCodec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "SetMaxBitrate test",
    "CMceComVideoCodec",
    "SetMaxBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_SetMaxBitrateL, Teardown)

EUNIT_TEST (
    "SetConfigKeyL test",
    "CMceComVideoCodec",
    "SetConfigKeyL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_SetConfigKeyLL, Teardown)

EUNIT_TEST (
    "IsConfigKeyValid test",
    "CMceComVideoCodec",
    "IsConfigKeyValid",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoCodec_IsConfigKeyValidL, Teardown)


EUNIT_END_TEST_TABLE



//  END OF FILE
