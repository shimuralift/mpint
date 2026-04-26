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
In the Makefile a new executable variant MPintNative has been
implemented. It introduces a preprocessor flag DEMO_NATIVE,
which, when turned on, produces a demoNative executable which
does not utilize the MPint header/library at all.
Instead it typedefs native type signed long int to the types
MPint/Bint.
This should serve for comparison of native integer performance
versus native integer wrapped with operator overloading.


## What to do for you right now
There are various minor compile errors left of course.
One category is initialization/const issues with the native variant.
The other is construction of integers from strings. For the latter just
replace the respective test functions with their equivalents in ordinary
native int literals. Use preprocessor distinctions like near the start of
demo.cpp to implement this and, if necessary, to resolve the former category
i have mentioned.

