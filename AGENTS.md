# AGENTS.md

This file, *AGENTS.md*, is a general description of project mpint, suitable for LLM based code agents.  
Claude-specific information, is in *CLAUDE.md*.  
Human readers should also refer to *README.md*.

## Project Overview
Project mpint is an exercise in LLM assisted C++ operator overloading.  
The objective is to provide *class MPint*, with a set of operators,
which implements an integer with arbitrary precision.

The use case is modernization of legacy C code containing native
integer arithmetic. The traditional approach would be to link the
old C code with some multiprecision library, and rewrite all the
arithmetic in terms of the interface provided by the library. This
would e.g. require to rewrite an expression like  _a*(b+c)_  as
*mult(a, add(b, c))*, or similar. This is a tedious and error prone
process on nontrivial code, and the result is much more difficult
to read and maintain.

With class *MPint*, one would only have to declare formerly native
integers like *a, b, c* as being of type *MPint*, and the overloaded
operators work in exactly the same way as the operators of the
native integer types. So, ideally, no arithmetic expressions or algorithms
have to be changed. Additionally, *MPint* has constructors, which take a
string as argument, to compensate for the lack of native integer literals.

Project mpint has a *Makefile* driven build, with targets *all* (default) and *clean*,
but that only provides some demo executables of the various *MPint* implementations present
in directories *src* and *include*. These demo executables are used for regression testing
and profiling, driven by *test/test.sh*.

A human (or artificial) consumer is meant to either pick one of the existing *MPint*
implementations, source and header, and start their own project with them, possibly code agent
assisted, or develop their own implementation, using one existing implementation
as a starting point in which case the existing tests and profiling might be helpful.

We have two pimpl-style implementations of *MPint*: *MPintWrappedNativePimpl*
which is just the *MPint* operators wrapping the native *signed long int* type,
and *MPintGMPPimpl* which wraps the C interface of the GNU Multiprecision
library.
In subdirectory mpint/demo, there are several executable artifacts for
demo/testing/profiling purposes:
- *demoNative*: runs the demo on the native *signed long int* type without
  using *MPint* at all (for baseline comparison).
- *demoGMPXX*: uses *mpz_class* from the GMP C++ interface (*gmpxx.h*)
  directly via a typedef, without going through *class MPint*.
- *demoWrappedNativePimpl*: drives the *MPintWrappedNativePimpl* operators.
- *demoGMPPimpl*: drives the *MPintGMPPimpl* wrapper around the GMP C interface.

In subdirectory *mpint/test* there is a bash script *test.sh* which
runs all four demo variants and compares their outputs to respective
reference outputs. *test.sh* with option *prof* does some rdtsc based
profiling of the demo variants and shows a summary of results.


## Development Guidelines
Coding standards and conventions:
* The Compiler is GNU g++ with *-std=c++14* setting. 
* The OS is Debian Linux 13.5.
* Other dependencies are the GNU Multiprecision (GMP) package, GNU make, and bash.

File structure preferences:  
We have this general directory structure:

    include
    src
    demo
        bin
        src
    test

Testing approaches:
simple stdout/stderr based regression test, driven by *test/test.sh regr*,
see below.

Profiling/Benchmarking:
driven by *test/test.sh prof*, see below


## Important Commands
Build commands:  
make, with targets *all*(default) and *clean*.  

Test commands:  
simple stdout/stderr based regression test:  
*cd test; ./test.sh regr*  

Profiling/Benchmarking:  
*cd test; ./test.sh prof*


## Known test-suite overflow exemptions (*demoNative* / *demoWrappedNativePimpl*)
Both native-backed demos compute on a 64-bit *signed long int* and so can
silently overflow on inputs where *demoGMPPimpl* (arbitrary precision) stays exact.
All other lines of *test/test.sh*'s reference outputs (*expr*, *basicexpr*,
*moreexpr*, *extraexpr*, *strconstr*, *floatconv*, *missingexpr*, *detTest*, *reduTest*)
have been independently cross-checked against external oracles (a from-
scratch Python reimplementation of the C++ semantics, and PARI/gp's
*matdet*/*qfrep* for *detTest*/*reduTest*) and match exactly. The known/observed
overflow-driven divergences are:

- *extraexpr()* repeated-squaring test ("23^19"): the true value is
  74615470927590710561908487 (exact on *demoGMPPimpl*). *demoNative* and
  *demoWrappedNativePimpl* both print -3983830012993820921, which is exactly the
  64-bit signed two's-complement wraparound of the same repeated-squaring
  algorithm (confirmed by independently simulating it with explicit int64
  wraparound arithmetic). This is the only overflow in the entire
  *expr/basicexpr/moreexpr/extraexpr/strconstr/floatconv/missingexpr* battery;
  in particular the GCD test's large inputs (482923147313, 988823136811)
  fit comfortably under 64-bit and are unaffected.

- *detTest()* GaussInt column (known): computeDetGaussInt's fraction-free
  Gaussian elimination keeps intermediate values that can exceed the final
  determinant's magnitude. For the two dense (sparsity 0%) 4x4 cases (run 25
  and run 26 of 32), *demoNative/demoWrappedNativePimpl*'s GaussInt overflows to
  402904 and -117875 respectively, while Dodgson and GaussFloat on the same
  runs still report the correct determinants -43753032 and -18819899
  (matching demoGMPPimpl). No other *detTest* case overflows.

- *reduTest()* (potential, not fully isolated): starting at run 13 of 16
  (the first dimension==5 case), demoNative/demoWrappedNativePimpl's generated
  Gram matrices diverge completely from demoGMPPimpl's, and stay diverged for
  all subsequent runs. Runs 1-12 (dimension <= 4) match demoGMPPimpl bit-for-bit.
  isSingular() (called by PosDefState while constructing each candidate
  lattice) calls the very same computeDetGaussInt() that's confirmed to
  overflow on dense 4x4 input above; a wrong singular/non-singular verdict
  on a 5x5 candidate would consume a different number of drand48() draws
  than demoGMPPimpl and fork the entire subsequent random sequence, which is
  consistent with what's observed. This is the likely root cause but has
  not been confirmed by direct instrumentation of isSingular() itself.
