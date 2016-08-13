/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
#ifndef __CTSTCTRLCODEC_H__
#define __CTSTCTRLCODEC_H__

// INCLUDES
#include <CppUnit/TestCase.h>
#include "CTcParameterList.h"

// FORWARD DECLARATIONS
class CTcCTRLCodec;

// CLASS DEFINITION
/**
 * 
 */
class CTstCtrlCodec
	: public CTestCase
	{
	public:	// Constructors and destructor

		CTstCtrlCodec () { }
		~CTstCtrlCodec () { }

	public:	// from CTestCase

		void setUpL();
		void tearDown();
		static MTest* suiteL();

	protected:	// Test case functions

		void TestIsCompleteL();
		void TestTypeL();
		void TestGetIdentifierL();
		void TestGetParametersL();
		void TestGetParametersStructureL();
		void TestGetParametersArrayL();
		void TestConstructResponse1L();
		void TestConstructResponse2L();
		void TestConstructOkResponseL();
		void TestConstructErrorResponseL();

	private: // Data

		CTcCTRLCodec* iCodec;
		TBuf8< 1024 > iReq;
		TBuf8< 1024 > iRes;
		CTcParameterList* iList;
	
	};

#endif	// __CTSTCTRLCODEC_H__