#ifndef NSGA2H
#define NSGA2H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "typedef.h"

void nsga_paretoset(MOGAparam ga,int recordallpop,population *feasible_pop,int &feasible_popsize,
                    void (*funrb)(double*, double*, int**, double*, double*));

void nsga_deallocate(MOGAparam ga,population *feasible_pop,int recordallpop);

#endif
