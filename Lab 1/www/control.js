var url = "control/"
var mode = "manual"

function sendRequest(color){
    console.log("sending with color")
    console.log(color);
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    xhr.send(JSON.stringify({"mode": mode, "color": color}));
}


function sendRequestMode(){
    console.log("sending without color")
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


document.getElementById("mode").addEventListener("click", function(){
    if (mode == "auto"){
        console.log("sending auto")
        mode = "manual"
        sendRequestMode(mode)
    }
    else if (mode == "manual"){
        console.log("senging manual")
        mode = "auto"
        sendRequestMode(mode)
    }
});
