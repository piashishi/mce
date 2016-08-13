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
#include "ut_cmcecommediastream.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComMediaStream* UT_CMceComMediaStream::NewL()
    {
    UT_CMceComMediaStream* self = UT_CMceComMediaStream::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComMediaStream* UT_CMceComMediaStream::NewLC()
    {
    UT_CMceComMediaStream* self = new( ELeave ) UT_CMceComMediaStream();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComMediaStream::~UT_CMceComMediaStream()
    {
    }

// Default constructor
UT_CMceComMediaStream::UT_CMceComMediaStream()
    {
    }

// Second phase construct
void UT_CMceComMediaStream::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComMediaStream::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComMediaStream::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_CMceComMediaStream::UT_CMceComMediaStream_SetSourceLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_AddSinkLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_DeleteSinkL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SourceL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SinksL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_BindLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_BoundStreamLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_BoundStreamL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_BinderL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_operatorParenthesisL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_operatorConstParenthesisL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SendStreamL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_ReceiveStreamL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_OfferStreamL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_AnswerStreamL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SdpIndexL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_InternalizeFlatLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_ExternalizeFlatLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_InternalizeLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_ExternalizeLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_BaseFactoryL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_FactoryL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SetSourceL1L()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_AddSinkL1L()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_IdL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SessionL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_InitializeLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_EventReceivedLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_UpdateLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_IsEnabledL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SetRemoteMediaPortL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SetLocalMediaPortL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_RemoteMediaPortL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_LocalMediaPortL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_DecodedLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_EventReceivedL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SetStateL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SetLinkIdL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_DirectionL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SetDirectionL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SetDirectionLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_EnableL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_SdpStreamTypeL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_PreconditionsLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_PreconditionsL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_EmptySinkLL()
    {
    }

void UT_CMceComMediaStream::UT_CMceComMediaStream_EmptySourceLL()
    {
    }




	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComMediaStream,
    "CMceComMediaStream tests",
    "UNIT" )

EUNIT_TEST (
    "SetSourceL test",
    "CMceComMediaStream",
    "SetSourceL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SetSourceLL, Teardown)

EUNIT_TEST (
    "AddSinkL test",
    "CMceComMediaStream",
    "AddSinkL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_AddSinkLL, Teardown)

EUNIT_TEST (
    "DeleteSink test",
    "CMceComMediaStream",
    "DeleteSink",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_DeleteSinkL, Teardown)

EUNIT_TEST (
    "Source test",
    "CMceComMediaStream",
    "Source",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SourceL, Teardown)

EUNIT_TEST (
    "Sinks test",
    "CMceComMediaStream",
    "Sinks",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SinksL, Teardown)

EUNIT_TEST (
    "BindL test",
    "CMceComMediaStream",
    "BindL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_BindLL, Teardown)

EUNIT_TEST (
    "BoundStreamL test",
    "CMceComMediaStream",
    "BoundStreamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_BoundStreamLL, Teardown)

EUNIT_TEST (
    "BoundStream test",
    "CMceComMediaStream",
    "BoundStream",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_BoundStreamL, Teardown)

EUNIT_TEST (
    "Binder test",
    "CMceComMediaStream",
    "Binder",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_BinderL, Teardown)

EUNIT_TEST (
    "operatorParenthesis test",
    "CMceComMediaStream",
    "operatorParenthesis",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_operatorParenthesisL, Teardown)

EUNIT_TEST (
    "operatorConstParenthesis test",
    "CMceComMediaStream",
    "operatorConstParenthesis",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_operatorConstParenthesisL, Teardown)

EUNIT_TEST (
    "SendStream test",
    "CMceComMediaStream",
    "SendStream",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SendStreamL, Teardown)

EUNIT_TEST (
    "ReceiveStream test",
    "CMceComMediaStream",
    "ReceiveStream",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_ReceiveStreamL, Teardown)

EUNIT_TEST (
    "OfferStream test",
    "CMceComMediaStream",
    "OfferStream",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_OfferStreamL, Teardown)

EUNIT_TEST (
    "AnswerStream test",
    "CMceComMediaStream",
    "AnswerStream",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_AnswerStreamL, Teardown)

EUNIT_TEST (
    "SdpIndex test",
    "CMceComMediaStream",
    "SdpIndex",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SdpIndexL, Teardown)

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComMediaStream",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComMediaStream",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "InternalizeL test",
    "CMceComMediaStream",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_InternalizeLL, Teardown)

EUNIT_TEST (
    "ExternalizeL test",
    "CMceComMediaStream",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_ExternalizeLL, Teardown)

EUNIT_TEST (
    "BaseFactory test",
    "CMceComMediaStream",
    "BaseFactory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_BaseFactoryL, Teardown)

EUNIT_TEST (
    "Factory test",
    "CMceComMediaStream",
    "Factory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_FactoryL, Teardown)

EUNIT_TEST (
    "SetSourceL(sc) test",
    "CMceComMediaStream",
    "SetSourceL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SetSourceL1L, Teardown)

EUNIT_TEST (
    "AddSinkL(sc) test",
    "CMceComMediaStream",
    "AddSinkL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_AddSinkL1L, Teardown)

EUNIT_TEST (
    "Id test",
    "CMceComMediaStream",
    "Id",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_IdL, Teardown)

EUNIT_TEST (
    "Session test",
    "CMceComMediaStream",
    "Session",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SessionL, Teardown)

EUNIT_TEST (
    "InitializeL test",
    "CMceComMediaStream",
    "InitializeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_InitializeLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComMediaStream",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_EventReceivedLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComMediaStream",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_UpdateLL, Teardown)

EUNIT_TEST (
    "IsEnabled test",
    "CMceComMediaStream",
    "IsEnabled",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_IsEnabledL, Teardown)

EUNIT_TEST (
    "SetRemoteMediaPort test",
    "CMceComMediaStream",
    "SetRemoteMediaPort",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SetRemoteMediaPortL, Teardown)

EUNIT_TEST (
    "SetLocalMediaPort test",
    "CMceComMediaStream",
    "SetLocalMediaPort",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SetLocalMediaPortL, Teardown)

EUNIT_TEST (
    "RemoteMediaPort test",
    "CMceComMediaStream",
    "RemoteMediaPort",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_RemoteMediaPortL, Teardown)

EUNIT_TEST (
    "LocalMediaPort test",
    "CMceComMediaStream",
    "LocalMediaPort",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_LocalMediaPortL, Teardown)

EUNIT_TEST (
    "DecodedL test",
    "CMceComMediaStream",
    "DecodedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_DecodedLL, Teardown)

EUNIT_TEST (
    "EventReceived test",
    "CMceComMediaStream",
    "EventReceived",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_EventReceivedL, Teardown)

EUNIT_TEST (
    "SetState test",
    "CMceComMediaStream",
    "SetState",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SetStateL, Teardown)

EUNIT_TEST (
    "SetLinkId test",
    "CMceComMediaStream",
    "SetLinkId",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SetLinkIdL, Teardown)

EUNIT_TEST (
    "Direction test",
    "CMceComMediaStream",
    "Direction",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_DirectionL, Teardown)

EUNIT_TEST (
    "SetDirection test",
    "CMceComMediaStream",
    "SetDirection",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SetDirectionL, Teardown)

EUNIT_TEST (
    "SetDirectionL test",
    "CMceComMediaStream",
    "SetDirectionL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SetDirectionLL, Teardown)

EUNIT_TEST (
    "Enable test",
    "CMceComMediaStream",
    "Enable",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_EnableL, Teardown)

EUNIT_TEST (
    "SdpStreamType test",
    "CMceComMediaStream",
    "SdpStreamType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_SdpStreamTypeL, Teardown)

EUNIT_TEST (
    "PreconditionsL test",
    "CMceComMediaStream",
    "PreconditionsL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_PreconditionsLL, Teardown)

EUNIT_TEST (
    "Preconditions test",
    "CMceComMediaStream",
    "Preconditions",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_PreconditionsL, Teardown)

EUNIT_TEST (
    "EmptySinkL test",
    "CMceComMediaStream",
    "EmptySinkL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_EmptySinkLL, Teardown)

EUNIT_TEST (
    "EmptySourceL test",
    "CMceComMediaStream",
    "EmptySourceL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComMediaStream_EmptySourceLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
