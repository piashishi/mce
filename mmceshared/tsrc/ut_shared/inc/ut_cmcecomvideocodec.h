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




#ifndef __UT_CMCECOMVIDEOCODEC_H__
#define __UT_CMCECOMVIDEOCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComVideoCodec;
class CMceMediaManager;
class CMceComSession;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComVideoCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComVideoCodec* NewL();
    static UT_CMceComVideoCodec* NewLC();
    ~UT_CMceComVideoCodec();

private:    // Constructors and destructors

    UT_CMceComVideoCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Setup2L();
     void Teardown();
     void Teardown2();

private:    // Test methods
    
    void UT_CMceComVideoCodec_InternalizeFlatLL();
    void UT_CMceComVideoCodec_ExternalizeFlatLL();
    void UT_CMceComVideoCodec_UpdateLL();
    void UT_CMceComVideoCodec_CloneLL();
    void UT_CMceComVideoCodec_FactoryL();
    void UT_CMceComVideoCodec_operatorAssignL();
    void UT_CMceComVideoCodec_DoMccDecodeLL();
    void UT_CMceComVideoCodec_DoMccEncodeLL();
    void UT_CMceComVideoCodec_DoMccValidateLL();
    void UT_CMceComVideoCodec_DoMccAdjustLL();
    void UT_CMceComVideoCodec_DoMccRequireSignallingL();
    void UT_CMceComVideoCodec_DoSetDefaultFmtpAttributeLL();
    void UT_CMceComVideoCodec_GetMaxBitRateL();
    void UT_CMceComVideoCodec_SetMaxBitrateL();
    void UT_CMceComVideoCodec_SetConfigKeyLL();
    void UT_CMceComVideoCodec_IsConfigKeyValidL();

    
                             

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    CMceComVideoCodec* iCodec;
    
    CMceComSession* iSession;
	CMceComVideoCodec* iSendCodec;
	CMceComVideoCodec* iReceiveCodec;
    
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMVIDEOCODEC_H__

// End of file
