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
Optimised `include/MPintGMPOpt.hpp` to avoid unnecessary GMP limb-array copies in operators.

Binary operators: replaced the by-value-lhs delegation pattern with a full set of
`const MPint& / MPint&&` overload combinations per operator (lhs-lvalue, lhs-rvalue,
rhs-rvalue, both-rvalue). The lvalue-lhs overload writes directly into a fresh result
via the GMP function, skipping the copy of lhs. The rvalue overloads modify in place
and return via `std::move`. The both-rvalue overload resolves the overload ambiguity
that would otherwise arise. The shift-with-MPint-rhs rvalue overloads extract the
shift count into a local before overwriting `rhs.mVal`.

Unary operators: added `&&`-qualified overloads for `operator+`, `operator-`,
`operator~` that modify `*this` in place (via `mpz_neg`/`mpz_com`) and return
`std::move(*this)`, avoiding a fresh allocation when the operand is a temporary.

Added `#include <utility>` for `std::move`. All 8 regression diffs pass.

## What I have done since our last conversation
updated *test/prof_output.txt*, *transcript.txt*, and *CLAUDE.md*

## What I want Claude to do in the upcoming conversation
Now i need regression tests for the optimisations in Opt in the last conversation.
Full coverage, and to be checked by an oracle. Implement them in *demo/exprTest.cpp*
in a function *operatorOpt()*. in *demo/demo.cpp* and *test/test.sh*, including
its output for *regr* and the *prof* table, it should go between *injTest* and *detTest*.
