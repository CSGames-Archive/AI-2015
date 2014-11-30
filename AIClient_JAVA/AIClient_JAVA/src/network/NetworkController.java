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

public class NetworkController {
	private static NetworkController instance = null;
	private Socket webSocket;
	private PrintWriter outToServer;
	private BufferedReader inFromServer;

	protected NetworkController() {
		try {
			webSocket = new Socket("127.0.0.1", 1337);
			outToServer = new PrintWriter(webSocket.getOutputStream(), true);
			inFromServer = new BufferedReader(new InputStreamReader(
					webSocket.getInputStream()));
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static NetworkController getInstance() {
		if (instance == null) {
			instance = new NetworkController();
		}
		return instance;
	}
	
	public void sendMessage(String message) {
		System.out.println(message);
		outToServer.println(message);
	}

	public String readMessage() {
		String textServer = "";
		try {
			textServer = inFromServer.readLine();
			System.out.println("Server: " + textServer);
		} catch (IOException e) {
			e.printStackTrace();
		}
		return textServer;
	}

	public void close() {
		try {
			webSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
