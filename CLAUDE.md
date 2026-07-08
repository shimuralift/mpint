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
* Renamed demo variant *GMPPimple* to *GMPPimpl* and *WrappedNativePimple* to *WrappedNativePimpl* throughout.
* Renamed source files: `src/MPintWrappedNativePimple.cpp` → `src/MPintWrappedNativePimpl.cpp` and `src/MPintGMPPimple.cpp` → `src/MPintGMPPimpl.cpp` (via `git mv`).
* Renamed test ref files: `test/demoWrappedNativePimple.output.ref` → `test/demoWrappedNativePimpl.output.ref` and `test/demoGMPPimple.output.ref` → `test/demoGMPPimpl.output.ref`.
* Updated `Makefile`: target variables, build rules, `-DDEMO_WRAPPEDNATIVEPIMPL`/`-DDEMO_GMPPIMPL` flags, and source file references.
* Updated `demo/src/demoTypedef.hpp`: `DEMO_WRAPPEDNATIVEPIMPL` and `DEMO_GMPPIMPL` macros.
* Updated `test/test.sh`: all variable names and executable/output/ref file paths.
* Updated `AGENTS.md`: new class and executable names throughout.
* Updated `.gitignore.example` and copied it over `.gitignore`.
* All four `./test/test.sh all` diffs pass.

## What I have done since our last conversation

## What I want Claude to do in the upcoming conversation
