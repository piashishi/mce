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




#ifndef __UT_CMCECOMREDCODEC_H__
#define __UT_CMCECOMREDCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComRedCodec;
class CMceMediaManager;
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
class UT_CMceComRedCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComRedCodec* NewL();
    static UT_CMceComRedCodec* NewLC();
    ~UT_CMceComRedCodec();

private:    // Constructors and destructors

    UT_CMceComRedCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Setup2L();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComRedCodec_SetBitrateL();
    void UT_CMceComRedCodec_SetAllowedBitratesL();
    void UT_CMceComRedCodec_SetPayloadTypeL();
    void UT_CMceComRedCodec_GetMaxBitRateL();
    void UT_CMceComRedCodec_CloneLL();
    void UT_CMceComRedCodec_DoDecodeAudioLL();
    void UT_CMceComRedCodec_DoDecodeAudioL2L();

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    
    CMceComSession* iSession;
    CMceComMediaSource* iSource;
    CMceComMediaSink* iSink;
    CMceComAudioStream* iStream;
    CMceComRedCodec* iCodec;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMREDCODEC_H__

// End of file
