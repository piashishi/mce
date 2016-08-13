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
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include "CMceComAudioStreamTest.h"

#include "mceinsession.h"
#include "mceoutsession.h"
#include "mceaudiostream.h"
#include "mcertpsink.h"
#include "mcertpsource.h"
#include "mcemicsource.h"
#include "mcespeakersink.h"
#include "mcecomsession.h"
#include "mcecommediastream.h"
#include "mcecomaudiostream.h"
#include "mcecomrtpsink.h"
#include "mcecomrtpsource.h"
#include "mcecommicsource.h"
#include "mcecomspeakersink.h"
#include "mcecomamrcodec.h"

#include "mcetestdefs.h"


// ----------------------------------------------------------------------------
// CMceComAudioStreamTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceComAudioStreamTest::setUpL()
    {
    
    iMediaManager = new (ELeave) CMceMediaManagerStub();
    iSession = CMceComSession::NewL();
    iSession->iID = 1;
    
    iAudioIn = CMceComAudioStream::NewLC();
    iAudioOut = CMceComAudioStream::NewLC();
    iRtpSource = CMceComRtpSource::NewLC();
    iAudioIn->SetSourceL( iRtpSource );
    CleanupStack::Pop();
    
    iRtpSink = CMceComRtpSink::NewLC();
    iAudioOut->AddSinkL( iRtpSink );
    CleanupStack::Pop();
    
    iAudioIn->BindL( iAudioOut );
    CleanupStack::Pop();

    iSession->AddStreamL( iAudioIn );
    CleanupStack::Pop();
    
    }

// ----------------------------------------------------------------------------
// CMceComAudioStreamTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceComAudioStreamTest::tearDown()
    {

    delete iSession;
    delete iMediaManager;
        
    }

// ----------------------------------------------------------------------------
// CMceComAudioStreamTest::suiteL
// ----------------------------------------------------------------------------
//
MTest* CMceComAudioStreamTest::suiteL()
    {
    CTestSuite *suite = CTestSuite::NewL(_L8("CMceComAudioStreamTest"));

	suite->addTestL( 
	    CTestCaller<CMceComAudioStreamTest>::NewL(
	        _L8("TestUseRtcpL"),
            &TestUseRtcpL ) );

	suite->addTestL( 
	    CTestCaller<CMceComAudioStreamTest>::NewL(
	        _L8("TestEventReceivedL"),
            &TestEventReceivedL ) );

    return suite;
    }

// ----------------------------------------------------------------------------
// CMceComAudioStreamTest::TestUseRtcpL
// ----------------------------------------------------------------------------
//
void CMceComAudioStreamTest::TestUseRtcpL()
    {
    // By default using RTCP for the source and all the sinks
    assertL( iAudioOut->UseRtcp() );
    
    // Setting the sink not to support RTCP
    iRtpSink->iSuppressRTCP = ETrue;
    assertL( !iAudioOut->UseRtcp() );
    
    // Removing the only source and setting the sink to support RTCP
    iAudioIn->SetSourceL( NULL );
    iRtpSink->iSuppressRTCP = EFalse;
    assertL( iAudioOut->UseRtcp() );
    
    // Setting the sink again not to support RTCP
    iRtpSink->iSuppressRTCP = ETrue;
    assertL( !iAudioOut->UseRtcp() );    
    }

// ----------------------------------------------------------------------------
// CMceComAudioStreamTest::TestEventReceivedL
// ----------------------------------------------------------------------------
//
void CMceComAudioStreamTest::TestEventReceivedL()
    {
    TUid uid = TUid::Uid( 777 );
    TMceComEventHandlerStub handler( *iMediaManager );

//disabled source    
    
    TMceIds ids;
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    ids.iMediaID = iAudioIn->iID;
    ids.iSourceID = iRtpSource->iID;

    TMceComEvent event1( ids, NULL, EMceItcDisable, handler );
    iSession->EventReceivedL( event1 );

    assertL( iMediaManager->iCallback == 2 );
    assertL( iMediaManager->iSink == NULL );
    assertL( iMediaManager->iSource == iRtpSource );

//disabled sink

    ids = TMceIds();
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    ids.iMediaID = iAudioOut->iID;
    ids.iSinkID = iRtpSink->iID;

    TMceComEvent event2( ids, NULL, EMceItcDisable, handler );
    iSession->EventReceivedL( event2 );

    assertL( iMediaManager->iCallback == 1 );
    assertL( iMediaManager->iSink == iRtpSink );
    assertL( iMediaManager->iSource == NULL );


//enabled source    
    
    ids = TMceIds();
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    ids.iMediaID = iAudioIn->iID;
    ids.iSourceID = iRtpSource->iID;

    TMceComEvent event3( ids, NULL, EMceItcEnable, handler );
    iSession->EventReceivedL( event3 );

    assertL( iMediaManager->iCallback == 4 );
    assertL( iMediaManager->iSink == NULL );
    assertL( iMediaManager->iSource == iRtpSource );

//enabled sink

    ids = TMceIds();
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    ids.iMediaID = iAudioOut->iID;
    ids.iSinkID = iRtpSink->iID;

    TMceComEvent event4( ids, NULL, EMceItcEnable, handler );
    iSession->EventReceivedL( event4 );

    assertL( iMediaManager->iCallback == 3 );
    assertL( iMediaManager->iSink == iRtpSink );
    assertL( iMediaManager->iSource == NULL );

//sink RR

    ids = TMceIds();
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    ids.iMediaID = iAudioOut->iID;
    ids.iSinkID = iRtpSink->iID;

    TMceComEvent event5( ids, NULL, EMceItcSendRR, handler );
    iSession->EventReceivedL( event5 );

    assertL( iMediaManager->iCallback == 6 );
    assertL( iMediaManager->iSink == iRtpSink );
    assertL( iMediaManager->iSource == NULL );


//sink SR

    ids = TMceIds();
    ids.iAppUID = uid.iUid;
    ids.iSessionID = 1;
    ids.iMediaID = iAudioOut->iID;
    ids.iSinkID = iRtpSink->iID;

    TMceComEvent event6( ids, NULL, EMceItcSendSR, handler );
    iSession->EventReceivedL( event6 );

    assertL( iMediaManager->iCallback == 5 );
    assertL( iMediaManager->iSink == iRtpSink );
    assertL( iMediaManager->iSource == NULL );
    }
