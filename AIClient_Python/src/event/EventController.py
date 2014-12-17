'''
Created on Dec 16, 2014

@author: samuel
'''

class EventController:
    _instance = None
    
def Singleton(klass):
    if not klass._instance:
        klass._instance = klass()
    
    return klass._instance

