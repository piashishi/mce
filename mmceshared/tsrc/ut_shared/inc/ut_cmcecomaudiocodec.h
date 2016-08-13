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




#ifndef __UT_CMCECOMAUDIOCODEC_H__
#define __UT_CMCECOMAUDIOCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComAudioCodec;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComAudioCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComAudioCodec* NewL();
    static UT_CMceComAudioCodec* NewLC();
    ~UT_CMceComAudioCodec();

private:    // Constructors and destructors

    UT_CMceComAudioCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComAudioCodec_SetSamplingFreqL();
    void UT_CMceComAudioCodec_SetPTimeL();
    void UT_CMceComAudioCodec_SetMaxPTimeL();
    void UT_CMceComAudioCodec_InternalizeFlatLL();
    void UT_CMceComAudioCodec_ExternalizeFlatLL();
    void UT_CMceComAudioCodec_UpdateLL();
    void UT_CMceComAudioCodec_CloneLL();
    void UT_CMceComAudioCodec_FactoryL();
    void UT_CMceComAudioCodec_operatorAssignL();
    void UT_CMceComAudioCodec_DoMccDecodeLL();
    void UT_CMceComAudioCodec_DoMccEncodeLL();
    void UT_CMceComAudioCodec_DoMccValidateLL();
    void UT_CMceComAudioCodec_DoMccAdjustLL();
    void UT_CMceComAudioCodec_DoMccRequireSignallingL();
    void UT_CMceComAudioCodec_DoSetDefaultFmtpAttributeLL();
    void UT_CMceComAudioCodec_DoMccEncodeComfortNoiseLL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    CMceComAudioCodec* iCodec;
    
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMAUDIOCODEC_H__

// End of file
