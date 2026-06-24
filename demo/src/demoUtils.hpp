#pragma once


#include "demoTypedef.hpp"


class SQState {
public:
    SQState(const unsigned int dim,
    		const unsigned long int entryMagnitude,
			const unsigned int sparsity);
    ~SQState();

    void printMatrix();
    void printDoubleMatrix();
    void reinitializeCurrentState();
    MPint ** getMatrix();
    long double ** getDoubleMatrix();
    unsigned int * getPermutationVector();

protected:
    struct SQStateImpl;
    SQState(SQStateImpl* impl) noexcept;   // for use by derived-class ctors
    SQStateImpl*  pImpl;
};

class PosDefState : public SQState {
public:
	PosDefState(const unsigned int dim,
    	    	const unsigned long int entryMagnitude,
	    		const unsigned int sparsity);
};


void printProgressHeader(const int runsPerCase, const int dimensions, const int sparsities);
void printProgress(const int run, const int runs, const unsigned int dim, const int sparsity);
int getRangeSize(const int low, const int high, const int step);
