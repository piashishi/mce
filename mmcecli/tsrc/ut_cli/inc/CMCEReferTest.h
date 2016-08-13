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


#ifndef __MCE_REFER_TEST_H__
#define __MCE_REFER_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceManager;
class CMceReferObserverStub;
class CMCEThreadLocalStorage;
class CMceRefer;

class CMceReferTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceReferTest()  {}
    inline ~CMceReferTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests
    
    void ErrorOccuredTestL();
    void ErrorOccuredTest2L();
    void EventReceivedTestL();
    void EventReceivedTest2L();
    void EventReceivedTest3L();
    void ReceiverTestL();
    void ConstructTestL();
    void ResolveStateTestL();
    void HandleEventTestL();
    void EventStateChangedTestL();
    void HandleStateChangedTestL();
    void TransferEventOwnershipTestL();
    void AssociatedSessionTestL();
	void AssociatedEventsLTestL();
	void AssociatedRefersLTestL();
    
private://data


    TUid iUid;
    
    CMceManager* iManager;
    
    CMceReferObserverStub* iReferObserver;
    
    
    CMCEThreadLocalStorage* iStorage;
    
    CMceRefer* iRefer;

    TMceTransactionDataContainer iContainer;
	
	EUNIT_DECLARE_TEST_TABLE;
};

#endif // __MCE_REFER_TEST_H__
