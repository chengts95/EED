/* Routines to decode the population */

# include "basicfun.h"
 

/* Function to decode a population to find out the binary variable values based on its bit pattern */
void decode_pop(int popsize,int nbin,int *nbits,
                double *min_binvar, double *max_binvar,
                population *pop)
{
    int i;
    for (i=0; i<popsize; i++)
      decode_ind(nbin,nbits,min_binvar,max_binvar,&(pop->ind[i]));
}

/* Function to decode an individual to find out the binary variable values based on its bit pattern */
void decode_ind (int nbin,int *nbits,double *min_binvar, double *max_binvar,
                 individual *ind)
{
    int j, k;
    int sum;
    for (j=0; j<nbin; j++)
    {
       sum=0;
       for (k=0; k<nbits[j]; k++)
       {
         if (ind->gene[j][k]==1)
            sum += pow((double)2,nbits[j]-1-k);
       }
      ind->xbin[j]=min_binvar[j]+
         (double)sum*(max_binvar[j]-min_binvar[j])/(double)(pow((double)2,nbits[j])-1);
   }
}
