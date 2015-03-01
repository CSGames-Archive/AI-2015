'''
Created on Jan 24, 2015

@author: samuel
'''
from event.IngoingEvent import IngoingEvent
from aiclient.Singleton import Singleton
from world.World import World

class EndGameEvent(IngoingEvent):

    def __init__(self):
        pass
    
    def fillArguments(self, string):
        pass
                
    def execute(self):
        world = Singleton(World)
        world.endGame()
        