# pragma once

#ifdef DEMO_NATIVE
typedef signed long int Long;
#else
#include "MPint.hpp"
typedef MPint Long;
#endif


/* does lll-reduction to <dim>-sized Long-matrix <gr> (should be symmetric and >0) .
   The algorithm is implemented as suggested in H.Cohen, A Course In Computational
   Algebraic Number Theory, 2nd ed., Springer 1995.

   <ge> should point to a previously malloced <dim>-sized double-array and contains
   after termination the norms of the Gram-Schmidt-basisvectors corresponding to the
   reduced <gr> (cf. Cohen, p81).

   <mo> should point to a previously malloced <dim>-sized double-matrix and its sub=
   diagonal triangle contains after termination the Gram-Schmidt-coefficients be=
   Longing to <ge> (cf. Cohen, p81).

   The function may be invoked with (Long **)NULL for <ba> or <invba> , otherwise
   they should point to previously malloced <dim>-sized Long-matrices, which are
   typically set as indentity-matrices, in which case the following holds :
   gr_after = ba*gr_before*transpose(ba) and
   gr_before = invba*gr_after*transpose(invba). */
extern int triple_l(Long ** gr, Long ** ba, Long ** invba, double * ge, double ** mo, int dim);

/* does lll-reduction with deep insertionsto <dim>-sized Long-matrix <gr>
   (should be symmetric and >0).
   The algorithm is implemented as suggested in H.Cohen, A Course In Computational
   Algebraic Number Theory, 2nd ed., Springer 1995.

   <ge> should point to a previously malloced <dim>-sized double-array and contains
   after termination the norms of the Gram-Schmidt-basisvectors corresponding to the
   reduced <gr> (cf. Cohen, p81).

   <mo> should point to a previously malloced <dim>-sized double-matrix and its sub=
   diagonal triangle contains after termination the Gram-Schmidt-coefficients be=
   Longing to <ge> (cf. Cohen, p81).

   The function may be invoked with (Long **)NULL for <ba> or <invba> , otherwise
   they should point to previously malloced <dim>-sized Long-matrices, which are
   typically set as indentity-matrices, in which case the following holds:
   gr_after = ba*gr_before*transpose(ba) and
   gr_before = invba*gr_after*transpose(invba). */
extern int deep_triple_l(Long ** gr, Long ** ba, Long ** invba, double * ge, double ** mo, int dim);

extern int shortvecs_count(double * ge, double ** mo, Long len, int dim);

extern void shortvecs(double * ge, double ** mo, Long len, Long ** vecs, int dim);
