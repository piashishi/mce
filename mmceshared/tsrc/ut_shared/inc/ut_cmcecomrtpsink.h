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




#ifndef __UT_CMCECOMRTPSINK_H__
#define __UT_CMCECOMRTPSINK_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComRtpSink;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComRtpSink : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComRtpSink* NewL();
    static UT_CMceComRtpSink* NewLC();
    ~UT_CMceComRtpSink();

private:    // Constructors and destructors

    UT_CMceComRtpSink();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComRtpSink_InternalizeFlatLL();
    void UT_CMceComRtpSink_ExternalizeFlatLL();
    void UT_CMceComRtpSink_EventReceivedLL();
    void UT_CMceComRtpSink_CloneLL();
    void UT_CMceComRtpSink_UpdateLL();
    void UT_CMceComRtpSink_UseRTCPL();
    void UT_CMceComRtpSink_SetSSRCL();
    void UT_CMceComRtpSink_IsEnabledL();
    void UT_CMceComRtpSink_MccTypeL();
    void UT_CMceComRtpSink_PrepareLL();


private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMRTPSINK_H__

// End of file
