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

#include "CTcParameterList.h"
#include "CTstParameterList.h"

_LIT8( KTestName1, "RemoteURI" );
_LIT8( KTestValue1, "<sip:joku@jossain.net>" );
_LIT8( KTestArrayName, "Headers" );
_LIT8( KTestArrayItem1, "From: billy@wild.west" );
_LIT8( KTestStructureName, "TestClientIds" );
_LIT8( KTestBogusName, "abba" );

void CTstParameterList::setUpL()
	{
	iList = new( ELeave ) CTcParameterList;
	}

void CTstParameterList::tearDown()
	{
	delete iList;
	}

void CTstParameterList::TestConstructorL()
	{
	// Create array
	CTcParameterList* list = new( ELeave ) CTcParameterList;
	CleanupStack::PushL( list );

	// Verify correct initialization
	assertL( list->Count() == 0 );

	// Destroy array
	CleanupStack::PopAndDestroy( list );
	}

void CTstParameterList::TestAddFetchL()
	{
	// Add three items, name-value, array, and structure
	iList->AddParameterL( CreateNameValueLC() );
	CleanupStack::Pop();
	iList->AddParameterL( CreateArrayLC() );
	CleanupStack::Pop();
	iList->AddParameterL( CreateStructureLC() );
	CleanupStack::Pop();

	// Verify, should contain three items
	assertL( iList->Count() == 3 );
	assertL( iList->ParameterType( 0 ) == MTcTyped::ENameValue );
	assertL( iList->ParameterType( 1 ) == MTcTyped::EArray );
	assertL( iList->ParameterType( 2 ) == MTcTyped::EStructure );

	// Verify access to the NameValue item
	CTcNameValue& nameValue = iList->AsNameValueL( 0 );
	assertTDesC8sEqualL( KTestName1, nameValue.Name() );
	assertTDesC8sEqualL( KTestValue1, nameValue.Value() );
	TRAPD( err, iList->AsArrayL( 0 ) );
	assertL( err == KTcErrRequestCorrupt );
	TRAP( err, iList->AsStructureL( 0 ) );
	assertL( err == KTcErrRequestCorrupt );

	// Verify access to the Array item
	CTcArray& array = iList->AsArrayL( 1 );
	assertTDesC8sEqualL( KTestArrayName, array.Name() );
	assertTDesC8sEqualL( KTestArrayItem1, array.Item( 0 ) );
	TRAP( err, iList->AsNameValueL( 1 ) );
	assertL( err == KTcErrRequestCorrupt );
	TRAP( err, iList->AsStructureL( 1 ) );
	assertL( err == KTcErrRequestCorrupt );

	// Verify access to the Structure item
	CTcStructure& structure = iList->AsStructureL( 2 );
	assertTDesC8sEqualL( KTestStructureName, structure.Name() );
	assertTDesC8sEqualL( KTestName1, structure.Item( 0 ).Name() );
	assertTDesC8sEqualL( KTestValue1, structure.Item( 0 ).Value() );
	TRAP( err, iList->AsNameValueL( 2 ) );
	assertL( err == KTcErrRequestCorrupt );
	TRAP( err, iList->AsArrayL( 2 ) );
	assertL( err == KTcErrRequestCorrupt );

	// Verify access outside the list
	TRAP( err, iList->AsNameValueL( -1 ) );
	assertL( err == KTcErrRequestCorrupt );
	TRAP( err, iList->AsNameValueL( 10 ) );
	assertL( err == KTcErrRequestCorrupt );
	}

void CTstParameterList::TestInsertRemoveL()
	{
	// Add two items, name-value and array
	iList->AddParameterL( CreateNameValueLC() );
	CleanupStack::Pop();
	iList->AddParameterL( CreateArrayLC() );
	CleanupStack::Pop();
	// Insert a structure to the middle
	iList->InsertParameterL( CreateStructureLC(), 1 );
	CleanupStack::Pop();

	// Verify, should contain three items in correct order
	assertL( iList->Count() == 3 );
	assertL( iList->ParameterType( 0 ) == MTcTyped::ENameValue );
	assertL( iList->ParameterType( 1 ) == MTcTyped::EStructure );
	assertL( iList->ParameterType( 2 ) == MTcTyped::EArray );

	// Verify remove
	iList->RemoveParameter( KTestArrayName, MTcTyped::EArray );
	assertL( iList->Count() == 2 );
	assertL( iList->ParameterType( 0 ) == MTcTyped::ENameValue );
	assertL( iList->ParameterType( 1 ) == MTcTyped::EStructure );
	iList->RemoveParameter( KTestName1 );
	assertL( iList->Count() == 1 );
	assertL( iList->ParameterType( 0 ) == MTcTyped::EStructure );
	// Non-existing item, should not crash
	iList->RemoveParameter( KTestBogusName );

	// Verify reset
	iList->Reset();
	assertL( iList->Count() == 0 );
	}


void CTstParameterList::TestFindL()
	{
	// Add three items, name-value, array, and structure
	iList->AddParameterL( CreateNameValueLC() );
	CleanupStack::Pop();
	iList->AddParameterL( CreateArrayLC() );
	CleanupStack::Pop();
	iList->AddParameterL( CreateStructureLC() );
	CleanupStack::Pop();

	// Existing, any type
	assertL( iList->FindParameter( KTestName1 ) == 0 );
	// Existing, require array type
	assertL( iList->FindParameter( KTestArrayName, MTcTyped::EArray ) == 1 );
	// Existing but with different type, require namevalue type
	assertL( iList->FindParameter( KTestStructureName, MTcTyped::ENameValue ) == KErrNotFound );
	// Non-existing, any type
	assertL( iList->FindParameter( KTestBogusName ) == KErrNotFound );

	// Add a structure item with same name as array
	iList->AddParameterL( CreateStructureLC() );
	iList->AsStructure( 3 ).SetName( KTestArrayName );
	CleanupStack::Pop();

	// Verify find with same name but different type
	assertL( iList->FindParameter( KTestArrayName, MTcTyped::EArray ) == 1 );
	assertL( iList->FindParameter( KTestArrayName, MTcTyped::EStructure ) == 3 );
	assertL( iList->FindParameter( KTestArrayName, MTcTyped::EUnknown ) == 1 );
	}

MTcTyped* CTstParameterList::CreateNameValueLC()
	{
	CTcNameValue* nameValue = CTcNameValue::NewLC();
	nameValue->SetL( KTestName1, KTestValue1 );
	return nameValue;
	}

MTcTyped* CTstParameterList::CreateArrayLC()
	{
	CTcArray* array = CTcArray::NewLC();
	array->SetName( KTestArrayName );
	array->AddItemL( KTestArrayItem1 );
	return array;
	}

MTcTyped* CTstParameterList::CreateStructureLC()
	{
	CTcStructure* structure = CTcStructure::NewLC();
	structure->SetName( KTestStructureName );
	structure->AddItemL( KTestName1, KTestValue1 );
	return structure;
	}

MTest* CTstParameterList::suiteL()
	{
	// Always use NewL (Do not use NewLC) !!!
	CTestSuite *suite = CTestSuite::NewL( _L8("CTstParameterList") );
    
	suite->addTestL(
		CTestCaller< CTstParameterList >::NewL(	_L8("TestConstructorL"), &TestConstructorL ) );
	suite->addTestL(
		CTestCaller< CTstParameterList >::NewL(	_L8("TestAddFetchL"), &TestAddFetchL ) );
	suite->addTestL(
		CTestCaller< CTstParameterList >::NewL(	_L8("TestInsertRemoveL"), &TestInsertRemoveL ) );
	suite->addTestL(
		CTestCaller< CTstParameterList >::NewL(	_L8("TestFindL"), &TestFindL ) );
	
	return suite;
	}
