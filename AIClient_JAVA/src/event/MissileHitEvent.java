/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** MissileHitEvent.java
 ** Event that happen when a missile hit an entity
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import world.World;

public class MissileHitEvent extends IngoingEvent {

	private int hitEntity;
	private int hitTeamId;
	private int hitCharacterId;
	private int originTeamId;
	private int originCharacterId;

	@Override
	public void execute() {
		World.getInstance().getTeam(originTeamId)
				.getCharacter(originCharacterId).missileHit();

		if (hitEntity == 1) {
			World.getInstance().getTeam(hitTeamId).getCharacter(hitCharacterId)
					.hitByMissile();
		} else if (hitEntity == 2) {
			World.getInstance().getTeam(hitTeamId).getCharacter(hitCharacterId)
					.mineHit();
		} else if (hitEntity == 3) {
			World.getInstance().getTeam(hitTeamId).getCharacter(hitCharacterId)
					.missileHit();
		}
	}

	@Override
	public boolean fillArguments(String message) {
		String[] messageParts = message.split(SEPARATOR, 6);

		hitEntity = convertCharToNumeral(messageParts[0]);
		hitTeamId = convertCharToNumeral(messageParts[1]);
		if (hitTeamId == 0) {
			return false;
		}
		hitCharacterId = convertCharToNumeral(messageParts[2]);

		originTeamId = convertCharToNumeral(messageParts[3]);
		if (originTeamId == 0) {
			return false;
		}
		originCharacterId = convertCharToNumeral(messageParts[4]);

		return true;
	}

}

/*
 * 
 * def __init__(self): self.hitEntity = 0 self.hitTeamId = 0 self.hitCharacterId
 * = 0 self.originTeamId = 0 self.originCharacterId = 0
 * 
 * def fillArguments(self, string): arguments = string.split(":", 5)
 * 
 * self.hitEntity = int(arguments[0]) self.hitTeamId = int(arguments[1])
 * self.hitCharacterId = int(arguments[2]) self.originTeamId = int(arguments[3])
 * self.originCharacterId = int(arguments[4])
 * 
 * def execute(self): world = Singleton(World)
 * world.getTeam(self.originTeamId).characters
 * [self.originCharacterId].missileHit() if(self.hitEntity == 1):
 * world.getTeam(self.hitTeamId).characters[self.hitCharacterId].hitByMissile()
 * elif(self.hitEntity == 2):
 * world.getTeam(self.hitTeamId).characters[self.hitCharacterId].mineHit()
 * elif(self.hitEntity == 3):
 * world.getTeam(self.hitTeamId).characters[self.hitCharacterId].missileHit()
 */