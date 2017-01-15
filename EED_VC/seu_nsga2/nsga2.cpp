#include <memory.h>
#include <fstream>

#include "nsga2.h"
#include "basicfun.h"

static int nbinmut;
static int nrealmut;
static int nbincross;
static int nrealcross;
static int bitlength;

static  population *parent_pop;
static  population *child_pop;
static  population *mixed_pop;
static  population **all_pop;

static void nsga_pop_feasible(MOGAparam ga,population *pop,population *feasible_pop,int &feasible_popsize);
static void nsga_InitSolve(MOGAparam ga,population *feasible_pop,int recordallpop);
static void nsga_Solving(MOGAparam ga,int recordallpop,population *feasible_pop,int &feasible_popsize,
                         void (*funrb)(double*, double*, int**, double*, double*));

void nsga_deallocate(MOGAparam ga,population *feasible_pop,int recordallpop)
{
    if (ga.nreal>0)
    {
        delete[] ga.min_realvar;
        delete[] ga.max_realvar;
    }
    if (ga.nbin>0)
    {
        delete[] ga.min_binvar;
        delete[] ga.max_binvar;
        delete[] ga.nbits;
    }
    if ((ga.nreal>0)||(ga.nbin>0))
    {
      deallocate_pop(ga.nreal,ga.nbin,ga.ncon,parent_pop, ga.popsize);
      deallocate_pop(ga.nreal,ga.nbin,ga.ncon,child_pop, ga.popsize);
      deallocate_pop(ga.nreal,ga.nbin,ga.ncon,mixed_pop, 2*ga.popsize);
      deallocate_pop(ga.nreal,ga.nbin,ga.ncon,feasible_pop, ga.popsize);

      delete parent_pop;
      delete child_pop;
      delete mixed_pop;
      delete feasible_pop;
    }
    if (recordallpop)
    {
      for(int i=0; i<ga.ngen; i++)
      {
         // 有错误
         deallocate_pop(ga.nreal,ga.nbin,ga.ncon,all_pop[i],ga.popsize);
         delete  all_pop[i];
      }
      delete[] all_pop;
    }
}

void nsga_InitSolve(MOGAparam ga,population *feasible_pop,int recordallpop)
{
    nbinmut = 0;
    nrealmut = 0;
    nbincross = 0;
    nrealcross = 0;

    bitlength = 0;
    if (ga.nbin>0)
      for (int i=0; i<ga.nbin; i++) bitlength += ga.nbits[i];

    parent_pop=new population;
    child_pop=new  population;
    mixed_pop=new  population;

    allocate_pop(ga.nreal,ga.nbin,ga.nbits,ga.nobj,ga.ncon,parent_pop, ga.popsize);
    allocate_pop(ga.nreal,ga.nbin,ga.nbits,ga.nobj,ga.ncon,child_pop, ga.popsize);
    allocate_pop(ga.nreal,ga.nbin,ga.nbits,ga.nobj,ga.ncon,mixed_pop, 2*ga.popsize);

    allocate_pop(ga.nreal,ga.nbin,ga.nbits,ga.nobj,ga.ncon,feasible_pop, ga.popsize);

    if (recordallpop==1)
    {
       all_pop=new population*[ga.ngen];
       for(int i=0; i<ga.ngen; i++)
       {
         all_pop[i]=new population;
         allocate_pop(ga.nreal,ga.nbin,ga.nbits,ga.nobj,ga.ncon,all_pop[i],ga.popsize);
       }
    }
}

void nsga_pop_feasible(MOGAparam ga,population *pop,population *feasible_pop,int &feasible_popsize)
{
    int i, j, k;
    int ind_id=0;
    for (i=0; i<ga.popsize; i++)
    {
        if (pop->ind[i].constr_violation == 0.0 && pop->ind[i].rank==1)
        {
            for (j=0; j<ga.nobj; j++)
            {
                feasible_pop->ind[ind_id].obj[j]=pop->ind[i].obj[j];
            }
            if (ga.ncon>0)
            {
                for (j=0; j<ga.ncon; j++)
                {
                   feasible_pop->ind[ind_id].constr[j]=pop->ind[i].constr[j];
                }
            }
            if (ga.nreal>0)
            {
                for (j=0; j<ga.nreal; j++)
                {
                   feasible_pop->ind[ind_id].xreal[j]=pop->ind[i].xreal[j];
                }
            }
            if (ga.nbin>0)
            {
                for (j=0; j<ga.nbin; j++)
                {
                    for (k=0; k<ga.nbits[j]; k++)
                    {
                      feasible_pop->ind[ind_id].gene[j][k]=pop->ind[i].gene[j][k];
                    }
                }
            }
            feasible_pop->ind[ind_id].constr_violation=pop->ind[i].constr_violation;
            feasible_pop->ind[ind_id].rank=pop->ind[i].rank;
            feasible_pop->ind[ind_id].crowd_dist=pop->ind[i].crowd_dist;
            ind_id +=1;
      }
    }
   feasible_popsize=ind_id;
}

void nsga_Solving(MOGAparam ga,int recordallpop,population *feasible_pop,int &feasible_popsize,
     void (*funrb)(double*, double*, int**, double*, double*))
{
    int i;
    deb_randomize();
    initialize_pop(ga.popsize,
                   ga.nreal,ga.min_realvar,ga.max_realvar,
                   ga.nbin,ga.nbits,
                   parent_pop);

    if (ga.nbin>0)
       decode_pop(ga.popsize,ga.nbin,ga.nbits,ga.min_binvar,ga.max_binvar,parent_pop);

   //  需要和被解决问题相对应
    evaluate_pop(ga.popsize,ga.ncon,parent_pop,(*funrb));

    assign_rank_and_crowding_distance(ga.popsize,ga.nobj,parent_pop);

    if (recordallpop) all_pop[0]=parent_pop;

    //Print_First_pop();

    for (i=2; i<=ga.ngen; i++)
    {
        selection(ga.popsize,ga.nobj,
                  ga.nreal,
                  ga.pcross_real,ga.eta_c,
                  ga.min_realvar,ga.max_realvar,
                  nrealcross,
                  ga.nbin,
                  ga.pcross_bin,ga.nbits,
                  nbincross,
                  parent_pop,child_pop);

        mutation_pop(ga.popsize,
                     ga.nreal,ga.pmut_real,ga.eta_m,
                     ga.min_realvar,ga.max_realvar,nrealmut,
                     ga.nbin,ga.nbits,ga.pmut_bin,nbinmut,
                     child_pop);
       if (ga.nbin>0)
          decode_pop(ga.popsize,ga.nbin,ga.nbits,
                     ga.min_binvar,ga.max_binvar,
                     child_pop);
        // 和被求解问题有关
        evaluate_pop(ga.popsize,ga.ncon,child_pop,(*funrb));

        merge(ga.popsize,ga.nobj, ga.ncon, ga.nreal,ga.nbin, ga.nbits,
               parent_pop, child_pop, mixed_pop);
		
        fill_nondominated_sort(ga.popsize,ga.nobj,ga.ncon,ga.nreal,
                               ga.nbin,ga.nbits,
                               mixed_pop, parent_pop);

        if (recordallpop==1)  all_pop[i-1]=parent_pop;
    }

 // 满足条件的解
   nsga_pop_feasible(ga,parent_pop,feasible_pop,feasible_popsize);
}

 void nsga_paretoset(MOGAparam ga,int recordallpop,population *feasible_pop,int &feasible_popsize,
                      void (*funrb)(double*, double*, int**, double*, double*))
{
   nsga_InitSolve(ga,feasible_pop,recordallpop);
   nsga_Solving(ga,recordallpop,feasible_pop,feasible_popsize,(*funrb));
}
