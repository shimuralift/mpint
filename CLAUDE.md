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
Purely analytical session — no code changes. Explained why the six demo output files differ after `test.sh regr`:

**demoGMP vs demoGMPPimpl vs demoGMPXX:**
* **Unsigned long constructor semantics:** `MPintGMPPimpl.cpp` line 69 casts `unsigned long` to `signed long` before storage (`mpz_init_set_si`), so `(unsigned long)(-23)` → -23. `MPintGMP.hpp` calls `mpz_init_set_ui` directly → 18446744073709551593. `mpz_class` (GMPXX) likewise stores the full unsigned value. This cascades into `detTest`/`reduTest`: GMP/GMPXX build matrices with huge positive entries → empty theta series.
* **String constructor features:** `MPintGMP.hpp` and `MPintGMPPimpl.cpp` share a custom `set_mpint_str` supporting `'` digit separators, `+` prefix for non-decimal bases, and float/double overflow detection. `mpz_class` lacks these; demo guards them with `#ifndef DEMO_GMPXX` and `#if defined(DEMO_ARBPREC) && !defined(DEMO_GMPXX)`.

**demoNative vs demoWrappedNative:**
* `DEMO_NATIVE` is defined only for Native (bare `signed long int` typedef), causing two blocks to be skipped: `injTest()` `#ifndef DEMO_NATIVE` (string ctor validity tests + value-preserving `operator>>` test) and `missingexpr()` `#if !defined(DEMO_NATIVE) && !defined(DEMO_GMPXX)` (`+` prefix non-decimal strings).
* `demoWrappedNative` does not define `DEMO_ARBPREC`, so float/double overflow tests do not run there either.

## What I have done since our last conversation
updated transcript.txt, CLAUDE.md, .gitignore.example, and test/prof_output.txt

## What I want Claude to do in the upcoming conversation

