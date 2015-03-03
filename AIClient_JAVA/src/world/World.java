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

/**
 * Class that contain all the informations about the Teams, Characters and Missiles
 */
public class World {

	/**
	 * An Enum that represent all the entity that can be found in the world
	 */
	public enum MapEntity {
		EMPTY, BOX, CHARACTER
	}

	private static World instance = null;
	private int yourId;
	private boolean gameIsStarted = false;
	private boolean gameIsFinished = false;
	private boolean map[][] = null;

	/**
	 * List of all the teams
	 */
	private List<Team> teams = new ArrayList<Team>();
	
	/*
	 * THIS SECTION IS OUT OF ACCESS
	 */
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

	public void updateBox(Point position) {
		map[position.x][position.y] = true;
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
	/*
	 * OUT OF ACCESS
	 */
	
	/**
	 * Return the team associate with a certain id
	 * Important : the id of the team are not starting at 0
	 * 
	 * @param id the id of the team we want
	 * @return the team or null if not found
	 */
	public Team getTeam(int id) {
		for (Iterator<Team> iterator = teams.iterator(); iterator.hasNext();) {
			Team team = iterator.next();
			if (team.getId() == id) {
				return team;
			}
		}
		return null;
	}

	/**
	 * Return the team associate with your id
	 * 
	 * @return your team
	 */
	public Team getMyTeam() {
		return getTeam(yourId);
	}

	/**
	 * Check if there's a box at a certain position
	 * 
	 * @param position the position to check
	 * @return True if there's a box, else False
	 */
	public boolean isBoxAtPosition(Point position) {
		return map[position.x][position.y];
	}

	/**
	 * check if there's a character at a certain position
	 * 
	 * @param position the position to check
	 * @return True if there's a character, else False
	 */
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

	/**
	 * Return the Entity at a certain position
	 * 
	 * @param position the position to check
	 * @return the entity that is on the specify position
	 */
	public MapEntity whatIsAtPosition(Point position) {
		if (isBoxAtPosition(position)) {
			return MapEntity.BOX;
		} else if (isCharacterAtposition(position)) {
			return MapEntity.CHARACTER;
		}
		return MapEntity.EMPTY;
	}
}
