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




#ifndef __UT_CMCECOMMEDIASTREAM_H__
#define __UT_CMCECOMMEDIASTREAM_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComMediaStream;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComMediaStream : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComMediaStream* NewL();
    static UT_CMceComMediaStream* NewLC();
    ~UT_CMceComMediaStream();

private:    // Constructors and destructors

    UT_CMceComMediaStream();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
	void UT_CMceComMediaStream_SetSourceLL();
	void UT_CMceComMediaStream_AddSinkLL();
    void UT_CMceComMediaStream_DeleteSinkL();
	void UT_CMceComMediaStream_SourceL();
	void UT_CMceComMediaStream_SinksL();
    void UT_CMceComMediaStream_BindLL();
    void UT_CMceComMediaStream_BoundStreamLL();
    void UT_CMceComMediaStream_BoundStreamL();
	void UT_CMceComMediaStream_BinderL();
	void UT_CMceComMediaStream_operatorParenthesisL();
	void UT_CMceComMediaStream_operatorConstParenthesisL();
    void UT_CMceComMediaStream_SendStreamL();
    void UT_CMceComMediaStream_ReceiveStreamL();
    void UT_CMceComMediaStream_OfferStreamL();
    void UT_CMceComMediaStream_AnswerStreamL();
    void UT_CMceComMediaStream_SdpIndexL();
    void UT_CMceComMediaStream_SerializationId();
    void UT_CMceComMediaStream_InternalizeFlatLL();
    void UT_CMceComMediaStream_ExternalizeFlatLL();
    void UT_CMceComMediaStream_InternalizeLL();
    void UT_CMceComMediaStream_ExternalizeLL();
    void UT_CMceComMediaStream_BaseFactoryL();
    void UT_CMceComMediaStream_FactoryL();
	void UT_CMceComMediaStream_SetSourceL1L();
	void UT_CMceComMediaStream_AddSinkL1L();
	void UT_CMceComMediaStream_IdL();
	void UT_CMceComMediaStream_SessionL();
    void UT_CMceComMediaStream_InitializeLL();
    void UT_CMceComMediaStream_EventReceivedLL();
    void UT_CMceComMediaStream_UpdateLL();
    void UT_CMceComMediaStream_IsEnabledL();
	void UT_CMceComMediaStream_SetRemoteMediaPortL();
    void UT_CMceComMediaStream_SetLocalMediaPortL();
	void UT_CMceComMediaStream_RemoteMediaPortL();
	void UT_CMceComMediaStream_LocalMediaPortL();
    void UT_CMceComMediaStream_DecodedLL();
    void UT_CMceComMediaStream_EventReceivedL();
    void UT_CMceComMediaStream_SetStateL();
    void UT_CMceComMediaStream_SetLinkIdL();
    void UT_CMceComMediaStream_DirectionL();
    void UT_CMceComMediaStream_SetDirectionL();
    void UT_CMceComMediaStream_SetDirectionLL();
    void UT_CMceComMediaStream_EnableL();
    void UT_CMceComMediaStream_SdpStreamTypeL();
    void UT_CMceComMediaStream_PreconditionsLL();
    void UT_CMceComMediaStream_PreconditionsL();
    void UT_CMceComMediaStream_EmptySinkLL();
    void UT_CMceComMediaStream_EmptySourceLL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMMEDIASTREAM_H__

// End of file
