var url = "control/"


function sendRequest(color){
    console.log(color);
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    xhr.send(JSON.stringify({"mode": "manual", "color": color}));
}


document.getElementById("red").addEventListener("click", function () {
    // console.log('red');
    // let xhr = new XMLHttpRequest();
    // xhr.open("POST", url, true);
    // xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    // xhr.send(JSON.stringify({"mode": "manual", "color": "red"}));
    sendRequest("red")
});

document.getElementById("yellow").addEventListener("click", function () {
    // console.log('yellow');
    // let xhr = new XMLHttpRequest();
    // xhr.open("POST", url, true);
    // xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    // xhr.send(JSON.stringify({"mode": "manual", "color": "yellow"}));
    sendRequest("yellow")
});

document.getElementById("green").addEventListener("click", function () {
    console.log('green');
    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    xhr.send(JSON.stringify({"mode": "manual", "color": "green"}));
});





