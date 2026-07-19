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
Fixed variant order in `test/test.sh`: GMP/GMPOpt had been inserted before WrappedNativePimpl
instead of after it throughout the script. Corrected in all affected locations:
variable declarations, `doRegression` run and diff blocks, `doProf` run commands and awk
table header. Also removed two duplicate entries (one extra run and one extra diff for GMPPimpl)
that were left over from the botched insertion. All 8 regression diffs pass in the correct order.

## What I have done since our last conversation
updated *test/prof_output.txt*, *transcript.txt*, and *CLAUDE.md*

## What I want Claude to do in the upcoming conversation
Now, in the Opt implementation variants the ten binary operators

    [[nodiscard]] friend MPint operator+(MPint lhs, const MPint& rhs) noexcept { return lhs += rhs; }
    [[nodiscard]] friend MPint operator-(MPint lhs, const MPint& rhs) noexcept { return lhs -= rhs; }
    [[nodiscard]] friend MPint operator*(MPint lhs, const MPint& rhs) noexcept { return lhs *= rhs; }
    [[nodiscard]] friend MPint operator/(MPint lhs, const MPint& rhs)           { return lhs /= rhs; }
    [[nodiscard]] friend MPint operator%(MPint lhs, const MPint& rhs)           { return lhs %= rhs; }
    [[nodiscard]] friend MPint operator&(MPint lhs, const MPint& rhs) noexcept { return lhs &= rhs; }
    [[nodiscard]] friend MPint operator|(MPint lhs, const MPint& rhs) noexcept { return lhs |= rhs; }
    [[nodiscard]] friend MPint operator^(MPint lhs, const MPint& rhs) noexcept { return lhs ^= rhs; }
    [[nodiscard]] friend MPint operator<<(MPint lhs, const MPint& rhs) noexcept { return lhs <<= rhs; }
    [[nodiscard]] friend MPint operator>>(MPint lhs, const MPint& rhs) noexcept { return lhs >>= rhs; }

are delegated to their respective compound assignments. to make this work, their *MPint lhs* arguments are always copied.
Since this is a non-pimpl implementation, can the copy operation be avoided in some use cases, e.g. when *lhs" comes from
an rvalue? Or perhaps 
*mpz_add, mpz_sub, mpz_mul, mpz_tdiv_q, mpz_tdiv_r, mpz_and, mpz_ior, mpz_xor, mpz_mul_2exp, mpz_fdiv_q_2exp*
might be used directly instead of delegating?
