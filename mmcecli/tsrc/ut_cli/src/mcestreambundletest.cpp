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
#include "mcestreambundletest.h"
#include "mcestubs.h"
#include "mceevent.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mceinsession.h"
#include "mceoutsession.h"
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
#include "mcefactory.h"
#include "mcestreambundle.h"
#include "mcemediastream.h"


// ----------------------------------------------------------------------------
// CMceStreamBundleTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceStreamBundleTest::setUpL()
    {
    
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManagerObserver = new (ELeave) CMceManagerObserverStub();
    iStreamObserver = new (ELeave) CMceStreamObserverStub();
    
    iManager = CMceManager::NewL( iUid, &iContainer );
    iManager->SetInSessionObserver( iManagerObserver );
    iManager->SetMediaObserver( iStreamObserver );
    
    iStreamBundle = CMceStreamBundle::NewL( CMceStreamBundle::ELS );
    
    }

// ----------------------------------------------------------------------------
// CMceStreamBundleTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceStreamBundleTest::tearDown()
    {
    if ( iInSession )
        {
        MCE_TEST_DELETE( iInSession );
        }
    
    if ( iOutSession )
        {
        MCE_TEST_DELETE( iOutSession );
        }
    
    
    MCE_MAN_DELETE( iManager );

    delete iManagerObserver;
    delete iStreamObserver;
    
    delete iStorage;
    Dll::SetTls( NULL );
    
    delete iStreamBundle;
        
    }


// ----------------------------------------------------------------------------
// CMceStreamBundleTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceStreamBundleTest::suiteL()
    {
    CMceStreamBundleTest* suite = new CMceStreamBundleTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceStreamBundleTest,
    "CMceStreamBundleTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceStreamBundleTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceStreamBundleTest", setUpL, GettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceStreamBundleTest", setUpL, AddStreamTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceStreamBundleTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceStreamBundleTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceStreamBundleTest", setUpL, AddTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceStreamBundleTest::ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceStreamBundleTest::ConstructionTestL()
    {
	CMceStreamBundle* bundle = new (ELeave) CMceStreamBundle();
    CleanupStack::PushL( bundle );
    bundle->ConstructL( CMceStreamBundle::EFID  );
    
	EUNIT_ASSERT( bundle->iFlatData->Type()  == CMceStreamBundle::EFID );
	EUNIT_ASSERT( bundle->SerializationId() != KMceNotAssigned );
    // Call NOP
    bundle->InitializeL( *iOutSession );
    CleanupStack::PopAndDestroy( bundle );
    }


// ----------------------------------------------------------------------------
// CMceStreamBundleTest::GettersTestL
// ----------------------------------------------------------------------------
//
void CMceStreamBundleTest::GettersTestL()
    {
	EUNIT_ASSERT_EQUALS( CMceStreamBundle::ELS, iStreamBundle->Type() );
 	iStreamBundle->iFlatData->iBundleType = CMceStreamBundle::EFID; 
 	EUNIT_ASSERT_EQUALS( CMceStreamBundle::EFID, iStreamBundle->Type() );
	
	iStreamBundle->iFlatData->iID.iAppId = KMceTestAppId;
	iStreamBundle->iFlatData->iID.iId = KMceTestMiscId;
	
 	EUNIT_ASSERT( iStreamBundle->SerializationId() != KMceNotAssigned );
    }


// ----------------------------------------------------------------------------
// CMceStreamBundleTest::FactoriesTestL
// ----------------------------------------------------------------------------
//
void CMceStreamBundleTest::AddStreamTestL()
    {
    iAudio = CMceAudioStream::NewL();
    EUNIT_ASSERT(!iStreamBundle->Streams().Count());
    iStreamBundle->AddStreamL(*iAudio);
    EUNIT_ASSERT_EQUALS ( 1, iStreamBundle->Streams().Count());
    iStreamBundle->RemoveStreamL(*iAudio);
    EUNIT_ASSERT(!iStreamBundle->Streams().Count());
    delete iAudio;
    }

// ----------------------------------------------------------------------------
// CMceStreamBundleTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceStreamBundleTest::ExternalizeTestL()
    {
    iStreamBundle->InitializeL(*iOutSession);
    iStreamBundle->iFlatData->iBundleType = CMceStreamBundle::EFID; 
	iStreamBundle->iFlatData->iID.iAppId = KMceTestAppId;
	iStreamBundle->iFlatData->iID.iId = KMceTestMiscId;

    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iStreamBundle->ExternalizeL( serCtx );
	CleanupStack::PopAndDestroy();// serCtx
	writeStream.Close();
	writeStream.Pop();
	
	RDesReadStream readStream( buffer );
	readStream.PushL();	

	EUNIT_ASSERT_EQUALS( CMceStreamBundle::EFID, readStream.ReadUint8L() );
	EUNIT_ASSERT( KMceTestAppId == readStream.ReadUint32L() );
	EUNIT_ASSERT( KMceTestMiscId == readStream.ReadUint32L() );

	readStream.Close();
	readStream.Pop();		
    }
    
// ----------------------------------------------------------------------------
// CMceStreamBundleTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceStreamBundleTest::InternalizeTestL()
    {

    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();

	writeStream.WriteUint8L( CMceStreamBundle::EFID );
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    
	// Write also AudioStream's members	

	writeStream.WriteUint32L( 1 );		// streamcount 
	writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
	
	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
	iStreamBundle->InitializeL(*iOutSession);
    TRAPD( err, iStreamBundle->InternalizeL( serCtx ) );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	//initial the out session
	MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EIdle );
    iStreamBundle->InitializeL(*iOutSession);
    iAudio = CMceAudioStream::NewL();
    iAudio->iFlatData->iID.iAppId = KMceTestAppId;
	iAudio->iFlatData->iID.iId = KMceTestMiscId;
    iOutSession->AddStreamL(iAudio);
	iStreamBundle->InternalizeL( serCtx );
	
    EUNIT_ASSERT_EQUALS( CMceStreamBundle::EFID, iStreamBundle->iFlatData->iBundleType );
    EUNIT_ASSERT( iStreamBundle->iFlatData->iID.iAppId == KMceTestAppId );
    EUNIT_ASSERT( iStreamBundle->iFlatData->iID.iId == KMceTestMiscId );
    
    MCE_DELETE_PROFILE;
    
    
    CleanupStack::PopAndDestroy();//serCtx	
    readStream.Close();
    
    readStream.Pop();
    }

// ----------------------------------------------------------------------------
// CMceStreamBundleTest::SetMediaAttributeLinesTestL
// ----------------------------------------------------------------------------
//
void CMceStreamBundleTest::AddTestL()
    {
    iAudio = CMceAudioStream::NewL();
    CMceAudioStream* bound = CMceAudioStream::NewL();
    CleanupStack::PushL(bound);
    iAudio->BindL( bound );
    CleanupStack::Pop(bound);
    
    CMceRtpSink* rtpSink = CMceRtpSink::NewLC();
    EUNIT_ASSERT( !rtpSink->Id().IsAssigned() );
    EUNIT_ASSERT( rtpSink->IsEnabled() );
    
    iAudio->BoundStreamL().AddSinkL( rtpSink );
    
    CleanupStack::Pop(rtpSink);
    
    iStreamBundle->AddStreamL( *iAudio );
    
    
    TRAPD( err, iStreamBundle->AddedL() );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNone, err );
	iAudio->BoundStreamL().RemoveSinkL(*rtpSink);
	delete iAudio;	
    }
