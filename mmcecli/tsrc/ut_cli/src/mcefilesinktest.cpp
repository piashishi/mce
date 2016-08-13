/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
#include "mcefilesinktest.h"
#include "mcefilesink.h"
#include "mcecomfilesink.h"
#include "mcemanager.h"
#include "mceoutsession.h"
#include "mceaudiostream.h"
#include "mcevideostream.h"
#include "mceserial.h"
#include "mcestubs.h"
#include "mcetestdefs.h"


_LIT16( KTranscodeFileName, "transcodefile" );

const TUint32 KTranscodeSessionId = 2345;
const TInt KQuality = 4;
const TInt KProgress = 7;
const TUint KMceTestCategory = 5;

// ----------------------------------------------------------------------------
// CMceFileSinkTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceFileSinkTest::setUpL()
    {
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
    
    iUid = TUid::Uid( 777 );
    iManager = CMceManager::NewL( iUid, NULL );    
    iFileSink = CMceFileSink::NewL(KMceTestAVFileName() );
    iFileWithoutManager = CMceFileSink::NewL();
    iFileFlatData = static_cast<CMceComFileSink*>(iFileSink->iFlatData);
    }


// ----------------------------------------------------------------------------
// CMceFileSinkTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceFileSinkTest::tearDown()
    {
    delete iFileSink;
    delete iFileWithoutManager;
    delete iManager;
    
    delete iStorage;
    Dll::SetTls( NULL );
    }


// ----------------------------------------------------------------------------
// CMceFileSinkTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceFileSinkTest::suiteL()
    {
    CMceFileSinkTest* suite = new CMceFileSinkTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceFileSinkTest,
    "CMceFileSinkTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceFileSinkTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSinkTest", setUpL, EnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSinkTest", setUpL, DisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSinkTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSinkTest", setUpL, ExternalizeTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceFileSinkTest:: ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceFileSinkTest::ConstructionTestL()
    {
    EUNIT_ASSERT( iFileSink != NULL );
    EUNIT_ASSERT( iFileSink->iFlatData != NULL );
    
    EUNIT_ASSERT( iFileWithoutManager != NULL );
    EUNIT_ASSERT( iFileWithoutManager->iFlatData != NULL );
    
    // Try to initialize with NULL manager
    TRAPD( err, iFileWithoutManager->InitializeL( NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	//Try to initialize with NULL stream
	TRAPD( err1, iFileWithoutManager->InitializeL( iManager ));
	MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )
	EUNIT_ASSERT_EQUALS( KErrArgument, err1 );
	
	// Succeed initializing afterwards
	MCE_CREATE_PROFILE;
	CMceOutSession* session = CMceOutSession::NewL( *iManager,
                                                    *profile,
                                                    KMceRecipient );
    CleanupStack::PushL( session );                                
    
	CMceVideoStream* stream = CMceVideoStream::NewLC();
    iFileWithoutManager->StreamAddedL(*stream);
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );   
	iFileWithoutManager->InitializeL( iManager );
	CMceComFileSink* flat = static_cast<CMceComFileSink*>(iFileWithoutManager->iFlatData);
    EUNIT_ASSERT( flat->iInitialInfoRetrieved );
    
    
    
    // Make abnormal conditions
    flat->iInitialInfoRetrieved = EFalse;
    iFileWithoutManager->InitializeL( iManager );
    EUNIT_ASSERT( flat->iInitialInfoRetrieved );
    iFileWithoutManager->UnInitialize( *stream );
   	CleanupStack::PopAndDestroy( session );
 
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceFileSinkTest::EnableTestL
// ----------------------------------------------------------------------------
//
void CMceFileSinkTest::EnableTestL()
    {
    // As long as CMceDispaySink::EnableL does nothing but
    // calls CMceMediaSource::DoEnableL almost dummy test is enough.
    iFileFlatData->Enabled ( EFalse );
    iFileSink->EnableL();
    EUNIT_ASSERT( iFileFlatData->IsEnabled () );
    }


// ----------------------------------------------------------------------------
// CMceFileSinkTest::DisableTestL
// ----------------------------------------------------------------------------
//
void CMceFileSinkTest::DisableTestL()
    {
    // As long as CMceFileSource::DisableL does nothing but
    // calls CMceMediaSource::DoDisableL almost dummy test is enough.
    iFileFlatData->IsEnabled ( ETrue );
    iFileSink->DisableL();
    EUNIT_ASSERT( !iFileFlatData->IsEnabled ());
    }


// ----------------------------------------------------------------------------
// CMceFileSinkTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceFileSinkTest::InternalizeTestL()
    {
    TBuf8<1500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();
    
    // Write base class data
    writeStream.WriteUint8L( KMceTestSourceType );
    writeStream.WriteUint8L( KMceTestCategory ); 
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( KMceTestEnabledFalse );
    
    
    TMceFileInfo fileInfo = TMceFileInfo();
    fileInfo.iFileName.Append( KMceTestAVFileName16 );
    fileInfo.iDuration = TTimeIntervalMicroSeconds( KMceTestDuration );
    fileInfo.iAudioElementCount = KMceTestAudioElementCount;
    fileInfo.iVideoElementCount = KMceTestVideoElementCount;
    fileInfo.iAudioCodec.Append( KMceTestAudioCodec );
    fileInfo.iVideoCodec.Append( KMceTestVideoCodec );
    TPckgBuf<TMceFileInfo> fileBuf( fileInfo );
    MceSerial::EncodeL( fileBuf, writeStream );
    //iTranscodeInfo
    TMceTranscodeInfo tcInfo = TMceTranscodeInfo();
    tcInfo.iTranscodeSessionId = KTranscodeSessionId;
    tcInfo.iFileName.Append( KTranscodeFileName );
    tcInfo.iQuality = KQuality;
    tcInfo.iProgress = KProgress;
    TPckgBuf<TMceTranscodeInfo> tcInfoBuf( tcInfo );
    MceSerial::EncodeL( tcInfoBuf, writeStream );
    
    writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
	
    iFileSink->InternalizeL( serCtx );
    
   
    EUNIT_ASSERT_EQUALS( 0, iFileFlatData->iFileInfo.iFileName.Compare( KMceTestAVFileName16 ) );
    EUNIT_ASSERT( TTimeIntervalMicroSeconds( KMceTestDuration ) == iFileFlatData->iFileInfo.iDuration );
    EUNIT_ASSERT_EQUALS( KMceTestAudioElementCount, iFileFlatData->iFileInfo.iAudioElementCount );
    EUNIT_ASSERT_EQUALS( KMceTestVideoElementCount, iFileFlatData->iFileInfo.iVideoElementCount );
    EUNIT_ASSERT_EQUALS( 0, iFileFlatData->iFileInfo.iAudioCodec.Compare( KMceTestAudioCodec ) );
    EUNIT_ASSERT_EQUALS( 0, iFileFlatData->iFileInfo.iVideoCodec.Compare( KMceTestVideoCodec ) );
   
     CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();
    }


// ----------------------------------------------------------------------------
// CMceFileSinkTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceFileSinkTest::ExternalizeTestL()
    {
    iFileFlatData->iCategory = KMceTestCategory;
    iFileFlatData->iID.iAppId = KMceTestAppId;
    iFileFlatData->iID.iId = KMceTestMiscId; 
    iFileFlatData->iType = KMceTestSourceType;
    iFileFlatData->Enabled ( KMceTestEnabledFalse );
    
    
    iFileFlatData->iFileInfo.iFileName = KMceTestAVFileName16;
    iFileFlatData->iFileInfo.iDuration = KMceTestDuration;
    iFileFlatData->iFileInfo.iAudioElementCount = KMceTestAudioElementCount;
    iFileFlatData->iFileInfo.iVideoElementCount = KMceTestVideoElementCount;
    iFileFlatData->iFileInfo.iAudioCodec = KMceTestAudioCodec;
    iFileFlatData->iFileInfo.iVideoCodec = KMceTestVideoCodec;
    
    TBuf8<1500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iFileSink->ExternalizeL( serCtx );
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
	
	
    TPckgBuf<TMceFileInfo> fileInfoBuf;
    MceSerial::DecodeL( fileInfoBuf, readStream );
    TMceFileInfo fileInfo = fileInfoBuf();
    EUNIT_ASSERT_EQUALS( 0, fileInfo.iFileName.Compare( KMceTestAVFileName16 ) );
    EUNIT_ASSERT( fileInfo.iDuration == KMceTestDuration );
    EUNIT_ASSERT_EQUALS( KMceTestAudioElementCount, fileInfo.iAudioElementCount );
    EUNIT_ASSERT_EQUALS( KMceTestVideoElementCount, fileInfo.iVideoElementCount );
    EUNIT_ASSERT_EQUALS( 0, fileInfo.iAudioCodec.Compare( KMceTestAudioCodec ) );
    EUNIT_ASSERT_EQUALS( 0, fileInfo.iVideoCodec.Compare( KMceTestVideoCodec ) );
    readStream.Close();
	readStream.Pop();
    }
