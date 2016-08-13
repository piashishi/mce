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
#include "ut_cmcecomcodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mmcccodecinformation.h>
#include <mmcccodecinformationfactory.h>
#include "mcemediamanager.h"
#include "mcecomaudiostream.h"
#include "mcecommediasource.h"
#include "mcecommediasink.h"
#include "mcecomsession.h"
#include "mcecomfactory.h"
#include "mcecomaudiocodec.h"
#include "mcecomamrcodec.h"
#include "cleanupresetanddestroy.h"


_LIT8( KTestFlatData, "\x3\x0\x0\x0\x41\x4d\x52\x0\x0\x0\x0\x2\x0\x0\x0\x60\x0\x0\
\x0\x0\x14\x0\x0\x0\xa8\x2f\x0\x0\xff\x0\x0\x0\x4\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\
\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0");


_LIT8( KTestFlatDataAudio, "\x3\x0\x0\x0\x41\x4d\x52\x0\x0\x0\x0\x2\x0\x0\x0\x60\x0\
\x0\x0\x0\x14\x0\x0\x0\xa8\x2f\x0\x0\xff\x0\x0\x0\x4\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\
\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x0\x40\x1f\x14\x0\x90\x1");

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComCodec* UT_CMceComCodec::NewL()
    {
    UT_CMceComCodec* self = UT_CMceComCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComCodec* UT_CMceComCodec::NewLC()
    {
    UT_CMceComCodec* self = new( ELeave ) UT_CMceComCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComCodec::~UT_CMceComCodec()
    {
    }

// Default constructor
UT_CMceComCodec::UT_CMceComCodec()
    {
    }

// Second phase construct
void UT_CMceComCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS

#define SETUP( codec )\
    codec->iID = TMceMediaId( 2 )


void UT_CMceComCodec::SetupL()
    {
    iCodecFactory = CMccCodecInformationFactory::NewL();
    
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );

    iSession = CMceComSession::NewL();
    CMceComAudioStream* stream = CMceComAudioStream::NewLC();
    CMceComMediaSource* mediaSource = CMceComMediaSource::NewLC();
    stream->SetSourceL( mediaSource );
    CleanupStack::Pop( mediaSource );
    iSource = mediaSource;
    CMceComMediaSink* mediaSink = CMceComMediaSink::NewLC();
    stream->AddSinkL( mediaSink );
    CleanupStack::Pop( mediaSink );
    iSink = mediaSink;
    
    TMceComAudioCodecFactory factory;
    CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNameAMR() );
    stream->AddCodecL( codec );
    CleanupStack::Pop( codec );
    iCodec = codec;
    
    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    iStream = stream;
    
    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    } 

void UT_CMceComCodec::Teardown()
    {
	CMceComSession::Delete( iSession, *iManager );
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
	delete iCodecFactory;
	iCodecFactory = NULL;
    }


void UT_CMceComCodec::UT_CMceComCodec_IdL()
    {
    EUNIT_ASSERT( iCodec->Id() != 0 );
    }

void UT_CMceComCodec::UT_CMceComCodec_StreamL()
    {
    EUNIT_ASSERT( iCodec->Stream() == iStream );
    }

void UT_CMceComCodec::UT_CMceComCodec_SetFmtpAttributeLL()
    {
    EUNIT_ASSERT( *iCodec->iFmtpAttr == KNullDesC8 );
    
    delete iCodec->iFmtpAttr;
    iCodec->iFmtpAttr = NULL;
    
    iCodec->SetFmtpAttributeL( _L8("attribute1"), EFalse );
    EUNIT_ASSERT( *iCodec->iFmtpAttr == _L8("attribute1") );

    iCodec->SetFmtpAttributeL( _L8("attribute2"), ETrue );
    EUNIT_ASSERT( *iCodec->iFmtpAttr == _L8("attribute2") );

    iCodec->SetFmtpAttributeL( _L8("attribute3"), EFalse );
    EUNIT_ASSERT( *iCodec->iFmtpAttr == _L8("attribute2; attribute3") );
    
    }

void UT_CMceComCodec::UT_CMceComCodec_SetKeepAliveDataLL()
    {
    EUNIT_ASSERT( *iCodec->iKeepAliveData == KNullDesC8 );
    
    iCodec->SetKeepAliveDataL( _L8("KeepAliveData") );
    EUNIT_ASSERT( *iCodec->iKeepAliveData == _L8("KeepAliveData") );
    
    iCodec->SetKeepAliveDataL( KNullDesC8 );
    EUNIT_ASSERT( *iCodec->iKeepAliveData == KNullDesC8 );    
    }

void UT_CMceComCodec::UT_CMceComCodec_SetBitrateL()
    {
    iCodec->iBitrate = 1000;

    EUNIT_ASSERT( iCodec->CMceComCodec::SetBitrate( 2000 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == 2000 );

    EUNIT_ASSERT( iCodec->CMceComCodec::SetBitrate( 0 ) == KErrArgument );
    EUNIT_ASSERT( iCodec->iBitrate == 2000 );
    
    }

void UT_CMceComCodec::UT_CMceComCodec_SetAllowedBitratesL()
    {
    iCodec->iAllowedBitrates = 1000;
    
    EUNIT_ASSERT( iCodec->CMceComCodec::SetAllowedBitrates( 2000 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iAllowedBitrates == 2000 );
    
    }


void UT_CMceComCodec::UT_CMceComCodec_SetCodecModeL()
    {
    EUNIT_ASSERT( iCodec->CMceComCodec::SetCodecMode( 0 ) == KErrNotSupported );
    }


void UT_CMceComCodec::UT_CMceComCodec_SetPayloadTypeL()
    {
    EUNIT_ASSERT( iCodec->CMceComCodec::SetPayloadType( 1 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iPayloadType == 1 );
    
    EUNIT_ASSERT( iCodec->CMceComCodec::SetPayloadType( 
        KMaxDynPayloadType + 1 ) == KErrNotSupported );
    EUNIT_ASSERT( iCodec->iPayloadType == 1 );
    }


void UT_CMceComCodec::UT_CMceComCodec_GetMaxBitRateL()
    {
    iCodec->iBitrate = 1000;
    EUNIT_ASSERT( iCodec->CMceComCodec::GetMaxBitRate() == 1000 );
    
    }

void UT_CMceComCodec::UT_CMceComCodec_SerializationIdL()
    {
    iCodec->iID = TMceMediaId( 200 );
    TUint64 id = iCodec->iID.Uint64();
    EUNIT_ASSERT( iCodec->SerializationId() == id );
    
    }

void UT_CMceComCodec::UT_CMceComCodec_InternalizeExternalizeFlatLL()
    {
    
    TMceMediaId id = iCodec->iID;
    TMceComCodecName sdpName = iCodec->iSdpName;
    iCodec->iPayloadType = 111;
	TUint8 payloadType = iCodec->iPayloadType;
	iCodec->iFourCC = 111;
	TUint32 fourCC = iCodec->iFourCC;
	iCodec->iFrameSize = 111;
	TUint frameSize = iCodec->iFrameSize;
	iCodec->iBitrate = 111;
	TUint bitrate = iCodec->iBitrate;
	iCodec->iAllowedBitrates = 111;
	TUint32 allowedBitrates = iCodec->iAllowedBitrates;
	iCodec->iCodecMode = 111;
	TUint32 codecMode = iCodec->iCodecMode;
    iCodec->iState = 111;
	TInt state = iCodec->iState;
	iCodec->iPriority = 111;
	TInt priority = iCodec->iPriority;
	iCodec->iPriorityPreference = 111;
	TInt priorityPreference = iCodec->iPriorityPreference;
	iCodec->iKeepAliveTimer = 111;
    TUint8 keepAliveTimer = iCodec->iKeepAliveTimer;
    iCodec->iKeepAlivePayloadType = 111;
    TUint8 keepAlivePayloadType = iCodec->iKeepAlivePayloadType;
    
   	CBufFlat* encodeBuf = CBufFlat::NewL( KMceExternalizeBufferExpandSize );
	CleanupStack::PushL( encodeBuf );

    EUNIT_ASSERT( encodeBuf->Ptr( 0 ).Length() == 0 );
    
	RBufWriteStream writeStream( *encodeBuf, 0 );
	writeStream.PushL();
    
    iCodec->CMceComCodec::ExternalizeFlatL( writeStream );
    EUNIT_ASSERT( encodeBuf->Ptr( 0 ).Length() > 0 );
    
    TMceComAudioCodecFactory factory;
    CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNameAMR() );
    
	RDesReadStream readStream( encodeBuf->Ptr( 0 ) );
    CleanupClosePushL( readStream );

    codec->CMceComCodec::InternalizeFlatL( readStream );
    EUNIT_ASSERT( id == codec->iID );
    EUNIT_ASSERT( sdpName == codec->iSdpName );
	EUNIT_ASSERT( payloadType == codec->iPayloadType );
	EUNIT_ASSERT( fourCC == codec->iFourCC );
	EUNIT_ASSERT( frameSize == codec->iFrameSize );
	EUNIT_ASSERT( bitrate == codec->iBitrate );
	EUNIT_ASSERT( allowedBitrates == codec->iAllowedBitrates );
	EUNIT_ASSERT( codecMode == codec->iCodecMode );
	EUNIT_ASSERT( state == codec->iState );
	EUNIT_ASSERT( priority == codec->iPriority );
	EUNIT_ASSERT( priorityPreference == codec->iPriorityPreference );
    EUNIT_ASSERT( keepAliveTimer == codec->iKeepAliveTimer );
    EUNIT_ASSERT( keepAlivePayloadType == codec->iKeepAlivePayloadType );

	CleanupStack::PopAndDestroy(); // readStream
	CleanupStack::PopAndDestroy( codec );
	CleanupStack::PopAndDestroy(); // writeStream
	CleanupStack::PopAndDestroy( encodeBuf );
    
    }

void UT_CMceComCodec::UT_CMceComCodec_InternalizeExternalizeLL()
    {
    CBufFlat* encodeBuf = CBufFlat::NewL( KMceExternalizeBufferExpandSize );
	CleanupStack::PushL( encodeBuf );

    EUNIT_ASSERT( encodeBuf->Ptr( 0 ).Length() == 0 );
    
	RBufWriteStream writeStream( *encodeBuf, 0 );
	writeStream.PushL();
    
    MMceComSerializationContext writeCtx( writeStream );
    iCodec->CMceComCodec::ExternalizeL( writeCtx );
    
    EUNIT_ASSERT( encodeBuf->Ptr( 0 ).Length() > 0 );
    
    //null tested
	RDesReadStream readStream( encodeBuf->Ptr( 0 ) );
    CleanupClosePushL( readStream );
    MMceComSerializationContext readCtx( readStream );
    
    iCodec->CMceComCodec::InternalizeL( readCtx );

	CleanupStack::PopAndDestroy(); // readStream
	CleanupStack::PopAndDestroy(); // writeStream
	CleanupStack::PopAndDestroy( encodeBuf );
    }

void UT_CMceComCodec::UT_CMceComCodec_UpdateLL()
    {
    
    CMceComAMRCodec* update = CMceComAMRCodec::NewL( KMceSDPNameAMR() );
    CleanupStack::PushL( update );
    
    update->iSdpName = KMceSDPNamePCMA();
    update->iID = TMceMediaId( 12 );
    update->iPayloadType = 97;
    update->iFourCC = 111;
    update->iBitrate = 111;
    update->iAllowedBitrates = 111;
    update->iCodecMode = 111;
	update->iState = 111;
	update->iPriority = 111;
	update->iPriorityPreference  = 111;
    update->iKeepAliveTimer = 111;
    update->iKeepAlivePayloadType = 111;
    
    iCodec->CMceComCodec::UpdateL( *update );

    EUNIT_ASSERT( iCodec->iSdpName == KMceSDPNamePCMA() );
    EUNIT_ASSERT( iCodec->iID == TMceMediaId( 12 ) )
    EUNIT_ASSERT( iCodec->iPayloadType == 97 )
    EUNIT_ASSERT( iCodec->iFourCC == 111 )
    EUNIT_ASSERT( iCodec->iBitrate == 111 )
    EUNIT_ASSERT( iCodec->iAllowedBitrates == 111 );
    EUNIT_ASSERT( iCodec->iCodecMode == 111 );
	EUNIT_ASSERT( iCodec->iState == 111 );
	EUNIT_ASSERT( iCodec->iPriority == 111);
	EUNIT_ASSERT( iCodec->iPriorityPreference == 111);
    EUNIT_ASSERT( iCodec->iKeepAliveTimer == 111);
    EUNIT_ASSERT( iCodec->iKeepAlivePayloadType == 111);
    EUNIT_ASSERT( *iCodec->iKeepAliveData == KNullDesC8() );
    EUNIT_ASSERT( update->iKeepAliveData == NULL );

    iCodec->CMceComCodec::UpdateL( *update );

    EUNIT_ASSERT( iCodec->iSdpName == KMceSDPNamePCMA() );
    EUNIT_ASSERT( iCodec->iID == TMceMediaId( 12 ) )
    EUNIT_ASSERT( iCodec->iPayloadType == 97 )
    EUNIT_ASSERT( iCodec->iFourCC == 111 )
    EUNIT_ASSERT( iCodec->iBitrate == 111 )
    EUNIT_ASSERT( iCodec->iAllowedBitrates == 111 );
    EUNIT_ASSERT( iCodec->iCodecMode == 111 );
	EUNIT_ASSERT( iCodec->iState == 111 );
	EUNIT_ASSERT( iCodec->iPriority == 111);
	EUNIT_ASSERT( iCodec->iPriorityPreference == 111);
    EUNIT_ASSERT( iCodec->iKeepAliveTimer == 111);
    EUNIT_ASSERT( iCodec->iKeepAlivePayloadType == 111);
    EUNIT_ASSERT( *iCodec->iKeepAliveData == KNullDesC8() );
    EUNIT_ASSERT( update->iKeepAliveData == NULL );
    
    CleanupStack::PopAndDestroy( update );
    }

void UT_CMceComCodec::UT_CMceComCodec_DecodesL()
    {
    EUNIT_ASSERT( iCodec->Decodes( KMceSDPNameAMR(), KNullDesC8 ) );
    EUNIT_ASSERT( !iCodec->Decodes( KMceSDPNamePCMA(), KNullDesC8 ) );
       
    _LIT8( KMceSDPNameAMR_slash, "AMR/8000" );
    _LIT8( KMceSDPName_amr_slash, "amr/8000" );
    _LIT8( KMceSDPNameAMRWB_slash, "AMR-WB/16000" );
    
    EUNIT_ASSERT( iCodec->Decodes( KMceSDPNameAMR_slash(), KNullDesC8 ) );
    EUNIT_ASSERT( iCodec->Decodes( KMceSDPName_amr_slash(), KNullDesC8 ) );
    EUNIT_ASSERT( !iCodec->Decodes( KMceSDPNameAMRWB_slash(), KNullDesC8 ) );
    }

void UT_CMceComCodec::UT_CMceComCodec_InitializeLL()
    {
    // Tested already at setup
    EUNIT_ASSERT( ETrue );    
    }

void UT_CMceComCodec::UT_CMceComCodec_SynchronizeLL()
    {
    CMceComAMRCodec* codec = CMceComAMRCodec::NewL( KMceSDPNameAMR() );
    CleanupStack::PushL( codec );

    delete codec->iFmtpAttr;
    codec->iFmtpAttr = NULL;
    codec->iFmtpAttr = _L8( "new" ).AllocL();
    codec->iPayloadType = 99;
    codec->iCodecSdpIndex = 2;
    codec->iIsNegotiated = ETrue;
    iCodec->SynchronizeL( *codec, EFalse );
    
    EUNIT_ASSERT( *iCodec->iFmtpAttr != *codec->iFmtpAttr );
    EUNIT_ASSERT( iCodec->iPayloadType != codec->iPayloadType );
    EUNIT_ASSERT( iCodec->iCodecSdpIndex == codec->iCodecSdpIndex );
    EUNIT_ASSERT( iCodec->iIsNegotiated == codec->iIsNegotiated );

    iCodec->SynchronizeL( *codec, ETrue );
    EUNIT_ASSERT( *iCodec->iFmtpAttr == *codec->iFmtpAttr );
    EUNIT_ASSERT( iCodec->iPayloadType == codec->iPayloadType );
    EUNIT_ASSERT( iCodec->iCodecSdpIndex == codec->iCodecSdpIndex );
    EUNIT_ASSERT( iCodec->iIsNegotiated == codec->iIsNegotiated );
    
    CleanupStack::PopAndDestroy( codec );
    }

void UT_CMceComCodec::UT_CMceComCodec_EventReceivedLL()
    {
    TMceIds ids;
    TMceEvent event( ids, NULL, NULL );
    EUNIT_ASSERT( iCodec->EventReceivedL( event ) == KMceEventNotOwner );

    ids.iCodecID = iCodec->Id();

    EUNIT_ASSERT( iCodec->EventReceivedL( event ) == KMceEventUpdate );


    ids.iSinkID = TMceMediaId( 4 );
    ids.iSourceID = TMceMediaId( 5 );
    EUNIT_ASSERT( iCodec->EventReceivedL( event ) == KMceEventNotConsumed );
        
    }

void UT_CMceComCodec::UT_CMceComCodec_ResolveAllowedBitratesL()
    {
    }

void UT_CMceComCodec::UT_CMceComCodec_BaseFactoryL()
    {
    }

void UT_CMceComCodec::UT_CMceComCodec_operatorAssignL()
    {
    }

void UT_CMceComCodec::UT_CMceComCodec_MccDecodeLL()
    {
    CMccCodecInformation* codec = 
        iCodecFactory->CreateCodecInformationL( iCodec->iSdpName );
            
    CleanupStack::PushL( codec );
    iCodec->MccDecodeL( *codec );

    CleanupStack::PopAndDestroy( codec );
    
    }

void UT_CMceComCodec::UT_CMceComCodec_MccPopulateLL()
    {
    const TInt codecCount( 8 );
    CDesC8ArrayFlat* sdpNames = new ( ELeave ) CDesC8ArrayFlat( codecCount );
    CleanupStack::PushL( sdpNames );
    sdpNames->AppendL( KMceSDPNamePCMU() );
    sdpNames->AppendL( KMceSDPNamePCMA() );
    sdpNames->AppendL( KMceSDPNameAMR() );
    sdpNames->AppendL( KMceSDPNameG729() );
    sdpNames->AppendL( KMceSDPNameiLBC() );
    sdpNames->AppendL( KMceSDPNameDtmf() );
    sdpNames->AppendL( KMceSDPNameCn() );
    sdpNames->AppendL( KMceSDPNameRed() );
    
    CMceComSession* session = CMceComSession::NewL();
    CleanupStack::PushL( session );
    TMceComAudioCodecFactory factory;
    RPointerArray<CMceSrvStream> srvStreams; 
    MceCleanupResetAndDestroy< RPointerArray<CMceSrvStream> >::PushL( srvStreams );
    
    for ( TInt i = 0; i < codecCount; ++i )
        {
        CMceComAudioStream* stream = CMceComAudioStream::NewLC();
        
        CMceComMediaSource* mediaSource = CMceComMediaSource::NewLC();
        stream->SetSourceL( mediaSource );
        CleanupStack::Pop( mediaSource );
        
        CMceComMediaSink* mediaSink = CMceComMediaSink::NewLC();
        stream->AddSinkL( mediaSink );
        CleanupStack::Pop( mediaSink );
        
        const TDesC8& name = (*sdpNames)[i];
        CMceComAudioCodec* codec = factory.CreateCodecLC( (*sdpNames)[i] );
        codec->iPTime = 0;
        codec->iMaxPTime = 0;
        stream->AddCodecL( codec );
        CleanupStack::Pop( codec );
        
        session->AddStreamL( stream );
        CleanupStack::Pop( stream );
        
        CMceSrvStream* srvStream = CMceSrvStream::NewL( 
            *iManager, *stream, *mediaSource, *mediaSink, *codec );
        CleanupStack::PushL( srvStream );
        srvStreams.AppendL( srvStream );
        CleanupStack::Pop( srvStream );
        }
    
    session->InitializeL();
    session->PrepareL( *iManager );
    
    CMccCodecInformationFactory* mccCodecFactory =
        CMccCodecInformationFactory::NewL();
    CleanupStack::PushL( mccCodecFactory );
    
    for ( TInt i = 0; i < codecCount; ++i )
        {
        CMccCodecInformation* mccCodec 
            = mccCodecFactory->CreateCodecInformationL( (*sdpNames)[i] );
        CleanupStack::PushL( mccCodec );
        srvStreams[i]->Codec().MccPopulateL( 
            *mccCodec, *srvStreams[i], EMceRoleOfferer );
        srvStreams[i]->Codec().MccPopulateL( 
            *mccCodec, *srvStreams[i], EMceRoleAnswerer );
        CleanupStack::PopAndDestroy( mccCodec );
        }
    
    CleanupStack::PopAndDestroy( mccCodecFactory );
    CleanupStack::PopAndDestroy( &srvStreams );
    CleanupStack::PopAndDestroy( session );
    CleanupStack::PopAndDestroy( sdpNames );
    }

void UT_CMceComCodec::UT_CMceComCodec_MccValidateLL()
    {
    CMccCodecInformation* codec = 
        iCodecFactory->CreateCodecInformationL( iCodec->iSdpName );
        
    // Validation fails because of codec mode
    codec->SetCodecMode( EBandwidthEfficient );   
    codec->SetBitrate(-4);  
    iCodec->iCodecMode = EOctetAligned;       
    CleanupStack::PushL( codec );
    EUNIT_ASSERT_LEAVE( iCodec->MccValidateL( *codec, *iSession->MccStreams()[ 0 ], EMceRoleAnswerer ));

    // Validation ok, values encodec to mcc codec
    iCodec->iCodecMode = 4;
    codec->SetPTime( 40 );
    iCodec->iPTime = 20;
    iCodec->MccValidateL( *codec, *iSession->MccStreams()[ 0 ], EMceRoleAnswerer );
    EUNIT_ASSERT( codec->PTime() == 20 ); 
    
    // Validation ok, values decoded from mcc codec  
    codec->SetPriority( 100 );
    iCodec->iPriority = 90;
    iCodec->MccValidateL( *codec, *iSession->MccStreams()[ 0 ], EMceRoleOfferer );
    EUNIT_ASSERT( iCodec->iPriority == 100 ); 
    
    // Validation not done because stream is disabled, should not leave
    codec->SetCodecMode( 4 );
    iCodec->iCodecMode = 5;
    iStream->Enable( EFalse, ETrue );
    iCodec->MccValidateL( *codec, *iSession->MccStreams()[ 0 ], EMceRoleOfferer );
    
    CleanupStack::PopAndDestroy( codec );
    }
    
void UT_CMceComCodec::UT_CMceComCodec_DoMccValidateLL()
    {    
    CMccCodecInformation* codec = 
        iCodecFactory->CreateCodecInformationL( iCodec->iSdpName );
    
   	// Validation passes due to no codec mode difference
	codec->SetCodecMode( 4 );
	iCodec->iCodecMode = 4;
	CleanupStack::PushL( codec );
	EUNIT_ASSERT( iCodec->CMceComCodec::DoMccValidateL( *codec, *iSession->MccStreams()[ 0 ], EMceRoleAnswerer )==NULL);
    
    // Validation leaves due to codec mode difference
    iCodec->iCodecMode = 5;       
    EUNIT_ASSERT_LEAVE( iCodec->CMceComCodec::DoMccValidateL( *codec, *iSession->MccStreams()[ 0 ], EMceRoleAnswerer ));
    CleanupStack::PopAndDestroy( codec );
    }

void UT_CMceComCodec::UT_CMceComCodec_MccAdjustLL()
    {
    }

void UT_CMceComCodec::UT_CMceComCodec_MccRequireSignallingL()
    {
    }

void UT_CMceComCodec::UT_CMceComCodec_SetStateL()
    {
    }

void UT_CMceComCodec::UT_CMceComCodec_SetDefaultFmtpAttributeLL()
    {
    }

void UT_CMceComCodec::UT_CMceComCodec_FmtpAttrL()
    {
    EUNIT_ASSERT( iCodec->FmtpAttr().CompareF( KNullDesC8 ) == 0 );
    
    _LIT8( KMceTestFmtpAttr, "something" );
    
    iCodec->SetFmtpAttributeL( KMceTestFmtpAttr );
    EUNIT_ASSERT( iCodec->FmtpAttr().CompareF( KMceTestFmtpAttr ) == 0 );
    
    delete iCodec->iFmtpAttr;
    iCodec->iFmtpAttr = NULL;
    
    _LIT8( KMceTestFmtpAttr2, "something2" );
    iCodec->SetFmtpProposalL( KMceTestFmtpAttr2 );
    EUNIT_ASSERT( iCodec->FmtpAttr().CompareF( KMceTestFmtpAttr2 ) == 0 );
    }
    
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComCodec,
    "CMceComCodec tests",
    "UNIT" )

EUNIT_TEST (
    "Id test",
    "CMceComCodec",
    "Id",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_IdL, Teardown)

EUNIT_TEST (
    "Stream test",
    "CMceComCodec",
    "Stream",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_StreamL, Teardown)

EUNIT_TEST (
    "SetFmtpAttributeL test",
    "CMceComCodec",
    "SetFmtpAttributeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SetFmtpAttributeLL, Teardown)

EUNIT_TEST (
    "SetKeepAliveDataL test",
    "CMceComCodec",
    "SetKeepAliveDataL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SetKeepAliveDataLL, Teardown)

EUNIT_TEST (
    "SetBitrate test",
    "CMceComCodec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComCodec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "SetCodecMode test",
    "CMceComCodec",
    "SetCodecMode",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SetCodecModeL, Teardown)

EUNIT_TEST (
    "SetPayloadType test",
    "CMceComCodec",
    "SetPayloadType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SetPayloadTypeL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComCodec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "SerializationId test",
    "CMceComCodec",
    "SerializationId",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SerializationIdL, Teardown)

EUNIT_TEST (
    "InternalizeExternalizeFlatL test",
    "CMceComCodec",
    "InternalizeExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_InternalizeExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "InternalizeExternalizeL test",
    "CMceComCodec",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_InternalizeExternalizeLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComCodec",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_UpdateLL, Teardown)

EUNIT_TEST (
    "Decodes test",
    "CMceComCodec",
    "Decodes",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_DecodesL, Teardown)

EUNIT_TEST (
    "InitializeL test",
    "CMceComCodec",
    "InitializeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_InitializeLL, Teardown)

EUNIT_TEST (
    "SynchronizeL test",
    "CMceComCodec",
    "SynchronizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SynchronizeLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComCodec",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_EventReceivedLL, Teardown)

EUNIT_TEST (
    "ResolveAllowedBitrates test",
    "CMceComCodec",
    "ResolveAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_ResolveAllowedBitratesL, Teardown)

EUNIT_TEST (
    "BaseFactory test",
    "CMceComCodec",
    "BaseFactory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_BaseFactoryL, Teardown)

EUNIT_TEST (
    "operatorAssign test",
    "CMceComCodec",
    "operatorAssign",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_operatorAssignL, Teardown)

EUNIT_TEST (
    "MccDecodeL test",
    "CMceComCodec",
    "MccDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_MccDecodeLL, Teardown)

EUNIT_TEST (
    "MccPopulateL test",
    "CMceComCodec",
    "MccPopulateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_MccPopulateLL, Teardown)

EUNIT_TEST (
    "MccValidateL test",
    "CMceComCodec",
    "MccValidateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_MccValidateLL, Teardown)
    
EUNIT_TEST (
    "DoMccValidateL test",
    "CMceComCodec",
    "DoMccValidateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_DoMccValidateLL, Teardown)

EUNIT_TEST (
    "MccAdjustL test",
    "CMceComCodec",
    "MccAdjustL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_MccAdjustLL, Teardown)

EUNIT_TEST (
    "MccRequireSignalling test",
    "CMceComCodec",
    "MccRequireSignalling",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_MccRequireSignallingL, Teardown)

EUNIT_TEST (
    "SetState test",
    "CMceComCodec",
    "SetState",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SetStateL, Teardown)

EUNIT_TEST (
    "SetDefaultFmtpAttributeL test",
    "CMceComCodec",
    "SetDefaultFmtpAttributeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_SetDefaultFmtpAttributeLL, Teardown)

EUNIT_TEST (
    "FmtpAttr test",
    "CMceComCodec",
    "FmtpAttr",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCodec_FmtpAttrL, Teardown)
    
EUNIT_END_TEST_TABLE



//  END OF FILE
