#!/bin/bash

ARGC=$#
CMDLPARAM=$1
DRYPARAM=$2

EXECUTABLENATIVE="../demo/bin/demoNative"
OUTFILENATIVE="demoNative.output"

EXECUTABLEGMPXX="../demo/bin/demoGMPXX"
OUTFILEGMPXX="demoGMPXX.output"

EXECUTABLEWRAPPEDNATIVE="../demo/bin/demoWrappedNative"
OUTFILEWRAPPEDNATIVE="demoWrappedNative.output"

EXECUTABLEGMP="../demo/bin/demoGMP"
OUTFILEGMP="demoGMP.output"

EXECUTABLEWRAPPEDNATIVEPIMPL="../demo/bin/demoWrappedNativePimpl"
OUTFILEWRAPPEDNATIVEPIMPL="demoWrappedNativePimpl.output"

EXECUTABLEGMPPIMPL="../demo/bin/demoGMPPimpl"
OUTFILEGMPPIMPL="demoGMPPimpl.output"

REFFILENATIVE="demoNative.output.ref"
REFFILEGMPXX="demoGMPXX.output.ref"
REFFILEWRAPPEDNATIVE="demoWrappedNative.output.ref"
REFFILEGMP="demoGMP.output.ref"
REFFILEWRAPPEDNATIVEPIMPL="demoWrappedNativePimpl.output.ref"
REFFILEGMPPIMPL="demoGMPPimpl.output.ref"

DIFFCMD="diff"
RMCMD="rm"
SHOWOUTPUTCMD="cat"

DRY_RUN_PREFIX="############################## DRY RUN : "

runCmd () {
    local cmdline=$1
    local retval=0
    if [ "${DRYPARAM}" == "dry" ]; then
        echo "${DRY_RUN_PREFIX}${cmdline} ##########"
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

doRegression () {
    local retval=0
    local diffretval=0


    runExecutable ${EXECUTABLENATIVE} ${OUTFILENATIVE}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi

    runExecutable ${EXECUTABLEGMPXX} ${OUTFILEGMPXX}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi

    runExecutable ${EXECUTABLEWRAPPEDNATIVE} ${OUTFILEWRAPPEDNATIVE}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi

    runExecutable ${EXECUTABLEGMP} ${OUTFILEGMP}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi

    runExecutable ${EXECUTABLEWRAPPEDNATIVEPIMPL} ${OUTFILEWRAPPEDNATIVEPIMPL}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi

    runExecutable ${EXECUTABLEGMPPIMPL} ${OUTFILEGMPPIMPL}
    retval=$?
    if [ "${retval}" -ne 0 ]; then
        return ${retval}
    fi


    doDiff "${OUTFILENATIVE}" "${REFFILENATIVE}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    doDiff "${OUTFILEGMPXX}" "${REFFILEGMPXX}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    doDiff "${OUTFILEWRAPPEDNATIVE}" "${REFFILEWRAPPEDNATIVE}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    doDiff "${OUTFILEGMP}" "${REFFILEGMP}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    doDiff "${OUTFILEWRAPPEDNATIVEPIMPL}" "${REFFILEWRAPPEDNATIVEPIMPL}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi

    doDiff "${OUTFILEGMPPIMPL}" "${REFFILEGMPPIMPL}"
    diffretval=$?
    if [ "${diffretval}" -ne 0 ]; then
        retval=${diffretval}
    fi


    return ${retval}
}

doProf () {
    local tmp1 tmp2 tmp3 tmp4 tmp5 tmp6 tdata1 tdata2 tdata3 tdata4 tdata5 tdata6
    tmp1=$(mktemp); tmp2=$(mktemp); tmp3=$(mktemp)
    tmp4=$(mktemp); tmp5=$(mktemp); tmp6=$(mktemp)
    tdata1=$(mktemp); tdata2=$(mktemp); tdata3=$(mktemp)
    tdata4=$(mktemp); tdata5=$(mktemp); tdata6=$(mktemp)

    runCmd "${EXECUTABLENATIVE} -prof > ${tmp1} 2>&1"
    runCmd "${EXECUTABLEGMPXX} -prof > ${tmp2} 2>&1"
    runCmd "${EXECUTABLEWRAPPEDNATIVE} -prof > ${tmp3} 2>&1"
    runCmd "${EXECUTABLEGMP} -prof > ${tmp4} 2>&1"
    runCmd "${EXECUTABLEWRAPPEDNATIVEPIMPL} -prof > ${tmp5} 2>&1"
    runCmd "${EXECUTABLEGMPPIMPL} -prof > ${tmp6} 2>&1"

    if [ "${DRYPARAM}" == "dry" ]; then
        echo "${DRY_RUN_PREFIX}<post processing results and printing a summarizing table on stdout>"
        rm -f "${tmp1}" "${tmp2}" "${tmp3}" "${tmp4}" "${tmp5}" "${tmp6}" \
              "${tdata1}" "${tdata2}" "${tdata3}" "${tdata4}" "${tdata5}" "${tdata6}"
        return 0
    fi

    # Strip the "===" header line, keep only per-function rows
    grep -v '^===' "${tmp1}" > "${tdata1}"
    grep -v '^===' "${tmp2}" > "${tdata2}"
    grep -v '^===' "${tmp3}" > "${tdata3}"
    grep -v '^===' "${tmp4}" > "${tdata4}"
    grep -v '^===' "${tmp5}" > "${tdata5}"
    grep -v '^===' "${tmp6}" > "${tdata6}"

    echo ""
    grep '===' "${tmp1}" | sed 's/profiling report/profiling comparison/'
    echo ""

    # Merge the six data files side-by-side and format as a table.
    # Each data line has the form "  name: cycles cycles".
    paste "${tdata1}" "${tdata2}" "${tdata3}" "${tdata4}" "${tdata5}" "${tdata6}" | awk -F'\t' '
    BEGIN {
        printf "%-14s  %20s  %20s  %22s  %20s  %26s  %20s\n",
               "function", "demoNative", "demoGMPXX",
               "demoWrappedNative", "demoGMP",
               "demoWrappedNativePimpl", "demoGMPPimpl"
        printf "%-14s  %20s  %20s  %22s  %20s  %26s  %20s\n",
               "--------------",
               "--------------------", "--------------------",
               "----------------------", "--------------------",
               "--------------------------", "--------------------"
    }
    {
        split($1, a, ":"); name = a[1]
        gsub(/^[[:space:]]+|[[:space:]]+$/, "", name)
        c1 = a[2];  gsub(/[[:space:]]*cycles[[:space:]]*$/, "", c1); gsub(/^[[:space:]]+/, "", c1)
        split($2, b, ":"); c2 = b[2]; gsub(/[[:space:]]*cycles[[:space:]]*$/, "", c2); gsub(/^[[:space:]]+/, "", c2)
        split($3, d, ":"); c3 = d[2]; gsub(/[[:space:]]*cycles[[:space:]]*$/, "", c3); gsub(/^[[:space:]]+/, "", c3)
        split($4, e, ":"); c4 = e[2]; gsub(/[[:space:]]*cycles[[:space:]]*$/, "", c4); gsub(/^[[:space:]]+/, "", c4)
        split($5, f, ":"); c5 = f[2]; gsub(/[[:space:]]*cycles[[:space:]]*$/, "", c5); gsub(/^[[:space:]]+/, "", c5)
        split($6, g, ":"); c6 = g[2]; gsub(/[[:space:]]*cycles[[:space:]]*$/, "", c6); gsub(/^[[:space:]]+/, "", c6)
        printf "%-14s  %20s  %20s  %22s  %20s  %26s  %20s\n", name, c1, c2, c3, c4, c5, c6
    }
    '

    rm -f "${tmp1}" "${tmp2}" "${tmp3}" "${tmp4}" "${tmp5}" "${tmp6}" \
          "${tdata1}" "${tdata2}" "${tdata3}" "${tdata4}" "${tdata5}" "${tdata6}"
    return 0
}

printHelp () {
    local retval=0

    local helptext='synopsis:
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
                regr)
                    doRegression
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
