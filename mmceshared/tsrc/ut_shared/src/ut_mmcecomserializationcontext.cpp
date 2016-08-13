/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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




//  CLASS HEADER
#include "ut_mmcecomserializationcontext.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_MMceComSerializationContext* UT_MMceComSerializationContext::NewL()
    {
    UT_MMceComSerializationContext* self = UT_MMceComSerializationContext::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_MMceComSerializationContext* UT_MMceComSerializationContext::NewLC()
    {
    UT_MMceComSerializationContext* self = new( ELeave ) UT_MMceComSerializationContext();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_MMceComSerializationContext::~UT_MMceComSerializationContext()
    {
    }

// Default constructor
UT_MMceComSerializationContext::UT_MMceComSerializationContext()
    {
    }

// Second phase construct
void UT_MMceComSerializationContext::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_MMceComSerializationContext::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_MMceComSerializationContext::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_MMceComSerializationContext::UT_MMceComSerializationContext_IsCachedL()
    {
    }


	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_MMceComSerializationContext,
    "MMceComSerializationContext tests",
    "UNIT" )

EUNIT_TEST (
    "IsCached test",
    "MMceComSerializationContext",
    "IsCached",
    "FUNCTIONALITY",
    SetupL, UT_MMceComSerializationContext_IsCachedL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
