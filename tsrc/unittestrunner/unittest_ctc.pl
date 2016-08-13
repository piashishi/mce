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
use XML::Parser::Expat;

#---------------------------------------Initialization------------------------------------------------------#

$projectrootname = "/"; #is set to correct at run-time 
$projectdrive = "z:"; #is set to correct at run-time 

$eunitUnitTestRunner = "eunittest_ctc.pl";
$cppunitUnitTestRunner = "cppunittest_ctc.pl";
$scriptLocation = "ipappsrv/multimediacommsengine/tsrc/unittestrunner";
$coverageResultsDir = "ipappsrv/multimediacommsengine/tsrc/unittestrunner/results/";
$buildResults = "BuildResults.txt";
$coverageDat = "MON.dat";
$coverageSymbols = "MON.sym";
$coverageProfile = "profile.txt";

$eunitResultsFile = "EUnitLog.xml";
$cppunitResultsFile = "CppUnitResults.txt";
$coverageResultsFile = "CTCHTML/index.html";
$finalResultsFile = "AllResults.html";
$cssFile = "CTCHTML/ctc.css";
$cssLink = "<link rel=\"stylesheet\"";

$xmlDllLine = "dll";
$xmlResultLine = "result";
$xmlCaseFailed = "FAIL";
$xmlCasePassed = "OK";
$outputString = "";
$outputFileBodyStart = "<body";
$cppunitTestFailuresLine = "There were";

$totalCount = 0;
$passedCount = 0;
$failedCount = 0;

# from command line
my ($param_noclean,
		$cppunitDlls,
		$eunitDlls,
		$allocFailure);

#---------------------------------------Main Start----------------------------------------------------------#

# read command line parameters
my $result = GetOptions("noclean" 			  => \$param_noclean,
												"cppunitdlls:s"   => \$cppunitDlls,
												"eunitdlls:s"	    => \$eunitDlls,
												"allocfailure:i"  => \$allocFailure,
												"help"						=> \$help);
												
$startdir = cwd;

if (defined $help)
{
	print_help();
	exit;
}

# create directory for results
if (mkdir("results", 0777))
{
    print("The results directory was created successfully! \n");
} 
else 
{
    print("The results directory already exists. \n");
} 

# find project root
findProjectDriveAndRoot();

# set target for intrumentation result
$ENV{'CTC_DATA_PATH'}= "$projectdrive$projectrootname$coverageResultsDir";	


if (!defined $param_noclean)
{
	# clear previous results
	print("Cleaning previous results. \n");
	unlink("$projectdrive$projectrootname$coverageResultsDir$buildResults");
	unlink("$projectdrive$projectrootname$coverageResultsDir$coverageDat");
	unlink("$projectdrive$projectrootname$coverageResultsDir$coverageSymbols");
	unlink("$projectdrive$projectrootname$coverageResultsDir$coverageProfile");
	unlink("$projectdrive$projectrootname$coverageResultsDir$finalResultsFile");
		
	# run cppunit tests
	system("$cppunitUnitTestRunner -drive=$projectdrive -root=$projectrootname -cppunitdlls=$cppunitDlls -allocfailure=$allocFailure");
	chdir($startdir);
	
	# run eunit tests
	system("$eunitUnitTestRunner -drive=$projectdrive -root=$projectrootname -eunitdlls=$eunitDlls -allocfailure=$allocFailure");
	chdir($startdir);
}
else
{ 	
	# run cppunit tests
	system("$cppunitUnitTestRunner -drive=$projectdrive -root=$projectrootname -cppunitdlls=$cppunitDlls -allocfailure=$allocFailure -noclean");
	chdir($startdir);
	
	# run eunit tests
	system("$eunitUnitTestRunner -drive=$projectdrive -root=$projectrootname -eunitdlls=$eunitDlls -allocfailure=$allocFailure -noclean");
	chdir($startdir);
}

# create textual output
chdir("$projectdrive$projectrootname$coverageResultsDir");
doSystemCall("ctcpost $coverageSymbols $coverageDat -p $coverageProfile -T 70");
doSystemCall("ctc2html -i $coverageProfile -t 70");


# clear target for intrumentation result
$ENV{'CTC_DATA_PATH'}= "";	

# combine all results
#
open(COVERAGE, "$projectdrive$projectrootname$coverageResultsDir$coverageResultsFile") or die("file $coverageResultsFile not found!\n");
@coverageFileContent = <COVERAGE>;

# eunit

$eunitOutputString = "<span class=\"head1\">EUnit Results</span><br><br>";

if ( -e "$projectdrive$projectrootname$coverageResultsDir$eunitResultsFile" )
{
	open(EUNITRESULTS,  "$projectdrive$projectrootname$coverageResultsDir$eunitResultsFile") or die ("Couldn't open $projectdrive$projectrootname$coverageResultsDir$eunitResultsFile!\n");
	$parser = new XML::Parser::Expat;
	$parser->setHandlers('Start' => \&sh,
                     'End'   => \&eh,
                     'Char'  => \&ch);
	$totalCount = 0;
	$passedCount = 0;
	$failedCount = 0;
		
	$parser->parse(*EUNITRESULTS);
		
	close(EUNITRESULTS);
}
else
{
	print ("file $eunitResultsFile not found!\n");
}


# cppunit

$cppUnitOutputString = "<br><span class=\"head1\">CppUnit Results</span><br><br>";

if ( -e "$projectdrive$projectrootname$coverageResultsDir$cppunitResultsFile" )
{
	open(CPPUNITRESULTS,  "$projectdrive$projectrootname$coverageResultsDir$cppunitResultsFile") or die ("Couldn't open $projectdrive$projectrootname$coverageResultsDir$cppunitResultsFile!\n");
	@cppunitResultsFileContent = <CPPUNITRESULTS>;
	
	for ($k = 0; ( $k + 3 ) <= $#cppunitResultsFileContent; $k++)
		{
			$totalCount = 0;
			$passedCount = 0;
			$failedCount = 0;
			
			$currentLine = @cppunitResultsFileContent[$k];
			for ($currentLine) {
	        s/:+$//;
	    }
			$cppUnitOutputString .= "<span class=\"head3\">$currentLine => </span>";
			
			$currentLine = @cppunitResultsFileContent[++$k];
			@currentLineParts = split ' ', $currentLine;
			$totalCount = $currentLineParts[2];
			$currentLine = @cppunitResultsFileContent[++$k];
			if ( $currentLine  =~ m/$cppunitTestFailuresLine/ )
			{
				@currentLineParts = split ' ', $currentLine;
				$failedCount = $currentLineParts[2] + $currentLineParts[5];
				$k++; #over empty line
			}
			$passedCount = $totalCount - $failedCount;
			if ( $failedCount > 0 )
			{
				$cppUnitOutputString .= "<span class=\"red\">Testcases passed/run: $passedCount/$totalCount </span><br><br>\n";
			}
			else
			{
				$cppUnitOutputString .= "<span class=\"blue\">Testcases passed/run: $passedCount/$totalCount </span><br><br>\n";
			}
			
		}
	close(CPPUNITRESULTS);
}
else
{
	print ("file $cppunitResultsFile not found!\n");
}

# append coverage information after eunit and cppunit results

for ($j = 0; $j <= $#coverageFileContent; $j++)
	{
		$currentLine = @coverageFileContent[$j];
		
		if ($currentLine =~ /$cssLink/)
		{
			if ( open(CSSFILE,  "$projectdrive$projectrootname$coverageResultsDir$cssFile") )
			{
				# append css styles to results html
				$outputString .= "<style type=\"text/css\"> body {";
				@cssFileContent = <CSSFILE>;
				my($line);
				foreach $line (@cssFileContent)
				{ 
					$outputString .= $line;
				}
				$outputString .= "}</style>\n";
				close(CSSFILE);
			}
		}
		else
		{
			$outputString .= $currentLine;

			if ($currentLine =~ /$outputFileBodyStart/)
			{
				$outputString .= $cppUnitOutputString;
				$outputString .= $eunitOutputString;
			}
		}
		
	}
	
open(NEWRESULTSFILE, "> $projectdrive$projectrootname$coverageResultsDir$finalResultsFile") or die "Cannot open final results file\n";
print NEWRESULTSFILE "$outputString";
close(NEWRESULTSFILE);
close(OUTPUT);
close(COVERAGE);

chdir($startdir);

#---------------------------------------Main Ends-------------------------------------------------------------#

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

sub sh
{
  my ($p, $el, %atts) = @_;
	if ( $el eq $xmlDllLine )
	{
		$eunitOutputString .= "<span class=\"head3\">";
		$dllName = %atts->{name};
		@dllNameParts = split m!(\\)!, $dllName;
		$dllName = $dllNameParts[$#dllNameParts];
		$eunitOutputString .= "$dllName => </span>";
		$totalCount = %atts->{size};
	}
	
	if ( $el eq $xmlResultLine )
	{
		$status = %atts->{status};
		if ( $status eq $xmlCasePassed )
		{
			$passedCount++;
		}
		else
		{
			$failedCount++;
		}
	}
}

sub eh
{
	my ($p, $el) = @_;
	if ( $el eq $xmlDllLine )
	{
		$totalCount = $passedCount + $failedCount;
		if ( $failedCount > 0 )
		{
			$eunitOutputString .= "<span class=\"red\">Testcases passed/run: $passedCount/$totalCount </span><br><br>\n";
		}
		else
		{
			$eunitOutputString .= "<span class=\"blue\">Testcases passed/run: $passedCount/$totalCount </span><br><br>\n";
		}
		$passedCount = 0;	
		$failedCount = 0;
	}
}

sub ch
{
	my ($p, $el) = @_;
	#print ("$el\n");
}

sub doSystemCall
{
	#print("\nDoing system call: $_[0]\n");
	#system($_[0]);
	system("echo Doing system call: $_[0] >> $projectdrive$projectrootname$coverageResultsDir$buildResults");
	system("$_[0] >> $projectdrive$projectrootname$coverageResultsDir$buildResults 2>&1");
}

sub print_help
{
	print("\n*************************************************************\n\n");
	print("Script runs by default all ipappservices cppunit and eunit tests\n");
	print("and creates build, test and coverage results to:\n\n");
	print("    multimediacommsengine/internal/test/results/\n\n");
	print("Own configuration file (list of components to be processed)\n");
	print("can be used as well:\n\n");
	print("    >unittest_ctc.pl -cppunitdlls=myowncppunitcomponents.txt\n");
	print("-eunitdlls=myowneunitcomponents.txt\n\n");
	print("Those text files should follow the syntax of default configuration files\n");
	print("multimediacommsengine/internal/test/results/cppunitdlls_ctc.txt and");
	print("multimediacommsengine/internal/test/results/eunitdlls_ctc.txt\n\n");
	print("Alloc failure simulation can be turned on with following command:\n\n");
	print("    >unittest_ctc.pl -allocfailure=2\n\n");
	print("Any number will turn eunit alloc on and for cppunit that value defines\n");
	print("certain alloc failure mode (modes 0-3).\n");
	print("When running just some set of components you might want to \"merge\" the results");
	print("with existing coverage results.\n");
	print("That is possible with command:\n\n");
	print("    >unittest_ctc.pl -cppunitdlls=myowncppunitcomponents.txt");
	print("-eunitdlls=myowneunitcomponents.txt -noclean\n");
	print("\n*************************************************************\n");
}
