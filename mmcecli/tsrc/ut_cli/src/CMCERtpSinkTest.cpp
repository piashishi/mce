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
#include "CMceRtpSinkTest.h"
#include "mcestubs.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
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
#include "mceserial.h"
#include "mceevents.h"

const TBool KSuppressedTrue = ETrue;
const TUint32 KSomeSSRC = 500;
const TUint32 KLastPacket = 1000;
_LIT8( KTestIdentifier, "TestIdentifier");
const TUint8 KMceTestCategory = 5;

// ----------------------------------------------------------------------------
// CMceRtpSinkTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceRtpSinkTest::setUpL()
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
// CMceRtpSinkTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::tearDown()
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
// CMceRtpSinkTest::suiteL
// ----------------------------------------------------------------------------
//
    
MEUnitTestSuite* CMceRtpSinkTest::suiteL()
    {
    CMceRtpSinkTest* suite = new CMceRtpSinkTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }
    
EUNIT_BEGIN_TEST_TABLE( 
    CMceRtpSinkTest,
    "CMceRtpSinkTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, EnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, DisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, LastPacketTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, SendSRTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, UpdateTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, DoITCSendTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, HandleEventTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSinkTest", setUpL, EventReceivedTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceRtpSinkTest::ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::ConstructionTestL()
    {
    //rtp sink
    CMceRtpSink* rtpSink = CMceRtpSink::NewL();
    CleanupStack::PushL( rtpSink );
    EUNIT_ASSERT( rtpSink->Type() == KMceRTPSink );
    EUNIT_ASSERT( !rtpSink->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    CMceComRtpSink* rtpFlat = static_cast<CMceComRtpSink*>(rtpSink->iFlatData);
    EUNIT_ASSERT( rtpFlat->iSuppressRTCP == EFalse);
    EUNIT_ASSERT( rtpFlat->iSSRC == 0); 
    EUNIT_ASSERT( rtpSink->Ssrc() == 0 );
    
    CleanupStack::PopAndDestroy( rtpSink );
    
    rtpSink = CMceRtpSink::NewL(ETrue); // Same as NewL()
    CleanupStack::PushL( rtpSink );
    EUNIT_ASSERT( rtpSink->Type() == KMceRTPSink );
    EUNIT_ASSERT( !rtpSink->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    rtpFlat = static_cast<CMceComRtpSink*>(rtpSink->iFlatData);
    EUNIT_ASSERT( rtpFlat->iSuppressRTCP );
    CleanupStack::PopAndDestroy( rtpSink );
    }


// ----------------------------------------------------------------------------
// CMceRtpSinkTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::ExternalizeTestL()
    {
    CMceRtpSink* rtpSink = CMceRtpSink::NewLC();
    CMceComRtpSink* rtpFlat = static_cast<CMceComRtpSink*>(rtpSink->iFlatData);
       
    rtpFlat->iID.iAppId = KMceTestAppId;
    rtpFlat->iID.iId = KMceTestMiscId; 
    rtpFlat->iType = KMceTestSinkType;
    rtpFlat->Enabled ( KMceTestEnabledFalse );
	rtpFlat->iSuppressRTCP = KSuppressedTrue;
	rtpFlat->iSSRC = KSomeSSRC;
	rtpFlat->iLastPacket = KLastPacket;	
    rtpFlat->iCategory = KMceTestCategory;
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	rtpSink->ExternalizeL( serCtx );
	
	CleanupStack::PopAndDestroy();//serCtx
	writeStream.Close();
	writeStream.Pop();
	
	RDesReadStream readStream( buffer );
	readStream.PushL();
	
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestSinkType );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestCategory );
	EUNIT_ASSERT( KMceTestAppId == readStream.ReadUint32L() );
	EUNIT_ASSERT( KMceTestMiscId == readStream.ReadUint32L() );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestEnabledFalse );
	EUNIT_ASSERT( readStream.ReadUint8L() == KSuppressedTrue );
	EUNIT_ASSERT( readStream.ReadUint32L() == KSomeSSRC );
	EUNIT_ASSERT( readStream.ReadUint32L() == KLastPacket );
		
	readStream.Close();
	readStream.Pop();   
	
	CleanupStack::PopAndDestroy( rtpSink ); 
    }


// ----------------------------------------------------------------------------
// CMceRtpSinkTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::InternalizeTestL()
    {
    CMceRtpSink* rtpSink = CMceRtpSink::NewLC();
    CMceComRtpSink* rtpFlat = static_cast<CMceComRtpSink*>(rtpSink->iFlatData);
    
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();
    
    writeStream.WriteUint8L( KMceTestSinkType );
    writeStream.WriteUint8L( KMceTestCategory );
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( KMceTestEnabledFalse );
    
    writeStream.WriteUint8L( KSuppressedTrue );
    writeStream.WriteUint32L( KSomeSSRC );
    writeStream.WriteUint32L( KLastPacket );
    writeStream.WriteUint32L( KTestIdentifier().Length() );
    writeStream.WriteL( KTestIdentifier() );
    
	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    rtpSink->InternalizeL( serCtx );
    
    EUNIT_ASSERT( rtpFlat->iType == KMceTestSinkType );
    EUNIT_ASSERT( rtpFlat->IsEnabled() == KMceTestEnabledFalse );
    EUNIT_ASSERT( rtpFlat->Id().iAppId == KMceTestAppId );
    EUNIT_ASSERT( rtpFlat->Id().iId == KMceTestMiscId );
    
    EUNIT_ASSERT( rtpFlat->iSuppressRTCP == KSuppressedTrue );
    EUNIT_ASSERT( rtpFlat->iSSRC == KSomeSSRC );
    EUNIT_ASSERT( rtpFlat->iLastPacket == KLastPacket );
    EUNIT_ASSERT( rtpFlat->iIdentity->Des().Compare( KTestIdentifier ) == 0 );
    
	CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();
    
  	CleanupStack::PopAndDestroy( rtpSink ); 
    }
    

// ----------------------------------------------------------------------------
// CMceRtpSinkTest::EnableTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::EnableTestL()
    {
    // As long as function CMceRtpSink::Enable() does nothing
    // but calls base class DoEnable()-function, there is no need to
    // do more than just run the function once to keep coverage tool happy.
    
    CMceRtpSink* rtpSink = CMceRtpSink::NewLC();
    rtpSink->EnableL();
    CleanupStack::PopAndDestroy( rtpSink ); 
    }
    
    
// ----------------------------------------------------------------------------
// CMceRtpSinkTest::DisableTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::DisableTestL()
    {
    // As long as function CMceRtpSink::Disable() does nothing
    // but calls base class DoDisable()-function, there is no need to
    // do more than just run the function once to keep coverage tool happy.
    
    CMceRtpSink* rtpSink = CMceRtpSink::NewLC();
    rtpSink->DisableL();
    CleanupStack::PopAndDestroy( rtpSink );
    }
    

// ----------------------------------------------------------------------------
// CMceRtpSinkTest::LastPacketTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::LastPacketTestL()
    {
    CMceRtpSink* rtpSink = CMceRtpSink::NewLC();
    CMceComRtpSink* rtpFlat = static_cast<CMceComRtpSink*>(rtpSink->iFlatData);
    rtpFlat->iLastPacket = 30;
    
    EUNIT_ASSERT( rtpFlat->iLastPacket == rtpSink->LastPacket() );

    CleanupStack::PopAndDestroy( rtpSink );
    }
                
// ----------------------------------------------------------------------------
// CMceRtpSinkTest::SendSRTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::SendSRTestL()
    {

	MCE_CREATE_PROFILE;
    
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT_EQUALS( KMceRecipient(), iOutSession->Recipient() );

    CMceAudioStream* stream1 = NULL;

    stream1 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream1 );

	//rtp sink
    CMceRtpSink* rtpSink = CMceRtpSink::NewL();
    CleanupStack::PushL( rtpSink );

	// Ensure that no session is used during initialization
	rtpSink->iFlatData->iID.iAppId = 777;
	rtpSink->iFlatData->iID.iId = 777;
    
	TRAPD(err, rtpSink->SendSRL()); // No stream present, must leave
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
	    
    stream1->AddSinkL( rtpSink );
    CleanupStack::Pop( rtpSink );
    rtpSink->InitializeL( *stream1 );
    
	TRAP(err, rtpSink->SendSRL()); // No session present, must leave
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );

    iOutSession->AddStreamL( stream1 );
    CleanupStack::Pop( stream1 );
    stream1->InitializeL( *iOutSession, EFalse );

    TRAPD( error, rtpSink->SendSRL() ); // Session not established, does nothing
    MCE_TEST_HANDLE_ALLOC_FAILURE( error )
    EUNIT_ASSERT( error == KErrNotReady );

	// Ensure that rtpSink gets correct id
	rtpSink->iFlatData->iID.iAppId = KMceNotAssigned;
	rtpSink->iFlatData->iID.iId = KMceNotAssigned;
    
    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, 1, EFalse );

    rtpSink->SendSRL();
    
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    
    MCE_DELETE_PROFILE;
    
    }

// ----------------------------------------------------------------------------
// CMceRtpSinkTest::UpdateTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::UpdateTestL()
    {
    CMceRtpSink* rtpSink = CMceRtpSink::NewL();
    CleanupStack::PushL( rtpSink );
    rtpSink->UpdateL( ETrue );
    CMceComRtpSink* rtpFlat = static_cast<CMceComRtpSink*>(rtpSink->iFlatData);
    EUNIT_ASSERT( rtpFlat->iSuppressRTCP );
    rtpSink->UpdateL( EFalse );
    EUNIT_ASSERT( !rtpFlat->iSuppressRTCP );
    CleanupStack::PopAndDestroy( rtpSink );    
    }

// ----------------------------------------------------------------------------
// CMceRtpSinkTest::DoITCSendTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::DoITCSendTestL()
    {
    // No stream
	CMceRtpSink* sink = CMceRtpSink::NewLC();
    TRAPD( err, sink->DoITCSendL( EMceItcEnable ) );
    EUNIT_ASSERT_EQUALS( KErrNotReady, err );
    

    // Attach stream to sink. Stream has no session.
    CMceAudioStream* stream = CMceAudioStream::NewLC();
    sink->iStream = stream;
    
    TRAP( err, sink->DoITCSendL( EMceItcEnable ) );
    EUNIT_ASSERT_EQUALS( KErrNotReady, err );


	// Attach session that is idle, to stream.
	MCE_CREATE_PROFILE;
	CMceOutSession* session = CMceOutSession::NewL( *iManager,
													*profile,
													KMceRecipient );
	CleanupStack::PushL( session );
	session->iFlatData->iState = CMceSession::EIdle;
	stream->iSession = session;
	sink->DoITCSendL( EMceItcEnable );

	CleanupStack::PopAndDestroy( session );	
	MCE_DELETE_PROFILE;
	CleanupStack::PopAndDestroy( stream );
    CleanupStack::PopAndDestroy( sink );
    }

// ----------------------------------------------------------------------------
// CMceRtpSinkTest::HandleEventTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::HandleEventTestL()
    {
	CMceRtpSink* sink = CMceRtpSink::NewLC();    

    // Attach stream to sink. Stream has no session.
    CMceAudioStream* stream = CMceAudioStream::NewLC();
    sink->iStream = stream;

	// Attach session that is idle, to stream.
	MCE_CREATE_PROFILE;
	CMceOutSession* session = CMceOutSession::NewL( *iManager,
													*profile,
													KMceRecipient );
	CleanupStack::PushL( session );
	stream->iSession = session;	

	TMceIds ids;
    ids.iCallbackID = EMceItcSRReceived;
	TMceEvent event = TMceEvent( ids, NULL, NULL );

	EUNIT_ASSERT_EQUALS( KMceEventConsumed, sink->HandleEvent( event ) );
	
	ids.iCallbackID = EMceItcLinkCreated;
    EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, sink->HandleEvent( event ) );

	ids.iCallbackID = EMceItcRRReceived;
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, sink->HandleEvent( event ) );

	// Clear the RTP observer
	iManager->iRtpObserver = NULL;
	
	ids.iCallbackID = EMceItcSRReceived;
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, sink->HandleEvent( event ) );
	
	ids.iCallbackID = EMceItcLinkCreated;
    EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, sink->HandleEvent( event ) );

	ids.iCallbackID = EMceItcRRReceived;
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, sink->HandleEvent( event ) );

	CleanupStack::PopAndDestroy( session );
	MCE_DELETE_PROFILE;
	CleanupStack::PopAndDestroy( stream );
    CleanupStack::PopAndDestroy( sink );
    }

// ----------------------------------------------------------------------------
// CMceRtpSinkTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSinkTest::EventReceivedTestL()
	{
	const TMceMediaId mediaId( 2703 );
	CMceRtpSink* sink = CMceRtpSink::NewLC();
	sink->iFlatData->iID = mediaId;

	TMceIds ids;
    ids.iSinkID = mediaId;
    ids.iCallbackID = EMceItcSRReceived;
    TMceEvent event = TMceEvent( ids, NULL, NULL );


    CMceAudioStream* stream = CMceAudioStream::NewLC();
    sink->iStream = stream;
	MCE_CREATE_PROFILE;
	CMceOutSession* session = CMceOutSession::NewL( *iManager,
													*profile,
													KMceRecipient );
	CleanupStack::PushL( session );
	stream->iSession = session;	
	
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, sink->EventReceivedL( event ) );

	// Assign source ID
	ids.iSourceID = 58;
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, sink->EventReceivedL( event ) );

	CleanupStack::PopAndDestroy( session );
	MCE_DELETE_PROFILE;
	CleanupStack::PopAndDestroy( stream );
    CleanupStack::PopAndDestroy( sink );
	}
