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
* Description:    
*
*/





#ifndef MCESTUBS_H
#define MCESTUBS_H

#include <e32base.h>
#include <s32mem.h>

#include <sipprofileregistryobserver.h>
#include <sipmanagedprofile.h>
#include <sipprofile.h>

#include "mcetransactiondatacontainer.h"
#include "mceinsession.h"
#include "mceinevent.h"
#include "mceoutevent.h"
#include "mceinrefer.h"
#include "mceclientserver.h"
#include "mceinsessionobserver.h"
#include "mcetransactionobserver.h"
#include "mceintransactionobserver.h"
#include "mceineventobserver.h"
#include "mceeventobserver.h"
#include "mcesessionobserver.h"
#include "mcestreamobserver.h"
#include "mcertpobserver.h"
#include "mcefcmsgobserver.h"
#include "mceinreferobserver.h"
#include "mcereferobserver.h"
#include "mcetestdefs.h"

#define MCE_OBS_CLEAR\
        delete iHeaders;\
        iHeaders = 0;\
        delete iContentType;\
        iContentType = 0;\
        delete iBody;\
        iBody = 0;\


#define MCE_SES_OBS_CLEAR\
        MCE_OBS_CLEAR;\
        delete iReasonPhrase;\
        iReasonPhrase = 0;\
        iError = 0;\
        iStatusCode = 0;
        
#define MCE_MAN_OBS_CLEAR\
        MCE_OBS_CLEAR;\
        delete iContentHeaders;\
        iContentHeaders = 0;
        
class CSIPProfileRegistryObserverStub : public CBase, 
										public MSIPProfileRegistryObserver
    {
public:

    inline CSIPProfileRegistryObserverStub()
        {
        // NOP
        }
        
    inline ~CSIPProfileRegistryObserverStub()
        {
        // NOP
        }
        
   	inline void ProfileRegistryEventOccurred(TUint32 /*aProfileId*/, TEvent /*aEvent*/)
   		{
   		// NOP
   		};    
   	 
   	inline void ProfileRegistryErrorOccurred(TUint32 /*aProfileId*/, TInt /*aError*/)
   		{
		// NOP
   		}
    };

class CMceManagerObserverStub : public CBase, public MMceInSessionObserver
    {
public:

    inline CMceManagerObserverStub()
        {
        }
        
    inline ~CMceManagerObserverStub()
        {
        MCE_MAN_OBS_CLEAR;
        }

    inline void IncomingSession(
                    CMceInSession* aSession,
                    TMceTransactionDataContainer* aContainer )
        {
        MCE_MAN_OBS_CLEAR;
        iSession = aSession;
        if (aContainer)
	        {        	
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        iContentHeaders = aContainer->GetContentHeaders();
	        }
        }
      
    inline void IncomingUpdate(
					CMceSession& /*aOrigSession*/, 
					CMceInSession* aUpdatedSession,
    				TMceTransactionDataContainer* aContainer )
        {
        MCE_MAN_OBS_CLEAR;
        iSession = aUpdatedSession;
        if (aContainer)
	        {        	
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        iContentHeaders = aContainer->GetContentHeaders();
	        }
        
        }

public:      
       
        CMceInSession* iSession;
        CDesC8Array* iHeaders;
        HBufC8* iContentType;
        HBufC8* iBody;
        CDesC8Array* iContentHeaders;
                
    };


class CMceSessionObserverStub : public CBase, public MMceSessionObserver
    {
public:

    inline CMceSessionObserverStub()
       : iStateChangedCount( 0 )
        {
        }
        
    inline ~CMceSessionObserverStub()
        {
        MCE_SES_OBS_CLEAR;
        }

    inline void SessionStateChanged(
        CMceSession& aSession,
        TMceTransactionDataContainer* aContainer )
        {
        MCE_SES_OBS_CLEAR;
        iSession = &aSession;
        if ( aContainer )
	        {	
	        iStatusCode = aContainer->GetStatusCode();
	        iReasonPhrase = aContainer->GetReasonPhrase();
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        }
        iStateChangedCount++;
        DeleteSessionIfNeeded();
        }

    inline void SessionConnectionStateChanged(
        CMceSession& aSession,
        TBool aActive )
        {
        iSession = &aSession;
        iActive = aActive;
        DeleteSessionIfNeeded();       
        }

    inline void UpdateFailed(
        CMceSession& aSession,
        TMceTransactionDataContainer* aContainer )
        {
        MCE_SES_OBS_CLEAR;
        iSession = &aSession;
        if ( aContainer )
	        {	
	        iStatusCode = aContainer->GetStatusCode();
	        iReasonPhrase = aContainer->GetReasonPhrase();
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        }
        DeleteSessionIfNeeded();
        }
        
    inline void Failed( 
        CMceSession& aSession, 
        TInt aError )
        {
        iSession = &aSession;
        iError = aError;
        DeleteSessionIfNeeded();       
        }
        
    inline void Clear()
        {
        MCE_SES_OBS_CLEAR;
        }
    
public:

    CMceSession* iSession;
    CDesC8Array* iHeaders;
    HBufC8* iReasonPhrase;
    HBufC8* iContentType;
    HBufC8* iBody;
    TInt iStatusCode;
    TBool iActive;
    TInt iError;
    TInt iStateChangedCount;
    TBool iDeleteSessionWithinCallback;
    
private:

    inline void DeleteSessionIfNeeded()
        {
        if ( iDeleteSessionWithinCallback )
            {
            delete iSession;
            iSession = NULL;
            }
        }
    };


class CMceEventObserverStub : public CBase, public MMceEventObserver
    {
public:

    inline CMceEventObserverStub()
       : iStateChangedCount( 0 )
        {
        }
        
    inline ~CMceEventObserverStub()
        {
        MCE_SES_OBS_CLEAR;
        delete iEventOwnedByObserver;
        }

    inline void EventStateChanged(
                CMceEvent& aEvent,
                TMceTransactionDataContainer* aContainer )
        {
        MCE_SES_OBS_CLEAR;
        iEvent = &aEvent;
        if (aContainer)
	        {	
	        iStatusCode = aContainer->GetStatusCode();
	        iReasonPhrase = aContainer->GetReasonPhrase();
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        }
        iStateChangedCount++;        
        }

	inline void NotifyReceived(
					CMceEvent& aEvent,
    				TMceTransactionDataContainer* aContainer )
		{
        MCE_SES_OBS_CLEAR;
        iEvent = &aEvent;
        if (aContainer)
	        {	
	        iStatusCode = aContainer->GetStatusCode();
	        iReasonPhrase = aContainer->GetReasonPhrase();
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        }
		}


    inline void EventConnectionStateChanged(
                    CMceEvent& aEvent,
                    TBool aActive )
        {
        iEvent = &aEvent;
        iActive = aActive;        
        }

    inline void Failed( CMceEvent& aEvent, TInt aError )
        {
        TBool isInEvent = aEvent.IsInEvent();
        
        if ( !isInEvent && 
             aError == KErrTotalLossOfPrecision &&
             &aEvent == iEventOwnedByObserver )
            {
            // Failed event is owned by us, so let's delete it now.
            // MCE API does not deny this and the situation must be tested.
            delete iEventOwnedByObserver;
            iEventOwnedByObserver = NULL;
            }
        iEvent = &aEvent;
        iError = aError;
        }

public:

    CMceEvent* iEvent;
    CDesC8Array* iHeaders;
    HBufC8* iReasonPhrase;
    HBufC8* iContentType;
    HBufC8* iBody;
    TUint32 iStatusCode;
    TBool iActive;
    TInt iError;
    TInt iStateChangedCount;
    // This variable is meant to simulate a common situation where owner of
    // CMceEvent is same as implementor MMceEventObserver. In such a situation
    // owner might delete CMceEvent immediately when it observes a failure.
    CMceOutEvent* iEventOwnedByObserver;
    };

class CMceReferObserverStub : public CBase, public MMceReferObserver
    {
public:

    inline CMceReferObserverStub()
       : iStateChangedCount( 0 )
        {
        }
        
    inline ~CMceReferObserverStub()
        {
        MCE_SES_OBS_CLEAR;
        }

    inline void ReferStateChanged(
                CMceRefer& aRefer,
                TMceTransactionDataContainer* aContainer )
        {
        MCE_SES_OBS_CLEAR;
        iRefer = &aRefer;
        if (aContainer)
	        {	
	        iStatusCode = aContainer->GetStatusCode();
	        iReasonPhrase = aContainer->GetReasonPhrase();
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        }
        iStateChangedCount++;        
        }


    inline void ReferConnectionStateChanged(
                    CMceRefer& aRefer,
                    TBool aActive )
        {
        iRefer = &aRefer;
        iActive = aActive;        
        }

    inline void Failed( CMceRefer& aRefer, TInt aError )
        {
        iRefer = &aRefer;
        iError = aError;
        }

public:

    CMceRefer* iRefer;
    CDesC8Array* iHeaders;
    HBufC8* iReasonPhrase;
    HBufC8* iContentType;
    HBufC8* iBody;
    TUint32 iStatusCode;
    TBool iActive;
    TInt iError;
    TInt iStateChangedCount;
    };



class CMceInEventObserverStub : public CBase, public MMceInEventObserver
    {
public:

    inline CMceInEventObserverStub()
        {
        }
        
    inline ~CMceInEventObserverStub()
        {
        MCE_SES_OBS_CLEAR;
        }

    inline void IncomingEvent(
                CMceInEvent* aEvent,
                TMceTransactionDataContainer* aContainer )
        {
        MCE_SES_OBS_CLEAR;
        iEvent = aEvent;
        if (aContainer)
	        {	
	        iStatusCode = aContainer->GetStatusCode();
	        iReasonPhrase = aContainer->GetReasonPhrase();
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        }
        }

    
public:

    CMceEvent* iEvent;
    CDesC8Array* iHeaders;
    HBufC8* iReasonPhrase;
    HBufC8* iContentType;
    HBufC8* iBody;
    TUint32 iStatusCode;
    TBool iActive;
    TInt iError;        
    };

class CMceInReferObserverStub : public CBase, public MMceInReferObserver
    {
public:

    inline CMceInReferObserverStub()
        {
        }
        
    inline ~CMceInReferObserverStub()
        {
        MCE_SES_OBS_CLEAR;
        }

	inline void IncomingRefer(
		CMceInRefer* aRefer,
		const TDesC8& /*aReferTo*/,
    	TMceTransactionDataContainer* aContainer )
        {
        MCE_SES_OBS_CLEAR;
        iRefer = aRefer;
        if (aContainer)
	        {	
	        iStatusCode = aContainer->GetStatusCode();
	        iReasonPhrase = aContainer->GetReasonPhrase();
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        }
        }


public:

    CMceRefer* iRefer;
    CDesC8Array* iHeaders;
    HBufC8* iReasonPhrase;
    HBufC8* iContentType;
    HBufC8* iBody;
    TUint32 iStatusCode;
    TBool iActive;
    TInt iError;        
    };

class CMceStreamObserverStub : public CBase, public MMceStreamObserver
    {
public:

    inline CMceStreamObserverStub()
       : iStateChangedCount( 0 )
        {
        }
        
    inline ~CMceStreamObserverStub()
        {
        }


    inline void StreamStateChanged( 
               CMceMediaStream& aStream)
        {
        iStream = NULL;
        iSink = NULL;
        iSource = NULL;
        iStream = &aStream;
        iStateChangedCount++;
        }

    inline void StreamStateChanged(
                    CMceMediaStream& aStream,
                    CMceMediaSink& aSink)
        {
        iStream = NULL;
        iSink = NULL;
        iSource = NULL;
        iStream = &aStream;
        iSink = &aSink;
        iStateChangedCount++;
        }

    inline void StreamStateChanged(
                    CMceMediaStream& aStream,
                    CMceMediaSource& aSource)
        {
        iStream = NULL;
        iSink = NULL;
        iSource = NULL;
        iStream = &aStream;
        iSource = &aSource;
        iStateChangedCount++;
        }
        
public:

   CMceMediaStream* iStream;
   CMceMediaSink* iSink;
   CMceMediaSource* iSource;
   TInt iStateChangedCount;
   

    };
    
    
class CMceRtpObserverStub : public CBase, public MMceRtpObserver
    {
public:

    inline CMceRtpObserverStub()
        {
        }
        
    inline ~CMceRtpObserverStub()
        {
        }
    
    inline void SRReceived( CMceSession& aSession,
					        CMceMediaStream& aStream )
        {
        iReceived = 1;
        iSession = NULL;
        iStream = NULL;
        iSession = &aSession;
        iStream = &aStream;
        }

    inline void RRReceived( CMceSession& aSession,
					        CMceMediaStream& aStream )
        {
        iReceived = 2;
        iSession = NULL;
        iStream = NULL;
        iSession = &aSession;
        iStream = &aStream;
        }

    inline void InactivityTimeout(
    			CMceMediaStream& aStream,
    			CMceRtpSource& aSource)
        {
        iReceived = 3;
        iStream = NULL;
        iSource = NULL;
        iStream = &aStream;
        iSource = &aSource;
        }
    
	inline void SsrcAdded(
				CMceMediaStream& aStream,
				CMceRtpSource& aSource,
				TUint aSsrc )
	    {
        iReceived = 4;
        iStream = NULL;
        iSource = NULL;
        iStream = &aStream;
        iSource = &aSource;
        iSsrc = aSsrc;
	    }
	    
	inline void SsrcRemoved(
				CMceMediaStream& aStream,
				CMceRtpSource& aSource,
				TUint aSsrc )
	    {
        iReceived = 5;
        iStream = NULL;
        iSource = NULL;
        iStream = &aStream;
        iSource = &aSource;
        iSsrc = aSsrc;
	    }

public:

    CMceSession* iSession;
    CMceMediaStream* iStream;
    CMceRtpSource* iSource;
    TInt iReceived;
    TUint iSsrc;

    };


class CMceFcMsgObserverStub : public CBase, public MMceFcMsgObserver
    {
public:

    inline CMceFcMsgObserverStub()
        {
        }
        
    inline ~CMceFcMsgObserverStub()
        {
        delete iMessage;
        }
    
    inline void FCMsgReceived(
				CMceSession& aSession,
				HBufC8* aMessage )
        {
        delete iMessage;
        iSession = &aSession;
        iMessage = aMessage;
        }

    inline void FCMsgErrorOccurred(
				CMceSession& aSession,
				TInt aError )
        {
        iSession = &aSession;
        iError = aError;
        }
				
				 

public:

    CMceSession* iSession;
    HBufC8* iMessage;
    TInt iError;
   

    };
    

class CMceTransactionObserverStub : public CBase, public MMceTransactionObserver
	{
	
public:	
		
	inline CMceTransactionObserverStub( )
		{
		}
		
	inline 	~CMceTransactionObserverStub( )
		{
		MCE_SES_OBS_CLEAR
		}
	
	
	inline void TransactionResponse( CMceSession& aSession,
	    							TMceTransactionId aTransactionId,
					    			TMceTransactionDataContainer* aContainer )
		{
		MCE_SES_OBS_CLEAR
        iSession = &aSession;
        iTransactionID = aTransactionId;
        if (aContainer)
	        {        	
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        iContentHeaders = aContainer->GetContentHeaders();
	        iStatusCode = aContainer->GetStatusCode();
			iReasonPhrase = aContainer->GetReasonPhrase();
	        }
		}


	inline void TransactionFailed( CMceSession& aSession,
		                             TMceTransactionId aTransactionId, 
		                             TInt aError )

		{
		iSession = &aSession;
		iTransactionID = aTransactionId;
		iError = aError;
		}
		
		
	public:
	
	CMceSession* iSession;
	TMceTransactionId iTransactionID;
	TInt iError;
    
    CDesC8Array* iHeaders;
    HBufC8* iContentType;
    HBufC8* iBody;
    CDesC8Array* iContentHeaders;
    TInt iStatusCode;
    HBufC8* iReasonPhrase;
    };    
	

class CMceInTransactionObserverStub : public CBase, public MMceInTransactionObserver
	{
	
public:	
		
	inline CMceInTransactionObserverStub( )
		{
		}
		
	inline 	~CMceInTransactionObserverStub( )
		{
		MCE_MAN_OBS_CLEAR;	
		}
	
	
	inline void IncomingRequest(const TDesC8& /*aMethod*/,
								CMceSession& aSession,
	    						TMceTransactionId aTransactionId,
	    						TMceTransactionDataContainer* aContainer  )
		{
		MCE_MAN_OBS_CLEAR;
        iSession = &aSession;
        iTransactionID = aTransactionId;
        if (aContainer)
	        {        	
	        iHeaders = aContainer->GetHeaders();
	        iContentType = aContainer->GetContentType();
	        iBody = aContainer->GetContent();
	        iContentHeaders = aContainer->GetContentHeaders();
	        }
		}
		
	public:
	
	CMceSession* iSession;
	TMceTransactionId iTransactionID;
    CDesC8Array* iContentHeaders;
    CDesC8Array* iHeaders;
    HBufC8* iContentType;
    HBufC8* iBody;
	};    	

#endif // MCESTUBS_H

// End of File
