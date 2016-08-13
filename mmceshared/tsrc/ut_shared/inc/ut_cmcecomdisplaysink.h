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




#ifndef __UT_CMCECOMDISPLAYSINK_H__
#define __UT_CMCECOMDISPLAYSINK_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComDisplaySink;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComDisplaySink : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComDisplaySink* NewL();
    static UT_CMceComDisplaySink* NewLC();
    ~UT_CMceComDisplaySink();

private:    // Constructors and destructors

    UT_CMceComDisplaySink();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComDisplaySink_InternalizeFlatLL();
    void UT_CMceComDisplaySink_ExternalizeFlatLL();
    void UT_CMceComDisplaySink_EventReceivedLL();
    void UT_CMceComDisplaySink_CloneLL();
    void UT_CMceComDisplaySink_UpdateLL();
    void UT_CMceComDisplaySink_CreateEndpointProxyLL();
    void UT_CMceComDisplaySink_UsesEndpointProxyL();
    void UT_CMceComDisplaySink_DisplayRectL();
    void UT_CMceComDisplaySink_SetDisplayRectL();
    void UT_CMceComDisplaySink_ToRectL();
    void UT_CMceComDisplaySink_ToPointAndSizeL();
    void UT_CMceComDisplaySink_MccTypeL();
    void UT_CMceComDisplaySink_InitParamLL();
    void UT_CMceComDisplaySink_DoInitParamLL();
    void UT_CMceComDisplaySink_EnableLL();
    void UT_CMceComDisplaySink_DisableLL();
    void UT_CMceComDisplaySink_PrepareLL();
    void UT_CMceComDisplaySink_SetViewFinderL();
    void UT_CMceComDisplaySink_MccParameterNameL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMDISPLAYSINK_H__

// End of file
