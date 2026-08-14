# test.md

This file, **test.md**, describes the testing and benchmarking facilities of project mpint
in directory **test**.


## The test script
**test.sh** is a bash script which executes each of the demo programs from **demo/bin**.  
It has to be called from directory **test**.
This is its usage info it outputs it when called with command line option *help*:

    [claudeuser@gondwana:mpint]$ cd test
    [claudeuser@gondwana:test]$ ./test.sh help
    synopsis:
    ./test.sh  "regr"|"prof"|"help" ["dry"]
    
    mandatory 1st arg:
        regr          : runs the executables, compares their output
                        (stdout and stderr combined) to a reference
        prof          : runs all demo* variants with -prof and shows
                        cycle counts side-by-side for easy comparison
        help          : prints this help
    
    optional 2nd arg:
        dry : prints the commands w/o executing them
    
    exit code:
        0 if no error occurs, nonzero else
    
    files relative to the directory this script is in:
        test.sh                 : this script
        <executable>.output     : output of the executables
        <executable>.output.ref : reference output
    [claudeuser@gondwana:test]$ echo $?
    0

In *regr* mode, each of the demo programs runs the same sequence of test suites, see  
*demo/demo.md*. **./test.sh regr** compares the combinmed output, stdout/stderr/exit code,  
of a demo program against a prerecorded reference.

In *prof* mode, each of the demo programs runs the same sequence of test suites multiple times,  
and puts out a summary in terms of rdtsc cpu cycles. **test.sh regr** formats the output of the  
various demos into a table for comparison. The most recently taken benchmark is saved in  
**prof_output.txt**.
