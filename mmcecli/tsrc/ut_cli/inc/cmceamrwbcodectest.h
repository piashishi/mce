/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef __CMCEAMRWBCODECTEST_H__
#define __CMCEAMRWBCODECTEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceAmrWbCodec;

class CMceAmrWbCodecTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceAmrWbCodecTest()  {}
    inline ~CMceAmrWbCodecTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public: // Tests

    void SettersTestL();
    void CloneTestL();
    void InternalizeTestL();
    void ExternalizeTestL();
    
private: // Data

	CMceAmrWbCodec* iCodec;
	
	EUNIT_DECLARE_TEST_TABLE;
	};

#endif // __CMCEAMRWBCODECTEST_H__
