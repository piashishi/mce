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


#ifndef __MCE_FCMSGEXCHANGE_TEST_H__
#define __MCE_FCMSGEXCHANGE_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>

class CMceManager;
class CMceSession;
class CMceFcMsgExchange;
class CMCEThreadLocalStorage;
class CMceFcMsgObserverStub;

class CMceFcMsgExchangeTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceFcMsgExchangeTest()  {}
    inline ~CMceFcMsgExchangeTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void InitializeTestL();
        
    void SendTestL();

    void MediaAttributeLinesTestL();

    void UpdateTestL();
    
private://data
    TUid iUid;
    
    CMCEThreadLocalStorage* iStorage;
    
    CMceManager* iManager;
    
    CMceSession* iOutSession;
    
    CMceFcMsgExchange* iFC;
    
    CMceFcMsgObserverStub* iFCObserver;
    
    EUNIT_DECLARE_TEST_TABLE;
    	
};




#endif // __MCE_FCMSGEXCHANGE_TEST_H__
