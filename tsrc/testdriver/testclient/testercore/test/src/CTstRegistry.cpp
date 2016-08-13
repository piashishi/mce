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

#include "CTstRegistry.h"
#include "CTcRegistry.h"

_LIT8( KTstInvalidObjectName, "myObject" );

void CTstRegistry::setUpL()
	{
	iRegistry = new( ELeave ) CTcRegistry;
	}

void CTstRegistry::tearDown()
	{
	delete iRegistry;	// This calls DestroyAll()
	}

void CTstRegistry::TestObjectPtrL()
	{
	// Verify that the registry is empty
	assertL( iRegistry->Count() == 0 );

	// Empty registry, expect an error reported
	TRAPD( err, iRegistry->ObjectPtrL( KTstInvalidObjectName ) );
	assertL( err == KTcErrObjectNotFound );

	// Add a single TPoint object to the array
	TPoint* point = new( ELeave ) TPoint( 10, 5 );
	iRegistry->AddObjectL( point );
	// Get the assigned name
	TPtrC8 pointName = iRegistry->ObjectNameL( point );

	// Verify IsRegistered()
	assertL( !iRegistry->IsRegistered( 0 ) );
	assertL( iRegistry->IsRegistered( point ) );


	// Fetch the objcet back and verify
	TPoint* pointPtr = (TPoint*)iRegistry->ObjectPtrL( pointName );
	assertL( point == pointPtr );
	// Verify that the registry has a single item
	assertL( iRegistry->Count() == 1 );

	// Add a second TPoint object to the array
	TPoint* point2 = new( ELeave ) TPoint( 2, 2 );
	iRegistry->AddObjectL( point2 );
	// Get the assigned name
	TPtrC8 pointName2 = iRegistry->ObjectNameL( point2 );

	// Fetch the objcet back and verify
	TPoint* pointPtr2 = (TPoint*)iRegistry->ObjectPtrL( pointName2 );
	assertL( point2 == pointPtr2 );
	// Verify that the registry has two items
	assertL( iRegistry->Count() == 2 );

	// Also verify that the first point is still there
	pointPtr = (TPoint*)iRegistry->ObjectPtrL( pointName );
	assertL( point == pointPtr );

	// Verify ptr->name mapping
	assertTDesC8sEqualL( pointName, iRegistry->ObjectNameL( pointPtr ) );
	}

void CTstRegistry::TestDestroyObjectL()
	{
	// Verify that the registry is empty
	assertL( iRegistry->Count() == 0 );

	// Empty registry, expect it not to crash
	iRegistry->DestroyObject( KTstInvalidObjectName );

	// Try deleting a NULL object, expect it not to crash
	iRegistry->DestroyObject( NULL );

	// Try deleting an invalid object, expect it not to crash
	iRegistry->DestroyObject( (TAny*)0x12345678 );

	// Add a single TPoint object to the array
	TPoint* point = new( ELeave ) TPoint( 10, 5 );
	iRegistry->AddObjectL( point );
	// Get the assigned name
	TPtrC8 pointName = iRegistry->ObjectNameL( point );

	// Destroy it by name
	iRegistry->DestroyObject( pointName );
	// Verify that it's really gone
	assertL( iRegistry->Count() == 0 );

	// Add a single TPoint object to the array
	point = new( ELeave ) TPoint( 10, 5 );
	iRegistry->AddObjectL( point );
	// Destroy it by pointer
	iRegistry->DestroyObject( point );
	// Verify that it's really gone
	assertL( iRegistry->Count() == 0 );

	// Add a single CBase derived object to the array
	CPeriodic* obj = CPeriodic::NewL( CActive::EPriorityLow );
	iRegistry->AddObjectL( obj );
	// Destroy it by pointer
	iRegistry->DestroyObject( obj );
	// Verify that it's really gone
	assertL( iRegistry->Count() == 0 );

	// Add a single CBase derived object to the array, do not give ownership
	obj = CPeriodic::NewL( CActive::EPriorityLow );
	CleanupStack::PushL( obj );
	const CPeriodic& objRef = *obj;
	iRegistry->AddObjectL( objRef );
	// Destroy it by pointer
	iRegistry->DestroyObject( obj );
	// Verify that it's really gone
	assertL( iRegistry->Count() == 0 );
	// Delete object, this fais if registry incorrectly deleted the object already
	CleanupStack::PopAndDestroy( obj );

	// Add two objects, destroy both
	point = new( ELeave ) TPoint( 10, 5 );
	iRegistry->AddObjectL( point );
	TPoint* point2 = new( ELeave ) TPoint( 2, 5 );
	iRegistry->AddObjectL( point2 );

	// Destroy both by pointer, last one first
	iRegistry->DestroyObject( point2 );
	// Verify that it's really gone
	assertL( iRegistry->Count() == 1 );
	iRegistry->DestroyObject( point );
	// Verify that it's really gone
	assertL( iRegistry->Count() == 0 );
	}

// An own static function to collect the test functions into one 
// suite of tests. The framework will run the tests and free the
// memory allocated for the test suite.
// 
MTest* CTstRegistry::suiteL()
	{
	// Always use NewL (Do not use NewLC) !!!
    CTestSuite *suite = CTestSuite::NewL( _L8("CTstRegistry") );
    
    suite->addTestL(
		CTestCaller< CTstRegistry >::NewL(	_L8("TestObjectPtrL"), &TestObjectPtrL ) );

    suite->addTestL(
		CTestCaller< CTstRegistry >::NewL(	_L8("TestDestroyObjectL"), &TestDestroyObjectL ) );
	
	return suite;
	}
