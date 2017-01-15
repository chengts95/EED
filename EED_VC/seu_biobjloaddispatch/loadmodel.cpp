#include "loadmodel.h"
#include <math.h>

static int unitnumber;
static float totalload;
static float c[100][10];
static float e[100][10];

void initloadmodel(int unitnum,unitload *uload,float sumtotal)
{
  unitnumber=unitnum;
  totalload=sumtotal;
  for(int i=0; i<unitnumber; i++)
  {
    c[i][0]=uload[i].coff.c[0];
    c[i][1]=uload[i].coff.c[1];
    c[i][2]=uload[i].coff.c[2];
    for(int j=0; j<enum; j++)
      e[i][j]=uload[i].coff.e[j];
 }
}

float costfun(int uid,float load)
{
   float funcv;
   funcv = load*(c[uid][2] * load + c[uid][1]) + c[uid][0];
   return (funcv);
}

float emissionfun(int uid,float load)
{
  double funcv;
  //  funcv=0.01*(e[uid][0]+(e[uid][1]+e[uid][2]*load)*load)+e[uid][3]*exp(e[uid][4]*load);
  funcv = load*(e[uid][2] * load + e[uid][1]) + e[uid][0];
  return (funcv);
}

void problem(double *xreal, double *xbin, int **gene,double *obj, double *constr)
{
    obj[0] =costfun(0,xreal[0]);
    obj[1] =emissionfun(0,xreal[0]);
    for(int i=1; i<unitnumber; i++)
    {
      obj[0] +=costfun(i,xreal[i]) ;
      obj[1] += emissionfun(i,xreal[i]);
    }
 //  约束处理
//   只有constr[0]=0时，约束条件才满足ind.constr_violation
    constr[0]=totalload;
    for(int i =0; i<unitnumber; i++)
      constr[0] -=xreal[i];
    if (constr[0]>0.05) //很重要
      constr[0] =-fabs(constr[0]); //约束条件不满足时，数值一定为负
    else constr[0]=0.0;

}
