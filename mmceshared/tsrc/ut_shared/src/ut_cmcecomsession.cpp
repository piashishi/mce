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
#include "ut_cmcecomsession.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComSession* UT_CMceComSession::NewL()
    {
    UT_CMceComSession* self = UT_CMceComSession::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComSession* UT_CMceComSession::NewLC()
    {
    UT_CMceComSession* self = new( ELeave ) UT_CMceComSession();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComSession::~UT_CMceComSession()
    {
    }

// Default constructor
UT_CMceComSession::UT_CMceComSession()
    {
    }

// Second phase construct
void UT_CMceComSession::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComSession::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_CMceComSession::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }
    


void UT_CMceComSession::UT_CMceComSession_IdL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_AddStreamLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_StreamsL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_SetObserverL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_AddBundleLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_RemoveBundleLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_BundlesL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_MediaObserverL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_SetOriginatorLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_SetRecipientLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_ModifierL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_SerializationIdL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_InternalizeFlatLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_ExternalizeFlatLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_InternalizeLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_ExternalizeLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_BaseFactoryL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_FactoryL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_InitializeLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_EventReceivedLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_UpdateLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_CloneLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_IsStructureChangedL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_UpdateFlatLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_DeleteL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_SdpSessionL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_BackupL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_IsBackupL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_IsMergedL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_MergeL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_UnMergeL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_UnMergeLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_AttachSDPSessionLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_DetachSDPSessionL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_SetNegotiationStateLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_NegotiationStateL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_PrepareLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_PrepareL1L()
    {
    }

void UT_CMceComSession::UT_CMceComSession_MccStreamsL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_AdoptedMccStreamsL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_AdoptStreamLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_RemoveAdoptedStreamL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_SecureSessionLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_SecureSessionL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_CloneSecureSessionLL()
    {
    }

void UT_CMceComSession::UT_CMceComSession_DeleteSecureSessionL()
    {
    }



	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComSession,
    "CMceComSession tests",
    "UNIT" )

EUNIT_TEST (
    "Id test",
    "CMceComSession",
    "Id",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_IdL, Teardown)

EUNIT_TEST (
    "AddStreamL test",
    "CMceComSession",
    "AddStreamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_AddStreamLL, Teardown)

EUNIT_TEST (
    "Streams test",
    "CMceComSession",
    "Streams",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_StreamsL, Teardown)

EUNIT_TEST (
    "SetObserver test",
    "CMceComSession",
    "SetObserver",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_SetObserverL, Teardown)

EUNIT_TEST (
    "AddBundleL test",
    "CMceComSession",
    "AddBundleL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_AddBundleLL, Teardown)

EUNIT_TEST (
    "RemoveBundleL test",
    "CMceComSession",
    "RemoveBundleL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_RemoveBundleLL, Teardown)

EUNIT_TEST (
    "Bundles test",
    "CMceComSession",
    "Bundles",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_BundlesL, Teardown)

EUNIT_TEST (
    "MediaObserver test",
    "CMceComSession",
    "MediaObserver",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_MediaObserverL, Teardown)

EUNIT_TEST (
    "SetOriginatorL test",
    "CMceComSession",
    "SetOriginatorL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_SetOriginatorLL, Teardown)

EUNIT_TEST (
    "SetRecipientL test",
    "CMceComSession",
    "SetRecipientL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_SetRecipientLL, Teardown)

EUNIT_TEST (
    "Modifier test",
    "CMceComSession",
    "Modifier",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_ModifierL, Teardown)

EUNIT_TEST (
    "SerializationId test",
    "CMceComSession",
    "SerializationId",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_SerializationIdL, Teardown)

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComSession",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComSession",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "InternalizeL test",
    "CMceComSession",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_InternalizeLL, Teardown)

EUNIT_TEST (
    "ExternalizeL test",
    "CMceComSession",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_ExternalizeLL, Teardown)

EUNIT_TEST (
    "BaseFactory test",
    "CMceComSession",
    "BaseFactory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_BaseFactoryL, Teardown)

EUNIT_TEST (
    "Factory test",
    "CMceComSession",
    "Factory",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_FactoryL, Teardown)

EUNIT_TEST (
    "InitializeL test",
    "CMceComSession",
    "InitializeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_InitializeLL, Teardown)

EUNIT_TEST (
    "EventReceivedL test",
    "CMceComSession",
    "EventReceivedL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_EventReceivedLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComSession",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_UpdateLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComSession",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_CloneLL, Teardown)

EUNIT_TEST (
    "IsStructureChanged test",
    "CMceComSession",
    "IsStructureChanged",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_IsStructureChangedL, Teardown)

EUNIT_TEST (
    "UpdateFlatL test",
    "CMceComSession",
    "UpdateFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_UpdateFlatLL, Teardown)

EUNIT_TEST (
    "Delete test",
    "CMceComSession",
    "Delete",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_DeleteL, Teardown)

EUNIT_TEST (
    "SdpSession test",
    "CMceComSession",
    "SdpSession",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_SdpSessionL, Teardown)

EUNIT_TEST (
    "Backup test",
    "CMceComSession",
    "Backup",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_BackupL, Teardown)

EUNIT_TEST (
    "IsBackup test",
    "CMceComSession",
    "IsBackup",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_IsBackupL, Teardown)

EUNIT_TEST (
    "IsMerged test",
    "CMceComSession",
    "IsMerged",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_IsMergedL, Teardown)

EUNIT_TEST (
    "Merge test",
    "CMceComSession",
    "Merge",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_MergeL, Teardown)

EUNIT_TEST (
    "UnMerge test",
    "CMceComSession",
    "UnMerge",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_UnMergeL, Teardown)

EUNIT_TEST (
    "UnMergeL test",
    "CMceComSession",
    "UnMergeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_UnMergeLL, Teardown)

EUNIT_TEST (
    "AttachSDPSessionL test",
    "CMceComSession",
    "AttachSDPSessionL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_AttachSDPSessionLL, Teardown)

EUNIT_TEST (
    "DetachSDPSession test",
    "CMceComSession",
    "DetachSDPSession",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_DetachSDPSessionL, Teardown)

EUNIT_TEST (
    "SetNegotiationStateL test",
    "CMceComSession",
    "SetNegotiationStateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_SetNegotiationStateLL, Teardown)

EUNIT_TEST (
    "NegotiationState test",
    "CMceComSession",
    "NegotiationState",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_NegotiationStateL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComSession",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_PrepareLL, Teardown)

EUNIT_TEST (
    "PrepareL(m) test",
    "CMceComSession",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_PrepareL1L, Teardown)

EUNIT_TEST (
    "MccStreams test",
    "CMceComSession",
    "MccStreams",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_MccStreamsL, Teardown)

EUNIT_TEST (
    "AdoptedMccStreams test",
    "CMceComSession",
    "AdoptedMccStreams",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_AdoptedMccStreamsL, Teardown)

EUNIT_TEST (
    "AdoptStreamL test",
    "CMceComSession",
    "AdoptStreamL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_AdoptStreamLL, Teardown)

EUNIT_TEST (
    "RemoveAdoptedStream test",
    "CMceComSession",
    "RemoveAdoptedStream",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_RemoveAdoptedStreamL, Teardown)

EUNIT_TEST (
    "SecureSessionL test",
    "CMceComSession",
    "SecureSessionL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_SecureSessionLL, Teardown)

EUNIT_TEST (
    "SecureSession test",
    "CMceComSession",
    "SecureSession",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_SecureSessionL, Teardown)

EUNIT_TEST (
    "CloneSecureSessionL test",
    "CMceComSession",
    "CloneSecureSessionL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_CloneSecureSessionLL, Teardown)

EUNIT_TEST (
    "DeleteSecureSession test",
    "CMceComSession",
    "DeleteSecureSession",
    "FUNCTIONALITY",
    SetupL, UT_CMceComSession_DeleteSecureSessionL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
