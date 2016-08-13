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
#include <digia/eunit/EUnitMacros.h>
#include "CMceFcMsgExchangeTest.h"
#include "mcestubs.h"
#include "mcetestdefs.h"

#include "mcemanager.h"
#include "mcemanagerreceiver.h"
#include "mceeventreceiver.h"
#include "mceeventmanagerreceiver.h"
#include "mcesessionreceiver.h"

#include "mcefcmsgexchange.h"
#include "mceoutsession.h"
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


_LIT8( KMceFCTestType, "TBCP" );
_LIT8( KMceFCTestData, "some data" );
const TUint KMceFCTestPort = 2050;
const TUint KMceFCTestDefaultPort = 0;


// ----------------------------------------------------------------------------
// CMceFcMsgExchangeTest::setUpL
// ----------------------------------------------------------------------------
//	
void CMceFcMsgExchangeTest::setUpL()
    {
    iStorage = new (ELeave) CMCEThreadLocalStorage();
    Dll::SetTls( iStorage );
        
    iUid = TUid::Uid( 777 );
   
    iManager = CMceManager::NewL( iUid );
    
    iFC = CMceFcMsgExchange::NewL( *iManager, KMceFCTestType );
    
    MCE_CREATE_PROFILE;    
    
    iOutSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    
    MCE_DELETE_PROFILE;
     
    iFCObserver = new( ELeave ) CMceFcMsgObserverStub();
    
    iFC->InitializeL( *iOutSession, KMceFCTestPort, *iFCObserver );
    }

// ----------------------------------------------------------------------------
// CMceFcMsgExchangeTest::tearDown
// ----------------------------------------------------------------------------
//
void CMceFcMsgExchangeTest::tearDown()
    {
    MCE_TEST_DELETE( iOutSession );
    delete iFCObserver;
    
    delete iFC;
    
    MCE_MAN_DELETE( iManager );   
    
    delete iStorage;
    Dll::SetTls( NULL );
    
    }

// ----------------------------------------------------------------------------
// CMceFcMsgExchangeTest::suiteL
// ----------------------------------------------------------------------------
//
MEUnitTestSuite* CMceFcMsgExchangeTest::suiteL()
    {
    CMceFcMsgExchangeTest* suite = new CMceFcMsgExchangeTest;
    CleanupStack::PushL(suite);
    suite->CEUnitTestSuiteClass::ConstructL();
      
    CleanupStack::Pop(suite);                                   
    return suite;
  
    }
    
EUNIT_BEGIN_TEST_TABLE( 
    CMceFcMsgExchangeTest,
    "CMceFcMsgExchangeTest tests",
    "UNIT" )
MCE_EUNIT_TESTCASE("CMceFcMsgExchangeTest", setUpL, InitializeTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFcMsgExchangeTest", setUpL, SendTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFcMsgExchangeTest", setUpL, MediaAttributeLinesTestL, tearDown )
MCE_EUNIT_TESTCASE("CMceFcMsgExchangeTest", setUpL, UpdateTestL, tearDown )
EUNIT_END_TEST_TABLE

void CMceFcMsgExchangeTest::InitializeTestL()
    {
    MCE_CREATE_PROFILE;    
    // fake an insession
    CMceSession* inSession = CMceOutSession::NewL( *iManager, *profile, KMceRecipient );
    CleanupStack::PushL( inSession );
    inSession->iFlatData->iType = CMceComSession::EInSession;
    
    iFC->InitializeL( *inSession, KMceFCTestDefaultPort, *iFCObserver );
    CleanupStack::Pop( inSession );
    MCE_TEST_DELETE( inSession );
    MCE_DELETE_PROFILE;    
    }
        
void CMceFcMsgExchangeTest::SendTestL()
    {
    HBufC8* data = KMceFCTestData().AllocLC();
    iFC->SendL( *iOutSession, data );
    CleanupStack::Pop( data );
    }

void CMceFcMsgExchangeTest::MediaAttributeLinesTestL()
    {
    MDesC8Array* atts = iFC->MediaAttributeLinesL( *iOutSession );
    EUNIT_ASSERT( atts != NULL );
    delete atts;
    }

void CMceFcMsgExchangeTest::UpdateTestL()
    {
    // First call with NULL
    iFC->UpdateL( *iOutSession, NULL );
    
    // Create attribute array
    CDesC8Array* atts = new ( ELeave ) CDesC8ArrayFlat( KMceArrayGranularity );
    CleanupStack::PushL( atts );
    atts->AppendL( KMceAttr1 );
    atts->AppendL( KMceAttr2 );
    
    iFC->UpdateL( *iOutSession, atts );
    CleanupStack::Pop( atts );
    }
    
// End of file
