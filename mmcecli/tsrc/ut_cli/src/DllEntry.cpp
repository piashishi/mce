/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32const.h>
#include <digia/eunit/CEUnitTestSuite.h>

#include "CMceManagerTest.h"
#include "CMceSessionTest.h"
#include "CMceInSessionTest.h"
#include "CMceOutSessionTest.h"
#include "CMceMediaStreamTest.h"
#include "CMceAudioStreamTest.h"
#include "CMceMediaSourceTest.h"
#include "CMceRtpSourceTest.h"
#include "CMceMediaSinkTest.h"
#include "CMceRtpSinkTest.h"
#include "CMceAudiocodecTest.h"
#include "CMceAmrCodecTest.h"
#include "cmceamrwbcodectest.h"
#include "CMCEMiscTest.h"
#include "CMceEventTest.h"
#include "CMceOutEventTest.h"
#include "CMceInEventTest.h"
#include "CMceReferTest.h"
#include "CMceOutReferTest.h"
#include "CMceInReferTest.h"
#include "CMceFcMsgExchangeTest.h"
#include "mcevideostreamtest.h"
#include "mcecamerasourcetest.h"
#include "mcefilesourcetest.h"
#include "mcedisplaysinktest.h"
#include "mcevideocodectest.h"
#include "mceStreambundletest.h"
#include "mcefilesinktest.h"
#include "mceavsinktest.h"
#include "mceh263codectest.h"
#include "mceavccodectest.h"
#include "mceg711codectest.h"
#include "mcesecureinsessiontest.h"
#include "mcesecureoutsessiontest.h"


#ifdef _BullseyeCoverage
GLDEF_C int __stdcall __E32Dll(void*, unsigned, void*)
	{
	return(KErrNone);
	}
#else
#ifndef EKA2
// Starting point of the DLL (Removed in EKA2) 
GLDEF_C TInt E32Dll(TDllReason)
	{
	return(KErrNone);
	}
#endif
#endif // _BullseyeCoverage



// Exactly one exported function returning the suite of 
// test functions for the test runner in the framework.
// (Always needed)
//
EXPORT_C MEUnitTest* CreateTestL ()
	{
    CEUnitTestSuite *suite = CEUnitTestSuite::NewLC(_L("MceClientTestSuite"));

	suite->AddL( CMceReferTest::suiteL() );
	suite->AddL( CMceInReferTest::suiteL() );
	suite->AddL( CMceOutReferTest::suiteL() );
	suite->AddL( CMceEventTest::suiteL() );
	suite->AddL( CMceInEventTest::suiteL() );
	suite->AddL( CMceOutEventTest::suiteL() );

	suite->AddL( CMceManagerTest::suiteL() );
	suite->AddL( CMceSessionTest::suiteL() );
	suite->AddL( CMceOutSessionTest::suiteL() );
	suite->AddL( CMceInSessionTest::suiteL() );

	suite->AddL( CMceMediaStreamTest::suiteL() );
	suite->AddL( CMceAudioStreamTest::suiteL() );
	suite->AddL( CMceMediaSourceTest::suiteL() );
	suite->AddL( CMceRtpSourceTest::suiteL() );
	suite->AddL( CMceMediaSinkTest::suiteL() );
	suite->AddL( CMceRtpSinkTest::suiteL() );
	suite->AddL( CMceAudioCodecTest::suiteL() );
	suite->AddL( CMceAmrCodecTest::suiteL() );
	suite->AddL( CMceAmrWbCodecTest::suiteL() );
	suite->AddL( CMCEMiscTest::suiteL() );
	
    suite->AddL( CMceVideoStreamTest::suiteL() );
    suite->AddL( CMceCameraSourceTest::suiteL() ); 
    suite->AddL( CMceFileSourceTest::suiteL() );
	suite->AddL( CMceDisplaySinkTest::suiteL() );
	suite->AddL( CMceVideoCodecTest::suiteL() );
	suite->AddL( CMceFcMsgExchangeTest::suiteL() );
	suite->AddL( CMceStreamBundleTest::suiteL() );
	suite->AddL( CMceFileSinkTest::suiteL() );
	suite->AddL( CMceAvSinkTest::suiteL() );
	
	suite->AddL( CMceH263CodecTest::suiteL() );
    suite->AddL( CMceAvcCodecTest::suiteL() );
	suite->AddL( CMceG711CodecTest::suiteL() );
	suite->AddL( CMceSecureInSessionTest::suiteL() );
	suite->AddL( CMceSecureOutSessionTest::suiteL() );
	CleanupStack::Pop(); // rootSuite
	return suite;	
	}
