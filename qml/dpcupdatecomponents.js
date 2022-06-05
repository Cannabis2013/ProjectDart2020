.import "dpccontrollerinterface.js" as DPCInterface

function updateTurnValues(){
    var json = DPCInterface.getTurnValues();
    setTurnControllerValues(json);
    updateFinishCandidate(json);
}

function setTurnControllerValues(json){
    dpcTurnController.leftButtonEnabled = json["canUndo"];
    dpcTurnController.rightButtonEnabled = json["canRedo"];
    dpcTurnController.currentRoundIndex = json["currentRoundIndex"];
    dpcTurnController.currentPlayer = json["currentPlayerName"];
}

function updateScoreBoard(json){
    let playerName = json["inputPlayerName"];
    let playerScore = json["remainingScore"];
    let inGame = json["inGame"];
    let reportAsByteArray = statistics.createReport(playerName);
    let report = JSON.parse(reportAsByteArray);
    let minVal = report["minimum"];
    let midVal = report["middle"];
    let maxVal = report["maximum"];
    dpcScoreBoard.setData(playerName,playerScore,minVal,midVal,maxVal,inGame);
}

function setWinnerDetails(){
    let winnerDetails = DPCInterface.getWinnerValues();
    keyDataDisplay.setCurrentWinner(winnerDetails["winnerName"]);
    keyDataDisplay.setThrowSuggestion("");
    dpcContent.state = "winner";
}

function clearComponents(){
    dpcScoreBoard.clearData();
    dpcTurnController.reset();
    keyDataDisplay.clear();
}

function updateFinishCandidate(json){
    keyDataDisplay.setThrowSuggestion(json["finishCandidate"]);
}
