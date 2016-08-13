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


#ifndef __MCE_FILESINK_TEST_H__
#define __MCE_FILESINK_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceManager;
class CMceFileSink;
class CMCEThreadLocalStorage;
class CMceComFileSink;
class CMceOutSession;
class CSIPProfile;

class CMceFileSinkTest: public CEUnitTestSuiteClass
	{
public:

    inline CMceFileSinkTest()  {}
    inline ~CMceFileSinkTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void ConstructionTestL();
    void EnableTestL();
    void DisableTestL();
    void InternalizeTestL();
    void ExternalizeTestL();
    
    
private://data

    TUid iUid;
    CMCEThreadLocalStorage* iStorage;
    CMceManager* iManager;
    CMceFileSink* iFileSink;
    CMceComFileSink* iFileFlatData;
    CMceFileSink* iFileWithoutManager;
    
    EUNIT_DECLARE_TEST_TABLE;
   	
};

#endif // __MCE_FILESINK_TEST_H__
