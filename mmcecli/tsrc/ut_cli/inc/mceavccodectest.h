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


#ifndef __MCE_AVC_TEST_H__
#define __MCE_AVC_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceAvcCodec;

class CMceAvcCodecTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceAvcCodecTest()  {}
    inline ~CMceAvcCodecTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void SettersTestL();
    void CloneTestL();
    void InternalizeTestL();
    void ExternalizeTestL();
    void SetBitRatesTestL();
    void SetAllowBitRatesTestL();
    
private://data

	CMceAvcCodec* iCodec;
	
	EUNIT_DECLARE_TEST_TABLE;
	
};

#endif // __MCE_AVC_TEST_H__
