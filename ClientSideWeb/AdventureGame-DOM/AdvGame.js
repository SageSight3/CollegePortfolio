var story = JSON.parse(document.getElementById('advGame').textContent)

function nextScene(aSceneID) {
//find index of scene with aSceneID
    let sceneIndex = getSceneID(aSceneID);

//load scene

    let scene = story["scenes"][sceneIndex];

//load scene into html

    //clear previous scene
    document.getElementById('story').innerHTML = "";
    document.getElementById('choices').innerHTML = "";

    let flavEl = document.createElement("p");
    flavEl.innerHTML = scene.flavorText;
    document.getElementById("story").append(flavEl);

    if (scene.images != "") { //change to handle multiple images
        let sceneImage = document.createElement("img");
        sceneImage.src = "images/" + scene.images;
        document.getElementById("story").append(sceneImage);
    }

    if (scene.choices == 0) {
        let ending = document.createElement("p");
        if (scene.endingType == "good") {
            ending.innerHTML = "Good Ending";
            document.getElementById("bg").style.backgroundImage = "url('./images/AvaliFlagGood.webp')";
            document.getElementById("game").style.backgroundColor = "rgb(0, 0 , 112)";
        } else {
            ending.innerHTML = "Bad Ending";
            document.getElementById("bg").style.backgroundImage = "url('./images/AvaliFlagBad.webp')";
            document.getElementById("game").style.backgroundColor = "rgb(112,0,0)";
        }
        document.getElementById('choices').append(ending);
        return;
    } else {
        document.getElementById("game").style.backgroundColor = "orange";
    }

    for(let index = 0; index < scene.choices.length; ++index) {
        let aChoice = document.createElement("button");
        aChoice.onclick = function() {nextScene(scene.choices[index].choiceID)};
        aChoice.innerHTML = scene.choices[index].choiceText;
        document.getElementById("choices").append(aChoice);
    }

}

nextScene("start");

function getSceneID(aSceneID) {
    for (let index = 0; index < story["scenes"].length; ++index) {
        if (story["scenes"][index]["sceneID"] == aSceneID) {
            return index;
        }
    }
}