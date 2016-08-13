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
#ifndef __CTSTARRAY_H__
#define __CTSTARRAY_H__

// INCLUDES
#include <CppUnit/TestCase.h>

// FORWARD DECLARATIONS
class CTcArray;

// CLASS DEFINITION
/**
 * Unit tests for CTcArray.
 */
class CTstArray
	: public CTestCase
	{
	public:	// Constructors and destructor

		CTstArray () {}
		~CTstArray () {}

	public:	// from CTestCase

		void setUpL();
		void tearDown();
		static MTest* suiteL();

	protected:	// Test case functions

		void TestConstructorL();
		void TestSettersGettersL();
		void TestDescArraySetterL();

	private: // Data

		/// Array under test. Owned.
		CTcArray* iArray;

	};

#endif	// __CTSTARRAY_H__