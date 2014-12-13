/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** GameStartEvent.java
 ** Event that happen when a game start
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import world.World;

public class GameStartEvent extends IngoingEvent {
	private int numberOfTeam, numberOfCharacter;
	private int[] teamIDs;

	@Override
	public void execute() {
		World.getInstance().startGame(numberOfTeam, numberOfCharacter, teamIDs);
	}

	@Override
	public boolean fillArguments(String message) {
		String[] headerParts = message.split(SEPARATOR, 3);

		numberOfTeam = convertCharToNumeral(headerParts[0]);
		numberOfCharacter = convertCharToNumeral(headerParts[1]);

		if (numberOfTeam < 1 || numberOfCharacter < 1) {
			return false;
		}

		//Plus one for the sender id that we don't use
		String[] ids = headerParts[2].split(SEPARATOR, numberOfTeam+1);
		for (int index = 0; index < ids.length-1; ++index) {
			teamIDs[index] = convertCharToNumeral(ids[index]);
			if (teamIDs[index] == 0) {
				return false;
			}
		}

		return false;
	}
}
