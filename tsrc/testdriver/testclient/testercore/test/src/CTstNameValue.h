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
#ifndef __CTSTNAMEVALUE_H__
#define __CTSTNAMEVALUE_H__

// INCLUDES
#include <CppUnit/TestCase.h>

// CLASS DEFINITION
/**
 * 
 */
class CTstNameValue
	: public CTestCase
	{
	public:	// Constructors and destructor

		CTstNameValue () { }
		~CTstNameValue () { }

	public:	// from CTestCase

		void setUpL();
		void tearDown();
		static MTest* suiteL();

	protected:	// Test case functions

		void TestConstructorL();
		void TestSettersGettersL();

	};

#endif	// __CTSTNAMEVALUE_H__