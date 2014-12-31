'''
Created on Dec 20, 2014

@author: samuel
'''
from world.Character import Character

class Team(object):

    def __init__(self, teamId, numberOfCharacter):
        self.teamId = teamId
        self.characters = []
        for index in range(0, numberOfCharacter):
            self.characters.insert(index, Character(index, 0, 0))
    