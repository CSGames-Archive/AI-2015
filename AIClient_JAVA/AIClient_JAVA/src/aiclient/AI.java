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

import world.World;
import event.MoveCharacterEvent;
import event.QueueController;

public class AI {
	public enum AIStatus {
		INIT, LOWER_RIGHT, LOWER_LEFT, UPPER_RIGHT, UPPER_LEFT
	}

	AIStatus status = AIStatus.INIT;
	QueueController queueController = QueueController.getInstance();
	World world = World.getInstance();

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
		MoveCharacterEvent moveEvent1 = new MoveCharacterEvent(0, 11, 0);
		queueController.addOutgoingEvent(moveEvent1);
		MoveCharacterEvent moveEvent2 = new MoveCharacterEvent(1, 0, 11);
		queueController.addOutgoingEvent(moveEvent2);
        status = AIStatus.LOWER_RIGHT;
	}

	public void lowerRight() {

	}

	public void lowerLeft() {

	}

	public void upperRight() {

	}

	public void upperLeft() {

	}
}
