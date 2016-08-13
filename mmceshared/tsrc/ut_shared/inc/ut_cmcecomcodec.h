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




#ifndef __UT_CMCECOMCODEC_H__
#define __UT_CMCECOMCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComCodec;
class CMceMediaManager;
class CMccCodecInformationFactory;
class CMceComSession;
class CMceComMediaSource;
class CMceComMediaSink;
class CMceComAudioStream;
class CMceComAudioCodec;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComCodec* NewL();
    static UT_CMceComCodec* NewLC();
    ~UT_CMceComCodec();

private:    // Constructors and destructors

    UT_CMceComCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
	void UT_CMceComCodec_IdL();
	void UT_CMceComCodec_StreamL();
    void UT_CMceComCodec_SetFmtpAttributeLL();
    void UT_CMceComCodec_SetKeepAliveDataLL();
    void UT_CMceComCodec_SetBitrateL();
    void UT_CMceComCodec_SetAllowedBitratesL();
    void UT_CMceComCodec_SetCodecModeL();
    void UT_CMceComCodec_SetPayloadTypeL();
    void UT_CMceComCodec_GetMaxBitRateL();
    void UT_CMceComCodec_SerializationIdL();
    void UT_CMceComCodec_InternalizeExternalizeFlatLL();
    void UT_CMceComCodec_InternalizeExternalizeLL();
    void UT_CMceComCodec_UpdateLL();
    void UT_CMceComCodec_DecodesL();
    void UT_CMceComCodec_InitializeLL();
    void UT_CMceComCodec_SynchronizeLL();
    void UT_CMceComCodec_EventReceivedLL();
    void UT_CMceComCodec_ResolveAllowedBitratesL();
    void UT_CMceComCodec_BaseFactoryL();
    void UT_CMceComCodec_operatorAssignL();
    void UT_CMceComCodec_MccDecodeLL();
    void UT_CMceComCodec_MccPopulateLL();
    void UT_CMceComCodec_MccValidateLL();
    void UT_CMceComCodec_DoMccValidateLL();
    void UT_CMceComCodec_MccAdjustLL();
    void UT_CMceComCodec_MccRequireSignallingL();
    void UT_CMceComCodec_SetStateL();
    void UT_CMceComCodec_SetDefaultFmtpAttributeLL();
    void UT_CMceComCodec_FmtpAttrL();


private:    // Data

    
    CMccCodecInformationFactory* iCodecFactory;
    
    CMceMediaManager* iManager;
    CMceServerStub* iServer;
    
    CMceComSession* iSession;
    CMceComMediaSource* iSource;
    CMceComMediaSink* iSink;
    CMceComAudioStream* iStream;
    CMceComAudioCodec* iCodec;
    
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMCODEC_H__

// End of file
