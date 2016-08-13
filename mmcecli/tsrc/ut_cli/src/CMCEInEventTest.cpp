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
#include "CMceInEventTest.h"

#include "mcestubs.h"
#include "mcetestdefs.h"
#include "mceclientserver.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceeventreceiver.h"
#include "mcereferreceiver.h"
#include "mceeventmanagerreceiver.h"

#include "mceinevent.h"
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
// CMceInEventTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceInEventTest::setUpL()
    {
    
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManagerObserver = new (ELeave) CMceManagerObserverStub();
    iSessionObserver = new (ELeave) CMceSessionObserverStub();
    iStreamObserver = new (ELeave) CMceStreamObserverStub();
    iRtpObserver = new (ELeave) CMceRtpObserverStub();
    iInEventObserver = new (ELeave) CMceInEventObserverStub();
    
    iManager = CMceManager::NewL( iUid, &iContainer );
    iManager->SetInSessionObserver( iManagerObserver );
    iManager->SetSessionObserver( iSessionObserver );
    iManager->SetMediaObserver( iStreamObserver );
    iManager->SetRtpObserver( iRtpObserver );
    iManager->SetInEventObserver( iInEventObserver );
    }

// ----------------------------------------------------------------------------
// CMceInEventTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceInEventTest::tearDown()
    {

    if ( iInEvent )
        {
        MCE_TEST_DELETE( iInEvent );
        }
    
    
    MCE_MAN_DELETE( iManager );

    delete iManagerObserver;
    delete iSessionObserver;
    delete iStreamObserver;
    delete iRtpObserver;
    delete iInEventObserver;
    
    delete iStorage;
    Dll::SetTls( NULL );
        
    }

// ----------------------------------------------------------------------------
// CMceInEventTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceInEventTest::suiteL()
    {
    CMceInEventTest* suite = new CMceInEventTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceInEventTest,
    "CMceInEventTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceInEventTest", setUpL, AcceptTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceInEventTest", setUpL, RejectTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceInEventTest", setUpL, RespondTest1L, tearDown )
MCE_EUNIT_TESTCASE("CMceInEventTest", setUpL, RespondTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceInEventTest", setUpL, RespondTest3L, tearDown )
MCE_EUNIT_TESTCASE("CMceInEventTest", setUpL, RespondTest4L, tearDown )
MCE_EUNIT_TESTCASE("CMceInEventTest", setUpL, NotifyTestL, tearDown )
EUNIT_END_TEST_TABLE

#define MCE_INCOMING_EVENT( manager, id )\
    if ( manager )\
        {\
\
        CMceMsgSIPEvent* msg = new (ELeave) CMceMsgSIPEvent();\
        CleanupStack::PushL( msg );\
        msg->iEventType = EMceItcEventTypeSubscribe;\
        msg->iEventHeader = _L8("WHAT").AllocL();\
        msg->iRecipient = _L8("WHAT").AllocL();\
        msg->iOriginator = _L8("WHAT").AllocL();\
        msg->iId = id;\
        msg->EncodeL();\
\
        iStorage->Reset();\
        manager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        manager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = msg->EncodeBuffer().Ptr(0).AllocL();\
        manager->iEventReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        iStorage->iContent = KMceMessageBody().AllocL();\
        manager->iEventReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();\
\
        CleanupStack::PopAndDestroy( msg );\
\
        manager->iEventReceiver->iIdsPckg().iAppUID = manager->AppUid().iUid;\
        manager->iEventReceiver->iIdsPckg().iSessionID = id;\
        manager->iEventReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;\
        manager->iEventReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeEvent;\
\
        MCE_EVE_RECEIVE( manager, KErrNone );\
        iStorage->Reset();\
        manager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        manager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }

	
// ----------------------------------------------------------------------------
// CMceInEventTest::SubscribeTest1L
// ----------------------------------------------------------------------------
//
void CMceInEventTest::AcceptTestL()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_EVENT( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    
   
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EIdle );
    EUNIT_ASSERT( iInEvent->IsInEvent() );
     
    //simple accept
    iInEvent->AcceptL();
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInEvent->Id() );

    //simple accept
    TRAPD(err,iInEvent->AcceptL());
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )  
    EUNIT_ASSERT( err == KErrNotReady );
    
      //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   	iInEvent->iState = CMceEvent::ETerminated ;
   
    }

// ----------------------------------------------------------------------------
// CMceInEventTest::SubscribeTest2L
// ----------------------------------------------------------------------------
//
void CMceInEventTest::RejectTestL()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_EVENT( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EIdle );
    EUNIT_ASSERT( iInEvent->IsInEvent() );
    
    //simple reject
    iInEvent->RejectL();
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::ETerminated);
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInEvent->Id() );

    
    TRAPD(err,iInEvent->RejectL());
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )   
    EUNIT_ASSERT( err == KErrNotReady );   
      //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   	iInEvent->iState = CMceEvent::ETerminated ;
    
    }


// ----------------------------------------------------------------------------
// CMceInEventTest::RespondTest1L
// ----------------------------------------------------------------------------
//
void CMceInEventTest::RespondTest1L()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_EVENT( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EIdle );
    EUNIT_ASSERT( iInEvent->IsInEvent() );
    
    iInEvent->RespondL(_L8("FINE"), 222);
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInEvent->Id() );

    //simple accept
    TRAPD(err,iInEvent->RespondL(_L8("FINE"), 222));
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )   
    EUNIT_ASSERT( err == KErrNotReady ); 
      //This is needed otherwise it will leave as KErrNotReady when trys to delete event
   	iInEvent->iState = CMceEvent::ETerminated ;
      
    }
    
// ----------------------------------------------------------------------------
// CMceInEventTest::RespondTest2L
// ----------------------------------------------------------------------------
//
void CMceInEventTest::RespondTest2L()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_EVENT( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EIdle );
    EUNIT_ASSERT( iInEvent->IsInEvent() );
    
    iInEvent->RespondL(_L8("NOT_FINE"), 444);
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInEvent->Id() );

    //simple accept
    TRAPD(err,iInEvent->RespondL(_L8("NOT_FINE"), 444));
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )   
    EUNIT_ASSERT( err == KErrNotReady );    
    }

// ----------------------------------------------------------------------------
// CMceInEventTest::RespondTest3L
// ----------------------------------------------------------------------------
//
void CMceInEventTest::RespondTest3L()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_EVENT( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EIdle );
    EUNIT_ASSERT( iInEvent->IsInEvent() );
    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    
    iInEvent->RespondL(_L8("NOT_FINE"), 444, headers );
    CleanupStack::Pop( headers );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInEvent->Id() );

    }


// ----------------------------------------------------------------------------
// CMceInEventTest::RespondTest4L
// ----------------------------------------------------------------------------
//
void CMceInEventTest::RespondTest4L()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_EVENT( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EIdle );
    EUNIT_ASSERT( iInEvent->IsInEvent() );
    
    HBufC8* contentType = KMceEventHeader().AllocLC();
    HBufC8* content = KMceEventHeader().AllocLC();
    // Leaving cases
    // content type, no content
    TRAPD( err, iInEvent->RespondL(_L8("NOT_FINE"), 444, NULL, contentType, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )  
    EUNIT_ASSERT( err == KErrArgument );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EIdle );
    
    // no content type, content
    TRAPD( err2, iInEvent->RespondL(_L8("NOT_FINE"), 444, NULL, NULL, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )   
    EUNIT_ASSERT( err2 == KErrArgument );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EIdle );
    
    // successfull
    iInEvent->RespondL(_L8("NOT_FINE"), 444, NULL, contentType, content );
    CleanupStack::Pop( content );
    CleanupStack::Pop( contentType );
    
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInEvent->Id() );

    }

// ----------------------------------------------------------------------------
// CMceInEventTest::NotifyTestL
// ----------------------------------------------------------------------------
//
void CMceInEventTest::NotifyTestL()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_EVENT( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EIdle );
    EUNIT_ASSERT( iInEvent->IsInEvent() );
    
    //simple accept
    iInEvent->AcceptL();
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInEvent->Id() );
    MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::EActive, KMceNotAssigned );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );
	iInEvent->NotifyL();
	EUNIT_ASSERT( iInEvent->State() == CMceEvent::EPending );
	MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::EActive, KMceNotAssigned );
	EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );
    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    iInEvent->NotifyL(headers);
	CleanupStack::Pop(headers);
	MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::EActive, KMceNotAssigned );
	EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );
	
    HBufC8* contentType = KMceEventHeader().AllocLC();
    HBufC8* content = KMceEventHeader().AllocLC();
    
    // Leaving cases
    // content type, no content
    TRAPD( err, iInEvent->NotifyL( NULL, contentType, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )   
    EUNIT_ASSERT( err == KErrArgument );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );
    
    // no content type content
    TRAPD( err2, iInEvent->NotifyL( NULL, NULL, content) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )   
    EUNIT_ASSERT( err2 == KErrArgument );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );
    
    // Successfull
    iInEvent->NotifyL(0, contentType, content);
    CleanupStack::Pop(content);
    CleanupStack::Pop(contentType);
    MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::EActive, KMceNotAssigned );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );
    
    iInEvent->TerminateL();
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInEvent->Id() );
    
    MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::ETerminated, KMceNotAssigned );
	EUNIT_ASSERT( iInEvent->State() == CMceEvent::ETerminated );
	
    TRAPD(err3,iInEvent->NotifyL());
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )   
    EUNIT_ASSERT( err3 == KErrNotReady );    
    }
