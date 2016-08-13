/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include "CMceComSessionTest.h"

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

#include "mcecomvideostream.h"
#include "mcecomdisplaysink.h"
#include "mcecamerasource.h"
#include "mcecomcamerasource.h"
#include "mcevideostream.h"
#include "mcedisplaysink.h"
#include "mcecomh263codec.h"
#include "mceh263codec.h"
#include "mcecomfilesource.h"
#include "mcefilesource.h"

#include "mceserial.h"
#include "mcetestdefs.h"


    
// ----------------------------------------------------------------------------
// CMceComSessionTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceComSessionTest::setUpL()
    {
    iMediaManager = new (ELeave) CMceMediaManagerStub();
    }

// ----------------------------------------------------------------------------
// CMceComSessionTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceComSessionTest::tearDown()
    {
    delete iSession;
    delete iMediaManager;
    delete iClientSession;
    }

// ----------------------------------------------------------------------------
// CMceComSessionTest::suiteL
// ----------------------------------------------------------------------------
//
MTest* CMceComSessionTest::suiteL()
    {
    CTestSuite *suite = CTestSuite::NewL(_L8("CMceComSessionTest"));

	suite->addTestL(
	    CTestCaller<CMceComSessionTest>::NewL(
	        _L8("TestUseRtcpL"),
	        &TestUseRtcpL));

	suite->addTestL(
	    CTestCaller<CMceComSessionTest>::NewL(
	        _L8("TestUpdate1L"),
	        &TestUpdate1L));

	suite->addTestL(
	    CTestCaller<CMceComSessionTest>::NewL(
	        _L8("TestUpdate2L"),
	        &TestUpdate2L ) );
    	                                   
    return suite;
    }

// ----------------------------------------------------------------------------
// CMceComSessionTest::TestUseRtcpL
// ----------------------------------------------------------------------------
//
void CMceComSessionTest::TestUseRtcpL()
    {
    iSession = CMceComSession::NewL();
    
    // No streams
    assertL( iSession->UseRtcp() );
    
    // Stream exists, RTCP enabled by default
    CMceComAudioStream* stream = CMceComAudioStream::NewLC();
    CMceComRtpSink* rtpSink = CMceComRtpSink::NewLC();
    stream->AddSinkL( rtpSink );
    CleanupStack::Pop( rtpSink ); 
    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream ); 
    assertL( iSession->UseRtcp() );   
    
    // Stream exists, disable RTCP
    rtpSink->iSuppressRTCP = ETrue;
    assertL( !iSession->UseRtcp() );
    
    rtpSink->iSuppressRTCP = EFalse;
    assertL( iSession->UseRtcp() );
    
    //BoundStream
     
    CMceComAudioStream* streamB = CMceComAudioStream::NewLC();
    CMceComRtpSink* rtpSinkB = CMceComRtpSink::NewLC();
    streamB->AddSinkL( rtpSinkB );
    CleanupStack::Pop( rtpSinkB ); 
    stream->BindL(streamB);
    CleanupStack::Pop( streamB ); 
    assertL( iSession->UseRtcp() ); 
    rtpSinkB->iSuppressRTCP = ETrue;
    assertL( !iSession->UseRtcp() );
    }

	
// ----------------------------------------------------------------------------
// CMceComSessionTest::TestUpdate1L
// ----------------------------------------------------------------------------
//
void CMceComSessionTest::TestUpdate1L()
    {
    CMceComAudioStream* audioIn = NULL;
    CMceComAMRCodec* inCodec = NULL;
    CMceComAudioStream* audioOut = NULL;
    CMceComAMRCodec* outCodec = NULL;

    CMceComRtpSink* rtpSink = NULL;
    CMceComRtpSource* rtpSource = NULL;
    CMceComSpeakerSink* speaker = NULL;
    CMceComMicSource* mic = NULL;

    TUid uid = TUid::Uid( 777 );
    TMceIds ids;
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    TMceComEventHandlerStub handler( *iMediaManager );
    TBuf8<KMceMaxSdpNameLength> amr;
    amr.Append( _L8("AMR") );
    
    iSession = CMceComSession::NewL();
    iSession->iType = CMceComSession::EInSession;
    iSession->iID = 1;
    iSession->iIsConnectionActive = ETrue;
    iSession->iMccID = 12;
    iSession->iState = CMceSession::EIncoming;
    delete iSession->iOriginator;
    iSession->iOriginator = 0;
    iSession->iOriginator = KMceOriginator().AllocL();
    delete iSession->iRecipient; 
    iSession->iRecipient = 0;
    iSession->iRecipient = KMceRecipient().AllocL();
    
    CMceMsgObject<CMceComSession>* sessionMsg = new (ELeave) CMceMsgObject<CMceComSession>( *iSession, EMceItcMsgTypeSession );
    CleanupStack::PushL( sessionMsg );
    sessionMsg->EncodeL();
    
    // Decode takes ownbership temporarily!
    CMceComSession* tempSession = iSession;
    iSession = 0;
    sessionMsg->DecodeL( sessionMsg->EncodeBuffer().Ptr( 0 ) );
    iSession = tempSession;
    
    iClientSession = sessionMsg->iObject;
    
    CleanupStack::PopAndDestroy( sessionMsg );
    
    assertL( iClientSession->Id() == 1 );
    assertL( iClientSession->iType == CMceComSession::EInSession );
    assertL( iClientSession->iIsConnectionActive );
    assertL( iClientSession->iMccID == KMceNotAssigned );
    assertL( iClientSession->iState == CMceSession::EIncoming );
    assertL( iClientSession->iOriginator->Compare( KMceOriginator ) == 0 );
    assertL( iClientSession->iRecipient->Compare( KMceRecipient ) == 0 );

    assertL( iSession->Id() == 1 );
    assertL( iSession->iType == CMceComSession::EInSession );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator ) == 0 );

    
//just session    
    
    delete iClientSession->iOriginator;
    iClientSession->iOriginator = 0;
    iClientSession->iOriginator = KMceOriginator1().AllocL();
    delete iClientSession->iRecipient;
    iClientSession->iRecipient = 0;
    iClientSession->iRecipient = KMceRecipient1().AllocL();

    CMceComSession* updatedSession = ClientSessionReceivedLC();
    assertL( updatedSession->Id() == 1 );
    assertL( updatedSession->iType == CMceComSession::EInSession );
    assertL( updatedSession->iIsConnectionActive );
    assertL( updatedSession->iMccID == KMceNotAssigned );
    assertL( updatedSession->iState == CMceSession::EIncoming );
    assertL( updatedSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( updatedSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
        
        
    TMceComEvent event( ids, updatedSession, EMceItcUpdate, handler );

    iSession->EventReceivedL( event );
    CleanupStack::PopAndDestroy( updatedSession );
    
    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->Streams().Count() == 0 );


//session with stream
    
    audioIn = CMceComAudioStream::NewL();
    CleanupStack::PushL( audioIn );
    inCodec = CMceComAMRCodec::NewL( amr );
    CleanupStack::PushL( inCodec );
    audioIn->iID = TMceMediaId( uid, 1 );
    inCodec->iID = TMceMediaId( uid, 2 );
    inCodec->iPayloadType = 96;
    inCodec->iBitrate = 2300;
    audioIn->AddCodecL( inCodec );
    CleanupStack::Pop( inCodec );
    iClientSession->AddStreamL( audioIn );
    CleanupStack::Pop( audioIn );
    
    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event1( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event1 );
    
    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 1 );
    iAudioIn = static_cast<CMceComAudioStream*>( iSession->Streams()[0] );
    assertL( iAudioIn->iID == TMceMediaId( uid, 1 ) );
    assertL( iAudioIn->CodecCount() == 1 );
    assertL( !iAudioIn->BoundStream() );
    iInCodec = static_cast<CMceComAMRCodec*>(iAudioIn->CodecL( 0 ) );
    assertL( iInCodec->iID == TMceMediaId( uid, 2 ) );
    assertL( iInCodec->iPayloadType == 96 );
    assertL( iInCodec->iBitrate == 2300 );
    assertL( updatedSession->Streams().Count() == 0 );

    
    //bitrate and allowed bitrate tests for amr
    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate475 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate475 );
    assertL( iInCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrateAll ) == KErrNone );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate475 );

    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate102 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate102 );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );

    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate795 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate795 );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );

    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate740 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate740 );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );

    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate670 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate670 );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );

    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate590 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate590 );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );

    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate515 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate515 );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );

    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate475 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate475 );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );
    
    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate122 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate122 );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );

    assertL( iInCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate670 ) == KErrNone );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrate670 );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate670 );
    
    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate515 ) == KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate515 );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrate670 );

    assertL( iInCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate670 ) == KErrNone );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrate670 );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate515 );

    assertL( iInCodec->SetBitrate( KMceAmrNbBitrate102 ) != KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate515 );
    assertL( iInCodec->SetBitrate( 0 ) != KErrNone );
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate515 );
    
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrate670 );    
    assertL( iInCodec->SetAllowedBitrates( 0x1FFF ) != KErrNone );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrate670 );    
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate515 );
    assertL( iInCodec->SetAllowedBitrates( 0 ) != KErrNone );
    assertL( iInCodec->iAllowedBitrates == KMceAllowedAmrNbBitrate670 );    
    assertL( iInCodec->iBitrate == KMceAmrNbBitrate515 );
    
    CleanupStack::PopAndDestroy( updatedSession );

//session with new binded stream

    audioOut = CMceComAudioStream::NewLC();
    outCodec = CMceComAMRCodec::NewLC( amr );
    audioOut->iID = TMceMediaId( uid, 3 );
    outCodec->iID = TMceMediaId( uid, 4 );
    outCodec->iPayloadType = 97;
    outCodec->iBitrate = 5000;
    audioOut->AddCodecL( outCodec );
    CleanupStack::Pop( outCodec );
    audioIn->BindL( audioOut );
    CleanupStack::Pop( audioOut );
    
    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event2( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event2 );

    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 1 );
    iAudioIn = static_cast<CMceComAudioStream*>( iSession->Streams()[0] );
    assertL( iAudioIn->iID == TMceMediaId( uid, 1 ) );
    assertL( iAudioIn->BoundStream() );
    assertL( iAudioIn->CodecCount() == 1 );
    iInCodec = static_cast<CMceComAMRCodec*>(iAudioIn->CodecL( 0 ) );
    assertL( iInCodec->iID == TMceMediaId( uid, 2 ) );
    assertL( iInCodec->iPayloadType == 96 );
    assertL( iInCodec->iBitrate == 2300 );
    iAudioOut = static_cast<CMceComAudioStream*>( &(iAudioIn->BoundStreamL() ) );
    assertL( iAudioOut->iID == TMceMediaId( uid, 3 ) );
    assertL( iAudioOut->CodecCount() == 1 );
    iOutCodec = static_cast<CMceComAMRCodec*>( iAudioOut->CodecL( 0 ) );
    assertL( iOutCodec->iID == TMceMediaId( uid, 4 ) );
    assertL( iOutCodec->iPayloadType == 97 );
    assertL( iOutCodec->iBitrate == 5000 );
    
    assertL( updatedSession->Streams().Count() == 0 );
    CleanupStack::PopAndDestroy( updatedSession );

//session with sinks & sources

    rtpSource = CMceComRtpSource::NewL();
    CleanupStack::PushL( rtpSource );
    rtpSource->iID = TMceMediaId( uid, 5 );
    rtpSource->Enabled( ETrue );
    audioIn->SetSourceL( rtpSource );
    CleanupStack::Pop( rtpSource );
    
    rtpSink = CMceComRtpSink::NewL();
    CleanupStack::PushL( rtpSink );
    rtpSink->iID = TMceMediaId( uid, 6 );
    rtpSink->Enabled( EFalse );
    audioOut->AddSinkL( rtpSink );
    CleanupStack::Pop( rtpSink );

    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event3( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event3 );

    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 1 );
    iAudioIn = static_cast<CMceComAudioStream*>( iSession->Streams()[0] );
    assertL( iAudioIn->iID == TMceMediaId( uid, 1 ) );
    assertL( iAudioIn->BoundStream() );
    assertL( iAudioIn->CodecCount() == 1 );
    iInCodec = static_cast<CMceComAMRCodec*>(iAudioIn->CodecL( 0 ) );
    assertL( iInCodec->iID == TMceMediaId( uid, 2 ) );
    assertL( iInCodec->iPayloadType == 96 );
    assertL( iInCodec->iBitrate == 2300 );
    iAudioOut = static_cast<CMceComAudioStream*>( &(iAudioIn->BoundStreamL() ) );
    assertL( iAudioOut->iID == TMceMediaId( uid, 3 ) );
    assertL( iAudioOut->BoundStream() );
    assertL( iAudioOut->CodecCount() == 1 );
    iOutCodec = static_cast<CMceComAMRCodec*>( iAudioOut->CodecL( 0 ) );
    assertL( iOutCodec->iID == TMceMediaId( uid, 4 ) );
    assertL( iOutCodec->iPayloadType == 97 );
    assertL( iOutCodec->iBitrate == 5000 );
    iRtpSource = static_cast<CMceComRtpSource*>( iAudioIn->Source() );
    assertL( iRtpSource->iID == TMceMediaId( uid, 5 ) );
    assertL( iRtpSource->IsEnabled() );
    iRtpSink = static_cast<CMceComRtpSink*>( iAudioOut->Sinks()[0] );
    assertL( iRtpSink->iID == TMceMediaId( uid, 6 ) );
    assertL( !iRtpSink->IsEnabled() );
    
    assertL( updatedSession->Streams().Count() == 0 );
    CleanupStack::PopAndDestroy( updatedSession );

    
//session with added stream sinks & sources
    
    TInt i = 0;
    for ( i = 0; i<3;i++) 
        {
        CMceComAudioStream* newAudio = CMceComAudioStream::NewLC();
        newAudio->iID = TMceMediaId( uid, 300+i );
        
        speaker = CMceComSpeakerSink::NewL();
        CleanupStack::PushL( speaker );
        speaker->iID = TMceMediaId( uid, 100+i );
        speaker->Enabled( ETrue );
        audioIn->AddSinkL( speaker );
        CleanupStack::Pop( speaker );
        CMceComAMRCodec* newCodec = CMceComAMRCodec::NewLC( amr );
        newCodec->iID = TMceMediaId( uid, 500+i );
        audioIn->AddCodecL( newCodec );
        CleanupStack::Pop( newCodec ); 
        
        mic = CMceComMicSource::NewL();
        CleanupStack::PushL( mic );
        mic->iID = TMceMediaId( uid, 200+i );
        mic->Enabled( ETrue );
        audioOut->SetSourceL( mic );
        CleanupStack::Pop( mic );
        iClientSession->AddStreamL( newAudio );
        CleanupStack::Pop( newAudio );
            
        updatedSession = ClientSessionReceivedLC();
        TMceComEvent event4( ids, updatedSession, EMceItcUpdate, handler );
        iSession->EventReceivedL( event4 );

        assertL( iSession->iID == 1 );
        assertL( iSession->iIsConnectionActive );
        assertL( iSession->iMccID == 12 );
        assertL( iSession->iState == CMceSession::EIncoming );
        assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
        assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
        assertL( iSession->Streams().Count() == 2 + i );
        assertL( iSession->Streams()[1+i]->iID == TMceMediaId( uid, 300+i ) );
        iAudioIn = static_cast<CMceComAudioStream*>( iSession->Streams()[0] );
        assertL( iAudioIn->iID == TMceMediaId( uid, 1 ) );
        assertL( iAudioIn->BoundStream() );
        assertL( iAudioIn->CodecCount() == 2 + i );
        iInCodec = static_cast<CMceComAMRCodec*>(iAudioIn->CodecL( 0 ) );
        assertL( iInCodec->iID == TMceMediaId( uid, 2 ) );
        assertL( iInCodec->iPayloadType == 96 );
        assertL( iInCodec->iBitrate == 2300 );
        iAudioOut = static_cast<CMceComAudioStream*>( &(iAudioIn->BoundStreamL() ) );
        assertL( iAudioOut->iID == TMceMediaId( uid, 3 ) );
        assertL( iAudioOut->BoundStream() );
        assertL( iAudioOut->CodecCount() == 1 );
        iOutCodec = static_cast<CMceComAMRCodec*>( iAudioOut->CodecL( 0 ) );
        assertL( iOutCodec->iID == TMceMediaId( uid, 4 ) );
        assertL( iOutCodec->iPayloadType == 97 );
        assertL( iOutCodec->iBitrate == 5000 );
        iRtpSource = static_cast<CMceComRtpSource*>( iAudioIn->Source() );
        assertL( iRtpSource->iID == TMceMediaId( uid, 5 ) );
        assertL( iRtpSource->IsEnabled() );
        iRtpSink = static_cast<CMceComRtpSink*>( iAudioOut->Sinks()[0] );
        assertL( iRtpSink->iID == TMceMediaId( uid, 6 ) );
        assertL( !iRtpSink->IsEnabled() );
        iSpeaker = static_cast<CMceComSpeakerSink*>( iAudioIn->Sinks()[i] );
        assertL( iSpeaker->iID == TMceMediaId( uid, 100+i ) );
        assertL( iSpeaker->IsEnabled() );
        iMic = static_cast<CMceComMicSource*>( iAudioOut->Source() );
        assertL( iMic->iID == TMceMediaId( uid, 200+i ) );
        assertL( iMic->IsEnabled() );
        
        assertL( updatedSession->Streams().Count() == 0 );
        CleanupStack::PopAndDestroy( updatedSession );
        
        }

        
//session with removed sinks & sources

    for ( i = 0; i<3;i++) 
        {
        audioIn->DeleteSink( 0 );
        audioOut->SetSourceL( NULL );
            
        updatedSession = ClientSessionReceivedLC();
        TMceComEvent event4( ids, updatedSession, EMceItcUpdate, handler );
        iSession->EventReceivedL( event4 );

        assertL( iSession->iID == 1 );
        assertL( iSession->iIsConnectionActive );
        assertL( iSession->iMccID == 12 );
        assertL( iSession->iState == CMceSession::EIncoming );
        assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
        assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
        assertL( iSession->Streams().Count() == 4 );
        iAudioIn = static_cast<CMceComAudioStream*>( iSession->Streams()[0] );
        assertL( iAudioIn->iID == TMceMediaId( uid, 1 ) );
        assertL( iAudioIn->BoundStream() );
        assertL( iAudioIn->CodecCount() == 4 );
        iInCodec = static_cast<CMceComAMRCodec*>(iAudioIn->CodecL( 0 ) );
        assertL( iInCodec->iID == TMceMediaId( uid, 2 ) );
        assertL( iInCodec->iPayloadType == 96 );
        assertL( iInCodec->iBitrate == 2300 );
        iAudioOut = static_cast<CMceComAudioStream*>( &(iAudioIn->BoundStreamL() ) );
        assertL( iAudioOut->iID == TMceMediaId( uid, 3 ) );
        assertL( iAudioOut->BoundStream() );
        assertL( iAudioOut->CodecCount() == 1 );
        iOutCodec = static_cast<CMceComAMRCodec*>( iAudioOut->CodecL( 0 ) );
        assertL( iOutCodec->iID == TMceMediaId( uid, 4 ) );
        assertL( iOutCodec->iPayloadType == 97 );
        assertL( iOutCodec->iBitrate == 5000 );
        iRtpSource = static_cast<CMceComRtpSource*>( iAudioIn->Source() );
        assertL( iRtpSource->iID == TMceMediaId( uid, 5 ) );
        assertL( iRtpSource->IsEnabled() );
        iRtpSink = static_cast<CMceComRtpSink*>( iAudioOut->Sinks()[0] );
        assertL( iRtpSink->iID == TMceMediaId( uid, 6 ) );
        assertL( !iRtpSink->IsEnabled() );
        assertL( iAudioIn->Sinks().Count() == 2 - i );
        assertL( iAudioOut->Source() == NULL );
        
        assertL( updatedSession->Streams().Count() == 0 );
        CleanupStack::PopAndDestroy( updatedSession );
        
        }
//session with removed binded stream
    
    audioIn->BindL( NULL );
        
    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event5( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event5 );

    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 4 );
    iAudioIn = static_cast<CMceComAudioStream*>( iSession->Streams()[0] );
    assertL( iAudioIn->iID == TMceMediaId( uid, 1 ) );
    assertL( !iAudioIn->BoundStream() );
    assertL( iAudioIn->CodecCount() == 4 );
    iInCodec = static_cast<CMceComAMRCodec*>(iAudioIn->CodecL( 0 ) );
    assertL( iInCodec->iID == TMceMediaId( uid, 2 ) );
    assertL( iInCodec->iPayloadType == 96 );
    assertL( iInCodec->iBitrate == 2300 );
    iRtpSource = static_cast<CMceComRtpSource*>( iAudioIn->Source() );
    assertL( iRtpSource->iID == TMceMediaId( uid, 5 ) );
    assertL( iRtpSource->IsEnabled() );
    
    assertL( updatedSession->Streams().Count() == 0 );
    CleanupStack::PopAndDestroy( updatedSession );
    
//session with removed all streams
    
    while( iClientSession->Streams().Count() > 0 )
        {
        CMceComMediaStream* stream = iClientSession->Streams()[0];
        iClientSession->Streams().Remove( 0 );
        delete stream;
        }

    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event6( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event6 );

    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 0 );
    
    assertL( updatedSession->Streams().Count() == 0 );
    CleanupStack::PopAndDestroy( updatedSession );
    
    }
    

// ----------------------------------------------------------------------------
// CMceComSessionTest::TestUpdate2L
// ----------------------------------------------------------------------------
//
void CMceComSessionTest::TestUpdate2L()
    {

    CMceComVideoStream* videoIn = NULL;
    CMceComH263Codec* inCodec = NULL;
    CMceComVideoStream* videoOut = NULL;
    CMceComH263Codec* outCodec = NULL;

    CMceComRtpSink* rtpSink = NULL;
    CMceComRtpSource* rtpSource = NULL;
    CMceComDisplaySink* displaySink = NULL;
    CMceComCameraSource* cameraSource = NULL;

    TUid uid = TUid::Uid( 777 );
    TMceIds ids;
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    TMceComEventHandlerStub handler( *iMediaManager );
    TBuf8<KMceMaxSdpNameLength> amr;
    amr.Append( _L8("AMR") );
    
    iSession = CMceComSession::NewL();
    iSession->iType = CMceComSession::EInSession;
    iSession->iID = 1;
    iSession->iIsConnectionActive = ETrue;
    iSession->iMccID = 12;
    iSession->iState = CMceSession::EIncoming;
    delete iSession->iOriginator;
    iSession->iOriginator = 0;
    iSession->iOriginator = KMceOriginator().AllocL();
    delete iSession->iRecipient; 
    iSession->iRecipient = 0;
    iSession->iRecipient = KMceRecipient().AllocL();
    
    CMceMsgObject<CMceComSession>* sessionMsg = new (ELeave) CMceMsgObject<CMceComSession>( *iSession, EMceItcMsgTypeSession );
    CleanupStack::PushL( sessionMsg );
    sessionMsg->EncodeL();
    
    // Decode takes ownbership temporarily!
    CMceComSession* tempSession = iSession;
    iSession = 0;
    sessionMsg->DecodeL( sessionMsg->EncodeBuffer().Ptr( 0 ) );
    iSession = tempSession;
    
    iClientSession = sessionMsg->iObject;
    
    CleanupStack::PopAndDestroy( sessionMsg );
    
    assertL( iClientSession->Id() == 1 );
    assertL( iClientSession->iType == CMceComSession::EInSession );
    assertL( iClientSession->iIsConnectionActive );
    assertL( iClientSession->iMccID == KMceNotAssigned );
    assertL( iClientSession->iState == CMceSession::EIncoming );
    assertL( iClientSession->iOriginator->Compare( KMceOriginator ) == 0 );
    assertL( iClientSession->iRecipient->Compare( KMceRecipient ) == 0 );

    assertL( iSession->Id() == 1 );
    assertL( iSession->iType == CMceComSession::EInSession );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator ) == 0 );

    
//just session    
    
    delete iClientSession->iOriginator;
    iClientSession->iOriginator = 0;
    iClientSession->iOriginator = KMceOriginator1().AllocL();
    delete iClientSession->iRecipient;
    iClientSession->iRecipient = 0;
    iClientSession->iRecipient = KMceRecipient1().AllocL();

    CMceComSession* updatedSession = ClientSessionReceivedLC();
    assertL( updatedSession->Id() == 1 );
    assertL( updatedSession->iType == CMceComSession::EInSession );
    assertL( updatedSession->iIsConnectionActive );
    assertL( updatedSession->iMccID == KMceNotAssigned );
    assertL( updatedSession->iState == CMceSession::EIncoming );
    assertL( updatedSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( updatedSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
        
        
    TMceComEvent event( ids, updatedSession, EMceItcUpdate, handler );

    iSession->EventReceivedL( event );
    CleanupStack::PopAndDestroy( updatedSession );
    
    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->Streams().Count() == 0 );


//session with stream
    
	TMceComFactory factory;

	videoIn = 
	    static_cast<CMceComVideoStream*>( factory.MediaStreamFactory().CreateLC( KMceVideo ) );
	videoIn->iLocalMediaPort = KMceMMTestVideoLocalPort;
	 
	rtpSource = 
	    static_cast<CMceComRtpSource*>( factory.SourceFactory().CreateLC( KMceRTPSource ) );

	rtpSource->iBufferLength = KMceMMTestDefaultBufferLength;
	rtpSource->iBufferTreshold = KMceMMTestDefaultBufferThreshold;
	
	displaySink = 
	    static_cast<CMceComDisplaySink*>( factory.SinkFactory().CreateLC( KMceDisplaySink ) );
	videoIn->AddSinkL( displaySink );
	CleanupStack::Pop( displaySink );

	videoIn->SetSourceL( rtpSource );
	CleanupStack::Pop( rtpSource );


    CMceComVideoCodec* h263 = 
        static_cast<CMceComVideoCodec*>( factory.VideoCodecFactory().CreateLC( KMceSDPNameH263() ) );
	h263->iClockRate = KMceMMTestVideoClockrate;
	h263->iPayloadType = KMceMMTestVideoPayloadType;
	h263->iCodecMode = KMceMMTestVideoCodecMode;
	h263->iAllowedBitrates = KMceMMTestVideoAllowedBitrates;
	h263->iBitrate = KMceMMTestVideoBitrate;
	
	videoIn->AddCodecL( h263 );
	CleanupStack::Pop( h263 );
    
    videoIn->iID = TMceMediaId( uid, 1 );
    h263->iID = TMceMediaId( uid, 2 );
    
    iClientSession->AddStreamL( videoIn );
    CleanupStack::Pop( videoIn );
    
    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event1( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event1 );
    
    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 1 );
    iVideoIn = static_cast<CMceComVideoStream*>( iSession->Streams()[0] );
    assertL( iVideoIn->iID == TMceMediaId( uid, 1 ) );
    assertL( iVideoIn->CodecCount() == 1 );
    assertL( !iVideoIn->BoundStream() );
    iInVideoCodec = static_cast<CMceComH263Codec*>(iVideoIn->CodecL( 0 ) );
    assertL( iInVideoCodec->iID == TMceMediaId( uid, 2 ) );
    assertL( updatedSession->Streams().Count() == 0 );

    
    //bitrate and allowed bitrate tests for H263
    assertL( iInVideoCodec->SetBitrate( KMceH263Level10Bitrate ) == KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate10 );
    
    assertL( iInVideoCodec->SetAllowedBitrates( KMceAllowedH263BitrateAll ) == KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263BitrateAll );

    assertL( iInVideoCodec->SetBitrate( KMceH263Level45Bitrate ) == KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedAmrNbBitrateAll );

    assertL( iInVideoCodec->SetAllowedBitrates( KMceAllowedH263Bitrate10 ) == KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate10 );

    assertL( iInVideoCodec->SetAllowedBitrates( KMceAllowedH263Bitrate45 ) == KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate45 );

    assertL( iInVideoCodec->SetMaxBitrate( KMceH263Level10Bitrate ) == KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate10 );

    assertL( iInVideoCodec->SetMaxBitrate( KMceH263Level45Bitrate ) == KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate45 );

    assertL( iInVideoCodec->SetBitrate( 0 ) != KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate45 );

    assertL( iInVideoCodec->SetAllowedBitrates( 0 ) != KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate45 );

    assertL( iInVideoCodec->SetAllowedBitrates( 128000 ) != KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate45 );

    assertL( iInVideoCodec->SetMaxBitrate( 0 ) != KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level10Bitrate );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate45 );

    assertL( iInVideoCodec->SetBitrate( KMceH263Level45Bitrate - 100 ) == KErrNone );
    assertL( iInVideoCodec->iBitrate == KMceH263Level45Bitrate - 100 );
    assertL( iInVideoCodec->iMaxBitRate == KMceH263Level45Bitrate );
    assertL( iInVideoCodec->iAllowedBitrates == KMceAllowedH263Bitrate45 );

    
    CleanupStack::PopAndDestroy( updatedSession );

//session with new binded stream

	videoOut = 
	    static_cast<CMceComVideoStream*>( factory.MediaStreamFactory().CreateLC( KMceVideo ) );
	videoOut->iLocalMediaPort = KMceMMTestVideoLocalPort;

	cameraSource = 
	    static_cast<CMceComCameraSource*>( factory.SourceFactory().CreateLC( KMceCameraSource ) );
	
	videoOut->SetSourceL( cameraSource );
	CleanupStack::Pop( cameraSource );
    videoOut->iID = TMceMediaId( uid, 3 );

    h263 = 
        static_cast<CMceComVideoCodec*>( factory.VideoCodecFactory().CreateLC( KMceSDPNameH263() ) );
	h263->iClockRate = KMceMMTestVideoClockrate;
	h263->iPayloadType = KMceMMTestVideoPayloadType;
	h263->iCodecMode = KMceMMTestVideoCodecMode;
	h263->iAllowedBitrates = KMceMMTestVideoAllowedBitrates;
	h263->iBitrate = KMceMMTestVideoBitrate;
    h263->iID = TMceMediaId( uid, 4 );
	videoOut->AddCodecL( h263 );
	CleanupStack::Pop( h263 );

	CMceComVideoStream* localStream = 
	    static_cast<CMceComVideoStream*>( factory.MediaStreamFactory().CreateLC( KMceVideo ) );

	displaySink = 
	    static_cast<CMceComDisplaySink*>( factory.SinkFactory().CreateLC( KMceDisplaySink ) );
	localStream->AddSinkL( displaySink );
	CleanupStack::Pop( displaySink );

	localStream->SetSourceL( cameraSource );

    h263 = 
        static_cast<CMceComVideoCodec*>( factory.VideoCodecFactory().CreateLC( KMceSDPNameH263() ) );
	localStream->AddCodecL( h263 );
    h263->iID = TMceMediaId( uid, 99 );
	CleanupStack::Pop( h263 );

	iClientSession->AddStreamL( localStream );   
	CleanupStack::Pop( localStream );

    videoIn->BindL( videoOut );
    CleanupStack::Pop( videoOut );
		
    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event2( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event2 );

    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 2 );
    iVideoIn = static_cast<CMceComVideoStream*>( iSession->Streams()[0] );
    assertL( iVideoIn->iID == TMceMediaId( uid, 1 ) );
    assertL( iVideoIn->BoundStream() );
    assertL( iVideoIn->CodecCount() == 1 );
    iInVideoCodec = static_cast<CMceComH263Codec*>(iVideoIn->CodecL( 0 ) );
    assertL( iInVideoCodec->iID == TMceMediaId( uid, 2 ) );
    iVideoOut = static_cast<CMceComVideoStream*>( &(iVideoIn->BoundStreamL() ) );
    assertL( iVideoOut->iID == TMceMediaId( uid, 3 ) );
    assertL( iVideoOut->CodecCount() == 1 );
    iOutVideoCodec = static_cast<CMceComH263Codec*>( iVideoOut->CodecL( 0 ) );
    assertL( iOutVideoCodec->iID == TMceMediaId( uid, 4 ) );
    
    assertL( updatedSession->Streams().Count() == 0 );
    CleanupStack::PopAndDestroy( updatedSession );

//session with sinks & sources

    rtpSource = CMceComRtpSource::NewL();
    CleanupStack::PushL( rtpSource );
    rtpSource->iID = TMceMediaId( uid, 5 );
    rtpSource->Enabled( ETrue );
    videoIn->SetSourceL( rtpSource );
    CleanupStack::Pop( rtpSource );

	rtpSink = 
	    static_cast<CMceComRtpSink*>( factory.SinkFactory().CreateLC( KMceRTPSink ) );
    rtpSink->iID = TMceMediaId( uid, 6 );
    rtpSink->Enabled( EFalse );
	videoOut->AddSinkL( rtpSink );
	CleanupStack::Pop( rtpSink );

    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event3( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event3 );

    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 2 );
    iVideoIn = static_cast<CMceComVideoStream*>( iSession->Streams()[0] );
    assertL( iVideoIn->iID == TMceMediaId( uid, 1 ) );
    assertL( iVideoIn->BoundStream() );
    assertL( iVideoIn->CodecCount() == 1 );
    iInVideoCodec = static_cast<CMceComH263Codec*>(iVideoIn->CodecL( 0 ) );
    assertL( iInVideoCodec->iID == TMceMediaId( uid, 2 ) );
    iVideoOut = static_cast<CMceComVideoStream*>( &(iVideoIn->BoundStreamL() ) );
    assertL( iVideoOut->iID == TMceMediaId( uid, 3 ) );
    assertL( iVideoOut->BoundStream() );
    assertL( iVideoOut->CodecCount() == 1 );
    iOutVideoCodec = static_cast<CMceComH263Codec*>( iVideoOut->CodecL( 0 ) );
    assertL( iOutVideoCodec->iID == TMceMediaId( uid, 4 ) );
    iRtpSource = static_cast<CMceComRtpSource*>( iVideoIn->Source() );
    assertL( iRtpSource->iID == TMceMediaId( uid, 5 ) );
    assertL( iRtpSource->IsEnabled() );
    iRtpSink = static_cast<CMceComRtpSink*>( iVideoOut->Sinks()[0] );
    assertL( iRtpSink->iID == TMceMediaId( uid, 6 ) );
    
    assertL( updatedSession->Streams().Count() == 0 );
    CleanupStack::PopAndDestroy( updatedSession );

    
//session with added stream sinks & sources
    
    TInt i = 0;
    for ( i = 0; i<3;i++) 
        {
        CMceComVideoStream* newVideo = CMceComVideoStream::NewLC();
        newVideo->iID = TMceMediaId( uid, 300+i );
        
        displaySink = CMceComDisplaySink::NewL();
        CleanupStack::PushL( displaySink );
        displaySink->iID = TMceMediaId( uid, 100+i );
        displaySink->Enabled( ETrue );
        videoIn->AddSinkL( displaySink );
        CleanupStack::Pop( displaySink );
        CMceComH263Codec* newCodec = CMceComH263Codec::NewLC( KMceSDPNameH263() );
        newCodec->iID = TMceMediaId( uid, 500+i );
        videoIn->AddCodecL( newCodec );
        CleanupStack::Pop( newCodec ); 
        
        CMceComFileSource* file = CMceComFileSource::NewLC();
        file->iID = TMceMediaId( uid, 200+i );
        file->Enabled( ETrue );
        videoOut->SetSourceL( file );
        CleanupStack::Pop( file );
        iClientSession->AddStreamL( newVideo );
        CleanupStack::Pop( newVideo );
            
        updatedSession = ClientSessionReceivedLC();
        TMceComEvent event4( ids, updatedSession, EMceItcUpdate, handler );
        iSession->EventReceivedL( event4 );

        assertL( iSession->iID == 1 );
        assertL( iSession->iIsConnectionActive );
        assertL( iSession->iMccID == 12 );
        assertL( iSession->iState == CMceSession::EIncoming );
        assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
        assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
        assertL( iSession->Streams().Count() == 3 + i );
        assertL( iSession->Streams()[2+i]->iID == TMceMediaId( uid, 300+i ) );
        iVideoIn = static_cast<CMceComVideoStream*>( iSession->Streams()[0] );
        assertL( iVideoIn->iID == TMceMediaId( uid, 1 ) );
        assertL( iVideoIn->BoundStream() );
        assertL( iVideoIn->CodecCount() == 2 + i );
        iInVideoCodec = static_cast<CMceComH263Codec*>(iVideoIn->CodecL( 0 ) );
        assertL( iInVideoCodec->iID == TMceMediaId( uid, 2 ) );
        iVideoOut = static_cast<CMceComVideoStream*>( &(iVideoIn->BoundStreamL() ) );
        assertL( iVideoOut->iID == TMceMediaId( uid, 3 ) );
        assertL( iVideoOut->BoundStream() );
        assertL( iVideoOut->CodecCount() == 1 );
        iOutVideoCodec = static_cast<CMceComH263Codec*>( iVideoOut->CodecL(0 ) );
        assertL( iOutVideoCodec->iID == TMceMediaId( uid, 4 ) );
        iRtpSource = static_cast<CMceComRtpSource*>( iVideoIn->Source() );
        assertL( iRtpSource->iID == TMceMediaId( uid, 5 ) );
        assertL( iRtpSource->IsEnabled() );
        iRtpSink = static_cast<CMceComRtpSink*>( iVideoOut->Sinks()[0] );
        assertL( iRtpSink->iID == TMceMediaId( uid, 6 ) );
        assertL( !iRtpSink->IsEnabled() );
        iDisplaySink = static_cast<CMceComDisplaySink*>( iVideoIn->Sinks()[1+i] );
        assertL( iDisplaySink->iID == TMceMediaId( uid, 100+i ) );
        assertL( iDisplaySink->IsEnabled() );
        file = static_cast<CMceComFileSource*>( iVideoOut->Source() );
        assertL( file->iID == TMceMediaId( uid, 200+i ) );
        assertL( file->IsEnabled() );
        
        assertL( updatedSession->Streams().Count() == 0 );
        CleanupStack::PopAndDestroy( updatedSession );
        
        }

        
//session with removed sinks & sources

    for ( i = 0; i<3;i++) 
        {
        videoIn->DeleteSink( 0 );
        videoOut->SetSourceL( NULL );
            
        updatedSession = ClientSessionReceivedLC();
        TMceComEvent event4( ids, updatedSession, EMceItcUpdate, handler );
        iSession->EventReceivedL( event4 );

        assertL( iSession->iID == 1 );
        assertL( iSession->iIsConnectionActive );
        assertL( iSession->iMccID == 12 );
        assertL( iSession->iState == CMceSession::EIncoming );
        assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
        assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
        assertL( iSession->Streams().Count() == 5 );
        iVideoIn = static_cast<CMceComVideoStream*>( iSession->Streams()[0] );
        assertL( iVideoIn->iID == TMceMediaId( uid, 1 ) );
        assertL( iVideoIn->BoundStream() );
        assertL( iVideoIn->CodecCount() == 4 );
        iInVideoCodec = static_cast<CMceComH263Codec*>(iVideoIn->CodecL( 0 ) );
        assertL( iInVideoCodec->iID == TMceMediaId( uid, 2 ) );
        iVideoOut = static_cast<CMceComVideoStream*>( &(iVideoIn->BoundStreamL() ) );
        assertL( iVideoOut->iID == TMceMediaId( uid, 3 ) );
        assertL( iVideoOut->BoundStream() );
        assertL( iVideoOut->CodecCount() == 1 );
        iOutVideoCodec = static_cast<CMceComH263Codec*>( iVideoOut->CodecL( 0 ) );
        assertL( iOutVideoCodec->iID == TMceMediaId( uid, 4 ) );
        iRtpSource = static_cast<CMceComRtpSource*>( iVideoIn->Source() );
        assertL( iRtpSource->iID == TMceMediaId( uid, 5 ) );
        assertL( iRtpSource->IsEnabled() );
        iRtpSink = static_cast<CMceComRtpSink*>( iVideoOut->Sinks()[0] );
        assertL( iRtpSink->iID == TMceMediaId( uid, 6 ) );
        assertL( !iRtpSink->IsEnabled() );
        assertL( iVideoIn->Sinks().Count() == 3 - i );
        assertL( iVideoOut->Source() == NULL );
        
        assertL( updatedSession->Streams().Count() == 0 );
        CleanupStack::PopAndDestroy( updatedSession );
        
        }
//session with removed binded stream
    
    videoIn->BindL( NULL );
        
    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event5( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event5 );

    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 5 );
    iVideoIn = static_cast<CMceComVideoStream*>( iSession->Streams()[0] );
    assertL( iVideoIn->iID == TMceMediaId( uid, 1 ) );
    assertL( !iVideoIn->BoundStream() );
    assertL( iVideoIn->CodecCount() == 4 );
    iInVideoCodec = static_cast<CMceComH263Codec*>(iVideoIn->CodecL( 0 ) );
    assertL( iInVideoCodec->iID == TMceMediaId( uid, 2 ) );
    iRtpSource = static_cast<CMceComRtpSource*>( iVideoIn->Source() );
    assertL( iRtpSource->iID == TMceMediaId( uid, 5 ) );
    assertL( iRtpSource->IsEnabled() );
    
    assertL( updatedSession->Streams().Count() == 0 );
    CleanupStack::PopAndDestroy( updatedSession );
    
//session with removed all streams
    
    while( iClientSession->Streams().Count() > 0 )
        {
        CMceComMediaStream* stream = iClientSession->Streams()[0];
        iClientSession->Streams().Remove( 0 );
        delete stream;
        }

    updatedSession = ClientSessionReceivedLC();
    TMceComEvent event6( ids, updatedSession, EMceItcUpdate, handler );
    iSession->EventReceivedL( event6 );

    assertL( iSession->iID == 1 );
    assertL( iSession->iIsConnectionActive );
    assertL( iSession->iMccID == 12 );
    assertL( iSession->iState == CMceSession::EIncoming );
    assertL( iSession->iRecipient->Compare( KMceRecipient1 ) == 0 );
    assertL( iSession->iOriginator->Compare( KMceOriginator1 ) == 0 );
    assertL( iSession->Streams().Count() == 0 );
    
    assertL( updatedSession->Streams().Count() == 0 );
    CleanupStack::PopAndDestroy( updatedSession );
    }

// ----------------------------------------------------------------------------
// CMceComSessionTest::ClientSessionReceivedLC
// ----------------------------------------------------------------------------
//	
CMceComSession* CMceComSessionTest::ClientSessionReceivedLC()
    {

    CMceComSession* receivedSession = NULL;
    
    CMceMsgObject<CMceComSession>* sessionMsg = new (ELeave) CMceMsgObject<CMceComSession>( *iClientSession, EMceItcMsgTypeSession );
    CleanupStack::PushL( sessionMsg );
    sessionMsg->EncodeL();
    
    // Decode takes ownbership temporarily!
    CMceComSession* tempSession = iClientSession;
    iClientSession = 0;
    sessionMsg->DecodeL( sessionMsg->EncodeBuffer().Ptr( 0 ) );
    iClientSession = tempSession;
    
    receivedSession = sessionMsg->iObject;
    
    CleanupStack::PopAndDestroy( sessionMsg );

    CleanupStack::PushL( receivedSession );
    
    return receivedSession;    
    }
