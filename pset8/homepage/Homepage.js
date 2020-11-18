// Home
function dosomething() {
    document.getElementById("designtxt").style.backgroundColor = "black";
    document.getElementById("designtxt").style.color = "white";
}
function dontdosomething() {
    var text = document.getElementById("designtxt").style.backgroundColor = "";
    var text = document.getElementById("designtxt").style.color = ""
}

// Portfolio
function ddefault() {
    document.querySelector('#card_school_roster').style.display = "block";
    document.querySelector('#card_DNA').style.display = "block";
    document.querySelector('#card_spell').style.display = "block";
    document.querySelector('#card_filter').style.display = "block";
    document.querySelector('#card_recover').style.display = "none";
    document.querySelector('#card_tideman').style.display = "none";
    document.querySelector('#card_readability').style.display = "none";
    document.querySelector('#card_encrypter').style.display = "block";
    document.querySelector('#card_credit').style.display = "block";
    document.querySelector('#card_miel').style.display = "none";
}
function al() {
    document.querySelector('#card_school_roster').style.display = "block";
    document.querySelector('#card_DNA').style.display = "block";
    document.querySelector('#card_spell').style.display = "block";
    document.querySelector('#card_filter').style.display = "block";
    document.querySelector('#card_recover').style.display = "block";
    document.querySelector('#card_tideman').style.display = "block";
    document.querySelector('#card_readability').style.display = "block";
    document.querySelector('#card_encrypter').style.display = "block";
    document.querySelector('#card_credit').style.display = "block";
    document.querySelector('#card_miel').style.display = "block";
}
function cod() {
    document.querySelector('#card_school_roster').style.display = "block";
    document.querySelector('#card_DNA').style.display = "block";
    document.querySelector('#card_spell').style.display = "block";
    document.querySelector('#card_filter').style.display = "block";
    document.querySelector('#card_recover').style.display = "block";
    document.querySelector('#card_tideman').style.display = "block";
    document.querySelector('#card_readability').style.display = "block";
    document.querySelector('#card_encrypter').style.display = "block";
    document.querySelector('#card_credit').style.display = "block";
    document.querySelector('#card_miel').style.display = "none";
}
function mus() {
    document.querySelector('#card_school_roster').style.display = "none";
    document.querySelector('#card_DNA').style.display = "none";
    document.querySelector('#card_spell').style.display = "none";
    document.querySelector('#card_filter').style.display = "none";
    document.querySelector('#card_recover').style.display = "none";
    document.querySelector('#card_tideman').style.display = "none";
    document.querySelector('#card_readability').style.display = "none";
    document.querySelector('#card_encrypter').style.display = "none";
    document.querySelector('#card_credit').style.display = "none";
    document.querySelector('#card_miel').style.display = "block";
}

window.onload=function() {
    document.getElementById("abtpic").querySelector('img').style.transform = "rotate(360deg)";
}

// About Me
function swap_color(id) {
    let item = document.querySelector(id);

    if (item.style.backgroundColor == "white") {
        item.style.backgroundColor = "black";
        item.style.color = "white";
    } else {
        item.style.backgroundColor = "white";
        item.style.color = "black";
    }
}

