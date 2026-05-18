# CLAUDE.md

## Project Overview
MPint shall become A C++(14) class which can be used instead of existing
native integer types in legacy C/C++ code.
There is an empty shell for that class in MPint.hpp.

For now, MPint should just be a proxy to "signed long int", as signified by
the private member variable "mVal". For the future, this is going to replaced
by an instance of some multi precision integer type from e.g. GMP, PARI, etc.

The point is to provide overloaded operators, so that the delicate
arithmetic expressions in the legacy stuff (from 1990ies math research)
do not have be rewritten in terms of methods like "c=add(a,b)" instead of
"c=a+b", which is extremely error prone, and even harder to read and maintain than
what currently exists.

## Development Guidelines
Coding standards and conventions: no prefs so far, tbd later

File structure preferences: no prefs so far, tbd later

Testing approaches: simple stdout/stderr based regression test,
driven by test/test.sh all, see below

Profiling/Benchmarking: driven by test/test.sh prof, see below

## Important Commands
Build commands: make

Test commands: simple stdout/stderr based regression test: cd test; ./test.sh all

Profiling/Benchmarking: cd test; ./test.sh prof

## What I've done in the meantime
I've introduced redu.cpp and redu.hpp to the sources for testing/profiling.
The code provides four algorithms for LLL reduction of integral gram matrices
(integral and positive definite) and for computing shortest lattice vectors
if those gram matrices are considered to define an integral lattice.
That should not go into the MPint* libs, only into teh various demo*
executables. So far, they are not called in demo.
SQState and, as a subclass, PosDefState have been factored out into
demoutils. They should provide a set of square resp. positive
definite random matrices for use in various matrix algorithms, which
act destructively on them, e.g. gaussian elimination. Once instantiated,
these matrices can be restored.
PosDefState is intended to have the same public interface as SQState,
these classes should only differ in their ctor implementations.
They follow the pimpl idiom, so the header does not reveal the
implementation details. Unforunately, the protected pImpl aggregate
in superclass SQState is not recognized by the compiler in the
PosDefState ctor.


## What to do for you right now
Why is pImpl from Superclass SQState not recognized in the PosDefState
ctor, and how could it be fixed?
