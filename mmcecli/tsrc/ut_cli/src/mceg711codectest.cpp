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
#include "mceg711codectest.h"
#include "mcestubs.h"

#include "mceg711codec.h"
#include "mcecomaudiocodec.h"

#include "mcemanager.h"
#include "mceoutsession.h"
#include "mceaudiostream.h"


#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"

// ----------------------------------------------------------------------------
// CMceG711CodecTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceG711CodecTest::setUpL()
    {
    _LIT8( KG711, "G711" );
    TBuf8<KMceMaxSdpNameLength> sdpName( KG711 );
    iG711 = CMceG711Codec::NewL(sdpName);				
    }

// ----------------------------------------------------------------------------
// CMceG711CodecTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceG711CodecTest::tearDown()
    {

    delete iG711;
       
    }

// ----------------------------------------------------------------------------
// CMceG711CodecTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceG711CodecTest::suiteL()
    {
    CMceG711CodecTest* suite = new CMceG711CodecTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceG711CodecTest,
    "CMceG711CodecTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceG711CodecTest", setUpL, SettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceG711CodecTest", setUpL, CloneTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceG711CodecTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceG711CodecTest", setUpL, InternalizeTestL, tearDown )
EUNIT_END_TEST_TABLE 
	
// ----------------------------------------------------------------------------
// CMceG711CodecTest::SettersTestL
// ----------------------------------------------------------------------------
//
void CMceG711CodecTest::SettersTestL()
    {
    CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iG711->iFlatData );
    
    flatData->iSamplingFreq = 0;
 	iG711->SetSamplingFreq( 8000 );
 	EUNIT_ASSERT_EQUALS( 8000, flatData->iSamplingFreq );
    
    flatData->iSamplingFreq = 0;
 	iG711->SetSamplingFreq( 8001 );
 	EUNIT_ASSERT_EQUALS( 0, flatData->iSamplingFreq );
 	
    _LIT8( KNoName, "NoName" );
    _LIT8( KSomeName, "SomeName" );
    TBuf8<KMceMaxSdpNameLength> sdpName( KNoName );
    TBuf8<KMceMaxSdpNameLength> sdpName2( KSomeName );
    flatData->iSdpName = sdpName;
    iG711->SetSdpNameL( sdpName2 );
    EUNIT_ASSERT_EQUALS( KSomeName(), flatData->iSdpName );
    
    flatData->iEnableVAD = EFalse;
    iG711->EnableVAD( ETrue );
    EUNIT_ASSERT( flatData->iEnableVAD );
    
    flatData->iPTime = 0;
    iG711->SetPTime( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iPTime );
    
    flatData->iMaxPTime = 0;
    iG711->SetMaxPTime( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iMaxPTime );
    
    flatData->iBitrate = 0;
    iG711->SetBitrate( KMceG711Bitrate64 );
 	EUNIT_ASSERT_EQUALS( KMceG711Bitrate64, flatData->iBitrate );
    
    flatData->iAllowedBitrates = 0;
    iG711->SetAllowedBitrates( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iAllowedBitrates );
    
    flatData->iPayloadType = 0;
    iG711->SetPayloadType( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iPayloadType );
    
    flatData->iCodecMode = 0;
    iG711->SetCodecMode( KMceG711PCMU );
 	EUNIT_ASSERT_EQUALS( KMceG711PCMU, flatData->iCodecMode );
    }


// ----------------------------------------------------------------------------
// CMceG711CodecTest::CloneTestL
// ----------------------------------------------------------------------------
//
void CMceG711CodecTest::CloneTestL()
    {
    CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iG711->iFlatData );
        
    CMceAudioCodec* clone = iG711->CloneL();
    
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
// CMceG711CodecTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceG711CodecTest::ExternalizeTestL()
    {
    }

// ----------------------------------------------------------------------------
// CMceG711CodecTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceG711CodecTest::InternalizeTestL()
    {
    }
