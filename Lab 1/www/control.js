var url = "control/"

document.getElementById("red").addEventListener("click", function () {
    console.log('red');

    let xhr = new XMLHttpRequest();
    xhr.open("POST", url, true);
    xhr.setRequestHeader("Content-Type", "application/json; charset=UTF-8");
    xhr.send(JSON.stringify({"mode": "manual", "color": "red"}));



});
document.getElementById("yellow").addEventListener("click", function () {
    console.log('yellow');
});
document.getElementById("green").addEventListener("click", function () {
    console.log('green');
});
