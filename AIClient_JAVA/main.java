package notdefault;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

class main {
	public static void main(String argv[]) throws Exception {

		Socket webSocket = new Socket("127.0.0.1", 1337);
		PrintWriter outToServer = new PrintWriter(webSocket.getOutputStream(),
				true);
		BufferedReader inFromServer = new BufferedReader(new InputStreamReader(
				webSocket.getInputStream()));
		BufferedReader stdIn = new BufferedReader(new InputStreamReader(
				System.in));

		String textServer;
		String textClient = "AIClientReady";

		outToServer.println(textClient);
		
		while ((textServer = inFromServer.readLine()) != null) {
			System.out.println("Server: " + textServer);
			if (textServer.equals("Bye."))
				break;

			textClient = stdIn.readLine();
			if (textClient != null) {
				System.out.println("Client: " + textClient);
				outToServer.println(textClient);
			}
		}
		webSocket.close();
	}
}