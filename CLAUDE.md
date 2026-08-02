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
Rewrote the transcript processing script (scratchpad/process_transcript.py) with major formatting changes:
- User prompts now right-aligned starting at column 100, wrapped before column 200 with two-space line breaks
- Claude responses wrapped at column 99 with two-space line breaks
- Commit lines formatted as **[branch sha]** message on their own line
- No italics, no tool headers, no compiler/git output, no trivial file-op lines
- Added IN_OLD_CODE state to handle old-format (non-indented) tool output from sessions 25-30
- Extended look-ahead in IN_CODE/IN_BASH to skip timing and separator lines, preventing premature state exit
- Expanded RE_FILEOP_LINE and RE_FILE_OP to catch more tool-summary patterns
- Result: transcript.md 51 sessions, 3430 lines, 0 lines over 200 chars
- Regenerated transcript.md and transcript_remaining.md

## What I have done since our last conversation
(nothing yet)

## What I want Claude to do in the upcoming conversation
(nothing yet)
