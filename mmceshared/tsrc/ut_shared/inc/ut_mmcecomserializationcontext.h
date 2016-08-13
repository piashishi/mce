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




#ifndef __UT_MMCECOMSERIALIZATIONCONTEXT_H__
#define __UT_MMCECOMSERIALIZATIONCONTEXT_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>
#pragma warn_illtokenpasting off
#include "mcecommontesthelper.h"


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class MMceComSerializationContext;
class CMceMediaManager;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_MMceComSerializationContext : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_MMceComSerializationContext* NewL();
    static UT_MMceComSerializationContext* NewLC();
    ~UT_MMceComSerializationContext();

private:    // Constructors and destructors

    UT_MMceComSerializationContext();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    
    void UT_MMceComSerializationContext_IsCachedL();
    

private:    // Data

	CMceMediaManager* iManager;
    CMceServerStub* iServer;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT_MMCECOMSERIALIZATIONCONTEXT_H__

// End of file
