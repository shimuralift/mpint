#include <float.h>
#include <iostream>
#include <stdlib.h>

#include "MPint.hpp"

//typedef signed long int Bint;
typedef MPint Bint;

struct st_squarematrix_state {
  Bint *flatMatrix;
};
typedef struct st_squarematrix_state SQState;

static Bint gcd(const Bint a, const Bint b) {
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

static void exitNoMem() {
  std::cerr << "det.cpp: exiting: could not calloc/malloc." << std::endl;
  exit(-1);
}

static void initRandomMatrix(const unsigned int dim, SQState **stateHnd,
                             Bint ***matrixPtr, long double ***dmatrixPtr,
                             unsigned int **perm) {
  SQState *statePtr = NULL;
  Bint **matrix = NULL;
  long double **dmatrix = NULL;
  if (0 == (statePtr = (SQState *)malloc(sizeof(SQState)))) {
    exitNoMem();
  }
  statePtr->flatMatrix = new Bint[dim * dim]();
  if (0 == (matrix = (Bint **)calloc(dim, sizeof(Bint *)))) {
    exitNoMem();
  }
  if (0 == (dmatrix = (long double **)calloc(dim, sizeof(long double *)))) {
    exitNoMem();
  }
  for (unsigned int ridx = 0; ridx < dim; ridx++) {
    matrix[ridx] = new Bint[dim]();
    if (0 ==
        (dmatrix[ridx] = (long double *)calloc(dim, sizeof(long double)))) {
      exitNoMem();
    }
    if (0 == (*perm = (unsigned int *)calloc(dim, sizeof(unsigned int)))) {
      exitNoMem();
    }
  }
  *stateHnd = statePtr;
  *matrixPtr = matrix;
  *dmatrixPtr = dmatrix;
}

static void sameRandomMatrix(const unsigned int dim, const SQState *statePtr,
                             Bint **matrix, long double **dmatrix,
                             unsigned int *perm) {
  for (unsigned int ridx = 0; ridx < dim; ridx++) {
    perm[ridx] = ridx;
    for (unsigned int cidx = 0; cidx < dim; cidx++) {
      matrix[ridx][cidx] = statePtr->flatMatrix[ridx * dim + cidx];
      dmatrix[ridx][cidx] = static_cast<long double>(statePtr->flatMatrix[ridx * dim + cidx]);
    }
  }
}

static void nextRandomMatrix(const unsigned int dim,
                             const unsigned int sparsity,
                             const SQState *statePtr, Bint **matrix,
                             long double **dmatrix, unsigned int *perm,
                             const unsigned long int entryMagnitude) {
  for (unsigned int flatidx = 0; flatidx < dim * dim; flatidx++) {
    unsigned long int randint = lrand48();
    randint %= 100;
    randint += 1;
    Bint entry = 0;
    if (randint > sparsity) {
      unsigned long int randnumHigh = mrand48();
      randnumHigh <<= 32;
      unsigned long int randnumLow = mrand48();
      unsigned long int randnum = (randnumHigh | randnumLow);
      int sgn = (mrand48() < 0) ? -1 : 1;
      entry = sgn * (randnum % entryMagnitude);
    }
    statePtr->flatMatrix[flatidx] = entry;
  }
  sameRandomMatrix(dim, statePtr, matrix, dmatrix, perm);
}

static void freeRandomMatrix(const unsigned int dim, SQState *statePtr,
                             Bint **matrix, long double **dmatrix,
                             unsigned int *perm) {
  for (unsigned int ridx = 0; ridx < dim; ridx++) {
    delete[] matrix[ridx];
    free(dmatrix[ridx]);
  }
  free(matrix);
  free(dmatrix);
  free(perm);
  delete[] statePtr->flatMatrix;
  free(statePtr);
}

static void printProgressHeader(const int runsPerCase, const int dimensions,
                                const int sparsities) {
  std::cout << " "
            << "number of cases  ==  dimensions x sparsities:" << std::endl;
  std::cout << "  " << (dimensions * sparsities) << " == " << dimensions
            << " x " << sparsities << std::endl;
  std::cout << " " << "number of runs  ==  runs per case x cases:" << std::endl;
  std::cout << "  " << (runsPerCase * dimensions * sparsities)
            << " == " << runsPerCase << " x " << (dimensions * sparsities)
            << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
}

static void printProgress(const int run, const int runs, const unsigned int dim,
                          const int sparsity) {
  std::cout << "run " << run << " of " << runs << ", dimension == " << dim
            << ", sparsity == " << sparsity << "%" << std::endl;
}

static void printDeterminants(const Bint detDodgson, const Bint detGaussInt,
                              const long double detGaussFloat) {
  std::cout << "Dodgson:    " << detDodgson << std::endl;
  std::cout << "GaussInt:   " << detGaussInt << std::endl;
  std::cout << "GaussFloat: " << detGaussFloat << std::endl;
  std::cout << std::endl;
}

static void printMatrix(Bint **matrix, const unsigned int dim) {
  std::cout << "[";
  for (unsigned int ridx = 0; ridx < dim; ridx++) {
    const char *openRowParen = (ridx == 0) ? "[" : " [";
    std::cout << openRowParen;
    for (unsigned int cidx = 0; cidx < dim; cidx++) {
      const char *entryTrailer =
          (cidx < dim - 1) ? " " : ((ridx < dim - 1) ? "]\n" : "]]\n");
      std::cout << matrix[ridx][cidx] << entryTrailer;
    }
  }
}

static void printMatrix(long double **matrix, const unsigned int dim) {
  std::cout << "[";
  for (unsigned int ridx = 0; ridx < dim; ridx++) {
    const char *openRowParen = (ridx == 0) ? "[" : " [";
    std::cout << openRowParen;
    for (unsigned int cidx = 0; cidx < dim; cidx++) {
      const char *entryTrailer =
          (cidx < dim - 1) ? " " : ((ridx < dim - 1) ? "]\n" : "]]\n");
      std::cout << matrix[ridx][cidx] << entryTrailer;
    }
  }
}

static int getRangeSize(const int low, const int high, const int step) {
  int range = high - low;
  int retval = range / step;
  if (retval * step < range) {
    retval++;
  }
  return retval;
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
    for (int sparsity = sparsityLow; sparsity < sparsityHigh;
         sparsity += sparsityStep) {
      SQState *state = NULL;
      Bint **matrix = NULL;
      long double **dmatrix = NULL;
      unsigned int *perm = NULL;
      initRandomMatrix(dim, &state, &matrix, &dmatrix, &perm);
      for (int runIdx = 0; runIdx < runsPerCase; runIdx++) {
        Bint detDodgson = 0;
        Bint detGaussInt = 0;
        long double detGaussFloat = 0.0L;
        printProgress(++run, runsPerCase * cases, dim, sparsity);

        nextRandomMatrix(dim, sparsity, state, matrix, dmatrix, perm,
                         entryMagnitude);
        printMatrix(matrix, dim);
        computeDetDodgson(dim, matrix, perm, &detDodgson);

        sameRandomMatrix(dim, state, matrix, dmatrix, perm);
        printMatrix(matrix, dim);
        computeDetGaussInt(dim, matrix, perm, &detGaussInt);

        sameRandomMatrix(dim, state, matrix, dmatrix, perm);
        printMatrix(dmatrix, dim);
        computeDetGaussFloat(dim, dmatrix, perm, &detGaussFloat);

        printDeterminants(detDodgson, detGaussInt, detGaussFloat);
      } /* for(int runIdx = 0; runIdx < runsPerCase; runIdx++) {... */
      freeRandomMatrix(dim, state, matrix, dmatrix, perm);
    } /* for(int sparsity = sparsityLow;...) {... */
  } /* for(unsigned int dim = dimLow;...) {... */
  return;
}
