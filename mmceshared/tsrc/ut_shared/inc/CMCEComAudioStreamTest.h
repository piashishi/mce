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


#ifndef __MCE_COMAUDIOSTREAM_TEST_H__
#define __MCE_COMAUDIOSTREAM_TEST_H__

#include <cppunit/TestCase.h>
class CMceMediaManagerStub;
class CMceComSession;
class CMceComAudioStream;
class CMceComRtpSink;
class CMceComRtpSource;


class CMceComAudioStreamTest : public CTestCase
	{
public:

    inline CMceComAudioStreamTest()  {}
    inline ~CMceComAudioStreamTest() {}
	
    void setUpL();
    void tearDown();

    static MTest* suiteL();
	
public://tests

    void TestUseRtcpL();
    void TestEventReceivedL(); 

private://data
    
    CMceMediaManagerStub* iMediaManager;
    CMceComSession* iSession;
    
private://not owned
    
    CMceComAudioStream* iAudioIn;
    CMceComAudioStream* iAudioOut;
    CMceComRtpSink* iRtpSink;
    CMceComRtpSource* iRtpSource;
};

#endif // __MCE_COMAUDIOSTREAM_TEST_H__
