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


#ifndef __MCECOMMONTESTHELPER_H__
#define __MCECOMMONTESTHELPER_H__

//  EXTERNAL INCLUDES
#include <e32base.h>
#include <e32const.h>

//  INTERNAL INCLUDES
#include "mcesrv.h"
#include "mcemediaobserver.h"
#include "mceevents.h"
#include "mcesdpsession.h"
#include "mcecomsession.h"

const TMceMediaEventCode KMMTestNoValue( (TMceMediaEventCode) KMaxTInt16 );

#define MCE_PRINT_HEXDUMP( string )\
    {\
	TBuf<256> str;\
    for( TInt i = 0; i < string.Length(); i++ )\
        {\
        const TUint8 chara = string[ i ];\
		str.Append( '\\');\
		str.Append( 'x');\
		str.AppendNum( chara, EHex );\
        }\
	RDebug::Print(str);\
    }


class CMceServerStub : public CBase, 
                       public MMceMediaSessionObserver, 
                       public MMceMediaGeneralObserver
                            
    {
    
public:


    inline CMceServerStub()
        {
        Reset();
        }
    
    inline void Reset()
        {
        iEvent = KMMTestNoValue;
        iSession = NULL;
        iStream = NULL;
        iSink = NULL;
        iSource = NULL;
        iError = KMMTestNoValue;
        iItcEvent = EMceItcNotAssigned;
        iItcData = KMceNotAssigned;
        iItcDataDesC = NULL;
        }
    
    inline void Updated( CMceComSession& aSession )
        {
        iEvent = EMceMediaUpdated;
    	iSession = &aSession;
        }

    inline void Reserved( CMceComSession& aSession )
        {
        iEvent = EMceMediaReserved;
    	iSession = &aSession;
        }
    inline void SessionClosed( CMceComSession& aSession )
    	{
        iEvent = EMceMediaSessionStopped;
    	iSession = &aSession;
    	}
    	
    inline void EventReceived( TMceMccComEvent& aEvent )
    	{
        iEvent = EMceMediaEventReceived;
        iStream = aEvent.iStream;
        iSink = aEvent.iSink;
        iSource = aEvent.iSource;
        iItcEvent = aEvent.iItcEvent;
        iItcData = aEvent.iItcData;
        iItcDataDesC = aEvent.iItcDataDesC;
    	}
    	
    inline void MediaError( TMceMccComEvent& aEvent )
    	{
        iEvent = EMceMediaError;
    	iError = aEvent.iError;
        iStream = aEvent.iStream;
        iSink = aEvent.iSink;
        iSource = aEvent.iSource;
        iItcEvent = aEvent.iItcEvent;
        iItcData = aEvent.iItcData;
        iItcDataDesC = aEvent.iItcDataDesC;
    	}
    inline void MediaError( TInt aError )
    	{
        iEvent = EMceMediaError;
    	iError = aError;
    	iSession = NULL;
    	}
    inline void SessionCreatedL ( CMceComSession* aSession )
        {
        iEvent = (TMceMediaEventCode)KMceEventCodeNotAssigned;
        if ( &iStockedSession->SdpSession() )
            {
            iStockedSession->SdpSession().AttachContext( NULL );
            CMceComSession::Delete( iStockedSession, iStockedSession->SdpSession().Manager() );
            }
        else                
            {
            delete iStockedSession;
            }
        iStockedSession = aSession;
        }
    	
    	
public:

    TMceMediaEventCode iEvent;
    CMceComSession* iSession;
    CMceComMediaStream* iStream;
    CMceComEndpoint* iSink;
    CMceComEndpoint* iSource;
    CMceComRtpSource* iRtpSource;
    TInt iError;
    TMceItcCallBack iItcEvent;
    TUint32 iItcData;
    const TDesC8* iItcDataDesC;
    CMceComSession* iStockedSession;
    
    
    };

#endif //__MCECOMMONTESTHELPER_H__