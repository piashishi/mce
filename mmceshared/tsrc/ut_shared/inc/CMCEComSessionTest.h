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


#ifndef __MCE_COMSESSION_TEST_H__
#define __MCE_COMSESSION_TEST_H__

#include <cppunit/TestCase.h>
#include "mceamrcodec.h"

class CMceComSession;
class CMceMediaManagerStub;
class CMceComAudioStream;
class CMceComAMRCodec;
class CMceComRtpSink;
class CMceComRtpSource;
class CMceComSpeakerSink;
class CMceComMicSource;
class CMceComVideoStream;
class CMceComH263Codec;
class CMceComDisplaySink;
class CMceComCameraSource;

const TInt KH263FormatModeNew( 20 );
const TInt KH263DefaultAllowedBitrate( 1 );

    
const TUint KMceMMTestAudioLocalPort = 5006;
const TUint KMceMMTestVideoLocalPort = 5008;
const TUint KMceMMTestAudioPayloadType = 96;
const TUint KMceMMTestVideoPayloadType = 97;
const TUint KMceMMTestVideoPayloadTypeExtra = 107;
const TUint KMceMMTestAudioSamplingFreq = 8000;
const TUint KMceMMTestVideoClockrate = 90000;
const TAmrCodecMode KMceMMTestAudioCodecMode = EMceBandwidthEfficient;
const TUint KMceMMTestVideoCodecMode = KH263FormatModeNew;
const TUint KMceMMTestAudioAllowedBitrates = KMceAllowedAmrNbBitrateAll;
const TUint KMceMMTestVideoAllowedBitrates = KH263DefaultAllowedBitrate;
const TUint KMceMMTestAudioBitrate = KMceAmrNbBitrate795;
const TUint KMceMMTestVideoBitrate = 64000;

const TUint KMceMMTestAudioPTime = 60;
const TUint KMceMMTestAudioMaxPTime = 120;
const TUint KMceMMTestDefaultBufferLength = 10;
const TUint KMceMMTestDefaultBufferThreshold = 5;


    
class CMceComSessionTest : public CTestCase
	{
public:

    inline CMceComSessionTest()  {}
    inline ~CMceComSessionTest() {}
	
    void setUpL();
    void tearDown();

    static MTest* suiteL();
	
public: //tests

    void TestUseRtcpL();
    void TestUpdate1L();
    void TestUpdate2L();                                   

private:

    CMceComSession* ClientSessionReceivedLC();
                               
    
private://data

    CMceMediaManagerStub* iMediaManager;

    CMceComSession* iSession;
    CMceComSession* iClientSession;

private://not owned
    
    CMceComAudioStream* iAudioIn;
    CMceComAMRCodec* iInCodec;
    CMceComAudioStream* iAudioOut;
    CMceComAMRCodec* iOutCodec;

    CMceComRtpSink* iRtpSink;
    CMceComRtpSource* iRtpSource;
    CMceComSpeakerSink* iSpeaker;
    CMceComMicSource* iMic;

    CMceComVideoStream* iVideoIn;
    CMceComH263Codec* iInVideoCodec;
    CMceComVideoStream* iVideoOut;
    CMceComH263Codec* iOutVideoCodec;

    CMceComDisplaySink* iDisplaySink;
    CMceComCameraSource* iCameraSource;	
	};

#endif // __MCE_COMSESSION_TEST_H__
