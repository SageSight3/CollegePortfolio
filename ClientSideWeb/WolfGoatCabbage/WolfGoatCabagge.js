let wolfGoatCabbage = Vue.createApp({
    data () {
        return {
            wolfAcross: false,
            cabbageAcross: false,
            goatAcross: false,
            boatAcross: false,
            validMove: true,
        }
    },
    methods: {
        moveWolf() {
            if (this.wolfAcross == this.boatAcross) {
                this.wolfAcross = !this.wolfAcross;
                this.boatAcross = this.wolfAcross;
                this.validMove = true;
            } else {
                this.validMove = false;
            }
        },
        moveGoat() {
            if (this.goatAcross == this.boatAcross) {
                this.goatAcross = !this.goatAcross;
                this.boatAcross = this.goatAcross;
                this.validMove = true;
            } else {
                this.validMove = false;
            }
        },
        moveBoat() {
            this.boatAcross = !this.boatAcross;
            this.validMove = true;
        },
        moveCabbage() {
            if (this.cabbageAcross == this.boatAcross) {
                this.cabbageAcross = !this.cabbageAcross;
                this.boatAcross = this.cabbageAcross;
                this.validMove = true;
            } else {
                this.validMove = false;
            }
        },
        reset() {
            this.wolfAcross = false;
            this.goatAcross = false;
            this.boatAcross = false;
            this.cabbageAcross = false;
        }
    },
    computed: {
        goatEaten () {
            if (this.wolfAcross == this.goatAcross && this.wolfAcross != this.boatAcross) {
                return true;
            }
        },
        cabbageEaten () {
            if (this.goatAcross == this.cabbageAcross && this.goatAcross != this.boatAcross) {
                return true;
            }
        },
        win () { 
            if (this.wolfAcross && this.goatAcross && this.boatAcross && this.cabbageAcross) {
                return true;
            }
        },
        gameOver () {
            if (this.goatEaten || this.cabbageEaten || this.win) {
                return true;
            }
        },
        status () {
            if (!this.wolfAcross && !this.goatAcross && !this.boatAcross && !this.cabbageAcross) {
                return "See if you can them all safely across the river.";
            }

            if (!this.validMove) {
                return "You're on the wrong side of the river to do that!";
            }

            if (this.goatEaten) {
                return "The goat got eaten!"
            }

            if (this.cabbageEaten) {
                return "The cabbage got eaten!"
            }

            if (this.win) {
                return "You did it!"
            }
        }
    }
}).mount("#app");