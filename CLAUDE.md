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
* Renamed demo variant *GMP* to *GMPPimple* and *WrappedNative* to *WrappedNativePimple* throughout.
* Renamed source files: `src/MPintWrappedNative.cpp` → `src/MPintWrappedNativePimple.cpp` and `src/MPintGMP.cpp` → `src/MPintGMPPimple.cpp` (via `git mv`).
* Renamed test ref files: `test/demoWrappedNative.output.ref` → `test/demoWrappedNativePimple.output.ref` and `test/demoGMP.output.ref` → `test/demoGMPPimple.output.ref`.
* Updated `Makefile`: target variables, build rules, `-DDEMO_WRAPPEDNATIVEPIMPLE`/`-DDEMO_GMPPIMPLE` flags, and source file references.
* Updated `demo/src/demoTypedef.hpp`: `DEMO_WRAPPEDNATIVEPIMPLE` and `DEMO_GMPPIMPLE` macros.
* Updated `test/test.sh`: all variable names and executable/output/ref file paths; widened `doProf()` column for `demoWrappedNativePimple`.
* Updated `AGENTS.md`: new class and executable names throughout, added description of `demoGMPXX` variant, updated variant count from three to four.
* All four `./test/test.sh all` diffs pass.

## What I have done since our last conversation

## What I want Claude to do in the upcoming conversation
