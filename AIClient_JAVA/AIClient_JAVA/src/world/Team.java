/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Team.java
 ** A team
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

public class Team {
	private int id;
	private Character[] characters;

	public Team(int id, int numberOfCharacter) {
		this.id = id;
		for (int index = 0; index < numberOfCharacter; ++index) {
			// TODO: refactor with map
			characters[index] = new Character(0, 0);
		}
	}

	public int getId() {
		return id;
	}

	public Character getCharacter(int id) {
		return characters[id];
	}
}
