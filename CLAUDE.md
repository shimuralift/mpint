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
Created *transcript.md* from *transcript.txt* by stripping code diffs and tool noise.

A Python processing script was written to:
- Strip numbered diff lines (Write/Edit/Update/Read tool content), timing lines, session banners,
  `ctrl+o` annotations, `✻` spinner lines, `▎` notifications, `※ recap:` annotations,
  horizontal rules, and slash-command responses.
- Keep user prompts (formatted as `**>** ...`), my conversational text, bash output
  (including commit IDs formatted as `` **Commit `sha`**: message ``), and tool summaries.
- Collapse session banners into `## Session N` headers.
- Collapse consecutive `---` separators.

Result: 8609 lines from 17782 (52% reduction). Script retained in the session scratchpad
for reuse when *transcript.txt* is extended.

## What I have done since our last conversation
(nothing yet)

## What I want Claude to do in the upcoming conversation
(nothing specified yet)
