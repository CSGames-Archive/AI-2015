'''
Created on Dec 20, 2014

@author: samuel
'''

class Character(object):
    
    def __init__(self, characterId, positionX, positionY):
        self.characterId = characterId
        self.positionX = positionX
        self.positionY = positionY
        self.mineReady = True
    
    def move(self, positionX, positionY):
        self.positionX = positionX
        self.positionY = positionY
        