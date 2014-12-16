'''
Created on Dec 15, 2014

@author: samuel
'''
from event.IngoingEvent import IngoingEvent

class JoinGameEvent(IngoingEvent):

    def __init__(self):
        self.yourId = 0
        
    def execute(self):
        print("JoinGameEvent: {}".format(self.yourId))

    def fillArguments(self, string):
        self.yourId = int(string)
        if self.yourId == 0:
            return False
        return True