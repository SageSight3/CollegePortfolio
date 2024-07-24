function randomColor() {
    let colorHexCode = "#";
    for (let digit = 0; digit < 6; digit++) {
        colorHexCode += Math.floor(Math.random()*16).toString(16); //16 specifies the nums to be interpreted in hex?
    }
    return colorHexCode;
}

let myApp = Vue.createApp({
    data () {
        return {
            backColor: "#000000",
            linesPerNode: 20,
            ctx: null,
            nodes: [],
            animator: null
        };
    },
    methods: {
        redrawEverything() {
            this.ctx.fillStyle = this.backColor;
            this.ctx.fillRect(0, 0, 400, 400);
            for (let node = 0; node < this.nodes.length-1; ++node) { //-1 here because we look ahead to draw to the next node
                for (let line = 0; line < this.linesPerNode; line++) { //draws "this.linesPerNode" lines to the next node
                    let startNode = this.nodes[node];
                    let endNode = this.nodes[node+1];
                    this.drawLine(startNode.x + startNode.deltaX*line, startNode.y + startNode.deltaY*line, endNode.x + endNode.deltaX*line, endNode.y + endNode.deltaY*line, startNode.color, endNode.color);
                }
            }
        },
        addNode() {
            //build node
            let node = {};
            node.x = Math.round(Math.random()*400);
            node.y = Math.round(Math.random()*400);
            node.deltaX = Math.round(Math.random()*20-10);
            node.deltaY = Math.round(Math.random()*20-10);
            node.color = randomColor();
            node.id = Symbol();

            //for prepping animator - everything should be going clockwise
            if (node.x == 400){
                node.xDir = 0; //0 means decrement x, 1 means inc
            } else {
                node.xDir = 1;
            }
            if (node.y == 400){
                node.yDir = 0; //0 means decrement x, 1 means inc
            } else {
                node.yDir = 1;
            }
            if (node.deltaX == 10){
                node.deltaXChange = 0; //0 means decrement x, 1 means inc
            } else {
                node.deltaXChange = 1;
            }
            if (node.deltaY == 10){
                node.deltaYChange = 0; //0 means decrement x, 1 means inc
            } else {
                node.deltaYChange = 1;
            }

            //add node to list
            this.nodes.push(node);
            this.redrawEverything();
        },
        drawLine(xStart, yStart, xEnd, yEnd, startColor, endColor) {
            //console.log("startColor: " + startColor);
            //console.log("endColor: " + endColor);
            //set up the line's gradient
            let grad = this.ctx.createLinearGradient(xStart, yStart, xEnd, yEnd);
            grad.addColorStop(0, startColor);
            grad.addColorStop(1, endColor);
            this.ctx.strokeStyle = grad;

            //draw the line
            this.ctx.beginPath(); //clears out previous draw paths
            this.ctx.lineWidth = 2;
            this.ctx.moveTo(xStart, yStart); //moves position to line start coords
            this.ctx.lineTo(xEnd, yEnd); //draws line to end coords
            this.ctx.stroke(); //puts line down?
        },
        deleteNode(indexOfNode) {
            this.nodes.splice(indexOfNode, 1);
            this.redrawEverything();
        },
        updateAnimation() {
            //update vector direction, if necessary
            for (node of this.nodes) {
                if (node.x == 400){
                    node.xDir = 0; //0 means decrement x, 1 means inc
                } else if (node.x == 0) {
                    node.xDir = 1;
                }
                if (node.y == 400){
                    node.yDir = 0; //0 means decrement x, 1 means inc
                } else if (node.y == 0) {
                    node.yDir = 1;
                }
                if (node.deltaX == 10){
                    node.deltaXChange = 0; //0 means decrement x, 1 means inc
                } else if (node.deltaX == -10) {
                    node.deltaXChange = 1;
                }
                if (node.deltaY == 10){
                    node.deltaYChange = 0; //0 means decrement x, 1 means inc
                } else if (node.deltaY == -10) {
                    node.deltaYChange = 1;
                }

                //update line properties
                if (node.xDir == 1) {
                    node.x++;
                } else {
                    node.x--;
                }
                if (node.yDir == 1) {
                    node.y++;
                } else {
                    node.y--;
                }
                if (node.deltaXChange == 1) {
                    node.deltaX++;
                } else {
                    node.deltaX--;
                }
                if (node.deltaYChange == 1) {
                    node.deltaY++;
                } else {
                    node.deltaY--;
                }
            }
            this.redrawEverything();
        },
        startAnimation() {
            //don't put () on method in setInterval, () means execute and apply return value to what called the method, not just this your
            //method to do shit with?
            this.animator = setInterval(this.updateAnimation, 40);
            //console.log("starting animation");
        },
        stopAnimation() {
           clearInterval(this.animator); //cancels setInterval
           //console.log("stopping animation");
        }
    },
    computed: {
        numOfNodes() {
            let returnStr = "";
            if (this.nodes.length == 1) {
                returnStr = "1 node";
            } else {
                returnStr = this.nodes.length.toString() + " nodes";
            }
            return returnStr;
        }
    },
    mounted () { //think of it like page constructor, with app objects/html being inst vars
        this.ctx = this.$refs.splineDisplay.getContext("2d"); //gets graphics context for drawing
        this.redrawEverything();
    }
    //The mounted method above is a lifecycle hook that is automatically executed once 
    //Vue has parsed all of the template code and created any DOM elements.
}).mount("#app");