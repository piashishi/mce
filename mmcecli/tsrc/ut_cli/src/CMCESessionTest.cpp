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
#include <sipstrconsts.h>
#include <digia/eunit/EUnitMacros.h>
#include "CMceSessionTest.h"
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
#include "mcecomamrcodec.h"
#include "mcetransactiondatacontainer.h"
#include "mceserial.h"
#include "mceitcsender.h"
#include "mceevents.h"

// ----------------------------------------------------------------------------
// CMceSessionTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceSessionTest::setUpL()
    {
    
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManagerObserver = new (ELeave) CMceManagerObserverStub();
    iSessionObserver = new (ELeave) CMceSessionObserverStub();
    iStreamObserver = new (ELeave) CMceStreamObserverStub();
    iRtpObserver = new (ELeave) CMceRtpObserverStub();
    iFCObserver = new (ELeave) CMceFcMsgObserverStub();
    
    iTransactionObserver = new (ELeave) CMceTransactionObserverStub();
    iInTransactionObserver = new (ELeave) CMceInTransactionObserverStub();
    
    iManager = CMceManager::NewL( iUid, &iContainer );
    iManager->SetInSessionObserver( iManagerObserver );
    iManager->SetSessionObserver( iSessionObserver );
    iManager->SetMediaObserver( iStreamObserver );
    iManager->SetRtpObserver( iRtpObserver );
    
    iManager->SetTransactionObserver( iTransactionObserver );
    iManager->SetInTransactionObserver( iInTransactionObserver );
    
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceSessionTest::tearDown()
    {

    if ( iInSession )
        {
        MCE_TEST_DELETE( iInSession );
        }
    
    if ( iOutSession )
        {
        MCE_TEST_DELETE( iOutSession );        
        }

    MCE_MAN_DELETE( iManager );        

    delete iManagerObserver;
    iManagerObserver = NULL;
    delete iSessionObserver;
    iSessionObserver = NULL;
    delete iStreamObserver;
    iStreamObserver = NULL;
    delete iRtpObserver;
    iRtpObserver = NULL;
    delete iFCObserver;
    iFCObserver = NULL;
    delete iTransactionObserver;
    iTransactionObserver = NULL;
    delete iInTransactionObserver;
    iInTransactionObserver = NULL;
    
    delete iStorage;
    iStorage = NULL;
    Dll::SetTls( NULL );

    }

// ----------------------------------------------------------------------------
// CMceSessionTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceSessionTest::suiteL()
    {
    CMceSessionTest* suite = new CMceSessionTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceSessionTest,
    "CMceSessionTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, UpdateTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, TerminateTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, TerminateTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, TerminateTest3L, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, ErrorOccuredTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, ReceiverErrorOccuredTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, UpdatedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, FCMessageReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, ReceiverTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, IncomingUpdateTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, IncomingUpdateTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, IncomingUpdateTest3L, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, IncomingUpdateTest4L, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, ZombieTestsL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, FactoryTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, SetContainerTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, FCErrorOccurredTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, HandleEventTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, HandleEventResponseReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, HandleEventRequestReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, SetSessionSDPLinesTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, SessionSDPLinesTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, SessionServiceTypeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, ControlPathSecurityLevelTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, AddStreamTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, AddStreamPrecondTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, AddStreamPullModeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, AddStreamPullModeTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, GetModifierTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, SetModifierTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, AssociatedEventsTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, AssociatedRefersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, RemoveStreamTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, SIPParamsCleanupTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, AddBundleTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, TypeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, SerializationIdTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, ExternalizeInternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, ITCSenderTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, ITCManagerTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, ConnectionActiveTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, InitializeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, InitializeWithBundleTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, EventReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, SendRequestTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSessionTest", setUpL, SendResponseTestL, tearDown )
EUNIT_END_TEST_TABLE 
	
// ----------------------------------------------------------------------------
// CMceSessionTest::UpdateTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::UpdateTestL()
    {
    CMceComSession* inSession = NULL;
    CMceMsgObject<CMceComSession>* msg = NULL;
    CMceAudioStream* outAudio = NULL;
    CMceAudioStream* inAudio = NULL;	
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    
    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    
    outAudio = static_cast<CMceAudioStream*>( iInSession->Streams()[0] );
    EUNIT_ASSERT( outAudio->Id().IsAssigned() );
    inAudio = static_cast<CMceAudioStream*>( &(outAudio->BoundStreamL()) );
    EUNIT_ASSERT( inAudio->Id().IsAssigned() );
    
    CMceMicSource* mic = CMceMicSource::NewL();
    EUNIT_ASSERT( !mic->Id().IsAssigned() );
    CleanupStack::PushL( mic );
    outAudio->SetSourceL(  mic );
    EUNIT_ASSERT( !mic->Id().IsAssigned() );
    CleanupStack::Pop( mic );
    
    CMceSpeakerSink* speaker = CMceSpeakerSink::NewL();
    EUNIT_ASSERT( !speaker->Id().IsAssigned() );
    CleanupStack::PushL( speaker );
    inAudio->AddSinkL( speaker );
    EUNIT_ASSERT( !speaker->Id().IsAssigned() );
    CleanupStack::Pop( speaker );

    //leaving cases
    HBufC8* ct = KMceContentType().AllocLC();
    HBufC8* c = KMceMessageBody().AllocLC();
    CDesC8Array* ch = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( ch );
    // content type && no content
    TRAPD( err1, iInSession->UpdateL( 0, NULL, ct, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    TRAPD( err2, iInSession->UpdateL( 0, NULL, NULL, c ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    // no content type &&  no content && content headers
    TRAPD( err3, iInSession->UpdateL( 0, NULL, NULL, NULL, ch ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )
    EUNIT_ASSERT_EQUALS( err3, KErrArgument );
    
    CleanupStack::PopAndDestroy( ch );
    
    // bigger timeout than given
    TRAPD( err6, iInSession->UpdateL( iInSession->SessionTimer()+1 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err6 )
    EUNIT_ASSERT_EQUALS( err6, KErrArgument );
    EUNIT_ASSERT( iInSession->SessionTimer() == KMceTestTimeout );
    
    //update
    iInSession->UpdateL( 0, NULL, ct, c );
    CleanupStack::Pop( c );
    CleanupStack::Pop( ct );
    
    EUNIT_ASSERT( iInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( mic->Id().IsAssigned() );
    EUNIT_ASSERT( speaker->Id().IsAssigned() );
    EUNIT_ASSERT( iInSession->SessionTimer() == KMceTestTimeout );
    
    msg = new (ELeave) CMceMsgObject<CMceComSession>();
    CleanupStack::PushL( msg );
    msg->DecodeL( *(iStorage->iContext) );
    msg->PushL();
    
    inSession = msg->iObject;
    
    EUNIT_ASSERT( inSession->iType == CMceComSession::EInSession );
    EUNIT_ASSERT( inSession->iState == CMceSession::EIncoming );
    EUNIT_ASSERT( inSession->iID == KMceTestSessionId1 );
    EUNIT_ASSERT( inSession->Streams().Count() == 1 );
    
    EUNIT_ASSERT( static_cast<CMceComAudioStream*>( inSession->Streams()[0] )->Source() != NULL );
    EUNIT_ASSERT( static_cast<CMceComAudioStream*>( inSession->Streams()[0] )->Sinks().Count() == 1 );
    EUNIT_ASSERT( static_cast<CMceComAudioStream*>( inSession->Streams()[0] )->BoundStreamL().Source() != NULL );
    EUNIT_ASSERT( static_cast<CMceComAudioStream*>( inSession->Streams()[0] )->BoundStreamL().Sinks().Count() == 1 );
    
    TBuf8<KMceMaxSdpNameLength> codecStr;
    codecStr.Append(_L8("AMR"));    
    
    CMceComAMRCodec* codec = CMceComAMRCodec::NewLC( codecStr );

    static_cast<CMceComAudioStream*>( inSession->Streams()[0] )->AddCodecL( codec );
    CleanupStack::Pop();
    
    msg->EncodeL();
        
    iStorage->Reset();
    iInSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iInSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
            
    iStorage->iContext = msg->EncodeBuffer().Ptr(0).AllocL();
    iInSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();

    //updated
    outAudio = static_cast<CMceAudioStream*>( iInSession->Streams()[0] );
    inAudio = static_cast<CMceAudioStream*>( &(outAudio->BoundStreamL() ) );
    
    CleanupStack::PopAndDestroy( msg );

    iStorage->Reset();
    iInSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iInSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;

    CMceSpeakerSink* speaker2 = CMceSpeakerSink::NewL();
    EUNIT_ASSERT( !speaker2->Id().IsAssigned() );
    CleanupStack::PushL( speaker2 );
    TRAPD( err7, inAudio->AddSinkL( speaker2 ) );
    EUNIT_ASSERT_EQUALS( err7, KErrNotSupported );
    EUNIT_ASSERT( !speaker2->Id().IsAssigned() );
    CleanupStack::PopAndDestroy( speaker2 );

    //update
    TUint timer = iInSession->SessionTimer()-1;
    iInSession->UpdateL( timer );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( speaker->Id().IsAssigned() );
    EUNIT_ASSERT( iInSession->SessionTimer() == timer );
    
    iStorage->Reset();
    iInSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iInSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;

    //updated
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EEstablished );

    TUint timer2 = KMceTestMinSE - 1;
    iInSession->UpdateL( timer2 );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iInSession->SessionTimer() == KMceTestMinSE );
    
    iStorage->Reset();
    iInSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iInSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;

    //updated
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EEstablished );

    // Update fails
    iStorage->iStatus = KErrGeneral;
    iInSession->UpdateL();
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStatusCode, KErrGeneral );
    iSessionObserver->Clear();
    
    // Update fails, no observer
    iManager->SetSessionObserver( NULL );
    iStorage->iStatus = KErrTotalLossOfPrecision;
    iInSession->UpdateL();
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStatusCode, 0 );
    iSessionObserver->Clear();
    
    iManager->SetSessionObserver( iSessionObserver );
    
    // Update fails, container
    iManager->iContainer = NULL;
    iStorage->iStatus = KErrTotalLossOfPrecision;
    iInSession->UpdateL();
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStatusCode, 0 );
    iSessionObserver->Clear();
    iManager->iContainer = &iContainer;
    //
    
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );

	// Try to update Idle session... and fail
	MCE_CREATE_PROFILE;
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
	TRAPD( err, iOutSession->UpdateL() );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
    MCE_DELETE_PROFILE;

    }
    

// ----------------------------------------------------------------------------
// CMceSessionTest::TerminateTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::TerminateTestL()
    {
    
    MCE_CREATE_PROFILE;
   
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

	TRAPD( err, iOutSession->TerminateL() );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
        
    iOutSession->TerminateL();
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminating );

    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    EUNIT_ASSERT( iSessionObserver->iStateChangedCount == 3 );

  
    
    MCE_DELETE_PROFILE;
    
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::TerminateTest2L
// ----------------------------------------------------------------------------
//
void CMceSessionTest::TerminateTest2L()
    {
    // with headers.
    MCE_CREATE_PROFILE;
   
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
    
    // headers
    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    
    // terminate    
    iOutSession->TerminateL( headers, NULL, NULL );
    CleanupStack::Pop( headers );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminating );

    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    EUNIT_ASSERT( iSessionObserver->iStateChangedCount == 3 );

  
    
    MCE_DELETE_PROFILE;
    
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::TerminateTest3L
// ----------------------------------------------------------------------------
//
void CMceSessionTest::TerminateTest3L()
    {
    
    MCE_CREATE_PROFILE;
   
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    
    HBufC8* content = _L8("CONTENT").AllocLC();
	HBufC8* contentType = _L8("CONTENT_TYPE").AllocLC();
	
	// Leaving cases
	// wrong state
	TRAPD( err3, iOutSession->TerminateL( NULL, contentType, content ) );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err3 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
    
	// content type, no content
	TRAPD( err, iOutSession->TerminateL( NULL, contentType, NULL ) );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	// no content type, content
	TRAPD( err2, iOutSession->TerminateL( NULL, NULL, content ) );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
	EUNIT_ASSERT_EQUALS( KErrArgument, err2 );
	
    iOutSession->TerminateL( NULL, contentType, content );
    CleanupStack::Pop( contentType );
    CleanupStack::Pop( content );
    
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminating );

    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    EUNIT_ASSERT( iSessionObserver->iStateChangedCount == 3 );

    MCE_DELETE_PROFILE;
    }
    
// ----------------------------------------------------------------------------
// CMceSessionTest::ErrorOccuredTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::ErrorOccuredTestL()
    {

	MCE_CREATE_PROFILE;

    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
    
    //Completed with error
    MCE_SES_RECEIVE( iOutSession, KErrGeneral );
    
    //call directly with no observer
    iManager->SetSessionObserver( NULL );
    TRAPD( err, iOutSession->ErrorOccuredL( KErrTotalLossOfPrecision ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrArgument );
    iManager->SetSessionObserver( iSessionObserver );
    
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    
    MCE_DELETE_PROFILE;
    }
    

// ----------------------------------------------------------------------------
// CMceSessionTest::ReceiverErrorOccuredTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::ReceiverErrorOccuredTestL()
	{
	MCE_CREATE_PROFILE;

	TInt errorCode = KErrTimedOut;
	TUint transactionID = 5000;

	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    CMceSessionReceiver* receiver = iOutSession->iReceiver;
    TMceIds ids;
    ids.iTransactionID = transactionID;
    
    //Test 1: Error for Extension Request Received:
    receiver->ErrorOccuredL( ids, errorCode);

	EUNIT_ASSERT( iTransactionObserver->iSession == iOutSession );
	EUNIT_ASSERT( iTransactionObserver->iTransactionID == transactionID );
	EUNIT_ASSERT( iTransactionObserver->iError == KErrTimedOut );
    
    //Test 2: Error for Non Extension related request.
    ids.iTransactionID = KMceNotAssigned;
    receiver->ErrorOccuredL( ids, errorCode );
	EUNIT_ASSERT( iSessionObserver->iError == KErrTimedOut );
	EUNIT_ASSERT( iSessionObserver->iSession == iOutSession );

    MCE_DELETE_PROFILE;
	}
    

// ----------------------------------------------------------------------------
// CMceSessionTest::UpdatedTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::UpdatedTestL()
    {
    
	MCE_CREATE_PROFILE;

    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
    
    // change state without observer
    iManager->SetSessionObserver( NULL );
    
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    
    iManager->SetSessionObserver( iSessionObserver );
    
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::FCMessageReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::FCMessageReceivedTestL()
    {
    
    MCE_CREATE_PROFILE;
    
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
    
    
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
            
    iStorage->iContext = KMceFCMessage().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    MCE_SESSION_RECEIVE( iOutSession, EMceItcFCMsgReceived, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iFCObserver->iSession == NULL );

    iOutSession->SetFCObserver( iFCObserver );
    
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
            
    iStorage->iContext = KMceFCMessage().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    MCE_SESSION_RECEIVE( iOutSession, EMceItcFCMsgReceived, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iFCObserver->iSession == iOutSession );
    EUNIT_ASSERT( iFCObserver->iMessage->Compare( KMceFCMessage ) == 0 );

    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;

    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    
    MCE_DELETE_PROFILE;
    
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::ReceiverTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::ReceiverTestL()
    {
    // Tests for the leaving cases
    MCE_CREATE_PROFILE;
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    CMceSessionReceiver* receiver = iOutSession->iReceiver;
    TMceIds ids;
    HBufC8* context = KMceTestFailContext().AllocLC();
    HBufC8* content = NULL;
 
    TRAPD( err1, receiver->IncomingEventL( EMceItcUpdateFailed, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
    EUNIT_ASSERT_EQUALS( err1, KErrGeneral );
    
    TRAPD( err2, receiver->IncomingEventL( EMceItcSRReceived, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err2, KErrNotSupported );
    
    TRAPD( err3, receiver->IncomingEventL( EMceItcRRReceived, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )
    EUNIT_ASSERT_EQUALS( err3, KErrNotSupported );
    
    TRAPD( err4, receiver->IncomingEventL( EMceItcInactivityTimeout, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 )
    EUNIT_ASSERT_EQUALS( err4, KErrNotSupported );
    
    TRAPD( err5, receiver->IncomingEventL( EMceItcSessionConnectionStateChanged, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err5 )
    EUNIT_ASSERT_EQUALS( err5, KErrNotSupported );
    
    TRAPD( err6, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err6 )
    EUNIT_ASSERT_EQUALS( err6, KErrNotSupported );
    
    TRAPD( err7, receiver->IncomingEventL( EMceItcUpdateFailed, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err7 )
    EUNIT_ASSERT_EQUALS( err7, KErrGeneral );
    
    TRAPD( err8, receiver->IncomingEventL( EMceItcSRReceived, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err8 )
    EUNIT_ASSERT_EQUALS( err8, KErrNotSupported );
    
    TRAPD( err9, receiver->IncomingEventL( EMceItcRRReceived, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err9 )
    EUNIT_ASSERT_EQUALS( err9, KErrNotSupported );
    
    TRAPD( err10, receiver->IncomingEventL( EMceItcInactivityTimeout, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err10 )
    EUNIT_ASSERT_EQUALS( err10, KErrNotSupported );

    TRAPD( err10a, receiver->IncomingEventL( EMceItcResponseReceived, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err10a )
    EUNIT_ASSERT_EQUALS( err10a, KErrGeneral );
    
    TRAPD( err10b, receiver->IncomingEventL( EMceItcRequestReceived, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err10b )
    EUNIT_ASSERT_EQUALS( err10b, KErrGeneral );
    TRAPD( err11, receiver->IncomingEventL( EMceItcSessionConnectionStateChanged, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err11 )
    EUNIT_ASSERT_EQUALS( err11, KErrNotSupported );
    
    TRAPD( err12, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err12 )
    EUNIT_ASSERT_EQUALS( err12, KErrNotSupported );
    CleanupStack::PopAndDestroy( context );
    
    // cover wrong session ID
    TRAPD( err13, receiver->IncomingEventL( EMceItcStateChanged, ids ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err13 )
    EUNIT_ASSERT_EQUALS( err13, KErrGeneral );
    
    // cover DoCancel
    MCE_SES_RECEIVE( iOutSession, KErrCompletion );
    
    // cover RunError with KErrServerTerminated
    receiver->ReceiveNext();
    TRAPD( err14, MCE_SES_RECEIVE( iOutSession, KErrServerTerminated ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err14 )
    EUNIT_ASSERT_EQUALS( err14, KErrServerTerminated );
    
    MCE_DELETE( iOutSession );
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::IncomingUpdateTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::IncomingUpdateTestL()
    {
    MCE_CREATE_PROFILE;
   
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );

    MCE_INCOMING_UPDATE2( iOutSession );
    
    EUNIT_ASSERT( iOutSession->IsZombie() );
    EUNIT_ASSERT( iManagerObserver->iSession != NULL );
    EUNIT_ASSERT( !iManagerObserver->iSession->IsZombie() );
    delete iOutSession;
    iOutSession = NULL;
    iInSession = static_cast< CMceInSession* >( iManagerObserver->iSession );
    iManagerObserver->iSession = NULL;
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    
    iInSession->UpdateL();
    iStorage->Reset();
    iInSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iInSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
 
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EEstablished );

    MCE_SESSION_STATECHANGE( iInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );
    MCE_DELETE_PROFILE;    
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::IncomingUpdateTest2L
// ----------------------------------------------------------------------------
//
void CMceSessionTest::IncomingUpdateTest2L()
    {
    MCE_CREATE_PROFILE;
   
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );

    HBufC8* ct= KMceContentType().AllocLC();
    CDesC8Array* hdrs =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs );
    hdrs->AppendL( KMceHeader1 );
    hdrs->AppendL( KMceHeader2 );
    HBufC8* c = KMceMessageBody().AllocLC();
    CDesC8Array* cHdrs =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( cHdrs );
    cHdrs->AppendL( KMceHeader1 );
    
    // The macro uses cleanupstack internally for the params
    CleanupStack::Pop( cHdrs );
    CleanupStack::Pop( c );
    CleanupStack::Pop( hdrs );
    CleanupStack::Pop( ct );
    MCE_INCOMING_UPDATE( iOutSession, hdrs, ct, c, cHdrs );
      
    EUNIT_ASSERT( iOutSession->IsZombie() );
    EUNIT_ASSERT( iManagerObserver->iSession != NULL );
    EUNIT_ASSERT( !iManagerObserver->iSession->IsZombie() );
    delete iOutSession;
    iOutSession = NULL;
    iInSession = static_cast< CMceInSession* >( iManagerObserver->iSession );
    iManagerObserver->iSession = NULL;
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );

    iInSession->UpdateL();
    iStorage->Reset();
    iInSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iInSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EEstablished );


    MCE_SESSION_STATECHANGE( iInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );
    MCE_DELETE_PROFILE;    
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::IncomingUpdateTest3L
// ----------------------------------------------------------------------------
//
void CMceSessionTest::IncomingUpdateTest3L()
    {
    // No observer, the update is rejected
    MCE_CREATE_PROFILE;
   
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EEstablished );
    // clear insession observer
    iManager->SetInSessionObserver( NULL );
    MCE_INCOMING_UPDATE2( iOutSession );
    
    EUNIT_ASSERT( !iOutSession->IsZombie() );
    EUNIT_ASSERT( iManagerObserver->iSession == NULL );
   
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
 
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    MCE_DELETE_PROFILE;    
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::IncomingUpdateTest4L
// ----------------------------------------------------------------------------
//
void CMceSessionTest::IncomingUpdateTest4L()
    {
    // Call method directly, cover all branches
    MCE_CREATE_PROFILE;
   
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );

    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 2 );

    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[1] );

    //allready exists
    TRAPD( error, iOutSession->IncomingUpdateL( iInSession, NULL ) );
    EUNIT_ASSERT( error != KErrNone );
    EUNIT_ASSERT( iManager->Sessions().Count() == 2 );
    EUNIT_ASSERT( !iOutSession->IsZombie() );
    
    delete iInSession;
    iInSession = NULL;
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    
    iInSession = CMceInSession::NewL();
    
    // clear container
    iManager->iContainer->Clear();
    iManager->iContainer = NULL;
    
    iOutSession->IncomingUpdateL( iInSession, NULL );
    
    EUNIT_ASSERT( iOutSession->IsZombie() );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    
    delete iOutSession;
    iOutSession = NULL;
    EUNIT_ASSERT( !iInSession->IsZombie() );
    iManager->iContainer = &iContainer;

    delete iInSession;
    iInSession = NULL;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    
    MCE_DELETE_PROFILE;    
    }
    
// ----------------------------------------------------------------------------
// CMceSessionTest::ZombieTestsL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::ZombieTestsL()
    {
    // Zombie tests for session and out session
    MCE_CREATE_PROFILE;
   
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );

    MCE_INCOMING_UPDATE2( iOutSession );
    
    EUNIT_ASSERT( iOutSession->IsZombie() );
    
    // Actual tests
    // UpdateL
    TRAPD( err1, iOutSession->UpdateL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    // TerminateL
    TRAPD( err2, iOutSession->TerminateL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    // SendITCEventL
    TRAPD( err3, iOutSession->SendITCEventL( EMceItcTerminateSession ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )
    EUNIT_ASSERT_EQUALS( err3, KErrGeneral );
    
    // CancelL
    TRAPD( err4, iOutSession->CancelL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 )
    EUNIT_ASSERT_EQUALS( err4, KErrArgument );
    
    EUNIT_ASSERT( iManagerObserver->iSession != NULL );
    EUNIT_ASSERT( !iManagerObserver->iSession->IsZombie() );
    delete iOutSession;
    iOutSession = NULL;
    iInSession = static_cast< CMceInSession* >( iManagerObserver->iSession );
    iManagerObserver->iSession = NULL;
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    
    iInSession->UpdateL();
    iStorage->Reset();
    iInSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iInSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
 
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EEstablished );

    MCE_SESSION_STATECHANGE( iInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );
    MCE_DELETE_PROFILE;    
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::FactoryTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::FactoryTestL()
    {
    MCE_CREATE_PROFILE;
  
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
  
    TMceFactory fac = iOutSession->Factory();
    
    // CMceSession* TMceFactory::CreateLC
    // in session
    CMceSession* inSession = fac.CreateLC( CMceComSession::EInSession );
    EUNIT_ASSERT( inSession != NULL );
    CleanupStack::PopAndDestroy( inSession );
    // out session
    CMceSession* outSession = fac.CreateLC( CMceComSession::EOutSession );
    EUNIT_ASSERT( outSession != NULL );
    CleanupStack::PopAndDestroy( outSession );
    
    // default
    CMceSession* otherSession = NULL;
    TRAPD( err, otherSession = fac.CreateLC( ( CMceComSession::TType )( KErrNotFound ) ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotSupported );
    EUNIT_ASSERT( otherSession == NULL );
    
    MCE_DELETE_PROFILE;
    }

void CMceSessionTest::SetContainerTestL()
    {
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
  
    // test with NULL;
    CMceMsgBase* nullMsg = NULL;  
    HBufC8* nullContent = NULL;
    
    iOutSession->SetContainer( *static_cast<CMceMsgSIPReply*>( nullMsg ), nullContent );
    iOutSession->SetContainer( *static_cast<CMceMsgSIPData*>( nullMsg ), nullContent );
    iOutSession->SetContainer( *static_cast<CMceMsgArray<TMceFactory>*>( nullMsg ), nullContent );
    
    // real test cases
    TMceFactory factory;
    
    // reply
    CMceMsgArray< TMceFactory >* msgArray = 
        new (ELeave) CMceMsgArray< TMceFactory >( factory );
    CleanupStack::PushL( msgArray ); 
    msgArray->PushL();
    
    TUint32 code = 444;
    HBufC8* content = KMceMessageBody().AllocLC();
   
    HBufC8* reason = KMceReason().AllocLC();
    CDesC8Array* hdrs = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs );
    HBufC8* ct = KMceContentType().AllocLC();
    
    CMceMsgSIPReply* replyMsg = new( ELeave ) CMceMsgSIPReply( *reason, code, *hdrs, *ct );
    CleanupStack::PushL( replyMsg );    
    msgArray->iArray.AppendL( replyMsg );
    iOutSession->SetContainer( *msgArray, content );
    
    EUNIT_ASSERT_EQUALS( iContainer.iStatusCode, code );
    EUNIT_ASSERT( iContainer.iContent == content );
    EUNIT_ASSERT( iContainer.iContentType == ct );
    EUNIT_ASSERT( iContainer.iHeaders == hdrs );
    iContainer.Clear();
    CleanupStack::Pop( replyMsg );
    CleanupStack::Pop( ct );
    CleanupStack::Pop( hdrs );
    CleanupStack::Pop( reason );
    CleanupStack::Pop( content );
    CleanupStack::PopAndDestroy( msgArray );
   
    // data
    CMceMsgArray< TMceFactory >* msgArray2 = 
        new (ELeave) CMceMsgArray< TMceFactory >( factory );
    CleanupStack::PushL( msgArray2 ); 
    msgArray2->PushL();
    
    HBufC8* content2 = KMceMessageBody().AllocLC();
   
    CDesC8Array* hdrs2 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs2 );
    HBufC8* ct2 = KMceContentType().AllocLC();
    
    CMceMsgSIPData* dataMsg = new( ELeave ) CMceMsgSIPData( SipStrConsts::EBye, *hdrs2, *ct2 );
    CleanupStack::PushL( dataMsg );
    msgArray2->iArray.AppendL( dataMsg );
    iOutSession->SetContainer( *msgArray2, content2 );
    
    EUNIT_ASSERT( iContainer.iContent == content2 );
    EUNIT_ASSERT( iContainer.iContentType == ct2 );
    EUNIT_ASSERT( iContainer.iHeaders == hdrs2 );
    iContainer.Clear();
    CleanupStack::Pop( dataMsg );
    CleanupStack::Pop( ct2 );
    CleanupStack::Pop( hdrs2 );
    CleanupStack::Pop( content2 );
    CleanupStack::PopAndDestroy( msgArray2 );
    
    // unknown event
    CMceMsgArray< TMceFactory >* msgArray3 = 
        new (ELeave) CMceMsgArray< TMceFactory >( factory );
    CleanupStack::PushL( msgArray3 ); 
    msgArray3->PushL();
    
    HBufC8* content3 = KMceMessageBody().AllocLC();
   
    CMceMsgSIPEvent* eventMsg = new( ELeave ) CMceMsgSIPEvent();
    CleanupStack::PushL( eventMsg );
    msgArray3->iArray.AppendL( eventMsg );
    iOutSession->SetContainer( *msgArray3, content3 );
    
    CleanupStack::Pop( eventMsg );
    CleanupStack::PopAndDestroy( content3 );
    CleanupStack::PopAndDestroy( msgArray3 );
    
    // session
    CMceMsgArray< TMceFactory >* msgArray4 = 
        new (ELeave) CMceMsgArray< TMceFactory >( factory );
    CleanupStack::PushL( msgArray4 ); 
    
    HBufC8* content4 = KMceMessageBody().AllocLC();
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 2 );
     
    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[1] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );

    CMceMsgObject<CMceSession>* sessionMsg = 
        new( ELeave ) CMceMsgObject<CMceSession>( *iInSession, EMceItcMsgTypeSession );
    CleanupStack::PushL( sessionMsg );
    msgArray4->iArray.AppendL( sessionMsg );
    MCE_SES_RECEIVE( iInSession, KErrCompletion );
    
    iOutSession->SetContainer( *msgArray4, content4 );
    
    CleanupStack::Pop( sessionMsg );
    CleanupStack::PopAndDestroy( content4 );
    CleanupStack::PopAndDestroy( msgArray4 );
    
    // NULL container
    iManager->iContainer = NULL;
    iContainer.Clear();
    // reply, no container
    CMceMsgArray< TMceFactory >* msgArray5 = 
        new (ELeave) CMceMsgArray< TMceFactory >( factory );
    CleanupStack::PushL( msgArray5 ); 
    msgArray5->PushL();
    
    TUint32 code5 = 444;
    HBufC8* content5 = KMceMessageBody().AllocLC();
   
    HBufC8* reason5 = KMceReason().AllocLC();
    CDesC8Array* hdrs5= new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs5 );
    HBufC8* ct5 = KMceContentType().AllocLC();
    
    CMceMsgSIPReply* replyMsg5 = new( ELeave ) CMceMsgSIPReply( *reason5, code5, *hdrs5, *ct5 );
    CleanupStack::PushL( replyMsg5 );    
    msgArray5->iArray.AppendL( replyMsg5 );
    iOutSession->SetContainer( *msgArray5, content5 );
    
    EUNIT_ASSERT( iContainer.iStatusCode != code5 );
    EUNIT_ASSERT( iContainer.iContent != content5 );
    EUNIT_ASSERT( iContainer.iContentType != ct5 );
    EUNIT_ASSERT( iContainer.iHeaders != hdrs5 );
    iContainer.Clear();
    CleanupStack::Pop( replyMsg5 );
    CleanupStack::Pop( ct5 );
    CleanupStack::Pop( hdrs5 );
    CleanupStack::Pop( reason5 );
    CleanupStack::Pop( content5 );
    CleanupStack::PopAndDestroy( msgArray5 );
   
    // data, no container
    CMceMsgArray< TMceFactory >* msgArray6 = 
        new (ELeave) CMceMsgArray< TMceFactory >( factory );
    CleanupStack::PushL( msgArray6 ); 
    msgArray6->PushL();
    
    HBufC8* content6 = KMceMessageBody().AllocLC();
   
    CDesC8Array* hdrs6 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs6 );
    HBufC8* ct6 = KMceContentType().AllocLC();
    
    CMceMsgSIPData* dataMsg6 = new( ELeave ) CMceMsgSIPData( SipStrConsts::EBye, *hdrs6, *ct6 );
    CleanupStack::PushL( dataMsg6 );
    msgArray6->iArray.AppendL( dataMsg6 );
    
    CDesC8Array* hdrs7 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs7 );
    HBufC8* ct7 = KMceContentType().AllocLC();
    
    CMceMsgSIPData* dataMsg7 = new( ELeave ) CMceMsgSIPData( SipStrConsts::EBye, *hdrs7, *ct7 );
    CleanupStack::PushL( dataMsg7 );
    msgArray6->iArray.AppendL( dataMsg7 );
    
    iOutSession->SetContainer( *msgArray6, content6 );
    
    EUNIT_ASSERT( iContainer.iContent != content6 );
    EUNIT_ASSERT( iContainer.iContentType != ct6 );
    EUNIT_ASSERT( iContainer.iHeaders != hdrs6 );
    iContainer.Clear();
    CleanupStack::Pop( dataMsg7 );
    CleanupStack::Pop( ct7 );
    CleanupStack::Pop( hdrs7 );
    CleanupStack::Pop( dataMsg6 );
    CleanupStack::Pop( ct6 );
    CleanupStack::Pop( hdrs6 );
    CleanupStack::Pop( content6 );
    CleanupStack::PopAndDestroy( msgArray6 );
    
    
    iManager->iContainer = &iContainer;
    iInSession = NULL;
    
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::FCErrorOccurredTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::FCErrorOccurredTestL()
    {
    MCE_CREATE_PROFILE;
    
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
     
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    TRequestStatus& status = iOutSession->iReceiver->iStatus;
    TPckgBuf<TMceIds>* ids = iStorage->GetIds( status );
    (*ids)() = TMceIds();
    (*ids)().iAppUID = iManager->AppUid().iUid;
    (*ids)().iSessionID = iOutSession->Id();
    (*ids)().iCallbackID = EMceItcFCErrorReceived;
    (*ids)().iStatus = KErrGeneral;
    (*ids)().iMsgType = KMceNotAssigned;
    (*ids)().iState = CMceSession::EEstablished;
        
    MCE_SES_RECEIVE( iOutSession, KErrNone );
            
    EUNIT_ASSERT( iFCObserver->iSession == NULL );
    EUNIT_ASSERT( iFCObserver->iError != KErrGeneral );
    
    iOutSession->SetFCObserver( iFCObserver );
    TPckgBuf<TMceIds>* ids2 = iStorage->GetIds( status );
    (*ids2)() = TMceIds();
    (*ids2)().iAppUID = iManager->AppUid().iUid;
    (*ids2)().iSessionID = iOutSession->Id();
    (*ids2)().iCallbackID = EMceItcFCErrorReceived;
    (*ids2)().iStatus = KErrTotalLossOfPrecision;
    (*ids2)().iMsgType = KMceNotAssigned;
    (*ids2)().iState = CMceSession::EEstablished;
    MCE_SES_RECEIVE( iOutSession, KErrNone );
    
    EUNIT_ASSERT( iFCObserver->iSession == iOutSession );
    EUNIT_ASSERT_EQUALS( iFCObserver->iError, KErrTotalLossOfPrecision );
    
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );
    
    MCE_DELETE_PROFILE;
    
    }
    
// ----------------------------------------------------------------------------
// CMceSessionTest::HandleEventTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::HandleEventTestL()
    {
    
    // Cover branches, that normal usage is not covering.
    MCE_CREATE_PROFILE;
    
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 2 );
    // EMceItcUpdateFailed && reply message
    HBufC8* reason = KMceReason().AllocLC();
    CDesC8Array* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );
        
    HBufC8* contentType = KMceContentType().AllocLC();
    CMceMsgSIPReply* replyMsg = new (ELeave) CMceMsgSIPReply( *reason, 444, *headers, *contentType );
    CleanupStack::PushL( replyMsg );
    replyMsg->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = replyMsg->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();    
    
    CleanupStack::PopAndDestroy( replyMsg );
    CleanupStack::PopAndDestroy( contentType );
    CleanupStack::PopAndDestroy( headers );
    CleanupStack::PopAndDestroy( reason );
    
    MCE_SESSION_RECEIVE( iOutSession, EMceItcUpdateFailed, CMceSession::EEstablished, EMceItcMsgTypeSIPReply );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 2 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStatusCode, 444 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iReasonPhrase->Compare( KMceReason ), 0 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iHeaders->Count(), 2 );  
    EUNIT_ASSERT_EQUALS( iSessionObserver->iContentType->Compare( KMceContentType ), 0 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iBody->Compare( KMceMessageBody ), 0 );
    iSessionObserver->Clear();
    
    // EMceItcStateChanged && reply message && no observer
    iManager->SetSessionObserver( NULL );    
    HBufC8* reason2 = KMceReason().AllocLC();
    CDesC8Array* headers2 = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers2 );
    headers2->AppendL( KMceHeader1 );
    headers2->AppendL( KMceHeader2 );
        
    HBufC8* contentType2 = KMceContentType().AllocLC();
    CMceMsgSIPReply* replyMsg2 = new (ELeave) CMceMsgSIPReply( *reason2, 433, *headers2, *contentType2);
    CleanupStack::PushL( replyMsg2 );
    replyMsg2->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = replyMsg2->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();    
    
    CleanupStack::PopAndDestroy( replyMsg2 );
    CleanupStack::PopAndDestroy( contentType2 );
    CleanupStack::PopAndDestroy( headers2 );
    CleanupStack::PopAndDestroy( reason2 );
    
    MCE_SESSION_RECEIVE( iOutSession, EMceItcStateChanged, CMceSession::EEstablished, EMceItcMsgTypeSIPReply );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 2 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStatusCode, 0 );
    EUNIT_ASSERT( iSessionObserver->iReasonPhrase == NULL );
    EUNIT_ASSERT( iSessionObserver->iHeaders == NULL );  
    EUNIT_ASSERT( iSessionObserver->iContentType == NULL );
    EUNIT_ASSERT( iSessionObserver->iBody == NULL );
    iSessionObserver->Clear();
    iManager->SetSessionObserver( iSessionObserver );    
    
    // EMceItcStateChanged && reply message && no container
    iManager->iContainer = NULL;
    HBufC8* reason3 = KMceReason().AllocLC();
    CDesC8Array* headers3 = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers3 );
    headers3->AppendL( KMceHeader1 );
    headers3->AppendL( KMceHeader2 );
        
    HBufC8* contentType3 = KMceContentType().AllocLC();
    CMceMsgSIPReply* replyMsg3 = new (ELeave) CMceMsgSIPReply( *reason3, 422, *headers3, *contentType3);
    CleanupStack::PushL( replyMsg3 );
    replyMsg3->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = replyMsg3->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();    
    
    CleanupStack::PopAndDestroy( replyMsg3 );
    CleanupStack::PopAndDestroy( contentType3 );
    CleanupStack::PopAndDestroy( headers3 );
    CleanupStack::PopAndDestroy( reason3 );
    
    MCE_SESSION_RECEIVE( iOutSession, EMceItcStateChanged, CMceSession::EEstablished, EMceItcMsgTypeSIPReply );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 3 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStatusCode , 0 );
    EUNIT_ASSERT( iSessionObserver->iReasonPhrase == NULL );
    EUNIT_ASSERT( iSessionObserver->iHeaders == NULL );  
    EUNIT_ASSERT( iSessionObserver->iContentType == NULL );
    EUNIT_ASSERT( iSessionObserver->iBody == NULL );
    iSessionObserver->Clear();
    iManager->iContainer = &iContainer;
    
    // data message, EMceItcStateChanged
    CDesC8Array* headers4 = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers4 );
    headers4->AppendL( KMceHeader1 );
    headers4->AppendL( KMceHeader2 );
        
    HBufC8* contentType4 = KMceContentType().AllocLC();
    
    CMceMsgSIPData* dataMsg4 = new (ELeave) CMceMsgSIPData( SipStrConsts::EBye, *headers4, *contentType4);
    CleanupStack::PushL( dataMsg4 );
    dataMsg4->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = dataMsg4->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();    
    
    CleanupStack::PopAndDestroy( dataMsg4 );
    CleanupStack::PopAndDestroy( contentType4 );
    CleanupStack::PopAndDestroy( headers4 );
    
    MCE_SESSION_RECEIVE( iOutSession, EMceItcStateChanged, CMceSession::EEstablished, EMceItcMsgTypeSIPData );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 4 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iHeaders->Count(), 2 );  
    EUNIT_ASSERT_EQUALS( iSessionObserver->iContentType->Compare( KMceContentType ), 0 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iBody->Compare( KMceMessageBody ), 0 );
    iSessionObserver->Clear();
    
    // data message, no observer
    iManager->SetSessionObserver( NULL );
    CDesC8Array* headers5 = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers5 );
    headers5->AppendL( KMceHeader1 );
    headers5->AppendL( KMceHeader2 );
        
    HBufC8* contentType5 = KMceContentType().AllocLC();
    
    CMceMsgSIPData* dataMsg5 = new (ELeave) CMceMsgSIPData( SipStrConsts::EBye, *headers5, *contentType5);
    CleanupStack::PushL( dataMsg5 );
    dataMsg5->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = dataMsg5->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();    
    
    CleanupStack::PopAndDestroy( dataMsg5 );
    CleanupStack::PopAndDestroy( contentType5 );
    CleanupStack::PopAndDestroy( headers5 );
    
    MCE_SESSION_RECEIVE( iOutSession, EMceItcStateChanged, CMceSession::EEstablished, EMceItcMsgTypeSIPData );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 4 );
    EUNIT_ASSERT( iSessionObserver->iHeaders == NULL );  
    EUNIT_ASSERT( iSessionObserver->iContentType == NULL );
    EUNIT_ASSERT( iSessionObserver->iBody == NULL );
    iSessionObserver->Clear();
    iManager->SetSessionObserver( iSessionObserver );    
    
    // data message, no container, EMceItcUpdateFailed
    iManager->iContainer = NULL;
    CDesC8Array* headers6 = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers6 );
    headers6->AppendL( KMceHeader1 );
    headers6->AppendL( KMceHeader2 );
        
    HBufC8* contentType6 = KMceContentType().AllocLC();
    
    CMceMsgSIPData* dataMsg6 = new (ELeave) CMceMsgSIPData( SipStrConsts::EBye, *headers6, *contentType6 );
    CleanupStack::PushL( dataMsg6 );
    dataMsg6->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = dataMsg6->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();    
    
    CleanupStack::PopAndDestroy( dataMsg6 );
    CleanupStack::PopAndDestroy( contentType6 );
    CleanupStack::PopAndDestroy( headers6 );
    
    MCE_SESSION_RECEIVE( iOutSession, EMceItcUpdateFailed, CMceSession::EEstablished, EMceItcMsgTypeSIPData );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 4);
    EUNIT_ASSERT( iSessionObserver->iHeaders == NULL );  
    EUNIT_ASSERT( iSessionObserver->iContentType == NULL );
    EUNIT_ASSERT( iSessionObserver->iBody == NULL );
    iSessionObserver->Clear();
    iManager->iContainer = &iContainer;
    
    // data message, no message, no observer
    // array message ( reply && session ), EMceItcStateChanged
    TMceFactory factory;
    
    CMceMsgArray< TMceFactory >* msgArray7 = 
        new (ELeave) CMceMsgArray< TMceFactory >( factory );
    CleanupStack::PushL( msgArray7 );
    
    HBufC8* reason7 = KMceReason().AllocLC();
    CDesC8Array* headers7 = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers7 );
    headers7->AppendL( KMceHeader1 );
    headers7->AppendL( KMceHeader2 );
        
    HBufC8* contentType7 = KMceContentType().AllocLC();
    CMceMsgSIPReply* replyMsg7 = new (ELeave) CMceMsgSIPReply( *reason7, KMce200OK, *headers7, *contentType7 );
    CleanupStack::PushL( replyMsg7 );
    msgArray7->iArray.AppendL( replyMsg7 );
    CleanupStack::Pop( replyMsg7 );
    
    CMceSession* inSession7= factory.CreateLC( CMceComSession::EInSession );
    inSession7->iFlatData->iID = iOutSession->Id();
    CMceMsgObject<CMceSession>* sessionMsg7 = 
        new( ELeave ) CMceMsgObject<CMceSession>( *inSession7, EMceItcMsgTypeSession );
    CleanupStack::PushL( sessionMsg7 );
    msgArray7->iArray.AppendL( sessionMsg7 );
    CleanupStack::Pop( sessionMsg7 );
    
    msgArray7->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = msgArray7->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();    
     
    CleanupStack::PopAndDestroy( inSession7 );
    CleanupStack::PopAndDestroy( contentType7 );
    CleanupStack::PopAndDestroy( headers7 );
    CleanupStack::PopAndDestroy( reason7 );
    CleanupStack::PopAndDestroy( msgArray7 );

    MCE_SESSION_RECEIVE( iOutSession, EMceItcStateChanged, CMceSession::EEstablished, EMceItcMsgTypeMessageArray );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 5 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStatusCode, KMce200OK );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iReasonPhrase->Compare( KMceReason ), 0 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iHeaders->Count(), 2 );  
    EUNIT_ASSERT_EQUALS( iSessionObserver->iContentType->Compare( KMceContentType ), 0 );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iBody->Compare( KMceMessageBody ), 0 );
    iSessionObserver->Clear();
    
    // array message (( reply && session )) , EMceItcStateChanged, no observer
    iManager->SetSessionObserver( NULL );
    CMceMsgArray< TMceFactory >* msgArray8 = 
        new (ELeave) CMceMsgArray< TMceFactory >( factory );
    CleanupStack::PushL( msgArray8 );
    
    HBufC8* reason8 = KMceReason().AllocLC();
    CDesC8Array* headers8 = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers8 );
    headers8->AppendL( KMceHeader1 );
    headers8->AppendL( KMceHeader2 );
        
    HBufC8* contentType8 = KMceContentType().AllocLC();
    CMceMsgSIPReply* replyMsg8 = new (ELeave) CMceMsgSIPReply( *reason8, KMce200OK, *headers8, *contentType8 );
    CleanupStack::PushL( replyMsg8 );
    msgArray8->iArray.AppendL( replyMsg8 );
    CleanupStack::Pop( replyMsg8 );
    
    CMceSession* inSession8= factory.CreateLC( CMceComSession::EInSession );
    inSession8->iFlatData->iID = iOutSession->Id();
    CMceMsgObject<CMceSession>* sessionMsg8 = 
        new( ELeave ) CMceMsgObject<CMceSession>( *inSession8, EMceItcMsgTypeSession );
    CleanupStack::PushL( sessionMsg8 );
    msgArray8->iArray.AppendL( sessionMsg8 );
    CleanupStack::Pop( sessionMsg8 );
    
    msgArray8->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = msgArray8->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();    
    
    CleanupStack::PopAndDestroy( inSession8 );
    CleanupStack::PopAndDestroy( contentType8 );
    CleanupStack::PopAndDestroy( headers8 );
    CleanupStack::PopAndDestroy( reason8 );
    CleanupStack::PopAndDestroy( msgArray8 );

    MCE_SESSION_RECEIVE( iOutSession, EMceItcStateChanged, CMceSession::EEstablished, EMceItcMsgTypeMessageArray );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 5 );//no observer
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStatusCode, 0 );
    EUNIT_ASSERT( iSessionObserver->iReasonPhrase == NULL );
    EUNIT_ASSERT( iSessionObserver->iHeaders == NULL );  
    EUNIT_ASSERT( iSessionObserver->iContentType == NULL );
    EUNIT_ASSERT( iSessionObserver->iBody == NULL );
    iSessionObserver->Clear();
    iManager->SetSessionObserver( iSessionObserver );
    
    // array message, EMceItcUpdateFailed, no container
    iManager->iContainer = NULL;
    CMceMsgArray< TMceFactory >* msgArray9 = 
        new (ELeave) CMceMsgArray< TMceFactory >( factory );
    CleanupStack::PushL( msgArray9 );
    
    HBufC8* reason9 = KMceReason().AllocLC();
    CDesC8Array* headers9 = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers9 );
    headers9->AppendL( KMceHeader1 );
    headers9->AppendL( KMceHeader2 );
        
    HBufC8* contentType9 = KMceContentType().AllocLC();
    CMceMsgSIPReply* replyMsg9 = new (ELeave) CMceMsgSIPReply( *reason9, KMce200OK, *headers9, *contentType9 );
    CleanupStack::PushL( replyMsg9 );
    msgArray9->iArray.AppendL( replyMsg9 );
    CleanupStack::Pop( replyMsg9 );
    
    CMceSession* inSession9= factory.CreateLC( CMceComSession::EInSession );
    inSession9->iFlatData->iID = iOutSession->Id();
    CMceMsgObject<CMceSession>* sessionMsg9 = 
        new( ELeave ) CMceMsgObject<CMceSession>( *inSession9, EMceItcMsgTypeSession );
    CleanupStack::PushL( sessionMsg9 );
    msgArray9->iArray.AppendL( sessionMsg9 );
    CleanupStack::Pop( sessionMsg9 );
    
    msgArray9->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = msgArray9->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();    
    
    CleanupStack::PopAndDestroy( inSession9 );
    CleanupStack::PopAndDestroy( contentType9 );
    CleanupStack::PopAndDestroy( headers9 );
    CleanupStack::PopAndDestroy( reason9 );
    CleanupStack::PopAndDestroy( msgArray9 );

    MCE_SESSION_RECEIVE( iOutSession, EMceItcUpdateFailed, CMceSession::EEstablished, EMceItcMsgTypeMessageArray );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 5 );//no container
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStatusCode, 0 );
    EUNIT_ASSERT( iSessionObserver->iReasonPhrase == NULL );
    EUNIT_ASSERT( iSessionObserver->iHeaders == NULL );  
    EUNIT_ASSERT( iSessionObserver->iContentType == NULL );
    EUNIT_ASSERT( iSessionObserver->iBody == NULL );
    iSessionObserver->Clear();
    
    iManager->iContainer = &iContainer;
    
    // session message
    CMceSession* inSession10= factory.CreateLC( CMceComSession::EInSession );
    inSession10->iFlatData->iID = iOutSession->Id();
    CMceMsgObject<CMceSession>* sessionMsg10 = 
        new( ELeave ) CMceMsgObject<CMceSession>( *inSession10, EMceItcMsgTypeSession );
    CleanupStack::PushL( sessionMsg10 );
    
    sessionMsg10->EncodeL();
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = sessionMsg10->EncodeBuffer().Ptr(0).AllocL();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    CleanupStack::PopAndDestroy( sessionMsg10 );
    CleanupStack::PopAndDestroy( inSession10 );
   
    MCE_SESSION_RECEIVE( iOutSession, EMceItcUpdateFailed, CMceSession::EEstablished, EMceItcMsgTypeSession );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 5 );
    iSessionObserver->Clear();
    
     
    iStorage->Reset();
    iOutSession->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutSession->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
  
    
    // Call directly for coverage
    CMceMsgBase* nullMsg = NULL;
    HBufC8* nullContent = NULL;
    TMceIds ids;
    TMceEvent event;
     
    // EMceItcObjectAdded (other callback), data message (any)
    ids.iCallbackID = EMceItcObjectAdded;
    event = TMceEvent( ids, nullMsg, nullContent );
    iOutSession->HandleEvent( event );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 5 );
    
    // EMceItcStateChanged, null reply message, no observer, 
    iManager->SetSessionObserver( NULL );
    ids.iCallbackID = EMceItcStateChanged;
    ids.iMsgType = EMceItcMsgTypeSIPReply;
  
    event = TMceEvent( ids, nullMsg, nullContent );
    iOutSession->HandleEvent( event );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 5 );
    
    // EMceItcStateChanged, null data message, no observer, 
    iManager->SetSessionObserver( NULL );
    ids.iCallbackID = EMceItcStateChanged;
    ids.iMsgType = EMceItcMsgTypeSIPData;
    
    event = TMceEvent( ids, nullMsg, nullContent );
    iOutSession->HandleEvent( event );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 5 );
    
    // EMceItcStateChanged, null array message, no observer, 
    iManager->SetSessionObserver( NULL );
    ids.iCallbackID = EMceItcStateChanged;
    ids.iMsgType = EMceItcMsgTypeMessageArray;
    
    event = TMceEvent( ids, nullMsg, nullContent );
    iOutSession->HandleEvent( event );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 5 );
    
    iManager->SetSessionObserver( iSessionObserver );
    
	MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::HandleEventResponseReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::HandleEventResponseReceivedTestL()
    {
	//EMceItcResponseReceived 
    MCE_CREATE_PROFILE;
    TMceIds ids;

    TMceEvent event;
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 2 );
    		
    TUint32 code = 200;
    HBufC8* content = KMceMessageBody().AllocLC();
   
    HBufC8* reason = KMceReason().AllocLC();
    CDesC8Array* hdrs = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs );
    HBufC8* ct = KMceContentType().AllocLC();
    
    CMceMsgSIPReply* replyMsg = new( ELeave ) CMceMsgSIPReply( *reason, code, *hdrs, *ct );
    replyMsg->PushL();
    
    CleanupStack::PushL( replyMsg );
	ids.iCallbackID = EMceItcResponseReceived;
	ids.iMsgType = EMceItcMsgTypeSIPReply;
	ids.iTransactionID = 5000;
	
	event = TMceEvent( ids, replyMsg, content );
	iOutSession->HandleEventResponseReceivedL( event );
	
	EUNIT_ASSERT( iTransactionObserver->iBody == content );
	EUNIT_ASSERT( iTransactionObserver->iStatusCode == code );
	EUNIT_ASSERT( iTransactionObserver->iHeaders == hdrs );
	EUNIT_ASSERT( iTransactionObserver->iContentType == ct );
	EUNIT_ASSERT( iTransactionObserver->iReasonPhrase == reason );
	
	CleanupStack::PopAndDestroy( replyMsg ); // No Need to remove
	
	CleanupStack::Pop( ct );
    CleanupStack::Pop( hdrs );
    CleanupStack::Pop( reason );
    
    CleanupStack::Pop( content );	// No Need to remove
    MCE_DELETE_PROFILE;
    }
    
    
// ----------------------------------------------------------------------------
// CMceSessionTest::HandleEventRequestReceivedTestL 
// ----------------------------------------------------------------------------
//
void CMceSessionTest::HandleEventRequestReceivedTestL()
    {
    //EMceItcRequestReceived
	MCE_CREATE_PROFILE;
	TMceIds ids;

    TMceEvent event;
    TInt sessionId = 1;
    TBool detailed = EFalse;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    MCE_ESTABLISH_SESSION( iOutSession, iSessionObserver, sessionId, detailed );
    EUNIT_ASSERT_EQUALS( iSessionObserver->iStateChangedCount, 2 );

	HBufC8* content = KMceMessageBody().AllocLC();
   
    HBufC8* method = KMceMethodINFO().AllocLC();
 
    CDesC8Array* hdrs = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs );
    HBufC8* ct = KMceContentType().AllocLC();
    
    CMceMsgSIPRequest* request = new( ELeave ) CMceMsgSIPRequest( *method, *hdrs, *ct );
    request->PushL();
    
    CleanupStack::PushL( request );
		
	ids.iCallbackID = EMceItcRequestReceived;
	ids.iMsgType = EMceItcMsgTypeSIPRequest;
	ids.iTransactionID = 5000;
	
	event = TMceEvent( ids, request, content );
	iOutSession->HandleEventRequestReceivedL( event );
	
	EUNIT_ASSERT( iInTransactionObserver->iBody == content );
	EUNIT_ASSERT( iInTransactionObserver->iHeaders == hdrs );
	EUNIT_ASSERT( iInTransactionObserver->iContentType == ct );
	
    CleanupStack::PopAndDestroy( request ); 
    CleanupStack::Pop ( ct );
    CleanupStack::Pop( hdrs );
    CleanupStack::Pop( method );
    CleanupStack::Pop( content );
    MCE_DELETE_PROFILE;
    
    }
    

// ----------------------------------------------------------------------------
// CMceSessionTest::SetSessionSDPLinesTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::SetSessionSDPLinesTestL()
    {
    // State() == CMceSession::EIdle, called with NULL
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EIdle );
    
    iOutSession->SetSessionSDPLinesL( NULL );
    
    CDesC8Array* flatDataLines = iOutSession->iFlatData->iLocalSessionSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaCount() );
    
    // State() == CMceSession::EIdle
    CDesC8Array* lines = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( lines );
    lines->AppendL( KMceAttr1 );
    lines->AppendL( KMceAttr2 );
    iOutSession->SetSessionSDPLinesL( lines );
    CleanupStack::Pop( lines );
    flatDataLines = iOutSession->iFlatData->iLocalSessionSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 2, flatDataLines->MdcaCount() );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaPoint( 0 ).Compare( KMceAttr1 ) );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaPoint( 1 ).Compare( KMceAttr2 ) );
    
    MCE_DELETE_PROFILE;
    
    MCE_DELETE( iOutSession );
    // State() == CMceSession::EIncoming
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    
    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    lines = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( lines );
    lines->AppendL( KMceAttr1 );
    lines->AppendL( KMceAttr2 );
    iInSession->SetSessionSDPLinesL( lines );
    CleanupStack::Pop( lines );
    flatDataLines = iInSession->iFlatData->iLocalSessionSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 2, flatDataLines->MdcaCount() );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaPoint( 0 ).Compare( KMceAttr1 ) );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaPoint( 1 ).Compare( KMceAttr2 ) );
    
    // State() == CMceSession::EEstablished
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EEstablished );
    lines = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( lines );
    iInSession->SetSessionSDPLinesL( lines );
    CleanupStack::Pop( lines );
    flatDataLines = iInSession->iFlatData->iLocalSessionSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaCount() );
    
    // State() == CMceSession::ETerminated
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );
    lines = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( lines );
    TRAPD( error, iInSession->SetSessionSDPLinesL( lines ) );
    CleanupStack::PopAndDestroy( lines );
    EUNIT_ASSERT_EQUALS( error, KErrNotReady );
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::SessionSDPLinesTestL
// ----------------------------------------------------------------------------
//
void CMceSessionTest::SessionSDPLinesTestL()
    {
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EIdle );
    
    CDesC8Array* flatDataLines = iOutSession->iFlatData->iRemoteSessionSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    flatDataLines->AppendL( KMceAttr1 );
    flatDataLines->AppendL( KMceAttr2 );
    
    MDesC8Array* sessionLines = iOutSession->SessionSDPLinesL();
    EUNIT_ASSERT( sessionLines != NULL );
    CleanupDeletePushL( sessionLines );
    EUNIT_ASSERT_EQUALS( 2, sessionLines->MdcaCount() );
    EUNIT_ASSERT_EQUALS( 0, sessionLines->MdcaPoint( 0 ).Compare( KMceAttr1 ) );
    EUNIT_ASSERT_EQUALS( 0, sessionLines->MdcaPoint( 1 ).Compare( KMceAttr2 ) );
    CleanupStack::PopAndDestroy();
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::SessionServiceTypeTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::SessionServiceTypeTestL()
    {
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EIdle );
    
    TUint32 serviceType = iOutSession->ServiceType();
    EUNIT_ASSERT_EQUALS( 184, serviceType );
    
    iOutSession->SetServiceTypeL( 100 );
    EUNIT_ASSERT_EQUALS( 100, iOutSession->ServiceType() );
    iOutSession->SetServiceTypeL( 0 );
    EUNIT_ASSERT_EQUALS( 0, iOutSession->ServiceType() );
    
    iOutSession->iFlatData->iState = CMceSession::EOffering;
    TRAPD( err1, iOutSession->SetServiceTypeL( 80 ) );
    EUNIT_ASSERT_EQUALS( KErrNotReady, err1 );
    
    iOutSession->iFlatData->iState = CMceSession::EIncoming;
    TRAPD( err2, iOutSession->SetServiceTypeL( 256 ) );
    EUNIT_ASSERT_EQUALS( KErrArgument, err2 );
    
    TRAPD( err3, iOutSession->SetServiceTypeL( KMceMaxTypeOfServiceValue ) );
    EUNIT_ASSERT_EQUALS( KErrArgument, err3 );
    
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::ControlPathSecurityLevelTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::ControlPathSecurityLevelTestL()
	{
 	MCE_CREATE_PROFILE;

	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
	
	CMceSession::TControlPathSecurityLevel level =
		CMceSession::EControlPathSecurityUnknown;
	iOutSession->iFlatData->iSipContactAddrSecure = level;

	EUNIT_ASSERT_EQUALS( level, iOutSession->ControlPathSecurityLevel() );

	level = CMceSession::EControlPathSecure;
	iOutSession->iFlatData->iSipContactAddrSecure = level;
	EUNIT_ASSERT_EQUALS( level, iOutSession->ControlPathSecurityLevel() );

	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::AddStreamTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::AddStreamTestL()
	{        
	MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    TInt count = iInSession->iMediaStreams.Count();

	// Initialized stream
	CMceAudioStream* stream = CMceAudioStream::NewLC();
	stream->SetState( CMceMediaStream::EInitialized );

    iInSession->AddStreamL( stream );
    CleanupStack::Pop( stream );

    EUNIT_ASSERT_EQUALS( count + 1, iInSession->iMediaStreams.Count() );

	// Try to add a stream that has already been added
	TRAPD( err, iInSession->AddStreamL( stream ) );
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	EUNIT_ASSERT_EQUALS( count + 1, iInSession->iMediaStreams.Count() );
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::AddStreamPrecondTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::AddStreamPrecondTestL()
	{
	MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );

	CMceAudioStream* stream = CMceAudioStream::NewLC();

	// Make precondition to fail
	stream->iLinkedStream = stream;

    TRAPD( err, iInSession->AddStreamL( stream ) );

	stream->iLinkedStream = NULL;
    EUNIT_ASSERT_EQUALS( KErrArgument, err );
    CleanupStack::PopAndDestroy( stream );
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::AddStreamPullModeTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::AddStreamPullModeTestL()
	{        
	MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    TInt count = iInSession->iMediaStreams.Count();

	// Uninitialized incoming stream (pull mode)
	CMceAudioStream* stream = CMceAudioStream::NewLC(); 
	EUNIT_ASSERT_EQUALS( 0, stream->iCodecs.Count() );
	
    iInSession->AddStreamL( stream );
    CleanupStack::Pop( stream );

	EUNIT_ASSERT_EQUALS( CMceMediaStream::EInitialized, stream->State() );
	// At least one codec has been added
	EUNIT_ASSERT( stream->iCodecs.Count() > 0 );

	EUNIT_ASSERT_EQUALS( count + 1, iInSession->iMediaStreams.Count() );
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::AddStreamPullModeTest2L()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::AddStreamPullModeTest2L()
	{
	MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    TInt count = iInSession->iMediaStreams.Count();

	// Uninitialized incoming stream (pull mode)
	CMceAudioStream* stream = CMceAudioStream::NewLC(); 
	EUNIT_ASSERT_EQUALS( 0, stream->iCodecs.Count() );
	// Manager is not defined, so stream is not initialized
	iInSession->iManager = NULL;

    iInSession->AddStreamL( stream );
    CleanupStack::Pop( stream );

	EUNIT_ASSERT_EQUALS( CMceMediaStream::EUninitialized, stream->State() );
	EUNIT_ASSERT( stream->iCodecs.Count() == 0 );

	EUNIT_ASSERT_EQUALS( count + 1, iInSession->iMediaStreams.Count() );
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::GetModifierTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::GetModifierTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
	
	// Modifier out of range
	TUint value( 0 );
	TRAPD( err, iOutSession->GetModifierL( KMceMaxSessionModifiers + 1,
										   value ) );
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	
	const TInt KModifierId = 2;
	const TUint KModifierValue = 500;
	iOutSession->SetModifierL( KModifierId, KModifierValue );
	iOutSession->GetModifierL( KModifierId, value );
	EUNIT_ASSERT_EQUALS( KModifierValue, value );

	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::SetModifierTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::SetModifierTestL()
	{
	// Modifier out of range
	TRAPD( err, iOutSession->SetModifierL( KMceMaxSessionModifiers + 1, 1 ) );
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::AssociatedEventsTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::AssociatedEventsTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

	EUNIT_ASSERT( !iOutSession->AssociatedEventsL() );
	
	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::AssociatedRefersTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::AssociatedRefersTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

	EUNIT_ASSERT( !iOutSession->AssociatedRefersL() );
	
	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::RemoveStreamTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::RemoveStreamTestL()
	{
	MCE_CREATE_PROFILE;
	
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
	
	// The stream is not related to the session
	CMceAudioStream* stream = CMceAudioStream::NewLC();
	stream->SetState( CMceMediaStream::EInitialized );
	EUNIT_ASSERT_EQUALS( 0, iOutSession->iMediaStreams.Count() );
	iOutSession->RemoveStreamL( *stream );
	EUNIT_ASSERT_EQUALS( 0, iOutSession->iMediaStreams.Count() );		
	
	// The stream is related to the session, but the session state is invalid
	iOutSession->AddStreamL( stream );
	CleanupStack::Pop( stream );
	EUNIT_ASSERT_EQUALS( 1, iOutSession->iMediaStreams.Count() );
	iOutSession->iFlatData->iState = CMceSession::EOffering;
	TRAPD( err, iOutSession->RemoveStreamL( *stream ) )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
	EUNIT_ASSERT_EQUALS( 1, iOutSession->iMediaStreams.Count() );
	
	// Session state CMceSession::EIdle, the stream found and removed
	iOutSession->iFlatData->iState = CMceSession::EIdle;
    iOutSession->RemoveStreamL( *stream );
    EUNIT_ASSERT_EQUALS( 0, iOutSession->iMediaStreams.Count() );

    // Session state CMceSession::EIncoming, the stream found and removed
    iOutSession->iFlatData->iState = CMceSession::EIncoming;
    stream = CMceAudioStream::NewLC();
    iOutSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    EUNIT_ASSERT_EQUALS( 1, iOutSession->iMediaStreams.Count() );
    iOutSession->RemoveStreamL( *stream );
    EUNIT_ASSERT_EQUALS( 0, iOutSession->iMediaStreams.Count() );
    
    // Session state CMceSession::EEstablished, the stream found and removed
    iOutSession->iFlatData->iState = CMceSession::EEstablished;
    stream = CMceAudioStream::NewLC();
    iOutSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    EUNIT_ASSERT_EQUALS( 1, iOutSession->iMediaStreams.Count() );    
    iOutSession->RemoveStreamL( *stream );
    EUNIT_ASSERT_EQUALS( 0, iOutSession->iMediaStreams.Count() );

    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::SIPParamsCleanupTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::SIPParamsCleanupTestL()
	{
	// Pass null pointer
	CMceSession::SIPParamsCleanup( NULL );


	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
	
	EUNIT_ASSERT( iOutSession->iFlatData->iSIPHeaders != NULL );
    EUNIT_ASSERT( iOutSession->iFlatData->iSIPContentType != NULL );
    EUNIT_ASSERT( iOutSession->iFlatData->iSIPContentHeaders != NULL );

	CDesC8Array* headers = iOutSession->iFlatData->iSIPHeaders;
	HBufC8* contentType = iOutSession->iFlatData->iSIPContentType;
	CDesC8Array* contentHeaders = iOutSession->iFlatData->iSIPContentHeaders;

	CMceSession::SIPParamsCleanup( iOutSession );
	
	delete headers;
	delete contentType;
	delete contentHeaders;

	EUNIT_ASSERT( !iOutSession->iFlatData->iSIPHeaders );
    EUNIT_ASSERT( !iOutSession->iFlatData->iSIPContentType );
    EUNIT_ASSERT( !iOutSession->iFlatData->iSIPContentHeaders );

	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::AddBundleTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::AddBundleTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

	CMceStreamBundle* bundle = CMceStreamBundle::NewLC( CMceStreamBundle::ELS );
	iOutSession->AddBundleL( bundle );
	CleanupStack::Pop( bundle );


	iOutSession->RemoveBundleL( *bundle );
	CleanupStack::PushL( bundle );

	
	// Try to remove bundle again	
	TRAPD( err, iOutSession->RemoveBundleL( *bundle ) );
	CleanupStack::PopAndDestroy( bundle );
	EUNIT_ASSERT_EQUALS( KErrNotFound, err );

	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::TypeTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::TypeTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

	EUNIT_ASSERT_EQUALS( KMceSessionNormal, iOutSession->Type() );
	
	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::SerializationIdTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::SerializationIdTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

	EUNIT_ASSERT( iOutSession->iFlatData->iID == iOutSession->SerializationId() );

	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::ExternalizeInternalizeTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::ExternalizeInternalizeTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

	CBufFlat* encodeBuf = CBufFlat::NewL( KMceExternalizeBufferExpandSize );
	CleanupStack::PushL( encodeBuf );    
	RBufWriteStream writeStream( *encodeBuf, 0 );
	writeStream.PushL();

    iOutSession->ExternalizeFlatL( writeStream );
    EUNIT_ASSERT( encodeBuf->Ptr( 0 ).Length() > 0 );


	RDesReadStream readStream( encodeBuf->Ptr( 0 ) );
    CleanupClosePushL( readStream );
    iOutSession->InternalizeFlatL( readStream );

	CleanupStack::PopAndDestroy(); // readStream
	CleanupStack::PopAndDestroy(); // writeStream
	CleanupStack::PopAndDestroy( encodeBuf );

	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::ITCSenderTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::ITCSenderTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

	EUNIT_ASSERT( iOutSession->iSender == &iOutSession->ITCSender() );

	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::ITCManagerTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::ITCManagerTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

	EUNIT_ASSERT( iOutSession->iManager == &iOutSession->Manager() );

	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::ConnectionActiveTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::ConnectionActiveTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
	
	iOutSession->iFlatData->iIsConnectionActive = ETrue;
	EUNIT_ASSERT( iOutSession->ConnectionActive() );

	iOutSession->iFlatData->iIsConnectionActive = EFalse;
	EUNIT_ASSERT( !iOutSession->ConnectionActive() );
	
	iOutSession->iFlatData->iIsConnectionActive = ETrue;
	EUNIT_ASSERT( iOutSession->ConnectionActive() );
			 
	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::InitializeTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::InitializeTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
	
	// Temporarily clear iManager to cause InitializeL to leave
	CMceManager* manager = iOutSession->iManager;
	iOutSession->iManager = NULL;
	
	TRAPD( err, iOutSession->InitializeL( ETrue, ETrue ) );
	iOutSession->iManager = manager;
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::InitializeWithBundleTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::InitializeWithBundleTestL()
	{
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

	CMceStreamBundle* bundle = CMceStreamBundle::NewLC( CMceStreamBundle::ELS );
	iOutSession->AddBundleL( bundle );
	CleanupStack::Pop( bundle );

	iOutSession->InitializeL( ETrue, ETrue );

	EUNIT_ASSERT( bundle->iSession == iOutSession);
	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::EventReceivedTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::EventReceivedTestL()
    {
	MCE_CREATE_PROFILE;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

    // Use any event to simulate the observer deleting 
    // the MCE session within the CMceSession::EventReceivedL callback 
    TMceIds ids;
    ids.iSessionID = iOutSession->Id();
    ids.iCallbackID = EMceItcSessionConnectionStateChanged;
    ids.iState = EFalse; // Connection inactive
    TMceEvent event( ids, NULL, NULL );
    iSessionObserver->iDeleteSessionWithinCallback = ETrue;
    iOutSession->EventReceivedL( event );
    // The expected result is no panic
    iOutSession = NULL;
	
	MCE_DELETE_PROFILE;    
    }

// ----------------------------------------------------------------------------
// CMceSessionTest::SendRequestTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::SendRequestTestL()
	{
	MCE_CREATE_PROFILE;
	TMceTransactionId TransactionID = KMceNotAssigned;
	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EEstablished );
	
	HBufC8* content = KMceMessageBody().AllocLC();
    CDesC8Array* hdrs = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs );
    HBufC8* ct = KMceContentType().AllocLC();

	iManager->SetTransactionObserver( iTransactionObserver );

	TransactionID = iOutSession->SendRequestL( KMceMethodINFO, hdrs, ct, content );

	CleanupStack::Pop( ct );
	CleanupStack::Pop( hdrs );
	CleanupStack::Pop( content );

	// Ensure we get valid Transaction ID for request sent.
	if ( TransactionID == KMceNotAssigned )
		{
		User::LeaveNoMemory();
		}
	MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceSessionTest::SendResponseTestL()
// ----------------------------------------------------------------------------
//
void CMceSessionTest::SendResponseTestL()
	{
	MCE_CREATE_PROFILE;

	iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );

    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EEstablished );

	iManager->SetInTransactionObserver( iInTransactionObserver );
		
	TMceTransactionId transactionID = 5000;
	TUint32 code = 200;
    HBufC8* content = KMceMessageBody().AllocLC();
   
    HBufC8* reason = KMceReason().AllocLC();
    CDesC8Array* hdrs = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs );
    HBufC8* ct = KMceContentType().AllocLC();

    iOutSession->SendResponseL( transactionID, *reason, code,
    							hdrs, ct, content );
				
	// Ensure we get valid Transaction ID Exit for the request for which the 
	// response is being sent.
	
	EUNIT_ASSERT( transactionID != KMceNotAssigned );

	CleanupStack::Pop( ct );
    CleanupStack::Pop( hdrs );
    CleanupStack::PopAndDestroy( reason );
    CleanupStack::Pop( content );
    
	MCE_DELETE_PROFILE;
	}

// End of File
