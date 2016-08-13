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




//  CLASS HEADER
#include "ut_cmcecomcamerasource.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <sdpcodecstringpool.h>
#include "mcemediamanager.h"
#include "mcecomcamerasource.h"
#include "mcecomavccodec.h"
#include "mcesdpsession.h"
#include "mcetestdefs.h"

//  INTERNAL INCLUDES
const TUint8 KMceTestCategory = 5;


// CONSTRUCTION
UT_CMceComCameraSource* UT_CMceComCameraSource::NewL()
    {
    UT_CMceComCameraSource* self = UT_CMceComCameraSource::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComCameraSource* UT_CMceComCameraSource::NewLC()
    {
    UT_CMceComCameraSource* self = new( ELeave ) UT_CMceComCameraSource();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComCameraSource::~UT_CMceComCameraSource()
    {
    }

// Default constructor
UT_CMceComCameraSource::UT_CMceComCameraSource()
    {
    }

// Second phase construct
void UT_CMceComCameraSource::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComCameraSource::SetupL()
    {
    SdpCodecStringPool::OpenL();
    
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    iManagerStub = new (ELeave) CMceMediaManagerStub();
    iSession = CMceComSession::NewL();
    
    CMceComVideoStream* stream = CMceComVideoStream::NewLC();
    CMceComCameraSource* source = CMceComCameraSource::NewL();
    CleanupStack::PushL( source );
    
    stream->SetSourceL( source );
    CleanupStack::Pop( source );

    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );

    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    
    iSource = source;
    
    } 

void UT_CMceComCameraSource::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
	delete iSession;
	iSession = NULL;
	delete iManagerStub;
	iManagerStub = NULL;
	
    SdpCodecStringPool::Close();    
	
    }

void UT_CMceComCameraSource::UT_CMceComCameraSource_InternalizeFlatLL()
    {
    }

void UT_CMceComCameraSource::UT_CMceComCameraSource_ExternalizeFlatLL()
    {
    }

void UT_CMceComCameraSource::UT_CMceComCameraSource_EventReceivedLL()
    {
    TMceComEventHandlerStub handler( *iManagerStub );

    TMceIds ids;
    CBase* message = NULL;
    TMceItcFunctions action = EMceItcEnable;
    TMceComEvent event( ids, message, action, handler );

    EUNIT_ASSERT( iSource->EventReceivedL( event ) != KMceEventConsumed );
    
    TUid uid = TUid::Uid( 777 );

//disabled source    
    
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    ids.iMediaID = iSource->MediaStream()->iID;
    ids.iSourceID = iSource->iID;

    TMceComEvent event1( ids, NULL, EMceItcDisable, handler );
    EUNIT_ASSERT( iSource->EventReceivedL( event1 ) == KMceEventConsumed );

//EMceItcZoomFactor source    
    
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    ids.iMediaID = iSource->MediaStream()->iID;
    ids.iSourceID = iSource->iID;

    TMceComEvent event2( ids, NULL, EMceItcZoomFactor, handler );
    EUNIT_ASSERT( iSource->EventReceivedL( event2 ) == KMceEventConsumed );

//not consumed    
    ids.iCodecID = 1;
    TMceComEvent event3( ids, NULL, EMceItcZoomFactor, handler );
    EUNIT_ASSERT( iSource->EventReceivedL( event2 ) == KMceEventNotConsumed );
        
    
    }

void UT_CMceComCameraSource::UT_CMceComCameraSource_CloneLL()
    {
    CMceComMediaSource* clone = NULL;
    clone = iSource->CloneL();
    delete clone;
    
    }

void UT_CMceComCameraSource::UT_CMceComCameraSource_UpdateL()
    {
    CMceComCameraSource* update = iSource;
    iSource->UpdateL( *iSource );
    
    EUNIT_ASSERT( iSource->iCameraIndex == update->iCameraIndex );
    EUNIT_ASSERT( iSource->iZoomFactor == update->iZoomFactor );
    EUNIT_ASSERT( iSource->iDigitalZoomFactor == update->iDigitalZoomFactor );
    EUNIT_ASSERT( iSource->iContrast == update->iContrast );
    EUNIT_ASSERT( iSource->iBrightness == update->iBrightness );
    EUNIT_ASSERT( iSource->iExposure == update->iExposure );
    EUNIT_ASSERT( iSource->iWhiteBalance == update->iWhiteBalance );
    EUNIT_ASSERT( iSource->iCamerasAvailable == update->iCamerasAvailable );
    //EUNIT_ASSERT( iSource->iCameraInfo == update->iCameraInfo );
    EUNIT_ASSERT( iSource->iInitialInfoRetrieved == update->iInitialInfoRetrieved );
    
    
    }

void UT_CMceComCameraSource::UT_CMceComCameraSource_MccTypeL()
    {
    EUNIT_ASSERT( iSource->MccType() == KUidMccVideoSource );
    
    }

void UT_CMceComCameraSource::UT_CMceComCameraSource_InitParamLL()
    {
    _LIT8( KConfig, "foo");
    CMceComAvcCodec* codec = CMceComAvcCodec::NewLC( KMceSDPNameH264() );
    HBufC8* settings = NULL;
    settings = iSource->InitParamL( *codec ).AllocLC();
    EUNIT_ASSERT( settings->Length() != 0 );
    
    CMceComMediaStream* astream = CMceComAudioStream::NewLC();
    codec->InitializeL( *astream );
    EUNIT_ASSERT( iSource->InitParamL( *codec ) == *settings );

    CMceComMediaStream* vstream = CMceComVideoStream::NewLC();
    codec->InitializeL( *vstream );
    EUNIT_ASSERT( iSource->InitParamL( *codec ) == *settings );

    codec->iConfigKey = KConfig().AllocL();
    EUNIT_ASSERT( iSource->InitParamL( *codec ) != *settings );
    
    CleanupStack::PopAndDestroy( 3 );
    CleanupStack::PopAndDestroy( codec );
    
    }

void UT_CMceComCameraSource::UT_CMceComCameraSource_DoPreparedL()
    {
    CMceSdpSession* sdpSession = 
        CMceSdpSession::NewLC( *iSession, *iManager );
    iSession->iSdpSession = sdpSession;
    
    EUNIT_ASSERT( iSource->DoPrepared() == KErrNone );

    iSession->iSdpSession = NULL;
    EUNIT_ASSERT( iSource->DoPrepared() == KErrNone );
    
    CMceComMediaStream* stream = iSource->MediaStream();
    CMceComSession* dummy = NULL;
    stream->InitializeL( *dummy );
    
    EUNIT_ASSERT( iSource->DoPrepared() == KErrNone );
    
    
    CMceComCameraSource* source = CMceComCameraSource::NewLC();
    EUNIT_ASSERT( source->DoPrepared() == KErrNone );
    
    CleanupStack::PopAndDestroy( source );
    CleanupStack::PopAndDestroy( sdpSession );
    
    
    }


    

	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComCameraSource,
    "CMceComCameraSource tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComCameraSource",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCameraSource_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComCameraSource",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCameraSource_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComCameraSource",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCameraSource_EventReceivedLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComCameraSource",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCameraSource_CloneLL, Teardown)

EUNIT_TEST (
    "Update test",
    "CMceComCameraSource",
    "Update",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCameraSource_UpdateL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComCameraSource",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCameraSource_MccTypeL, Teardown)

EUNIT_TEST (
    "InitParamL test",
    "CMceComCameraSource",
    "InitParamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCameraSource_InitParamLL, Teardown)

EUNIT_TEST (
    "DoPrepared test",
    "CMceComCameraSource",
    "DoPrepared",
    "FUNCTIONALITY",
    SetupL, UT_CMceComCameraSource_DoPreparedL, Teardown)



EUNIT_END_TEST_TABLE



//  END OF FILE
