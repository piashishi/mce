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

#include <e32def.h>
#include <e32base.h>
#include <digia/eunit/EUnitMacros.h>
#include "cmceamrwbcodectest.h"
#include "mcestubs.h"
#include "mceamrwbcodec.h"
#include "mcecomaudiocodec.h"


// ----------------------------------------------------------------------------
// CMceAmrWbCodecTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceAmrWbCodecTest::setUpL()
    {
    TBuf8< KMceMaxSdpNameLength > sdpName( KMceSDPNameAMRWB );
    iCodec = CMceAmrWbCodec::NewL( sdpName );				
    }

// ----------------------------------------------------------------------------
// CMceAmrWbCodecTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceAmrWbCodecTest::tearDown()
    {
    delete iCodec;
    iCodec = NULL;
    }

// ----------------------------------------------------------------------------
// CMceAmrWbCodecTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceAmrWbCodecTest::suiteL()
    {
    CMceAmrWbCodecTest* suite = new CMceAmrWbCodecTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;
    }
    
EUNIT_BEGIN_TEST_TABLE( 
    CMceAmrWbCodecTest,
    "CMceAmrWbCodecTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceAmrWbCodecTest", setUpL, SettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAmrWbCodecTest", setUpL, CloneTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAmrWbCodecTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAmrWbCodecTest", setUpL, InternalizeTestL, tearDown )
EUNIT_END_TEST_TABLE       
	
// ----------------------------------------------------------------------------
// CMceAmrWbCodecTest::SettersTestL
// ----------------------------------------------------------------------------
//
void CMceAmrWbCodecTest::SettersTestL()
    {
    CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iCodec->iFlatData );

    flatData->iSamplingFreq = 0;
 	iCodec->SetSamplingFreq( KMceAmrNbSamplingFreq );
 	EUNIT_ASSERT_EQUALS( KMceAmrNbSamplingFreq, flatData->iSamplingFreq );
    
    flatData->iSamplingFreq = 0;
 	iCodec->SetSamplingFreq( KMceAmrWbSamplingFreq );
 	EUNIT_ASSERT_EQUALS( KMceAmrWbSamplingFreq, flatData->iSamplingFreq );
 	
 	flatData->iSamplingFreq = 0;
 	// Try to set invalid value
 	iCodec->SetSamplingFreq( KMceAmrWbSamplingFreq + 1 );
 	EUNIT_ASSERT_EQUALS( 0, flatData->iSamplingFreq );
 	
    _LIT8( KNoName, "NoName" );
    _LIT8( KSomeName, "SomeName" );
    TBuf8<KMceMaxSdpNameLength> sdpName( KNoName );
    TBuf8<KMceMaxSdpNameLength> sdpName2( KSomeName );
    flatData->iSdpName = sdpName;
    iCodec->SetSdpNameL( sdpName2 );
    EUNIT_ASSERT_EQUALS( KSomeName(), flatData->iSdpName );
    
    flatData->iEnableVAD = EFalse;
    iCodec->EnableVAD( ETrue );
    EUNIT_ASSERT( flatData->iEnableVAD );
    iCodec->EnableVAD( EFalse );
    EUNIT_ASSERT( !flatData->iEnableVAD );

    flatData->iPTime = 0;
    iCodec->SetPTime( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iPTime );

    flatData->iMaxPTime = 0;
    iCodec->SetMaxPTime( 40 );
 	EUNIT_ASSERT_EQUALS( 40, flatData->iMaxPTime );



	// AMR codec's bitrates are not allowed for AMR-WB
	const TInt invalidBitrates[] = 
		{
		KMceAmrNbBitrate475,
		KMceAmrNbBitrate515,
		KMceAmrNbBitrate590,
		KMceAmrNbBitrate670,
		KMceAmrNbBitrate740,
		KMceAmrNbBitrate795,
		KMceAmrNbBitrate102,
		KMceAmrNbBitrate122,
		0
		};
	TInt i(0);
	flatData->iBitrate = 0;
	while ( invalidBitrates[i] )
		{
		flatData->iBitrate = 0;
    	EUNIT_ASSERT_EQUALS( KErrNotSupported,
    					   iCodec->SetBitrate( invalidBitrates[i] ) );
 		EUNIT_ASSERT_EQUALS( 0, flatData->iBitrate );
		++i;
		}


	// ARM-WB's bitrates
	const TInt validBitrates[] = 
		{
		KMceAmrWbBitrate660,
		KMceAmrWbBitrate885,
		KMceAmrWbBitrate1265,
		KMceAmrWbBitrate1425,
		KMceAmrWbBitrate1585,
		KMceAmrWbBitrate1825,
		KMceAmrWbBitrate1985,
		KMceAmrWbBitrate2305,
		KMceAmrWbBitrate2385,
		0
		};
	i = 0;
	while ( invalidBitrates[i] )
		{
		flatData->iBitrate = 0;
    	EUNIT_ASSERT_EQUALS( KErrNone,
    					   iCodec->SetBitrate( validBitrates[i] ) );
 		EUNIT_ASSERT_EQUALS( validBitrates[i], flatData->iBitrate );
		++i;
		}



	const TUint KAllowedBitrates = KMceAllowedAmrWbBitrate1825 |
								   KMceAllowedAmrWbBitrate2305;
	flatData->iAllowedBitrates = KAllowedBitrates;
	EUNIT_ASSERT_EQUALS( KErrArgument, iCodec->SetAllowedBitrates( 0x10101 ) );
	EUNIT_ASSERT_EQUALS( KAllowedBitrates, flatData->iAllowedBitrates );
	
	// Set such allowed bitrates, that it causes the current bitrate to be
	// decreased.
	flatData->iBitrate = KMceAmrWbBitrate2385;
	flatData->iAllowedBitrates = KMceAllowedAmrWbBitrateAll;
	EUNIT_ASSERT_EQUALS( KErrNone,
					   iCodec->SetAllowedBitrates( KAllowedBitrates ) );
	EUNIT_ASSERT_EQUALS( KAllowedBitrates, flatData->iAllowedBitrates );
	EUNIT_ASSERT_EQUALS( KMceAmrWbBitrate2305, flatData->iBitrate );



    flatData->iPayloadType = 96;
    iCodec->SetPayloadType( 10 );
 	EUNIT_ASSERT_EQUALS( 96, flatData->iPayloadType );
    
    iCodec->SetPayloadType( 101 );
 	EUNIT_ASSERT_EQUALS( 101, flatData->iPayloadType );
 	


    flatData->iCodecMode = 0;
    EUNIT_ASSERT_EQUALS( KErrNotSupported,
    				   iCodec->SetCodecMode( EMceBandwidthEfficient - 1 ) );
 	EUNIT_ASSERT_EQUALS( 0, flatData->iCodecMode );
    
 	EUNIT_ASSERT_EQUALS( KErrNone,
 					   iCodec->SetCodecMode( EMceBandwidthEfficient ) );
 	EUNIT_ASSERT_EQUALS( EMceBandwidthEfficient, flatData->iCodecMode );
 	
 	EUNIT_ASSERT_EQUALS( KErrNone,
 					   iCodec->SetCodecMode( EMceOctetAligned ) );
 	EUNIT_ASSERT_EQUALS( EMceOctetAligned, flatData->iCodecMode );
 	
 	EUNIT_ASSERT_EQUALS( KErrNotSupported,
 					   iCodec->SetCodecMode( EMceOctetAligned + 1 ) );
 	EUNIT_ASSERT_EQUALS( EMceOctetAligned, flatData->iCodecMode );
    }

// ----------------------------------------------------------------------------
// CMceAmrWbCodecTest::CloneTestL
// ----------------------------------------------------------------------------
//
void CMceAmrWbCodecTest::CloneTestL()
    {
    CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iCodec->iFlatData );
        
    CMceAudioCodec* clone = iCodec->CloneL();
    
    CMceComAudioCodec* cloneFlatData = 
        static_cast<CMceComAudioCodec*>( clone->iFlatData );
        
    EUNIT_ASSERT(flatData->iID.iAppId == cloneFlatData->iID.iAppId);
    EUNIT_ASSERT(flatData->iID.iId == cloneFlatData->iID.iId);
    EUNIT_ASSERT(flatData->iFmtpAttr != cloneFlatData->iFmtpAttr);
    EUNIT_ASSERT( *(flatData->iFmtpAttr) == *(cloneFlatData->iFmtpAttr) );
    EUNIT_ASSERT(flatData->iEnableVAD == cloneFlatData->iEnableVAD);
    EUNIT_ASSERT(flatData->iSamplingFreq == cloneFlatData->iSamplingFreq);
    EUNIT_ASSERT(flatData->iPTime == cloneFlatData->iPTime);
    EUNIT_ASSERT(flatData->iMaxPTime == cloneFlatData->iMaxPTime);
    EUNIT_ASSERT(flatData->iBitrate == cloneFlatData->iBitrate);
    EUNIT_ASSERT(flatData->iAllowedBitrates == cloneFlatData->iAllowedBitrates);
    EUNIT_ASSERT(flatData->iPayloadType == cloneFlatData->iPayloadType);
    EUNIT_ASSERT(flatData->iFourCC == cloneFlatData->iFourCC);
    delete clone;
    }

// ----------------------------------------------------------------------------
// CMceAmrWbCodecTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAmrWbCodecTest::ExternalizeTestL()
    {
    }

// ----------------------------------------------------------------------------
// CMceAmrWbCodecTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAmrWbCodecTest::InternalizeTestL()
    {
    }
