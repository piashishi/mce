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
#include "CMceInReferTest.h"

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


_LIT8( KContentSIPFragType, "message/sipfrag;version=2.0" );
_LIT8( KContentMsgOK, "200 OK");
        

// ----------------------------------------------------------------------------
// CMceInReferTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceInReferTest::setUpL()
    {
    
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManagerObserver = new (ELeave) CMceManagerObserverStub();
    iSessionObserver = new (ELeave) CMceSessionObserverStub();
    iStreamObserver = new (ELeave) CMceStreamObserverStub();
    iRtpObserver = new (ELeave) CMceRtpObserverStub();
    iInEventObserver = new (ELeave) CMceInEventObserverStub();
    iInReferObserver = new (ELeave) CMceInReferObserverStub();
    
    iManager = CMceManager::NewL( iUid, &iContainer );
    iEventObserver = new (ELeave) CMceEventObserverStub();
    iReferObserver = new (ELeave) CMceReferObserverStub();
    iManager->SetEventObserver( iEventObserver );
    iManager->SetReferObserver( iReferObserver );
    iManager->SetInReferObserver( iInReferObserver );
    }

// ----------------------------------------------------------------------------
// CMceInReferTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceInReferTest::tearDown()
    {
    if ( iInEvent )
        {
        MCE_TEST_DELETE( iInEvent );
        delete iInRefer;
        }   
    else if ( iInRefer )
        {
        delete iInRefer;
        iInRefer = NULL;
        }
    
    
    MCE_MAN_DELETE( iManager );

    delete iManagerObserver;
    delete iSessionObserver;
    delete iStreamObserver;
    delete iRtpObserver;
    delete iInEventObserver;
    delete iInReferObserver;
    delete iEventObserver;
    delete iReferObserver;
    
    delete iStorage;
    Dll::SetTls( NULL );
        
    }

// ----------------------------------------------------------------------------
// CMceInReferTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceInReferTest::suiteL()
    {
    CMceInReferTest* suite = new CMceInReferTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;                
    }
    
EUNIT_BEGIN_TEST_TABLE( 
    CMceInReferTest,
    "CMceInReferTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, AcceptTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, AcceptTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, RejectTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, RejectTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, RespondTest1L, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, RespondTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, RespondTest3L, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, RespondTest4L, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, RespondTest5L, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, RespondTest6L, tearDown )
MCE_EUNIT_TESTCASE("CMceInReferTest", setUpL, TerminateTestL, tearDown )
EUNIT_END_TEST_TABLE    
                      

#define MCE_INCOMING_REFER_SUPPR( manager )\
    if ( manager )\
        {\
\
		CMceMsgSIPEvent* msg = new (ELeave) CMceMsgSIPEvent();\
        CleanupStack::PushL( msg );\
        msg->iId = 757584;\
        msg->iDialogId = 78587675;\
        msg->iEventType = EMceItcEventTypeRefer;\
        msg->iEventHeader = _L8("WHAT").AllocL();\
        msg->iRecipient = _L8("WHAT").AllocL();\
        msg->iOriginator = _L8("WHAT").AllocL();\
        msg->iReferType = CMceRefer::ESuppressed;\
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
        manager->iEventReceiver->iIdsPckg().iSessionID = KMceTestSessionId1;\
        manager->iEventReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;\
        manager->iEventReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeEvent;\
\
        MCE_EVE_RECEIVE( manager, KErrNone );\
        iStorage->Reset();\
        manager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        manager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }

	
// ----------------------------------------------------------------------------
// CMceInReferTest::AcceptTestL
// ----------------------------------------------------------------------------
//
void CMceInReferTest::AcceptTestL()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    
    MCE_INCOMING_REFER( iManager );
    
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    //simple accept
    iInEvent = iInRefer->AcceptL();
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );

    //simple accept
    TRAPD(err,iInRefer->AcceptL());
    MCE_TEST_HANDLE_ALLOC_FAILURE( err ) 
    EUNIT_ASSERT( err == KErrNotReady );
    
    TInt aError;
    CActiveScheduler::RunIfReady(aError, CActive::EPriorityStandard );
    MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::EActive, KMceNotAssigned );
    iInEvent->TerminateL();
     //This is needed otherwise it will leave as KErrNotReady when trys to delete event
    iInEvent->iState = CMceEvent::ETerminated ;

    }

// ----------------------------------------------------------------------------
// CMceInReferTest::AcceptTest2L
// ----------------------------------------------------------------------------
//
void CMceInReferTest::AcceptTest2L()
    {
    // Suppressed
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_REFER_SUPPR( iManager );
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ESuppressed );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    //simple accept
    iInEvent = iInRefer->AcceptL();
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );
    EUNIT_ASSERT( !iInEvent );
    
    MCE_SES_RECEIVE( iInRefer, KErrCompletion );
    }

// ----------------------------------------------------------------------------
// CMceInReferTest::RejectTestL
// ----------------------------------------------------------------------------
//
void CMceInReferTest::RejectTestL()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_REFER( iManager );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    iInRefer->RejectL();
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );

    TRAPD(err,iInRefer->RejectL());
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )  
    EUNIT_ASSERT( err == KErrNotReady );

    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    MCE_SES_RECEIVE( iInEvent, KErrCompletion );
    iInEvent = NULL;
    }

// ----------------------------------------------------------------------------
// CMceInReferTest::RejectTest2L
// ----------------------------------------------------------------------------
//
void CMceInReferTest::RejectTest2L()
    {
    // Suppressed
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_REFER_SUPPR( iManager );
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ESuppressed );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    iInRefer->RejectL();
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );
    
    MCE_SES_RECEIVE( iInRefer, KErrCompletion );
    }


// ----------------------------------------------------------------------------
// CMceInReferTest::RespondTest1L
// ----------------------------------------------------------------------------
//
void CMceInReferTest::RespondTest1L()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_REFER( iManager );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    //simple accept
    iInEvent = iInRefer->RespondL(_L8("FINE"), 222);
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );

    //simple accept
    TRAPD(err,iInRefer->RespondL(_L8("FINE"), 222));
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )   
    EUNIT_ASSERT( err == KErrNotReady );
    //This is needed otherwise it will leave as KErrNotReady when trys to delete event
    iInRefer->iEvent->iState = CMceEvent::ETerminated ;

    }
    
// ----------------------------------------------------------------------------
// CMceInReferTest::RespondTest2L
// ----------------------------------------------------------------------------
//
void CMceInReferTest::RespondTest2L()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_REFER( iManager );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    iInEvent = iInRefer->RespondL(_L8("NOT_FINE"), 444);
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );
    EUNIT_ASSERT( !iInEvent );
    
    TRAPD(err,iInRefer->RespondL(_L8("NOT_FINE"), 444));
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )   
    EUNIT_ASSERT( err == KErrNotReady );
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    MCE_SES_RECEIVE( iInEvent, KErrCompletion );
    iInEvent = NULL;
    }

// ----------------------------------------------------------------------------
// CMceInReferTest::RespondTest3L
// ----------------------------------------------------------------------------
//
void CMceInReferTest::RespondTest3L()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_REFER( iManager );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    
    iInEvent = iInRefer->RespondL(_L8("NOT_FINE"), 444, headers );
    CleanupStack::Pop( headers );
    EUNIT_ASSERT( !iInEvent );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );
    
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    MCE_SES_RECEIVE( iInEvent, KErrCompletion );
    iInEvent = NULL;
    }
    
// ----------------------------------------------------------------------------
// CMceInReferTest::RespondTest4L
// ----------------------------------------------------------------------------
//
void CMceInReferTest::RespondTest4L()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_REFER( iManager );
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    HBufC8* contentType = KMceEventHeader().AllocLC();
    HBufC8* content = KMceEventHeader().AllocLC();
    // Leaving cases
    // content type, no content
    TRAPD( err, iInEvent = iInRefer->RespondL(_L8("NOT_FINE"), 444, NULL, contentType, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )   
    EUNIT_ASSERT( err == KErrArgument );
    EUNIT_ASSERT( iInRefer->State() == CMceEvent::EIdle );
    EUNIT_ASSERT( !iInEvent );
    
    // no content type, content
    TRAPD( err2, iInEvent = iInRefer->RespondL(_L8("NOT_FINE"), 444, NULL, NULL, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )  
    EUNIT_ASSERT( err2 == KErrArgument );
    EUNIT_ASSERT( iInRefer->State() == CMceEvent::EIdle );
    EUNIT_ASSERT( !iInEvent );
    
    // successfull
    iInEvent = iInRefer->RespondL(_L8("NOT_FINE"), 444, NULL, content, contentType);
    CleanupStack::Pop( content );
    CleanupStack::Pop( contentType );
    
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );
    EUNIT_ASSERT( !iInEvent );
    iInEvent = static_cast<CMceInEvent*>( iManager->Events()[0] );
    MCE_SES_RECEIVE( iInEvent, KErrCompletion );
    iInEvent = NULL;
    }

// ----------------------------------------------------------------------------
// CMceInReferTest::RespondTest5L
// ----------------------------------------------------------------------------
//
void CMceInReferTest::RespondTest5L()
    {
    // Suppressed
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_REFER_SUPPR( iManager );
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ESuppressed );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    //simple accept
    iInEvent = iInRefer->RespondL(_L8("FINE"), 222);
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );
    EUNIT_ASSERT( !iInEvent );
    
    MCE_SES_RECEIVE( iInRefer, KErrCompletion );
    }

// ----------------------------------------------------------------------------
// CMceInReferTest::RespondTest6L
// ----------------------------------------------------------------------------
//
void CMceInReferTest::RespondTest6L()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    MCE_INCOMING_REFER_SUPPR ( iManager );
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ESuppressed );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    HBufC8* contentType = KMceEventHeader().AllocLC();
    HBufC8* content = KMceEventHeader().AllocLC();
    
    // successfull
    iInEvent = iInRefer->RespondL(_L8("FINE"), 222, NULL, content, contentType);
    CleanupStack::Pop( content );
    CleanupStack::Pop( contentType );
    
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );
    EUNIT_ASSERT( !iInEvent );
    
    MCE_SES_RECEIVE( iInRefer, KErrCompletion );
    }
    
// ----------------------------------------------------------------------------
// CMceInReferTest::TerminateTestL
// ----------------------------------------------------------------------------
//
void CMceInReferTest::TerminateTestL()
    {
    EUNIT_ASSERT( iManager->Events().Count() == 0 );
    
    MCE_INCOMING_REFER( iManager );
    
    EUNIT_ASSERT( iManager->Events().Count() == 1 );
    EUNIT_ASSERT( iManager->Refers().Count() == 1 );
    
    iInRefer = static_cast<CMceInRefer*>( iManager->Refers()[0] );
    EUNIT_ASSERT( iInRefer->IsInRefer() );
    EUNIT_ASSERT( iInRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EIdle );
    
    //simple accept
    iInEvent = iInRefer->AcceptL();
    EUNIT_ASSERT( iInRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInRefer->Id() );

    //simple accept
    TRAPD(err,iInRefer->AcceptL());
    MCE_TEST_HANDLE_ALLOC_FAILURE( err ) 
    EUNIT_ASSERT( err == KErrNotReady );
    
    MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::EActive, KMceNotAssigned );
    HBufC8* sipfrag = KContentSIPFragType().AllocLC();
	
	HBufC8* messageOK = KContentMsgOK().AllocLC();
	iInEvent->TerminateL( NULL, sipfrag, messageOK );
	
	CleanupStack::Pop( messageOK );
	CleanupStack::Pop( sipfrag );
     //This is needed otherwise it will leave as KErrNotReady when trys to delete event
    iInEvent->iState = CMceEvent::ETerminated ;

	//terminate with headers
	MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::EActive, KMceNotAssigned );
	EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );

	CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 ); 
    iInEvent->TerminateL(headers);
	CleanupStack::Pop(headers);
	
	//terminate with subscription state headers
	MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::EActive, KMceNotAssigned );
	EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );

	CDesC8ArrayFlat* headers2 = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers2 );
    headers->AppendL( KMceSubscriptionStateHeader3 );
    headers->AppendL( KMceHeader2 ); 
    iInEvent->TerminateL( headers2 );
	CleanupStack::Pop( headers2 );


    // Leaving cases
    // content type, no content
	MCE_SESSION_STATECHANGE( iInEvent, CMceEvent::EActive, KMceNotAssigned );
	EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );

	HBufC8* contentType = KMceEventHeader().AllocLC();
    HBufC8* content = KMceEventHeader().AllocLC();
    
    
    TRAPD( err1, iInEvent->TerminateL( NULL, contentType, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )   
    EUNIT_ASSERT( err1 == KErrArgument );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );
    
    // no content type content
    TRAPD( err2, iInEvent->TerminateL( NULL, NULL, content) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )   
    EUNIT_ASSERT( err2 == KErrArgument );
    EUNIT_ASSERT( iInEvent->State() == CMceEvent::EActive );
    iInEvent->TerminateL(0, contentType, content);
    CleanupStack::Pop( content );
    CleanupStack::Pop( contentType );	
    }
