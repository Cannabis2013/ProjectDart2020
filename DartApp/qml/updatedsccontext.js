.import "dsccontrollerinterface.js" as DSCInterface

function updateTurnValues()
{
    var json = DSCInterface.getTurnValues();
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

function addInput(score)
{
    var obj = {score : score};
    var json = JSON.stringify(obj);
    var response = dsController.addInput(json);
    return JSON.parse(response);
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

function setWinnerDetails()
{
    let winnerDetails = DSCInterface.getWinnerValues();
    keyDataDisplay.setCurrentWinner(winnerDetails["winnerName"]);
    keyDataDisplay.setThrowSuggestion("");
    dsscContent.state = "winner";
}

function clearComponents()
{
    singleColumnScoreBoard.clearData();
    singleColumnScoreTurnController.reset();
    keyDataDisplay.clear();
}
