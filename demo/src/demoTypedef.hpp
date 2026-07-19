#pragma once


#if defined DEMO_NATIVE
    typedef signed long int MPint;
#elif defined DEMO_GMPXX
    #include <gmpxx.h>
    typedef mpz_class MPint;
    #define DEMO_ARBPREC
#elif defined DEMO_WRAPPEDNATIVE
    #include "MPintWrappedNative.hpp"
#elif defined DEMO_WRAPPEDNATIVEOPT
    #include "MPintWrappedNativeOpt.hpp"
#elif defined DEMO_WRAPPEDNATIVEPIMPL
    #include "MPintPimpl.hpp"
#elif defined DEMO_GMP
    #include "MPintGMP.hpp"
    #define DEMO_ARBPREC
#elif defined DEMO_GMPOPT
    #include "MPintGMPOpt.hpp"
    #define DEMO_ARBPREC
#elif defined DEMO_GMPPIMPL
    #include "MPintPimpl.hpp"
    #define DEMO_ARBPREC
#else
    #error No MPint implementation selected, cf demoTypedef.hpp and Makefile.
#endif

// Conversion helpers: abstract over backend differences.
// mpz_class (DEMO_GMPXX) exposes .get_d()/.get_si() instead of implicit casts;
// its arithmetic returns expression-template proxies, so helpers are templated.
#ifdef DEMO_GMPXX
  template<class E> inline double      mpint_to_d (const E& v) { return mpz_class(v).get_d(); }
  template<class E> inline float       mpint_to_f (const E& v) { return static_cast<float>(mpz_class(v).get_d()); }
  template<class E> inline long double mpint_to_ld(const E& v) { return static_cast<long double>(mpz_class(v).get_d()); }
  template<class E> inline int         mpint_to_i (const E& v) { return static_cast<int>(mpz_class(v).get_si()); }
#else
  inline double      mpint_to_d (const MPint& v) { return static_cast<double>(v); }
  inline float       mpint_to_f (const MPint& v) { return static_cast<float>(v); }
  inline long double mpint_to_ld(const MPint& v) { return static_cast<long double>(v); }
  inline int         mpint_to_i (const MPint& v) { return static_cast<int>(v); }
#endif
