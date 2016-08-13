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
#include "ut_cmcecomaudiostream.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"
#include "mcecomaudiostream.h"
#include "mcecommicsource.h"
#include "mcecomrtpsink.h"
#include "mcecomsession.h"
#include "mcecomfactory.h"
#include "mcecomaudiocodec.h"
#include <mmcccodecinformationfactory.h>
#include "mmcccodeccn.h"
#include "mcecncodec.h"


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComAudioStream* UT_CMceComAudioStream::NewL()
    {
    UT_CMceComAudioStream* self = UT_CMceComAudioStream::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComAudioStream* UT_CMceComAudioStream::NewLC()
    {
    UT_CMceComAudioStream* self = new( ELeave ) UT_CMceComAudioStream();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComAudioStream::~UT_CMceComAudioStream()
    {
    }

// Default constructor
UT_CMceComAudioStream::UT_CMceComAudioStream()
    {
    }

// Second phase construct
void UT_CMceComAudioStream::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComAudioStream::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );

    iSession = CMceComSession::NewL();
    CMceComAudioStream* stream = CMceComAudioStream::NewLC();
    CMceComMediaSource* mediaSource = CMceComMicSource::NewLC();
    stream->SetSourceL( mediaSource );
    CleanupStack::Pop( mediaSource );
    iSource = mediaSource;
    CMceComMediaSink* mediaSink = CMceComRtpSink::NewLC();
    stream->AddSinkL( mediaSink );
    CleanupStack::Pop( mediaSink );
    iSink = mediaSink;
    
    TMceComAudioCodecFactory factory;
    CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNameAMR() );
    stream->AddCodecL( codec );
    CleanupStack::Pop( codec );
    iCodecAmr = codec;
    
    CMceComAudioCodec* cnCodec = factory.CreateCodecLC( KMceSDPNameCn() );
    stream->AddCodecL( cnCodec );
    CleanupStack::Pop( cnCodec );
    iCodecCn = cnCodec;
    
    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    iStream = stream;
    
    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    } 

void UT_CMceComAudioStream::Teardown()
    {
	CMceComSession::Delete( iSession, *iManager );
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_AddCodecLL()
    {
    TMceComAudioCodecFactory factory;
    CMceComAudioCodec* codec = factory.CreateCodecLC( KMceSDPNameG729() );
    
    TInt codecCount = iStream->CodecCount();
    
    iStream->AddCodecL( codec );

	EUNIT_ASSERT( iStream->CodecCount() == codecCount + 1 );
	
	CleanupStack::Pop( codec );
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_RemoveCodecLL()
    {
    TInt initialCodecCount = iStream->CodecCount();
    
	// Remove AMR codec
	iStream->RemoveCodecL( iCodecAmr );
	
	EUNIT_ASSERT( iStream->CodecCount() == initialCodecCount - 1 );
	
	// Try to remove with wrong parameter
	CMceComCodec* nullCodec = NULL;
	iStream->RemoveCodecL( nullCodec );
	
	// Count should still be the same
	EUNIT_ASSERT( iStream->CodecCount() == initialCodecCount - 1 );
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_FindCodecLL()
    {
    TMceComAudioCodecFactory factory;
    CMceComAudioCodec* amrCopy = factory.CreateCodecLC( KMceSDPNameAMR() );
	
	CMceComAudioCodec* g729 = factory.CreateCodecLC( KMceSDPNameG729() );
	
	// It should be able to find it by using the originally added AMR codec
	CMceComCodec* originalAmr = iStream->FindCodecL( *iCodecAmr );
	EUNIT_ASSERT( originalAmr != NULL );
	// It should be able to find the codec by comparing the SDP name
	CMceComCodec* searchByCopy = iStream->FindCodecL( *amrCopy );
	EUNIT_ASSERT( searchByCopy != NULL );
	// But the address found should be the one of the original AMR codec
	EUNIT_ASSERT( searchByCopy == iCodecAmr );
	
	// It should not find a codec which has not been added
	CMceComCodec* tryG729 = iStream->FindCodecL( *g729 );
	EUNIT_ASSERT( tryG729 == NULL );
	
	CleanupStack::PopAndDestroy( g729 );
	CleanupStack::PopAndDestroy( amrCopy );
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_InternalizeFlatLL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_ExternalizeFlatLL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_InternalizeLL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_ExternalizeLL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_InitializeLL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_UpdateLL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_CloneLL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_SynchronizeLL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_PrepareLL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_MccStreamTypeL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_MccLinkTypeL()
    {
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_UpdateDefaultCodecL()
    {
    EUNIT_ASSERT( iCodecAmr->IsEnabled() );
    EUNIT_ASSERT( iCodecAmr->SendSupported() );
    EUNIT_ASSERT( !iCodecCn->IsEnabled() );
    EUNIT_ASSERT( !iCodecCn->SendSupported() );
    
    // No change
    iStream->UpdateDefaultCodecL();
    EUNIT_ASSERT( iCodecAmr->IsEnabled() );
    EUNIT_ASSERT( !iCodecCn->IsEnabled() );
    
    // No enabled send codec
    iCodecAmr->SetEnabled( EFalse );
    iCodecAmr->iIsNegotiated = EFalse;
    iCodecCn->iIsNegotiated = EFalse;
    iStream->UpdateDefaultCodecL();
    EUNIT_ASSERT( !iCodecAmr->IsEnabled() );
    EUNIT_ASSERT( !iCodecCn->IsEnabled() );
    
    // Codec which does not support sending is enabled -> codec with
    // sending support is actually enabled
    iCodecCn->SetEnabled( ETrue );
    iCodecAmr->iIsNegotiated = ETrue;
    iCodecCn->iIsNegotiated = ETrue;
    iStream->UpdateDefaultCodecL();
    EUNIT_ASSERT( iCodecAmr->IsEnabled() );
    EUNIT_ASSERT( !iCodecCn->IsEnabled() );
    }

void UT_CMceComAudioStream::UT_CMceComAudioStream_FindCodecFromListL()
	{
    TMceComAudioCodecFactory factory;
    CMceComAudioCodec* amrCopy = factory.CreateCodecLC( KMceSDPNameAMR() );
    
    // Should not find it since the AMR codec added in SetupL has a different
    // address
    TInt ret = iStream->FindCodecFromList( amrCopy );
    EUNIT_ASSERT( iStream->FindCodecFromList( amrCopy ) == KErrNotFound );
    // But it should find iCodecAmr
    EUNIT_ASSERT( iStream->FindCodecFromList( iCodecAmr ) >= 0 );
    iStream->AddCodecL( amrCopy );
    // Now our AMR codec should be found
    EUNIT_ASSERT( iStream->FindCodecFromList( amrCopy ) >= 0 );
    
    iStream->DestroyCodecs();

	EUNIT_ASSERT( iStream->FindCodecFromList( amrCopy ) == KErrNotFound );
	
	CleanupStack::Pop( amrCopy );
	}
	
void UT_CMceComAudioStream::UT_CMceComAudioStream_RemoveCodecFromListLL()
	{
	// Try searching for AMR codec
	TInt indexOfAmr = iStream->FindCodecFromList( iCodecAmr );
	EUNIT_ASSERT( indexOfAmr >= 0 );
	
	// Try searching for CN codec
	TInt indexOfCn = iStream->FindCodecFromList( iCodecCn );
	EUNIT_ASSERT( indexOfCn >= 0 );
	
	iStream->RemoveCodecFromListL( indexOfAmr );
	delete iCodecAmr;
	
	// Try to remove with wrong parameter
	EUNIT_ASSERT_SPECIFIC_LEAVE( iStream->RemoveCodecFromListL( -1 ), KErrArgument );
	
	// CN should still be there, first in the list
	EUNIT_ASSERT( iStream->FindCodecFromList( iCodecCn ) == 0 );
	
	iStream->RemoveCodecFromListL( 0 );
	delete iCodecCn;
	
	EUNIT_ASSERT( iStream->FindCodecFromList( iCodecCn ) == KErrNotFound );
	}

void UT_CMceComAudioStream::UT_CMceComAudioStream_DestroyCodecsL()
	{
	EUNIT_ASSERT( iStream->CodecCount() > 0 );
	iStream->DestroyCodecs();
	EUNIT_ASSERT( iStream->CodecCount() == 0 );
	}

void UT_CMceComAudioStream::UT_CMceComAudioStream_CodecLL()
	{
	// First one should be AMR
	EUNIT_ASSERT( iStream->CodecL( 0 ) == iCodecAmr );
	// Second one should be CN
	EUNIT_ASSERT( iStream->CodecL( 1 ) == iCodecCn );
	// There should not be a third codec
	EUNIT_ASSERT_SPECIFIC_LEAVE( iStream->CodecL( 2 ), KErrArgument );
	// Can't index with negative numbers
	EUNIT_ASSERT_SPECIFIC_LEAVE( iStream->CodecL( -1 ), KErrArgument );
	
	// Remove AMR codec
	iStream->RemoveCodecL( iCodecAmr );
	// Now the first one should be CN
	EUNIT_ASSERT( iStream->CodecL( 0 ) == iCodecCn );
	// And there is no second codec
	EUNIT_ASSERT_SPECIFIC_LEAVE( iStream->CodecL( 1 ), KErrArgument );
	}

//  TEST TABLE
EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComAudioStream,
    "CMceComAudioStream tests",
    "UNIT" )

EUNIT_TEST (
    "AddCodecL test",
    "CMceComAudioStream",
    "AddCodecL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_AddCodecLL, Teardown)

EUNIT_TEST (
    "RemoveCodecL test",
    "CMceComAudioStream",
    "RemoveCodecL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_RemoveCodecLL, Teardown)

EUNIT_TEST (
    "FindCodecL test",
    "CMceComAudioStream",
    "FindCodecL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_FindCodecLL, Teardown)

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComAudioStream",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComAudioStream",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "InternalizeL test",
    "CMceComAudioStream",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_InternalizeLL, Teardown)

EUNIT_TEST (
    "ExternalizeL test",
    "CMceComAudioStream",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_ExternalizeLL, Teardown)

EUNIT_TEST (
    "InitializeL test",
    "CMceComAudioStream",
    "InitializeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_InitializeLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComAudioStream",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_UpdateLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComAudioStream",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_CloneLL, Teardown)

EUNIT_TEST (
    "SynchronizeL test",
    "CMceComAudioStream",
    "SynchronizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_SynchronizeLL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComAudioStream",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_PrepareLL, Teardown)

EUNIT_TEST (
    "MccStreamType test",
    "CMceComAudioStream",
    "MccStreamType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_MccStreamTypeL, Teardown)

EUNIT_TEST (
    "MccLinkType test",
    "CMceComAudioStream",
    "MccLinkType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_MccLinkTypeL, Teardown)

EUNIT_TEST (
    "UpdateDefaultCodecL test",
    "CMceComAudioStream",
    "UpdateDefaultCodecL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_UpdateDefaultCodecL, Teardown)




EUNIT_TEST (
    "FindCodecFromList test",
    "CMceComAudioStream",
    "FindCodecFromList",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_FindCodecFromListL, Teardown)

EUNIT_TEST (
    "RemoveCodecFromListL test",
    "CMceComAudioStream",
    "RemoveCodecFromListL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_RemoveCodecFromListLL, Teardown)
    
EUNIT_TEST (
    "DestroyCodecs test",
    "CMceComAudioStream",
    "DestroyCodecs",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_DestroyCodecsL, Teardown)
 
EUNIT_TEST (
    "CodecL test",
    "CMceComAudioStream",
    "CodecL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComAudioStream_CodecLL, Teardown)


    
EUNIT_END_TEST_TABLE




//  END OF FILE
