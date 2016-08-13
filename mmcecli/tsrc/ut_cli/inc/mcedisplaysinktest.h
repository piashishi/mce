/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __MCE_DISPLAYSINK_TEST_H__
#define __MCE_DISPLAYSINK_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceManager;
class CMceDisplaySink;
class CMCEThreadLocalStorage;
class CMceComDisplaySink;
class CMceOutSession;
class CSIPProfile;

class CMceDisplaySinkTest: public CEUnitTestSuiteClass
	{
public:

    inline CMceDisplaySinkTest()  {}
    inline ~CMceDisplaySinkTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void ConstructionTestL();
    void EnableTestL();
    void DisableTestL();
    void DisplaysAvailableTestL();
    void SetDisplayIndexTestL();
    void SetDisplayTestL();
    void SetDisplayRectTestL();
    void DisplayRectTestL();
    void SetPriorityTestL();
    void PriorityTestL();
    void InternalizeTestL();
    void ExternalizeTestL();
    void GetITCValueTestL();
    void SetITCValueTestL();

private: // Helper function    
    
    CMceOutSession* CreateDisplaySessionLC( CSIPProfile& aProfile ); // Transfers ownership 
      
    
private://data

    TUid iUid;
    CMCEThreadLocalStorage* iStorage;
    CMceManager* iManager;
    CMceDisplaySink* iDisplay;
    CMceComDisplaySink* iDisplayFlatData;
    CMceDisplaySink* iDisplayWithoutManager;
    
    EUNIT_DECLARE_TEST_TABLE;
   	
};

#endif // __MCE_DISPLAYSINK_TEST_H__
