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
#include "mcesecureoutsessiontest.h"
#include "CMceSessionTest.h"
#include "mcestubs.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceinsession.h"
#include "mcesecureoutsession.h"
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
#include "mceoutevent.h"
#include "mceoutrefer.h"
#include "mcereferreceiver.h"


// ----------------------------------------------------------------------------
// CMceSecureOutSessionTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceSecureOutSessionTest::setUpL()
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
// CMceSecureOutSessionTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceSecureOutSessionTest::tearDown()
    {

    if ( iSecureOutSession )
        {
        MCE_TEST_DELETE( iSecureOutSession );
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
// CMceSecureOutSessionTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceSecureOutSessionTest::suiteL()
    {
    CMceSecureOutSessionTest* suite = new CMceSecureOutSessionTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceSecureOutSessionTest,
    "CMceSecureOutSessionTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceSecureOutSessionTest", setUpL, TypeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureOutSessionTest", setUpL, CryptoContextsTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureOutSessionTest", setUpL, EstablishTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureOutSessionTest", setUpL, FailureTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureOutSessionTest", setUpL, CancelTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceSecureOutSessionTest", setUpL, RemainTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceSecureOutSessionTest::TypeTestL
// ----------------------------------------------------------------------------
//
void CMceSecureOutSessionTest::TypeTestL()
	{
	iSecureOutSession = CMceSecureOutSession::NewL();
    EUNIT_ASSERT(iSecureOutSession->Type() == KMceSessionSecure);
	delete iSecureOutSession; iSecureOutSession = NULL;
	}

// ----------------------------------------------------------------------------
// CMceSecureOutSessionTest::CryptoContextsTestL
// ----------------------------------------------------------------------------
//
void CMceSecureOutSessionTest::CryptoContextsTestL()
	{
	iSecureOutSession = CMceSecureOutSession::NewL();
	
    // Set crypto context. Granularity 1 forces alloc in each operation.
	RArray<TMceCryptoContext> array( 1 );
    array.AppendL( EAES_CM_128_HMAC_SHA1_32 );
    array.AppendL( EAES_CM_128_HMAC_SHA1_32 );

    iSecureOutSession->SetCryptoContextsL( array );
    EUNIT_ASSERT_EQUALS( 2,
    				   iSecureOutSession->SupportedCryptoContextsL().Count() );
    
    //get crypto
    array.Remove( EAES_CM_128_HMAC_SHA1_32 );
    iSecureOutSession->SetCryptoContextsL( array );
    EUNIT_ASSERT_EQUALS(1, iSecureOutSession->CryptoContexts().Count() );
    
    //set again crypto to increase the coverage
    iSecureOutSession->SetCryptoContextsL( array );
    EUNIT_ASSERT_EQUALS( 1, iSecureOutSession->CryptoContexts().Count() );
    
    array.Reset();
    delete iSecureOutSession; iSecureOutSession = NULL;
    
    //
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT_EQUALS( 0, iStorage->iSessionId );

    iSecureOutSession = CMceSecureOutSession::NewL( *iManager,
    												*profile,
    												KMceRecipient );
    EUNIT_ASSERT_EQUALS( 1, iManager->Sessions().Count() );
    EUNIT_ASSERT_EQUALS( 2, iSecureOutSession->CryptoContexts().Count() );
    delete iSecureOutSession; iSecureOutSession = NULL;
    MCE_DELETE_PROFILE;
	}

// ----------------------------------------------------------------------------
// CMceOutSessionTest::FailureTestL
// ----------------------------------------------------------------------------
//
void CMceSecureOutSessionTest::FailureTestL()
    {

	MCE_CREATE_PROFILE;
    profile->SetEnabled(ETrue);
    TRAPD( notFound, CMceSecureOutSession::NewL( *iManager, *profile, KMceRecipient ));
	 
    MCE_TEST_HANDLE_ALLOC_FAILURE( notFound )
    EUNIT_ASSERT( notFound == KErrNotFound );
	MCE_DELETE_PROFILE;    

    
    }
// ----------------------------------------------------------------------------
// CMceOutSessionTest::EstablishTestL
// ----------------------------------------------------------------------------
//
void CMceSecureOutSessionTest::EstablishTestL()
    {
    MCE_CREATE_PROFILE;

    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iSecureOutSession = CMceSecureOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iSecureOutSession->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iSecureOutSession->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
    
    iSecureOutSession->EstablishL();
    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iSecureOutSession->Id() == 1 );
    
    
    CMceMsgObject<CMceComSession>* sentSessionMsg = 
            new (ELeave) CMceMsgObject<CMceComSession>();
            
    CleanupStack::PushL( sentSessionMsg );
    sentSessionMsg->DecodeL( *(iStorage->iContext) );
    sentSessionMsg->PushL();
    
    CMceComSession* sentSession = sentSessionMsg->iObject;
    
    EUNIT_ASSERT( sentSession->iType == CMceComSession::EOutSession );
    EUNIT_ASSERT( sentSession->iState == CMceSession::EIdle );
    EUNIT_ASSERT( sentSession->iID == iStorage->iIDS.iSessionID );
    EUNIT_ASSERT( sentSession->Streams().Count() == 0 );

    sentSessionMsg->Pop();
    delete sentSession;
    CleanupStack::PopAndDestroy( sentSessionMsg );

    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iSecureOutSession->Id() == 1 );

    TRAPD( notReady, iSecureOutSession->EstablishL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( notReady )
    EUNIT_ASSERT( notReady == KErrNotReady );

    MCE_TEST_DELETE( iSecureOutSession );
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    
//detailed
    
    iStorage->Reset();

    iSecureOutSession = CMceSecureOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iSecureOutSession->Recipient().Compare( KMceRecipient ) == 0 );

    for ( int i=0;i<2;i++ )
        {
        
        CMceAudioStream* outStream = CMceAudioStream::NewL();
        CleanupStack::PushL( outStream );
        CMceAudioStream* inStream = CMceAudioStream::NewL();
        CleanupStack::PushL( inStream );
           
        outStream->AddSinkL( CMceRtpSink::NewLC() );
        CleanupStack::Pop();
        outStream->SetSourceL( CMceMicSource::NewLC() );
        CleanupStack::Pop();
        
        CDesC8ArrayFlat* sdp = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
        CleanupStack::PushL( sdp );
        sdp->AppendL( KMceMedialine1 );
        sdp->AppendL( KMceMedialine2 );    
        outStream->SetMediaAttributeLinesL( sdp );
        CleanupStack::Pop( sdp );
        
        inStream->SetSourceL( CMceRtpSource::NewLC() );
        CleanupStack::Pop();
        inStream->AddSinkL( CMceSpeakerSink::NewLC() );
        CleanupStack::Pop();
        
        sdp = 0;
        sdp = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
        CleanupStack::PushL( sdp );
        sdp->AppendL( KMceMedialine1 );
        sdp->AppendL( KMceMedialine2 );    
        inStream->SetMediaAttributeLinesL( sdp );
        CleanupStack::Pop( sdp );
        
        
        outStream->BindL( inStream );
        CleanupStack::Pop( inStream );
        iSecureOutSession->AddStreamL( outStream );
        CleanupStack::Pop( outStream );
        
        // Try to add same stream again 
   		TRAPD( err, iSecureOutSession->AddStreamL( outStream ) );
   		MCE_TEST_HANDLE_ALLOC_FAILURE( err )
   		EUNIT_ASSERT_EQUALS( KErrArgument, err );
  
        }

    static_cast<CMceAudioStream*>( iSecureOutSession->Streams()[1])->BindL( NULL );
    
    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    
    HBufC8* contentType = KMceContentType().AllocLC();
    HBufC8* body = KMceMessageBody().AllocLC();

    // Leaving cases
    // content type, no content
    TRAPD( err, iSecureOutSession->EstablishL( KMceTestTimeout, 
                             headers,
                             contentType,
                             NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT( err == KErrArgument );
    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::EIdle );
    
    // no content type, content
    TRAPD( err2, iSecureOutSession->EstablishL( KMceTestTimeout, 
                             headers,
                             NULL,
                             body ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT( err2 == KErrArgument );
    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::EIdle );
    
    // no headers, no content type, no content, content headers
    TRAPD( err3, iSecureOutSession->EstablishL( KMceTestTimeout, 
                             NULL,
                             NULL,
                             NULL,
                             headers ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )                         
    EUNIT_ASSERT( err3 == KErrArgument );
    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::EIdle );
    
    iSecureOutSession->EstablishL( KMceTestTimeout, 
                             headers,
                             contentType,
                             body );
                             
    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::EOffering );

    CleanupStack::Pop( body );
    CleanupStack::Pop( contentType );
    CleanupStack::Pop( headers );
    
    EUNIT_ASSERT( iStorage->iContent->Compare( KMceMessageBody ) == 0 );
    
    
    sentSessionMsg = new (ELeave) CMceMsgObject<CMceComSession>();
            
    CleanupStack::PushL( sentSessionMsg );
    sentSessionMsg->DecodeL( *(iStorage->iContext) );
    sentSessionMsg->PushL();
    
    sentSession = sentSessionMsg->iObject;
    
    EUNIT_ASSERT( sentSession->iType == CMceComSession::EOutSession );
    EUNIT_ASSERT( sentSession->iState == CMceSession::EIdle );
    EUNIT_ASSERT( sentSession->iID == iStorage->iIDS.iSessionID );
    
    EUNIT_ASSERT( sentSession->iSIPContentType->Compare( KMceContentType ) == 0 );
    EUNIT_ASSERT( sentSession->iSIPHeaders->Count() == 2 );
    EUNIT_ASSERT( sentSession->iSIPHeaders->MdcaPoint( 0 ).Compare( KMceHeader1 ) == 0 );
    EUNIT_ASSERT( sentSession->iSIPHeaders->MdcaPoint( 1 ).Compare( KMceHeader2 ) == 0 );

    
    EUNIT_ASSERT( sentSession->Streams().Count() == 2 );
    
    EUNIT_ASSERT( sentSession->Streams()[0]->iLocalMediaSDPLines->MdcaPoint( 0 ).Compare( KMceMedialine1 ) == 0 );
    EUNIT_ASSERT( sentSession->Streams()[0]->iLocalMediaSDPLines->MdcaPoint( 1 ).Compare( KMceMedialine2 ) == 0 );
    EUNIT_ASSERT( static_cast<CMceComAudioStream*>( sentSession->Streams()[0])->BoundStream() );
    EUNIT_ASSERT( static_cast<CMceComAudioStream*>( sentSession->Streams()[0])->BoundStreamL().iLocalMediaSDPLines->MdcaPoint( 0 ).Compare( KMceMedialine1 ) == 0 );
    EUNIT_ASSERT( static_cast<CMceComAudioStream*>( sentSession->Streams()[0])->BoundStreamL().iLocalMediaSDPLines->MdcaPoint( 1 ).Compare( KMceMedialine2 ) == 0 );
    EUNIT_ASSERT( !static_cast<CMceComAudioStream*>( sentSession->Streams()[1])->BoundStream() );


    TRAPD( notReady2, iSecureOutSession->EstablishL( KMceTestTimeout, NULL, NULL, NULL) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( notReady2 )
    EUNIT_ASSERT( notReady2 == KErrNotReady );
    
    sentSessionMsg->Pop();
    delete sentSession;
    CleanupStack::PopAndDestroy( sentSessionMsg );

    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::EOffering );

    MCE_DELETE_PROFILE;    
    
    }


// ----------------------------------------------------------------------------
// CMceOutSessionTest::CancelTestL
// ----------------------------------------------------------------------------
//
void CMceSecureOutSessionTest::CancelTestL()
    {

	MCE_CREATE_PROFILE;
	HBufC8* originator = KMceOriginator().AllocLC();
    iSecureOutSession = CMceSecureOutSession::NewL( *iManager, 
                                        *profile, 
                                        KMceRecipient, 
                                        originator );
    CleanupStack::Pop( originator );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iSecureOutSession->Recipient().Compare( KMceRecipient ) == 0 );

	TRAPD(err, iSecureOutSession->CancelL());
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
    
    iSecureOutSession->EstablishL();
    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iSecureOutSession->ConnectionActive() );

    MCE_CALLBACK( iSecureOutSession, KMceMediaIdNotAssigned, KMceMediaIdNotAssigned, 
                  KMceMediaIdNotAssigned, KMceMediaIdNotAssigned, 
                  EMceItcSessionConnectionStateChanged, EFalse, KMceNotAssigned );

    EUNIT_ASSERT( !iSecureOutSession->ConnectionActive() );
    EUNIT_ASSERT( iSessionObserver->iSession == iSecureOutSession );
    EUNIT_ASSERT( !iSessionObserver->iActive );

    iSecureOutSession->CancelL();
    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::ECancelling );
    
    MCE_SESSION_STATECHANGE( iSecureOutSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iSecureOutSession->State() == CMceSession::ETerminated );

    MCE_DELETE_PROFILE;
    
    }
    
// ----------------------------------------------------------------------------
// CMceOutSessionTest::RemainTestL
// ----------------------------------------------------------------------------
//
void CMceSecureOutSessionTest::RemainTestL()
    {
    // inside dialog
	MCE_CREATE_PROFILE;

    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    CMceEvent* event = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    CleanupStack::PushL( event );
    	
    CMceRefer* refer = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo, CMceRefer::EMultipleRefer );
    CleanupStack::PushL( refer );
	
	// with event
	CMceSecureOutSession* outSession1= CMceSecureOutSession::NewL( *event );
	CleanupStack::PushL( outSession1 );
	EUNIT_ASSERT( outSession1->Profile() == event->ProfileId() );
	EUNIT_ASSERT( outSession1->DialogId() == event->DialogId() );
	EUNIT_ASSERT( outSession1->Recipient() == event->Recipient() );
	EUNIT_ASSERT( outSession1->Originator() == event->Originator() );
	
	// with refer
	CMceSecureOutSession* outSession2= CMceSecureOutSession::NewL( *refer );
	CleanupStack::PushL( outSession2 );
	EUNIT_ASSERT( outSession2->Profile() == refer->ProfileId() );
	EUNIT_ASSERT( outSession2->DialogId() == refer->DialogId() );
	EUNIT_ASSERT( outSession2->Recipient() == refer->Recipient() );
	EUNIT_ASSERT( outSession2->Originator() == refer->Originator() );
	
	// leave with not assigned dialog id
	TUint32 id = refer->DialogId();
	refer->iDialogId = KMceNotAssigned;
	CMceOutSession* outSession3 = NULL;
	TRAPD( err, outSession3 = CMceOutSession::NewL( *refer ) );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( err, KErrArgument );
	EUNIT_ASSERT( !outSession3 );
	
	// set refer id back
	refer->iDialogId = id;
	// clean
	CleanupStack::Pop( outSession2 );
	CleanupStack::Pop( outSession1 );
	CleanupStack::Pop( refer );
	CleanupStack::Pop( event );
	event->iState = CMceEvent::EActive;
	MCE_TEST_DELETE( event );
	MCE_TEST_DELETE( refer );
	MCE_TEST_DELETE( outSession1 );
	MCE_TEST_DELETE( outSession2 );
	
    MCE_DELETE_PROFILE;    
    }
