var url = "control/"
var mode = "manual"

function sendRequest(color){
    console.log(color);
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    xhr.send(JSON.stringify({"mode": "manual", "color": color}));
}

document.getElementById("red").addEventListener("click", function () {
    if (mode == "manual"){
        sendRequest("red")
    }
    else{
        alert("cannot set color manually while not in manual mode.")
    }
});

document.getElementById("yellow").addEventListener("click", function () {
    if (mode == "manual"){
        sendRequest("yellow")
    }
    else{
        alert("cannot set color manually while not in manual mode.")
    }
});

document.getElementById("green").addEventListener("click", function () {
    if (mode == "manual"){
        sendRequest("green")
    }
    else{
        alert("cannot set color manually while not in manual mode.")
    }
});
