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
#include "mcesecureinsessiontest.h"
#include "CMceSessionTest.h"
#include "mcestubs.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceinsession.h"
#include "mcesecureinsession.h"
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
// CMceSecureInSessionTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceSecureInSessionTest::setUpL()
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
// CMceSecureInSessionTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceSecureInSessionTest::tearDown()
    {

    if ( iSecureInSession )
        {
        MCE_TEST_DELETE( iSecureInSession );
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
// CMceSecureInSessionTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceSecureInSessionTest::suiteL()
    {
    CMceSecureInSessionTest* suite = new CMceSecureInSessionTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceSecureInSessionTest,
    "CMceSecureInSessionTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceSecureInSessionTest", setUpL, TypeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureInSessionTest", setUpL, CryptoContextsTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureInSessionTest", setUpL, NewLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureInSessionTest", setUpL, AcceptTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureInSessionTest", setUpL, RejectTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureInSessionTest", setUpL, RingTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureInSessionTest", setUpL, IncomingTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureInSessionTest", setUpL, ZombieTestsL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceSecureInSessionTest::TypeTestL
// ----------------------------------------------------------------------------
//
void CMceSecureInSessionTest::TypeTestL()
	{
	iSecureInSession = CMceSecureInSession::NewL();
    EUNIT_ASSERT(iSecureInSession->Type() == KMceSessionSecure);
	delete iSecureInSession; iSecureInSession = NULL;
	}

// ----------------------------------------------------------------------------
// CMceSecureInSessionTest::CryptoContextsTestL
// ----------------------------------------------------------------------------
//
void CMceSecureInSessionTest::CryptoContextsTestL()
	{
	iSecureInSession = CMceSecureInSession::NewL();
	
    //Set crypto context. Use granularity 1 in tests to force alloc each time.
    RArray<TMceCryptoContext> array( 1 ); 
    array.AppendL( EAES_CM_128_HMAC_SHA1_32 );
    array.AppendL( EAES_CM_128_HMAC_SHA1_80 );

    iSecureInSession->SetCryptoContextsL( array );
    EUNIT_ASSERT_EQUALS( 2,
    				   iSecureInSession->SupportedCryptoContextsL().Count() );
    
    //get crypto
    array.Remove(EAES_CM_128_HMAC_SHA1_32);
    iSecureInSession->SetCryptoContextsL( array );
    EUNIT_ASSERT_EQUALS( 1, iSecureInSession->CryptoContexts().Count() );
    
    //set again crypto to increase the coverage
    iSecureInSession->SetCryptoContextsL( array );
    EUNIT_ASSERT_EQUALS( 1, iSecureInSession->CryptoContexts().Count() );
    
    array.Reset();
    array.AppendL( EAES_CM_128_HMAC_SHA1_32 );
    iSecureInSession->SetCryptoContextsL( array );
    EUNIT_ASSERT_EQUALS( 1, iSecureInSession->CryptoContexts().Count() );

    array.Reset();
    delete iSecureInSession; iSecureInSession = NULL;
   	}
   	
// ----------------------------------------------------------------------------
// CMceSecureInSessionTest::NewLTestL()
// ----------------------------------------------------------------------------
//
void CMceSecureInSessionTest::NewLTestL()
    {
	MCE_CREATE_PROFILE;

    MCE_INCOMING_SECURE_SESSION( iManager, KMceTestSessionId1 );
    
    iSecureInSession = static_cast<CMceSecureInSession*>( iManager->Sessions()[0] );
    
    EUNIT_ASSERT(iSecureInSession->SupportedCryptoContextsL().Count() == 2);
    
    MCE_TEST_DELETE( iSecureInSession );

    MCE_DELETE_PROFILE;    

    
    }   	    
// ----------------------------------------------------------------------------
// CMceSecureInSessionTest::AcceptTestL
// ----------------------------------------------------------------------------
//
void CMceSecureInSessionTest::AcceptTestL()
    {
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iSecureInSession = static_cast<CMceSecureInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iSecureInSession->Id() == KMceTestSessionId1 );

    //update
    iSecureInSession->UpdateL();
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );

    MCE_SESSION_STATECHANGE( iSecureInSession, CMceSession::EProceeding, KMceNotAssigned );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EProceeding );
    
    //ring
    iSecureInSession->RingL();
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EProceeding );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );

    //siple accept
    iSecureInSession->AcceptL();
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EAnswering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );
    
    MCE_SESSION_STATECHANGE( iSecureInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EEstablished );
    
    MCE_SESSION_STATECHANGE( iSecureInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::ETerminated );

    MCE_TEST_DELETE( iSecureInSession );
    
//detailed
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 + 1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iSecureInSession = static_cast<CMceSecureInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iSecureInSession->Id() == KMceTestSessionId1 + 1 );

    //update
    iSecureInSession->UpdateL();
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );
    

    MCE_SESSION_STATECHANGE( iSecureInSession, CMceSession::EProceeding, KMceNotAssigned );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EProceeding );
    
    //ring
    iSecureInSession->RingL();
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EProceeding );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );

    //leaving cases
    //too small
    TRAPD( err1, iSecureInSession->AcceptL( KMceReason, 199 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )   
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    //too big
    TRAPD( err2, iSecureInSession->AcceptL( KMceReason, 300 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )   
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    // successfull
    //detailed accept without headers
    iSecureInSession->AcceptL( KMceReason, 200 );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EAnswering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );
    
    MCE_SESSION_STATECHANGE( iSecureInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EEstablished );
    
    MCE_SESSION_STATECHANGE( iSecureInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::ETerminated );

    MCE_TEST_DELETE( iSecureInSession );

    }
    
// ----------------------------------------------------------------------------
// CMceSecureInSessionTest::RejectTestL
// ----------------------------------------------------------------------------
//
void CMceSecureInSessionTest::RejectTestL()
    {
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iSecureInSession = static_cast<CMceSecureInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iSecureInSession->Id() == KMceTestSessionId1 );
    
    //siple reject
    iSecureInSession->RejectL();
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );
        
    MCE_TEST_DELETE( iSecureInSession );

//detailed
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 + 1  );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iSecureInSession = static_cast<CMceSecureInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iSecureInSession->Id() == KMceTestSessionId1 + 1);
    

    //detailed reject without headers
    iSecureInSession->RejectL( KMceReason, 488 );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );
        
    MCE_TEST_DELETE( iSecureInSession );

//detailed
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 + 2 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iSecureInSession = static_cast<CMceSecureInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iSecureInSession->Id() == KMceTestSessionId1 + 2 );

    //detailed reject
    //Leaving cases
    HBufC8* ct = KMceContentType().AllocLC();
    HBufC8* c = KMceMessageBody().AllocLC();
    
    // content type && no content
    TRAPD( err1, iSecureInSession->RejectL( KMceReason, 444, NULL, ct, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )   
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    // no content type && content
    TRAPD( err2, iSecureInSession->RejectL( KMceReason, 444, NULL, NULL, c ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )  
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    // too small code
    TRAPD( err3, iSecureInSession->RejectL( KMceReason, 299 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )   
    EUNIT_ASSERT_EQUALS( err3, KErrArgument );
    
    // too big code
    TRAPD( err4, iSecureInSession->RejectL( KMceReason, 700 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 )  
    EUNIT_ASSERT_EQUALS( err4, KErrArgument );
    
    CleanupStack::PopAndDestroy( c );
    CleanupStack::PopAndDestroy( ct );

    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );
    
    iSecureInSession->RejectL( KMceReason, 566, headers );
    CleanupStack::Pop( headers );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::ETerminated );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );
    }

// ----------------------------------------------------------------------------
// CMceSecureInSessionTest::RingTestL
// ----------------------------------------------------------------------------
//
void CMceSecureInSessionTest::RingTestL()
    {
    // Cover the leaving cases.
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iSecureInSession = static_cast<CMceSecureInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iSecureInSession->Id() == KMceTestSessionId1 );

    //update
    iSecureInSession->UpdateL();
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );

    MCE_SESSION_STATECHANGE( iSecureInSession, CMceSession::EProceeding, KMceNotAssigned );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EProceeding );
    
    HBufC8* ct = KMceContentType().AllocLC();
    HBufC8* c = KMceMessageBody().AllocLC();
    
    // Actual test cases
    // content type && no content
    TRAPD( err1, iSecureInSession->RingL( NULL, ct, NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )   
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    // no content type && content
    TRAPD( err2, iSecureInSession->RingL( NULL, NULL, c ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )   
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    CleanupStack::PopAndDestroy( c );
    CleanupStack::PopAndDestroy( ct );
    }

// ----------------------------------------------------------------------------
// CMceSecureInSessionTest::IncomingTestL
// ----------------------------------------------------------------------------
//
void CMceSecureInSessionTest::IncomingTestL()
    {
    // Incoming session, no in session observer
    iManager->SetInSessionObserver( NULL );
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    }

// ----------------------------------------------------------------------------
// CMceSecureInSessionTest::ZombieTestsL
// ----------------------------------------------------------------------------
//
void CMceSecureInSessionTest::ZombieTestsL()
    {
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );

    iSecureInSession = static_cast<CMceSecureInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EIncoming );
    EUNIT_ASSERT( iSecureInSession->Id() == KMceTestSessionId1 );

    //update
    iSecureInSession->UpdateL();
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );

    MCE_SESSION_STATECHANGE( iSecureInSession, CMceSession::EProceeding, KMceNotAssigned );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EProceeding );
    
    //siple accept
    iSecureInSession->AcceptL();
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EAnswering );
    EUNIT_ASSERT( iStorage->iIDS.iSessionID == iSecureInSession->Id() );
    
    MCE_SESSION_STATECHANGE( iSecureInSession, CMceSession::EEstablished, KMceNotAssigned );
    EUNIT_ASSERT( iSecureInSession->State() == CMceSession::EEstablished );
    
    // Incoming update
    MCE_INCOMING_UPDATE2( iSecureInSession );
    
    EUNIT_ASSERT( iSecureInSession->IsZombie() );
    // Actual tests
    // RingL
    TRAPD( err1, iSecureInSession->RingL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )   
    EUNIT_ASSERT_EQUALS( err1, KErrArgument );
    
    // AcceptL
    TRAPD( err2, iSecureInSession->AcceptL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )  
    EUNIT_ASSERT_EQUALS( err2, KErrArgument );
    
    TRAPD( err3, iSecureInSession->AcceptL( KMceReason, 222 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )   
    EUNIT_ASSERT_EQUALS( err3, KErrArgument );
    
    // RejectL
    TRAPD( err4, iSecureInSession->RejectL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 )   
    EUNIT_ASSERT_EQUALS( err4, KErrArgument );
    
    TRAPD( err5, iSecureInSession->AcceptL( KMceReason, 444 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err5 )   
    EUNIT_ASSERT_EQUALS( err5, KErrArgument );
    
    
    EUNIT_ASSERT( iManagerObserver->iSession != NULL );
    delete iSecureInSession;
    iSecureInSession = static_cast< CMceSecureInSession* >( iManagerObserver->iSession );
    iManagerObserver->iSession = NULL;    
    }
