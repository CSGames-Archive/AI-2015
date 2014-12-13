package event;

public class AddPlayerEvent extends OutgoingEvent {
	private String teamName;
	private String[] characterNames;
	
	public AddPlayerEvent(String teamName, String[] characterNames) {
		this.teamName = teamName;
		this.characterNames = characterNames;
	}
	
	@Override
	public String toString() {
		String message =  "Game:AddPlayer:" + teamName;
		for( int index = 0; index < characterNames.length; ++index) {
			message += ":" + characterNames[index];
		}
		return message;
	}
}
