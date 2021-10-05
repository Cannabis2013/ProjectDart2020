function initializeComponent()
{
    connectInterface();
    applicationInterface.requestCurrentTournamentId();
}

function connectInterface()
{
    applicationInterface.sendDartsTournamentData.connect(handleMetaData);
    applicationInterface.sendOrderedDartsInputs.connect(recievePoints);
    applicationInterface.dartsControllerIsReady.connect(backendIsReady);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.dartsInputRemoveSucces.connect(backendRemovedPoint);
    applicationInterface.addedInput.connect(addInput);
}

function disconnectInterface()
{
    applicationInterface.sendDartsTournamentData.disconnect(handleMetaData);
    applicationInterface.sendOrderedDartsInputs.disconnect(recievePoints);
    applicationInterface.dartsControllerIsReady.disconnect(backendIsReady);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerIsReset.disconnect(reinitialize);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.dartsInputRemoveSucces.disconnect(backendRemovedPoint);
    applicationInterface.addedInput.disconnect(addInput);
}

function handleMetaData(data){
    var json = JSON.parse(data);
    metaValues.title = json["title"];
    metaValues.winnerName= json["winnerName"];
    metaValues.keyPoint = json["keyPoint"];
    metaValues.assignedPlayerNames = json["assignedPlayerNames"];
    initializeScoreBoard();
    applicationInterface.requestOrderedDartsInputs();
}

function initializeScoreBoard()
{
    var assignedPlayerNames = metaValues.assignedPlayerNames;
    var keyPoint = metaValues.keyPoint;
    singleColumnPointBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function recievePoints(points)
{
    var jsonData = JSON.parse(points);
    var count = jsonData.length;
    for(var i = 0;i < count;++i)
    {
        var entity = jsonData[i];
        var playerName = entity["playerName"];
        var playerPoint = entity["point"];
        var totalScore = entity["totalScore"];
        singleColumnPointBoard.setData(playerName,playerPoint,totalScore);
    }
    applicationInterface.requestControllerState();
}

function backendIsReady()
{
    dpscBody.state = "ready";
}

// When backend has evaluated and persisted player input
function addInput(data)
{
    var json = JSON.parse(data);
    updatePointBoard(json);
    setThrowSuggestion(json);
    setTurnControllerValues(json);
    dpscBody.state = "waitingForInput";
}

function updatePointBoard(json)
{
    let playerName = json["playerName"];
    let playerPoint = json["point"];
    let totalScore = json["totalScore"];
    singleColumnPointBoard.setData(playerName,playerPoint,totalScore);
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
    pointSingleColumnTurnController.currentRoundIndex = json["roundIndex"];
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
    metaValues.winnerName = json.playerName;
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
