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


#ifndef __MCE_CAMERASOURCE_TEST_H__
#define __MCE_CAMERASOURCE_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceManager;
class CMceCameraSource;
class CMCEThreadLocalStorage;
class CMceComCameraSource;
class CMceOutSession;
class CSIPProfile;

class CMceCameraSourceTest: public CEUnitTestSuiteClass
	{
public:

    inline CMceCameraSourceTest()  {}
    inline ~CMceCameraSourceTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void ConstructionTestL();
    void EnableTestL();
    void DisableTestL();
    void CamerasAvailableTestL();
    void SetCameraIndexTestL();
    void GetCameraInfoTestL();
    void SetZoomFactorTestL();
    void ZoomFactorTestL();
    void SetDigitalZoomFactorTestL();
    void DigitalZoomFactorTestL();
    void SetContrastTestL();
    void ContrastTestL();
    void SetBrightnessTestL();
    void BrightnessTestL();
    void SetExposureTestL();
    void ExposureTestL();
    void SetWhiteBalanceTestL();
    void WhiteBalanceTestL();
    void InternalizeTestL();
    void ExternalizeTestL();
    void GetITCValueTestL();
    void SetITCValueTestL();   

private: // Helper function    
    
    CMceOutSession* CreateCameraSessionLC( CSIPProfile& aProfile ); // Transfers ownership 
    
private://data

    TUid iUid;
    CMCEThreadLocalStorage* iStorage;
    CMceManager* iManager;
    CMceCameraSource* iCamera;
    CMceComCameraSource* iCameraFlatData; // Owned by iCamera
    CMceCameraSource* iCameraWithoutManager; 
    
    EUNIT_DECLARE_TEST_TABLE;
    
};

#endif // __MCE_CAMERASOURCE_TEST_H__
