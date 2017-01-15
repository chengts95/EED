//---------------------------------------------------------------------------

#ifndef sim_loaddispatchH
#define sim_loaddispatchH

#include "seu_sim_nsga2lib.h"
#include "loadmodel.h"
#include "sim_paretoset_analyze.h"

void sim_dispatch(nsga2cfg ga,
             int unitnum,unitload *uload,double totalload,
             double **x,double **obj,int &feasible_popsize,
             loadv &bestC,loadv &bestE,loadv &best);

//---------------------------------------------------------------------------
#endif
