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
Reworked session detection in the transcript processing script and created *transcript_remaining.md*.

Session boundaries now use user-defined markers instead of the Claude Code logo:
- End markers: `/exit` slash command, standalone `#{20,}` hash lines, or banner art.
- Session header is deferred to the first real user prompt after an end marker.
- Fixed banner art embedded inside Write/Edit tool blocks (mid-session reconnects) being
  mistaken for session boundaries.

The script is now parameterised (`process_transcript.py [input [output]]`) so the same
script handles both *transcript.txt* and *transcript_remaining.txt*.

Results: *transcript.md* — 51 sessions, 8586 lines; *transcript_remaining.md* — 1 session, 170 lines.

## What I have done since our last conversation
(nothing yet)

## What I want Claude to do in the upcoming conversation
(nothing specified yet)
