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





#include "mce.h"
#include "mcestubs.h"
#include "mceclientserver.h"
#include "mceserverstarter.h"
#include "mceclient.pan"
#include "mcecomamrcodec.h"
#include "mcecomh263codec.h"
#include "mceaudiostream.h"
#include "mcevideostream.h"
#include "mcecomfilesource.h"
#include "mceserial.h"
#include "mcedefs.h"
#include "mcecomcamerasource.h"

#define RETURN_IF_ERROR(err) {TInt _err=err; if(_err!=KErrNone) {return _err;}}

#define RMCEStub RMce


// -----------------------------------------------------------------------------
// RMCEStub::RMCEStub
// -----------------------------------------------------------------------------
//
RMCEStub::RMCEStub() 
 : RSessionBase (),
   iConnected (EFalse)
	{
	
	}

// -----------------------------------------------------------------------------
// RMCEStub::Version
// -----------------------------------------------------------------------------
//
TVersion RMCEStub::Version() const
	{
    TVersion version (KMceServerMajorVersionNumber,
                      KMceServerMinorVersionNumber,
                      KMceServerBuildVersionNumber);
    return version;
	}

// -----------------------------------------------------------------------------
// RMCEStub::Connect
// -----------------------------------------------------------------------------
//
TInt RMCEStub::Connect (const TUid& /*aUid*/)
	{

    iConnected = ETrue;
    return KErrNone;
	}

// -----------------------------------------------------------------------------
// RMCEStub::Connect
// -----------------------------------------------------------------------------
//
TInt RMCEStub::Connect ()
	{

    iConnected = ETrue;
    return KErrNone;
	}

// -----------------------------------------------------------------------------
// RMCEStub::Close
// -----------------------------------------------------------------------------
//
void RMCEStub::Close()
	{
    iConnected = EFalse;
    RHandleBase::Close();
	}

// -----------------------------------------------------------------------------
// RMCEStub::Send
// From MMceItc
// -----------------------------------------------------------------------------
//
TInt RMCEStub::Send (TMceItcFunctions aFunction, TIpcArgs& aArgs )
	{
	__ASSERT_ALWAYS (iConnected, Panic( KErrCouldNotConnect ));
    
    CMCEThreadLocalStorage* storage = static_cast<CMCEThreadLocalStorage*> ( Dll::Tls() );
    if ( storage )
        {

        TPckgBuf<TMceIds>* idsPtr = (TPckgBuf<TMceIds>*)aArgs.iArgs[ EMceItcArgIds ];
        storage->iIDS = (*idsPtr)();
        
        (*idsPtr)().iStatus = storage->iStatus;
        
        if ( aFunction == EMceItcEstablishSession || aFunction == EMceItcUpdate )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            storage->iContext = context->AllocL();
            TDes8* content = (TDes8*)aArgs.iArgs[ EMceItcArgMessageContent ];
            if ( content )
                {
                storage->iContent = content->AllocL();
                }
            }

        if ( aFunction == EMceItcRequestSend )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            storage->iContext = context->AllocL();
            TDes8* content = (TDes8*)aArgs.iArgs[ EMceItcArgMessageContent ];
            if ( content )
                {
                storage->iContent = content->AllocL();
                }
			 (*idsPtr)().iTransactionID = 5000;
            }

		if ( aFunction == EMceItcReplySend )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            storage->iContext = context->AllocL();
            TDes8* content = (TDes8*)aArgs.iArgs[ EMceItcArgMessageContent ];
            if ( content )
                {
                storage->iContent = content->AllocL();
                }
            }

        if ( aFunction == EMceItcGetSupportedAudioCodecs )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            
            TBuf8<KMceMaxSdpNameLength> codecStr1;
            codecStr1.Append(_L8("AMR"));    
            
            TBuf8<KMceMaxSdpNameLength> codecStr2;
            codecStr2.Append(_L8("PCMU"));
            
            CMceComAMRCodec* codec1 = CMceComAMRCodec::NewL( codecStr1 );
            CleanupStack::PushL( codec1 );
            CMceComAMRCodec* codec2 = CMceComAMRCodec::NewL( codecStr2 );
            CleanupStack::PushL( codec2 );
            
            CMceMsgObject<CMceComAudioCodec>* msgCodec1 = new (ELeave) CMceMsgObject<CMceComAudioCodec>( *codec1, EMceItcMsgTypeCodec );
            CleanupStack::PushL( msgCodec1 );
            msgCodec1->EncodeL();
            
            CMceMsgObject<CMceComAudioCodec>* msgCodec2 = new (ELeave) CMceMsgObject<CMceComAudioCodec>( *codec2, EMceItcMsgTypeCodec );
            CleanupStack::PushL( msgCodec2 );
            msgCodec2->EncodeL();
            
            CDesC8ArrayFlat* codecs = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
            CleanupStack::PushL( codecs );
            
            codecs->AppendL( msgCodec1->EncodeBuffer().Ptr( 0 ) );
            codecs->AppendL( msgCodec2->EncodeBuffer().Ptr( 0 ) );

            CMceMsgTextArray* msgCodecs = new (ELeave) CMceMsgTextArray( *codecs );
            CleanupStack::PushL( msgCodecs );
            msgCodecs->EncodeL();
            
            context->Copy( msgCodecs->EncodeBuffer().Ptr( 0 ) );
            
            CleanupStack::PopAndDestroy( msgCodecs );
            CleanupStack::PopAndDestroy( codecs );
            CleanupStack::PopAndDestroy( msgCodec2 );
            CleanupStack::PopAndDestroy( msgCodec1 );
            CleanupStack::PopAndDestroy( codec2 );
            CleanupStack::PopAndDestroy( codec1 );
            }

        else if ( aFunction == EMceItcGetSupportedVideoCodecs )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            
            TBuf8<KMceMaxSdpNameLength> codecStr1;
            codecStr1.Append(_L8("H263-2000"));    
            
            CMceComH263Codec* codec1 = CMceComH263Codec::NewL( codecStr1 );
            CleanupStack::PushL( codec1 );
            
            CMceMsgObject<CMceComVideoCodec>* msgCodec1 = new (ELeave) CMceMsgObject<CMceComVideoCodec>( *codec1, EMceItcMsgTypeCodec );
            CleanupStack::PushL( msgCodec1 );
            msgCodec1->EncodeL();
            
            CDesC8ArrayFlat* codecs = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
            CleanupStack::PushL( codecs );
            
            codecs->AppendL( msgCodec1->EncodeBuffer().Ptr( 0 ) );

            CMceMsgTextArray* msgCodecs = new (ELeave) CMceMsgTextArray( *codecs );
            CleanupStack::PushL( msgCodecs );
            msgCodecs->EncodeL();
            
            context->Copy( msgCodecs->EncodeBuffer().Ptr( 0 ) );
            
            CleanupStack::PopAndDestroy( msgCodecs );
            CleanupStack::PopAndDestroy( codecs );
            CleanupStack::PopAndDestroy( msgCodec1 );
            CleanupStack::PopAndDestroy( codec1 );
            }

        else if ( aFunction == EMceItcCreateSession )
            {
            storage->iSessionId++;
           
            (*idsPtr)().iSessionID = storage->iSessionId;
            if ( (*idsPtr)().iDialogID == KMceNotAssigned )
                {
                (*idsPtr)().iDialogID = storage->iSessionId;
                }
            }
        else if ( aFunction == EMceItcDeleteSession )
            {
            (*idsPtr)().iState = CMceSession::ETerminated;
            }
        else if ( aFunction == EMceItcEstablishSession )
            {
            (*idsPtr)().iState = CMceSession::EOffering;
            }
        else if ( aFunction == EMceItcTerminateSession )
            {
            (*idsPtr)().iState = CMceSession::ETerminating;
            }
        else if ( aFunction == EMceItcAcceptSession )
            {
            (*idsPtr)().iState = CMceSession::EAnswering;
            }
        else if ( aFunction == EMceItcRejectSession )
            {
            (*idsPtr)().iState = CMceSession::ETerminated;
            }
        else if ( aFunction == EMceItcUpdate )
            {
            (*idsPtr)().iState = CMceSession::EOffering;
            }
        else if ( aFunction == EMceItcCancel )
            {
            (*idsPtr)().iState = CMceSession::ECancelling;
            }
        else if ( aFunction == EMceItcEnable )
            {
            (*idsPtr)().iState = (TUint32)ETrue;
            }
        else if ( aFunction == EMceItcDisable )
            {
            (*idsPtr)().iState = (TUint32)EFalse;
            }
        else if ( aFunction == EMceItcRing )
            {
            (*idsPtr)().iState = CMceSession::EProceeding;
            }
        else if ( aFunction == EMceItcReferEvent )
            {
            (*idsPtr)().iState = CMceEvent::EPending;
            }
        else if ( aFunction == EMceItcNotify )
            {
            (*idsPtr)().iState = CMceEvent::EPending;
            }
        else if ( aFunction == EMceItcSubscribe )
            {
            (*idsPtr)().iState = CMceEvent::EPending;
            }
        else if ( aFunction == EMceItcSubscribeUpdate )
            {
            (*idsPtr)().iState = CMceEvent::EPending;
            }
        else if ( aFunction == EMceItcAcceptEvent )
            {
            (*idsPtr)().iState = CMceEvent::EPending;
            }
        else if ( aFunction == EMceItcRejectEvent )
            {
            (*idsPtr)().iState = CMceEvent::ETerminated;
            }
        else if ( aFunction == EMceItcTerminateEvent )
            {
            (*idsPtr)().iState = CMceEvent::EPending;
            }
        else if ( aFunction == EMceItcRespondEvent )
            {
            CMceMsgSIPReply* reply = new (ELeave) CMceMsgSIPReply();
            CleanupStack::PushL(reply);
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            reply->DecodeL(*context);
            reply->PushL();
            if (reply->iCode > 200 && reply->iCode < 300)
	            (*idsPtr)().iState = CMceEvent::EPending;
            else
	            (*idsPtr)().iState = CMceEvent::ETerminated;
            reply->Pop();
            delete reply->iContentType;
            delete reply->iReason;
            delete reply->iSIPHeaders;
            reply->iContentType = 0;
            reply->iReason = 0;
            reply->iSIPHeaders = 0;
            CleanupStack::PopAndDestroy(reply);
            }
        else if ( aFunction == EMceItcGetDefaultHeaders )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            
            CDesC8ArrayFlat* hdrs = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
            CleanupStack::PushL( hdrs );
            
            hdrs->AppendL( _L8("Hdr1: Header 1") );
            hdrs->AppendL( _L8("Hdr2: Header 2") );

            CMceMsgTextArray* msgHdrs = new (ELeave) CMceMsgTextArray( *hdrs );
            CleanupStack::PushL( msgHdrs );
            msgHdrs->EncodeL();
            
            context->Copy( msgHdrs->EncodeBuffer().Ptr( 0 ) );
            
            CleanupStack::PopAndDestroy( msgHdrs );
            CleanupStack::PopAndDestroy( hdrs );
            }
        else if ( aFunction == EMceItcFCGetMediaLines )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            
            CDesC8ArrayFlat* atts = new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
            CleanupStack::PushL( atts );
            
            atts->AppendL( KMceAttr1 );
            atts->AppendL( KMceAttr2 );

            CMceMsgTextArray* msgAtts = new (ELeave) CMceMsgTextArray( *atts );
            CleanupStack::PushL( msgAtts );
            msgAtts->EncodeL();
            
            context->Copy( msgAtts->EncodeBuffer().Ptr( 0 ) );
            
            CleanupStack::PopAndDestroy( msgAtts );
            CleanupStack::PopAndDestroy( atts );
            }
        else if ( aFunction == EMceItcGain )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestGain );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcMaxGain  )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestMaxGain );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcGetSession  )
            {

            CMceSession::TState sessionState = (CMceSession::TState)storage->iBackupSessionState;
            CMceComSession::TType sessionType = (CMceComSession::TType)storage->iBackupSessionType;
            
            storage->Reset();
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            
            CMceComSession* ses = CMceComSession::NewLC( sessionType );
            ses->iID = (*idsPtr)().iSessionID;
            ses->iState = sessionState;
            CMceMsgObject<CMceComSession>* sesMsg = 
                new( ELeave ) CMceMsgObject<CMceComSession>( *ses, EMceItcMsgTypeSession );
            CleanupStack::PushL( sesMsg );
            sesMsg->EncodeL();
            context->Copy( sesMsg->EncodeBuffer().Ptr( 0 ) );
            CleanupStack::PopAndDestroy( sesMsg );
            CleanupStack::PopAndDestroy( ses );
            }
        else if ( aFunction == EMceItcCameraInfo )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TCameraInfo info;
            info.iHardwareVersion.iMajor = KMceTestCameraInfoHWVersionMajor;
            info.iHardwareVersion.iMinor = KMceTestCameraInfoHWVersionMinor; 
            info.iHardwareVersion.iBuild = KMceTestCameraInfoHWVersionBuild;
            info.iSoftwareVersion.iMajor = KMceTestCameraInfoSWVersionMajor;
            info.iSoftwareVersion.iMinor = KMceTestCameraInfoSWVersionMinor;
            info.iSoftwareVersion.iBuild = KMceTestCameraInfoSWVersionBuild;        
            info.iOrientation = KMceTestCameraInfoOrientation;
            info.iOptionsSupported = KMceTestCameraInfoOptionsSupported;
            info.iFlashModesSupported = KMceTestCameraInfoFlashModesSupported;
            info.iExposureModesSupported = KMceTestCameraInfoExposureModesSupported;
            info.iWhiteBalanceModesSupported = KMceTestCameraInfoWBModesSupported;
            info.iMinZoom = KMceTestCameraInfoMinZoom;
            info.iMaxZoom = KMceTestCameraInfoMaxZoom;
            info.iMaxDigitalZoom = KMceTestCameraInfoMaxDigitalZoom;
            info.iMinZoomFactor = KMceTestCameraInfoMinZoomFactor;
            info.iMaxZoomFactor = KMceTestCameraInfoMaxZoomFactor;
            info.iMaxDigitalZoomFactor = KMceTestCameraInfoMaxDigitalZoomFactor;
            info.iNumImageSizesSupported = KMceTestCameraInfoNumImageSizesSupported;
            info.iImageFormatsSupported = KMceTestCameraInfoImageFormatsSupported;
            info.iNumVideoFrameSizesSupported = KMceTestCameraInfoNumVideoFrameSizesSupported;
            info.iNumVideoFrameRatesSupported = KMceTestCameraInfoNumVideoFrameRatesSupported;
            info.iVideoFrameFormatsSupported = KMceTestCameraInfoVideoFrameFormatsSupported;
            info.iMaxFramesPerBufferSupported = KMceTestCameraInfoMaxFramesPerBufferSupported;
            info.iMaxBuffersSupported = KMceTestCameraInfoMaxBuffersSupported;
                   
            TMceCameraInfo cameraInfo;
            cameraInfo.iIndex = 0;
            cameraInfo.iInfo = info;
            
            TPckgBuf<TMceCameraInfo> cameraInfoBuf( cameraInfo );
            context->Copy( cameraInfoBuf );
            
            }
        else if ( aFunction == EMceItcCamerasAvailable )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestCamerasAvailable );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcZoomFactor )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestZoomFactor );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcDigitalZoomFactor )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestDigitalZoomFactor );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcContrast )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestContrast );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcBrightness )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestBrightness );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcExposure )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestExposure );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcWhiteBalance )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestWhiteBalance );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcDisplaysAvailable )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestDisplaysAvailable );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcDisplayRect )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TRect rect;
            rect.iTl.iX = KMceTestDisplayRectTlX;
            rect.iTl.iY = KMceTestDisplayRectTlY;
            rect.iBr.iX = KMceTestDisplayRectBrX;
            rect.iBr.iY = KMceTestDisplayRectBrY;
                       
            TPckgBuf<TRect> rectBuf( rect );
            context->Copy( rectBuf );
            }
        else if ( aFunction == EMceItcDisplayPriority )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TMceItcArgTInt value( KMceTestDisplayPriority );
            context->Copy( value );
            }
        else if ( aFunction == EMceItcFileInfo )
            {
            TPckgBuf<TMceFileInfo>* buf = (TPckgBuf<TMceFileInfo>*)aArgs.iArgs[ EMceItcArgContext ];

            TMceFileInfo& info = (*buf)();
            
            if ( info.iFileName == KMceTestAudioFileName() ||
                 info.iFileName == KMceTestAVFileName16() )
                {
                info.iAudioElementCount = KMceTestAudioElementCount;
                info.iAudioCodec.Append( KMceTestAudioCodec );
                }
            
            if ( info.iFileName == KMceTestVideoFileName() ||
                 info.iFileName == KMceTestAVFileName16() )
                {   
                info.iVideoElementCount = KMceTestVideoElementCount; 
                info.iVideoCodec = KMceTestVideoCodec;
                }
            
            info.iDuration = KMceTestDuration;
            
            }
        else if ( aFunction == EMceItcFilePosition )
            {
            TPckgBuf<TTimeIntervalMicroSeconds>* bufPtr = 
                (TPckgBuf<TTimeIntervalMicroSeconds>*)aArgs.iArgs[ EMceItcArgContext ];
            (*bufPtr)() = KMceTestPosition;
            }
        else if ( aFunction == EMceItcSetCameraIndex )
            {
            TDes8* context = (TDes8*)aArgs.iArgs[ EMceItcArgContext ];
            TPckgBuf<TMceCameraInfo>* buf = (TPckgBuf<TMceCameraInfo>*)aArgs.iArgs[ EMceItcArgContext ];

            TCameraInfo cinfo;
            cinfo.iMinZoom = KMceTestCameraInfoMinZoom;
            cinfo.iMaxZoom = KMceTestCameraInfoMaxZoom;
            
            TMceCameraInfo& info = (*buf)();
            info.iIndex = 1;
            info.iInfo = cinfo;
            }
        else if ( aFunction == EMceItcSetZoomFactor )
            {
            }
        else if ( aFunction == EMceItcSetDigitalZoomFactor )
            {
            }
        else if ( aFunction == EMceItcSetContrast )
            {
            }
        else if ( aFunction == EMceItcSetBrightness )
            {
            }
        else if ( aFunction == EMceItcSetExposure )
            {
            }
        else if ( aFunction == EMceItcSetWhiteBalance )
            {
            }
        else if ( aFunction == EMceItcSetDisplayIndex )
            {
            }
        else if ( aFunction == EMceItcSetDisplayRect )
            {
            }
        else if ( aFunction == EMceItcSetDisplayPriority )
            {
            }
        else
            {
            }
        }
        
        
	return KErrNone;
	}

// -----------------------------------------------------------------------------
// RMCEStub::Receive
// From MMceItc
// -----------------------------------------------------------------------------
//
void RMCEStub::Receive (TIpcArgs& aArgs, TRequestStatus& aStatus )
	{
	__ASSERT_ALWAYS (iConnected, Panic(KErrCouldNotConnect));
	
	aStatus = KRequestPending;
    CMCEThreadLocalStorage* storage = static_cast<CMCEThreadLocalStorage*> ( Dll::Tls() );
    if ( storage )
        {
        TPckgBuf<TMceIds>* idsPtr = (TPckgBuf<TMceIds>*)aArgs.iArgs[ EMceItcArgIds ];
        storage->Register( idsPtr, aStatus );

        }
	}

// -----------------------------------------------------------------------------
// RMCEStub::Receive
// From MMceItc
// -----------------------------------------------------------------------------
//
TInt RMCEStub::Receive (TIpcArgs& /*aArgs*/, TPtr8 aContext, TPtr8 aContent )
	{
	__ASSERT_ALWAYS (iConnected, Panic( KErrCouldNotConnect ) );

    CMCEThreadLocalStorage* storage = static_cast<CMCEThreadLocalStorage*> ( Dll::Tls() );
    if ( storage )
        {
    /*        
        TAny* contextPtr = (TAny*)aArgs.iArgs[ EMceItcArgContext ];
        TAny* contentPtr = (TAny*)aArgs.iArgs[ EMceItcArgMessageContent ];
        
        if ( contextPtr && storage->iContext )
            {
            TDes8* context = (TDes8*)contextPtr;
            context->Copy( *(storage->iContext) );
            }
        if ( contentPtr && storage->iContent )
            {
            TDes8* content = (TDes8*)contentPtr;
            
            content->Copy( *(storage->iContent) );
            }
     */
     
        
	    if ( storage->iContext )
	    	{
	    	aContext.Copy( *(storage->iContext) );
	    	}
	    	
	    if ( storage->iContent )
	    	{
	    	aContent.Copy( *(storage->iContent) );
	    	}
	    	
		}
	
	return KErrNone;
	

	/*

    aArgs.Set( EMceItcArgContext, &aContext);
    aArgs.Set( EMceItcArgMessageContent, &aContent );

	return SendReceive( EMceItcReceive, aArgs);
	*/
	}


// -----------------------------------------------------------------------------
// RMCEStub::CancelReceive
// From MMceItc
// -----------------------------------------------------------------------------
//
void RMCEStub::CancelReceive ( TIpcArgs& aArgs )
	{
    __ASSERT_ALWAYS (iConnected, Panic(KErrCouldNotConnect));
    CMCEThreadLocalStorage* storage = static_cast<CMCEThreadLocalStorage*> ( Dll::Tls() );
    if ( storage )
        {
        TPckgBuf<TMceIds>* idsPtr = (TPckgBuf<TMceIds>*)aArgs.iArgs[ EMceItcArgIds ];
        TRequestStatus* status = storage->GetStatus( idsPtr );
    	User::RequestComplete( status, KErrNone );
        }
	}


// -----------------------------------------------------------------------------
// RMCEStub::SendAppUid
// -----------------------------------------------------------------------------
//
TInt RMCEStub::SendClientUid ( const TUid& aUid ) const
	{
	TMceIds ids;
	ids.iAppUID = aUid.iUid;
	
    TPckgBuf<TInt> clientUidPckg( aUid.iUid );
    TPckgBuf<TMceIds> idsPckg( ids );
    TIpcArgs itcMsgArgs;
    
    itcMsgArgs.Set(EMceItcArgIds, &idsPckg);
    itcMsgArgs.Set(EMceItcArgAppUid, &clientUidPckg);

	return KErrNone;
	}

// -----------------------------------------------------------------------------
// RMCEStub::Panic
// -----------------------------------------------------------------------------
//
void RMCEStub::Panic (TInt aReason) const
	{
    User::Panic( KMceClientPanic, aReason);
	}



// -----------------------------------------------------------------------------
// CMCEThreadLocalStorage::CMCEThreadLocalStorage
// -----------------------------------------------------------------------------
//
CMCEThreadLocalStorage::CMCEThreadLocalStorage()
    : iSessionId(0) 
    {
    iEntries.Reset();
    }

// -----------------------------------------------------------------------------
// CMCEThreadLocalStorage::Reset
// -----------------------------------------------------------------------------
//
void CMCEThreadLocalStorage::Reset()
    {
    delete iContext;
    delete iContent;
    iContext = NULL;
    iContent = NULL;
    iStatus = 0;
    iBackupSessionState = CMceSession::EEstablished;
    iBackupSessionType = CMceComSession::EInSession;

    }

// -----------------------------------------------------------------------------
// CMCEThreadLocalStorage::~CMCEThreadLocalStorage
// -----------------------------------------------------------------------------
//
CMCEThreadLocalStorage::~CMCEThreadLocalStorage()
    {
    Reset();
    }

    
// -----------------------------------------------------------------------------
// CMCEThreadLocalStorage::Register
// -----------------------------------------------------------------------------
//
void CMCEThreadLocalStorage::Register( TPckgBuf<TMceIds>* aIds, TRequestStatus& aStatus )
    {
    int i = 0;
    TBool found = EFalse;
    while( !found && i < iEntries.Count() )
        {
        if ( iEntries[i].iStatus == &aStatus )
            {
            found = ETrue;
            }
        i++;            
        }
        
    if ( !found )
        {
        i = 0;
        while( !found && i < iEntries.Count() )
            {
            if ( iEntries[i].iStatus == NULL )
                {
                found = ETrue;
                iEntries[i] = TRegistryEntry( &aStatus, aIds );
                }
            i++;            
            }
        }
    
    }

    
// -----------------------------------------------------------------------------
// CMCEThreadLocalStorage::GetIds
// -----------------------------------------------------------------------------
//
TPckgBuf<TMceIds>* CMCEThreadLocalStorage::GetIds( TRequestStatus& aStatus )
    {
    
     for( int i = 0; i < iEntries.Count(); i++ )
        {
        if ( iEntries[i].iStatus == &aStatus )
            {
            return iEntries[i].iIDS;
            }
        }
    
    return NULL;
        
    }

// -----------------------------------------------------------------------------
// CMCEThreadLocalStorage::GetStatus
// -----------------------------------------------------------------------------
//
TRequestStatus* CMCEThreadLocalStorage::GetStatus( TPckgBuf<TMceIds>* aIds )
    {
    for( int i = 0; i < iEntries.Count(); i++ )
        {
        if ( iEntries[i].iIDS == aIds )
            {
            return iEntries[i].iStatus;
            }
        }
    
    return NULL;
    }

