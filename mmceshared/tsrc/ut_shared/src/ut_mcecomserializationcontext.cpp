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
#include "ut_.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_ADDCLASSHERE* UT_ADDCLASSHERE::NewL()
    {
    UT_ADDCLASSHERE* self = UT_ADDCLASSHERE::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_ADDCLASSHERE* UT_ADDCLASSHERE::NewLC()
    {
    UT_ADDCLASSHERE* self = new( ELeave ) UT_ADDCLASSHERE();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_ADDCLASSHERE::~UT_ADDCLASSHERE()
    {
    }

// Default constructor
UT_ADDCLASSHERE::UT_ADDCLASSHERE()
    {
    }

// Second phase construct
void UT_ADDCLASSHERE::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_ADDCLASSHERE::SetupL()
    {
    iManager = CMceMediaManager::NewL( *iServer );
    
    } 

void UT_ADDCLASSHERE::Teardown()
    {
	delete iManager;
	iManager = NULL;
    }




	
//  TEST TABLE




//  END OF FILE
