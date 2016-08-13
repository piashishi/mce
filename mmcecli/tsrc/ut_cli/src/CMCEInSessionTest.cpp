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
#include "CMceInSessionTest.h"
#include "CMceSessionTest.h"
#include "mcestubs.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceitcsender.h"
#include "mceinsession.h"
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



// ----------------------------------------------------------------------------
// CMceInSessionTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceInSessionTest::setUpL()
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
    iManager->SetSessionObserver( iSessionObserver );
    iManager->SetMediaObserver( iStreamObserver );
    iManager->SetRtpObserver( iRtpObserver );
    }

// ----------------------------------------------------------------------------
// CMceInSessionTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceInSessionTest::tearDown()
    {
    if ( iInSession )
        {
        MCE_TEST_DELETE( iInSession );
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
// CMceInSessionTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceInSessionTest::suiteL()
    {
    CMceInSessionTest* suite = new CMceInSessionTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceInSessionTest,
    "CMceInSessionTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceInSessionTest", setUpL, AcceptTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceInSessionTest", setUpL, RejectTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceInSessionTest", setUpL, RingTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceInSessionTest", setUpL, IncomingTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceInSessionTest", setUpL, ZombieTestsL, tearDown )
MCE_EUNIT_TESTCASE("CMceInSessionTest", setUpL, RespondLTestL, tearDown )
EUNIT_END_TEST_TABLE    

// ----------------------------------------------------------------------------
// CMceInSessionTest::AcceptTestL
// ----------------------------------------------------------------------------
//
void CMceInSessionTest::AcceptTestL()
    {
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iInSession->Id() == KMceTestSessionId1 );

    //update
    iInSession->UpdateL();
    EUNIT_ASSERT( iInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );

    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EProceeding, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EProceeding );
    
    //ring
    iInSession->RingL();
    EUNIT_ASSERT( iInSession->State() == CMceSession::EProceeding );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );

    //siple accept
    iInSession->AcceptL();
    EUNIT_ASSERT( iInSession->State() == CMceSession::EAnswering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );
    
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EEstablished );
    
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );

    MCE_TEST_DELETE( iInSession );
    
//detailed
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 + 1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iInSession->Id() == KMceTestSessionId1 + 1 );

    //update
    iInSession->UpdateL();
    EUNIT_ASSERT( iInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );
    

    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EProceeding, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EProceeding );
    
    //ring
    iInSession->RingL();
    EUNIT_ASSERT( iInSession->State() == CMceSession::EProceeding );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );

    //leaving cases
    //too small
    TRAPD( err1, iInSession->AcceptL( KMceReason, 199 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )   
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    //too big
    TRAPD( err2, iInSession->AcceptL( KMceReason, 300 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )   
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    // successfull
    //detailed accept without headers
    iInSession->AcceptL( KMceReason, 200 );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EAnswering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );
    
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EEstablished );
    
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );

    MCE_TEST_DELETE( iInSession );

    }
    
// ----------------------------------------------------------------------------
// CMceInSessionTest::RejectTestL
// ----------------------------------------------------------------------------
//
void CMceInSessionTest::RejectTestL()
    {
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iInSession->Id() == KMceTestSessionId1 );
    
    //siple reject
    iInSession->RejectL();
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );
        
    MCE_TEST_DELETE( iInSession );

//detailed
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 + 1  );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iInSession->Id() == KMceTestSessionId1 + 1);
    

    //detailed reject without headers
    iInSession->RejectL( KMceReason, 488 );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );
        
    MCE_TEST_DELETE( iInSession );

//detailed
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 + 2 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iInSession->Id() == KMceTestSessionId1 + 2 );

    //detailed reject
    //Leaving cases
    HBufC8* ct = KMceContentType().AllocLC();
    HBufC8* c = KMceMessageBody().AllocLC();
    
    // content type && no content
    TRAPD( err1, iInSession->RejectL( KMceReason, 444, NULL, ct, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )   
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    // no content type && content
    TRAPD( err2, iInSession->RejectL( KMceReason, 444, NULL, NULL, c ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )  
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    // too small code
    TRAPD( err3, iInSession->RejectL( KMceReason, 299 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )   
    EUNIT_ASSERT_EQUALS( err3, KErrArgument );
    
    // too big code
    TRAPD( err4, iInSession->RejectL( KMceReason, 700 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 )  
    EUNIT_ASSERT_EQUALS( err4, KErrArgument );
    
    CleanupStack::PopAndDestroy( c );
    CleanupStack::PopAndDestroy( ct );

    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );
    
    iInSession->RejectL( KMceReason, 566, headers );
    CleanupStack::Pop( headers );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );
    }

// ----------------------------------------------------------------------------
// CMceInSessionTest::RingTestL
// ----------------------------------------------------------------------------
//
void CMceInSessionTest::RingTestL()
    {
    // Cover the leaving cases.
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iInSession->Id() == KMceTestSessionId1 );

    //update
    iInSession->UpdateL();
    EUNIT_ASSERT( iInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );

    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EProceeding, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EProceeding );
    
    HBufC8* ct = KMceContentType().AllocLC();
    HBufC8* c = KMceMessageBody().AllocLC();
    
    // Actual test cases
    // content type && no content
    TRAPD( err1, iInSession->RingL( NULL, ct, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )   
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    // no content type && content
    TRAPD( err2, iInSession->RingL( NULL, NULL, c ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )   
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    CleanupStack::PopAndDestroy( c );
    CleanupStack::PopAndDestroy( ct );
    }

// ----------------------------------------------------------------------------
// CMceInSessionTest::IncomingTestL
// ----------------------------------------------------------------------------
//
void CMceInSessionTest::IncomingTestL()
    {
    // Incoming session, no in session observer
    iManager->SetInSessionObserver( NULL );
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    }

// ----------------------------------------------------------------------------
// CMceInSessionTest::ZombieTestsL
// ----------------------------------------------------------------------------
//
void CMceInSessionTest::ZombieTestsL()
    {
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iInSession->Id() == KMceTestSessionId1 );

    //update
    iInSession->UpdateL();
    EUNIT_ASSERT( iInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );

    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EProceeding, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EProceeding );
    
    //siple accept
    iInSession->AcceptL();
    EUNIT_ASSERT( iInSession->State() == CMceSession::EAnswering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iInSession->Id() );
    
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EEstablished );
    
    // Incoming update
    MCE_INCOMING_UPDATE2( iInSession );
    
    EUNIT_ASSERT( iInSession->IsZombie() );
    // Actual tests
    // RingL
    TRAPD( err1, iInSession->RingL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )   
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    // AcceptL
    TRAPD( err2, iInSession->AcceptL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )  
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    TRAPD( err3, iInSession->AcceptL( KMceReason, 222 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )   
    EUNIT_ASSERT_EQUALS( err3, KErrArgument );
    
    // RejectL
    TRAPD( err4, iInSession->RejectL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 )   
    EUNIT_ASSERT_EQUALS( err4, KErrArgument );
    
    TRAPD( err5, iInSession->AcceptL( KMceReason, 444 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err5 )   
    EUNIT_ASSERT_EQUALS( err5, KErrArgument );
    
    
    EUNIT_ASSERT( iManagerObserver->iSession != NULL );
    delete iInSession;
    iInSession = static_cast< CMceInSession* >( iManagerObserver->iSession );
    iManagerObserver->iSession = NULL;
    }

// ----------------------------------------------------------------------------
// CMceInSessionTest::RespondLTestL
// ----------------------------------------------------------------------------
//
void CMceInSessionTest::RespondLTestL()
    {
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );


    // Make this a zombie session
    delete iInSession->iReceiver;
    iInSession->iReceiver = NULL;
    
    delete iInSession->iSender;
    iInSession->iSender = NULL;
    
	TRAPD( err, iInSession->RespondL( KNullDesC8, 10, NULL, NULL, NULL ) );
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
    }
