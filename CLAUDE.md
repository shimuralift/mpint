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
(nothing yet)

## What I want Claude to do in the upcoming conversation
There are some legal questions, regarding IP ownership and licensing.  
First of all: I do not intend to publish any of your responses. I'm not a lawyer, hence  
I'm not entitled to give legal advice to anyone, and certainly not publicly.  
So I have a strong disincentive to publish your answers.  
I might publish this prompt, though.


Questions come in two sections, general questions first,  
and questions regarding project mpint specifically second.  
Give publicly available references to your responses. I'm interested in the global situation,  
but also in the particular ramifications for someone - or some entity - based in germany.

### General legal questions
1. It is publicly believed - quite plausibly - that any of the major commercial LLM based  
code agents have been trained on licensed open - or closed - source code which is publicly  
available on the WWW, e.g. on GitHub.  
Whenever a code agent generates code, how do the licenses/patents/trade secrets on the training  
data carry over to the generated code?  
What is the current (8/2026) status quo, and how might the question be  
resolved in a court case, if some entity sued?
2. When one instructs a code agent to modify licensed source code - open or not - is one entitled to  
attach the original license to the modified code? Again, what's the status quo,  
and what are potential court rulings on that?
3. It's conceivable that only the prompts given to an agent are sufficient to arrive at  
agent-generated code which represents a value then. Note that this question is self-referential  
relative to this prompt. What's the status quo and what are your - or publicly available -  
references regarding this aspect?
4. If one works with not otherwise protected trade secrets in software development, how risky  
is it to expose them - "the crown jewels" - to a code agent?

### Legal questions specifically related to project mpint
1. When one modernizes old GPLed code to become multi-precision-integer capable using the results  
of project mpint, can the modernized code be put under the GPL as well?
2. What is the situation with other types of licenses, or public domain code?
3. Could I publish the project mpint git repository as being in the public domain?  
How could I protect myself from someone else who tries to claim code ownership, and then even  
effectively lock me out from project mpint?
