'''
Created on Dec 15, 2014

@author: samuel
'''
import time
from event.EventController import EventController
from network.NetworkController import NetworkController
from aiclient.Singleton import Singleton
from world.World import World

eventController = Singleton(EventController)
netController = Singleton(NetworkController)

netController.init()

time.sleep(2)
eventController.executeIngoingEvents()
netController.executeOutgoingEvents()

time.sleep(2)
eventController.executeIngoingEvents()
netController.executeOutgoingEvents()

world = Singleton(World)
if world.gameIsStarted:
    print("Game is started")
    time.sleep(1)

netController.closeConnection()
print(" - end - ")