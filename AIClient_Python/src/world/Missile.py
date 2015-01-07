'''
Created on Jan 6, 2015

@author: samuel
'''
from mathUtils.Vector2 import Vector2

class Missile(object):

    def __init__(self, position):
        self.isReady = True
        self.position = Vector2(position.x, position.y)
        
    def move(self, position):
        self.position.x = position.x
        self.position.y = position.y
