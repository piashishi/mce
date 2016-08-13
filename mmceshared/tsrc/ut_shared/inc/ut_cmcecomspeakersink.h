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




#ifndef __UT_CMCECOMSPEAKERSINK_H__
#define __UT_CMCECOMSPEAKERSINK_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComSpeakerSink;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComSpeakerSink : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComSpeakerSink* NewL();
    static UT_CMceComSpeakerSink* NewLC();
    ~UT_CMceComSpeakerSink();

private:    // Constructors and destructors

    UT_CMceComSpeakerSink();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComSpeakerSink_InternalizeFlatLL();
    void UT_CMceComSpeakerSink_ExternalizeFlatLL();
    void UT_CMceComSpeakerSink_EventReceivedLL();
    void UT_CMceComSpeakerSink_CloneLL();
    void UT_CMceComSpeakerSink_UpdateLL();
    void UT_CMceComSpeakerSink_CreateEndpointProxyLL();
    void UT_CMceComSpeakerSink_UsesEndpointProxyL();
    void UT_CMceComSpeakerSink_ReusableL();
    void UT_CMceComSpeakerSink_MccTypeL();
    void UT_CMceComSpeakerSink_InitParamLL();
    void UT_CMceComSpeakerSink_PrepareLL();


private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    
    CMceComSpeakerSink* iSpeaker;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMSPEAKERSINK_H__

// End of file
