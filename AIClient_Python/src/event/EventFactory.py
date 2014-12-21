'''
Created on Dec 16, 2014

@author: samuel
'''
from event.JoinGameEvent import JoinGameEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from event.GameStartEvent import GameStartEvent

class EventFactory(object):
    @staticmethod
    def generateEvent(message):
        messageParts = message.split(":", 1)
        event = EventFactory.createEvent(messageParts[0])
        if event != None:
            event.fillArguments(messageParts[1])
            queueController = Singleton(QueueController)
            queueController.addIngoingEvent(event)
    
    @staticmethod
    def createEvent(eventType):
        if eventType == "JoinGame":
            return JoinGameEvent()
        elif eventType == "GameStart":
            return GameStartEvent()
        return None