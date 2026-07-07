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

## What I have done since our last conversation
I've updated *transcript.txt* and made a minor cosmetic change to *test/test.sh*.
I've also updated *CLAUDE.md*.

## What Claude has done since our last conversation
* Reviewed `MPint` string constructors in both backends for injection vulnerabilities.
* Fixed `parse_str` in `src/MPintWrappedNative.cpp`: rejects invalid characters, validates each digit against the actual base, rejects "0x"/"0b" with no following digits, and rejects empty/sign-only inputs. Previously `"abc"` silently yielded 1122 (treating a/b/c as hex digits in base-10 context).
* Fixed `mpz_set_mpint_str` in `src/MPintGMP.cpp`: now handles 0x/0X prefix explicitly instead of relying on GMP auto-detect (which accepted bare "0x" as valid), and checks the return value of `mpz_set_str`, throwing `std::invalid_argument` on failure.
* Fixed `operator>>` in both backends to preserve the existing value on parse failure and set `failbit` (the old delegating form could zero the variable on failure per C++ standard).
* Added `injTest()` to `demo/src/exprTest.cpp` and `demo/src/exprTest.hpp`; called from `demo/src/demo.cpp` between `missingexpr` and `detTest`. Tests valid edge cases ("0", "-0", "+0x0"), rejects a range of malformed strings, and verifies that `operator>>` sets `failbit` and leaves the value unchanged on bad input.
* Updated regression reference files `test/demoNative.output.ref`, `test/demoWrappedNative.output.ref`, `test/demoGMP.output.ref`; all three diffs pass.
* Noted that clangd IDE diagnostics (false positives from missing `-DDEMO_*`/`-Iinclude` flags) can be fixed by running `bear -- make` to generate `compile_commands.json`.

## What I want you to do in the upcoming conversation
The MPint(...) implementations have ctors from various other types,
from the native integers, and from strings. Make sure that they don"t
enable injection attacks using maliciously crafted arguments.
Also review *operator>>* with respect to that.
Add a new section/function to *demo/src/exprtest.cpp* and *.hpp*,
to the *test/test.sh* script, and update the regression test reference
files in *test*.
