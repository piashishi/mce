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

#include "CTstCtrlCodec.h"
#include "CTcCTRLCodec.h"
#include "CTcParameterList.h"
#include "TTcIdentifier.h"

_LIT8( KTcReq1, "<garbagehere>CTRL/2.0þREQþCSIP.NewLþ_objectref_÷mySIPþ$" );
_LIT8( KTcRes1, "CTRL/2.0þRESþCSIP.NewLþCSIP*÷mySIPþ$" );
_LIT8( KTcReq2, "CTRL/2.0þREQþPro1-pIMS-Obs.CreateProfileþúSetType÷TClass÷EProprietaryþTName÷NokiapreR5ImsþùþúSetIapId÷TUint32÷1þùþúSetAORs÷TDesC8&÷sip:user1@10.21.32.190þùþúSetPrivateIdentity÷TDesC8&÷user1@ietf.netþùþúSetName÷TDesC8&÷MicrophoneþùþúEnableSigComp÷TBool÷ETrueþùþúEnableAutoRegistration÷TBool÷ETrueþùþúEnableSecurityNegotiation÷TBool÷ETrueþùþúSetServer÷TServer÷ERegistrarþTDesC8&÷sip:10.21.32.190þùþúSetServerParameter÷TServer÷ERegistrarþTServerParameter÷EDigestRealmþTDesC8&÷home1.netþùþúSetServerExtensionParameter÷TServer÷ERegistrarþTDesC8&÷passwdþTDesC8&÷passwordþùþúSetServer÷TServer÷EOutboundProxyþTDesC8&÷sip:D1003518.reg-108.noklab.net;lrþùþ$" );
_LIT8( KTcReq3, "CTRL/2.0þREQþmySIPConnection1._RESET_þ$" );
_LIT8( KTcReq4, "CTRL/2.0þREQþpIMS-C1.GetProfilesþvoid÷NULLþóTIntArray[]÷2õ5õ28òþ$" );
_LIT8( KTcRes2, "CTRL/2.0þRESþmySIP.AddClientþvoid÷NULLþTUid÷101F5D3EþTDesC8&÷NULLþóMDesC8Array& []÷Accept: text/plainõNULLõNULLòþTBool÷Etrueþ$");
_LIT8( KTcRes3, "CTRL/2.0þRESþSendInviteþTInt÷0þúSetType÷TClass÷EProprietaryþTName÷10þùþ$");
_LIT8( KTcReqInvalid, "CTRL/2.0þREQþCSIP.NewL$" );
_LIT8( KTcReqIncomplete, "CTRL/2.0þREQþCSIP.NewLþ_objectref_÷mySIPþ" );
_LIT8( KTcReq5, "CTRL/2.0þREQþSendInviteþvoid÷NULLþ$" );
_LIT8( KTcReq6, "CTRL/2.0þREQþFunctionþdot.here÷mySIPþ$" );
_LIT8( KTcReqStart, "CTRL/2.0þREQþSIP:REG_2._START_þ$" );
_LIT8( KTcReqEnd, "CTRL/2.0þREQþSIP:REG_2._END_þ$" );

void CTstCtrlCodec::setUpL()
	{
	iCodec = new( ELeave ) CTcCTRLCodec( iReq, iRes );
	iList = new( ELeave ) CTcParameterList;
	}

void CTstCtrlCodec::tearDown()
	{
	delete iCodec;
	delete iList;
	iReq.Zero();
	iRes.Zero();
	}

void CTstCtrlCodec::TestIsCompleteL()
	{
	// empty request, should not be complete
	assertL( !iCodec->IsComplete() );

	// real request, should be incomplete (missing $)
	iReq.Copy( KTcReqIncomplete );
	assertL( !iCodec->IsComplete() );
	
	// real request, should be complete
	iReq.Copy( KTcReq1 );
	assertL( iCodec->IsComplete() );
	}

void CTstCtrlCodec::TestTypeL()
	{
	// empty request, should return unknown
	assertL( iCodec->RequestType() == CTcCTRLCodec::EUnknown );

	// response, should return unknown, Type() is only concerned about requests
	iReq.Copy( KTcRes1 );
	assertL( iCodec->RequestType() == CTcCTRLCodec::EUnknown );

	// invalid response (missing the last field separator)
	iReq.Copy( KTcReqInvalid );
	assertL( iCodec->RequestType() == CTcCTRLCodec::EUnknown );
	
	// real request
	iReq.Copy( KTcReq1 );
	assertL( iCodec->RequestType() == CTcCTRLCodec::ERequest );

	// real reset request
	iReq.Copy( KTcReq3 );
	assertL( iCodec->RequestType() == CTcCTRLCodec::EResetRequest );

	// real start request
	iReq.Copy( KTcReqStart );
	assertL( iCodec->RequestType() == CTcCTRLCodec::EStartRequest );

	// real end request
	iReq.Copy( KTcReqEnd );
	assertL( iCodec->RequestType() == CTcCTRLCodec::EEndRequest );
	}

void CTstCtrlCodec::TestGetIdentifierL()
	{
	// empty request, should leave with KTcErrRequestCorrupt
	TTcIdentifier id;
	TRAPD( err, iCodec->GetIdentifierL( id ) );
	assertL( err == KTcErrRequestCorrupt );

	// real request, function invokation
	iReq.Copy( KTcReq5 );
	iCodec->GetIdentifierL( id );
	assertTDesC8sEqualL( KNullDesC8, id.iContainer );
	assertTDesC8sEqualL( _L8("SendInvite"), id.iFunction );

	// real request, function invokation but with scope delimiter
	// present after identifier field
	iReq.Copy( KTcReq6 );
	iCodec->GetIdentifierL( id );
	assertTDesC8sEqualL( KNullDesC8, id.iContainer );
	assertTDesC8sEqualL( _L8("Function"), id.iFunction );

	// real request, OO invokation
	iReq.Copy( KTcReq1 );
	iCodec->GetIdentifierL( id );
	assertTDesC8sEqualL( _L8("CSIP"), id.iContainer );
	assertTDesC8sEqualL( _L8("NewL"), id.iFunction );

	// reset request, OO reset
	iReq.Copy( KTcReq3 );
	iCodec->GetIdentifierL( id );
	assertTDesC8sEqualL( _L8("mySIPConnection1"), id.iContainer );
	assertTDesC8sEqualL( _L8("_RESET_"), id.iFunction );
	}

void CTstCtrlCodec::TestGetParametersL()
	{
	// empty request, should leave with KTcErrRequestCorrupt
	TRAPD( err, iCodec->GetParametersL( *iList ) );
	assertL( err == KTcErrRequestCorrupt );

	// real request
	iReq.Copy( KTcReq1 );
	iCodec->GetParametersL( *iList );

	// Verify, should contain a single name-value pair
	assertL( iList->Count() == 1 );
	assertL( iList->ParameterType( 0 ) == MTcTyped::ENameValue );
	CTcNameValue& tv = iList->AsNameValue( 0 );
	assertTDesC8sEqualL( _L8("_objectref_"), tv.Name() );
	assertTDesC8sEqualL( _L8("mySIP"), tv.Value() );
	}

void CTstCtrlCodec::TestGetParametersStructureL()
	{
	// real request
	iReq.Copy( KTcReq2 );
	iCodec->GetParametersL( *iList );
	
	// Should have 12 structures
	assertL( iList->Count() == 12 );
	for( TInt i = 0; i < 12; i++ )
		{
		assertL( iList->ParameterType( i ) == MTcTyped::EStructure );
		}

	// Verify first stucture
	CTcStructure& s1 = iList->AsStructure( 0 );
	assertL( s1.Count() == 2 );
	assertTDesC8sEqualL( _L8("SetType"), s1.Name() );
	assertTDesC8sEqualL( _L8("TClass"), s1.Item( 0 ).Name() );
	assertTDesC8sEqualL( _L8("EProprietary"), s1.Item( 0 ).Value() );
	assertTDesC8sEqualL( _L8("TName"), s1.Item( 1 ).Name() );
	assertTDesC8sEqualL( _L8("NokiapreR5Ims"), s1.Item( 1 ).Value() );	

	// Verify last stucture
	CTcStructure& s2 = iList->AsStructure( 11 );
	assertL( s2.Count() == 2 );
	assertTDesC8sEqualL( _L8("SetServer"), s2.Name() );
	assertTDesC8sEqualL( _L8("TServer"), s2.Item( 0 ).Name() );
	assertTDesC8sEqualL( _L8("EOutboundProxy") ,s2.Item( 0 ).Value() );
	assertTDesC8sEqualL( _L8("TDesC8&"), s2.Item( 1 ).Name() );
	assertTDesC8sEqualL( _L8("sip:D1003518.reg-108.noklab.net;lr"), s2.Item( 1 ).Value() );	
	}

void CTstCtrlCodec::TestGetParametersArrayL()
	{
	// real request
	iReq.Copy( KTcReq4 );
	iCodec->GetParametersL( *iList );
	
	// Should have 2 items
	assertL( iList->Count() == 2 );
	assertL( iList->ParameterType( 0 ) == MTcTyped::ENameValue );
	assertL( iList->ParameterType( 1 ) == MTcTyped::EArray );

	// Verify type-value pair
	CTcNameValue& tv = iList->AsNameValue( 0 );
	assertTDesC8sEqualL( _L8("void"), tv.Name() );
	assertTDesC8sEqualL( _L8("NULL"), tv.Value() );

	// Verify array
	CTcArray& a1 = iList->AsArray( 1 );
	assertL( a1.Count() == 3 );
	assertTDesC8sEqualL( _L8("TIntArray[]"), a1.Name() );
	assertTDesC8sEqualL( _L8("2"), a1.Item( 0 ) );
	assertL( 2 == a1.ItemAsInt( 0 ) );
	assertTDesC8sEqualL( _L8("5"), a1.Item( 1 ) );
	assertL( 5 == a1.ItemAsInt( 1 ) );
	assertTDesC8sEqualL( _L8("28"), a1.Item( 2 ) );
	assertL( 28 == a1.ItemAsInt( 2 ) );
	}

void CTstCtrlCodec::TestConstructResponse1L()
	{
	TTcIdentifier id( _L8("mySIP"), _L8("AddClient") );
	CTcNameValue* retVal = CTcNameValue::NewLC();
	retVal->SetL( _L8("void"), _L8("NULL") );

	CTcNameValue* tv = CTcNameValue::NewLC();
	tv->SetL( _L8("TUid"), _L8("101F5D3E") );
	iList->AddParameterL( tv );
	CleanupStack::Pop();

	CTcArray* a1 = CTcArray::NewLC();
	iList->AddParameterL( a1 );
	CleanupStack::Pop();

	a1->SetName( _L8("MDesC8Array& []") );
	a1->AddItemL( _L8("Accept: text/plain") );
	a1->AddItemL( _L8("NULL") );
	a1->AddItemL( _L8("NULL") );

	tv = CTcNameValue::NewLC();
	tv->SetL( _L8("TDesC8&"), _L8("NULL") );
	iList->InsertParameterL( tv, 1 );
	CleanupStack::Pop();

	tv = CTcNameValue::NewLC();
	tv->SetL( _L8("TBool"), _L8("Etrue") );
	iList->AddParameterL( tv );
	CleanupStack::Pop();

	iCodec->ConstructResponse( id, *retVal, *iList );
	CleanupStack::PopAndDestroy( retVal );
	assertTDesC8sEqualL( KTcRes2, iRes );
	}

void CTstCtrlCodec::TestConstructResponse2L()
	{
	TTcIdentifier id( _L8("SendInvite") );
	CTcNameValue* retVal = CTcNameValue::NewLC();
	retVal->SetL( _L8("TInt"), _L8("0") );

	CTcStructure* s1 = CTcStructure::NewLC();
	iList->AddParameterL( s1 );
	CleanupStack::Pop();

	s1->SetName( _L8("SetType") );
	s1->AddItemL( _L8("TClass"), _L8("EProprietary") );
	s1->AddItemL( _L8("TName"), 10 );

	iCodec->ConstructResponse( id, *retVal, *iList );
	CleanupStack::PopAndDestroy( retVal );
	assertTDesC8sEqualL( KTcRes3, iRes );
	}

void CTstCtrlCodec::TestConstructOkResponseL()
	{
	iCodec->ConstructOkResponse();
	assertTDesC8sEqualL( _L8("CTRL/2.0þRESþ_OK_þ$"), iRes );
	}

void CTstCtrlCodec::TestConstructErrorResponseL()
	{
	iCodec->ConstructErrorResponse( _L8("Unknown function: SendInvite") );
	assertTDesC8sEqualL( _L8("CTRL/2.0þERRþUnknown function: SendInviteþ$"), iRes );
	}

MTest* CTstCtrlCodec::suiteL()
	{
	// Always use NewL (Do not use NewLC) !!!
	CTestSuite *suite = CTestSuite::NewL( _L8("CTstCtrlCodec") );
    
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestIsCompleteL"), &TestIsCompleteL ) );
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestTypeL"), &TestTypeL ) );
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestGetIdentifierL"), &TestGetIdentifierL ) );
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestGetParametersL"), &TestGetParametersL ) );
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestGetParametersStructureL"), &TestGetParametersStructureL ) );
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestGetParametersArrayL"), &TestGetParametersArrayL ) );
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestConstructResponse1L"), &TestConstructResponse1L ) );
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestConstructResponse2L"), &TestConstructResponse2L ) );
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestConstructOkResponseL"), &TestConstructOkResponseL ) );
	suite->addTestL(
		CTestCaller< CTstCtrlCodec >::NewL(	_L8("TestConstructErrorResponseL"), &TestConstructErrorResponseL ) );
	
	return suite;
	}
