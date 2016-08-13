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




#ifndef __UT_CMCECOMILBCCODEC_H__
#define __UT_CMCECOMILBCCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComiLBCCodec;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComiLBCCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComiLBCCodec* NewL();
    static UT_CMceComiLBCCodec* NewLC();
    ~UT_CMceComiLBCCodec();

private:    // Constructors and destructors

    UT_CMceComiLBCCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods

    void UT_CMceComiLBCCodec_SetBitrateL();
    void UT_CMceComiLBCCodec_SetAllowedBitratesL();
    void UT_CMceComiLBCCodec_SetCodecModeL();
    void UT_CMceComiLBCCodec_SetPayloadTypeL();
    void UT_CMceComiLBCCodec_GetMaxBitRateL();
    void UT_CMceComiLBCCodec_SetPTimeL();
    void UT_CMceComiLBCCodec_SetMaxPTimeL();
    void UT_CMceComiLBCCodec_DoMccEncodeLL();
    void UT_CMceComiLBCCodec_DoMccValidateLL();
    void UT_CMceComiLBCCodec_DoMccAdjustLL();
    void UT_CMceComiLBCCodec_DoSetDefaultFmtpAttributeLL();   
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    CMceComiLBCCodec* iCodec;
    
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMILBCCODEC_H__

// End of file
