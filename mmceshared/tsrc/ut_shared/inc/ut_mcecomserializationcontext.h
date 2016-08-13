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




#ifndef __UT__H__
#define __UT__H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>


//  INTERNAL INCLUDES


//  FORWARD DECLARATIONS

class ;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_ : public CEUnitTestSuiteClass
    {
public:     // Constructors and destructors

    static UT_* NewL();
    static UT_* NewLC();
    ~UT_();

private:    // Constructors and destructors

    UT_();
    void ConstructL();

private:    // EUNIT methods

     void SetupL();
     void Teardown();

private:    // Test methods
    

private:    // Data

	CMceMediaManager* iManager;

	EUNIT_DECLARE_TEST_TABLE; 
		
    };


#endif      //  __UT__H__

// End of file
