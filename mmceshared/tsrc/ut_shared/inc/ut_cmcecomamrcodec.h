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




#ifndef __UT_CMCECOMAMRCODEC_H__
#define __UT_CMCECOMAMRCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComAMRCodec;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComAMRCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComAMRCodec* NewL();
    static UT_CMceComAMRCodec* NewLC();
    ~UT_CMceComAMRCodec();

private:    // Constructors and destructors

    UT_CMceComAMRCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComAMRCodec_SetBitrateL();
    void UT_CMceComAMRCodec_SetAllowedBitratesL();
    void UT_CMceComAMRCodec_SetCodecModeL();
    void UT_CMceComAMRCodec_SetPayloadTypeL();
    void UT_CMceComAMRCodec_GetMaxBitRateL();
    void UT_CMceComAMRCodec_ResolveAllowedBitratesL();
    void UT_CMceComAMRCodec_SetSamplingFreqL();
    void UT_CMceComAMRCodec_SetPTimeL();
    void UT_CMceComAMRCodec_SetMaxPTimeL();
    void UT_CMceComAMRCodec_DoMccValidateLL();
    void UT_CMceComAMRCodec_DoSetDefaultFmtpAttributeLL();
    void UT_CMceComAMRCodec_CloneLL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    CMceComAMRCodec* iCodec;
    
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMAMRCODEC_H__

// End of file
