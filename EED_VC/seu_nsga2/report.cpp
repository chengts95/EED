/* Routines for storing population data into files */
# include "basicfun.h"

/* Function to print the title of a population in a file */
void report_pop_titile(int nobj,int ncon,int nreal, int bitlength,
                       ofstream &ofpop)
{
    int i;
    ofpop<<"objectives"<<"\t"<<nobj<<endl;
    ofpop<<"constraints"<<"\t"<<ncon<<endl;
    ofpop<<"real_var"<<"\t"<<nreal<<endl;
    ofpop<<"bits_of_bin_var"<<"\t"<<bitlength<<endl;
    for(i=0; i<nobj; i++)
      ofpop<<"objectives"<<(i+1)<<"\t";
    for(i=0; i<ncon; i++)
      ofpop<<"constraints"<<(i+1)<<"\t";
    for(int i=0; i<nreal; i++)
      ofpop<<"real_var"<<(i+1)<<"\t";
    for(int i=0; i<bitlength; i++)
      ofpop<<"bits_of_bin_var"<<"\t";
    ofpop<<"constr_violation"<<"\t"<<"rank"<<"\t"<<"crowding_distance"<<endl;
}

void report_pop (int popsize,int nobj,int ncon,int nreal,
                 int nbin, int *nbits,
                 population *pop,ofstream &ofpop)
{
    int i, j, k;
    for (i=0; i<popsize; i++)
    {
        for (j=0; j<nobj; j++)
        {
            ofpop<<pop->ind[i].obj[j]<<"\t";
        }
        if (ncon>0)
        {
            for (j=0; j<ncon; j++)
            {
             ofpop<<pop->ind[i].constr[j]<<"\t";
            }
        }
        if (nreal!=0)
        {
            for (j=0; j<nreal; j++)
            {
              ofpop<<pop->ind[i].xreal[j]<<"\t";
            }
        }
        if (nbin>0)
        {
            for (j=0; j<nbin; j++)
            {
                for (k=0; k<nbits[j]; k++)
                {
                   ofpop<<pop->ind[i].gene[j][k]<<"\t";
                }
            }
        }
        ofpop<<pop->ind[i].constr_violation<<"\t";
        ofpop<<pop->ind[i].rank<<"\t";
        ofpop<<pop->ind[i].crowd_dist<<endl;
    }
}

/* Function to print the information of feasible and non-dominated population in a file */
void report_feasible (int popsize,int nobj, int ncon, int nreal,
                      int nbin,int *nbits,
                      population *pop,ofstream &ofpop)
{
    int i, j, k;
    for (i=0; i<popsize; i++)
    {
        if (pop->ind[i].constr_violation == 0.0 && pop->ind[i].rank==1)
        {
            for (j=0; j<nobj; j++)
            {
                ofpop<<pop->ind[i].obj[j]<<"\t";
            }
            if (ncon>0)
            {
                for (j=0; j<ncon; j++)
                {
                   ofpop<<pop->ind[i].constr[j]<<"\t";
                }
            }
            if (nreal>0)
            {
                for (j=0; j<nreal; j++)
                {
                   ofpop<<pop->ind[i].xreal[j]<<"\t";
                }
            }
            if (nbin>0)
            {
                for (j=0; j<nbin; j++)
                {
                    for (k=0; k<nbits[j]; k++)
                    {
                         ofpop<<pop->ind[i].gene[j][k]<<"\t";
                    }
                }
            }
            ofpop<<pop->ind[i].constr_violation<<"\t";
            ofpop<<pop->ind[i].rank<<"\t";
            ofpop<<pop->ind[i].crowd_dist<<endl;
        }
    }
}
