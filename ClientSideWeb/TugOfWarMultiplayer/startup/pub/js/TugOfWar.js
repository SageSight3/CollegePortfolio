var socket = io();

let tugOfWar = Vue.createApp({
    data () {
        return {
            dogOffset: 0,
            outcome: ''
        }
    },
    methods: {
        moveLeft() {
            this.dogOffset--;
            socket.emit("moveLeft");
        },
        moveRight() {
            this.dogOffset++;
            socket.emit("moveRight");
        }
    },
    computed: {
        currentDogOffset() {
            return {
                left: this.dogOffset + "px"
            }
        }
    },
    mounted () {
        //Whenever the server sends a client the message, "updatePosition", dogOffset will update to the value provided
        socket.on("updatePosition", (newOffset) => {
            this.dogOffset = newOffset;
        });
        socket.on("leftWins", () => {
            this.outcome = "left wins";
        });
        socket.on("rightWins", () => {
            this.outcome = "right wins";
        });
    }
}).mount('#app');