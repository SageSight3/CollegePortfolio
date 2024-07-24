exports.incrementer = function incrementer(delta) {

    return n => n + delta;
}

exports.rms = function rms() {
    let args = Array.from(arguments);
    let squaresSum = args.map( (n) => n*n).reduce((sum, square)=>sum + square);
    return Math.sqrt(squaresSum/args.length);
}

exports.Rectangle = function Rectangle(width, height) {
    this.height = height || 1;
    this.width = width || 1;

    this.area = function () { return this.width * this.height; }
    return this.area();
}

exports.makeWarning = function makeWarning(aWarningMessage) {
    const warningPattern = /(.+):(\d+): warning: (.+)/g;
    let matches = warningPattern.exec(aWarningMessage);

    if (!matches) {
        return null;
    }
    
    return { filename:matches[1], lineNumber:matches[2], warningMessage:matches[3] };
}

