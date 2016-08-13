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




#ifndef __UT_CMCECOMCAMERASOURCE_H__
#define __UT_CMCECOMCAMERASOURCE_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComCameraSource;
class CMceMediaManager;
class CMceComSession;
class CMceMediaManagerStub;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComCameraSource : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComCameraSource* NewL();
    static UT_CMceComCameraSource* NewLC();
    ~UT_CMceComCameraSource();

private:    // Constructors and destructors

    UT_CMceComCameraSource();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods

    void UT_CMceComCameraSource_InternalizeFlatLL();
    void UT_CMceComCameraSource_ExternalizeFlatLL();
    void UT_CMceComCameraSource_EventReceivedLL();
    void UT_CMceComCameraSource_CloneLL();
    void UT_CMceComCameraSource_UpdateL();
    void UT_CMceComCameraSource_MccTypeL();
    void UT_CMceComCameraSource_InitParamLL();
    void UT_CMceComCameraSource_DoPreparedL();    

private:    // Data

	CMceMediaManager* iManager;
	CMceMediaManagerStub* iManagerStub;
	
    CMceServerStub* iServer;
    CMceComCameraSource* iSource;
    CMceComSession* iSession;
    
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMCAMERASOURCE_H__

// End of file
