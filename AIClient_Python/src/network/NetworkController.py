'''
Created on Dec 17, 2014

@author: samuel
'''
import socket
import sys
from event.EventFactory import EventFactory

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
            self.webSocket.connect((self.HOST, self.PORT))
        except:
            print("Cannot connect to server", sys.exc_info()[0])

    def sendMessage(self, message):
        try:
            self.webSocket.sendall(message.encode())
        except:
            print("Error while sending to the socket", sys.exc_info()[0])
        
    def readMessage(self):
        try:
            message = self.webSocket.recv(1024)
            return message
        except:
            print("Error while reading from the socket", sys.exc_info()[0])
            return ""
        
    def init(self):
        self.sendMessage("AIClientReady\n")
        # Start reading thread
    
    def readFunctionThread(self):
        mustExit = False
        while not mustExit:
            message = self.readMessage()
            
            if message == "Net:OkForExit" or message == "":
                mustExit = True
                break
            
            self.dispatchMessage(message.decode())
    
    def dispatchMessage(self, message):
        messageParts = message.split(":", 1)
        if messageParts[0] == "Net":
            pass
            self.dispatchNetMessage(message)
        elif messageParts[0] == "Game":
            EventFactory.generateEvent(message)
        
    def dispatchNetMessage(self, message):
        if message == "JoinGameFailed":
            print("JoinGameFailed")
        elif message == "ErrorGameClientDisconnect":
            print("Error : the game client was disconnected")
        else:
            print("unknow net message:" + message)
        
    def closeConnection(self):
        self.sendMessage("Exit")
        #reader thread join
        self.webSocket.close()
        