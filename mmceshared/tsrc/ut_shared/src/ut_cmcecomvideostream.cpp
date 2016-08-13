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
#include "ut_cmcecomvideostream.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/EUnitMacros.h>
#include "mcemediamanager.h"
#include "mcecomvideostream.h"
#include "mcecomcamerasource.h"
#include "mcecomrtpsink.h"
#include "mcecomsession.h"
#include "mcecomfactory.h"
#include "mcecomvideocodec.h"
#include <mmcccodecinformationfactory.h>


//  INTERNAL INCLUDES

// CONSTRUCTION
UT_CMceComVideoStream* UT_CMceComVideoStream::NewL()
    {
    UT_CMceComVideoStream* self = UT_CMceComVideoStream::NewLC(); 
    CleanupStack::Pop();

    return self;
    }

UT_CMceComVideoStream* UT_CMceComVideoStream::NewLC()
    {
    UT_CMceComVideoStream* self = new( ELeave ) UT_CMceComVideoStream();
    CleanupStack::PushL( self );

	self->ConstructL(); 

    return self;
    }

// Destructor (virtual by CBase)
UT_CMceComVideoStream::~UT_CMceComVideoStream()
    {
    }

// Default constructor
UT_CMceComVideoStream::UT_CMceComVideoStream()
    {
    }

// Second phase construct
void UT_CMceComVideoStream::ConstructL()
    {
    // The ConstructL from the base class CEUnitTestSuiteClass must be called.
    // It generates the test case table.
    CEUnitTestSuiteClass::ConstructL();
    }

//  METHODS


void UT_CMceComVideoStream::SetupL()
    {
    iServer = new (ELeave) CMceServerStub();
    iManager = CMceMediaManager::NewL( *iServer );

    iSession = CMceComSession::NewL();
    CMceComVideoStream* stream = CMceComVideoStream::NewLC();
    CMceComMediaSource* mediaSource = CMceComCameraSource::NewLC();
    stream->SetSourceL( mediaSource );
    CleanupStack::Pop( mediaSource );
    iSource = mediaSource;
    
    CMceComMediaSink* mediaSink = CMceComRtpSink::NewLC();
    stream->AddSinkL( mediaSink );
    CleanupStack::Pop( mediaSink );
    iSink = mediaSink;
    
    TMceComVideoCodecFactory factory;
    CMceComVideoCodec* codec = factory.CreateCodecLC( KMceSDPNameH263() );
    stream->AddCodecL( codec );
    CleanupStack::Pop( codec );
    iCodecH263 = codec;
    
    iSession->AddStreamL( stream );
    CleanupStack::Pop( stream );
    iStream = stream;
    
    iSession->InitializeL();
    iSession->PrepareL( *iManager );
    } 

void UT_CMceComVideoStream::Teardown()
    {
	CMceComSession::Delete( iSession, *iManager );
	delete iManager;
	iManager = NULL;
	delete iServer;
	iServer = NULL;
    }


void UT_CMceComVideoStream::UT_CMceComVideoStream_AddCodecLL()
    {
    iStream->DestroyCodecs();
    EUNIT_ASSERT( iStream->CodecCount() == 0 );
    
    TMceComVideoCodecFactory factory;
    CMceComVideoCodec* codec = factory.CreateCodecLC( KMceSDPNameH263() );
    
    iStream->AddCodecL( codec );

	EUNIT_ASSERT( iStream->CodecCount() == 1 );
	
	CMceComVideoCodec* nullCodec = NULL;
	
	EUNIT_ASSERT_SPECIFIC_LEAVE( iStream->AddCodecL( nullCodec ), KErrArgument );
	
	CleanupStack::Pop( codec );
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_RemoveCodecLL()
    {
    TInt initialCodecCount = iStream->CodecCount();
    
	// Remove H263 codec
	iStream->RemoveCodecL( iCodecH263 );
	
	EUNIT_ASSERT( iStream->CodecCount() == initialCodecCount - 1 );
	
	// Try to remove with wrong parameter
	CMceComCodec* nullCodec = NULL;
	iStream->RemoveCodecL( nullCodec );
	
	// Count should still be the same
	EUNIT_ASSERT( iStream->CodecCount() == initialCodecCount - 1 );
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_FindCodecLL()
    {
    TMceComVideoCodecFactory factory;
    CMceComVideoCodec* h263Copy = factory.CreateCodecLC( KMceSDPNameH263() );
	
	// It should be able to find it by using the originally added H263 codec
	CMceComCodec* originalH263 = iStream->FindCodecL( *iCodecH263 );
	EUNIT_ASSERT( originalH263 != NULL );
	// It should be able to find the codec by comparing the SDP name
	CMceComCodec* searchByCopy = iStream->FindCodecL( *h263Copy );
	EUNIT_ASSERT( searchByCopy != NULL );
	// But the address found should be the one of the original H263 codec
	EUNIT_ASSERT( searchByCopy == iCodecH263 );
	
	CleanupStack::PopAndDestroy( h263Copy );
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_InternalizeFlatLL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_ExternalizeFlatLL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_InternalizeLL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_ExternalizeLL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_InitializeLL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_UpdateLL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_CloneLL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_SynchronizeLL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_PrepareLL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_MccStreamTypeL()
    {
    }

void UT_CMceComVideoStream::UT_CMceComVideoStream_MccLinkTypeL()
    {
    EUNIT_ASSERT_EQUALS( iStream->MccLinkType(), KMccLinkGeneralVideo );
    
    TMceCryptoContext crypto;
    iStream->iSession->iClientCryptoSuites.AppendL( crypto );
    EUNIT_ASSERT_EQUALS( iStream->MccLinkType(), KMccLinkSecureVideo );
    
    iStream->iSession->iClientCryptoSuites.Reset();
    iStream->iStreamType = CMceComMediaStream::ELocalStream;
    EUNIT_ASSERT_EQUALS( iStream->MccLinkType(), KMccLinkLocal );
    }


void UT_CMceComVideoStream::UT_CMceComVideoStream_FindCodecFromListL()
	{
    TMceComVideoCodecFactory factory;
    CMceComVideoCodec* h263Copy = factory.CreateCodecLC( KMceSDPNameH263() );
    
    // Should not find it since the H263 codec added in SetupL has a different
    // address
    TInt ret = iStream->FindCodecFromList( h263Copy );
    EUNIT_ASSERT( iStream->FindCodecFromList( h263Copy ) == KErrNotFound );
    // But it should find iCodecH263
    EUNIT_ASSERT( iStream->FindCodecFromList( iCodecH263 ) >= 0 );
    iStream->AddCodecL( h263Copy );
    // Now our AMR codec should be found
    EUNIT_ASSERT( iStream->FindCodecFromList( h263Copy ) >= 0 );
    
    iStream->DestroyCodecs();

	EUNIT_ASSERT( iStream->FindCodecFromList( h263Copy ) == KErrNotFound );
	
	CleanupStack::Pop( h263Copy );
	}
	
void UT_CMceComVideoStream::UT_CMceComVideoStream_RemoveCodecFromListLL()
	{
	// Try searching for H263 codec
	TInt indexOfH263 = iStream->FindCodecFromList( iCodecH263 );
	EUNIT_ASSERT( indexOfH263 >= 0 );
	
	iStream->RemoveCodecFromListL( indexOfH263 );
	delete iCodecH263;
	
	// Try to remove with wrong parameter
	EUNIT_ASSERT_SPECIFIC_LEAVE( iStream->RemoveCodecFromListL( -1 ), KErrArgument );
	
	EUNIT_ASSERT( iStream->FindCodecFromList( iCodecH263 ) == KErrNotFound );
	}

void UT_CMceComVideoStream::UT_CMceComVideoStream_DestroyCodecsL()
	{
	EUNIT_ASSERT( iStream->CodecCount() > 0 );
	iStream->DestroyCodecs();
	EUNIT_ASSERT( iStream->CodecCount() == 0 );
	}

void UT_CMceComVideoStream::UT_CMceComVideoStream_CodecLL()
	{
	// First one should be H263
	EUNIT_ASSERT( iStream->CodecL( 0 ) == iCodecH263 );
	// There should not be a second codec
	EUNIT_ASSERT_SPECIFIC_LEAVE( iStream->CodecL( 1 ), KErrArgument );
	// Can't index with negative numbers
	EUNIT_ASSERT_SPECIFIC_LEAVE( iStream->CodecL( -1 ), KErrArgument );
	
	// Remove H263 codec
	iStream->RemoveCodecL( iCodecH263 );
	// And there should be no codecs in the list
	EUNIT_ASSERT_SPECIFIC_LEAVE( iStream->CodecL( 0 ), KErrArgument );
	}


	
//  TEST TABLE
EUNIT_BEGIN_TEST_TABLE( 
    UT_CMceComVideoStream,
    "CMceComVideoStream tests",
    "UNIT" )

EUNIT_TEST (
    "AddCodecL test",
    "CMceComVideoStream",
    "AddCodecL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_AddCodecLL, Teardown)

EUNIT_TEST (
    "RemoveCodecL test",
    "CMceComVideoStream",
    "RemoveCodecL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_RemoveCodecLL, Teardown)

EUNIT_TEST (
    "FindCodecL test",
    "CMceComVideoStream",
    "FindCodecL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_FindCodecLL, Teardown)

EUNIT_TEST (
    "InternalizeFlatL test",
    "CMceComVideoStream",
    "InternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_InternalizeFlatLL, Teardown)

EUNIT_TEST (
    "ExternalizeFlatL test",
    "CMceComVideoStream",
    "ExternalizeFlatL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_ExternalizeFlatLL, Teardown)

EUNIT_TEST (
    "InternalizeL test",
    "CMceComVideoStream",
    "InternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_InternalizeLL, Teardown)

EUNIT_TEST (
    "ExternalizeL test",
    "CMceComVideoStream",
    "ExternalizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_ExternalizeLL, Teardown)

EUNIT_TEST (
    "InitializeL test",
    "CMceComVideoStream",
    "InitializeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_InitializeLL, Teardown)

EUNIT_TEST (
    "UpdateL test",
    "CMceComVideoStream",
    "UpdateL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_UpdateLL, Teardown)

EUNIT_TEST (
    "CloneL test",
    "CMceComVideoStream",
    "CloneL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_CloneLL, Teardown)

EUNIT_TEST (
    "SynchronizeL test",
    "CMceComVideoStream",
    "SynchronizeL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_SynchronizeLL, Teardown)

EUNIT_TEST (
    "PrepareL test",
    "CMceComVideoStream",
    "PrepareL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_PrepareLL, Teardown)

EUNIT_TEST (
    "MccStreamType test",
    "CMceComVideoStream",
    "MccStreamType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_MccStreamTypeL, Teardown)

EUNIT_TEST (
    "MccLinkType test",
    "CMceComVideoStream",
    "MccLinkType",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_MccLinkTypeL, Teardown)



EUNIT_TEST (
    "FindCodecFromList test",
    "CMceComVideoStream",
    "FindCodecFromList",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_FindCodecFromListL, Teardown)

EUNIT_TEST (
    "RemoveCodecFromListL test",
    "CMceComVideoStream",
    "RemoveCodecFromListL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_RemoveCodecFromListLL, Teardown)
    
EUNIT_TEST (
    "DestroyCodecs test",
    "CMceComVideoStream",
    "DestroyCodecs",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_DestroyCodecsL, Teardown)
 
EUNIT_TEST (
    "CodecL test",
    "CMceComVideoStream",
    "CodecL",
    "FUNCTIONALITY",
    SetupL, UT_CMceComVideoStream_CodecLL, Teardown)
    
    
EUNIT_END_TEST_TABLE




//  END OF FILE

