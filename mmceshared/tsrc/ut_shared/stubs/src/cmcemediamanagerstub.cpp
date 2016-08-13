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




// INCLUDE FILES
#include "mcemediamanager.h"
#include "mcemediaobserver.h"
#include "mceamrcodec.h"
#include "mcemediadefs.h"

#include "mcecomamrcodec.h"
#include "mcecomh263codec.h"

#include "mcelogs.h"

#include "mcesdpsession.h"

// ================ MEMBER FUNCTIONS =======================



// ---------------------------------------------------------
// CMceMediaManager::CMceMediaManager
// C++ default constructor can NOT contain any code, that
// might leave.
// Status : Draft
// ---------------------------------------------------------
CMceMediaManager::CMceMediaManager()
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::ConstructL
// Symbian 2nd phase constructor can leave.
// Status : Draft
// ---------------------------------------------------------
void CMceMediaManager::ConstructL( MMceMediaGeneralObserver& aObserver )
    {  
    iObserver = &aObserver;
    
    }


// ---------------------------------------------------------
// CMceMediaManager::NewL
// Static constructor.
// Status : Draft
// ---------------------------------------------------------
CMceMediaManager* CMceMediaManager::NewL( MMceMediaGeneralObserver& aObserver )
    {
    CMceMediaManager* self = NewLC( aObserver );
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------
// CMceMediaManager::NewLC
// Static constructor.
// Status : Draft
// ---------------------------------------------------------
CMceMediaManager* CMceMediaManager::NewLC( MMceMediaGeneralObserver& aObserver )
    {
    CMceMediaManager* self = new ( ELeave ) CMceMediaManager;
    CleanupStack::PushL( self );
    self->ConstructL( aObserver );
    return self;
    }


// ---------------------------------------------------------
// CMceMediaManager::~CMceMediaManager
// Destructor
// Status : Draft
// ---------------------------------------------------------    
CMceMediaManager::~CMceMediaManager()
    {
    }   

// ---------------------------------------------------------
// CMceMediaManager::SendRTCPAnyDataL 
// ---------------------------------------------------------   
// 
void CMceMediaManager::SendRTCPAnyDataL( const CMceComMediaStream& /*aMediaStream*/, 
                                         const TDesC8& /*aData*/ )
    {
    MCE_DEBUG1("CMceMediaManager::SendRTCPAnyDataL");
    
    }

// ---------------------------------------------------------
// CMceMediaManager::PauseL 
// ---------------------------------------------------------   
// 
void CMceMediaManager::PauseL( CMceComMediaSink& /*aSink*/ )
    {
    MCE_DEBUG1("CMceMediaManager::PauseL( sink )");
    }
    
// ---------------------------------------------------------
// CMceMediaManager::PauseL
// ---------------------------------------------------------  
// 
void CMceMediaManager::PauseL( CMceComMediaSource& /*aSource*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::PauseL( source )");
    }
    
// ---------------------------------------------------------
// CMceMediaManager::ResumeL 
// ---------------------------------------------------------    
//
void CMceMediaManager::ResumeL( CMceComMediaSink& /*aSink*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::ResumeL( sink )");
    
    }
    
// ---------------------------------------------------------
// CMceMediaManager::ResumeL 
// ---------------------------------------------------------  
//  
void CMceMediaManager::ResumeL( CMceComMediaSource& /*aSource*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::ResumeL( source )");
    }

// ---------------------------------------------------------
// CMceMediaManager::CloseSession
// Closes MCC session and removes the internal sdp session
// Status : Draft
// ---------------------------------------------------------    
TInt CMceMediaManager::CloseSession( CMceComSession& /*aSession*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::CloseSession");
    return KErrNone;
    }


// ---------------------------------------------------------
// CMceMediaManager::StartInactivityTimerL 
// ---------------------------------------------------------    
//
void CMceMediaManager::StartInactivityTimerL( 
                        const CMceComRtpSource& /*aRtpSource*/,
                        TUint32 /*aInactivityTimeout*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::StartInactivityTimerL");
    
    }
    
// ---------------------------------------------------------
// CMceMediaManager::StopInactivityTimerL 
// ---------------------------------------------------------    
//
void CMceMediaManager::StopInactivityTimerL( const CMceComRtpSource& /*aRtpSource*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::StopInactivityTimerL");
    }


// ---------------------------------------------------------
// CMceMediaManager::SendRTCPReceiverReportL 
// ---------------------------------------------------------    
//
void CMceMediaManager::SendRTCPReceiverReportL( const CMceComRtpSource& /*aRtpSource*/ )
    {
    MCE_DEBUG1("CMceMediaManager::SendRTCPReceiverReportL");
    }
    
// ---------------------------------------------------------
// CMceMediaManager::SendRTCPSenderReportL 
// ---------------------------------------------------------   
// 
void CMceMediaManager::SendRTCPSenderReportL( const CMceComRtpSink& /*aRtpSink*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::SendRTCPSenderReportL");
    }   

// ---------------------------------------------------------
// CMceMediaManager::SetBalanceL 
// ---------------------------------------------------------    
//
void CMceMediaManager::SetBalanceL( const CMceComMediaSink& /*aSink*/, 
                                    TInt /*aBalance*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::SetBalanceL");
    }  

// ---------------------------------------------------------
// CMceMediaManager::SetBalanceL 
// ---------------------------------------------------------    
//
void CMceMediaManager::SetBalanceL( const CMceComMediaSource& /*aSource*/,
                                    TInt /*aBalance*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::SetBalanceL");
    }  

// ---------------------------------------------------------
// CMceMediaManager::GetGainL 
// ---------------------------------------------------------    
//
void CMceMediaManager::GetGainL( const CMceComMediaSource& /*aSource*/,
                                 TInt& aGain )
    {
    MCE_DEBUG1("CMceMediaManager::GetGainL");
    aGain = 1;
    }  

// ---------------------------------------------------------
// CMceMediaManager::SetGainL 
// --------------------------------------------------------- 
//   
void CMceMediaManager::SetGainL( const CMceComMediaSource& /*aSource*/,
                                 TInt /*aGain*/ )
    { 
    MCE_DEBUG1("CMceMediaManager::SetGainL");
    }   

// ---------------------------------------------------------
// CMceMediaManager::SetVolumeL 
// --------------------------------------------------------- 
//   
void CMceMediaManager::SetVolumeL( const CMceComMediaSink& /*aSink*/, 
                                  TInt /*aVolume*/ )
    {
    MCE_DEBUG1("CMceMediaManager::SetVolumeL");
    }

// ---------------------------------------------------------
// CMceMediaManager::GetVolumeL 
// --------------------------------------------------------- 
//   
void CMceMediaManager::GetVolumeL( const CMceComMediaSink& /*aSink*/, 
                                  TInt& aVolume )
    {
    MCE_DEBUG1("CMceMediaManager::GetVolumeL");
    aVolume = 1;
    }

// ---------------------------------------------------------
// CMceMediaManager::GetMaxVolumeL 
// --------------------------------------------------------- 
//   
void CMceMediaManager::GetMaxVolumeL( TInt& aMaxVolume )
    {
    MCE_DEBUG1("CMceMediaManager::GetMaxVolumeL");
    aMaxVolume = 10;
    }

// ---------------------------------------------------------
// CMceMediaManager::SetAudioRoutingL 
// --------------------------------------------------------- 
//           
void CMceMediaManager::SetAudioRoutingL( const CMceComSpeakerSink& /*aSpeaker*/, 
                                        TInt /*aRoutingDestination*/ )
    {
    MCE_DEBUG1("CMceMediaManager::SetAudioRoutingL");
    }

// ---------------------------------------------------------
// CMceMediaManager::GetAudioRoutingL 
// --------------------------------------------------------- 
//           
void CMceMediaManager::GetAudioRoutingL( const CMceComSpeakerSink& /*aSpeaker*/,
                                        TInt& aRoutingDestination )
    {
    MCE_DEBUG1("CMceMediaManager::GetAudioRoutingL");
    aRoutingDestination = 1;
    }

// ---------------------------------------------------------
// CMceMediaManager::GetMaxGainL 
// --------------------------------------------------------- 
//           
void CMceMediaManager::GetMaxGainL( TInt& aMaxGain )
    {
    MCE_DEBUG1("CMceMediaManager::GetMaxGainL");
    aMaxGain = 10;
    }
                        
// ---------------------------------------------------------
// CMceMediaManager::GetSupportedCodecs 
// ---------------------------------------------------------    
//
 TInt CMceMediaManager::GetSupportedCodecs( RArray<TFourCC>& /*aCodecs*/  )
    { 
    TInt err = KErrNone;
    return err;
    }     

// ---------------------------------------------------------
// CMceMediaManager::GetCapabilities 
// ---------------------------------------------------------  
//  
  void CMceMediaManager::GetCapabilitiesL( 
 						RPointerArray<CMceComAudioCodec>& aCapabilities  )
    { 
	CMceComAMRCodec* comcodec = CMceComAMRCodec::NewL( _L8("AMR") );
	CleanupStack::PushL( comcodec );
	aCapabilities.Append( static_cast<CMceComAudioCodec*> ( comcodec ) );
	CleanupStack::Pop( comcodec ); 
	comcodec->iSamplingFreq = 100;
	comcodec->iPayloadType = 97;
	comcodec->iBitrate = 3600;
	comcodec->iMaxPTime = 400;
	comcodec->iPTime = 300;
	comcodec->iEnableVAD = EFalse;
    
    }  


// ---------------------------------------------------------
// CMceMediaManager::GetCapabilities 
// ---------------------------------------------------------  
//  
  void CMceMediaManager::GetCapabilitiesL( 
 						RPointerArray<CMceComVideoCodec>& aCapabilities  )
    { 
	CMceComH263Codec* comcodec = CMceComH263Codec::NewL( _L8("H263-2000") );
	CleanupStack::PushL( comcodec );
	aCapabilities.Append( static_cast<CMceComVideoCodec*> ( comcodec ) );
	CleanupStack::Pop( comcodec ); 
	comcodec->iPayloadType = 96;
    
    }  

// ---------------------------------------------------------
// CMceMediaManager::EncodeL
// ---------------------------------------------------------    
CSdpDocument* CMceMediaManager::EncodeL( CMceComSession& /*aSession*/ )
    {

    MCE_DEBUG1("MediaManager: CMceMediaManager::CreateOfferL() ")

    CSdpDocument* offer = NULL;
    return offer;
    }


// ---------------------------------------------------------
// CMceMediaManager::DecodeL
// ---------------------------------------------------------    
TMceSipWarningCode CMceMediaManager::DecodeL( 
                            CMceComSession& /*aSession*/,
                            CSdpDocument& /*aSdpDocument*/ )
    {
    
    TMceSipWarningCode result = KErrNone;
    return result;
    
    }

// ---------------------------------------------------------
// CMceMediaManager::UpdateL
// ---------------------------------------------------------    
TMceReturnStatus CMceMediaManager::UpdateL( CMceComSession& /*aSession*/ )
    {

    TMceReturnStatus result = KErrNone;
    return result;
    }
              
// ---------------------------------------------------------
// CMceMediaManager::ReserveL
// ---------------------------------------------------------    
TMceReturnStatus CMceMediaManager::ReserveL( CMceComSession& /*aSession*/, 
                                             const TDesC8& /*aToken*/ )
    {
    TMceReturnStatus result = KErrNone;
    return result;
    }

// ---------------------------------------------------------
// CMceMediaManager::ReservationNeeded
// ---------------------------------------------------------    
TBool CMceMediaManager::ReservationNeeded( CMceComSession& /*aSession*/ )
    {
    return EFalse;
    }

// ---------------------------------------------------------
// CMceMediaManager::NeedToNegotiate
// ---------------------------------------------------------    
TBool CMceMediaManager::NeedToNegotiate( CMceComSession& /*aSession*/,
                                         CSdpDocument* /*aSdpDocument*/ )
    {
    TBool result( EFalse );
    return result;
    }

// ---------------------------------------------------------
// CMceMediaManager::NeedToNegotiate
// ---------------------------------------------------------    
TBool CMceMediaManager::ConfirmationNeeded( CMceComSession& /*aSession*/ )
    {
    TBool result( EFalse );
    return result;
    }
    
// ---------------------------------------------------------------------------
// CMceMediaManager::EnableViewFinderL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::EnableViewFinderL( const CMceComMediaSink& /*aMediaSink*/, 
                                          const TDesC8& /*aParam*/ )
    {
    MCE_DEBUG1("CMceMediaManager::EnableViewFinderL");
    }


// ---------------------------------------------------------------------------
// CMceMediaManager::DisableViewFinderL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::DisableViewFinderL( const CMceComMediaSink& /*aMediaSink*/ )
    {
    MCE_DEBUG1("CMceMediaManager::DisableViewFinderL");
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetDisplayRectL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetDisplayRectL( CMceComDisplaySink& /*aSink*/, 
                                        TRect& aDisplayRect )
    {
    MCE_DEBUG1("CMceMediaManager::GetDisplayRectL");
    aDisplayRect = TRect( 10, 10 ,20 ,20 );
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetDisplayRectL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetDisplayRectL( CMceComDisplaySink& /*aSink*/, 
                                        TRect /*aDisplayRect*/ )
    {
    MCE_DEBUG1("CMceMediaManager::SetDisplayRectL");
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetDisplayPriorityL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetDisplayPriorityL( CMceComDisplaySink& /*aSink*/, 
                                            TInt& aDisplayPriority )
    {
    MCE_DEBUG1("CMceMediaManager::GetDisplayPriorityL");
    aDisplayPriority = 2;
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetDisplayPriorityL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetDisplayPriorityL( CMceComDisplaySink& /*aSink*/, 
                                            TInt /*aDisplayPriority*/ )
    {
    MCE_DEBUG1("CMceMediaManager::SetDisplayPriorityL");
    }   

// ---------------------------------------------------------------------------
// CMceMediaManager::SetDisplayIndexL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetDisplayIndexL( CMceComDisplaySink& /*aSink*/, 
                                         TInt /*aDisplayIndex*/ )
    {
    MCE_DEBUG1("CMceMediaManager::SetDisplayIndexL");
    }

// ---------------------------------------------------------
// CMceMediaManager::GetDisplayRotationL 
// --------------------------------------------------------- 
//   
void CMceMediaManager::GetDisplayRotationL( CMceComDisplaySink& /*aSink*/, 
                                            TInt& aDisplayRotation )
    {
    MCE_DEBUG1("CMceMediaManager::GetDisplayRotationL");
    aDisplayRotation = 1;
    }

// ---------------------------------------------------------
// CMceMediaManager::SetDisplayRotationL 
// --------------------------------------------------------- 
//   
void CMceMediaManager::SetDisplayRotationL( CMceComDisplaySink& /*aSink*/, 
                                            TInt /*aDisplayRotation*/ )
    {
    MCE_DEBUG1("CMceMediaManager::SetDisplayRotationL");
    }


// ---------------------------------------------------------
// CMceMediaManager::SetCNameL
// ---------------------------------------------------------    
//
void CMceMediaManager::SetCNameL( 
    const CMceComEndpoint& /*aEndpoint*/, 
    const TDesC8& /*aCName*/ )
    {
    //NOP
    }

// ---------------------------------------------------------
// CMceMediaManager::DtmfL
// ---------------------------------------------------------    
//
void CMceMediaManager::DtmfL( 
    CMceComMediaSource& /*aSource*/, 
    TMceComEvent& /*aEvent*/,
    const TDesC8& /*aSequence*/ )
    {
    MCE_DEBUG1("CMceMediaManager::DtmfL");
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetZoomFactorL     
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetZoomFactorL( CMceComCameraSource& /*aSource*/, 
                             TInt& aZoomFactor )
    {
    
    MCE_DEBUG1("CMceMediaManager::GetZoomFactorL");
    aZoomFactor = 1;
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetDigitalZoomFactorL  
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetDigitalZoomFactorL( CMceComCameraSource& /*aSource*/, 
                                    TInt& aDigitalZoomFactor )
    {
    
    MCE_DEBUG1("CMceMediaManager::GetDigitalZoomFactorL");
    aDigitalZoomFactor = 1;
    
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetContrastL       
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetContrastL( CMceComCameraSource& /*aSource*/, 
                                     TInt& aContrast )
    {
    
    MCE_DEBUG1("CMceMediaManager::GetContrastL");
    aContrast = 1;
      
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetBrightnessL     
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetBrightnessL( CMceComCameraSource& /*aSource*/, 
                                       TInt& aBrightness )
    {
    
    MCE_DEBUG1("CMceMediaManager::GetBrightnessL");
    aBrightness = 1;
   
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetExposureL   
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetExposureL( CMceComCameraSource& /*aSource*/, 
                                     TInt& aExposure )
    {
    
    MCE_DEBUG1("CMceMediaManager::GetExposureL");
    aExposure = 1;
    
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetWhiteBalanceL   
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetWhiteBalanceL( CMceComCameraSource& /*aSource*/, 
                                         TInt& aWhiteBalance )
    {
    
    MCE_DEBUG1("CMceMediaManager::GetWhiteBalanceL");
    aWhiteBalance = 1;
    
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetCameraIndexL    
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetCameraIndexL( CMceComCameraSource& /*aSource*/,
                                        TInt /*aCameraIndex*/,
                                        TCameraInfo& /*aCameraInfo*/ )
    {
    MCE_DEBUG1("CMceMediaManager::SetCameraIndexL");
    }
                              
// ---------------------------------------------------------------------------
// CMceMediaManager::SetZoomFactorL     
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetZoomFactorL( CMceComCameraSource& /*aSource*/, 
                                       TInt /*aZoomFactor*/ )
    {
   
    MCE_DEBUG1("CMceMediaManager::SetZoomFactorL");
    
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetDigitalZoomFactorL  
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetDigitalZoomFactorL( CMceComCameraSource& /*aSource*/, 
                                              TInt /*aDigitalZoomFactor*/ )
    {
    
    MCE_DEBUG1("CMceMediaManager::SetDigitalZoomFactorL");
    
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetContrastL   
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetContrastL( CMceComCameraSource& /*aSource*/, 
                                     TInt /*aContrast*/ )
    {
    
    MCE_DEBUG1("CMceMediaManager::SetContrastL");
    
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetBrightnessL     
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetBrightnessL( CMceComCameraSource& /*aSource*/, 
                                       TInt /*aBrightness*/ )
    {
    
    MCE_DEBUG1("CMceMediaManager::SetBrightnessL");
   
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetExposureL   
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetExposureL( CMceComCameraSource& /*aSource*/, 
                                     TInt /*aExposure*/ )
    {
    
    MCE_DEBUG1("CMceMediaManager::SetExposureL");
    
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetWhiteBalanceL   
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetWhiteBalanceL( CMceComCameraSource& /*aSource*/, 
                                         TInt /*aWhiteBalance*/ )
    {
    
    MCE_DEBUG1("CMceMediaManager::SetWhiteBalanceL");
        
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetFileInfoL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetFileInfoL( CMceComFileSource& /*aSource*/, 
                                     TMceFileInfo& /*aFileInfo*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetFilePositionL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::GetFilePositionL( CMceComFileSource& /*aSource*/, 
                                         TTimeIntervalMicroSeconds& /*aFilePosition*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetFilePositionL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::SetFilePositionL( CMceComFileSource& /*aSource*/, 
                                         TTimeIntervalMicroSeconds& /*aFilePosition*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::FastForwardL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::FastForwardL( CMceComFileSource& /*aSource*/, 
                                     TBool& /*aOnOff*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::FastRewindL
// ---------------------------------------------------------------------------
//
void CMceMediaManager::FastRewindL( CMceComFileSource& /*aSource*/, 
                                    TBool& /*aOnOff*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetCameraInfoL
// ---------------------------------------------------------------------------
//                              
void CMceMediaManager::GetCameraInfoL( TInt /*aCameraIndex*/, 
                                       TCameraInfo& /*aCameraInfo*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetCamerasAvailableL
// ---------------------------------------------------------------------------
//                              
void CMceMediaManager::GetCamerasAvailableL( TInt& /*aCamerasAvailable*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetDisplaysAvailableL
// ---------------------------------------------------------------------------
//                               
void CMceMediaManager::GetDisplaysAvailableL( TInt& /*aDisplaysAvailable*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::GetFileInfoL
// ---------------------------------------------------------------------------
//                               
void CMceMediaManager::GetFileInfoL( TMceFileInfo& /*aFileInfo*/ )
    {
    // NOP
    }


// ---------------------------------------------------------------------------
// CMceMediaManager::SetFileInfoL
// ---------------------------------------------------------------------------
//                               
void CMceMediaManager::SetFileInfoL( CMceComFileSource& /*aSource*/, 
                                     TMceFileInfo& /*aFileInfo*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::TranscodeFileL
// ---------------------------------------------------------------------------
//                               
TUint32 CMceMediaManager::TranscodeFileL( CMceComFileSource* /*aFile*/ )
    {
    return 0;
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::CancelTranscodeFileL
// ---------------------------------------------------------------------------
//                               
void CMceMediaManager::CancelTranscodeFileL( TUint32 /*aSessionId*/ )
    {
    // NOP
    }

// ---------------------------------------------------------------------------
// CMceMediaManager::SetMccParameterL
// ---------------------------------------------------------------------------
//     
void CMceMediaManager::SetMccParameterL( 
    const CMceComMediaSink& /*aMediaSink*/,
    TUint32 /*aParam*/,
    const TDesC8& /*aValue*/,
    TBool /*aAllowNonPrepared*/ ) const
    {
    }
    
/*
** From MMcpCtrlObserver ***
*/

// ---------------------------------------------------------
// CMceMediaManager::MccMediaSignalReceived
// --------------------------------------------------------- 
//   	
void CMceMediaManager::MccEventReceived( const TMccEvent& /*aEvent*/)
	{
	}

// ---------------------------------------------------------
// CMceMediaManager::MccCtrlError
// ---------------------------------------------------------   
// 	

void CMceMediaManager::MccCtrlError( TInt /*aError*/,
                                     TUint32 /*aSessionId*/,
                                     TUint32 /*aLinkId*/,
                                     TUint32 /*aStreamId*/,
                                     TUint32 /*aSinkSourceId*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::MccMediaActive
// ---------------------------------------------------------    
//  

void CMceMediaManager::MccMediaActive( TUint32 /*aSessionId*/,
                                       TUint32 /*aLinkId*/,
                                       TUint32 /*aStreamId*/,
                                       TUint32 /*aSinkSourceId*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::MccMediaInactive
// ---------------------------------------------------------    
//  

void CMceMediaManager::MccMediaInactive( TUint32 /*aSessionId*/,
                                         TUint32 /*aLinkId*/,
                                         TUint32 /*aStreamId*/,
                                         TUint32 /*aSinkSourceId*/ )
    {
    }
    
// ---------------------------------------------------------
// CMceMediaManager::MccMediaResumed
// --------------------------------------------------------- 
//      
void CMceMediaManager::MccMediaResumed( TUint32 /*aSessionId*/,
                                        TUint32 /*aLinkId*/,
                                        TUint32 /*aStreamId*/,
                                        TUint32 /*aSinkSourceId*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::MccMediaPaused
// ---------------------------------------------------------  
//      
void CMceMediaManager::MccMediaPaused( TUint32 /*aSessionId*/,
                                       TUint32 /*aLinkId*/,
                                       TUint32 /*aStreamId*/,
                                       TUint32 /*aSinkSourceId*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::MccMediaStopped
// --------------------------------------------------------- 
//      
void CMceMediaManager::MccMediaStopped( TUint32 /*aSessionId*/,
                                        TUint32 /*aLinkId*/,     
                                        TUint32 /*aStreamId*/,
                                        TUint32 /*aSinkSourceId*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::MccMediaStarted
// --------------------------------------------------------- 
//   
void CMceMediaManager::MccMediaStarted( TUint32 /*aSessionId*/,
                                        TUint32 /*aLinkId*/,     
                                        TUint32 /*aStreamId*/,
                                        TUint32 /*aSinkSourceId*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::MccMediaPrepared 
// ---------------------------------------------------------    
//
void CMceMediaManager::MccMediaPrepared( TUint32 /*aSessionId*/,
                                         TUint32 /*aLinkId*/,
                                         TUint32 /*aStreamId*/,
                                         TUint32 /*aSinkSourceId*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::GetSSRCL 
// ---------------------------------------------------------    
//
TUint32 CMceMediaManager::GetSSRCL( CMceSrvStream& /*aStream*/ )
    {
    return 0;
    }

// ---------------------------------------------------------
// CMceMediaManager::ReuseLink 
// ---------------------------------------------------------    
//                
TBool CMceMediaManager::ReuseLink( CMceSrvStream& /*aStream*/ )
    {
    return EFalse;
    }

// ---------------------------------------------------------
// CMceMediaManager::ReuseSource 
// ---------------------------------------------------------    
//    
TBool CMceMediaManager::ReuseSource( CMceSrvStream& /*aStream*/ )
    {
    return EFalse;
    }

// ---------------------------------------------------------
// CMceMediaManager::ReuseSink 
// ---------------------------------------------------------    
//    
TBool CMceMediaManager::ReuseSink( CMceSrvStream& /*aStream*/ )
    {
    return EFalse;
    }

// ---------------------------------------------------------
// CMceMediaManager::CanReleaseEndpoint 
// ---------------------------------------------------------    
//     
TBool CMceMediaManager::CanReleaseEndpoint( 
    CMceSrvStream& /*aStream*/, TUint32 /*aEndpointId*/ )
    {
    return ETrue;
    }

// ---------------------------------------------------------
// CMceMediaManager::ReleaseSink 
// ---------------------------------------------------------    
//
TInt CMceMediaManager::ReleaseSink( 
    CMceSrvStream& /*aStream*/, TUint32 /*aEndpointId*/ )
    {
    return 0;
    }

// ---------------------------------------------------------
// CMceMediaManager::ReleaseSource 
// ---------------------------------------------------------    
//
TInt CMceMediaManager::ReleaseSource( 
    CMceSrvStream& /*aStream*/, TUint32 /*aEndpointId*/ )
    {
    return 0;
    }



// ---------------------------------------------------------
// CMceMediaManager::UpdateConfigKeyL
// ---------------------------------------------------------    
//
void CMceMediaManager::UpdateConfigKeyL( const CMceComMediaSource& /*aSource*/ )
    {
    }


// ---------------------------------------------------------
// CMceMediaManager::SdpCodec
// ---------------------------------------------------------
CMceSdpCodec* CMceMediaManager::SdpCodec( const CSdpMediaField& /*aMedia*/ )
    {    
    return 0;
    }

// ---------------------------------------------------------
// CMceMediaManager::SdpCodec
// ---------------------------------------------------------
CMceSdpCodec* CMceMediaManager::SdpCodec( CMceComMediaStream& /*aStream*/ )
    {    
    return 0;
    }

// ---------------------------------------------------------
// CMceMediaManager::CreateSessionL
// ---------------------------------------------------------    
CMceSdpSession& CMceMediaManager::CreateSessionL( CMceComSession& aSession )
    {
    CMceSdpSession* sdpSession = CMceSdpSession::NewL( aSession, *this );
    CleanupStack::PushL( sdpSession );

    aSession.AttachSDPSessionL( *sdpSession );
    User::LeaveIfError (iMceSdpSessions.Append( sdpSession ));
    CleanupStack::Pop( sdpSession ); 

    return *sdpSession;
    }

// ---------------------------------------------------------
// CMceMediaManager::SynchronizeMccStreamL 
// ---------------------------------------------------------    
//
void CMceMediaManager::SynchronizeMccStreamL( 
    CMceSrvStream& /*aStream*/, 
    TMceNegotiationRole /*aRole*/,
    TBool /*aSyncCodecOnly*/ )
    {
    }
    
// ---------------------------------------------------------
// CMceMediaManager::SynchronizeMccStreamL 
// ---------------------------------------------------------    
//
void CMceMediaManager::SynchronizeMccStreamL( 
    CMceSrvStream& /*aStream*/, 
    TUint32 /*aForceEnableEndpoint*/, 
    TUint32 /*aForceDisableEndpoint*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::CreateMccSessionL
// ---------------------------------------------------------    
//
void CMceMediaManager::CreateMccSessionL( CMceComSession& /*aSession*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::CreateMccLinkL
// ---------------------------------------------------------    
//
void CMceMediaManager::CreateMccLinkL( CMceSrvStream& /*aStream*/ )
    {      
    }

// ---------------------------------------------------------
// CMceMediaManager::CreateMccStreamL
// ---------------------------------------------------------    
//
void CMceMediaManager::CreateMccStreamL( 
            CMceSrvStream& /*aStream*/,
            TMceNegotiationRole /*aRole*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::InitializeMccStreamL
// ---------------------------------------------------------    
//
void CMceMediaManager::InitializeMccStreamL( CMceSrvStream& /*aStream*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::ValidateMccStreamL
// ---------------------------------------------------------   
//
void CMceMediaManager::ValidateMccStreamL( CMceSrvStream& /*aStream*/ )
    {
    }
// ---------------------------------------------------------
// CMceMediaManager::AdjustMccStreamL
// ---------------------------------------------------------   
//
void CMceMediaManager::AdjustMccStreamL( CMceSrvStream& /*aStream*/ )
    {    
    }

// ---------------------------------------------------------
// CMceMediaManager::PrepareMccStreamL
// ---------------------------------------------------------    
//
void CMceMediaManager::PrepareMccStreamL( 
            CMceSrvStream& /*aStream*/,
            TMceNegotiationRole /*aRole*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::StartMccStreamL
// ---------------------------------------------------------   
//
void CMceMediaManager::StartMccStreamL( CMceSrvStream& /*aStream*/ )
    {

    }

// ---------------------------------------------------------
// CMceMediaManager::PrepareUpdateL 
// ---------------------------------------------------------    
//
void CMceMediaManager::PrepareUpdateL( CMceSdpSession& /*aSession*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::CleanupL
// ---------------------------------------------------------   
//
void CMceMediaManager::CleanupL( CMceComSession& /*aSession*/ )
    {
    }

// ---------------------------------------------------------
// CMceMediaManager::SetRemoteAddressL 
// ---------------------------------------------------------    
//
void CMceMediaManager::SetRemoteAddressL( CMceSrvStream& /*aStream*/ )
    {
    }


