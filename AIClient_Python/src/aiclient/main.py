'''
Created on Dec 15, 2014

@author: samuel
'''
import socket
from event.JoinGameEvent import JoinGameEvent

# Socket definition
HOST, PORT = "localhost", 1337
data = "AIClientReady\n"

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    # Connect to server and send data
    sock.connect((HOST, PORT))
    sock.sendall(data.encode())

    # Receive data from the server and shut down
    received = sock.recv(1024)
finally:
    sock.close()

myEvent = JoinGameEvent()
myEvent.fillArguments(received)

print("Sent:     {}".format(data))
print("Received: {}".format(received))