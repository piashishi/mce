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




#ifndef __UT_CMCECOMMEDIASOURCE_H__
#define __UT_CMCECOMMEDIASOURCE_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComMediaSource;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComMediaSource : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComMediaSource* NewL();
    static UT_CMceComMediaSource* NewLC();
    ~UT_CMceComMediaSource();

private:    // Constructors and destructors

    UT_CMceComMediaSource();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods

    void UT_CMceComMediaSource_InternalizeFlatLL();
    void UT_CMceComMediaSource_ExternalizeFlatLL();
    void UT_CMceComMediaSource_EventReceivedLL();
    void UT_CMceComMediaSource_UpdateLL();
    void UT_CMceComMediaSource_CloneLL();
    void UT_CMceComMediaSource_UseRTCPL();
    void UT_CMceComMediaSource_TypeL();
    void UT_CMceComMediaSource_FactoryL();
    void UT_CMceComMediaSource_MccTypeL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMMEDIASOURCE_H__

// End of file
