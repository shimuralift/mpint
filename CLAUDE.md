# CLAUDE.md

## Project Overview
Project mpint is an exercise in LLM assisted C++ operator overloading.  
The objective is to provide a class *MPint* with a set of operators
which implements an integer with arbitrary precision.

The use case is modernization of legacy C code containing native
integer arithmetic. The traditional approach would be to link the
old C code with some multiprecision library, and rewrite all the
arithmetic in terms of the interface provided by the library. This
would e.g. require to rewrite an expression like *a*(b+c)* as
*mult(a, add(b, c))*, or similar. This is a tedious and error prone
process on nontrivial code, and the result is much more difficult
to read and maintain.

With class *MPint*, one would only have to declare formerly native
integers like *a, b, c* as being of type *MPint*, and the overloaded
operators work in exactly the same way as the operators of the
native integer types. So, ideally, no arithmetic expressions or algorithms
have to be changed. Additionally, *MPint* has constructors, which take a
string as argument, to compensate for the lack of native integer literals.

*MPint* is built and archived into a static library, accompanied by
a generic header file *MPint.hpp*. There are no implementation details
exposed by this generic header, these are hidden
in  _MPint_ \* _.cpp_  using the pimpl idiom.
All library code, resulting libraries, and the header reside in 
subdirectories of *mpint/lib/*.

We have two implementations of *MPint*: *MPintWrappedNative* which
is just the *MPint* operators wrapping the native *signed long int* type,
and *MPintGMP* which wraps the C interface of the GNU Multiprecision
library.
In subdirectory mpint/demo, there are several executable artifacts for
demo/testing/profiling purposes: *demoWrappedNative* which drives the 
*MPintWrappedNative* operators, *demoGMP* for the *MPintGMP* wrapper around the
GMP interface, and, for comparison, *demoNative*, which runs the demo on
the native *signed long int* type without using *MPint* at all.
In subdirectory *mpint/test* there is a bash script *test.sh* which
runs all three demo variants and compares their outputs to respective
reference outputs. *test.sh* with option *prof* does some rdtsc based
profiling of the demo variants and shows a summary of results.


## Development Guidelines
Coding standards and conventions:
* The Compiler is GNU g++ with *-std=c++14* setting. 
* The OS is Debian Linux 13.5.
* Other dependencies are the GNU Multiprecision (GMP) package, GNU make, and bash.

File structure preferences:  
For both mpint and multiPrecOperators (see below) we have the general directory
structure

    lib
        bin
        include
        src
    demo
        bin
        src
    test (mpint only)
    dist (mpint only)

Testing approaches:
simple stdout/stderr based regression test, driven by *test/test.sh all*,
see below.

Profiling/Benchmarking:
driven by *test/test.sh prof*, see below


## Important Commands
Build commands:  
make, with targets *all*(default) and *clean*.  
mpint and multiPrecOperators have separate Makefiles in their top level directories.
On checkout, multiPrecOperators is a mostly empty directory structure, guarded
by .gitkeep files. multiPrecOperators is populated with src files from mpint by
mpint's *make all* and reverted to its empty state by mpint's *make clean*.
For actually shipping and using it, it must be copied elsewhere.
The files copied into multiPrecOperators by 'make all' are listed in mpint's
.gitignore (and its committed template .gitignore.example), so that populating
or cleaning multiPrecOperators never shows up as a change in 'git status' on
this branch.

Test commands (mpint only):  
simple stdout/stderr based regression test: *cd test; ./test.sh all*
multiPrecOperators can only be smoke tested by running the demo\* executables.

Profiling/Benchmarking (mpint only):
*cd test; ./test.sh prof*


## Known test-suite overflow exemptions (*demoNative* / *demoWrappedNative*)
Both native-backed demos compute on a 64-bit *signed long int* and so can
silently overflow on inputs where *demoGMP* (arbitrary precision) stays exact.
All other lines of *test/test.sh*'s reference outputs (*expr*, *basicexpr*,
*moreexpr*, *extraexpr*, *strconstr*, *floatconv*, *missingexpr*, *detTest*, *reduTest*)
have been independently cross-checked against external oracles (a from-
scratch Python reimplementation of the C++ semantics, and PARI/gp's
*matdet*/*qfrep* for *detTest*/*reduTest*) and match exactly. The known/observed
overflow-driven divergences are:

- *extraexpr()* repeated-squaring test ("23^19"): the true value is
  74615470927590710561908487 (exact on *demoGMP*). *demoNative* and
  *demoWrappedNative* both print -3983830012993820921, which is exactly the
  64-bit signed two's-complement wraparound of the same repeated-squaring
  algorithm (confirmed by independently simulating it with explicit int64
  wraparound arithmetic). This is the only overflow in the entire
  *expr/basicexpr/moreexpr/extraexpr/strconstr/floatconv/missingexpr* battery;
  in particular the GCD test's large inputs (482923147313, 988823136811)
  fit comfortably under 64-bit and are unaffected.

- *detTest()* GaussInt column (known): computeDetGaussInt's fraction-free
  Gaussian elimination keeps intermediate values that can exceed the final
  determinant's magnitude. For the two dense (sparsity 0%) 4x4 cases (run 25
  and run 26 of 32), *demoNative/demoWrappedNative*'s GaussInt overflows to
  402904 and -117875 respectively, while Dodgson and GaussFloat on the same
  runs still report the correct determinants -43753032 and -18819899
  (matching demoGMP). No other *detTest* case overflows.

- *reduTest()* (potential, not fully isolated): starting at run 13 of 16
  (the first dimension==5 case), demoNative/demoWrappedNative's generated
  Gram matrices diverge completely from demoGMP's, and stay diverged for
  all subsequent runs. Runs 1-12 (dimension <= 4) match demoGMP bit-for-bit.
  isSingular() (called by PosDefState while constructing each candidate
  lattice) calls the very same computeDetGaussInt() that's confirmed to
  overflow on dense 4x4 input above; a wrong singular/non-singular verdict
  on a 5x5 candidate would consume a different number of drand48() draws
  than demoGMP and fork the entire subsequent random sequence, which is
  consistent with what's observed. This is the likely root cause but has
  not been confirmed by direct instrumentation of isSingular() itself.

### Subproject *dist/multiPrecOperators*
mpint itself has grown organically over time and contains
idiosyncratic bash script based testing and profiling involving
some more arcane examples in integral determinant calculation and
lattice reduction and finding shortest vectors. This is good enough
for the author but not appropriate for most users.

In directory *dist* there is a project multiPrecOperators which
serves as a starting point for the user. It contains classes *MPint*,
*MPintWrappedNative* (initially a copy of *MPint*) and a generic header
*MPint.hpp*. Both classes can be compiled into a static library to
be used in a user project. There is also some demo program which
may serve as a smoke test.
multiPrecOperator does not have any regression test and profiling
facilities. The recommended approach is to modify *MPint.cpp* in
order to use a multi precision library, or use a code agent to do
that. Initially *MPint* implements its operator functionality in terms
of *signed long int*.
*MPintWrappedNative* should be left unmodified for later comparison
with the user's *MPint* implementation.
Consequentially, the demo comes in three variants, *demoMP*,
*demoWrappedNative*, and *demoNative*. The latter variant does not use
*MPint* at all, but just the native *signed long int* directly.
All systematic testing, profiling, versioning, and integration, as
well as the implementation using a suitable multi precision integer
package is deliberately left to the user, or rather a code
agent.
