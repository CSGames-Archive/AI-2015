'''
Created on Dec 20, 2014

@author: samuel
'''
from world.Character import Character

class Team(object):
    teamId = 0
    characters = []

    def __init__(self, teamId, numberOfCharacter):
        self.teamId = teamId
        for index in range(0, numberOfCharacter):
            self.characters.insert(index, Character(0, 0))
    