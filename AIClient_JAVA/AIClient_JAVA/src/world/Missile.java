/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Missile.java
 ** A missile
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

import java.awt.Point;

public class Missile {

	public enum Direction {
		UP, DOWN, LEFT, RIGHT
	}

	private Point position;
	private Direction direction;
	private boolean isReady;

	public Missile() {
		this.position = new Point(0, 0);
		this.direction = Direction.UP;
		this.isReady = true;
	}

	public void shoot() {
		this.isReady = false;
	}
	
	public void updateInfo(Point position, Direction direction) {
		this.position = position;
		this.direction = direction;
	}

	public void hit() {
		this.isReady = true;
	}

	public Point getPosition() {
		return position;
	}

	public Direction getDirection() {
		return direction;
	}

	public boolean isReady() {
		return isReady;
	}
}