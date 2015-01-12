'''
Created on Dec 16, 2014

@author: samuel
'''
from event.JoinGameEvent import JoinGameEvent
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from event.GameStartEvent import GameStartEvent
from event.UpdateCharacterEvent import UpdateCharacterEvent
from event.MineHitEvent import MineHitEvent
from event.MissileHitEvent import MissileHitEvent
from event.UpdateMissileEvent import UpdateMissileEvent
from event.UpdateBoxEvent import UpdateBoxEvent

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
        elif eventType == "UpdateCharacter":
            return UpdateCharacterEvent()
        elif eventType == "MineHit":
            return MineHitEvent()
        elif eventType == "MissileHit":
            return MissileHitEvent()
        elif eventType == "UpdateMissile":
            return UpdateMissileEvent()
        elif eventType == "UpdateBox":
            return UpdateBoxEvent()
        return None