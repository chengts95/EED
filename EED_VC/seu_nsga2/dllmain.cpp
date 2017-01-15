// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "typedef.h"
#include "nsga2.h"

#include "sim_nsga2.h"


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


extern "C" __declspec(dllexport) void __stdcall ga_paretoset(MOGAparam ga,population *feasible_pop,int &feasible_popsize,
                 void (*funrb)(double*, double*, int**, double*, double*))
{
   int recordallpop=1;
   nsga_paretoset(ga,recordallpop,feasible_pop,feasible_popsize,(*funrb));
}

extern "C" __declspec(dllexport) void __stdcall ga_deallocate(MOGAparam ga,population *feasible_pop)
{
   int recordallpop=1;
   nsga_deallocate(ga,feasible_pop,recordallpop);
}

// ¼ò»¯Êä³ö
extern "C" __declspec(dllexport) void __stdcall sim_ga_paretoset(nsga2cfg sim_ga,
                 double *min_x,double *max_x,
                 double **x,double **obj,int &feasible_popsize,
                 void (*objfun)(double*, double*, int**, double*, double*))
{
   sim_nsga2_paretoset(sim_ga,min_x,max_x,x,obj,feasible_popsize,(*objfun));
}
