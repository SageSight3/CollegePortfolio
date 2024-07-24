//This part is the same as usual...
var express = require("express");
var app = express();

var http = require("http");

//We are getting an instance of a Node HTTP (web) server here.
//We are also telling it to connect up with our Express application,
//so it can handle requests.
var server = http.Server(app);

//On command prompt, we need to do "npm install socket.io"
var socketio = require("socket.io");

//instantiates our 'io' instance, and also connects it up with the HTTP
//server we already created.
var io = socketio(server);

//Just for static files (like usual).  Eg. index.html, client.js, etc.
app.use(express.static("pub"));

let dogOffset = 0; //the "official" record of where the dogs are located
io.on("connection", (socket) => {
	console.log("someone connected");
	socket.emit("updatePosition", dogOffset); //socket.emit sends message to target client, io.emit broadcasts to all clients?
	
	socket.on("disconnect", () => {
		console.log("somebody disconnected");
	});

	//this gets called when a client emits a "moveLeft" message
	socket.on("moveLeft", (dataFromClient) => {
		dogOffset--;
		console.log("Position is now " + dogOffset);
		io.emit("updatePosition", dogOffset); //tell all clients the new position
		if (dogOffset == -50) {
			io.emit("leftWins");
			dogOffset = 0;
		}
	});

	//"moveRight" message handler
	socket.on("moveRight", (dataFromClient) => {
		dogOffset++;
		console.log("Position is now " + dogOffset);
		io.emit("updatePosition", dogOffset);
		if (dogOffset == 50) {
			io.emit("rightWins");
			dogOffset = 0;
		}
	})
});


server.listen(8080, function() {
	console.log("Server is listening on port 8080");
});



