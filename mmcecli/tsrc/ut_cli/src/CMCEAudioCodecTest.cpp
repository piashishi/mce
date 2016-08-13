/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include "CMceAudioCodecTest.h"
#include "mcestubs.h"

#include "mceamrcodec.h"
#include "mcecomaudiocodec.h"

#include "mcemanager.h"
#include "mceoutsession.h"
#include "mceaudiostream.h"

#include "mcemanagerreceiver.h"
#include "mcesessionreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"

#include "mcetransactiondatacontainer.h"
#include "mceevents.h"
#include "mceserial.h"
#include "mcefactory.h"

_LIT8( KSomeName, "SomeName" );
const CMceCodec::TState KState = CMceCodec::EEnabled;        

const TUint8 KEnableVad = ETrue;    
const TUint8 KEnableComfortNoise = ETrue;    
const TUint KSamplingFreq = 444;
const TUint KPTime = 555;
const TUint KMaxPTime = 666;


// ----------------------------------------------------------------------------
// CMceAudioCodecTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceAudioCodecTest::setUpL()
    {
    TBuf8<KMceMaxSdpNameLength> sdpName( KMceTestAudioCodec );
    iAMR = CMceAmrCodec::NewL(sdpName);				
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::tearDown()
    {
    delete iAMR;
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceAudioCodecTest::suiteL()
    {    
    CMceAudioCodecTest* suite = new CMceAudioCodecTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceAudioCodecTest,
    "CMceAudioCodecTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, GettersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, FactoryTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, CompareSdpIndexTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, ComparePreferencesTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, BaseFactoryTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, UpdatedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, InitializeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, InternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, ExternalizeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, EventReceivedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, SetStateLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, SetStandByTimerLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, SetMMFPriorityLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, SetMMFPriorityPreferenceLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, SetKeepAliveTimerLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, SetKeepAlivePayloadTypeLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, TypeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, SetSdpNameLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, SetPreferenceLTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, MMFPriorityTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceAudioCodecTest", setUpL, MMFPriorityPreferenceTestL, tearDown )
EUNIT_END_TEST_TABLE       

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::GettersTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::GettersTestL()
    {
	TMceMediaId id = iAMR->Id();
	EUNIT_ASSERT( id.iAppId == KMceNotAssigned);
	EUNIT_ASSERT( id.iId == KMceNotAssigned);
	
	CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iAMR->iFlatData );

 	flatData->iSamplingFreq = KSamplingFreq;
 	EUNIT_ASSERT_EQUALS( KSamplingFreq, iAMR->SamplingFreq() );

    TBuf8<KMceMaxSdpNameLength> sdpName( KSomeName );
    flatData->iSdpName = sdpName;
    EUNIT_ASSERT_EQUALS( KSomeName(), iAMR->SdpName() );

    flatData->iEnableVAD = KEnableVad;
	EUNIT_ASSERT( iAMR->VAD() == KEnableVad );
	
 	flatData->iPTime = KPTime;
 	EUNIT_ASSERT_EQUALS( KPTime, iAMR->PTime() );

 	flatData->iMaxPTime = KMaxPTime;
 	EUNIT_ASSERT_EQUALS( KMaxPTime, iAMR->MaxPTime() );

 	flatData->iBitrate = KMceTestBitrate;
 	EUNIT_ASSERT_EQUALS( KMceTestBitrate, iAMR->Bitrate() );        

 	flatData->iAllowedBitrates = KMceTestAllowedBitrates;
 	EUNIT_ASSERT_EQUALS( KMceTestBitrate, iAMR->Bitrate() );        
 	
  	flatData->iPayloadType = KMceTestPayloadType;
 	EUNIT_ASSERT_EQUALS( KMceTestPayloadType, iAMR->PayloadType() );

 	flatData->iCodecMode = KMceTestCodecMode;
 	EUNIT_ASSERT_EQUALS( KMceTestCodecMode, iAMR->CodecMode() );
 	
 	flatData->iFourCC = KMceTestFourCC;
 	EUNIT_ASSERT_EQUALS( KMceTestFourCC, iAMR->FourCC() );
 	
 	flatData->iFrameSize  = KMceTestFrameSize;
 	EUNIT_ASSERT_EQUALS( KMceTestFrameSize, iAMR->FrameSize() );
    }


// ----------------------------------------------------------------------------
// CMceAudioCodecTest::UpdatedTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::UpdatedTestL()
    {
    iAMR->Updated();
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::FactoryTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::FactoryTestL()
    {
    TMceAudioCodecFactory factory = CMceAudioCodec::Factory();
    TMceAudioCodecFactory* ptrFactory = &factory;
    EUNIT_ASSERT( ptrFactory != NULL );
    }
 
// ----------------------------------------------------------------------------
// CMceAudioCodecTest::CompareSdpIndexTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::CompareSdpIndexTestL()
    {
    TBuf8<KMceMaxSdpNameLength> sdpName( KMceTestAudioCodec );
    CMceAmrCodec* amr1 = CMceAmrCodec::NewLC(sdpName);
    CMceAmrCodec* amr2 = CMceAmrCodec::NewLC(sdpName);
    
    CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iAMR->iFlatData );

    CMceComAudioCodec* flatData1 = 
        static_cast<CMceComAudioCodec*>( amr1->iFlatData );
        
    CMceComAudioCodec* flatData2 = 
        static_cast<CMceComAudioCodec*>( amr2->iFlatData );
        
    flatData1->iCodecSdpIndex = 0;
    flatData2->iCodecSdpIndex = 0;
    EUNIT_ASSERT( flatData->CompareSdpIndex(*flatData1, *flatData2) == 1 );
    
    flatData1->iCodecSdpIndex = 1;
    flatData2->iCodecSdpIndex = 2;
    EUNIT_ASSERT( flatData->CompareSdpIndex(*flatData1, *flatData2) == -1 );
    
    flatData1->iCodecSdpIndex = 2;
    flatData2->iCodecSdpIndex = 1;
    EUNIT_ASSERT( flatData->CompareSdpIndex(*flatData1, *flatData2) == 1 );
    
    CleanupStack::PopAndDestroy( amr2 );
    CleanupStack::PopAndDestroy( amr1 );	
    }
    
// ----------------------------------------------------------------------------
// CMceAudioCodecTest::ComparePreferencesTestL()
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::ComparePreferencesTestL()
    {
    TBuf8<KMceMaxSdpNameLength> sdpName( KMceTestAudioCodec );
    CMceAmrCodec* amr1 = CMceAmrCodec::NewLC(sdpName);
    CMceAmrCodec* amr2 = CMceAmrCodec::NewLC(sdpName);

    CMceComAudioCodec* flatData1 = 
        static_cast<CMceComAudioCodec*>( amr1->iFlatData );
        
    CMceComAudioCodec* flatData2 = 
        static_cast<CMceComAudioCodec*>( amr2->iFlatData );
        
    flatData1->iPreference = 0;
    flatData2->iPreference = 0;
    EUNIT_ASSERT( iAMR->ComparePreferences(*amr1, *amr2) == 0 );
    
    flatData1->iPreference = 1;
    flatData2->iPreference = 2;
    EUNIT_ASSERT( iAMR->ComparePreferences(*amr1, *amr2) == -1 );
    
    flatData1->iPreference = 2;
    flatData2->iPreference = 1;
    EUNIT_ASSERT( iAMR->ComparePreferences(*amr1, *amr2) == 1 );
    
    CleanupStack::PopAndDestroy( amr2 );
    CleanupStack::PopAndDestroy( amr1 );	
    }
    
// ----------------------------------------------------------------------------
// CMceAudioCodecTest::BaseFactoryTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::BaseFactoryTestL()
    {
    TMceFactory factory = iAMR->BaseFactory();
    TMceFactory* ptrFactory = &factory;
    EUNIT_ASSERT( ptrFactory != NULL );
    }


// ----------------------------------------------------------------------------
// CMceAudioCodecTest::ExternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::ExternalizeTestL()
    {

	TBuf8<KMceMaxSdpNameLength> sdpName( KSomeName );
	
	// base
	CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iAMR->iFlatData );
	flatData->iSdpName = sdpName;
	
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

	// audio
	flatData->iEnableVAD = KEnableVad;
	flatData->iSamplingFreq = KSamplingFreq;
	flatData->iPTime = KPTime;
	flatData->iMaxPTime = KMaxPTime;
	
    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );	
    writeStream.PushL();   
    MMceComSerializationContext serCtx( writeStream );
    CleanupClosePushL( serCtx );
     
	iAMR->ExternalizeL( serCtx );
	
    CleanupStack::PopAndDestroy();//serCtx
	writeStream.Close();
	writeStream.Pop();
	
	RDesReadStream readStream( buffer );
	readStream.PushL();
	
	TUint32 expectedSdpNameLength = readStream.ReadUint32L();
	EUNIT_ASSERT_EQUALS( sdpName.Length(), expectedSdpNameLength );
	TBuf8<500> externSdpName;
	readStream.ReadL( externSdpName, expectedSdpNameLength );
	EUNIT_ASSERT_EQUALS( sdpName, externSdpName );
	
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
	
	EUNIT_ASSERT( readStream.ReadUint8L() == KEnableVad );
	EUNIT_ASSERT( readStream.ReadUint16L() == KSamplingFreq );
	EUNIT_ASSERT( readStream.ReadUint16L() == KPTime );
	EUNIT_ASSERT( readStream.ReadUint16L() == KMaxPTime );

	
	readStream.Close();
	readStream.Pop();
	
	
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::InternalizeTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::InternalizeTestL()
    {

    TBuf8<500> buffer;
    RDesWriteStream writeStream( buffer );
    writeStream.PushL();

    // data in CMCeComCodec
	TBuf8<KMceMaxSdpNameLength> sdpName( KSomeName );
    writeStream.WriteUint32L( sdpName.Length() );
    if ( sdpName.Length() > 0 )
        {
        writeStream.WriteL( KSomeName );
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
    
    // Data in CMceAudioCodec
    writeStream.WriteUint8L( KEnableVad );
    writeStream.WriteUint16L( KSamplingFreq );
    writeStream.WriteUint16L( KPTime );
    writeStream.WriteUint16L( KMaxPTime );
    //RedPayloadType
    writeStream.WriteUint8L( KMceTestPayloadType );
    writeStream.WriteUint16L( KRedCount );
    writeStream.WriteUint8L( KEnableComfortNoise );
   
	writeStream.CommitL();
	writeStream.Close();
    writeStream.Pop();
    
	RDesReadStream readStream( buffer );
	readStream.PushL();
    MMceComSerializationContext serCtx( readStream );
    CleanupClosePushL( serCtx );
	
    iAMR->InternalizeL( serCtx );
    
    CMceComAudioCodec* flatData = 
        static_cast<CMceComAudioCodec*>( iAMR->iFlatData );
    
    EUNIT_ASSERT( flatData->iSdpName == KSomeName );
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
    
    EUNIT_ASSERT( flatData->iEnableVAD == KEnableVad );
    EUNIT_ASSERT( flatData->iSamplingFreq == KSamplingFreq );
    EUNIT_ASSERT( flatData->iPTime == KPTime );
    EUNIT_ASSERT( flatData->iMaxPTime == KMaxPTime );

    
    CleanupStack::PopAndDestroy();//serCtx
    readStream.Close();
    readStream.Pop();
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::InitializeTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::InitializeTestL()
    {
   
    MCE_CREATE_PROFILE;
    
    TMceTransactionDataContainer container;		
    
    CMceManagerObserverStub* managerObserver = 
    	new (ELeave) CMceManagerObserverStub;
    CleanupStack::PushL( managerObserver );

	CMCEThreadLocalStorage* storage = new (ELeave) CMCEThreadLocalStorage();
	CleanupStack::PushL( storage );
    Dll::SetTls( storage );
    
    TUid uid = TUid::Uid( 777 );	
    CMceManager* manager = CMceManager::NewL( uid, &container );
    manager->SetInSessionObserver( managerObserver );
	CleanupStack::PushL( manager );
	
	CMceOutSession* session = CMceOutSession::NewL( *manager, *profile, KMceRecipient );
    CleanupStack::PushL( session );
    		
    CMceAudioStream* stream = CMceAudioStream::NewLC(); 
    session->AddStreamL( stream );
    CleanupStack::Pop( stream);
    
    stream->InitializeL( *session, EFalse );
    iAMR->InitializeL( *stream );
    EUNIT_ASSERT( iAMR->iStream == stream );
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );

    CleanupStack::Pop( manager );
    MCE_MAN_DELETE( manager );          
    CleanupStack::PopAndDestroy( storage );
    Dll::SetTls( NULL );
    CleanupStack::PopAndDestroy( managerObserver );
    
    MCE_DELETE_PROFILE;
  
    }
    
// ----------------------------------------------------------------------------
// CMceAudioCodecTest::EventReceivedTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::EventReceivedTestL()
    {
	TMceMediaId id;
	id.iAppId = KMceTestAppId;
	id.iId = KMceTestMiscId;

	TMceIds ids;
	ids.iCodecID = id; 
	TMceEvent event( ids, NULL, NULL );
	
	TInt status = iAMR->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotOwner, status );
	
	iAMR->iFlatData->iID = id;
	status = iAMR->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventUpdate, status );
	
	ids.iSinkID = id;
	status = iAMR->EventReceivedL( event );
	EUNIT_ASSERT_EQUALS( KMceEventNotConsumed, status );	
	
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::SetStateLTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::SetStateLTestL()
    {
    CMceCodec::TState codecState = CMceCodec::EStandby;
    iAMR->SetStateL( codecState );
    
    EUNIT_ASSERT_EQUALS( codecState,
    	static_cast<CMceComCodec*>( iAMR->iFlatData )->iState );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::SetStandByTimerLTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::SetStandByTimerLTestL()
    {
    TRAPD( err, iAMR->SetStandByTimerL( 1 ) );
    EUNIT_ASSERT_EQUALS( KErrNotSupported, err );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::SetMMFPriorityLTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::SetMMFPriorityLTestL()
    {
    const TInt KPriority = 82;
    iAMR->SetMMFPriorityL( KPriority );
    
    EUNIT_ASSERT_EQUALS( KPriority,
    	static_cast<CMceComCodec*>( iAMR->iFlatData )->iPriority );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::SetMMFPriorityPreferenceLTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::SetMMFPriorityPreferenceLTestL()
    {
    const TInt KPriorityPref = 0x4b6;
    iAMR->SetMMFPriorityPreferenceL( KPriorityPref );
    
    EUNIT_ASSERT_EQUALS( KPriorityPref,
    	static_cast<CMceComCodec*>( iAMR->iFlatData )->iPriorityPreference );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::SetKeepAliveTimerLTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::SetKeepAliveTimerLTestL()
    {
    const TUint8 KTimerValue = 59;
    iAMR->SetKeepAliveTimerL( KTimerValue );
    
    EUNIT_ASSERT_EQUALS( KTimerValue,
    	static_cast<CMceComCodec*>( iAMR->iFlatData )->iKeepAliveTimer );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::SetKeepAlivePayloadTypeLTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::SetKeepAlivePayloadTypeLTestL()
    {
    const TUint8 KPayload = 245;
    iAMR->SetKeepAlivePayloadTypeL( KPayload );
    
    EUNIT_ASSERT_EQUALS( KPayload,
    	static_cast<CMceComCodec*>( iAMR->iFlatData )->iKeepAlivePayloadType );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::TypeTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::TypeTestL()
    {
    TMceCodecType codecType( 0 );
    EUNIT_ASSERT_EQUALS( codecType, iAMR->Type() );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::SetSdpNameLTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::SetSdpNameLTestL()
    {
    // This function does nothing.
    iAMR->SetSdpNameL( KNullDesC8 );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::SetPreferenceLTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::SetPreferenceLTestL()
    {
    const TInt KPreference = 27031;
    iAMR->SetPreferenceL( KPreference );
    
    EUNIT_ASSERT_EQUALS( KPreference,
    	static_cast<CMceComCodec*>( iAMR->iFlatData )->iPreference );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::MMFPriorityTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::MMFPriorityTestL()
    {
    const TInt KPriority = 0x50f9;
    static_cast<CMceComCodec*>( iAMR->iFlatData )->iPriority = KPriority;
    EUNIT_ASSERT_EQUALS( KPriority, iAMR->MMFPriority() );
    }

// ----------------------------------------------------------------------------
// CMceAudioCodecTest::MMFPriorityPreferenceTestL
// ----------------------------------------------------------------------------
//
void CMceAudioCodecTest::MMFPriorityPreferenceTestL()
    {
    const TInt KPriorityPref = 0x50f9;
    static_cast<CMceComCodec*>( iAMR->iFlatData )->iPriorityPreference =
    	KPriorityPref;
    EUNIT_ASSERT_EQUALS( KPriorityPref, iAMR->MMFPriorityPreference() );
    }
