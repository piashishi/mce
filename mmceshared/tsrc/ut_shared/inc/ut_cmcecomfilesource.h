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




#ifndef __UT_CMCECOMFILESOURCE_H__
#define __UT_CMCECOMFILESOURCE_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComFileSource;
class CMceMediaManager;
class CMceComSession;
class CMceMediaManagerStub;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComFileSource : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComFileSource* NewL();
    static UT_CMceComFileSource* NewLC();
    ~UT_CMceComFileSource();

private:    // Constructors and destructors

    UT_CMceComFileSource();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComFileSource_InternalizeFlatLL();
    void UT_CMceComFileSource_ExternalizeFlatLL();
    void UT_CMceComFileSource_EventReceivedLL();
    void UT_CMceComFileSource_CloneLL();
    void UT_CMceComFileSource_UpdateLL();
    void UT_CMceComFileSource_MccTypeL();
    void UT_CMceComFileSource_InitParamLL();
    void UT_CMceComFileSource_InitializedLL();


private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    CMceComFileSource* iSource;
    CMceComSession* iSession;
    CMceMediaManagerStub* iManagerStub;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMFILESOURCE_H__

// End of file
