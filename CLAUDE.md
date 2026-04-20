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
"c=a+b", whis is extremely error prone, and even harder to read and maintain than
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
Only updated transcript.txt and CLAUDE.md.

## What to do for you right now
GMP comes with a C++ interface similar to MPint, given by header file gmpxx.h.

It seems to promise also "a drop-in replacement for signed long int.
All arithmetic, comparison, bitwise, increment/decrement, and stream
operators are provided so legacy code needs no textual changes."

Try to utilize the GMP installation on this machine (gondwana@debian_trixie)
in the same way, with that header gmpxx.h and the corresponding GMP libs, as with
lipMPGMP and MPintGMP.h.

So I'm asking to create a new build/testing variant called MPintGMPXX with its
own executable bin/demoGMPXX and to integrate it into the existing
test/profiling infrastructure in subdir test.
