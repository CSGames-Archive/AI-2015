'''
Created on Dec 20, 2014

@author: samuel
'''
from event.AddPlayerEvent import AddPlayerEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from world.Team import Team

class World(object):
    _instance = None
    yourId = 0
    gameIsStarted = False
    teams = []
    map = {}

    def error(self, message):
        print(message)
    
    def joinGame(self, yourId):
        self.yourId = yourId
        print("JoinGameEvent: {}".format(self.yourId))
        
        teamName = "team" + str(yourId)
        characterNames = ["Character1" + str(yourId), "Character2" + str(yourId)]
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