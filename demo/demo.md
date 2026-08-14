# demo.md

This file, **demo.md**, describes the demo programs, source code and build artifacts, in this
subdirectory.

## Overview
The *Makefile* driven build of project mpint does **not** provide any deliverable artifacts  
such as libraries or headers. Instead, the build only produces demo executables in the  
**demo/bin** directory. These executables, one for each *class MPint* implementation, and two  
for baseline comparison, only run a series of test suites, and print out results for regression  
testing by comparison to prerecorded such output in the **test** directory.  
When the **-prof** option is given to any of the executables, each of the test suites is run  
multiply, and the duration is measured in rdtsc clock cycles. These timings are put out in  
a table like this:

    [claudeuser@gondwana:mpint]$ demo/bin/demoGMPOpt -prof
    === profiling report (rdtsc cpu cycles, avg of 100000 runs) ===
      expr       :     8 168 cycles
      basicexpr  :    71 368 cycles
      moreexpr   :    26 027 cycles
      extraexpr  :    49 585 cycles
      strconstr  :    21 995 cycles
      floatconv  :    25 791 cycles
      missingexpr:    10 455 cycles
      injTest    :    67 398 cycles
      operatorOpt:    30 951 cycles
      detTest    :   654 831 cycles
      reduTest   : 6 210 012 cycles
    [claudeuser@gondwana:mpint]$ echo $?
    0

The **test/test.sh** script orchestrates both regression testing and benchmarking over all demo  
executable variants and gives a combined output.

## Variants of the demo executables 
See **AGENTS.md** for an overview of the demo variants.

## The Makefile
The **Makefile** resides in the top level mpint project directory and is quite straightforward.  
Here, only the compiler invocations for the demo variants are shown:

    $(CXX) $(CXXFLAGS) -DDEMO_NATIVE -I$(DEMO_INCLDIR) -o $@ $(DEMO_SRCS)
    $(CXX) $(CXXFLAGS) -DDEMO_GMPXX -I$(DEMO_INCLDIR) -o $@ $(DEMO_SRCS) -lgmp -lgmpxx
    $(CXX) $(CXXFLAGS) -DDEMO_WRAPPEDNATIVE -I$(DEMO_INCLDIR) -I$(INCLDIR) -o $@ $(DEMO_SRCS)
    $(CXX) $(CXXFLAGS) -DDEMO_WRAPPEDNATIVEOPT -I$(DEMO_INCLDIR) -I$(INCLDIR) -o $@ $(DEMO_SRCS)
    $(CXX) $(CXXFLAGS) -DDEMO_WRAPPEDNATIVEPIMPL -I$(DEMO_INCLDIR) -I$(INCLDIR) -o $@ $(DEMO_SRCS) $(WRAPPEDNATIVEPIMPL_SRC)
    $(CXX) $(CXXFLAGS) -DDEMO_GMP -I$(DEMO_INCLDIR) -I$(INCLDIR) -o $@ $(DEMO_SRCS) -lgmp
    $(CXX) $(CXXFLAGS) -DDEMO_GMPOPT -I$(DEMO_INCLDIR) -I$(INCLDIR) -o $@ $(DEMO_SRCS) -lgmp
    $(CXX) $(CXXFLAGS) -DDEMO_GMPPIMPL -I$(DEMO_INCLDIR) -I$(INCLDIR) -o $@ $(DEMO_SRCS)  $(GMPPIMPL_SRC) -lgmp

For each variant, a distinctive CPP macro is set. This is further processed in **demoTypedef.hpp**,  
see below

## The test suites in a demo executable
The entry points to these suites are defined in **exprTest.cpp** and declared in **exprTest.hpp**  
There is both some redundancy in here and missing coverage. I've never checked coverage myself  
systematically, or instructed the code agent to do that.  
Results have been checked against 
these suites are mainly for regression testing, but they are featured in the profiling option  
as well:
- "elementary operator expressions": **expr()**  
a few simple ctor invocations and operator calls, written initially by the code agent
- "my elementary operator expressions": **basicexpr()**  
a more comprehensive ctor and operator test, written by myself long before the project was started
- "more operator expressions": **moreexpr()**  
tests of native int and MPint interaction, written by the code agent
- "extra operator expressions": **extraexpr()**  
mostly comparison operators and euclid's algorithm, written by the code agent
- "string constructor tests": **strconstr()**
tests MPint construction from strings, to compensate lack of native int literals,  
written by code agent
- "float/double conversion tests": **floatconv()**  
conversions of MPint to native floating point numbers, written by code agent
- "missing coverage tests": **missingexpr()**
some operators and ctors not covered before, found and written by code agent
- "input safety tests": **injTest()**  
tests validation of string input to ctors
- "operator optimisation tests": **operatorOpt()**  
tests extra operators in the "Opt" variants

In addition, there are the following two suites, which are rather "real world" use cases.  
They have been taken from decades-old C programs and been modernized only slightly.  
Only the critical (i.e. overflow prone) integers have been replaced with MPint instances.  
The results have been checked against an oracle in form of a contemporary (as of 2026)  PARI/GP  
installation by the code agent on instruction. Still, the results might not always be accurate,  
but it is out of scope of project mpint to ensure this.  
These suites are not so useful for regression testing of numerical correctness,  
but more so for bechmarking:
- "determinant example": **detTest()**: det.hpp / det.cpp  
Here we have two integral implementations of determinant calculation of integral square matrices,  
one based on Gaussian elimination, the other on Dodgson's method. A third implementation is  
Gaussian, but uses floating point numbers, it is just for comparison.
- "integral lattice example": **reduTest()**: redu.hpp / redu.cpp  
Runs on a - more or less - random series of positive definite integral square matrices,  
representing integral lattices, performs **LLL reduction** on them and counts  
**shortest vectors** of these lattices, ordered by their integral lengths.  
The algorithms are implemented according to  
*H.Cohen, A Course In Computational Algebraic Number Theory, 2nd ed., Springer 1995*.  
Results have been checked against an oracle consisting of **PARI/GP**. Whether that's an independent  
oracle is debatable, since all implementations i have seen, including *PARI/GP*, are based on the  
algorithms presented in Cohen's book.

### Known test-suite overflow exemptions (*demoNative / demoWrappedNative[...]*)
All native-backed demos compute on a 64-bit *signed long int* and so can silently overflow  
on inputs where *demoGMPPimpl* (arbitrary precision) stays exact. 
All other lines of *test/test.sh*'s reference outputs (*expr*, *basicexpr*, *moreexpr*,  
*extraexpr*, *strconstr*, *floatconv*, *missingexpr*, *detTest*, *reduTest*) have been  
independently cross-checked against external oracles (a from-scratch Python reimplementation  
of the C++ semantics, and PARI/gp's *matdet*/*qfrep* for *detTest*/*reduTest*) and match exactly.  
The known/observed overflow-driven divergences are:

- *extraexpr()* repeated-squaring test ("23^19"): the true value is 74615470927590710561908487  
(exact on *demoGMPPimpl*). *demoNative* and *demoWrappedNativePimpl* both print  
-3983830012993820921, which is exactly the 64-bit signed two's-complement wraparound of the  
same repeated-squaring algorithm (confirmed by independently simulating it with explicit int64  
wraparound arithmetic). This is the only overflow in the entire  
*expr/basicexpr/moreexpr/extraexpr/strconstr/floatconv/missingexpr* battery; in particular  
the GCD test's large inputs (482923147313, 988823136811) fit comfortably under 64-bit  
and are unaffected.

- *detTest()* GaussInt column (known): computeDetGaussInt's fraction-free Gaussian elimination  
keeps intermediate values that can exceed the final determinant's magnitude. For the two dense  
(sparsity 0%) 4x4 cases (run 25 and run 26 of 32), *demoNative/demoWrappedNativePimpl*'s GaussInt  
overflows to 402904 and -117875 respectively, while Dodgson and GaussFloat on the same runs still  
report the correct determinants -43753032 and -18819899 (matching demoGMPPimpl).  
No other *detTest* case overflows.

- *reduTest()* (potential, not fully isolated): starting at run 13 of 16  
(the first dimension==5 case), demoNative/demoWrappedNativePimpl's generated Gram matrices  
diverge completely from demoGMPPimpl's, and stay diverged for all subsequent runs. Runs 1-12  
(dimension <= 4) match demoGMPPimpl bit-for-bit.  
isSingular() (called by PosDefState while constructing each candidate lattice) calls the very same  
computeDetGaussInt() that's confirmed to overflow on dense 4x4 input above; a wrong  
singular/non-singular verdict on a 5x5 candidate would consume a different number of drand48()  
draws than demoGMPPimpl and fork the entire subsequent random sequence, which is consistent with  
what's observed. This is the likely root cause but has not been confirmed by direct  
instrumentation of isSingular() itself.

## Other sources in **demo/src**
- **demo.cpp**  
Here resides the **main()** function. All test suites are executed in order, both in the  
regression test and the profiling contexts.
- **demoTypedef.hpp**  
the proper include files are inserted for each variant, and some additional CPP macros are set.  
This is the relevant switch:

    #if defined DEMO_NATIVE
        typedef signed long int MPint;
    #elif defined DEMO_GMPXX
        #include <gmpxx.h>
        typedef mpz_class MPint;
        #define DEMO_ARBPREC
    #elif defined DEMO_WRAPPEDNATIVE
        #include "MPintWrappedNative.hpp"
    #elif defined DEMO_WRAPPEDNATIVEOPT
        #include "MPintWrappedNativeOpt.hpp"
    #elif defined DEMO_WRAPPEDNATIVEPIMPL
        #include "MPintPimpl.hpp"
    #elif defined DEMO_GMP
        #include "MPintGMP.hpp"
        #define DEMO_ARBPREC
    #elif defined DEMO_GMPOPT
        #include "MPintGMPOpt.hpp"
        #define DEMO_ARBPREC
    #elif defined DEMO_GMPPIMPL
        #include "MPintPimpl.hpp"
        #define DEMO_ARBPREC
    #else
        #error No MPint implementation selected, cf demoTypedef.hpp and Makefile.
    #endif

- **demoUtils.cpp/demoUtils.hpp**  
Provides some basic primitives to allocate/destroy and print matrices as 2dim arrays.  
It also generates series of random square matrices and positive definite matrices for the  
**detTest** and **reduTest** suites. These series are "random" but deterministic since seeded  
with a constant to a RNG, to enable regression testing.
