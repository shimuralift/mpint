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

## What I want you to do in the upcoming conversation
The MPint(...) implementations have ctors from various other types,
from the native integers, and from strings. Make sure that they don"t
enable injection attacks using maliciously crafted arguments.
Also review *operator>>* with respect to that.
Add a new section/function to *demo/src/exprtest.cpp* and *.hpp*,
to the *test/test.sh* script, and update the regression test reference
files in *test*.
