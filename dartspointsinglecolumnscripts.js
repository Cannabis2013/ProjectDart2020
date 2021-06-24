function initializeComponent()
{
    connectInterface();
    applicationInterface.assembleDartsTournamentValues();
}

function connectInterface()
{
    // Initializing ui values
    applicationInterface.sendDartsTournamentData.connect(handleDartsTournamentMetaData);
    applicationInterface.sendOrderedDartsPoints.connect(recievePoints);
    applicationInterface.dartsPointControllerIsReady.connect(backendIsReady);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.dartsControllerRemovedPoint.connect(backendRemovedPoint);
    applicationInterface.addedDartsPoint.connect(handleBackendPersistedInput);
}

function disconnectInterface()
{
    applicationInterface.sendDartsTournamentData.disconnect(handleDartsTournamentMetaData);
    applicationInterface.sendOrderedDartsPoints.disconnect(recievePoints);
    applicationInterface.dartsPointControllerIsReady.disconnect(backendIsReady);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerIsReset.disconnect(reinitialize);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.dartsControllerRemovedPoint.disconnect(backendRemovedPoint);
    applicationInterface.addedDartsPoint.disconnect(handleBackendPersistedInput);
}

function handleDartsTournamentMetaData(data){
    var json = JSON.parse(data);
    dartsPointSingleColumnMetaValues.title = json["title"];
    dartsPointSingleColumnMetaValues.winnerName= json["winnerName"];
    dartsPointSingleColumnMetaValues.keyPoint = json["keyPoint"];
    dartsPointSingleColumnMetaValues.attempts = json["attempts"];
    dartsPointSingleColumnMetaValues.assignedPlayerNames = json["assignedPlayerNames"];
    initializeScoreBoard();
    applicationInterface.requestOrderedDartsInputs();
}

function initializeScoreBoard()
{
    var assignedPlayerNames = dartsPointSingleColumnMetaValues.assignedPlayerNames;
    var keyPoint = dartsPointSingleColumnMetaValues.keyPoint;
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
    dartsPointSingleColumnBody.state = "ready";
}

// When backend has evaluated and persisted player input
function handleBackendPersistedInput(data)
{
    var json = JSON.parse(data);
    updatePointBoard(json);
    setThrowSuggestion(json);
    setTurnControllerValues(json);
    dartsPointSingleColumnBody.state = "waitingForInput";
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
    keyDataDisplay.setThrowSuggestion(json.targetRow);
}

function reinitialize()
{
    singleColumnPointBoard.clearData();
    pointSingleColumnTurnController.backendIsStopped();
    keyDataDisplay.clear();
    initializeScoreBoard();
    dartsPointSingleColumnBody.state = "ready";
}

function handleRequestTournamentReset()
{
    if(dartsPointSingleColumnBody.state === "ready")
        dartsPointSingleColumnBody.state = "stopped";
}

function backendRemovedPoint(data)
{
    var json = JSON.parse(data);
    setTurnControllerValues(json);
    updatePointBoard(json);
    dartsPointSingleColumnBody.state = "waitingForInput";
}

function setTurnControllerValues(json)
{
    pointSingleColumnTurnController.leftButtonEnabled = json["canUndo"];
    pointSingleColumnTurnController.rightButtonEnabled = json["canRedo"];
    pointSingleColumnTurnController.currentRoundIndex = json["roundIndex"];
    pointSingleColumnTurnController.currentPlayer = json["currentPlayerName"];
}

function handleScoreKeyPadInput(input, keyCode){
    dartsPointSingleColumnBody.state = "waitingForInputConfirmation";
    var obj = {
        point : input,
        modKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    applicationInterface.sendDartsPoint(json);
}

function backendIsStopped()
{
    if(dartsPointSingleColumnBody.state !== "preRestart")
        dartsPointSingleColumnBody.state = "stopped";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    dartsPointSingleColumnMetaValues.winnerName = json.playerName;
    dartsPointSingleColumnBody.state = "winner";
}

function backendIsReadyAndAwaitsInput(data)
{
    var json = JSON.parse(data);
    setThrowSuggestion(json);
    setTurnControllerValues(json);
    dartsPointSingleColumnBody.state = "waitingForInput";
}

function undoClicked()
{
    dartsPointSingleColumnBody.state = "waitingForInputConfirmation";
    requestUndo();
    applicationInterface.requestUndo();
}

function redoClicked()
{
    dartsPointSingleColumnBody.state = "waitingForInputConfirmation";
    applicationInterface.requestRedo();
}

function setWinnerText()
{
    keyDataDisplay.setCurrentWinner(dartsPointSingleColumnMetaValues.winnerName);
}
