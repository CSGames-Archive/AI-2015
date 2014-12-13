/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Main.java
 ** Main program loop
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package main;

import world.World;
import network.NetworkController;
import event.EventController;
import event.MoveCharacterEvent;

class Main {
	public static void main(String args[]) {
		// Initialization
		NetworkController.getInstance().init();
		//Waiting for join game
		pause(1000);
		EventController.getInstance().executeAllEvents();
		//Waiting for the game start
		pause(1000);
		EventController.getInstance().executeAllEvents();
		
		if(World.getInstance().isGameIsStarted()) {
			// AI Loop
			MoveCharacterEvent moveEvent = new MoveCharacterEvent(0,50,50);
			EventController.getInstance().addOutgoingEvent(moveEvent);
			EventController.getInstance().executeAllEvents();
			pause(1000);
		}
		
		NetworkController.getInstance().close();
		System.out.println(" - end - ");
	}
	
	public static void pause(long milli) {
		try {
			Thread.sleep(milli);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}