'''
Created on Dec 17, 2014

@author: samuel
'''
import socket

def Singleton(klass):
    if not klass._instance:
        klass._instance = klass()
    return klass._instance

class NetworkController(object):
    _instance = None
    HOST, PORT = "localhost", 1337
    webSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    def __init__(self):
        try:
            self.webSocket.connect(self.HOST, self.PORT)
        except:
            print("Cannot connect to server")

    def sendMessage(self, message):
        try:
            self.webSocket.sendall(message.decode())
        except:
            print("Error while sending message")
        
    def init(self):
        self.sendMessage("AIClientReady")
        # Start reading thread