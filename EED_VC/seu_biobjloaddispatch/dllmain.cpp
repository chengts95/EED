// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "sim_loaddispatch.h"

#define EXPORT extern "C" __declspec(dllexport)

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

EXPORT void  __stdcall seu_biobjloaddispatch(nsga2cfg ga,
                 int unitnum,unitload *uload,double totalload,
                 double **x,double **obj,int &feasible_popsize,
                 loadv &bestC,loadv &bestE,loadv &best)
{
    sim_dispatch(ga,
             unitnum,uload,totalload,
             x,obj,feasible_popsize,
             bestC,bestE,best);

}
 

EXPORT int  __stdcall biobjloaddispatch(nsga2cfg &ga,
                 int unitnum,unitload *uload,double totalload,
				 int &feasible_popsize,
                 loadv &bestC,loadv &bestE,loadv &best)
{
    double **x;
    double **obj;
	x = new double*[ga.popsize];
	obj = new double*[ga.popsize];
    for (int i=0; i<ga.popsize; i++)
	{ 
	 	 x[i]=new double[ga.nreal];
	   obj[i]=new double[ga.nobj];
	}
   
	/*sim_dispatch(ga,
               unitnum,uload,totalload,
             x,obj,feasible_popsize,
            bestC,bestE,best);
*/
   return (ga.nreal+ga.popsize+ga.nobj);
}
 