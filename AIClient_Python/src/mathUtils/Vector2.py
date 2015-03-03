'''
Created on Jan 6, 2015

@author: samuel
'''


class Vector2(object):

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __eq__(self, other):
        if isinstance(other, Vector2):
            return self.x == other.x and self.y == other.y
        return NotImplemented