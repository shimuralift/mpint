# CLAUDE.md

This file, *CLAUDE.md*, is meant to give claude-specific information.  
For a general description of project mpint, suitable for LLM based code agents,  
see *AGENTS.md*.  
Human readers should also refer to *README.md*.

## Project Overview
Project mpint is an exercise in LLM assisted C++ operator overloading.  
The objective is to provide *class MPint* with a set of operators which implements an integer  
with arbitrary precision.

## Claude Versions Used
* Claude Code agent of version 2.1.x by anthropic was used.
* The underlying LLM was Sonett 4.5 - 4.6.
* On a Claude Pro annual subscription in 2026.



## What Claude has done in our last conversation
Added `operatorOpt()` regression tests for the rvalue-ref overloads in `include/MPintGMPOpt.hpp`.  

Oracle-based approach: each test block computes the expected result via the lvalue+lvalue path,  
then verifies one or both operands forced to rvalue (via `std::move`) gives an identical result.

Coverage in `demo/src/exprTest.cpp`:
- All 8 binary operators (`+`, `-`, `*`, `/`, `%`, `&`, `|`, `^`) in all three rvalue-operand  
combinations: rv-lhs, rv-rhs, both-rv.
- Int-rhs shifts (`<<`/`>>`) with rv-lhs.
- MPint-rhs shifts in all three value-category combinations, guarded by `#ifndef DEMO_GMPXX`  
(mpz_class does not accept mpz_class shift counts).
- `&&`-qualified unary `+`, `-`, `~` via `MPint(17)` temporaries.
- Left- and right-associative chained expressions.

Wired into `demo/src/demo.cpp` between injTest and detTest at `total[8]`;  
detTest/reduTest shifted to `total[9]`/`total[10]`; `names[11]` updated.  
All 8 regression diffs pass.

## What I have done since our last conversation
I've reviewed *README.md*, *AGENTS.md*, and *CLAUDE.md*

## What I want Claude to do in the upcoming conversation
I want to transform *transcript.txt* into a usable document, transcript.md*, containing my  
prompts and questions, your questions,proposals and answers, and the IDs of the commits  
we have made in chronological order. As a first step, create *transcript.md* from *transcript.txt*  
by stripping out all the proposed (and possibly comitted) diffs you have made. The code changes  
are better explored by a reader using git, gitk, or similar tools.
