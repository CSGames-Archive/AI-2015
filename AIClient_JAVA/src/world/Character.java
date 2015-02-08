/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Character.java
 ** A character
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

import java.awt.Point;

import event.DropMineEvent;
import event.MoveCharacterEvent;
import event.QueueController;
import event.ShootMissileEvent;

public class Character {
	private Point position;
	private int id;
	private int life;
	private Mine mine = new Mine();
	private Missile missile = new Missile();

	public Character(int id) {
		this.id = id;
		this.position = new Point(0, 0);
		this.life = 3;
	}

	public void move(Point position) {
		QueueController queueController = QueueController.getInstance();
		MoveCharacterEvent event = new MoveCharacterEvent(id, position);
		queueController.addOutgoingEvent(event);
	}

	public void dropMine() {
		if (mine.isReady()) {
			QueueController queueController = QueueController.getInstance();
			DropMineEvent event = new DropMineEvent(id);
			queueController.addOutgoingEvent(event);
			mine.drop();
		}
	}

	public void shootMissile(Missile.Direction direction) {
		if (missile.isReady()) {
			QueueController queueController = QueueController.getInstance();
			ShootMissileEvent event = new ShootMissileEvent(id,
					direction.ordinal());
			queueController.addOutgoingEvent(event);
			missile.shoot();
		}
	}

	public void updateInfo(Point position) {
		this.position = position;
	}

	public void hitByMine() {
		if (isAlive()) {
			--life;
			//System.out.println("Character " + id + " hit a mine");
		}
	}

	public void hitByMissile() {
		if (isAlive()) {
			--life;
			//System.out.println("Character " + id + " hit a missile");
		}
	}

	public void mineHit() {
		mine.hit();
		//System.out.println("Character " + id + " mine hit target");
	}

	public void missileHit() {
		missile.hit();
		//System.out.println("Character " + id + " missile hit target");
	}

	public Point getPosition() {
		return position;
	}

	public boolean isAlive() {
		return life > 0;
	}

	public Missile getMissile() {
		return missile;
	}
}
