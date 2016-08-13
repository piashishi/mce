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
#include "mceh263codectest.h"
#include "mcestubs.h"

#include "mceh263codec.h"
#include "mcecomvideocodec.h"

#include "mcemanager.h"
#include "mceoutsession.h"
#include "mcevideostream.h"


#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"

// ----------------------------------------------------------------------------
// CMceH263CodecTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceH263CodecTest::setUpL()
    {
    _LIT8( Kh263, "H263" );
    TBuf8<KMceMaxSdpNameLength> sdpName( Kh263 );
    iH263 = CMceH263Codec::NewL(sdpName);				
    }

// ----------------------------------------------------------------------------
// CMceH263CodecTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceH263CodecTest::tearDown()
    {
	if (iH263)
		{
		delete iH263;
		iH263 = NULL;
		}
    }

// ----------------------------------------------------------------------------
// CMceH263CodecTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceH263CodecTest::suiteL()
    {
    CMceH263CodecTest* suite = new CMceH263CodecTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceH263CodecTest,
    "CMceH263CodecTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceH263CodecTest", setUpL, SettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceH263CodecTest", setUpL, CompareSdpIndexTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceH263CodecTest", setUpL, CloneTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceH263CodecTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceH263CodecTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceH263CodecTest", setUpL, SetAllowBitRatesTestL, tearDown )
EUNIT_END_TEST_TABLE 
	
// ----------------------------------------------------------------------------
// CMceH263CodecTest::SettersTestL
// ----------------------------------------------------------------------------
//
void CMceH263CodecTest::SettersTestL()
    {
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iH263->iFlatData );
        
    flatData->iFrameRate = 0;
 	iH263->SetFrameRateL( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iFrameRate );
	
	flatData->iMaxBitRate = 0;
 	TRAPD( error, iH263->SetMaxBitrateL( 12 ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( error )
    EUNIT_ASSERT( error == KErrNotSupported );
 	//KMceH263Level10Bitrate
 	flatData->iMaxBitRate = 0;
 	iH263->SetMaxBitrateL( KMceH263Level10Bitrate );
 	EUNIT_ASSERT_EQUALS( KMceH263Level10Bitrate, flatData->iMaxBitRate );
	//KMceH263Level45Bitrate
	flatData->iMaxBitRate = 0;
 	iH263->SetMaxBitrateL( KMceH263Level45Bitrate );
 	EUNIT_ASSERT_EQUALS( KMceH263Level45Bitrate, flatData->iMaxBitRate );
 	
	flatData->iAllowedResolutions = 0;
 	iH263->SetAllowedResolutionsL( 100 );
 	EUNIT_ASSERT_EQUALS( 100, flatData->iAllowedResolutions );
	
	flatData->iResolutionWidth = 0;
	TSize resoulutionSize;
	resoulutionSize.iWidth=20;
	resoulutionSize.iHeight=30;
 	iH263->SetResolutionL( resoulutionSize );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iResolutionWidth );
	EUNIT_ASSERT_EQUALS( 30, flatData->iResolutionHeight );


	flatData->iAllowedFrameRates = 0;
 	iH263->SetAllowedFrameRatesL( 50 );
 	EUNIT_ASSERT_EQUALS( 50, flatData->iAllowedFrameRates );
	
	
    _LIT8( KNoName, "NoName" );
    _LIT8( KSomeName, "SomeName" );
    TBuf8<KMceMaxSdpNameLength> sdpName( KNoName );
    TBuf8<KMceMaxSdpNameLength> sdpName2( KSomeName );
    flatData->iSdpName = sdpName;
    iH263->SetSdpNameL( sdpName2 );
    EUNIT_ASSERT_EQUALS( KSomeName(), flatData->iSdpName );
    
    flatData->iPayloadType = 0;
    iH263->SetPayloadType( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iPayloadType );
    
    flatData->iCodecMode = 0;
    iH263->SetCodecMode( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iCodecMode );

 	
    const TUid id = TUid::Uid( 0 );
    TRAPD( error1, iH263->SetPreferredEncodingDecodingDeviceL( id ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( error1 )
    EUNIT_ASSERT( error1 == KErrNotSupported );


    _LIT8( KConfigKey, "configkey" );
    TRAPD( error2, iH263->SetConfigKeyL( KConfigKey ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( error2 )
    EUNIT_ASSERT( error2 == KErrNotSupported );
 	
    }

// ----------------------------------------------------------------------------
// CMceH263CodecTest::CompareSdpIndexTestL
// ----------------------------------------------------------------------------
//
void CMceH263CodecTest::CompareSdpIndexTestL()
    {
    _LIT8( Kh263, "H263" );
    TBuf8<KMceMaxSdpNameLength> sdpName( Kh263 );
    CMceH263Codec* h263Codec1 = CMceH263Codec::NewLC(sdpName);
    CMceH263Codec* h263Codec2 = CMceH263Codec::NewLC(sdpName);

    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iH263->iFlatData );
        
    CMceComVideoCodec* flatData1 = 
        static_cast<CMceComVideoCodec*>( h263Codec1->iFlatData );
        
        
    CMceComVideoCodec* flatData2 = 
        static_cast<CMceComVideoCodec*>( h263Codec2->iFlatData );
        
        
    flatData1->iCodecSdpIndex = 0;
    flatData2->iCodecSdpIndex = 0;
    EUNIT_ASSERT( flatData->CompareSdpIndex(*flatData1, *flatData2) == 1 );
    
    flatData1->iCodecSdpIndex = 1;
    flatData2->iCodecSdpIndex = 2;
    EUNIT_ASSERT( flatData->CompareSdpIndex(*flatData1, *flatData2) == -1 );
    
    flatData1->iCodecSdpIndex = 2;
    flatData2->iCodecSdpIndex = 1;
    EUNIT_ASSERT( flatData->CompareSdpIndex(*flatData1, *flatData2) == 1 );
    
    CleanupStack::PopAndDestroy( h263Codec2 );
    CleanupStack::PopAndDestroy( h263Codec1 );	
    }
    
// ----------------------------------------------------------------------------
// CMceH263CodecTest::CloneTestL
// ----------------------------------------------------------------------------
//
void CMceH263CodecTest::CloneTestL()
    {
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iH263->iFlatData );
        
    CMceVideoCodec* clone = iH263->CloneL();
    
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
// CMceH263CodecTest::SetAllowBitRatesTestL()
// ----------------------------------------------------------------------------
//
void CMceH263CodecTest::SetAllowBitRatesTestL()
    {
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iH263->iFlatData );
    // bit rates is equal so no setting need    
    flatData->iAllowedBitrates  = 0;
 	TInt err = iH263->SetAllowedBitrates( 0 );
 	EUNIT_ASSERT_EQUALS( 0, flatData->iAllowedBitrates );
	EUNIT_ASSERT( err == KErrNone );
	
	flatData->iAllowedBitrates  = 10;
 	err = iH263->SetAllowedBitrates( 0 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iAllowedBitrates );
	EUNIT_ASSERT( err == KErrArgument );
	
	//bit set but no bound stream
    flatData->iAllowedBitrates  = 10;
 	iH263->SetAllowedBitrates( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iAllowedBitrates );
 	
 	//max bit rate
 	flatData->iAllowedBitrates  = 10;
 	err = iH263->SetAllowedBitrates( 65000 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iAllowedBitrates );
 	EUNIT_ASSERT( err == KErrArgument );
 	// bitrate will be set in comcodec
 	flatData->iAllowedBitrates  = 10;
 	flatData->iBitrate  =65000;
 	err = iH263->SetAllowedBitrates( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iAllowedBitrates );
 	EUNIT_ASSERT( err == KErrNone );
 	
 	
 	// add stream but not allowed to set because not bound stream
	CMceVideoStream* stream = CMceVideoStream::NewL();
	CleanupStack::PushL(stream);
	iH263->iStream = stream;
	flatData->iAllowedBitrates  = 10;
 	iH263->SetAllowedBitrates( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iAllowedBitrates );
    
    //add bound stream and session
   
    CMceVideoStream* bound = CMceVideoStream::NewL();
    CleanupStack::PushL(bound);
    bound->AddCodecL(iH263);
    stream->BindL( bound );
    CleanupStack::Pop(bound);
    flatData->iAllowedBitrates  = 10;
 	iH263->SetAllowedBitrates( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iAllowedBitrates );
    
    bound->RemoveCodecL(*iH263);
    iH263= NULL;
    CleanupStack::PopAndDestroy( stream);
	
    }
// ----------------------------------------------------------------------------
// CMceH263CodecTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceH263CodecTest::ExternalizeTestL()
    {
    }

// ----------------------------------------------------------------------------
// CMceH263CodecTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceH263CodecTest::InternalizeTestL()
    {
    }
