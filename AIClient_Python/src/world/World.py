'''
Created on Dec 20, 2014

@author: samuel
'''
from event.AddPlayerEvent import AddPlayerEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from world.Team import Team
from enum import Enum

class Entity(Enum):
    EMPTY, BOX, CHARACTER = range(3)

class World(object):
    _instance = None
    yourId = 0
    gameIsStarted = False
    gameIsFinished = False
    teams = []
    map = {}

    def error(self, message):
        print(message)
    
    def joinGame(self, yourId):
        self.yourId = yourId
        print("JoinGameEvent: {}".format(self.yourId))
        
        teamName = "python team (" + str(yourId) + ")"
        characterNames = ["python king (" + str(yourId) + ")", "python soldier (" + str(yourId) + ")"]
        event = AddPlayerEvent(teamName, characterNames)
        queueController = Singleton(QueueController)
        queueController.outEvents.put(event)
        
    def startGame(self, mapWidth, mapHeight, numberOfteam, numberOfCharacter, teamIDs):
        self.gameIsStarted = True
        for index in range(0, numberOfteam):
            self.teams.insert(index, Team(teamIDs[index], numberOfCharacter))
    
    def getTeam(self, teamId):
        for team in self.teams:
            if team.teamId == teamId:
                return team
        return None
    
    def getMyTeam(self):
        return self.getTeam(self.yourId)
    
    def updateBox(self, x, y):
        self.map[x, y] = 1;

    def isBoxAtPosition(self, position):
        if (position.x, position.y) in self.map:
            return True
        return False
        
    def isCharacterAtposition(self, position):
        for team in self.teams:
            for character in team.characters:
                if character.position == position:
                    return True
        return False

    def isMissileAtPosition(self, position) -> bool:
        for team in self.teams:
            for character in team.characters:
                if character.missile.position == position and character.missile.isReady is False:
                    return True
        return False
    
    def whatIsAtPosition(self, position):
        if self.isBoxAtPosition(position):
            return Entity.BOX
        if self.isCharacterAtposition(position):
            return Entity.CHARACTER
        return Entity.EMPTY
    
    def endGame(self):
        print("End game")
        self.gameIsFinished = True
