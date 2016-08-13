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




#ifndef __UT_CMCECOMDTFMCODEC_H__
#define __UT_CMCECOMDTFMCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComDtmfCodec;
class CMceMediaManager;
class CMceComAudioCodec;
class CMceComSession;
class CMceComMediaSource;
class CMceComMediaSink;
class CMceComAudioStream;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComDtmfCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComDtmfCodec* NewL();
    static UT_CMceComDtmfCodec* NewLC();
    ~UT_CMceComDtmfCodec();

private:    // Constructors and destructors

    UT_CMceComDtmfCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComDtmfCodec_SetBitrateL();
    void UT_CMceComDtmfCodec_SetAllowedBitratesL();
    void UT_CMceComDtmfCodec_SetCodecModeL();
    void UT_CMceComDtmfCodec_SetPayloadTypeL();
    void UT_CMceComDtmfCodec_GetMaxBitRateL();
    void UT_CMceComDtmfCodec_DoMccValidateLL();
    void UT_CMceComDtmfCodec_CloneLL();

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    
    CMceComSession* iSession;
    CMceComMediaSource* iDownlinkSource;
    CMceComMediaSink* iDownlinkSink;
    CMceComAudioStream* iDownlinkStream;
    CMceComMediaSource* iUplinkSource;
    CMceComMediaSink* iUplinkSink;
    CMceComAudioStream* iUplinkStream;
    CMceComAudioCodec* iCodec;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMDTFMCODEC_H__

// End of file
