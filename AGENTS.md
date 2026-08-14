# AGENTS.md

This file, **AGENTS.md**, is a general description of project mpint, suitable for LLM based  
code agents, and humans.  
Claude-specific information, is in **CLAUDE.md**.  
Human readers should also refer to **README.md** for a general overview.

## Project Overview
Project mpint is an exercise in LLM assisted C++ operator overloading.  
The objective is to provide *class MPint*, with a set of operators, which implements an integer  
with arbitrary precision.

The use case is modernization of legacy C code containing native integer arithmetic.  
The traditional approach would be to link the old C code with some multiprecision library,  
and rewrite all the arithmetic in terms of the interface provided by the library. This would e.g.  
require to rewrite an expression like  _a*(b+c)_  as *mult(a, add(b, c))*, or similar. This is  
a tedious and error prone process on nontrivial code, and the result is much more difficult  
to read and maintain.

With class *MPint*, one would only have to declare formerly native integers like *a, b, c*  
as being of type *MPint*, and the overloaded operators work in exactly the same way as the  
operators of the native integer types. So, ideally, no arithmetic expressions or algorithms  
have to be changed. Additionally, *MPint* has constructors, which take a string as argument,  
to compensate for the lack of native integer literals.

Project mpint has a **Makefile** driven build, with targets *all* (default) and *clean*, but that  
only provides some demo executables of the various *MPint* implementations present in directories  
**src** and **include**. These demo executables are used for regression testing and profiling,  
driven by *test/test.sh*.

A human (or artificial) consumer is meant to either pick one of the existing *MPint* implementations,  
header (.hpp) and/or source (.cpp), and start their own project with them, possibly code agent  
assisted, or develop their own implementation, using an existing one as a starting point in which case  
the existing tests and profiling might be helpful.

In subdirectory **demo**, there are sources and eight executable artifacts for  
development/testing/profiling purposes:

- **demoNative**: runs the demo on the native *signed long int* type without using *MPint* at all  
(for baseline comparison).


- **demoGMPXX**: uses *mpz_class* from the GMP C++ interface (*gmpxx.h*) directly via a typedef,  
without going through *class MPint*.


- **demoWrappedNative**: wherein *signed long int* is wrapped in a *class MPint* operator  
implementation (as another baseline for profiling).
- **demoWrappedNativeOpt**: an optimization of *demoWrappedNative* with more operator definitions  
to avoid unnessesary copies of *MPint* instances. It introduces more code and longer  
compile time, but improves runtime performance.
- **demoWrappedNativePimpl**: an implementation of *demoWrappedNative* using a generic, clean  
header file *include/MPintPimpl.hpp*, which does not expose implementation details  
of *class MPint*. It comes with significant runtime performace penalty.


- **demoGMP**: drives the *MPintGMP* wrapper around the GMP C interface.
- **demoGMPOpt**: an optimization of *demoGMP* with more operator definitions  
to avoid unnessesary copies of *MPint* instances. It introduces more code and longer  
compile time, but improves runtime performance.
- **demoGMPPimpl**: an implementation of *demoGMP* using a generic, clean  
header file *include/MPintPimpl.hpp*, which does not expose implementation details  
of *class MPint*. It comes with significant runtime performace penalty.

We have two pimpl-style implementations of *MPint*: **MPintWrappedNativePimpl** which is just  
the *MPint* operators wrapping the native *signed long int* type, and **MPintGMPPimpl** which  
wraps the C interface of the GNU Multiprecision library. These implementations come with a  
rather generic common header file *include/MPintPimpl.hpp* to be included with whatever source  
is to be refurbished. The advantage of it is that implementation details of *class MPint*  
are not exposed via the header files, but that comes with a performance penalty, of course.

There are also four non-pimpl implementations, header file only: **MPintWrappedNative[Opt]** and  
**MPintGMP[Opt]** which are faster, but with less clean interfaces.

In subdirectory **test** there is a bash script *test.sh* which runs all six demo variants  
and compares their outputs to respective reference outputs.  
*test.sh* with option *prof* does some rdtsc based profiling of the demo variants and shows  
a summary of results.


## Development Guidelines
Coding standards and conventions:
* The Compiler is GNU g++ with *-std=c++14* setting. 
* The OS is Debian Linux 13.5.
* Other dependencies are the GNU Multiprecision (GMP) package, GNU make, and bash.

File structure preferences:  
We have this general directory structure:

    demo 
        bin 
        src
    docs
    include
    src
    test

- **demo**: sources and build artifacts for testing the variants of *class MPint* implementations,  
see *demo/demo.md* for details.
- **docs**: various documentation markdown files, see *docs/docs.md*
- **include**: header files (.hpp) of *class MPint* implementations
- **src**: source files (.cpp) of *class MPint* implementations
- **test**: contains a script *test/test.sh* with options *prof* and *regr* for benchmarking and  
regression testing, respectively. See *test/test.md* for detailed information.

Testing approaches:
simple stdout/stderr based regression test, driven by *test/test.sh regr*, see below.

Profiling/Benchmarking:
driven by *test/test.sh prof*, see below


## Important Commands
Build commands:  
**make all**  
**make clean**

Test commands:  
simple stdout/stderr based regression test:  
**cd test; ./test.sh regr**

Profiling/Benchmarking:  
**cd test; ./test.sh prof**
