/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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




#ifndef __UT_MCECOMSERIAL_H__
#define __UT_MCECOMSERIAL_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_MceComSerial : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_MceComSerial* NewL();
    static UT_MceComSerial* NewLC();
    ~UT_MceComSerial();

private:    // Constructors and destructors

    UT_MceComSerial();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_MceComSerial_TDes_DecodeLL();
    void UT_MceComSerial_TDes_EncodeLL();
    void UT_MceComSerial_HBuf_EncodeLL();
    void UT_MceComSerial_HBuf_DecodeLL();
    void UT_MceComSerial_CDesC8Array_DecodeLL();
    void UT_MceComSerial_CDesC8Array_EncodeLL();
    void UT_MceComSerial_TMceMediaId_DecodeLL();
    void UT_MceComSerial_TMceMediaId_EncodeLL();
	void UT_MceComSerial_RArray_TMceCryptoContext_EncodeLL();
    void UT_MceComSerial_RArray_TMceCryptoContext_DecodeLL();

    void UT_MceComSerial_CMceMsgBase_DecodeLL();
    void UT_MceComSerial_CMceMsgBase_DoDecodeLL();
    void UT_MceComSerial_CMceMsgBase_EncodeBufferCloneLL();
	void UT_MceComSerial_CMceMsgBase_PushLL();
	void UT_MceComSerial_CMceMsgBase_PopL();
    void UT_MceComSerial_CMceMsgBase_OwnershipRollbackPushLCL();
    
    void UT_MceComSerial_CMceMsgTextArray_EncodeLL();
    void UT_MceComSerial_CMceMsgTextArray_DoDecodeLL();
	void UT_MceComSerial_CMceMsgTextArray_CloseL();
	void UT_MceComSerial_CMceMsgTextArray_LocalCloseL();
    void UT_MceComSerial_CMceMsgTextArray_ArrayL();
	
    void UT_MceComSerial_CMceMsgSIPData_EncodeLL();
    void UT_MceComSerial_CMceMsgSIPData_DoDecodeLL();
	void UT_MceComSerial_CMceMsgSIPData_CloseL();
	void UT_MceComSerial_CMceMsgSIPData_LocalCloseL();
    void UT_MceComSerial_CMceMsgSIPData_HeadersL();
    void UT_MceComSerial_CMceMsgSIPData_ContentTypeL();

    void UT_MceComSerial_CMceMsgSIPReply_EncodeLL();
    void UT_MceComSerial_CMceMsgSIPReply_DoDecodeLL();
	void UT_MceComSerial_CMceMsgSIPReply_CloseL();
	void UT_MceComSerial_CMceMsgSIPReply_LocalCloseL();
    void UT_MceComSerial_CMceMsgSIPReply_ReasonL();
    
    void UT_MceComSerial_CMceMsgSIPEvent_EncodeLL();
    void UT_MceComSerial_CMceMsgSIPEvent_DoDecodeLL();
	void UT_MceComSerial_CMceMsgSIPEvent_CloseL();
	void UT_MceComSerial_CMceMsgSIPEvent_LocalCloseL();
	void UT_MceComSerial_CMceMsgSIPEvent_IdL();
	void UT_MceComSerial_CMceMsgSIPEvent_DialogIdL();
	void UT_MceComSerial_CMceMsgSIPEvent_EventTypeL();
    void UT_MceComSerial_CMceMsgSIPEvent_RecipientL();
    void UT_MceComSerial_CMceMsgSIPEvent_OriginatorL();
    void UT_MceComSerial_CMceMsgSIPEvent_EventHeaderL();
    void UT_MceComSerial_CMceMsgSIPEvent_ReferToL();
	void UT_MceComSerial_CMceMsgSIPEvent_ReferTypeL();
	void UT_MceComSerial_CMceMsgSIPEvent_RefreshIntervalL();
    void UT_MceComSerial_CMceMsgSIPEvent_SIPHeadersL();
    void UT_MceComSerial_CMceMsgSIPEvent_ContentTypeL();
    
    void UT_MceComSerial_CMceMsgObject_EncodeLL();
    void UT_MceComSerial_CMceMsgObject_DoDecodeLL();
    void UT_MceComSerial_CMceMsgObject_DoDecodeL1L();
    void UT_MceComSerial_CMceMsgObject_ObjectL();
	void UT_MceComSerial_CMceMsgObject_CloseL();
	void UT_MceComSerial_CMceMsgObject_LocalCloseL();

    void UT_MceComSerial_CMceMsgArray_EncodeLL();
    void UT_MceComSerial_CMceMsgArray_DoDecodeLL();
	void UT_MceComSerial_CMceMsgArray_CloseL();
	void UT_MceComSerial_CMceMsgArray_LocalCloseL();
    
    void UT_MceComSerial_TMceMediaStreamSerializer_InternalizeLL();
    void UT_MceComSerial_TMceMediaStreamSerializer_ExternalizeLL();

    void UT_MceComSerial_TMceSessionSerializer_InternalizeLL();
    void UT_MceComSerial_TMceSessionSerializer_ExternalizeLL();

    void UT_MceComSerial_TMceAudioStreamSerializer_InternalizeLL();
    void UT_MceComSerial_TMceAudioStreamSerializer_ExternalizeLL();

    void UT_MceComSerial_TMceVideoStreamSerializer_InternalizeLL();
    void UT_MceComSerial_TMceVideoStreamSerializer_ExternalizeLL();


    
private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_MCECOMSERIAL_H__

// End of file
