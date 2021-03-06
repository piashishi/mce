/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:    Implementation.
*
*/




// INCLUDES

#include "TMCETestUIEngineCmdCreateVoIPSession.h"
#include "CMCETestUIEngineOutSession.h"
#include "CMCETestUIQuestionSingleSelection.h"
#include "CMCETestUIEngineProfile.h"


// -----------------------------------------------------------------------------
// TMCETestUIEngineCmdCreateVoIPSession::Caption
// -----------------------------------------------------------------------------
//
TMCETestUIEngineCmdCreateVoIPSession::TMCETestUIEngineCmdCreateVoIPSession(
		            CMCETestUIEngine& aEngine )
    : TMCETestUIEngineCmdBase( aEngine ),
      iProfile( NULL )
    {
    }

// -----------------------------------------------------------------------------
// TMCETestUIEngineCmdCreateVoIPSession::TMCETestUIEngineCmdCreateVoIPSession
// -----------------------------------------------------------------------------
//
TMCETestUIEngineCmdCreateVoIPSession::TMCETestUIEngineCmdCreateVoIPSession(
		            CMCETestUIEngine& aEngine,
		            CMCETestUIEngineProfile& aProfile )
    : TMCETestUIEngineCmdBase( aEngine ),
      iProfile( &aProfile )
    {
    }

// -----------------------------------------------------------------------------
// TMCETestUIEngineCmdCreateVoIPSession::ExecuteL
// -----------------------------------------------------------------------------
//
EXPORT_C void TMCETestUIEngineCmdCreateVoIPSession::ExecuteL()
	{
	TSessionType sessionType = EVoIPSession;	
	        
	TDirection direction = ENotSpesified;

	TVideoDirection videoDirection = EVideoNotSpesified;

   // Solve used profile
    CMCETestUIEngineProfile* usedProfile = iProfile;
    
    if ( !usedProfile )
        {
        const RPointerArray<CMCETestUIEngineProfile>& profiles = 
                        iEngine.UsedProfiles();

        RPointerArray<CMCETestUIEngineProfile> registeredProfiles;
        CleanupClosePushL( registeredProfiles );    
        for ( TInt i = 0; i < profiles.Count(); ++i )
            {
            if ( profiles[i]->IsRegistered() )
                {
                registeredProfiles.AppendL( profiles[i] );
                }
            }

        if ( registeredProfiles.Count() == 1 )
            {
            usedProfile = registeredProfiles[ 0 ];
            }
        else
            {         
        	CMCETestUIQuestionSingleSelection* profileQuestion = 
    	            CMCETestUIQuestionSingleSelection::NewLC();        
    	    profileQuestion->SetCaptionL( KUserQuestionSelectUsedProfile );   
            
     
            
            for ( TInt i = 0; i < registeredProfiles.Count(); ++i )
                {      
                const TDesC8& providerName = registeredProfiles[i]->ProviderName();    
                HBufC* providerName16 = HBufC16::NewLC( providerName.Length() );
                TPtr providerNamePtr = providerName16->Des();
                providerNamePtr.Copy( providerName );
                
                profileQuestion->AddChoiceL( *providerName16 );
                
                CleanupStack::PopAndDestroy( providerName16 );
                providerName16 = NULL;  
                }
            
            TInt index = iEngine.AskQuestionL( *profileQuestion );
                
            CleanupStack::PopAndDestroy( profileQuestion ); 
            
            if ( index >= 0 && index < registeredProfiles.Count() )
                {
                usedProfile = registeredProfiles[ index ];
                }
                
            }
        CleanupStack::PopAndDestroy(); // registeredProfiles
        }
    
    if ( usedProfile )
        {
	    iEngine.CreateOutSessionL( *usedProfile, direction ,videoDirection,sessionType);
        }
    else
        {
        iEngine.NotifyUser( KUserNotificationSessionCannotCreate );
        }
	}

// -----------------------------------------------------------------------------
// TMCETestUIEngineCmdCreateVoIPSession::Caption
// -----------------------------------------------------------------------------
//
EXPORT_C const TDesC& TMCETestUIEngineCmdCreateVoIPSession::Caption() const
	{
	return KCommandCaptionCreateVoIPSession;
	}




// End of File
