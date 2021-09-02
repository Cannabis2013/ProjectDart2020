function initializeComponent()
{
    connectInterface();
    applicationInterface.requestCurrentTournamentId();
}

function connectInterface()
{
    applicationInterface.sendOrderedDartsPoints.connect(recievePoints);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    applicationInterface.dartsPointControllerIsReady.connect(backendInitializedAndReady);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.connect(handleDartsMetaData);
    applicationInterface.dartsControllerRemovedPoint.connect(backendRemovedPoint);
    applicationInterface.addedDartsPoint.connect(backendPersistedInput);
}

function disconnectInterface()
{
    applicationInterface.sendOrderedDartsPoints.disconnect(recievePoints);
    applicationInterface.dartsPointControllerIsReady.disconnect(backendInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.disconnect(handleDartsMetaData);
    applicationInterface.dartsControllerRemovedPoint.disconnect(backendRemovedPoint);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.addedDartsPoint.disconnect(backendPersistedInput);
}

function handleDartsMetaData(data){
    var json = JSON.parse(data);
    initializeMetaValues(json);
    initializeScoreBoard();
    applicationInterface.requestOrderedDartsInputs();
}

function initializeMetaValues(json)
{
    metaValues.title = json["title"];
    metaValues.winnerName= json["winnerName"];
    metaValues.keyPoint = json["keyPoint"];
    metaValues.attempts = json["attempts"];
    metaValues.assignedPlayerNames = json["assignedPlayerNames"];
}

function initializeScoreBoard()
{
    var assignedPlayerNames = metaValues.assignedPlayerNames;
    var keyPoint = metaValues.keyPoint;
    pointScoreBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function backendInitializedAndReady()
{
    dartsPointMultiColumnBody.state = "ready";
}

function recievePoints(scores)
{
    var jsonData = JSON.parse(scores);
    var count = jsonData.length;
    for(var i = 0;i < count;++i)
    {
        var entity = jsonData[i];
        var playerName = entity["playerName"];
        var playerPoint = entity["score"];
        var playerScore = entity["totalScore"];
        pointScoreBoard.setData(playerName,playerPoint,playerScore);
    }
    applicationInterface.requestControllerState();
}

// When backend has evaluated and persisted player input
function backendPersistedInput(data)
{
    var json = JSON.parse(data);
    updatePointBoard(json);
    setThrowSuggestion(json);
    setTurnControllerValues(json);
    dartsPointMultiColumnBody.state = "waitingForInput";
}

function updatePointBoard(json)
{
    let playerName = json["playerName"];
    let pointValue = json["score"];
    let scoreValue = json["totalScore"];
    pointScoreBoard.setData(playerName,pointValue,scoreValue);
}

function setThrowSuggestion(json)
{
    keyDataDisplay.setThrowSuggestion(json.targetRow);
}

function reinitialize()
{
    // reinitialize controller after reset
    pointScoreBoard.clearData();
    initializeScoreBoard();
    requestStatusFromBackend();
}

function handleRequestTournamentReset()
{
    if(dartsPointMultiColumnBody.state === "ready")
        dartsPointMultiColumnBody.state = "stopped";
    applicationInterface.requestTournamentReset();
}

function backendRemovedPoint(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    pointScoreBoard.takeData(playerName);
    setTurnControllerValues(json);
    dartsPointMultiColumnBody.state = "waitingForInput";
}

function backendIsReadyAndAwaitsInput(data)
{
    var json = JSON.parse(data);
    let throwSuggestion = json.targetRow;
    let suggestion = textSourceContainer.throwSuggestLabel + " " + throwSuggestion;
    keyDataDisplay.setThrowSuggestion(suggestion);
    setTurnControllerValues(json);
    dartsPointMultiColumnBody.state = "waitingForInput";
}

function setTurnControllerValues(json)
{
    singleColumnTurnController.leftButtonEnabled = json["canUndo"];
    singleColumnTurnController.rightButtonEnabled = json["canRedo"];
    singleColumnTurnController.currentRoundIndex = json["roundIndex"];
    singleColumnTurnController.currentPlayer = json["currentPlayerName"];
}

function handlePointKeyPadInput(value,keyCode){
    dartsPointMultiColumnBody.state = "waitingForInputConfirmation";
    var obj = {
        point : value,
        modKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    applicationInterface.sendDartsPoint(json);
}

function backendIsStopped()
{
    if(dartsPointMultiColumnBody.state !== "preRestart")
        dartsPointMultiColumnBody.state = "stopped";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    tournamentMetaData.determinedWinner = json.winner;
    dartsPointMultiColumnBody.state = "winner";
}

function undoClicked()
{
    dartsPointMultiColumnBody.state = "waitingForInputConfirmation";
    requestUndo();
}

function redoClicked()
{
    dartsPointMultiColumnBody.state = "waitingForInputConfirmation";
    requestRedo();
}

function setWinnerText()
{
    var winnerName = textSourceContainer.winnerLabel + " " +
            tournamentMetaData.determinedWinner;
    keyDataDisplay.item.setCurrentWinner(winnerName);
}

