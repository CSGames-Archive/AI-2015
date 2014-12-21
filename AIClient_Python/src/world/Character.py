'''
Created on Dec 20, 2014

@author: samuel
'''

class Character(object):
    positionX = 0
    positionY = 0
    
    def __init__(self, positionX, positionY):
        self.positionX = positionX
        self.positionY = positionY
    
    def move(self, positionX, positionY):
        self.positionX = positionX
        self.positionY = positionY
        