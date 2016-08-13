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

$eunitExe = "/epoc32/release/winscw/udeb/EUnitExeRunner.exe";
$eunitParams = "/l xml /e ExeEnv /w 90 /p All /t 300";
$eunitParams2 = "/d alloc";
$eunitResults = "EUnitLog.xml";
$eunitDllsDefault = "eunitdlls_ctc.txt";
$buildResults = "BuildResults.txt";

$eunitSrcDllLocation = "/epoc32/release/winscw/udeb/";
$eunitDstDllLocation = "/epoc32/release/winscw/udeb/z/sys/bin/";

$eunitLog = "/epoc32/winscw/c/DigiaEUnit/Logs/DigiaEUnit_log.xml";
$eunitLog2 = "/epoc32/winscw/c/shared/Eunit/Logs/EUnit_log.xml";

$eunitTestBuildMode = "1";
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
	  $eunitDlls,
		$allocFailure);

#---------------------------------------Main Start----------------------------------------------------------#

# read command line parameters
my $result = GetOptions("noclean" 			 => \$param_noclean,
												"drive=s"			   => \$projectdrive,						
												"root=s" 			   => \$projectrootname,
												"eunitdlls:s"	   => \$eunitDlls,
												"allocfailure:i" => \$allocFailure);


if (!defined $projectdrive)
{
	die("Project drive not defined!\n");
}

if (!defined $projectrootname)
{
	die("Project root not defined!\n");
}

if (!defined $eunitDlls || length($eunitDlls) == 0 )
{
	print("Project dlls not defined, using defaults!\n");
	$eunitDlls = $eunitDllsDefault;
}

if (defined $allocFailure && $allocFailure > 0 )
{
	print("Alloc failure mode active!\n");
}

$startdir = cwd;

# remove previous results
unlink("$coverageResultsDir$eunitResults");

# open file including eunit test dlls path and names
open(EUNITDLLS, $eunitDlls) or die("file $eunitDlls not found!\n");
@dllsFileContent = <EUNITDLLS>;

# open file containing files exluded from measurements
open(IGNOREDFILE, $ignoredFileName) or die("file $ignoredFileName not found!\n");

$excludedCmd = parseExcluded();

# build
doBuild();

#run all tests (with or without alloc)
if (defined $allocFailure && $allocFailure > 0)
{
	doSystemCall("$eunitExe $eunitParams $eunitParams2");
}
else
{
	doSystemCall("$eunitExe $eunitParams");
}

# cleanup
doBuild( "clean" );

# store results file
copy($eunitLog, "$projectdrive$projectrootname$coverageResultsDir$eunitResults");
copy($eunitLog2, "$projectdrive$projectrootname$coverageResultsDir$eunitResults");

close (EUNITDLLS);
close (IGNOREDFILE);

#---------------------------------------Main Ends-------------------------------------------------------------#

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
	    
	    print("DLL path: $currentPathLine\n");
	    print("DLL name: $currentDllNameLine\n");
	    print("DLL build mode: $currentBuildModeLine\n");
	    print("DLL extra commands: $currentExtraCommandsLine\n");
	
	    chdir($projectrootname);
	    chdir($currentPathLine);
	    
	    $temp = cwd;
	    print("current directory is $temp\n");
	    
	    if ( defined $_[0] )
	    {
	    	# do just cleaning
	    	if (!defined $param_noclean)
	    	{
	    		#delete old test dll
		    	unlink("$eunitSrcDllLocation$currentDllNameLine");
		    	unlink("$eunitDstDllLocation$currentDllNameLine");
		    	if ($currentBuildModeLine =~ /$eunitTestBuildMode/)
					{
						doSystemCall("abld test reallyclean winscw udeb ");
		    	}
		    	else
		    	{
		    		doSystemCall("abld reallyclean winscw udeb ");
		    	}
	    	}
	    	else
	    	{
	    		print("no_cleanup param defined!\n");
	    	}
	    }
	   	else
	   	{
		    #delete old test dll
		    unlink("$eunitSrcDllLocation$currentDllNameLine");
		    unlink("$eunitDstDllLocation$currentDllNameLine");
		    
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
					
					if ($currentBuildModeLine =~ /$eunitTestBuildMode/)
					{
						doSystemCall("abld test reallyclean winscw udeb ");
		    		doSystemCall("$ctcCommandPart1 $projectdrive$projectrootname$coverageResultsDir$coverageSymbols $excludedCmd $ctcCommandPart2Test");
		    	}
		    	else
		    	{
		    		doSystemCall("abld reallyclean winscw udeb ");
		    		doSystemCall("$ctcCommandPart1 $projectdrive$projectrootname$coverageResultsDir$coverageSymbols $excludedCmd $ctcCommandPart2");
		    	}
				}
		
				#copy test dll to correct location
				print("copying test dll to: $eunitDstDllLocation$currentDllNameLine \n");
				copy ("$eunitSrcDllLocation$currentDllNameLine", "$eunitDstDllLocation$currentDllNameLine");
				
				#do additional commands
				chdir($projectrootname);
				if ( length($currentExtraCommandsLine) > 0 )
				{
					doSystemCall("$currentExtraCommandsLine");
				}
			}
			
	  	# store current pathline for previous loop increment
	    $previousPathLine = $currentPathLine;
	}
}
sub doSystemCall
{
	system("echo Doing system call: $_[0] >> $projectdrive$projectrootname$coverageResultsDir$buildResults");
	system("$_[0] >> $projectdrive$projectrootname$coverageResultsDir$buildResults 2>&1");
}
