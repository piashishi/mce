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

#include <e32def.h>
#include <e32base.h>
#include <digia/eunit/EUnitMacros.h>
#include "mcecamerasourcetest.h"
#include "mcecamerasource.h"
#include "mcecomcamerasource.h"
#include "mcemanager.h"
#include "mcetestdefs.h"
#include "mcestubs.h"
#include "mceoutsession.h"
#include "mcevideostream.h"
#include "mcertpsink.h"
#include "mcemediasource.h"
#include "mceserial.h"

const TUint8 KMceTestCategory = 5;
// ----------------------------------------------------------------------------
// CMceCameraSourceTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceCameraSourceTest::setUpL()
    {
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
    
    iUid = TUid::Uid( 777 );
    iManager = CMceManager::NewL( iUid, NULL );    
	iCamera = CMceCameraSource::NewL( *iManager );
	iCameraWithoutManager = CMceCameraSource::NewL();
	iCameraFlatData = static_cast<CMceComCameraSource*>(iCamera->iFlatData);
    }

// ----------------------------------------------------------------------------
// CMceCameraSourceTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::tearDown()
    {
    
    delete iCamera;
    delete iCameraWithoutManager;
    delete iManager;
    
    delete iStorage;
    Dll::SetTls( NULL );
    }

// ----------------------------------------------------------------------------
// CMceCameraSourceTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceCameraSourceTest::suiteL()
    {
    CMceCameraSourceTest* suite = new CMceCameraSourceTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceCameraSourceTest,
    "CMceCameraSourceTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, EnableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, DisableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, CamerasAvailableTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, SetCameraIndexTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, GetCameraInfoTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, SetZoomFactorTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, ZoomFactorTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, SetDigitalZoomFactorTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, DigitalZoomFactorTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, SetContrastTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, ContrastTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, SetBrightnessTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, BrightnessTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, SetExposureTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, ExposureTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, SetWhiteBalanceTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, WhiteBalanceTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, GetITCValueTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceCameraSourceTest", setUpL, SetITCValueTestL, tearDown )
EUNIT_END_TEST_TABLE 

// ----------------------------------------------------------------------------
// CMceCameraSourceTest:: ConstructionTestL
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::ConstructionTestL()
    {
    EUNIT_ASSERT( iCamera != NULL );
    EUNIT_ASSERT( iCamera->iFlatData != NULL );
    TCameraInfo cameraInfo;
    iCamera->GetCameraInfo(cameraInfo);
    EUNIT_ASSERT( cameraInfo.iHardwareVersion.iMajor == KMceTestCameraInfoHWVersionMajor );
    EUNIT_ASSERT( cameraInfo.iHardwareVersion.iMinor == KMceTestCameraInfoHWVersionMinor ); 
    EUNIT_ASSERT( cameraInfo.iHardwareVersion.iBuild == KMceTestCameraInfoHWVersionBuild );
    EUNIT_ASSERT( cameraInfo.iSoftwareVersion.iMajor == KMceTestCameraInfoSWVersionMajor );
    EUNIT_ASSERT( cameraInfo.iSoftwareVersion.iMinor == KMceTestCameraInfoSWVersionMinor );
    EUNIT_ASSERT( cameraInfo.iSoftwareVersion.iBuild == KMceTestCameraInfoSWVersionBuild ); 
    EUNIT_ASSERT( cameraInfo.iOrientation == KMceTestCameraInfoOrientation );
    EUNIT_ASSERT( cameraInfo.iOptionsSupported == KMceTestCameraInfoOptionsSupported );
    EUNIT_ASSERT( cameraInfo.iFlashModesSupported == KMceTestCameraInfoFlashModesSupported );
    EUNIT_ASSERT( cameraInfo.iExposureModesSupported == KMceTestCameraInfoExposureModesSupported );
    EUNIT_ASSERT( cameraInfo.iWhiteBalanceModesSupported == KMceTestCameraInfoWBModesSupported );
    EUNIT_ASSERT( cameraInfo.iMinZoom == KMceTestCameraInfoMinZoom );
    EUNIT_ASSERT( cameraInfo.iMaxZoom == KMceTestCameraInfoMaxZoom );
    EUNIT_ASSERT( cameraInfo.iMaxDigitalZoom == KMceTestCameraInfoMaxDigitalZoom );
    EUNIT_ASSERT( cameraInfo.iMinZoomFactor == KMceTestCameraInfoMinZoomFactor );
    EUNIT_ASSERT( cameraInfo.iMaxZoomFactor == KMceTestCameraInfoMaxZoomFactor );
    EUNIT_ASSERT( cameraInfo.iMaxDigitalZoomFactor == KMceTestCameraInfoMaxDigitalZoomFactor );
    EUNIT_ASSERT( cameraInfo.iNumImageSizesSupported == KMceTestCameraInfoNumImageSizesSupported );
    EUNIT_ASSERT( cameraInfo.iImageFormatsSupported == KMceTestCameraInfoImageFormatsSupported );
    EUNIT_ASSERT( cameraInfo.iNumVideoFrameSizesSupported == KMceTestCameraInfoNumVideoFrameSizesSupported );
    EUNIT_ASSERT( cameraInfo.iNumVideoFrameRatesSupported == KMceTestCameraInfoNumVideoFrameRatesSupported );
    EUNIT_ASSERT( cameraInfo.iVideoFrameFormatsSupported == KMceTestCameraInfoVideoFrameFormatsSupported );
    EUNIT_ASSERT( cameraInfo.iMaxFramesPerBufferSupported == KMceTestCameraInfoMaxFramesPerBufferSupported );
    EUNIT_ASSERT( cameraInfo.iMaxBuffersSupported == KMceTestCameraInfoMaxBuffersSupported );
    
    EUNIT_ASSERT( iCameraWithoutManager != NULL );
    EUNIT_ASSERT( iCameraWithoutManager->iFlatData != NULL );
    iCameraWithoutManager->GetCameraInfo(cameraInfo);
    EUNIT_ASSERT( cameraInfo.iHardwareVersion.iMajor != KMceTestCameraInfoHWVersionMajor );
    
    // Try to initialize the camera without the manager
    TRAPD( err, iCameraWithoutManager->InitializeL( NULL ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	CMceComCameraSource* cameraFlatData = static_cast<CMceComCameraSource*>(iCameraWithoutManager->iFlatData);
	EUNIT_ASSERT( !cameraFlatData->iInitialInfoRetrieved );

	// Succeed initializing afterwards
	iCameraWithoutManager->InitializeL( iManager );
	EUNIT_ASSERT( cameraFlatData->iInitialInfoRetrieved );
    }




// ----------------------------------------------------------------------------
// CMceCameraSourceTest::EnableTestL
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::EnableTestL()
    {
    // As long as CMceCameraSource::EnableL does nothing but
    // calls CMceMediaSource::DoEnableL almost dummy test is enough.
    iCameraFlatData->Enabled( EFalse );
    iCamera->EnableL();
    EUNIT_ASSERT( iCameraFlatData->IsEnabled() );
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::DisableTestL
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::DisableTestL()
    {
    // As long as CMceCameraSource::DisableL does nothing but
    // calls CMceMediaSource::DoDisableL almost dummy test is enough.
    iCameraFlatData->Enabled( ETrue );
    iCamera->DisableL();
    EUNIT_ASSERT( !iCameraFlatData->IsEnabled() );
    }
    
    
// ----------------------------------------------------------------------------
// CMceCameraSourceTest::CamerasAvailableTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::CamerasAvailableTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestCamerasAvailable, iCamera->CamerasAvailable() );  
    EUNIT_ASSERT_EQUALS( 0, iCameraWithoutManager->CamerasAvailable() );    
    }    


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::SetCameraIndexTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::SetCameraIndexTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialCameraIndex, iCameraFlatData->iCameraIndex );
    
    TRAPD( err, iCamera->SetCameraIndexL( -1 ) ); // Invalid index, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
    
    TRAP( err, iCamera->SetCameraIndexL( iCamera->CamerasAvailable() + 1 ) ); // Invalid index, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
    iCamera->SetCameraIndexL( 1 );
    EUNIT_ASSERT_EQUALS( 1, iCameraFlatData->iCameraIndex ); 
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialCameraIndex, camFlatData->iCameraIndex );
    
    session->EstablishL();     
    
    camFlatData->iCameraInfo.iMinZoom = 0;
    camFlatData->iCameraInfo.iMaxZoom = 0;
    cam->SetCameraIndexL( 1 );
    EUNIT_ASSERT_EQUALS( 1, camFlatData->iCameraIndex );
    EUNIT_ASSERT_EQUALS( KMceTestCameraInfoMinZoom, camFlatData->iCameraInfo.iMinZoom);
    EUNIT_ASSERT_EQUALS( KMceTestCameraInfoMaxZoom, camFlatData->iCameraInfo.iMaxZoom);
    
    CleanupStack::PopAndDestroy( session );
 
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::GetCameraInfoTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::GetCameraInfoTestL()
    {
    TCameraInfo info;
    iCamera->GetCameraInfo( info );
    EUNIT_ASSERT( info.iHardwareVersion.iMajor == KMceTestCameraInfoHWVersionMajor );
    EUNIT_ASSERT( info.iHardwareVersion.iMinor == KMceTestCameraInfoHWVersionMinor ); 
    EUNIT_ASSERT( info.iHardwareVersion.iBuild == KMceTestCameraInfoHWVersionBuild );
    EUNIT_ASSERT( info.iSoftwareVersion.iMajor == KMceTestCameraInfoSWVersionMajor );
    EUNIT_ASSERT( info.iSoftwareVersion.iMinor == KMceTestCameraInfoSWVersionMinor );
    EUNIT_ASSERT( info.iSoftwareVersion.iBuild == KMceTestCameraInfoSWVersionBuild ); 
    EUNIT_ASSERT( info.iOrientation == KMceTestCameraInfoOrientation );
    EUNIT_ASSERT( info.iOptionsSupported == KMceTestCameraInfoOptionsSupported );
    EUNIT_ASSERT( info.iFlashModesSupported == KMceTestCameraInfoFlashModesSupported );
    EUNIT_ASSERT( info.iExposureModesSupported == KMceTestCameraInfoExposureModesSupported );
    EUNIT_ASSERT( info.iWhiteBalanceModesSupported == KMceTestCameraInfoWBModesSupported );
    EUNIT_ASSERT( info.iMinZoom == KMceTestCameraInfoMinZoom );
    EUNIT_ASSERT( info.iMaxZoom == KMceTestCameraInfoMaxZoom );
    EUNIT_ASSERT( info.iMaxDigitalZoom == KMceTestCameraInfoMaxDigitalZoom );
    EUNIT_ASSERT( info.iMinZoomFactor == KMceTestCameraInfoMinZoomFactor );
    EUNIT_ASSERT( info.iMaxZoomFactor == KMceTestCameraInfoMaxZoomFactor );
    EUNIT_ASSERT( info.iMaxDigitalZoomFactor == KMceTestCameraInfoMaxDigitalZoomFactor );
    EUNIT_ASSERT( info.iNumImageSizesSupported == KMceTestCameraInfoNumImageSizesSupported );
    EUNIT_ASSERT( info.iImageFormatsSupported == KMceTestCameraInfoImageFormatsSupported );
    EUNIT_ASSERT( info.iNumVideoFrameSizesSupported == KMceTestCameraInfoNumVideoFrameSizesSupported );
    EUNIT_ASSERT( info.iNumVideoFrameRatesSupported == KMceTestCameraInfoNumVideoFrameRatesSupported );
    EUNIT_ASSERT( info.iVideoFrameFormatsSupported == KMceTestCameraInfoVideoFrameFormatsSupported );
    EUNIT_ASSERT( info.iMaxFramesPerBufferSupported == KMceTestCameraInfoMaxFramesPerBufferSupported );
    EUNIT_ASSERT( info.iMaxBuffersSupported == KMceTestCameraInfoMaxBuffersSupported );
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::SetZoomFactorTestL
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::SetZoomFactorTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor, iCameraFlatData->iZoomFactor );
    
    TRAPD( err, iCamera->SetZoomFactorL( -1 ) ); // Invalid index, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	TCameraInfo cameraInfo;
	iCamera->GetCameraInfo(cameraInfo);
	TRAP( err, iCamera->SetZoomFactorL( cameraInfo.iMaxZoom + 1 ) ); // Invalid index, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
    iCamera->SetZoomFactorL( KMceTestInitialZoomFactor + 1 );
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor + 1, iCameraFlatData->iZoomFactor ); 
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor, camFlatData->iZoomFactor );
    
    session->EstablishL();     
    
    cam->SetZoomFactorL( KMceTestInitialZoomFactor + 1 );
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor + 1, camFlatData->iZoomFactor );
    
    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::ZoomFactorTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::ZoomFactorTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor, iCamera->ZoomFactorL() );
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor, iCameraWithoutManager->ZoomFactorL() );
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor, camFlatData->iZoomFactor );

    session->EstablishL();     

    EUNIT_ASSERT_EQUALS( KMceTestZoomFactor, cam->ZoomFactorL() );    
    EUNIT_ASSERT_EQUALS( KMceTestZoomFactor, camFlatData->iZoomFactor );

    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::SetDigitalZoomFactorTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::SetDigitalZoomFactorTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialDigitalZoomFactor, iCameraFlatData->iDigitalZoomFactor );
    
    TRAPD( err, iCamera->SetDigitalZoomFactorL( -1 ) ); // Invalid index, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
	TCameraInfo cameraInfo;
	iCamera->GetCameraInfo(cameraInfo);
	TRAP( err, iCamera->SetDigitalZoomFactorL( cameraInfo.iMaxDigitalZoom + 1 ) ); // Invalid index, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
    iCamera->SetDigitalZoomFactorL( KMceTestInitialDigitalZoomFactor + 1 );
    EUNIT_ASSERT_EQUALS( KMceTestInitialDigitalZoomFactor + 1, iCameraFlatData->iDigitalZoomFactor ); 
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor, camFlatData->iDigitalZoomFactor );
    
    session->EstablishL();     
    
    cam->SetDigitalZoomFactorL( KMceTestInitialDigitalZoomFactor + 1 );
    EUNIT_ASSERT_EQUALS( KMceTestInitialDigitalZoomFactor + 1, camFlatData->iDigitalZoomFactor );
    
    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::DigitalZoomFactorTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::DigitalZoomFactorTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialDigitalZoomFactor, 
                       iCamera->DigitalZoomFactorL() );
    EUNIT_ASSERT_EQUALS( KMceTestInitialDigitalZoomFactor, 
                       iCameraWithoutManager->DigitalZoomFactorL() );
                       
                       
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialDigitalZoomFactor, camFlatData->iDigitalZoomFactor );

    session->EstablishL();     

    EUNIT_ASSERT_EQUALS( KMceTestDigitalZoomFactor, cam->DigitalZoomFactorL() );    
    EUNIT_ASSERT_EQUALS( KMceTestDigitalZoomFactor, camFlatData->iDigitalZoomFactor );

    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::SetContrastTestL
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::SetContrastTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialContrast, iCameraFlatData->iContrast );
    
    iCamera->SetContrastL( KMceTestInitialContrast + 1 );
    EUNIT_ASSERT_EQUALS( KMceTestInitialContrast + 1, iCameraFlatData->iContrast ); 
    
    iCamera->SetContrastL( CCamera::EContrastAuto );
    EUNIT_ASSERT_EQUALS( CCamera::EContrastAuto, iCameraFlatData->iContrast ); 
    
    // Make adjusting contrast not supported
    static_cast<CMceComCameraSource*>( 
        iCamera->iFlatData )->iCameraInfo.iOptionsSupported = TCameraInfo::EViewFinderDirectSupported;
    TRAPD( err, iCamera->SetContrastL( 0 ) ); // Unsupported, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotSupported, err );
    
    // Make adjusting contrast supported, but try illegal values
    static_cast<CMceComCameraSource*>( 
        iCamera->iFlatData )->iCameraInfo.iOptionsSupported = TCameraInfo::EContrastSupported;
    TRAP( err, iCamera->SetContrastL( -101 ) ); // Illegal, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
	
    TRAP( err, iCamera->SetContrastL( 101 ) ); // Illegal, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialContrast, camFlatData->iContrast );
    
    session->EstablishL();     
    
    cam->SetContrastL( KMceTestInitialContrast + 1 );
    EUNIT_ASSERT_EQUALS( KMceTestInitialContrast + 1, camFlatData->iContrast );
    
    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::ContrastTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::ContrastTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialContrast, iCamera->ContrastL() );
    EUNIT_ASSERT_EQUALS( KMceTestInitialContrast, iCameraWithoutManager->ContrastL() );
                       
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialContrast, camFlatData->iContrast );

    session->EstablishL();     

    EUNIT_ASSERT_EQUALS( KMceTestContrast, cam->ContrastL() );    
    EUNIT_ASSERT_EQUALS( KMceTestContrast, camFlatData->iContrast );

    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::SetBrightnessTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::SetBrightnessTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialBrightness, iCameraFlatData->iBrightness );
    
    iCamera->SetBrightnessL( KMceTestInitialBrightness + 1 );
    EUNIT_ASSERT_EQUALS( KMceTestInitialBrightness + 1, iCameraFlatData->iBrightness ); 
    
    iCamera->SetBrightnessL( CCamera::EBrightnessAuto );
    EUNIT_ASSERT_EQUALS( CCamera::EBrightnessAuto, iCameraFlatData->iBrightness ); 
    
    // Make adjusting brightness not supported
    static_cast<CMceComCameraSource*>( 
        iCamera->iFlatData )->iCameraInfo.iOptionsSupported = TCameraInfo::EViewFinderDirectSupported;
    TRAPD( err, iCamera->SetBrightnessL( 0 ) ); // Unsupported, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotSupported, err );
    
    // Make adjusting brightness supported, but try illegal values
    static_cast<CMceComCameraSource*>( 
        iCamera->iFlatData )->iCameraInfo.iOptionsSupported = TCameraInfo::EBrightnessSupported;
    TRAP( err, iCamera->SetBrightnessL( -101 ) ); // Illegal, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
    
    TRAP( err, iCamera->SetBrightnessL( 101 ) ); // Illegal, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrArgument, err );
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialBrightness, camFlatData->iBrightness );
    
    session->EstablishL();     
    
    cam->SetBrightnessL( KMceTestInitialBrightness + 1 );
    EUNIT_ASSERT_EQUALS( KMceTestInitialBrightness + 1, camFlatData->iBrightness );
    
    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE; 
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::BrightnessTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::BrightnessTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialBrightness, iCamera->BrightnessL() );
    EUNIT_ASSERT_EQUALS( KMceTestInitialBrightness, iCameraWithoutManager->BrightnessL() );
                       
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialBrightness, camFlatData->iBrightness );

    session->EstablishL();     

    EUNIT_ASSERT_EQUALS( KMceTestBrightness, cam->BrightnessL() );    
    EUNIT_ASSERT_EQUALS( KMceTestBrightness, camFlatData->iBrightness );

    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::SetExposureTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::SetExposureTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialExposure, iCameraFlatData->iExposure );
    
    iCamera->SetExposureL( CCamera::EExposureNight );
    EUNIT_ASSERT_EQUALS( CCamera::EExposureNight, iCameraFlatData->iExposure ); 
    
    // Make only EExposureAuto supported
    static_cast<CMceComCameraSource*>( 
        iCamera->iFlatData )->iCameraInfo.iExposureModesSupported = CCamera::EExposureAuto;
    TRAPD( err, iCamera->SetExposureL( CCamera::EExposureNight ) ); // Unsupported, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotSupported, err );
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialExposure, camFlatData->iExposure );
    
    session->EstablishL();     
    
    cam->SetExposureL( CCamera::EExposureNight );
    EUNIT_ASSERT_EQUALS( CCamera::EExposureNight, camFlatData->iExposure );
    
    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE; 
    
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::ExposureTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::ExposureTestL()
    {
    EUNIT_ASSERT( KMceTestInitialExposure == iCamera->ExposureL() );
    EUNIT_ASSERT( KMceTestInitialExposure == iCameraWithoutManager->ExposureL() );
                       
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialExposure, camFlatData->iExposure );

    session->EstablishL();     

    EUNIT_ASSERT_EQUALS( KMceTestExposure, cam->ExposureL() );    
    EUNIT_ASSERT_EQUALS( KMceTestExposure, camFlatData->iExposure );

    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::SetWhiteBalanceTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::SetWhiteBalanceTestL()
    {
    EUNIT_ASSERT_EQUALS( KMceTestInitialWhiteBalance, iCameraFlatData->iWhiteBalance );
    
    iCamera->SetWhiteBalanceL( CCamera::EWBDaylight );
    EUNIT_ASSERT_EQUALS( CCamera::EWBDaylight, iCameraFlatData->iWhiteBalance ); 
    
    // Make only EWBAuto supported
    static_cast<CMceComCameraSource*>( 
        iCamera->iFlatData )->iCameraInfo.iWhiteBalanceModesSupported = CCamera::EWBAuto;
    TRAPD( err, iCamera->SetWhiteBalanceL( CCamera::EWBDaylight ) ); // Unsupported, must leave;
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotSupported, err );
    
    // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialWhiteBalance, camFlatData->iWhiteBalance );
    
    session->EstablishL();     
    
    cam->SetWhiteBalanceL( CCamera::EWBDaylight );
    EUNIT_ASSERT_EQUALS( CCamera::EWBDaylight, camFlatData->iWhiteBalance );
    
    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE; 
    }  
    
    
// ----------------------------------------------------------------------------
// CMceCameraSourceTest::WhiteBalanceTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::WhiteBalanceTestL()
    {
    EUNIT_ASSERT( KMceTestInitialWhiteBalance == iCamera->WhiteBalanceL() );
    EUNIT_ASSERT( KMceTestInitialWhiteBalance == iCameraWithoutManager->WhiteBalanceL() );
    
        // Establish session
    MCE_CREATE_PROFILE;
    
    CMceOutSession* session = this->CreateCameraSessionLC( *profile );
    CMceCameraSource* cam = static_cast<CMceCameraSource*>(session->Streams()[0]->Source());
    CMceComCameraSource* camFlatData = static_cast<CMceComCameraSource*>(cam->iFlatData);
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialWhiteBalance, camFlatData->iWhiteBalance );

    session->EstablishL();     

    EUNIT_ASSERT_EQUALS( KMceTestExposure, cam->WhiteBalanceL() );    
    EUNIT_ASSERT_EQUALS( KMceTestExposure, camFlatData->iWhiteBalance );

    CleanupStack::PopAndDestroy( session );
    
    MCE_DELETE_PROFILE;
    }  
    

// ----------------------------------------------------------------------------
// CMceCameraSourceTest::InternalizeTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::InternalizeTestL()
    {
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();
    
    // Write base class data
    writeStream.WriteUint8L( KMceTestSourceType );
    writeStream.WriteUint8L( KMceTestCategory );
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( KMceTestEnabledFalse );
    
    // Write camera data
    writeStream.WriteInt32L( KMceTestInitialCameraIndex + 1 );
    writeStream.WriteInt32L( KMceTestInitialZoomFactor + 1 );
    writeStream.WriteInt32L( KMceTestInitialDigitalZoomFactor + 1 );
    writeStream.WriteInt32L( KMceTestInitialContrast + 1 );
    writeStream.WriteInt32L( KMceTestInitialBrightness + 1 );
    writeStream.WriteInt32L( TInt(CCamera::EExposureNight) );
    writeStream.WriteInt32L( TInt(CCamera::EWBDaylight) );
    writeStream.WriteInt32L( 2 ); // iCameraAvailable
    TCameraInfo cameraInfo;
    TPckgBuf<TCameraInfo> tcInfoBuf( cameraInfo );
    MceSerial::EncodeL( tcInfoBuf, writeStream );
    writeStream.WriteUint8L( ETrue );
    
	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    iCamera->InternalizeL( serCtx );
    
    EUNIT_ASSERT( iCamera->iFlatData->iType == KMceTestSourceType );
    EUNIT_ASSERT( iCamera->iFlatData->IsEnabled() == KMceTestEnabledFalse );
    EUNIT_ASSERT( iCamera->iFlatData->Id().iAppId == KMceTestAppId );
    EUNIT_ASSERT( iCamera->iFlatData->Id().iId == KMceTestMiscId );
    
    EUNIT_ASSERT_EQUALS( KMceTestInitialCameraIndex + 1, iCameraFlatData->iCameraIndex );
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor + 1, iCameraFlatData->iZoomFactor );
    EUNIT_ASSERT_EQUALS( KMceTestInitialDigitalZoomFactor + 1, iCameraFlatData->iDigitalZoomFactor );
    EUNIT_ASSERT_EQUALS( KMceTestInitialContrast + 1, iCameraFlatData->iContrast );
    EUNIT_ASSERT_EQUALS( KMceTestInitialBrightness + 1, iCameraFlatData->iBrightness );
    EUNIT_ASSERT_EQUALS( CCamera::EExposureNight, iCameraFlatData->iExposure );
    EUNIT_ASSERT_EQUALS( CCamera::EWBDaylight, iCameraFlatData->iWhiteBalance );
    EUNIT_ASSERT_EQUALS( 2, iCameraFlatData->iCamerasAvailable );
    EUNIT_ASSERT( iCameraFlatData->iInitialInfoRetrieved );
    
    CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();
    }
    

// ----------------------------------------------------------------------------
// CMceCameraSourceTest::ExternalizeTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::ExternalizeTestL()
    {
    iCamera->iFlatData->iID.iAppId = KMceTestAppId;
    iCamera->iFlatData->iID.iId = KMceTestMiscId; 
    iCamera->iFlatData->iType = KMceTestSourceType;
    iCamera->iFlatData->Enabled( KMceTestEnabledFalse );
    
    iCameraFlatData->iCameraIndex = KMceTestInitialCameraIndex + 1;
    iCameraFlatData->iZoomFactor = KMceTestInitialZoomFactor + 1;
    iCameraFlatData->iDigitalZoomFactor = KMceTestInitialDigitalZoomFactor + 1;
    iCameraFlatData->iContrast = KMceTestInitialContrast + 1;
    iCameraFlatData->iBrightness = KMceTestInitialBrightness + 1;
    iCameraFlatData->iExposure = CCamera::EExposureNight;
    iCameraFlatData->iWhiteBalance = CCamera::EWBDaylight;
    
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iCamera->ExternalizeL( serCtx );
	
    CleanupStack::PopAndDestroy();//serCtx
	writeStream.Close();
	writeStream.Pop();
	
	RDesReadStream readStream( buffer );
	readStream.PushL();
	
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestSourceType );
	EUNIT_ASSERT( KMceTestAppId == readStream.ReadUint32L() );
	EUNIT_ASSERT( KMceTestMiscId == readStream.ReadUint32L() );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestEnabledFalse );
	
	EUNIT_ASSERT_EQUALS( KMceTestInitialCameraIndex + 1, readStream.ReadUint32L() );
    EUNIT_ASSERT_EQUALS( KMceTestInitialZoomFactor + 1, readStream.ReadUint32L() );
    EUNIT_ASSERT_EQUALS( KMceTestInitialDigitalZoomFactor + 1, readStream.ReadUint32L() );
    EUNIT_ASSERT_EQUALS( KMceTestInitialContrast + 1, readStream.ReadUint32L() );
    EUNIT_ASSERT_EQUALS( KMceTestInitialBrightness + 1, readStream.ReadUint32L() );
    EUNIT_ASSERT_EQUALS( CCamera::EExposureNight, readStream.ReadUint32L() );
    EUNIT_ASSERT_EQUALS( CCamera::EWBDaylight, readStream.ReadUint32L() );
	
	readStream.Close();
	readStream.Pop();
    }


// ----------------------------------------------------------------------------
// CMceCameraSourceTest::GetITCValueTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::GetITCValueTestL()
    {
    // Successfull case has been tested with getters, so just try without session
    TRAPD( err, iCamera->GetITCValueL( EMceItcWhiteBalance ) );

    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
    }
    

// ----------------------------------------------------------------------------
// CMceCameraSourceTest::SetITCValueTestL 
// ----------------------------------------------------------------------------
//
void CMceCameraSourceTest::SetITCValueTestL()
    {
    // Successfull case has been tested with getters, so just try without session
    TRAPD( err, iCamera->SetITCValueL( EMceItcSetWhiteBalance, 
                                       CCamera::EWBDaylight ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err )
	EUNIT_ASSERT_EQUALS( KErrNotReady, err );
    }

// ----------------------------------------------------------------------------
// CMceCameraSourceTest::CreateCameraSessionLC 
// Creates a session with one video stream with camera source and rtp sink.
// Leaves instance on cleanupstack.
// ----------------------------------------------------------------------------
//
CMceOutSession* CMceCameraSourceTest::CreateCameraSessionLC( CSIPProfile& aProfile )
    {
    CMceOutSession* session = CMceOutSession::NewL( *iManager, aProfile, KMceRecipient );
    CleanupStack::PushL( session );
    
    CMceVideoStream* stream = CMceVideoStream::NewLC();
    
    CMceCameraSource* cam = CMceCameraSource::NewLC( *iManager );
    stream->SetSourceL( cam );
    CleanupStack::Pop( cam );
    
    CMceRtpSink* rtp = CMceRtpSink::NewLC();
    stream->AddSinkL( rtp );
    CleanupStack::Pop( rtp );
    
    session->AddStreamL( stream );
    CleanupStack::Pop( stream );
    
    return session;
    }
