#!/usr/bin/env python
"""
Very simple HTTP server in python.
Usage::
    ./dummy-web-server.py [<port>]
Send a GET request::
    curl http://localhost
Send a HEAD request::
    curl -I http://localhost
Send a POST request::
    curl -d "foo=bar&bin=baz" http://localhost
"""
from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
from os import curdir, sep
import SocketServer
import os.path
import serial
import time


ser = 0
if os.path.exists('/dev/ttyACM0'):
    ser = serial.Serial('/dev/ttyACM0', 9600)

class S(BaseHTTPRequestHandler):
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

    def do_GET(self):
        print "get path =" , self.path
        if self.path == "/favicon.ico" :
           print "favicon request"
           f = open(curdir + sep + self.path)
           self.wfile.write(f.read())
			  
        elif self.path == "/" :
           print "getting root"
           self.path="/index.html" 
           #load html file, and send it to client
           self._set_headers()
           f = open(curdir + sep + self.path)
           #self.send_response(200)
           #self.send_header('Content-type','text/html')
           self.end_headers()
           self.wfile.write(f.read())
        elif self.path == "/jscolor.js" :
           print "getting js"
           f = open(curdir + sep + self.path)
           self.send_response(200)
           self.wfile.write(f.read())
        
        else : #test with adding colour directly into GET path
           sendSerialColour(self.path[1:7])
           self.wfile.write("<html><body><h1>manual colour set OK</h1></body></html>")

    def do_HEAD(self):
        self._set_headers()
        
    def do_POST(self):
        # Doesn't do anything with posted data
        content_len = int(self.headers.getheader('content-length',0))
        print "post length=",content_len
        post_body = self.rfile.read(content_len)
        print "post received: ", post_body
        if content_len == 6: #rough and dirty check
           sendSerialColour(post_body)
        self._set_headers()
        self.wfile.write("<html><body><h1>POST!</h1></body></html>")
        
def sendSerialColour(hex_str):
   print "hexstr=",hex_str
   cRed = int(hex_str[0:2],16)
   cGreen = int(hex_str[2:4],16)
   cBlue = int(hex_str[4:6],16)
   print "setting serial RGB: ", cRed,":", cGreen,":", cBlue
   if (ser != 0):
       ser.write(bytearray(["c", cRed, cGreen, cBlue]))
	

def run(server_class=HTTPServer, handler_class=S, port=80):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print 'Starting httpd...'
    httpd.serve_forever()

if __name__ == "__main__":
    from sys import argv

    if len(argv) == 2:
        run(port=int(argv[1]))
    else:
        run()
