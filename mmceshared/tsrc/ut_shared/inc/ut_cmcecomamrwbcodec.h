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




#ifndef __UT_CMCECOMAMRWBCODEC_H__
#define __UT_CMCECOMAMRWBCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS
class CMceComAMRWbCodec;
class CMceComAMRCodec;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComAMRWbCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComAMRWbCodec* NewL();
    static UT_CMceComAMRWbCodec* NewLC();
    ~UT_CMceComAMRWbCodec();

private:    // Constructors and destructors

    UT_CMceComAMRWbCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComAMRWbCodec_SetBitrateL();
    void UT_CMceComAMRWbCodec_SetAllowedBitratesL();
    void UT_CMceComAMRWbCodec_GetMaxBitRateL();
    void UT_CMceComAMRWbCodec_ResolveAllowedBitratesL();
    void UT_CMceComAMRWbCodec_DoMccValidateLL();
    void UT_CMceComAMRWbCodec_DoSetDefaultFmtpAttributeLL();
    void UT_CMceComAMRWbCodec_CloneLL();
    
private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    CMceComAMRWbCodec* iCodec;
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMceComAMRWbCodec_H__

// End of file
