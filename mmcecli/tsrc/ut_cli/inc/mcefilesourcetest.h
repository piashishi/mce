/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __MCE_FILESOURCE_TEST_H__
#define __MCE_FILESOURCE_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceManager;
class CMceFileSource;
class CMCEThreadLocalStorage;
class CMceComFileSource;
class CMceOutSession;
class CSIPProfile;

class CMceFileSourceTest: public CEUnitTestSuiteClass
	{
public:

    inline CMceFileSourceTest()  {}
    inline ~CMceFileSourceTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void ConstructionTestL();
    void EnableTestL();
    void DisableTestL();
    void MediaElementCountTestL();
    void SetCurrentMediaElementTestL();
    void CurrentMediaElementTestL();
    void SetPositionTestL();
    void PositionTestL();
    void DurationTestL();
    void SetFastForwardTestL();
    void SetFastRewindTestL();
    void InternalizeTestL();
    void ExternalizeTestL();
    
private: // Helper function    
    
    CMceOutSession* CreateDisplaySessionLC( CSIPProfile& aProfile ); // Transfers ownership 
      
    
private://data

    TUid iUid;
    CMCEThreadLocalStorage* iStorage;
    CMceManager* iManager;
    CMceFileSource* iFileSource;
    CMceComFileSource* iFileFlatData;
    CMceFileSource* iFileWithoutManager;
    
    EUNIT_DECLARE_TEST_TABLE;
   	
};

#endif // __MCE_FILESOURCE_TEST_H__
