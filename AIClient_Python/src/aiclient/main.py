'''
Created on Dec 15, 2014

@author: samuel
'''
import time
from event.EventController import EventController
from network.NetworkController import NetworkController
from aiclient.Singleton import Singleton
from world.World import World
from event.MoveCharacterEvent import MoveCharacterEvent
from event.QueueController import QueueController

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
    moveEvent = MoveCharacterEvent(0, -50, 50)
    queueController = Singleton(QueueController)
    queueController.outEvents.put(moveEvent)
    netController.executeOutgoingEvents()
    time.sleep(1)

netController.closeConnection()
print(" - end - ")