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
#include "UT_CMceComAMRWbCodec.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include <mceamrcodec.h>
#include <mceamrwbcodec.h>

#include <mmcccodecinformation.h>
#include <mmcccodecinformationfactory.h>
#include "mcecomamrcodec.h"
#include "mcecomamrwbcodec.h"
#include "mcemediamanager.h"
#include "mcecomaudiostream.h"


_LIT8( KDefaultAmrWbFmtp, "octet-align=0; mode-set=0,1,2,3,4,5,6,7,8" );

//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComAMRWbCodec* UT_CMceComAMRWbCodec::NewL()
    {
    UT_CMceComAMRWbCodec* self = UT_CMceComAMRWbCodec::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComAMRWbCodec* UT_CMceComAMRWbCodec::NewLC()
    {
    UT_CMceComAMRWbCodec* self = new( ELeave ) UT_CMceComAMRWbCodec();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComAMRWbCodec::~UT_CMceComAMRWbCodec()
    {
  	delete iManager;
	delete iServer;
    delete iCodec;
    }

// Default constructor
UT_CMceComAMRWbCodec::UT_CMceComAMRWbCodec()
    {
    }

// Second phase construct
void UT_CMceComAMRWbCodec::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComAMRWbCodec::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );
    
    TMceComAudioCodecFactory factory;
    iCodec = static_cast<CMceComAMRWbCodec*>( 
        factory.CreateCodecLC( KMceSDPNameAMRWB() ) );
        
    CleanupStack::Pop( iCodec );
    } 

void UT_CMceComAMRWbCodec::Teardown()
    {
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    delete iCodec;
	iCodec = NULL;
    }


void UT_CMceComAMRWbCodec::UT_CMceComAMRWbCodec_SetBitrateL()
    {
    iCodec->iBitrate = 0;

    // Sucess Cases
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrWbBitrate660 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate660 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrWbBitrate885 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate885 );
	
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrWbBitrate1265 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1265 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrWbBitrate1425 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1425 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrWbBitrate1585 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1585 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrWbBitrate1825 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1825 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrWbBitrate1985 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1985 );
    
    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrWbBitrate2305 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate2305 );

    EUNIT_ASSERT( iCodec->SetBitrate( KMceAmrWbBitrate2385 ) == KErrNone );    
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate2385 );

    // Failure Case
    iCodec->iBitrate = 0;
    EUNIT_ASSERT( iCodec->SetBitrate( 123456 ) != KErrNone ); 
    
    // Value of Bit-rate is not set and remain as before if set.   
    EUNIT_ASSERT( iCodec->iBitrate == 0 );

    }


void UT_CMceComAMRWbCodec::UT_CMceComAMRWbCodec_SetAllowedBitratesL()
    {
	// Failure Case: Default value will retain.
	// TBD: Store the Default value in Constructor of Actual Class implementation.  
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( 0 ) != KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate2385 );
    
    //iBitrate = KMceAmrWbBitrate2385;
    
    // SET AllowBitrate All
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrWbBitrateAll ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate2385 );

    //Set KMceAllowedAmrWbBitrate2385
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrWbBitrate2385 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate2385 );

    //Set KMceAllowedAmrWbBitrate2305
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrWbBitrate1985 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1985 );

	//Set KMceAllowedAmrWbBitrate1985
	EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrWbBitrate1825 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1825 );

    //Set KMceAllowedAmrWbBitrate1825
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrWbBitrate1585 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1585 );

	//Set KMceAllowedAmrWbBitrate1425
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrWbBitrate1425 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1425 );

	//Set KMceAllowedAmrWbBitrate1265
	EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrWbBitrate1265 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate1265 );

    //Set KMceAllowedAmrWbBitrate885
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrWbBitrate885 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate885 );
       
    //Set KMceAllowedAmrWbBitrate660
    EUNIT_ASSERT( iCodec->SetAllowedBitrates( KMceAllowedAmrWbBitrate660 ) == KErrNone );
    EUNIT_ASSERT( iCodec->iBitrate == KMceAmrWbBitrate660 );
    }

    
void UT_CMceComAMRWbCodec::UT_CMceComAMRWbCodec_GetMaxBitRateL()
    {
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate2385 );
    iCodec->iAllowedBitrates = 0;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == 0 );
    
    iCodec->iAllowedBitrates = 0;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == 0 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate2385;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate2385 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate2305;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate2305 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate1985;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate1985 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate1825;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate1825 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate1585;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate1585 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate1425;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate1425 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate1265;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate1265 );

	iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate885;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate885 );
    
    iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate660;
    EUNIT_ASSERT( iCodec->GetMaxBitRate() == KMceAmrWbBitrate660 );
    }

void UT_CMceComAMRWbCodec::UT_CMceComAMRWbCodec_ResolveAllowedBitratesL()
    {
    //TBD
    TUint allowedBitrates = 0;

    const TUint KAllowedBitrate1 = KMceAmrWbBitrate660;
    const TUint KAllowedBitrate2 = KMceAmrWbBitrate885;
    const TUint KAllowedBitrate3 = KMceAmrWbBitrate1265;
    const TUint KAllowedBitrate4 = KMceAmrWbBitrate1425;
    const TUint KAllowedBitrate5 = KMceAmrWbBitrate1585;
    const TUint KAllowedBitrate6 = KMceAmrWbBitrate1825;
	const TUint KAllowedBitrate7 = KMceAmrWbBitrate1985;
    const TUint KAllowedBitrate8 = KMceAmrWbBitrate2305;
    const TUint KAllowedBitrate9 = KMceAmrWbBitrate2385;
    const TUint KNotAllowedBitrate = KMceAmrWbBitrate2385 + 50;

	// Allowed Bit Rate Test
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate1, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrWbBitrate660 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate2, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrWbBitrate885 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate3, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrWbBitrate1265 );
    

    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate4, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrWbBitrate1425 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate5, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrWbBitrate1585 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate6, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrWbBitrate1825 );
    

    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate7, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrWbBitrate1985 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate8, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrWbBitrate2305 );
    
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KAllowedBitrate9, allowedBitrates ) == KErrNone );
    EUNIT_ASSERT( allowedBitrates == KMceAllowedAmrWbBitrateAll );

    // Not Allowed Bit Rate Test
    EUNIT_ASSERT( iCodec->ResolveAllowedBitrates( KNotAllowedBitrate,  allowedBitrates ) != KErrNone ); 
    }


void UT_CMceComAMRWbCodec::UT_CMceComAMRWbCodec_DoMccValidateLL()
    {
    CMccCodecInformationFactory* InfoCodecFactory;
    InfoCodecFactory = CMccCodecInformationFactory::NewL();
    CleanupStack::PushL( InfoCodecFactory );
    
    CMccCodecInformation* codec = 
        InfoCodecFactory->CreateCodecInformationL( iCodec->iSdpName );
	
	CleanupStack::PushL( codec );
    
   	// Validation passes due to no codec mode difference
   	codec->SetAllowedBitrates( KMceAllowedAmrWbBitrate2385 );
	iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate2385;
	
	CMceSrvStream *srvStram = NULL;
		
	EUNIT_ASSERT( iCodec->DoMccValidateL( *codec, *srvStram, EMceRoleAnswerer ) == NULL);
    
    // Validation leaves due to codec mode difference
    iCodec->iAllowedBitrates =KMceAllowedAmrWbBitrate2385 + 20;   
    codec->SetAllowedBitrates( KMceAllowedAmrWbBitrate2385 );    
    EUNIT_ASSERT( iCodec->DoMccValidateL( *codec, *srvStram, EMceRoleAnswerer ) == NULL);
    codec->SetAllowedBitrates( KMceAllowedAmrWbBitrate2385 );
	iCodec->iAllowedBitrates = KMceAllowedAmrWbBitrate2385;
	iCodec->iCodecMode = EOctetAligned;
    codec->SetCodecMode(EBandwidthEfficient);
    EUNIT_ASSERT_LEAVE( iCodec->DoMccValidateL( *codec, *srvStram, EMceRoleAnswerer ));
    CleanupStack::PopAndDestroy( codec );
    CleanupStack::PopAndDestroy( InfoCodecFactory );
    }



void UT_CMceComAMRWbCodec::UT_CMceComAMRWbCodec_DoSetDefaultFmtpAttributeLL()
    {
	iCodec->DoSetDefaultFmtpAttributeL();
	EUNIT_ASSERT( *iCodec->iFmtpAttr == KDefaultAmrWbFmtp );
    }


void UT_CMceComAMRWbCodec::UT_CMceComAMRWbCodec_CloneLL()
    {
    CMceComAudioCodec* clone = NULL;
    clone = iCodec->CloneL();
    // Ensure Clone is not Null
    EUNIT_ASSERT( clone );
    // Ensure Clone is AMR-WB Codec
    EUNIT_ASSERT( clone->iSdpName == iCodec->iSdpName );
    delete clone;
    }

	
//  TEST TABLE

EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComAMRWbCodec,
    "CMceComAMRWbCodec tests",
    "UNIT" )

EUNIT_TEST (
    "SetBitrate test",
    "CMceComAMRWbCodec",
    "SetBitrate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRWbCodec_SetBitrateL, Teardown)

EUNIT_TEST (
    "SetAllowedBitrates test",
    "CMceComAMRWbCodec",
    "SetAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRWbCodec_SetAllowedBitratesL, Teardown)

EUNIT_TEST (
    "GetMaxBitRate test",
    "CMceComAMRWbCodec",
    "GetMaxBitRate",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRWbCodec_GetMaxBitRateL, Teardown)

EUNIT_TEST (
    "ResolveAllowedBitrates test",
    "CMceComAMRWbCodec",
    "ResolveAllowedBitrates",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRWbCodec_ResolveAllowedBitratesL, Teardown)

EUNIT_TEST (
    "DoMccValidateL test",
    "CMceComAMRWbCodec",
    "DoMccValidateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRWbCodec_DoMccValidateLL, Teardown)    

EUNIT_TEST (
    "DoSetDefaultFmtpAttributeL test",
    "CMceComAMRWbCodec",
    "DoSetDefaultFmtpAttributeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRWbCodec_DoSetDefaultFmtpAttributeLL, Teardown)


EUNIT_TEST (
    "CloneL test",
    "CMceComAMRWbCodec",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAMRWbCodec_CloneLL, Teardown)


EUNIT_END_TEST_TABLE



//  END OF FILE
