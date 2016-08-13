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

$eunitExe = "/epoc32/release/winscw/udeb/EUnitExeRunner.exe";
$eunitParams = "/l xml";
$eunitResults = "multimediacommsengine/internal/test/results/EUnitLog.xml";
$eunitDlls = "eunitdlls.txt";
$eunitSrcDllLocation = "/epoc32/release/winscw/udeb/";
$eunitDstDllLocation = "/epoc32/release/winscw/udeb/z/sys/bin/";
$eunitLog = "/epoc32/winscw/c/DigiaEUnit/Logs/DigiaEUnit_log.xml";
$eunitTestBuildMode = "1";


# check whether command line parameter project drive was passed and is sane
$tempProjectDrive = @ARGV[0];
if ($tempProjectDrive =~ /(\D)(\s*:)/ && length($tempProjectDrive) == 2)
{
		# set project drive
		$projectdrive = $tempProjectDrive;
} 
else
{
		print "Project drive argument in illegal format or not defined, using default value!\n";
}
print "Project drive is: $projectdrive\n";

# check whether command line parameter project root was passed and is sane
$tempProjectRoot = @ARGV[1];
if (length($tempProjectRoot) > 0)
{
		# set project drive
		$projectrootname = $tempProjectRoot;
} 
else
{
		print "Project root argument in illegal format or not defined, using default value!\n";
}
print "Project root is: $projectrootname\n";


$startdir = cwd;
unlink $eunitResults;

# open file including eunit test dlls path and names
open(EUNITDLLS, $eunitDlls) or die "eunitdlls.txt not found!\n";
@dllsFileContent = <EUNITDLLS>;

my $previousPathLine = "";
for ($j = 0; $j <= $#dllsFileContent; $j++)
{  
    my $currentPathLine = @dllsFileContent[$j];
    # remove \n from path
    for ($currentPathLine) {
        s/\n+$//;
    }
    
    $j++;
    
    my $currentDllNameLine = @dllsFileContent[$j];
    # remove \n from dll name
    for ($currentDllNameLine) {
        s/\n+$//;
    }
    
    $j++;
    
    my $currentBuildModeLine = @dllsFileContent[$j];
    # remove \n from build mode
    for ($currentBuildModeLine) {
        s/\n+$//;
    }
    
    $j++;
    
    my $currentExtraCommandsLine = @dllsFileContent[$j];
    # remove \n from extra commands
    for ($currentExtraCommandsLine) {
        s/\n+$//;
    }
    
    print "DLL path: $currentPathLine\n";
    print "DLL name: $currentDllNameLine\n";
    print "DLL build mode: $currentBuildModeLine\n";
    print "DLL extra commands: $currentExtraCommandsLine\n";

    chdir($projectrootname);
    chdir($currentPathLine);
    
    $temp = cwd;
    print "current directory is $temp\n";
    
    #delete old test dll
    unlink("$eunitSrcDllLocation$currentDllNameLine");
    unlink("$eunitDstDllLocation$currentDllNameLine");
    
		# clean possibly old coverage build but take in account that directory can contain other
		# tests also, those are not allowed to be cleaned! 
		# it would be most easy if dlls would match with mmp file name but this is not true everywhere
		$prevLen = length($previousPathLine);
		if (($currentPathLine =~ /$previousPathLine/) && ($prevLen > 0))
		{
			print "previous dll was from same path - don't build again!\n";
		}
		else
		{
			print "previous dll was not from same path - build all!\n";
			system("bldmake bldfiles");
			
			if ($currentBuildModeLine =~ /$eunitTestBuildMode/)
			{
				system("abld test reallyclean winscw udeb ");
    	}
    	else
    	{
    		system("abld reallyclean winscw udeb ");
    	}
		}
		
  	# store current pathline for previous loop increment
    $previousPathLine = $currentPathLine;
}

close (EUNITDLLS);
