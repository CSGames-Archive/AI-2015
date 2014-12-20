'''
Created on Dec 15, 2014

@author: samuel
'''
import time
from event.EventController import EventController
from network.NetworkController import NetworkController
from aiclient.Singleton import Singleton

eventController = Singleton(EventController)

netController = Singleton(NetworkController)
netController.init()

time.sleep(2)

eventController.executeIngoingEvents()
netController.executeOutgoingEvents()

netController.closeConnection()