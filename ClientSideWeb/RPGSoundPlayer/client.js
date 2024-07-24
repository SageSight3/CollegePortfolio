let currentSound = null;

function playSwingSound() {
    let mySound = new Audio("sounds/battle/swing.wav");
    mySound.play();
}

function getSoundPlayerFor(soundURL) {
    return function () {
        let sound = new Audio(soundURL);
        currentSound = sound;
        document.getElementById("soundPlaying").innerHTML = "playing ".concat(soundURL);
        sound.play()
    }
}

function updateProgressBar() {
    if (currentSound != null && isFinite(currentSound.duration)) {
        document.getElementById("prog").max = currentSound.duration;
        document.getElementById("prog").value = currentSound.currentTime;
        //console.log(currentSound.duration);
        //console.log(currentSound.currentTime);
    }
}

setInterval(updateProgressBar, 15);

function setSoundInfo(path) {
    //console.log("mouseenter");
    document.getElementById("soundInfo").innerText = path;
}

function clearSoundInfo() {
    //console.log("mouseleave");
    document.getElementById("soundInfo").innerText = "Click a sound";
}

function addListeners(button) {
   button.addEventListener("click", getSoundPlayerFor(button.dataset.path));
   //why does this handler specifically need an anonymous function?
   button.addEventListener("mouseenter", function () { setSoundInfo(button.dataset.path); });
   button.addEventListener("mouseleave", clearSoundInfo);
}

let soundButtons = document.querySelectorAll(".RPGSound");

for(let button of soundButtons) {
    addListeners(button);
}

function appendButtonForSound(title, soundURL) {
    let b = document.createElement("button");
    b.innerText = title;
    b.setAttribute("class", "RPGSound"); //https://www.quora.com/Can-you-create-an-element-in-JS-with-an-ID-or-a-class
    b.dataset.path = soundURL;
    addListeners(b);
    document.body.append(b);
}

appendButtonForSound("Coin", "sounds/inventory/coin.wav");