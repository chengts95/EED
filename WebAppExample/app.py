# -*- coding: utf-8 -*- 

'''
 The Web application is used to demo environmental/economic power dispatch shared Library
 
 The Optimized object is the standard IEEE six-generator 30-bus test system 

 * M.A. Abido. A novel multiobjective evolutionary algorithm for environmental/economic power dispatch, Electric Power Systems Research. (65):71-81 , 2003,）
  
 Author: Cheng Tianshi
 Email: chengts95@163.com

'''
import tornado.web
import tornado.httpserver
import tornado.ioloop
import tornado.options

import biobjloaddispatch_handler

class aboutHandler(tornado.web.RequestHandler):

    def get(self):
        self.render("about.html")    

class Application(tornado.web.Application):
    def __init__(self):
        handlers = [
            (r"/", biobjloaddispatch_handler.MainHandler),
            (r"/dispatch/", biobjloaddispatch_handler.dispatchHandler),
            (r"/realtime/", biobjloaddispatch_handler.realtimeHandler),
            (r"/realtime/ws",biobjloaddispatch_handler.realtimeWSHandler),
            (r"/unitchar/", biobjloaddispatch_handler.unitcharHandler),
            (r"/dispatchcfg/", biobjloaddispatch_handler.dispatchcfgHandler),
            (r"/dispatchcfg_reset/", biobjloaddispatch_handler.dispatchcfg_resetHandler),
            (r"/about/", aboutHandler)
        ]
        
        settings = {
            'template_path': 'templates',
            'static_path': 'static'
        }
        tornado.web.Application.__init__(self, handlers, **settings)

if __name__ == '__main__':
    tornado.options.parse_command_line()
    
    app = Application()
    server = tornado.httpserver.HTTPServer(app)
    server.listen(8000)
    tornado.ioloop.IOLoop.instance().start()
   

