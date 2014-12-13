/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** MoveCharacter.java
 ** Event call to move a character
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

public class MoveCharacterEvent extends OutgoingEvent {
	private int characterID;
	private int positionX, positionY;

	public MoveCharacterEvent(int characterID, int positionX, int positionY) {
		this.characterID = characterID;
		this.positionX = positionX;
		this.positionY = positionY;
	}

	@Override
	public String toString() {
		String message = "Game:Move" + SEPARATOR;
		message += characterID + SEPARATOR;
		message += positionX + SEPARATOR;
		message += positionY;
		return message;
	}
}
