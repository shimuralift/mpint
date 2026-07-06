#pragma once


#if defined DEMO_NATIVE
    typedef signed long int MPint;
#elif defined DEMO_WRAPPEDNATIVE
    #include "MPint.hpp"
#elif defined DEMO_GMP
    #include "MPint.hpp"
    #define DEMO_ARBPREC
#else
    #error No MPint implementation selected, cf demoTypedef.hpp and Makefile.
#endif
