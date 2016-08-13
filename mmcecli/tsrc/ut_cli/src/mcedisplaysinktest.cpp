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
#include "mcedisplaysinktest.h"
#include "mcedisplaysink.h"
#include "mcecomdisplaysink.h"
#include "mcemanager.h"
#include "mceoutsession.h"
#include "mcevideostream.h"
#include "mcertpsource.h"
#include "mcestubs.h"
#include "mcetestdefs.h"


const TInt KTestDisplayIndex = 1;
const TUint KMceTestCategory = 5; 
// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceDisplaySinkTest::setUpL()
    {
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
    
    iUid = TUid::Uid( 777 );
    iManager = CMceManager::NewL( iUid, NULL );    
	iDisplay = CMceDisplaySink::NewL( *iManager );
	iDisplayWithoutManager = CMceDisplaySink::NewL();
	iDisplayFlatData = static_cast<CMceComDisplaySink*>(iDisplay->iFlatData);
    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::tearDown()
    {
    delete iDisplay;
    delete iDisplayWithoutManager;
    delete iManager;
    
    delete iStorage;
    Dll::SetTls( NULL );
    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceDisplaySinkTest::suiteL()
    {
    CMceDisplaySinkTest* suite = new CMceDisplaySinkTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceDisplaySinkTest,
    "CMceDisplaySinkTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, EnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, DisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, DisplaysAvailableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, SetDisplayIndexTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, SetDisplayTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, SetDisplayRectTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, DisplayRectTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, SetPriorityTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, PriorityTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, GetITCValueTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceDisplaySinkTest", setUpL, SetITCValueTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceDisplaySinkTest:: ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::ConstructionTestL()
    {
    EUNIT_ASSERT( iDisplay != NULL );
    EUNIT_ASSERT( iDisplay->iFlatData != NULL );
    
    EUNIT_ASSERT( iDisplayWithoutManager != NULL );
    EUNIT_ASSERT( iDisplayWithoutManager->iFlatData != NULL );
    
    // Try to initialize the display without the manager
    TRAPD( err, iDisplayWithoutManager->InitializeL( NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	// Succeed initializing afterwards
	iDisplayWithoutManager->InitializeL( iManager );
	EUNIT_ASSERT( iDisplayFlatData->iInitialInfoRetrieved );
	
	// Simulate situation where sender already exists during initialization
	iDisplayFlatData->iInitialInfoRetrieved = EFalse;
	iDisplayWithoutManager->InitializeL( iManager );
	EUNIT_ASSERT( !iDisplayFlatData->iInitialInfoRetrieved );
    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::EnableTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::EnableTestL()
    {
    // As long as CMceDispaySink::EnableL does nothing but
    // calls CMceMediaSource::DoEnableL almost dummy test is enough.
    iDisplayFlatData->Enabled( EFalse );
    iDisplay->EnableL();
    EUNIT_ASSERT( iDisplayFlatData->IsEnabled() );
    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::DisableTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::DisableTestL()
    {
    // As long as CMceDisplaySink::DisableL does nothing but
    // calls CMceMediaSource::DoDisableL almost dummy test is enough.
    iDisplayFlatData->Enabled( ETrue );
    iDisplay->DisableL();
    EUNIT_ASSERT( !iDisplayFlatData->IsEnabled() );
    }
    
    
// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::DisplaysAvailableTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::DisplaysAvailableTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestDisplaysAvailable, iDisplay->DisplaysAvailable() );  
    EUNIT_ASSERT_EQUALS( 0, iDisplayWithoutManager->DisplaysAvailable() );   
    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::SetDisplayIndexTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::SetDisplayIndexTestL()
    {
    
    EUNIT_ASSERT_EQUALS( 0, iDisplayFlatData->iDisplayIndex );
    
    TRAPD( err, iDisplay->SetDisplayIndexL( -1 ) ); // Invalid index, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
    
    TRAP( err, iDisplay->SetDisplayIndexL( iDisplay->DisplaysAvailable() + 1 ) ); // Invalid index, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
    iDisplay->SetDisplayIndexL( 1 );
    EUNIT_ASSERT_EQUALS( 1, iDisplayFlatData->iDisplayIndex ); 
    

    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateDisplaySessionLC( *profile );
    CMceDisplaySink* display = static_cast<CMceDisplaySink*>
            (session->Streams()[0]->Sinks()[0]);
    CMceComDisplaySink* displayFlatData = 
            static_cast<CMceComDisplaySink*>(display->iFlatData);
    
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iDisplayIndex );
    
    session->EstablishL();     
    
    display->SetDisplayIndexL( 1 );
    EUNIT_ASSERT_EQUALS( 1, displayFlatData->iDisplayIndex );
    
    CleanupStack::PopAndDestroy( session );
 
    MCE_DELETE_PROFILE;
    
    }  


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::SetDisplayTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::SetDisplayTestL()
    {

    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::SetDisplayRectTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::SetDisplayRectTestL()
    {
    /*
    
    Outcommented because of temporarily hard-coded default values 
    
    EUNIT_ASSERT_EQUALS( 0, iDisplayFlatData->iDisplayRectTlX );
    EUNIT_ASSERT_EQUALS( 0, iDisplayFlatData->iDisplayRectTlY );
    EUNIT_ASSERT_EQUALS( 0, iDisplayFlatData->iDisplayRectBrX );
    EUNIT_ASSERT_EQUALS( 0, iDisplayFlatData->iDisplayRectBrY );
    */
    
    TRect tester;
    tester.iTl.iX = 20;
    tester.iTl.iY = 30;
    tester.iBr.iX = 40;
    tester.iBr.iY = 50;
    
    iDisplay->SetDisplayRectL( tester );
    
    EUNIT_ASSERT_EQUALS( 20, iDisplayFlatData->iDisplayRectTlX );
    EUNIT_ASSERT_EQUALS( 30, iDisplayFlatData->iDisplayRectTlY );
    EUNIT_ASSERT_EQUALS( 40, iDisplayFlatData->iDisplayRectBrX );
    EUNIT_ASSERT_EQUALS( 50, iDisplayFlatData->iDisplayRectBrY );
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateDisplaySessionLC( *profile );
    CMceDisplaySink* display = static_cast<CMceDisplaySink*>
            (session->Streams()[0]->Sinks()[0]);
    CMceComDisplaySink* displayFlatData = 
            static_cast<CMceComDisplaySink*>(display->iFlatData);
    
    /*
    
    Outcommented because of temporarily hard-coded default values 
    
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iDisplayRectTlX );
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iDisplayRectTlY );
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iDisplayRectBrX );
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iDisplayRectBrY ); 
    */
    
    session->EstablishL();    
    
    display->SetDisplayRectL( tester );
    
    EUNIT_ASSERT_EQUALS( 20, displayFlatData->iDisplayRectTlX );
    EUNIT_ASSERT_EQUALS( 30, displayFlatData->iDisplayRectTlY );
    EUNIT_ASSERT_EQUALS( 40, displayFlatData->iDisplayRectBrX );
    EUNIT_ASSERT_EQUALS( 50, displayFlatData->iDisplayRectBrY ); 
     
    CleanupStack::PopAndDestroy( session );
 
    MCE_DELETE_PROFILE;    
    }
    
    
// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::DisplayRectTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::DisplayRectTestL()
    {
    
    /*
    
    Outcommented because of temporarily hard-coded default values 
    
    EUNIT_ASSERT_EQUALS( 0, iDisplay->DisplayRectL().iTl.iX );
    EUNIT_ASSERT_EQUALS( 0, iDisplay->DisplayRectL().iTl.iY );
    EUNIT_ASSERT_EQUALS( 0, iDisplay->DisplayRectL().iBr.iX );
    EUNIT_ASSERT_EQUALS( 0, iDisplay->DisplayRectL().iBr.iY );
    */
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateDisplaySessionLC( *profile );
    CMceDisplaySink* display = static_cast<CMceDisplaySink*>
            (session->Streams()[0]->Sinks()[0]);
    CMceComDisplaySink* displayFlatData = 
            static_cast<CMceComDisplaySink*>(display->iFlatData);
    
    /*
    
    Outcommented because of temporarily hard-coded default values 
                
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iDisplayRectTlX );
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iDisplayRectTlY );
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iDisplayRectBrX );
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iDisplayRectBrY );
    */
    
    session->EstablishL();     

    const TRect rect = display->DisplayRectL();

    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectTlX, rect.iTl.iX );    
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectTlY, rect.iTl.iY );   
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectBrX, rect.iBr.iX );   
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectBrY, rect.iBr.iY );   
    
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectTlX, displayFlatData->iDisplayRectTlX );    
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectTlY, displayFlatData->iDisplayRectTlY );   
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectBrX, displayFlatData->iDisplayRectBrX );   
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectBrY, displayFlatData->iDisplayRectBrY );   
    
    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::SetPriorityTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::SetPriorityTestL()
    {
    EUNIT_ASSERT_EQUALS( 0, iDisplayFlatData->iPriority );
	
    iDisplay->SetPriorityL( 1 );
    EUNIT_ASSERT_EQUALS( 1, iDisplayFlatData->iPriority ); 
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateDisplaySessionLC( *profile );
    CMceDisplaySink* display = static_cast<CMceDisplaySink*>
            (session->Streams()[0]->Sinks()[0]);
    CMceComDisplaySink* displayFlatData = 
            static_cast<CMceComDisplaySink*>(display->iFlatData);
                
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iPriority );
    
    session->EstablishL();     
    
    display->SetPriorityL( 1 );
    EUNIT_ASSERT_EQUALS( 1, displayFlatData->iPriority );
    
    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }    
    
    
// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::PriorityTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::PriorityTestL()
    {
    EUNIT_ASSERT_EQUALS( 0, iDisplay->PriorityL() );
    EUNIT_ASSERT_EQUALS( 0, iDisplayWithoutManager->PriorityL() );
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateDisplaySessionLC( *profile );
    CMceDisplaySink* display = static_cast<CMceDisplaySink*>
            (session->Streams()[0]->Sinks()[0]);
    CMceComDisplaySink* displayFlatData = 
            static_cast<CMceComDisplaySink*>(display->iFlatData);
                
    EUNIT_ASSERT_EQUALS( 0, displayFlatData->iPriority );
    
    session->EstablishL();  

    EUNIT_ASSERT_EQUALS( KMceTestDisplayPriority, display->PriorityL() );    
    EUNIT_ASSERT_EQUALS( KMceTestDisplayPriority, displayFlatData->iPriority );

    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }
    
    
// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::InternalizeTestL()
    {
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();
    
    // Base class data
    writeStream.WriteUint8L( KMceTestSinkType );
    writeStream.WriteUint8L( KMceTestCategory ); 
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( KMceTestEnabledFalse );
    
    // Display data
    writeStream.WriteInt32L( KTestDisplayIndex );
    writeStream.WriteInt32L( KMceTestDisplayRectTlX );
    writeStream.WriteInt32L( KMceTestDisplayRectTlY );
    writeStream.WriteInt32L( KMceTestDisplayRectBrX );
    writeStream.WriteInt32L( KMceTestDisplayRectBrY );
    writeStream.WriteUint32L( KMceTestDisplayPriority );
    writeStream.WriteInt32L( ETrue ); // iIsViewFinder
    writeStream.WriteInt32L( CMceDisplaySink::EClockwise90Degree );
    writeStream.WriteInt32L( 2 ); // iDisplaysAvailable
    writeStream.WriteUint8L( ETrue ); // iInitialInfoRetrieved
    
   	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
	
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    iDisplay->InternalizeL( serCtx );
    
    EUNIT_ASSERT( iDisplay->iFlatData->iType == KMceTestSinkType );
    EUNIT_ASSERT( iDisplay->iFlatData->IsEnabled() == KMceTestEnabledFalse );
    EUNIT_ASSERT( iDisplay->iFlatData->Id().iAppId == KMceTestAppId );
    EUNIT_ASSERT( iDisplay->iFlatData->Id().iId == KMceTestMiscId );
    
    EUNIT_ASSERT_EQUALS( KTestDisplayIndex, iDisplayFlatData->iDisplayIndex );
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectTlX, iDisplayFlatData->iDisplayRectTlX );
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectTlY, iDisplayFlatData->iDisplayRectTlY );
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectBrX, iDisplayFlatData->iDisplayRectBrX );
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectBrY, iDisplayFlatData->iDisplayRectBrY );
    EUNIT_ASSERT( KMceTestDisplayPriority == iDisplayFlatData->iPriority );
    EUNIT_ASSERT( iDisplayFlatData->iIsViewFinder );
    EUNIT_ASSERT( iDisplayFlatData->iRotation == CMceDisplaySink::EClockwise90Degree );
    EUNIT_ASSERT( iDisplayFlatData->iDisplaysAvailable == 2 );
    EUNIT_ASSERT( iDisplayFlatData->iInitialInfoRetrieved );
    
    CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();
    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::ExternalizeTestL()
    {
    // Base class data
    iDisplay->iFlatData->iCategory = KMceTestCategory;
    iDisplay->iFlatData->iID.iAppId = KMceTestAppId;
    iDisplay->iFlatData->iID.iId = KMceTestMiscId; 
    iDisplay->iFlatData->iType = KMceTestSinkType;
    iDisplay->iFlatData->Enabled( KMceTestEnabledFalse );
    
    // Display data
    iDisplayFlatData->iDisplayIndex = KTestDisplayIndex;
    iDisplayFlatData->iDisplayRectTlX = KMceTestDisplayRectTlX;
    iDisplayFlatData->iDisplayRectTlY = KMceTestDisplayRectTlY;
    iDisplayFlatData->iDisplayRectBrX = KMceTestDisplayRectBrX;
    iDisplayFlatData->iDisplayRectBrY = KMceTestDisplayRectBrY;
    iDisplayFlatData->iPriority = KMceTestDisplayPriority;
    
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iDisplay->ExternalizeL( serCtx );
	
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
	
    EUNIT_ASSERT_EQUALS( KTestDisplayIndex, readStream.ReadInt32L() );
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectTlX, readStream.ReadInt32L() );
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectTlY, readStream.ReadInt32L() );
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectBrX, readStream.ReadInt32L() );
    EUNIT_ASSERT_EQUALS( KMceTestDisplayRectBrY, readStream.ReadInt32L() );
    EUNIT_ASSERT_EQUALS( KMceTestDisplayPriority, readStream.ReadUint32L() );
	
	readStream.Close();
	readStream.Pop();
    }    


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::GetITCValueTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::GetITCValueTestL()
    {
    // Successfull case has been tested with getters, so just try without session
    TRAPD( err, iDisplay->GetITCValueL( EMceItcDisplayPriority ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::SetITCValueTestL
// ----------------------------------------------------------------------------
//
void CMceDisplaySinkTest::SetITCValueTestL()
    {
    // Successfull case has been tested with getters, so just try without session
    TRAPD( err, iDisplay->SetITCValueL( EMceItcSetDisplayPriority, 
                                       0 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
    }


// ----------------------------------------------------------------------------
// CMceDisplaySinkTest::CreateDisplaySessionLC 
// Creates a session with one video stream with display sink and rtp source.
// Leaves instance on cleanupstack.
// ----------------------------------------------------------------------------
//
CMceOutSession* CMceDisplaySinkTest::CreateDisplaySessionLC( CSIPProfile& aProfile )
    {
    CMceOutSession* session = CMceOutSession::NewL( *iManager, aProfile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceVideoStream* stream = CMceVideoStream::NewLC();
    
    CMceDisplaySink* display = CMceDisplaySink::NewLC( *iManager );
    stream->AddSinkL( display );
    CleanupStack::Pop( display );
    
    CMceRtpSource* rtp = CMceRtpSource::NewLC();
    stream->SetSourceL( rtp );
    CleanupStack::Pop( rtp );
    
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );
    
    return session;
    }    
