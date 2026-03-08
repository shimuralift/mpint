#!/bin/bash

ARGC=$#
CMDLPARAM=$1
DRYPARAM=$2

EXECUTABLE="../bin/demo"
OUTFILE="demo.output"
REFFILE="demo.output.ref"

DIFFCMD="diff"
RMCMD="rm"
SHOWOUTPUTCMD="cat"
REDIRECTION="> ${OUTFILE} 2>&1"

runCmd () {
    local cmdline=$1
    local silent=$2
    local retval=0
    if [ "${DRYPARAM}" == "dry" ]; then
        echo "############################## DRY RUN : ${cmdline} ##########"
        return $?
    else
        if [ "${silent}" != "silent" ]; then
            echo "############################## START : ${cmdline} ##########"
        fi
        eval "${cmdline}"
        retval=$?
        echo "############################## EXIT  : ${cmdline} : EXITCODE : ${retval} ##########"
        return ${retval}
    fi
}

runExecutable () {
    local retval=0
    runCmd "${EXECUTABLE} ${REDIRECTION}"
    retval=$?
    runCmd "${SHOWOUTPUTCMD} ${OUTFILE}"
    return ${retval}
}

doDiff () {
    runCmd "${DIFFCMD} ${OUTFILE} ${REFFILE}"
    return $?
}

doAll () {
    local retval=0
    runExecutable
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi
    doDiff
    return $?
}

printHelp () {
    local retval=0

    local helptext='synopsis:
./test.sh  "all"|"diff"|"help" ["dry"]

mandatory 1st arg:
    all           : runs scratch make and the resulting executable, compares its output
                    (stdout and stderr combined) to a reference
    diff          : compares out file against ref file, and shows diff output
    help          : prints this help

optional 2nd arg:
    dry : prints the commands w/o executing them

exit code:
    0 if no error occurs, nonzero else

files relative to the directory this script is in:
    test.sh                 : this script
    <executable>.output     : output of the executable
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
                diff)
                    doDiff
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
