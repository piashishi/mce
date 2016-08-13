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




#ifndef __UT_CMCECOMFILESINK_H__
#define __UT_CMCECOMFILESINK_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComFileSink;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComFileSink : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComFileSink* NewL();
    static UT_CMceComFileSink* NewLC();
    ~UT_CMceComFileSink();

private:    // Constructors and destructors

    UT_CMceComFileSink();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComFileSink_InternalizeFlatLL();
    void UT_CMceComFileSink_ExternalizeFlatLL();
    void UT_CMceComFileSink_CloneLL();
    void UT_CMceComFileSink_UpdateLL();
    void UT_CMceComFileSink_MccTypeL();
    void UT_CMceComFileSink_InitParamLL();

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMFILESINK_H__

// End of file
