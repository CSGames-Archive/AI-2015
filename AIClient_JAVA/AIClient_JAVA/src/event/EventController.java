/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** EventController.java
 ** Singleton that manage all the events
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

import java.util.LinkedList;
import java.util.Queue;

import network.NetworkController;

public class EventController {
	private static EventController instance = null;
	Queue<OutgoingEvent> outEvents = new LinkedList<OutgoingEvent>();
	Queue<IngoingEvent> inEvents = new LinkedList<IngoingEvent>();

	protected EventController() {
		// Exists only to defeat instantiation
	}

	public static EventController getInstance() {
		if (instance == null) {
			instance = new EventController();
		}
		return instance;
	}

	public void addOutgoingEvent(OutgoingEvent event) {
		outEvents.add(event);
	}

	public void addIngoingEvent(IngoingEvent event) {
		inEvents.add(event);
	}

	public void executeAllEvents() {
		executeIngoingEvents();
		executeOutgoingEvents();
	}
	
	public void executeIngoingEvents() {
		while (!inEvents.isEmpty()) {
			IngoingEvent event = inEvents.remove();
			event.execute();
		}
	}
	
	public void executeOutgoingEvents() {
		while (!outEvents.isEmpty()) {
			OutgoingEvent event = outEvents.remove();
			NetworkController.getInstance().sendMessage(event.toString());
		}
	}
}