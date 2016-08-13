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


#ifndef __MCE_MANAGER_TEST_H__
#define __MCE_MANAGER_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceManager;
class CMceManagerObserverStub;
class CMceSessionObserverStub;
class CMCEThreadLocalStorage;
class CMceStreamObserverStub;
class CMceRtpObserverStub;
class CMceInEventObserverStub;
class CMceInReferObserverStub;
class CMceTransactionObserverStub;
class CMceInTransactionObserverStub;

class CMceManagerTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceManagerTest()  {}
    inline ~CMceManagerTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void SesionsTestL();
    void ObserversTestL();
    void IdTestL();
    void SetDefaultHeadersTestL();
    void DefaultHeadersTestL();
    void EventManagerReceiverTestL();
    void EventManagerReceiverTest2L();
    void ManagerReceiverTestL();
    void FindReferTestL();
    void TransCodeTestL();
    void TransCodeCompletedTestL();
    void SetDtmfObserverTestL();
    void FindAssociatedSessionTestL();
    
private://data


    TUid iUid;
    
    CMceManager* iManager;
    
    CMceManagerObserverStub* iManagerObserver;
    
    CMceSessionObserverStub* iSessionObserver;

    CMceStreamObserverStub* iStreamObserver;

    CMceRtpObserverStub* iRtpObserver;
    
    CMceInEventObserverStub* iInEventObserver;
    
    CMceInReferObserverStub* iInReferObserver;
	
    CMCEThreadLocalStorage* iStorage;
    
    TMceTransactionDataContainer iContainer;
    
    CMceTransactionObserverStub* iTransactionObserver;
    
    CMceInTransactionObserverStub* iInTransactionObserver;
    
    EUNIT_DECLARE_TEST_TABLE;
    	
};

#endif // __MCE_MANAGER_TEST_H__
