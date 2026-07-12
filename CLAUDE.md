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
Fixed signed/unsigned bug in `demo/src/demoUtils.cpp` (both `SQState` and `PosDefState` constructors):
`sgn * (randnum % entryMagnitude)` promoted `int sgn` to `unsigned long int`, so -1 became 2^64-1 and the product was 2^64-v instead of -v.
Fix: assign `randnum % entryMagnitude` to `MPint` first, then `if (sgn < 0) entry = -entry`.
This bug was previously masked by the old `MPintGMPPimpl` unsigned ctor (which cast unsigned long back to signed long, accidentally restoring the sign).
Updated all six `.output.ref` files; all six `test.sh regr` diffs pass.

Then verified all results across all six demo variants using PARI/gp (det/theta) and Python (exprTest) as oracles.
A Python parser (`gen_verify.py` in scratchpad) extracts matrices/dets/theta series and emits PARI/gp; a second script (`check_expr.py`) verifies arithmetic using Python's arbitrary-precision integers with C truncated-division semantics.

**exprTest oracle (Python):**
- demoGMP, demoGMPPimpl, demoGMPXX: all checks passed.
- demoWrappedNative, demoWrappedNativePimpl, demoNative: one expected fail — `23^19` overflows `signed long int` (labeled as such in test output).
- All other arithmetic (unary/binary ops, shifts, comparisons, compound assignments, negative truncated div/mod) passes in every variant.

**det/theta oracle (PARI/gp):**
- All 32 Dodgson determinants correct in all six variants (PARI/gp `matdet`).
- All 16 theta series correct in all six variants (PARI/gp `qfminim`), 13–234 norms per run.
- Known limitation (not a new bug): GaussInt overflows `signed long int` intermediate products for two non-singular 4×4 det runs, giving wrong GaussInt output in demoNative/WrappedNative/WrappedNativePimpl. Side-effect: `isSingular()` uses GaussInt internally; overflow changes `PosDefState` retry-loop random state for dim≥4, so dim=5 theta matrices differ between GMP and native variants — but each variant's theta series is oracle-verified correct for its own matrices.

## What I have done since our last conversation
Updated transcript.txt, CLAUDE.md.

## What I want Claude to do in the upcoming conversation

