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

$allocFailureType = "3";
$cppunitExe = "/epoc32/release/winscw/UDEB/cppunit.exe";
$cppunitParams = "0 FILE txt C:\\CppUnitResults noleakpanic noprompt";
$cppunitResults = "/epoc32/winscw/c/CppUnitResults.txt";
$cppunitDlls = "cppunitdlls.txt";
$newErrorsFile = "results/CppUnitErrors.txt";
$newResultsFile = "results/CppUnitResults.txt";
$cppunitLog = "/epoc32/winscw/c/CppUnitLog.txt";

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

# open file including cppunittestdlls path and names
open(CPPUNITDLLS, $cppunitDlls) or die "cppunitdlls.txt not found!\n";
@dllsFileContent = <CPPUNITDLLS>;

my $previousPathLine = "";
for ($j = 0; $j <= $#dllsFileContent; $j++)
{  
    my $currentPathLine = @dllsFileContent[$j];
    # remove \n from path
    for ($currentPathLine) {
        s/\n+$//;
    }
    
    $j++;
    
    my $currentDllLine = @dllsFileContent[$j];
    # remove \n from currentdll
    for ($currentDllLine) {
        s/\n+$//;
    }
    
    print "DLL path: $currentPathLine\n";
    print "DLL name: $currentDllLine\n";

    chdir($projectrootname);
    chdir($currentPathLine);
    
    $temp = cwd;
    print "current directory is $temp\n";
    
		# clean possibly old coverage build but take in account that directory can contain other
		# tests also, those are not allowed to be cleaned! 
		# it would be most easy if dlls would match with mmp file name but this is not true everywhere
		$prevLen = length($previousPathLine);
		if (($currentPathLine =~ /$previousPathLine/) && ($prevLen > 0))
		{
			print "previous dll was from same path - don't clean again!\n";
		}
		else
		{
			print "previous dll was not from same path - clean all!\n";
			system("bldmake bldfiles");
    	system("abld reallyclean winscw udeb ");
		}
  	
  	# store current pathline for previous loop increment
    $previousPathLine = $currentPathLine;
}

close (CPPUNITDLLS);

