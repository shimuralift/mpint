#include <float.h>
#include <iostream>
#include <stdlib.h>


#include "demoTypedef.hpp"
#include "demoUtils.hpp"

typedef MPint Bint;


static Bint gcd(const Bint a, const Bint b) { // @suppress("No return")
  Bint d1;
  Bint d2;
  if (a == 0 && b == 0) {
    return 0;
  }
  if (b == 0) {
    return a;
  }
  d1 = a;
  d2 = b;
  for (;;) {
    d1 = d1 % d2;
    if (d1 == 0) {
      return d2;
    }
    d2 = d2 % d1;
    if (d2 == 0) {
      return d1;
    }
  }
}

static void computeDetDodgson(const unsigned int dim, Bint **matrix,
                              unsigned int *perm, Bint *det) {
  Bint c = 1;
  Bint s = 1;
  for (unsigned int k = 0; k < dim - 1; k++) {
    Bint p = matrix[perm[k]][k];
    if (p == 0) {
      unsigned int ridx;
      for (ridx = k + 1; ridx < dim; ridx++) {
        if (matrix[perm[ridx]][k] != 0) {
          break;
        }
      }
      if (ridx == dim) {
        *det = 0;
        return;
      }
      unsigned int swap = perm[ridx];
      perm[ridx] = perm[k];
      perm[k] = swap;
      s *= -1;
      p = matrix[perm[k]][k];
    }
    for (unsigned int ridx = k + 1; ridx < dim; ridx++) {
      for (unsigned int cidx = k + 1; cidx < dim; cidx++) {
        Bint m1 = p * matrix[perm[ridx]][cidx];
        Bint m2 = matrix[perm[ridx]][k] * matrix[perm[k]][cidx];
        matrix[perm[ridx]][cidx] = (m1 - m2) / c;
      }
    }
    c = p;
  }
  *det = s * matrix[perm[dim - 1]][dim - 1];
  return;
}

static void computeDetGaussInt(const unsigned int dim, Bint **matrix,
                               unsigned int *perm, Bint *det) {
  Bint denominator = 1;
  *det = 1;
  for (unsigned int j = 0; j < dim; j++) {
    unsigned int ridx;
    for (ridx = j; ridx < dim; ridx++) {
      if (matrix[perm[ridx]][j] != 0) {
        break;
      }
    }
    if (ridx == dim) {
      *det = 0;
      return;
    }
    if (ridx > j) {
      unsigned int swap = perm[ridx];
      perm[ridx] = perm[j];
      perm[j] = swap;
      *det *= -1;
    }
    *det *= matrix[perm[j]][j];
    for (ridx = j + 1; ridx < dim; ridx++) {
      Bint ggt = 0;
      ggt = gcd(denominator, *det);
      if (ggt > 1 || ggt < -1) {
        *det /= ggt;
        denominator /= ggt;
      }
      if (matrix[perm[ridx]][j] != 0) {
        denominator *= matrix[perm[j]][j];
        for (unsigned int cidx = j + 1; cidx < dim; cidx++) {
          matrix[perm[ridx]][cidx] =
              (matrix[perm[j]][j] * matrix[perm[ridx]][cidx] -
               matrix[perm[j]][cidx] * matrix[perm[ridx]][j]);
        }
      }
    }
  }
  *det /= denominator;
  return;
}

static void computeDetGaussFloat(const unsigned int dim, long double **matrix,
                                 unsigned int *perm, long double *det) {
  long double EPS = LDBL_EPSILON;
  *det = 1.0L;
  for (unsigned int j = 0; j < dim; j++) {
    unsigned int ridx;
    for (ridx = j; ridx < dim; ridx++) {
      if (matrix[perm[ridx]][j] > EPS || matrix[perm[ridx]][j] < -EPS) {
        break;
      }
    }
    if (ridx == dim) {
      *det = 0.0L;
      return;
    }
    if (ridx > j) {
      unsigned int swap = perm[ridx];
      perm[ridx] = perm[j];
      perm[j] = swap;
      *det *= -1.0L;
    }
    *det *= matrix[perm[j]][j];
    long double inv = 1.0L / matrix[perm[j]][j];
    for (ridx = j + 1; ridx < dim; ridx++) {
      if (matrix[perm[ridx]][j] > EPS || matrix[perm[ridx]][j] < -EPS) {
        for (unsigned int cidx = j + 1; cidx < dim; cidx++) {
          matrix[perm[ridx]][cidx] =
              matrix[perm[ridx]][cidx] -
              matrix[perm[j]][cidx] * matrix[perm[ridx]][j] * inv;
        }
      }
    }
  }
  return;
}

bool isSingular(const unsigned int dim, Bint** matrix, unsigned int* perm) {
  Bint det = 0;
  computeDetGaussInt(dim, matrix, perm, &det);
  return det == 0;
}

static void printDeterminants(const Bint detDodgson, const Bint detGaussInt,
                              const long double detGaussFloat) {
  std::cout << "Dodgson:    " << detDodgson << std::endl;
  std::cout << "GaussInt:   " << detGaussInt << std::endl;
  std::cout << "GaussFloat: " << detGaussFloat << std::endl;
  std::cout << std::endl;
}

void detTest() {
  const int runsPerCase = 2;
  const int dimLow = 1;
  const int dimHigh = 5;
  const int dimStep = 1;
  const int sparsityLow = 0;
  const int sparsityHigh = 100;
  const int sparsityStep = 30;
  const unsigned long int entryMagnitude = 100;
  const long int rand48Seed = 4711;

  const int dimRangeSize = getRangeSize(dimLow, dimHigh, dimStep);
  const int sparsityRangeSize =
      getRangeSize(sparsityLow, sparsityHigh, sparsityStep);
  const int cases = dimRangeSize * sparsityRangeSize;

  int run = 0;

  srand48(rand48Seed);
  printProgressHeader(runsPerCase, dimRangeSize, sparsityRangeSize);
  for (unsigned int dim = dimLow; dim < dimHigh; dim += dimStep) {
    for (int sparsity = sparsityLow; sparsity < sparsityHigh; sparsity += sparsityStep) {
      for (int runIdx = 0; runIdx < runsPerCase; runIdx++) {
        SQState *sqState = new SQState(dim, entryMagnitude, sparsity);
        Bint detDodgson = 0;
        Bint detGaussInt = 0;
        long double detGaussFloat = 0.0L;
        printProgress(++run, runsPerCase * cases, dim, sparsity);


        sqState->printMatrix();
        computeDetDodgson(dim, sqState->getMatrix(), sqState->getPermutationVector(), &detDodgson);

        sqState->reinitializeCurrentState();
        sqState->printMatrix();
        computeDetGaussInt(dim, sqState->getMatrix(), sqState->getPermutationVector(), &detGaussInt);

        sqState->reinitializeCurrentState();
        sqState->printDoubleMatrix();
        computeDetGaussFloat(dim, sqState->getDoubleMatrix(), sqState->getPermutationVector(), &detGaussFloat);


        printDeterminants(detDodgson, detGaussInt, detGaussFloat);
        delete sqState;
      } /* for(int runIdx = 0; runIdx < runsPerCase; runIdx++) {... */
    } /* for(int sparsity = sparsityLow;...) {... */
  } /* for(unsigned int dim = dimLow;...) {... */
  return;
}
