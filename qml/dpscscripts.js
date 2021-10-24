function initializeComponent()
{
    connectInterface();
    applicationInterface.requestCurrentTournamentId();
}

function connectInterface()
{
    applicationInterface.sendDartsTournamentData.connect(handleMetaData);
    applicationInterface.sendDartsScores.connect(recieveScores);
    applicationInterface.dartsControllerIsReady.connect(backendIsReady);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.controllerSendsTurnValues.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.addedInput.connect(backendAddedInput);
    applicationInterface.dartsInputRemoveSucces.connect(backendRemovedPoint);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
}

function disconnectInterface()
{
    applicationInterface.sendDartsTournamentData.disconnect(handleMetaData);
    applicationInterface.sendDartsScores.disconnect(recieveScores);
    applicationInterface.dartsControllerIsReady.disconnect(backendIsReady);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.controllerSendsTurnValues.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerIsReset.disconnect(reinitialize);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.dartsInputRemoveSucces.disconnect(backendRemovedPoint);
    applicationInterface.addedInput.disconnect(backendAddedInput);
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

function addDartsScoresToScoreBoard(json)
{
    for(var i = 0;i < json.length;++i)
        addToScoreBoard(json[i]);
}

function addToScoreBoard(json)
{
    let playerName = json["inputPlayerName"];
    let playerPoint = json["point"];
    let playerScore = json["remainingScore"];
    let middleValue = json["middleValue"];
    let minimum = json["currentMinimum"];
    let maximum = json["currentMaximum"];
    singleColumnPointBoard.setData(playerName,playerScore,middleValue,minimum,maximum);
}

function backendIsReady()
{
    dpscBody.state = "ready";
}

function backendAddedInput(data)
{
    var json = JSON.parse(data);
    addToScoreBoard(json);
    setThrowSuggestion(json);
    setTurnControllerValues(json);
    applicationInterface.requestControllerState();
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

function backendRemovedPoint(data)
{
    var json = JSON.parse(data);
    setTurnControllerValues(json);
    updatePointBoard(json);
    dpscBody.state = "waitingForInput";
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

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    metaValues.winnerName = json["winnerName"];
    dpscBody.state = "winner";
}

function backendIsReadyAndAwaitsInput(data)
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
