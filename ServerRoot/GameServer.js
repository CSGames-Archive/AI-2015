// Load the TCP Library
net = require('net');

var Debug = true;
var HOST = '127.0.0.1';
var PORT = 1337;

var clients = [];
var iIdClients = 1; 

net.createServer(function (socket) {

  // Identify this client
  socket.adress = socket.remoteAddress + ":" + socket.remotePort;
  socket.id = iIdClients;
  socket.x = 0;
  socket.y = 0;
  socket.name = 'null';

  // Put this new client in the list
  clients.push(socket);
  iIdClients++;

  //envoie liste de player
  broadcast('join:' + socket.x  + ':' + socket.y + ':' + socket.id + '\0', socket);
  envoieListe(socket);

  // Handle incoming messages from clients.
  socket.on('data', function (data) {
    if (data == 'exit')
	{
      socket.write('ok');
	}
    else
    {
      data += ':' + socket.id;
      broadcast(data, socket);
    }
  });

  // Remove the client from the list when it leaves
  socket.on('end', function () 
  {
    if (Debug)
      process.stdout.write('end' + '\n');
    bobBye(socket);
  });

  // Remove the client from the list when it leaves
  socket.on('error', function ()
  {
    if (Debug)
      process.stdout.write('error' + '\n');
    bobBye(socket);
  });
  
  // Send a message to all clients
  function broadcast(message, sender) 
{
    clients.forEach(function (client) {
      // Don't want to send it to sender
      if (client === sender) return;
        client.write(message);
    });
    // Log it to the server output too

    if (Debug)
      process.stdout.write('broadcast' + message + '\n');
}

function bobBye(socket)
{
    clients.splice(clients.indexOf(socket), 1);
    broadcast('exit:' + socket.id);
}

function envoieListe(sender)
{
  var liste = '';

  clients.forEach(function (client) 
  {
    if (client === sender) return;
      liste += 'join:' + client.x + ':' + client.y + ':' + client.id + ':';
  });

  liste += '\0';

  if (liste.length > 0)
  {
    if (Debug);
      process.stdout.write( liste + '\n');
    sender.write(liste);
  }
}

}).listen(PORT, HOST);

// Put a friendly message on the terminal of the server.
console.log('MobaApp server running at port: ' + PORT + ' Host: ' + HOST);

