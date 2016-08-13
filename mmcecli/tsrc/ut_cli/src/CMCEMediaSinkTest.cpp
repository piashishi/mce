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
#include "CMceMediaSinkTest.h"
#include "mcetestdefs.h"

#include "mcestubs.h"
#include "mcemanager.h"
#include "MCEFactory.h"
#include "mcespeakersink.h"
#include "mcecomspeakersink.h"
#include "mcecommediasink.h"
#include "mcesession.h"
#include "mceoutsession.h"
#include "mceaudiostream.h"
#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mceevents.h"
#include "mcertpsink.h"

const TInt KMceTestRouteToIHF = 3;
const TInt KMceTestVolume = 5;
const TUint8 KMceTestCategory =5;

// ----------------------------------------------------------------------------
// CMceMediaSinkTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceMediaSinkTest::setUpL()
    {
	iSpeaker = CMceSpeakerSink::NewL();
    }

// ----------------------------------------------------------------------------
// CMceMediaSinkTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::tearDown()
    {
    delete iSpeaker;
    }

// ----------------------------------------------------------------------------
// CMceMediaSinkTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceMediaSinkTest::suiteL()
    {
    CMceMediaSinkTest* suite = new CMceMediaSinkTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceMediaSinkTest,
    "CMceMediaSinkTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, GettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, FactoryTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, DoDisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, DoEnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, InitializeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, HandleEventTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, EventReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, UpdatedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, SetVolumeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, VolumeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, MaxVolumeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, EndPointProxyTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, SerializationIdTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, UnInitializeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSinkTest", setUpL, CreateEndpointProxyLTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::ConstructionTestL()
    {
    CMceMediaSink* mediaSink = static_cast<CMceMediaSink*>(iSpeaker);
    
 	TRAPD( err, mediaSink->ConstructL( NULL ) );
 	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
 	EUNIT_ASSERT_EQUALS( KErrArgument, err );
    }


// ----------------------------------------------------------------------------
// CMceMediaSinkTest::GettersTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::GettersTestL()
    {
 	TMceMediaId id = iSpeaker->Id();
	EUNIT_ASSERT( id.iAppId == KMceNotAssigned);
	EUNIT_ASSERT( id.iId == KMceNotAssigned);
	   
    EUNIT_ASSERT( iSpeaker->Type() == KMceSpeakerSink );
    iSpeaker->iFlatData->iType = KMceTestSinkType;
    EUNIT_ASSERT( iSpeaker->Type() == KMceTestSinkType );
    
    iSpeaker->iFlatData->Enabled ( KMceTestEnabledTrue);
    EUNIT_ASSERT( iSpeaker->IsEnabled() );
    iSpeaker->iFlatData->Enabled ( KMceTestEnabledFalse );
    EUNIT_ASSERT( !iSpeaker->IsEnabled() );
    }


// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: FactoryTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::FactoryTestL()
    {
    TMceSinkFactory factory = CMceMediaSink::Factory();
    TMceSinkFactory* ptrFactory = &factory;
    
    EUNIT_ASSERT( ptrFactory != NULL );
    
    // TMceSinkFactory::CreateLC( TMceSinkType aType )
    // KMceRTPSink
    CMceMediaSink* rtpSink = factory.CreateLC( KMceRTPSink );
    EUNIT_ASSERT( rtpSink != NULL );
    CleanupStack::PopAndDestroy( rtpSink );
    // KMceSpeakerSink
    CMceMediaSink* speakerSink = factory.CreateLC( KMceSpeakerSink );
    EUNIT_ASSERT( speakerSink != NULL );
    CleanupStack::PopAndDestroy( speakerSink );
    
    // default
    CMceMediaSink* otherSink = NULL;
    TRAPD( err, otherSink = factory.CreateLC( ( TMceSinkType )( KErrNotFound ) ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotSupported );
    EUNIT_ASSERT( otherSink == NULL );
    }


// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: DoDisableTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::DoDisableTestL()
    {
    // Disable as not assigned 
  	iSpeaker->iFlatData->Enabled ( ETrue );
  	iSpeaker->DisableL();
  	EUNIT_ASSERT( !iSpeaker->iFlatData->IsEnabled () );
  	
  	// Disable as assigned, preparations
 
  	MCE_CREATE_PROFILE;
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
		
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceSpeakerSink* sink = CMceSpeakerSink::NewLC();
	sink->iFlatData->Enabled ( EFalse );
	stream->AddSinkL( sink );
	CleanupStack::Pop( sink );
	
	session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	CMceSpeakerSink* sink2 = CMceSpeakerSink::NewLC();
	sink2->iFlatData->Enabled ( ETrue );
	TRAPD( err, stream->AddSinkL( sink2 ) ); // not supported second sink
	EUNIT_ASSERT_EQUALS( err, KErrNotSupported );
	
	session->InitializeL();

	// Actual testcase
	
	sink->DisableL();
	EUNIT_ASSERT( !sink->iFlatData->IsEnabled( ) );

	sink2->DisableL();
	EUNIT_ASSERT( !sink2->iFlatData->IsEnabled ());
	CleanupStack::PopAndDestroy( sink2 );
	
	// Cleanup

    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    
    MCE_DELETE_PROFILE;
     
    }


// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: DoEnableTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::DoEnableTestL()
    {
    // Enable as not assigned 
  	iSpeaker->iFlatData->Enabled ( EFalse );
  	iSpeaker->EnableL();
  	EUNIT_ASSERT( iSpeaker->iFlatData->IsEnabled ( ) );
  	
  	// Enable as assigned, preparations

    MCE_CREATE_PROFILE;
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
		
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceSpeakerSink* sink = CMceSpeakerSink::NewLC();
	sink->iFlatData->Enabled ( EFalse );
	stream->AddSinkL( sink );
	CleanupStack::Pop( sink );
	
	session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	CMceSpeakerSink* sink2 = CMceSpeakerSink::NewLC();
	sink2->iFlatData->Enabled ( ETrue );
	TRAPD( err, stream->AddSinkL( sink2 ) );// not supported second sink
	EUNIT_ASSERT_EQUALS( err, KErrNotSupported );
	
	session->InitializeL();

	// Actual testcase
	
	sink->EnableL();
	EUNIT_ASSERT( sink->iFlatData->IsEnabled () );

	sink2->EnableL();
	EUNIT_ASSERT( sink2->iFlatData->IsEnabled() );
	CleanupStack::PopAndDestroy( sink2 );
    
	// Cleanup

    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    
    MCE_DELETE_PROFILE;
    
    }
    

// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::ExternalizeTestL()
    {
    iSpeaker->iFlatData->iCategory = KMceTestCategory;
    iSpeaker->iFlatData->iID.iAppId = KMceTestAppId;
    iSpeaker->iFlatData->iID.iId = KMceTestMiscId; 
    iSpeaker->iFlatData->iType = KMceTestSinkType;
    iSpeaker->iFlatData->Enabled ( KMceTestEnabledFalse );
    
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iSpeaker->ExternalizeL( serCtx );
	CleanupStack::PopAndDestroy();//serCtx
	writeStream.Close();
	writeStream.Pop();
	
	RDesReadStream readStream( buffer );
	readStream.PushL();
	
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestSinkType );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestCategory );
	EUNIT_ASSERT( KMceTestAppId == readStream.ReadUint32L() );
	EUNIT_ASSERT( KMceTestMiscId == readStream.ReadUint32L() );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestEnabledFalse );
	
	readStream.Close();
	readStream.Pop();
    }


// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::InternalizeTestL()
    {

    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();
    
    writeStream.WriteUint8L( KMceTestSinkType );
    //iCategory = aReadStream.ReadUint8L();
    writeStream.WriteUint8L( KMceTestCategory );
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( KMceTestEnabledFalse );
    writeStream.WriteInt32L( KMceTestRouteToIHF );
    writeStream.WriteInt32L( KMceTestVolume );
    
	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    iSpeaker->InternalizeL( serCtx );
    
    EUNIT_ASSERT( iSpeaker->iFlatData->iType == KMceTestSinkType );
    EUNIT_ASSERT( iSpeaker->iFlatData->IsEnabled() == KMceTestEnabledFalse );
    EUNIT_ASSERT( iSpeaker->iFlatData->Id().iAppId == KMceTestAppId );
    EUNIT_ASSERT( iSpeaker->iFlatData->Id().iId == KMceTestMiscId );
    EUNIT_ASSERT( static_cast<CMceComSpeakerSink*>( iSpeaker->iFlatData )->
        iAudioRoute == KMceTestRouteToIHF );
    EUNIT_ASSERT( static_cast<CMceComSpeakerSink*>( iSpeaker->iFlatData )->
        iVolume == KMceTestVolume );
    
	CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();
    
    }


// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: InitializeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::InitializeTestL()
    {
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );

    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
    
    stream->InitializeL( *session, EFalse );
    iSpeaker->InitializeL( *stream ); //Sink is not added to stream, no matter
    iSpeaker->StreamAddedL( *stream );
    EUNIT_ASSERT( iSpeaker->iStream == stream );
    TMceMediaId id = iSpeaker->Id();
	EUNIT_ASSERT( id.iAppId != KMceNotAssigned );
	EUNIT_ASSERT( id.iId != KMceNotAssigned );	
	
    iSpeaker->InitializeL( *stream ); // ID alreaydy set, must not change
    EUNIT_ASSERT( iSpeaker->iStream == stream );  
    EUNIT_ASSERT( iSpeaker->Id().iAppId == id.iAppId );
	EUNIT_ASSERT( iSpeaker->Id().iId == id.iId );
	    
    CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );

    }


// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: HandleEventTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::HandleEventTestL()
    {
    
    // Prepare to call update
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );
    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	stream->InitializeL( *session, EFalse );
	iSpeaker->InitializeL( *stream );
	iSpeaker->StreamAddedL( *stream );    
    
    // Actual testcase
    
	TMceMediaId id;
	id.iAppId = KMceTestAppId;
	id.iId = KMceTestMiscId;

	TMceIds ids;
	ids.iCallbackID = KMceNotAssigned;	
	TMceEvent event( ids, NULL, NULL );  
	TInt status = iSpeaker->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );
	
	ids.iCallbackID = EMceItcStateChanged; 
	ids.iMsgType = EMceItcMsgTypeSink;
	status = iSpeaker->HandleEvent( event );	
	EUNIT_ASSERT_EQUALS( KMceEventUpdate, status );
	
	ids.iMsgType = EMceItcMsgTypeSession;
	ids.iState = KMceTestEnabledTrue;
	iSpeaker->iFlatData->Enabled ( KMceTestEnabledFalse );
	
	status = iSpeaker->HandleEvent( event );	
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, status );
	EUNIT_ASSERT( iSpeaker->iFlatData->IsEnabled ( ) == KMceTestEnabledTrue);
	
	// Cleanup
	
	CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );

    }
 
    
// ----------------------------------------------------------------------------
// CMceMediaSinkTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::EventReceivedTestL()
    {
    
    // Prepare to call HandleEvent()
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );
    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	stream->InitializeL( *session, EFalse );
	iSpeaker->InitializeL( *stream ); 
	
	// Actual testcase
	
	TMceMediaId id;
	id.iAppId = KMceTestAppId;
	id.iId = KMceTestMiscId;

	TMceIds ids;
	ids.iSinkID = id; 
	TMceEvent event( ids, NULL, NULL );
	
	TInt status = iSpeaker->EventReceivedL( event ); //Ids don't match 
	EUNIT_ASSERT_EQUALS( KMceEventNotOwner, status );
	
	iSpeaker->iFlatData->iID = id; // Make Ids match	
	ids.iCodecID = id;  // Make Id not to be a SinkId
	status = iSpeaker->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );	

	ids.iCodecID = KMceMediaIdNotAssigned;	// Make Id to be a SinkId
	status = iSpeaker->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );	
	
	// Cleanup
	
	CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    }
    
    
// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: UpdatedTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::UpdatedTestL()
    {
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMceStreamObserverStub* streamObserver =
		new (ELeave) CMceStreamObserverStub;
	CleanupStack::PushL( streamObserver );	

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );
    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	stream->InitializeL( *session, EFalse );
	iSpeaker->InitializeL( *stream );
	iSpeaker->StreamAddedL( *stream );    

	// Call updated with no observer present
	iSpeaker->Updated();
	EUNIT_ASSERT( !streamObserver->iSink );
	EUNIT_ASSERT( !streamObserver->iStream );
	EUNIT_ASSERT_EQUALS( 0, streamObserver->iStateChangedCount );    

	// Call updated with observer present
    manager->SetMediaObserver( streamObserver );
    iSpeaker->Updated();
    EUNIT_ASSERT( streamObserver->iSink == iSpeaker );
    EUNIT_ASSERT( streamObserver->iStream == stream );
	EUNIT_ASSERT_EQUALS( 1, streamObserver->iStateChangedCount );    
		    
    CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( streamObserver );
    CleanupStack::PopAndDestroy( managerObserver );
    
    }

// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: SetVolumeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::SetVolumeTestL()
    {      	
  	MCE_CREATE_PROFILE;
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
		
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceSpeakerSink* sink = CMceSpeakerSink::NewLC();	
	stream->AddSinkL( sink );
	CleanupStack::Pop( sink );
		 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	session->InitializeL();

	sink->SetVolumeL(10);
	EUNIT_ASSERT_EQUALS( static_cast<CMceComSpeakerSink*>( sink->iFlatData )->iVolume, 10 );
	
	// Cleanup

    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    
    MCE_DELETE_PROFILE;
     
    }


// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: VolumeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::VolumeTestL()
    {
  	MCE_CREATE_PROFILE;
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
		
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceSpeakerSink* sink = CMceSpeakerSink::NewLC();	
	stream->AddSinkL( sink );
	CleanupStack::Pop( sink );
		 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	session->InitializeL();

	// Actual testcase
	
	TInt volume = KErrNotFound;
	volume = sink->VolumeL();
	EUNIT_ASSERT( volume != KErrNotFound );
	
	// Cleanup

    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    
    MCE_DELETE_PROFILE;
     
    }


// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: MaxVolumeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::MaxVolumeTestL()
    {
  	MCE_CREATE_PROFILE;
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
		
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceSpeakerSink* sink = CMceSpeakerSink::NewLC();	
	stream->AddSinkL( sink );
	CleanupStack::Pop( sink );
		 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	session->InitializeL();
	
	// Fail with no session
	stream->iSession = NULL;
	
	TInt volume( 0 );
	TRAPD( err, volume = sink->MaxVolumeL() );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( err, KErrNotReady );
	EUNIT_ASSERT_EQUALS( volume, 0 ); // Volume remains untouched
	stream->iSession = session;
	
	// Cleanup

    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    
    MCE_DELETE_PROFILE;
     
    }
    
// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: EndPointProxyTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::EndPointProxyTestL()
    {
  	MCE_CREATE_PROFILE;
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
		
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceSpeakerSink* sink = CMceSpeakerSink::NewLC();	
	stream->AddSinkL( sink );
	CleanupStack::Pop( sink );
		 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	session->InitializeL();

	// Actual testcase
	
	MMceEndPointProxy*  ep1 = sink->EndpointProxy();
	EUNIT_ASSERT( ep1 == NULL);
	
	// Cleanup
	
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    
    MCE_DELETE_PROFILE;
     
    }    
// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: SerializationIdTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::SerializationIdTestL()
    {
  	MCE_CREATE_PROFILE;
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
		
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceSpeakerSink* sink = CMceSpeakerSink::NewLC();	
	stream->AddSinkL( sink );
	CleanupStack::Pop( sink );
		 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	session->InitializeL();

	// Actual testcase
	TUint64 serialId = sink->SerializationId();
	EUNIT_ASSERT(serialId);
	
	// Cleanup
	
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    
    MCE_DELETE_PROFILE;
     
    }    
    
// ----------------------------------------------------------------------------
// CMceMediaSinkTest:: UnInitializeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::UnInitializeTestL()
    {
  	MCE_CREATE_PROFILE;
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver(managerObserver);
	CleanupStack::PushL( manager );
		
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceSpeakerSink* sink = CMceSpeakerSink::NewLC();	
	stream->AddSinkL( sink );
	CleanupStack::Pop( sink );
		 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	session->InitializeL();

	// Actual testcase
	sink->UnInitialize(*stream);
	EUNIT_ASSERT(sink->iStream==NULL);
	
	// Cleanup
	
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    
    MCE_DELETE_PROFILE;
     
    }

// ----------------------------------------------------------------------------
// CMceMediaSinkTest::CreateEndpointProxyLTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSinkTest::CreateEndpointProxyLTestL()
    {
    CMceSpeakerSink* sink = CMceSpeakerSink::NewLC();
	EUNIT_ASSERT( !sink->CMceMediaSink::CreateEndpointProxyL() );
    CleanupStack::PopAndDestroy( sink );
    }
