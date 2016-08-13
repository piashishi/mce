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



#include "sipmanagedprofileregistry.h"
#include "sipmanagedprofile.h"

EXPORT_C CSIPManagedProfileRegistry* CSIPManagedProfileRegistry::NewL(
                        MSIPProfileRegistryObserver& aObserver)

    {
    CSIPManagedProfileRegistry* self = new ( ELeave ) CSIPManagedProfileRegistry( aObserver );
    return self;
    }
    
EXPORT_C CSIPManagedProfileRegistry* CSIPManagedProfileRegistry::NewLC(
                        MSIPProfileRegistryObserver& aObserver)
    {
    CSIPManagedProfileRegistry* self = new ( ELeave ) CSIPManagedProfileRegistry( aObserver );
    CleanupStack::PushL( self );
    return self;
    }
    
EXPORT_C CSIPManagedProfileRegistry::~CSIPManagedProfileRegistry()
    {
    }
    
EXPORT_C CSIPManagedProfile* CSIPManagedProfileRegistry::CreateL(const TSIPProfileTypeInfo& /*aType*/) 
    {
    CSIPManagedProfile* prof = CSIPManagedProfile::NewL( this );
    return prof;
    }
    
EXPORT_C TBool CSIPManagedProfileRegistry::IsInUseL(const CSIPProfile& /*aSIPProfile*/) const
    {
    return ETrue;
    }
    
EXPORT_C void CSIPManagedProfileRegistry::SaveL(CSIPProfile& /*aSIPProfile*/)
    {
    }
    
EXPORT_C void CSIPManagedProfileRegistry::DestroyL(CSIPProfile& /*aSIPProfile*/)
    {
    }
    
CSIPManagedProfileRegistry::CSIPManagedProfileRegistry(MSIPProfileRegistryObserver& aObserver)
    : CSIPProfileRegistryBase( aObserver )
    {
    }

void CSIPManagedProfileRegistry::ConstructL()
    {
    }

CSIPProfile* CSIPManagedProfileRegistry::NewInstanceL()
    {
    User::Leave( KErrNotSupported );
    return NULL;
    }
