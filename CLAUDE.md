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
(nothing yet)

## What I have done since our last conversation
I've updated *transcript_remaining.txt* and *CLAUDE.md*. I've introduced *transcript_sample.txt*

## What I want Claude to do in the upcoming conversation
transcript.md still is not easy to read. Some  rework is needed:
- no italics anywhere.
- no compiler or git command lines or output. as far I can see, you summarized all that quite nicely anyway.
- no lines about trivial file operations, like "Read/Updated/Wrote SomeFile"
- *transcript.md*, i.e. the source code of it for simplicity, should have a maximal width of 200 characters.
- my prompts should start at column 100 in verbatim style, hence should be broken into multi line before column 200.
- your responses should start at column 1 and are broken up before column 100
- for the necessary line breaks use two blanks at the end of the line.
- where you've made a commit, just format it on its own line in bold, like  
**[somebranch a99b4711]** this is the first line of the commit message

I've made up a sample of what I want to have: *transcript_sample.md*.
