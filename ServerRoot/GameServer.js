// Load the TCP Library
net = require('net');

var Debug = true;
var HOST = '127.0.0.1';
var PORT = 1337;

var clients = [];
var currentClientId = 1;
var currentClientConnected = 0;

net.createServer(function (socket) {

	// Identify this client
	socket.adress = socket.remoteAddress + ":" + socket.remotePort;
	socket.id = currentClientId;

	// Put this new client in the list
	clients.push(socket);
	currentClientConnected++;
	currentClientId++;

	if (Debug)
		process.stdout.write(' - join - ' + '\n');
			
	// Handle incoming messages from clients.
	socket.on('data', function (data) {
		if (data == 'exit')
		{
			socket.write('ok');
		}
		else
		{
			data += ':' + "clientId" + ':' + socket.id;
			broadcast(data, socket);
		}
	});

	// Remove the client from the list when it leaves
	socket.on('end', function () 
	{
		if (Debug)
			process.stdout.write(' - end - ' + '\n');
		removeSocket(socket);
	});

	// Remove the client from the list when it leaves
	socket.on('error', function ()
	{
		if (Debug)
			process.stdout.write(' - error - ' + '\n');
		removeSocket(socket);
	});
  
	// Send a message to all clients
	function broadcast(message, sender) 
	{
		clients.forEach(function (client)
		{
			// Don't want to send it to sender
			if (client === sender) return;
			client.write(message);
		});

		if (Debug)
		process.stdout.write('broadcast - ' + message + '\n');
	}

	function removeSocket(socket)
	{
		clients.splice(clients.indexOf(socket), 1);
		broadcast('exit:' + socket.id);
	}

}).listen(PORT, HOST);

// Starting message on the terminal of the server
console.log('Game Server: ' + HOST + ':' + PORT);

