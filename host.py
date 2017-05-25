# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import socket;  
import threading;
import struct;
import cv2
import time
import os
import numpy

class webCamera: 
    def __init__(self, resolution = (640, 480), host = ("", 7999)):      
        self.resolution = resolution;      
        self.host = host;      
        self.setSocket(self.host);    
        self.img_quality = 15
    def setImageResolution(self, resolution):      
        self.resolution = resolution;  
    def setHost(self, host):      
        self.host = host;  
    def setSocket(self, host):      
        self.socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM); #创建服务器套接字                 
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1);#设置套接字参数              
        self.socket.bind(self.host);      #绑定地址到套接字
        self.socket.listen(5);  #开始TCP监听，最多允许5个链接进来    
        print("Server running on port:%d" % host[1]);
    def recv_config(self,client):    
        info = struct.unpack("lhh",client.recv(12)); #对收到的unsigned long ,unsingned short 在python中都为整型  ，接收tcp数据缓冲为8 
        if info[0]>911:        #print(info[0])        
            self.img_quality=int(info[0])-911              
            self.resolution=list(self.resolution)        
            self.resolution[0]=info[1]        
            self.resolution[1]=info[2]        
            self.resolution=tuple(self.resolution)                
            return 1    
        else :        
            return 0
    def _processConnection(self, client,addr):     
        if(self.recv_config(client)==0):        
            return    
        camera = cv2.VideoCapture(0)    
        encode_param=[int(cv2.IMWRITE_JPEG_QUALITY),self.img_quality] #  cv2.IMWRITE_JPEG_QUALITY类型为Long，必须转换成int，    img_quality为图片质量，为0-100间      
        f = open("video_info.txt",'a+')  
#python3中  
        #print("Got connection from %s:%d" % (addr[0], addr[1]),file=f)    
        #print("像素为:%d * %d"%(self.resolution[0],self.resolution[1]),file=f)    
        #print ("打开摄像头成功",file=f)    
        #print("连接开始时间:%s"%time.strftime("%Y-%m-%d %H:%M:%S", 
        #        time.localtime(time.time())),file=f) 
#python2 中
        print >> f,"Got connection from %s:%d" % (addr[0], addr[1])
        print >> f,"像素为:%d * %d" %(self.resolution[0],self.resolution[1])
        print >> f,"打开摄像头成功"
        print >> f,"连接开始时间:%s"%time.strftime("%Y-%m-%d %H:%M:%S", 
                time.localtime(time.time()))
        f.close()    
        while(1):        
            time.sleep(0.13)        
            (grabbed, self.img) = camera.read()        
            self.img  = cv2.resize(self.img,self.resolution)             
            result, imgencode = cv2.imencode('.jpg',self.img,encode_param)        
            img_code = numpy.array(imgencode)        
            self.imgdata  = img_code.tostring()                   
            try:                    
                client.send(struct.pack("lhh",len(self.imgdata),
                        self.resolution[0],self.resolution[1])+self.imgdata); #发送图片信息(图片长度,分辨率,图片内容)                
            except:            
                f = open("video_info.txt", 'a+')            
            #    print("%s:%d disconnected!" % (addr[0], addr[1]),file=f);            
             #   print("连接结束时间:%s"%time.strftime("%Y-%m-%d %H:%M:%S", 
             #       time.localtime(time.time())),file=f)      
             #   print("****************************************",file=f)
                print >> f,"%s:%d disconnected!" % (addr[0], addr[1])        
                print >> f,"连接结束时间:%s"%time.strftime("%Y-%m-%d %H:%M:%S", 
                    time.localtime(time.time()))      
                print >> f,"****************************************"

                camera.release()            
                f.close()            
                return;
    def run(self):      
        while(1):        
            client,addr = self.socket.accept();        
            clientThread = threading.Thread(target = self._processConnection, 
                args = (client, addr, ));  #有客户端连接时产生新的线程进行处理                      
            clientThread.start();
def main():      
    cam = webCamera();               
    cam.run();  
if __name__ == "__main__":      
    main();






