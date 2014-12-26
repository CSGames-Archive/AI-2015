'''
Created on Dec 20, 2014

@author: samuel
'''
from event.IngoingEvent import IngoingEvent
from aiclient.Singleton import Singleton
from world.World import World

class GameStartEvent(IngoingEvent):

    def __init__(self):
        self.numberOfTeam = 0
        self.numberOfCharacter = 0
        self.teamsIds = []

    def fillArguments(self, string):
        numberParts = string.split(":", 2)
        self.numberOfTeam = int(numberParts[0])
        self.numberOfCharacter = int(numberParts[1])
        
        # The last number is the game client id that we don't need
        teamIds = numberParts[2].split(":", self.numberOfTeam)
        for index in range(0, self.numberOfTeam):
            self.teamsIds.insert(index, int(teamIds[index]))
            
    def execute(self):
        world = Singleton(World)
        world.startGame(self.numberOfTeam, self.numberOfCharacter, self.teamsIds)