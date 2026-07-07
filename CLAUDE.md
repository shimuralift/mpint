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
I've updated *transcript.txt* and made a minor cosmetic change to *Makefile*.
I've also updated *CLAUDE.md*:  
Now, there's a new paragraph "What Claude has done (...)".  
I want you to update that with a summary of your activities after a Claude Code session.

## What Claude has done since our last conversation
- Modified *test/test.sh*: factored out `DRY_RUN_PREFIX` constant, updated `runCmd()` to use it,
  routed the three profiling executable calls in `doProf()` through `runCmd()`, and replaced the
  early dry-return with a proper dry guard + echo before the post-processing block.
- Added a `SessionStart` hook to *.claude/settings.local.json* that injects *CLAUDE.md* as
  `additionalContext` at the start of every session.
- Saved memory entries to auto-read CLAUDE.md at session start and auto-update it before commits.

## What I want you to do in the upcoming conversation
*test/test.sh* has an optional argument *dry* which only prints the shell command without
actually executing them.  
With *./test.sh prof dry* this echoes only
"DRY: would run <some executables here> with -prof and display side-by-side".
I want you to run the commands in lines 118, 120, and 122 through function *runCmd()*,
which already respects the *dry* option, instead of running them directly.
Please don"t do that for output post-processing and table generation, but echo
a line conforming to what *runCmd()* does in the *dry* case, but without quoting all
these commands. Like
"############################## DRY RUN : <post processing results and printing a summarizing table on stdout>
Factor out ""############################## DRY RUN : " as a string constant to be used in both *runCmd()*
and the echo mentioned above.
