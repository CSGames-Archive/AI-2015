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

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import event.AddPlayerEvent;
import event.QueueController;

public class World {
	private static World instance = null;
	private int yourId;
	private boolean gameIsStarted = false;
	private List<Team> teams = new ArrayList<Team>();

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
		QueueController.getInstance().addOutgoingEvent(event);
	}

	public void startGame(int numberOfTeam, int numberOfCharacter,
			List<Integer> teamIDs) {
		gameIsStarted = true;
		for (int index = 0; index < numberOfTeam; ++index) {
			teams.add(new Team(teamIDs.get(index), numberOfCharacter));
		}
	}

	public Team getTeam(int id) {
		for (Iterator<Team> iterator = teams.iterator(); iterator.hasNext();) {
			Team team = iterator.next();
			if (team.getId() == id) {
				return team;
			}
		}
		return null;
	}

	public boolean isGameIsStarted() {
		return gameIsStarted;
	}

	public int getYourId() {
		return yourId;
	}
}
