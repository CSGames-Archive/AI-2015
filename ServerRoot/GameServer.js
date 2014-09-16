// Load the TCP Library
net = require('net');

var Debug = true;
var HOST = '127.0.0.1';
var PORT = 1337;

var clients = [];
var currentClientId = 1;
var currentClientConnected = 0;
var gameClientId = 0;

net.createServer(function (socket) {

	// Identify this client
	socket.adress = socket.remoteAddress + ":" + socket.remotePort;
	socket.id = currentClientId;
	socket.msg = ''; // Current message, per connection
	socket.setEncoding('utf8');
	
	// Put this new client in the list
	clients.push(socket);
	currentClientConnected++;
	currentClientId++;

	if (Debug)
		process.stdout.write(' - join - ' + '\n');
			
	// Handle incoming messages from clients.
	socket.on('data', function (data) {
		//socket.msg += data.toString('utf8');
		
		var arr = data.split('\n');
		arr.forEach(function (chunk)
		{
			if(chunk.length > 1)
			{
				process.stdout.write(' - Chunk - ' + chunk + '\n');
				socket.emit('message', chunk);
			}
		});
	});

	socket.on('message', function(msg) {
		if (msg == 'Exit')
		{
			socket.write('OkForExit');
		}
		else if (msg == 'GameClientReady')
		{
			if(gameClientId == 0)
			{
				gameClientId = socket.id;
				if (Debug)
					process.stdout.write(' - Game Client Ready - ' + '\n');
			}
			else
			{
				socket.write('Error: Game client already connected');
			}
		}
		else if (msg == 'AIClientReady')
		{
			if(gameClientId != 0)
			{
				socket.write('YourId:' + socket.id);
			}
			else
			{
				socket.write('Error: Game client not connected');
			}
		}
		else
		{
			if(gameClientId != 0)
			{
				msg += ':' + socket.id + ':';
				broadcast(msg, socket);
			}
			else
			{
				socket.write('Error: Game client not connected');
			}
		}
	});
	
	// Remove the client from the list when it leaves
	socket.on('end', function () 
	{
		if (Debug)
			process.stdout.write(' - End - ' + '\n');
		removeSocket(socket);
	});

	// Remove the client from the list when it leaves
	socket.on('error', function ()
	{
		if (Debug)
			process.stdout.write(' - Error - ' + '\n');
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
			process.stdout.write('Broadcast - ' + message + '\n');
	}

	function removeSocket(socket)
	{
		if(socket.id == gameClientId)
		{
			process.exit();
		}
		
		clients.splice(clients.indexOf(socket), 1);
		broadcast('ClientDisconnect:' + socket.id);
	}

}).listen(PORT, HOST);

// Starting message on the terminal of the server
console.log('Game Server: ' + HOST + ':' + PORT);

