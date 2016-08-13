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
#include "CMceMediaStreamTest.h"
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

const TMceMediaType KMediaType = 15;

const TUint KLocalMediaPort = 1;
const TUint KRemoteMediaPort = 65535;

// ----------------------------------------------------------------------------
// CMceMediaStreamTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceMediaStreamTest::setUpL()
    {
    
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManagerObserver = new (ELeave) CMceManagerObserverStub();
    iStreamObserver = new (ELeave) CMceStreamObserverStub();
    
    iManager = CMceManager::NewL( iUid, &iContainer );
    iManager->SetInSessionObserver( iManagerObserver );
    iManager->SetMediaObserver( iStreamObserver );
    
    iAudio = CMceAudioStream::NewL();
    
    }

// ----------------------------------------------------------------------------
// CMceMediaStreamTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::tearDown()
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
    
    delete iAudio;
        
    }


// ----------------------------------------------------------------------------
// CMceMediaStreamTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceMediaStreamTest::suiteL()
    {
    CMceMediaStreamTest* suite = new CMceMediaStreamTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }
    
EUNIT_BEGIN_TEST_TABLE( 
    CMceMediaStreamTest,
    "CMceMediaStreamTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceMediaStreamTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaStreamTest", setUpL, GettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaStreamTest", setUpL, SetLocalMediaPortTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaStreamTest", setUpL, SessionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaStreamTest", setUpL, FactoriesTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaStreamTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaStreamTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaStreamTest", setUpL, SetMediaAttributeLinesTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceMediaStreamTest", setUpL, MediaAttributeLinesTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceMediaStreamTest::ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::ConstructionTestL()
    {
	CMceMediaStream* media = static_cast<CMceMediaStream*>( iAudio );
	
	TRAPD( err, media->ConstructL( NULL ) );
	MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );

	EUNIT_ASSERT( media->Type() == KMceAudio );
    EUNIT_ASSERT( !media->Id().IsAssigned() );
    
    // Call NOP
    media->CMceMediaStream::InitializeL( iManager, *iOutSession );
    }


// ----------------------------------------------------------------------------
// CMceMediaStreamTest::GettersTestL
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::GettersTestL()
    {
	EUNIT_ASSERT_EQUALS( KMceAudio, iAudio->Type() );
 	iAudio->iFlatData->iType = KMediaType; 
 	EUNIT_ASSERT_EQUALS( KMediaType, iAudio->Type() );
	
	iAudio->iFlatData->iID.iAppId = KMceTestAppId;
	iAudio->iFlatData->iID.iId = KMceTestMiscId;
	
 	TMceMediaId id = iAudio->Id();
	EUNIT_ASSERT( id.iAppId == KMceTestAppId );
	EUNIT_ASSERT( id.iId == KMceTestMiscId );
	
	iAudio->iFlatData->iIsEnabled = EFalse;
	EUNIT_ASSERT( !iAudio->IsEnabled() );
	iAudio->iFlatData->iIsEnabled = ETrue;
	EUNIT_ASSERT( iAudio->IsEnabled() );
	
	EUNIT_ASSERT( 5000 == iAudio->LocalMediaPort() );
	iAudio->iFlatData->iLocalMediaPort = KLocalMediaPort;
	EUNIT_ASSERT( KLocalMediaPort == iAudio->LocalMediaPort() );	
	
    }

// ----------------------------------------------------------------------------
// CMceMediaStreamTest::SetLocalMediaPortTestL
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::SetLocalMediaPortTestL()
    {
	iAudio->SetLocalMediaPortL( KLocalMediaPort );
	EUNIT_ASSERT( KLocalMediaPort == iAudio->LocalMediaPort() );		
    }

// ----------------------------------------------------------------------------
// CMceMediaStreamTest::SessionTestL
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::SessionTestL()
    {
	EUNIT_ASSERT( !iAudio->Session() );
	
	iAudio->iSession = iOutSession;
	
	EUNIT_ASSERT( iAudio->Session() == iOutSession );
    }

// ----------------------------------------------------------------------------
// CMceMediaStreamTest::FactoriesTestL
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::FactoriesTestL()
    {
    TMceMediaStreamFactory streamFactory = CMceMediaStream::Factory();
    TMceMediaStreamFactory* ptrStreamFactory = &streamFactory;
    EUNIT_ASSERT( ptrStreamFactory != NULL );

    // TMceMediaStreamFactory::CreateLC( TMceMediaType aType )
    // KMceAudio
    CMceMediaStream* audioStream = streamFactory.CreateLC( KMceAudio );
    EUNIT_ASSERT( audioStream != NULL );
    CleanupStack::PopAndDestroy( audioStream );
    // default
    CMceMediaStream* otherStream = NULL;
    TRAPD( err, otherStream = streamFactory.CreateLC( (TMceMediaType)(KErrNotFound) ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
    EUNIT_ASSERT_EQUALS( err, KErrNotSupported );
    EUNIT_ASSERT( otherStream == NULL );
    
    TMceFactory baseFactory = iAudio->BaseFactory();
    TMceFactory* ptrBaseFactory = &baseFactory;
    EUNIT_ASSERT( ptrBaseFactory != NULL );

    }

// ----------------------------------------------------------------------------
// CMceMediaStreamTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::ExternalizeTestL()
    {
    iAudio->iFlatData->iType = KMediaType; 
	iAudio->iFlatData->iID.iAppId = KMceTestAppId;
	iAudio->iFlatData->iID.iId = KMceTestMiscId;
	iAudio->iFlatData->iIsEnabled = ETrue;
	iAudio->iFlatData->iLocalMediaPort = KLocalMediaPort;
	iAudio->iFlatData->iRemoteMediaPort = KRemoteMediaPort;
	
	CDesC8Array* array = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
	CleanupStack::PushL( array );
	
	array->AppendL( KMceMedialine1 );
	array->AppendL( KMceMedialine2 );
	
	CleanupStack::Pop( array );
	
	TInt arrayCount = array->Count();

	TInt line1Length = KMceMedialine1().Length();
	TInt line2Length = KMceMedialine2().Length();
	
	delete iAudio->iFlatData->iLocalMediaSDPLines;
	iAudio->iFlatData->iLocalMediaSDPLines = array;

    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iAudio->ExternalizeL( serCtx );
	CleanupStack::PopAndDestroy();// serCtx
	writeStream.Close();
	writeStream.Pop();
	
	RDesReadStream readStream( buffer );
	readStream.PushL();	

	EUNIT_ASSERT_EQUALS( KMediaType, readStream.ReadUint8L() );
	EUNIT_ASSERT( KMceTestAppId == readStream.ReadUint32L() );
	EUNIT_ASSERT( KMceTestMiscId == readStream.ReadUint32L() );
	EUNIT_ASSERT_EQUALS( ETrue, readStream.ReadUint8L() );
	EUNIT_ASSERT_EQUALS( KLocalMediaPort, readStream.ReadUint16L() );
	EUNIT_ASSERT_EQUALS( KRemoteMediaPort, readStream.ReadUint16L() );
	
	EUNIT_ASSERT_EQUALS( arrayCount, readStream.ReadUint32L() );
	
	EUNIT_ASSERT_EQUALS( line1Length, readStream.ReadUint32L() );
	TBuf8<500> line1;	
	readStream.ReadL( line1, line1Length );
	EUNIT_ASSERT_EQUALS( KMceMedialine1(), line1 );

	EUNIT_ASSERT_EQUALS( line2Length, readStream.ReadUint32L() );
	TBuf8<500> line2;	
	readStream.ReadL( line2, line2Length );
	EUNIT_ASSERT_EQUALS( KMceMedialine2(), line2 );

	readStream.Close();
	readStream.Pop();		
    }
    
// ----------------------------------------------------------------------------
// CMceMediaStreamTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::InternalizeTestL()
    {

    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();

	writeStream.WriteUint8L( KMediaType );
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( ETrue );	// iIsEnabled
	writeStream.WriteUint16L( KLocalMediaPort );
	writeStream.WriteUint16L( KRemoteMediaPort );
	
	// local SDP lines
	writeStream.WriteUint32L( 2 ); // Size of iLocalMediaSDPLines
	writeStream.WriteUint32L( KMceMedialine1().Length() );
	writeStream.WriteL( KMceMedialine1 );
	writeStream.WriteUint32L( KMceMedialine2().Length() );
	writeStream.WriteL( KMceMedialine2 );
	
	// remote SDP lines
	writeStream.WriteUint32L( 2 ); // Size of iRemoteMediaSDPLines
	writeStream.WriteUint32L( KMceMedialine2().Length() );
	writeStream.WriteL( KMceMedialine2 );
	writeStream.WriteUint32L( KMceMedialine1().Length() );
	writeStream.WriteL( KMceMedialine1 );

	writeStream.WriteUint8L( EFalse ); // iLinkOwner
	writeStream.WriteUint8L( CMceMediaStream::EIdle ); // iState
	writeStream.WriteUint8L( EFalse ); // iIgnoreRemotePort
	writeStream.WriteUint8L( EFalse ); 	// isSource == FALSE
	writeStream.WriteUint32L( 0 );		// sinkCount 
	
	// Write also AudioStream's members	

	writeStream.WriteUint32L( 0 );		// codecCount 

	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    iAudio->InternalizeL( serCtx );

    EUNIT_ASSERT_EQUALS( KMediaType, iAudio->iFlatData->iType );
    EUNIT_ASSERT( iAudio->iFlatData->Id().iAppId == KMceTestAppId );
    EUNIT_ASSERT( iAudio->iFlatData->Id().iId == KMceTestMiscId );
    EUNIT_ASSERT_EQUALS( ETrue, iAudio->iFlatData->iIsEnabled );
    EUNIT_ASSERT_EQUALS( KLocalMediaPort, iAudio->iFlatData->iLocalMediaPort);
    EUNIT_ASSERT_EQUALS( KRemoteMediaPort, iAudio->iFlatData->iRemoteMediaPort );

	EUNIT_ASSERT_EQUALS( 2, iAudio->iFlatData->iLocalMediaSDPLines->Count() );
	EUNIT_ASSERT( (*(iAudio->iFlatData->iLocalMediaSDPLines))[0] == KMceMedialine1 );
	EUNIT_ASSERT( (*(iAudio->iFlatData->iLocalMediaSDPLines))[1] == KMceMedialine2 );

    EUNIT_ASSERT_EQUALS( 2, iAudio->iFlatData->iRemoteMediaSDPLines->Count() );
    EUNIT_ASSERT( (*(iAudio->iFlatData->iRemoteMediaSDPLines))[0] == KMceMedialine2 );
	EUNIT_ASSERT( (*(iAudio->iFlatData->iRemoteMediaSDPLines))[1] == KMceMedialine1 );
	
    EUNIT_ASSERT( !iAudio->iFlatData->iSource );
    
    EUNIT_ASSERT_EQUALS( 0, iAudio->iFlatData->iSinks.Count() );
    EUNIT_ASSERT_EQUALS( 0, static_cast< CMceComAudioStream* >( iAudio->iFlatData ) 
        ->CodecCount() );
    
    CleanupStack::PopAndDestroy();//serCtx	
    readStream.Close();
    
    readStream.Pop();
    }

// ----------------------------------------------------------------------------
// CMceMediaStreamTest::SetMediaAttributeLinesTestL
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::SetMediaAttributeLinesTestL()
    {
    // no session
    CDesC8Array* lines = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( lines );
    iAudio->SetMediaAttributeLinesL( lines );
    CleanupStack::Pop( lines );
    
    CDesC8Array* flatDataLines = iAudio->iFlatData->iLocalMediaSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaCount() );
    
    // session idle
    MCE_CREATE_PROFILE;
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    EUNIT_ASSERT( iOutSession->State() == CMceSession::EIdle );
    
    iOutSession->AddStreamL( iAudio );
    CMceMediaStream* audio = iAudio;
    iAudio = NULL; //ownership in session
    
    lines = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( lines );
    lines->AppendL( KMceAttr1 );
    lines->AppendL( KMceAttr2 );
    
    audio->SetMediaAttributeLinesL( lines );
    CleanupStack::Pop( lines );
    
    flatDataLines = audio->iFlatData->iLocalMediaSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 2, flatDataLines->MdcaCount() );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaPoint( 0 ).Compare( KMceAttr1 ) );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaPoint( 1 ).Compare( KMceAttr2 ) );
    
    MCE_DELETE_PROFILE;
    
    MCE_DELETE( iOutSession );
    
    // session incoming, there's linked stream
    MCE_INCOMING_SESSION( iManager, KMceTestSessionId1 );
    EUNIT_ASSERT( iManager->Sessions().Count() == 1 );
    
    iInSession = static_cast<CMceInSession*>( iManager->Sessions()[0] );
    EUNIT_ASSERT( iInSession->State() == CMceSession::EIncoming );
    
    iAudio = CMceAudioStream::NewL();
    CMceAudioStream* bound = CMceAudioStream::NewLC();
    iAudio->BindL( bound );
    CleanupStack::Pop( bound );
    iInSession->AddStreamL( iAudio );
    audio = iAudio;
    iAudio = NULL; //ownership in session
    iInSession->InitializeL();
    
    lines = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( lines );
    lines->AppendL( KMceAttr1 );
    lines->AppendL( KMceAttr2 );
    
    audio->SetMediaAttributeLinesL( lines );
    CleanupStack::Pop( lines );
    flatDataLines = audio->iFlatData->iLocalMediaSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 2, flatDataLines->MdcaCount() );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaPoint( 0 ).Compare( KMceAttr1 ) );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaPoint( 1 ).Compare( KMceAttr2 ) );
    
    CDesC8Array* boundFlatDataLines = bound->iFlatData->iLocalMediaSDPLines;
    EUNIT_ASSERT( boundFlatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 2, boundFlatDataLines->MdcaCount() );
    EUNIT_ASSERT_EQUALS( 0, boundFlatDataLines->MdcaPoint( 0 ).Compare( KMceAttr1 ) );
    EUNIT_ASSERT_EQUALS( 0, boundFlatDataLines->MdcaPoint( 1 ).Compare( KMceAttr2 ) );
    
    // session established, called with NULL on bound
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::EEstablished, KMceNotAssigned );
    
    bound ->SetMediaAttributeLinesL( NULL );
    flatDataLines = audio->iFlatData->iLocalMediaSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 0, flatDataLines->MdcaCount() );
    
    boundFlatDataLines = bound->iFlatData->iLocalMediaSDPLines;
    EUNIT_ASSERT( boundFlatDataLines != NULL );
    EUNIT_ASSERT_EQUALS( 0, boundFlatDataLines->MdcaCount() );
    
    // session in wrong state
    MCE_SESSION_STATECHANGE( iInSession, CMceSession::ETerminated, KMceNotAssigned );
    EUNIT_ASSERT( iInSession->State() == CMceSession::ETerminated );
    lines = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( lines );
    lines->AppendL( KMceAttr1 );
    lines->AppendL( KMceAttr2 );
    
    TRAPD( error2, audio->SetMediaAttributeLinesL( lines ) );
    CleanupStack::PopAndDestroy( lines );
    EUNIT_ASSERT_EQUALS( error2, KErrNotReady );
    }
    
// ----------------------------------------------------------------------------
// CMceMediaStreamTest::MediaAttributeLinesTestL
// ----------------------------------------------------------------------------
//
void CMceMediaStreamTest::MediaAttributeLinesTestL()
    {
    CDesC8Array* flatDataLines = iAudio->iFlatData->iRemoteMediaSDPLines;
    EUNIT_ASSERT( flatDataLines != NULL );
    flatDataLines->AppendL( KMceAttr1 );
    flatDataLines->AppendL( KMceAttr2 );
    
    MDesC8Array* mediaAttributeLines = iAudio->MediaAttributeLinesL();
    EUNIT_ASSERT( mediaAttributeLines != NULL );
    CleanupDeletePushL( mediaAttributeLines );
    EUNIT_ASSERT_EQUALS( 2, mediaAttributeLines->MdcaCount() );
    EUNIT_ASSERT_EQUALS( 0, mediaAttributeLines->MdcaPoint( 0 ).Compare( KMceAttr1 ) );
    EUNIT_ASSERT_EQUALS( 0, mediaAttributeLines->MdcaPoint( 1 ).Compare( KMceAttr2 ) );
    CleanupStack::PopAndDestroy();
    }
