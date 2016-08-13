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


#ifndef __MCE_INREFER_TEST_H__
#define __MCE_INREFER_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"
class CMceManager;
class CMceManagerObserverStub;
class CMceSessionObserverStub;
class CMceInEventObserverStub;
class CMceInReferObserverStub;
class CMceEventObserverStub;
class CMceReferObserverStub;
class CMCEThreadLocalStorage;
class CMceStreamObserverStub;
class CMceRtpObserverStub;
class CMceInEvent;
class CMceEvent;
class CMceInRefer;

class CMceInReferTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceInReferTest()  {}
    inline ~CMceInReferTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void AcceptTestL();
    
    void AcceptTest2L();

    void RejectTestL();
    
    void RejectTest2L();
    
    void RespondTest1L();

    void RespondTest2L();
    
    void RespondTest3L();
    
    void RespondTest4L();
    
    void RespondTest5L();
    
    void RespondTest6L();
    
    void TerminateTestL();
    
private://data


    TUid iUid;
    
    CMceManager* iManager;
    
    CMceManagerObserverStub* iManagerObserver;
    
    CMceSessionObserverStub* iSessionObserver;
    
    CMceInEventObserverStub* iInEventObserver;
    
    CMceEventObserverStub* iEventObserver;
    
    CMceInReferObserverStub* iInReferObserver;
    
    CMceReferObserverStub* iReferObserver;
    
    CMceStreamObserverStub* iStreamObserver;

    CMceRtpObserverStub* iRtpObserver;
	
    CMCEThreadLocalStorage* iStorage;
    
    CMceInEvent* iInEvent;
    CMceInRefer* iInRefer;

    TMceTransactionDataContainer iContainer;
	
	EUNIT_DECLARE_TEST_TABLE;
};

#endif // __MCE_OUTSESSION_TEST_H__
