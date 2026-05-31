#include <cmath>
#include <cstdlib>
#include <iostream>

#include "demoUtils.hpp"

#define EPS 0.0000001

typedef MPint Long;


void make_Long_vector(Long ** vec, int dim) {
    if((*vec = new Long[dim]) == 0) {
        std::cerr << "data_utils.c:make_Long_vector:not enough space (dim = " << dim << ")\n";
        exit(1);
    }
}

void destroy_Long_vector(Long ** vec) {
    if(*vec == (Long *)NULL) {
        std::cerr << "data_utils:destroy_Long_vector:pointer is already NULL\n";
        exit(2);
    }
    delete[](*vec);
    *vec = (Long *)NULL;
}

void make_Long_rectmatrix(Long *** mat,
                          int      rows,
                          int      cols) {
    int i;

    if((*mat = (Long **)malloc(rows * sizeof(Long *))) == 0) {
        fprintf(stderr,
                "data_utils.c:make_Long_rectmatrix:not enough space (rows = %d)\n",
                rows);
        exit(1);
    }
    for(i = 0; i < rows; i++)
        make_Long_vector(&((*mat)[i]), cols);
}

void destroy_Long_matrix(Long *** mat,
                         int      rows) {
    int i;

    if(*mat == (Long **)NULL) {
        fprintf(stderr,
                "data_utils:destroy_Long_matrix:pointer is already NULL\n");
        exit(2);
    }
    for(i = 0; i < rows; i++)
        destroy_Long_vector(&((*mat)[i]));
    free(*mat);
    *mat = (Long **)NULL;
}

void make_double_vector(double ** vec, int dim) {
    if((*vec = (double *)malloc(dim * sizeof(double))) == 0) {
        std::cerr << "data_utils.c:make_double_vector:not enough space (dim = " << dim << ")\n";
        exit(1);
    }
}

void destroy_double_vector(double ** vec) {
    if(*vec == (double *)NULL) {
        std::cerr << "data_utils:destroy_double_vector:pointer is already NULL\n";
        exit(2);
    }
    free(*vec);
    *vec = (double *)NULL;
}

static void make_double_squarematrix(double *** mat,
                                     int        dim) {
    int i;

    if((*mat = (double **)malloc(dim * sizeof(double *))) == 0) {
        fprintf(stderr,
                "data_utils.c:make_double_rectmatrix:not enough space (rows = %d)\n",
                dim);
        exit(1);
    }
    for(i = 0; i < dim; i++)
        make_double_vector(&((*mat)[i]), dim);
}

void destroy_double_matrix(double *** mat,
                           int        dim) {
    int i;

    if(*mat == (double **)NULL) {
        fprintf(stderr,
                "data_utils:destroy_double_matrix:pointer is already NULL\n");
        exit(2);
    }
    for(i = 0; i < dim; i++)
        destroy_double_vector(&((*mat)[i]));
    free(*mat);
    *mat = (double **)NULL;
}

/* adds <from>-th row <lam>-times to <to>-th row
   in <dim>-sized Long-squarematrix <mat> . */
void Long_rowadd(int from, int to, Long lam, Long ** mat, int dim) {
    int i;

    if(from == to)
        std::cerr << "\nla_utils:Long_rowadd:warning:not unimodular\n";
    if(lam != 0)
        for(i = 0; i < dim; i++)
            mat[to][i] += lam * mat[from][i];
}

/* adds <from>-th row <lam>-times to <to>-th row
   in <dim>-sized double-squarematrix <mat> . */
void double_rowadd(int from, int to, double lam, double ** mat, int dim) {
    int i;

    if(from == to)
        std::cerr << "\nla_utils:double_rowadd:warning:not unimodular\n";
    if(lam != 0.0)
        for(i = 0; i < dim; i++)
            mat[to][i] += lam * mat[from][i];
}

/* adds <from>-th column <lam>-times to <to>-th column
   in <dim>-sized Long-squarematrix <mat> . */
void Long_coladd(int from, int to, Long lam, Long ** mat, int dim) {
    int i;

    if(from == to)
        std::cerr << "\nla_utils:Long_coladd:warning:not unimodular\n";
    if(lam != 0)
        for(i = 0; i < dim; i++)
            mat[i][to] += lam * mat[i][from];
}

/* transposes <indx1>-th and <indx2>-th row
   in <dim>-sized Long-squarematrix <mat> . */
void Long_rowchange(int indx1, int indx2, Long ** mat, int dim) {
    int  k;
    Long help;

    if(indx1 != indx2)
        for(k = 0; k < dim; k++) {
            help = mat[indx1][k];
            mat[indx1][k] = mat[indx2][k];
            mat[indx2][k] = help;
        }
}

/* transposes <indx1>-th and <indx2>-th column
   in <dim>-sized Long-squarematrix <mat> . */
void Long_colchange(int indx1, int indx2, Long ** mat, int dim) {
    int  k;
    Long help;

    if(indx1 != indx2)
        for(k = 0; k < dim; k++) {
            help = mat[k][indx1];
            mat[k][indx1] = mat[k][indx2];
            mat[k][indx2] = help;
        }
}

static void inc_gram_schmidt(Long ** gr, double * ge, double ** mo, double *  a, int k) {
    int  j;
    int  i;
    Long inter;

    for(j = 0; j < k; j++) {
        inter = gr[k][j];
        a[j] = static_cast<double>(inter);
        for(i = 0; i < j; i++)
            a[j] -= mo[j][i] * a[i];
        mo[k][j] = a[j] / ge[j];
    }
    inter = gr[k][k];
    ge[k] = static_cast<double>(inter);
    for(i = 0; i < k; i++)
        ge[k] -= mo[k][i] * a[i];
}

static Long my_round(double r) {
    Long i;

    if(r >= 0)
        i = static_cast<signed long int>((2 * r + 1) / 2);
    else {
        i = static_cast<signed long int>((2 * (-r) + 1) / 2);
        i *= -1;
    }
    return i;
}

static void size_reduction(Long ** gr, Long ** ba, Long ** invba, double ** mo, int k, int l, int dim) {
    Long q;
    Long iq;

    q = my_round(mo[k][l]);
    Long_rowadd(l, k, -q, gr, dim);
    Long_coladd(l, k, -q, gr, dim);
    if(ba != NULL)
        Long_rowadd(l, k, -q, ba, dim);
    if(invba != NULL)
        Long_coladd(k, l, q, invba, dim);
    iq = q;
    mo[k][l] -= static_cast<double>(iq);
    double_rowadd(l, k, static_cast<double>(-iq), mo, l);
}

static void swap(Long ** gr, Long ** ba, Long ** invba, double ** mo, double * ge, int k, int kmax, int dim) {
    int    j;
    double mu;
    double b;
    double t;

    Long_rowchange(k, k - 1, gr, dim);
    Long_colchange(k, k - 1, gr, dim);
    if(ba != NULL)
        Long_rowchange(k, k - 1, ba, dim);
    if(invba != NULL)
        Long_colchange(k, k - 1, invba, dim);
    for(j = 0; j < k - 1; j++) {
        mu = mo[k][j];
        mo[k][j] = mo[k - 1][j];
        mo[k - 1][j] = mu;
    }
    mu = mo[k][k - 1];
    b = ge[k] + mu * mu * ge[k - 1];
    mo[k][k - 1] = mu * ge[k - 1] / b;
    ge[k] = ge[k - 1] * ge[k] / b;
    ge[k - 1] = b;
    for(j = k + 1; j <= kmax; j++) {
        t = mo[j][k];
        mo[j][k] = mo[j][k - 1] - mu * t;
        mo[j][k - 1] = t + mo[k][k - 1] * mo[j][k];
    }
}

static void insert(Long ** gr, Long ** ba, Long ** invba, Long * inter, int k, int i, int dim) {
    int j;
    int l;

    for(l = 0; l < dim; l++)
        inter[l] = gr[k][l];
    for(j = k; j >= i + 1; j--)
        for(l = 0; l < dim; l++)
            gr[j][l] = gr[j - 1][l];
    for(l = 0; l < dim; l++)
        gr[i][l] = inter[l];
    if(ba != NULL) {
        for(l = 0; l < dim; l++)
            inter[l] = ba[k][l];
        for(j = k; j >= i + 1; j--)
            for(l = 0; l < dim; l++)
                ba[j][l] = ba[j - 1][l];
        for(l = 0; l < dim; l++)
            ba[i][l] = inter[l];
    }
    if(invba != NULL) {
        for(l = 0; l < dim; l++)
            inter[l] = invba[l][k];
        for(j = k; j >= i + 1; j--)
            for(l = 0; l < dim; l++)
                invba[l][j] = invba[l][j - 1];
        for(l = 0; l < dim; l++)
            invba[l][i] = inter[l];
    }
    for(l = 0; l < dim; l++)
        inter[l] = gr[l][k];
    for(j = k; j >= i + 1; j--)
        for(l = 0; l < dim; l++)
            gr[l][j] = gr[l][j - 1];
    for(l = 0; l < dim; l++)
        gr[l][i] = inter[l];
}

/* recursion for finding shortest vectors */
static void shrt_count(int c, double damage, double * ge, double ** mo, int n, Long * vec, int con, int * anzahl, Long len) {
    double x;
    double gec;
    int    i;
    int    j;
    Long   help;
    Long   my_len;

    my_len = len;
    if(c == -1) {
        for(i = 0; i < n && vec[i] == 0; ++i);
        if(i == n)
            con = 1;
        else
            ++(*anzahl);
    }
    else {
        x = 0;
        for(j = c + 1; j < n; ++j) {
            help = vec[j];
            x += static_cast<double>(help) * mo[j][c];
        }
        help = my_round(x);
        i = static_cast<int>(-help);
        gec = ge[c];
        if(gec * (x + i) * (x + i) + damage < static_cast<double>(my_len) + EPS) {
            while((gec * (x + i) * (x + i) + damage < static_cast<double>(my_len) + EPS) ||
                  (x + i <= 0))
                ++i;
            --i;
            while((gec * (x + i) * (x + i) + damage < static_cast<double>(my_len) + EPS) &&
                  con == 0) {
                vec[c] = i;
                shrt_count(c - 1,
                           gec * (x + i) * (x + i) + damage,
                           ge,
                           mo,
                           n,
                           vec,
                           con,
                           anzahl,
                           len);
                --i;
            }
        }
    }
}

/* recursion for finding shortest vectors */
static void shrt(int c, double damage, double * ge, double ** mo, int n, Long * vec, int con, int * anzahl, Long ** v, Long len) {
    double x;
    double gec;
    int    i;
    int    j;
    Long   help;
    Long   my_len;

    my_len = len;
    if(c == -1) {
        for(i = 0; i < n && vec[i] == 0; ++i);
        if(i == n)
            con = 1;
        else {
            for(i = 0; i < n; ++i)
                v[*anzahl][i] = vec[i];
            v[*anzahl][n] = my_round(damage);
            ++(*anzahl);
        }
    }
    else {
        x = 0;
        for(j = c + 1; j < n; ++j) {
            help = vec[j];
            x += static_cast<double>(help) * mo[j][c];
        }
        help = my_round(x);
        i = static_cast<int>(-help);
        gec = ge[c];
        if(gec * (x + i) * (x + i) + damage < static_cast<double>(my_len) + EPS) {
            while((gec * (x + i) * (x + i) + damage < static_cast<double>(my_len) + EPS) ||
                  (x + i <= 0))
                ++i;
            --i;
            while((gec * (x + i) * (x + i) + damage < static_cast<double>(my_len) + EPS) &&
                  con == 0) {
                vec[c] = i;
                shrt(c - 1,
                     gec * (x + i) * (x + i) + damage,
                     ge,
                     mo,
                     n,
                     vec,
                     con,
                     anzahl,
                     v,
                     len);
                --i;
            }
        }
    }
}


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
int triple_l(Long ** gr, Long ** ba, Long ** invba, double * ge, double ** mo, int dim) {
    int      k;
    int      kmax;
    int      lovasz_cond;
    int      l;
    double * a;
    Long     inter;

    if(dim <= 1) {
        std::cerr << "\nredu_utils.c:triple_l:dimension smaller than two\n";
        exit(3);
    }
    make_double_vector(&a, dim);
    k = 1;
    kmax = 0;
    inter = gr[0][0];
    ge[0] = static_cast<double>(inter);
    do {
        if(k > kmax) {
            kmax = k;
            inc_gram_schmidt(gr, ge, mo, a, k);
            if(fabs(ge[k]) < EPS) {
                std::cerr << "\nredu_utils.c:triple_l:grammatrix not pos.def.\n";
/*
                exit(4);
*/
                return -1;
            }
        }
        do {
            size_reduction(gr, ba, invba, mo, k, k - 1, dim);
            lovasz_cond = (ge[k] >= (0.75 - mo[k][k - 1] * mo[k][k - 1]) * ge[k - 1]);
            if(!lovasz_cond) {
                swap(gr, ba, invba, mo, ge, k, kmax, dim);
                k = (k > 2 ? k - 1 : 1);
            }
        }
        while(!lovasz_cond);
        for(l = k - 2; l >= 0; l--)
            size_reduction(gr, ba, invba, mo, k, l, dim);
        k++;
    }
    while(k < dim);
    for(l = 1; l < dim; l++)
        inc_gram_schmidt(gr, ge, mo, a, l);
    destroy_double_vector(&a);
    return dim;
}

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
int deep_triple_l(Long ** gr, Long ** ba, Long ** invba, double * ge, double ** mo, int dim) {
    int      k;
    int      l;
    int      i;
    double * a;
    double   b;
    Long   * inter;
    int      flag;
    Long     help;

    if(dim <= 1) {
        std::cerr << "\nredu_utils.c:deep_triple_l:dimension smaller than two\n";
        exit(3);
    }
    make_double_vector(&a, dim);
    make_Long_vector(&inter, dim);
    k = 0;
    flag = 0;
    do {
        inc_gram_schmidt(gr, ge, mo, a, k);
        if(fabs(ge[k]) < EPS) {
            std::cerr << "\nredu_utils.c:deep_triple_l:grammatrix not pos.def.\n";
            exit(4);
        }
        if(k == 0)
            k = 1;
        else {
            for(l = k - 1; l >= 0; l--)
                size_reduction(gr, ba, invba, mo, k, l, dim);
            help = gr[k][k];
            b = static_cast<double>(help);
            i = 0;
            while(i != k) {
                if(3 * ge[i] <= 4 * b)
                {
                    b -= mo[k][i] * mo[k][i] * ge[i];
                    i++;
                }
                else {
                    insert(gr, ba, invba, inter, k, i, dim);
                    if(i > 0) {
                        k = i - 1;
                        help = gr[k][k];
                        b = static_cast<double>(help);
                        i = 0;
                    }
                    else {
                        k = 0;
                        flag = 1;
                    }
                }
            }
            if(flag == 0)
                k++;
            else
                flag = 0;
        }
    }
    while(k < dim);
    for(l = 1; l < dim; l++)
        inc_gram_schmidt(gr, ge, mo, a, l);
    destroy_Long_vector(&inter);
    destroy_double_vector(&a);
    return dim;
}

int shortvecs_count(double * ge, double ** mo, Long len, int dim) {
    Long * vec;
    int    con    = 0;
    int    anzahl = 0;

    make_Long_vector(&vec, dim);
    /* recursively calculate the vectors up to length max */
    shrt_count(dim - 1, 0.0, ge, mo, dim, vec, con, &anzahl, len);
    destroy_Long_vector(&vec);
    return anzahl ;
}

void shortvecs(double * ge, double ** mo, Long len, Long ** vecs, int dim) {
    Long * vec;
    int    con    = 0;
    int    anzahl = 1;

    make_Long_vector(&vec, dim);
    /* recursively calculate the vectors up to length max */
    shrt(dim - 1, 0.0, ge, mo, dim, vec, con, &anzahl, vecs, len);
    destroy_Long_vector(&vec);
    return;
}


void reduTest() {
	  const int runsPerCase = 2;
	  const int dimLow = 2;
	  const int dimHigh = 5;
	  const int dimStep = 1;
	  const int sparsityLow = 10;
	  const int sparsityHigh = 30;
	  const int sparsityStep = 10;
	  const unsigned long int entryMagnitude = 300;
	  const long int rand48Seed = 4713;

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
				  PosDefState *pdState = new PosDefState(dim, entryMagnitude, sparsity);
				  printProgress(++run, runsPerCase * cases, dim, sparsity);

				  double * ge;
				  double ** mo;
				  Long len = entryMagnitude*dim;
				  Long ** vecs;
				  unsigned int shortvec_numb;

				  pdState->printMatrix();
				  make_double_vector(&ge, dim);
				  make_double_squarematrix(&mo, dim);
				  triple_l(pdState->getMatrix(), (Long **)NULL, (Long **)NULL, ge, mo, dim);

				  pdState->printMatrix();
				  shortvec_numb = shortvecs_count(ge, mo, len, dim);
				  make_Long_rectmatrix(&vecs, shortvec_numb + 1, dim + 1);
				  shortvecs(ge, mo, len, vecs, dim);
				  destroy_double_vector(&ge);
				  destroy_double_matrix(&mo, dim);
				  destroy_Long_matrix(&vecs, shortvec_numb + 1);

				  delete pdState;
			  } /* for(int runIdx = 0; runIdx < runsPerCase; runIdx++) {... */
		  } /* for(int sparsity = sparsityLow;...) {... */
	  } /* for(unsigned int dim = dimLow;...) {... */
	  return;
}
