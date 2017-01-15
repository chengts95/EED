/* Definition of random number generation routines */

#include "basicfun.h"

static double seed;
static double oldrand[55];
static int jrand;

/* Create next batch of 55 random numbers */
void advance_random()
{
    int i;
    double new_random;
    for(i=0; i<24; i++)
    {
        new_random = oldrand[i]-oldrand[i+31];
        if(new_random<0.0)
        {
            new_random = new_random+1.0;
        }
        oldrand[i] = new_random;
    }
    for(i=24; i<55; i++)
    {
        new_random = oldrand[i]-oldrand[i-24];
        if(new_random<0.0)
        {
            new_random = new_random+1.0;
        }
        oldrand[i] = new_random;
    }
}

/* Get randomize off and running */
void warmup_random (double seed)
{
    int j1, ii;
    double new_random, prev_random;
    oldrand[54] = seed;
    new_random = 0.000000001;
    prev_random = seed;
    for(j1=1; j1<=54; j1++)
    {
        ii = (21*j1)%54;
        oldrand[ii] = new_random;
        new_random = prev_random-new_random;
        if(new_random<0.0)
        {
            new_random += 1.0;
        }
        prev_random = oldrand[ii];
    }
    advance_random();
    advance_random();
    advance_random();
    jrand = 0;
}

/* Get seed number for random and start it up */
void deb_randomize()
{
    int i;
    seed=0.5;
    for(i=0; i<=54; i++)
        oldrand[i] = 0.0;
    jrand=0;
    warmup_random(seed);
}

/* Fetch a single random number between 0.0 and 1.0 */
double randomperc()
{
    jrand++;
    if(jrand>=55)
    {
        jrand = 1;
        advance_random();
    }
    return((double)oldrand[jrand]);
}

/* Fetch a single random integer between low and high including the bounds */
int rnd (int low, int high)
{
    int res;
    if (low >= high)
    {
        res = low;
    }
    else
    {
        res = low + (randomperc()*(high-low+1));
        if (res > high)
        {
            res = high;
        }
    }
    return (res);
}

/* Fetch a single random real number between low and high including the bounds */
double rndreal (double low, double high)
{
    return (low + (high-low)*randomperc());
}


