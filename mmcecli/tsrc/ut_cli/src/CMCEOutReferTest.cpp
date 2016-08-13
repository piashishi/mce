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
#include "CMceOutReferTest.h"

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
#include "mceevent.h"


#define MCE_SESSION_NOTIFY( session, state, type )\
    MCE_SESSION_RECEIVE( session, EMceItcNotifyReceived, state, type )


#define MCE_ACCEPT_REFER( session, sesObserver )\
    if ( session )\
        {\
\
        HBufC8* reason = KMceReason().AllocLC();\
        CDesC8Array* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        CleanupStack::PushL( headers );\
        headers->AppendL( KMceHeader1 );\
        headers->AppendL( KMceHeader2 );\
        HBufC8* ct = KMceContentType().AllocLC();\
\
        CMceMsgSIPReply* replyMsg = new (ELeave) CMceMsgSIPReply( *reason, KMce200OK, *headers, *ct );\
        CleanupStack::PushL( replyMsg );\
        replyMsg->EncodeL();\
\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = replyMsg->EncodeBuffer().Ptr(0).AllocL();\
        session->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        iStorage->iContent = KMceMessageBody().AllocL();\
        session->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();\
\
        CleanupStack::PopAndDestroy( replyMsg );\
        CleanupStack::PopAndDestroy( ct );\
        CleanupStack::PopAndDestroy( headers );\
        CleanupStack::PopAndDestroy( reason );\
\
        MCE_SESSION_STATECHANGE( session, CMceEvent::EActive, EMceItcMsgTypeSIPReply );\
        EUNIT_ASSERT( session->State() == CMceRefer::EAccepted );\
        EUNIT_ASSERT( sesObserver->iStateChangedCount == 1 );\
        EUNIT_ASSERT( sesObserver->iStatusCode == KMce200OK );\
        EUNIT_ASSERT( sesObserver->iReasonPhrase->Compare( KMceReason ) == 0 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaCount() == 2 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaPoint(0).Compare( KMceHeader1 ) == 0 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaPoint(1).Compare( KMceHeader2 ) == 0 );\
        EUNIT_ASSERT( sesObserver->iBody->Compare( KMceMessageBody ) == 0 );\
        EUNIT_ASSERT( sesObserver->iContentType->Compare( KMceContentType ) == 0 );\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }

#define MCE_ACCEPT_REFER_SUPPR( refer, referObserver )\
    if ( refer )\
        {\
\
        HBufC8* reason = KMceReason().AllocLC();\
        CDesC8Array* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        CleanupStack::PushL( headers );\
        headers->AppendL( KMceHeader1 );\
        headers->AppendL( KMceHeader2 );\
        HBufC8* empty = KMceEmpty().AllocLC();\
\
        CMceMsgSIPReply* replyMsg = new (ELeave) CMceMsgSIPReply( *reason, KMce202Accepted, *headers, *empty );\
        CleanupStack::PushL( replyMsg );\
        replyMsg->EncodeL();\
\
        iStorage->Reset();\
        refer->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        refer->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = replyMsg->EncodeBuffer().Ptr(0).AllocL();\
        refer->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        iStorage->iContent = KMceMessageBody().AllocL();\
        refer->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();\
\
        CleanupStack::PopAndDestroy( replyMsg );\
        CleanupStack::PopAndDestroy( empty );\
        CleanupStack::PopAndDestroy( headers );\
        CleanupStack::PopAndDestroy( reason );\
\
        MCE_SESSION_STATECHANGE( refer, CMceRefer::ETerminated, EMceItcMsgTypeSIPReply );\
        EUNIT_ASSERT( refer->State() == CMceRefer::ETerminated );\
        EUNIT_ASSERT( referObserver->iStateChangedCount == 1 );\
        EUNIT_ASSERT( referObserver->iStatusCode == KMce202Accepted );\
        EUNIT_ASSERT( referObserver->iReasonPhrase->Compare( KMceReason ) == 0 );\
        EUNIT_ASSERT( referObserver->iHeaders->MdcaCount() == 2 );\
        EUNIT_ASSERT( referObserver->iHeaders->MdcaPoint(0).Compare( KMceHeader1 ) == 0 );\
        EUNIT_ASSERT( referObserver->iHeaders->MdcaPoint(1).Compare( KMceHeader2 ) == 0 );\
        EUNIT_ASSERT( referObserver->iBody->Compare( KMceMessageBody ) == 0 );\
        iStorage->Reset();\
        refer->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        refer->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }

#define MCE_REJECT_REFER( session, sesObserver )\
    if ( session )\
        {\
\
        HBufC8* reason = KMceReason2().AllocLC();\
        CDesC8Array* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        CleanupStack::PushL( headers );\
        headers->AppendL( KMceHeader1 );\
        headers->AppendL( KMceHeader2 );\
        HBufC8* empty = KMceEmpty().AllocLC();\
\
        CMceMsgSIPReply* replyMsg = new (ELeave) CMceMsgSIPReply( *reason, KMce444NOK, *headers, *empty );\
        CleanupStack::PushL( replyMsg );\
        replyMsg->EncodeL();\
\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = replyMsg->EncodeBuffer().Ptr(0).AllocL();\
        session->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        iStorage->iContent = KMceMessageBody().AllocL();\
        session->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();\
\
        CleanupStack::PopAndDestroy( replyMsg );\
        CleanupStack::PopAndDestroy( empty );\
        CleanupStack::PopAndDestroy( headers );\
        CleanupStack::PopAndDestroy( reason );\
\
        MCE_SESSION_STATECHANGE( session, CMceRefer::ETerminated, EMceItcMsgTypeSIPReply );\
        EUNIT_ASSERT( session->State() == CMceRefer::ETerminated );\
        EUNIT_ASSERT( sesObserver->iStateChangedCount == 1 );\
        EUNIT_ASSERT( sesObserver->iStatusCode == KMce444NOK );\
        EUNIT_ASSERT( sesObserver->iReasonPhrase->Compare( KMceReason2 ) == 0 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaCount() == 2 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaPoint(0).Compare( KMceHeader1 ) == 0 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaPoint(1).Compare( KMceHeader2 ) == 0 );\
        EUNIT_ASSERT( sesObserver->iBody->Compare( KMceMessageBody ) == 0 );\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }
        
        
        
#define MCE_RECEIVE_NOTIFY( session, sesObserver )\
    if ( session )\
        {\
      	HBufC8* contentType = KMceReason2().AllocLC();\
        CDesC8Array* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        CleanupStack::PushL( headers );\
        headers->AppendL( KMceHeader1 );\
        headers->AppendL( KMceHeader2 );\
        HBufC8* empty1 = KMceEmpty().AllocLC();\
        HBufC8* empty2 = KMceEmpty().AllocLC();\
        HBufC8* empty3 = KMceEmpty().AllocLC();\
        HBufC8* empty4 = KMceEmpty().AllocLC();\
\
        CMceMsgSIPEvent* eventMsg = new (ELeave) CMceMsgSIPEvent(\
        0,\
        0,\
        EMceItcEventTypeSubscribe,\
        empty1,\
        empty2,\
        empty3,\
        empty4,\
        CMceRefer::ENoSuppression,\
        0,\
        headers,\
        contentType);\
\
        CleanupStack::Pop( empty4 );\
        CleanupStack::Pop( empty3 );\
        CleanupStack::Pop( empty2 );\
        CleanupStack::Pop( empty1 );\
        CleanupStack::Pop( headers );\
        CleanupStack::Pop( contentType );\
\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        CleanupStack::PushL( eventMsg );\
		eventMsg->EncodeL();\
        iStorage->iContext = eventMsg->EncodeBuffer().Ptr(0).AllocL();\
        session->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        iStorage->iContent = KMceMessageBody().AllocL();\
        session->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();\
\
        CleanupStack::PopAndDestroy( eventMsg );\
\
        MCE_SESSION_NOTIFY( session, CMceRefer::EAccepted, EMceItcMsgTypeEvent );\
\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaCount() == 2 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaPoint(0).Compare( KMceHeader1 ) == 0 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaPoint(1).Compare( KMceHeader2 ) == 0 );\
        EUNIT_ASSERT( sesObserver->iBody->Compare( KMceMessageBody ) == 0 );\
\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }
        
        
        
// ----------------------------------------------------------------------------
// CMceOutReferTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceOutReferTest::setUpL()
    {
    
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManager = CMceManager::NewL( iUid, &iContainer );
    iEventObserver = new (ELeave) CMceEventObserverStub();
    iReferObserver = new (ELeave) CMceReferObserverStub();
    iManager->SetEventObserver( iEventObserver );
    iManager->SetReferObserver( iReferObserver );
    
    }

// ----------------------------------------------------------------------------
// CMceOutReferTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceOutReferTest::tearDown()
    {

    if ( iOutEvent )
        {
        MCE_TEST_DELETE( iOutEvent );
        delete iOutRefer;
        iOutRefer = 0;
        }
    else if ( iOutRefer )
        {
        MCE_TEST_DELETE( iOutRefer );
        }
    
    MCE_MAN_DELETE( iManager );

    delete iReferObserver;
    iReferObserver = 0;
    delete iEventObserver;
    iEventObserver = 0;
    delete iManagerObserver;
    iManagerObserver = 0;
    delete iSessionObserver;
    iSessionObserver = 0;
    delete iStreamObserver;
    iStreamObserver = 0;
    delete iRtpObserver;
    iRtpObserver = 0;
    
    delete iStorage;
    Dll::SetTls( NULL );
        
    }

// ----------------------------------------------------------------------------
// CMceOutReferTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceOutReferTest::suiteL()
    {
    CMceOutReferTest* suite = new CMceOutReferTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceOutReferTest,
    "CMceOutReferTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceOutReferTest", setUpL, ReferTest1L, tearDown )
MCE_EUNIT_TESTCASE("CMceOutReferTest", setUpL, ReferTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceOutReferTest", setUpL, ReferTest3L, tearDown )
MCE_EUNIT_TESTCASE("CMceOutReferTest", setUpL, ReferTest4L, tearDown )
MCE_EUNIT_TESTCASE("CMceOutReferTest", setUpL, ReferTest5L, tearDown )
MCE_EUNIT_TESTCASE("CMceOutReferTest", setUpL, NotifyTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceOutReferTest", setUpL, CancelTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceOutReferTest", setUpL, RemainTestL, tearDown )
EUNIT_END_TEST_TABLE 
	
// ----------------------------------------------------------------------------
// CMceOutReferTest::ReferTest1L
// ----------------------------------------------------------------------------
//
void CMceOutReferTest::ReferTest1L()
    {
    
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutRefer = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo );
    EUNIT_ASSERT( !iOutRefer->IsInRefer() );
    EUNIT_ASSERT( iOutRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iOutRefer->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
    
    iOutEvent = iOutRefer->ReferL();
    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

	MCE_ACCEPT_REFER(iOutEvent, iReferObserver);
	EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EAccepted );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );
    
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    iStorage->Reset();
    iOutEvent->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutEvent->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    TRAPD( err, iOutEvent->TerminateL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotSupported );
    
    MCE_SESSION_STATECHANGE( iOutEvent, CMceEvent::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceRefer::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    MCE_DELETE_PROFILE;    
    
    }

// ----------------------------------------------------------------------------
// CMceOutReferTest::ReferTest2L
// ----------------------------------------------------------------------------
//
void CMceOutReferTest::ReferTest2L()
    {
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );
    HBufC8* originator = KMceOriginator().AllocLC();
    iOutRefer = CMceOutRefer::NewL( *iManager, 
                                    *profile, 
                                    KMceRecipient, 
                                    KMceReferTo,
                                    CMceRefer::ENoSuppression,
                                    originator );
    CleanupStack::Pop( originator );
    EUNIT_ASSERT( !iOutRefer->IsInRefer() );
    EUNIT_ASSERT( iOutRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iOutRefer->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutRefer->Originator().Compare( KMceOriginator ) == 0 );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
    
    iOutEvent = iOutRefer->ReferL();
    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );
    
	MCE_REJECT_REFER(iOutEvent, iReferObserver);
	       
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    MCE_DELETE_PROFILE;    
    
    }

// ----------------------------------------------------------------------------
// CMceOutReferTest::ReferTest3L
// ----------------------------------------------------------------------------
//
void CMceOutReferTest::ReferTest3L()
    {
    
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutRefer = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo );
    EUNIT_ASSERT( !iOutRefer->IsInRefer() );
    EUNIT_ASSERT( iOutRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iOutRefer->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
    
    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    
    iOutEvent = iOutRefer->ReferL(headers);
	CleanupStack::Pop(headers);
    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

	MCE_ACCEPT_REFER(iOutEvent, iReferObserver);

    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EAccepted );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );
    
    MCE_SESSION_STATECHANGE( iOutEvent, CMceRefer::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    MCE_DELETE_PROFILE;        
    }


// ----------------------------------------------------------------------------
// CMceOutReferTest::ReferTest4L
// ----------------------------------------------------------------------------
//
void CMceOutReferTest::ReferTest4L()
    {
    
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutRefer = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo );
    EUNIT_ASSERT( !iOutRefer->IsInRefer() );
    EUNIT_ASSERT( iOutRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iOutRefer->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
	HBufC8* content = _L8("CONTENT").AllocLC();
	HBufC8* contentType = _L8("CONTENT_TYPE").AllocLC();
	
	// Leaving cases
	// content type, no content
	TRAPD( err, iOutEvent = iOutRefer->ReferL(NULL, contentType, NULL ) );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT( err == KErrArgument );
	EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EIdle );
	EUNIT_ASSERT( !iOutEvent );
	// no content type, content
    TRAPD( err2, iOutEvent = iOutRefer->ReferL(NULL, NULL, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
	EUNIT_ASSERT( err2 == KErrArgument );
	EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EIdle );
	EUNIT_ASSERT( !iOutEvent );
	
	// Successful
    iOutEvent = iOutRefer->ReferL(NULL, contentType, content);
    CleanupStack::Pop(contentType);
    CleanupStack::Pop(content);
    
    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

	MCE_ACCEPT_REFER(iOutEvent, iReferObserver);

    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EAccepted );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );
    
    MCE_SESSION_STATECHANGE( iOutEvent, CMceRefer::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    // wrong state
    TRAPD( err3, iOutRefer->ReferL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )
    EUNIT_ASSERT( err3 == KErrNotReady );
    
    MCE_DELETE_PROFILE;        
    }

// ----------------------------------------------------------------------------
// CMceOutReferTest::ReferTest5L
// ----------------------------------------------------------------------------
//
void CMceOutReferTest::ReferTest5L()
    {
    // Suppressed
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutRefer = CMceOutRefer::NewL( *iManager, 
                                    *profile, 
                                    KMceRecipient, 
                                    KMceReferTo,
                                    CMceRefer::ESuppressed );
    EUNIT_ASSERT( !iOutRefer->IsInRefer() );
    EUNIT_ASSERT( iOutRefer->Type() == CMceRefer::ESuppressed );
    EUNIT_ASSERT( iOutRefer->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
	
	// Successful
    iOutEvent = iOutRefer->ReferL();
    EUNIT_ASSERT( !iOutEvent );
    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

	MCE_ACCEPT_REFER_SUPPR(iOutRefer, iReferObserver);

    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::ETerminated );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );
    
    MCE_DELETE_PROFILE;        
    }


// ----------------------------------------------------------------------------
// CMceOutReferTest::NotifyTestL
// ----------------------------------------------------------------------------
//
void CMceOutReferTest::NotifyTestL()
    {
    MCE_CREATE_PROFILE;
        
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutRefer = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo );
    EUNIT_ASSERT( !iOutRefer->IsInRefer() );
    EUNIT_ASSERT( iOutRefer->Type() == CMceRefer::ENoSuppression );
    EUNIT_ASSERT( iOutRefer->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
    
    iOutEvent = iOutRefer->ReferL();
    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EPending );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );

	MCE_ACCEPT_REFER(iOutEvent, iReferObserver);
    EUNIT_ASSERT( iOutRefer->State() == CMceRefer::EAccepted );
    EUNIT_ASSERT( iOutRefer->Id() == 1 );
    
    EUNIT_ASSERT( iOutEvent->State() == CMceEvent::EActive );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    
    iStorage->Reset();
    iOutEvent->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iOutEvent->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    MCE_RECEIVE_NOTIFY(iOutEvent, iEventObserver);

    MCE_SESSION_STATECHANGE( iOutEvent, CMceRefer::ETerminated, KMceNotAssigned );

    EUNIT_ASSERT( iOutEvent->State() == CMceRefer::ETerminated );
    EUNIT_ASSERT( iOutEvent->Id() == 1 );
    MCE_DELETE_PROFILE;        
    }
    
// ----------------------------------------------------------------------------
// CMceOutReferTest::CancelTestL
// ----------------------------------------------------------------------------
//
void CMceOutReferTest::CancelTestL()
    {

    }
    
    
// ----------------------------------------------------------------------------
// CMceOutReferTest::RemainTestL
// ----------------------------------------------------------------------------
//
void CMceOutReferTest::RemainTestL()
    {
    // Create instances inside dialog
	MCE_CREATE_PROFILE;

    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    CMceEvent* event = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    CleanupStack::PushL( event );
    	
    CMceSession* session = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
	
    CMceRefer* refer = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo, CMceRefer::EMultipleRefer );
    CleanupStack::PushL(refer);
		
	// with event	
    CMceOutRefer* outRefer1= CMceOutRefer::NewL( *event, KMceReferTo, CMceRefer::ESuppressed );
	CleanupStack::PushL(outRefer1);
	EUNIT_ASSERT( outRefer1->ProfileId() == event->ProfileId() );
	EUNIT_ASSERT( outRefer1->DialogId() == event->DialogId() );
	EUNIT_ASSERT( outRefer1->Recipient() == event->Recipient() );
	EUNIT_ASSERT( outRefer1->Originator() == event->Originator() );
	EUNIT_ASSERT( outRefer1->Type() == CMceRefer::ESuppressed );
	
	// with session
    CMceOutRefer* outRefer2= CMceOutRefer::NewL( *session, KMceReferTo, CMceRefer::EMultipleRefer );
    CleanupStack::PushL(outRefer2);
	EUNIT_ASSERT( outRefer2->ProfileId() == session->Profile() );
	EUNIT_ASSERT( outRefer2->DialogId() == session->DialogId() );
	EUNIT_ASSERT( outRefer2->Recipient() == session->Recipient() );
	EUNIT_ASSERT( outRefer2->Originator() == session->Originator() );
	EUNIT_ASSERT( outRefer2->Type() == CMceRefer::EMultipleRefer );
	
    // with refer
    CMceOutRefer* outRefer3= CMceOutRefer::NewL( *refer, KMceReferTo, CMceRefer::ESuppressed );
    CleanupStack::PushL(outRefer3);
	EUNIT_ASSERT( outRefer3->ProfileId() == refer->ProfileId() );
	EUNIT_ASSERT( outRefer3->DialogId() == refer->DialogId() );
	EUNIT_ASSERT( outRefer3->Recipient() == refer->Recipient() );
	EUNIT_ASSERT( outRefer3->Originator() == refer->Originator() );
	EUNIT_ASSERT( outRefer3->Type() == CMceRefer::ESuppressed );
	
	
	event->iState = CMceEvent::EActive;
    
    
	CleanupStack::Pop( outRefer3 );
	CleanupStack::Pop( outRefer2 );
	CleanupStack::Pop( outRefer1 );
    CleanupStack::Pop( refer );
    CleanupStack::Pop( session );
    CleanupStack::Pop( event );
    
	
    MCE_TEST_DELETE( outRefer3 );
	MCE_TEST_DELETE( outRefer2 );
	MCE_TEST_DELETE( outRefer1 );
	MCE_TEST_DELETE( refer );
	MCE_TEST_DELETE( session );
	MCE_TEST_DELETE( event );
    
    MCE_DELETE_PROFILE;
    }
