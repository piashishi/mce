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




#ifndef __UT_CMCECOMAVSINK_H__
#define __UT_CMCECOMAVSINK_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComAvSink;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComAvSink : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComAvSink* NewL();
    static UT_CMceComAvSink* NewLC();
    ~UT_CMceComAvSink();

private:    // Constructors and destructors

    UT_CMceComAvSink();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComAvSink_InternalizeFlatLL();
    void UT_CMceComAvSink_ExternalizeFlatLL();
    void UT_CMceComAvSink_EventReceivedLL();
    void UT_CMceComAvSink_CloneLL();
    void UT_CMceComAvSink_UpdateLL();
    void UT_CMceComAvSink_ServesProxyClientL();
    void UT_CMceComAvSink_AddProxyClientLL();
    void UT_CMceComAvSink_RemoveProxyClientL();
    void UT_CMceComAvSink_MccTypeL();
    void UT_CMceComAvSink_InitParamLL();
    void UT_CMceComAvSink_PrepareLL();
    void UT_CMceComAvSink_ClientEnableLL();
    void UT_CMceComAvSink_ClientDisableLL();
    void UT_CMceComAvSink_SetParameterLL();

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
	

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMAVSINK_H__

// End of file
