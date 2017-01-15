# -*- coding: utf-8 -*- 

'''
 
 The Optimized object is the standard IEEE six-generator 30-bus test system 

 * M.A. Abido. A novel multiobjective evolutionary algorithm for environmental/economic power dispatch, Electric Power Systems Research. (65):71-81 , 2003,）
  
 Author: Cheng Tianshi
 Email: chengts95@seu.edu.cn

'''
from ctypes import windll,c_double,c_int,c_float,POINTER,byref,Structure
import numpy as np

class nsga2cfg(Structure):
    _fields_ = [("nreal",c_int),
                ("nobj",c_int),
                ("ncon",c_int),
                ("popsize",c_int),
                ("ngen",c_int),
                ("pcross_real",c_double),
                ("pmut_real",c_double),
                ("eta_c",c_double),
                ("eta_m",c_double)]
          
class curvecoff(Structure):
    _fields_ = [("c",c_float*3),
                ("e",c_float*5)]

class unitload(Structure):
    _fields_ = [("min",c_float),
                ("max",c_float),
                ("coff",curvecoff)]

class loadv(Structure):
    _fields_ = [("xreal",c_float*10),
                ("cobj",c_float),
                ("eobj",c_float)]

unitnum=c_int()
totalload=c_double()
ga=nsga2cfg()
popsize=c_int()
bestC=loadv()
bestE=loadv()
best=loadv()
c = (c_double*6*3)()
e = (c_double*6*5)()

load_min =[0.05,0.05,0.05,0.05,0.05,0.05]
load_max = (c_double*6)()
load_max =[1.5,1.5,1.15,1.5,1.5,1.5]

c=[[10,200,100],
   [10,150,120],
   [20,180,40],
   [10,100,60],
   [20,180,40],
   [10,150,100]]

e=[[4.091,-5.554,6.490,2.0e-4,2.857],
   [2.543,-6.047,5.638,5.0e-4,3.333],
   [4.258,-5.094,4.586,1.0e-6,8.000],
   [5.426,-3.550,3.380,2.0e-3,2.000],
   [4.258,-5.094,4.586,1.0e-6,8.000],
   [6.131,-5.555,5.151,1.0e-5,6.667]]

unitnum=6

ga.nreal=unitnum
ga.nobj=2
ga.ncon=1
ga.popsize=200
ga.ngen=200
ga.pcross_real=0.9
ga.pmut_real=0.1
ga.eta_c=20
ga.eta_m=15
    
bestcpop=np.zeros(shape=(ga.popsize))
bestepop=np.zeros(shape=(ga.popsize))
   
uload=(unitload*unitnum)()
for i in range(unitnum):
    uload[i].min = load_min[i]
    uload[i].max = load_max[i]
    for j in range(3):
        uload[i].coff.c[j]=c[i][j]
    for j in range(5):
        uload[i].coff.e[j]=e[i][j] 
        
mydll = windll.seu_biobjloaddispatch
f = mydll.seu_biobjloaddispatch

x = (POINTER(c_double) * ga.popsize)()
for i in range(ga.popsize):
    x[i] = (c_double * ga.nreal)()
        
obj = (POINTER(c_double) * ga.popsize)()
for i in range(ga.popsize):
    obj[i] = (c_double *ga.nobj)()
        
def loaddispatch(totalload):

    f(ga,unitnum,uload,c_double(totalload),byref(x),byref(obj),byref(popsize),byref(bestC),byref(bestE),byref(best))

    for i in range(ga.popsize):
        bestcpop[i]=obj[i][0]
   
    for i in range(ga.popsize):
        bestepop[i]=obj[i][1]
