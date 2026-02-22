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
I've introduced another test, which computes determinants of integral
square matrices. There are three methods used: Dodgson's method,
Gaussian elimination using integers only, and for reference, Gaussian elimination
using floating point numbers.
I know from previous tinkering (not legally available to you)
that Integral Gauss comes to its limits when running on signed long int
in one of the examples, possibly due to int overflow.
But that problem will go away when we have MPint use real multi precision
integers, like GMP.

## What to do for you right now
Right now, the det example does not compile, because there's no conversion
from MPint to double. Please add that to MPint in a graceful, human readable and
maintainable fashion.
