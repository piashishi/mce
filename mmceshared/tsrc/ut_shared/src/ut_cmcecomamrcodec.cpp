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
#include "ut_cmcecomamrcodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mceamrcodec.h>
#include <mmcccodecinformation.h>
#include <mmcccodecinformationfactory.h>
#include "mcecomamrcodec.h"
#include "mcemediamanager.h"

_LIT8( KDefaultAmrFmtp, "octet-align=0; mode-set=0,1,2,3,4,5,6,7" );

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComAMRCodec* UT_CMceComAMRCodec::NewL()
    {
    UT_CMceComAMRCodec* self = UT_CMceComAMRCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComAMRCodec* UT_CMceComAMRCodec::NewLC()
    {
    UT_CMceComAMRCodec* self = new( ELeave ) UT_CMceComAMRCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComAMRCodec::~UT_CMceComAMRCodec()
    {
  	delete iManager;
	delete iServer;
    delete iCodec;
    }

// Default constructor
UT_CMceComAMRCodec::UT_CMceComAMRCodec()
    {
    }

// Second phase construct
void UT_CMceComAMRCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComAMRCodec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    TMceComAudioCodecFactory factory;
    iCodec = static_cast<CMceComAMRCodec*>( 
        factory.CreateCodecLC( KMceSDPNameAMR() ) );
    CleanupStack::Pop( iCodec );
    } 

void UT_CMceComAMRCodec::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    delete iCodec;
	iCodec = NULL;
    }


void UT_CMceComAMRCodec::UT_CMceComAMRCodec_SetBitrateL()
    {
    iCodec->iBitrate = 0;
    // Sucess Cases
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrNbBitrate475 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate475 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrNbBitrate515 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate515 );
	
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrNbBitrate590 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate590 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrNbBitrate670 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate670 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrNbBitrate740 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate740 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrNbBitrate795 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate795 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrNbBitrate102 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate102 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrNbBitrate122 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate122 );

    // Failure Case
    iCodec->iBitrate = 0;
    EUNIT_ASSERT( iCodec->SetBitrate( 123456 ) != KErrNone ); 
    
    // Value of Bit-rate is not set and remain as before if set.   
    EUNIT_ASSERT( iCodec->iBitrate == 0 );
    }

void UT_CMceComAMRCodec::UT_CMceComAMRCodec_SetAllowedBitratesL()
    {
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 0 ) != KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate122 );
    
    //iBitrate = KMceAmrNbBitrate122;
    
    // SET AllowBitrate All
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrateAll ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate122 );

    //Set KMceAllowedAmrNbBitrate122
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate122 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate122 );

    //Set KMceAllowedAmrNbBitrate102
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate102 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate102 );

	//Set KMceAllowedAmrNbBitrate795
	EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate795 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate795 );

    //Set KMceAllowedAmrNbBitrate740
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate740 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate740 );

	//Set KMceAllowedAmrNbBitrate670
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate670 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate670 );

	//Set KMceAllowedAmrNbBitrate590
	EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate590 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate590 );

    //Set KMceAllowedAmrNbBitrate515
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate515 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate515 );
       
    //Set KMceAllowedAmrNbBitrate475
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrNbBitrate475 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrNbBitrate475 );
    
    }

void UT_CMceComAMRCodec::UT_CMceComAMRCodec_SetCodecModeL()
    {
    const TUint KInvalidCodecMode( 10 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetCodecMode( KInvalidCodecMode ) );
    EUNIT_ASSERT( KInvalidCodecMode != iCodec->iCodecMode );
    
    EUNIT_ASSERT( KErrNone == 
        iCodec->SetCodecMode( EMceBandwidthEfficient ) );
    EUNIT_ASSERT( EMceBandwidthEfficient == iCodec->iCodecMode );
    
    EUNIT_ASSERT( KErrNone == 
        iCodec->SetCodecMode( EMceOctetAligned ) );
    EUNIT_ASSERT( EMceOctetAligned == iCodec->iCodecMode );
    }

void UT_CMceComAMRCodec::UT_CMceComAMRCodec_SetPayloadTypeL()
    {
    const TUint8 KInvalidPayloadType( KMinDynPayloadType - 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetPayloadType( KInvalidPayloadType ) );
    EUNIT_ASSERT( KInvalidPayloadType != iCodec->iPayloadType );
    
    EUNIT_ASSERT( KErrNone == 
        iCodec->SetPayloadType( KMinDynPayloadType ) );
    EUNIT_ASSERT( KMinDynPayloadType == iCodec->iPayloadType );
    }
    
void UT_CMceComAMRCodec::UT_CMceComAMRCodec_GetMaxBitRateL()
    {
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrNbBitrate122 );
    iCodec->iAllowedBitrates = 0;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == 0 );
    
    iCodec->iAllowedBitrates = 0;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == 0 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate122;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrNbBitrate122 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate102;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrNbBitrate102 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate795;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrNbBitrate795 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate740;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrNbBitrate740 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate670;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrNbBitrate670 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate590;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrNbBitrate590 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate515;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrNbBitrate515 );

	iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate475;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrNbBitrate475 );
    
    }

void UT_CMceComAMRCodec::UT_CMceComAMRCodec_ResolveAllowedBitratesL()
    {
    TUint allowedBitrates = 0;

    const TUint KAllowedBitrate1 = KMceAmrNbBitrate475;
    const TUint KAllowedBitrate2 = KMceAmrNbBitrate515;
    const TUint KAllowedBitrate3 = KMceAmrNbBitrate590;
    const TUint KAllowedBitrate4 = KMceAmrNbBitrate670;
    const TUint KAllowedBitrate5 = KMceAmrNbBitrate740;
    const TUint KAllowedBitrate6 = KMceAmrNbBitrate795;
	const TUint KAllowedBitrate7 = KMceAmrNbBitrate102;
    const TUint KAllowedBitrate8 = KMceAmrNbBitrate122;

    const TUint KNotAllowedBitrate = KMceAmrNbBitrate122 + 50;

	// Allowed Bit Rate Test
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate1, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrNbBitrate475 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate2, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrNbBitrate515 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate3, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrNbBitrate590 );
    

    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate4, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrNbBitrate670 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate5, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrNbBitrate740 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate6, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrNbBitrate795 );
    

    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate7, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrNbBitrate102 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate8, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrNbBitrateAll );

    // Not Allowed Bit Rate Test
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KNotAllowedBitrate,  allowedBitrates ) != KErrNone ); 
    
    }

void UT_CMceComAMRCodec::UT_CMceComAMRCodec_SetSamplingFreqL()
    {
    const TUint KInvalidSamplingFreq( 5000 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetSamplingFreq( KInvalidSamplingFreq ) );
    EUNIT_ASSERT( KInvalidSamplingFreq != iCodec->iSamplingFreq );
    
    EUNIT_ASSERT( KErrNone == 
        iCodec->SetSamplingFreq( KMceAmrNbSamplingFreq ) );
    EUNIT_ASSERT( KMceAmrNbSamplingFreq == iCodec->iSamplingFreq );
    
    EUNIT_ASSERT( KErrNone == 
        iCodec->SetSamplingFreq( KMceAmrWbSamplingFreq ) );
    EUNIT_ASSERT( KMceAmrWbSamplingFreq == iCodec->iSamplingFreq );
    }

void UT_CMceComAMRCodec::UT_CMceComAMRCodec_SetPTimeL()
    {
    const TUint KInvalidPTime( 10 );
    EUNIT_ASSERT( KErrNotSupported == iCodec->SetPTime( KInvalidPTime ) );
    EUNIT_ASSERT( KInvalidPTime != iCodec->iPTime );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetPTime( KMceDefaultPtime ) );
    EUNIT_ASSERT( KMceDefaultPtime == iCodec->iPTime );
    }

void UT_CMceComAMRCodec::UT_CMceComAMRCodec_SetMaxPTimeL()
    {
    const TUint KInvalidMaxPTime( KMceDefaultMaxPtime + 1 );
    EUNIT_ASSERT( KErrNotSupported == 
        iCodec->SetMaxPTime( KInvalidMaxPTime ) );
    EUNIT_ASSERT( KInvalidMaxPTime != iCodec->iMaxPTime );
    
    EUNIT_ASSERT( KErrNone == iCodec->SetMaxPTime( KMceDefaultMaxPtime ) );
    EUNIT_ASSERT( KMceDefaultMaxPtime == iCodec->iMaxPTime );
    }

void UT_CMceComAMRCodec::UT_CMceComAMRCodec_DoMccValidateLL()
    {
    CMccCodecInformationFactory* InfoCodecFactory;
    InfoCodecFactory = CMccCodecInformationFactory::NewL();
    CleanupStack::PushL( InfoCodecFactory );
    
    CMccCodecInformation* codec = 
        InfoCodecFactory->CreateCodecInformationL( iCodec->iSdpName );

	CleanupStack::PushL( codec );
   	// Validation passes due to no codec mode difference
   	codec->SetAllowedBitrates( KMceAllowedAmrNbBitrate122 );
	iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate122;
	
	CMceSrvStream *srvStram = NULL;
		
	EUNIT_ASSERT( iCodec->DoMccValidateL( *codec, *srvStram, EMceRoleAnswerer ) == NULL);
    
    // Validation leaves due to codec mode difference
    iCodec->iAllowedBitrates =KMceAllowedAmrNbBitrate122 + 20;   
    codec->SetAllowedBitrates( KMceAllowedAmrNbBitrate122 );    
    EUNIT_ASSERT_LEAVE( iCodec->DoMccValidateL( *codec, *srvStram, EMceRoleAnswerer ));
    codec->SetAllowedBitrates( KMceAllowedAmrNbBitrate122 );
	iCodec->iAllowedBitrates = KMceAllowedAmrNbBitrate122;
    iCodec->iCodecMode = EOctetAligned;
    codec->SetCodecMode(EBandwidthEfficient);
    EUNIT_ASSERT_LEAVE( iCodec->DoMccValidateL( *codec, *srvStram, EMceRoleAnswerer ));
    CleanupStack::PopAndDestroy( codec );
    CleanupStack::PopAndDestroy( InfoCodecFactory );
    }

void UT_CMceComAMRCodec::UT_CMceComAMRCodec_DoSetDefaultFmtpAttributeLL()
    {
   	iCodec->DoSetDefaultFmtpAttributeL();
	EUNIT_ASSERT( *iCodec->iFmtpAttr == KDefaultAmrFmtp );
    }


void UT_CMceComAMRCodec::UT_CMceComAMRCodec_CloneLL()
    {
    CMceComAudioCodec* clone = NULL;
    clone = iCodec->CloneL();
    // Ensure Clone is not Null
    EUNIT_ASSERT( clone );
    // Ensure Clone is AMR-Codec
    EUNIT_ASSERT( clone->iSdpName == iCodec->iSdpName );
    delete clone;
    }



	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComAMRCodec,
    "CMceComAMRCodec tests",
    "UNIT" )

EUNIT_TEST (
    "SetBitrate test",
    "CMceComAMRCodec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComAMRCodec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "SetCodecMode test",
    "CMceComAMRCodec",
    "SetCodecMode",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_SetCodecModeL, Teardown)

EUNIT_TEST (
    "SetPayloadType test",
    "CMceComAMRCodec",
    "SetPayloadType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_SetPayloadTypeL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComAMRCodec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "ResolveAllowedBitrates test",
    "CMceComAMRCodec",
    "ResolveAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_ResolveAllowedBitratesL, Teardown)

EUNIT_TEST (
    "SetSamplingFreq test",
    "CMceComAMRCodec",
    "SetSamplingFreq",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_SetSamplingFreqL, Teardown)

EUNIT_TEST (
    "SetPTime test",
    "CMceComAMRCodec",
    "SetPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_SetPTimeL, Teardown)

EUNIT_TEST (
    "SetMaxPTime test",
    "CMceComAMRCodec",
    "SetMaxPTime",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_SetMaxPTimeL, Teardown)

EUNIT_TEST (
    "DoMccValidateL test",
    "CMceComAMRCodec",
    "DoMccValidateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_DoMccValidateLL, Teardown)

EUNIT_TEST (
    "DoSetDefaultFmtpAttributeL test",
    "CMceComAMRCodec",
    "DoSetDefaultFmtpAttributeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_DoSetDefaultFmtpAttributeLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComAMRCodec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRCodec_CloneLL, Teardown)

EUNIT_END_TEST_TABLE



//  END OF FILE
