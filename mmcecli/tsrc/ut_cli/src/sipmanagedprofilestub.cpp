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



#include "sipmanagedprofile.h"
#include "sipmanagedprofileregistry.h"

EXPORT_C CSIPManagedProfile::~CSIPManagedProfile()
    {
    }

EXPORT_C void CSIPManagedProfile::SetType(const TSIPProfileTypeInfo& /*aSIPProfileTypeInfo*/)
    {
    }

EXPORT_C TInt CSIPManagedProfile::SetParameter(TUint32 /*aParam*/, const TDesC8& /*aVal*/)
    {
    return KErrNone;
    }

EXPORT_C TInt CSIPManagedProfile::SetParameter(TUint32 /*aParam*/, TUint32 /*aVal*/)
    {
    return KErrNone;
    }

EXPORT_C TInt CSIPManagedProfile::SetParameter(TUint32 /*aParam*/, TBool /*aVal*/)
    {
    return KErrNone;
    }
    
EXPORT_C TInt CSIPManagedProfile::SetParameter(TUint32 /*aParam*/, const MDesC8Array& /*aVal*/)
    {
    return KErrNone;
    }
        
EXPORT_C TInt CSIPManagedProfile::SetParameter(TUint32 /*aServerType*/, TUint32 /*aParam*/, const TDesC8& /*aVal*/)
    {
    return KErrNone;
    }

EXPORT_C CSIPManagedProfile* CSIPManagedProfile::CloneL() const
    {
    User::Leave( KErrNotSupported );
    return 0;
    }

CSIPManagedProfile* CSIPManagedProfile::NewL(CSIPManagedProfileRegistry* aSIPRegistry)
    {
    CSIPManagedProfile* self = new ( ELeave ) CSIPManagedProfile( aSIPRegistry );
    return self;
    }

CSIPManagedProfile* CSIPManagedProfile::NewLC(CSIPManagedProfileRegistry* aSIPRegistry)
    {
    CSIPManagedProfile* self = new ( ELeave ) CSIPManagedProfile( aSIPRegistry );
    CleanupStack::PushL( self );
    return self;
    }

CSIPManagedProfile::CSIPManagedProfile(CSIPManagedProfileRegistry* aSIPRegistry)
    : CSIPProfile( aSIPRegistry )
    {
    }

void CSIPManagedProfile::SetParameterL(TUint32 /*aParam*/, const TDesC8& /*aVal*/)
    {
    }

void CSIPManagedProfile::SetParameterL(TUint32 /*aParam*/, TUint32 /*aVal*/)
    {
    }

void CSIPManagedProfile::SetParameterL(TUint32 /*aParam*/, TBool /*aVal*/)
    {
    }

void CSIPManagedProfile::SetParameterL(TUint32 /*aServerType*/,
            TUint32 /*aParam*/, const TDesC8& /*aVal*/)
    {
    }

EXPORT_C void CSIPManagedProfile::SetParameterL(TUint32 /*aParam*/, const MDesC8Array& /*aVal*/)
    {
    }
