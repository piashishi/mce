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
#include "CMceMediaSourceTest.h"
#include "mcetestdefs.h"

#include "mcestubs.h"
#include "mcemanager.h"
#include "MCEFactory.h"
#include "mcemicsource.h"
#include "mcecommediasource.h"
#include "mcesession.h"
#include "mceoutsession.h"
#include "mceaudiostream.h"
#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mceevents.h"
#include "mcertpsource.h"
#include "mcecommicsource.h"

const TUint8 KMceTestCategory =5;
const TChar KTestTone = 'A';
_LIT( KTestSequence, "01234567890abcd#p123");

// ----------------------------------------------------------------------------
// CMceMediaSourceTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceMediaSourceTest::setUpL()
    {
	iMic = CMceMicSource::NewL();
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::tearDown()
    {
    delete iMic;
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceMediaSourceTest::suiteL()
    {
    CMceMediaSourceTest* suite = new CMceMediaSourceTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceMediaSourceTest,
    "CMceMediaSourceTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, GettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, FactoryTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, DoDisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, DoEnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, InitializeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, HandleEventTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, EventReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, UpdatedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, SetGainTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, GainTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, MaxGainTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, SerializationIdTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, UnInitializeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, StartDtmfToneTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, StopDtmfToneTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, SendDtmfToneTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, SendDtmfToneSequenceTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaSourceTest", setUpL, CancelDtmfToneSequenceTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::ConstructionTestL()
    {
    CMceMediaSource* mediaSource = static_cast<CMceMediaSource*>(iMic);
    
 	TRAPD( err, mediaSource->ConstructL( NULL ) );
 	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
 	EUNIT_ASSERT_EQUALS( KErrArgument, err );
    }


// ----------------------------------------------------------------------------
// CMceMediaSourceTest::GettersTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::GettersTestL()
    {
 	TMceMediaId id = iMic->Id();
	EUNIT_ASSERT( id.iAppId == KMceNotAssigned);
	EUNIT_ASSERT( id.iId == KMceNotAssigned);
	   
    EUNIT_ASSERT( iMic->Type() == KMceMicSource );
    iMic->iFlatData->iType = KMceTestSourceType;
    EUNIT_ASSERT( iMic->Type() == KMceTestSourceType );
    
    iMic->iFlatData->Enabled ( KMceTestEnabledTrue );
    EUNIT_ASSERT( iMic->IsEnabled() );
    iMic->iFlatData->Enabled ( KMceTestEnabledFalse );
    EUNIT_ASSERT( !iMic->IsEnabled() );
    }


// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: FactoryTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::FactoryTestL()
    {
    TMceSourceFactory factory = CMceMediaSource::Factory();
    TMceSourceFactory* ptrFactory = &factory;
    
    EUNIT_ASSERT( ptrFactory != NULL );
    
    // TMceSourceFactory::CreateLC( TMceSourceType aType )
    // KMceRTPSource
    CMceMediaSource* rtpSource = factory.CreateLC( KMceRTPSource );
    EUNIT_ASSERT( rtpSource != NULL );
    CleanupStack::PopAndDestroy( rtpSource );
    
    // KMceMicSource
    CMceMediaSource* micSource = factory.CreateLC( KMceMicSource );
    EUNIT_ASSERT( micSource != NULL );
    CleanupStack::PopAndDestroy( micSource );
    
    //default
    CMceMediaSource* otherSource = NULL;
    TRAPD( err, otherSource = factory.CreateLC( ( TMceSourceType )( KErrNotFound ) ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotSupported );
    EUNIT_ASSERT( otherSource == NULL );
    }


// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: DoDisableTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::DoDisableTestL()
    {
   
    // Disable as not assigned 
  	iMic->iFlatData->Enabled ( ETrue );
  	iMic->DisableL();
  	EUNIT_ASSERT( !iMic->iFlatData->IsEnabled ());
  	
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
    manager->SetInSessionObserver( managerObserver );
	CleanupStack::PushL( manager );
    
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceMicSource* source = CMceMicSource::NewLC();
	source->iFlatData->Enabled ( EFalse );
	stream->SetSourceL( source );
	CleanupStack::Pop( source );
     
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	session->InitializeL();

	// Actual testcase
	
	source->DisableL();
	EUNIT_ASSERT( !source->iFlatData->IsEnabled ());
	
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
// CMceMediaSourceTest:: DoEnableTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::DoEnableTestL()
    {
    
    // Enable as not assigned 
  	iMic->iFlatData->Enabled ( EFalse );
  	iMic->EnableL();
  	EUNIT_ASSERT( iMic->iFlatData->IsEnabled () );
  	
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
    manager->SetInSessionObserver( managerObserver );
	CleanupStack::PushL( manager );
    	
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceAudioStream* stream = CMceAudioStream::NewLC();
  
	CMceMicSource* source = CMceMicSource::NewLC();
	source->iFlatData->Enabled ( EFalse );
	stream->SetSourceL( source );
	CleanupStack::Pop( source );
     
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	session->InitializeL();

	// Actual testcase
	
	source->EnableL();
	EUNIT_ASSERT( source->iFlatData->IsEnabled () );
	
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
// CMceMediaSourceTest:: ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::ExternalizeTestL()
    {
    iMic->iFlatData->iCategory = KMceTestCategory;
    iMic->iFlatData->iID.iAppId = KMceTestAppId;
    iMic->iFlatData->iID.iId = KMceTestMiscId; 
    iMic->iFlatData->iType = KMceTestSourceType;
    iMic->iFlatData->Enabled ( KMceTestEnabledFalse );
    static_cast<CMceComMicSource*>( iMic->iFlatData )->iGain = KMceTestGain;
    
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    

    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iMic->ExternalizeL( serCtx );
    CleanupStack::PopAndDestroy();//serCtx
	writeStream.Close();
	writeStream.Pop();
	
	RDesReadStream readStream( buffer );
	readStream.PushL();
	
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestSourceType );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestCategory );
	EUNIT_ASSERT( KMceTestAppId == readStream.ReadUint32L() );
	EUNIT_ASSERT( KMceTestMiscId == readStream.ReadUint32L() );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestEnabledFalse );
	EUNIT_ASSERT( readStream.ReadInt32L() == KMceTestGain );
	
	readStream.Close();
	readStream.Pop();


    }


// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::InternalizeTestL()
    {

    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();
    
    writeStream.WriteUint8L( KMceTestSourceType );
    writeStream.WriteUint8L( KMceTestCategory );
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( KMceTestEnabledFalse );
    writeStream.WriteInt32L( KMceTestGain );
    
	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    iMic->InternalizeL( serCtx );
    
    EUNIT_ASSERT( iMic->iFlatData->iType == KMceTestSourceType );
    EUNIT_ASSERT( iMic->iFlatData->IsEnabled() == KMceTestEnabledFalse );
    EUNIT_ASSERT( iMic->iFlatData->Id().iAppId == KMceTestAppId );
    EUNIT_ASSERT( iMic->iFlatData->Id().iId == KMceTestMiscId );
    EUNIT_ASSERT( static_cast<CMceComMicSource*>( iMic->iFlatData )->iGain == KMceTestGain );
    
    CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();
    
    }


// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: InitializeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::InitializeTestL()
    {
  
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver( managerObserver );
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );
    
    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
    
    stream->InitializeL( *session, EFalse );
    iMic->InitializeL( *stream ); //Sink is not added to stream, no matter
    iMic->StreamAddedL( *stream );
    EUNIT_ASSERT( iMic->iStream == stream );
    TMceMediaId id = iMic->Id();
	EUNIT_ASSERT( id.iAppId != KMceNotAssigned );
	EUNIT_ASSERT( id.iId != KMceNotAssigned );	
	
    iMic->InitializeL( *stream ); // ID alreaydy set, must not change
    EUNIT_ASSERT( iMic->iStream == stream );  
    EUNIT_ASSERT( iMic->Id().iAppId == id.iAppId );
	EUNIT_ASSERT( iMic->Id().iId == id.iId );
	    
    CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );

    }


// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: HandleEventTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::HandleEventTestL()
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
    manager->SetInSessionObserver( managerObserver );
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );
    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream );    
	iMic->StreamAddedL( *stream );
    
    // Actual testcase
    
	TMceMediaId id;
	id.iAppId = KMceTestAppId;
	id.iId = KMceTestMiscId;

	TMceIds ids;
	ids.iCallbackID = KMceNotAssigned;	
	TMceEvent event( ids, NULL, NULL );  
	TInt status = iMic->HandleEvent( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );
	
	ids.iCallbackID = EMceItcStateChanged; 
	ids.iMsgType = EMceItcMsgTypeSource;
	status = iMic->HandleEvent( event );	
	EUNIT_ASSERT_EQUALS( KMceEventUpdate, status );
	
	ids.iMsgType = EMceItcMsgTypeSession;
	ids.iState = KMceTestEnabledTrue;
	iMic->iFlatData->Enabled ( KMceTestEnabledFalse );
	
	status = iMic->HandleEvent( event );	
	EUNIT_ASSERT_EQUALS( KMceEventConsumed, status );
	EUNIT_ASSERT( iMic->iFlatData->IsEnabled() == KMceTestEnabledTrue);
	
	// Cleanup
	
	CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );

    }
 
    
// ----------------------------------------------------------------------------
// CMceMediaSourceTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::EventReceivedTestL()
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
    manager->SetInSessionObserver( managerObserver );
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );
    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream ); 
	
	// Actual testcase
	
	TMceMediaId id;
	id.iAppId = KMceTestAppId;
	id.iId = KMceTestMiscId;

	TMceIds ids;
	ids.iSourceID = id; 
	TMceEvent event( ids, NULL, NULL );
	
	TInt status = iMic->EventReceivedL( event ); //Ids don't match 
	EUNIT_ASSERT_EQUALS( KMceEventNotOwner, status );
	
	iMic->iFlatData->iID = id; // Make Ids match	
	ids.iCodecID = id;  // Make Id not to be a SourceId
	status = iMic->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );	

	ids.iCodecID = KMceMediaIdNotAssigned;	// Make Id to be a SourceId
	status = iMic->EventReceivedL( event );
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
// CMceMediaSourceTest:: UpdatedTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::UpdatedTestL()
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
    manager->SetInSessionObserver( managerObserver );
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );
    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream );
	iMic->StreamAddedL( *stream );    

	// Call updated with no observer present
	iMic->Updated();
	EUNIT_ASSERT( !streamObserver->iSource );
	EUNIT_ASSERT( !streamObserver->iStream );
	EUNIT_ASSERT_EQUALS( 0, streamObserver->iStateChangedCount );    

	// Call updated with observer present
    manager->SetMediaObserver( streamObserver );
    iMic->Updated();
    EUNIT_ASSERT( streamObserver->iSource == iMic );
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
// CMceMediaSourceTest:: SetGainLTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::SetGainTestL()
    {
    MCE_CREATE_PROFILE;
    
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
 
    CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );    
 	CleanupStack::PushL( session );
 	
 	CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream ); 
	
    iMic->SetGainL( KMceTestGain );
    EUNIT_ASSERT_EQUALS( static_cast<CMceComMicSource*>( iMic->iFlatData )->iGain, KMceTestGain );
    stream->iSession = session;
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: GainTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::GainTestL()
    {
    MCE_CREATE_PROFILE;
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
 
 	CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );    
 	CleanupStack::PushL( session );
 	
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream ); 

    TInt gain = KErrNotFound;
    gain = iMic->GainL();
    EUNIT_ASSERT( gain != KErrNotFound );
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: MaxGainTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::MaxGainTestL()
    {
    MCE_CREATE_PROFILE;
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
 
 	CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );    
 	CleanupStack::PushL( session );
 	
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream ); 
	
    
    // Fail with no session
    stream->iSession = NULL;
    TInt gain = KErrNotFound;
    TRAPD( err, gain = iMic->MaxGainL() );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotReady );
    EUNIT_ASSERT_EQUALS( gain, KErrNotFound );
    stream->iSession = session;
    
    // Successfull
    //gain = iMic->MaxGainL();
    //EUNIT_ASSERT_EQUALS( gain, KMceTestMaxGain );
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: SerializationIdTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::SerializationIdTestL()
    {
  
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver( managerObserver );
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );
    
    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
    
    stream->InitializeL( *session, EFalse );
    iMic->InitializeL( *stream ); //Sink is not added to stream, no matter
    iMic->StreamAddedL( *stream );
    EUNIT_ASSERT( iMic->iStream == stream );
    TMceMediaId id = iMic->Id();
	EUNIT_ASSERT( id.iAppId != KMceNotAssigned );
	EUNIT_ASSERT( id.iId != KMceNotAssigned );	
	
   	//actual test
   	TUint64 serializationId = iMic->SerializationId();
   	EUNIT_ASSERT(serializationId != KMceNotAssigned);
	    
    CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );

    }
    
// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: UnInitializeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::UnInitializeTestL()
    {
  
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    manager->SetInSessionObserver( managerObserver );
	CleanupStack::PushL( manager );
 
 	TMceFactory factory;
 	CMceSession* session = factory.CreateLC( CMceComSession::EInSession );
    
    
    session->iManager = manager;
    
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
    
    stream->InitializeL( *session, EFalse );
    iMic->InitializeL( *stream ); //Sink is not added to stream, no matter
    iMic->StreamAddedL( *stream );
    EUNIT_ASSERT( iMic->iStream == stream );
    TMceMediaId id = iMic->Id();
	EUNIT_ASSERT( id.iAppId != KMceNotAssigned );
	EUNIT_ASSERT( id.iId != KMceNotAssigned );	
	
    iMic->InitializeL( *stream ); // ID alreaydy set, must not change
    EUNIT_ASSERT( iMic->iStream == stream );  
    EUNIT_ASSERT( iMic->Id().iAppId == id.iAppId );
	EUNIT_ASSERT( iMic->Id().iId == id.iId );
	    
	//actual test cases
	iMic->UnInitialize(*stream);  
	EUNIT_ASSERT(iMic->iStream == NULL);
	  
    CleanupStack::PopAndDestroy( session );
    
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );            
    
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: DtmfAvailableTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::DtmfAvailableTestL()
    {
    MCE_CREATE_PROFILE;
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
    
 	CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
 	CleanupStack::PushL( session );
 	
    CMceAudioStream* stream = CMceAudioStream::NewLC();
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream );
	
    iMic->DtmfAvailable();
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: DtmfActiveTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::DtmfActiveTestL()
    {
    MCE_CREATE_PROFILE;
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
    
 	CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
 	CleanupStack::PushL( session );
 	
    CMceAudioStream* stream = CMceAudioStream::NewLC();
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream );
	
    iMic->DtmfActive();
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: StartDtmfToneTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::StartDtmfToneTestL()
    {
    MCE_CREATE_PROFILE;
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
    
 	CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
 	CleanupStack::PushL( session );
 	
    CMceAudioStream* stream = CMceAudioStream::NewLC();
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream );
	
    TRAPD( err, iMic->StartDtmfToneL( KTestTone ) )
    
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotReady );
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: StopDtmfToneTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::StopDtmfToneTestL()
    {
    MCE_CREATE_PROFILE;
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
    
 	CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
 	CleanupStack::PushL( session );
 	
    CMceAudioStream* stream = CMceAudioStream::NewLC();
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream );
	
    TRAPD( err, iMic->StopDtmfToneL() )
    
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotReady );
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: SendDtmfToneTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::SendDtmfToneTestL()
    {
    MCE_CREATE_PROFILE;
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
    
 	CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
 	CleanupStack::PushL( session );
 	
    CMceAudioStream* stream = CMceAudioStream::NewLC();
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream );
	
	TTimeIntervalMicroSeconds32 durat = 5000000;
    TRAPD( err, iMic->SendDtmfToneL( KTestTone, durat ) )
    
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotReady );
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: SendDtmfToneSequenceTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::SendDtmfToneSequenceTestL()
    {
    MCE_CREATE_PROFILE;
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
    
 	CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
 	CleanupStack::PushL( session );
 	
    CMceAudioStream* stream = CMceAudioStream::NewLC();
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream );
	
    TRAPD( err, iMic->SendDtmfToneSequenceL( KTestSequence ) )
    
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotReady );
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    }

// ----------------------------------------------------------------------------
// CMceMediaSourceTest:: CancelDtmfToneSequenceTestL
// ----------------------------------------------------------------------------
//
void CMceMediaSourceTest::CancelDtmfToneSequenceTestL()
    {
    MCE_CREATE_PROFILE;
    CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );
    CMceManager* manager = CMceManager::NewL( uid, &iContainer );
    CleanupStack::PushL( manager );
    
 	CMceSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
 	CleanupStack::PushL( session );
 	
    CMceAudioStream* stream = CMceAudioStream::NewLC();
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );
	
	stream->InitializeL( *session, EFalse );
	iMic->InitializeL( *stream );
	
    TRAPD( err, iMic->CancelDtmfToneSequenceL() )
    
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotReady );
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    MCE_DELETE_PROFILE;
    }
