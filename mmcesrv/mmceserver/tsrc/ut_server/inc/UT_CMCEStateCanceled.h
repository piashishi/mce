/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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




#ifndef __UT_CMCESTATECANCELED_H__
#define __UT_CMCESTATECANCELED_H__

//  EXTERNAL INCLUDES
#include <digia/eunit/ceunittestsuiteclass.h>

//  INTERNAL INCLUDES
#include "mceclientserver.h"

//  FORWARD DECLARATIONS
class CMceSipSession;
class CMceCsSession;
class CMceServerCore;
class CMCETls;
class CMceStateCanceled;

//  CLASS DEFINITION
/**
 *
 * EUnitWizard generated test class. 
 *
 */
class UT_CMceStateCanceled
     : public CEUnitTestSuiteClass
    {
    public:     // Constructors and destructors

        /**
         * Two phase construction
         */
        static UT_CMceStateCanceled* NewL();
        static UT_CMceStateCanceled* NewLC();
        /**
         * Destructor
         */
        ~UT_CMceStateCanceled();

    private:    // Constructors and destructors

        UT_CMceStateCanceled();
        void ConstructL();

	public: 	// From observer interface
		
		

    private:    // New methods

         void SetupL();
         void Teardown();        
        
         void UT_CMceStateCanceled_AcceptLL();
         void UT_CMceStateCanceled_EntryLL();
         void UT_CMceStateCanceled_ExitLL();
        

    private:    // Data

    	EUNIT_DECLARE_TEST_TABLE; 
    		
    	TMceIds iIds;
        CMceServerCore* iServerCore;
        CMceCsSession* iSession;
        CMceSipSession* iSipSession;
    
    private: //not Owned


        CMCETls* iStorage;
		CMceStateCanceled* iState;
		
    };

#endif      //  __UT_CMCESTATECANCELED_H__

// End of file
