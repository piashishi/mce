/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef CMCESESSIONTEST_H
#define CMCESESSIONTEST_H

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceManager;
class CMceManagerObserverStub;
class CMceSessionObserverStub;
class CMCEThreadLocalStorage;
class CMceStreamObserverStub;
class CMceRtpObserverStub;
class CMceInSession;
class CMceOutSession;
class CMceFcMsgObserverStub;
class CMceSession;
class CMceTransactionObserverStub;
class CMceInTransactionObserverStub;


class CMceSessionTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceSessionTest()  {}
    inline ~CMceSessionTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public: // tests

	void UpdateTestL();
	void TerminateTestL();
	void TerminateTest2L();
	void TerminateTest3L(); 
	void ErrorOccuredTestL();
	void ReceiverErrorOccuredTestL();
    void UpdatedTestL();
    void FCMessageReceivedTestL();
    void ReceiverTestL();
    void IncomingUpdateTestL();
    void IncomingUpdateTest2L();
    void IncomingUpdateTest3L();
    void IncomingUpdateTest4L();
    void ZombieTestsL();
    void FactoryTestL();
    void SetContainerTestL();
    void FCErrorOccurredTestL();
    void HandleEventTestL();
    void HandleEventResponseReceivedTestL();
    void HandleEventRequestReceivedTestL();
    void SetSessionSDPLinesTestL();
    void SessionSDPLinesTestL();
    void SessionServiceTypeTestL();
    void ControlPathSecurityLevelTestL();
    void AddStreamTestL();
    void AddStreamPrecondTestL();
    void AddStreamPullModeTestL();
    void AddStreamPullModeTest2L();
    void GetModifierTestL();
    void SetModifierTestL();
    void AssociatedEventsTestL();
    void AssociatedRefersTestL();
    void RemoveStreamTestL();
    void SIPParamsCleanupTestL();
    void AddBundleTestL();
    void TypeTestL();
    void SerializationIdTestL();
    void ExternalizeInternalizeTestL();
    void ITCSenderTestL();
    void ITCManagerTestL();
    void ConnectionActiveTestL();
    void InitializeTestL();
    void InitializeWithBundleTestL();
    void EventReceivedTestL();
    void SendRequestTestL();
    void SendResponseTestL();

private: // data

    TUid iUid;
    
    CMceManager* iManager;
    
    CMceManagerObserverStub* iManagerObserver;
    
    CMceSessionObserverStub* iSessionObserver;
    
    CMceTransactionObserverStub* iTransactionObserver;
    
    CMceInTransactionObserverStub* iInTransactionObserver;
    
    CMceStreamObserverStub* iStreamObserver;

    CMceRtpObserverStub* iRtpObserver;
    CMceFcMsgObserverStub* iFCObserver;
	
    CMCEThreadLocalStorage* iStorage;
	
	CMceInSession* iInSession;
	CMceOutSession* iOutSession;

    TMceTransactionDataContainer iContainer;	
    
    EUNIT_DECLARE_TEST_TABLE;
};

#endif // CMCESESSIONTEST_H
