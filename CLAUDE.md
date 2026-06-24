# CLAUDE.md

## Project Overview
Project mpint is an exercise in LLM assisted C++ operator overloading.
The objective is to provide a class 'MPint' with a set of operators
which implements an integer with arbitrary precision.

The use case is modernization of legacy C code containing native
integer arithmetic. The traditional approach would be to link the
old C code with some multiprecision library, and rewrite all the
arithmetic in terms of the interface provided by the library. This
would e.g. require to rewrite an expression like 'a*(b+c)' as
'mult(a, add(b, c))' or similar. This is a tedious and error prone
process on nontrivial code, and the result is much more difficult
to read and maintain.

With class MPint, one would only have to declare formerly native
integers like a, b, c as being of type MPint, and the overloaded
operators work in exactly the same way as the operators of the
native integer types. So, ideally, no arithmetic expressions or algorithms
have to be changed.


MPint is built and archived into a static library, accompanied by
a generic header file MPint.hpp. There are no implementation details
exposed by this generic header, these are hidden
in MPint*.cpp using the pimpl idiom.

All library code, resulting libraries, and the header reside in 
subdirectories mpint/lib/src, mpint/lib/bin, and mpint/lib/include,
respectively.

We have two implementations of MPint, i.e. MPintWrappedNative which
is just The MPint operators wrapping the native 'signed long int type',
and MPintGMP which wraps the C interface of the GNU Multiprecision
library.

In subdirectory mpint/demo, there are several executable artifacts for
demo/testing/profiling purposes: demoWrappedNative which drives the 
MPintWrappedNative operators, demoGMP for the MPintGMP wrapper around the
GMP interface, and, for comparison, demoNative, which runs the demo on
the native 'signed long int' type without using MPint at all.

In subdirectory mpint/test there is a bash script 'test.sh' which
runs all three demo variants and compares their outputs to respective
reference outputs. 'test.sh' with option 'prof' does some rdtsc based
profiling of the demo variants and shows a summary of results.


### Subproject dist/multiPrecOperators
mpint itself has grown organically over time and contains
idiosyncratic bash script based testing and profiling involving
some more arcane examples in integral determinant calculation and
lattice reduction and finding shortest vectors. This is good enough
for the author but not appropriate for most users.

In directory dist there is a project 'multiPrecOperators' which
serves as a starting point for the user. It contains classes MPint,
MPintWrappedNative (initially a copy of MPint) and a generic header
MPint.hpp. Both classes can be compiled into a static library to
be used in a user project. There is also some demo program which
may serve as a smoke test.

multiPrecOperator does not have any regression test and profiling
facilities. The recommended approach is to modify MPint.cpp in
order to use a multoprecision library, or use a code agent to do
that. Initially MPint implements its operator functionality in terms
of 'signed long int'.
MPintWrappedNative should be left unmodified for later comparison
with the user's MPint implementation.

Consequentially, the demo comes in three variants, demoMP,
demoWrappedNative, and demoNative. The latter variant does not use
MPint at all, but just the native 'signed long int' directly.

All systematic testing, profiling, versioning, and integration, as
well as the implementation using a suitable multi precision integer
package is deliberately left to the user, or rather a code
agent.


## Development Guidelines
Coding standards and conventions:
The Compiler is GNU g++ with '-std=c++14' setting. 
The OS is Debian Linux 13.5.
Other dependencies are the GNU Multiprecision (GMP) package, GNU make, and bash.


File structure preferences:
For both mpint and multiPrecOperators we have the general directory
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
simple stdout/stderr based regression test, driven by test/test.sh all,
see below.

Profiling/Benchmarking:
driven by test/test.sh prof, see below

## Important Commands
Build commands:
make, with targets all(default) and clean.
mpint and multiPrecOperators have separate Makefiles in their top level directories.
On checkout, multiPrecOperators is mostly an empty directory structure, guarded
by .gitkeep files. multiPrecOperators is populated with src files from mpint by
mpint's 'make all' and reverted to its empty state by mpint's 'make clean'.
For actually ditributing and using it, it must be copied elsewhere.

Test commands (mpint only):
simple stdout/stderr based regression test: cd test; ./test.sh all
'multiPrecOperators' can only be smoke tested by running the demo* executables.

Profiling/Benchmarking (mpint only):
cd test; ./test.sh prof

## What I've done in the meantime
I've rearranged the projects file system structure, renamed some source, library,
and executable files, and some internal make targets, and adapted the test script
(see above). I also introduced subproject 'dist/multiPrecOperators' (see above).

## What to do for you right now
multiPrecOperators is intended to be an empty directory structure on fresh checkout.
Exceptions are its Makefile and demo/src/demo.cpp.
Everything else is to be populated on mpint's 'make all' as follows:

mpint/lib/src/MPintWrappedNative.cpp -> multiPrecOperators/lib/src/MPint.cpp
mpint/lib/src/MPintWrappedNative.cpp -> multiPrecOperators/lib/src/MPintWrappedNative.cpp
mpint/lib/include/MPint.hpp -> multiPrecOperators/lib/include/MPint.hpp
mpint/demo/src/demoTypedef.hpp -> multiPrecOperators/demo/src/demoTypedef.hpp
mpint/demo/src/exprTest.cpp -> multiPrecOperators/demo/src/exprTest.cpp
mpint/demo/src/exprTest.hpp -> multiPrecOperators/demo/src/exprTest.hpp

All these sources shall be deleted from multiPrecOperators on mpint's 'make clean.

