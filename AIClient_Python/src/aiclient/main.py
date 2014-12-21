'''
Created on Dec 15, 2014

@author: samuel
'''
import time
from event.EventController import EventController
from network.NetworkController import NetworkController
from aiclient.Singleton import Singleton
from world.World import World
from aiclient.AI import AI

eventController = Singleton(EventController)
world = Singleton(World)
netController = Singleton(NetworkController)
ai = AI()

netController.init()

while netController.connected:
    eventController.executeIngoingEvents()
    
    if world.gameIsStarted:
        ai.tick()
    
    netController.executeOutgoingEvents()
    time.sleep(0.03)

netController.closeConnection()
print(" - end - ")