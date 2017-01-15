'''
 The Web application is used to demo environmental/economic power dispatch shared Library
 
 The Optimized object is the standard IEEE six-generator 30-bus test system 

 * M.A. Abido. A novel multiobjective evolutionary algorithm for environmental/economic power dispatch, Electric Power Systems Research. (65):71-81 , 2003,）
  
 Author: Cheng Tianshi
 Email: chengts95@seu.edu.cn

'''
import tornado.web
import tornado.websocket
import json
import pprint

import biobjloaddispatch_def as seu
import realtime as rt

client = list() 
        
class MainHandler(tornado.web.RequestHandler):

    def get(self):
        self.render("index.html", messages=None)


class dispatchHandler(tornado.web.RequestHandler):

    def post(self):
        
        jsonobj = tornado.escape.json_decode(self.request.body)
        
        print('Post data received')

        for key in jsonobj.keys():
            print( 'key: %s , value: %s' % (key, jsonobj[key]))
        
        loaded=float(jsonobj['key1'])
            
        totalload=loaded/100
        seu.loaddispatch(totalload)

        # new dictionary
        response_to_send = {}
         
        response_to_send['best_cobj'] =seu.best.cobj
        response_to_send['best_eobj'] =seu.best.eobj
      
        received_data_best_load = list()
        for i in range(seu.unitnum):
            received_data_best_load.append(seu.best.xreal[i]*100)
        response_to_send['best_load'] =received_data_best_load
        
        response_to_send['bestc_cobj'] =seu.bestC.cobj
        response_to_send['bestc_eobj'] =seu.bestC.eobj
      
        received_data_bestc_load = list()
        for i in range(seu.unitnum):
            received_data_bestc_load.append(seu.bestC.xreal[i]*100)
        response_to_send['bestc_load'] =received_data_bestc_load
        
        response_to_send['beste_cobj'] =seu.bestE.cobj
        response_to_send['beste_eobj'] =seu.bestE.eobj
     
        received_data_beste_load = list()
        for i in range(seu.unitnum):
            received_data_beste_load.append(seu.bestE.xreal[i]*100)
        response_to_send['beste_load'] =received_data_beste_load
                
        # Pareto Set
        received_data_bestcpop = list()
        for i in range(seu.ga.popsize):
            received_data_bestcpop.append(seu.bestcpop[i])
        response_to_send['bestcpop'] =received_data_bestcpop 
         
        received_data_bestepop = list()
        for i in range(seu.ga.popsize):
            received_data_bestepop.append(seu.bestepop[i])
        response_to_send['bestepop'] = received_data_bestepop

        print('Response to return')
        #pprint.pprint(response_to_send)
    
        self.write(json.dumps(response_to_send))


class realtimeHandler(tornado.web.RequestHandler):
    
    def get(self):
        self.render("realtime.html")    
 
    def post(self):
        
        rt.realtimedata()
            # new dictionary
        response_to_send = {}
         
        received_data_load = list()
        for i in range(seu.unitnum):
            received_data_load.append(rt.rtload[i])
        response_to_send['load'] =received_data_load
        
        received_data_c = list()
        for i in range(seu.unitnum):
            received_data_c.append(rt.rtc[i])
        response_to_send['c'] =received_data_c
        
      
        received_data_e = list()
        for i in range(seu.unitnum):
            received_data_e.append(rt.rte[i])
        response_to_send['e'] =received_data_e
        
        
        response_to_send['sumload'] =rt.rtsumload[0]       
        response_to_send['sumc'] =rt.rtsumc[0]       
        response_to_send['sume'] =rt.rtsume[0]
        
        
        totalload=rt.rtsumload[0]/100
        seu.loaddispatch(totalload)

        # new dictionary
        response_to_send['best_cobj'] =seu.best.cobj
        response_to_send['best_eobj'] =seu.best.eobj
      
        received_data_best_load = list()
        for i in range(seu.unitnum):
            received_data_best_load.append(seu.best.xreal[i]*100)
        response_to_send['best_load'] =received_data_best_load
      
        received_data_best_load_c = list()
        for i in range(seu.unitnum):
            received_data_best_load_c.append(rt.costfun(i,seu.best.xreal[i]))
        response_to_send['best_load_c'] =received_data_best_load_c
      
        received_data_best_load_e = list()
        for i in range(seu.unitnum):
            received_data_best_load_e.append(rt.emissionfun(i,seu.best.xreal[i]))
        response_to_send['best_load_e'] =received_data_best_load_e
       
        print('Response to return')
        pprint.pprint(response_to_send)
    
        self.write(json.dumps(response_to_send))  

class realtimeWSHandler(tornado.websocket.WebSocketHandler):

    def open(self):
        client.append(self)
      
    def on_close(self):
        client.remove(self)
  
    def on_message(self, message):
        rt.realtimedata()
        # new dictionary
        response_to_send = {}
         
        received_data_load = list()
        for i in range(seu.unitnum):
            received_data_load.append(rt.rtload[i])
        response_to_send['load'] =received_data_load
        
        received_data_c = list()
        for i in range(seu.unitnum):
            received_data_c.append(rt.rtc[i])
        response_to_send['c'] =received_data_c
        
      
        received_data_e = list()
        for i in range(seu.unitnum):
            received_data_e.append(rt.rte[i])
        response_to_send['e'] =received_data_e
        
        
        response_to_send['sumload'] =rt.rtsumload[0]       
        response_to_send['sumc'] =rt.rtsumc[0]       
        response_to_send['sume'] =rt.rtsume[0]
        
        print('Response to return')
        pprint.pprint(response_to_send)
    
        self.write(json.dumps(response_to_send))    

class dispatchcfgHandler(tornado.web.RequestHandler):

    def get(self):
        self.render("dispatchcfg.html",popsize=seu.ga.popsize,ngen=seu.ga.ngen,pcross_real=seu.ga.pcross_real,
                                     pmut_real=seu.ga.pmut_real,eta_c=seu.ga.eta_c,eta_m=seu.ga.eta_m)    
    
class dispatchcfg_resetHandler(tornado.web.RequestHandler):

    def post(self):
        jsonobj = tornado.escape.json_decode(self.request.body)
        seu.ga.popsize= int(jsonobj['popsize'])
        seu.ga.ngen=int(jsonobj['ngen'])
        seu.ga.pcross_real=float(jsonobj['pcross_real'])
        seu.ga.pmut_real=float(jsonobj['pmut_real'])
        seu.ga.eta_c=float(jsonobj['eta_c'])
        seu.ga.eta_m=float(jsonobj['eta_m'])
        print('Post data received')
        print(seu.ga.popsize)
        
class unitcharHandler(tornado.web.RequestHandler):

    def get(self):
        self.render("unitchar.html",
                    c00=seu.c[0][0],c10=seu.c[1][0],c20=seu.c[2][0],c30=seu.c[3][0],c40=seu.c[4][0],c50=seu.c[5][0],
                    c01=seu.c[0][1],c11=seu.c[1][1],c21=seu.c[2][1],c31=seu.c[3][1],c41=seu.c[4][1],c51=seu.c[5][1],
                    c02=seu.c[0][2],c12=seu.c[1][2],c22=seu.c[2][2],c32=seu.c[3][2],c42=seu.c[4][2],c52=seu.c[5][2],
                    e00=seu.e[0][0],e10=seu.e[1][0],e20=seu.e[2][0],e30=seu.e[3][0],e40=seu.e[4][0],e50=seu.e[5][0],
                    e01=seu.e[0][1],e11=seu.e[1][1],e21=seu.e[2][1],e31=seu.e[3][1],e41=seu.e[4][1],e51=seu.e[5][1],
                    e02=seu.e[0][2],e12=seu.e[1][2],e22=seu.e[2][2],e32=seu.e[3][2],e42=seu.e[4][2],e52=seu.e[5][2],
                    e03=seu.e[0][3],e13=seu.e[1][3],e23=seu.e[2][3],e33=seu.e[3][3],e43=seu.e[4][3],e53=seu.e[5][3],
                    e04=seu.e[0][4],e14=seu.e[1][4],e24=seu.e[2][4],e34=seu.e[3][4],e44=seu.e[4][4],e54=seu.e[5][4])    
    
    def post(self):
        jsonobj = tornado.escape.json_decode(self.request.body)
        print('Post data received')
        self.write()

 
