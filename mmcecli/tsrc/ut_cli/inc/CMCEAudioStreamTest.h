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




#ifndef __MCE_AUDIOSTREAM_TEST_H__
#define __MCE_AUDIOSTREAM_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceManager;
class CMceManagerObserverStub;
class CMceSessionObserverStub;
class CMCEThreadLocalStorage;
class CMceStreamObserverStub;
class CMceRtpObserverStub;
class CMceOutSession;


class CMceAudioStreamTest : public CEUnitTestSuiteClass
	{
public:

    inline CMceAudioStreamTest()  {}
    inline ~CMceAudioStreamTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

    void EnableTestL();
    void DisableTestL();
    void BindTestL();
    void EventReceivedTestL();
    void EventReceivedTest2L();
    void AddCodecTestL();
    void ReorderCodecsTestL();
    void ReorderCodecsByPreferncesTestL();
    void RemoveCodecTestL();
    void SynchronizeWithFileTestL();
    void RemoveSinkTestL();
    void ReplaceCodecsLTestL();
    void FindCodecTestL();

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

#endif // __MCE_AUDIOSTREAM_TEST_H__
