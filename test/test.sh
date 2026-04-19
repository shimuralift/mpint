#!/bin/bash

ARGC=$#
CMDLPARAM=$1
DRYPARAM=$2

EXECUTABLE="../bin/demo"
OUTFILE="demo.output"


EXECUTABLEGMP="../bin/demoGMP"
OUTFILEGMP="demoGMP.output"


REFFILE="demo.output.ref"
REFFILEGMP="demoGMP.output.ref"

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
    local reffile=$2
    runCmd "${DIFFCMD} ${outfile} ${reffile}"
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

    runExecutable ${EXECUTABLEGMP} ${OUTFILEGMP}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi

    
    doDiff "${OUTFILE}" "${REFFILE}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    doDiff "${OUTFILEGMP}" "${REFFILEGMP}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    
    return ${retval}
}

doProf () {
    if [ "${DRYPARAM}" == "dry" ]; then
        echo "DRY: would run ${EXECUTABLE}, ${EXECUTABLEGMP} with -prof and display side-by-side"
        return 0
    fi

    local tmp1 tmp2 tdata1 tdata2
    tmp1=$(mktemp)
    tmp2=$(mktemp)
    tdata1=$(mktemp)
    tdata2=$(mktemp)

    echo "profiling ${EXECUTABLE} ..."
    ${EXECUTABLE}     -prof > "${tmp1}" 2>&1
    echo "profiling ${EXECUTABLEGMP} ..."
    ${EXECUTABLEGMP}  -prof > "${tmp2}" 2>&1

    # Strip the "===" header line, keep only per-function rows
    grep -v '^===' "${tmp1}" > "${tdata1}"
    grep -v '^===' "${tmp2}" > "${tdata2}"

    echo ""
    grep '===' "${tmp1}" | sed 's/profiling report/profiling comparison/'
    echo ""

    # Merge the two data files side-by-side and format as a table.
    # Each data line has the form "  name: cycles cycles".
    paste "${tdata1}" "${tdata2}" | awk -F'\t' '
    BEGIN {
        printf "%-14s  %20s  %20s\n",
               "function", "demo (long int)", "demoGMP"
        printf "%-14s  %20s  %20s\n",
               "--------------",
               "--------------------",
               "--------------------"
    }
    {
        split($1, a, ":"); name = a[1]
        gsub(/^[[:space:]]+|[[:space:]]+$/, "", name)
        c1 = a[2]
        gsub(/[[:space:]]*cycles[[:space:]]*$/, "", c1); gsub(/^[[:space:]]+/, "", c1)
        split($2, b, ":"); c2 = b[2]
        gsub(/[[:space:]]*cycles[[:space:]]*$/, "", c2); gsub(/^[[:space:]]+/, "", c2)
        printf "%-14s  %20s  %20s\n", name, c1, c2
    }
    '

    rm -f "${tmp1}" "${tmp2}" "${tdata1}" "${tdata2}"
    return 0
}

printHelp () {
    local retval=0

    local helptext='synopsis:
./test.sh  "all"|"prof"|"help" ["dry"]

mandatory 1st arg:
    all           : runs the executables, compares their output
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
                prof)
                    doProf
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
