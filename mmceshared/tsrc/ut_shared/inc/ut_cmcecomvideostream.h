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




#ifndef __UT_CMCECOMVIDEOSTREAM_H__
#define __UT_CMCECOMVIDEOSTREAM_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComVideoStream;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComVideoStream : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComVideoStream* NewL();
    static UT_CMceComVideoStream* NewLC();
    ~UT_CMceComVideoStream();

private:    // Constructors and destructors

    UT_CMceComVideoStream();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComVideoStream_AddCodecLL();
    void UT_CMceComVideoStream_RemoveCodecLL();
    void UT_CMceComVideoStream_FindCodecLL();
    void UT_CMceComVideoStream_InternalizeFlatLL();
    void UT_CMceComVideoStream_ExternalizeFlatLL();
    void UT_CMceComVideoStream_InternalizeLL();
    void UT_CMceComVideoStream_ExternalizeLL();
    void UT_CMceComVideoStream_InitializeLL();
    void UT_CMceComVideoStream_UpdateLL();
    void UT_CMceComVideoStream_CloneLL();
    void UT_CMceComVideoStream_SynchronizeLL();
    void UT_CMceComVideoStream_PrepareLL();
    void UT_CMceComVideoStream_MccStreamTypeL();
    void UT_CMceComVideoStream_MccLinkTypeL();
		void UT_CMceComVideoStream_FindCodecFromListL();
		void UT_CMceComVideoStream_RemoveCodecFromListLL();
		void UT_CMceComVideoStream_DestroyCodecsL();
		void UT_CMceComVideoStream_CodecLL();
		
private:    // Data

		CMceMediaManager* iManager;
    CMceServerStub* iServer;

    CMceComSession* iSession;
    CMceComMediaSource* iSource;
    CMceComMediaSink* iSink;
    CMceComVideoStream* iStream;
    CMceComVideoCodec* iCodecH263;
	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMVIDEOSTREAM_H__

// End of file
