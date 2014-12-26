'''
Created on Dec 20, 2014

@author: samuel
'''

class Character(object):
    
    def __init__(self, positionX, positionY):
        self.positionX = positionX
        self.positionY = positionY
    
    def move(self, positionX, positionY):
        self.positionX = positionX
        self.positionY = positionY
        