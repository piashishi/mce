/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
#include "ut_cmcecomsession.h"
#include "ut_cmcecomendpoint.h"
#include "ut_cmcecomstreambundle.h"
#include "ut_cmcecommediastream.h"
#include "ut_cmcecomaudiostream.h"
#include "ut_cmcecomvideostream.h"
#include "ut_cmcecomcamerasource.h"
#include "ut_cmcecommediasink.h"
#include "ut_cmcecomrtpsink.h"
#include "ut_cmcecomspeakersink.h"
#include "ut_cmcecomavsink.h"
#include "ut_cmcecommediasource.h"
#include "ut_cmcecommicsource.h"
#include "ut_cmcecomrtpsource.h"
#include "ut_cmcecomcodec.h"
#include "ut_cmcecomaudiocodec.h"
#include "ut_cmcecomamrcodec.h"
#include "ut_cmcecomamrwbcodec.h"
#include "ut_cmcecomg711codec.h"
#include "ut_cmcecomg729codec.h"
#include "ut_cmcecomilbccodec.h"
#include "ut_cmcecomdtmfcodec.h"
#include "ut_cmcecomredcodec.h"
#include "ut_cmcecomcncodec.h"
#include "ut_cmcecomvideocodec.h"
#include "ut_cmcecomh263codec.h"
#include "ut_cmcecomavccodec.h"
#include "ut_cmcecomdisplaysink.h"
#include "ut_cmcecomfilesource.h"
#include "ut_cmcecomfilesink.h"
#include "ut_mcecomfactory.h"
#include "ut_mcecomserial.h" 
#include "ut_mmcecomserializationcontext.h"

//  EXTERNAL INCLUDES
#include <digia/eunit/CEUnitTestSuite.h>




/**
 * Test suite factory function.
 */
EXPORT_C MEUnitTest* CreateTestSuiteL()
    {
    CEUnitTestSuite* rootSuite = CEUnitTestSuite::NewLC(_L("Wizard generated"));

    rootSuite->AddL( UT_CMceComSession::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComMediaStream::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComAudioStream::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComVideoStream::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComEndpoint::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComMediaSink::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComMediaSource::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComRtpSink::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComSpeakerSink::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComDisplaySink::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComFileSink::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComAvSink::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComRtpSource::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComCameraSource::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComMicSource::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComFileSource::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComStreamBundle::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComCodec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComAudioCodec::NewLC() );
    CleanupStack::Pop();

    rootSuite->AddL( UT_CMceComVideoCodec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComAMRCodec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComAMRWbCodec::NewLC() );
    CleanupStack::Pop();
    rootSuite->AddL( UT_CMceComG711Codec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComG729Codec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComiLBCCodec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComDtmfCodec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComRedCodec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComCnCodec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComH263Codec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_CMceComAvcCodec::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_MceComFactory::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_MceComSerial::NewLC() );
    CleanupStack::Pop();
    
    rootSuite->AddL( UT_MMceComSerializationContext::NewLC() );
    CleanupStack::Pop();
    

    CleanupStack::Pop(); // rootSuite

    return rootSuite;
    
    }
 

#ifdef _BullseyeCoverage
GLDEF_C int __stdcall __E32Dll(void*, unsigned, void*)
	{
	return 0;
	}
#endif

//  END OF FILE
