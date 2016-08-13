/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#include <CppUnit/TestSuite.h>
#include "CTstNameValue.h"
#include "CTstArray.h"
#include "CTstStructure.h"
#include "CTstParameterList.h"
#include "CTstRegistry.h"
#include "CTstCtrlCodec.h"

#ifndef EKA2
// Starting point of the DLL (Removed in EKA2) 
GLDEF_C TInt E32Dll(TDllReason)
	{
	return(KErrNone);
	}
#endif

EXPORT_C MTest* CreateTestL()
	{
	// Always use NewL (Do not use NewLC) !!!
	CTestSuite *suite = CTestSuite::NewL( _L8("Module test suite") );
 
	suite->addTestL( CTstNameValue::suiteL() );
	suite->addTestL( CTstArray::suiteL() );
	suite->addTestL( CTstStructure::suiteL() );
	suite->addTestL( CTstParameterList::suiteL() );
	suite->addTestL( CTstRegistry::suiteL() );
	suite->addTestL( CTstCtrlCodec::suiteL() );

	return suite;
	}

