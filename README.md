# README.md

This file, *README.md*, is a general description of project mpint, suitable for human readers.  
Technical detail is provided in *AGENTS.md*, for both humans and agents.

## Project Overview
Project mpint is an exercise in LLM assisted C++ operator overloading.  
The objective is to provide *class MPint* with a set of operators
which implements an integer with arbitrary precision.

The use case is modernization of legacy C code containing native
integer arithmetic. The traditional approach would be to link the
old C code with some multiprecision library, and rewrite all the
arithmetic in terms of the interface provided by the library. This
would e.g. require to rewrite an expression like  _a*(b+c)_  as
*mult(a, add(b, c))*, or similar. This is a tedious and error prone
process on nontrivial code, and the result is much more difficult
to read and maintain.

## Motivation of Project
mpint is the author's first attempt to
use an LLM based code agent for a programming task other than "agent, go
and write me a web application!".  
The idea to use C++ operator overloading to migrate legacy C code
from native integers to multiprecision arithmetic dates back to the
1990ies, but I've seen only some minimal implementations back then,
strictly focused on a particular purpose. A more comprehensive general
solution seemed to require quite some tedious effort when done by a human.
