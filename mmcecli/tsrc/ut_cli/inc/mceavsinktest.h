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


#ifndef __MCE_AVSINK_TEST_H__
#define __MCE_AVSINK_TEST_H__

#include <digia/eunit/ceunittestsuiteclass.h>
#include "mcetransactiondatacontainer.h"

class CMceAvSink;

class CMceAvSinkTest: public CEUnitTestSuiteClass
	{
public:

    inline CMceAvSinkTest()  {}
    inline ~CMceAvSinkTest() {}
	
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
    void SetVolumeTestL();
    void VolumeTestL();
    void MaxVolumeTestL();
    void EndPointProxyTestL();
    void SerializationIdTestL();
    void UnInitializeTestL();
    
private://data

	// Use speaker sink to test base class
	CMceAvSink* iAV;

    TMceTransactionDataContainer iContainer;
    
    EUNIT_DECLARE_TEST_TABLE;
	};

#endif // __MCE_AVSINK_TEST_H__
