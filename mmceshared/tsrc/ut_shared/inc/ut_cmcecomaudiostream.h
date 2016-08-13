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




#ifndef __UT_CMCECOMAUDIOSTREAM_H__
#define __UT_CMCECOMAUDIOSTREAM_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

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
class UT_CMceComAudioStream : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComAudioStream* NewL();
    static UT_CMceComAudioStream* NewLC();
    ~UT_CMceComAudioStream();

private:    // Constructors and destructors

    UT_CMceComAudioStream();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComAudioStream_AddCodecLL();
    void UT_CMceComAudioStream_RemoveCodecLL();
    void UT_CMceComAudioStream_FindCodecLL();
    void UT_CMceComAudioStream_InternalizeFlatLL();
    void UT_CMceComAudioStream_ExternalizeFlatLL();
    void UT_CMceComAudioStream_InternalizeLL();
    void UT_CMceComAudioStream_ExternalizeLL();
    void UT_CMceComAudioStream_InitializeLL();
    void UT_CMceComAudioStream_UpdateLL();
    void UT_CMceComAudioStream_CloneLL();
    void UT_CMceComAudioStream_SynchronizeLL();
    void UT_CMceComAudioStream_PrepareLL();
    void UT_CMceComAudioStream_MccStreamTypeL();
    void UT_CMceComAudioStream_MccLinkTypeL();
    void UT_CMceComAudioStream_UpdateDefaultCodecL();
		void UT_CMceComAudioStream_FindCodecFromListL();
		void UT_CMceComAudioStream_RemoveCodecFromListLL();
		void UT_CMceComAudioStream_DestroyCodecsL();
		void UT_CMceComAudioStream_CodecLL();

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
    
    CMceComSession* iSession;
    CMceComMediaSource* iSource;
    CMceComMediaSink* iSink;
    CMceComAudioStream* iStream;
    CMceComAudioCodec* iCodecAmr;
    CMceComAudioCodec* iCodecCn;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMAUDIOSTREAM_H__

// End of file
