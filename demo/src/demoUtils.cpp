#include <float.h>
#include <iostream>
#include <stdlib.h>


#include "demoUtils.hpp"
#include "det.hpp"


// ---------------------------------------------------------------------------
// The only implementation detail: what an SQState actually stores.
// struct SQState::SQStateImpl is an 'aggregate', i.e. it does not have a
// user defined ctor. On construction with 'new', an ordered list of
// member initializations may be provided, e.g. 'new SQStateImpl{...}', see below.
// ---------------------------------------------------------------------------
struct SQState::SQStateImpl {
    const unsigned int      mDim;
    MPint           *       mFlatMatrix;
    MPint           **      mMatrix;
    long double     **      mDmatrix;
    unsigned int    *       mPerm;
};

SQState::SQState(SQStateImpl* impl) noexcept : pImpl(impl) {}

SQState::SQState(const unsigned int dim,
		const unsigned long int entryMagnitude,
		const unsigned int sparsity) :
		    pImpl(new SQStateImpl{dim, new MPint[dim * dim], new MPint * [dim],
	              new long double * [dim], new unsigned int[dim]}) {
	for (unsigned int ridx = 0; ridx < pImpl->mDim; ridx++) {
		pImpl->mMatrix[ridx] = new MPint[dim];
		pImpl->mDmatrix[ridx] = new long double[dim];
	}
	for (unsigned int flatidx = 0; flatidx < dim * dim; flatidx++) {
		unsigned long int randint = lrand48();
		randint %= 100;
		randint += 1;
		MPint entry = 0;
		if (randint > sparsity) {
			unsigned long int randnumHigh = mrand48();
			randnumHigh <<= 32;
			unsigned long int randnumLow = mrand48();
			unsigned long int randnum = (randnumHigh | randnumLow);
			int sgn = (mrand48() < 0) ? -1 : 1;
			entry = randnum % entryMagnitude;
			if (sgn < 0) entry = -entry;
		}
		pImpl->mFlatMatrix[flatidx] = entry;
	}
	this->reinitializeCurrentState();
}

PosDefState::PosDefState(const unsigned int dim,
		const unsigned long int entryMagnitude,
		const unsigned int sparsity) :
    SQState(new SQState::SQStateImpl{dim, new MPint[dim * dim], new MPint * [dim],
              new long double * [dim], new unsigned int[dim]}) {
	for (unsigned int ridx = 0; ridx < dim; ridx++) {
		pImpl->mMatrix[ridx] = new MPint[dim];
		pImpl->mDmatrix[ridx] = new long double[dim];
	}

	const unsigned int cols = 3 * dim;
	MPint* Lflat = new MPint[dim * cols];
	MPint** L = new MPint*[dim];
	for (unsigned int ridx = 0; ridx < dim; ridx++)
		L[ridx] = Lflat + ridx * cols;

	for (;;) {
		for (unsigned int flatidx = 0; flatidx < dim * cols; flatidx++) {
			unsigned long int randint = lrand48();
			randint %= 100;
			randint += 1;
			MPint entry = 0;
			if (randint > sparsity) {
				unsigned long int randnumHigh = mrand48();
				randnumHigh <<= 32;
				unsigned long int randnumLow = mrand48();
				unsigned long int randnum = (randnumHigh | randnumLow);
				int sgn = (mrand48() < 0) ? -1 : 1;
				entry = randnum % entryMagnitude;
				if (sgn < 0) entry = -entry;
			}
			Lflat[flatidx] = entry;
		}

		for (unsigned int ridx = 0; ridx < dim; ridx++) {
			for (unsigned int cidx = 0; cidx < dim; cidx++) {
				MPint sum = 0;
				for (unsigned int k = 0; k < cols; k++)
					sum += L[ridx][k] * L[cidx][k];
				pImpl->mFlatMatrix[ridx * dim + cidx] = sum;
			}
		}

		reinitializeCurrentState();
		if (!isSingular(dim, pImpl->mMatrix, pImpl->mPerm)) {
			reinitializeCurrentState();
			break;
		}
	}

	delete[] L;
	delete[] Lflat;
}

SQState::~SQState() {
	for (unsigned int ridx = 0; ridx < pImpl->mDim; ridx++) {
		delete[] pImpl->mMatrix[ridx];
		delete[] pImpl->mDmatrix[ridx];
	}
	delete[] pImpl->mFlatMatrix;
	delete[] pImpl->mMatrix;
	delete[] pImpl->mDmatrix;
	delete[] pImpl->mPerm;
	delete pImpl;
}


void SQState::printMatrix() {
	std::cout << "[";
	for (unsigned int ridx = 0; ridx < pImpl->mDim; ridx++) {
		const char *openRowParen = (ridx == 0) ? "[" : " [";
		std::cout << openRowParen;
		for (unsigned int cidx = 0; cidx < pImpl->mDim; cidx++) {
			const char *entryTrailer =
					(cidx < pImpl->mDim - 1) ? " " : ((ridx < pImpl->mDim - 1) ? "]\n" : "]]\n");
			std::cout << pImpl->mMatrix[ridx][cidx] << entryTrailer;
		}
	}
}

void SQState::printDoubleMatrix() {
	std::cout << "[";
	for (unsigned int ridx = 0; ridx < pImpl->mDim; ridx++) {
		const char *openRowParen = (ridx == 0) ? "[" : " [";
		std::cout << openRowParen;
		for (unsigned int cidx = 0; cidx < pImpl->mDim; cidx++) {
			const char *entryTrailer =
					(cidx < pImpl->mDim - 1) ? " " : ((ridx < pImpl->mDim - 1) ? "]\n" : "]]\n");
			std::cout << pImpl->mDmatrix[ridx][cidx] << entryTrailer;
		}
	}
}

void SQState::reinitializeCurrentState() {
	for (unsigned int ridx = 0; ridx < pImpl->mDim; ridx++) {
		pImpl->mPerm[ridx] = ridx;
		for (unsigned int cidx = 0; cidx < pImpl->mDim; cidx++) {
			pImpl->mMatrix[ridx][cidx] = pImpl->mFlatMatrix[ridx * pImpl->mDim + cidx];
			pImpl->mDmatrix[ridx][cidx] = mpint_to_ld(pImpl->mFlatMatrix[ridx * pImpl->mDim + cidx]);
		}
	}
}

MPint ** SQState::getMatrix() {
	return pImpl->mMatrix;
}

long double ** SQState::getDoubleMatrix() {
	return pImpl->mDmatrix;
}

unsigned int * SQState::getPermutationVector() {
	return pImpl->mPerm;
}



void printProgressHeader(const int runsPerCase, const int dimensions,
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

void printProgress(const int run, const int runs, const unsigned int dim,
                          const int sparsity) {
  std::cout << "run " << run << " of " << runs << ", dimension == " << dim
            << ", sparsity == " << sparsity << "%" << std::endl;
}

int getRangeSize(const int low, const int high, const int step) {
  int range = high - low;
  int retval = range / step;
  if (retval * step < range) {
    retval++;
  }
  return retval;
}

