#ifndef SIM_NSGA2LIBH
#define SIM_NSGA2LIBH

#define IMPORT extern "C" __declspec(dllimport) 

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

IMPORT void __stdcall sim_ga_paretoset(nsga2cfg ga,
                 double *min_x,double *max_x,
                 double **x,double **obj,int &feasible_popsize,
                 void (*objfun)(double*, double*, int**, double*, double*));

#endif
