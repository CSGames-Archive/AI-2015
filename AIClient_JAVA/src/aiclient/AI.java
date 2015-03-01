/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** AI.java
 ** The AI loop
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package aiclient;

import java.awt.Point;

import world.Character;
import world.Missile;
import world.World;
import event.QueueController;

public class AI {
	public enum AIStatus {
		INIT, LOWER_RIGHT, LOWER_LEFT, UPPER_RIGHT, UPPER_LEFT
	}

	AIStatus status = AIStatus.INIT;
	QueueController queueController = QueueController.getInstance();
	World world = World.getInstance();

	Point position1 = new Point(0, 0);
	Point position2 = new Point(7, 0);
	Point position3 = new Point(0, 7);
	Point position4 = new Point(7, 7);

	public void tick() {
		if (status == AIStatus.INIT) {
			init();
		} else if (status == AIStatus.LOWER_RIGHT) {
			lowerRight();
		} else if (status == AIStatus.LOWER_LEFT) {
			lowerLeft();
		} else if (status == AIStatus.UPPER_RIGHT) {
			upperRight();
		} else if (status == AIStatus.UPPER_LEFT) {
			upperLeft();
		}
	}

	public void init() {
		System.out.println("Init");
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		king.move(position2);
		soldier.move(position3);

		king.shootMissile(Missile.Direction.RIGHT);
		soldier.shootMissile(Missile.Direction.LEFT);

		status = AIStatus.LOWER_RIGHT;
	}

	public void lowerRight() {
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		if (king.getPosition().equals(position2)) {
			System.out.println("LR");
			king.move(position1);
			soldier.move(position4);

			king.dropMine();
			soldier.dropMine();

			king.shootMissile(Missile.Direction.LEFT);
			soldier.shootMissile(Missile.Direction.RIGHT);

			status = AIStatus.LOWER_LEFT;
		}
	}

	public void lowerLeft() {
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		if (king.getPosition().equals(position1)) {
			System.out.println("LL");
			king.move(position4);
			soldier.move(position1);

			king.shootMissile(Missile.Direction.UP);
			soldier.shootMissile(Missile.Direction.DOWN);

			king.dropMine();
			soldier.dropMine();

			status = AIStatus.UPPER_RIGHT;
		}
	}

	public void upperRight() {
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		if (king.getPosition().equals(position4)) {
			System.out.println("UR");
			king.move(position3);
			soldier.move(position2);

			king.shootMissile(Missile.Direction.DOWN);
			soldier.shootMissile(Missile.Direction.UP);

			king.dropMine();
			soldier.dropMine();

			status = AIStatus.UPPER_LEFT;
		}
	}

	public void upperLeft() {
		Character king = world.getMyTeam().getCharacter(0);
		Character soldier = world.getMyTeam().getCharacter(1);

		if (king.getPosition().equals(position3)) {
			System.out.println("UL");
			king.move(position2);
			soldier.move(position3);

			king.dropMine();
			soldier.dropMine();

			king.shootMissile(Missile.Direction.RIGHT);
			soldier.shootMissile(Missile.Direction.LEFT);

			status = AIStatus.LOWER_RIGHT;
		}
	}
}
