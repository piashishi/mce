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


#ifndef __MCE_AUDIOCODEC_TEST_H__
#define __MCE_AUDIOCODEC_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceAmrCodec;

class CMceAudioCodecTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceAudioCodecTest()  {}
    inline ~CMceAudioCodecTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void GettersTestL();
    void UpdatedTestL();
    void FactoryTestL();
    void CompareSdpIndexTestL();
    void ComparePreferencesTestL();
    void BaseFactoryTestL();
    void InitializeTestL();
    void InternalizeTestL();
    void ExternalizeTestL();
    void EventReceivedTestL();
    void SetStateLTestL();
    void SetStandByTimerLTestL();
    void SetMMFPriorityLTestL();
    void SetMMFPriorityPreferenceLTestL();
    void SetKeepAliveTimerLTestL();
    void SetKeepAlivePayloadTypeLTestL();
    void TypeTestL();
    void SetSdpNameLTestL();
    void SetPreferenceLTestL();
    void MMFPriorityTestL();
    void MMFPriorityPreferenceTestL();
    
private://data

	CMceAmrCodec* iAMR;
	
	EUNIT_DECLARE_TEST_TABLE;
	
};

#endif // __MCE_AUDIOCODEC_TEST_H__
