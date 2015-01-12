'''
Created on Dec 21, 2014

@author: samuel
'''

from enum import Enum
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from world.World import World
from mathUtils.Vector2 import Vector2

class AIStatus(Enum):
    INIT, LOWER_RIGHT, LOWER_LEFT, UPPER_RIGHT, UPPER_LEFT = range(5)

class AI(object):
    aiStatus = AIStatus.INIT
    queueController = Singleton(QueueController)
    world = Singleton(World)

    position1 = Vector2(0,0)
    position2 = Vector2(7,0)
    position3 = Vector2(0,7)
    position4 = Vector2(7,7)
    
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
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        character1.goTo(self.position2)
        character2.goTo(self.position3)
        
        character1.shootRight()
        character2.shootLeft()
        
        self.aiStatus = AIStatus.LOWER_RIGHT
        
        print(self.world.map)
        
        print(self.world.isCharacterAtposition(self.position1))
        print(self.world.isCharacterAtposition(Vector2(0, 4)))
    
    def lowerRight(self):
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        if character1.position == self.position2:
            character1.goTo(self.position1)
            character2.goTo(self.position4)

            character1.dropMine()
            character2.dropMine()
            
            character1.shootLeft()
            character2.shootRight()
            
            self.aiStatus = AIStatus.LOWER_LEFT
    
    def lowerLeft(self):
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        if character1.position == self.position1:
            character1.goTo(self.position4)
            character2.goTo(self.position1)
            
            character1.shootUp()
            character2.shootDown()
            
            character1.dropMine()
            character2.dropMine()
            
            self.aiStatus = AIStatus.UPPER_RIGHT
    
    def upperRight(self):
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        if character1.position == self.position4:
            character1.goTo(self.position3)
            character2.goTo(self.position2)

            character1.shootDown()
            character2.shootUp()

            character1.dropMine()
            character2.dropMine()
            
            self.aiStatus = AIStatus.UPPER_LEFT
    
    def upperLeft(self):
        character1 = self.world.getMyTeam().getFirstCharacter()
        character2 = self.world.getMyTeam().getSecondCharacter()
        
        if character1.position == self.position3:
            character1.goTo(self.position2)
            character2.goTo(self.position3)
            
            character1.shootRight()
            character2.shootLeft()
            
            character1.dropMine()
            character2.dropMine()
            
            self.aiStatus = AIStatus.LOWER_RIGHT
