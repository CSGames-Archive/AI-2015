'''
Created on Dec 21, 2014

@author: samuel
'''

from enum import Enum
from event.MoveCharacterEvent import MoveCharacterEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from world.World import World

class AIStatus(Enum):
    INIT, LOWER_RIGHT, LOWER_LEFT, UPPER_RIGHT, UPPER_LEFT = range(5)

class AI(object):
    aiStatus = AIStatus.INIT
    queueController = Singleton(QueueController)
    world = Singleton(World)
    
    def tick(self):
        if self.aiStatus == AIStatus.INIT:
            self.init()
        elif self.aiStatus == AIStatus.LOWER_RIGHT:
            self.lowerRight()
        elif self.aiStatus == AIStatus.LOWER_LEFT:
            self.lowerLeft()
        elif self.aiStatus == AIStatus.UPPER_RIGHT:
            self.upperRight()
        elif self.aiStatus == AIStatus.UPPER_LEFT:
            self.upperLeft()
    
    def init(self):
        event1 = MoveCharacterEvent(0, 100, -100)
        self.queueController.outEvents.put(event1)
        event2 = MoveCharacterEvent(1, -100, -100)
        self.queueController.outEvents.put(event2)
        self.aiStatus = AIStatus.LOWER_RIGHT
    
    def lowerRight(self):
        character = self.world.getTeam(self.world.yourId).characters[0]
        if character.positionX == 100 and character.positionY == -100:
            event1 = MoveCharacterEvent(0, -100, -100)
            self.queueController.outEvents.put(event1)
            event2 = MoveCharacterEvent(1, 100, -100)
            self.queueController.outEvents.put(event2)
            self.aiStatus = AIStatus.LOWER_LEFT
    
    def lowerLeft(self):
        pass
    
    def upperRight(self):
        pass
    
    def upperLeft(self):
        pass