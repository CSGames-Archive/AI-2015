/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Client.java
 ** Main program loop
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package aiclient;

import network.NetworkController;
import world.World;
import event.EventController;

class Client {
	public static void main(String args[]) {

		NetworkController networkController = NetworkController.getInstance();
		EventController eventController = EventController.getInstance();
		World world = World.getInstance();
		AI ai = new AI();

		// Initialization
		networkController.init();

		while (networkController.isConnected() && !world.isGameIsFinished()) {
			eventController.executeIngoingEvents();

			if (world.isGameIsStarted()) {
				ai.tick();
			}

			networkController.executeOutgoingEvents();
			pause(30);
		}

		NetworkController.getInstance().close();
		System.out.println(" - end - ");
	}

	public static void pause(long milli) {
		try {
			Thread.sleep(milli);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}