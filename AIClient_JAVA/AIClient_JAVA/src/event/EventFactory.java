/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** EventFactory.java
 ** Factory that generate event
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

public class EventFactory {

	public static void generateEvent(String message) {
		String[] messageParts = message.split(":", 2);
		IngoingEvent event = createEvent(messageParts[0]);
		if(event != null) {
			event.fillArguments(messageParts[1]);
			EventController.getInstance().addIngoingEvent(event);
		} else {
			System.out.println("Factory Error: Message invalid");
		}
	}
	
	private static IngoingEvent createEvent(String type) {
		if(type.equals("JoinGame")) {
			return new JoinGameEvent();
		} else if(type.equals("UpdateCharacter")) {
			return new UpdateCharacterEvent();
		} else if(type.equals("GameStart")) {
			return new GameStartEvent();
		}
		return null;
	}
}