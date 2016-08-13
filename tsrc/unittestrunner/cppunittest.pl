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
$buildResults = "multimediacommsengine/internal/test/results/BuildResults.txt";
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

# check whether command line parameter allocFailureType was passed and is sane
$tempAllocFailureType = @ARGV[2];
if ($tempAllocFailureType > 0 && $tempAllocFailureType <= 3)
{
		# set failure rate
		$allocFailureType = $tempAllocFailureType;
} 
print "Failure type is: $allocFailureType\n";

# count total number of test cases
$totalcount = 0;

sub findtestcases()
{
    my $testcasecount = 0;
    my $testcase = "TestCase";
    my $rate = "rate";
    my $rateone = "rate:1\n";
	
    for ($i = 0; $i < @_; $i++)
    {   		
    		if ($_[$i] =~ /$testcase/)
        {
		    		# if line contains "rate", alloc failure has been ON and therefore only
		    		# line with "rate:1" is counted
		    		if ($_[$i] =~ /$rate/)
		    		{
			    			if ($_[$i] =~ /$rateone/)
			    			{
			            	$testcasecount++;
			          }
		    		}
	    			else
	    			{
	    			 		$testcasecount++;
	    			}
    		}
        
    }  
    $line = "Testcases count: $testcasecount\n" ;  
    $totalcount += $testcasecount;
    return  $line;
}

sub findErrors()
{
    my @errorLines;
    my $errors =  " There were ";
    for ($i = 0; $i < @_; $i++)
    {
        if ($_[$i] =~ /^$errors/ )
        {
            push @errorLines, $_[$i];
            last;
        }
    }  
    substr(@errorLines[0], 0, 0) = "   ";
    return  @errorLines;
}

$startdir = cwd;
unlink $cppunitResults;

# open file including cppunittestdlls path and names
open(CPPUNITDLLS, $cppunitDlls) or die "cppunitdlls.txt not found!\n";
@dllsFileContent = <CPPUNITDLLS>;

# open CppUnitErrors.txt file
open(NEWERRORSFILE, "> $newErrorsFile") or die "Cannot open error file\n";

# open CppUnitResults.txt file
open(NEWRESULTSFILE, "> $newResultsFile") or die "Cannot open results file\n";

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
			print "previous dll was from same path - don't build again!\n";
		}
		else
		{
			print "previous dll was not from same path - build all!\n";
			system("bldmake bldfiles");
    	system("abld reallyclean winscw udeb ");
    	system("abld build winscw udeb >> $projectdrive$projectrootname$buildResults");
		}
    
   	# run unit tests
   	print("Running: $cppunitExe $currentDllLine $allocFailureType $cppunitParams");
   	system("$cppunitExe $currentDllLine $allocFailureType $cppunitParams");
  	
  	# store current pathline for previous loop increment
    $previousPathLine = $currentPathLine;
    
    # open CppUnitLog.txt for counting testcases
    # print first currently tested dll's name
    print NEWRESULTSFILE "$currentDllLine\E:\n";
    open(CPPUNITLOG, "< $cppunitLog");
    my @cppunitlog = <CPPUNITLOG>;
    my $testcases = &findtestcases(@cppunitlog);
    print NEWRESULTSFILE $testcases;
    close (CPPUNITLOG);
    # remove cppunit log so that total test case count is not errorenous if next tests fail
    unlink $cppunitLog;
    
    # if errors during test executing CppUnitResults.txt has been created
    open (CPPUNITRESULTS, "< $cppunitResults");
    if (-e CPPUNITRESULTS){
        print "Errors found!\n";
        @cppunitresults = <CPPUNITRESULTS>;
        my @cppuniterrors = &findErrors(@cppunitresults);
        print NEWRESULTSFILE @cppuniterrors ;
        # print testdllname to CppunitErrors.txt
        print NEWERRORSFILE "$currentDllLine\E:\n";
        my $line = "-";
        $line x=80;
        $line .="\n";
        print NEWERRORSFILE "$line";
        # print CppUnitResults.txt to CppunitErrors.txt
        print NEWERRORSFILE "@cppunitresults";
		
        close (CPPUNITRESULTS) or die "Cannot close /epoc32/winscw/c/CppUnitResults.txt\n";
        unlink $cppunitResults;
    }
    print NEWRESULTSFILE "\n";
}

#print total test case count
print NEWRESULTSFILE "Total count: $totalcount\n\n";

close (CPPUNITDLLS);
close (NEWRESULTSFILE);
close (NEWERRORSFILE);

