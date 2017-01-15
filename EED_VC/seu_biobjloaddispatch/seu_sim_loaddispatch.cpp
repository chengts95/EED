//---------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "sim_loaddispatch.h"

#define EXPORT extern "C" __declspec(dllexport) __stdcall

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
        return 1;
}
//---------------------------------------------------------------------------

EXPORT void  seu_biobjloaddispatch(nsga2cfg ga,
                 int unitnum,unitload *uload,double totalload,
                 double **x,double **obj,int &feasible_popsize,
                 loadv &bestC,loadv &bestE,loadv &best)
{
    sim_dispatch(ga,
             unitnum,uload,totalload,
             x,obj,feasible_popsize,
             bestC,bestE,best);
}
 
