function process() {
        var name = userNameEdit.currentValue
        if (name === "")
                return
        var mail = mailEdit.currentValue
        if (mail === "")
                mail = "defaultsucker@gmail.com"
        var obj = {
                "name": name,
                "mail": mail
        }
        var json = JSON.stringify(obj)
        endStateButtons.buttonOneEnabled = false
        endStateButtons.buttonTwoEnabled = false
        playersContext.createPlayer(json)
        backButtonClicked()
}

function evaluateInputs() {
        var playerName = userNameEdit.currentValue
        if (playerName !== "")
                endStateButtons.buttonTwoEnabled = true
        else
                endStateButtons.buttonTwoEnabled = false
}
