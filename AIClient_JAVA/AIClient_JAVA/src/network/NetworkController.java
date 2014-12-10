/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** NetworkController.java
 ** Control all the network communication
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package network;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import event.EventFactory;

public class NetworkController {
	private static NetworkController instance = null;
	private Socket webSocket;
	private PrintWriter outToServer;
	private BufferedReader inFromServer;
	private ReaderThread readerThead;

	protected NetworkController() {
		try {
			webSocket = new Socket("127.0.0.1", 1337);
			outToServer = new PrintWriter(webSocket.getOutputStream(), true);
			inFromServer = new BufferedReader(new InputStreamReader(
					webSocket.getInputStream()));
			readerThead = new ReaderThread();
		} catch (Exception e) {
			// TODO make some retry for server connection
			e.printStackTrace();
		}
	}

	public static NetworkController getInstance() {
		if (instance == null) {
			instance = new NetworkController();
		}
		return instance;
	}

	public void init() {
		sendMessage("AIClientReady");
		readerThead.start();
	}

	public void readFunctionThread() {
		boolean exit = false;
		while (!exit) {
			String fullMessage = readMessage();

			if (fullMessage.equals("Net:OkForExit") || fullMessage == null) {
				exit = true;
				break;
			}

			dispatchMessage(fullMessage);
		}

	}

	public void dispatchMessage(String message) {
		String[] messageParts = message.split(":", 2);
		if (messageParts[0].equals("Net")) {
			parseNetMessage(messageParts[1]);
		} else if (messageParts[0].equals("Game")) {
			EventFactory.generateEvent(messageParts[1]);
		}
	}

	public void parseNetMessage(String message) {
		if (message.equals("JoinGameFailed")) {
			System.out.println("Error : the game client was not connected");
			System.out.println("Info : connection retry in few seconds...");
			try {
				Thread.sleep(2000);
				sendMessage("AIClientReady");
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		} else if (message.equals("ErrorGameClientDisconnect")) {
			System.out.println("Error : the game client was disconnected");
		} else {
			System.out.println("unknow net message: " + message);
		}
	}

	public void sendMessage(String message) {
		if (outToServer != null) {
			System.out.println(message);
			outToServer.println(message);
		} else {
			System.out.println("Error: can't send the message: " + message);
		}
	}

	public String readMessage() {
		String textServer = "";
		try {
			textServer = inFromServer.readLine();
			System.out.println("Server: " + textServer);
		} catch (IOException e) {
			e.printStackTrace();
		} catch (NullPointerException e) {
			System.out.println("Error: can't read on socket");
		}
		return textServer;
	}

	public void close() {
		try {
			sendMessage("Exit");
			readerThead.join();
			webSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
