from aiclient.Singleton import Singleton
from event.QueueController import QueueController
from mathUtils.MathUtils import MathUtils
from world.Character import Character
from world.World import World
from mathUtils.Vector2 import Vector2
from aiclient.AIDefault import AIDefault

'''
Attack and follow strategy
'''
class MyAI(AIDefault):
    queueController = Singleton(QueueController)
    world = Singleton(World)
    otherTeam = None
    oponent = None
    tank1 = None
    firstTick = True
    oponentLastPosition = None

    def initWorld(self):
        self.tank1 = self.world.getMyTeam().getFirstCharacter()
        ':type tank1: Character'
        self.otherTeam = self.world.getOtherTeam()
        ':type otherTeam: Team'
        self.oponent = self.otherTeam.getSecondCharacter()
        ':type oponent: Character'
        self.firstTick = False

    def tick(self):
        self.initWorld()
        if self.world.getMyTeam().getFirstCharacter().getPosition() ==\
                self.world.getOtherTeam().getSecondCharacter().getPosition():
            return None

        if self.isAttackable(self.tank1.getPosition(), self.oponent.getPosition()):
            targetDirection = MathUtils.getDirectionFromPositions(self.tank1.getPosition(), self.oponent.getPosition())
            self.tank1.shootMissile(targetDirection)
            print('shoot')
        elif self.oponent.getPosition() != self.oponentLastPosition:
            self.tank1.goTo(self.oponent.getPosition())
            self.oponentLastPosition = self.oponent.getPosition()

    def getOponent(self) -> Character:
        return self.otherTeam.getFirstCharacter()

    def isAttackable(self, fromposition: Vector2, toposition: Vector2):
        ret = fromposition.x == toposition.x or fromposition.y == toposition.y
        if ret is True:
            objects = self.world.whatIsInTheWay(fromposition,
                                                     MathUtils.getDirectionVector(fromposition, toposition))
            ret = len(objects) == 0
        print("me ({0},{1}) him ({2},{3}) = {4}".format(fromposition.x, fromposition.y, toposition.x,
                                                        toposition.y, ret))
        return ret