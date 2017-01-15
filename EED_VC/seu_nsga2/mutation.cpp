/* Mutation routines */

# include "basicfun.h"
/* Routine for real polynomial mutation of an individual */
void real_mutate_ind (int nreal,double pmut_real, double eta_m,
                      double *min_realvar,double *max_realvar,
                      int &nrealmut,
                      individual *ind)
{
    int j;
    double rndv, delta1, delta2, mut_pow, deltaq;
    double y, yl, yu, val, xy;
    for (j=0; j<nreal; j++)
    {
        if (randomperc() <= pmut_real)
        {
            y = ind->xreal[j];
            yl = min_realvar[j];
            yu = max_realvar[j];
            delta1 = (y-yl)/(yu-yl);
            delta2 = (yu-y)/(yu-yl);
            rndv = randomperc();
            mut_pow = 1.0/(eta_m+1.0);
            if (rndv <= 0.5)
            {
                xy = 1.0-delta1;
                val = 2.0*rndv+(1.0-2.0*rndv)*(pow(xy,(eta_m+1.0)));
                deltaq =  pow(val,mut_pow) - 1.0;
            }
            else
            {
                xy = 1.0-delta2;
                val = 2.0*(1.0-rndv)+2.0*(rndv-0.5)*(pow(xy,(eta_m+1.0)));
                deltaq = 1.0 - (pow(val,mut_pow));
            }
            y = y + deltaq*(yu-yl);
            if (y<yl)
                y = yl;
            if (y>yu)
                y = yu;
            ind->xreal[j] = y;
            nrealmut+=1;
        }
    }
}

/* Routine for binary mutation of an individual */
void bin_mutate_ind (int nbin,int *nbits,double pmut_bin,
                     int &nbinmut,
                     individual *ind)
{
    int j, k;
    double prob;
    for (j=0; j<nbin; j++)
    {
        for (k=0; k<nbits[j]; k++)
        {
            prob = randomperc();
            if (prob <=pmut_bin)
            {
                if (ind->gene[j][k] == 0)
                {
                    ind->gene[j][k] = 1;
                }
                else
                {
                    ind->gene[j][k] = 0;
                }
                nbinmut+=1;
            }
        }
    }
}

/* Function to perform mutation of an individual */
void mutation_ind (int nreal,double pmut_real, double eta_m,
                   double *min_realvar,double *max_realvar,
                   int &nrealmut,
                   int nbin,int *nbits,double pmut_bin,
                   int &nbinmut,
                   individual *ind)
{
    if (nreal>0)
    {
        real_mutate_ind(nreal,pmut_real,eta_m,min_realvar,max_realvar,
                        nrealmut,
                        ind);
    }
    if (nbin>0)
    {
        bin_mutate_ind(nbin,nbits,pmut_bin,nbinmut,ind);
    }
    return;
}


/* Function to perform mutation in a population */
void mutation_pop (int popsize,
                   int nreal,double pmut_real, double eta_m,
                   double *min_realvar,double *max_realvar,
                   int &nrealmut,
                   int nbin,int *nbits,double pmut_bin,
                   int &nbinmut,
                   population *pop)
{
    int i;
    for (i=0; i<popsize; i++)
    {
        mutation_ind(nreal,pmut_real,eta_m,min_realvar,max_realvar,
                     nrealmut,
                     nbin,nbits,pmut_bin,nbinmut,
                     &(pop->ind[i]));
    }
    return;
}


