//---------------------------------------------------------------------------
#ifndef loadmodelH
#define loadmodelH

#define cnum 3
#define enum 3

struct curvecoff
{
	float c[cnum];
	float e[enum];
};

struct unitload
{
   float min,max;
   curvecoff coff;
};

struct loadv
{
    float xreal[100];
    float cobj,eobj;
};

 void initloadmodel(int unitnum,unitload *uload,float sumtotal);

 void problem(double *xreal, double *xbin, int **gene,double *obj, double *constr);


//---------------------------------------------------------------------------
#endif
