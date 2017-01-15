//---------------------------------------------------------------------------
#ifndef sim_paretoset_analyzeH
#define sim_paretoset_analyzeH

#include "loadmodel.h"
#include "seu_sim_nsga2lib.h"

void SingleBestSolutionInParetoSet(nsga2cfg ga,double **x,double **obj,int feasible_popsize,
                                   loadv &bestC,loadv &bestE);

void BestCompromiseSolutionInParetoSet(nsga2cfg ga,double **x,double **obj,int feasible_popsize,
                                       loadv &best);


//---------------------------------------------------------------------------
#endif
