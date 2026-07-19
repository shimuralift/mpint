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
Introduced two new variants *MPintWrappedNativeOpt* and *MPintGMPOpt* as exact copies of their
non-Opt counterparts, ready for performance optimisation experiments.

Changes across the repo (committed as one commit):
- `include/MPintWrappedNativeOpt.hpp` — copy of `MPintWrappedNative.hpp`
- `include/MPintGMPOpt.hpp` — copy of `MPintGMP.hpp`
- `demo/src/demoTypedef.hpp` — two new `#elif` branches in variant order: WrappedNative, **WrappedNativeOpt**, WrappedNativePimpl, GMP, **GMPOpt**, GMPPimpl
- `Makefile` — two new header vars, targets, test-output vars, and build rules in the same order
- `test/test.sh` — 8-variant regression (run + diff) and 8-column profiling table, same order
- `test/demoWrappedNativeOpt.output.ref` and `test/demoGMPOpt.output.ref` — generated; outputs identical to the corresponding non-Opt refs; all 8 regression diffs pass
- `.gitignore.example` — two new `.output` entries added and entry order aligned with variant order

## What I have done since our last conversation
(to be filled in by user)

## What I want Claude to do in the upcoming conversation
(to be filled in by user)
