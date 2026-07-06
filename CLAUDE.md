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
I've removed sub project *dist/multiPrecOperators*.

I've added *README.md* (high level POV, mostly for humans on first contact),
and *AGENTS.md*, which is meant to give a more detailed and technical overview
of the respective status quo of project mpint at any time. This is also the place
where you (Claude Code) might document important changes, but only on my permission.

*CLAUDE.md* itself gives only some data about my code agent setup, but still has 
the paragraphs "What I have done (...)" and "What I want you to do (...)".  
I want you to look at these paragraphs automatically on the start of a new conversation.

I've changed the purpose of project mpint, it no longer builds the MPint implementations
into static libraries. mpint is meant as a source code development environment to develop
and test a *MPint* implementation, i.e. a *MPintSomeVariant.cpp* and perhaps a *MPintSomeVariant.hpp* 
based on one of the existing ones, most likely *MPintWrappedNative* as a starting point.

## What I want you to do in the current conversation
Read *README.md*, *AGENTS.md*, and examine my most recent four commits to
get an overview of the changed project and purpose.
I will give further instructions then.