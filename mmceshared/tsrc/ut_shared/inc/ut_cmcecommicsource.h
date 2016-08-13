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




#ifndef __UT_CMCECOMMICSOURCE_H__
#define __UT_CMCECOMMICSOURCE_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComMicSource;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComMicSource : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComMicSource* NewL();
    static UT_CMceComMicSource* NewLC();
    ~UT_CMceComMicSource();

private:    // Constructors and destructors

    UT_CMceComMicSource();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComMicSource_InternalizeFlatLL();
    void UT_CMceComMicSource_ExternalizeFlatLL();
    void UT_CMceComMicSource_EventReceivedLL();
    void UT_CMceComMicSource_UpdateLL();
    void UT_CMceComMicSource_CloneLL();
    void UT_CMceComMicSource_ReusableL();
    void UT_CMceComMicSource_MccTypeL();
    void UT_CMceComMicSource_PrepareLL();


private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMMICSOURCE_H__

// End of file
