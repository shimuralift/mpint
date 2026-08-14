# README.md

This file, **README.md**, is a general description of project mpint, suitable for human readers.  
Technical detail is provided in **AGENTS.md**, for both humans and agents.

## Motivation of Project
mpint is the author's first attempt to use an LLM based code agent for a programming task   
other than "agent, go and write me a web application!".

The idea to use C++ operator overloading to migrate legacy C code from native integers to   
multiprecision arithmetic dates back to the 1990ies, but I've seen only some minimal  
implementations back then, strictly focused on a particular purpose. A more comprehensive  
general solution seemed to require quite some tedious effort when done by a human at that time.

## Overview
Project mpint is an exercise in LLM assisted C++ operator overloading.  
The objective is to provide *class MPint* with a set of operators which implements an integer  
with arbitrary precision.

The use case is modernization of legacy C code containing native integer arithmetic.  
The traditional approach would be to link the old C code with some multiprecision library,  
and rewrite all the arithmetic in terms of the interface provided by the library.  
This would e.g. require to rewrite an expression like  _a*(b+c)_  as *mult(a, add(b, c))*,  
or similar. This is a tedious and error prone process on nontrivial code, and the result  
is much more difficult to read and maintain.

Project mpint has a **Makefile** driven build, with targets *all* (default) and *clean*, but that  
only provides some demo executables of the various *MPint* implementations present in  
directories **src** and **include**. These demo executables are used for regression testing and  
profiling, driven by *test/test.sh*.

A human (or artificial) consumer is meant to either pick one of the existing *MPint*  
implementations, source and/or header, and start their own project with them, possibly code   
agent assisted, or develop their own implementation, using an existing one as a starting point,  
in which case the existing test and profiling framework might be helpful.

## Files and directories at the top level
We have the canonical Markdown files:
- **README.md** (for GitHub or similar)
- **AGENTS.md** (for code agents in general, and human usage)
- **CLAUDE.md** (for specifics of and interaction with the anthropic code agent).

Other files:
- **.gitignore.example** is a suggestion for a *.gitignore* to be user-created.
- **Makefile** provides targets *all* and *clean*, as described above.

Directories:

- **demo**: sources and build artifacts for testing the variants of *class MPint* implementations,  
see *demo/demo.md* for details.
- **docs**: various documentation markdown files, see *docs/docs.md*
- **include**: header files (.hpp) of *class MPint* implementations
- **src**: source files (.cpp) of *class MPint* implementations
- **test**: contains a script *test/test.sh* with options *prof* and *regr* for benchmarking and  
regression testing, respectively. See *test/test.md* for detailed information.
