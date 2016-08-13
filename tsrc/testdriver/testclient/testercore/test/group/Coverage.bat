@rem
@rem Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
@rem All rights reserved.
@rem This component and the accompanying materials are made available
@rem under the terms of "Eclipse Public License v1.0"
@rem which accompanies this distribution, and is available
@rem at the URL "http://www.eclipse.org/legal/epl-v10.html".
@rem
@rem Initial Contributors:
@rem Nokia Corporation - initial contribution.
@rem
@rem Contributors:
@rem
@rem Description:
@rem

set my_wins_udeb=%EPOCROOT%epoc32\release\wins\udeb\
set my_output_file=Coverage.txt
set my_uncovered=UnCovered.txt
set my_dll=TesterCore

prep /EXCALL /INC CTcArray.cpp(0-0) /INC CTcCTRLCodec.cpp(0-0) /INC CTcParameterList.cpp(0-0) /INC CTcRegistry.cpp(0-0) /INC CTcStructure.cpp(0-0) /INC TTcIdentifier.cpp(0-0) /INC CTcTypeValue.cpp(0-0) /LV %my_wins_udeb%%my_dll%.dll

profile /i %my_wins_udeb%%my_dll% /o %my_wins_udeb%%my_dll% %my_wins_udeb%cppunit.exe

prep /M %my_wins_udeb%%my_dll%

plist %my_wins_udeb%%my_dll% > %my_output_file%

c:\cygwin\bin\grep -h -e ":    \.\|\.cpp" %my_output_file% | c:\cygwin\bin\grep -vh "inline" > %my_uncovered%
