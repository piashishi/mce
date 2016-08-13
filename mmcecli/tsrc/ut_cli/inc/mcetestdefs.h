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
#include <sipmanagedprofileregistry.h>
#include <ecam.h>
#include <digia/eunit/EUnitMacros.h>
#include "mceclientserver.h"
#include "mcetransactiondatacontainer.h"

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

const TUint32 KMceTestSessionId1 = 543;
const TUint32 KMceTestSecureSessionId1 = 678;
const TUint32 KMceTestTimeout = 2000;
const TUint32 KMceTestMinSE = 1000;
const TUint32 KMceTestTimeoutNegative = - 500;
const TUint32 KMceTestTimeoutTooBig = KMaxTInt;
const TUint32 KMce200OK = 200;
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
_LIT8( KMceOriginator, "ORIGINATOR");
_LIT8( KMceRecipient, "RECIPIENT");
_LIT8( KMceReferTo, "REFERTO");
_LIT8( KMceMessageBody, "MESSAGE: this is your body");
_LIT8( KMceContentType, "XML");
_LIT8( KMceHeader1, "Header1: value1");
_LIT8( KMceHeader2, "Header2: value2");
_LIT8( KMceMethod1, "METHOD1" );
_LIT8( KMceMethod2, "METHOD2" );
_LIT8( KMceAttr1, "a= test attr 1" );
_LIT8( KMceAttr2, "a= test attr 1" );
_LIT8( KMceMedialine1, "octet-align=1");
_LIT8( KMceMedialine2, "AS:64");
_LIT8( KMceReason, "OK");
_LIT8( KMceReason2, "NOK");
_LIT8( KMceMethodINFO, "INFO");
_LIT8( KMceFCMessage, "Floor control message");
_LIT8( KMceEventHeader, "TestEvent");
_LIT8( KMceTestFailContext, "context" );
_LIT16( KMceTestAudioFileName, "TestFile" );
_LIT16( KMceTestVideoFileName, "VideoFile" );
_LIT( KMceTestAVFileName, "AVFile" );
_LIT16( KMceTestAVFileName16, "AVFile" );
_LIT8( KMceTestAudioCodec, "AMR");
_LIT8( KMceTestVideoCodec, "H263" );
_LIT8( KMceTestKeepAliveData, "keep alive" );
_LIT8( KMceTestConfigKeyData, "CongigKey" );

_LIT8( KMceSubscriptionStateHeader1, "Subscription-State: pending; expires=3599");
_LIT8( KMceSubscriptionStateHeader2, "Subscription-State: active; expires=2107");
_LIT8( KMceSubscriptionStateHeader3, "Subscription-State: terminated; reason=probation; retry-after=3600");
_LIT8( KMceSubscriptionStateHeader4, "Subscription-State: active; expires=300; reason=probation; retry-after=4000");
_LIT8( KMceSampleContent, "v=0\r\n\
o=usera 1234567890 1234567890 IN IP4 10.20.180.74\r\n\
s=-\r\n\
i=-\r\n\
c=IN IP4 10.20.180.74\r\n\
t=0 0\r\n\
m=video 5000 RTP/AVP 97\r\n\
a=sendrecv\r\n\
a=curr:qos local sendrecv\r\n\
a=curr:qos remote none\r\n\
a=des:qos mandatory local sendrecv\r\n\
a=des:qos mandatory remote sendrecv\r\n\
a=rtpmap:97 H263-2000/90000\r\n\
a=fmtp:97 profile=0;level=10\r\n");

#define MCE_EUNIT_TESTCASE( text, setupFunc, runFunc, teardownFunc ) \
__EUNIT_INTERNAL_TEST_DEFINITION( L##text L"::" L###runFunc, 0, setupFunc, runFunc, teardownFunc )

#ifndef MCE_UNIT_TEST_DEFS
#define MCE_UNIT_TEST_DEFS\
    friend class CMceManagerTest;\
    friend class CMceSessionTest;\
    friend class CMceInSessionTest;\
    friend class CMceOutSessionTest;\
    friend class CMceMediaStreamTest;\
    friend class CMceAudioStreamTest;\
    friend class CMceVideoStreamTest;\
    friend class CMceMediaSinkTest;\
    friend class CMceRtpSinkTest;\
    friend class CMceDisplaySinkTest;\
    friend class CMceMediaSourceTest;\
	friend class CMceRtpSourceTest;\
	friend class CMceCameraSourceTest;\
    friend class CMceSpeakerSinkTest;\
    friend class CMceFileSourceTest;\
    friend class CMceAudioCodecTest;\
    friend class CMceAmrCodecTest;\
	friend class CMceAmrWbCodecTest;\
    friend class CMceVideoCodecTest;\
    friend class CMceEventTest;\
    friend class CMceOutEventTest;\
    friend class CMceInEventTest;\
    friend class CMceReferTest;\
    friend class CMceOutReferTest;\
    friend class CMceInReferTest;\
    friend class CMceFcMsgExchangeTest;\
    friend class CMceStreamBundleTest;\
    friend class CMceFileSinkTest;\
    friend class CMceAvSinkTest;\
    friend class CMceH263CodecTest;\
    friend class CMceAvcCodecTest;\
    friend class CMceG711CodecTest;\
    friend class CMceSecureInSessionTest;\
    friend class CMceSecureOutSessionTest;
#endif    
    
#define MCE_RECEIVE( obj, result )\
    if ( obj )\
        {\
        MCE_COMPLETE( obj, result );\
        }

#define MCE_COMPLETE( obj, result )\
    if ( obj && obj->iSessionReceiver )\
        {\
        MCE_COMPLETE_AO( obj->iSessionReceiver, result );\
        }

#define MCE_EVE_RECEIVE( obj, result )\
    if ( obj )\
        {\
        MCE_EVE_COMPLETE( obj, result );\
        }

#define MCE_EVE_COMPLETE( obj, result )\
    if ( obj && obj->iEventReceiver )\
        {\
        MCE_COMPLETE_AO( obj->iEventReceiver, result );\
        }

#define MCE_SES_RECEIVE( obj, result )\
    if ( obj )\
        {\
        MCE_SES_COMPLETE( obj, result );\
        }

#define MCE_SES_COMPLETE( obj, result )\
    if ( obj && obj->iReceiver )\
        {\
        MCE_COMPLETE_AO( obj->iReceiver, result );\
        }

// Simulate active scheduler active object completion
#define MCE_COMPLETE_AO( ao, result ) \
    if ( ao->IsActive() )\
        { \
        ao->Cancel();\
        ao->iStatus = result;\
        TRAPD( runLErr, ao->RunL() );\
        if ( runLErr != KErrNone ) \
            { \
            User::LeaveIfError( ao->RunError(runLErr) ); \
            } \
        }

#define MCE_CALLBACK( session, mediaid, sinkid, sourceid, codecid, callback, state, type )\
    if ( session && session->iReceiver )\
        {\
        TRequestStatus& status = session->iReceiver->iStatus;\
        TPckgBuf<TMceIds>* ids = iStorage->GetIds( status );\
        (*ids)() = TMceIds();\
        (*ids)().iAppUID = session->Manager().AppUid().iUid;\
        (*ids)().iSessionID = session->Id();\
        (*ids)().iMediaID = mediaid;\
        (*ids)().iSinkID = sinkid;\
        (*ids)().iSourceID = sourceid;\
        (*ids)().iCodecID = codecid;\
        (*ids)().iCallbackID = callback;\
        (*ids)().iMsgType = type;\
        (*ids)().iState = state;\
        MCE_SES_RECEIVE( session, KErrNone );\
        }


#define MCE_SESSION_RECEIVE( session, callback, state, type )\
    MCE_CALLBACK( session, KMceMediaIdNotAssigned, KMceMediaIdNotAssigned,\
                  KMceMediaIdNotAssigned, KMceMediaIdNotAssigned, callback, state, type )


#define MCE_STREAM_STATECHANGE( session, media, state, type )\
    MCE_CALLBACK( session, media->Id(), KMceMediaIdNotAssigned,\
                  KMceMediaIdNotAssigned, KMceMediaIdNotAssigned, EMceItcStateChanged, state, type )


#define MCE_SINK_STATECHANGE( session, media, sink, state, type )\
    MCE_CALLBACK( session, media->Id(), sink->Id(),\
                  KMceMediaIdNotAssigned, KMceMediaIdNotAssigned, EMceItcStateChanged, state, type )

        
#define MCE_SOURCE_STATECHANGE( session, media, source, state, type )\
    MCE_CALLBACK( session, media->Id(), KMceMediaIdNotAssigned,\
                  source->Id(), KMceMediaIdNotAssigned, EMceItcStateChanged, state, type )

#define MCE_CODEC_CHANGE( session, media, codec )\
    MCE_CALLBACK( session, media->Id(), KMceMediaIdNotAssigned,\
                  KMceMediaIdNotAssigned, codec->Id(), EMceItcStateChanged, KMceNotAssigned, EMceItcMsgTypeCodec )


#define MCE_SESSION_STATECHANGE( session, state, type )\
    MCE_SESSION_RECEIVE( session, EMceItcStateChanged, state, type )

#define MCE_TEST_DELETE( obj )\
        MCE_SES_RECEIVE( obj, KErrCompletion );\
        delete obj;\
        obj = NULL

#define MCE_MAN_DELETE( obj )\
        MCE_RECEIVE( obj, KErrCompletion );\
        MCE_EVE_RECEIVE( obj, KErrCompletion );\
        delete obj;\
        obj = NULL

#define MCE_ESTABLISH_SESSION( session, sesObserver, sesId, detailed )\
    if ( session )\
        {\
        EUNIT_ASSERT( session->Id() != KMceNotAssigned );\
        if (!detailed)\
            {\
            session->EstablishL();\
            }\
        else\
            {\
            CDesC8ArrayFlat* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
            CleanupStack::PushL( headers );\
            headers->AppendL( KMceHeader1 );\
            headers->AppendL( KMceHeader2 );\
\
            HBufC8* contentType = KMceContentType().AllocLC();\
            HBufC8* body = KMceMessageBody().AllocLC();\
\
            session->EstablishL( KMceTestTimeout,\
                                     headers,\
                                     contentType,\
                                     body );\
\
            CleanupStack::Pop( body );\
            CleanupStack::Pop( contentType );\
            CleanupStack::Pop( headers );\
            }\
\
        EUNIT_ASSERT( session->State() == CMceSession::EOffering );\
        EUNIT_ASSERT( session->Id() == sesId );\
        EUNIT_ASSERT( sesObserver->iStateChangedCount == 0 );\
\
        MCE_SESSION_STATECHANGE( iOutSession, CMceSession::EProceeding, KMceNotAssigned );\
\
        EUNIT_ASSERT( session->State() == CMceSession::EProceeding );\
        EUNIT_ASSERT( sesObserver->iStateChangedCount == 1 );\
\
        HBufC8* reason = KMceReason().AllocLC();\
        CDesC8Array* headers = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        CleanupStack::PushL( headers );\
        headers->AppendL( KMceHeader1 );\
        headers->AppendL( KMceHeader2 );\
        HBufC8* empty = KMceEmpty().AllocLC();\
\
        CMceMsgSIPReply* replyMsg = new (ELeave) CMceMsgSIPReply( *reason, KMce200OK, *headers, *empty );\
        CleanupStack::PushL( replyMsg );\
        replyMsg->EncodeL();\
\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = replyMsg->EncodeBuffer().Ptr(0).AllocL();\
        session->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        iStorage->iContent = KMceMessageBody().AllocL();\
        session->iReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();\
\
        CleanupStack::PopAndDestroy( replyMsg );\
        CleanupStack::PopAndDestroy( empty );\
        CleanupStack::PopAndDestroy( headers );\
        CleanupStack::PopAndDestroy( reason );\
\
        MCE_SESSION_STATECHANGE( session, CMceSession::EEstablished, EMceItcMsgTypeSIPReply );\
        EUNIT_ASSERT( session->State() == CMceSession::EEstablished );\
        EUNIT_ASSERT( sesObserver->iStateChangedCount == 2 );\
        EUNIT_ASSERT( sesObserver->iStatusCode == KMce200OK );\
        EUNIT_ASSERT( sesObserver->iReasonPhrase->Compare( KMceReason ) == 0 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaCount() == 2 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaPoint(0).Compare( KMceHeader1 ) == 0 );\
        EUNIT_ASSERT( sesObserver->iHeaders->MdcaPoint(1).Compare( KMceHeader2 ) == 0 );\
        EUNIT_ASSERT( sesObserver->iBody->Compare( KMceMessageBody ) == 0 );\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }


#define MCE_INCOMING_SESSION( manager, id )\
    if ( manager )\
        {\
\
        CMceComSession* inSession = NULL;\
        CMceComAudioStream* outStream = NULL;\
        CMceComAudioStream* inStream = NULL;\
        CMceMsgObject<CMceComSession>* msg = NULL;\
\
        inSession = CMceComSession::NewL( CMceComSession::EInSession );\
\
        inSession->iID = id;\
        inSession->iState = CMceSession::EIncoming;\
        inSession->iIsConnectionActive = ETrue;\
        CleanupStack::PushL( inSession );\
\
        delete inSession->iOriginator;\
        delete inSession->iRecipient;\
        delete inSession->iSIPContentType;\
        delete inSession->iSIPHeaders;\
        inSession->iOriginator = 0;\
        inSession->iRecipient = 0;\
        inSession->iSIPContentType = 0;\
        inSession->iSIPHeaders = 0;\
        inSession->iOriginator = KMceOriginator().AllocL();\
        inSession->iRecipient = KMceRecipient().AllocL();\
        inSession->iSIPContentType = KMceContentType().AllocL();\
        inSession->iSIPHeaders =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        inSession->iSIPHeaders->AppendL( KMceHeader1 );\
        inSession->iSIPHeaders->AppendL( KMceHeader2 );\
        inSession->iTimeout = KMceTestTimeout;\
        inSession->iMinSE = KMceTestMinSE;\
\
        outStream = CMceComAudioStream::NewLC();\
        inStream = CMceComAudioStream::NewLC();\
\
        TBuf8<KMceMaxSdpNameLength> codec1;\
        codec1.Append(_L8("AMR"));\
\
        outStream->AddSinkL( CMceComRtpSink::NewLC() );\
        CleanupStack::Pop();\
        inStream->SetSourceL( CMceComRtpSource::NewLC() );\
        CleanupStack::Pop();\
\
        delete inStream->iLocalMediaSDPLines;\
        inStream->iLocalMediaSDPLines = 0;\
        inStream->iLocalMediaSDPLines =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine1 );\
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine2 );\
\
        outStream->BindL( inStream );\
        CleanupStack::Pop( inStream );\
        inSession->AddStreamL( outStream );\
        CleanupStack::Pop( outStream );\
\
        msg = new (ELeave) CMceMsgObject<CMceComSession>( *inSession, EMceItcMsgTypeSession );\
        CleanupStack::PushL( msg );\
        msg->EncodeL();\
\
        iStorage->Reset();\
        manager->iSessionReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        manager->iSessionReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = msg->EncodeBuffer().Ptr(0).AllocL();\
        manager->iSessionReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        iStorage->iContent = KMceMessageBody().AllocL();\
        manager->iSessionReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();\
\
        CleanupStack::PopAndDestroy( msg );\
        CleanupStack::PopAndDestroy( inSession );\
\
        manager->iSessionReceiver->iIdsPckg().iAppUID = manager->AppUid().iUid;\
        manager->iSessionReceiver->iIdsPckg().iSessionID = KMceTestSessionId1;\
        manager->iSessionReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;\
        manager->iSessionReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeSession;\
\
        MCE_RECEIVE( manager, KErrNone );\
        iStorage->Reset();\
        manager->iSessionReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        manager->iSessionReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }

#define MCE_INCOMING_SECURE_SESSION( manager, id )\
    if ( manager )\
        {\
\
        CMceComSession* inSession = NULL;\
        CMceComAudioStream* outStream = NULL;\
        CMceComAudioStream* inStream = NULL;\
        CMceMsgObject<CMceComSession>* msg = NULL;\
\
        inSession = CMceComSession::NewL( CMceComSession::EInSession );\
\
        inSession->iID = id;\
        inSession->iState = CMceSession::EIncoming;\
        inSession->iIsConnectionActive = ETrue;\
        CleanupStack::PushL( inSession );\
\
        delete inSession->iOriginator;\
        delete inSession->iRecipient;\
        delete inSession->iSIPContentType;\
        delete inSession->iSIPHeaders;\
        inSession->iOriginator = 0;\
        inSession->iRecipient = 0;\
        inSession->iSIPContentType = 0;\
        inSession->iSIPHeaders = 0;\
        inSession->iOriginator = KMceOriginator().AllocL();\
        inSession->iRecipient = KMceRecipient().AllocL();\
        inSession->iSIPContentType = KMceContentType().AllocL();\
        inSession->iSIPHeaders =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        inSession->iSIPHeaders->AppendL( KMceHeader1 );\
        inSession->iSIPHeaders->AppendL( KMceHeader2 );\
        inSession->iTimeout = KMceTestTimeout;\
        inSession->iMinSE = KMceTestMinSE;\
        inSession->iIsSecureSession = ETrue;\
        outStream = CMceComAudioStream::NewLC();\
        inStream = CMceComAudioStream::NewLC();\
\
        TBuf8<KMceMaxSdpNameLength> codec1;\
        codec1.Append(_L8("AMR"));\
\
        outStream->AddSinkL( CMceComRtpSink::NewLC() );\
        CleanupStack::Pop();\
        inStream->SetSourceL( CMceComRtpSource::NewLC() );\
        CleanupStack::Pop();\
\
        delete inStream->iLocalMediaSDPLines;\
        inStream->iLocalMediaSDPLines = 0;\
        inStream->iLocalMediaSDPLines =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine1 );\
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine2 );\
\
        outStream->BindL( inStream );\
        CleanupStack::Pop( inStream );\
        inSession->AddStreamL( outStream );\
        CleanupStack::Pop( outStream );\
\
        msg = new (ELeave) CMceMsgObject<CMceComSession>( *inSession, EMceItcMsgTypeSession );\
        CleanupStack::PushL( msg );\
        msg->EncodeL();\
\
        iStorage->Reset();\
        manager->iSessionReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        manager->iSessionReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = msg->EncodeBuffer().Ptr(0).AllocL();\
        manager->iSessionReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        iStorage->iContent = KMceMessageBody().AllocL();\
        manager->iSessionReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();\
\
        CleanupStack::PopAndDestroy( msg );\
        CleanupStack::PopAndDestroy( inSession );\
\
        manager->iSessionReceiver->iIdsPckg().iAppUID = manager->AppUid().iUid;\
        manager->iSessionReceiver->iIdsPckg().iSessionID = KMceTestSessionId1;\
        manager->iSessionReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;\
        manager->iSessionReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeSession;\
		manager->iSessionReceiver->iIdsPckg().iSecureFlag = ETrue;\
\
        MCE_RECEIVE( manager, KErrNone );\
        iStorage->Reset();\
        manager->iSessionReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        manager->iSessionReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }

#define MCE_CREATE_PROFILE\
	CSIPProfileRegistryObserverStub* profileRegistryObserver =\
		new(ELeave)CSIPProfileRegistryObserverStub;\
	CleanupStack::PushL( profileRegistryObserver );\
    CSIPManagedProfileRegistry* managedProfileRegistry =\
    	CSIPManagedProfileRegistry::NewL( *profileRegistryObserver );\
 	CleanupStack::PushL( managedProfileRegistry );\
\
    TSIPProfileTypeInfo typeInfo;\
    typeInfo.iSIPProfileClass = TSIPProfileTypeInfo::EInternet;\
    typeInfo.iSIPProfileName = _L8("IETF");\
\
    CSIPManagedProfile* profile = managedProfileRegistry->CreateL( typeInfo );\
    CleanupStack::PushL( profile );\
\
	// AutoRegistration\
	User::LeaveIfError( profile->SetParameter( KSIPAutoRegistration, EFalse ) )
	
#define MCE_DELETE_PROFILE\
    CleanupStack::PopAndDestroy( profile );\
    CleanupStack::PopAndDestroy( managedProfileRegistry );\
  	CleanupStack::PopAndDestroy( profileRegistryObserver )

#define MCE_INCOMING_REFER( manager )\
    if ( manager )\
        {\
\
		CMceMsgSIPEvent* msg = new (ELeave) CMceMsgSIPEvent();\
        CleanupStack::PushL( msg );\
        msg->iId = 757584;\
        msg->iDialogId = 785876;\
        msg->iEventType = EMceItcEventTypeRefer;\
        msg->iEventHeader = _L8("WHAT").AllocL();\
        msg->iRecipient = _L8("WHAT").AllocL();\
        msg->iOriginator = _L8("WHAT").AllocL();\
        msg->EncodeL();\
\
        iStorage->Reset();\
        manager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        manager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = msg->EncodeBuffer().Ptr(0).AllocL();\
        manager->iEventReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        iStorage->iContent = KMceMessageBody().AllocL();\
        manager->iEventReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();\
\
        CleanupStack::PopAndDestroy( msg );\
\
        manager->iEventReceiver->iIdsPckg().iAppUID = manager->AppUid().iUid;\
        manager->iEventReceiver->iIdsPckg().iSessionID = KMceTestSessionId1;\
        manager->iEventReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;\
        manager->iEventReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeEvent;\
\
        MCE_EVE_RECEIVE( manager, KErrNone );\
        iStorage->Reset();\
        manager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        manager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
        }

// NOTE! Cleanupstack is used internally for headers, contentType, content and contentHeaders
#define MCE_INCOMING_UPDATE( session, headers, contentType, content, contentHeaders )\
    if ( session )\
        {\
        CleanupStack::PushL( content );\
        CleanupStack::PushL( headers );\
        CleanupStack::PushL( contentType );\
        CleanupStack::PushL( contentHeaders );\
        CMceComSession* inSession = NULL;\
        CMceComAudioStream* outStream = NULL;\
        CMceComAudioStream* inStream = NULL;\
        CMceMsgObject<CMceComSession>* msg = NULL;\
\
        inSession = CMceComSession::NewL( CMceComSession::EInSession );\
\
        inSession->iID = session->Id();\
        inSession->iState = CMceSession::EIncoming;\
        inSession->iIsConnectionActive = ETrue;\
        CleanupStack::PushL( inSession );\
\
        delete inSession->iOriginator;\
        delete inSession->iRecipient;\
        delete inSession->iSIPContentType;\
        delete inSession->iSIPHeaders;\
        delete inSession->iSIPContentHeaders;\
        inSession->iOriginator = 0;\
        inSession->iRecipient = 0;\
        inSession->iSIPContentType = 0;\
        inSession->iSIPHeaders = 0;\
        inSession->iSIPContentHeaders = 0;\
        inSession->iOriginator = KMceOriginator().AllocL();\
        inSession->iRecipient = KMceRecipient().AllocL();\
        CleanupStack::Pop( inSession );\
        inSession->iSIPContentType = contentType;\
        inSession->iSIPHeaders = headers;\
        inSession->iSIPContentHeaders = contentHeaders;\
        CleanupStack::Pop( contentHeaders );\
        CleanupStack::Pop( contentType );\
        CleanupStack::Pop( headers );\
        CleanupStack::PushL( inSession );\
\
        outStream = CMceComAudioStream::NewLC();\
        inStream = CMceComAudioStream::NewLC();\
\
        TBuf8<KMceMaxSdpNameLength> codec1;\
        codec1.Append(_L8("AMR"));\
\
        outStream->AddSinkL( CMceComRtpSink::NewLC() );\
        CleanupStack::Pop();\
        inStream->SetSourceL( CMceComRtpSource::NewLC() );\
        CleanupStack::Pop();\
\
        delete inStream->iLocalMediaSDPLines;\
        inStream->iLocalMediaSDPLines = 0;\
        inStream->iLocalMediaSDPLines =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine1 );\
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine2 );\
\
        outStream->BindL( inStream );\
        CleanupStack::Pop( inStream );\
        inSession->AddStreamL( outStream );\
        CleanupStack::Pop( outStream );\
\
        msg = new (ELeave) CMceMsgObject<CMceComSession>( *inSession, EMceItcMsgTypeSession );\
        CleanupStack::PushL( msg );\
        msg->EncodeL();\
\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = msg->EncodeBuffer().Ptr(0).AllocL();\
        session->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        CleanupStack::PopAndDestroy( msg );\
        CleanupStack::PopAndDestroy( inSession );\
\
        iStorage->iContent = content;\
        CleanupStack::Pop( content );\
        session->iReceiver->iSizesPckg().iContentBufSize = content ? iStorage->iContent->Length() : KErrNotFound;\
\
\
        session->iReceiver->iIdsPckg().iAppUID = session->Manager().AppUid().iUid;\
        session->iReceiver->iIdsPckg().iSessionID = session->Id();\
 \
        MCE_SESSION_RECEIVE( session, EMceItcIncomingUpdate, CMceSession::EIncoming, EMceItcMsgTypeSession );\
        iStorage->Reset();\
     }
     
#define MCE_INCOMING_UPDATE2( session )\
    if ( session )\
        {\
        CMceComSession* inSession = NULL;\
        CMceComAudioStream* outStream = NULL;\
        CMceComAudioStream* inStream = NULL;\
        CMceMsgObject<CMceComSession>* msg = NULL;\
\
        inSession = CMceComSession::NewL( CMceComSession::EInSession );\
\
        inSession->iID = session->Id();\
        inSession->iState = CMceSession::EIncoming;\
        inSession->iIsConnectionActive = ETrue;\
        CleanupStack::PushL( inSession );\
\
        delete inSession->iOriginator;\
        delete inSession->iRecipient;\
        delete inSession->iSIPContentType;\
        delete inSession->iSIPHeaders;\
        delete inSession->iSIPContentHeaders;\
        inSession->iOriginator = 0;\
        inSession->iRecipient = 0;\
        inSession->iSIPContentType = 0;\
        inSession->iSIPHeaders = 0;\
        inSession->iSIPContentHeaders = 0;\
        inSession->iOriginator = KMceOriginator().AllocL();\
        inSession->iRecipient = KMceRecipient().AllocL();\
        inSession->iSIPContentType = 0;\
        inSession->iSIPHeaders = 0;\
        inSession->iSIPContentHeaders = 0;\
\
        outStream = CMceComAudioStream::NewLC();\
        inStream = CMceComAudioStream::NewLC();\
\
        TBuf8<KMceMaxSdpNameLength> codec1;\
        codec1.Append(_L8("AMR"));\
\
        outStream->AddSinkL( CMceComRtpSink::NewLC() );\
        CleanupStack::Pop();\
        inStream->SetSourceL( CMceComRtpSource::NewLC() );\
        CleanupStack::Pop();\
\
        delete inStream->iLocalMediaSDPLines;\
        inStream->iLocalMediaSDPLines = 0;\
        inStream->iLocalMediaSDPLines =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );\
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine1 );\
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine2 );\
\
        outStream->BindL( inStream );\
        CleanupStack::Pop( inStream );\
        inSession->AddStreamL( outStream );\
        CleanupStack::Pop( outStream );\
\
        msg = new (ELeave) CMceMsgObject<CMceComSession>( *inSession, EMceItcMsgTypeSession );\
        CleanupStack::PushL( msg );\
        msg->EncodeL();\
\
        iStorage->Reset();\
        session->iReceiver->iSizesPckg().iContextBufSize = KErrNotFound;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
        iStorage->iContext = msg->EncodeBuffer().Ptr(0).AllocL();\
        session->iReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();\
\
        CleanupStack::PopAndDestroy( msg );\
        CleanupStack::PopAndDestroy( inSession );\
\
        iStorage->iContent = 0;\
        session->iReceiver->iSizesPckg().iContentBufSize = KErrNotFound;\
\
\
        session->iReceiver->iIdsPckg().iAppUID = session->Manager().AppUid().iUid;\
        session->iReceiver->iIdsPckg().iSessionID = session->Id();\
 \
        MCE_SESSION_RECEIVE( session, EMceItcIncomingUpdate, CMceSession::EIncoming, EMceItcMsgTypeSession );\
        iStorage->Reset();\
     }
#define MCE_TEST_HANDLE_ALLOC_FAILURE( error )\
    if ( error == KErrNoMemory )\
        {\
        User::Leave( error );\
        }
        
const TInt KMceMaxFixedArrayLength = 10;

class CMCEThreadLocalStorage : public CBase
    {
public:

    CMCEThreadLocalStorage();
    void Reset();
    ~CMCEThreadLocalStorage();
    
    void Register( TPckgBuf<TMceIds>* aIds, TRequestStatus& aStatus );
    TPckgBuf<TMceIds>* GetIds( TRequestStatus& aStatus );
    TRequestStatus* GetStatus( TPckgBuf<TMceIds>* aIds );
       
public:

    HBufC8* iContext;
    HBufC8* iContent;
    TInt iSessionId;
    TInt iStatus;
    TMceIds iIDS;
   
    TUint iBackupSessionState;
    TUint iBackupSessionType;
    class TRegistryEntry
        {
    public:

        inline TRegistryEntry()
            : iStatus( NULL ),
              iIDS( NULL )
            {
            }
    
        inline TRegistryEntry( TRequestStatus* aStatus, TPckgBuf<TMceIds>* aIDS )
            : iStatus( aStatus ),
              iIDS( aIDS )
            {
            }
            
        TRequestStatus* iStatus;
        TPckgBuf<TMceIds>* iIDS;
        
        };
        
    TFixedArray<TRegistryEntry,KMceMaxFixedArrayLength> iEntries;
            
    
    };


#endif // MCETESTDEFS_H

// End of File
