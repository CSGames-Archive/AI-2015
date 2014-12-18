'''
Created on Dec 15, 2014

@author: samuel
'''
from event.EventController import EventController, Singleton
from network.NetworkController import NetworkController

eventController = Singleton(EventController)

netController = Singleton(NetworkController)
netController.init()

netController.readFunctionThread()

eventController.executeAllEvents()

netController.closeConnection()