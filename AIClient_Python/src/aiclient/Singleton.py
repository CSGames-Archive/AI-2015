'''
Created on Dec 17, 2014

@author: samuel
'''

def Singleton(klass):
    if not klass._instance:
        klass._instance = klass()
    return klass._instance