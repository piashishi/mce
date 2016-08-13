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
#include "CMceEventTest.h"

#include "mcestubs.h"
#include "mcetestdefs.h"
#include "mceclientserver.h"
#include "mceserial.h"

#include "mcemanager.h"
#include "mceoutevent.h"
#include "mceeventreceiver.h"
#include "mcemanagerreceiver.h"
#include "mceeventmanagerreceiver.h"

// ----------------------------------------------------------------------------
// CMceEventTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceEventTest::setUpL()
    {
    MCE_CREATE_PROFILE;
    
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iEventObserver = new (ELeave) CMceEventObserverStub();
    iInReferObserver = new (ELeave) CMceInReferObserverStub();
    iReferObserver = new (ELeave) CMceReferObserverStub();
    iManager = CMceManager::NewL( iUid, &iContainer );
    iManager->SetInReferObserver( iInReferObserver );
    iManager->SetReferObserver( iReferObserver );
    iManager->SetEventObserver( iEventObserver );
    iEvent = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    EUNIT_ASSERT_EQUALS( iEvent->State(), CMceEvent::EIdle );
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceEventTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceEventTest::tearDown()
    {
    MCE_TEST_DELETE( iEvent );
    
    MCE_MAN_DELETE( iManager );

    delete iEventObserver;
    delete iInReferObserver;
    delete iReferObserver;
    delete iStorage;
    Dll::SetTls( NULL );
    }

// ----------------------------------------------------------------------------
// CMceEventTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceEventTest::suiteL()
    {
    CMceEventTest* suite = new CMceEventTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceEventTest,
    "CMceEventTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, ErrorOccuredTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, ErrorOccuredTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, ErrorOccuredTest3L, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, ErrorOccuredTest4L, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, EventReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, EventReceivedTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, EventReceivedTest3L, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, ReceiverTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, ConstructTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, HandleEventTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, AssociatedSessionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, AssociatedEventsLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceEventTest", setUpL, AssociatedRefersLTestL, tearDown )
EUNIT_END_TEST_TABLE     

		                                   
// ----------------------------------------------------------------------------
// CMceEventTest::ErrorOccuredTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::ErrorOccuredTestL()
    {
    // for plain event
    TInt error = KErrGeneral;
    TMceIds ids;
    iEvent->iReceiver->ErrorOccuredL( ids, error );
    EUNIT_ASSERT_EQUALS( iEvent->State(), CMceEvent::ETerminated );
    EUNIT_ASSERT( iEventObserver->iEvent == iEvent ); 
    EUNIT_ASSERT_EQUALS( iEventObserver->iError,error );
    }
    
// ----------------------------------------------------------------------------
// CMceEventTest::ErrorOccuredTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::ErrorOccuredTest2L()
    {
    // leave, no event observer
    iManager->SetEventObserver( NULL );
    TInt error = KErrGeneral;
    TMceIds ids;
    TRAPD( err, iEvent->iReceiver->ErrorOccuredL( ids, error ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrArgument );
    EUNIT_ASSERT_EQUALS( iEvent->State(), CMceEvent::ETerminated );
    EUNIT_ASSERT( iEventObserver->iEvent != iEvent ); 
    EUNIT_ASSERT( iEventObserver->iError != error );
    //This is needed otherwise it will leave as KErrNotReady when trys to delete event
    iEvent->iState = CMceEvent::EActive;
    }

// ----------------------------------------------------------------------------
// CMceEventTest::ErrorOccuredTest2L
// ----------------------------------------------------------------------------
//
void CMceEventTest::ErrorOccuredTest3L()
    {
    // Event attached to incoming refer
    TInt error = KErrGeneral;
    iManager->SetEventObserver( iEventObserver );
    EUNIT_ASSERT( iManager->Events().Count() == 1 ); // iEvent is there
    
    MCE_INCOMING_REFER( iManager );
    
    EUNIT_ASSERT( iManager->Events().Count() == 2 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    CMceInRefer* refer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    CleanupStack::PushL( refer );
    EUNIT_ASSERT( refer->IsInRefer() );
    EUNIT_ASSERT( refer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( refer->State() == CMceRefer::EIdle );
    
    CMceEvent* event = refer->AcceptL();
    CleanupStack::PushL( event );
    EUNIT_ASSERT_EQUALS( refer->State(), CMceRefer::EPending );
    EUNIT_ASSERT_EQUALS( event->State(), CMceEvent::EPending );
    
    TMceIds ids;
    event->iReceiver->ErrorOccuredL( ids, error );
    CleanupStack::Pop( event );  
      //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   iEvent->iState = CMceEvent::EActive;
   
    MCE_TEST_DELETE( event );
    CleanupStack::PopAndDestroy( refer );
    }

// ----------------------------------------------------------------------------
// CMceEventTest::ErrorOccuredTest4L
// ----------------------------------------------------------------------------
//
void CMceEventTest::ErrorOccuredTest4L()
    {
    // CMceOutEvent is deleted inside MMceEventObserver
    MCE_CREATE_PROFILE;
    TInt error = KErrTotalLossOfPrecision;
    TMceIds ids;
    CMceOutEvent* event = CMceOutEvent::NewL( *iManager, 
                                              *profile, 
                                              KMceRecipient, 
                                              KMceEventHeader, 
                                              1000 );
    // Now let us transfer the ownership to observer so that it can delete
    // the object inside MMceEventObserver
    iEventObserver->iEventOwnedByObserver = event; 
    event->iReceiver->ErrorOccuredL( ids, error );
	EUNIT_ASSERT( iEventObserver->iEventOwnedByObserver == NULL ); 
    EUNIT_ASSERT_EQUALS( iEventObserver->iError,error );
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceEventTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::EventReceivedTestL()
    {
    /*TMceIds& aId*/
    // Cover leaving, when wrong id.
    TMceIds ids;
    ids.iSessionID = KMceTestWrongId;
    TRAPD( err, iEvent->iReceiver->IncomingEventL( EMceItcStateChanged, ids ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrGeneral );
    
    // Leave, when media id
    ids.iSessionID = iEvent->Id();
    ids.iMediaID = iEvent->Id();
    TRAPD( err2, iEvent->iReceiver->IncomingEventL( EMceItcStateChanged, ids ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT_EQUALS( err2, KErrGeneral );
      //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   	iEvent->iState = CMceEvent::ETerminated ;
   
    }

// ----------------------------------------------------------------------------
// CMceEventTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::EventReceivedTest2L()
    {
    /*TMceIds& aId, CMceMsgBase& aMessage*/
    // Cover leaving, when wrong id.
    TMceIds ids;
    ids.iMsgType = EMceItcMsgTypeSIPReply;
    ids.iSessionID = KMceTestWrongId;
    CMceMsgSIPReply* msg = new( ELeave ) CMceMsgSIPReply();
    CleanupStack::PushL( msg );
    msg->EncodeL();
    HBufC8* context = msg->EncodeBufferCloneL();
    TRAPD( err, iEvent->iReceiver->IncomingEventL( EMceItcStateChanged, 
                                                   ids, 
                                                   *context ) );
    delete context;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )                                                    
    CleanupStack::PopAndDestroy( msg );                                                   
    EUNIT_ASSERT_EQUALS( err, KErrGeneral );
      //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   	iEvent->iState = CMceEvent::ETerminated ;
   
    }

// ----------------------------------------------------------------------------
// CMceEventTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::EventReceivedTest3L()
    {
    /*TMceIds& aId, CMceMsgBase& aMessage, HBufC8* aContent*/
    // Cover leaving, when wrong id.
    TMceIds ids;
    ids.iMsgType = EMceItcMsgTypeSIPReply;
    CMceMsgSIPReply* msg = new( ELeave ) CMceMsgSIPReply();
    CleanupStack::PushL( msg );
    msg->EncodeL();
    HBufC8* context = msg->EncodeBufferCloneL();
    HBufC8* body = NULL;
    ids.iSessionID = KMceTestWrongId;
    TRAPD( err, iEvent->iReceiver->IncomingEventL( EMceItcStateChanged,
                                                   ids, 
                                                   *context, 
                                                   body ) );
    delete context;   
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )                                                
    CleanupStack::PopAndDestroy( msg );
    EUNIT_ASSERT_EQUALS( err, KErrGeneral );
      //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   	iEvent->iState = CMceEvent::ETerminated ;
   
    }
    
// ----------------------------------------------------------------------------
// CMceEventTest::ReceiverTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::ReceiverTestL()
    {
    // Tests for the leaving cases
    CMceEventReceiver* receiver = iEvent->iReceiver;
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
      //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   	iEvent->iState = CMceEvent::ETerminated ;
   
    }

// ----------------------------------------------------------------------------
// CMceEventTest::ConstructTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::ConstructTestL()
    {
    // Cover the leaving branches
    // NULL aEventHeader
    TRAPD( err1,  iEvent->CMceEvent::ConstructL( NULL, NULL, NULL, 0, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )  
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    // NULL aRecipient
    HBufC8* referTo = KMceReferTo().AllocLC();
    TRAPD( err2,  iEvent->CMceEvent::ConstructL( referTo, NULL, NULL, 0, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 ) 
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    CleanupStack::PopAndDestroy( referTo );
      //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   	iEvent->iState = CMceEvent::ETerminated ;
   
    }

// ----------------------------------------------------------------------------
// CMceEventTest::HandleEventTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::HandleEventTestL()
    {
    // cover the uncovered branches
    EUNIT_ASSERT_EQUALS( iEventObserver->iStateChangedCount, 0 );
    // EMceItcMsgTypeSIPReply && aEvent.Action() != EMceItcStateChanged
    TUint32 code1 = 444;
    
    HBufC8* reason1 = KMceReason().AllocLC();
    CDesC8Array* hdrs1 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs1 );
    HBufC8* ct1 = KMceContentType().AllocLC();
    
    CMceMsgSIPReply* replyMsg1 = new( ELeave ) CMceMsgSIPReply( *reason1, code1, *hdrs1, *ct1 );
    CleanupStack::PushL( replyMsg1 );   
    replyMsg1->EncodeL(); 
    iStorage->Reset();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iEvent->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = replyMsg1->EncodeBuffer().Ptr(0).AllocL();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iEvent->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();
    
    CleanupStack::PopAndDestroy( replyMsg1 );
    CleanupStack::PopAndDestroy( ct1 );
    CleanupStack::PopAndDestroy( hdrs1 );
    CleanupStack::PopAndDestroy( reason1 );
    
    MCE_SESSION_RECEIVE( iEvent, EMceItcNotifyReceived, CMceEvent::ETerminated, EMceItcMsgTypeSIPReply );
    EUNIT_ASSERT( iEventObserver->iEvent == NULL );
    EUNIT_ASSERT_EQUALS( iEventObserver->iStateChangedCount, 0 );
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    // EMceItcMsgTypeSIPReply && aEvent.Action() == EMceItcStateChanged  && !refer && !observer
    iManager->SetEventObserver( NULL );
    TUint32 code2 = 444;
    
    HBufC8* reason2 = KMceReason().AllocLC();
    CDesC8Array* hdrs2 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs2 );
    HBufC8* ct2 = KMceContentType().AllocLC();
    
    CMceMsgSIPReply* replyMsg2 = new( ELeave ) CMceMsgSIPReply( *reason2, code2, *hdrs2, *ct2 );
    CleanupStack::PushL( replyMsg2 );   
    replyMsg2->EncodeL(); 
    iStorage->Reset();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iEvent->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = replyMsg2->EncodeBuffer().Ptr(0).AllocL();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iEvent->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();
    
    CleanupStack::PopAndDestroy( replyMsg2 );
    CleanupStack::PopAndDestroy( ct2 );
    CleanupStack::PopAndDestroy( hdrs2 );
    CleanupStack::PopAndDestroy( reason2 );
    
    MCE_SESSION_RECEIVE( iEvent, EMceItcStateChanged, CMceEvent::ETerminated, EMceItcMsgTypeSIPReply );
    EUNIT_ASSERT( iEventObserver->iEvent == NULL );
    EUNIT_ASSERT_EQUALS( iEventObserver->iStateChangedCount, 0 );
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iManager->SetEventObserver( iEventObserver );
    
    // EMceItcMsgTypeSIPReply && aEvent.Action() == EMceItcStateChanged  && !refer && !container
    iManager->iContainer = NULL;
    TUint32 code3 = 433;
    
    HBufC8* reason3 = KMceReason().AllocLC();
    CDesC8Array* hdrs3 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs3 );
    HBufC8* ct3 = KMceContentType().AllocLC();
    
    CMceMsgSIPReply* replyMsg3 = new( ELeave ) CMceMsgSIPReply( *reason3, code3, *hdrs3, *ct3 );
    CleanupStack::PushL( replyMsg3 );
    replyMsg3->EncodeL(); 
    iStorage->Reset();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iEvent->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = replyMsg3->EncodeBuffer().Ptr(0).AllocL();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iEvent->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();
    
    CleanupStack::PopAndDestroy( replyMsg3 );
    CleanupStack::PopAndDestroy( ct3 );
    CleanupStack::PopAndDestroy( hdrs3 );
    CleanupStack::PopAndDestroy( reason3 );
    
    MCE_SESSION_RECEIVE( iEvent, EMceItcStateChanged, CMceEvent::ETerminated, EMceItcMsgTypeSIPReply );
    EUNIT_ASSERT( iEventObserver->iEvent == iEvent );
    EUNIT_ASSERT_EQUALS( iEventObserver->iStateChangedCount, 1 );
    EUNIT_ASSERT_EQUALS( iEventObserver->iStatusCode, 0 );
    EUNIT_ASSERT( iEventObserver->iHeaders == NULL );
    EUNIT_ASSERT( iEventObserver->iBody == NULL );
    EUNIT_ASSERT( iEventObserver->iContentType == NULL );
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iManager->iContainer = &iContainer;
    
    // EMceItcMsgTypeEvent && aEvent.Action() != EMceItcNotifyReceived
    TUint32 sesId = 123;
    TUint32 dlgId = 456;
    TUint32 interval = 180;
    
    CDesC8Array* hdrs4 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs4 );
    hdrs4->AppendL( KMceHeader1 );
    hdrs4->AppendL( KMceHeader2 );
    HBufC8* ct4 = KMceContentType().AllocLC();
    
    
    CMceMsgSIPEvent* eventMsg4 = new( ELeave ) CMceMsgSIPEvent( sesId,
                                                                dlgId,
                                                                EMceItcEventTypeSubscribe,
                                                                CMceRefer::ENoSuppression,
                                                                interval,
                                                                hdrs4,
                                                                ct4 );
    CleanupStack::Pop( ct4 );
    CleanupStack::Pop( hdrs4 );
    CleanupStack::PushL( eventMsg4 );
    eventMsg4->EncodeL();
    iStorage->Reset();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iEvent->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = eventMsg4->EncodeBuffer().Ptr(0).AllocL();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iEvent->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();
    
    CleanupStack::PopAndDestroy( eventMsg4 );
    
    MCE_SESSION_RECEIVE( iEvent, EMceItcStateChanged, CMceEvent::ETerminated, EMceItcMsgTypeEvent );
    EUNIT_ASSERT_EQUALS( iEventObserver->iStateChangedCount, 1 );
                  
    // EMceItcMsgTypeEvent && aEvent.Action() == EMceItcNotifyReceived && !container
    iManager->iContainer = NULL;
    CDesC8Array* hdrs5 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs5 );
    hdrs5->AppendL( KMceHeader1 );
    hdrs5->AppendL( KMceHeader2 );
    HBufC8* ct5 = KMceContentType().AllocLC();
    
    
    CMceMsgSIPEvent* eventMsg5 = new( ELeave ) CMceMsgSIPEvent( sesId,
                                                                dlgId,
                                                                EMceItcEventTypeSubscribe,
                                                                CMceRefer::ENoSuppression,
                                                                interval,
                                                                hdrs5,
                                                                ct5 );
    CleanupStack::Pop( ct5 );
    CleanupStack::Pop( hdrs5 );
    CleanupStack::PushL( eventMsg5 );
    eventMsg5->EncodeL();
    iStorage->Reset();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iEvent->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = eventMsg5->EncodeBuffer().Ptr(0).AllocL();
    iEvent->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iEvent->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();
    
    CleanupStack::PopAndDestroy( eventMsg5 );
    
    MCE_SESSION_RECEIVE( iEvent, EMceItcNotifyReceived, CMceEvent::ETerminated, EMceItcMsgTypeEvent );
    EUNIT_ASSERT_EQUALS( iEventObserver->iStateChangedCount, 1 );
    
    iManager->iContainer = &iContainer;
    }
    
// ----------------------------------------------------------------------------
// CMceEventTest::AssociatedSessionTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::AssociatedSessionTestL()
	{
	EUNIT_ASSERT( !iEvent->AssociatedSession() );
	}

// ----------------------------------------------------------------------------
// CMceEventTest::AssociatedEventsLTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::AssociatedEventsLTestL()
	{
	EUNIT_ASSERT( !iEvent->AssociatedEventsL() );
	}

// ----------------------------------------------------------------------------
// CMceEventTest::AssociatedRefersLTestL
// ----------------------------------------------------------------------------
//
void CMceEventTest::AssociatedRefersLTestL()
	{
	EUNIT_ASSERT( !iEvent->AssociatedRefersL() );
	}
