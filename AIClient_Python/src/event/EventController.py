'''
Created on Dec 16, 2014

@author: samuel
'''

import queue
from event.IngoingEvent import IngoingEvent
from event.OutgoingEvent import OutgoingEvent
from network.NetworkController import NetworkController

def Singleton(klass):
    if not klass._instance:
        klass._instance = klass()
    return klass._instance

class EventController:
    _instance = None
    outEvents = queue.Queue()
    inEvents = queue.Queue()

    def addOutgoingEvent(self, event):
        self.outEvents.put(OutgoingEvent(event))
    
    def addIngoingEvent(self, event):
        self.inEvents.put(IngoingEvent(event))
    
    def executeAllEvents(self):
        self.executeIngoingEvents()
        self.executeOutgoingEvents()
    
    def executeIngoingEvents(self):
        while not self.inEvents.empty():
            event = IngoingEvent(self.inEvents.get())
            event.execute()
    
    def executeOutgoingEvents(self):
        while not self.outEvents.empty():
            event = OutgoingEvent(self.outEvents.get())
            netController = Singleton(NetworkController)
            netController.sendMessage(event.toString())