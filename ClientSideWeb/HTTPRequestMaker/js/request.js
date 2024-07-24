let requestMaker = Vue.createApp({
    data () {
        return {
            requestMethod: "GET",
            url: "",
            paramList: [],
            reply: ""
        }
    },
    methods: {
        sendRequest() {
            //build search params
            let searchParams = new URLSearchParams;
            for (param of this.paramList) {
                searchParams.append(param.name, param.value);
            }
            //fetch json
            if (this.requestMethod == "GET") {
                fetch(this.url + "?" + searchParams).then(
                    (response) => {
                        if (!response.ok) {
                            throw new Error("status: " + response.status);
                        }
                        return response.text();
                    }
                ).then(
                    (text) => {
                        this.reply = text;
                    },
                    (err) => {
                        this.reply = "Error: " + err.message;
                    }
                );
            } else {
                //To-Do: generic fetch block for POST, PUT, PATCH, and DELETE
                fetch(this.url, {
                    method: this.requestMethod,
                    body: searchParams
                }).then(
                    (response) => {
                        if (!response.ok) {
                            throw new Error("status: " + response.status);
                        }
                        return response.text();
                    }
                ).then(
                    (text) => {
                        this.reply = text;
                    },
                    (err) => {
                        this.reply = "Error: " + err.message;
                    }
                );
            }
        },
        addParam() {
            let param = {};
            param.name = "";
            param.value = "";
            param.id = Symbol();
            this.paramList.push(param);
        },
        deleteParam(index) {
            this.paramList.splice(index, 1);
        },
        /*
        logParams() {
            console.log("Logging paramList");
            for (param of this.paramList) {
                console.log(param);
            }
        },
        */
    },
}).mount('#app');