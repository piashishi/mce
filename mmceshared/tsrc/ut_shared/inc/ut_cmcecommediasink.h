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




#ifndef __UT_CMCECOMMEDIASINK_H__
#define __UT_CMCECOMMEDIASINK_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComMediaSink;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComMediaSink : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComMediaSink* NewL();
    static UT_CMceComMediaSink* NewLC();
    ~UT_CMceComMediaSink();

private:    // Constructors and destructors

    UT_CMceComMediaSink();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComMediaSink_InternalizeFlatLL();
    void UT_CMceComMediaSink_ExternalizeFlatLL();
    void UT_CMceComMediaSink_EventReceivedLL();
    void UT_CMceComMediaSink_UpdateLL();
    void UT_CMceComMediaSink_CloneLL();
    void UT_CMceComMediaSink_UseRTCPL();
    void UT_CMceComMediaSink_TypeL();
    void UT_CMceComMediaSink_FactoryL();
    void UT_CMceComMediaSink_SetSSRCL();
    void UT_CMceComMediaSink_MccTypeL();


private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
	

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMMEDIASINK_H__

// End of file
