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
* Created `demo/bin/demoGMPXX`: a new demo variant using `mpz_class` from `gmpxx.h` directly (no `class MPint`) via `typedef mpz_class MPint` in `demo/src/demoTypedef.hpp`.
* Inserted `DEMO_GMPXX` in the correct position (after `DEMO_NATIVE`) in `demoTypedef.hpp`, `Makefile`, and `test/test.sh`, giving the order: Native → GMPXX → WrappedNative → GMP throughout.
* Added templated conversion helpers (`mpint_to_d`, `mpint_to_f`, `mpint_to_ld`, `mpint_to_i`) to `demoTypedef.hpp` to abstract over `mpz_class`'s explicit `.get_d()`/`.get_si()` API and its expression-template arithmetic results.
* Fixed all compile-time incompatibilities in `demo/src/exprTest.cpp`, `demo/src/redu.cpp`, and `demo/src/demoUtils.cpp`: shift-by-MPint (`<<=`/`>>=` require `mp_bitcnt_t`), implicit cast operators (`static_cast<long>` etc.), and ambiguous `long long` construction.
* Fixed runtime incompatibilities in `exprTest.cpp`: guarded string-constructor calls that use `+` prefix (mpz_class rejects it), single-quote digit separators (mpz_class doesn't strip them), and the float/double overflow-throw tests (mpz_class returns infinity instead). Also guarded `injTest()` for `"+0x0"` (throws for mpz_class) and `"0x"`/`"0b"` (accepted as 0 by mpz_class, not rejected).
* Updated `test/test.sh` `doProf()` to a 4-column table; added `demoGMPXX` to `doAll()`.
* Generated `test/demoGMPXX.output.ref`; all four `./test/test.sh all` diffs pass.

## What I have done since our last conversation
I've updated *transcript.txt*, *CLAUDE.md*, *.gitignore.example*, and *test/prof_output.txt*.

## What I want Claude to do in the upcoming conversation
Rename demo variant *GMP* to *GMPPimple*, and *WrappedNative* to *WrappedNativePimple*.
Do that in *Makefile*, *demo/src/demoTypedef.hpp*, and *test/test.sh*. Also update
*AGENTS.md* with respect to this name change and to the introduction of variant *GMPXX*.
