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
#include "CMceManagerTest.h"
#include "mcestubs.h"
#include "mcetestdefs.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mceeventreceiver.h"
#include "mcereferreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mcesessionreceiver.h"

#include "mceoutsession.h"
#include "mceoutrefer.h"
#include "mceinsession.h"
#include "mceaudiostream.h"
#include "mcertpsink.h"
#include "mcertpsource.h"
#include "mcemicsource.h"
#include "mcespeakersink.h"
#include "mceamrcodec.h"
#include "mcecomsession.h"
#include "mcecomaudiostream.h"
#include "mcecomrtpsink.h"
#include "mcecomrtpsource.h"
#include "mcecommicsource.h"
#include "mcecomspeakersink.h"
#include "mcecomamrcodec.h"
#include "mceserial.h"
#include "mcefilesource.h"
#include "mcevideostream.h"

#define MCE_BODYALSO 1
#define MCE_NOBOUND 2
#define MCE_NODETAILS 3
  

// ----------------------------------------------------------------------------
// CMceManagerTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceManagerTest::setUpL()
    {

    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );

    iManagerObserver = new (ELeave) CMceManagerObserverStub();
    iSessionObserver = new (ELeave) CMceSessionObserverStub();
    iStreamObserver = new (ELeave) CMceStreamObserverStub();
    iRtpObserver = new (ELeave) CMceRtpObserverStub();
    iInEventObserver = new( ELeave ) CMceInEventObserverStub();
    iInReferObserver = new( ELeave ) CMceInReferObserverStub();
    iInTransactionObserver = new (ELeave ) CMceInTransactionObserverStub();
        
    iManager = CMceManager::NewL( iUid, &iContainer );
    iManager->SetInSessionObserver( iManagerObserver );
    iManager->SetSessionObserver( iSessionObserver );
    iManager->SetInEventObserver( iInEventObserver );
    iManager->SetInReferObserver( iInReferObserver );
    iManager->SetTransactionObserver( iTransactionObserver );
    iManager->SetInTransactionObserver( iInTransactionObserver );
//    iManager->SetMediaObserver( iStreamObserver );
//    iManager->SetRtpObserver( iRtpObserver );    
    }

// ----------------------------------------------------------------------------
// CMceManagerTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceManagerTest::tearDown()
    {
    TInt count = iManager->Sessions().Count();
    for( int i = count - 1; i >= 0 ;i--)
        {
        CMceSession* session = iManager->Sessions()[i];
        MCE_TEST_DELETE( session );
        }

    MCE_MAN_DELETE( iManager );        

    delete iManagerObserver;
    delete iSessionObserver;
    delete iStreamObserver;
    delete iRtpObserver;
    delete iInEventObserver;
    delete iInReferObserver;
    delete iTransactionObserver;
    delete iInTransactionObserver;
    delete iStorage;
    Dll::SetTls( NULL );
       
    }

// ----------------------------------------------------------------------------
// CMceManagerTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceManagerTest::suiteL()
    {
    CMceManagerTest* suite = new CMceManagerTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;
    }

EUNIT_BEGIN_TEST_TABLE( 
    CMceManagerTest,
    "CMceManagerTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, SesionsTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, ObserversTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, IdTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, SetDefaultHeadersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, DefaultHeadersTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, EventManagerReceiverTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, EventManagerReceiverTest2L, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, ManagerReceiverTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, FindReferTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, TransCodeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, TransCodeCompletedTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, SetDtmfObserverTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceManagerTest", setUpL, FindAssociatedSessionTestL, tearDown )
EUNIT_END_TEST_TABLE   

// ----------------------------------------------------------------------------
// CMceManagerTest::SessionsTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::SesionsTestL()
    {
    
    EUNIT_ASSERT( iManager->Sessions().Count() == 0 );
    CMceComSession* inSession = NULL;
    CMceComAudioStream* outStream = NULL;
    CMceComAudioStream* inStream = NULL;
    CMceMsgObject<CMceComSession>* msg = NULL;
    CMceInSession* incomingSession = NULL;
    
//new incoming session with no content
    for ( int i = 0;i<3;i++ )
        {
        
        inSession = CMceComSession::NewL( CMceComSession::EInSession );
        
        inSession->iID = KMceTestSessionId1 + i;
        inSession->iState = CMceSession::EIncoming;
        inSession->iIsConnectionActive = ETrue;
        CleanupStack::PushL( inSession );
        
        delete inSession->iOriginator;
        delete inSession->iRecipient;
        delete inSession->iSIPContentType;
        delete inSession->iSIPHeaders;
        inSession->iOriginator = 0;
        inSession->iRecipient = 0;
        inSession->iSIPContentType = 0;
        inSession->iSIPHeaders= 0;
        inSession->iOriginator = KMceOriginator().AllocL();
        inSession->iRecipient = KMceRecipient().AllocL();
        inSession->iSIPContentType = KMceContentType().AllocL();
        inSession->iSIPHeaders =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
        inSession->iSIPHeaders->AppendL( KMceHeader1 );
        inSession->iSIPHeaders->AppendL( KMceHeader2 );
            
        if ( i != MCE_NOBOUND )
            {
            outStream = CMceComAudioStream::NewL();
            CleanupStack::PushL( outStream );
            EUNIT_ASSERT( outStream->iID.IsAssigned() );
            EUNIT_ASSERT( outStream->iID.iAppId == 0 );
            }
            
        inStream = CMceComAudioStream::NewL();
        CleanupStack::PushL( inStream );
        EUNIT_ASSERT( inStream->iID.IsAssigned() );
        EUNIT_ASSERT( inStream->iID.iAppId == 0 );
       
        TBuf8<KMceMaxSdpNameLength> codec1;
        codec1.Append( KMceSDPNameAMR );
        TBuf8<KMceMaxSdpNameLength> codec2;
        codec2.Append( KMceSDPNamePCMU );


        if ( i != MCE_NOBOUND )
            {
            CMceComAMRCodec* codec = CMceComAMRCodec::NewL( codec1 );
            CleanupStack::PushL( codec );
            codec->iBitrate = 64;
            codec->iAllowedBitrates = 222;
            codec->iSamplingFreq = 10;
            codec->iEnableVAD = ETrue;
            codec->iPayloadType = 96;
            codec->iCodecMode = 15;
            codec->iPTime = 200;
            codec->iMaxPTime = 400;
            codec->iFourCC = 234323;
            
            outStream->AddCodecL( codec );
            CleanupStack::Pop( codec );
            CMceComRtpSink* sink = CMceComRtpSink::NewL();
            CleanupStack::PushL( sink );
            outStream->AddSinkL( sink );
            CleanupStack::Pop( sink );
            }
            
        CMceComAMRCodec* codec = CMceComAMRCodec::NewL( codec2 );
        CleanupStack::PushL( codec );
        inStream->AddCodecL( codec );
        CleanupStack::Pop( codec );
        
        CMceComRtpSource* source = CMceComRtpSource::NewL();
        CleanupStack::PushL( source );
        inStream->SetSourceL( source );
        CleanupStack::Pop( source );
        
        delete inStream->iLocalMediaSDPLines;
        inStream->iLocalMediaSDPLines = 0;
        inStream->iLocalMediaSDPLines =  new (ELeave) CDesC8ArrayFlat( KMceArrayGranularity );
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine1 );
        inStream->iLocalMediaSDPLines->AppendL( KMceMedialine2 );
        
        
        if ( i != MCE_NOBOUND )
            {
            outStream->BindL( inStream );
            CleanupStack::Pop( inStream );
            inSession->AddStreamL( outStream );    
            CleanupStack::Pop( outStream );
            }
        else
            {
            inSession->AddStreamL( inStream );    
            CleanupStack::Pop( inStream );
            }

            
        msg = new (ELeave) CMceMsgObject<CMceComSession>( *inSession, EMceItcMsgTypeSession );
        CleanupStack::PushL( msg );
        msg->EncodeL();
        
        iStorage->Reset();
        iManager->iSessionReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
        iManager->iSessionReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
                
        iStorage->iContext = msg->EncodeBuffer().Ptr(0).AllocL();
        iManager->iSessionReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
        
        if ( i == MCE_BODYALSO )
            {
            iStorage->iContent = KMceMessageBody().AllocL();
            iManager->iSessionReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();
            }
            
        CleanupStack::PopAndDestroy( msg );
        CleanupStack::PopAndDestroy( inSession );

        iManager->iSessionReceiver->iIdsPckg().iAppUID = iManager->AppUid().iUid;
        iManager->iSessionReceiver->iIdsPckg().iSessionID = KMceTestSessionId1 + i;
        iManager->iSessionReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;
        iManager->iSessionReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeSession;

        if ( i == MCE_NODETAILS )
            {
            iManager->iSessionReceiver->iDetailedCallbacks = EFalse;
            }
            
        MCE_RECEIVE( iManager, KErrNone );

        EUNIT_ASSERT( iManagerObserver->iSession != NULL );
        incomingSession = static_cast<CMceInSession*>( iManager->Sessions()[i] );
        
        EUNIT_ASSERT( iManagerObserver->iSession == incomingSession );
        
        if ( i != MCE_NODETAILS )
            {
            EUNIT_ASSERT( iManagerObserver->iContentType != NULL);
            EUNIT_ASSERT( iManagerObserver->iContentType->Compare( KMceContentType ) == 0);
            EUNIT_ASSERT( iManagerObserver->iHeaders != NULL );
            EUNIT_ASSERT( iManagerObserver->iHeaders->MdcaCount() == 2 );
            EUNIT_ASSERT( iManagerObserver->iHeaders->MdcaPoint(0).Compare( KMceHeader1 ) == 0 );
            EUNIT_ASSERT( iManagerObserver->iHeaders->MdcaPoint(1).Compare( KMceHeader2 ) == 0 );
            }
        else
            {
            EUNIT_ASSERT( iManagerObserver->iContentType == NULL);
            EUNIT_ASSERT( iManagerObserver->iHeaders == NULL );
            }
        
        
        if ( i == MCE_BODYALSO )
            {
            EUNIT_ASSERT( iManagerObserver->iBody->Compare( KMceMessageBody ) == 0 );
            }
        else
            {
            EUNIT_ASSERT( iManagerObserver->iBody == NULL );
            }
        
        
        EUNIT_ASSERT( iManager->Sessions().Count() == i+1 );
        EUNIT_ASSERT( incomingSession->Id() == KMceTestSessionId1 + i );
        EUNIT_ASSERT( incomingSession->State() == CMceSession::EIncoming );
        EUNIT_ASSERT( incomingSession->ConnectionActive() );
        
        EUNIT_ASSERT( incomingSession->Originator().Compare( KMceOriginator ) == 0 );
        EUNIT_ASSERT( incomingSession->Recipient().Compare( KMceRecipient ) == 0 );
        EUNIT_ASSERT( incomingSession->Streams().Count() == 1 );
        
        if ( i != MCE_NOBOUND )
            {
            CMceAudioStream* audioOut = static_cast<CMceAudioStream*>( incomingSession->Streams()[0] );
            EUNIT_ASSERT( audioOut->Id().IsAssigned() );
            EUNIT_ASSERT( audioOut->Id().iAppId == 0 );
            EUNIT_ASSERT( audioOut->Type() == KMceAudio );
            EUNIT_ASSERT( audioOut->BoundStream() );
            EUNIT_ASSERT( audioOut->Codecs().Count() == 1 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->Id().IsAssigned() );
            EUNIT_ASSERT( audioOut->Codecs()[0]->Id().iAppId == 0 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->SdpName().Compare(_L8("AMR") ) == 0 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->Bitrate() == 64 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->AllowedBitrates() == 222 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->SamplingFreq() == 10 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->VAD() );
            EUNIT_ASSERT( audioOut->Codecs()[0]->PayloadType() == 96 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->CodecMode() == 15 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->PTime() == 200 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->MaxPTime() == 400 );
            EUNIT_ASSERT( audioOut->Codecs()[0]->FourCC() == 234323 );
            
            EUNIT_ASSERT( audioOut->Source() == NULL );
            EUNIT_ASSERT( audioOut->Sinks().Count() == 1 );
            EUNIT_ASSERT( audioOut->Sinks()[0]->Id().IsAssigned() );
            EUNIT_ASSERT( audioOut->Sinks()[0]->Id().iAppId == 0 );
            EUNIT_ASSERT( audioOut->Sinks()[0]->Type() == KMceRTPSink );
        
            CMceAudioStream* audioIn = static_cast<CMceAudioStream*>( &(audioOut->BoundStreamL()) );
            EUNIT_ASSERT( audioIn->Id().IsAssigned() );
            EUNIT_ASSERT( audioIn->Id().iAppId == 0 );
            EUNIT_ASSERT( audioIn->Type() == KMceAudio );
            EUNIT_ASSERT( audioIn->BoundStream() );
            EUNIT_ASSERT( audioIn->Codecs().Count() == 1 );
            EUNIT_ASSERT( audioIn->Codecs()[0]->Id().IsAssigned() );
            EUNIT_ASSERT( audioIn->Codecs()[0]->Id().iAppId == 0 );
            EUNIT_ASSERT( audioIn->Codecs()[0]->SdpName().Compare( KMceSDPNamePCMU ) == 0 );
            EUNIT_ASSERT( audioIn->Source() != NULL );
            EUNIT_ASSERT( audioIn->Source()->Id().IsAssigned() );
            EUNIT_ASSERT( audioIn->Source()->Id().iAppId == 0 );
            EUNIT_ASSERT( audioIn->Source()->Type() == KMceRTPSource );
            EUNIT_ASSERT( audioIn->Sinks().Count() == 0 );
            
            }
        else
            {
            
            CMceAudioStream* audioIn = static_cast<CMceAudioStream*>( incomingSession->Streams()[0] );
            EUNIT_ASSERT( audioIn->Id().IsAssigned() );
            EUNIT_ASSERT( audioIn->Id().iAppId == 0 );
            EUNIT_ASSERT( audioIn->Type() == KMceAudio );
            EUNIT_ASSERT( !audioIn->BoundStream() );
            EUNIT_ASSERT( audioIn->Codecs().Count() == 1 );
            EUNIT_ASSERT( audioIn->Codecs()[0]->Id().IsAssigned() );
            EUNIT_ASSERT( audioIn->Codecs()[0]->Id().iAppId == 0 );
            EUNIT_ASSERT( audioIn->Codecs()[0]->SdpName().Compare( KMceSDPNamePCMU ) == 0 );
            EUNIT_ASSERT( audioIn->Source() != NULL );
            EUNIT_ASSERT( audioIn->Source()->Id().IsAssigned() );
            EUNIT_ASSERT( audioIn->Source()->Id().iAppId == 0 );
            EUNIT_ASSERT( audioIn->Source()->Type() == KMceRTPSource );
            EUNIT_ASSERT( audioIn->Sinks().Count() == 0 );
            
            }
    
        }
    
        EUNIT_ASSERT( iManager->Sessions().Count() == 3 );

        //runs to non context & content callback, which leaves    
        iManager->iSessionReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
        iManager->iSessionReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
                
        iManager->iSessionReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;
        iManager->iSessionReceiver->iIdsPckg().iMsgType = KMceNotAssigned;

        MCE_RECEIVE( iManager, KErrNone );
        EUNIT_ASSERT( iManager->Sessions().Count() == 3 );

        //unsupported call back
        iManager->iSessionReceiver->iIdsPckg().iCallbackID = EMceItcSRReceived;
        iManager->iSessionReceiver->iIdsPckg().iMsgType = KMceNotAssigned;
        iManager->iSessionReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
        iStorage->Reset();
                
        iStorage->iContext = KMceHeader1().AllocL();
        iManager->iSessionReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
               
        MCE_RECEIVE( iManager, KErrNone );
        EUNIT_ASSERT( iManager->Sessions().Count() == 3 );

        //Completed with error
        MCE_RECEIVE( iManager, KErrGeneral );
        EUNIT_ASSERT( iManager->Sessions().Count() == 3 );
   
    }
    
    

	
// ----------------------------------------------------------------------------
// CMceManagerTest::ObserversTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::ObserversTestL()
    {
    
    EUNIT_ASSERT( iManager->RtpObserver() == NULL );
    EUNIT_ASSERT( iManager->MediaObserver() == NULL );
//    EUNIT_ASSERT( iManager->SessionObserver() == NULL );
    
    iManager->SetSessionObserver( iSessionObserver );
    EUNIT_ASSERT( iManager->SessionObserver() == iSessionObserver );
    iManager->SetMediaObserver( iStreamObserver );
    EUNIT_ASSERT( iManager->MediaObserver() == iStreamObserver );
    iManager->SetRtpObserver( iRtpObserver );
    EUNIT_ASSERT( iManager->RtpObserver() == iRtpObserver );
    
    iManager->SetTransactionObserver( iTransactionObserver );
    EUNIT_ASSERT( iManager->TransactionObserver() == iTransactionObserver );
    
    iManager->SetInTransactionObserver( iInTransactionObserver );
    EUNIT_ASSERT( iManager->InTransactionObserver() == iInTransactionObserver );
    
    EUNIT_ASSERT( &(iManager->ServerSession()) != NULL );
    
    }
    

// ----------------------------------------------------------------------------
// CMceManagerTest::IdTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::IdTestL()
    {
    EUNIT_ASSERT( iManager->AppUid().iUid == iUid.iUid );

    for(int i = 0; i<10;i++ )
        {
        TMceMediaId mid = iManager->NextMediaId();
        EUNIT_ASSERT( mid.iAppId == iManager->AppUid().iUid );
        EUNIT_ASSERT( mid.iId == i + 1 );
        }

    }

// ----------------------------------------------------------------------------
// CMceManagerTest::SetDefaultHeadersTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::SetDefaultHeadersTestL()
    {
    // NULL, NULL
   iManager->SetDefaultHeadersL( NULL, NULL );  
    
    // NULL, headers
    CDesC8Array* headers1 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers1 );
    headers1->AppendL( KMceHeader1 );
    headers1->AppendL( KMceHeader2 );
    iManager->SetDefaultHeadersL( NULL, headers1 ); 
    CleanupStack::Pop( headers1 );
     
    // methods, NULL 
    CDesC8Array* methods1 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( methods1 );
    methods1->AppendL( KMceMethod1 );
    methods1->AppendL( KMceMethod2 );
    iManager->SetDefaultHeadersL( methods1, NULL ); 
    CleanupStack::Pop( methods1 );
    
    // methods, headers
    CDesC8Array* methods2 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( methods2 );
    methods2->AppendL( KMceMethod1 );
    methods2->AppendL( KMceMethod2 ); 
    
    CDesC8Array* headers2 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( headers2 );
    headers2->AppendL( KMceHeader1 );
    headers2->AppendL( KMceHeader2 );
    
    iManager->SetDefaultHeadersL( methods2, headers2 );  
    CleanupStack::Pop( headers2 );  
    CleanupStack::Pop( methods2 );
    }

// ----------------------------------------------------------------------------
// CMceManagerTest::DefaultHeadersTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::DefaultHeadersTestL()
    {
    CDesC8Array* defHdrs = iManager->DefaultHeadersL( KMceMethod1 );
    EUNIT_ASSERT( defHdrs != NULL );
    delete defHdrs;
    }

// ----------------------------------------------------------------------------
// CMceManagerTest::EventManagerReceiverTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::EventManagerReceiverTestL()
    {
    // Tests for the leaving cases
    CMceEventManagerReceiver* receiver = iManager->iEventReceiver;
    TMceIds ids;
    ids.iMsgType = EMceItcMsgTypeSession;
    HBufC8* context = KMceTestFailContext().AllocLC();
    HBufC8* content = NULL;
    TRAPD( err1, receiver->IncomingEventL( EMceItcStateChanged, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )  
    EUNIT_ASSERT_EQUALS( err1, KErrNotSupported );
    
    TRAPD( err2, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )  
    EUNIT_ASSERT_EQUALS( err2, KErrNotSupported );
    
    TRAPD( err3, receiver->IncomingEventL( EMceItcStateChanged, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )   
    EUNIT_ASSERT_EQUALS( err3, KErrNotSupported );
    
    TRAPD( err4, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 )   
    EUNIT_ASSERT_EQUALS( err4, KErrNotSupported );
    
    TRAPD( err5, receiver->IncomingEventL( EMceItcStateChanged, ids ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err5 )   
    EUNIT_ASSERT_EQUALS( err5, KErrNotSupported );
    
    TRAPD( err6, receiver->ErrorOccuredL( ids, KErrGeneral ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err6 )   
    EUNIT_ASSERT_EQUALS( err6, KErrGeneral );
    
    // IncomingEventL; EMceItcObjectAdded, EMceItcMsgTypeSession, context, no content
    ids.iMsgType = EMceItcMsgTypeSession;
    TRAPD( err7, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err7 )   
    EUNIT_ASSERT_EQUALS( err7, KErrNotSupported );
    
    CleanupStack::PopAndDestroy(context);
    // IncomingEventL; EMceItcEventTypeEither
    HBufC8* ct = KMceContentType().AllocLC();
    CDesC8Array* hdrs = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs );
    hdrs->AppendL( KMceHeader1 );
    hdrs->AppendL( KMceHeader2 );
    CMceMsgSIPEvent* eventMsg = new(ELeave) CMceMsgSIPEvent( 1,
                                                             1,
                                                             EMceItcEventTypeEither,
                                                             CMceRefer::ENoSuppression,
                                                             0,
                                                             hdrs,
                                                             ct );
    CleanupStack::Pop( hdrs );                             
    CleanupStack::Pop( ct );
    CleanupStack::PushL( eventMsg );
    eventMsg->EncodeL();
    context = eventMsg->EncodeBuffer().Ptr(0).AllocL();
    CleanupStack::PopAndDestroy( eventMsg );
    CleanupStack::PushL( context );
    ids.iMsgType = EMceItcMsgTypeEvent;
    TRAPD( err8, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err8 )   
    EUNIT_ASSERT_EQUALS( err8, KErrNotSupported );
    CleanupStack::PopAndDestroy( context );
    }

// ----------------------------------------------------------------------------
// CMceManagerTest::EventManagerReceiverTest2L
// ----------------------------------------------------------------------------
//
void CMceManagerTest::EventManagerReceiverTest2L()
    {
    // Test for uncovered branches of HandleIncomingEventL 
    TUint32 sesId = 123;
    TUint32 dlgId = 456;
    TUint32 interval = 180;
    EUNIT_ASSERT( iInEventObserver->iEvent == NULL );
    // EMceItcEventTypeSubscribe && no in event observer
    iManager->SetInEventObserver( NULL );
    CMceMsgSIPEvent* eventMsg1 = new(ELeave) CMceMsgSIPEvent( sesId,
                                                              dlgId,
                                                              EMceItcEventTypeSubscribe,
                                                              CMceRefer::ENoSuppression,
                                                              interval,
                                                              NULL,
                                                              NULL );
    CleanupStack::PushL( eventMsg1 );
    eventMsg1->EncodeL();
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = eventMsg1->EncodeBuffer().Ptr(0).AllocL();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    CleanupStack::PopAndDestroy( eventMsg1 );
    
    iManager->iEventReceiver->iIdsPckg().iAppUID = iManager->AppUid().iUid;
    iManager->iEventReceiver->iIdsPckg().iSessionID = sesId;
    iManager->iEventReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;
    iManager->iEventReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeEvent;

    MCE_EVE_RECEIVE( iManager, KErrNone );
    EUNIT_ASSERT( iInEventObserver->iEvent == NULL );
    
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    
    iManager->SetInEventObserver( iInEventObserver );
    
    // EMceItcEventTypeSubscribe && no container
    iManager->iContainer = NULL;
    HBufC8* ct2 = KMceContentType().AllocLC();
    CDesC8Array* hdrs2 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs2 );
    hdrs2->AppendL( KMceHeader1 );
    hdrs2->AppendL( KMceHeader2 );
    CMceMsgSIPEvent* eventMsg2 = new(ELeave) CMceMsgSIPEvent( sesId,
                                                              dlgId,
                                                              EMceItcEventTypeSubscribe,
                                                              CMceRefer::ENoSuppression,
                                                              interval,
                                                              hdrs2,
                                                              ct2 );
    CleanupStack::Pop( hdrs2 );                                                              
    CleanupStack::Pop( ct2 );
    CleanupStack::PushL( eventMsg2 );
    eventMsg2->EncodeL();
    iStorage->iContext = eventMsg2->EncodeBuffer().Ptr(0).AllocL();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();

    CleanupStack::PopAndDestroy( eventMsg2 );
    
    iManager->iEventReceiver->iIdsPckg().iAppUID = iManager->AppUid().iUid;
    iManager->iEventReceiver->iIdsPckg().iSessionID = sesId;
    iManager->iEventReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;
    iManager->iEventReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeEvent;

    MCE_EVE_RECEIVE( iManager, KErrNone );
    EUNIT_ASSERT( iInEventObserver->iEvent != NULL );
    CMceEvent* event = iInEventObserver->iEvent;
    EUNIT_ASSERT_EQUALS( event->Id(), sesId );
    EUNIT_ASSERT( iInEventObserver->iHeaders == NULL );
    EUNIT_ASSERT( iInEventObserver->iBody == NULL );
    EUNIT_ASSERT_EQUALS( iInEventObserver->iStatusCode, 0 );
    EUNIT_ASSERT( iInEventObserver->iReasonPhrase == NULL );
    //Set Eactive is for testing othewise once it delete event, it will leaves -18
    event->iState = CMceEvent::EActive;
    MCE_TEST_DELETE( event );
    
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    iManager->iContainer = &iContainer;
    
    // EMceItcEventTypeRefer && no in refer observer
    iManager->SetInReferObserver( NULL );
    CMceMsgSIPEvent* eventMsg3 = new(ELeave) CMceMsgSIPEvent( sesId,
                                                              dlgId,
                                                              EMceItcEventTypeRefer,
                                                              CMceRefer::ESuppressed,
                                                              interval,
                                                              NULL,
                                                              NULL );
    CleanupStack::PushL( eventMsg3 );
    eventMsg3->EncodeL();
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iStorage->iContext = eventMsg3->EncodeBuffer().Ptr(0).AllocL();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    CleanupStack::PopAndDestroy( eventMsg3 );
    
    iManager->iEventReceiver->iIdsPckg().iAppUID = iManager->AppUid().iUid;
    iManager->iEventReceiver->iIdsPckg().iSessionID = sesId;
    iManager->iEventReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;
    iManager->iEventReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeEvent;

    MCE_EVE_RECEIVE( iManager, KErrNone );
    EUNIT_ASSERT( iInReferObserver->iRefer == NULL );
    
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    
    iManager->SetInReferObserver( iInReferObserver );
    
    // EMceItcEventTypeRefer && no container
    iManager->iContainer = NULL;
    HBufC8* ct4 = KMceContentType().AllocLC();
    CDesC8Array* hdrs4 = new( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( hdrs4 );
    hdrs4->AppendL( KMceHeader1 );
    hdrs4->AppendL( KMceHeader2 );
    CMceMsgSIPEvent* eventMsg4 = new(ELeave) CMceMsgSIPEvent( sesId,
                                                              dlgId,
                                                              EMceItcEventTypeRefer,
                                                              CMceRefer::ESuppressed,
                                                              interval,
                                                              hdrs4,
                                                              ct4 );
    CleanupStack::Pop( hdrs4 );                                                              
    CleanupStack::Pop( ct4 );
    CleanupStack::PushL( eventMsg4 );
    eventMsg4->EncodeL();
    iStorage->iContext = eventMsg4->EncodeBuffer().Ptr(0).AllocL();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = iStorage->iContext->Length();
    
    iStorage->iContent = KMceMessageBody().AllocL();
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = iStorage->iContent->Length();

    CleanupStack::PopAndDestroy( eventMsg4 );
    
    iManager->iEventReceiver->iIdsPckg().iAppUID = iManager->AppUid().iUid;
    iManager->iEventReceiver->iIdsPckg().iSessionID = sesId;
    iManager->iEventReceiver->iIdsPckg().iCallbackID = EMceItcObjectAdded;
    iManager->iEventReceiver->iIdsPckg().iMsgType = EMceItcMsgTypeEvent;

    MCE_EVE_RECEIVE( iManager, KErrNone );
    EUNIT_ASSERT( iInReferObserver->iRefer != NULL );
    CMceRefer* refer = iInReferObserver->iRefer;
    EUNIT_ASSERT_EQUALS( refer->Id(), sesId );
    EUNIT_ASSERT( iInEventObserver->iHeaders == NULL );
    EUNIT_ASSERT( iInEventObserver->iBody == NULL );
    EUNIT_ASSERT_EQUALS( iInEventObserver->iStatusCode, 0 );
    EUNIT_ASSERT( iInEventObserver->iReasonPhrase == NULL );
    MCE_TEST_DELETE( refer );
    
    iStorage->Reset();
    iManager->iEventReceiver->iSizesPckg().iContextBufSize = KErrNotFound;
    iManager->iEventReceiver->iSizesPckg().iContentBufSize = KErrNotFound;
    iManager->iContainer = &iContainer;
    }

// ----------------------------------------------------------------------------
// CMceManagerTest::ManagerReceiverTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::ManagerReceiverTestL()
    {
    // Tests for the leaving cases
    CMceManagerReceiver* receiver = iManager->iSessionReceiver;
    TMceIds ids;
    ids.iMsgType = EMceItcMsgTypeEvent;
    HBufC8* context = KMceTestFailContext().AllocLC();
    HBufC8* content = NULL;
    TRAPD( err1, receiver->IncomingEventL( EMceItcStateChanged, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err1 )  
    EUNIT_ASSERT_EQUALS( err1, KErrNotSupported );
    
    TRAPD( err2, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err2 )  
    EUNIT_ASSERT_EQUALS( err2, KErrNotSupported );
    
    TRAPD( err3, receiver->IncomingEventL( EMceItcStateChanged, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err3 )  
    EUNIT_ASSERT_EQUALS( err3, KErrNotSupported );
    
    TRAPD( err4, receiver->IncomingEventL( EMceItcObjectAdded, ids, *context, content ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err4 ) 
    EUNIT_ASSERT_EQUALS( err4, KErrNotSupported );
    
    CleanupStack::PopAndDestroy(context);
    
    TRAPD( err5, receiver->ErrorOccuredL( ids, KErrGeneral ) );
    MCE_TEST_HANDLE_ALLOC_FAILURE( err5 )   
    EUNIT_ASSERT_EQUALS( err5, KErrGeneral );
    }
 
// ----------------------------------------------------------------------------
// CMceManagerTest::FindReferTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::FindReferTestL()
    {
    MCE_CREATE_PROFILE;
    CMceRefer* refer1 = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo );
    CleanupStack::PushL( refer1 );
    CMceEvent* event1 = refer1->ReferEvent();
    
    CMceRefer* refer2 = CMceOutRefer::NewL( *iManager, *profile, KMceRecipient, KMceReferTo );
    CleanupStack::PushL( refer2 );
    CMceEvent* event2 = refer2->ReferEvent();
    
    CMceOutEvent* event3 = CMceOutEvent::NewL( *iManager, *profile, KMceRecipient, KMceEventHeader, 180 );
    CleanupStack::PushL( event3 );
    
    CMceRefer* found = NULL;
   
    // no refer
    found = iManager->FindRefer( *event3 );
    EUNIT_ASSERT( found == NULL );
    
    found = iManager->FindRefer( *event2 );
    EUNIT_ASSERT( found == refer2 );
    
    found = iManager->FindRefer( *event1 );
    EUNIT_ASSERT( found == refer1 );
    event3->iState = CMceEvent::EActive;
    event2->iState = CMceEvent::ETerminated;
    event1->iState = CMceEvent::ETerminated;
    CleanupStack::PopAndDestroy( event3 );
    CleanupStack::PopAndDestroy( refer2 );
    CleanupStack::PopAndDestroy( refer1 );
    MCE_DELETE_PROFILE;
    }
    
// ----------------------------------------------------------------------------
// CMceManagerTest::TransCodeTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::TransCodeTestL()
    {
    MCE_CREATE_PROFILE;
   
    // Transcode without session
    CMceFileSource* fileSource = CMceFileSource::NewL( *iManager, KMceTestAVFileName() );
    CleanupStack::PushL(fileSource);
    iManager->TranscodeL(*fileSource);
    TInt found = iManager->iTranscodingFiles.Find(fileSource);
    EUNIT_ASSERT ( found != KErrNotFound);
    
    CleanupStack::PopAndDestroy(fileSource);

    // Transcode with session
    CMceOutSession* session =
		CMceOutSession::NewL( *iManager, *profile, KMceRecipient );	
	CleanupStack::PushL( session );
    CMceVideoStream* stream = CMceVideoStream::NewLC();
    CMceFileSource* fileSource2 = CMceFileSource::NewL( *iManager, KMceTestAVFileName() );
    CleanupStack::PushL(fileSource2);
    stream->SetSourceL( fileSource2 );
    CleanupStack::Pop( fileSource2 );
    CMceRtpSink* rtpSink = CMceRtpSink::NewLC();
    stream->AddSinkL( rtpSink );
    CleanupStack::Pop( rtpSink );
    
	session->AddStreamL( stream );
    CleanupStack::Pop( stream );
    
    fileSource2->TranscodeL( KMceTestAVFileName() );
    found = iManager->iTranscodingFiles.Find(fileSource2);
    EUNIT_ASSERT ( found != KErrNotFound);
    
    CleanupStack::Pop( session );
    MCE_TEST_DELETE( session );
    
    MCE_DELETE_PROFILE;
    }    
    
// ----------------------------------------------------------------------------
// CMceManagerTest::TransCodeCompletedTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::TransCodeCompletedTestL()
    {
    MCE_CREATE_PROFILE;
    CMceFileSource* fileSource = CMceFileSource::NewL( *iManager, KMceTestAVFileName() );
    CleanupStack::PushL(fileSource);
    
    iManager->TranscodeL(*fileSource);
    TInt found = iManager->iTranscodingFiles.Find(fileSource);
    EUNIT_ASSERT ( found != KErrNotFound);
    
    iManager->TranscodeCompleted(*fileSource);
    found = iManager->iTranscodingFiles.Find(fileSource);
    EUNIT_ASSERT ( found == KErrNotFound);
    
    CleanupStack::PopAndDestroy(fileSource);
    MCE_DELETE_PROFILE;
    }        

// ----------------------------------------------------------------------------
// CMceManagerTest::SetDtmfObserverTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::SetDtmfObserverTestL()
    {
    EUNIT_ASSERT( iManager->DtmfObserver() == iManager->iDtmfObserver );
    
    MMceDtmfObserver* obs = reinterpret_cast< MMceDtmfObserver* >( 0x55 );

	iManager->SetDtmfObserver( obs );

	EUNIT_ASSERT( iManager->DtmfObserver() == obs );
	EUNIT_ASSERT( iManager->DtmfObserver() == iManager->iDtmfObserver );
    }

// ----------------------------------------------------------------------------
// CMceManagerTest::FindAssociatedSessionTestL
// ----------------------------------------------------------------------------
//
void CMceManagerTest::FindAssociatedSessionTestL()
    {
    // No sessions
    EUNIT_ASSERT( !iManager->FindAssociatedSession( 98 ) );

    
    // Add one session
    MCE_CREATE_PROFILE;
	CMceSession* session =
		CMceOutSession::NewL( *iManager, *profile, KMceRecipient );	
    
    // Search with wrong id
    EUNIT_ASSERT( !iManager->FindAssociatedSession( 98 ) );
    
    // Search with matching id
    EUNIT_ASSERT( session ==
    		 iManager->FindAssociatedSession( session->DialogId() ) );

    MCE_DELETE_PROFILE;
    }
