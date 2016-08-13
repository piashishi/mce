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


#ifndef __MCE_MEDIASOURCE_TEST_H__
#define __MCE_MEDIASOURCE_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceMicSource;

class CMceMediaSourceTest: public CEUnitTestSuiteClass
	{
public:
    
    inline CMceMediaSourceTest()  {}
    inline ~CMceMediaSourceTest() {}
	
    void setUpL();
    void tearDown();
    
    static MEUnitTestSuite* suiteL();
	
public://tests
    
	void ConstructionTestL();
    void GettersTestL();
    void DoDisableTestL();
    void DoEnableTestL();
    void ExternalizeTestL();
    void InternalizeTestL();
    void InitializeTestL();
    void FactoryTestL();
    void HandleEventTestL();
    void EventReceivedTestL();
    void UpdatedTestL();
    void SetGainTestL();
    void GainTestL();
    void MaxGainTestL();
    void SerializationIdTestL();
    void UnInitializeTestL();
    void DtmfAvailableTestL();
    void DtmfActiveTestL();
    void StartDtmfToneTestL();
    void StopDtmfToneTestL();
    void SendDtmfToneTestL();
    void SendDtmfToneSequenceTestL();
    void CancelDtmfToneSequenceTestL();
    
private:    //data
    
	// Use mic source to test base class
	CMceMicSource* iMic;
    TMceTransactionDataContainer iContainer;
    
    EUNIT_DECLARE_TEST_TABLE;
    };

#endif // __MCE_MEDIASOURCE_TEST_H__
