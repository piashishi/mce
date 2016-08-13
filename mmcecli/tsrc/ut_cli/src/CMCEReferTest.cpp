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
#include "CMceReferTest.h"

#include "mcestubs.h"
#include "mcetestdefs.h"
#include "mceclientserver.h"

#include "mcemanager.h"
#include "mceoutrefer.h"
#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceeventreceiver.h"
#include "mcereferreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mceevents.h"
#include "mceserial.h"



        

// ----------------------------------------------------------------------------
// CMceReferTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceReferTest::setUpL()
    {
    MCE_CREATE_PROFILE;
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManager = CMceManager::NewL( iUid, &iContainer );
    iReferObserver = new (ELeave) CMceReferObserverStub();
    iManager->SetReferObserver( iReferObserver );
    
    iRefer = CMceOutRefer::NewL( *iManager, 
                                 *profile, 
                                 KMceRecipient, 
                                 KMceReferTo,
                                 CMceRefer::ESuppressed );
    EUNIT_ASSERT( !iRefer->IsInRefer() );
    EUNIT_ASSERT( iRefer->Type() == CMceRefer::ESuppressed );
    EUNIT_ASSERT( iRefer->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iRefer->Id() == 1 );

    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceReferTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceReferTest::tearDown()
    {
    MCE_TEST_DELETE( iRefer );
    
    MCE_MAN_DELETE( iManager );
 
    delete iReferObserver;
    
    delete iStorage;
    Dll::SetTls( NULL );
        
    }

// ----------------------------------------------------------------------------
// CMceReferTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceReferTest::suiteL()
    {
    CMceReferTest* suite = new CMceReferTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceReferTest,
    "CMceReferTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, ErrorOccuredTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, ErrorOccuredTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, EventReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, EventReceivedTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, EventReceivedTest3L, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, ReceiverTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, ConstructTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, ResolveStateTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, HandleEventTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, EventStateChangedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, HandleStateChangedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, TransferEventOwnershipTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, AssociatedSessionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, AssociatedEventsLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceReferTest", setUpL, AssociatedRefersLTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceReferTest::ErrorOccuredTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::ErrorOccuredTestL()
    {
    // for plain refer
    TInt error = KErrGeneral;
    TMceIds ids;
    iRefer->iReceiver->ErrorOccuredL( ids, error );
    EUNIT_ASSERT( iReferObserver->iRefer == iRefer ); 
    EUNIT_ASSERT_EQUALS( iReferObserver->iError, error );
    }
    
// ----------------------------------------------------------------------------
// CMceReferTest::ErrorOccuredTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::ErrorOccuredTest2L()
    {
    // leave, no observer
    iManager->SetReferObserver( NULL );
    TInt error = KErrGeneral;
    TMceIds ids;
    TRAPD( err, iRefer->iReceiver->ErrorOccuredL( ids, error ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrArgument );
    EUNIT_ASSERT( iReferObserver->iRefer != iRefer ); 
    EUNIT_ASSERT( iReferObserver->iError != error );
    }

// ----------------------------------------------------------------------------
// CMceReferTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::EventReceivedTestL()
    {
    /*TMceIds& aId*/
    // Cover leaving, when wrong id.
    TMceIds ids;
    ids.iSessionID = KMceTestWrongId;
    TRAPD( err, iRefer->iReceiver->IncomingEventL( EMceItcStateChanged, ids ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrGeneral );
    }

// ----------------------------------------------------------------------------
// CMceReferTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::EventReceivedTest2L()
    {
    /*TMceIds& aId, CMceMsgBase& aMessage*/
    // Cover leaving, when wrong id.
    TMceIds ids;
    ids.iSessionID = KMceTestWrongId;
    ids.iMsgType = EMceItcMsgTypeSIPReply;
    CMceMsgSIPReply* msg = new( ELeave ) CMceMsgSIPReply();
    CleanupStack::PushL( msg );
    msg->EncodeL();
    HBufC8* context = msg->EncodeBufferCloneL();
    EUNIT_ASSERT( context != 0 );
    TRAPD( err, iRefer->iReceiver->IncomingEventL( EMceItcStateChanged,
                                                   ids,
                                                   *context ) );
    delete context;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    
    CleanupStack::PopAndDestroy( msg );
    EUNIT_ASSERT_EQUALS( err, KErrGeneral );
    }

// ----------------------------------------------------------------------------
// CMceReferTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::EventReceivedTest3L()
    {
    /*TMceIds& aId, CMceMsgBase& aMessage, HBufC8* aContent*/
    CMceReferReceiver* receiver = iRefer->iReceiver;
    // Cover leaving, when wrong id.
    TMceIds ids;
    ids.iSessionID = KMceTestWrongId;
    ids.iMsgType = EMceItcMsgTypeSIPReply;
    CMceMsgSIPReply* msg = new( ELeave ) CMceMsgSIPReply();
    CleanupStack::PushL( msg );
    msg->EncodeL();
    HBufC8* context = msg->EncodeBufferCloneL();
    CleanupStack::PopAndDestroy( msg );                                               
    CleanupStack::PushL( context );
    HBufC8* body = NULL;
    TRAPD( err1, receiver->IncomingEventL( EMceItcStateChanged,
                                                   ids, 
                                                   *context, 
                                                   body ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
    EUNIT_ASSERT_EQUALS( err1, KErrGeneral );
                                                       
    // !IsSessionId()
    ids.iSessionID = iRefer->Id();
    ids.iMediaID = iRefer->Id();
    TRAPD( err2, receiver->IncomingEventL( EMceItcStateChanged, ids, *context, body ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err2, KErrGeneral );
    
    CleanupStack::PopAndDestroy( context );
    }

// ----------------------------------------------------------------------------
// CMceReferTest::ReceiverTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::ReceiverTestL()
    {
    // Tests for the leaving cases
    CMceReferReceiver* receiver = iRefer->iReceiver;
    TMceIds ids;
    HBufC8* context = KMceTestFailContext().AllocLC();
    HBufC8* content = NULL;
    TRAPD( err1, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
    EUNIT_ASSERT_EQUALS( err1, KErrNotSupported );
    
    TRAPD( err2, receiver->IncomingEventL( EMceItcStateChanged, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err2, KErrGeneral );
    
    TRAPD( err3, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )
    EUNIT_ASSERT_EQUALS( err3, KErrNotSupported );
    
    TRAPD( err4, receiver->IncomingEventL( EMceItcStateChanged, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 )
    EUNIT_ASSERT_EQUALS( err4, KErrGeneral );
    CleanupStack::PopAndDestroy( context );
    }

// ----------------------------------------------------------------------------
// CMceReferTest::ConstructTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::ConstructTestL()
    {
    // Cover the leaving branches
    // NULL aRecipient
    TRAPD( err1,  iRefer->CMceRefer::ConstructL( NULL, NULL, NULL, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    // NULL aReferTo
    HBufC8* recipient = KMceRecipient().AllocLC();
    TRAPD( err2,  iRefer->CMceRefer::ConstructL( recipient, NULL, NULL, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    CleanupStack::PopAndDestroy( recipient );
    }
    
// ----------------------------------------------------------------------------
// CMceReferTest::ResolveStateTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::ResolveStateTestL()
    {
    // Test uncovered branches
    TInt result = static_cast<CMceRefer::TState> ( KErrNotFound );
    
    // !ReferEvent;
    TRAPD( err1, result = iRefer->ResolveStateL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    EUNIT_ASSERT_EQUALS( result, KErrNotFound );
   
    // ReferEvent()->State() == CMceEvent::EIdle
   	CMceRefer* refer = CMceOutRefer::NewL( *iRefer, KMceReferTo );
    CleanupStack::PushL( refer );
    result = refer->ResolveStateL();
    EUNIT_ASSERT_EQUALS( result, CMceRefer::EIdle );
    
    // default
    result = KErrNotFound;
    refer->ReferEvent()->iState = static_cast< CMceEvent::TState >( KErrNotFound );
    TRAPD( err2, result = refer->ResolveStateL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    EUNIT_ASSERT_EQUALS( result, KErrNotFound );
    //This is needed otherwise it will leave as KErrNotReady when trys to delete event
    refer->iOwnedEvent->iState = CMceEvent::ETerminated ;
    CleanupStack::PopAndDestroy( refer );
   }

// ----------------------------------------------------------------------------
// CMceReferTest::HandleEventTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::HandleEventTestL()
    {
    EUNIT_ASSERT_EQUALS( iReferObserver->iStateChangedCount, 0 );
    TMceIds ids;
    // Test uncovered branches
    //aEvent.MessageType() != EMceItcMsgTypeSIPReply
    ids.iMsgType = EMceItcMsgTypeSIPData;
    TMceEvent event1 = TMceEvent( ids, NULL, NULL );
    iRefer->HandleEventL( event1 );
    EUNIT_ASSERT_EQUALS( iReferObserver->iStateChangedCount, 0 );
    
    // aEvent.Action() != EMceItcStateChanged
    ids.iMsgType = EMceItcMsgTypeSIPReply;
    ids.iCallbackID = EMceItcObjectAdded;
    TMceEvent event2 = TMceEvent( ids, NULL, NULL );
    iRefer->HandleEventL( event2 );
    EUNIT_ASSERT_EQUALS( iReferObserver->iStateChangedCount, 0 );
    }

// ----------------------------------------------------------------------------
// CMceReferTest::EventStateChangedTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::EventStateChangedTestL()
    {
    CMceRefer* refer = CMceOutRefer::NewL( *iRefer, KMceReferTo );
    CleanupStack::PushL( refer );
    TMceIds ids;
    TMceEvent event = TMceEvent( ids, NULL, NULL );
    
    // wrong event ID.
    TRAPD( err1, refer->EventStateChangedL( event ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
     //This is needed otherwise it will leave as KErrNotReady when trys to delete event
    refer->iOwnedEvent->iState = CMceEvent::ETerminated ;
    CleanupStack::PopAndDestroy( refer );
    
    // !ReferEvent();
    TRAPD( err2, iRefer->EventStateChangedL( event ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    }
    
// ----------------------------------------------------------------------------
// CMceReferTest::HandleStateChangedTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::HandleStateChangedTestL()
    {
    TMceIds ids;
    
    //aEvent.Action() != EMceItcStateChanged
    ids.iCallbackID = EMceItcObjectAdded;
    TMceEvent event1 = TMceEvent( ids, NULL, NULL );
    TRAPD( err1, iRefer->HandleStateChangedL( event1 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    //aEvent.MessageType() != EMceItcMsgTypeSIPReply
    ids.iCallbackID = EMceItcStateChanged;
    ids.iMsgType = EMceItcMsgTypeSIPData;
    TMceEvent event2 = TMceEvent( ids, NULL, NULL );
    TRAPD( err2, iRefer->HandleStateChangedL( event2 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    //!iManager.ReferObserver()
    EUNIT_ASSERT_EQUALS( iReferObserver->iStateChangedCount, 0 );
    iManager->iReferObserver = NULL;
    ids.iMsgType = EMceItcMsgTypeSIPReply;
    TMceEvent event3 = TMceEvent( ids, NULL, NULL );
    iRefer->HandleStateChangedL( event3 );
    EUNIT_ASSERT_EQUALS( iReferObserver->iStateChangedCount, 0 );
    iManager->iReferObserver = iReferObserver;
    
    // !replyMsg
    TMceEvent event4 = TMceEvent( ids, NULL, NULL );
    iRefer->HandleStateChangedL( event4 );
    EUNIT_ASSERT( iReferObserver->iRefer == iRefer );
    EUNIT_ASSERT_EQUALS( iReferObserver->iStateChangedCount, 1 );
    EUNIT_ASSERT( iReferObserver->iBody == NULL );
    EUNIT_ASSERT( iReferObserver->iContentType == NULL );
    EUNIT_ASSERT_EQUALS( iReferObserver->iError, 0 );
    EUNIT_ASSERT( iReferObserver->iHeaders == NULL );
    EUNIT_ASSERT( iReferObserver->iReasonPhrase == NULL );
    EUNIT_ASSERT_EQUALS( iReferObserver->iStatusCode, 0 );
    
    // !container
    iManager->iContainer = NULL;
    TUint32 code = 433;
    
    HBufC8* reason = KMceReason().AllocLC();
    CDesC8Array* hdrs = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs );
    hdrs->AppendL( KMceHeader1 );
    HBufC8* ct = KMceContentType().AllocLC();
    
    CMceMsgSIPReply* replyMsg = new( ELeave ) CMceMsgSIPReply( *reason, code, *hdrs, *ct );
    CleanupStack::PushL( replyMsg );
    replyMsg->EncodeL(); 
    iStorage->Reset();
    iRefer->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iRefer->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = replyMsg->EncodeBuffer().Ptr(0).AllocL();
    iRefer->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iRefer->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();
    
    CleanupStack::PopAndDestroy( replyMsg );
    CleanupStack::PopAndDestroy( ct );
    CleanupStack::PopAndDestroy( hdrs );
    CleanupStack::PopAndDestroy( reason );
    
    MCE_SESSION_RECEIVE( iRefer, EMceItcStateChanged, CMceEvent::ETerminated, EMceItcMsgTypeSIPReply );
    EUNIT_ASSERT( iReferObserver->iRefer == iRefer );
    EUNIT_ASSERT_EQUALS( iReferObserver->iStateChangedCount, 2 );
    EUNIT_ASSERT( iReferObserver->iBody == NULL );
    EUNIT_ASSERT( iReferObserver->iContentType == NULL );
    EUNIT_ASSERT_EQUALS( iReferObserver->iError, 0 );
    EUNIT_ASSERT( iReferObserver->iHeaders == NULL );
    EUNIT_ASSERT( iReferObserver->iReasonPhrase == NULL );
    EUNIT_ASSERT_EQUALS( iReferObserver->iStatusCode, 0 );
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iManager->iContainer = &iContainer;
    }

// ----------------------------------------------------------------------------
// CMceReferTest::TransferEventOwnershipTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::TransferEventOwnershipTestL()
    {
    // cover !iEvent 
    CMceEvent* event = iRefer->TransferEventOwnership();
    EUNIT_ASSERT( event == NULL );
    }

// ----------------------------------------------------------------------------
// CMceReferTest::AssociatedSessionTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::AssociatedSessionTestL()
	{
	EUNIT_ASSERT( !iRefer->AssociatedSession() );
	}

// ----------------------------------------------------------------------------
// CMceReferTest::AssociatedEventsLTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::AssociatedEventsLTestL()
	{
	EUNIT_ASSERT( !iRefer->AssociatedEventsL() );
	}

// ----------------------------------------------------------------------------
// CMceReferTest::AssociatedRefersLTestL
// ----------------------------------------------------------------------------
//
void CMceReferTest::AssociatedRefersLTestL()
	{
	EUNIT_ASSERT( !iRefer->AssociatedRefersL() );
	}
