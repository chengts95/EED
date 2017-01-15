
# -*- coding: utf-8 -*- 

'''
 
 The Optimized object is the standard IEEE six-generator 30-bus test system 

 * M.A. Abido. A novel multiobjective evolutionary algorithm for environmental/economic power dispatch, Electric Power Systems Research. (65):71-81 , 2003,）
  
 Author: Cheng Tianshi
 Email: chengts95@seu.edu.cn

'''
import numpy as np
import biobjloaddispatch_def as seu
import random
import math

rtload=np.zeros(shape=6)
rtc=np.zeros(shape=6)
rte=np.zeros(shape=6)

rtsumload=np.zeros(shape=1)
rtsumc=np.zeros(shape=1)
rtsume=np.zeros(shape=1)

def costfun(i,load):
    return(load*(load*seu.uload[i].coff.c[2]+seu.uload[i].coff.c[1])+seu.uload[i].coff.c[0])

def emissionfun(i,load):
    funcv=0.01*(seu.e[i][0]+(seu.e[i][1]+seu.e[i][2]*load)*load)+seu.e[i][3]*math.exp(seu.e[i][4]*load)
    return funcv;

def realtimedata():
    rtsumload[0]=0
    rtsumc[0]=0
    rtsume[0]=0
    for i in range(6):
        rtload[i]=seu.load_max[i]*0.4-0.01*random.uniform(i,10)
        rtc[i]=costfun(i,rtload[i])
        rte[i]=emissionfun(i,rtload[i])
     
        rtsumc[0]=rtsumc[0]+rtc[i]
        rtsume[0]=rtsume[0]+rte[i]
        rtload[i]=rtload[i]*100
        rtsumload[0]=rtsumload[0]+rtload[i]
  
        
        
        
       
