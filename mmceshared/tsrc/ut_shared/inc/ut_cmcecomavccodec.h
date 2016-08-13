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




#ifndef __UT_CMCECOMAVCCODEC_H__
#define __UT_CMCECOMAVCCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>

#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComAvcCodec;
class CMceMediaManager;
class CMceComSession;
class CMceComVideoCodec;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComAvcCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComAvcCodec* NewL();
    static UT_CMceComAvcCodec* NewLC();
    ~UT_CMceComAvcCodec();

private:    // Constructors and destructors

    UT_CMceComAvcCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Setup2L();
     void Teardown();
     void Teardown2();

private:    // Test methods
    
    
    void UT_CMceComAvcCodec_NewLL();
    void UT_CMceComAvcCodec_SetBitrateL();
    void UT_CMceComAvcCodec_SetAllowedBitratesL();
    void UT_CMceComAvcCodec_GetMaxBitRateL();
    void UT_CMceComAvcCodec_SetMaxBitrateL();
    void UT_CMceComAvcCodec_ResolveAllowedBitratesL();
    void UT_CMceComAvcCodec_CloneLL();
    void UT_CMceComAvcCodec_DecodesL();
    void UT_CMceComAvcCodec_SetFmtpProposalLL();
    void UT_CMceComAvcCodec_SetFmtpFromIncomingSdpLL();
    void UT_CMceComAvcCodec_SetFmtpFromIncomingSdpL2L();
    void UT_CMceComAvcCodec_FtmpForOutgoingSdpLCL();

private:    // Data

	CMceMediaManager* iManager;
	CMceServerStub* iServer;
	CMceComAvcCodec* iCodec;
	
	CMceComSession* iSession;
	CMceComVideoCodec* iSendCodec;
	CMceComVideoCodec* iReceiveCodec;
	
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMAVCCODEC_H__

// End of file
