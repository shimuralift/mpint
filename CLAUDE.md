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
Between the previous and this session I made four commits (most recent first):

- *2be3304* — project no longer builds static libraries; directory structure
  adapted: *lib/src/* → *src/*, *lib/include/* → *include/*, *lib/bin/* removed;
  Makefile and *test/test.sh* updated accordingly. *AGENTS.md*, *README.md*,
  *CLAUDE.md* updated to reflect the new purpose (source development environment).
- *61c31f0* — removed sub project *dist/multiPrecOperators* entirely.
- *0dbfb92* — added *README.md* (high-level, for humans) and *AGENTS.md*
  (technical reference for agents); content moved out of *CLAUDE.md*.
- *0073a2c* — reorganised *CLAUDE.md*; minor Makefile comment; updated
  *transcript.txt*.

## What I want you to do in the current conversation
This session was orientation only. I read *README.md*, *AGENTS.md*, and the
four most recent commits as instructed. No code changes were made.

No outstanding tasks. Await further instructions.