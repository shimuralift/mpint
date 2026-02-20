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
Build commands: come up with a sensible Makefile
Test commands: testing tbd later

## What I've done in the meantime
No significant changes from my side, no commits.

## What to do for you right now
What haunts me for a long time now is the question
"What are header files, e.g. *.hpp are actually good for?"
In (well written and maintained) C, headers contained only
function declarations, typedefs, important constants, etc.
Libraries used in development come with such headers,
to include in a C project which use that library.
They were meant not to expose any of the inner workings of the library.
Apparently that's different in C++. When we look at e.g. MPint.cpp and
MPint.hpp, MPint.hpp exposes an awful lot of internals of 
class MPint, library or not.
Question: is there a better practice, that's commonly recognized?
Note that we are in C++14 here, so modules are not available.
