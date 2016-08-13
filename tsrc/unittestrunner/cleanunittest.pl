#
# Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
# All rights reserved.
# This component and the accompanying materials are made available
# under the terms of "Eclipse Public License v1.0"
# which accompanies this distribution, and is available
# at the URL "http://www.eclipse.org/legal/epl-v10.html".
#
# Initial Contributors:
# Nokia Corporation - initial contribution.
#
# Contributors:
#
# Description:  
#

use File::Copy;
use Cwd;
$projectrootname = "/MCE3/";
$projectdrive = "z:";

$eunitUnitTestRunner = "cleaneunittest.pl";
$cppunitUnitTestRunner = "cleancppunittest.pl";
$scriptLocation = "multimediacommsengine/internal/test";
$newCoverageFile = "multimediacommsengine/internal/test/results/CoverageAll.cov";
$newCoverageFileTxt = "results/CoverageAll.txt";
$coverageOutput = "c:/users/test.cov";
$coverageOutputTemp = "c:/users/bullseyecovtesttemp.txt";
$ignored = "ignored.txt";
$ignoredmodeSourceRelative = "1";

sub findProjectDriveAndRoot()
{
		$tempStartDir = $startdir;
		if ($tempStartDir =~ m/$scriptLocation/)
		{
			# extract project root
			for ($tempStartDir) {
				 s/$scriptLocation+$//;
    	}
    	# divide it to drive and root
    	if ($tempStartDir =~ /^(.:)(.*)/)
    	{
    		$projectdrive = $1;
    		$projectrootname = $2;
			}
			print "project drive: $projectdrive \n";
			print "project root: $projectrootname \n";
		}
		else
		{
			print "cannot determine project drive and root, use defaults!\n";
		}
}

$startdir = cwd;

# find project root
findProjectDriveAndRoot();

# set Bullseye coverage build on
system("cov01 -1");

# run eunit tests
system("$eunitUnitTestRunner $projectdrive $projectrootname @ARGV");
chdir($startdir);

#run cppunit tests
system("$cppunitUnitTestRunner $projectdrive $projectrootname @ARGV");
chdir($startdir);

# set Bullseye coverage build off
system("cov01 -0");

