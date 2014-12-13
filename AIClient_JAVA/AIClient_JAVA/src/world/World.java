/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** World.java
 ** The world
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

import event.AddPlayerEvent;
import event.EventController;

public class World {
	private static World instance = null;
	private int yourId;
	private boolean gameIsStarted = false;
	private Team[] teams;

	protected World() {
		// Exists only to defeat instantiation
	}

	public static World getInstance() {
		if (instance == null) {
			instance = new World();
		}
		return instance;
	}

	public void error(String message) {
		System.out.println(message);
	}

	public void joinGame(int id) {
		yourId = id;
		System.out.println("Join game with id:" + yourId);

		String teamName = "team" + id;
		String[] characterNames = { "character1" + id, "character2" + id };
		AddPlayerEvent event = new AddPlayerEvent(teamName, characterNames);
		EventController.getInstance().addOutgoingEvent(event);
	}

	public void startGame(int numberOfTeam, int numberOfCharacter, int[] teamIDs) {
		gameIsStarted = true;
		for (int index = 0; index < numberOfTeam; ++index) {
			teams[index] = new Team(teamIDs[index], numberOfCharacter);
		}
	}

	public Team getTeam(int id) {
		for(int index = 0; index < teams.length; ++index) {
			if(teams[index].getId() == id) {
				return teams[index];
			}
		}
		return null;
	}

	public boolean isGameIsStarted() {
		return gameIsStarted;
	}
}
