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




#ifndef __UT_CMCECOMENDPOINT_H__
#define __UT_CMCECOMENDPOINT_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS
class CMceMediaManager;
class CMceComSession;
class CMceComMediaSource;
class CMceComMediaSink;
class CMceComAudioStream;
class CMceComAudioCodec;
class CMceComEndpoint;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComEndpoint : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComEndpoint* NewL();
    static UT_CMceComEndpoint* NewLC();
    ~UT_CMceComEndpoint();

private:    // Constructors and destructors

    UT_CMceComEndpoint();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    
    void UT_CMceComEndpoint_SerializationIdL();
    void UT_CMceComEndpoint_InternalizeFlatLL();
    void UT_CMceComEndpoint_ExternalizeFlatLL();
    void UT_CMceComEndpoint_InternalizeLL();
    void UT_CMceComEndpoint_ExternalizeLL();
	void UT_CMceComEndpoint_IdL();
    void UT_CMceComEndpoint_BaseFactoryL();
    void UT_CMceComEndpoint_ReferenceCountL();
	void UT_CMceComEndpoint_MediaStreamL();
    void UT_CMceComEndpoint_operatorEqualL();
    void UT_CMceComEndpoint_UnInitializeL();
    void UT_CMceComEndpoint_IsEnabledL();
    void UT_CMceComEndpoint_EnabledL();
    void UT_CMceComEndpoint_InitializeLL();
    void UT_CMceComEndpoint_StreamAddedLL();
	void UT_CMceComEndpoint_EndpointProxyL();
    void UT_CMceComEndpoint_SetupEndpointProxyLL();
    void UT_CMceComEndpoint_CreateEndpointProxyLL();
    void UT_CMceComEndpoint_UsesEndpointProxyL();
    void UT_CMceComEndpoint_ReusableL();
    void UT_CMceComEndpoint_InitParamLL();
    void UT_CMceComEndpoint_EnableLL();
    void UT_CMceComEndpoint_DisableLL();
    void UT_CMceComEndpoint_PrepareLL();
    void UT_CMceComEndpoint_EventReceivedL();
    void UT_CMceComEndpoint_SetStateL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    
    CMceComSession* iSession;
    CMceComMediaSource* iSource;
    CMceComMediaSink* iSink;
    CMceComAudioStream* iStream;
    CMceComAudioCodec* iCodec;
    
    CMceComEndpoint* iComEndpoint;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMENDPOINT_H__

// End of file
