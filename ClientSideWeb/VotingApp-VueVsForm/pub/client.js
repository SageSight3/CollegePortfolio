let votingApp = Vue.createApp({
    data () {
        return {
            feedback: "Hi",
            candidate: "",
            pw: ""
        };
    },
    methods: {

        //fetches and promises are also AJAX?

        fetchNumCandidates() { 
            //then is a method call to the promise object, with the return in the first then also belonging to the promise object
            //fetch is a promise of something to fulfill (return?), followed by a then of what to do after the promise has been fulfilled
            //what a promise returns is also a promise object?, so can have more thens added to it?
            //check below this method in lab page for more help
            fetch("./numberOfCandidates").then( //Makes a GET request to /numberOfCandidates
                (result) => {
                    if (!result.ok) { 
                        throw new Error("status: " + result.status); //Throws error is not status code 200 through 299.
                    }
                    return result.text(); //returns the result as the next promise to the "then" below
                }
            ).then(
                (data) => { //This 'data' parameter is the next data sent from the server, returned from the 'then' above.
                    this.feedback = data;
                },

                //We used arrow functions instead of regular functions so that the keyword this still refers to our Vue application. 
                //Otherwise, we would have had troubles accessing the this.feedback property.
                (err) => {
                    this.feedback = "Error: " + err.message;
                }
            );
        },

        recordVote() {
           let params = new URLSearchParams();
           //if need to get multiple pieces of data, just call append multiple times
            params.append("candidate", this.candidate);
            fetch("/vote", {method: 'POST', body: params}).then( //Makes a POST request to /vote
                (result) => {
                    if (!result.ok) {
                        throw new Error("status: ", result.status);
                    }
                    return result.text();
                }
            ).then(
                (data) => {
                    this.feedback = data;
                },
                (err) => {
                    this.feedback = "Error: " + err.message;
                }
            );
        },

        getVotesForCandidate() {
            let params = new URLSearchParams();
            params.append("candidate", this.candidate);
            //since using GET, will build URL directly in fetch
            fetch("votesFor?" + params).then(
                (result) => {
                    if (!result.ok) {
                        throw new Error("status: ", result.status);
                    }
                    return result.text();
                }
            ).then(
                (data) => {
                    this.feedback = data;
                },
                (err) => {
                    this.feedback = "Error: " + err.message;
                }
            );
        },

        resetVotes() {
            let params = new URLSearchParams();
            params.append("pw", this.pw);
            fetch("/reset", {method: 'POST', body: params}).then (
                (result) => {
                    if (!result.ok) {
                        throw new Error("status: " + result.status);
                    }
                    return result.text();
                }
            ).then(
                (data) => {
                    this.feedback = data;
                },
                (err) => {
                    this.feedback = "Error: " + err.message;
                }
            );
        },

        getTotalVotes() {
            fetch("./totalVotes").then(
                (result) => {
                    if (!result.ok) {
                        throw new Error("status: " + result.status);
                    }
                    return result.text();
                }
            ).then(
                (data) => {
                    this.feedback = data;
                },
                (err) => {
                    this.feedback = "Error: " + err.message;
                }
            )
        }
    }

}).mount("#app");