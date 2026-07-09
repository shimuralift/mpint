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
* Created `include/MPintWrappedNative.hpp`: inline header-only `class MPint` wrapping `signed long int` directly (no pimpl). All operators inline; copy/move/destructor defaulted.
* Created `include/MPintGMP.hpp`: inline header-only `class MPint` wrapping `mpz_t` directly (no pimpl). All operators inline; mpz lifecycle managed in constructors/destructor/copy/move.
* Both files were seeded from the corresponding pimpl `.cpp` files via `cp` + `git add`.
* Added `DEMO_WRAPPEDNATIVE` and `DEMO_GMP` branches to `demo/src/demoTypedef.hpp`.
* Added `TARGET_WRAPPEDNATIVE` and `TARGET_GMP` build rules to `Makefile` (header-only, no extra `.cpp`). Variant order: Native → GMPXX → WrappedNative → GMP → WrappedNativePimpl → GMPPimpl.
* Updated `test/test.sh`: added both new variants to `doRegression()` and expanded `doProf()` to a 6-column table.
* Generated `test/demoWrappedNative.output.ref` and `test/demoGMP.output.ref`; all six `./test/test.sh regr` diffs pass.

## What I have done since our last conversation
updated transcript.txt, CLAUDE.md, .gitignore.example, and test/prof_output.txt

## What I want Claude to do in the upcoming conversation
In directory test, after *test.sh regr*, why are *demoGMP.output*, *demoGMPPimpl.output*, and *demoGMPXX.output* different from each other?
Why does *demoNative.output* differ from *demoWrappedNative.output*?
