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
#include "ut_cmcecomavccodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mceavccodec.h>
#include "mcemediamanager.h"
#include "mcecomavccodec.h"
#include "mmcccodecavc.h"
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
UT_CMceComAvcCodec* UT_CMceComAvcCodec::NewL()
    {
    UT_CMceComAvcCodec* self = UT_CMceComAvcCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComAvcCodec* UT_CMceComAvcCodec::NewLC()
    {
    UT_CMceComAvcCodec* self = new( ELeave ) UT_CMceComAvcCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComAvcCodec::~UT_CMceComAvcCodec()
    {
    }

// Default constructor
UT_CMceComAvcCodec::UT_CMceComAvcCodec()
    {
    }

// Second phase construct
void UT_CMceComAvcCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComAvcCodec::SetupL()
    {
    CMccControllerStub::OpenL();
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    TMceComVideoCodecFactory factory;
    iCodec = static_cast<CMceComAvcCodec*>( 
        factory.CreateCodecLC( KMceSDPNameH264() ) );
    CleanupStack::Pop( iCodec );

    } 

void UT_CMceComAvcCodec::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
	delete iCodec;
	iCodec = NULL;
	CMccControllerStub::Close();
    }

void UT_CMceComAvcCodec::Setup2L()
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

void UT_CMceComAvcCodec::Teardown2()
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

	
void UT_CMceComAvcCodec::UT_CMceComAvcCodec_NewLL()
    {
    delete iCodec;
    iCodec = NULL;
    iCodec = CMceComAvcCodec::NewL( KMceSDPNameH264() );
    
    EUNIT_ASSERT( iCodec );
    
    }


void UT_CMceComAvcCodec::UT_CMceComAvcCodec_SetBitrateL()
    {
    iCodec->iBitrate = 0;
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAvcLevel1BitrateBps ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAvcLevel1BitrateBps );
    EUNIT_ASSERT( iCodec->SetBitrate( 0 ) != KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAvcLevel1BitrateBps );
    }

void UT_CMceComAvcCodec::UT_CMceComAvcCodec_SetAllowedBitratesL()
    {
    
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 0 ) != KErrNone );
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAvcBitrateAll ) == KErrNone );
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAvcLevel1BitrateBps ) != KErrNone );
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAvcDefaultAllowedBitrate ) == KErrNone );
    
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 
        MCE_AVC_ALLOWED_BITRATES( KMceAvcCodecProfileIdBaseline, 
                                  KMceAvcCodecProfileIopConstraintSet, 
                                  KMceAvcBitrateLevel1 ) ) == KErrNone );    
    EUNIT_ASSERT_EQUALS( iCodec->iMaxBitRate, KMceAvcLevel1BitrateBps );
    
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 
        MCE_AVC_ALLOWED_BITRATES( KMceAvcCodecProfileIdBaseline, 
                                  KMceAvcCodecProfileIopConstraintSet, 
                                  KMceAvcBitrateLevel1b ) ) == KErrNone ); 
    EUNIT_ASSERT_EQUALS( iCodec->iMaxBitRate, KMceAvcLevel1bBitrateBps );
    
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 
        MCE_AVC_ALLOWED_BITRATES( KMceAvcCodecProfileIdBaseline, 
                                  KMceAvcCodecProfileIopConstraintSet, 
                                  KMceAvcBitrateLevel1_1 ) ) == KErrNone ); 
    EUNIT_ASSERT_EQUALS( iCodec->iMaxBitRate, KMceAvcLevel11BitrateBps );
    
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 
        MCE_AVC_ALLOWED_BITRATES( KMceAvcCodecProfileIdBaseline, 
                                  KMceAvcCodecProfileIopConstraintSet, 
                                  KMceAvcBitrateLevel1_2 ) ) == KErrNone ); 
    EUNIT_ASSERT_EQUALS( iCodec->iMaxBitRate, KMceAvcLevel12BitrateBps );
    
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 
        MCE_AVC_ALLOWED_BITRATES( KMceAvcCodecProfileIdBaseline, 
                                  KMceAvcCodecProfileIopConstraintSet, 
                                  KMceAvcBitrateLevel1_3 ) ) == KErrNone ); 
    EUNIT_ASSERT_EQUALS( iCodec->iMaxBitRate, KMceAvcLevel13BitrateBps );
    
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 
        MCE_AVC_ALLOWED_BITRATES( KMceAvcCodecProfileIdBaseline, 
                                  KMceAvcCodecProfileIopConstraintSet, 
                                  KMceAvcBitrateLevel2 ) ) == KErrNone ); 
    EUNIT_ASSERT_EQUALS( iCodec->iMaxBitRate, KMceAvcLevel2BitrateBps );
    }

void UT_CMceComAvcCodec::UT_CMceComAvcCodec_GetMaxBitRateL()
    {
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAvcLevel1BitrateBps );
    iCodec->iAllowedBitrates = 0;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == 0 );
    
    }

void UT_CMceComAvcCodec::UT_CMceComAvcCodec_SetMaxBitrateL()
    {
    const TUint KNotAllowedBitrate = 0xFFFF;
    
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KMceAvcLevel1BitrateBps ) == KErrNone );
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KNotAllowedBitrate ) != KErrNone );
    
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KMceAvcLevel1bBitrateBps ) == KErrNone );
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KMceAvcLevel11BitrateBps ) == KErrNone );
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KMceAvcLevel12BitrateBps ) == KErrNone );
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KMceAvcLevel13BitrateBps ) == KErrNone );
    EUNIT_ASSERT( iCodec->SetMaxBitrate( KMceAvcLevel2BitrateBps ) == KErrNone );
    }

void UT_CMceComAvcCodec::UT_CMceComAvcCodec_ResolveAllowedBitratesL()
    {

    TUint allowedBitrates = 0;

    TUint allowedBitrate = KMceAvcLevel1BitrateBps;
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( allowedBitrate, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAvcCodecProfileIdBaseline | 
                                     KMceAvcCodecProfileIopConstraintSet | 
                                     KMceAvcBitrateLevel1 );
    
    allowedBitrate = KMceAvcLevel1bBitrateBps - 1;
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( allowedBitrate, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAvcCodecProfileIdBaseline | 
                                     KMceAvcCodecProfileIopConstraintSet | 
                                     KMceAvcBitrateLevel1b );
    
    allowedBitrate = KMceAvcLevel11BitrateBps;
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( allowedBitrate, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAvcCodecProfileIdBaseline | 
                                     KMceAvcCodecProfileIopConstraintSet | 
                                     KMceAvcBitrateLevel1_1 );
                                     
    
    allowedBitrate = KMceAvcLevel12BitrateBps;
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( allowedBitrate, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAvcCodecProfileIdBaseline | 
                                     KMceAvcCodecProfileIopConstraintSet | 
                                     KMceAvcBitrateLevel1_2 );
    
    allowedBitrate = KMceAvcLevel13BitrateBps;
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( allowedBitrate, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAvcCodecProfileIdBaseline | 
                                     KMceAvcCodecProfileIopConstraintSet | 
                                     KMceAvcBitrateLevel1_3 );
    
    allowedBitrate = KMceAvcLevel2BitrateBps;
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( allowedBitrate, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAvcCodecProfileIdBaseline | 
                                     KMceAvcCodecProfileIopConstraintSet | 
                                     KMceAvcBitrateLevel2 );
   
    // Not supported bitrate
    allowedBitrate = KMceAvcLevel2BitrateBps + 100;                                                                                                    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( allowedBitrate,  allowedBitrates ) != KErrNone ); 
    
    
    }

void UT_CMceComAvcCodec::UT_CMceComAvcCodec_CloneLL()
    {
    CMceComVideoCodec* clone = NULL;
    clone = iCodec->CloneL();
    delete clone;
    }

void UT_CMceComAvcCodec::UT_CMceComAvcCodec_DecodesL()
    {
    // Strict decoding:
    //
    
    // Decodes level 1 when there's no fmtp yet set
    _LIT8( KProfileLevel1, "profile-level-id=42800A" );
    EUNIT_ASSERT( iCodec->Decodes( KMceSDPNameH264(), KProfileLevel1() ) );
    
    // Decodes level 1 when input fmtp is empty
    EUNIT_ASSERT( iCodec->Decodes( KMceSDPNameH264(), KNullDesC8() ) );
    
    // Doesn't decode level 1b when level 1 is set
    _LIT8( KProfileLevel1b, "profile-level-id=42900B" );
    EUNIT_ASSERT( !iCodec->Decodes( KMceSDPNameH264(), KProfileLevel1b() ) );
    
    // Doesn't decode level 1 as packetization-mode is different
    _LIT8( KProfileLevel1NonInterleaved, "profile-level-id=42800A; packetization-mode=1" );
    EUNIT_ASSERT( !iCodec->Decodes( KMceSDPNameH264(), KProfileLevel1NonInterleaved() ) );
    
    // Decodes as packetization-modes are equal
    _LIT8( KProfileLevel1SingleNal, "profile-level-id=42800A; packetization-mode=0" );
    EUNIT_ASSERT( iCodec->Decodes( KMceSDPNameH264(), KProfileLevel1SingleNal() ) );
    
    // Less strict decoding:
    //
    
    // Decodes downgraded level
    iCodec->SetFmtpAttributeL( KProfileLevel1b(), ETrue );
    EUNIT_ASSERT( iCodec->Decodes( KMceSDPNameH264(), KProfileLevel1(), EFalse ) );
    
    // Decodes upgraded level
    _LIT8( KProfileLevel3, "profile-level-id=42901E" );
    EUNIT_ASSERT( iCodec->Decodes( KMceSDPNameH264(), KProfileLevel3(), EFalse  ) );
    
    // Does not decode upgraded level as packetization mode does not match
    _LIT8( KProfileLevel3NonInterleaved, "profile-level-id=42901E;packetization-mode=1" );
    EUNIT_ASSERT( !iCodec->Decodes( KMceSDPNameH264(), KProfileLevel3NonInterleaved(), EFalse  ) );
    }

void UT_CMceComAvcCodec::UT_CMceComAvcCodec_SetFmtpProposalLL()
    {
    _LIT8( KProfileLevel1, "profile-level-id=42800A" );
    EUNIT_ASSERT( iCodec->SetFmtpProposalL( KProfileLevel1() ) );
    
    CMccControllerStub::Stub()->iSetFmtpFailure = ETrue;
    EUNIT_ASSERT( !iCodec->SetFmtpProposalL( KProfileLevel1() ) );
    }

void UT_CMceComAvcCodec::UT_CMceComAvcCodec_SetFmtpFromIncomingSdpLL()
    {
    TBool isAnswerer( ETrue );
    
    // Sprop-parameter-sets should be set to config key of receive stream
    // in case they are in fmtp of send stream
    //

    // Fmtp does not contains sprop-parameter-sets
    _LIT8( KMceTestFmtp, "profile-level-id=42800A" );
    iSendCodec->SetFmtpFromIncomingSdpL( KMceTestFmtp(), isAnswerer );
    EUNIT_ASSERT( iReceiveCodec->iConfigKey == NULL );
    
    // Fmtp contains sprop-parameter-sets but stream is incorrect
    _LIT8( KMceTestFmtp2, "profile-level-id=42800A; sprop-parameter-sets=133434134==" );
    iReceiveCodec->SetFmtpFromIncomingSdpL( KMceTestFmtp2(), isAnswerer );
    EUNIT_ASSERT( iReceiveCodec->iConfigKey == NULL );
    
    // Fmtp contains sprop-parameter-sets, stream correct, no bound codec found
    _LIT8( KMceTestFmtp3, "profile-level-id=42800C; sprop-parameter-sets=133434134==" );
    HBufC8* fmtpTemp = iReceiveCodec->iFmtpAttr;
    CleanupStack::PushL( fmtpTemp );
    iReceiveCodec->iFmtpAttr = NULL;
    iReceiveCodec->iFmtpAttr = KMceTestFmtp3().AllocL();
    iSendCodec->SetFmtpFromIncomingSdpL( KMceTestFmtp2(), isAnswerer );
    EUNIT_ASSERT( iReceiveCodec->iConfigKey == NULL );
    delete iReceiveCodec->iFmtpAttr;
    iReceiveCodec->iFmtpAttr = fmtpTemp;
    CleanupStack::Pop( fmtpTemp );
    
    // Fmtp contains sprop-parameter-sets, stream correct, bound codec, no fmtp param separator
    _LIT8( KMceTestFmtp4, "profile-level-id=42800A; sprop-parameter-sets=11111111==" );
    iSendCodec->SetFmtpFromIncomingSdpL( KMceTestFmtp4(), isAnswerer );
    EUNIT_ASSERT( iReceiveCodec->iConfigKey != NULL );
    EUNIT_ASSERT( iReceiveCodec->iConfigKey->CompareF( _L8("11111111==") ) == 0 );
    
    // Fmtp contains sprop-parameter-sets, stream correct, bound codec, fmtp param separator
    _LIT8( KMceTestFmtp5, "profile-level-id=42800A; sprop-parameter-sets=222222222==; packetization-mode=1" );
    iSendCodec->SetFmtpFromIncomingSdpL( KMceTestFmtp5(), isAnswerer );
    EUNIT_ASSERT( iReceiveCodec->iConfigKey != NULL );
    EUNIT_ASSERT( iReceiveCodec->iConfigKey->CompareF( _L8("222222222==") ) == 0 );
    
    // Fmtp contains faulty sprop-parameter-sets
    _LIT8( KMceTestFmtp6, "profile-level-id=42800A; sprop-parameter-sets=" );
    iSendCodec->SetFmtpFromIncomingSdpL( KMceTestFmtp6(), isAnswerer );
    EUNIT_ASSERT( iReceiveCodec->iConfigKey != NULL );
    EUNIT_ASSERT( iReceiveCodec->iConfigKey->CompareF( _L8("222222222==") ) == 0 );
    }
    
void UT_CMceComAvcCodec::UT_CMceComAvcCodec_SetFmtpFromIncomingSdpL2L()
    {
    // At offerer side we are more tolerant for better interoperability.
    // Incorrect fmtp of anwer is modified to correct
    TBool isAnswerer( EFalse );
    
    // Same answer as offered, no need to modify
    _LIT8( KMceTestLevel1bFmtp, "profile-level-id=42900B" );
    iCodec->SetFmtpAttributeL( KMceTestLevel1bFmtp, ETrue );
    iCodec->SetFmtpFromIncomingSdpL( KMceTestLevel1bFmtp, isAnswerer );
    EUNIT_ASSERT( iCodec->FmtpAttr().Compare( KMceTestLevel1bFmtp() ) == 0 );
    
    // Downgraded answer, fmtp stays at level 1b
    _LIT8( KMceTestLevel1Fmtp, "profile-level-id=42800A" );
    iCodec->SetFmtpFromIncomingSdpL( KMceTestLevel1Fmtp, isAnswerer );
    EUNIT_ASSERT( iCodec->FmtpAttr().Compare( KMceTestLevel1bFmtp() ) == 0 );
    
    // Upgraded answer, fmtp stays at level 1b
    _LIT8( KMceTestLevel3Fmtp, "profile-level-id=42901E" );
    iCodec->SetFmtpFromIncomingSdpL( KMceTestLevel3Fmtp, isAnswerer );
    EUNIT_ASSERT( iCodec->FmtpAttr().Compare( KMceTestLevel1bFmtp() ) == 0 );
    
    // Incoming fmtp is totally wrong, cannot tolerate (it is taken in use
    // without modifications but will cause failure later)
    _LIT8( KMceTestWrongFmtp, "profile-level-id=45" );
    iCodec->SetFmtpFromIncomingSdpL( KMceTestWrongFmtp, isAnswerer );
    EUNIT_ASSERT( iCodec->FmtpAttr().Compare( KMceTestWrongFmtp() ) == 0 );
    }
    
void UT_CMceComAvcCodec::UT_CMceComAvcCodec_FtmpForOutgoingSdpLCL()
    {
    _LIT8( KMceTestFmtp, "profile-level-id=42800A" );
    iSendCodec->SetFmtpAttributeL( KMceTestFmtp );
    
    // Wrong stream
    HBufC8* fmtp = iSendCodec->FtmpForOutgoingSdpLC();
    EUNIT_ASSERT( fmtp->CompareF( KMceTestFmtp() ) == 0 );
    CleanupStack::PopAndDestroy( fmtp );
    fmtp = NULL;
    
    // No conf key in bound codec
    iReceiveCodec->SetFmtpAttributeL( KMceTestFmtp );
    fmtp = iReceiveCodec->FtmpForOutgoingSdpLC();
    EUNIT_ASSERT( fmtp->CompareF( KMceTestFmtp() ) == 0 );
    CleanupStack::PopAndDestroy( fmtp );
    fmtp = NULL;
    
    // No sprop-parameter-sets in existing fmtp attr and no separators
    _LIT8( KOutputFmtp, "profile-level-id=42800A; sprop-parameter-sets=11111111==" );
    _LIT8( KTestConfigKey, "11111111==");
    delete iSendCodec->iConfigKey;
    iSendCodec->iConfigKey = NULL;
    iSendCodec->iConfigKey = KTestConfigKey().AllocL();
    fmtp = iReceiveCodec->FtmpForOutgoingSdpLC();
    EUNIT_ASSERT( fmtp->CompareF( KOutputFmtp() ) == 0 );
    CleanupStack::PopAndDestroy( fmtp );
    fmtp = NULL;
    
    // No sprop-parameter-sets in existing fmtp attr, separators exist at end (";")
    _LIT8( KMceTestFmtp2, "profile-level-id=42800A;" );
    iReceiveCodec->SetFmtpAttributeL( KMceTestFmtp2 );
    fmtp = iReceiveCodec->FtmpForOutgoingSdpLC();
    EUNIT_ASSERT( fmtp->CompareF( KOutputFmtp() ) == 0 );
    CleanupStack::PopAndDestroy( fmtp );
    fmtp = NULL;
    
    // No sprop-parameter-sets in existing fmtp attr, separators exist at end ("; ")
    _LIT8( KMceTestFmtp3, "profile-level-id=42800A; " );
    iReceiveCodec->SetFmtpAttributeL( KMceTestFmtp3 );
    fmtp = iReceiveCodec->FtmpForOutgoingSdpLC();
    EUNIT_ASSERT( fmtp->CompareF( KOutputFmtp() ) == 0 );
    CleanupStack::PopAndDestroy( fmtp );
    fmtp = NULL;
    
    // Sprop-parameter-sets in existing fmtp attr, no separators exist at end
    _LIT8( KMceTestFmtp4, "profile-level-id=42800A; sprop-parameter-sets=22222==" );
    iReceiveCodec->SetFmtpAttributeL( KMceTestFmtp4 );
    fmtp = iReceiveCodec->FtmpForOutgoingSdpLC();
    EUNIT_ASSERT( fmtp->CompareF( KOutputFmtp() ) == 0 );
    CleanupStack::PopAndDestroy( fmtp );
    fmtp = NULL;
    
    // Sprop-parameter-sets in existing fmtp attr, separator exist at end
    _LIT8( KMceTestFmtp5, "profile-level-id=42800A; sprop-parameter-sets=222222222222==; " );
    iReceiveCodec->SetFmtpAttributeL( KMceTestFmtp5 );
    fmtp = iReceiveCodec->FtmpForOutgoingSdpLC();
    EUNIT_ASSERT( fmtp->CompareF( KOutputFmtp() ) == 0 );
    CleanupStack::PopAndDestroy( fmtp );
    fmtp = NULL;
    }
        
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComAvcCodec,
    "CMceComAvcCodec tests",
    "UNIT" )

    

EUNIT_TEST (
    "NewL test",
    "CMceComAvcCodec",
    "NewL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_NewLL, Teardown)

    
EUNIT_TEST (
    "SetBitrate test",
    "CMceComAvcCodec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComAvcCodec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComAvcCodec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "SetMaxBitrate test",
    "CMceComAvcCodec",
    "SetMaxBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_SetMaxBitrateL, Teardown)

EUNIT_TEST (
    "ResolveAllowedBitrates test",
    "CMceComAvcCodec",
    "ResolveAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_ResolveAllowedBitratesL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComAvcCodec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_CloneLL, Teardown)

EUNIT_TEST (
    "Decodes test",
    "CMceComAvcCodec",
    "Decodes",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_DecodesL, Teardown)

EUNIT_TEST (
    "SetFmtpProposalL test",
    "CMceComAvcCodec",
    "SetFmtpProposalL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_SetFmtpProposalLL, Teardown)

EUNIT_TEST (
    "SetFmtpFromIncomingSdpL two-way test",
    "CMceComAvcCodec",
    "SetFmtpFromIncomingSdpL",
    "FUNCTIONALITY",
    Setup2L, UT_CMceComAvcCodec_SetFmtpFromIncomingSdpLL, Teardown2)

EUNIT_TEST (
    "SetFmtpFromIncomingSdpL one-way offerer side test",
    "CMceComAvcCodec",
    "SetFmtpFromIncomingSdpL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAvcCodec_SetFmtpFromIncomingSdpL2L, Teardown2)
        
EUNIT_TEST (
    "FtmpForOutgoingSdpLC test",
    "CMceComAvcCodec",
    "FtmpForOutgoingSdpLC",
    "FUNCTIONALITY",
    Setup2L, UT_CMceComAvcCodec_FtmpForOutgoingSdpLCL, Teardown2)
            
EUNIT_END_TEST_TABLE



//  END OF FILE
