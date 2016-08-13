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

#include "CTstStructure.h"
#include "CTcStructure.h"

_LIT8( KTestStructureName, "Ids" );
_LIT8( KTestItem1Name, "ContactId" );
const TInt KTestItem1Value( 249587 );
_LIT8( KTestItem1ValueAsStr, "249587" );
_LIT8( KTestItem2Name, "ConnectionId" );
const TInt KTestItem2Value( 10002 );
_LIT8( KTestItem2ValueAsStr, "10002" );
_LIT8( KTestBogusItem, "abba" );

void CTstStructure::setUpL()
	{
	iStructure = CTcStructure::NewLC();
	CleanupStack::Pop();
	}

void CTstStructure::tearDown()
	{
	delete iStructure;
	}

void CTstStructure::TestConstructorL()
	{
	// Create structure
	CTcStructure* structure = CTcStructure::NewLC();

	// Verify correct initialization
	assertL( structure->ParameterType() == MTcTyped::EStructure );
	assertL( structure->Count() == 0 );
	assertTDesC8sEqualL( KNullDesC8, structure->Name() );

	// Destroy structure
	CleanupStack::PopAndDestroy( structure );
	}

void CTstStructure::TestSettersGettersL()
	{
	// Set and verify name
	iStructure->SetName( KTestStructureName );
	assertTDesC8sEqualL( KTestStructureName, iStructure->Name() );

	// Add items
	iStructure->AddItemL( KNullDesC8, KNullDesC8 );
	iStructure->AddItemL( KTestItem1Name, KTestItem1Value );
	iStructure->AddItemL( KTestItem2Name, KTestItem2ValueAsStr );

	CTcNameValue* item = CTcNameValue::NewLC();
	item->SetL( KTestItem2Name, KTestItem2Value );
	iStructure->AddItemL( item );
	CleanupStack::Pop( item );

	// Verify item count
	assertL( iStructure->Count() == 4 );

	// Verify added items
	assertTDesC8sEqualL( KNullDesC8, iStructure->Item( 0 ).Name() );
	assertTDesC8sEqualL( KNullDesC8, iStructure->Item( 0 ).Value() );
	assertTDesC8sEqualL( KTestItem1Name, iStructure->Item( 1 ).Name() );
	assertTDesC8sEqualL( KTestItem1ValueAsStr, iStructure->Item( 1 ).Value() );
	assertTDesC8sEqualL( KTestItem2Name, iStructure->Item( 2 ).Name() );
	assertTDesC8sEqualL( KTestItem2ValueAsStr, iStructure->Item( 2 ).Value() );
	assertTDesC8sEqualL( KTestItem2Name, iStructure->Item( 3 ).Name() );
	assertTDesC8sEqualL( KTestItem2ValueAsStr, iStructure->Item( 3 ).Value() );
	}

void CTstStructure::TestFindL()
	{
	CTcNameValue* item;

	// Add items
	iStructure->AddItemL( KTestItem1Name, KTestItem1Value );
	iStructure->AddItemL( KTestItem2Name, KTestItem2ValueAsStr );

	// Find items by index ---
	// Mandatory item, existing
	item = iStructure->ItemL( 0, ETrue );
	assertTDesC8sEqualL( KTestItem1Name, item->Name() );
	// Mandatory items, non-existing
	TRAPD( err, item = iStructure->ItemL( 3, ETrue ) );
	assertL( err == KTcErrMandatoryStructureItemNotFound );
	TRAP( err, item = iStructure->ItemL( -1, ETrue ) );
	assertL( err == KTcErrMandatoryStructureItemNotFound );
	// Optional item, existing
	item = iStructure->ItemL( 1, EFalse );
	assertTDesC8sEqualL( KTestItem2Name, item->Name() );
	// Optional item, non-existing
	item = iStructure->ItemL( 2, EFalse );
	assertL( item == NULL );
	
	// Find items by name ---
	// Existing item
	item = iStructure->Item( KTestItem1Name );
	assertTDesC8sEqualL( KTestItem1ValueAsStr, item->Value() );
	// Non-existing item
	item = iStructure->Item( KTestBogusItem );
	assertL( item == NULL );

	// Find items by name ---
	// Mandatory item, existing
	item = iStructure->ItemL( KTestItem1Name, ETrue );
	assertTDesC8sEqualL( KTestItem1ValueAsStr, item->Value() );
	// Mandatory item, non-existing
	TRAP( err, item = iStructure->ItemL( KTestBogusItem, ETrue ) );
	assertL( err == KTcErrMandatoryStructureItemNotFound );
	// Optional item, existing
	item = iStructure->ItemL( KTestItem2Name, EFalse );
	assertTDesC8sEqualL( KTestItem2ValueAsStr, item->Value() );
	// Optional item, non-existing
	item = iStructure->ItemL( KTestBogusItem, EFalse );
	assertL( item == NULL );
	}

//
// An own static function to collect the test functions into one 
// suite of tests. The framework will run the tests and free the
// memory allocated for the test suite.
// 
MTest* CTstStructure::suiteL()
	{
	// Always use NewL (Do not use NewLC) !!!
    CTestSuite *suite = CTestSuite::NewL( _L8("CTstStructure") );
    
    suite->addTestL(
		CTestCaller< CTstStructure >::NewL(	_L8("TestConstructorL"), &TestConstructorL ) );

	suite->addTestL(
		CTestCaller< CTstStructure >::NewL(	_L8("TestSettersGettersL"), &TestSettersGettersL ) );

	suite->addTestL(
		CTestCaller< CTstStructure >::NewL(	_L8("TestFindL"), &TestFindL ) );

	return suite;
	}
