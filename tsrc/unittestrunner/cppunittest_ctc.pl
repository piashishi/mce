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
use Getopt::Long;

#---------------------------------------Initialization------------------------------------------------------#

$coverageResultsDir = "ipappsrv/multimediacommsengine/tsrc/unittestrunner/results/";

$cppunitExe = "/epoc32/release/winscw/UDEB/cppunit.exe";
$cppunitParams = "0 FILE txt C:\\CppUnitResults noleakpanic noprompt";
$cppunitResults = "/epoc32/winscw/c/CppUnitResults.txt";
$buildResults = "BuildResults.txt";
$cppunitDllsDefault = "cppunitdlls_ctc.txt";
$newErrorsFile = "CppUnitErrors.txt";
$newResultsFile = "CppUnitResults.txt";
$cppunitLog = "/epoc32/winscw/c/CppUnitLog.txt";

$ignoredFileName = "ignored_ctc.txt";
$ignoredmodeSourceRelative = "1";

$coverageSymbols = "MON.sym";
$ctcCommandPart1 = "ctcwrap -i d -n";
$ctcCommandPart2 = "abld build winscw udeb";
$ctcCommandPart2Test = "abld test build winscw udeb";
$ctcIgnoredPart1 = " -C \"EXCLUDE+";
$ctcIgnoredPart2 = "\" ";

# from command line
my ($param_noclean,
	  $projectrootname,
	  $projectdrive,
	  $cppunitDlls,
		$allocFailure);

#---------------------------------------Main Start----------------------------------------------------------#

# read command line parameters
my $result = GetOptions("noclean" 			 => \$param_noclean,
												"drive=s"			   => \$projectdrive,						
												"root=s" 			   => \$projectrootname,
												"cppunitdlls:s"	 => \$cppunitDlls,
												"allocfailure:i" => \$allocFailure);

if (!defined $projectdrive)
{
	die("Project drive not defined!\n");
}

if (!defined $projectrootname)
{
	die("Project root not defined!\n");
}

if (!defined $cppunitDlls || length($cppunitDlls) == 0 )
{
	print("Project dlls not defined, using defaults!\n");
	$cppunitDlls = $cppunitDllsDefault;
}

if (defined $allocFailure && $allocFailure > 0 && $allocFailure <=3 )
{
	print("Alloc failure mode defined!\n");
}
else
{
	$allocFailure = "3";
}
print("Allocfailure type is: $allocFailure\n");

# count total number of test cases
$totalcount = 0;

$startdir = cwd;

# clean previous results
unlink($cppunitResults);
unlink("projectdrive$projectrootname$coverageResultsDir$newErrorsFile");
unlink("projectdrive$projectrootname$coverageResultsDir$newResultsFile");

# open file including cppunittestdlls path and names
open(CPPUNITDLLS, $cppunitDlls) or die "cppunitdlls.txt not found!\n";
@dllsFileContent = <CPPUNITDLLS>;

# open CppUnitErrors.txt file
open(NEWERRORSFILE, "> $projectdrive$projectrootname$coverageResultsDir$newErrorsFile") or die "Cannot open error file\n";

# open CppUnitResults.txt file
open(NEWRESULTSFILE, "> $projectdrive$projectrootname$coverageResultsDir$newResultsFile") or die "Cannot open results file\n";

# open file containing files exluded from measurements
open(IGNOREDFILE, $ignoredFileName) or die("file $ignoredFileName not found!\n");

$excludedCmd = parseExcluded();

#build and run
doBuild();

#print total test case count
print NEWRESULTSFILE "Total count: $totalcount\n\n";

#clean
doBuild( "clean" );

close (CPPUNITDLLS);
close (NEWRESULTSFILE);
close (NEWERRORSFILE);
close (IGNOREDFILE);

#---------------------------------------Main Ends-------------------------------------------------------------#

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

sub parseExcluded()
{
	#exclude headers and test sources from measurements 
	@ignoredFileContent = <IGNOREDFILE>;
	$ignoredText = "";
	for ($j = 0; $j <= $#ignoredFileContent; $j++)
	{
		  my $currentIgnoredMode = @ignoredFileContent[$j];
	    # remove \n from path
	    for ($currentIgnoredMode) {
	        s/\n+$//;
	    }
	    
	    $j++;
	    
	    my $currentIgnoredLine = @ignoredFileContent[$j];
	    # remove \n from dll name
	    for ($currentIgnoredLine) {
	        s/\n+$//;
	    }
	    
	    #print("ignore mode: $currentIgnoredMode\n");
	    #print("ignore txt: $currentIgnoredLine\n");
	    
	    if ($currentIgnoredMode =~ /$ignoredmodeSourceRelative/)
			{
				$ignoredText .= "$ctcIgnoredPart1$projectdrive$projectrootname$currentIgnoredLine$ctcIgnoredPart2";
	    }
	    else
	    {
	    	$ignoredText .= "$ctcIgnoredPart1$projectdrive$currentIgnoredLine$ctcIgnoredPart2";
	    }
	}
	return $ignoredText;
}

sub doBuild()
{
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
	    
	    print("DLL path: $currentPathLine\n");
	    print("DLL name: $currentDllLine\n");
	
	    chdir($projectrootname);
	    chdir($currentPathLine);
	    
	    $temp = cwd;
	    print("current directory is $temp\n");
	    
	    if ( defined $_[0] )
	    {
	    	# do just cleaning
	    	if (!defined $param_noclean)
	    	{
	    		doSystemCall("abld test reallyclean winscw udeb ");
	    	}
	    	else
	    	{
	    		print("no_cleanup param defined!\n");
	    	}
	    }
	    else
	    {
				# clean possibly old coverage build but take in account that directory can contain other
				# tests also, those are not allowed to be cleaned! 
				# it would be most easy if dlls would match with mmp file name but this is not true everywhere
				$prevLen = length($previousPathLine);
				if (($currentPathLine =~ /$previousPathLine/) && ($prevLen > 0))
				{
					print("previous dll was from same path - don't build again!\n");
				}
				else
				{
					print("previous dll was not from same path - build all!\n");
					doSystemCall("bldmake bldfiles");
		    	doSystemCall("abld test reallyclean winscw udeb ");
		    	doSystemCall("$ctcCommandPart1 $projectdrive$projectrootname$coverageResultsDir$coverageSymbols $excludedCmd $ctcCommandPart2Test");
				}
		    
		   	# run unit tests
		   	doSystemCall("$cppunitExe $currentDllLine $allocFailure $cppunitParams");
		  	
		  	# store current pathline for previous loop increment
		    $previousPathLine = $currentPathLine;
		    
		    # open CppUnitLog.txt for counting testcases
		    # print first currently tested dll's name
		    print NEWRESULTSFILE "$currentDllLine\E:\n";
		    open(CPPUNITLOG, "< $cppunitLog");
		    my @cppunitlog = <CPPUNITLOG>;
		    my $testcases = &findtestcases(@cppunitlog);
		    print NEWRESULTSFILE $testcases;
		    close(CPPUNITLOG);
		    # remove cppunit log so that total test case count is not errorenous if next tests fail
		    unlink($cppunitLog);
		    
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
		        unlink($cppunitResults);
		    }
		    print NEWRESULTSFILE "\n";
		  }
	}
}

sub doSystemCall
{
	system("echo Doing system call: $_[0] >> $projectdrive$projectrootname$coverageResultsDir$buildResults");
	system("$_[0] >> $projectdrive$projectrootname$coverageResultsDir$buildResults 2>&1");
}
