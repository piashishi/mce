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
#include <mmcccodecinformation.h>
#include <mmcccodecinformationfactory.h>
#include <mceamrwbcodec.h>
#include "ut_mcecomfactory.h"
#include "mcecomfactory.h"
#include "mcecomaudiocodec.h"
#include "mcecomvideocodec.h"
#include "mceg711codec.h"
#include "mceg729codec.h"
#include "mcecncodec.h"
#include "mcetestdefs.h"
#include "mcecomamrwbcodec.h"
#include "mceserial.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


const TUint KMceInvalidPayloadType = 200;
_LIT8( KMceInvalidSDPCodec, "INVALID-CODEC" );   


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_MceComFactory* UT_MceComFactory::NewL()
    {
    UT_MceComFactory* self = UT_MceComFactory::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_MceComFactory* UT_MceComFactory::NewLC()
    {
    UT_MceComFactory* self = new( ELeave ) UT_MceComFactory();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_MceComFactory::~UT_MceComFactory()
    {
    }

// Default constructor
UT_MceComFactory::UT_MceComFactory()
    {
    }

// Second phase construct
void UT_MceComFactory::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_MceComFactory::SetupL()
    {
    iCodecFactory = CMccCodecInformationFactory::NewL();
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_MceComFactory::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
	delete iCodecFactory;
	iCodecFactory = NULL;
    }

void UT_MceComFactory::UT_MceComFactory_CMceComMediaStream_CreateLCL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_CMceComMediaStream_CreateLC1L()
    {
    }

void UT_MceComFactory::UT_MceComFactory_CMceComMediaSource_CreateLCL()
    {
    }
    
void UT_MceComFactory::UT_MceComFactory_CMceComMediaSource_CreateLC1L()
    {
    }

void UT_MceComFactory::UT_MceComFactory_CMceComMediaSink_CreateLCL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_CMceComMediaSink_CreateLC1L()
    {
    }

void UT_MceComFactory::UT_MceComFactory_CMceComAudioCodec_CreateLCL()
    {
    //Invalid Audio Codec Test
	CMceComAudioCodec* audioCodec;
	TRAPD( err, audioCodec = iAudioFactory.CreateLC( KMceInvalidSDPCodec()));
    EUNIT_ASSERT( err == KErrNotSupported );

	// Valid Code Test (AMR-WB)
    CMceComAudioCodec* audioCodec1 = iAudioFactory.CreateLC( KMceSDPNameAMRWB() );
    EUNIT_ASSERT( audioCodec1 ); 
    EUNIT_ASSERT( audioCodec1->iSdpName == KMceSDPNameAMRWB ); 
    CleanupStack::PopAndDestroy( audioCodec1 );
    }

void UT_MceComFactory::UT_MceComFactory_CMceComAudioCodec_CreateLC1L()
    {
    //TBD
    }

void UT_MceComFactory::UT_MceComFactory_CMceComAudioCodec_CreateCodecLCL()
    {
    // Test Based on payload Name.
    // Invalid Code Test
    CMceComAudioCodec* audioCodec = iAudioFactory.CreateCodecLC( KMceInvalidSDPCodec() );
    EUNIT_ASSERT( !audioCodec ); 
	delete audioCodec;
	audioCodec = NULL;

	// Valid Code Test (AMR-WB)
    CMceComAudioCodec* audioCodec1 = iAudioFactory.CreateCodecLC( KMceSDPNameAMRWB() );
    EUNIT_ASSERT( audioCodec1 ); 
    EUNIT_ASSERT( audioCodec1->iSdpName == KMceSDPNameAMRWB ); 
    CleanupStack::PopAndDestroy( audioCodec1 );
    
  	// Valid Code Test (PCMU)
    CMceComAudioCodec* audioCodec2 = iAudioFactory.CreateCodecLC( KMceSDPNamePCMU() );
    EUNIT_ASSERT( audioCodec2 ); 
    EUNIT_ASSERT( audioCodec2->iSdpName == KMceSDPNamePCMU ); 
    CleanupStack::PopAndDestroy( audioCodec2 );

	// Valid Code Test (PCMA)
    CMceComAudioCodec* audioCodec3 = iAudioFactory.CreateCodecLC( KMceSDPNamePCMA() );
    EUNIT_ASSERT( audioCodec3 ); 
    EUNIT_ASSERT( audioCodec3->iSdpName == KMceSDPNamePCMA ); 
    CleanupStack::PopAndDestroy( audioCodec3 );

	// Valid Code Test (AMR)
    CMceComAudioCodec* audioCodec4 = iAudioFactory.CreateCodecLC( KMceSDPNameAMR() );
    EUNIT_ASSERT( audioCodec4 ); 
    EUNIT_ASSERT( audioCodec4->iSdpName == KMceSDPNameAMR ); 
    CleanupStack::PopAndDestroy( audioCodec1 );

	// Valid Code Test (G729)
    CMceComAudioCodec* audioCodec5 = iAudioFactory.CreateCodecLC( KMceSDPNameG729() );
    EUNIT_ASSERT( audioCodec5 ); 
    EUNIT_ASSERT( audioCodec5->iSdpName == KMceSDPNameG729 ); 
    CleanupStack::PopAndDestroy( audioCodec5 );

	// Valid Code Test (iLBC)
    CMceComAudioCodec* audioCodec6 = iAudioFactory.CreateCodecLC( KMceSDPNameiLBC() );
    EUNIT_ASSERT( audioCodec6 ); 
    EUNIT_ASSERT( audioCodec6->iSdpName == KMceSDPNameiLBC ); 
    CleanupStack::PopAndDestroy( audioCodec6 );

	// Valid Code Test (telephone-event)
    CMceComAudioCodec* audioCodec7 = iAudioFactory.CreateCodecLC( KMceSDPNameDtmf() );
    EUNIT_ASSERT( audioCodec7 ); 
    EUNIT_ASSERT( audioCodec7->iSdpName == KMceSDPNameDtmf ); 
    CleanupStack::PopAndDestroy( audioCodec7 );

	// Valid Code Test (CN)
    CMceComAudioCodec* audioCodec8 = iAudioFactory.CreateCodecLC( KMceSDPNameCn() );
    EUNIT_ASSERT( audioCodec8 ); 
    EUNIT_ASSERT( audioCodec8->iSdpName == KMceSDPNameCn ); 
    CleanupStack::PopAndDestroy( audioCodec8 );

	// Valid Code Test (red)
    CMceComAudioCodec* audioCodec9 = iAudioFactory.CreateCodecLC( KMceSDPNameRed() );
    EUNIT_ASSERT( audioCodec9 ); 
    EUNIT_ASSERT( audioCodec9->iSdpName == KMceSDPNameRed ); 
    CleanupStack::PopAndDestroy( audioCodec9 );
    }

void UT_MceComFactory::UT_MceComFactory_CMceComAudioCodec_CreateCodecLC1L()
    {
    //Invalid Code Test
    //Codec with Dynamic Payload Type like AMR / AMR-WB and iLBC are not created using
    //payload type.
    
    CMceComAudioCodec* audioCodec = iAudioFactory.CreateCodecLC( KMceInvalidPayloadType );
    EUNIT_ASSERT( !audioCodec ); 
	delete audioCodec;
	audioCodec = NULL;

	// Valid Code Test (PCMU)
    CMceComAudioCodec* audioCodec1 = iAudioFactory.CreateCodecLC( KMcePCMUPayloadType );
    EUNIT_ASSERT( audioCodec1 ); 
    EUNIT_ASSERT( audioCodec1->iPayloadType == KMcePCMUPayloadType );
    EUNIT_ASSERT( audioCodec1->iSdpName == KMceSDPNamePCMU );  
    CleanupStack::PopAndDestroy( audioCodec1 );

	// Valid Code Test (PCMA)
    CMceComAudioCodec* audioCodec2 = iAudioFactory.CreateCodecLC( KMcePCMAPayloadType );
    EUNIT_ASSERT( audioCodec2 ); 
    EUNIT_ASSERT( audioCodec2->iPayloadType == KMcePCMAPayloadType ); 
    EUNIT_ASSERT( audioCodec2->iSdpName == KMceSDPNamePCMA );  
    CleanupStack::PopAndDestroy( audioCodec2 );
	    
	// Valid Code Test (G729)
    CMceComAudioCodec* audioCodec3 = iAudioFactory.CreateCodecLC( KMceDefaultG729PayloadType );
    EUNIT_ASSERT( audioCodec3 ); 
    EUNIT_ASSERT( audioCodec3->iPayloadType == KMceDefaultG729PayloadType ); 
    EUNIT_ASSERT( audioCodec2->iSdpName == KMceSDPNameG729 );  
    CleanupStack::PopAndDestroy( audioCodec3 );

	// Valid Code Test (CN-1)
    CMceComAudioCodec* audioCodec4 = iAudioFactory.CreateCodecLC( KMceDefaultCnPayloadType );
    EUNIT_ASSERT( audioCodec4 ); 
    EUNIT_ASSERT( audioCodec4->iPayloadType == KMceDefaultCnPayloadType ); 
    EUNIT_ASSERT( audioCodec4->iSdpName == KMceSDPNameCn );  
    CleanupStack::PopAndDestroy( audioCodec4 );
    
   	// Valid Code Test (CN-2)
    CMceComAudioCodec* audioCodec5 = iAudioFactory.CreateCodecLC( KMceDefaultCnPayloadType2 );
    EUNIT_ASSERT( audioCodec5 ); 
    EUNIT_ASSERT( audioCodec5->iPayloadType == KMceDefaultCnPayloadType2 ); 
    EUNIT_ASSERT( audioCodec5->iSdpName == KMceSDPNameCn );  
    CleanupStack::PopAndDestroy( audioCodec5 );
    }

void UT_MceComFactory::UT_MceComFactory_CMceComVideoCodec_CreateLCL()
    {
    // Invalid Codec
	CMceComVideoCodec* videoCodec;
	TRAPD( err, videoCodec = iVideoFactory.CreateLC( KMceInvalidSDPCodec()));
    EUNIT_ASSERT( err == KErrNotSupported );
	
	// Valid Code Test (H263)
    CMceComVideoCodec* videoCodec1 = iVideoFactory.CreateLC( KMceSDPNameH263() );
    EUNIT_ASSERT( videoCodec1 ); 
    EUNIT_ASSERT( videoCodec1->iSdpName == KMceSDPNameH263 ); 
    CleanupStack::PopAndDestroy( videoCodec1 );
    }

void UT_MceComFactory::UT_MceComFactory_CMceComVideoCodec_CreateLC1L()
    {
    // TBD 
    }

void UT_MceComFactory::UT_MceComFactory_CMceComVideoCodec_CreateCodecLCL()
    {
    //Invalid Coded Test. Earlier unknown codecs created
    // dummy codec instance but that is not needed even for transcoding
    
    CMceComVideoCodec* videoCodec = iVideoFactory.CreateCodecLC( KMceInvalidSDPCodec() );
    EUNIT_ASSERT( !videoCodec ); 

	// Valid Code Test (H263)
    CMceComVideoCodec* videoCodec1 = iVideoFactory.CreateCodecLC( KMceSDPNameH263() );
    EUNIT_ASSERT( videoCodec1 ); 
    EUNIT_ASSERT( videoCodec1->iSdpName == KMceSDPNameH263 ); 
    CleanupStack::PopAndDestroy( videoCodec1 );
    
  	// Valid Code Test (H263-2000)
    CMceComVideoCodec* videoCodec2 = iVideoFactory.CreateCodecLC( KMceSDPNameH2632000() );
    EUNIT_ASSERT( videoCodec2 ); 
    EUNIT_ASSERT( videoCodec2->iSdpName == KMceSDPNameH2632000 ); 
    CleanupStack::PopAndDestroy( videoCodec2 );
	
	// Valid Code Test (H263-1998)
    CMceComVideoCodec* videoCodec3 = iVideoFactory.CreateCodecLC( KMceSDPNameH2631998() );
    EUNIT_ASSERT( videoCodec3 ); 
    EUNIT_ASSERT( videoCodec3->iSdpName == KMceSDPNameH2631998 ); 
    CleanupStack::PopAndDestroy( videoCodec3 );
    
  	// Valid Code Test (H264)
    CMceComVideoCodec* videoCodec4 = iVideoFactory.CreateCodecLC( KMceSDPNameH264() );
    EUNIT_ASSERT( videoCodec4 ); 
    EUNIT_ASSERT( videoCodec4->iSdpName == KMceSDPNameH264 ); 
    CleanupStack::PopAndDestroy( videoCodec4 );
    }

void UT_MceComFactory::UT_MceComFactory_CMceComVideoCodec_CreateCodecLC1L()
    {
    //Invalid Code Test
    //Video Codecs are currenlty only created using codec SDP Name
    CMceComVideoCodec* videoCodec = iVideoFactory.CreateCodecLC( KMceInvalidPayloadType );
    EUNIT_ASSERT( !videoCodec ); 
	delete videoCodec;
	videoCodec = NULL;
    }

void UT_MceComFactory::UT_MceComFactory_CMceComSession_CreateLCL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_CMceMsgBase_CreateLL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_CMceMsgBase_CreateL1L()
    {
    }

void UT_MceComFactory::UT_MceComFactory_CreateBundleLCL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_CreateLCL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_MediaStreamFactoryL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_SourceFactoryL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_SinkFactoryL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_AudioCodecFactoryL()
    {
    }

void UT_MceComFactory::UT_MceComFactory_VideoCodecFactoryL()
    {
    }

	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_MceComFactory,
    "MceComFactory tests",
    "UNIT" )

EUNIT_TEST (
    "TMceComMediaStreamFactory::CreateLC test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComMediaStream_CreateLCL, Teardown)

EUNIT_TEST (
    "TMceComMediaStreamFactory::CreateLC(sc) test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComMediaStream_CreateLC1L, Teardown)

EUNIT_TEST (
    "TMceComSourceFactory::CreateLC test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComMediaSource_CreateLCL, Teardown)

EUNIT_TEST (
    "TMceComSourceFactory::CreateLC(sc) test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComMediaSource_CreateLC1L, Teardown)

EUNIT_TEST (
    "TMceComSinkFactory::CreateLC sink test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComMediaSink_CreateLCL, Teardown)


EUNIT_TEST (
    "TMceComSinkFactory::CreateLC(sc) sink test",
    "MceComFactory",
    "CreateLC1",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComMediaSink_CreateLC1L, Teardown)

EUNIT_TEST (
    "TMceComAudioCodecFactory::CreateLC test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComAudioCodec_CreateLCL, Teardown)

EUNIT_TEST (
    "TMceComAudioCodecFactory::CreateLC(sc) test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComAudioCodec_CreateLC1L, Teardown)


EUNIT_TEST (
    "TMceComAudioCodecFactory::CreateCodecLC test",
    "MceComFactory",
    "CreateCodecLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComAudioCodec_CreateCodecLCL, Teardown)

EUNIT_TEST (
    "TMceComAudioCodecFactory::CreateCodecLC(pl) test",
    "MceComFactory",
    "CreateCodecLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComAudioCodec_CreateCodecLC1L, Teardown)

EUNIT_TEST (
    "TMceComVideoCodecFactory::CreateLC test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComVideoCodec_CreateLCL, Teardown)

EUNIT_TEST (
    "TMceComVideoCodecFactory::CreateLC(sc) test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComVideoCodec_CreateLC1L, Teardown)

EUNIT_TEST (
    "TMceComVideoCodecFactory::CreateCodecLC test",
    "MceComFactory",
    "CreateCodecLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComVideoCodec_CreateCodecLCL, Teardown)

EUNIT_TEST (
    "TMceComVideoCodecFactory::CreateCodecLC(pl) test",
    "MceComFactory",
    "CreateCodecLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComVideoCodec_CreateCodecLC1L, Teardown)

EUNIT_TEST (
    "CreateLC session test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceComSession_CreateLCL, Teardown)

EUNIT_TEST (
    "CreateLC msg test",
    "MceComFactory",
    "CreateLC1",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceMsgBase_CreateLL, Teardown)

EUNIT_TEST (
    "CreateLC(sc) msg test",
    "MceComFactory",
    "CreateLC1",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CMceMsgBase_CreateL1L, Teardown)

EUNIT_TEST (
    "CreateBundleLC test",
    "MceComFactory",
    "CreateBundleLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CreateBundleLCL, Teardown)

EUNIT_TEST (
    "CreateLC test",
    "MceComFactory",
    "CreateLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_CreateLCL, Teardown)

EUNIT_TEST (
    "MediaStreamFactory test",
    "MceComFactory",
    "MediaStreamFactory",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_MediaStreamFactoryL, Teardown)

EUNIT_TEST (
    "SourceFactory test",
    "MceComFactory",
    "SourceFactory",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_SourceFactoryL, Teardown)

EUNIT_TEST (
    "SinkFactory test",
    "MceComFactory",
    "SinkFactory",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_SinkFactoryL, Teardown)

EUNIT_TEST (
    "AudioCodecFactory test",
    "MceComFactory",
    "AudioCodecFactory",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_AudioCodecFactoryL, Teardown)

EUNIT_TEST (
    "VideoCodecFactory test",
    "MceComFactory",
    "VideoCodecFactory",
    "FUNCTIONALITY",
    SetupL, UT_MceComFactory_VideoCodecFactoryL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
