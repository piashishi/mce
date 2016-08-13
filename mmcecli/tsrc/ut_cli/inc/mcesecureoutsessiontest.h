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


#ifndef __MCE_SECUREOUTSESSION_TEST_H__
#define __MCE_SECUREOUTSESSION_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceManager;
class CMceManagerObserverStub;
class CMceSessionObserverStub;
class CMCEThreadLocalStorage;
class CMceStreamObserverStub;
class CMceRtpObserverStub;
class CMceSecureOutSession;


class CMceSecureOutSessionTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceSecureOutSessionTest()  {}
    inline ~CMceSecureOutSessionTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests
	
	void TypeTestL();
	void CryptoContextsTestL();
	void EstablishTestL();
	void CancelTestL();
	void RemainTestL();
	void FailureTestL();
	
    
private://data


    TUid iUid;
    
    CMceManager* iManager;
    
    CMceManagerObserverStub* iManagerObserver;
    
    CMceSessionObserverStub* iSessionObserver;

    CMceStreamObserverStub* iStreamObserver;

    CMceRtpObserverStub* iRtpObserver;
	
    CMCEThreadLocalStorage* iStorage;
	
	CMceSecureOutSession* iSecureOutSession;

    TMceTransactionDataContainer iContainer;
    
    EUNIT_DECLARE_TEST_TABLE;
	
};

#endif // __MCE_SECUREOUTSESSION_TEST_H__
