/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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




//  CLASS HEADER
#include "ut_cmcecomilbccodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mceilbccodec.h>
#include "mcecomilbccodec.h"
#include "mcemediamanager.h"

const TUint KMceTestiLBCMode30FrameSize = 30;

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComiLBCCodec* UT_CMceComiLBCCodec::NewL()
    {
    UT_CMceComiLBCCodec* self = UT_CMceComiLBCCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComiLBCCodec* UT_CMceComiLBCCodec::NewLC()
    {
    UT_CMceComiLBCCodec* self = new( ELeave ) UT_CMceComiLBCCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComiLBCCodec::~UT_CMceComiLBCCodec()
    {
    delete iManager;
	delete iServer;
    delete iCodec;
    }

// Default constructor
UT_CMceComiLBCCodec::UT_CMceComiLBCCodec()
    {
    }

// Second phase construct
void UT_CMceComiLBCCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComiLBCCodec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    TMceComAudioCodecFactory factory;
    iCodec = static_cast<CMceComiLBCCodec*>( 
        factory.CreateCodecLC( KMceSDPNameiLBC() ) );
    CleanupStack::Pop( iCodec );
    }

void UT_CMceComiLBCCodec::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    delete iCodec;
	iCodec = NULL;
    }


void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_SetBitrateL()
    {
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_SetAllowedBitratesL()
    {
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_SetCodecModeL()
    {
    const TUint KInvalidCodecMode( 10 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetCodecMode( KInvalidCodecMode ) );
    EUNIT_ASSERT( KInvalidCodecMode != iCodec->iCodecMode );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetCodecMode( KiLBCodecMode ) );
    EUNIT_ASSERT( KiLBCodecMode == iCodec->iCodecMode );
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_SetPayloadTypeL()
    {
    const TUint8 KInvalidPayloadType( KMinDynPayloadType - 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetPayloadType( KInvalidPayloadType ) );
    EUNIT_ASSERT( KInvalidPayloadType != iCodec->iPayloadType );
    
    EUNIT_ASSERT( KErrNone == 
        iCodec->SetPayloadType( KMinDynPayloadType ) );
    EUNIT_ASSERT( KMinDynPayloadType == iCodec->iPayloadType );
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_GetMaxBitRateL()
    {
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_SetPTimeL()
    {
    const TUint KInvalidPTime( KMceTestiLBCMode30FrameSize - 1 );
    EUNIT_ASSERT( KErrNotSupported == iCodec->SetPTime( KInvalidPTime ) );
    EUNIT_ASSERT( KInvalidPTime != iCodec->iPTime );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetPTime( KMceiLBCDefaultPtime ) );
    EUNIT_ASSERT( KMceiLBCDefaultPtime == iCodec->iPTime );
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_SetMaxPTimeL()
    {
    const TUint KInvalidMaxPTime( KMceiLBCDefaultMaxPtime + 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetMaxPTime( KInvalidMaxPTime ) );
    EUNIT_ASSERT( KInvalidMaxPTime != iCodec->iMaxPTime );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetMaxPTime( KMceiLBCDefaultMaxPtime ) );
    EUNIT_ASSERT( KMceiLBCDefaultMaxPtime == iCodec->iMaxPTime );
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_DoMccEncodeLL()
    {
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_DoMccValidateLL()
    {
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_DoMccAdjustLL()
    {
    }

void UT_CMceComiLBCCodec::UT_CMceComiLBCCodec_DoSetDefaultFmtpAttributeLL()
    {
    }


	
//  TEST TABLE


EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComiLBCCodec,
    "CMceComiLBCCodec tests",
    "UNIT" )

EUNIT_TEST (
    "SetBitrate test",
    "CMceComiLBCCodec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComiLBCCodec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "SetCodecMode test",
    "CMceComiLBCCodec",
    "SetCodecMode",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_SetCodecModeL, Teardown)

EUNIT_TEST (
    "SetPayloadType test",
    "CMceComiLBCCodec",
    "SetPayloadType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_SetPayloadTypeL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComiLBCCodec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "SetPTime test",
    "CMceComiLBCCodec",
    "SetPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_SetPTimeL, Teardown)

EUNIT_TEST (
    "SetMaxPTime test",
    "CMceComiLBCCodec",
    "SetMaxPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_SetMaxPTimeL, Teardown)

EUNIT_TEST (
    "DoMccEncodeL test",
    "CMceComiLBCCodec",
    "DoMccEncodeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_DoMccEncodeLL, Teardown)

EUNIT_TEST (
    "DoMccValidateL test",
    "CMceComiLBCCodec",
    "DoMccValidateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_DoMccValidateLL, Teardown)

EUNIT_TEST (
    "DoMccAdjustL test",
    "CMceComiLBCCodec",
    "DoMccAdjustL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_DoMccAdjustLL, Teardown)

EUNIT_TEST (
    "DoSetDefaultFmtpAttributeL test",
    "CMceComiLBCCodec",
    "DoSetDefaultFmtpAttributeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComiLBCCodec_DoSetDefaultFmtpAttributeLL, Teardown)

EUNIT_END_TEST_TABLE


//  END OF FILE
