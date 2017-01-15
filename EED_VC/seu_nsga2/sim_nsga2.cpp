
#include "typedef.h"
#include "nsga2.h"
#include "sim_nsga2.h"

void sim_nsga2_paretoset(nsga2cfg sim_ga,
                 double *min_x,double *max_x,
                 double **x,double **obj,int &feasible_popsize,
                 void (*objfun)(double*, double*, int**, double*, double*))
{
   int recordallpop=1;

   MOGAparam ga;

   ga.nreal=sim_ga.nreal;
   ga.nobj=sim_ga.nobj;
   ga.ncon=sim_ga.ncon;
   
   ga.popsize=sim_ga.popsize;

   ga.pcross_real=sim_ga.pcross_real;
   ga.pmut_real=sim_ga.pmut_real;
   ga.eta_c=sim_ga.eta_c;
   ga.eta_m=sim_ga.eta_m;
   ga.ngen=sim_ga.ngen;

   ga.nbin=0;

   ga.min_realvar = new double[sim_ga.nreal];
   ga.max_realvar = new double[sim_ga.nreal];

   for (int i=0; i<sim_ga.nreal; i++)
   {
      ga.min_realvar[i]=min_x[i];
      ga.max_realvar[i]=max_x[i];
   }

   population *feasible_pop;
   feasible_pop=new population;

   nsga_paretoset(ga,recordallpop,feasible_pop,feasible_popsize,(*objfun));

   for (int i=0; i<ga.popsize; i++)
   {
     for (int j=0; j<ga.nreal; j++)
     {
        x[i][j]=feasible_pop->ind[i].xreal[j];
     }
     for (int k=0; k<ga.nobj; k++)
     {
       obj[i][k]=feasible_pop->ind[i].obj[k];
     }
  }
  delete  feasible_pop;
}

