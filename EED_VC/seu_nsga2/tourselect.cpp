/* Tournamenet Selections routines */

#include "basicfun.h"

/* Routine for binary tournament */
individual* tournament (int nobj,individual *ind1, individual *ind2)
{
    int flag;
    flag = check_dominance(nobj,ind1, ind2);
    if (flag==1)
    {
        return (ind1);
    }
    if (flag==-1)
    {
        return (ind2);
    }
    if (ind1->crowd_dist > ind2->crowd_dist)
    {
        return(ind1);
    }
    if (ind2->crowd_dist > ind1->crowd_dist)
    {
        return(ind2);
    }
    if ((randomperc()) <= 0.5)
    {
        return(ind1);
    }
    else
    {
        return(ind2);
    }
}

/* Routine for tournament selection, it creates a new_pop from old_pop by performing tournament selection and the crossover */
void selection (int popsize,int nobj,
                int nreal,
                double pcross_real,double eta_c,
                double *min_realvar,double *max_realvar,
                int &nrealcross,
                int nbin,
                double pcross_bin,int *nbits,
                int &nbincross,
                population *old_pop, population *new_pop)
{
    int *a1, *a2;
    int temp;
    int i;
    int randv;
    individual *parent1, *parent2;
    a1= new int[popsize];
    a2= new int[popsize];
    for (i=0; i<popsize; i++)
    {
        a1[i] = a2[i] = i;
    }
    for (i=0; i<popsize; i++)
    {
        randv = rnd (i, popsize-1);
        temp = a1[randv];
        a1[randv] = a1[i];
        a1[i] = temp;
        randv = rnd (i, popsize-1);
        temp = a2[randv];
        a2[randv] = a2[i];
        a2[i] = temp;
    }
    for (i=0; i<popsize; i+=4)
    {
        parent1 = tournament (nobj,&old_pop->ind[a1[i]], &old_pop->ind[a1[i+1]]);
        parent2 = tournament (nobj,&old_pop->ind[a1[i+2]], &old_pop->ind[a1[i+3]]);
        crossover (nreal,
                   pcross_real,eta_c,
                   min_realvar,max_realvar,
                   nrealcross,
                   nbin,
                   pcross_bin,nbits,
                   nbincross,
                   parent1, parent2, &new_pop->ind[i], &new_pop->ind[i+1]);
        parent1 = tournament (nobj,&old_pop->ind[a2[i]], &old_pop->ind[a2[i+1]]);
        parent2 = tournament (nobj,&old_pop->ind[a2[i+2]], &old_pop->ind[a2[i+3]]);
        crossover (nreal,
                   pcross_real,eta_c,
                   min_realvar,max_realvar,
                   nrealcross,
                   nbin,
                   pcross_bin,nbits,
                   nbincross,
                   parent1, parent2, &new_pop->ind[i+2], &new_pop->ind[i+3]);
    }
    delete[] a1;
    delete[] a2;
}


