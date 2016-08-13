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





#ifndef MCETESTDEFS_H
#define MCETESTDEFS_H

#include <e32base.h>
#include <s32mem.h>

#include "mceevents.h"
class CMceComMediaSink;
class CMceComMediaSource;
class CMceComRtpSink;
class CMceComRtpSource;
class CMceComSpeakerSink;
class CMceComMicSource;

const TUint32 KMceTestSessionId1 = 543;
const TUint32 KMceTestTimeout = 64000;
const TUint32 KMce200OK = 200;


#include <ecam.h>
#include "mceclientserver.h"
class CSIPProfileRegistryObserverStub;

const TUint32 KMceTestAppId = 111;
const TUint32 KMceTestMiscId = 222;  
const TUint32 KMceTestFourCC = 333; 
const TUint KMceTestFrameSize = 20;

const TUint KMceTestBitrate = 777;
const TUint8 KMceTestPayloadType = 100;
const TUint32 KMceTestCodecMode = 999;
const TUint KMceTestAllowedBitrates = 123;
const TInt32 KMceTestPriority = 40;
const TInt32 KMceTestPriorityPreference = 50;
const TInt32 KMceTestKeepAliveTimer = 180;
const TInt32 KMceTestKeepAlivePayloadType = 127;
const TBool KMceTestEnabledFalse = EFalse;
const TBool KMceTestEnabledTrue = ETrue;
const TUint KMceTestSourceType = 15;
const TUint KMceTestSinkType = 15;
const TUint KRedCount = 15;

const TInt KMceTestInitialCameraIndex = 0;
const TInt KMceTestInitialZoomFactor = 1;
const TInt KMceTestInitialDigitalZoomFactor = 1;
const TInt KMceTestInitialContrast = 0;
const TInt KMceTestInitialBrightness = 0;
const CCamera::TExposure KMceTestInitialExposure = CCamera::EExposureAuto;
const CCamera::TWhiteBalance KMceTestInitialWhiteBalance = CCamera::EWBAuto;

const TUint32 KMceTestSecureSessionId1 = 678;
const TUint32 KMceTestTimeout2 = 2000;
const TUint32 KMceTestMinSE = 1000;
const TUint32 KMceTestTimeoutNegative = - 500;
const TUint32 KMceTestTimeoutTooBig = KMaxTInt;
const TUint32 KMce202Accepted = 202;
const TUint32 KMce444NOK = 444;
const TUint32 KMceUpdateInterval = 1800;
const TInt KMceTestGain = 5;
const TInt KMceTestMaxGain = 100;
const TInt KMceTestCamerasAvailable = 2;
const TInt KMceTestZoomFactor = 2;
const TInt KMceTestDigitalZoomFactor = 3;
const TInt KMceTestContrast = 4;
const TInt KMceTestBrightness = 20;
const CCamera::TExposure KMceTestExposure = CCamera::EExposureAuto; 
const CCamera::TWhiteBalance KMceTestWhiteBalance = CCamera::EWBAuto;
const TInt KMceTestDisplaysAvailable = 2;
const TInt KMceTestDisplayRectTlX = 100;
const TInt KMceTestDisplayRectTlY = 110;
const TInt KMceTestDisplayRectBrX = 200;
const TInt KMceTestDisplayRectBrY = 210;
const TInt KMceTestDisplayPriority = 0;
const TInt8 KMceTestCameraInfoHWVersionMajor = 1;
const TInt8 KMceTestCameraInfoHWVersionMinor = 2;
const TInt16 KMceTestCameraInfoHWVersionBuild = 3;
const TInt8 KMceTestCameraInfoSWVersionMajor = 4;
const TInt8 KMceTestCameraInfoSWVersionMinor = 5;
const TInt16 KMceTestCameraInfoSWVersionBuild = 6;
const TCameraInfo::TCameraOrientation KMceTestCameraInfoOrientation = TCameraInfo::EOrientationUnknown;
const TUint32 KMceTestCameraInfoOptionsSupported =
                ( TCameraInfo::EViewFinderDirectSupported |
                  TCameraInfo::EViewFinderBitmapsSupported |
                  TCameraInfo::EImageCaptureSupported | 
                  TCameraInfo::EVideoCaptureSupported |
                  TCameraInfo::EViewFinderMirrorSupported | 
                  TCameraInfo::EContrastSupported | 
                  TCameraInfo::EBrightnessSupported |       
                  TCameraInfo::EViewFinderClippingSupported |
                  TCameraInfo::EImageClippingSupported |
                  TCameraInfo::EVideoClippingSupported );   
const TUint32 KMceTestCameraInfoFlashModesSupported = 0;
const TUint32 KMceTestCameraInfoExposureModesSupported = 
                ( CCamera::EExposureAuto | 
                  CCamera::EExposureNight );                
const TUint32 KMceTestCameraInfoWBModesSupported = 
                ( CCamera::EWBAuto |
                  CCamera::EWBDaylight );
const TInt KMceTestCameraInfoMinZoom = 1;
const TInt KMceTestCameraInfoMaxZoom = 4;
const TInt KMceTestCameraInfoMaxDigitalZoom = 20;
const TReal32 KMceTestCameraInfoMinZoomFactor = 0;
const TReal32 KMceTestCameraInfoMaxZoomFactor = 0;
const TReal32 KMceTestCameraInfoMaxDigitalZoomFactor = 1;
const TInt KMceTestCameraInfoNumImageSizesSupported = 2;
const TUint32 KMceTestCameraInfoImageFormatsSupported = CCamera::EFormatJpeg;
const TInt KMceTestCameraInfoNumVideoFrameSizesSupported = 2;
const TInt KMceTestCameraInfoNumVideoFrameRatesSupported = 2;
const TInt KMceTestCameraInfoVideoFrameFormatsSupported = CCamera::EFormatUserDefined;
const TInt KMceTestCameraInfoMaxFramesPerBufferSupported = 10;
const TInt KMceTestCameraInfoMaxBuffersSupported = 2;             

const TInt KMceTestAudioElementCount = 3;
const TInt KMceTestVideoElementCount = 2; 
const TInt64 KMceTestDuration = 50000;
const TInt64 KMceTestPosition = 32000;
           
const TUint32 KMceTestWrongId = KMceTestSessionId1 + 1;
const TInt KLoops = 10;
_LIT8( KMceMethod1, "METHOD1" );
_LIT8( KMceMethod2, "METHOD2" );
_LIT8( KMceAttr1, "a= test attr 1" );
_LIT8( KMceAttr2, "a= test attr 1" );
_LIT8( KMceReason, "OK");
_LIT8( KMceReason2, "NOK");
_LIT8( KMceEventHeader, "TestEvent");
_LIT8( KMceTestFailContext, "context" );
_LIT16( KMceTestAudioFileName, "TestFile" );
_LIT16( KMceTestVideoFileName, "VideoFile" );
_LIT( KMceTestAVFileName, "AVFile" );
_LIT16( KMceTestAVFileName16, "AVFile" );
_LIT8( KMceTestAudioCodec, "AMR");
_LIT8( KMceTestVideoCodec, "H263" );
_LIT8( KMceTestKeepAliveData, "keep alive" );


_LIT8( KMceOriginator, "ORIGINATOR");
_LIT8( KMceRecipient, "RECIPIENT");
_LIT8( KMceOriginator1, "new ORIGINATOR");
_LIT8( KMceRecipient1, "new RECIPIENT");
_LIT8( KMceReferTo, "REFERTO");
_LIT8( KMceMessageBody, "MESSAGE: this is your body");
_LIT8( KMceContentType, "XML");
_LIT8( KMceHeader1, "Header1: value1");
_LIT8( KMceHeader2, "Header2: value2");
_LIT8( KMceMedialine1, "octet-align=1");
_LIT8( KMceMedialine2, "AS:64");
_LIT8( KMceFCMessage, "Floor control message");



class CMceMediaManagerStub : public CBase
    {
public:

    inline CMceMediaManagerStub()
        : iCallback( 0 )
        {
        }
    inline ~CMceMediaManagerStub()
        {
        }
        
    void PauseL( CMceComMediaSink& aSink )
        {
        iCallback = 1;
        iSink = NULL;
        iSource = NULL;
        iSink = &aSink;
        }
        
    void PauseL( CMceComMediaSource& aSource )
        {
        iCallback = 2;
        iSink = NULL;
        iSource = NULL;
        iSource = &aSource;
        }
        
    void ResumeL( CMceComMediaSink& aSink )
        {
        iCallback = 3;
        iSink = NULL;
        iSource = NULL;
        iSink = &aSink;
        }
        
    void ResumeL( CMceComMediaSource& aSource )
        {
        iCallback = 4;
        iSink = NULL;
        iSource = NULL;
        iSource = &aSource;
        }

    void SendSRL( CMceComMediaSink& aSink )
        {
        iCallback = 5;
        iSink = &aSink;
        iSource = NULL;
        iSource = NULL;
        }
        
    void SendRRL( CMceComMediaSink& aSink )
        {
        iCallback = 6;
        iSink = &aSink;
        iSource = NULL;
        iSource = NULL;
        }
        
    CMceComMediaSink* iSink;
    CMceComMediaSource* iSource;
    TInt iCallback;
    
            
    };


class TMceComEventHandlerStub : public MMceEventHandler
    {
public:

    inline TMceComEventHandlerStub( CMceMediaManagerStub& aManager )
       : iManager( aManager )
        {
        }
    
    inline TInt HandleL( CMceComMediaSink& aTarget, TMceComEvent& aEvent )
        {
        TInt status = KMceEventConsumed;
        switch( aEvent.Action() )
            {
            case EMceItcEnable:
                {
                iManager.ResumeL( aTarget );
                break;
                }
            case EMceItcDisable:
                {
                iManager.PauseL( aTarget );
                break;
                }
            default:
                {
                status = KMceEventNotConsumed;
                }
            }
        return status;            
        }
    
    inline TInt HandleL( CMceComMediaSource& aTarget, TMceComEvent& aEvent )
        {
        TInt status = KMceEventConsumed;
        switch( aEvent.Action() )
            {
            case EMceItcEnable:
                {
                iManager.ResumeL( aTarget );
                break;
                }
            case EMceItcDisable:
                {
                iManager.PauseL( aTarget );
                break;
                }
            default:
                {
                status = KMceEventNotConsumed;
                }
            }
        return status;            
        }
    
    inline TInt HandleL( CMceComRtpSink& aTarget, TMceComEvent& aEvent )
        {
        TInt status = KMceEventConsumed;
        switch( aEvent.Action() )
            {
            case EMceItcSendRR:
                {
                iManager.SendRRL( (CMceComMediaSink&) aTarget );
                break;
                }
            case EMceItcSendSR:
                {
                iManager.SendSRL( (CMceComMediaSink&) aTarget );
                break;
                }
            default:
                {
                status = KMceEventNotConsumed;
                }
            }
        return status;
        }
    
    inline TInt HandleL( CMceComRtpSource& /*aTarget*/, TMceComEvent& /*aEvent*/ )
        {
        TInt status = KMceEventConsumed;
        return status;
        }
    
    inline TInt HandleL( CMceComSpeakerSink& /*aTarget*/, TMceComEvent& /*aEvent*/ )
        {
        TInt status = KMceEventConsumed;
        return status;
        }

    inline TInt HandleL( CMceComMicSource& /*aTarget*/, TMceComEvent& /*aEvent*/ )
        {
        TInt status = KMceEventConsumed;
        return status;
        }

    inline TInt HandleL( CMceComDisplaySink& /*aTarget*/, TMceComEvent& /*aEvent*/ )
        {
        TInt status = KMceEventConsumed;
        return status;
        }

    inline TInt HandleL( CMceComCameraSource& /*aTarget*/, TMceComEvent& /*aEvent*/ )
        {
        TInt status = KMceEventConsumed;
        return status;
        }

    inline TInt HandleL( CMceComFileSource& /*aTarget*/, TMceComEvent& /*aEvent*/ )
        {
        TInt status = KMceEventConsumed;
        return status;
        }

    inline TInt HandleL( CMceComFileSink& /*aTarget*/, TMceComEvent& /*aEvent*/ )
        {
        TInt status = KMceEventConsumed;
        return status;
        }

    
    
public://data
        
    CMceMediaManagerStub& iManager;
    
        };
    
    
//#define MCE_UNIT_TEST_DEFS



#endif // MCETESTDEFS_H

// End of File
