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




#ifndef __UT_CMCECOMRTPSOURCE_H__
#define __UT_CMCECOMRTPSOURCE_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComRtpSource;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComRtpSource : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComRtpSource* NewL();
    static UT_CMceComRtpSource* NewLC();
    ~UT_CMceComRtpSource();

private:    // Constructors and destructors

    UT_CMceComRtpSource();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComRtpSource_InternalizeFlatLL();
    void UT_CMceComRtpSource_ExternalizeFlatLL();
    void UT_CMceComRtpSource_EventReceivedLL();
    void UT_CMceComRtpSource_CloneLL();
    void UT_CMceComRtpSource_UpdateLL();
    void UT_CMceComRtpSource_InactivityTimerL();
    void UT_CMceComRtpSource_MccTypeL();
    void UT_CMceComRtpSource_InitParamLL();
    void UT_CMceComRtpSource_PrepareLL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMRTPSOURCE_H__

// End of file
