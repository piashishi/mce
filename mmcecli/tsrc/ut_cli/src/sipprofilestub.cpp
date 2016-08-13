/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:    implementation
*
*/




//  INCLUDE FILES

#include "sipprofile.h"
//#include "sipmanagedprofile.h"
#include "sipprofileregistry.h"
//#include "sipconcreteprofile.h"
//#include "SIPProfileTypeInfo.h"

_LIT8(KSIPProfileDefAOR, "user@aa");

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CSIPProfile::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSIPProfile* CSIPProfile::NewL(CSIPProfileRegistry* aSIPRegistry)
	{
    CSIPProfile* self = CSIPProfile::NewLC (aSIPRegistry);
    CleanupStack::Pop();
    return self;
	}

// -----------------------------------------------------------------------------
// CSIPProfile::NewLC
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSIPProfile* CSIPProfile::NewLC(CSIPProfileRegistry* aSIPRegistry)
	{
	CSIPProfile* self = new(ELeave)CSIPProfile(aSIPRegistry);
    CleanupStack::PushL (self);
    self->ConstructL ();
    return self;
	}

// -----------------------------------------------------------------------------
// CSIPProfile::~CSIPProfile
// -----------------------------------------------------------------------------
//
EXPORT_C CSIPProfile::~CSIPProfile()
	{
	}

// -----------------------------------------------------------------------------
// CSIPProfile::GetParameter
// -----------------------------------------------------------------------------
//	
EXPORT_C TInt CSIPProfile::GetParameter(TUint32 /*aParam*/, TDesC8 const *& aVal ) const
	{
	const TDesC8& val= KSIPProfileDefAOR;
    aVal = &val;
	return KErrNone;
	}	

// -----------------------------------------------------------------------------
// CSIPProfile::GetParameter
// -----------------------------------------------------------------------------
//	
EXPORT_C TInt CSIPProfile::GetParameter(TUint32 aParam, TUint32& aVal) const
	{
	aVal = 1;
	if ( aParam == KSIPProfileId && iEnabled)
		{
		return KErrNotFound;
		}
	return KErrNone;
	}	

// -----------------------------------------------------------------------------
// CSIPProfile::GetParameter
// -----------------------------------------------------------------------------
//	
EXPORT_C TInt CSIPProfile::GetParameter(TUint32 /*aParam*/, TBool& aVal) const
	{
	aVal = ETrue;
	return KErrNone;
	}
	
// -----------------------------------------------------------------------------
// CSIPProfile::CSIPProfile
// -----------------------------------------------------------------------------
//	
CSIPProfile::CSIPProfile(CSIPProfileRegistryBase* aRegistry):
	iSIPProfileRegistry(aRegistry), iEnabled(EFalse)
	{
	}

// -----------------------------------------------------------------------------
// CSIPProfile::ConstructL
// -----------------------------------------------------------------------------
//	
void CSIPProfile::ConstructL()
	{

	}

// -----------------------------------------------------------------------------
// CSIPProfile::IsContextActive
// -----------------------------------------------------------------------------
//	
TBool CSIPProfile::IsContextActive() const
	{
	return ETrue;
	}
	
// -----------------------------------------------------------------------------
// CSIPProfile::ContextId
// -----------------------------------------------------------------------------
//	
TUint32 CSIPProfile::ContextId() const
	{
	return 1;
	}

// -----------------------------------------------------------------------------
// CSIPProfile::SetEnabled
// -----------------------------------------------------------------------------
//	
void CSIPProfile::SetEnabled(TBool aEnabled)
	{
	iEnabled = aEnabled;
	}
