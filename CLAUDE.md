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
Added `#include <cmath>` to `demo/src/exprTest.cpp`.
Filled in the two commented-out assert stubs in `floatconv()` (lines 845/846 and 855/856) for the `DEMO_GMPXX` branch:
`mpz_class` has no `float`/`double` conversion operator, so the conversion goes through `get_d()` (returns `double`).
Assert condition is `std::isinf(f) && f > 0.0f` / `std::isinf(d) && d > 0.0` — confirms specifically positive infinity.
All six `test.sh regr` diffs pass.

## What I have done since our last conversation
Modified some tests in *demo/src/exprTest.cpp* and improved test output, so that diffs
of *demoGMP* and *demoGMPXX* output are more informative.
Updated transcript.txt, CLAUDE.md.

## What I want Claude to do in the upcoming conversation


