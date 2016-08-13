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
#include "ut_cmcecomfilesource.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <sdpcodecstringpool.h>
#include "mcemediamanager.h"
#include "mcesdpsession.h"
#include "mcetestdefs.h"

//  INTERNAL INCLUDES

_LIT16( KTranscodeFileName, "transcodefile" );

const TUint32 KTranscodeSessionId = 2345;
const TInt KQuality = 4;
const TInt KProgress = 7;
const TUint8 KMceTestCategory = 5;

// CONSTRUCTION
UT_CMceComFileSource* UT_CMceComFileSource::NewL()
    {
    UT_CMceComFileSource* self = UT_CMceComFileSource::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComFileSource* UT_CMceComFileSource::NewLC()
    {
    UT_CMceComFileSource* self = new( ELeave ) UT_CMceComFileSource();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComFileSource::~UT_CMceComFileSource()
    {
    }

// Default constructor
UT_CMceComFileSource::UT_CMceComFileSource()
    {
    }

// Second phase construct
void UT_CMceComFileSource::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComFileSource::SetupL()
    {
    SdpCodecStringPool::OpenL();
    
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    iManagerStub = new (ELeave) CMceMediaManagerStub();
    iSession = CMceComSession::NewL();
    
    CMceComVideoStream* stream = CMceComVideoStream::NewLC();
    CMceComFileSource* source = CMceComFileSource::NewL();
    CleanupStack::PushL( source );
    
    stream->SetSourceL( source );
    CleanupStack::Pop( source );

    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );

    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    
    iSource = source;    
    } 

void UT_CMceComFileSource::Teardown()
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


void UT_CMceComFileSource::UT_CMceComFileSource_InternalizeFlatLL()
    {
    
    }

void UT_CMceComFileSource::UT_CMceComFileSource_ExternalizeFlatLL()
    {
    }

void UT_CMceComFileSource::UT_CMceComFileSource_EventReceivedLL()
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

//EMceItcFileInfo source    
    
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    ids.iMediaID = iSource->MediaStream()->iID;
    ids.iSourceID = iSource->iID;

    TMceComEvent event2( ids, NULL, EMceItcFileInfo, handler );
    EUNIT_ASSERT( iSource->EventReceivedL( event2 ) == KMceEventConsumed );

//not consumed    
    ids.iCodecID = 1;
    TMceComEvent event3( ids, NULL, EMceItcFileInfo, handler );
    EUNIT_ASSERT( iSource->EventReceivedL( event2 ) == KMceEventNotConsumed );
    
    }

void UT_CMceComFileSource::UT_CMceComFileSource_CloneLL()
    {
    CMceComMediaSource* clone = NULL;
    clone = iSource->CloneL();
    delete clone;
    
    }

void UT_CMceComFileSource::UT_CMceComFileSource_UpdateLL()
    {
    CMceComFileSource* update = iSource;
    iSource->UpdateL( *iSource );
    
    EUNIT_ASSERT( iSource->iFastForward == update->iFastForward );
    EUNIT_ASSERT( iSource->iFastRewind == update->iFastRewind );
    EUNIT_ASSERT( iSource->iPosition == update->iPosition );
    //EUNIT_ASSERT( iSource->iFileInfo == update->iFileInfo );
    //EUNIT_ASSERT( iSource->iTranscodeInfo == update->iTranscodeInfo );
    
    
    }

void UT_CMceComFileSource::UT_CMceComFileSource_MccTypeL()
    {
    EUNIT_ASSERT( iSource->MccType() == KUidMccFileSource );
    
    }

void UT_CMceComFileSource::UT_CMceComFileSource_InitParamLL()
    {
    CMceComCodec* codec = NULL;
    EUNIT_ASSERT( iSource->InitParamL( *codec ).Length() > 0 );
    
    }

void UT_CMceComFileSource::UT_CMceComFileSource_InitializedLL()
    {
    CMceSdpSession* sdpSession = 
         CMceSdpSession::NewLC( *iSession, *iManager );
     iSession->iSdpSession = sdpSession;
     
     iSource->InitializedL();

     iSession->iSdpSession = NULL;
     iSource->InitializedL();
     
     CMceComMediaStream* stream = iSource->MediaStream();
     CMceComSession* dummy = NULL;
     stream->InitializeL( *dummy );
     
     iSource->InitializedL();
     
     
     CMceComFileSource* source = CMceComFileSource::NewLC();
     iSource->InitializedL();
     
     CleanupStack::PopAndDestroy( source );
     CleanupStack::PopAndDestroy( sdpSession );    
    }


	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComFileSource,
    "CMceComFileSource tests",
    "UNIT" )

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComFileSource",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSource_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComFileSource",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSource_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComFileSource",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSource_EventReceivedLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComFileSource",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSource_CloneLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComFileSource",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSource_UpdateLL, Teardown)

EUNIT_TEST (
    "MccType test",
    "CMceComFileSource",
    "MccType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSource_MccTypeL, Teardown)

EUNIT_TEST (
    "InitParamL test",
    "CMceComFileSource",
    "InitParamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSource_InitParamLL, Teardown)

EUNIT_TEST (
    "InitializedL test",
    "CMceComFileSource",
    "InitializedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComFileSource_InitializedLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
