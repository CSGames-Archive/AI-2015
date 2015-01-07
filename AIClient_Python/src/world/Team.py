'''
Created on Dec 20, 2014

@author: samuel
'''
from world.Character import Character
from mathUtils.Vector2 import Vector2

class Team(object):

    def __init__(self, teamId, numberOfCharacter):
        self.teamId = teamId
        self.characters = []
        for index in range(0, numberOfCharacter):
            self.characters.insert(index, Character(index, Vector2(0,0)))
    
    def getFirstCharacter(self):
        return self.characters[0]
    
    def getSecondCharacter(self):
        return self.characters[1]