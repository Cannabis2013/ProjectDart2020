
function setRestart()
{
    turnControllerBody.state = "startState";
    turnControllerBody.restartButtonClicked();
}

function clearLabels()
{
    turnControllerBody.currentPlayer = "Current player";
    turnControllerBody.currentRoundIndex = "Current round";
}
