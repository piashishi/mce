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
#include "CMceOutSessionTest.h"

#include "mcestubs.h"
#include "mcetestdefs.h"

#include "mcemanager.h"
#include "mceoutevent.h"
#include "mceoutrefer.h"
#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceeventreceiver.h"
#include "mcereferreceiver.h"
#include "mceeventmanagerreceiver.h"


#include "mceoutsession.h"
#include "mceaudiostream.h"
#include "mcertpsink.h"
#include "mcertpsource.h"
#include "mcemicsource.h"
#include "mcespeakersink.h"
#include "mcecomsession.h"
#include "mcecommediastream.h"
#include "mceserial.h"



        

// ----------------------------------------------------------------------------
// CMceOutSessionTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceOutSessionTest::setUpL()
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
// CMceOutSessionTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceOutSessionTest::tearDown()
    {

    if ( iOutSession )
        {
        MCE_TEST_DELETE( iOutSession );
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
// CMceOutSessionTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceOutSessionTest::suiteL()
    {
    CMceOutSessionTest* suite = new CMceOutSessionTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceOutSessionTest,
    "CMceOutSessionTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceOutSessionTest", setUpL, EstablishTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceOutSessionTest", setUpL, CancelTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceOutSessionTest", setUpL, RemainTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceOutSessionTest", setUpL, NewLTestL, tearDown )
EUNIT_END_TEST_TABLE 
	
// ----------------------------------------------------------------------------
// CMceOutSessionTest::EstablishTestL
// ----------------------------------------------------------------------------
//
void CMceOutSessionTest::EstablishTestL()
    {
    
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->Recipient().Compare( KMceRecipient ) == 0 );
    EUNIT_ASSERT( iOutSession->Id() == 1 );

    EUNIT_ASSERT( iStorage->iSessionId == 1 );
    
    iOutSession->EstablishL();
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iOutSession->Id() == 1 );
    
    
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

    EUNIT_ASSERT( iOutSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iOutSession->Id() == 1 );

    TRAPD( notReady, iOutSession->EstablishL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( notReady )
    EUNIT_ASSERT( notReady == KErrNotReady );

    MCE_TEST_DELETE( iOutSession );
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    
//detailed
    
    iStorage->Reset();

    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->Recipient().Compare( KMceRecipient ) == 0 );

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
        iOutSession->AddStreamL( outStream );
        CleanupStack::Pop( outStream );
        
        // Try to add same stream again 
   		TRAPD( err, iOutSession->AddStreamL( outStream ) );
   		MCE_TEST_HANDLE_ALLOC_FAILURE( err )
   		EUNIT_ASSERT_EQUALS( KErrArgument, err );
  
        }

    static_cast<CMceAudioStream*>( iOutSession->Streams()[1])->BindL( NULL );
    
    CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers );
    headers->AppendL( KMceHeader1 );
    headers->AppendL( KMceHeader2 );    
    
    HBufC8* contentType = KMceContentType().AllocLC();
    HBufC8* body = KMceMessageBody().AllocLC();

    // Leaving cases
    // content type, no content
    TRAPD( err, iOutSession->EstablishL( KMceTestTimeout, 
                             headers,
                             contentType,
                             NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT( err == KErrArgument );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EIdle );
    
    // no content type, content
    TRAPD( err2, iOutSession->EstablishL( KMceTestTimeout, 
                             headers,
                             NULL,
                             body ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )
    EUNIT_ASSERT( err2 == KErrArgument );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EIdle );
    
    // no headers, no content type, no content, content headers
    TRAPD( err3, iOutSession->EstablishL( KMceTestTimeout, 
                             NULL,
                             NULL,
                             NULL,
                             headers ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )                         
    EUNIT_ASSERT( err3 == KErrArgument );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EIdle );
    
    iOutSession->EstablishL( KMceTestTimeout, 
                             headers,
                             contentType,
                             body );
                             
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EOffering );

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


    TRAPD( notReady2, iOutSession->EstablishL( KMceTestTimeout, NULL, NULL, NULL) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( notReady2 )
    EUNIT_ASSERT( notReady2 == KErrNotReady );
    
    sentSessionMsg->Pop();
    delete sentSession;
    CleanupStack::PopAndDestroy( sentSessionMsg );

    EUNIT_ASSERT( iOutSession->State() == CMceSession::EOffering );

    MCE_DELETE_PROFILE;    
    
    }


// ----------------------------------------------------------------------------
// CMceOutSessionTest::CancelTestL
// ----------------------------------------------------------------------------
//
void CMceOutSessionTest::CancelTestL()
    {

	MCE_CREATE_PROFILE;
	HBufC8* originator = KMceOriginator().AllocLC();
    iOutSession = CMceOutSession::NewL( *iManager, 
                                        *profile, 
                                        KMceRecipient, 
                                        originator );
    CleanupStack::Pop( originator );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->Recipient().Compare( KMceRecipient ) == 0 );

	TRAPD(err, iOutSession->CancelL());
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
    
    iOutSession->EstablishL();
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EOffering );
    EUNIT_ASSERT( iOutSession->ConnectionActive() );

    MCE_CALLBACK( iOutSession, KMceMediaIdNotAssigned, KMceMediaIdNotAssigned, 
                  KMceMediaIdNotAssigned, KMceMediaIdNotAssigned, 
                  EMceItcSessionConnectionStateChanged, EFalse, KMceNotAssigned );

    EUNIT_ASSERT( !iOutSession->ConnectionActive() );
    EUNIT_ASSERT( iSessionObserver->iSession == iOutSession );
    EUNIT_ASSERT( !iSessionObserver->iActive );

    iOutSession->CancelL();
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ECancelling );
    
    MCE_SESSION_STATECHANGE( iOutSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::ETerminated );

    MCE_DELETE_PROFILE;
    
    }
    
// ----------------------------------------------------------------------------
// CMceOutSessionTest::RemainTestL
// ----------------------------------------------------------------------------
//
void CMceOutSessionTest::RemainTestL()
    {
    // inside dialog
	MCE_CREATE_PROFILE;

    EUNIT_ASSERT( iStorage->iSessionId == 0 );

    CMceEvent* event = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 1000 );
    CleanupStack::PushL( event );
    	
    CMceRefer* refer = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo, CMceRefer::EMultipleRefer );
    CleanupStack::PushL( refer );
	
	// with event
	CMceOutSession* outSession1= CMceOutSession::NewL( *event );
	CleanupStack::PushL( outSession1 );
	EUNIT_ASSERT( outSession1->Profile() == event->ProfileId() );
	EUNIT_ASSERT( outSession1->DialogId() == event->DialogId() );
	EUNIT_ASSERT( outSession1->Recipient() == event->Recipient() );
	EUNIT_ASSERT( outSession1->Originator() == event->Originator() );
	
	// with refer
	CMceOutSession* outSession2= CMceOutSession::NewL( *refer );
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
 
// ----------------------------------------------------------------------------
// CMceOutSessionTest::NewLTestL
// ----------------------------------------------------------------------------
//
void CMceOutSessionTest::NewLTestL()
    {
    const TUint32 KIap = 89;
    iOutSession = CMceOutSession::NewL( *iManager,
    									KIap,
    									KNullDesC8,
    									KMceRecipient,
    									NULL );
	EUNIT_ASSERT_EQUALS( KIap,
		static_cast<CMceComSession*>( iOutSession->iFlatData )->iIapId );
	EUNIT_ASSERT_EQUALS( KNullDesC8(),
		static_cast<CMceComSession*>( iOutSession->iFlatData )->iOriginator->Des() );
	EUNIT_ASSERT_EQUALS( KMceRecipient(),
		static_cast<CMceComSession*>( iOutSession->iFlatData )->iRecipient->Des() );
    }
