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

import java.util.ArrayList;
import java.util.List;

public class Team {
	private int id;
	private List<Character> characters = new ArrayList<Character>();

	public Team(int id, int numberOfCharacter) {
		this.id = id;
		for (int index = 0; index < numberOfCharacter; ++index) {
			characters.add(new Character(index));
		}
	}

	public int getId() {
		return id;
	}

	public Character getCharacter(int id) {
		return characters.get(id);
	}

	public List<Character> getCharacters() {
		return characters;
	}
}
