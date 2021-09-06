var url = "control/"
var mode = "manual"
sendRequestMode(mode)

function sendRequest(color){
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    xhr.send(JSON.stringify({"mode": mode, "color": color}));
}

function sendRequestMode(){
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    xhr.send(JSON.stringify({"mode": mode}));
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

document.getElementById("auto").addEventListener("click", function () {
    mode = "auto"
    sendRequestMode()
});

document.getElementById("manual").addEventListener("click", function () {
    mode = "manual"
    sendRequestMode()
});
