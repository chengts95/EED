#ifndef sim_nsga2H
#define sim_nsga2H

struct nsga2cfg
{
    int nreal;
    int nobj;
    int ncon;
    int popsize;
    int ngen;
    double pcross_real;
    double pmut_real;
    double eta_c;
    double eta_m;
};

void sim_nsga2_paretoset(nsga2cfg sim_ga,
                  double *min_x,double *max_x,
                 double **x,double **obj,int &feasible_popsize,
                 void (*objfun)(double*, double*, int**, double*, double*));

#endif
