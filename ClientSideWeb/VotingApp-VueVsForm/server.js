var express = require("express");
var server = express();
var bodyParser = require("body-parser");
server.use(bodyParser.urlencoded({extended: true}));

let voteTotals = {};

server.post("/vote", function (req, res) {
    //If needed, establish var for this candidate, then increment their total
    if (!voteTotals[req.body.candidate]) {
        voteTotals[req.body.candidate] = 0;
    }
    voteTotals[req.body.candidate]++;

    res.write("You voted for " + req.body.candidate + "\r\n\r\n");

    //print totals for all candidates
    for(candidate in voteTotals) {
        res.write(candidate + " has " + voteTotals[candidate] + "\r\n");
    }
    res.end();
});

server.post("/reset", function(req, res) {
    if (req.body.pw === "youveyeedyourlasthaw")  {
        voteTotals = {};
        res.write("Votes have been reset");
        res.end()
        return;
    }
    res.write("Incorect password");
    res.end();
});

server.get("/votesFor", function (req, res) {
    if (!voteTotals[req.query.candidate]) { //query for get, body for post
        res.write("Candidate doesn't exist");
        res.end();
        return;
    }
    res.write(req.query.candidate + " has " + voteTotals[req.query.candidate]);
    res.end();
});

server.get("/numberOfCandidates", function(req, res) {
	res.set("Content-Type", "text/html"); //Tells the browser what kind of content this will be
	res.set("Cache-Control", "no-cache");  //Tells the browser: "don't use a cached response; ask the server every time".
    let numOfCandidates = 0;
    for (candidate in voteTotals) {
        numOfCandidates++;
    }

    //https://www.w3schools.com/jsref/jsref_string.asp
	res.write("They're are " + String(numOfCandidates) + " candidates"); //sends this text as a response to the client
	res.end(); //done with the response to the client
});

server.get("/totalVotes", function(req, res) {
    res.set("Content-Type", "text/html");
    res.set("Cache-Control", "no-cache");

    let totalVotes = 0;
    for (votes in voteTotals) { //no works
        totalVotes += voteTotals[votes];
    }

    res.write("Total Votes: " + String(totalVotes));
    res.end();
});

server.use(express.static("./pub"));
server.listen(8080, function () {
    console.log("Server is now running on port 8080.") //This callback happens once the server is ready.
});