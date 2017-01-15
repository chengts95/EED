/* Data initializtion routines */

#include "basicfun.h"

/* Function to initialize an individual randomly */
void initialize_ind (int nreal,
                     double *min_realvar,double *max_realvar,
                     int nbin,int *nbits,
                     individual *ind)
{
    int j, k;
    if (nreal>0)
        for (j=0; j<nreal; j++)
            ind->xreal[j]=rndreal(min_realvar[j], max_realvar[j]);

    if (nbin>0)
    {
        for (j=0; j<nbin; j++)
        {
            for (k=0; k<nbits[j]; k++)
            {
                if (randomperc()<= 0.5)
                {
                    ind->gene[j][k] = 0;
                }
                else
                {
                    ind->gene[j][k] = 1;
                }
            }
        }
    }
}

/* Function to initialize a population randomly */
void initialize_pop (int popsize,
                     int nreal,
                     double *min_realvar,double *max_realvar,
                     int nbin,int *nbits,
                     population *pop)
{
    int i;
    for (i=0; i<popsize; i++)
    {
        initialize_ind (nreal,min_realvar,max_realvar,
                        nbin,nbits,
                        &(pop->ind[i]));
    }
}


