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

#include "CMceAmrCodecTest.h"
#include "mcestubs.h"

#include "mceamrcodec.h"
#include "mcecomaudiocodec.h"

#include "mcemanager.h"
#include "mceoutsession.h"
#include "mceaudiostream.h"


#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"

// ----------------------------------------------------------------------------
// CMceAmrCodecTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceAmrCodecTest::setUpL()
    {
    _LIT8( KAmr, "AMR" );
    TBuf8<KMceMaxSdpNameLength> sdpName( KAmr );
    iAMR = CMceAmrCodec::NewL(sdpName);				
    }

// ----------------------------------------------------------------------------
// CMceAmrCodecTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceAmrCodecTest::tearDown()
    {

    delete iAMR;
       
    }

// ----------------------------------------------------------------------------
// CMceAmrCodecTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceAmrCodecTest::suiteL()
    {
    CMceAmrCodecTest* suite = new CMceAmrCodecTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceAmrCodecTest,
    "CMceAmrCodecTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceAmrCodecTest", setUpL, SettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAmrCodecTest", setUpL, CloneTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAmrCodecTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAmrCodecTest", setUpL, InternalizeTestL, tearDown )
EUNIT_END_TEST_TABLE     
	
// ----------------------------------------------------------------------------
// CMceAmrCodecTest::SettersTestL
// ----------------------------------------------------------------------------
//
void CMceAmrCodecTest::SettersTestL()
    {
    CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iAMR->iFlatData );
    
    flatData->iSamplingFreq = 0;
 	iAMR->SetSamplingFreq( 8000 );
 	EUNIT_ASSERT_EQUALS( 8000, flatData->iSamplingFreq );
    
    flatData->iSamplingFreq = 0;
 	iAMR->SetSamplingFreq( 16000 );
 	EUNIT_ASSERT_EQUALS( 16000, flatData->iSamplingFreq );
 	
 	flatData->iSamplingFreq = 0;
 	iAMR->SetSamplingFreq( 16001 );
 	EUNIT_ASSERT_EQUALS( 0, flatData->iSamplingFreq );
 	
    _LIT8( KNoName, "NoName" );
    _LIT8( KSomeName, "SomeName" );
    TBuf8<KMceMaxSdpNameLength> sdpName( KNoName );
    TBuf8<KMceMaxSdpNameLength> sdpName2( KSomeName );
    flatData->iSdpName = sdpName;
    iAMR->SetSdpNameL( sdpName2 );
    EUNIT_ASSERT_EQUALS( KSomeName(), flatData->iSdpName );
    
    flatData->iEnableVAD = EFalse;
    iAMR->EnableVAD( ETrue );
    EUNIT_ASSERT( flatData->iEnableVAD );
   
    flatData->iPTime = 0;
    iAMR->SetPTime( 20 );
 	EUNIT_ASSERT_EQUALS( 20, flatData->iPTime );
   
    flatData->iMaxPTime = 0;
    iAMR->SetMaxPTime( 40 );
 	EUNIT_ASSERT_EQUALS( 40, flatData->iMaxPTime );
   
    flatData->iBitrate = 0;
    iAMR->SetBitrate( KMceAmrNbBitrate475 );
 	EUNIT_ASSERT_EQUALS( KMceAmrNbBitrate475, flatData->iBitrate );

    flatData->iAllowedBitrates = 0;
    iAMR->SetAllowedBitrates( 10 );
 	EUNIT_ASSERT_EQUALS( 10, flatData->iAllowedBitrates );
    
    flatData->iPayloadType = 96;
    iAMR->SetPayloadType( 10 );
 	EUNIT_ASSERT_EQUALS( 96, flatData->iPayloadType );
    
    iAMR->SetPayloadType( 101 );
 	EUNIT_ASSERT_EQUALS( 101, flatData->iPayloadType );
 	
 	// Allowed values are 4 or 5.
    flatData->iCodecMode = 0;
    iAMR->SetCodecMode( 10 );
 	EUNIT_ASSERT_EQUALS( 0, flatData->iCodecMode );
 	
 	iAMR->SetCodecMode( 4 );
 	EUNIT_ASSERT_EQUALS( 4, flatData->iCodecMode );
 	
 	iAMR->SetCodecMode( 5 );
 	EUNIT_ASSERT_EQUALS( 5, flatData->iCodecMode );
 	
 	iAMR->SetCodecMode( 6 );
 	EUNIT_ASSERT_EQUALS( 5, flatData->iCodecMode );
    }


// ----------------------------------------------------------------------------
// CMceAmrCodecTest::CloneTestL
// ----------------------------------------------------------------------------
//
void CMceAmrCodecTest::CloneTestL()
    {
    CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iAMR->iFlatData );
        
    CMceAudioCodec* clone = iAMR->CloneL();
    
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
// CMceAmrCodecTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAmrCodecTest::ExternalizeTestL()
    {
    }

// ----------------------------------------------------------------------------
// CMceAmrCodecTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAmrCodecTest::InternalizeTestL()
    {
    }
