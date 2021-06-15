function initializeComponent()
{
    connectInterface();
    requestControllerValues();
}

function connectInterface()
{
    dartsPointMultiColumnBody.requestControllerValues.connect(applicationInterface.assembleDartsTournamentValues);
    dartsPointMultiColumnBody.requestSingleAttemptPoints.connect(
                applicationInterface.handleRequestForDartsSingleAttemptPoints);
    applicationInterface.sendDartsPoints.connect(
                recieveDartsSingleAttemptPoints);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    applicationInterface.dartsPointControllerIsReady.connect(controllerIsInitializedAndReady);
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
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.addedDartsPoint.connect(extractPointScoreFromJson);
}

function disConnectInterface()
{
    dartsPointMultiColumnBody.requestControllerValues.disconnect(applicationInterface.assembleDartsTournamentValues);
    dartsPointMultiColumnBody.requestSingleAttemptPoints.disconnect(
                applicationInterface.handleRequestForDartsSingleAttemptPoints);
    applicationInterface.sendDartsPoints.disconnect(
                recieveDartsSingleAttemptPoints);
    applicationInterface.dartsSingleAttemptPointControllerIsReady.disconnect(controllerIsInitializedAndReady);
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
    applicationInterface.addedDartsPoint.disconnect(extractPointScoreFromJson);
}

function handleDartsMetaData(data){
    var json = JSON.parse(data);
    dartsSingleAttemptValues.title = json["title"];
    dartsSingleAttemptValues.winnerName= json["winnerName"];
    dartsSingleAttemptValues.keyPoint = json["keyPoint"];
    dartsSingleAttemptValues.attempts = json["attempts"];
    dartsSingleAttemptValues.assignedPlayerNames = json["assignedPlayerNames"];

    initializeScoreBoard();
    requestSingleAttemptPoints();
}

function initializeScoreBoard()
{
    var assignedPlayerNames = dartsSingleAttemptValues.assignedPlayerNames;
    var keyPoint = dartsSingleAttemptValues.keyPoint;
    pointScoreBoard.appendHeaderData(assignedPlayerNames,keyPoint);
}

function controllerIsInitializedAndReady()
{
    dartsPointMultiColumnBody.state = "ready";
}

function recieveDartsSingleAttemptPoints(scores)
{
    var jsonData = JSON.parse(scores);
    var count = jsonData.length;
    for(var i = 0;i < count;++i)
    {
        var entity = jsonData[i];
        var playerName = entity["playerName"];
        var playerScore = entity["score"];
        var playerPoint = entity["point"];
        pointScoreBoard.setData(playerName,playerPoint,playerScore);
    }
    dartsPointMultiColumnBody.requestStatusFromBackend();
}

// When backend has evaluated and persisted player input
function extractPointScoreFromJson(data)
{
    var json = JSON.parse(data);
    let playerName = json["playerName"];
    let pointValue = json["point"];
    let scoreValue = json["totalScore"];
    pointScoreBoard.setData(playerName,pointValue,scoreValue);
    requestStatusFromBackend();
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
    requestStatusFromBackend();
}

function backendIsReadyAndAwaitsInput(data)
{
    var json = JSON.parse(data);
    let throwSuggestion = json.targetRow;
    let suggestion = textSourceContainer.throwSuggestLabel + " " + throwSuggestion;
    notificationItemSlot.setThrowSuggestion(suggestion);
    setTurnControllerValues(json);
    dartsPointMultiColumnBody.state = "waitingForInput";
}

function setTurnControllerValues(json)
{
    singleColumnTurnController.leftButtonEnabled = json.canUndo;
    singleColumnTurnController.rightButtonEnabled = json.canRedo;
    singleColumnTurnController.currentRoundIndex = json.roundIndex;
    singleColumnTurnController.currentPlayer = json.playerName;
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
    notificationItemSlot.item.setCurrentWinner(winnerName);
}
