'''
Created on Dec 17, 2014

@author: samuel
'''
import socket
import sys
import threading
import time
from event.EventFactory import EventFactory
from aiclient.Singleton import Singleton
from event.QueueController import QueueController

class NetworkController(object):
    _instance = None
    HOST, PORT = "localhost", 1337
    webSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    readerThread = None
    connected = False
    
    def __init__(self):
        self.readerThread = threading.Thread(target=self.readFunctionThread)
        try:
            self.webSocket.connect((self.HOST, self.PORT))
            self.connected = True
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
            return "".encode()
        
    def init(self):
        self.sendMessage("AIClientReady\n")
        self.readerThread.start()
    
    def executeOutgoingEvents(self):
        queueController = Singleton(QueueController)
        while not queueController.outEvents.empty():
            event = queueController.outEvents.get()
            self.sendMessage(event.toString() + "\n")
    
    def readFunctionThread(self):
        mustExit = False
        while not mustExit:
            message = self.readMessage().decode()
            
            if message == "Net:OkForExit\n" or message == "":
                mustExit = True
                self.connected = False
                break
            
            self.dispatchMessage(message)
    
    def dispatchMessage(self, message):
        messageParts = message.split(":", 1)
        if messageParts[0] == "Net":
            self.parseNetMessage(messageParts[1])
        elif messageParts[0] == "Game":
            EventFactory.generateEvent(messageParts[1])
        
    def parseNetMessage(self, message):
        if message == "JoinGameFailed":
            self.connectionRetry()
        elif message == "ErrorGameClientDisconnect":
            print("Error : the game client was disconnected")
        else:
            print("unknow net message:" + message)
    
    def closeConnection(self):
        self.sendMessage("Exit")
        self.readerThread.join()
        self.webSocket.close()
        self.connected = False
        
    def connectionRetry(self):
        print("Error : the game client was not connected")
        print("Info : connection retry in few seconds...")
        time.sleep(2)
        self.sendMessage("AIClientReady\n")