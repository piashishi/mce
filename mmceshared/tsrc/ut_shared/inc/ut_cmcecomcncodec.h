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




#ifndef __UT_CMCECOMCNCODEC_H__
#define __UT_CMCECOMCNCODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComCnCodec;
class CMceMediaManager;
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
class UT_CMceComCnCodec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComCnCodec* NewL();
    static UT_CMceComCnCodec* NewLC();
    ~UT_CMceComCnCodec();

private:    // Constructors and destructors

    UT_CMceComCnCodec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComCnCodec_SetBitrateL();
    void UT_CMceComCnCodec_SetAllowedBitratesL();
    void UT_CMceComCnCodec_GetMaxBitRateL();
    void UT_CMceComCnCodec_CloneLL();
    void DoMccEncodeL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    
    CMceComSession* iSession;
    CMceComMediaSource* iSource;
    CMceComMediaSink* iSink;
    CMceComAudioStream* iStream;
    CMceComAudioCodec* iOtherCodec;
    CMceComAudioCodec* iCnCodec;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMCNCODEC_H__

// End of file
