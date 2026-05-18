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
PosDefState::PosDefState currently generates a plain random matrix,
identical to SQState. It needs to produce a positive definite integer
matrix instead.

Algorithm for the PosDefState ctor:
1. Allocate a temporary dim x (n*dim) matrix L (n=3 is fine), filling
   it with random integers the same way SQState fills its square matrix
   (using entryMagnitude and sparsity).
2. Compute G = L * L^T, a dim x dim symmetric positive semi-definite
   integer matrix.
3. Write G row-wise into pImpl->mFlatMatrix (dim^2 entries) and call
   reinitializeCurrentState() to populate mMatrix from mFlatMatrix.
4. Check whether G is singular using one of the integral determinant
   algorithms from det.cpp (computeDetDodgson or computeDetGaussInt).
   Note: these functions are currently static in det.cpp, so a small
   non-static wrapper (e.g. bool isSingular(...)) must be added to
   det.cpp and declared in det.hpp before demoUtils.cpp can call it.
   The det functions operate destructively on mMatrix, so after a
   non-singular result call reinitializeCurrentState() again to restore
   mMatrix from mFlatMatrix. No manual copy is needed.
5. If G is singular, discard it and repeat from step 1.

Note: sparsity must not be too small or L will be all zeros; the caller
is responsible for choosing a sensible value.
