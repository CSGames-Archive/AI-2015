'''
Created on Dec 20, 2014

@author: samuel
'''
from event.DropMineEvent import DropMineEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController

class Character(object):
    
    def __init__(self, characterId, positionX, positionY):
        self.characterId = characterId
        self.positionX = positionX
        self.positionY = positionY
        self.mineReady = True
        self.missileReady = True
    
    def move(self, positionX, positionY):
        self.positionX = positionX
        self.positionY = positionY
        
    def dropMine(self):
        if(self.mineReady):
            queueController = Singleton(QueueController)
            event = DropMineEvent(self.characterId)
            queueController.outEvents.put(event)
            self.mineReady = False

    def hitByMine(self):
        # Refactor with life system
        print("ouch!! - Mine")
        
    def mineHit(self):
        self.mineReady = True;
        print("Mine blow!")
        
    def hitByMissile(self):
        # Refactor with life system
        print("ouch!! - Missile")
        
    def missileHit(self):
        self.missileReady = True;
        print("Missile hit target")