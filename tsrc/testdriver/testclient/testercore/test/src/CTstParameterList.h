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
#ifndef __CTSTPARAMETERLIST_H__
#define __CTSTPARAMETERLIST_H__

// INCLUDES
#include <CppUnit/TestCase.h>

// FORWARD DECLARATIONS
class CTcParameterList;
class MTcTyped;

// CLASS DEFINITION
/**
 * Unit tests for CTcParameterList
 */
class CTstParameterList
	: public CTestCase
	{
	public:	// Constructors and destructor

		CTstParameterList () {}
		~CTstParameterList () {}

	public:	// from CTestCase

		void setUpL();
		void tearDown();
		static MTest* suiteL();

	protected:	// Test case functions

		void TestConstructorL();
		void TestAddFetchL();
		void TestInsertRemoveL();
		void TestFindL();

	private: // Utility functions

		MTcTyped* CreateNameValueLC();
		MTcTyped* CreateArrayLC();
		MTcTyped* CreateStructureLC();

	private: // Data

		/// Parameter list under test. Owned
		CTcParameterList* iList;
	
	};

#endif	// __CTSTPARAMETERLIST_H__