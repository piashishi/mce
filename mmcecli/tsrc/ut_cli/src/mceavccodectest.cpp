/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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

#include <e32def.h>
#include <e32base.h>
#include <digia/eunit/EUnitMacros.h>
#include "mceavccodectest.h"
#include "mcestubs.h"

#include "mceavccodec.h"
#include "mcecomvideocodec.h"

#include "mcemanager.h"
#include "mceoutsession.h"
#include "mcevideostream.h"


#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"

// ----------------------------------------------------------------------------
// CMceAvcCodecTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceAvcCodecTest::setUpL()
    {
    _LIT8( Kh264, "H264" );
    TBuf8<KMceMaxSdpNameLength> sdpName( Kh264 );
    iCodec = CMceAvcCodec::NewL(sdpName);				
    }

// ----------------------------------------------------------------------------
// CMceAvcCodecTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceAvcCodecTest::tearDown()
    {
	if (iCodec)
		{
		delete iCodec;
		iCodec = NULL;
		}
    }

// ----------------------------------------------------------------------------
// CMceAvcCodecTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceAvcCodecTest::suiteL()
    {
    CMceAvcCodecTest* suite = new CMceAvcCodecTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }
    
EUNIT_BEGIN_TEST_TABLE( 
    CMceAvcCodecTest,
    "CMceAvcCodecTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceAvcCodecTest", setUpL, SettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvcCodecTest", setUpL, CloneTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvcCodecTest", setUpL, SetBitRatesTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAvcCodecTest", setUpL, SetAllowBitRatesTestL, tearDown )
EUNIT_END_TEST_TABLE 

	
// ----------------------------------------------------------------------------
// CMceAvcCodecTest::SettersTestL
// ----------------------------------------------------------------------------
//
void CMceAvcCodecTest::SettersTestL()
    {
    const TInt KMceAvcLevel1BitrateBps = 64000;
    
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iCodec->iFlatData );
        
    flatData->iFrameRate = 0;
 	iCodec->SetFrameRateL( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iFrameRate );
	
 	flatData->iMaxBitRate = 0;
 	iCodec->SetMaxBitrateL( KMceAvcLevel1BitrateBps );
 	EUNIT_ASSERT_EQUALS( KMceAvcLevel1BitrateBps, flatData->GetMaxBitRate() );
 	
	flatData->iAllowedResolutions = 0;
 	iCodec->SetAllowedResolutionsL( 100 );
 	EUNIT_ASSERT_EQUALS( 100, flatData->iAllowedResolutions );
	
	flatData->iResolutionWidth = 0;
	TSize resoulutionSize;
	resoulutionSize.iWidth=20;
	resoulutionSize.iHeight=30;
 	iCodec->SetResolutionL( resoulutionSize );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iResolutionWidth );
	EUNIT_ASSERT_EQUALS( 30, flatData->iResolutionHeight );


	flatData->iAllowedFrameRates = 0;
 	iCodec->SetAllowedFrameRatesL( 50 );
 	EUNIT_ASSERT_EQUALS( 50, flatData->iAllowedFrameRates );
	
	
    _LIT8( KNoName, "NoName" );
    _LIT8( KSomeName, "SomeName" );
    TBuf8<KMceMaxSdpNameLength> sdpName( KNoName );
    TBuf8<KMceMaxSdpNameLength> sdpName2( KSomeName );
    flatData->iSdpName = sdpName;
    iCodec->SetSdpNameL( sdpName2 );
    EUNIT_ASSERT_EQUALS( KSomeName(), flatData->iSdpName );
    
    flatData->iPayloadType = 0;
    iCodec->SetPayloadType( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iPayloadType );
    
    flatData->iCodecMode = 0;
    iCodec->SetCodecMode( KMceAvcModeSingleNal );
 	EUNIT_ASSERT_EQUALS( KMceAvcModeSingleNal, flatData->iCodecMode );

    flatData->iCodecMode = 0;
    iCodec->SetCodecMode( KMceAvcModeNonInterleaved );
    EUNIT_ASSERT_EQUALS( KMceAvcModeNonInterleaved, flatData->iCodecMode );
    
    flatData->iCodecMode = 0;
    EUNIT_ASSERT( iCodec->SetCodecMode( KMceAvcModeInterleaved ) == KErrNotSupported );
    EUNIT_ASSERT_EQUALS( KMceAvcModeSingleNal, flatData->iCodecMode );
    
    const TUid id = TUid::Uid( 0 );
    TRAPD( error, iCodec->SetPreferredEncodingDecodingDeviceL( id ) );
    EUNIT_ASSERT( error == KErrNone );


    _LIT8( KConfigKey, "configkey" );
    iCodec->SetConfigKeyL( KConfigKey );
    EUNIT_ASSERT_EQUALS( KConfigKey(), *flatData->iConfigKey );


    }

    
// ----------------------------------------------------------------------------
// CMceAvcCodecTest::CloneTestL
// ----------------------------------------------------------------------------
//
void CMceAvcCodecTest::CloneTestL()
    {
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iCodec->iFlatData );
        
    CMceVideoCodec* clone = iCodec->CloneL();
    
    CMceComVideoCodec* cloneFlatData = 
        static_cast<CMceComVideoCodec*>( clone->iFlatData );
   
	   
    EUNIT_ASSERT(flatData->iID.iAppId == cloneFlatData->iID.iAppId);
    EUNIT_ASSERT(flatData->iID.iId == cloneFlatData->iID.iId);
    EUNIT_ASSERT(flatData->iFmtpAttr != cloneFlatData->iFmtpAttr);
    EUNIT_ASSERT( *(flatData->iFmtpAttr) == *(cloneFlatData->iFmtpAttr) );
    EUNIT_ASSERT(flatData->iPayloadType == cloneFlatData->iPayloadType);
    EUNIT_ASSERT(flatData->iBitrate == cloneFlatData->iBitrate);
    EUNIT_ASSERT(flatData->iAllowedBitrates == cloneFlatData->iAllowedBitrates);
    EUNIT_ASSERT(flatData->iCodecMode == cloneFlatData->iCodecMode);
    EUNIT_ASSERT(flatData->iFourCC == cloneFlatData->iFourCC);
    EUNIT_ASSERT(flatData->iFrameSize == cloneFlatData->iFrameSize);
    EUNIT_ASSERT(flatData->iFrameRate == cloneFlatData->iFrameRate);
    EUNIT_ASSERT(flatData->iMaxBitRate == cloneFlatData->iMaxBitRate);
    EUNIT_ASSERT(flatData->iAllowedResolutions == cloneFlatData->iAllowedResolutions);
    EUNIT_ASSERT(flatData->iResolutionWidth  == cloneFlatData->iResolutionWidth );
  	EUNIT_ASSERT(flatData->iResolutionHeight == cloneFlatData->iResolutionHeight);
  	EUNIT_ASSERT(flatData->iAllowedFrameRates == cloneFlatData->iAllowedFrameRates);
  	EUNIT_ASSERT(flatData->iClockRate == cloneFlatData->iClockRate);
  
    delete clone;
    }

// ----------------------------------------------------------------------------
// CMceAvcCodecTest::SetAllowBitRatesTestL()
// ----------------------------------------------------------------------------
//
void CMceAvcCodecTest::SetAllowBitRatesTestL()
    {
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iCodec->iFlatData );
    // bit rates is equal so no setting need    
    flatData->iAllowedBitrates  = 0;
 	TInt err = iCodec->SetAllowedBitrates( 0 );
 	EUNIT_ASSERT_EQUALS( 0, flatData->iAllowedBitrates );
	EUNIT_ASSERT( err == KErrNone );
	
	flatData->iAllowedBitrates  = 10;
 	err = iCodec->SetAllowedBitrates( 0 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iAllowedBitrates );
	EUNIT_ASSERT( err == KErrArgument );
	
	//bit set but no bound stream
    flatData->iAllowedBitrates  = 10;
 	iCodec->SetAllowedBitrates( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iAllowedBitrates );
 	
 	//max bit rate
 	/*
 	flatData->iAllowedBitrates  = 10;
 	err = iCodec->SetAllowedBitrates( 65000 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iAllowedBitrates );
 	EUNIT_ASSERT( err == KErrArgument );
 	// bitrate will be set in comcodec
 	flatData->iAllowedBitrates  = 10;
 	flatData->iBitrate  =65000;
 	err = iCodec->SetAllowedBitrates( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iAllowedBitrates );
 	EUNIT_ASSERT( err == KErrArgument );
 	*/
 	
 	// add stream but not allowed to set because not bound stream
	CMceVideoStream* stream = CMceVideoStream::NewL();
	CleanupStack::PushL(stream);
	iCodec->iStream = stream;
	flatData->iAllowedBitrates  = 10;
 	iCodec->SetAllowedBitrates( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iAllowedBitrates );
    
    //add bound stream and session
   
    CMceVideoStream* bound = CMceVideoStream::NewL();
    CleanupStack::PushL(bound);
    bound->AddCodecL(iCodec);
    stream->BindL( bound );
    CleanupStack::Pop(bound);
    flatData->iAllowedBitrates  = 10;
 	iCodec->SetAllowedBitrates( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iAllowedBitrates );
    
    bound->RemoveCodecL(*iCodec);
    iCodec= NULL;
    CleanupStack::PopAndDestroy( stream);
	
    }

// ----------------------------------------------------------------------------
// CMceAvcCodecTest::SetBitRatesTestL()
// ----------------------------------------------------------------------------
//
void CMceAvcCodecTest::SetBitRatesTestL()
    {
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iCodec->iFlatData );
    // bit rates is equal so no setting need    
    flatData->iBitrate  = 0;
    TInt err = iCodec->SetBitrate( 0 );
    EUNIT_ASSERT_EQUALS( 0, flatData->iBitrate );
    EUNIT_ASSERT( err == KErrNone );
    
    flatData->iBitrate  = 10;
    err = iCodec->SetBitrate( 0 );
    EUNIT_ASSERT_EQUALS( 10, flatData->iBitrate );
    EUNIT_ASSERT( err == KErrArgument );
    
    //bit set but no bound stream
    flatData->iBitrate  = 10;
    iCodec->SetBitrate( 20 );
    EUNIT_ASSERT_EQUALS( 20, flatData->iBitrate );
    
    //max bit rate
    flatData->iBitrate  = 10;
    err = iCodec->SetBitrate( 65000 );
    EUNIT_ASSERT_EQUALS( 65000, flatData->iBitrate );
    // bitrate will be set in comcodec
    flatData->iBitrate  = 10;
    err = iCodec->SetBitrate( 20 );
    EUNIT_ASSERT_EQUALS( 20, flatData->iBitrate );
    EUNIT_ASSERT( err == KErrNone );
    
    
    // add stream but not allowed to set because not bound stream
    CMceVideoStream* stream = CMceVideoStream::NewL();
    CleanupStack::PushL(stream);
    iCodec->iStream = stream;
    flatData->iBitrate  = 10;
    iCodec->SetBitrate( 20 );
    EUNIT_ASSERT_EQUALS( 20, flatData->iBitrate );
    
    //add bound stream and session
   
    CMceVideoStream* bound = CMceVideoStream::NewL();
    CleanupStack::PushL(bound);
    bound->AddCodecL(iCodec);
    stream->BindL( bound );
    CleanupStack::Pop(bound);
    flatData->iBitrate  = 10;
    iCodec->SetBitrate( 20 );
    EUNIT_ASSERT_EQUALS( 20, flatData->iBitrate );
    
    bound->RemoveCodecL(*iCodec);
    iCodec= NULL;
    CleanupStack::PopAndDestroy( stream);
    }

// ----------------------------------------------------------------------------
// CMceAvcCodecTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAvcCodecTest::ExternalizeTestL()
    {
    }

// ----------------------------------------------------------------------------
// CMceAvcCodecTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAvcCodecTest::InternalizeTestL()
    {
    }
