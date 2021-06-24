function initializeComponent()
{
    connectInterface();
    applicationInterface.assembleDartsTournamentValues();
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
    dartsPointMultiColumnBody.requestStart.connect(applicationInterface.handleRequestStart);
    dartsPointMultiColumnBody.requestStop.connect(applicationInterface.handleRequestStop);
    dartsPointMultiColumnBody.requestRestart.connect(applicationInterface.handleRestartTournament);
    dartsPointMultiColumnBody.sendInput.connect(applicationInterface.handleDartsPointInput);
    dartsPointMultiColumnBody.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedPoint.connect(backendRemovedPoint);
    dartsPointMultiColumnBody.requestUndo.connect(applicationInterface.handleDartsUndoRequest);
    dartsPointMultiColumnBody.requestRedo.connect(applicationInterface.handleDartsRedoRequest);
    pointKeyPad.sendInput.connect(handlePointKeyPadInput);
    applicationInterface.addedDartsPoint.connect(backendPersistedInput);
}

function disconnectInterface()
{
    applicationInterface.sendOrderedDartsPoints.disconnect(
                recievePoints);
    applicationInterface.dartsPointControllerIsReady.disconnect(backendInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.disconnect(handleDartsMetaData);
    dartsPointMultiColumnBody.requestStart.disconnect(applicationInterface.handleRequestStart);
    dartsPointMultiColumnBody.requestStop.disconnect(applicationInterface.handleRequestStop);
    dartsPointMultiColumnBody.requestRestart.disconnect(applicationInterface.handleRestartTournament);
    dartsPointMultiColumnBody.sendInput.disconnect(applicationInterface.handleDartsPointInput);
    dartsPointMultiColumnBody.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedPoint.disconnect(backendRemovedPoint);
    dartsPointMultiColumnBody.requestUndo.disconnect(applicationInterface.handleDartsUndoRequest);
    dartsPointMultiColumnBody.requestRedo.disconnect(applicationInterface.handleDartsRedoRequest);
    pointKeyPad.sendInput.disconnect(handlePointKeyPadInput);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.addedDartsPoint.disconnect(backendPersistedInput);
}

function handleDartsMetaData(data){
    var json = JSON.parse(data);
    dartsSingleAttemptValues.title = json["title"];
    dartsSingleAttemptValues.winnerName= json["winnerName"];
    dartsSingleAttemptValues.keyPoint = json["keyPoint"];
    dartsSingleAttemptValues.attempts = json["attempts"];
    dartsSingleAttemptValues.assignedPlayerNames = json["assignedPlayerNames"];

    initializeScoreBoard();
    applicationInterface.requestOrderedDartsInputs();
}

function initializeScoreBoard()
{
    var assignedPlayerNames = dartsSingleAttemptValues.assignedPlayerNames;
    var keyPoint = dartsSingleAttemptValues.keyPoint;
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
    dartsPointMultiColumnBody.sendInput(json);
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
