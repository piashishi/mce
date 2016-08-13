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

#include <e32def.h>
#include <e32base.h>
#include <digia/eunit/EUnitMacros.h>
#include "mcevideocodectest.h"
#include "mcevideocodec.h"
#include "mcecomvideocodec.h"
#include "mceh263codec.h"
#include "mcefactory.h"
#include "mcetestdefs.h"
#include "mceserial.h"


const CMceCodec::TState KState = CMceCodec::EEnabled;        

const TUint KSomeAllowedFrameRates = 10;
const TReal KSomeFrameRate = 43.4;
const TUint KSomeMaxBitRate = 300;
const TUint KSomeAllowedResolutions = 400;
const TUint KSomeResolutionWidth = 200;
const TUint KSomeResolutionHeight = 500;
const TUint KSomeClockRate = 100;
const TReal KSomeReceiveFrameRate = 43.4;
        
// -----------------------------------------------------------------------------
// CMceVideoCodecTest::setUpL
// -----------------------------------------------------------------------------
//	
void CMceVideoCodecTest::setUpL()
    {
    TBuf8<KMceMaxSdpNameLength> sdpName = KMceTestVideoCodec();
    iVideoCodec = CMceH263Codec::NewL( sdpName );
    }


// -----------------------------------------------------------------------------
// CMceVideoCodecTest::tearDown
// -----------------------------------------------------------------------------
//
void CMceVideoCodecTest::tearDown()
    {
    delete iVideoCodec;
    }


// -----------------------------------------------------------------------------
// CMceVideoCodecTest::suiteL
// -----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceVideoCodecTest::suiteL()
    {
    CMceVideoCodecTest* suite = new CMceVideoCodecTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
		 
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceVideoCodecTest,
    "CMceVideoCodecTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceVideoCodecTest", setUpL, ConstructionTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceVideoCodecTest", setUpL, GettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceVideoCodecTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceVideoCodecTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceVideoCodecTest", setUpL, FactoryTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceVideoCodecTest", setUpL, ConfigKeyTestL, tearDown )
EUNIT_END_TEST_TABLE 

// -----------------------------------------------------------------------------
// CMceVideoCodecTest:: ConstructionTestL
// -----------------------------------------------------------------------------
//
void CMceVideoCodecTest::ConstructionTestL()
    {
    EUNIT_ASSERT( iVideoCodec != NULL );
    }


// -----------------------------------------------------------------------------
// CMceVideoCodecTest:: GettersTestL
// -----------------------------------------------------------------------------
//
void CMceVideoCodecTest::GettersTestL()
    {
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iVideoCodec->iFlatData );
    
    // AllowedFrameRates
    flatData->iAllowedFrameRates = KSomeAllowedFrameRates;
    EUNIT_ASSERT( iVideoCodec->AllowedFrameRates() == KSomeAllowedFrameRates );
    
    // FrameRate
    flatData->iFrameRate = KSomeFrameRate;
    EUNIT_ASSERT( iVideoCodec->FrameRate() == KSomeFrameRate);
    
    // MaxBitRate
    flatData->iMaxBitRate = KSomeMaxBitRate;
    EUNIT_ASSERT( iVideoCodec->MaxBitRate() == KSomeMaxBitRate );
    
    // AllowedResolutions
    flatData->iAllowedResolutions = KSomeAllowedResolutions;
    EUNIT_ASSERT( iVideoCodec->AllowedResolutions() == KSomeAllowedResolutions );
    
    // Resolution
    flatData->iResolutionWidth = KSomeResolutionWidth;
    flatData->iResolutionHeight = KSomeResolutionHeight;
    EUNIT_ASSERT_EQUALS( KSomeResolutionWidth, iVideoCodec->Resolution().iWidth );
    EUNIT_ASSERT_EQUALS( KSomeResolutionHeight, iVideoCodec->Resolution().iHeight );
    
    }


// -----------------------------------------------------------------------------
// CMceVideoCodecTest:: InternalizeTestL
// -----------------------------------------------------------------------------
//
void CMceVideoCodecTest::InternalizeTestL()
    {
    // Prepare to internalize base class data
    
    
    
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();

    writeStream.WriteUint32L( KMceTestVideoCodec().Length() );
    if ( KMceTestVideoCodec().Length() > 0 )
        {
        writeStream.WriteL( KMceTestVideoCodec );
        }
    
    writeStream.WriteUint32L( KMceTestAppId );
    writeStream.WriteUint32L( KMceTestMiscId );
    writeStream.WriteUint8L( KMceTestPayloadType );
    writeStream.WriteUint32L( KMceTestFourCC );
    writeStream.WriteUint32L( KMceTestFrameSize );
    writeStream.WriteUint32L( KMceTestBitrate );
    writeStream.WriteUint32L( KMceTestAllowedBitrates );
    writeStream.WriteUint32L( KMceTestCodecMode ); 
    writeStream.WriteInt32L( KState );
    writeStream.WriteInt32L( KMceTestPriority );
    writeStream.WriteInt32L( KMceTestPriorityPreference );
    writeStream.WriteInt32L( KMceTestKeepAliveTimer );
    writeStream.WriteInt32L( KMceTestKeepAlivePayloadType );
    
    writeStream.WriteUint32L( KMceTestKeepAliveData().Length() );
    if ( KMceTestKeepAliveData().Length() > 0 )
        {
        writeStream.WriteL( KMceTestKeepAliveData );
        }

    
    // Prepare to internalize video data
    
    writeStream.WriteReal64L( KSomeFrameRate );
    writeStream.WriteUint32L( KSomeMaxBitRate );
    writeStream.WriteUint32L( KSomeAllowedResolutions );
    writeStream.WriteInt32L( KSomeResolutionWidth );
    writeStream.WriteInt32L( KSomeResolutionHeight );
    writeStream.WriteUint32L( KSomeAllowedFrameRates );
    writeStream.WriteUint32L( KSomeClockRate );
    writeStream.WriteReal64L( KSomeReceiveFrameRate );
    writeStream.WriteUint32L( KMceTestConfigKeyData().Length() );
    if ( KMceTestConfigKeyData().Length() > 0 )
        {
        writeStream.WriteL( KMceTestConfigKeyData );
        }
    const TUint32 encoderUid = 100200;
    writeStream.WriteUint32L( encoderUid );
            
    // Internalize
    
    writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    iVideoCodec->InternalizeL( serCtx );
    
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iVideoCodec->iFlatData );
    
    // Asserts

    EUNIT_ASSERT( flatData->iSdpName == KMceTestVideoCodec );
    EUNIT_ASSERT( flatData->Id().iAppId == KMceTestAppId );
    EUNIT_ASSERT( flatData->iPayloadType == KMceTestPayloadType );
    EUNIT_ASSERT( flatData->Id().iId == KMceTestMiscId );
    EUNIT_ASSERT( flatData->iFourCC == KMceTestFourCC );
    EUNIT_ASSERT( flatData->iFrameSize == KMceTestFrameSize );
    EUNIT_ASSERT( flatData->iBitrate == KMceTestBitrate );
    EUNIT_ASSERT( flatData->iAllowedBitrates == KMceTestAllowedBitrates );
    EUNIT_ASSERT( flatData->iCodecMode == KMceTestCodecMode );    
    EUNIT_ASSERT( flatData->iPriority == KMceTestPriority );
    EUNIT_ASSERT( flatData->iPriorityPreference == KMceTestPriorityPreference );
    EUNIT_ASSERT( flatData->iKeepAliveTimer == KMceTestKeepAliveTimer );
    EUNIT_ASSERT( flatData->iKeepAlivePayloadType == KMceTestKeepAlivePayloadType );
    EUNIT_ASSERT( flatData->iKeepAliveData != NULL );
    EUNIT_ASSERT( flatData->iKeepAliveData->CompareF( KMceTestKeepAliveData ) == 0 );
    
    
    EUNIT_ASSERT( flatData->iFrameRate == KSomeFrameRate );
    EUNIT_ASSERT( flatData->iMaxBitRate == KSomeMaxBitRate );
    EUNIT_ASSERT( flatData->iAllowedResolutions == KSomeAllowedResolutions );
    EUNIT_ASSERT( flatData->iResolutionWidth == KSomeResolutionWidth );
    EUNIT_ASSERT( flatData->iResolutionHeight == KSomeResolutionHeight );
    EUNIT_ASSERT( flatData->iAllowedFrameRates == KSomeAllowedFrameRates );
    EUNIT_ASSERT( flatData->iClockRate == KSomeClockRate );
    EUNIT_ASSERT( flatData->iReceiveFrameRate == KSomeReceiveFrameRate );
    EUNIT_ASSERT( flatData->iConfigKey != NULL );
    EUNIT_ASSERT( flatData->iConfigKey->CompareF( KMceTestConfigKeyData ) == 0 );
    EUNIT_ASSERT( flatData->iEncodingDecodingDevice.iUid == encoderUid );

    
    CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();    
   
    }
    

// -----------------------------------------------------------------------------
// CMceVideoCodecTest:: ExternalizeTestL
// -----------------------------------------------------------------------------
//
void CMceVideoCodecTest::ExternalizeTestL()
    {      
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iVideoCodec->iFlatData );
    
    // Prepare to externalize base class data
    
    flatData->iID.iAppId = KMceTestAppId;
	flatData->iID.iId = KMceTestMiscId;
	flatData->iPayloadType = KMceTestPayloadType;
	flatData->iFourCC = KMceTestFourCC;
	flatData->iFrameSize = KMceTestFrameSize;
	flatData->iBitrate = KMceTestBitrate;
	flatData->iAllowedBitrates = KMceTestAllowedBitrates;
    flatData->iCodecMode = KMceTestCodecMode;
    flatData->iState = KState;
	flatData->iPriority = KMceTestPriority;
	flatData->iPriorityPreference = KMceTestPriorityPreference;
	flatData->iKeepAliveTimer = KMceTestKeepAliveTimer;
	flatData->iKeepAlivePayloadType = KMceTestKeepAlivePayloadType;
	MCE_DELETE( flatData->iKeepAliveData );
	flatData->iKeepAliveData = KMceTestKeepAliveData().AllocL();

    // Prepare to externalize video data
    
    flatData->iFrameRate = KSomeFrameRate;
    flatData->iMaxBitRate = KSomeMaxBitRate;
    flatData->iAllowedResolutions = KSomeAllowedResolutions;
    flatData->iResolutionWidth = KSomeResolutionWidth;
    flatData->iResolutionHeight = KSomeResolutionHeight;
    flatData->iAllowedFrameRates = KSomeAllowedFrameRates;
    flatData->iClockRate = KSomeClockRate;
    flatData->iReceiveFrameRate = KSomeReceiveFrameRate;
    MCE_DELETE( flatData->iConfigKey );
    flatData->iConfigKey = KMceTestConfigKeyData().AllocL();
    
        
    // Externalize
    
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();    
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
    
	iVideoCodec->ExternalizeL( serCtx );
    CleanupStack::PopAndDestroy();//serCtx
	
	writeStream.Close();
	writeStream.Pop();
	
	// Asserts
	
	RDesReadStream readStream( buffer );
	readStream.PushL();
    
    TUint32 expectedSdpNameLength = readStream.ReadUint32L();
	EUNIT_ASSERT_EQUALS( KMceTestVideoCodec().Length(), expectedSdpNameLength );
	TBuf8<500> externSdpName;
	readStream.ReadL( externSdpName, expectedSdpNameLength );
	EUNIT_ASSERT_EQUALS( KMceTestVideoCodec(), externSdpName );
    
    EUNIT_ASSERT( KMceTestAppId == readStream.ReadUint32L() );
	EUNIT_ASSERT( KMceTestMiscId == readStream.ReadUint32L() );
	EUNIT_ASSERT( readStream.ReadUint8L() == KMceTestPayloadType );
	EUNIT_ASSERT( readStream.ReadUint32L() == KMceTestFourCC );
	EUNIT_ASSERT( readStream.ReadUint32L() == KMceTestFrameSize );
	EUNIT_ASSERT( readStream.ReadUint32L() == KMceTestBitrate );
	EUNIT_ASSERT( readStream.ReadUint32L() == KMceTestAllowedBitrates );	
	EUNIT_ASSERT( readStream.ReadUint32L() == KMceTestCodecMode );	
	EUNIT_ASSERT( readStream.ReadInt32L() == KState );	
	EUNIT_ASSERT( readStream.ReadInt32L() == KMceTestPriority );	
	EUNIT_ASSERT( readStream.ReadInt32L() == KMceTestPriorityPreference );	
	EUNIT_ASSERT( readStream.ReadInt32L() == KMceTestKeepAliveTimer );	
	EUNIT_ASSERT( readStream.ReadInt32L() == KMceTestKeepAlivePayloadType );
	TUint32 keepAliveDataLength = readStream.ReadUint32L();
	EUNIT_ASSERT_EQUALS( KMceTestKeepAliveData().Length(), keepAliveDataLength );
	HBufC8* externKeepAliveData = HBufC8::NewLC ( keepAliveDataLength );
    TPtr8 externKeepAliveDataPtr = externKeepAliveData->Des();
	readStream.ReadL( externKeepAliveDataPtr, keepAliveDataLength );
	EUNIT_ASSERT_EQUALS( 0, KMceTestKeepAliveData().Compare( *externKeepAliveData ) );
	CleanupStack::PopAndDestroy( externKeepAliveData );
	
	EUNIT_ASSERT( readStream.ReadReal64L() == KSomeFrameRate );
	EUNIT_ASSERT( readStream.ReadUint32L() == KSomeMaxBitRate );
	EUNIT_ASSERT( readStream.ReadUint32L() == KSomeAllowedResolutions );
	EUNIT_ASSERT( readStream.ReadInt32L() == KSomeResolutionWidth );
	EUNIT_ASSERT( readStream.ReadInt32L() == KSomeResolutionHeight );
	EUNIT_ASSERT( readStream.ReadUint32L() == KSomeAllowedFrameRates );
	EUNIT_ASSERT( readStream.ReadUint32L() == KSomeClockRate );
	EUNIT_ASSERT( readStream.ReadReal64L() == KSomeReceiveFrameRate );
    TUint32 configKeyDataLength = readStream.ReadUint32L();
    EUNIT_ASSERT_EQUALS( KMceTestConfigKeyData().Length(), configKeyDataLength );
    HBufC8* externConfigKeyData = HBufC8::NewLC ( configKeyDataLength );
    TPtr8 externConfigKeyDataPtr = externConfigKeyData->Des();
    readStream.ReadL( externConfigKeyDataPtr, configKeyDataLength );
    EUNIT_ASSERT_EQUALS( 0, KMceTestConfigKeyData().Compare( *externConfigKeyData ) );
    CleanupStack::PopAndDestroy( externConfigKeyData );
	
    readStream.Close();
	readStream.Pop(); 
  
    }


// -----------------------------------------------------------------------------
// CMceVideoCodecTest:: FactoryTestL
// -----------------------------------------------------------------------------
//
void CMceVideoCodecTest::FactoryTestL()
    {
    TMceVideoCodecFactory factory = CMceVideoCodec::Factory();
    TMceVideoCodecFactory* ptrFactory = &factory;
    EUNIT_ASSERT( ptrFactory != NULL );
    }
 
// -----------------------------------------------------------------------------
// CMceVideoCodecTest::ConfigKeyTestL
// -----------------------------------------------------------------------------
//

void CMceVideoCodecTest::ConfigKeyTestL()
    {
    CMceComVideoCodec* flatData = 
        static_cast<CMceComVideoCodec*>( iVideoCodec->iFlatData );
        
    MCE_DELETE( flatData->iConfigKey );
    HBufC8* configKey = iVideoCodec->ConfigKeyL();
    EUNIT_ASSERT( configKey == NULL );
    
    flatData->iConfigKey = KMceTestConfigKeyData().AllocL();

    configKey = iVideoCodec->ConfigKeyL();
    CleanupStack::PushL( configKey );
    EUNIT_ASSERT_EQUALS( 0, configKey->Compare( KMceTestConfigKeyData ) );
    CleanupStack::PopAndDestroy( configKey );    
    }
