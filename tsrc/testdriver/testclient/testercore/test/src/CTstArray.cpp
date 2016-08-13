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
#include "CTstArray.h"
#include "CTcArray.h"

_LIT8( KTestArrayName, "Headers" );
_LIT8( KTestItem1, "To: jesse.james@wild.west");
_LIT8( KTestItem2, "From: billy@wild.west");
_LIT8( KTestItemIntAsStr, "10" );
const TInt KTestItemInt( 10 );

void CTstArray::setUpL()
	{
	iArray = CTcArray::NewLC();
	CleanupStack::Pop();
	}

void CTstArray::tearDown()
	{
	delete iArray;
	}

void CTstArray::TestConstructorL()
	{
	// Create array
	CTcArray* array = CTcArray::NewLC();

	// Verify correct initialization
	assertL( array->ParameterType() == MTcTyped::EArray );
	assertL( array->Count() == 0 );
	assertTDesC8sEqualL( KNullDesC8, array->Name() );

	// Destroy array
	CleanupStack::PopAndDestroy( array );
	}

void CTstArray::TestSettersGettersL()
	{
	// Set and verify name
	iArray->SetName( KTestArrayName );
	assertTDesC8sEqualL( KTestArrayName, iArray->Name() );

	// Add items: empty item, string and integer
	iArray->AddItemL( KNullDesC8 );
	iArray->AddItemL( KTestItem1 );
	iArray->AddItemL( KTestItemInt );
	assertL( iArray->Count() == 3 );

	// Verify added items
	assertTDesC8sEqualL( KNullDesC8, iArray->Item( 0 ) );
	assertTDesC8sEqualL( KTestItem1, iArray->Item( 1 ) );
	assertTDesC8sEqualL( KTestItemIntAsStr, iArray->Item( 2 ) );
	assertL( KTestItemInt == iArray->ItemAsInt( 2 ) );

	// Verify the MDesCArray interface
	assertL( iArray->AsMDesCArray().MdcaCount() == 3 );
	assertTDesC8sEqualL( KTestItem1, iArray->AsMDesCArray().MdcaPoint( 1 ) );

	// Remove items, verify that correct ones have been removed
	iArray->RemoveItem( 1 );
	assertTDesC8sEqualL( KNullDesC8, iArray->Item( 0 ) );
	assertTDesC8sEqualL( KTestItemIntAsStr, iArray->Item( 1 ) );
	assertL( iArray->Count() == 2 );
	iArray->RemoveItem( 0 );
	assertTDesC8sEqualL( KTestItemIntAsStr, iArray->Item( 0 ) );
	assertL( iArray->Count() == 1 );
	iArray->RemoveItem( 0 );
	assertL( iArray->Count() == 0 );
	}

void CTstArray::TestDescArraySetterL()
	{
	// Create a descriptor array
	CDesC8ArrayFlat* desArray = new( ELeave ) CDesC8ArrayFlat( 3 );
	CleanupStack::PushL( desArray );
	desArray->AppendL( KNullDesC8 );
	desArray->AppendL( KTestItem1 );
	desArray->AppendL( KTestItemIntAsStr );

	// Add the descriptor array to the CTcArray
	iArray->AddItemsL( *desArray );
	CleanupStack::PopAndDestroy( desArray );

	// Verify added items
	assertTDesC8sEqualL( KNullDesC8, iArray->Item( 0 ) );
	assertTDesC8sEqualL( KTestItem1, iArray->Item( 1 ) );
	assertTDesC8sEqualL( KTestItemIntAsStr, iArray->Item( 2 ) );
	assertL( KTestItemInt == iArray->ItemAsInt( 2 ) );
	}

//
// An own static function to collect the test functions into one 
// suite of tests. The framework will run the tests and free the
// memory allocated for the test suite.
// 
MTest* CTstArray::suiteL()
	{
	// Always use NewL (Do not use NewLC) !!!
    CTestSuite *suite = CTestSuite::NewL( _L8("CTstArray") );
    
    suite->addTestL(
		CTestCaller< CTstArray >::NewL(	_L8("TestConstructorL"), &TestConstructorL ) );

	suite->addTestL(
		CTestCaller< CTstArray >::NewL(	_L8("TestSettersGettersL"), &TestSettersGettersL ) );

	suite->addTestL(
		CTestCaller< CTstArray >::NewL(	_L8("TestDescArraySetterL"), &TestDescArraySetterL ) );

	return suite;
	}
