'''
Created on Dec 20, 2014

@author: samuel
'''
from event.DropMineEvent import DropMineEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from world.Missile import Missile
from mathUtils.Vector2 import Vector2
from event.MoveCharacterEvent import MoveCharacterEvent
from event.ThrowMissileEvent import ThrowMissileEvent, Direction

class Character(object):
    queueController = Singleton(QueueController)
    
    def __init__(self, characterId, position):
        self.characterId = characterId
        self.position = Vector2(position.x, position.y)
        self.mineReady = True
        self.missile = Missile(Vector2(0,0))
        self.life = 3
    
    def move(self, position):
        self.position.x = position.x
        self.position.y = position.y
        
    def goTo(self, position):
        event1 = MoveCharacterEvent(self.characterId, position.x, position.y)
        self.queueController.outEvents.put(event1)
        
    def dropMine(self):
        if(self.mineReady):
            event = DropMineEvent(self.characterId)
            self.queueController.addOutgoingEvent(event)
            self.mineReady = False

    def hitByMine(self):
        if self.isAlive():
            self.life -= 1
        print("ouch!! - Mine")
        
    def mineHit(self):
        self.mineReady = True;
        print("Mine blow!")
        
    def shootMissile(self, direction):
        if(self.missile.isReady):
            event = ThrowMissileEvent(self.characterId, direction)
            self.queueController.addOutgoingEvent(event)
            
    def shootUp(self):
        self.shootMissile(Direction.UP)
        
    def shootDown(self):
        self.shootMissile(Direction.DOWN)
        
    def shootLeft(self):
        self.shootMissile(Direction.LEFT)
        
    def shootRight(self):
        self.shootMissile(Direction.RIGHT)
        
    def hitByMissile(self):
        if self.isAlive():
            self.life -= 1
        print("ouch!! - Missile")
        
    def missileHit(self):
        self.missile.isReady = True;
        print("Missile hit target")
        
    def isAlive(self):
        return self.life > 0
    