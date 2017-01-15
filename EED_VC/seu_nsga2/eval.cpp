/* Routine for evaluating population members  */
# include "basicfun.h"

/* Routine to evaluate objective function values and constraints for an individual */
void evaluate_ind(int ncon,individual &ind,
           void (*funrb)(double*, double*, int**, double*, double*))
{
    int j;
    (*funrb)(ind.xreal, ind.xbin, ind.gene, ind.obj, ind.constr);
    if (ncon==0)
    {
        ind.constr_violation = 0.0;
    }
    else
    {
        ind.constr_violation = 0.0;
        for (j=0; j<ncon; j++)
            if (ind.constr[j]<0.0)
                ind.constr_violation += ind.constr[j];
    }
}


/* Routine to evaluate objective function values and constraints for a population */
void evaluate_pop (int popsize,int ncon,population *pop,
                   void (*funrb)(double*, double*, int**, double*, double*))
{
    int i;
    for (i=0; i<popsize; i++)
        evaluate_ind(ncon, pop->ind[i], (*funrb));
}


