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
#include "CMceOutEventTest.h"

#include "mcestubs.h"
#include "mcetestdefs.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceeventreceiver.h"
#include "mcereferreceiver.h"
#include "mceeventmanagerreceiver.h"

#include "mceoutevent.h"
#include "mceaudiostream.h"
#include "mcertpsink.h"
#include "mcertpsource.h"
#include "mcemicsource.h"
#include "mcespeakersink.h"
#include "mcecomsession.h"
#include "mcecommediastream.h"
#include "mceserial.h"
#include "mceoutrefer.h"
#include "mceoutsession.h"



        

// ----------------------------------------------------------------------------
// CMceOutEventTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceOutEventTest::setUpL()
    {
    
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManager = CMceManager::NewL( iUid, &iContainer );
    
    iEventObserver = new (ELeave) CMceEventObserverStub();
    iManager->SetEventObserver( iEventObserver );
    }

// ----------------------------------------------------------------------------
// CMceOutEventTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceOutEventTest::tearDown()
    {

    if ( iOutEvent )
        {
        MCE_TEST_DELETE( iOutEvent );
        }
    
    
    MCE_MAN_DELETE( iManager );

    delete iEventObserver;
    delete iManagerObserver;
    delete iSessionObserver;
    delete iStreamObserver;
    delete iRtpObserver;
    
    delete iStorage;
    Dll::SetTls( NULL );
        
    }

// ----------------------------------------------------------------------------
// CMceOutEventTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceOutEventTest::suiteL()
    {
    CMceOutEventTest* suite = new CMceOutEventTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceOutEventTest,
    "CMceOutEventTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceOutEventTest", setUpL, SubscribeTest1L, tearDown )
MCE_EUNIT_TESTCASE("CMceOutEventTest", setUpL, SubscribeTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceOutEventTest", setUpL, SubscribeTest3L, tearDown )
MCE_EUNIT_TESTCASE("CMceOutEventTest", setUpL, UpdateTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceOutEventTest", setUpL, CancelTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceOutEventTest", setUpL, RemainTestL, tearDown )
EUNIT_END_TEST_TABLE 
	
// ----------------------------------------------------------------------------
// CMceOutEventTest::SubscribeTest1L
// ----------------------------------------------------------------------------
//
void CMceOutEventTest::SubscribeTest1L()
    {
    
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutEvent = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    EUNIT_ASSERT( iOutEvent->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutEvent->EventHeader().Compare( KMceEventHeader ) == 0 );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
    
    iOutEvent->SubscribeL();
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EPending );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::EActive, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    iOutEvent->TerminateL();
    
    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    TRAPD( err, iOutEvent->TerminateL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotReady );
    
    MCE_DELETE_PROFILE;    
    
    }

// ----------------------------------------------------------------------------
// CMceOutEventTest::SubscribeTest2L
// ----------------------------------------------------------------------------
//
void CMceOutEventTest::SubscribeTest2L()
    {
    
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutEvent = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    EUNIT_ASSERT( iOutEvent->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutEvent->EventHeader().Compare( KMceEventHeader ) == 0 );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
        
    HBufC8* contentType = KMceEventHeader().AllocLC();
    HBufC8* content = KMceEventHeader().AllocLC();
    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    
    // Leaving cases.
    // Content type, no content
    TRAPD( err, iOutEvent->SubscribeL( NULL, contentType, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT( err == KErrArgument );
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EIdle );
    
    // no content type, content
    TRAPD( err2, iOutEvent->SubscribeL( NULL, NULL, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT( err2 == KErrArgument );
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EIdle );
    
    // Successfull
    iOutEvent->SubscribeL( headers, contentType, content );
    CleanupStack::Pop(headers);
    CleanupStack::Pop(content);
    CleanupStack::Pop(contentType);
    
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EPending );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::EActive, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    iOutEvent->TerminateL();
    
    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    MCE_DELETE_PROFILE;    
    
    }


// ----------------------------------------------------------------------------
// CMceOutEventTest::SubscribeTest3L
// ----------------------------------------------------------------------------
//
void CMceOutEventTest::SubscribeTest3L()
    {
    
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutEvent = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    EUNIT_ASSERT( iOutEvent->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutEvent->EventHeader().Compare( KMceEventHeader ) == 0 );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
        
    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    iOutEvent->SubscribeL(headers);
	CleanupStack::Pop(headers);
    
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EPending );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::EActive, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    iOutEvent->TerminateL();
    
    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    TRAPD(err, iOutEvent->SubscribeL())
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT( err == KErrNotReady );
    MCE_DELETE_PROFILE;    
    
    }

// ----------------------------------------------------------------------------
// CMceOutEventTest::UpdateL
// ----------------------------------------------------------------------------
//
void CMceOutEventTest::UpdateTestL()
    {
    
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutEvent = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    EUNIT_ASSERT( iOutEvent->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutEvent->EventHeader().Compare( KMceEventHeader ) == 0 );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
        
    HBufC8* contentType = KMceEventHeader().AllocLC();
    HBufC8* content = KMceEventHeader().AllocLC();
    iOutEvent->SubscribeL(0, contentType, content);
    CleanupStack::Pop(content);
    CleanupStack::Pop(contentType);
    
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EPending );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::EActive, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    iOutEvent->UpdateL( KMceUpdateInterval );
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EPending );
    
    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::EActive, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
	content = _L8("CONTENT").AllocLC();
	contentType = _L8("CONTENT_TYPE").AllocLC();
    
    // Leaving cases.
    // Interval 0
    TRAPD( err, iOutEvent->UpdateL( 0 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT( err == KErrArgument );
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    
    // Content type, no content
    TRAPD( err2, iOutEvent->UpdateL( KMceUpdateInterval, NULL, contentType, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT( err2 == KErrArgument );
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    
    // no content type, content
    TRAPD( err3, iOutEvent->UpdateL( KMceUpdateInterval, NULL, NULL, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )
    EUNIT_ASSERT( err3 == KErrArgument );
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    
    // Successfull	
    iOutEvent->UpdateL(KMceUpdateInterval, NULL, contentType, content);
    CleanupStack::Pop(contentType);
    CleanupStack::Pop(content);

    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::EActive, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    iOutEvent->UpdateL(KMceUpdateInterval, headers);
	CleanupStack::Pop(headers);
	
    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::EActive, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    iOutEvent->TerminateL();
    
    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    
    TRAPD(err4, iOutEvent->UpdateL( KMceUpdateInterval ))
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 )
    EUNIT_ASSERT( err4 == KErrNotReady );

    MCE_DELETE_PROFILE;    
    
    }
// ----------------------------------------------------------------------------
// CMceOutEventTest::CancelTestL
// ----------------------------------------------------------------------------
//
void CMceOutEventTest::CancelTestL()
    {

	MCE_CREATE_PROFILE;

    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutEvent = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    EUNIT_ASSERT( iOutEvent->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutEvent->EventHeader().Compare( KMceEventHeader ) == 0 );
    
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    EUNIT_ASSERT( iStorage->iSessionId == 1 );
    
    iOutEvent->SubscribeL();
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EPending );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );

    MCE_DELETE_PROFILE;
    
    }
    
    
// ----------------------------------------------------------------------------
// CMceOutEventTest::RemainTestL
// ----------------------------------------------------------------------------
//
void CMceOutEventTest::RemainTestL()
    {
    // inside dialog
	MCE_CREATE_PROFILE;

    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    CMceEvent* event = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    CleanupStack::PushL( event );
    	
    CMceSession* session = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
	
    CMceRefer* refer = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo, CMceRefer::EMultipleRefer );
    CleanupStack::PushL( refer );
	
	CMceOutEvent* outEvent1= CMceOutEvent::NewL( *event, KMceEventHeader, 1000 );
	CleanupStack::PushL( outEvent1 );
	EUNIT_ASSERT( outEvent1->ProfileId() == event->ProfileId() );
	EUNIT_ASSERT( outEvent1->DialogId() == event->DialogId() );
	EUNIT_ASSERT( outEvent1->Recipient() == event->Recipient() );
	EUNIT_ASSERT( outEvent1->Originator() == event->Originator() );
	
	
    CMceOutEvent* outEvent2= CMceOutEvent::NewL( *session, KMceEventHeader, 1000 );
	CleanupStack::PushL( outEvent2 );
	EUNIT_ASSERT( outEvent2->ProfileId() == session->Profile() );
	EUNIT_ASSERT( outEvent2->DialogId() == session->DialogId() );
	EUNIT_ASSERT( outEvent2->Recipient() == session->Recipient() );
	EUNIT_ASSERT( outEvent2->Originator() == session->Originator() );
	
	
    CMceOutEvent* outEvent3= CMceOutEvent::NewL( *refer, KMceEventHeader, 1000 );
    CleanupStack::PushL( outEvent3 );
	EUNIT_ASSERT( outEvent3->ProfileId() == refer->ProfileId() );
	EUNIT_ASSERT( outEvent3->DialogId() == refer->DialogId() );
	EUNIT_ASSERT( outEvent3->Recipient() == refer->Recipient() );
	EUNIT_ASSERT( outEvent3->Originator() == refer->Originator() );
	
	   //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   	outEvent1->iState = CMceEvent::ETerminated ;
   	outEvent2->iState = CMceEvent::ETerminated ;
   	outEvent3->iState = CMceEvent::ETerminated ;
    event->iState = CMceEvent::EActive;
	CleanupStack::Pop( outEvent3 );
	CleanupStack::Pop( outEvent2 );
	CleanupStack::Pop( outEvent1 );
	CleanupStack::Pop( refer );
	CleanupStack::Pop( session );
	CleanupStack::Pop( event );
	
	MCE_TEST_DELETE( event );
	MCE_TEST_DELETE( session );
	MCE_TEST_DELETE( refer );
	MCE_TEST_DELETE( outEvent1 );
	MCE_TEST_DELETE( outEvent2 );
	MCE_TEST_DELETE( outEvent3 );
	
    MCE_DELETE_PROFILE;    
    }
