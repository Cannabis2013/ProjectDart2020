function initializeComponent()
{
    connectInterface();
    applicationInterface.requestCurrentTournamentId();
}

function connectInterface()
{
    applicationInterface.sendDartsTournamentData.connect(handleMetaData);
    applicationInterface.sendDartsScores.connect(recieveScores);
    applicationInterface.controllerReady.connect(controllerReady);
    applicationInterface.controllerStopped.connect(backendIsStopped);
    applicationInterface.winnerFound.connect(winnerFound);
    applicationInterface.sendDartsScore.connect(updatePlayerScore);
    applicationInterface.updateDartsTurnValues.connect(updateTurnValues);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
}

function disconnectInterface()
{
    applicationInterface.sendDartsTournamentData.disconnect(handleMetaData);
    applicationInterface.sendDartsScores.disconnect(recieveScores);
    applicationInterface.controllerReady.disconnect(controllerReady);
    applicationInterface.controllerStopped.connect(backendIsStopped);
    applicationInterface.updateDartsTurnValues.disconnect(updateTurnValues);
    applicationInterface.winnerFound.disconnect(winnerFound);
    applicationInterface.sendDartsScore.disconnect(updatePlayerScore);
    applicationInterface.dartsControllerIsReset.disconnect(reinitialize);
}

function handleMetaData(data){
    var json = JSON.parse(data);
    metaValues.title = json["title"];
    metaValues.winnerName= json["winnerName"];
    metaValues.keyPoint = json["keyPoint"];
    metaValues.assignedPlayerNames = getPlayerNames(json["assignedPlayerDetails"]);
    initializeScoreBoard();
    applicationInterface.requestDartsScores();
}

function getPlayerNames(playerDetails)
{
    let playerNames = [];
    let count = playerDetails.length;
    for(var i = 0;i < count;i++)
    {
        let playerDetail = playerDetails[i];
        let playerName = playerDetail["playerName"];
        playerNames.push(playerName);
    }
    return playerNames;
}

function initializeScoreBoard()
{
    var assignedPlayerNames = metaValues.assignedPlayerNames;
    var keyPoint = metaValues.keyPoint;
    singleColumnPointBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function recieveScores(scores)
{
    var json = JSON.parse(scores);
    addDartsScoresToScoreBoard(json);
    applicationInterface.requestControllerState();
}

function controllerReady()
{
    dpscBody.state = "ready";
}

function addDartsScoresToScoreBoard(json)
{
    for(var i = 0;i < json.length;++i)
        addToScoreBoard(json[i]);
}

function updatePlayerScore(data)
{
    var json = JSON.parse(data);
    addToScoreBoard(json);
    applicationInterface.dartsNextTurn();
}

function updateTurnValues(data)
{
    setThrowSuggestion(json);
    setTurnControllerValues(json);
    applicationInterface.requestControllerState();
}

function addToScoreBoard(json)
{
    let playerName = json["inputPlayerName"];
    let playerPoint = json["point"];
    let playerScore = json["remainingScore"];
    let middleValue = json["middleValue"];
    let minimum = json["currentMinimum"];
    let maximum = json["currentMaximum"];
    let inGame = json["inGame"];
    singleColumnPointBoard.setData(playerName,playerScore,middleValue,minimum,maximum,inGame);
}

function setThrowSuggestion(json)
{
    keyDataDisplay.setThrowSuggestion(json["suggestedFinish"]);
}

function reinitialize()
{
    singleColumnPointBoard.clearData();
    pointSingleColumnTurnController.reset();
    keyDataDisplay.clear();
    initializeScoreBoard();
    dpscBody.state = "ready";
}

function handleRequestTournamentReset()
{
    dpscBody.state = "stopped";
    applicationInterface.requestTournamentReset();
}

function setTurnControllerValues(json)
{
    pointSingleColumnTurnController.leftButtonEnabled = json["canUndo"];
    pointSingleColumnTurnController.rightButtonEnabled = json["canRedo"];
    pointSingleColumnTurnController.currentRoundIndex = json["currentRoundIndex"];
    pointSingleColumnTurnController.currentPlayer = json["currentPlayerName"];
}

function handleScoreKeyPadInput(input, keyCode){
    dpscBody.state = "waitingForInputConfirmation";
    var obj = {
        point : input,
        modKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    applicationInterface.addUserInput(json);
}

function backendIsStopped()
{
    if(dpscBody.state !== "preRestart")
        dpscBody.state = "stopped";
}

function winnerFound(data)
{
    var json = JSON.parse(data);
    metaValues.winnerName = json["winnerName"];
    dpscBody.state = "winner";
}

function updateTurnValues(data)
{
    var json = JSON.parse(data);
    setThrowSuggestion(json);
    setTurnControllerValues(json);
    dpscBody.state = "waitingForInput";
}

function undoClicked()
{
    dpscBody.state = "waitingForInputConfirmation";
    requestUndo();
    applicationInterface.requestUndo();
}

function redoClicked()
{
    dpscBody.state = "waitingForInputConfirmation";
    applicationInterface.requestRedo();
}

function pauseClicked()
{
    dpscBody.state = "stopped";
    applicationInterface.requestStopGame();
}

function setWinnerText()
{
    keyDataDisplay.setCurrentWinner(metaValues.winnerName);
}
