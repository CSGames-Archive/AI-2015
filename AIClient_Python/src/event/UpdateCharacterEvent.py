'''
Created on Dec 21, 2014

@author: samuel
'''
from event.IngoingEvent import IngoingEvent
from world.World import World
from aiclient.Singleton import Singleton

class UpdateCharacterEvent(IngoingEvent):

    def __init__(self):
        self.teamId = 0
        self.characterId = 0
        self.positionX = 0
        self.positionY = 0
    
    def fillArguments(self, string):
        arguments = string.split(":", 4)
        
        self.teamId = int(arguments[0])
        self.characterId = int(arguments[1])
        self.positionX = int(arguments[2])
        self.positionY = int(arguments[3])
        
    def execute(self):
        world = Singleton(World)
        world.getTeam(self.teamId).characters[self.characterId].move(self.positionX, self.positionY)
        