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
Testing approaches: no prefs so far, tbd later

## Important Commands
Build commands: make
Test commands: simple stdout/stderr based regression test: cd test; ./test.sh all
Benchmarking: cd test; ./test.sh prof

## What I've done in the meantime
Nothing particular, updated transcript.txt and some minor changes.

## What to do for you right now
Please remove the MPintMyOwn variant, i.e. the .cpp, .hpp files and everything in the
Makefile and subdir test that is related to it.
