function initializeComponent()
{
    connectInterface();
    requestControllerValues();
}

function connectInterface()
{
    dartsSingleAttemptBody.requestControllerValues.connect(applicationInterface.assembleDartsTournamentValues);
    dartsSingleAttemptBody.requestSingleAttemptPoints.connect(
                applicationInterface.handleRequestForDartsSingleAttemptPoints);
    applicationInterface.sendAssembledDartsSingleAttemptPoints.connect(
                recieveDartsSingleAttemptPoints);
    applicationInterface.dartsControllerIsReset.connect(reinitialize);
    applicationInterface.dartsSingleAttemptPointControllerIsReady.connect(controllerIsInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.connect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.connect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.connect(handleDartsMetaData);
    dartsSingleAttemptBody.requestStart.connect(applicationInterface.handleRequestStart);
    dartsSingleAttemptBody.requestStop.connect(applicationInterface.handleRequestStop);
    dartsSingleAttemptBody.requestRestart.connect(applicationInterface.handleRestartTournament);
    dartsSingleAttemptBody.sendInput.connect(applicationInterface.handleDartsSingleAttemptInput);
    dartsSingleAttemptBody.requestStatusFromBackend.connect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedSingleAttemptPoint.connect(backendRemovedPoint);
    dartsSingleAttemptBody.requestUndo.connect(applicationInterface.handleUndoRequest);
    dartsSingleAttemptBody.requestRedo.connect(applicationInterface.handleRedoRequest);
    pointKeyPad.sendInput.connect(handlePointKeyPadInput);
    applicationInterface.controllerAwaitsInput.connect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerAddedDartsSingleAttemptPoint.connect(extractPointScoreFromJson);
}

function disConnectInterface()
{
    dartsSingleAttemptBody.requestControllerValues.disconnect(applicationInterface.assembleDartsTournamentValues);
    dartsSingleAttemptBody.requestSingleAttemptPoints.disconnect(
                applicationInterface.handleRequestForDartsSingleAttemptPoints);
    applicationInterface.sendAssembledDartsSingleAttemptPoints.disconnect(
                recieveDartsSingleAttemptPoints);
    applicationInterface.dartsSingleAttemptPointControllerIsReady.disconnect(controllerIsInitializedAndReady);
    applicationInterface.controllerHasDeclaredAWinner.disconnect(backendDeclaredAWinner);
    applicationInterface.controllerIsStopped.disconnect(backendIsStopped);
    applicationInterface.sendDartsTournamentData.disconnect(handleDartsMetaData);
    dartsSingleAttemptBody.requestStart.disconnect(applicationInterface.handleRequestStart);
    dartsSingleAttemptBody.requestStop.disconnect(applicationInterface.handleRequestStop);
    dartsSingleAttemptBody.requestRestart.disconnect(applicationInterface.handleRestartTournament);
    dartsSingleAttemptBody.sendInput.disconnect(applicationInterface.handleDartsSingleAttemptInput);
    dartsSingleAttemptBody.requestStatusFromBackend.disconnect(applicationInterface.handleControllerStateRequest);
    applicationInterface.dartsControllerRemovedSingleAttemptPoint.disconnect(backendRemovedPoint);
    dartsSingleAttemptBody.requestUndo.disconnect(applicationInterface.handleUndoRequest);
    dartsSingleAttemptBody.requestRedo.disconnect(applicationInterface.handleRedoRequest);
    pointKeyPad.sendInput.disconnect(handlePointKeyPadInput);
    applicationInterface.controllerAwaitsInput.disconnect(backendIsReadyAndAwaitsInput);
    applicationInterface.dartsControllerAddedDartsSingleAttemptPoint.disconnect(extractPointScoreFromJson);
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
    dartsSingleAttemptBody.state = "ready";
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
    dartsSingleAttemptBody.requestStatusFromBackend();
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
    if(dartsSingleAttemptBody.state === "ready")
        dartsSingleAttemptBody.state = "stopped";
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
    dartsSingleAttemptBody.state = "waitingForInput";
}

function setTurnControllerValues(json)
{
    singleAttemptTurnController.leftButtonEnabled = json.canUndo;
    singleAttemptTurnController.rightButtonEnabled = json.canRedo;
    singleAttemptTurnController.currentRoundIndex = json.roundIndex;
    singleAttemptTurnController.currentPlayer = json.playerName;
}

function handlePointKeyPadInput(value,keyCode){
    dartsSingleAttemptBody.state = "waitingForInputConfirmation";
    var obj = {
        point : value,
        modKeyCode : keyCode
    };
    var json = JSON.stringify(obj);
    dartsSingleAttemptBody.sendInput(json);
}

function backendIsStopped()
{
    if(dartsSingleAttemptBody.state !== "preRestart")
        dartsSingleAttemptBody.state = "stopped";
}

function backendDeclaredAWinner(data)
{
    var json = JSON.parse(data);
    tournamentMetaData.determinedWinner = json.winner;
    dartsSingleAttemptBody.state = "winner";
}

function undoClicked()
{
    dartsSingleAttemptBody.state = "waitingForInputConfirmation";
    requestUndo();
}

function redoClicked()
{
    dartsSingleAttemptBody.state = "waitingForInputConfirmation";
    requestRedo();
}

function setWinnerText()
{
    var winnerName = textSourceContainer.winnerLabel + " " +
            tournamentMetaData.determinedWinner;
    notificationItemSlot.item.setCurrentWinner(winnerName);
}
