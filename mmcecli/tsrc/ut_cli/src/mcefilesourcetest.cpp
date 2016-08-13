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
#include "mcefilesourcetest.h"
#include "mcefilesource.h"
#include "mcecomfilesource.h"
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
const TUint8 KMceTestCategory = 5;
// ----------------------------------------------------------------------------
// CMceFileSourceTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceFileSourceTest::setUpL()
    {
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
    
    iUid = TUid::Uid( 777 );
    iManager = CMceManager::NewL( iUid, NULL );    
    iFileSource = CMceFileSource::NewL( *iManager, KMceTestAVFileName() );
    iFileWithoutManager = CMceFileSource::NewL();
    iFileFlatData = static_cast<CMceComFileSource*>(iFileSource->iFlatData);
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::tearDown()
    {
    delete iFileSource;
    delete iFileWithoutManager;
    delete iManager;
    
    delete iStorage;
    Dll::SetTls( NULL );
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceFileSourceTest::suiteL()
    {
    CMceFileSourceTest* suite = new CMceFileSourceTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }
    
EUNIT_BEGIN_TEST_TABLE( 
    CMceFileSourceTest,
    "CMceFileSourceTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, EnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, DisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, DisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, DisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, MediaElementCountTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, SetCurrentMediaElementTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, CurrentMediaElementTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, SetPositionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, PositionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, DurationTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, SetFastForwardTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, SetFastRewindTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFileSourceTest", setUpL, ExternalizeTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceFileSourceTest:: ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::ConstructionTestL()
    {
    EUNIT_ASSERT( iFileSource != NULL );
    EUNIT_ASSERT( iFileSource->iFlatData != NULL );
    
    EUNIT_ASSERT( iFileWithoutManager != NULL );
    EUNIT_ASSERT( iFileWithoutManager->iFlatData != NULL );
    
    // Try to initialize with NULL manager
    TRAPD( err, iFileWithoutManager->InitializeL( NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	// Succeed initializing afterwards
	iFileWithoutManager->InitializeL( iManager );
	CMceComFileSource* flat = static_cast<CMceComFileSource*>(iFileWithoutManager->iFlatData);
    EUNIT_ASSERT( flat->iInitialInfoRetrieved );
    
    // Make abnormal conditions
    flat->iInitialInfoRetrieved = EFalse;
    iFileWithoutManager->InitializeL( iManager );
    EUNIT_ASSERT( flat->iInitialInfoRetrieved );
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::EnableTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::EnableTestL()
    {
    // As long as CMceDispaySink::EnableL does nothing but
    // calls CMceMediaSource::DoEnableL almost dummy test is enough.
    iFileFlatData->Enabled( EFalse );
    iFileSource->EnableL();
    EUNIT_ASSERT( iFileFlatData->IsEnabled() );
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::DisableTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::DisableTestL()
    {
    // As long as CMceFileSource::DisableL does nothing but
    // calls CMceMediaSource::DoDisableL almost dummy test is enough.
    iFileFlatData->Enabled( ETrue );
    iFileSource->DisableL();
    EUNIT_ASSERT( !iFileFlatData->IsEnabled() );
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::MediaElementCountTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::MediaElementCountTestL()
    {
    TInt audioElements = iFileSource->MediaElementCountL( KMceAudio );
    EUNIT_ASSERT_EQUALS( KMceTestAudioElementCount, audioElements );
    EUNIT_ASSERT_EQUALS( KMceTestVideoElementCount, 
                       iFileSource->MediaElementCountL( KMceVideo ) );
    
    EUNIT_ASSERT_EQUALS( 0, iFileWithoutManager->MediaElementCountL( KMceAudio ) );
    EUNIT_ASSERT_EQUALS( 0, iFileWithoutManager->MediaElementCountL( KMceVideo ) );
    
    // Try also with non-existing mediatype 
    EUNIT_ASSERT_EQUALS( 0, iFileWithoutManager->MediaElementCountL( 555 ) );
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::SetCurrentMediaElementTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::SetCurrentMediaElementTestL()
    {
  
    // Try to set illegal values
    TRAPD( err, iFileSource->SetCurrentMediaElementL( KMceAudio, -1 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
    TRAP( err, iFileSource->SetCurrentMediaElementL( KMceAudio, 
               iFileFlatData->iFileInfo.iAudioElementCount + 1 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	EUNIT_ASSERT_EQUALS( 0, iFileFlatData->iCurrentAudioElement );
	iFileSource->SetCurrentMediaElementL( KMceAudio, 1 );
	EUNIT_ASSERT_EQUALS( 1, iFileFlatData->iCurrentAudioElement );
	
	EUNIT_ASSERT_EQUALS( 0, iFileFlatData->iCurrentVideoElement );
	iFileSource->SetCurrentMediaElementL( KMceVideo, 1 );
	EUNIT_ASSERT_EQUALS( 1, iFileFlatData->iCurrentVideoElement );

    
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::CurrentMediaElementTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::CurrentMediaElementTestL()
    {
    EUNIT_ASSERT_EQUALS( 0, iFileSource->CurrentMediaElement( KMceAudio ) );
    EUNIT_ASSERT_EQUALS( 0, iFileSource->CurrentMediaElement( KMceVideo ) );
    
    iFileFlatData->iCurrentAudioElement = 2;
    iFileFlatData->iCurrentVideoElement = 1;
    
    EUNIT_ASSERT_EQUALS( 2, iFileSource->CurrentMediaElement( KMceAudio ) );
    EUNIT_ASSERT_EQUALS( 1, iFileSource->CurrentMediaElement( KMceVideo ) );
    
    // Try also with non-existing mediatype 
    EUNIT_ASSERT_EQUALS( 0, iFileSource->CurrentMediaElement( 555 ) );
    }    


// ----------------------------------------------------------------------------
// CMceFileSourceTest::SetPositionTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::SetPositionTestL()
    {
    iFileSource->DisableL();
    
    // Try to set illegal values
    TRAPD( err, iFileSource->SetPositionL( TTimeIntervalMicroSeconds( -1 ) ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	TRAP( err, iFileSource->SetPositionL(
	        TTimeIntervalMicroSeconds( iFileSource->DurationL().Int64() + 1 ) ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	// Succesfull case
	
	iFileSource->SetPositionL( TTimeIntervalMicroSeconds( 1 ) );
	EUNIT_ASSERT( iFileFlatData->iPosition == TTimeIntervalMicroSeconds( 1 ) );
	
	// Start to establish session in order to gain ids
    
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = CMceOutSession::NewL( *iManager,
                                                    *profile,
                                                    KMceRecipient );
    CleanupStack::PushL( session );                                                
    CMceVideoStream* stream = CMceVideoStream::NewLC();
    CMceFileSource* file = CMceFileSource::NewLC( *iManager,
                                                  KMceTestAVFileName() );
    file->DisableL();
    stream->SetSourceL( file );
    CleanupStack::Pop( file );
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );   
                        
    CMceComFileSource* fileFlatData = 
            static_cast<CMceComFileSource*>(file->iFlatData);
    
    EUNIT_ASSERT( fileFlatData->iPosition == TTimeIntervalMicroSeconds( 0 ) );
    
    session->EstablishL();     
    
    file->SetPositionL( TTimeIntervalMicroSeconds( 2 ) );
    
    EUNIT_ASSERT( fileFlatData->iPosition == TTimeIntervalMicroSeconds( 2 ) );
    
    CleanupStack::PopAndDestroy( session );
 
    MCE_DELETE_PROFILE;

    }
    

// ----------------------------------------------------------------------------
// CMceFileSourceTest::PositionTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::PositionTestL()
    {
    EUNIT_ASSERT( iFileWithoutManager->PositionL() == TTimeIntervalMicroSeconds( 0 ) );
    EUNIT_ASSERT( iFileSource->PositionL() == TTimeIntervalMicroSeconds( 0 ) );
    
    // Try with ids, but without stream and session => class invariant fails
    iFileFlatData->iID.iAppId = 5;
    iFileFlatData->iID.iId = 5;
    EUNIT_ASSERT( iFileSource->PositionL() == 0 );
    
    // Start to establish session in order to gain ids
    
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = CMceOutSession::NewL( *iManager,
                                                    *profile,
                                                    KMceRecipient );
    CleanupStack::PushL( session );                                                
    CMceVideoStream* stream = CMceVideoStream::NewLC();
    CMceFileSource* file = CMceFileSource::NewLC( *iManager,
                                                  KMceTestAVFileName() );
    stream->SetSourceL( file );
    CleanupStack::Pop( file );
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );   
                        
    CMceComFileSource* fileFlatData = 
            static_cast<CMceComFileSource*>(file->iFlatData);
    
    EUNIT_ASSERT( file->PositionL() == TTimeIntervalMicroSeconds( 0 ) );
    EUNIT_ASSERT( fileFlatData->iPosition == TTimeIntervalMicroSeconds( 0 ) );
    
    session->EstablishL();     
    
    EUNIT_ASSERT( file->PositionL() == KMceTestPosition );
    EUNIT_ASSERT( fileFlatData->iPosition == KMceTestPosition );
    
    CleanupStack::PopAndDestroy( session );
 
    MCE_DELETE_PROFILE;
    
    }    


// ----------------------------------------------------------------------------
// CMceFileSourceTest::DurationTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::DurationTestL()
    {
    EUNIT_ASSERT( iFileWithoutManager->DurationL().Int64() == (TInt64)(0) );
    EUNIT_ASSERT( iFileSource->DurationL().Int64() == KMceTestDuration );
    }    


// ----------------------------------------------------------------------------
// CMceFileSourceTest::SetFastForwardTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::SetFastForwardTestL()
    {
    // Try to set fast forward without video elements
    TRAPD( err, iFileWithoutManager->SetFastForwardL( ETrue ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotSupported, err );
	
	// Try with ids, but without stream and session => class invariant fails
    iFileFlatData->iID.iAppId = 5;
    iFileFlatData->iID.iId = 5;
    
    iFileSource->SetFastForwardL( EFalse );

	// Succesfull case
	EUNIT_ASSERT( !iFileFlatData->iFastForward );
	iFileSource->SetFastForwardL( ETrue );
	EUNIT_ASSERT( iFileFlatData->iFastForward );
	
	iFileSource->SetFastForwardL( EFalse );
	EUNIT_ASSERT( !iFileFlatData->iFastForward );
	
	// Set fast forward when fast rewind is ongoing
    iFileFlatData->iFastRewind = ETrue;
	
    iFileSource->SetFastForwardL( ETrue );
    EUNIT_ASSERT( iFileFlatData->iFastForward );
    EUNIT_ASSERT( !iFileFlatData->iFastRewind );	

    // Start to establish session in order to gain ids
    
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = CMceOutSession::NewL( *iManager,
                                                    *profile,
                                                    KMceRecipient );
    CleanupStack::PushL( session );                                                
    CMceVideoStream* stream = CMceVideoStream::NewLC();
    CMceFileSource* file = CMceFileSource::NewLC( *iManager,
                                                  KMceTestAVFileName() );
    stream->SetSourceL( file );
    CleanupStack::Pop( file );
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );   
                        
    CMceComFileSource* fileFlatData = 
            static_cast<CMceComFileSource*>(file->iFlatData);
    
    EUNIT_ASSERT( !fileFlatData->iFastForward );
    
    session->EstablishL();     
    
    file->SetFastForwardL( ETrue );
  
    EUNIT_ASSERT( fileFlatData->iFastForward );
    
    CleanupStack::PopAndDestroy( session );
 
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::SetFastRewindTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::SetFastRewindTestL()
    {
    // Try to set fast rewind without video elements
    TRAPD( err, iFileWithoutManager->SetFastRewindL( ETrue ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotSupported, err );
	
	// Try with ids, but without stream and session => class invariant fails
    iFileFlatData->iID.iAppId = 5;
    iFileFlatData->iID.iId = 5;
    iFileSource->SetFastRewindL( EFalse );
    
	// Succesfull case
	EUNIT_ASSERT( !iFileFlatData->iFastRewind );
	iFileSource->SetFastRewindL( ETrue );
	EUNIT_ASSERT( iFileFlatData->iFastRewind );
	
	iFileSource->SetFastRewindL( EFalse );
	EUNIT_ASSERT( !iFileFlatData->iFastRewind );
	
	// Set fast rewind when fast forward is ongoing
    iFileFlatData->iFastForward = ETrue;
	
    iFileSource->SetFastRewindL( ETrue );
    EUNIT_ASSERT( iFileFlatData->iFastRewind );
    EUNIT_ASSERT( !iFileFlatData->iFastForward );
    
    // Start to establish session in order to gain ids
    
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = CMceOutSession::NewL( *iManager,
                                                    *profile,
                                                    KMceRecipient );
    CleanupStack::PushL( session );                                                
    CMceVideoStream* stream = CMceVideoStream::NewLC();
    CMceFileSource* file = CMceFileSource::NewLC( *iManager,
                                                  KMceTestAVFileName() );
    stream->SetSourceL( file );
    CleanupStack::Pop( file );
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );   
                        
    CMceComFileSource* fileFlatData = 
            static_cast<CMceComFileSource*>(file->iFlatData);
    
    EUNIT_ASSERT( !fileFlatData->iFastRewind );
    
    session->EstablishL();     
    
    file->SetFastRewindL( ETrue );
  
    EUNIT_ASSERT( fileFlatData->iFastRewind );
    
    CleanupStack::PopAndDestroy( session );
 
    MCE_DELETE_PROFILE;	
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::InternalizeTestL()
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
    
    // Write file data
    writeStream.WriteUint8L( ETrue ); // iFastForward
    writeStream.WriteUint8L( ETrue ); // iFastRewind
    // iPosition
    TPckgBuf<TTimeIntervalMicroSeconds> positionBuf( TTimeIntervalMicroSeconds( 1 ) );
    MceSerial::EncodeL( positionBuf, writeStream );
    // iFileInfo
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
    writeStream.WriteUint8L( ETrue ); // iInitialInfoRetrieved
    
    writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
	
    iFileSource->InternalizeL( serCtx );
    
    EUNIT_ASSERT( iFileFlatData->iFastForward );
    EUNIT_ASSERT( iFileFlatData->iFastRewind );
    EUNIT_ASSERT( iFileFlatData->iPosition == TTimeIntervalMicroSeconds( 1 ) );
    EUNIT_ASSERT_EQUALS( 0, iFileFlatData->iFileInfo.iFileName.Compare( KMceTestAVFileName16 ) );
    EUNIT_ASSERT( TTimeIntervalMicroSeconds( KMceTestDuration ) == iFileFlatData->iFileInfo.iDuration );
    EUNIT_ASSERT_EQUALS( KMceTestAudioElementCount, iFileFlatData->iFileInfo.iAudioElementCount );
    EUNIT_ASSERT_EQUALS( KMceTestVideoElementCount, iFileFlatData->iFileInfo.iVideoElementCount );
    EUNIT_ASSERT_EQUALS( 0, iFileFlatData->iFileInfo.iAudioCodec.Compare( KMceTestAudioCodec ) );
    EUNIT_ASSERT_EQUALS( 0, iFileFlatData->iFileInfo.iVideoCodec.Compare( KMceTestVideoCodec ) );
    EUNIT_ASSERT( iFileFlatData->iTranscodeInfo.iTranscodeSessionId == KTranscodeSessionId );
    EUNIT_ASSERT_EQUALS( 0,iFileFlatData->iTranscodeInfo.iFileName.Compare( KTranscodeFileName ) );
    EUNIT_ASSERT_EQUALS( KQuality, iFileFlatData->iTranscodeInfo.iQuality );
    EUNIT_ASSERT_EQUALS( KProgress, iFileFlatData->iTranscodeInfo.iProgress );
    EUNIT_ASSERT_EQUALS( ETrue, iFileFlatData->iInitialInfoRetrieved );
    
    CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();
    }


// ----------------------------------------------------------------------------
// CMceFileSourceTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceFileSourceTest::ExternalizeTestL()
    {
    iFileFlatData->iCategory = KMceTestCategory;
    iFileFlatData->iID.iAppId = KMceTestAppId;
    iFileFlatData->iID.iId = KMceTestMiscId; 
    iFileFlatData->iType = KMceTestSourceType;
    iFileFlatData->Enabled( KMceTestEnabledFalse );
    
    iFileFlatData->iFastForward = ETrue;
    iFileFlatData->iFastRewind = ETrue;
    iFileFlatData->iPosition = TTimeIntervalMicroSeconds( 1 );
    iFileFlatData->iFileInfo.iFileName = KMceTestAVFileName16;
    iFileFlatData->iFileInfo.iDuration = KMceTestDuration;
    iFileFlatData->iFileInfo.iAudioElementCount = KMceTestAudioElementCount;
    iFileFlatData->iFileInfo.iVideoElementCount = KMceTestVideoElementCount;
    iFileFlatData->iFileInfo.iAudioCodec = KMceTestAudioCodec;
    iFileFlatData->iFileInfo.iVideoCodec = KMceTestVideoCodec;
    iFileFlatData->iTranscodeInfo.iTranscodeSessionId = KTranscodeSessionId;
    iFileFlatData->iTranscodeInfo.iFileName = KTranscodeFileName;
    iFileFlatData->iTranscodeInfo.iQuality = KQuality;
    iFileFlatData->iTranscodeInfo.iProgress = KProgress;
    
    TBuf8<1500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iFileSource->ExternalizeL( serCtx );
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
	
	EUNIT_ASSERT( readStream.ReadUint8L() );
	EUNIT_ASSERT( readStream.ReadUint8L() );
    TPckgBuf<TTimeIntervalMicroSeconds> positionBuf;
    MceSerial::DecodeL( positionBuf, readStream );
    TTimeIntervalMicroSeconds tester = positionBuf();
    EUNIT_ASSERT( tester == TTimeIntervalMicroSeconds( 1 ) );
    TPckgBuf<TMceFileInfo> fileInfoBuf;
    MceSerial::DecodeL( fileInfoBuf, readStream );
    TMceFileInfo fileInfo = fileInfoBuf();
    EUNIT_ASSERT_EQUALS( 0, fileInfo.iFileName.Compare( KMceTestAVFileName16 ) );
    EUNIT_ASSERT( fileInfo.iDuration == KMceTestDuration );
    EUNIT_ASSERT_EQUALS( KMceTestAudioElementCount, fileInfo.iAudioElementCount );
    EUNIT_ASSERT_EQUALS( KMceTestVideoElementCount, fileInfo.iVideoElementCount );
    EUNIT_ASSERT_EQUALS( 0, fileInfo.iAudioCodec.Compare( KMceTestAudioCodec ) );
    EUNIT_ASSERT_EQUALS( 0, fileInfo.iVideoCodec.Compare( KMceTestVideoCodec ) );
    TPckgBuf<TMceTranscodeInfo> tcInfoBuf;
    MceSerial::DecodeL( tcInfoBuf, readStream );
    TMceTranscodeInfo tcInfo = tcInfoBuf();
    EUNIT_ASSERT( tcInfo.iTranscodeSessionId == KTranscodeSessionId );
    EUNIT_ASSERT_EQUALS( 0, tcInfo.iFileName.Compare( KTranscodeFileName ) );
    EUNIT_ASSERT_EQUALS( tcInfo.iQuality, KQuality );
    EUNIT_ASSERT_EQUALS( tcInfo.iProgress, KProgress );
    
	readStream.Close();
	readStream.Pop();
    }
