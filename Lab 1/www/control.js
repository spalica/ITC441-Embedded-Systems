var url = "control/"
var mode = "manual"

function sendRequest(color){
    console.log("sending with color")
    console.log(color);
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    xhr.send(JSON.stringify({"mode": "manual", "color": color}));
}


// function sendRequest(){
//     console.log("sending without color")
//     let xhr = new XMLHttpRequest();
//     xhr.open("POST", url, true);
//     xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
//     xhr.send(JSON.stringify({"mode": mode}));
// }




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
        mode = "manual"
        sendRequest("MODE_ONLY")
    }
    else if (mode == "manual"){
        mode = "auto"
        sendRequest("MODE_ONLY")
    }
});
