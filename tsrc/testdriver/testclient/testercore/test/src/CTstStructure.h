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
#ifndef __CTSTSTRUCTURE_H__
#define __CTSTSTRUCTURE_H__

// INCLUDES
#include <CppUnit/TestCase.h>

// FORWARD DECLARATIONS
class CTcStructure;

// CLASS DEFINITION
/**
 * Unit tests for CTcStructure
 */
class CTstStructure
	: public CTestCase
	{
	public:	// Constructors and destructor

		CTstStructure () {}
		~CTstStructure () {}

	public:	// from CTestCase

		void setUpL();
		void tearDown();
		static MTest* suiteL();

	protected:	// Test case functions

		void TestConstructorL();
		void TestSettersGettersL();
		void TestFindL();

	private: // Data

		/// Structure under test. Own.ed
		CTcStructure* iStructure;
	};

#endif	// __CTSTSTRUCTURE_H__