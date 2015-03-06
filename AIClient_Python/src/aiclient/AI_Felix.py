from enum import Enum
from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from mathUtils.Direction import Direction
from world.Character import Character
from world.World import World
from world.Team import Team
from mathUtils.Vector2 import Vector2

'''
Attack and follow strategy
'''
class AI(object):
    queueController = Singleton(QueueController)
    world = Singleton(World)
    otherTeam = None
    oponent = None
    tank1 = None
    firstTick = True

    def initWorld(self):
        self.tank1 = self.world.getMyTeam().getFirstCharacter()
        ':type tank1: Character'
        self.otherTeam = self.world.getOpponentTeam()
        ':type otherTeam: Team'
        self.oponent = self.otherTeam.getSecondCharacter()
        ':type oponent: Character'
        self.firstTick = False

    def tick(self):
        if self.firstTick is True:
            self.initWorld()

        if not self.isAttackable(self.tank1.getPosition(), self.oponent.getPosition()):
            self.tank1.goTo(self.oponent.getPosition())
        else:
            targetDirection = self.getDirectionFromPositions(self.tank1.getPosition(), self.oponent.getPosition())
            if targetDirection is not None:
                self.tank1.shootMissile(targetDirection)

    def getOponent(self) -> Character:
        return self.otherTeam.getFirstCharacter()

    def isAttackable(self, fromposition: Vector2, toposition: Vector2):
        ret = fromposition.x == toposition.x or fromposition.y == toposition.y
        #print("me ({0},{1}) him ({2},{3}) = {4}".format(fromposition.x, fromposition.y, toposition.x,
        #                                                toposition.y, ret))
        return ret

    def getDirectionVector(self, fromposition: Vector2, toposition: Vector2):
        return Vector2(toposition.x-fromposition.x, toposition.y-fromposition.y)

    def getDirectionFromPositions(self, fromposition: Vector2, toposition: Vector2):
        return self.getDirection(self.getDirectionVector(fromposition, toposition))

    def getDirection(self, direction: Vector2) -> Direction:
        if direction.x != 0:
            if direction.x < 0:
                return Direction.LEFT
            else:
                return Direction.RIGHT
        if direction.y != 0:
            if direction.y > 0:
                return Direction.UP
            else:
                return Direction.DOWN
        return None
