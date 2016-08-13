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
#include "mceavsinktest.h"
#include "mcetestdefs.h"

#include "mcestubs.h"
#include "mcemanager.h"
#include "MCEFactory.h"
#include "mceavsink.h"
#include "mcecomavsink.h"
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
#include "mcespeakersink.h"
#include "mcecomspeakersink.h"

const TUint8 KMceTestCategory = 5;

// ----------------------------------------------------------------------------
// CMceAvSinkTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceAvSinkTest::setUpL()
    {
	iAV = CMceAvSink::NewL();
    }

// ----------------------------------------------------------------------------
// CMceAvSinkTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::tearDown()
    {
    delete iAV;
    }

// ----------------------------------------------------------------------------
// CMceAvSinkTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceAvSinkTest::suiteL()
    {
    CMceAvSinkTest* suite = new CMceAvSinkTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceAvSinkTest,
    "CMceAvSinkTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, GettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, FactoryTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, DoDisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, DoEnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, InitializeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, HandleEventTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, EventReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, UpdatedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, SetVolumeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, VolumeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, MaxVolumeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, EndPointProxyTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, SerializationIdTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvSinkTest", setUpL, UnInitializeTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceAvSinkTest:: ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::ConstructionTestL()
    {
    CMceAvSink* av = new (ELeave) CMceAvSink();
    CleanupStack::PushL( av );
    av->ConstructL();
    EUNIT_ASSERT( av->iFlatData != NULL );
	CleanupStack::PopAndDestroy(av);
    }


// ----------------------------------------------------------------------------
// CMceAvSinkTest::GettersTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::GettersTestL()
    {
 	TMceMediaId id = iAV->Id();
	EUNIT_ASSERT( id.iAppId == KMceNotAssigned);
	EUNIT_ASSERT( id.iId == KMceNotAssigned);
	   
    EUNIT_ASSERT( iAV->Type() == KMceAvSink );
    iAV->iFlatData->iType = KMceTestSinkType;
    EUNIT_ASSERT( iAV->Type() == KMceTestSinkType );
    
    iAV->iFlatData->Enabled ( KMceTestEnabledTrue);
    EUNIT_ASSERT( iAV->IsEnabled() );
    iAV->iFlatData->Enabled ( KMceTestEnabledFalse );
    EUNIT_ASSERT( !iAV->IsEnabled() );
    }


// ----------------------------------------------------------------------------
// CMceAvSinkTest:: FactoryTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::FactoryTestL()
    {
    TMceSinkFactory factory = CMceAvSink::Factory();
    TMceSinkFactory* ptrFactory = &factory;
    
    EUNIT_ASSERT( ptrFactory != NULL );
    
    // TMceSinkFactory::CreateLC( TMceSinkType aType )
    // KMceRTPSink
    CMceMediaSink* rtpSink = factory.CreateLC( KMceRTPSink );
    EUNIT_ASSERT( rtpSink != NULL );
    CleanupStack::PopAndDestroy( rtpSink );
    
    
    // default
    CMceMediaSink* otherSink = NULL;
    TRAPD( err, otherSink = factory.CreateLC( ( TMceSinkType )( KErrNotFound ) ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotSupported );
    EUNIT_ASSERT( otherSink == NULL );
    }


// ----------------------------------------------------------------------------
// CMceAvSinkTest:: DoDisableTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::DoDisableTestL()
    {
    // Disable as not assigned 
  	iAV->iFlatData->Enabled ( ETrue );
  	iAV->DisableL();
  	EUNIT_ASSERT( !iAV->iFlatData->IsEnabled () );
    }


// ----------------------------------------------------------------------------
// CMceAvSinkTest:: DoEnableTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::DoEnableTestL()
    {
    // Enable as not assigned 
  	iAV->iFlatData->Enabled ( EFalse );
  	iAV->EnableL();
  	EUNIT_ASSERT( iAV->iFlatData->IsEnabled ( ) );
  	
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
// CMceAvSinkTest:: ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::ExternalizeTestL()
    {
    iAV->iFlatData->iID.iAppId = KMceTestAppId;
    iAV->iFlatData->iID.iId = KMceTestMiscId; 
    iAV->iFlatData->iType = KMceTestSinkType;
    iAV->iFlatData->Enabled ( KMceTestEnabledFalse );
    iAV->iFlatData->iCategory = KMceTestCategory;
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iAV->ExternalizeL( serCtx );
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
// CMceAvSinkTest:: InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::InternalizeTestL()
    {

    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();
    
    writeStream.WriteUint8L( KMceTestSinkType );
    writeStream.WriteUint8L( KMceTestCategory );
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( KMceTestEnabledFalse );
    writeStream.WriteInt32L( 3 ); // audioroute
    writeStream.WriteInt32L( 10 ); // volume
    
    
	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    iAV->InternalizeL( serCtx );
    
    EUNIT_ASSERT( iAV->iFlatData->iType == KMceTestSinkType );
    EUNIT_ASSERT( iAV->iFlatData->iCategory == KMceTestCategory );
    EUNIT_ASSERT( iAV->iFlatData->IsEnabled() == KMceTestEnabledFalse );
    EUNIT_ASSERT( iAV->iFlatData->Id().iAppId == KMceTestAppId );
    EUNIT_ASSERT( iAV->iFlatData->Id().iId == KMceTestMiscId );
   
   
    
	CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();
    
    }


// ----------------------------------------------------------------------------
// CMceAvSinkTest:: InitializeTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::InitializeTestL()
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
    iAV->InitializeL( *stream ); //Sink is not added to stream, no matter
    EUNIT_ASSERT( iAV->iStream == stream );
    TMceMediaId id = iAV->Id();
	EUNIT_ASSERT( id.iAppId != KMceNotAssigned );
	EUNIT_ASSERT( id.iId != KMceNotAssigned );	
	
    iAV->InitializeL( *stream ); // ID alreaydy set, must not change
    EUNIT_ASSERT( iAV->iStream == stream );  
    EUNIT_ASSERT( iAV->Id().iAppId == id.iAppId );
	EUNIT_ASSERT( iAV->Id().iId == id.iId );
	    
    CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );

    }


// ----------------------------------------------------------------------------
// CMceAvSinkTest:: HandleEventTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::HandleEventTestL()
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
	iAV->InitializeL( *stream );    
    
    // Actual testcase
    
	TMceMediaId id;
	id.iAppId = KMceTestAppId;
	id.iId = KMceTestMiscId;

	TMceIds ids;
	ids.iCallbackID = KMceNotAssigned;	
	TMceEvent event( ids, NULL, NULL );  
	TInt status = iAV->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );
	
	ids.iCallbackID = EMceItcStateChanged; 
	ids.iMsgType = EMceItcMsgTypeSink;
	status = iAV->HandleEvent( event );	
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );
	
	ids.iMsgType = EMceItcMsgTypeSession;
	ids.iState = KMceTestEnabledTrue;
	iAV->iFlatData->Enabled ( KMceTestEnabledFalse );
	
	status = iAV->HandleEvent( event );	
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );
	EUNIT_ASSERT( iAV->iFlatData->IsEnabled ( ) == KMceTestEnabledFalse);
	
	// Cleanup
	
	CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );

    }
 
    
// ----------------------------------------------------------------------------
// CMceAvSinkTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::EventReceivedTestL()
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
	iAV->InitializeL( *stream ); 
	
	// Actual testcase
	
	TMceMediaId id;
	id.iAppId = KMceTestAppId;
	id.iId = KMceTestMiscId;

	TMceIds ids;
	ids.iSinkID = id; 
	TMceEvent event( ids, NULL, NULL );
	
	TInt status = iAV->EventReceivedL( event ); //Ids don't match 
	EUNIT_ASSERT_EQUALS( KMceEventNotOwner, status );
	
	iAV->iFlatData->iID = id; // Make Ids match	
	ids.iCodecID = id;  // Make Id not to be a SinkId
	status = iAV->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotOwner, status );	

	ids.iCodecID = KMceMediaIdNotAssigned;	// Make Id to be a SinkId
	status = iAV->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotOwner, status );	
	
	// Cleanup
	
	CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    }
    
    
// ----------------------------------------------------------------------------
// CMceAvSinkTest:: UpdatedTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::UpdatedTestL()
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
	iAV->InitializeL( *stream );

	// Call updated with no observer present
	iAV->Updated();
	EUNIT_ASSERT( !streamObserver->iSink );
	EUNIT_ASSERT( !streamObserver->iStream );
	EUNIT_ASSERT_EQUALS( 0, streamObserver->iStateChangedCount );    

	// Call updated with observer present
    manager->SetMediaObserver( streamObserver );
    iAV->Updated();
    
    //Do nothing    
		    
    CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( streamObserver );
    CleanupStack::PopAndDestroy( managerObserver );
    
    }

// ----------------------------------------------------------------------------
// CMceAvSinkTest:: SetVolumeTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::SetVolumeTestL()
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
// CMceAvSinkTest:: VolumeTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::VolumeTestL()
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
// CMceAvSinkTest:: MaxVolumeTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::MaxVolumeTestL()
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
// CMceAvSinkTest:: EndPointProxyTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::EndPointProxyTestL()
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
// CMceAvSinkTest:: SerializationIdTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::SerializationIdTestL()
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
// CMceAvSinkTest:: UnInitializeTestL
// ----------------------------------------------------------------------------
//
void CMceAvSinkTest::UnInitializeTestL()
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
