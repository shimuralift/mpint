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

## What I've done in the meantime
The source files src/MPint.cpp, src/MPint.hpp have been duplicated, unmodified, to
src/MPintMyOwn.cpp, MPintMyOwn.hpp and to src/MPintGMP.cpp, src/MPintGMP.hpp.
Accordingly, the Makefile was extended to produce libraries bin/libMP.a,
bin/libMPMyOwn.a, bin/libMPGMP.a and three executables bin/demo, bin/demoMyOwn, bin/demoGMP.
These duplications are worrisome, of course, but they are only temporary for some explorative
testing and profiling.

A simple regression test script, to be run in subdir test, has been added.
It runs the demo executables and captures their resp. outputs (stderr and stdout
combined) to files test/demo*.output. These files will then be diffed to
test/demo.output.ref.

## What to do for you right now
Although the three implementation variants do not differ yet, and have their
implementation based on the native long int, implement some high-res profiling, prefereably
not in seconds but rather in cpu cycles, like rdtsc in the good old days.
Please stay platform/os/runtime dependent for now.
Avoid or at least minimize dependencies.
Implement timer starts/stops around the individual function calls in main, i.e.
claude_main(), basicexpr(), moreexpr(), extraexpr(), detTest().
Implement report generation on stdout, human readable, appended to stdout output
which already exists, but only, when command line option -prof is given to the respective demo*
executable, so that the output based regression test does not break.
