function process(){
    var playerName = userNameEdit.currentValue;
    if(playerName === "")
        return;
    var mail = mailEdit.currentValue;
    if(mail === "")
        mail = "defaultsucker@gmail.com";
    var obj = {
        playerName : playerName,
        playerMail : mail
    };
    var json = JSON.stringify(obj);
    endStateButtons.buttonOneEnabled = false;
    endStateButtons.buttonTwoEnabled = false;
    playersContext.createPlayer(json);
    requestQuit();
}

function evaluateInputs(){
    var playerName = userNameEdit.currentValue;
    if(playerName !== "")
        endStateButtons.buttonTwoEnabled = true;
    else
        endStateButtons.buttonTwoEnabled = false;
}
