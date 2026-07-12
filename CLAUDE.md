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
Analysed the `reduTest` profiling regression for `demoGMP` and `demoGMPXX`.

**Observation:** `reduTest` cycles increased significantly after commit `32ec7eb`:
- demoGMPXX: 2,224,750 → 7,041,859 (+216%)
- demoGMP: 3,194,445 → 6,536,646 (+105%)
- All other variants: essentially unchanged.

**Root cause:** The signed/unsigned bug fix changed entry generation in `PosDefState`.
Before the fix, inline-GMP variants (`mpz_init_set_ui`) stored `2^64 − v` (a huge positive) instead of `−v`.
The resulting Gram matrix `L * L^T` had entries on the order of `2^130`, so the minimum lattice vector
norm was astronomically larger than the `shortvecs` bound of 1000. `shortvecs` found no vectors and
returned immediately — giving falsely fast `reduTest` times.

After the fix, entries are correctly small and signed. The Gram matrices are legitimate positive-definite
matrices; `shortvecs` enumerates hundreds of real short vectors per run (as oracle-verified: 13–234 norms
per theta series). This is the correct, intended computation — the increased times reflect real work.

The native/wrapped-native variants were unaffected: their `signed long int` storage had been wrapping
`2^64 − v` back to `−v` in two's complement all along, accidentally producing correct small entries
even before the fix.

## What I have done since our last conversation
Analysed profiling results in *test/prof_output.txt*, updated transcript.txt, CLAUDE.md.

## What I want Claude to do in the upcoming conversation
(to be filled in by user)
