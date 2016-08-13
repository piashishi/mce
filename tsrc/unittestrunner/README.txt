README.txt

unittest.pl is perl script for executing cppunit tests and eunit tests. It reports test coverage
of every subsystem defined in cppunitdlls.txt and eunitdlls.txt. Some sources may be left out of 
coverage measurements. Those are defined in ignored.txt.


Before test executing:
---------------------------
There should not be any need to modify the scripts. Those determine project drive and root automatically
so as long as unittest.pl is run under multimediacommsengine\internal\test\ directory, working area can
be located anywhere.


Executing test.pl:
--------------------
unittest.pl collects code coverage of all tested subsystems and prints it to results\CoverageAll.txt file. 
Corresponding Bullseye coverage file is stored in results\CoverageAll.cov file and can be opened with
Bullseye coverage browser GUI in order to see code cxoverage details. 
Additionally, EUnit and CppUnit logs are stored in results\ directory.

NOTE! Script deletes old Bullseye coverage file c:\users\test.cov.

If errors occur while executing CppUnit tests, count for errors and failures are found for every
unsuccessfull subsystem. Errors are collected to CppunitErrors.txt.

If errors occur while executing EUnit tests, information can be found from results xml file. It can be
opened within EUnit report template in order to view detailts of test run.

Used alloc failure type for CppUnit can be passed as a parameter for the script (e.g. ">perl unittest.pl 2"). 
If parameter is not passed, alloc failure type 3 is used.


cppunitdlls.txt syntax:
--------------------------
It includes two rows for every subsystem. The first row is for defining path where build for that particular
subsytem is done. 
The second row is the test-dll name of subsystem.

eunitdlls.txt syntax:
--------------------------
It includes four rows for every subsystem. The first row is for defining path where build for that particular
subsytem is done.
The second row is the test-dll name of subsystem.
The third row is defining build type (if "0": normal build, if "1": test build)
The fourth row may contain some additional command line commands.

ignored.txt syntax:
--------------------------
It includes two rows for each ignore command.
The first line defines whether command is relative to test sources or to the drive root 
(if "0": relative to root, if "1": relative to sources)
The seconds line follows Bullseye syntax for covselect command. Find more info in Bullseye help.
