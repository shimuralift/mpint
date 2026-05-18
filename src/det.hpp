#pragma once

#ifdef DEMO_NATIVE
typedef signed long int MPint;
#else
#include "MPint.hpp"
#endif

bool isSingular(unsigned int dim, MPint** matrix, unsigned int* perm);
void detTest();
