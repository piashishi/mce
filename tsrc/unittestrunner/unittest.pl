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

$eunitUnitTestRunner = "eunittest.pl";
$cppunitUnitTestRunner = "cppunittest.pl";
$scriptLocation = "multimediacommsengine/internal/test";
$newCoverageFile = "multimediacommsengine/internal/test/results/CoverageAll.cov";
$newCoverageFileTxt = "results/CoverageAll.txt";
$buildResults = "multimediacommsengine/internal/test/results/BuildResults.txt";
$coverageOutput = "c:/users/test.cov";
$coverageOutputTemp = "c:/users/bullseyecovtesttemp.txt";
$ignored = "ignored.txt";
$ignoredmodeSourceRelative = "1";

sub findCoverageOutput()
{
		# no parsing at the moment
    my @output;
    for ($i = 0; $i < @_; $i++)
    {
   			push @output, $_[$i];
    }  
    return  @output;
}

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

#create directory for results
if (mkdir ("results", 0777))
{
    print "The results directory was created successfully! \n";
} 
else 
{
    print "The results directory already exists. \n";
} 

# remove old coverage file!!
unlink $coverageOutput;

# remove old build log
unlink ("$projectdrive$projectrootname$buildResults");

# find project root
findProjectDriveAndRoot();

# open CoverageAll.txt file
open(NEWCOVERAGEFILE, "> $newCoverageFileTxt") or die "Cannot open Coverage output txt file\n";

# open ignored.txt file
open(IGNOREDFILE, $ignored) or die "Cannot open ignored txt file\n";

# set Bullseye coverage build on
system("cov01 -1");

# clear coverage file
system("covclear --file $coverageOutput");

# remove all old coverage measurement exclusions
system("covselect --deleteAll");

# run eunit tests
system("$eunitUnitTestRunner $projectdrive $projectrootname @ARGV");
chdir($startdir);

#run cppunit tests
system("$cppunitUnitTestRunner $projectdrive $projectrootname @ARGV");
chdir($startdir);

# exclude stuff from coverage measurements
system("covselect --add !$projectdrive\E/epoc32/INCLUDE/");

#exclude headers and test sources from measurements 
@ignoredFileContent = <IGNOREDFILE>;
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
    
    print "ignore mode: $currentIgnoredMode\n";
    print "ignore txt: $currentIgnoredLine\n";
    
    if ($currentIgnoredMode =~ /$ignoredmodeSourceRelative/)
		{
			system("covselect --add !$projectdrive$projectrootname$currentIgnoredLine");
    }
    else
    {
    	system("covselect --add !$projectdrive$currentIgnoredLine");
    }
}

# store coverage file
copy($coverageOutput, "$projectdrive$projectrootname$newCoverageFile");

# create textual file out from coverage results
system("covdir --by-name -f $coverageOutput --decision  > $coverageOutputTemp");
    
open(COVERAGEOUTPUT, "< $coverageOutputTemp") or die "Cannot open Coverage output file\n";
my @coverageoutput = <COVERAGEOUTPUT>;
    
my @currentCoverageOutput = &findCoverageOutput(@coverageoutput);

# print parsed data to CoverageAll.txt
print NEWCOVERAGEFILE @currentCoverageOutput;
close (COVERAGEOUTPUT);

# set Bullseye coverage build off
system("cov01 -0");

close (NEWCOVERAGEFILE);
close (IGNOREDFILE);

