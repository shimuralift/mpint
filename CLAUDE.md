# CLAUDE.md

This file, *CLAUDE.md*, is meant to give claude-specific information.  
For a general description of project mpint, suitable for LLM based code agents,
refer to *AGENTS.md*.  
Human readers should also refer to *README.md*.

## Project Overview
Project mpint is an exercise in LLM assisted C++ operator overloading.  
The objective is to provide *class MPint* with a set of operators
which implements an integer with arbitrary precision.

## Claude Versions Used
* Claude Code agent of version 2.1.x by anthropic was used.
* The underlying LLM was Sonett 4.5 - 4.6.
* On a Claude Pro annual subscription in 2026.



## What Claude has done in our last conversation
Fixed Cause A: removed `static_cast<signed long int>(v)` from all four unsigned constructors in `src/MPintGMPPimpl.cpp`; they now route through `MPintImpl(unsigned long int v)` → `mpz_init_set_ui`, giving true unsigned semantics matching `MPintGMP.hpp`.
Changed `basicexpr()` in `demo/src/exprTest.cpp` lines 75, 76, 80 to use positive literals (`22`, `23`, `41`) instead of negative-value casts.
Updated all six `.output.ref` files; all six `test.sh regr` diffs pass.
After the fix `demoGMP` and `demoGMPPimpl` outputs are byte-for-byte identical; remaining GMP/GMPXX differences are solely Cause B (string parser features).
Oracle verification confirmed: `~23 = -24`, `22*6 = 132`, `23*6 = 138`, `41%6 = 5`, `132^11 = 143`, `23^11 = 28`.

## What I have done since our last conversation
Modified some tests in *demo/src/exprTest.cpp* and improved test output, so that diffs
of *demoGMP* and *demoGMPXX* output are more informative.
Updated transcript.txt, CLAUDE.md.

## What I want Claude to do in the upcoming conversation
Look at lines 845/846 and 855/856 in *demo/src/exprTest.cpp*.
How can "GMPXX returns +inf instead of throwing" be assert()ed here?

