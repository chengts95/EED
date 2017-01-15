
#include "sim_paretoset_analyze.h"

void SingleBestSolutionInParetoSet(nsga2cfg ga,double **x,double **obj,int feasible_popsize,
                                   loadv &bestC,loadv &bestE)
{
   float objMin;

   int bestID=0;

   objMin=obj[bestID][0];

   for(int k=1; k<feasible_popsize; k++)
     if (obj[k][0]<objMin)
     {
        objMin=obj[k][0];
        bestID=k;
     }
   for(int i=0; i<ga.nreal; i++)
     bestC.xreal[i]=x[bestID][i];

   bestC.cobj=obj[bestID][0];
   bestC.eobj=obj[bestID][1];


   //==============================

   bestID=0;

   objMin=obj[bestID][1];

   for(int k=1; k<feasible_popsize; k++)
     if (obj[k][1]<objMin)
     {
       objMin=obj[k][1];
       bestID=k;
     }
   for(int i=0; i<ga.nreal; i++)
   bestE.xreal[i]=x[bestID][i];
   bestE.cobj=obj[bestID][0];
   bestE.eobj=obj[bestID][1];


}

void BestCompromiseSolutionInParetoSet(nsga2cfg ga,double **x,double **obj,int feasible_popsize,
                                       loadv &best)
{
  float **mebfun;
  float *normebfun;
  float fmax,fmin;
  float maxmebfun;
  int bestID;
//==============
  mebfun=new float*[ga.nobj];
  for(int i=0; i<ga.nobj; i++)
     mebfun[i]=new float[ga.popsize];

  normebfun=new float[ga.popsize];

  for(int i=0; i<ga.nobj; i++)
  {
    fmax=obj[0][i];
    fmin=obj[0][i];
    for(int j=1; j<feasible_popsize; j++)
    {
      if (obj[j][i]>fmax) fmax=obj[j][i];
      if (obj[j][i]<fmin) fmin=obj[j][i];
    }

    for(int j=0; j<feasible_popsize; j++)
    {
      if (obj[j][i]<=fmin)
         mebfun[i][j]=1.0;
      if ((obj[j][i]>fmin)&&
         (obj[j][i]<fmax))
         mebfun[i][j]=(fmax-obj[j][i])/(fmax-fmin);
      if (obj[j][i]>=fmax)
         mebfun[i][j]=0;
     }
   }
//======= normailzed membership function
   float a,b;
   for(int k=0; k<feasible_popsize; k++)
   {

    a=mebfun[0][k];
    for(int i=1; i<ga.nobj; i++)
      a +=mebfun[i][k];

    b=0;
    for(int j=0; j<feasible_popsize; j++)
    {
      for(int i=0; i<ga.nobj; i++)
       b +=mebfun[i][j];
    }
    normebfun[k]=a/b;
   }
//==========
   bestID=0;
   maxmebfun=normebfun[0];
   for(int k=1; k<feasible_popsize; k++)
   {
    if (normebfun[k]>maxmebfun)
    {
      maxmebfun=normebfun[k];
      bestID=k;
    }
   }
//===============
   for(int i=0; i<ga.nreal; i++)
   best.xreal[i]=x[bestID][i];
   best.cobj=obj[bestID][0];
   best.eobj=obj[bestID][1];


  for(int i=0; i<ga.nobj; i++)
     delete[] mebfun[i];
  delete[] mebfun;
  delete[] normebfun;
}
