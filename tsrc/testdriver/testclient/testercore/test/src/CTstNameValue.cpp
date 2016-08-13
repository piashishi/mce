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
#include <CppUnit/TestCaller.h>
#include <CppUnit/TestSuite.h>

#include "CTstNameValue.h"
#include "CTcNameValue.h"

_LIT8( KTestName1, "RemoteURI" );
_LIT8( KTestName2, "Refresh" );
_LIT8( KTestValue1, "<sip:joku@jossain.net>" );
_LIT8( KTestValue2, "10" );
const TInt KTestValueInt( 10 );

void CTstNameValue::setUpL()
	{
	}

void CTstNameValue::tearDown()
	{
	}

void CTstNameValue::TestConstructorL()
	{
	CTcNameValue* tv = CTcNameValue::NewLC();
	assertTDesC8sEqualL( KNullDesC8, tv->Name() );
	assertTDesC8sEqualL( KNullDesC8, tv->Value() );
	CleanupStack::PopAndDestroy( tv );
	}

void CTstNameValue::TestSettersGettersL()
	{
	CTcNameValue* tv = CTcNameValue::NewLC();

	// Set name & value at once
	tv->SetL( KTestName1, KTestValue1 );
	assertTDesC8sEqualL( KTestName1, tv->Name() );
	assertTDesC8sEqualL( KTestValue1, tv->Value() );
	tv->SetL( KTestName2, KTestValueInt );
	assertTDesC8sEqualL( KTestName2, tv->Name() );
	assertTDesC8sEqualL( KTestValue2, tv->Value() );

	// Set name & value separately
	tv->SetNameL( KTestName2 );
	assertTDesC8sEqualL( KTestName2, tv->Name() );
	tv->SetValueL( KTestValue2 );
	assertTDesC8sEqualL( KTestValue2, tv->Value() );

	// Integer set / get
	tv->SetValueL( KTestValue2 );
	assertL( tv->ValueAsInt() == KTestValueInt );
	tv->SetValueL( KTestValueInt );
	assertL( tv->ValueAsInt() == KTestValueInt );
	tv->SetValueL( KTestValue1 );
	assertL( tv->ValueAsInt() == 0 );

	CleanupStack::PopAndDestroy( tv );
	}

//
// An own static function to collect the test functions into one 
// suite of tests. The framework will run the tests and free the
// memory allocated for the test suite.
// 
MTest* CTstNameValue::suiteL()
	{
	// Always use NewL (Do not use NewLC) !!!
    CTestSuite *suite = CTestSuite::NewL( _L8("CTstNameValue") );
    
    suite->addTestL(
		CTestCaller< CTstNameValue >::NewL(	_L8("TestConstructorL"), &TestConstructorL ) );

	suite->addTestL(
		CTestCaller< CTstNameValue >::NewL(	_L8("TestSettersGettersL"), &TestSettersGettersL ) );

	return suite;
	}
