'''
Created on Jan 6, 2015

@author: samuel
'''
from mathUtils.Vector2 import Vector2
from mathUtils.Direction import Direction

class Missile(object):

    def __init__(self, position):
        self.isReady = True
        self.position = Vector2(position.x, position.y)
        self.direction = Direction.UP
        
    def move(self, position, direction):
        self.position.x = position.x
        self.position.y = position.y
        self.direction = direction
