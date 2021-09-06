var url = "control/"
var mode = "manual"
sendRequestMode(mode)
console.log("done initializing")

function sendRequest(color){
    console.log("sending with color")
    console.log(color);
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    xhr.send(JSON.stringify({"mode": mode, "color": color}));
}


function sendRequestMode(){
    // console.log(mode)
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
    console.log("sending auto")
    mode = "auto"
    sendRequestMode()
});

document.getElementById("manual").addEventListener("click", function () {
    console.log("sending manual")
    mode = "manual"
    sendRequestMode()
});




// document.getElementById("mode").addEventListener("click", function(){
//     console.log("click on toggle switch")
//     if (mode == "auto"){
//         console.log("sending auto")
//         mode = "manual"
//         sendRequestMode()
//     }
//     else if (mode == "manual"){
//         console.log("sending manual")
//         mode = "auto"
//         sendRequestMode()
//     }
// });
