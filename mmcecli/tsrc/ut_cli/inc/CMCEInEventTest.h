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




#ifndef __MCE_INEVENT_TEST_H__
#define __MCE_INEVENT_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceManager;
class CMceManagerObserverStub;
class CMceSessionObserverStub;
class CMceInEventObserverStub;
class CMCEThreadLocalStorage;
class CMceStreamObserverStub;
class CMceRtpObserverStub;
class CMceInEvent;
class CMceEvent;

class CMceInEventTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceInEventTest()  {}
    inline ~CMceInEventTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void AcceptTestL();

    void RejectTestL();
    
    void RespondTest1L();

    void RespondTest2L();
    
    void RespondTest3L();
    
    void RespondTest4L();
    
	void NotifyTestL();
    
private://data


    TUid iUid;
    
    CMceManager* iManager;
    
    CMceManagerObserverStub* iManagerObserver;
    
    CMceSessionObserverStub* iSessionObserver;
    
    CMceInEventObserverStub* iInEventObserver;
    
    CMceStreamObserverStub* iStreamObserver;

    CMceRtpObserverStub* iRtpObserver;
	
    CMCEThreadLocalStorage* iStorage;
    
    CMceInEvent* iInEvent;

    TMceTransactionDataContainer iContainer;
    
    EUNIT_DECLARE_TEST_TABLE;
	
};

#endif // __MCE_OUTSESSION_TEST_H__
