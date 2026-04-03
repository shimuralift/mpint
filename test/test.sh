#!/bin/bash

ARGC=$#
CMDLPARAM=$1
DRYPARAM=$2

EXECUTABLE="../bin/demo"
OUTFILE="demo.output"

EXECUTABLEMyOwn="../bin/demoMyOwn"
OUTFILEMyOwn="demoMyOwn.output"

EXECUTABLEGMP="../bin/demoGMP"
OUTFILEGMP="demoGMP.output"


REFFILE="demo.output.ref"

DIFFCMD="diff"
RMCMD="rm"
SHOWOUTPUTCMD="cat"

runCmd () {
    local cmdline=$1
    local retval=0
    if [ "${DRYPARAM}" == "dry" ]; then
        echo "############################## DRY RUN : ${cmdline} ##########"
        return $?
    else
        echo "############################## START : ${cmdline} ##########"
        eval "${cmdline}"
        retval=$?
        echo "############################## EXIT  : ${cmdline} : EXITCODE : ${retval} ##########"
        return ${retval}
    fi
}

runExecutable () {
    local executable=$1
    local outfile=$2
    local retval=0
    local redirection="> ${outfile} 2>&1"
    runCmd "${executable} ${redirection}"
    retval=$?
    runCmd "${SHOWOUTPUTCMD} ${outfile}"
    return ${retval}
}

doDiff () {
    local outfile=$1    
    runCmd "${DIFFCMD} ${outfile} ${REFFILE}"
    return $?
}

doAll () {
    local retval=0
    local diffretval=0

    
    runExecutable ${EXECUTABLE} ${OUTFILE}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi

    runExecutable ${EXECUTABLEMyOwn} ${OUTFILEMyOwn}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi

    runExecutable ${EXECUTABLEGMP} ${OUTFILEGMP}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi

    
    doDiff "${OUTFILE}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    doDiff "${OUTFILEMyOwn}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    doDiff "${OUTFILEGMP}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    
    return ${retval}
}

printHelp () {
    local retval=0

    local helptext='synopsis:
./test.sh  "all"|"help" ["dry"]

mandatory 1st arg:
    all           : runs the executables, compares their output
                    (stdout and stderr combined) to a reference
    help          : prints this help

optional 2nd arg:
    dry : prints the commands w/o executing them

exit code:
    0 if no error occurs, nonzero else

files relative to the directory this script is in:
    test.sh                 : this script
    <executable>.output     : output of the executables
    <executable>.output.ref : reference output'

    echo "${helptext}"
    if [ $? -ne 0 ]; then
        retval=2
    fi
    return ${retval}
}


main () {
    local exitval=2
    if [ ${ARGC} -gt 2 ] || [ ${ARGC} -eq 0 ]; then
        printHelp
    else
        if [ "${DRYPARAM}" == "" ] || [ "${DRYPARAM}" == "dry" ]; then
            case "${CMDLPARAM}" in
                all)
                    doAll
                    exitval=$?
                    ;;
                help)
                    printHelp
                    exitval=$?
                    ;;
                *)
                    printHelp
                    ;;
            esac
        else
            printHelp
        fi
    fi
    return ${exitval}
}

main
exit $?
