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


#ifndef __MCE_VIDEOSTREAM_TEST_H__
#define __MCE_VIDEOSTREAM_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceVideoStream;

class CMceVideoStreamTest: public CEUnitTestSuiteClass
	{
public:

    inline CMceVideoStreamTest()  {}
    inline ~CMceVideoStreamTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void ConstructionTestL();
    
    
private://data

    CMceVideoStream* iVideoStream;   	
    
    EUNIT_DECLARE_TEST_TABLE;
};

#endif // __MCE_VIDEOSTREAM_TEST_H__
