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
#include "ut_mcecomserial.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"
#include "mceserial.h"

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_MceComSerial* UT_MceComSerial::NewL()
    {
    UT_MceComSerial* self = UT_MceComSerial::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_MceComSerial* UT_MceComSerial::NewLC()
    {
    UT_MceComSerial* self = new( ELeave ) UT_MceComSerial();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_MceComSerial::~UT_MceComSerial()
    {
    }

// Default constructor
UT_MceComSerial::UT_MceComSerial()
    {
    }

// Second phase construct
void UT_MceComSerial::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_MceComSerial::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_MceComSerial::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_MceComSerial::UT_MceComSerial_TDes_DecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TDes_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_HBuf_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_HBuf_DecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CDesC8Array_DecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CDesC8Array_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceMediaId_DecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceMediaId_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_RArray_TMceCryptoContext_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_RArray_TMceCryptoContext_DecodeLL()
    {
    }


void UT_MceComSerial::UT_MceComSerial_CMceMsgBase_DecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgBase_DoDecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgBase_EncodeBufferCloneLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgBase_PushLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgBase_PopL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgBase_OwnershipRollbackPushLCL()
    {
    }


void UT_MceComSerial::UT_MceComSerial_CMceMsgTextArray_EncodeLL()
    {
    }


void UT_MceComSerial::UT_MceComSerial_CMceMsgTextArray_DoDecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgTextArray_CloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgTextArray_LocalCloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgTextArray_ArrayL()
    {
    }


void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPData_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPData_DoDecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPData_CloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPData_LocalCloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPData_HeadersL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPData_ContentTypeL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPReply_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPReply_DoDecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPReply_CloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPReply_LocalCloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPReply_ReasonL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_DoDecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_CloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_LocalCloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_IdL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_DialogIdL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_EventTypeL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_RecipientL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_OriginatorL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_EventHeaderL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_ReferToL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_ReferTypeL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_RefreshIntervalL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_SIPHeadersL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgSIPEvent_ContentTypeL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgObject_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgObject_DoDecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgObject_DoDecodeL1L()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgObject_ObjectL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgObject_CloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgObject_LocalCloseL()
    {
    }


void UT_MceComSerial::UT_MceComSerial_CMceMsgArray_EncodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgArray_DoDecodeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgArray_CloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_CMceMsgArray_LocalCloseL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceMediaStreamSerializer_InternalizeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceMediaStreamSerializer_ExternalizeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceSessionSerializer_InternalizeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceSessionSerializer_ExternalizeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceAudioStreamSerializer_InternalizeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceAudioStreamSerializer_ExternalizeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceVideoStreamSerializer_InternalizeLL()
    {
    }

void UT_MceComSerial::UT_MceComSerial_TMceVideoStreamSerializer_ExternalizeLL()
    {
    }

	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_MceComSerial,
    "MceComSerial tests",
    "UNIT" )

EUNIT_TEST (
    "DecodeL TDes test",
    "MceComSerial",
    "DecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TDes_DecodeLL, Teardown)

EUNIT_TEST (
    "EncodeL TDes test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TDes_EncodeLL, Teardown)

EUNIT_TEST (
    "EncodeL HBuf test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_HBuf_EncodeLL, Teardown)

EUNIT_TEST (
    "DecodeL HBuf test",
    "MceComSerial",
    "DecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_HBuf_DecodeLL, Teardown)

EUNIT_TEST (
    "DecodeL CDesC8Array test",
    "MceComSerial",
    "DecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CDesC8Array_DecodeLL, Teardown)

EUNIT_TEST (
    "EncodeL CDesC8Array test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CDesC8Array_EncodeLL, Teardown)

EUNIT_TEST (
    "DecodeL TMceMediaId test",
    "MceComSerial",
    "DecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceMediaId_DecodeLL, Teardown)

EUNIT_TEST (
    "EncodeL TMceMediaId test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceMediaId_EncodeLL, Teardown)

EUNIT_TEST (
    "EncodeL TMceCryptoContext test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_RArray_TMceCryptoContext_EncodeLL, Teardown)

EUNIT_TEST (
    "DecodeL TMceCryptoContext test",
    "MceComSerial",
    "DecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_RArray_TMceCryptoContext_DecodeLL, Teardown)


EUNIT_TEST (
    "CMceMsgBase::DecodeL test",
    "MceComSerial",
    "DecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgBase_DecodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgBase::DoDecodeL test",
    "MceComSerial",
    "DoDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgBase_DoDecodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgBase::EncodeBufferCloneL test",
    "MceComSerial",
    "EncodeBufferCloneL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgBase_EncodeBufferCloneLL, Teardown)

EUNIT_TEST (
    "CMceMsgBase::PushL test",
    "MceComSerial",
    "PushL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgBase_PushLL, Teardown)

EUNIT_TEST (
    "CMceMsgBase::Pop test",
    "MceComSerial",
    "Pop",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgBase_PopL, Teardown)

EUNIT_TEST (
    "CMceMsgBase::OwnershipRollbackPushLC test",
    "MceComSerial",
    "OwnershipRollbackPushLC",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgBase_OwnershipRollbackPushLCL, Teardown)


EUNIT_TEST (
    "CMceMsgTextArray::EncodeL CMceMsgTextArray test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgTextArray_EncodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgTextArray::DecodeL test",
    "MceComSerial",
    "DoDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgTextArray_DoDecodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgTextArray::Close test",
    "MceComSerial",
    "Close",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgTextArray_CloseL, Teardown)

EUNIT_TEST (
    "CMceMsgTextArray::LocalClose test",
    "MceComSerial",
    "LocalClose",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgTextArray_LocalCloseL, Teardown)

EUNIT_TEST (
    "CMceMsgTextArray::Array test",
    "MceComSerial",
    "Array",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgTextArray_ArrayL, Teardown)


EUNIT_TEST (
    "CMceMsgSIPData::EncodeL test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPData_EncodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPData::DoDecodeL test",
    "MceComSerial",
    "DoDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPData_DoDecodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPData::Close test",
    "MceComSerial",
    "Close",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPData_CloseL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPData::LocalClose test",
    "MceComSerial",
    "LocalClose",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPData_LocalCloseL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPData::Headers test",
    "MceComSerial",
    "Headers",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPData_HeadersL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPData::ContentType test",
    "MceComSerial",
    "ContentType",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPData_ContentTypeL, Teardown)


EUNIT_TEST (
    "CMceMsgSIPReply::EncodeL test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPReply_EncodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPReply::DoDecodeL test",
    "MceComSerial",
    "DoDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPReply_DoDecodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPReply::Close test",
    "MceComSerial",
    "Close",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPReply_CloseL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPReply::LocalClose test",
    "MceComSerial",
    "LocalClose",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPReply_LocalCloseL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPReply::Reason test",
    "MceComSerial",
    "Reason",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPReply_ReasonL, Teardown)


EUNIT_TEST (
    "CMceMsgSIPEvent::EncodeL test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_EncodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::DoDecodeL test",
    "MceComSerial",
    "DoDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_DoDecodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::Close test",
    "MceComSerial",
    "Close",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_CloseL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::LocalClose test",
    "MceComSerial",
    "LocalClose",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_LocalCloseL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::Id test",
    "MceComSerial",
    "Id",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_IdL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::DialogId test",
    "MceComSerial",
    "DialogId",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_DialogIdL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::EventType test",
    "MceComSerial",
    "EventType",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_EventTypeL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::Recipient test",
    "MceComSerial",
    "Recipient",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_RecipientL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::Originator test",
    "MceComSerial",
    "Originator",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_OriginatorL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::EventHeader test",
    "MceComSerial",
    "EventHeader",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_EventHeaderL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::ReferTo test",
    "MceComSerial",
    "ReferTo",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_ReferToL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::ReferType test",
    "MceComSerial",
    "ReferType",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_ReferTypeL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::RefreshInterval test",
    "MceComSerial",
    "RefreshInterval",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_RefreshIntervalL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::SIPHeaders test",
    "MceComSerial",
    "SIPHeaders",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_SIPHeadersL, Teardown)

EUNIT_TEST (
    "CMceMsgSIPEvent::ContentType test",
    "MceComSerial",
    "ContentType",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgSIPEvent_ContentTypeL, Teardown)

EUNIT_TEST (
    "CMceMsgObject::EncodeL test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgObject_EncodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgObject::DoDecodeL test",
    "MceComSerial",
    "DoDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgObject_DoDecodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgObject::DoDecodeL(sc) test",
    "MceComSerial",
    "DoDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgObject_DoDecodeL1L, Teardown)

EUNIT_TEST (
    "CMceMsgObject::Object test",
    "MceComSerial",
    "Object",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgObject_ObjectL, Teardown)

EUNIT_TEST (
    "CMceMsgObject::Close test",
    "MceComSerial",
    "Close",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgObject_CloseL, Teardown)

EUNIT_TEST (
    "CMceMsgObject::LocalClose test",
    "MceComSerial",
    "LocalClose",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgObject_LocalCloseL, Teardown)


EUNIT_TEST (
    "CMceMsgArray::EncodeL test",
    "MceComSerial",
    "EncodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgArray_EncodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgArray::DoDecodeL test",
    "MceComSerial",
    "DoDecodeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgArray_DoDecodeLL, Teardown)

EUNIT_TEST (
    "CMceMsgArray::Close test",
    "MceComSerial",
    "Close",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgArray_CloseL, Teardown)

EUNIT_TEST (
    "CMceMsgArray::LocalClose test",
    "MceComSerial",
    "LocalClose",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_CMceMsgArray_LocalCloseL, Teardown)


EUNIT_TEST (
    "TMceMediaStreamSerializer::InternalizeL test",
    "MceComSerial",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceMediaStreamSerializer_InternalizeLL, Teardown)

EUNIT_TEST (
    "TMceMediaStreamSerializer::ExternalizeL test",
    "MceComSerial",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceMediaStreamSerializer_ExternalizeLL, Teardown)

EUNIT_TEST (
    "TMceSessionSerializer::InternalizeL test",
    "MceComSerial",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceSessionSerializer_InternalizeLL, Teardown)

EUNIT_TEST (
    "TMceSessionSerializer::ExternalizeL test",
    "MceComSerial",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceSessionSerializer_ExternalizeLL, Teardown)

EUNIT_TEST (
    "TMceAudioStreamSerializer::InternalizeL test",
    "MceComSerial",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceAudioStreamSerializer_InternalizeLL, Teardown)

EUNIT_TEST (
    "TMceAudioStreamSerializer::ExternalizeL test",
    "MceComSerial",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceAudioStreamSerializer_ExternalizeLL, Teardown)

EUNIT_TEST (
    "TMceVideoStreamSerializer::InternalizeL test",
    "MceComSerial",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceVideoStreamSerializer_InternalizeLL, Teardown)

EUNIT_TEST (
    "TMceVideoStreamSerializer::ExternalizeL test",
    "MceComSerial",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_MceComSerial_TMceVideoStreamSerializer_ExternalizeLL, Teardown)


EUNIT_END_TEST_TABLE



//  END OF FILE
