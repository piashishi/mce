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




#ifndef __UT_CMCECOMG711CODEC_H__
#define __UT_CMCECOMG711CODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComG711Codec;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComG711Codec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComG711Codec* NewL();
    static UT_CMceComG711Codec* NewLC();
    ~UT_CMceComG711Codec();

private:    // Constructors and destructors

    UT_CMceComG711Codec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComG711Codec_SetBitrateL();
    void UT_CMceComG711Codec_SetAllowedBitratesL();
    void UT_CMceComG711Codec_SetCodecModeL();
    void UT_CMceComG711Codec_GetMaxBitRateL();
    void UT_CMceComG711Codec_SetPTimeL();
    void UT_CMceComG711Codec_SetMaxPTimeL();
    void UT_CMceComG711Codec_CloneLL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    CMceComG711Codec* iCodec;
    
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMG711CODEC_H__

// End of file
