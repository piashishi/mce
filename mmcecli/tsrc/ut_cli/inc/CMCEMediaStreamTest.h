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


#ifndef __MCE_MEDIASTREAM_TEST_H__
#define __MCE_MEDIASTREAM_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceManager;
class CMceManagerObserverStub;
class CMCEThreadLocalStorage;
class CMceStreamObserverStub;
class CMceOutSession;
class CMceAudioStream;
class CMceInSession;

class CMceMediaStreamTest: public CEUnitTestSuiteClass
	{
public:

    inline CMceMediaStreamTest()  {}
    inline ~CMceMediaStreamTest() {}
	
    void setUpL();
    void tearDown();

    static MEUnitTestSuite* suiteL();
	
public://tests

	void ConstructionTestL();
	void GettersTestL();
	void SetLocalMediaPortTestL();
	void SessionTestL();
	void FactoriesTestL();
	void ExternalizeTestL();
	void InternalizeTestL();
	void SetMediaAttributeLinesTestL();
	void MediaAttributeLinesTestL();
    
private://data


    TUid iUid;
    
    CMceManager* iManager;
    
    CMceManagerObserverStub* iManagerObserver;
    
    CMceStreamObserverStub* iStreamObserver;
	
    CMCEThreadLocalStorage* iStorage;
        
    CMceOutSession* iOutSession;
    
    CMceInSession* iInSession;
    
    CMceAudioStream* iAudio;
    
    TMceTransactionDataContainer iContainer;	
    
    EUNIT_DECLARE_TEST_TABLE;
};

#endif // __MCE_MEDIASTREAM_TEST_H__
