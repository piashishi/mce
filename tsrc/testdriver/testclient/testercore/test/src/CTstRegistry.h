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
#ifndef __CTSTREGISTRY_H__
#define __CTSTREGISTRY_H__

// INCLUDES
#include <CppUnit/TestCase.h>

// FORWARD DECLARATIONS
class CTcRegistry;

// CLASS DEFINITION
/**
 * 
 */
class CTstRegistry
	: public CTestCase
	{
	public:	// Constructors and destructor

		CTstRegistry () { }
		~CTstRegistry () { }

	public:	// from CTestCase

		void setUpL();
		void tearDown();
		static MTest* suiteL();

	protected:	// Test case functions

		void TestObjectPtrL();
		void TestDestroyObjectL();

	private: // Data

		CTcRegistry* iRegistry;
		
	};

#endif	// __CTSTREGISTRY_H__