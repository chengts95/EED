#ifndef TYPEDEFH
#define TYPEDEFH

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

# define INF 1.0e14
# define EPS 1.0e-14
# define E  2.71828182845905
# define PI 3.14159265358979

typedef struct
{
    int rank;
    double constr_violation;
    double *xreal;
    int **gene;
    double *xbin;
    double *obj;
    double *constr;
    double crowd_dist;
} individual;

typedef struct
{
    individual *ind;
} population;

typedef struct lists
{
    int index;
    struct lists *parent;
    struct lists *child;
} list;

typedef struct
{
    int nreal;
    int nbin;
    int nobj;
    int ncon;
    int popsize;
    double pcross_real;
    double pcross_bin;
    double pmut_real;
    double pmut_bin;
    double eta_c;
    double eta_m;
    int ngen;

    int *nbits;
    double *min_realvar;
    double *max_realvar;
    double *min_binvar;
    double *max_binvar;
} MOGAparam;

#endif

