/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32def.h>
#include <e32base.h>
#include <digia/eunit/EUnitMacros.h>
#include "CMceAudioStreamTest.h"
#include "mcestubs.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mceinsession.h"
#include "mceoutsession.h"
#include "mceaudiostream.h"
#include "mcertpsink.h"
#include "mcertpsource.h"
#include "mcemicsource.h"
#include "mcespeakersink.h"
#include "mcecomsession.h"
#include "mcecomaudiostream.h"
#include "mcecomrtpsink.h"
#include "mcecomrtpsource.h"
#include "mcecommicsource.h"
#include "mcecomspeakersink.h"
#include "mcecomamrcodec.h"
#include "mceamrcodec.h"
#include "mceg711codec.h"
#include "mceg729codec.h"
#include "mceh263codec.h"
#include "mcedtmfcodec.h"
#include "mceredcodec.h"
#include "mceserial.h"
#include "mceevents.h"
#include "mcefilesource.h"

_LIT8( KAmr, "AMR" );
_LIT8( KG711, "G711" );
_LIT8( KG729, "G729" );
_LIT8( KDtmf, "DTMF" );
_LIT8( KRed, "red" );


// ----------------------------------------------------------------------------
// CMceAudioStreamTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceAudioStreamTest::setUpL()
    {
    
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManagerObserver = new (ELeave) CMceManagerObserverStub();
    iSessionObserver = new (ELeave) CMceSessionObserverStub();
    iStreamObserver = new (ELeave) CMceStreamObserverStub();
    iRtpObserver = new (ELeave) CMceRtpObserverStub();
    
    iManager = CMceManager::NewL( iUid, &iContainer );
    iManager->SetInSessionObserver( iManagerObserver );
    iManager->SetMediaObserver( iStreamObserver );
    iManager->SetSessionObserver( iSessionObserver );
    iManager->SetRtpObserver( iRtpObserver );
    
    }

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::tearDown()
    {

    if ( iOutSession )
        {
        MCE_TEST_DELETE( iOutSession );
        }
    
    
    MCE_MAN_DELETE( iManager );

    delete iManagerObserver;
    delete iSessionObserver;
    delete iStreamObserver;
    delete iRtpObserver;
    
    delete iStorage;
    Dll::SetTls( NULL );
        
    }

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceAudioStreamTest::suiteL()
    {
    CMceAudioStreamTest* suite = new CMceAudioStreamTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;
    }
    
EUNIT_BEGIN_TEST_TABLE( 
    CMceAudioStreamTest,
    "CMceAudioStreamTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, EnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, DisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, BindTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, EventReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, EventReceivedTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, AddCodecTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, ReorderCodecsTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, ReorderCodecsByPreferncesTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, RemoveCodecTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, SynchronizeWithFileTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, RemoveSinkTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, ReplaceCodecsLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioStreamTest", setUpL, FindCodecTestL, tearDown )
EUNIT_END_TEST_TABLE    
       

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::EnableTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::EnableTestL()
    {
    
    MCE_CREATE_PROFILE;    
    
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->Recipient().Compare( KMceRecipient ) == 0 );

    CMceAudioStream* stream1 = NULL;
    CMceAudioStream* stream2 = NULL;

    stream1 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream1 );

    stream1->EnableL();    

//mic
    CMceMicSource* mic = CMceMicSource::NewL();
    CleanupStack::PushL( mic );
    EUNIT_ASSERT( !mic->Id().IsAssigned() );
    EUNIT_ASSERT( mic->IsEnabled() );
    
    stream1->SetSourceL(  mic );
    CleanupStack::Pop( mic );

//rtp sink   
    CMceRtpSink* rtpSink = CMceRtpSink::NewL();
    CleanupStack::PushL( rtpSink );
    EUNIT_ASSERT( !rtpSink->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    
    stream1->AddSinkL( rtpSink );
    CleanupStack::Pop( rtpSink );
    
    stream2 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream2 );

//rtp source
    CMceRtpSource* rtpSource = CMceRtpSource::NewL();
    CleanupStack::PushL( rtpSource );
    EUNIT_ASSERT( !rtpSource->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSource->IsEnabled() );
    
    stream2->SetSourceL( rtpSource );
    CleanupStack::Pop( rtpSource );

//speaker
    CMceSpeakerSink* speaker = CMceSpeakerSink::NewL();
    CleanupStack::PushL( speaker );
    EUNIT_ASSERT( !speaker->Id().IsAssigned() );
    EUNIT_ASSERT( speaker->IsEnabled() );
    
    stream2->AddSinkL( speaker );
    CleanupStack::Pop( speaker );


    for ( int i=0; i<2;i++)
        {
        
        stream1->EnableL();    
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );

        mic->DisableL();
        EUNIT_ASSERT( !mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );
        
        mic->EnableL();
        rtpSink->DisableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( !rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );

        rtpSink->EnableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );
        
        stream2->EnableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );

        speaker->DisableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( !speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );
        
        speaker->EnableL();
        rtpSource->DisableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( !rtpSource->IsEnabled() );
        rtpSource->EnableL();
        
        if ( i == 0 )
            {
            stream1->BindL( stream2 );
            CleanupStack::Pop( stream2 );
            
            iOutSession->AddStreamL( stream1 );
            CleanupStack::Pop( stream1 );
            MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, 1, EFalse );
            }
        
        }
    
    MCE_DELETE_PROFILE;
    
    }
    
    
// ----------------------------------------------------------------------------
// CMceAudioStreamTest::DisableTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::DisableTestL()
    {
    
    MCE_CREATE_PROFILE;
        
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->Recipient().Compare( KMceRecipient ) == 0 );

    CMceAudioStream* stream1 = NULL;
    CMceAudioStream* stream2 = NULL;

    stream1 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream1 );

    stream1->EnableL();   
    stream1->DisableL(); 

//mic
    CMceMicSource* mic = CMceMicSource::NewL();
    CleanupStack::PushL( mic );
    EUNIT_ASSERT( !mic->Id().IsAssigned() );
    EUNIT_ASSERT( mic->IsEnabled() );
    
    stream1->SetSourceL(  mic );
    CleanupStack::Pop( mic );

//rtp sink   
    CMceRtpSink* rtpSink = CMceRtpSink::NewL();
    CleanupStack::PushL( rtpSink );
    EUNIT_ASSERT( !rtpSink->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    
    stream1->AddSinkL( rtpSink );
    CleanupStack::Pop( rtpSink );
    
    stream2 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream2 );

//rtp source
    CMceRtpSource* rtpSource = CMceRtpSource::NewL();
    CleanupStack::PushL( rtpSource );
    EUNIT_ASSERT( !rtpSource->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSource->IsEnabled() );
    
    stream2->SetSourceL( rtpSource );
    CleanupStack::Pop( rtpSource );

//speaker
    CMceSpeakerSink* speaker = CMceSpeakerSink::NewL();
    CleanupStack::PushL( speaker );
    EUNIT_ASSERT( !speaker->Id().IsAssigned() );
    EUNIT_ASSERT( speaker->IsEnabled() );
    
    stream2->AddSinkL( speaker );
    CleanupStack::Pop( speaker );


    for ( int i=0; i<2;i++)
        {
        
        stream1->DisableL();    
        EUNIT_ASSERT( !mic->IsEnabled() );
        EUNIT_ASSERT( !rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );

        mic->DisableL();
        rtpSink->EnableL();
        EUNIT_ASSERT( !mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );
        
        stream1->DisableL();
        EUNIT_ASSERT( !mic->IsEnabled() );
        EUNIT_ASSERT( !rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );

        mic->EnableL();
        rtpSink->DisableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( !rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );

        rtpSink->EnableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );
        
        stream2->DisableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( !speaker->IsEnabled() );
        EUNIT_ASSERT( !rtpSource->IsEnabled() );

        speaker->DisableL();
        rtpSource->EnableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( !speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );
        
        speaker->EnableL();
        rtpSource->DisableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( !rtpSource->IsEnabled() );
        
        rtpSource->EnableL();
        EUNIT_ASSERT( mic->IsEnabled() );
        EUNIT_ASSERT( rtpSink->IsEnabled() );
        EUNIT_ASSERT( speaker->IsEnabled() );
        EUNIT_ASSERT( rtpSource->IsEnabled() );

        if ( i == 0 )
            {
            stream1->BindL( stream2 );
            CleanupStack::Pop( stream2 );
            
            iOutSession->AddStreamL( stream1 );
            CleanupStack::Pop( stream1 );
            MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, 1, EFalse );
            }
        
        }
        
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
        
    MCE_DELETE_PROFILE;
    
    }

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::BindTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::BindTestL()
    {
    
    MCE_CREATE_PROFILE;
	    
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->Recipient().Compare( KMceRecipient ) == 0 );

    CMceAudioStream* stream1 = NULL;
    CMceAudioStream* stream2 = NULL;
    CMceAudioStream* stream3 = NULL;

    stream1 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream1 );

    EUNIT_ASSERT( !stream1->BoundStream() );
    TRAPD( error, stream1->BoundStreamL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( error )
    EUNIT_ASSERT( error != KErrNone );

    stream2 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream2 );

    stream1->BindL( stream2 );
    CleanupStack::Pop( stream2 );
    EUNIT_ASSERT( stream1->BoundStream() );
    EUNIT_ASSERT( &(stream1->BoundStreamL()) == stream2 );
    
    stream3 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream3 );
    
    stream1->BindL( stream3 );
    CleanupStack::Pop( stream3 );
    EUNIT_ASSERT( stream1->BoundStream() );
    EUNIT_ASSERT( &(stream1->BoundStreamL()) == stream3 );
    
    CleanupStack::PopAndDestroy( stream1 );
    
    MCE_DELETE_PROFILE;
    
    }


// ----------------------------------------------------------------------------
// CMceAudioStreamTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::EventReceivedTestL()
    {
    
    MCE_CREATE_PROFILE;
	
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->Recipient().Compare( KMceRecipient ) == 0 );

    CMceAudioStream* stream1 = NULL;
    CMceAudioStream* stream2 = NULL;
    CMceAmrCodec* codec1 = NULL;

    stream1 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream1 );

//mic
    CMceMicSource* mic = CMceMicSource::NewL();
    CleanupStack::PushL( mic );
    EUNIT_ASSERT( !mic->Id().IsAssigned() );
    EUNIT_ASSERT( mic->IsEnabled() );
    
    stream1->SetSourceL(  mic );
    CleanupStack::Pop( mic );

//rtp sink   
    CMceRtpSink* rtpSink = CMceRtpSink::NewL();
    CleanupStack::PushL( rtpSink );
    EUNIT_ASSERT( !rtpSink->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    rtpSink->DisableL();
    EUNIT_ASSERT( !rtpSink->IsEnabled() );
    
    stream1->AddSinkL( rtpSink );
    CleanupStack::Pop( rtpSink );
    
    stream2 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream2 );

//rtp source
    CMceRtpSource* rtpSource = CMceRtpSource::NewL();
    CleanupStack::PushL( rtpSource );
    EUNIT_ASSERT( !rtpSource->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSource->IsEnabled() );
    
    stream2->SetSourceL( rtpSource );
    CleanupStack::Pop( rtpSource );

//speaker
    CMceSpeakerSink* speaker = CMceSpeakerSink::NewL();
    CleanupStack::PushL( speaker );
    EUNIT_ASSERT( !speaker->Id().IsAssigned() );
    EUNIT_ASSERT( speaker->IsEnabled() );
    
    stream2->AddSinkL( speaker );
    CleanupStack::Pop( speaker );

    stream1->BindL( stream2 );
    CleanupStack::Pop( stream2 );
    
    iOutSession->AddStreamL( stream1 );
    CleanupStack::Pop( stream1 );
    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, 1, EFalse );

    
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 0);

    MCE_STREAM_STATECHANGE( iOutSession, stream1, ETrue, KMceNotAssigned )
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EEstablished );
    EUNIT_ASSERT( stream1->IsEnabled() );
    EUNIT_ASSERT( stream2->IsEnabled() );
    EUNIT_ASSERT( mic->IsEnabled() );
    EUNIT_ASSERT( !rtpSink->IsEnabled() );
    EUNIT_ASSERT( rtpSource->IsEnabled() );
    EUNIT_ASSERT( speaker->IsEnabled() );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 1 );
    EUNIT_ASSERT( iStreamObserver->iStream == stream1 );
    EUNIT_ASSERT( iStreamObserver->iSource == NULL );
    EUNIT_ASSERT( iStreamObserver->iSink == NULL );
    
    //stream updated with no media observer
    iManager->SetMediaObserver( NULL );
    MCE_STREAM_STATECHANGE( iOutSession, stream1, ETrue, KMceNotAssigned )
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 1 );
    iManager->SetMediaObserver( iStreamObserver );
    
    MCE_STREAM_STATECHANGE( iOutSession, stream2, ETrue, KMceNotAssigned )
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EEstablished );
    EUNIT_ASSERT( stream1->IsEnabled() );
    EUNIT_ASSERT( stream2->IsEnabled() );
    EUNIT_ASSERT( mic->IsEnabled() );
    EUNIT_ASSERT( !rtpSink->IsEnabled() );
    EUNIT_ASSERT( rtpSource->IsEnabled() );
    EUNIT_ASSERT( speaker->IsEnabled() );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 2 );
    EUNIT_ASSERT( iStreamObserver->iStream == stream2 );
    EUNIT_ASSERT( iStreamObserver->iSource == NULL );
    EUNIT_ASSERT( iStreamObserver->iSink == NULL );

    
    MCE_SOURCE_STATECHANGE( iOutSession, stream1, mic, EFalse, KMceNotAssigned )
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EEstablished );
    EUNIT_ASSERT( stream1->IsEnabled() );
    EUNIT_ASSERT( stream2->IsEnabled() );
    EUNIT_ASSERT( !mic->IsEnabled() );
    EUNIT_ASSERT( !rtpSink->IsEnabled() );
    EUNIT_ASSERT( rtpSource->IsEnabled() );
    EUNIT_ASSERT( speaker->IsEnabled() );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 3 );
    EUNIT_ASSERT( iStreamObserver->iStream == stream1 );
    EUNIT_ASSERT( iStreamObserver->iSource == mic );
    EUNIT_ASSERT( iStreamObserver->iSink == NULL );
    
    MCE_SINK_STATECHANGE( iOutSession, stream1, rtpSink, ETrue, KMceNotAssigned )
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EEstablished );
    EUNIT_ASSERT( stream1->IsEnabled() );
    EUNIT_ASSERT( stream2->IsEnabled() );
    EUNIT_ASSERT( !mic->IsEnabled() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    EUNIT_ASSERT( rtpSource->IsEnabled() );
    EUNIT_ASSERT( speaker->IsEnabled() );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 4 );
    EUNIT_ASSERT( iStreamObserver->iStream == stream1 );
    EUNIT_ASSERT( iStreamObserver->iSource == NULL );
    EUNIT_ASSERT( iStreamObserver->iSink == rtpSink );

    MCE_SOURCE_STATECHANGE( iOutSession, stream2, rtpSource, EFalse, KMceNotAssigned )
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EEstablished );
    EUNIT_ASSERT( stream1->IsEnabled() );
    EUNIT_ASSERT( stream2->IsEnabled() );
    EUNIT_ASSERT( !mic->IsEnabled() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    EUNIT_ASSERT( !rtpSource->IsEnabled() );
    EUNIT_ASSERT( speaker->IsEnabled() );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 5 );
    EUNIT_ASSERT( iStreamObserver->iStream == stream2 );
    EUNIT_ASSERT( iStreamObserver->iSource == rtpSource );
    EUNIT_ASSERT( iStreamObserver->iSink == NULL );
    
    MCE_SINK_STATECHANGE( iOutSession, stream2, speaker, EFalse, KMceNotAssigned )
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EEstablished );
    EUNIT_ASSERT( stream1->IsEnabled() );
    EUNIT_ASSERT( stream2->IsEnabled() );
    EUNIT_ASSERT( !mic->IsEnabled() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    EUNIT_ASSERT( !rtpSource->IsEnabled() );
    EUNIT_ASSERT( !speaker->IsEnabled() );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 6 );
    EUNIT_ASSERT( iStreamObserver->iStream == stream2 );
    EUNIT_ASSERT( iStreamObserver->iSource == NULL );
    EUNIT_ASSERT( iStreamObserver->iSink == speaker );

    CMceComRtpSink* updateSink = NULL;
    CMceComRtpSource* updateSource = NULL;
    CMceComAudioStream* updateStream = NULL;
    CMceMsgObject<CMceComMediaStream>* msgAudio = NULL;
    CMceMsgObject<CMceComMediaSink>* msgSink = NULL;
    CMceMsgObject<CMceComMediaSource>* msgSource = NULL;
    CMceMsgObject<CMceComAudioCodec>* msgCodec = NULL;

    //new rtp sink
    updateSink = CMceComRtpSink::NewL();
    CleanupStack::PushL( updateSink );
    
    EUNIT_ASSERT( rtpSink->LastPacket() == 0 );
    updateSink->iLastPacket = 234;
    
    msgSink = new (ELeave) CMceMsgObject<CMceComMediaSink>( *updateSink, EMceItcMsgTypeSink );
    CleanupStack::PushL( msgSink );
    msgSink->EncodeL();
    
    //new rtp source    
    updateSource = CMceComRtpSource::NewL();
    CleanupStack::PushL( updateSource );
    
    EUNIT_ASSERT( !rtpSource->IsEnabled() );
    updateSource->Enabled( ETrue );
    
    msgSource = new (ELeave) CMceMsgObject<CMceComMediaSource>( *updateSource, EMceItcMsgTypeSource );
    CleanupStack::PushL( msgSource );
    msgSource->EncodeL();

    //new sream
    updateStream = CMceComAudioStream::NewL();
    CleanupStack::PushL( updateStream );
    
    msgAudio = new (ELeave) CMceMsgObject<CMceComMediaStream>( *updateStream, EMceItcMsgTypeStream );
    CleanupStack::PushL( msgAudio );
    
    TBuf8<KMceMaxSdpNameLength> codecStr;
    codecStr.Append( KAmr);    
    
    CMceComAMRCodec* codec = CMceComAMRCodec::NewL( codecStr );
    CleanupStack::PushL( codec );
    updateStream->AddCodecL( codec );
    CleanupStack::Pop( codec );
    
    msgAudio->EncodeL();
    
    //new codec
    codec->iBitrate = 66;
    msgCodec = new (ELeave) CMceMsgObject<CMceComAudioCodec>( *codec, EMceItcMsgTypeCodec );
    CleanupStack::PushL( msgCodec );
    msgCodec->EncodeL();
    
    
    //update sink
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
            
    iStorage->iContext = msgSink->EncodeBuffer().Ptr( 0 ).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    MCE_SINK_STATECHANGE( iOutSession, stream1, rtpSink, ETrue, EMceItcMsgTypeSink );
    rtpSink = static_cast<CMceRtpSink*>( stream1->Sinks()[0] );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 7 );
    EUNIT_ASSERT( iStreamObserver->iStream == stream1 );
    EUNIT_ASSERT( iStreamObserver->iSource == NULL );
    EUNIT_ASSERT( iStreamObserver->iSink == rtpSink );
    EUNIT_ASSERT( rtpSink->LastPacket() == 234 );

    
    //update source
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
            
    iStorage->iContext = msgSource->EncodeBuffer().Ptr( 0 ).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    MCE_SOURCE_STATECHANGE( iOutSession, stream2, rtpSource, EFalse, EMceItcMsgTypeSource );
    rtpSource = static_cast<CMceRtpSource*>( stream2->Source() );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 8 );
    EUNIT_ASSERT( iStreamObserver->iStream == stream2 );
    EUNIT_ASSERT( iStreamObserver->iSource == rtpSource );
    EUNIT_ASSERT( iStreamObserver->iSink == NULL );
    EUNIT_ASSERT( rtpSource->IsEnabled() );

    
    //update stream (linked)
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
            
    iStorage->iContext = msgAudio->EncodeBuffer().Ptr( 0 ).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    MCE_STREAM_STATECHANGE( iOutSession, stream2, ETrue, EMceItcMsgTypeStream );
    stream2 = static_cast<CMceAudioStream*>( &(stream1->BoundStreamL()) );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 9 );
    EUNIT_ASSERT( iStreamObserver->iStream == stream2 );
    EUNIT_ASSERT( iStreamObserver->iSource == NULL );
    EUNIT_ASSERT( iStreamObserver->iSink == NULL );
    EUNIT_ASSERT( stream2->BoundStream() );
    EUNIT_ASSERT( stream2->Source() == NULL );
    EUNIT_ASSERT( stream2->Sinks().Count() == 0 );


    //update stream
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
            
    iStorage->iContext = msgAudio->EncodeBuffer().Ptr( 0 ).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    MCE_STREAM_STATECHANGE( iOutSession, stream1, ETrue, EMceItcMsgTypeStream );
    stream1 = static_cast<CMceAudioStream*>( iOutSession->Streams()[0] );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 10 );
    EUNIT_ASSERT( iStreamObserver->iStream != NULL );
    EUNIT_ASSERT( iStreamObserver->iSource == NULL );
    EUNIT_ASSERT( iStreamObserver->iSink == NULL );
    EUNIT_ASSERT( !stream1->BoundStream() );
    EUNIT_ASSERT( stream1->Source() == NULL );
    EUNIT_ASSERT( stream1->Sinks().Count() == 0 );
    EUNIT_ASSERT( stream1->Codecs().Count() == 1 );
    codec1 = static_cast<CMceAmrCodec*>( stream1->Codecs()[0] );
    EUNIT_ASSERT( codec1->Bitrate() != 66 );


    //update codec
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
            
    iStorage->iContext = msgCodec->EncodeBuffer().Ptr( 0 ).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    MCE_CODEC_CHANGE( iOutSession, stream1, codec1 );
    codec1 = static_cast<CMceAmrCodec*>( stream1->Codecs()[0] );
    EUNIT_ASSERT( iStreamObserver->iStateChangedCount == 10 );
    EUNIT_ASSERT( codec1->Bitrate() == 66 );    

    //link created
    TMceIds ids2;
    ids2.iMediaID = stream1->Id();
    ids2.iState = 6000;
    ids2.iCallbackID = EMceItcLinkCreated;
    TMceEvent event2 = TMceEvent( ids2, NULL, NULL );
    TInt status = stream1->EventReceivedL( event2 );
    EUNIT_ASSERT_EQUALS( status, KMceEventConsumed );
    EUNIT_ASSERT_EQUALS( stream1->LocalMediaPort(), 6000 );

    CleanupStack::PopAndDestroy( msgCodec );
    CleanupStack::PopAndDestroy( msgAudio );
    CleanupStack::PopAndDestroy( updateStream );
    CleanupStack::PopAndDestroy( msgSource );
    CleanupStack::PopAndDestroy( updateSource );
    CleanupStack::PopAndDestroy( msgSink );
    CleanupStack::PopAndDestroy( updateSink );

        
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    
    MCE_DELETE_PROFILE;
    
    }


// ----------------------------------------------------------------------------
// CMceAudioStreamTest::EventReceivedTest2L
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::EventReceivedTest2L()
    {
    // ID is not codec id
    TMceIds ids;
    TMceEvent event = TMceEvent( ids, NULL, NULL );
    CMceAudioStream* stream = CMceAudioStream::NewL();
    CleanupStack::PushL( stream );
    TInt status = stream->EventReceivedL( event );
    EUNIT_ASSERT_EQUALS( status, KMceEventNotConsumed );
    
    CleanupStack::PopAndDestroy( stream );
    }


// ----------------------------------------------------------------------------
// CMceAudioStreamTest::AddCodecTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::AddCodecTestL()
    {
    // Cover calling with NULL
    CMceAudioStream* stream = CMceAudioStream::NewL();
    CleanupStack::PushL( stream );
    TRAPD( err, stream->AddCodecL( NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrArgument );
    CleanupStack::PopAndDestroy( stream );
    }

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::ReorderCodecsTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::ReorderCodecsTestL()
    {
    CMceComAudioStream* stream = CMceComAudioStream::NewL();
    CleanupStack::PushL( stream );
    
    EUNIT_ASSERT_EQUALS( 0, stream->Codecs().Count() );
    
    TBuf8<KMceMaxSdpNameLength> sdpName( KAmr );    
    CMceComAudioCodec* amr = CMceComAudioCodec::NewLC(sdpName);
    
    amr->iCodecSdpIndex = 2;
    
    stream->AddCodecL( amr );
    CleanupStack::Pop( amr  );
    
    EUNIT_ASSERT_EQUALS( 1, stream->Codecs().Count() );
   
    sdpName = KG711;    
    CMceComAudioCodec* g711 = CMceComAudioCodec::NewLC(sdpName);
    
    g711->iCodecSdpIndex = 1;
    
    stream->AddCodecL( g711 );
    CleanupStack::Pop( g711  );
    
    EUNIT_ASSERT_EQUALS( 2, stream->Codecs().Count() );
    
    stream->ReorderCodecs();
    
    EUNIT_ASSERT_EQUALS( 1, stream->Codecs()[0]->iCodecSdpIndex );
    EUNIT_ASSERT_EQUALS( 2, stream->Codecs()[1]->iCodecSdpIndex );

    CleanupStack::PopAndDestroy( stream );  
    }

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::ReorderCodecsByPreferncesTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::ReorderCodecsByPreferncesTestL()
    {
    CMceAudioStream* stream = CMceAudioStream::NewL();
    CleanupStack::PushL( stream );
    
    EUNIT_ASSERT_EQUALS( 0, stream->Codecs().Count() );
    
    TBuf8<KMceMaxSdpNameLength> sdpName( KAmr );    
    CMceAmrCodec* amr = CMceAmrCodec::NewLC(sdpName);
    
    amr->iFlatData->iPreference = 2;
    
    stream->AddCodecL( amr );
    CleanupStack::Pop( amr  );
    
    EUNIT_ASSERT_EQUALS( 1, stream->Codecs().Count() );
   
    sdpName = KG711;    
    CMceG711Codec* g711 = CMceG711Codec::NewLC(sdpName);
    
    g711->iFlatData->iPreference = 1;
    
    stream->AddCodecL( g711 );
    CleanupStack::Pop( g711  );
    
    sdpName = KG729;    
    CMceG729Codec* g729 = CMceG729Codec::NewLC(sdpName);
    
    g729->iFlatData->iPreference = 0;
    
    stream->AddCodecL( g729 );
    CleanupStack::Pop( g729  );
    
    sdpName = KDtmf;    
    CMceDtmfCodec* dtmf = CMceDtmfCodec::NewLC(sdpName);
    
    dtmf->iFlatData->iPreference = 0;
    
    stream->AddCodecL( dtmf );
    CleanupStack::Pop( dtmf  );
    
    sdpName = KRed;    
    CMceRedCodec* red = CMceRedCodec::NewLC(sdpName);
    
    red->iFlatData->iPreference = 0;
    
    stream->AddCodecL( red );
    CleanupStack::Pop( red  );

    EUNIT_ASSERT_EQUALS( 5, stream->Codecs().Count() );
    
    stream->ReorderCodecsByPreferenceL( EFalse );
    
    
    CMceAudioCodec* codec1 = stream->Codecs()[0];
    CMceAudioCodec* codec2 = stream->Codecs()[1];
    CMceAudioCodec* codec3 = stream->Codecs()[2];
    CMceAudioCodec* codec4 = stream->Codecs()[3];
    CMceAudioCodec* codec5 = stream->Codecs()[4];
    
    EUNIT_ASSERT_EQUALS( 0, stream->Codecs()[0]->iFlatData->iPreference );
    EUNIT_ASSERT_EQUALS( 0, stream->Codecs()[1]->iFlatData->iPreference );
    EUNIT_ASSERT_EQUALS( 0, stream->Codecs()[2]->iFlatData->iPreference );
    EUNIT_ASSERT_EQUALS( 1, stream->Codecs()[3]->iFlatData->iPreference );
    EUNIT_ASSERT_EQUALS( 2, stream->Codecs()[4]->iFlatData->iPreference );

    stream->ReorderCodecsByPreferenceL( EFalse );
    
    EUNIT_ASSERT_EQUALS( 0, stream->Codecs()[0]->iFlatData->iPreference );
    EUNIT_ASSERT_EQUALS( 0, stream->Codecs()[1]->iFlatData->iPreference );
    EUNIT_ASSERT_EQUALS( 0, stream->Codecs()[2]->iFlatData->iPreference );
    EUNIT_ASSERT_EQUALS( 1, stream->Codecs()[3]->iFlatData->iPreference );
    EUNIT_ASSERT_EQUALS( 2, stream->Codecs()[4]->iFlatData->iPreference );

    // Red is discarded
    stream->ReorderCodecsByPreferenceL( ETrue );
    EUNIT_ASSERT_EQUALS( 4, stream->Codecs().Count() );
    
    CleanupStack::PopAndDestroy( stream );  
    }

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::RemoveCodecTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::RemoveCodecTestL()
    {
    CMceAudioStream* stream = CMceAudioStream::NewL();
    CleanupStack::PushL( stream );
    
    EUNIT_ASSERT_EQUALS( 0, stream->Codecs().Count() );
    
    TBuf8<KMceMaxSdpNameLength> sdpName( KAmr );    
    CMceAmrCodec* amr = CMceAmrCodec::NewLC(sdpName);
    
    stream->AddCodecL( amr );
    CleanupStack::Pop( amr  );
    
    EUNIT_ASSERT_EQUALS( 1, stream->Codecs().Count() );
   
    sdpName = KG711;    
    CMceG711Codec* g711 = CMceG711Codec::NewLC(sdpName);
    
    stream->AddCodecL( g711 );
    CleanupStack::Pop( g711  );
    
    EUNIT_ASSERT_EQUALS( 2, stream->Codecs().Count() );
    
    EUNIT_ASSERT( stream->Codecs()[0]->SdpName() == KAmr );
    stream->RemoveCodecL( *stream->Codecs()[1] );
    
    EUNIT_ASSERT_EQUALS( 1, stream->Codecs().Count() );
    EUNIT_ASSERT( stream->Codecs()[0]->SdpName() == KAmr );
    
    CleanupStack::PopAndDestroy( stream );
    }

 
 // ----------------------------------------------------------------------------
// CMceAudioStreamTest::RemoveCodecTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::SynchronizeWithFileTestL()
    {
    CMceAudioStream* stream = CMceAudioStream::NewL();
    CleanupStack::PushL( stream );
    
   	CMceFileSource* fileSource = CMceFileSource::NewL( *iManager, KMceTestAVFileName() );
   	CleanupStack::PushL( fileSource );
   	
   	stream->SynchronizeWithFileL(*fileSource);
   	EUNIT_ASSERT_EQUALS( 1, stream->Codecs().Count() );
   	
   	stream->SynchronizeWithFileL(*fileSource);
   	EUNIT_ASSERT_EQUALS( 1, stream->Codecs().Count() );
   	
   	
   	CleanupStack::PopAndDestroy(fileSource);
    CleanupStack::PopAndDestroy( stream );
    }

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::RemoveSinkTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::RemoveSinkTestL()
    {
    CMceAudioStream* stream1 = NULL;

    stream1 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream1 );

    stream1->EnableL();    

//mic
    CMceMicSource* mic = CMceMicSource::NewL();
    CleanupStack::PushL( mic );
    EUNIT_ASSERT( !mic->Id().IsAssigned() );
    EUNIT_ASSERT( mic->IsEnabled() );
    
    stream1->SetSourceL(  mic );
    CleanupStack::Pop( mic );

//rtp sink   
    CMceRtpSink* rtpSink = CMceRtpSink::NewL();
    CleanupStack::PushL( rtpSink );
    EUNIT_ASSERT( !rtpSink->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    
    stream1->AddSinkL( rtpSink );
    CleanupStack::Pop( rtpSink );
    

  //actual tests
  	stream1->RemoveSinkL(*rtpSink);
  	EUNIT_ASSERT(stream1->Sinks().Count()==0);
    CleanupStack::PopAndDestroy( stream1 );  
    }

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::ReplaceCodecsLTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::ReplaceCodecsLTestL()
	{
	CMceAudioStream* stream = CMceAudioStream::NewLC();
	TRAPD( err, stream->ReplaceCodecsL( NULL ) );
	CleanupStack::PopAndDestroy( stream );
    EUNIT_ASSERT_EQUALS( KErrNotSupported, err );
	}

// ----------------------------------------------------------------------------
// CMceAudioStreamTest::FindCodecTestL
// ----------------------------------------------------------------------------
//
void CMceAudioStreamTest::FindCodecTestL()
	{
	CMceCodec* codec = reinterpret_cast< CMceCodec* >( 0x108 );
	CMceAudioStream* stream = CMceAudioStream::NewLC();
 	EUNIT_ASSERT( !stream->FindCodec( *codec ) );
 	CleanupStack::PopAndDestroy( stream );
 	
 	// Test codec search for two-way stream where multiple codecs with same
 	// sdp name exist
 	//
 	CMceAudioStream* stream1 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream1 );

    CMceAudioStream* stream2 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream2 );

    stream1->BindL( stream2 );
    CleanupStack::Pop( stream2 );
    
    TBuf8<KMceMaxSdpNameLength> sdpName1( KG711 );  
    CMceG711Codec* g711_1 = CMceG711Codec::NewLC(sdpName1);
    stream1->AddCodecL( g711_1 );
    CleanupStack::Pop( g711_1 );
    CMceAudioCodec* g711_2 = g711_1->CloneL();
    CleanupStack::PushL( g711_2 );
    stream2->AddCodecL( g711_2 );
    CleanupStack::Pop( g711_2 );
    
    TBuf8<KMceMaxSdpNameLength> sdpName2( KAmr );    
    CMceAmrCodec* amr1 = CMceAmrCodec::NewLC(sdpName2);
    stream1->AddCodecL( amr1 );
    CleanupStack::Pop( amr1 );
    CMceAudioCodec* amr2 = amr1->CloneL();
    CleanupStack::PushL( amr2 );
    stream2->AddCodecL( amr2 );
    CleanupStack::Pop( amr2 );
    
    CMceAudioCodec* amr3 = amr1->CloneL();
    CleanupStack::PushL( amr3 );
    stream1->AddCodecL( amr3 );
    CleanupStack::Pop( amr3 );
    CMceAudioCodec* amr4 = amr1->CloneL();
    CleanupStack::PushL( amr4 );
    stream2->AddCodecL( amr4 );
    CleanupStack::Pop( amr4 );
    
    // Search based on pointer match
    CMceCodec* findResult = stream1->CMceMediaStream::FindCodec( stream1->BaseCodecs(), *g711_1 );
    EUNIT_ASSERT( findResult != NULL );
    EUNIT_ASSERT( findResult == g711_1 );
    
    // Search based on sdp match
    findResult = stream2->CMceMediaStream::FindCodec( stream2->BaseCodecs(), *amr1 );
    EUNIT_ASSERT( findResult != NULL );
    EUNIT_ASSERT( findResult != amr1 );
    EUNIT_ASSERT( findResult->SdpName() == amr1->SdpName() );
    
    // Search based on index match
    CMceCodec* findResult2 = stream2->CMceMediaStream::FindCodec( stream2->BaseCodecs(), *amr3 );
    EUNIT_ASSERT( findResult2 != NULL );
    EUNIT_ASSERT( findResult2 != amr2 );
    EUNIT_ASSERT( findResult2->SdpName() == amr2->SdpName() );
    EUNIT_ASSERT( findResult2 != findResult );
    
    CleanupStack::PopAndDestroy( stream1 );
	}
