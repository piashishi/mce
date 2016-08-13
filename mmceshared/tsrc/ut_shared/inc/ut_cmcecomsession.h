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




#ifndef __UT_CMCECOMSESSION_H__
#define __UT_CMCECOMSESSION_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off


//  INTERNAL INCLUDES

//  FORWARD DECLARATIONS
class CMceComSession;
class CMceMediaManager;


//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComSession : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComSession* NewL();
    static UT_CMceComSession* NewLC();
    ~UT_CMceComSession();

private:    // Constructors and destructors

    UT_CMceComSession();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
	void UT_CMceComSession_IdL();
	void UT_CMceComSession_AddStreamLL();
	void UT_CMceComSession_StreamsL();
	void UT_CMceComSession_SetObserverL();
	void UT_CMceComSession_AddBundleLL();
    void UT_CMceComSession_RemoveBundleLL();
	void UT_CMceComSession_BundlesL();
	void UT_CMceComSession_MediaObserverL();
	void UT_CMceComSession_SetOriginatorLL();
	void UT_CMceComSession_SetRecipientLL();
    void UT_CMceComSession_ModifierL();
    void UT_CMceComSession_SerializationIdL();
    void UT_CMceComSession_InternalizeFlatLL();
    void UT_CMceComSession_ExternalizeFlatLL();
    void UT_CMceComSession_InternalizeLL();
    void UT_CMceComSession_ExternalizeLL();
    void UT_CMceComSession_BaseFactoryL();
    void UT_CMceComSession_FactoryL();
    void UT_CMceComSession_InitializeLL();
    void UT_CMceComSession_EventReceivedLL();
    void UT_CMceComSession_UpdateLL();
    void UT_CMceComSession_CloneLL();
    void UT_CMceComSession_IsStructureChangedL();
    void UT_CMceComSession_UpdateFlatLL();
    void UT_CMceComSession_DeleteL();
    void UT_CMceComSession_SdpSessionL();
    void UT_CMceComSession_BackupL();
    void UT_CMceComSession_IsBackupL();
    void UT_CMceComSession_IsMergedL();
    void UT_CMceComSession_MergeL();
    void UT_CMceComSession_UnMergeL();
    void UT_CMceComSession_UnMergeLL();
    void UT_CMceComSession_AttachSDPSessionLL();
    void UT_CMceComSession_DetachSDPSessionL();
    void UT_CMceComSession_SetNegotiationStateLL();
    void UT_CMceComSession_NegotiationStateL();
    void UT_CMceComSession_PrepareLL();
    void UT_CMceComSession_PrepareL1L();
    void UT_CMceComSession_MccStreamsL();
    void UT_CMceComSession_AdoptedMccStreamsL();
    void UT_CMceComSession_AdoptStreamLL();
    void UT_CMceComSession_RemoveAdoptedStreamL();
    void UT_CMceComSession_SecureSessionLL();
	void UT_CMceComSession_SecureSessionL();
	void UT_CMceComSession_CloneSecureSessionLL();
    void UT_CMceComSession_DeleteSecureSessionL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMSESSION_H__

// End of file
