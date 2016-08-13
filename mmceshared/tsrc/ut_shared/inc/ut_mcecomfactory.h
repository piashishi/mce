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




#ifndef __UT_MCECOMFACTORY_H__
#define __UT_MCECOMFACTORY_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_MceComFactory : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_MceComFactory* NewL();
    static UT_MceComFactory* NewLC();
    ~UT_MceComFactory();

private:    // Constructors and destructors

    UT_MceComFactory();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_MceComFactory_CMceComMediaStream_CreateLCL();
    void UT_MceComFactory_CMceComMediaStream_CreateLC1L();
    void UT_MceComFactory_CMceComMediaSource_CreateLCL();
    void UT_MceComFactory_CMceComMediaSource_CreateLC1L();
    void UT_MceComFactory_CMceComMediaSink_CreateLCL();
    void UT_MceComFactory_CMceComMediaSink_CreateLC1L();
    void UT_MceComFactory_CMceComAudioCodec_CreateLCL();
    void UT_MceComFactory_CMceComAudioCodec_CreateLC1L();
    void UT_MceComFactory_CMceComAudioCodec_CreateCodecLCL();
    void UT_MceComFactory_CMceComAudioCodec_CreateCodecLC1L();
    void UT_MceComFactory_CMceComVideoCodec_CreateLCL();
    void UT_MceComFactory_CMceComVideoCodec_CreateLC1L();
    void UT_MceComFactory_CMceComVideoCodec_CreateCodecLCL();
    void UT_MceComFactory_CMceComVideoCodec_CreateCodecLC1L();
    void UT_MceComFactory_CMceComSession_CreateLCL();
    void UT_MceComFactory_CMceMsgBase_CreateLL();
    void UT_MceComFactory_CMceMsgBase_CreateL1L();
    void UT_MceComFactory_CreateBundleLCL();
    void UT_MceComFactory_CreateLCL();
    void UT_MceComFactory_MediaStreamFactoryL();
    void UT_MceComFactory_SourceFactoryL();
    void UT_MceComFactory_SinkFactoryL();
    void UT_MceComFactory_AudioCodecFactoryL();
    void UT_MceComFactory_VideoCodecFactoryL();

private:    // Data

	CMccCodecInformationFactory* iCodecFactory;
    TMceComAudioCodecFactory iAudioFactory;
    TMceComVideoCodecFactory iVideoFactory;

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_MCECOMFACTORY_H__

// End of file
