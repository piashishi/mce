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
#include "ut_cmcecomendpoint.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"
#include "mcecomaudiostream.h"
#include "mcecommicsource.h"
#include "mcecomrtpsink.h"
#include "mcecomsession.h"
#include "mcecomfactory.h"
#include "mcecomaudiocodec.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComEndpoint* UT_CMceComEndpoint::NewL()
    {
    UT_CMceComEndpoint* self = UT_CMceComEndpoint::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComEndpoint* UT_CMceComEndpoint::NewLC()
    {
    UT_CMceComEndpoint* self = new( ELeave ) UT_CMceComEndpoint();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComEndpoint::~UT_CMceComEndpoint()
    {
    }

// Default constructor
UT_CMceComEndpoint::UT_CMceComEndpoint()
    {
    }

// Second phase construct
void UT_CMceComEndpoint::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComEndpoint::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    iSession = CMceComSession::NewL();
    CMceComAudioStream* stream = CMceComAudioStream::NewLC();
    CMceComMediaSource* mediaSource = CMceComMicSource::NewLC();
    stream->SetSourceL( mediaSource );
    CleanupStack::Pop( mediaSource );
    iSource = mediaSource;
    CMceComMediaSink* mediaSink = CMceComRtpSink::NewLC();
    stream->AddSinkL( mediaSink );
    CleanupStack::Pop( mediaSink );
    iSink = mediaSink;
    iComEndpoint = mediaSource;
    
    TMceComAudioCodecFactory factory;
    CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNameAMR() );
    stream->AddCodecL( codec );
    CleanupStack::Pop( codec );

    iCodec = codec;
    
    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    iStream = stream;
    
    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    
    iSession->SetObserver( *iServer );
    } 

void UT_CMceComEndpoint::Teardown()
    {
	CMceComSession::Delete( iSession, *iManager );
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_CMceComEndpoint::UT_CMceComEndpoint_SerializationIdL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_InternalizeFlatLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_ExternalizeFlatLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_InternalizeLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_ExternalizeLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_IdL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_BaseFactoryL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_ReferenceCountL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_MediaStreamL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_operatorEqualL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_UnInitializeL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_IsEnabledL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_EnabledL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_InitializeLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_StreamAddedLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_EndpointProxyL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_SetupEndpointProxyLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_CreateEndpointProxyLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_UsesEndpointProxyL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_ReusableL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_InitParamLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_EnableLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_DisableLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_PrepareLL()
    {
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_EventReceivedL()
    {
    TUint32 linkId( 3 );
    TUint32 streamId( 4 );
    TUint32 endpointId( 5 );

    TMceMccComEvent event( KMccStreamPaused,  linkId, streamId, endpointId );
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcStateChanged );
    
    event.iEvent = KMccStreamResumed;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcStateChanged );
    
    event.iEvent = KMccInactivityEvent;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInactivityTimeout );
    
    event.iEvent = KMccStreamError;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaError );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    // No subtype, not forwarded
    event.iEvent = KMccRtcpReceived;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaError );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    event.iEventSubType = KRtcpSrPacket;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcSRReceived );
    
    event.iEventSubType = KRtcpRrPacket;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcRRReceived );
    
    event.iEventSubType = KRtcpPacketUndefined;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcFCMsgReceived );
    
    event.iEvent = KMccDtmfReceived;
    event.iEventSubType = KMccDtmfManualStart;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcDtmfSendStarted );
    
    event.iEventSubType = KMccDtmfSequenceStart;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcDtmfSendStarted );
    
    event.iEventSubType = KMccDtmfManualStop;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcDtmfSendCompleted );
    
    event.iEventSubType = KMccDtmfSequenceStop;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcDtmfSendCompleted );
    
    event.iEventSubType = KMccDtmfStopInDtmfString;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcDtmfSendCompleted );
    
    event.iEventSubType = KMccDtmfSendingComplete;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcDtmfSendCompleted );

    event.iEvent = KMccDtmfControl;
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcDtmfSendCompleted );
    
    event.iEvent = KMccStreamIdle;
    event.iEventSubType = EMceItcNotAssigned;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );

    event.iEvent = KMccStreamPlaying;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );

    event.iEvent = KMccStreamStarted;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    event.iEvent = KMccStreamBuffering;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    event.iEvent = KMccStreamStopped;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    event.iEvent = KMccStreamClosed;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    event.iEvent = KMccResourceNotAvailable;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    event.iEvent = KMccActivityEvent;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    event.iEvent = KMccResourceReserved;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    event.iEvent = KMccResourceReleased;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    
    // Unknown event, not forwarded
    event.iEvent = 998;  
    iComEndpoint->EventReceived( event );
    EUNIT_ASSERT( iServer->iEvent == EMceMediaEventReceived );
    EUNIT_ASSERT( iServer->iItcEvent == EMceItcInProgress );
    }

void UT_CMceComEndpoint::UT_CMceComEndpoint_SetStateL()
    {
    TUint32 linkId( 3 );
    TUint32 streamId( 4 );
    TUint32 endpointId( 5 );

    TMceMccComEvent event( KMccStreamResumed,  linkId, streamId, endpointId );
    iComEndpoint->SetState( event );
    EUNIT_ASSERT( iComEndpoint->IsEnabled() );
    
    event.iEvent = KMccStreamStopped;
    iComEndpoint->SetState( event );
    EUNIT_ASSERT( !iComEndpoint->IsEnabled() );
    
    event.iEvent = KMccStreamStarted;
    iComEndpoint->SetState( event );
    EUNIT_ASSERT( iComEndpoint->IsEnabled() );
    
    event.iEvent = KMccStreamPaused;
    iComEndpoint->SetState( event );
    EUNIT_ASSERT( !iComEndpoint->IsEnabled() );
    
    iComEndpoint->Enabled( ETrue );
    event.iEvent = KMccStreamError;
    iComEndpoint->SetState( event );
    EUNIT_ASSERT( !iComEndpoint->IsEnabled() );
    
    // No source or sink -> no effect on state
    iComEndpoint->Enabled( ETrue );
    event.iEvent = KMccResourceNotAvailable;
    iComEndpoint->SetState( event );
    EUNIT_ASSERT( iComEndpoint->IsEnabled() );
    
    // Source defined, effective
    event.iSource = iComEndpoint;
    iComEndpoint->SetState( event );
    EUNIT_ASSERT( !iComEndpoint->IsEnabled() );
    
    // Unknown event
    iComEndpoint->Enabled( ETrue );
    event.iEvent = KMccInactivityEvent;
    iComEndpoint->SetState( event );
    EUNIT_ASSERT( iComEndpoint->IsEnabled() );
    }


	
//  TEST TABLE
EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComEndpoint,
    "CMceComEndpoint tests",
    "UNIT" )

EUNIT_TEST (
    "SerializationId test",
    "CMceComEndpoint",
    "SerializationId",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_SerializationIdL, Teardown)

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComEndpoint",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComEndpoint",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "InternalizeL test",
    "CMceComEndpoint",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_InternalizeLL, Teardown)

EUNIT_TEST (
    "ExternalizeL test",
    "CMceComEndpoint",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_ExternalizeLL, Teardown)

EUNIT_TEST (
    "Id test",
    "CMceComEndpoint",
    "Id",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_IdL, Teardown)

EUNIT_TEST (
    "BaseFactory test",
    "CMceComEndpoint",
    "BaseFactory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_BaseFactoryL, Teardown)

EUNIT_TEST (
    "ReferenceCount test",
    "CMceComEndpoint",
    "ReferenceCount",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_ReferenceCountL, Teardown)

EUNIT_TEST (
    "MediaStream test",
    "CMceComEndpoint",
    "MediaStream",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_MediaStreamL, Teardown)

EUNIT_TEST (
    "operator== test",
    "CMceComEndpoint",
    "operator==",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_operatorEqualL, Teardown)

EUNIT_TEST (
    "UnInitialize test",
    "CMceComEndpoint",
    "UnInitialize",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_UnInitializeL, Teardown)

EUNIT_TEST (
    "IsEnabled test",
    "CMceComEndpoint",
    "IsEnabled",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_IsEnabledL, Teardown)

EUNIT_TEST (
    "Enabled test",
    "CMceComEndpoint",
    "Enabled",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_EnabledL, Teardown)

EUNIT_TEST (
    "InitializeL test",
    "CMceComEndpoint",
    "InitializeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_InitializeLL, Teardown)

EUNIT_TEST (
    "StreamAddedL test",
    "CMceComEndpoint",
    "StreamAddedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_StreamAddedLL, Teardown)

EUNIT_TEST (
    "EndpointProxy test",
    "CMceComEndpoint",
    "EndpointProxy",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_EndpointProxyL, Teardown)

EUNIT_TEST (
    "SetupEndpointProxyL test",
    "CMceComEndpoint",
    "SetupEndpointProxyL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_SetupEndpointProxyLL, Teardown)

EUNIT_TEST (
    "CreateEndpointProxyL test",
    "CMceComEndpoint",
    "CreateEndpointProxyL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_CreateEndpointProxyLL, Teardown)

EUNIT_TEST (
    "UsesEndpointProxy test",
    "CMceComEndpoint",
    "UsesEndpointProxy",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_UsesEndpointProxyL, Teardown)

EUNIT_TEST (
    "Reusable test",
    "CMceComEndpoint",
    "Reusable",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_ReusableL, Teardown)

EUNIT_TEST (
    "InitParamL test",
    "CMceComEndpoint",
    "InitParamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_InitParamLL, Teardown)

EUNIT_TEST (
    "EnableL test",
    "CMceComEndpoint",
    "EnableL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_EnableLL, Teardown)

EUNIT_TEST (
    "DisableL test",
    "CMceComEndpoint",
    "DisableL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_DisableLL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComEndpoint",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_PrepareLL, Teardown)

EUNIT_TEST (
    "EventReceived test",
    "CMceComEndpoint",
    "EventReceived",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_EventReceivedL, Teardown)

EUNIT_TEST (
    "SetState test",
    "CMceComEndpoint",
    "SetState",
    "FUNCTIONALITY",
    SetupL, UT_CMceComEndpoint_SetStateL, Teardown)

EUNIT_END_TEST_TABLE




//  END OF FILE
