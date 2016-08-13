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




#ifndef __UT_CMCECOMH263CODEC_H__
#define __UT_CMCECOMH263CODEC_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>

#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComH263Codec;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComH263Codec : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComH263Codec* NewL();
    static UT_CMceComH263Codec* NewLC();
    ~UT_CMceComH263Codec();

private:    // Constructors and destructors

    UT_CMceComH263Codec();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
     
    void UT_CMceComH263Codec_NewLL();
    void UT_CMceComH263Codec_SetBitrateL();
    void UT_CMceComH263Codec_SetAllowedBitratesL();
    void UT_CMceComH263Codec_GetMaxBitRateL();
    void UT_CMceComH263Codec_SetMaxBitrateL();
    void UT_CMceComH263Codec_ResolveAllowedBitratesL();
    void UT_CMceComH263Codec_CloneLL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    CMceComH263Codec* iCodec;
    
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMH263CODEC_H__

// End of file
