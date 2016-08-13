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


#ifndef __MCE_OUTSESSION_TEST_H__
#define __MCE_OUTSESSION_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceManager;
class CMceManagerObserverStub;
class CMceSessionObserverStub;
class CMCEThreadLocalStorage;
class CMceStreamObserverStub;
class CMceRtpObserverStub;
class CMceOutSession;

class CMceOutSessionTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceOutSessionTest()  {}
    inline ~CMceOutSessionTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void EstablishTestL();

    void CancelTestL();
    
    void RemainTestL();
    
    void NewLTestL();
    
private://data


    TUid iUid;
    
    CMceManager* iManager;
    
    CMceManagerObserverStub* iManagerObserver;
    
    CMceSessionObserverStub* iSessionObserver;
    
    CMceStreamObserverStub* iStreamObserver;

    CMceRtpObserverStub* iRtpObserver;
	
    CMCEThreadLocalStorage* iStorage;
    
    CMceOutSession* iOutSession;

    TMceTransactionDataContainer iContainer;
    
    EUNIT_DECLARE_TEST_TABLE;
	
};

#endif // __MCE_OUTSESSION_TEST_H__
