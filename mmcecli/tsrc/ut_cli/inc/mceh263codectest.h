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


#ifndef __MCE_H263CODEC_TEST_H__
#define __MCE_H263CODEC_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceH263Codec;

class CMceH263CodecTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceH263CodecTest()  {}
    inline ~CMceH263CodecTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void SettersTestL();
    void CompareSdpIndexTestL();
    void CloneTestL();
    void InternalizeTestL();
    void ExternalizeTestL();
    void SetAllowBitRatesTestL();
    
private://data

	CMceH263Codec* iH263;
	
	EUNIT_DECLARE_TEST_TABLE;
	
};

#endif // __MCE_H263CODEC_TEST_H__
