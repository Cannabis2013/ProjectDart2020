function startGame()
{
    let status = dsController.status();
    if(status === 0)
    {
        updateTurnValues();
        dsscContent.state = "waitingForInput";
    }
}
function updateTurnValues()
{
    var byteArray = dsController.getTurnValues();
    var json = JSON.parse(byteArray);
    setTurnControllerValues(json);
    keyDataDisplay.setThrowSuggestion(json["finishCandidate"]);
}

function setTurnControllerValues(json)
{
    singleColumnScoreTurnController.leftButtonEnabled = json["canUndo"];
    singleColumnScoreTurnController.rightButtonEnabled = json["canRedo"];
    singleColumnScoreTurnController.currentRoundIndex = json["currentRoundIndex"];
    singleColumnScoreTurnController.currentPlayer = json["currentPlayerName"];
}
function handleScoreKeyPadInput(value){
    dsscContent.state = "waitingForInputConfirmation";
    var response = addInput(value);
    updateScoreBoard(response);
    updateTurnValues();
    setState("waitingForInput");
}
function addInput(score)
{
    var obj = {score : score};
    var json = JSON.stringify(obj);
    var response = dsController.addInput(json);
    return JSON.parse(response);
}
function backendIsStopped()
{
    if(dsscContent.state !== "preRestart")
        dsscContent.state = "stopped";
}
function winnerFound()
{
    var byteArray = dsController.getWinnerJson();
    var json = JSON.parse(byteArray);
    var winnerDetails = json["WinnerDetails"];
    keyDataDisplay.setCurrentWinner(winnerDetails["winnerName"]);
    keyDataDisplay.setThrowSuggestion("");
    dsscContent.state = "winner";
}
function undoClicked()
{
    dsscContent.state = "waitingForInputConfirmation";
    var response = dsController.undoTurn();
    updateScoreBoard(JSON.parse(response));
    updateTurnValues();
    setState("waitingForInput");
}

function redoClicked()
{
    dsscContent.state = "waitingForInputConfirmation";
    var response = dsController.redoTurn();
    updateScoreBoard(JSON.parse(response));
    updateTurnValues();
    setState("waitingForInput");
}

function updateScoreBoard(json)
{
    let playerName = json["inputPlayerName"];
    let playerScore = json["remainingScore"];
    let reportAsByteArray = statistics.createReport(playerName);
    let report = JSON.parse(reportAsByteArray);
    let minVal = report["minimum"];
    let midVal = report["middle"];
    let maxVal = report["maximum"];
    singleColumnScoreBoard.setData(playerName,playerScore,minVal,midVal,maxVal);
}

function setState(state)
{
    let status = dsController.status();
    if(status === 0)
        dsscContent.state = state;
    else if(status === 2)
        winnerFound();
}
