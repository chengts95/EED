/* Memory allocation and deallocation routines */

# include "basicfun.h"

/* Function to allocate memory to an individual */
void allocate_ind (int nreal,int nbin,int *nbits,int nobj,int ncon,
                          individual *ind)
{
    int i;
    if (nreal>0)
        ind->xreal = new double[nreal];

    if (nbin>0)
    {
        ind->xbin =new double[nbin];

        ind->gene = new int*[nbin];
        for (i=0; i<nbin; i++)
            ind->gene[i] = new int[nbits[i]];
    }
    ind->obj = new double[nobj];
    if (ncon>0)
      ind->constr =new double[ncon];
}

/* Function to allocate memory to a population */
void allocate_pop(int nreal,int nbin,int *nbits,int nobj,int ncon,
                          population *pop, int size)
{
    int i;
    pop->ind = new individual[size];
    for (i=0; i<size; i++)
       allocate_ind(nreal,nbin,nbits,nobj,ncon,&(pop->ind[i]));
}

/* Function to deallocate memory to an individual */
void deallocate_ind(int nreal,int nbin,int ncon,individual *ind)
{
    int i;
    if (nreal>0)
        delete[] ind->xreal;

    if (nbin>0)
    {
        delete[] ind->xbin;

        for (i=0; i<nbin; i++)
            delete[] ind->gene[i];
        delete[] ind->gene;
    }
    delete[] ind->obj;
    if (ncon>0)
        delete[] ind->constr;
}

/* Function to deallocate memory to a population */
void deallocate_pop (int nreal,int nbin,int ncon,population *pop, int size)
{
    int i;
    for (i=0; i<size; i++)
        deallocate_ind(nreal,nbin,ncon,&(pop->ind[i]));
    delete[] pop->ind;
}

