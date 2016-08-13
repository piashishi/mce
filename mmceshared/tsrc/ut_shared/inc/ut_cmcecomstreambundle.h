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




#ifndef __UT_CMCECOMSTREAMBUNDLE_H__
#define __UT_CMCECOMSTREAMBUNDLE_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcecommontesthelper.h"

#pragma warn_illtokenpasting off

//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class CMceComStreamBundle;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceComStreamBundle : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_CMceComStreamBundle* NewL();
    static UT_CMceComStreamBundle* NewLC();
    ~UT_CMceComStreamBundle();

private:    // Constructors and destructors

    UT_CMceComStreamBundle();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_CMceComStreamBundle_TypeL();
    void UT_CMceComStreamBundle_AddStreamLL();
    void UT_CMceComStreamBundle_RemoveStreamLL();
	void UT_CMceComStreamBundle_StreamsL();
    void UT_CMceComStreamBundle_AddedLL();
    void UT_CMceComStreamBundle_SerializationIdL();
    void UT_CMceComStreamBundle_InternalizeFlatLL();
    void UT_CMceComStreamBundle_ExternalizeFlatLL();
    void UT_CMceComStreamBundle_InternalizeLL();
    void UT_CMceComStreamBundle_ExternalizeLL();
	void UT_CMceComStreamBundle_IdL();
    void UT_CMceComStreamBundle_BaseFactoryL();
    void UT_CMceComStreamBundle_InitializeLL();
    void UT_CMceComStreamBundle_UpdateLL();
    void UT_CMceComStreamBundle_CloneL();
    void UT_CMceComStreamBundle_CloneL1L();


private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;
	

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_CMCECOMSTREAMBUNDLE_H__

// End of file
