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
#include <digia/eunit/EUnitMacros.h>
#include "CMceRtpSourceTest.h"
#include "mcestubs.h"
#include "mceevents.h"
#include "mceserial.h"

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

const TUint32 KInactivityTimer = 5;
const TUint32 KBufferLength = 500;
const TUint32 KBufferTreshold = 123;
_LIT8( KTalkBurstIndicator, "TalkBurstIndicator");
_LIT8( KTestIdentifier, "TestIdentifier");

const TUint8 KMceTestCategory =5;
// ----------------------------------------------------------------------------
// CMceRtpSourceTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceRtpSourceTest::setUpL()
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
// CMceRtpSourceTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::tearDown()
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
// CMceRtpSourceTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceRtpSourceTest::suiteL()
    {
    CMceRtpSourceTest* suite = new CMceRtpSourceTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceRtpSourceTest,
    "CMceRtpSourceTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, SendRRTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, InactivityTimerTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, EnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, DisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, HandleEventTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, EventReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceRtpSourceTest", setUpL, UpdateTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceRtpSourceTest::ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::ConstructionTestL()
    {
  
    CMceRtpSource* rtpSource = CMceRtpSource::NewL();
    CleanupStack::PushL( rtpSource );
    EUNIT_ASSERT( rtpSource->Type() == KMceRTPSource );
    EUNIT_ASSERT( !rtpSource->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSource->IsEnabled() );
    CMceComRtpSource* rtpFlat = 
    		static_cast<CMceComRtpSource*>(rtpSource->iFlatData);
    EUNIT_ASSERT( rtpFlat->iInactivityTimer == 0 ); 
    CleanupStack::PopAndDestroy( rtpSource );
    
    }

// ----------------------------------------------------------------------------
// CMceRtpSourceTest::SendRRTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::SendRRTestL()
    {
    
    MCE_CREATE_PROFILE;
        
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT_EQUALS( KMceRecipient(), iOutSession->Recipient() );

    CMceAudioStream* stream1 = NULL;

    stream1 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream1 );

	//rtp sink
    CMceRtpSource* rtpSource = CMceRtpSource::NewL();
    CleanupStack::PushL( rtpSource );

	rtpSource->iFlatData->iID.iAppId = KMceTestAppId;
	rtpSource->iFlatData->iID.iId = KMceTestMiscId;
    
	TRAPD(err, rtpSource->SendRRL()); // No stream present, must leave
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
	    
    stream1->SetSourceL( rtpSource );
    CleanupStack::Pop( rtpSource );
    rtpSource->InitializeL( *stream1 );

	TRAP(err, rtpSource->SendRRL()); // No session present, must leave
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );

    iOutSession->AddStreamL( stream1 );
    CleanupStack::Pop( stream1 );
    stream1->InitializeL( *iOutSession, EFalse );

    TRAPD( error, rtpSource->SendRRL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( error )
    EUNIT_ASSERT( error == KErrNotReady ); // Session not established, does nothing

	// Ensure that rtpSource gets correct id
	rtpSource->iFlatData->iID.iAppId = KMceNotAssigned;
	rtpSource->iFlatData->iID.iId = KMceNotAssigned;
    
    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, 1, EFalse );

    rtpSource->SendRRL();
    
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    
    MCE_DELETE_PROFILE;
    
    }
	   
// ----------------------------------------------------------------------------
// CMceRtpSourceTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::ExternalizeTestL()
    {
    CMceRtpSource* rtpSource = CMceRtpSource::NewLC();
    CMceComRtpSource* rtpFlat = 
    		static_cast<CMceComRtpSource*>(rtpSource->iFlatData);

    rtpFlat->iID.iAppId = KMceTestAppId;
    rtpFlat->iID.iId = KMceTestMiscId; 
    rtpFlat->iType = KMceTestSourceType;
    rtpFlat->Enabled ( KMceTestEnabledFalse );
	rtpFlat->iInactivityTimer = KInactivityTimer;
	rtpFlat->iBufferLength = KBufferLength;
	rtpFlat->iBufferTreshold = KBufferTreshold;
	rtpFlat->iTalkBurstIndicator = KTalkBurstIndicator().AllocL();
	rtpFlat->iCategory = KMceTestCategory;
	
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    

    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	rtpSource->ExternalizeL( serCtx );
    CleanupStack::PopAndDestroy();//serCtx
	writeStream.Close();
	writeStream.Pop();

	RDesReadStream readStream( buffer );
	readStream.PushL();
	
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestSourceType );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestCategory );
	EUNIT_ASSERT( KMceTestAppId == readStream.ReadUint32L() );
	EUNIT_ASSERT( KMceTestMiscId == readStream.ReadUint32L() );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestEnabledFalse );
	EUNIT_ASSERT( readStream.ReadUint32L() == KInactivityTimer );
	EUNIT_ASSERT( readStream.ReadUint32L() == KBufferLength );
	EUNIT_ASSERT( readStream.ReadUint32L() == KBufferTreshold );
	
	TUint len = readStream.ReadUint32L();
    HBufC8* talkBurstIndicator = HBufC8::NewLC( len );
    TPtr8 ptr = talkBurstIndicator->Des();
    readStream.ReadL( ptr, len );
    
	EUNIT_ASSERT( talkBurstIndicator->Des().Compare( KTalkBurstIndicator ) == 0 );
    CleanupStack::PopAndDestroy( talkBurstIndicator );
    
	readStream.Close();
	readStream.Pop();   	
	
	
	
	CleanupStack::PopAndDestroy( rtpSource );     
    }

// ----------------------------------------------------------------------------
// CMceRtpSourceTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::InternalizeTestL()
    {
    CMceRtpSource* rtpSource = CMceRtpSource::NewLC();
    CMceComRtpSource* rtpFlat = 
    		static_cast<CMceComRtpSource*>(rtpSource->iFlatData);

    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();
    
    writeStream.WriteUint8L( KMceTestSourceType );
    writeStream.WriteUint8L ( KMceTestCategory );
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( KMceTestEnabledFalse );
    writeStream.WriteUint32L( KInactivityTimer );
    writeStream.WriteUint32L( KBufferLength );
    writeStream.WriteUint32L( KBufferTreshold );
    writeStream.WriteUint32L( KTalkBurstIndicator().Length() );
    writeStream.WriteL( KTalkBurstIndicator() );
    writeStream.WriteUint32L( KTestIdentifier().Length() );
    writeStream.WriteL( KTestIdentifier() );
    
	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    rtpSource->InternalizeL( serCtx );
    
    EUNIT_ASSERT( rtpFlat->iType == KMceTestSourceType );
    EUNIT_ASSERT( rtpFlat->IsEnabled() == KMceTestEnabledFalse );
    EUNIT_ASSERT( rtpFlat->Id().iAppId == KMceTestAppId );
    EUNIT_ASSERT( rtpFlat->Id().iId == KMceTestMiscId );
    EUNIT_ASSERT( rtpFlat->iInactivityTimer == KInactivityTimer );
    EUNIT_ASSERT( rtpFlat->iBufferLength == KBufferLength );
    EUNIT_ASSERT( rtpFlat->iBufferTreshold == KBufferTreshold );
    EUNIT_ASSERT( rtpFlat->iTalkBurstIndicator->Des().Compare( KTalkBurstIndicator ) == 0 );
    EUNIT_ASSERT( rtpFlat->iIdentity->Des().Compare( KTestIdentifier ) == 0 );
    
    CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();

	CleanupStack::PopAndDestroy( rtpSource );
    }


// ----------------------------------------------------------------------------
// CMceRtpSourceTest::InactivityTimerTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::InactivityTimerTestL()
    {
    MCE_CREATE_PROFILE;
    CMceRtpSource* rtpSource = CMceRtpSource::NewL();
    CleanupStack::PushL( rtpSource );    
    
    rtpSource->iFlatData->iID.iAppId = KMceTestAppId;
	rtpSource->iFlatData->iID.iId = KMceTestMiscId;
    
    // stream not set
    CMceComRtpSource* rtpFlat = 
    		static_cast<CMceComRtpSource*>(rtpSource->iFlatData);
	EUNIT_ASSERT( rtpFlat->iInactivityTimer == 0 );
	
	// enable
	TRAPD( err, rtpSource->EnableInactivityTimerL( KInactivityTimer ) );
	EUNIT_ASSERT_EQUALS( err, KErrNotReady );

    // disable
	rtpSource->DisableInactivityTimerL();
	EUNIT_ASSERT( rtpFlat->iInactivityTimer == 0 );	
    
    // Set session and stream
    
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT_EQUALS( KMceRecipient(), iOutSession->Recipient() );

    CMceAudioStream* stream1 = NULL;

    stream1 = CMceAudioStream::NewL();
    CleanupStack::PushL( stream1 );  
    stream1->SetSourceL( rtpSource );
    CleanupStack::Pop( stream1 );
    CleanupStack::Pop( rtpSource );
    CleanupStack::PushL( stream1 );  
    rtpSource->InitializeL( *stream1 );

    iOutSession->AddStreamL( stream1 );
    CleanupStack::Pop( stream1 );
    stream1->InitializeL( *iOutSession, EFalse );
    
    // Ensure that rtpSource gets correct id
	rtpSource->iFlatData->iID.iAppId = KMceNotAssigned;
	rtpSource->iFlatData->iID.iId = KMceNotAssigned;
    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, 1, EFalse );

    // enable
    rtpSource->EnableInactivityTimerL( KInactivityTimer );
	
    // disable
	rtpSource->DisableInactivityTimerL();
	EUNIT_ASSERT( rtpFlat->iInactivityTimer == 0 );	
    
    MCE_DELETE_PROFILE;
	}


// ----------------------------------------------------------------------------
// CMceRtpSourceTest::EnableTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::EnableTestL()
    {
    // As long as function CMceRtpSource::Enable() does nothing
    // but calls base class DoEnable()-function, there is no need to
    // do more than just run the function once to keep coverage tool happy.
    
    CMceRtpSource* rtpSource = CMceRtpSource::NewLC();
    rtpSource->EnableL();
    CleanupStack::PopAndDestroy( rtpSource );   
    }


// ----------------------------------------------------------------------------
// CMceRtpSourceTest::DisableTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::DisableTestL()
    {
    // As long as function CMceRtpSource::Disable() does nothing
    // but calls base class DoDisable()-function, there is no need to
    // do more than just run the function once to keep coverage tool happy.
    
    CMceRtpSource* rtpSource = CMceRtpSource::NewLC();
    rtpSource->DisableL();
    CleanupStack::PopAndDestroy( rtpSource );         
    }

// ----------------------------------------------------------------------------
// CMceRtpSourceTest::HandleEventTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::HandleEventTestL()
    {
    
	MCE_CREATE_PROFILE;

    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    
    CMceAudioStream* stream = CMceAudioStream::NewL();
    CleanupStack::PushL( stream );
    
    CMceRtpSource* rtpSource = CMceRtpSource::NewL();
    CleanupStack::PushL( rtpSource );    

    stream->SetSourceL( rtpSource );
    CleanupStack::Pop( rtpSource );

    iOutSession->AddStreamL( stream );
    CleanupStack::Pop( stream );

	stream->InitializeL( *iOutSession, EFalse );

    // Actual testcase begins
	
	TMceIds ids;
	TMceEvent event( ids, NULL, NULL ); 
	
	// default 
	
	ids.iCallbackID = KMceNotAssigned;	
	TInt status = rtpSource->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );	
	
	// SR received, observer not present

	ids.iCallbackID = EMceItcSRReceived;	
	iManager->iRtpObserver = NULL;
	status = rtpSource->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, status );
	EUNIT_ASSERT_EQUALS( 0, iRtpObserver->iReceived );
	EUNIT_ASSERT( !iRtpObserver->iStream );
	EUNIT_ASSERT( !iRtpObserver->iSource );	

	// SR received, observer present
	iManager->SetRtpObserver( iRtpObserver );	
	status = rtpSource->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, status );
	EUNIT_ASSERT_EQUALS( 1, iRtpObserver->iReceived );
	EUNIT_ASSERT( iRtpObserver->iStream == stream );

	// RR Received, observer not present
	iRtpObserver->iReceived = 0;
	iRtpObserver->iStream = NULL;
	ids.iCallbackID = EMceItcRRReceived;
	iManager->iRtpObserver = NULL;
	status = rtpSource->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, status );
	EUNIT_ASSERT_EQUALS( 0, iRtpObserver->iReceived );
	EUNIT_ASSERT( !iRtpObserver->iStream );

	// RR received, observer present
	iManager->SetRtpObserver( iRtpObserver );	
	status = rtpSource->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, status );
	EUNIT_ASSERT_EQUALS( 2, iRtpObserver->iReceived );
	EUNIT_ASSERT( iRtpObserver->iStream == stream );

	// InactivityTimeout, observer not present
	iRtpObserver->iReceived = 0;
	iRtpObserver->iStream = NULL;
	ids.iCallbackID = EMceItcInactivityTimeout;
	iManager->iRtpObserver = NULL;
	status = rtpSource->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, status );
	EUNIT_ASSERT_EQUALS( 0, iRtpObserver->iReceived );
	EUNIT_ASSERT( !iRtpObserver->iStream );
	EUNIT_ASSERT( !iRtpObserver->iSource );

	// InactivityTimeout, observer present
	iManager->SetRtpObserver( iRtpObserver );	
	status = rtpSource->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, status );
	EUNIT_ASSERT_EQUALS( 3, iRtpObserver->iReceived );
	EUNIT_ASSERT( iRtpObserver->iStream == stream );
	EUNIT_ASSERT( iRtpObserver->iSource == rtpSource );	


	MCE_DELETE_PROFILE;
	    
    }

// ----------------------------------------------------------------------------
// CMceRtpSourceTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::EventReceivedTestL()
    {

	MCE_CREATE_PROFILE;

	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    
    CMceAudioStream* stream = CMceAudioStream::NewL();
    CleanupStack::PushL( stream );
    
    CMceRtpSource* rtpSource = CMceRtpSource::NewL();
    CleanupStack::PushL( rtpSource );    

    stream->SetSourceL( rtpSource );
    CleanupStack::Pop( rtpSource );

    iOutSession->AddStreamL( stream );
    CleanupStack::Pop( stream );

	stream->InitializeL( *iOutSession, EFalse );

    // Actual testcase begins
    
    TMceMediaId rtpId = rtpSource->Id();
    
	TMceMediaId id;
	id.iAppId = KMceTestAppId;
	id.iId = KMceTestMiscId;

	// Id's don't match	
	TMceIds ids;
	ids.iSourceID = id;
	TMceEvent event( ids, NULL, NULL ); 

	TInt status = rtpSource->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotOwner, status );
	
	// Id's match, but Event.Id is not a SourceId
	ids.iSinkID = rtpId;
	ids.iSourceID = rtpId;
	
	status = rtpSource->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );

	// Id's match, Event.Id is a SourceId, 
	// but base class does not know the desired function
	ids.iSinkID = KMceMediaIdNotAssigned;	
	ids.iCallbackID = EMceItcSRReceived;

	status = rtpSource->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, status );
		
	MCE_DELETE_PROFILE; 
    }

// ----------------------------------------------------------------------------
// CMceRtpSourceTest::UpdateTestL
// ----------------------------------------------------------------------------
//
void CMceRtpSourceTest::UpdateTestL()
    {
    CMceRtpSource* rtpSource = CMceRtpSource::NewL();
    CleanupStack::PushL( rtpSource );
    for ( TInt i = 0; i < KLoops; i++ )
        {
        HBufC8* identity = KTestIdentifier().AllocLC();
        rtpSource->UpdateL( i, i, i, identity );
        CleanupStack::PopAndDestroy( identity );
        }
    CleanupStack::PopAndDestroy( rtpSource );
    }
