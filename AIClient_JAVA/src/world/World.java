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

import java.awt.Point;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import event.AddPlayerEvent;
import event.QueueController;

public class World {

	public enum MapEntity {
		EMPTY, BOX, CHARACTER
	}

	private static World instance = null;
	private int yourId;
	private boolean gameIsStarted = false;
	private boolean gameIsFinished = false;
	private List<Team> teams = new ArrayList<Team>();
	private boolean map[][] = null;

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

		String teamName = "java team" + id;
		String[] characterNames = { "java king" + id, "java soldier" + id };
		AddPlayerEvent event = new AddPlayerEvent(teamName, characterNames);
		QueueController.getInstance().addOutgoingEvent(event);
	}

	public void startGame(int mapWidth, int mapHeight, int numberOfTeam,
			int numberOfCharacter, List<Integer> teamIDs) {
		gameIsStarted = true;
		map = new boolean[mapWidth][mapHeight];
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

	public Team getMyTeam(int id) {
		return getTeam(yourId);
	}

	public void updateBox(Point position) {
		map[position.x][position.y] = true;
	}

	public boolean isBoxAtPosition(Point position) {
		return map[position.x][position.y];
	}

	public boolean isCharacterAtposition(Point position) {
		for (Iterator<Team> teamIterator = teams.iterator(); teamIterator
				.hasNext();) {
			Team team = teamIterator.next();

			for (Iterator<Character> characterIterator = team.getCharacters()
					.iterator(); characterIterator.hasNext();) {
				Character character = characterIterator.next();
				if (character.getPosition() == position) {
					return true;
				}
			}
		}
		return false;
	}

	public MapEntity whatIsAtPosition(Point position) {
		if (isBoxAtPosition(position)) {
			return MapEntity.BOX;
		} else if (isCharacterAtposition(position)) {
			return MapEntity.CHARACTER;
		}
		return MapEntity.EMPTY;
	}

	public void endGame() {
		System.out.println("End game");
		gameIsFinished = true;
	}

	public boolean isGameIsStarted() {
		return gameIsStarted;
	}

	public boolean isGameIsFinished() {
		return gameIsFinished;
	}
}
