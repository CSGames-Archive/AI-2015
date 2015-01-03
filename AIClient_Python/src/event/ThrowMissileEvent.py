'''
Created on Jan 2, 2015

@author: samuel
'''
from enum import Enum
from event.OutgoingEvent import OutgoingEvent

class Direction(Enum):
    UP, DOWN, LEFT, RIGHT = range(4)

class ThrowMissileEvent(OutgoingEvent):

    def __init__(self, characterId, direction):
        self.characterId = characterId
        self.direction = direction
        
    def toString(self):
        message = "Game:ThrowMissile:"
        message += str(self.characterId) + self.SEPARATOR
        message += str(self.direction.value)
        
        return message