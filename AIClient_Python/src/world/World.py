'''
Created on Dec 20, 2014

@author: scarriere
'''
from event.AddPlayerEvent import AddPlayerEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from world.Team import Team
from enum import Enum

class Entity(Enum):
    '''
    An Enum that represent all the entity that can be found in the world
        EMPTY, BOX, CHARACTER, MISSILE
    '''
    EMPTY, BOX, CHARACTER, MISSILE = range(4)

class World(object):
    '''
    Class that contain all the informations about the Teams, Characters and Missiles
        (You can't use any of the functions or variables that start with an "_")
    '''
    _instance = None
    _yourId = 0
    _map = {}
    _gameIsStarted = False
    _gameIsFinished = False
    
    teams = []
    '''
    List of all the teams
        (see :class:`.Team`)
    '''

    def _error(self, message):
        print(message)
    
    def _joinGame(self, yourId):
        self._yourId = yourId
        print("JoinGameEvent: {}".format(self._yourId))
        
        teamName = "python team (" + str(yourId) + ")"
        characterNames = ["python king (" + str(yourId) + ")", "python soldier (" + str(yourId) + ")"]
        event = AddPlayerEvent(teamName, characterNames)
        queueController = Singleton(QueueController)
        queueController.outEvents.put(event)
        
    def _startGame(self, mapWidth, mapHeight, numberOfteam, numberOfCharacter, teamIDs):
        self._gameIsStarted = True
        for index in range(0, numberOfteam):
            self.teams.insert(index, Team(teamIDs[index], numberOfCharacter))
    
    def _updateBox(self, x, y):
        self._map[x, y] = 1;

    def _endGame(self):
        print("End game")
        self._gameIsFinished = True

    def getTeam(self, teamId) -> Team:
        '''
        Return the team that is associate with the given team Id(:class:`int`)
        or None if not found
        
            Important: the team id are not starting at 0
            
        Exemple::
        
            aTeam = world.getTeam(2)
        '''
        for team in self.teams:
            if team._teamId == teamId:
                return team
        return None
    
    def getMyTeam(self) -> Team:
        '''
        Return the team associate with your id(:class:`int`)
        
        Exemple::

            myTeam = world.getMyTeam(2)
        '''
        return self.getTeam(self._yourId)

    def isBoxAtPosition(self, position) -> bool:
        '''
        Check if there's a box at a certain position(:class:`.Vector2`)
        
        Exemple::

            checkBox = world.isBoxAtPosition(Vector2(5,5))
        '''
        if (position.x, position.y) in self._map:
            return True
        return False
        
    def isCharacterAtposition(self, position) -> bool:
        '''
        Check if there's a character(:class:`.Character`)
        at a certain position(:class:`.Vector2`)
        
        Exemple::

            checkCharacter = world.isCharacterAtposition(Vector2(5,5))
        '''
        for team in self.teams:
            for character in team.characters:
                if character.position == position:
                    return True
        return False
    
    def whatIsAtPosition(self, position) -> Entity:
        '''
        Return the Entity(:class:`.Entity`)
        at a certain position(:class:`.Vector2`)
        
        Exemple::

            entity = world.whatIsAtPosition(Vector2(5,5))
        '''
        if self.isBoxAtPosition(position):
            return Entity.BOX
        if self.isCharacterAtposition(position):
            return Entity.CHARACTER
        return Entity.EMPTY

