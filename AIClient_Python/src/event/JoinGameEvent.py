'''
Created on Dec 15, 2014

@author: samuel
'''
from event.IngoingEvent import IngoingEvent
from aiclient.Singleton import Singleton
from world.World import World

class JoinGameEvent(IngoingEvent):
    yourId = 0
        
    def execute(self):
        world = Singleton(World)
        world.joinGame(self.yourId)

    def fillArguments(self, string):
        self.yourId = int(string)
        if self.yourId == 0:
            return False
        return True